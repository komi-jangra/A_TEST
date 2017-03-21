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
 *  ID: $ $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:56  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:30  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 02:56:41  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/26 00:15:13  randresol
 * LOG: Start Japan SS7 implementation
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_TCAP_TTC_H_
#define _ITS_TCAP_TTC_H_

#ident "$Id: tcap.h,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $"

#include <japan/sccp.h>

/*
 *  Q.773 Tags
 */

#define OTID_IDENT_TTC      (0x48U)
#define DTID_IDENT_TTC      (0x49U)
#define PABT_IDENT_TTC      (0x4AU)
#define DIALOG_IDENT_TTC    (0x6BU)
#define CSEQ_IDENT_TTC      (0x6CU)

/*
 * Component Sub Layer Primitive Types:
 *
 * Primitives for Dialogue Handling (Table 1/Q.771)
 * and Component Handling (Table 2/Q.771) :
 */
#define TCAP_PT_TC_UNI_TTC          (0x61U)     /* TC-Uni */
#define TCAP_PT_TC_BEGIN_TTC        (0x62U)     /* TC-Begin */
#define TCAP_PT_TC_END_TTC          (0x64U)     /* TC-End */
#define TCAP_PT_TC_CONTINUE_TTC     (0x65U)     /* TC-Continue */
#define TCAP_PT_TC_P_ABORT_TTC      (0x67U)     /* TC-P-Abort */
#define TCAP_PT_TC_U_ABORT_TTC      (0x68U)     /* TC-U-Abort */
#define TCAP_PT_TC_NOTICE_TTC       (0x69U)     /* TC-Notice */

/*
 * Q.771 (Note: TC-Timer-Reset is only valid with ITU White Book 97).
 */
#define TCAP_PT_TC_INVOKE_TTC         (0xA1U)     /* TC-Invoke */
#define TCAP_PT_TC_RESULT_L_TTC       (0xA2U)     /* TC-Result-L */
#define TCAP_PT_TC_U_ERROR_TTC        (0xA3U)     /* TC-U-Error */
#define TCAP_PT_TC_R_REJECT_TTC       (0xA4U)     /* TC-R-Reject */
#define TCAP_PT_TC_RESULT_NL_TTC      (0xA7U)     /* TC-Result-NL */
#define TCAP_PT_TC_L_CANCEL_TTC       (0xA8U)     /* TC-L-Cancel */
#define TCAP_PT_TC_U_CANCEL_TTC       (0xA9U)     /* TC-U-Cancel */
#define TCAP_PT_TC_L_REJECT_TTC       (0xAAU)     /* TC-L-Reject */
#define TCAP_PT_TC_U_REJECT_TTC       (0xABU)     /* TC-U-Reject */
#define TCAP_PT_TC_TIMER_RESET_TTC    (0xACU)     /* TC-Timer-Reset */

/*
 * Primitive parameter name definitions
 */

/*
 * Q.773 definitions:
 */
#define TCAP_PN_INVOKE_TAG_TTC         (0x02U)  /* Q.773 invoke tag */
#define TCAP_PN_LOCAL_OP_TAG_TTC       (0x02U)  /* Q.773 local operation tag */
#define TCAP_PN_GLOBAL_OP_TAG_TTC      (0x06U)  /* Q.773 global operation tag */
#define TCAP_PN_LOCAL_ERR_TAG_TTC      (0x02U)  /* Q.773 local error code tag */
#define TCAP_PN_GLOBAL_ERR_TAG_TTC     (0x06U)  /* Q.773 global error code tag */

/*
 * TCAP_PN_ABORT_REASON values (White Book):
 */
#define TCAP_UABT_AC_NOT_SUP_TTC      (1)     /* Application context not supported */
#define TCAP_UABT_DLG_REFUSED_TTC     (2)     /* Dialogue refused */
#define TCAP_UABT_USER_DEFINED_TTC    (3)     /* User defined */

/*
 * TCAP_PN_P_ABORT values:
 * (In addition to those defined in Table 12/Q.773).
 */
#define TCAP_PABT_ABNORMAL_DLG_TTC    (126)
#define TCAP_PABT_NO_COMMON_DLG_TTC   (127)

/*
 * P-ABORT values
 */
#define TCAP_ABT_REASON_UNREC_MSG_TYPE_TTC            (0x00U)
#define TCAP_ABT_REASON_UNREC_TRANS_ID_TTC            (0x01U)
#define TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_TTC   (0x02U)
#define TCAP_ABT_REASON_INCORRECT_TRANS_PORT_TTC      (0x03U)
#define TCAP_ABT_REASON_RES_UNAVAIL_TTC               (0x04U)

/*
 * Q.773 reject types
 */
#define TCAP_PROB_GENERAL_TTC         (0x00U)
#define TCAP_PROB_INVOKE_TTC          (0x01U)
#define TCAP_PROB_RETURN_RES_TTC      (0x02U)
#define TCAP_PROB_RETURN_ERR_TTC      (0x03U)

/*
 * Q.773 reject codes
 */
#define TCAP_PROB_SPEC_GEN_UNREC_COMP_TTC                (0x00U) 
#define TCAP_PROB_SPEC_GEN_MISTYPED_COMP_TTC             (0x01U)
#define TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_TTC         (0x02U)    
#define TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_TTC          (0x00U) 
#define TCAP_PROB_SPEC_INV_UNREC_OP_CODE_TTC             (0x01U) 
#define TCAP_PROB_SPEC_INV_MISTYPED_PARAM_TTC            (0x02U) 
#define TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_TTC            (0x03U) 
#define TCAP_PROB_SPEC_INV_INITIATE_RELEASE_TTC          (0x04U) 
#define TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_TTC           (0x05U) 
#define TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_TTC      (0x06U) 
#define TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_TTC      (0x07U) 
#define TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_TTC           (0x00U) 
#define TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_TTC        (0x01U) 
#define TCAP_PROB_SPEC_RES_MISTYPED_PARAM_TTC            (0x02U) 
#define TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_TTC           (0x00U) 
#define TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_TTC      (0x01U) 
#define TCAP_PROB_SPEC_ERR_UNREC_ERROR_TTC               (0x02U) 
#define TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_TTC          (0x03U) 
#define TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_TTC            (0x04U) 

/*
 * Get the rest from the ITU definitions.
 */
#include <tcap_cmn.h>

/*
 * the use of short names is deprecated and may be removed in
 * a future release.
 */
#include <tcap_sn.h>

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

/*
 * published API
 */
SS7DLLAPI int TCAP_SendComponent_TTC(ITS_HANDLE handle,
                                     ITS_HDR *hdr,
                                     TCAP_CPT *cpt);
SS7DLLAPI int TCAP_ReceiveComponent_TTC(ITS_HANDLE handle,
                                        ITS_EVENT *event,
                                        ITS_HDR *hdr, TCAP_CPT *cpt);

SS7DLLAPI int TCAP_AllocateDialogueId_TTC(ITS_HANDLE handle,
                                          ITS_CTXT *dialogue_id);

SS7DLLAPI int TCAP_SendDialogue_TTC(ITS_HANDLE handle,
                                    ITS_HDR *hdr,
                                    TCAP_DLG *dlg);
SS7DLLAPI int TCAP_ReceiveDialogue_TTC(ITS_HANDLE handle,
                                       ITS_EVENT *event,
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
SS7DLLAPI int TCAP_FetchAddrs_TTC(ITS_HANDLE handle, ITS_CTXT did,
                                  SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
SS7DLLAPI int TCAP_SetAddrs_TTC(ITS_HANDLE handle, ITS_CTXT did,
                                SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
SS7DLLAPI int TCAP_FetchQOS_TTC(ITS_HANDLE handle, ITS_CTXT did,
                                DLG_QOS *qos);
SS7DLLAPI int TCAP_SetQOS_TTC(ITS_HANDLE handle, ITS_CTXT did,
                              DLG_QOS *qos);


/*
 * this is only for TTC.  The default variant is White Book.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define TTC_TCAP_BLUE_BOOK        ITS_FIRST_GEN
#define TTC_TCAP_WHITE_BOOK       ITS_SECOND_GEN
#define TTC_TCAP_WHITE_BOOK_97    ITS_THIRD_GEN

SS7DLLAPI int TCAP_SetVariant_TTC(int variant);
SS7DLLAPI int TCAP_GetVariant_TTC();

/*
 * this needs to be a well known global to control which TCAP
 * variant is in use.  Users should NOT change this directly
 * (use the functions instead).
 */
SS7DLLAPI extern int  TTC_TCAP_Variant;

/*
 * users should not invoke these functions
 */
SS7DLLAPI int TCAP_ComponentSanityCheck_TTC(TCAP_CPT* cpt);
SS7DLLAPI int TCAP_DialogueSanityCheck_TTC(TCAP_DLG* dlg);

/*
 * these are for vendor implementations to check messages
 * that only originate from the stack.  Users should not
 * call either function directly.
 */
SS7DLLAPI int TCAP_VendorComponentSanityCheck_TTC(TCAP_CPT* cpt);
SS7DLLAPI int TCAP_VendorDialogueSanityCheck_TTC(TCAP_DLG* dlg);

#if defined(INCLUDE_CODEC)

#include <itu/ITU-TCAP-APDU-types.h>
#include <itu/ITU-TCAP-types.h>

SS7DLLAPI struct type_ITU__TCAP_ComponentPDU *
TCAP_CvtCPTToComponentPDU_CCITT(TCAP_CPT *cpt);
SS7DLLAPI int
TCAP_CvtComponentPDUToCPT_CCITT(TCAP_CPT *cpt,
                                struct type_ITU__TCAP_ComponentPDU *comp);

SS7DLLAPI struct type_ITU__TCAP_MessageType *
TCAP_CvtDLGToMessage_CCITT(TCAP_DLG *dlg,
                           ITS_INT ltid, ITS_INT rtid, ITS_UINT rtidLen,
                           int variant);
SS7DLLAPI int
TCAP_CvtMessageToDLG_CCITT(TCAP_DLG *dlg,
                           struct type_ITU__TCAP_MessageType *dialog,
                           int variant);

/* Manual TCAP-Codec Related */

SS7DLLAPI enum ParseCode
TCAP_FindParts_CCITT(ITS_OCTET *pdup, int wlen,
                     ITS_OCTET **tp, ITS_OCTET **dp, ITS_OCTET **cp);

SS7DLLAPI int 
TCAP_GetSub_TTC(ITS_OCTET *data, ITS_OCTET *stop);

SS7DLLAPI int 
TCAP_GetTag_TTC(ITS_OCTET *data, ITS_UINT *retTag, 
                ITS_OCTET *stop);

SS7DLLAPI int
TCAP_GetLength_TTC(ITS_OCTET *data, ITS_UINT *retLen,
                   ITS_OCTET *stop, ITS_BOOLEAN isConstructed);

SS7DLLAPI int
TCAP_SetLength_TTC(ITS_OCTET *data, ITS_UINT len, 
                   ITS_BOOLEAN toSet);

SS7DLLAPI ITS_BOOLEAN
TCAP_GetTID_TTC(ITS_OCTET** buf, ITS_UINT *tid, 
                ITS_UINT *tidLen);

SS7DLLAPI int
TCAP_CvtDataToCPT_CCITT(TCAP_CPT *cpt, ITS_OCTET *cp,
                        ITS_UINT cTag, ITS_USHORT cLen);

SS7DLLAPI int
TCAP_CvtDataToDLG_CCITT(TCAP_DLG *dlg, ITS_OCTET *pType,
                        ITS_OCTET *tp, ITS_OCTET *dp,
                        ITS_BOOLEAN cpPresent, ITS_USHORT len,
                        int variant);

SS7DLLAPI int
TCAP_CvtDLGToData_CCITT(TCAP_DLG *dlg, ITS_OCTET *tp, 
                        ITS_UINT *tpLen, ITS_OCTET *cpList, 
                        ITS_UINT cptsLen, ITS_INT ltid,
                        ITS_INT rtid, ITS_UINT rtidLen, 
                        int variant);

SS7DLLAPI int
TCAP_CvtCPTToData_CCITT(TCAP_CPT *cpt, ITS_OCTET *cp, 
                        ITS_UINT *cpLen);

#endif /* defined(INCLUDE_CODEC) */

#ifdef __cplusplus
}
#endif

#endif /* _ITS_TCAP_TTC_H */
