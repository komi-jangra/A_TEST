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
 *  ID: $Id: tcap.h,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
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
 * LOG: Revision 8.4  2005/03/21 13:50:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.10.1  2004/09/21 06:59:17  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.8  2003/02/10 14:21:23  yranade
 * LOG: Rectified the Abort Cause Identifier.
 * LOG:
 * LOG: Revision 7.7  2003/02/05 14:00:22  yranade
 * LOG: Move FindParts to TCAP_FindParts, since it's in Global Scope.
 * LOG:
 * LOG: Revision 7.6  2003/02/05 12:54:54  yranade
 * LOG: Changes for Windows build.
 * LOG:
 * LOG: Revision 7.5  2003/02/04 07:16:49  yranade
 * LOG: Tcap-Manual Codec Integration.
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.3  2003/01/07 15:57:40  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2003/01/07 15:26:07  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/07/03 17:40:49  mmiers
 * LOG: More china changes
 * LOG:
 * LOG: Revision 6.2  2002/03/20 17:56:24  mmiers
 * LOG: Move the codecs back.  It's consistent, so I'll just deal
 * LOG: with the VFrame pain (ASN).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 20:02:52  mmiers
 * LOG: Avoid many version defines, destination parsing.
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
 * LOG: Revision 3.4  2001/03/15 21:02:45  omayor
 * LOG: Fix a few typos made during the inline conversion.
 * LOG:
 * LOG: Revision 3.3  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.2  2000/11/29 17:50:44  mmiers
 * LOG: Weird Cisco TCAP fix.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/07/14 17:24:30  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:28  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  2000/03/10 15:25:11  mmiers
 * LOG: GDI stubs is no longer needed.  Add functions similar to what we did
 * LOG: for DECSS7 to our vendor lib.  Update test to remove mem leak.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:04  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.58  1999/11/10 18:06:43  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.57  1999/10/05 16:11:27  rsonak
 * LOG:
 * LOG: Move the defines here from its.h
 * LOG:
 * LOG: Revision 1.56  1999/09/30 14:51:11  mmiers
 * LOG:
 * LOG:
 * LOG: Hack to get L_REJECT working with our stack.
 * LOG:
 * LOG: Revision 1.55  1999/09/24 22:18:19  mmiers
 * LOG:
 * LOG:
 * LOG: Commit the fix for AARE in U-ABORT situations.
 * LOG:
 * LOG: Revision 1.54  1999/09/10 23:11:07  mmiers
 * LOG:
 * LOG:
 * LOG: Split out blue book and white book variants.
 * LOG:
 * LOG: Revision 1.53  1999/09/08 15:21:31  ite
 * LOG:
 * LOG:
 * LOG: Change bad tag values, increase the size of operation and error.
 * LOG:
 * LOG: Revision 1.52  1999/08/27 16:51:37  mmiers
 * LOG:
 * LOG:
 * LOG: Split up the dialogue allocation into two families.
 * LOG:
 * LOG: Revision 1.51  1999/08/26 02:45:55  mmiers
 * LOG:
 * LOG:
 * LOG: Note that TCAP QOS is ignored on request for CONT, ABORT, END.
 * LOG:
 * LOG: Revision 1.50  1999/08/25 21:57:53  mmiers
 * LOG:
 * LOG:
 * LOG: Add a check for vendor sanity.
 * LOG:
 * LOG: Revision 1.49  1999/08/25 21:22:40  mmiers
 * LOG:
 * LOG:
 * LOG: Add error checking for components and dialogue (sanity checks).
 * LOG:
 * LOG: Revision 1.48  1999/08/19 22:33:11  mmiers
 * LOG:
 * LOG:
 * LOG: Remove dead parameter.
 * LOG:
 * LOG: Revision 1.47  1999/08/16 22:30:57  mmiers
 * LOG:
 * LOG:
 * LOG: Oops, watch placement of ifdef(__cplusplus)
 * LOG:
 * LOG: Revision 1.46  1999/08/03 16:19:52  mmiers
 * LOG:
 * LOG:
 * LOG: Adjustments for using ANSI SCCP with ITU TCAP.
 * LOG:
 * LOG: Revision 1.45  1999/08/03 14:23:27  mmiers
 * LOG:
 * LOG:
 * LOG: Fix this up for alternate family SCCP.
 * LOG:
 * LOG: Revision 1.44  1999/08/02 21:45:36  mmiers
 * LOG:
 * LOG:
 * LOG: Add the protocol family for typo fix.
 * LOG:
 * LOG: Revision 1.43  1999/08/02 21:44:56  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a typo
 * LOG:
 * LOG: Revision 1.42  1999/07/28 16:29:23  mmiers
 * LOG:
 * LOG:
 * LOG: Finish making this dual protocol safe.
 * LOG:
 * LOG: Revision 1.41  1999/07/28 02:40:36  mmiers
 * LOG:
 * LOG:
 * LOG: Start making this dual protocol safe.
 * LOG:
 * LOG: Revision 1.40  1999/07/26 21:41:34  mmiers
 * LOG:
 * LOG:
 * LOG: Add define for operation family - reply required.
 * LOG:
 * LOG: Revision 1.39  1999/07/19 16:49:56  mmiers
 * LOG:
 * LOG:
 * LOG: Change defines
 * LOG:
 * LOG: Revision 1.38  1999/07/06 21:03:48  labuser
 * LOG:
 * LOG: fhasle: Fixed bug for op code specifiers part of op Code family
 * LOG:         Connection Control.
 * LOG:
 * LOG: Revision 1.37  1999/06/23 22:58:56  mmiers
 * LOG:
 * LOG:
 * LOG: Have to watch where we define extern "C".
 * LOG:
 * LOG: Revision 1.36  1999/06/22 20:05:35  ite
 * LOG:
 * LOG:
 * LOG: Add padding to work around NMS packing.
 * LOG:
 * LOG: Revision 1.35  1999/06/22 19:52:21  labuser
 * LOG:
 * LOG: fhasle: Updated TCAP Notice structure.
 * LOG:
 * LOG: Revision 1.34  1999/06/18 22:50:55  mmiers
 * LOG:
 * LOG:
 * LOG: Update ITU definitions for sanity.
 * LOG:
 * LOG: Revision 1.33  1999/06/15 22:41:41  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build for function signatures, predefines.
 * LOG:
 * LOG: Revision 1.32  1999/06/14 15:49:45  mmiers
 * LOG:
 * LOG:
 * LOG: Add notice PTYPE for ANSI
 * LOG:
 * LOG: Revision 1.31  1999/05/27 16:15:10  mmiers
 * LOG:
 * LOG:
 * LOG: mark ANSI release specific error codes.
 * LOG:
 * LOG: Revision 1.30  1999/05/24 20:26:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add codec signatures to headers.
 * LOG:
 * LOG: Revision 1.29  1999/03/30 22:51:29  mmiers
 * LOG:
 * LOG:
 * LOG: Add abort causes.
 * LOG:
 * LOG: Revision 1.28  1999/03/29 22:50:31  mmiers
 * LOG:
 * LOG:
 * LOG: Change the ABORT comment.
 * LOG:
 * LOG: Revision 1.27  1999/03/17 15:10:06  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.26  1999/02/26 02:24:40  mmiers
 * LOG:
 * LOG:
 * LOG: Updated TCAP for CC builds.
 * LOG:
 * LOG: Revision 1.25  1999/02/17 20:46:33  mmiers
 * LOG:
 * LOG:
 * LOG: Add more definitions for ITU TCAP.
 * LOG:
 * LOG: Revision 1.24  1999/02/17 02:31:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add ITU reject classes and codes.
 * LOG:
 * LOG: Revision 1.23  1999/02/13 00:44:19  mmiers
 * LOG:
 * LOG:
 * LOG: Prepare for ITU TCAP over ANSI SCCP and vice-versa.
 * LOG:
 * LOG: Revision 1.22  1999/02/12 23:40:24  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.21  1999/01/27 17:59:27  mmiers
 * LOG:
 * LOG:
 * LOG: Add DPC/OPC fields to TCAP structure.
 * LOG:
 * LOG: Revision 1.20  1998/10/14 23:30:41  mmiers
 * LOG: return type of TCAP_Terminate() was incorrect.  Should have been void.
 * LOG:
 * LOG: Revision 1.19  1998/10/02 04:09:56  mmiers
 * LOG: Add INVOKE direction handling to TCAP.
 * LOG:
 * LOG: Revision 1.18  1998/06/17 22:20:17  mmiers
 * LOG: clean up the tests a little bit.  Move the LLog crap into the compat
 * LOG: lib.
 * LOG:
 * LOG: Revision 1.17  1998/06/01 23:18:15  mmiers
 * LOG: More documentation.  Custom build steps for TCAP, SCCP.
 * LOG:
 * LOG: Revision 1.16  1998/05/31 22:20:11  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.15  1998/05/20 21:46:37  ahanda
 * LOG: Put MSG_TYPE and DATA macro args inside parens.
 * LOG:
 * LOG: Revision 1.14  1998/05/19 21:27:41  mmiers
 * LOG: Almost finished with TCAP++.
 * LOG:
 * LOG: Revision 1.13  1998/05/19 15:49:27  mmiers
 * LOG: Fix the namespace problems.
 * LOG:
 * LOG: Revision 1.12  1998/05/19 02:38:48  mmiers
 * LOG: Modify itu/tcap.h to remove the redundant structures (such as rrl/rrnl,
 * LOG: uerror/lerror, etc.).  If you have problems with this, update tcap.h
 * LOG: using "cvs update -r 1.11 tcap.h (for itu/tcap.h).
 * LOG:
 * LOG: Revision 1.11  1998/05/05 00:00:03  mmiers
 * LOG: Add new signatures, remove TCSM code from tcap.h.
 * LOG:
 * LOG: Revision 1.10  1998/04/29 21:10:16  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.9  1998/04/28 22:51:58  mmiers
 * LOG: Complete the pepsy<->ITS conversion code.  This is pretty close to
 * LOG: actually working, now.  Must fill in the context management functions
 * LOG: and then debug.
 * LOG:
 * LOG: Revision 1.8  1998/04/23 17:04:01  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.7  1998/04/23 00:11:30  mmiers
 * LOG: Working on TCAP now.
 * LOG:
 * LOG: Revision 1.6  1998/04/22 20:49:03  mmiers
 * LOG: TCAP cleanup.  I don't think the TCSM stuff is at all useful;
 * LOG: more thought needs to go into how to manage transactions when
 * LOG: single threaded.  When multi-threaded, unless processing is
 * LOG: synchronous, transactions are handled exactly the same way
 * LOG: as single threaded.
 * LOG:
 * LOG: Revision 1.5  1998/04/03 16:50:08  mmiers
 * LOG: Update tcap internals.
 * LOG:
 * LOG: Revision 1.4  1998/02/25 17:58:47  mmiers
 * LOG: Move CANCEL to component type (it's not a package).
 * LOG:
 * LOG: Revision 1.3  1998/02/24 17:17:13  ite
 * LOG: Add more ANSI error codes to the header.
 * LOG:
 * LOG: Revision 1.2  1998/02/11 00:15:59  mmiers
 * LOG: PP, not PPP
 * LOG:
 * LOG: Revision 1.1  1998/02/10 22:32:09  mmiers
 * LOG: Separate out the PART specific stuff from its.h.  Everything is now in
 * LOG: its appropriate place.  The TCAP headers moved from common to TCAP.  The
 * LOG: state machine code has been added to the tree.
 * LOG:
 * LOG: Revision 1.11  1998/02/05 16:02:45  ite
 * LOG: Changed name cptClass to opClass (C++ only).
 * LOG:
 * LOG: Revision 1.10  1998/02/05 01:44:30  ite
 * LOG: Added #if defined(_cplusplus) to solve class keyword issue.
 * LOG:
 * LOG: Revision 1.9  1998/02/04 23:26:00  rsonak
 * LOG: Modifications (including comments, no less) for DEC SS7 (ANSI related).
 * LOG:
 * LOG: Revision 1.8  1998/02/04 18:52:57  ite
 * LOG: sccp.h: Modify macros for correct behavior.
 * LOG: tcap.h: Correct usages, add some definitions for ANSI.
 * LOG:
 * LOG: Revision 1.7  1998/01/28 23:59:21  rsonak
 * LOG: Added USER_DEFINED_TYPE
 * LOG:
 * LOG: Revision 1.6  1998/01/28 23:57:59  rsonak
 * LOG: Modifications
 * LOG:
 * LOG: Revision 1.5  1998/01/28 23:17:01  rsonak
 * LOG: Added the USER_DEFINED_TYPE primitive
 * LOG:
 * LOG: Revision 1.4  1998/01/28 02:01:00  rsonak
 * LOG: Update from NMS integration.
 * LOG:
 * LOG: Revision 1.3  1998/01/27 15:42:18  mmiers
 * LOG: Modifications for NMS
 * LOG:
 * LOG: Revision 1.2  1998/01/12 16:23:11  mmiers
 * LOG: Add definitions for ANSI TCAP.
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

#ifndef _ITS_TCAP_CCITT_H_
#define _ITS_TCAP_CCITT_H_

#ident "$Id: tcap.h,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $"

#if !defined(USE_ANSI_SCCP)

#include <itu/sccp.h>

#else /* USE_ITU_SCCP */

#undef CCITT
#if !defined(ANSI)
#define ANSI 1
#endif
#include <ansi/sccp.h>
#undef ANSI
#define CCITT 1

#endif /* defined(USE_ANSI_SCCP) */

/*
 *  Q.773 Tags
 */

#define OTID_IDENT_CCITT      (0x48U)
#define DTID_IDENT_CCITT      (0x49U)
#define PABT_IDENT_CCITT      (0x4AU)
#define DIALOG_IDENT_CCITT    (0x6BU)
#define CSEQ_IDENT_CCITT      (0x6CU)

/*
 * Component Sub Layer Primitive Types:
 *
 * Primitives for Dialogue Handling (Table 1/Q.771)
 * and Component Handling (Table 2/Q.771) :
 */
#define TCAP_PT_TC_UNI_CCITT          (0x61U)     /* TC-Uni */
#define TCAP_PT_TC_BEGIN_CCITT        (0x62U)     /* TC-Begin */
#define TCAP_PT_TC_END_CCITT          (0x64U)     /* TC-End */
#define TCAP_PT_TC_CONTINUE_CCITT     (0x65U)     /* TC-Continue */
#define TCAP_PT_TC_P_ABORT_CCITT      (0x67U)     /* TC-P-Abort */
#define TCAP_PT_TC_U_ABORT_CCITT      (0x68U)     /* TC-U-Abort */
#define TCAP_PT_TC_NOTICE_CCITT       (0x69U)     /* TC-Notice */

/*
 * Q.771 (Note: TC-Timer-Reset is only valid with ITU White Book 97).
 */
#define TCAP_PT_TC_INVOKE_CCITT         (0xA1U)     /* TC-Invoke */
#define TCAP_PT_TC_RESULT_L_CCITT       (0xA2U)     /* TC-Result-L */
#define TCAP_PT_TC_U_ERROR_CCITT        (0xA3U)     /* TC-U-Error */
#define TCAP_PT_TC_R_REJECT_CCITT       (0xA4U)     /* TC-R-Reject */
#define TCAP_PT_TC_RESULT_NL_CCITT      (0xA7U)     /* TC-Result-NL */
#define TCAP_PT_TC_L_CANCEL_CCITT       (0xA8U)     /* TC-L-Cancel */
#define TCAP_PT_TC_U_CANCEL_CCITT       (0xA9U)     /* TC-U-Cancel */
#define TCAP_PT_TC_L_REJECT_CCITT       (0xAAU)     /* TC-L-Reject */
#define TCAP_PT_TC_U_REJECT_CCITT       (0xABU)     /* TC-U-Reject */
#define TCAP_PT_TC_TIMER_RESET_CCITT    (0xACU)     /* TC-Timer-Reset */

/*
 * Primitive parameter name definitions
 */

/*
 * Q.773 definitions:
 */
#define TCAP_PN_INVOKE_TAG_CCITT         (0x02U)  /* Q.773 invoke tag */
#define TCAP_PN_LOCAL_OP_TAG_CCITT       (0x02U)  /* Q.773 local operation tag */
#define TCAP_PN_GLOBAL_OP_TAG_CCITT      (0x06U)  /* Q.773 global operation tag */
#define TCAP_PN_LOCAL_ERR_TAG_CCITT      (0x02U)  /* Q.773 local error code tag */
#define TCAP_PN_GLOBAL_ERR_TAG_CCITT     (0x06U)  /* Q.773 global error code tag */

/*
 * TCAP_PN_ABORT_REASON values (White Book):
 */
#define TCAP_UABT_AC_NOT_SUP_CCITT      (1)     /* Application context not supported */
#define TCAP_UABT_DLG_REFUSED_CCITT     (2)     /* Dialogue refused */
#define TCAP_UABT_USER_DEFINED_CCITT    (3)     /* User defined */

/*
 * TCAP_PN_P_ABORT values:
 * (In addition to those defined in Table 12/Q.773).
 */
#define TCAP_PABT_ABNORMAL_DLG_CCITT    (126)
#define TCAP_PABT_NO_COMMON_DLG_CCITT   (127)

/*
 * P-ABORT values
 */
#define TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT            (0x00U)
#define TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT            (0x01U)
#define TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_CCITT   (0x02U)
#define TCAP_ABT_REASON_INCORRECT_TRANS_PORT_CCITT      (0x03U)
#define TCAP_ABT_REASON_RES_UNAVAIL_CCITT               (0x04U)

/*
 * Q.773 reject types
 */
#define TCAP_PROB_GENERAL_CCITT         (0x00U)
#define TCAP_PROB_INVOKE_CCITT          (0x01U)
#define TCAP_PROB_RETURN_RES_CCITT      (0x02U)
#define TCAP_PROB_RETURN_ERR_CCITT      (0x03U)

/*
 * Q.773 reject codes
 */
#define TCAP_PROB_SPEC_GEN_UNREC_COMP_CCITT                (0x00U) 
#define TCAP_PROB_SPEC_GEN_MISTYPED_COMP_CCITT             (0x01U)
#define TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_CCITT         (0x02U)    
#define TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_CCITT          (0x00U) 
#define TCAP_PROB_SPEC_INV_UNREC_OP_CODE_CCITT             (0x01U) 
#define TCAP_PROB_SPEC_INV_MISTYPED_PARAM_CCITT            (0x02U) 
#define TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_CCITT            (0x03U) 
#define TCAP_PROB_SPEC_INV_INITIATE_RELEASE_CCITT          (0x04U) 
#define TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_CCITT           (0x05U) 
#define TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_CCITT      (0x06U) 
#define TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_CCITT      (0x07U) 
#define TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_CCITT           (0x00U) 
#define TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_CCITT        (0x01U) 
#define TCAP_PROB_SPEC_RES_MISTYPED_PARAM_CCITT            (0x02U) 
#define TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_CCITT           (0x00U) 
#define TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_CCITT      (0x01U) 
#define TCAP_PROB_SPEC_ERR_UNREC_ERROR_CCITT               (0x02U) 
#define TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_CCITT          (0x03U) 
#define TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_CCITT            (0x04U) 

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
SS7DLLAPI int TCAP_SendComponent_CCITT(ITS_HANDLE handle,
                                       ITS_HDR *hdr,
                                       TCAP_CPT *cpt);
SS7DLLAPI int TCAP_ReceiveComponent_CCITT(ITS_HANDLE handle,
                                          ITS_EVENT *event,
                                          ITS_HDR *hdr, TCAP_CPT *cpt);

SS7DLLAPI int TCAP_AllocateDialogueId_CCITT(ITS_HANDLE handle,
                                            ITS_CTXT *dialogue_id);

SS7DLLAPI int TCAP_SendDialogue_CCITT(ITS_HANDLE handle,
                                      ITS_HDR *hdr,
                                      TCAP_DLG *dlg);
SS7DLLAPI int TCAP_ReceiveDialogue_CCITT(ITS_HANDLE handle,
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
SS7DLLAPI int TCAP_FetchAddrs_CCITT(ITS_HANDLE handle, ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
SS7DLLAPI int TCAP_SetAddrs_CCITT(ITS_HANDLE handle, ITS_CTXT did,
                                  SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
SS7DLLAPI int TCAP_FetchQOS_CCITT(ITS_HANDLE handle, ITS_CTXT did,
                                  DLG_QOS *qos);
SS7DLLAPI int TCAP_SetQOS_CCITT(ITS_HANDLE handle, ITS_CTXT did,
                                DLG_QOS *qos);


/*
 * this is only for CCITT.  The default variant is White Book.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define CCITT_TCAP_BLUE_BOOK        ITS_FIRST_GEN
#define CCITT_TCAP_WHITE_BOOK       ITS_SECOND_GEN
#define CCITT_TCAP_WHITE_BOOK_97    ITS_THIRD_GEN

SS7DLLAPI int TCAP_SetVariant_CCITT(int variant);
SS7DLLAPI int TCAP_GetVariant_CCITT();

/*
 * this needs to be a well known global to control which TCAP
 * variant is in use.  Users should NOT change this directly
 * (use the functions instead).
 */
SS7DLLAPI extern int  CCITT_TCAP_Variant;

/*
 * users should not invoke these functions
 */
SS7DLLAPI int TCAP_ComponentSanityCheck_CCITT(TCAP_CPT* cpt);
SS7DLLAPI int TCAP_DialogueSanityCheck_CCITT(TCAP_DLG* dlg);

/*
 * these are for vendor implementations to check messages
 * that only originate from the stack.  Users should not
 * call either function directly.
 */
SS7DLLAPI int TCAP_VendorComponentSanityCheck_CCITT(TCAP_CPT* cpt);
SS7DLLAPI int TCAP_VendorDialogueSanityCheck_CCITT(TCAP_DLG* dlg);

SS7DLLAPI int TCAP_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                ITS_OCTET *bytes, ITS_USHORT len,
                                TCAP_PPrintProc paramPrint);

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
TCAP_GetSub_CCITT(ITS_OCTET *data, ITS_OCTET *stop);

SS7DLLAPI int 
TCAP_GetTag_CCITT(ITS_OCTET *data, ITS_UINT *retTag, 
                  ITS_OCTET *stop);

SS7DLLAPI int
TCAP_GetLength_CCITT(ITS_OCTET *data, ITS_UINT *retLen,
                     ITS_OCTET *stop, ITS_BOOLEAN isConstructed);

SS7DLLAPI int
TCAP_SetLength_CCITT(ITS_OCTET *data, ITS_UINT len, 
                     ITS_BOOLEAN toSet);

SS7DLLAPI ITS_BOOLEAN
TCAP_GetTID_CCITT(ITS_OCTET** buf, ITS_UINT *tid, 
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

#endif /* _ITS_TCAP_CCITT_H */
