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
 *  ID: $Id: sccp.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
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
 * LOG: Revision 9.1.8.1  2005/09/21 13:00:08  adutta
 * LOG: API to register appliation with SCCP
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:22  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.10.2  2004/09/21 06:56:54  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.3.10.1  2004/01/27 05:56:51  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.2  2003/01/06 22:27:42  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/29 22:39:36  mmiers
 * LOG: Change signature
 * LOG:
 * LOG: Revision 6.2  2002/03/21 20:57:40  mmiers
 * LOG: Add CPC API for SCCP.  Let DSM have duplicate keys (albeit
 * LOG: under user management).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.9  2001/12/19 17:22:16  mmiers
 * LOG: Move all callbacks to vframe
 * LOG:
 * LOG: Revision 5.8  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.7  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.5  2001/10/08 20:08:02  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.4  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.3  2001/09/06 17:24:39  mmiers
 * LOG: Closing in.
 * LOG:
 * LOG: Revision 5.2  2001/08/30 15:14:13  labuser
 * LOG: Add LUDT/LUDTS function prototypes.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.5  2001/06/19 23:26:38  mmiers
 * LOG: Begin deprecation of short form names.
 * LOG:
 * LOG: Revision 4.4  2001/06/19 20:09:18  mmiers
 * LOG: rename struct (more generic).
 * LOG:
 * LOG: Revision 4.3  2001/06/11 21:31:47  mmiers
 * LOG: Add label to callback.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:51:44  mmiers
 * LOG: User requested stuff (user intervention).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/04/03 17:43:04  mmiers
 * LOG: Mispelled attribute.
 * LOG:
 * LOG: Revision 3.3  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.2  2000/10/04 17:12:13  omayor
 * LOG: Added LUDT and LUDTS to ITU SCCP.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:27  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.63  1999/11/10 18:06:43  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.62  1999/10/05 16:11:06  rsonak
 * LOG:
 * LOG: Move the defines here from its.h
 * LOG:
 * LOG: Revision 1.61  1999/10/05 15:19:58  mmiers
 * LOG:
 * LOG:
 * LOG: Move protocol source defines to their respective files.
 * LOG:
 * LOG: Revision 1.60  1999/08/30 15:53:28  mmiers
 * LOG:
 * LOG:
 * LOG: Essentially satisfies Hubert's objections to the OO model.
 * LOG:
 * LOG: Revision 1.59  1999/08/27 21:27:20  mmiers
 * LOG:
 * LOG:
 * LOG: Change the point code format order for ANSI
 * LOG:
 * LOG: Revision 1.58  1999/08/27 00:40:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add the message ies as well.
 * LOG:
 * LOG: Revision 1.57  1999/08/26 23:28:40  labuser
 * LOG:
 * LOG:
 * LOG: Give complete called party addr to global title translator.
 * LOG:
 * LOG: Revision 1.56  1999/07/09 16:11:32  mmiers
 * LOG:
 * LOG:
 * LOG: Make this dual-protocol safe.
 * LOG:
 * LOG: Revision 1.55  1999/06/28 20:19:19  mmiers
 * LOG:
 * LOG:
 * LOG: Add a destination point code member to the GTT callback data.
 * LOG:
 * LOG: Revision 1.54  1999/06/23 19:58:34  mmiers
 * LOG:
 * LOG:
 * LOG: Slight modification to handle MTP3 modifications (include syntax).
 * LOG:
 * LOG: Revision 1.53  1999/06/22 16:17:04  mmiers
 * LOG:
 * LOG:
 * LOG: Add in global title translation.
 * LOG:
 * LOG: Revision 1.52  1999/03/17 18:41:56  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol updates.
 * LOG:
 * LOG: Revision 1.51  1999/03/17 15:10:06  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.50  1999/03/12 23:24:44  mmiers
 * LOG:
 * LOG:
 * LOG: Finish dual protocol family support.
 * LOG:
 * LOG: Revision 1.49  1999/02/12 23:40:23  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.48  1998/11/18 18:35:02  jpakrasi
 * LOG: Added the SSN number for SMC, to the list of SSN's.
 * LOG:
 * LOG: Revision 1.47  1998/11/12 00:55:35  mmiers
 * LOG: Add GTT to C++.
 * LOG:
 * LOG: Revision 1.46  1998/11/11 00:44:45  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.45  1998/11/10 00:20:23  mmiers
 * LOG: Add ITU only parameter.
 * LOG:
 * LOG: Revision 1.44  1998/11/05 23:27:48  mmiers
 * LOG: Changed signatures of SCCP_SendUIS/UOS/Congestion.
 * LOG:
 * LOG: Revision 1.43  1998/10/28 23:52:48  mmiers
 * LOG: Update for SCCP SCMG.
 * LOG:
 * LOG: Revision 1.42  1998/10/27 17:05:44  mmiers
 * LOG: Move some functions/signatures around so that we can share code.
 * LOG:
 * LOG: Revision 1.41  1998/10/21 15:10:53  whu
 * LOG: Change syntax of MTP3 include.
 * LOG:
 * LOG: Revision 1.40  1998/10/20 00:59:35  mmiers
 * LOG: Missing parens in RN_SET_REF_NUM().
 * LOG:
 * LOG: Revision 1.39  1998/10/19 00:39:37  mmiers
 * LOG: Add protocol class mask.
 * LOG:
 * LOG: Revision 1.38  1998/10/15 23:15:29  mmiers
 * LOG: Add C++ for MTP3.  Add routing label to SCCP.
 * LOG:
 * LOG: Revision 1.37  1998/10/01 16:55:15  mmiers
 * LOG: ITU point code macros were backwards.
 * LOG:
 * LOG: Revision 1.36  1998/09/30 02:40:01  mmiers
 * LOG: Updates for SCCP.  I think I've got the compromises for SCCP routing
 * LOG: down.  Need to add the routing label everywhere.
 * LOG:
 * LOG: Revision 1.35  1998/09/29 17:32:46  mmiers
 * LOG: Tweaking MTP3.
 * LOG:
 * LOG: Revision 1.34  1998/09/29 01:34:35  mmiers
 * LOG: Add point code to allowed detection.
 * LOG:
 * LOG: Revision 1.33  1998/09/28 17:36:38  mmiers
 * LOG: Add signatures for SSN handling.
 * LOG:
 * LOG: Revision 1.32  1998/09/26 22:36:57  mmiers
 * LOG: Convert to using message format descriptors.  ISUP needs something like
 * LOG: this as well, for many of the same reasons.
 * LOG:
 * LOG: Revision 1.31  1998/09/25 19:40:33  mmiers
 * LOG: Include MTP3 definitions.
 * LOG:
 * LOG: Revision 1.30  1998/09/15 19:09:15  whu
 * LOG: Limit address encode/decode to one location for simplification.
 * LOG:
 * LOG: Revision 1.29  1998/09/15 00:05:39  whu
 * LOG: Change for proper ANSI formatting.
 * LOG:
 * LOG: Revision 1.28  1998/09/01 00:36:35  whu
 * LOG: IS634.c: Fix dereference/postfix operator precedence bug.
 * LOG:
 * LOG: *.java: decoding of MIN bugfixes, native method decls.
 * LOG:
 * LOG: jits*.cpp: Various fixes relating to connectionless and connection
 * LOG: oriented messaging.
 * LOG:
 * LOG: Revision 1.27  1998/07/21 21:29:09  mmiers
 * LOG: Update tests.
 * LOG:
 * LOG: Revision 1.26  1998/07/03 19:41:39  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.25  1998/07/03 16:09:30  mmiers
 * LOG: SCCP as a thread.
 * LOG:
 * LOG: Revision 1.24  1998/06/25 20:10:21  mmiers
 * LOG: Update for IS634.
 * LOG:
 * LOG: Revision 1.23  1998/06/19 22:24:59  mmiers
 * LOG: Reaching the end of TCAP.  Initial SCCP implementation.
 * LOG:
 * LOG: Revision 1.22  1998/06/17 19:57:02  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.21  1998/06/15 16:29:05  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.20  1998/06/01 23:18:14  mmiers
 * LOG: More documentation.  Custom build steps for TCAP, SCCP.
 * LOG:
 * LOG: Revision 1.19  1998/06/01 22:31:58  mmiers
 * LOG: Raw documentation for SCCP.
 * LOG:
 * LOG: Revision 1.18  1998/05/14 20:41:42  mmiers
 * LOG: Update SCCP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.17  1998/05/14 02:45:26  mmiers
 * LOG: More work on SCCP.  I think I have the encode done OK, still have to
 * LOG: write the decode.  The PTR table in SCCP messages is a bit of a bitch.
 * LOG: If we ever do the same for ISUP, the IEToEvent code could be reused.
 * LOG: That would give us (minus the ever important *PROCEDURES*) the requirement
 * LOG: of MTP3 and below ONLY.  However, ther are a *LOT* of procedures we
 * LOG: don't do (e.g., SST).
 * LOG:
 * LOG: Revision 1.16  1998/05/06 01:19:11  mmiers
 * LOG: Start writing encode for SCCP.
 * LOG:
 * LOG: Revision 1.15  1998/05/04 22:57:36  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.14  1998/04/07 15:51:54  mmiers
 * LOG: Update library to reflect vendor changes.
 * LOG:
 * LOG: Revision 1.13  1998/04/07 15:42:20  mmiers
 * LOG: Update function signatures in sccp.h.
 * LOG:
 * LOG: Revision 1.12  1998/03/20 02:46:18  mmiers
 * LOG: Change the SCCP_IE param_length from USHORT to OCTET.  No parameter can
 * LOG: have a length greater than 255, anyway.
 * LOG:
 * LOG: Revision 1.11  1998/02/26 22:26:16  mmiers
 * LOG: Make sure ISUP stays up to date.  Add project and workspace for VC++.
 * LOG:
 * LOG: Revision 1.10  1998/02/26 18:48:07  mmiers
 * LOG: sccp.h: A few changes to param ids.
 * LOG:
 * LOG: its_types.h: #define the max length of an event.
 * LOG:
 * LOG: Revision 1.9  1998/02/26 16:28:34  rsonak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.8  1998/02/26 15:52:52  rsonak
 * LOG: ITU and ANSI have different Addrss Indicator masks. Taken care of that!
 * LOG:
 * LOG: Revision 1.7  1998/02/26 02:14:11  rsonak
 * LOG: Interchanged the values of SCCP_CPA_HAS_PC and SCCP_CPA_HAS_SSN
 * LOG:
 * LOG: Revision 1.6  1998/02/25 22:12:22  mmiers
 * LOG: sccp.h: Some corrections, a plan for moving the address structure from
 * LOG: tcap.h to sccp.h.  Add SCCP as a possible event source to its.h.  Add
 * LOG: a type for point codes to its_types.h.
 * LOG:
 * LOG: Revision 1.5  1998/02/25 21:42:27  mmiers
 * LOG: Add in initial implementation of SCCP interface.
 * LOG:
 * LOG: Revision 1.4  1998/02/11 15:21:45  mmiers
 * LOG: Fix a few bugs in these files.
 * LOG:
 * LOG: Revision 1.3  1998/02/06 15:29:55  ite
 * LOG: update for changes to nms header location.
 * LOG:
 * LOG: Revision 1.2  1998/02/06 14:44:07  mmiers
 * LOG: Add ANSI header, update ITU header to compensate.
 * LOG:
 * LOG: Revision 1.1  1998/02/06 14:39:47  mmiers
 * LOG: Move from common tree to here.
 * LOG:
 * LOG: Revision 1.4  1998/02/04 23:28:31  rsonak
 * LOG: formatting.
 * LOG:
 * LOG: Revision 1.3  1998/02/04 18:52:56  ite
 * LOG: sccp.h: Modify macros for correct behavior.
 * LOG: tcap.h: Correct usages, add some definitions for ANSI.
 * LOG:
 * LOG: Revision 1.2  1998/01/28 02:00:59  rsonak
 * LOG: Update from NMS integration.
 * LOG:
 * LOG: Revision 1.1  1998/01/27 15:42:49  mmiers
 * LOG: New files for NMS and ANSI
 * LOG:
 * LOG: Revision 1.2  1997/12/08 22:05:04  jpakrasi
 * LOG: Update copyright information for 1998 year.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_SCCP_CCITT_H_
#define _ITS_SCCP_CCITT_H_

#ident "$Id: sccp.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>
#include <its_route.h>

#include <itu/mtp3.h>

/*
 * get the common data
 */
#include <sccp_cmn.h>

/*
 * use of the short names is deprecated and may be removed in a future
 * release
 */
#include <sccp_sn.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * CCITT message descriptors
 */
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CR_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CC_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CREF_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLSD_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLC_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT1_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT2_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_AK_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDT_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDT_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDTS_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDTS_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ED_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_EA_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSR_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSC_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ERR_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_IT_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDT_Desc_CCITT;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDTS_Desc_CCITT;

/*
 * Management callbacks
 * GTT callbacks and routing callbacks are only available
 * with our stack.
 */
SS7DLLAPI extern CALLBACK_Manager*    SCCP_CCITT_ManagementCallbacks;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_CCITT_GlobalTitleTranslator;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_CCITT_SSNRoutingCallbacks;

/*
 * function interface
 */
SS7DLLAPI int  SCCP_GetNextLocalRef_CCITT(ITS_HANDLE handle,
                                          ITS_CTXT* cref);

SS7DLLAPI int  SCCP_GetSharedLocalRef_CCITT(void *ctxtData,
                                            int len);
/*
 * address helpers
 */
SS7DLLAPI int SCCP_EncodeAddr_CCITT(SCCP_ADDR *addr, ITS_OCTET addrInd,
                                    ITS_UINT pc, ITS_OCTET ssn,
                                    const ITS_OCTET* gttInfo, ITS_USHORT gttLen);
SS7DLLAPI int SCCP_DecodeAddr_CCITT(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                                    ITS_UINT* pc, ITS_OCTET *ssn,
                                    ITS_OCTET* gttInfo, ITS_USHORT* gttLen);

SS7DLLAPI int SCCP_ComputeMSize_CCITT(ITS_OCTET which);

SS7DLLAPI int SCCP_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                ITS_OCTET mType,
                                ITS_SCCP_IE *ies, ITS_UINT ieCount,
                                ITS_BOOLEAN printUserData);

/*
 * Application status requests.
 */
SS7DLLAPI int SCCP_SendUserInService_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                           ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendUserOutOfService_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                              ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendSetCongestion_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                           ITS_UINT pc, ITS_OCTET ssn,
                                           ITS_OCTET cong);

/*.interface:SCCP
 *****************************************************************************
 *  Interface:
 *      SCCP_*
 *
 *  Purpose:
 *      This interface defines the user's C programming model for SCCP.
 *
 *  Usage:
 *
 *****************************************************************************/
/*
 * primitives
 */
/*** CR ***/
SS7DLLAPI int SCCP_SendConnectionRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRequest_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                  ITS_HDR *hdr,
                                                  ITS_SCCP_IE *ies, int *ieCount);

/*** CC ***/
SS7DLLAPI int SCCP_SendConnectionConfirm_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionConfirm_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                  ITS_HDR *hdr,
                                                  ITS_SCCP_IE *ies, int *ieCount);

/*** CREF ***/
SS7DLLAPI int SCCP_SendConnectionRefused_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRefused_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                  ITS_HDR *hdr,
                                                  ITS_SCCP_IE *ies, int *ieCount);

/*** RLSD ***/
SS7DLLAPI int SCCP_SendReleased_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                      ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleased_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                         ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int *ieCount);

/*** RLC ***/
SS7DLLAPI int SCCP_SendReleaseComplete_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleaseComplete_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm1_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm1_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                          ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm2_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm2_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                          ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int *ieCount);

/*** AK ***/
SS7DLLAPI int SCCP_SendAcknowledgement_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveAcknowledgement_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** UDT ***/
SS7DLLAPI int SCCP_SendUnitData_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                      ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitData_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                         ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int *ieCount);

/*** XUDT ***/
SS7DLLAPI int SCCP_SendExtendedUnitData_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitData_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                 ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int *ieCount);

/*** LUDT ***/
SS7DLLAPI int SCCP_SendLongUnitData_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitData_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int *ieCount);

/*** UDTS ***/
SS7DLLAPI int SCCP_SendUnitDataService_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitDataService_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** XUDTS ***/
SS7DLLAPI int SCCP_SendExtendedUnitDataService_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                                     ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitDataService_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                        ITS_HDR *hdr,
                                                        ITS_SCCP_IE *ies, int *ieCount);

/*** LUDTS ***/
SS7DLLAPI int SCCP_SendLongUnitDataService_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitDataService_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                    ITS_HDR *hdr,
                                                    ITS_SCCP_IE *ies, int *ieCount);

/*** ED ***/
SS7DLLAPI int SCCP_SendExpeditedData_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedData_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** EA ***/
SS7DLLAPI int SCCP_SendExpeditedDataAck_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedDataAck_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                 ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int *ieCount);

/*** RSR ***/
SS7DLLAPI int SCCP_SendResetRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetRequest_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int *ieCount);

/*** RSC ***/
SS7DLLAPI int SCCP_SendResetConfirmation_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetConfirmation_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                                  ITS_HDR *hdr,
                                                  ITS_SCCP_IE *ies, int *ieCount);

/*** ERR ***/
SS7DLLAPI int SCCP_SendError_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                   ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveError_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                      ITS_HDR *hdr,
                                      ITS_SCCP_IE *ies, int *ieCount);

/*** IT ***/
SS7DLLAPI int SCCP_SendInactivityTest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveInactivityTest_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/******************************** SCCP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

/*
 * implementation functions.  Users should not invoke these.
 */
SS7DLLAPI int SCCP_Encode_CCITT(ITS_SCCP_IE *ies, int ieCount,
                                ITS_OCTET msgType, ITS_EVENT *event,
                                ITS_HDR *hdr, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_Decode_CCITT(ITS_SCCP_IE *ies, int *ieCount,
                                ITS_EVENT *ev, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_EncodeMTP3_CCITT(ITS_OCTET* data, ITS_USHORT* len,
                                    ITS_OCTET mType, ITS_SCCP_IE *ies,
                                    int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_DecodeMTP3_CCITT(ITS_OCTET *data, ITS_USHORT len,
                                    ITS_OCTET* mType, ITS_SCCP_IE *ies,
                                    int *ieCount, SCCP_MSG_DESC* desc);

SS7DLLAPI int SCCP_SendEvent_CCITT(ITS_HANDLE handle, ITS_OCTET type,
                                   ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                   int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                      ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                      int *ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI SCCP_MSG_DESC *SCCP_GetDescriptor_CCITT(ITS_OCTET which);

ITS_BOOLEAN SCCP_IsSSNEquipped_CCITT(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_BOOLEAN SCCP_IsSSNAllowed_CCITT(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_OCTET   SCCP_IsSSNCongested_CCITT(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);

/*
 * management interface
 */
ITSSS7DLLAPI int SCCP_AddConcernedSubSystem_CCITT(ROUTE_Info *linfo,
                                                  ROUTE_Info *cinfo);
ITSSS7DLLAPI int SCCP_RemConcernedSubSystem_CCITT(ROUTE_Info *linfo,
                                                  ROUTE_Info *cinfo);
ITSSS7DLLAPI int SCCP_AddDuplicatedSubSystem_CCITT(ROUTE_Info *rinfo);
ITSSS7DLLAPI int SCCP_RemDuplicatedSubSystem_CCITT(ROUTE_Info *rinfo);
ITSSS7DLLAPI ITS_INT SCCP_EnableUserPart(ITS_OCTET up, ITS_USHORT id);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SCCP_CCITT_H_ */
