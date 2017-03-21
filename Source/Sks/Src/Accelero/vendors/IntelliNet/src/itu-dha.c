/*********************************-*-C-*-************************************
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
 * CONTRACT: INTNERNAL                                                      *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: itu-dha.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:32  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.6  2005/05/25 06:27:32  adutta
 * LOG: XUDT/LUDT implementation
 * LOG:
 * LOG: Revision 9.5  2005/05/11 13:47:02  yranade
 * LOG: Indeterminate Length Fixes. Help Desk ID 742.
 * LOG:
 * LOG: Revision 9.4  2005/05/05 06:46:53  adutta
 * LOG: Fix for #1566
 * LOG:
 * LOG: Revision 9.3  2005/04/08 09:05:28  snagesh
 * LOG: Fix for compilation issue
 * LOG:
 * LOG: Revision 9.2  2005/04/08 07:36:35  adutta
 * LOG: Fix for WSC Bug#1170
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.21  2005/03/21 13:53:42  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.12.2.13.2.1.12.5  2005/02/21 14:46:07  sbabu
 * LOG: TCAP OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.12.2.13.2.1.12.4  2005/02/03 10:14:45  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.12.2.13.2.1.12.3  2005/01/04 13:43:56  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.12.2.13.2.1.12.2  2004/12/31 10:44:29  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.12.2.13.2.1.12.1  2004/12/17 03:57:43  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.12.2.13.2.1.6.1  2004/10/25 20:34:11  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.12.2.13.2.1  2004/02/16 09:16:57  mmanikandan
 * LOG: Performance Improvement.
 * LOG:
 * LOG: Revision 7.12.2.13  2003/11/19 05:41:14  ssingh
 * LOG: TCAP_ERROR display is been removed from FindPTypeAndTID_CCITT
 * LOG: in case of Bad Tids or Unknown pType as calling function itself
 * LOG: is giving ERROR print. BUG# 588/589
 * LOG:
 * LOG: Revision 7.12.2.12  2003/07/25 09:49:37  yranade
 * LOG: Send correct reject causes in Reject when DataToCPT fails rather
 * LOG: than just BADLY_STRUCT_COMP.
 * LOG:
 * LOG: Revision 7.12.2.11  2003/06/10 10:38:55  yranade
 * LOG: Updates to send Abort with ABRT pdu in specific failure cases.
 * LOG:
 * LOG: Revision 7.12.2.10  2003/05/29 14:26:32  yranade
 * LOG: Oops undo last change, it was not needed.
 * LOG:
 * LOG: Revision 7.12.2.9  2003/05/29 14:12:12  yranade
 * LOG: Discard Begin received with an invalid OTID.
 * LOG:
 * LOG: Revision 7.12.2.8  2003/05/29 05:20:42  yranade
 * LOG: Detect error if DP present in Continue, when dstate is not AARQ_SENT.
 * LOG: Tweak SendPAbort.(fixes: 295, 335 (case 6).
 * LOG:
 * LOG: Revision 7.12.2.7  2003/05/16 13:41:06  yranade
 * LOG: Fix typo.
 * LOG:
 * LOG: Revision 7.12.2.6  2003/05/14 08:47:09  yranade
 * LOG: Update SendTransPAbort to use TCAP Codec.
 * LOG:
 * LOG: Revision 7.12.2.5  2003/05/13 03:01:51  vjatti
 * LOG: Bug 298:Added code for setting correct cause on failure of Unknown Msg.
 * LOG: Bug 293:Handling of incorrect Msg.
 * LOG: Bug 327:Handling of incorrect Component portion.
 * LOG:
 * LOG: Revision 7.12.2.4  2003/04/23 06:33:18  vjatti
 * LOG: Code clean up.
 * LOG:
 * LOG: Revision 7.12.2.3  2003/03/15 12:05:11  vjatti
 * LOG: Fix for LOCAL CANCEL for Pre Arranged End.
 * LOG: Don't Build the PDU/message if it has to be frred for Pre arranged end.
 * LOG:
 * LOG: Revision 7.12.2.2  2003/03/04 12:44:37  yranade
 * LOG: Get the missing reorder/list traversal bug fix right.
 * LOG:
 * LOG: Revision 7.12.2.1  2003/03/03 22:22:13  mmiers
 * LOG: Missing reorder/list traversal bug fix.
 * LOG:
 * LOG: Revision 7.12  2003/02/13 13:04:28  yranade
 * LOG: Cleanup.
 * LOG:
 * LOG: Revision 7.11  2003/02/07 15:18:53  yranade
 * LOG: Removed warnings shown by gcc -Wall.
 * LOG:
 * LOG: Revision 7.10  2003/02/07 13:57:46  tsanthosh
 * LOG: Changes for Pegs & Alarms
 * LOG:
 * LOG: Revision 7.9  2003/02/05 14:22:09  yranade
 * LOG: Renamed FindParts to TCAP_FindParts, since it's in Global Scope.
 * LOG: Removed warnings seen on windows.
 * LOG:
 * LOG: Revision 7.8  2003/02/04 16:37:45  mmiers
 * LOG: Error if codec not defined.
 * LOG:
 * LOG: Revision 7.7  2003/02/04 07:25:40  yranade
 * LOG: TCAP Manual Codec Integration.
 * LOG:
 * LOG: Revision 7.6  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.5  2002/12/04 17:35:00  ngoel
 * LOG: merge prc changes from PR6.1
 * LOG:
 * LOG: Revision 7.4  2002/11/14 22:27:20  omayor
 * LOG: Removed compilation warnings shown by gcc3.2
 * LOG:
 * LOG: Revision 7.3  2002/10/15 19:41:28  omayor
 * LOG: Use correct includes
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:10:13  omayor
 * LOG: Mnimization of DSM calls
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.16  2002/08/26 21:32:48  mmiers
 * LOG: Bad return value
 * LOG:
 * LOG: Revision 6.15  2002/08/26 18:18:48  mmiers
 * LOG: Add dest
 * LOG:
 * LOG: Revision 6.14  2002/08/26 16:54:13  mmiers
 * LOG: Add deselector hook.
 * LOG:
 * LOG: Revision 6.13  2002/08/19 18:05:28  mmiers
 * LOG: China build debug
 * LOG:
 * LOG: Revision 6.12  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.11  2002/08/15 20:26:11  mmiers
 * LOG: Warning/error removal
 * LOG:
 * LOG: Revision 6.10  2002/07/29 17:55:18  ngoel
 * LOG: increment totl message peg
 * LOG:
 * LOG: Revision 6.9  2002/07/03 21:19:48  mmiers
 * LOG: Fixes for DSM, VFrame
 * LOG:
 * LOG: Revision 6.8  2002/07/03 18:04:03  mmiers
 * LOG: changes for China
 * LOG:
 * LOG: Revision 6.7  2002/05/08 15:49:18  mmiers
 * LOG: Add user setting of NI
 * LOG:
 * LOG: Revision 6.6  2002/05/03 22:35:29  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 6.5  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/03/27 17:48:12  mmiers
 * LOG: Convert to using shared timers.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 23:08:26  mmiers
 * LOG: TCAP behaviors.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:31  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.14  2002/02/13 00:00:00  mmiers
 * LOG: Walk prim list in tail to head order to fix reordering bug.
 * LOG:
 * LOG: Revision 5.13  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.12  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.11  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.10  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 5.9  2001/11/08 16:38:35  mmiers
 * LOG: When the user specifies a different address in the first
 * LOG: continue, store it in the context.
 * LOG:
 * LOG: Revision 5.8  2001/09/26 21:28:44  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.7  2001/09/26 00:36:41  mmiers
 * LOG: Get the fixmes under 100.
 * LOG:
 * LOG: Revision 5.6  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.5  2001/09/07 17:04:11  mmiers
 * LOG: Fixes.
 * LOG:
 * LOG: Revision 5.4  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
 * LOG:
 * LOG: Revision 5.3  2001/09/06 15:33:32  mmiers
 * LOG: Cleanup.  Add reserved NI use to TCAP.
 * LOG:
 * LOG: Revision 5.2  2001/08/21 20:21:31  mmiers
 * LOG: Start adding in the missing code.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.12  2001/02/06 17:58:42  mmiers
 * LOG: About 90% thread safe.  SCCP connection oriented isn't, neither
 * LOG: are simultaneous messages within a TCAP transaction.
 * LOG:
 * LOG: Revision 3.11  2001/02/06 16:07:34  mmiers
 * LOG: Tweaks.
 * LOG:
 * LOG: Revision 3.10  2001/01/18 23:51:50  mmiers
 * LOG: Replace list allocator
 * LOG:
 * LOG: Revision 3.9  2001/01/03 17:30:34  mmiers
 * LOG: Don't check tr (pointer may be uninitialized).
 * LOG:
 * LOG: Revision 3.8  2000/12/19 20:07:05  mmiers
 * LOG: GCC warnings
 * LOG:
 * LOG: Revision 3.7  2000/11/29 17:50:59  mmiers
 * LOG: Weird Cisco len fix.
 * LOG:
 * LOG: Revision 3.6  2000/09/06 22:49:00  mmiers
 * LOG: Actually free the entries, ok?
 * LOG:
 * LOG: Revision 3.5  2000/09/06 16:11:41  mmiers
 * LOG: Suspenders and belts work with prim queue.
 * LOG:
 * LOG: Revision 3.4  2000/09/01 20:56:49  mmiers
 * LOG:
 * LOG:
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:07:24  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 17:28:17  mmiers
 * LOG: Ancient memory leak plugged.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:33  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.7  2000/07/14 17:23:20  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.6  2000/06/28 23:32:46  mmiers
 * LOG:
 * LOG:
 * LOG: Add some traces.
 * LOG:
 * LOG: Revision 2.5  2000/06/09 20:48:43  rsonak
 * LOG:
 * LOG: Commiting change done in revision 1.45.2.1 in PR2 to current. CCITT_TCAPDecodeData
 * LOG: is made non-static.
 * LOG:
 * LOG: Revision 2.4  2000/04/20 13:26:08  npopov
 * LOG: Fixed a memory leak in case of returning error in DisassemblePDU().
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:04:59  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  2000/02/24 23:59:02  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 18:23:34  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.45  1999/10/06 17:12:16  mmiers
 * LOG:
 * LOG:
 * LOG: Commit minor type fix to dha, Makefile for split stack
 * LOG:
 * LOG: Revision 1.44  1999/10/05 23:59:28  mmiers
 * LOG:
 * LOG:
 * LOG: Fix point code flipping issue.
 * LOG:
 * LOG: Revision 1.43  1999/10/05 21:13:12  mmiers
 * LOG:
 * LOG:
 * LOG: Don't let the user send user_info or ac_name at invalid times.
 * LOG:
 * LOG: Revision 1.42  1999/10/05 19:41:59  ite
 * LOG:
 * LOG:  fix to update Cgpa in case of firt Continue (incoming or outgoing).
 * LOG:  Update routing label of Transaction context when sending Begin.
 * LOG:
 * LOG: Revision 1.41  1999/10/05 19:01:04  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.40  1999/10/04 16:46:05  mmiers
 * LOG:
 * LOG:
 * LOG: Some sanity fixes.
 * LOG:
 * LOG: Revision 1.39  1999/09/30 14:51:36  mmiers
 * LOG:
 * LOG:
 * LOG: Hack to get L_REJECT working.
 * LOG:
 * LOG: Revision 1.38  1999/09/29 22:57:05  mmiers
 * LOG:
 * LOG:
 * LOG: Forgot to give the components to the PDU.
 * LOG:
 * LOG: Revision 1.37  1999/09/29 21:45:28  mmiers
 * LOG:
 * LOG:
 * LOG: More bug fixes for Fred.
 * LOG:
 * LOG: Revision 1.36  1999/09/29 21:36:34  mmiers
 * LOG:
 * LOG:
 * LOG: Fred picked up more bugs.
 * LOG:
 * LOG: Revision 1.35  1999/09/29 21:20:50  ite
 * LOG:
 * LOG: fhasle: fixed bug in ParseCMG. The Switch statment based on tag, was done on
 * LOG:         the offsets of the type_ITU__TCAP_ComponentPortion struct, instead of
 * LOG:         component type tags.
 * LOG:
 * LOG: Revision 1.34  1999/09/29 20:16:43  mmiers
 * LOG:
 * LOG:
 * LOG: Commit fixes for the bugs Fred found.
 * LOG:
 * LOG: Revision 1.33  1999/09/29 17:20:28  mmiers
 * LOG:
 * LOG:
 * LOG: Adjust for the while loop.
 * LOG:
 * LOG: Revision 1.32  1999/09/24 23:45:59  mmiers
 * LOG:
 * LOG:
 * LOG: Enable L-REJECT for parse errors.
 * LOG:
 * LOG: Revision 1.31  1999/09/24 22:21:27  mmiers
 * LOG:
 * LOG:
 * LOG: Almost finished with backup parser.
 * LOG:
 * LOG: Revision 1.30  1999/09/24 14:12:51  mmiers
 * LOG:
 * LOG:
 * LOG: More work on DHA.
 * LOG:
 * LOG: Revision 1.29  1999/09/23 22:28:40  mmiers
 * LOG:
 * LOG:
 * LOG: Almost there.  Just need the error case parser.
 * LOG:
 * LOG: Revision 1.28  1999/09/23 22:00:58  mmiers
 * LOG:
 * LOG:
 * LOG: More work on tags and parsing.
 * LOG:
 * LOG: Revision 1.27  1999/09/23 18:25:09  mmiers
 * LOG:
 * LOG:
 * LOG: Fix routine I added yesterday.
 * LOG:
 * LOG: Revision 1.26  1999/09/22 19:49:15  mmiers
 * LOG:
 * LOG:
 * LOG: Play around a bit with P-ABORT.
 * LOG:
 * LOG: Revision 1.25  1999/09/17 23:04:00  mmiers
 * LOG:
 * LOG:
 * LOG: Change return values for PAbort
 * LOG:
 * LOG: Revision 1.24  1999/09/10 23:10:23  mmiers
 * LOG:
 * LOG:
 * LOG: Split out white book and blue book variant behavior.
 * LOG:
 * LOG: Revision 1.23  1999/09/09 22:10:02  mmiers
 * LOG:
 * LOG:
 * LOG: Reverse the tids for a continue.
 * LOG:
 * LOG: Revision 1.22  1999/09/07 21:02:32  ite
 * LOG:
 * LOG:
 * LOG: Change interface for TCAP such that the dialogue id is not memcpy'd.
 * LOG: This fixes a reject bug.
 * LOG:
 * LOG: Revision 1.21  1999/09/01 15:34:09  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Fred's testing.
 * LOG:
 * LOG: Revision 1.20  1999/08/30 21:30:31  mmiers
 * LOG:
 * LOG:
 * LOG: Take care of prearranged end.
 * LOG:
 * LOG: Revision 1.19  1999/08/27 18:50:07  mmiers
 * LOG:
 * LOG:
 * LOG: Bug fix, save the DSP file.
 * LOG:
 * LOG: Revision 1.18  1999/08/27 16:50:12  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.17  1999/08/26 23:44:58  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.16  1999/08/26 15:24:13  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.15  1999/08/26 02:21:57  mmiers
 * LOG:
 * LOG:
 * LOG: Automate QOS reflection.  Fix UNI handling (newly added code would have
 * LOG: rejected UNIs).  Try to be clearer about the position of the routing
 * LOG: label.  There is still most likely a hole (or more specifically, to
 * LOG: much override) when building a routing label after the user has
 * LOG: overriden certain fields.
 * LOG:
 * LOG: Revision 1.14  1999/08/25 22:40:53  mmiers
 * LOG:
 * LOG:
 * LOG: Sanity checks.
 * LOG:
 * LOG: Revision 1.13  1999/08/25 17:41:57  ite
 * LOG:
 * LOG:
 * LOG: Fix the sign extend.
 * LOG:
 * LOG: Revision 1.12  1999/08/20 17:10:14  ite
 * LOG:
 * LOG:
 * LOG: Dialogue encoding bugs (RETOPT, SLS, etc.)
 * LOG:
 * LOG: Revision 1.11  1999/08/19 22:44:06  mmiers
 * LOG:
 * LOG:
 * LOG: Fix PAbort generation problem.
 * LOG:
 * LOG: Revision 1.10  1999/08/05 17:04:51  mmiers
 * LOG:
 * LOG:
 * LOG: Provision for dumping PDUs.
 * LOG:
 * LOG: Revision 1.9  1999/06/21 18:53:57  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up ITU TCAP.  Needs extensive testing.
 * LOG:
 * LOG: Revision 1.8  1999/06/18 23:13:45  mmiers
 * LOG:
 * LOG:
 * LOG: Parse ITU TIDs as variable sized.
 * LOG:
 * LOG: Revision 1.7  1999/06/18 22:15:41  mmiers
 * LOG:
 * LOG:
 * LOG: Remove extraneous deletes
 * LOG:
 * LOG: Revision 1.6  1999/06/15 22:41:18  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for codec function signatures.
 * LOG:
 * LOG: Revision 1.5  1999/06/15 22:32:06  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.4  1999/05/27 15:52:46  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.3  1999/05/24 20:31:20  mmiers
 * LOG:
 * LOG:
 * LOG: Codecs have moved into shared library.
 * LOG:
 * LOG: Revision 1.2  1999/05/18 17:00:17  mmiers
 * LOG:
 * LOG:
 * LOG: Initial coding of ITU TCAP complete.  Much testing and fixme
 * LOG: removal to do.
 * LOG:
 * LOG: Revision 1.1  1999/05/17 23:05:37  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_assertion.h>
#include <its_dsm.h>
#include <its_ss7_trans.h>
#include <its_ctf.h>

#ident "$Id: itu-dha.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#if defined(PRC)
#include <china/tcap.h>
#elif defined(TTC)
#include <japan/tcap.h>
#else
#include <itu/tcap.h>
#endif

#include "tcap_intern.h"

MLIST_Manager *__TCAP_CCITT_primQueue;

#if defined(SPLIT_STACK)
#define WHICH_STACK     (ITS_HANDLE)ISS7_ANSI_Stack
#elif defined(PRC)
#define WHICH_STACK     (ITS_HANDLE)ISS7_PRC_Stack
#elif defined(TTC)
#define WHICH_STACK     (ITS_HANDLE)ISS7_TTC_Stack
#else
#define WHICH_STACK     (ITS_HANDLE)ISS7_CCITT_Stack
#endif

/* TCAP-Codec Optimisation */
#if defined (PEPSY_CODEC)
#define AssemblePDU                 PEPSY_AssemblePDU
#define DisassemblePDU              PEPSY_DisassemblePDU
#elif defined (TCAP_CODEC)
#define AssemblePDU                 TCAP_AssemblePDU
#define DisassemblePDU              TCAP_DisassemblePDU
#else
#error "You must define a codec to use."
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
__TCAP_SendAppPAbort_CCITT(ITS_CTXT did, ITS_EVENT *event,
                           ITS_OCTET reason)
{
    ITS_EVENT ev;
    TCAP_DLG dlg;
    ITS_HDR hdr;

    TCAP_DEBUG(("__TCAP_SendAppPAbort.\n"));

    if (did == 0)
    {
        return;
    }

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;

    /* build end */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    dlg.ptype = TCPPT_TC_P_ABORT;
    dlg.u.abort.abort_reason = reason;

    if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
    {
        TCAP_ERROR(("__TCAP_SendAppPAbort_CCITT: Sanity check failed.\n"));
        
        /* Incoming as in toward application */
        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */

        return;
    }

    /* send to APP */
    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
    ev.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&ev.data[1], did);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

    if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
    {
        TCAP_WARNING(("__TCAP_SendAppPAbort_CCITT: unable to send PAbort response.\n"));

        /* Incoming as in toward application */
        /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */

         PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL); 
    }
    else
    {
        /* Add to Count "Received" ==> toward Application */
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);
    }

    ITS_EVENT_TERM(&ev);
}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

void
__TCAP_SendTransPAbort_CCITT(ITS_SCCP_IE *ies, int ieCount,
                             ITS_OCTET reason)
{
    TCAP_DLG dlg;
    ITS_OCTET pType = 0;
    ITS_UINT ltid = 0, rtid = 0, ltidLen, rtidLen, tmp;
    SCCP_ADDR cdp, clp;
    ITS_BOOLEAN knownPType = ITS_TRUE;
    int i;
    ITS_HDR hdr;
    ITS_OCTET ssn;
    TCAP_TRANS_ENTRY *sharedTx = NULL;
#if defined (PEPSY_CODEC)
    int len = 0;
    struct type_ITU__TCAP_MessageType *pdu;
    char *enc = NULL;
    PE pe;
#elif defined (TCAP_CODEC)
    ITS_OCTET tp[MAX_TCAP_TRANS_SIZE];
    ITS_UINT tpLen = 0;
#endif

    /* - DSM Stuff - */
    ITS_OCTET tidKey[4];
    int keyLen = 0;


    /*
     * NOTE: This can only be sent as a reaction to an incoming
     * event.
     */
    if (FindPTypeAndTID_CCITT(ies, ieCount, &pType,
                              &ltid, &ltidLen, &rtid, &rtidLen,
                              &cdp, &clp) == ITS_NO)
    {
        knownPType = ITS_FALSE;
    }

    if (knownPType && pType == TCPPT_TC_BEGIN)
    {
        tmp = rtid;
        rtid = ltid;
        ltid = tmp;

        tmp = rtidLen;
        rtidLen = ltidLen;
        ltidLen = tmp;
    }
    else if (!knownPType)
    {
        if (!ltid && !rtid)
        {
            /* discard, we give up */

            TCAP_ERROR(("TCAP_SendPAbort: Discarding Message.\n"));

            return;
        }

        /* must be begin */
        if (ltid && !rtid)
        {
            tmp = rtid;
            rtid = ltid;
            ltid = tmp;

            tmp = rtidLen;
            rtidLen = ltidLen;
            ltidLen = tmp;
        }
    }

    TCAP_DEBUG(("__TCAP_SendPAbort.\n"));

    if (rtid && ((sharedTx = TCAP_FindTransactionContext_CCITT(rtid, tidKey,
                                                            &keyLen)) != NULL))
    {
        TCAP_DEBUG(("TCAP_SendTransPAbort: Freeing DSM Tx for tid"
                    "%u.\n", rtid));

        TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
     
        TCAP_FreeLocalTx_CCITT(sharedTx->did);
    }

    /* build abort */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    dlg.ptype = TCPPT_TC_P_ABORT;
    dlg.u.abort.abort_reason = reason;

#if defined (PEPSY_CODEC)
    pdu = TCAP_CvtDLGToMessage_CCITT(&dlg, ltid, rtid, rtidLen, TCAP_Variant);
    if (!pdu)
    {
        TCAP_ERROR(("SendPAbort: Could not convert dialog to package.\n"));

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted. */

        return;
    }

    /* perform the encode */
    if (encode_ITU__TCAP_MessageType(&pe, 1, 0, NULL, (void *)pdu)
        == NOTOK)
    {
        TCAP_ERROR(("SendPAbort: Could not encode package.\n"));

        free_ITU__TCAP_MessageType(pdu);
        
        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted. */

        return;
    }
   
#if defined(LOCAL_DEBUG)
    print_ITU__TCAP_MessageType(pe, 1, 0, NULL, pdu);
#endif

    free_ITU__TCAP_MessageType(pdu);

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        TCAP_ERROR(("SendPAbort: Could not encode package.\n"));

        pe_free(pe);

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted. */

        return;
    }

    if (pe)
    {
        pe_free(pe);
    }

    if (enc == NULL && len == 0)
    {
        TCAP_ERROR(("SendPAbort: Encode left no data.\n"));
        

        return;
    }
#elif defined (TCAP_CODEC)

    if (TCAP_CvtDLGToData_CCITT(&dlg, tp, &tpLen, 
                                NULL, 0, ltid, 
                                rtid, rtidLen, 
                                TCAP_Variant) != ITS_SUCCESS)
    {
        TCAP_ERROR(("__TCAP_SendDecodeAbort: Could not convert dialog to data.\n"));

        return;
    }
#endif

    hdr.context.ssn = 0;
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            ies[i].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            ies[i].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            SCCP_DecodeAddr(&ies[i].param_data.callingPartyAddr,
                            NULL, NULL, &ssn, NULL, NULL);
            hdr.context.ssn = ssn;
        }
        else if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
        {
            ITS_UINT opc, dpc;

            opc = MTP3_RL_GET_OPC_VALUE(ies[i].param_data.routingLabel.label);
            dpc = MTP3_RL_GET_DPC_VALUE(ies[i].param_data.routingLabel.label);

            MTP3_RL_SET_OPC_VALUE(ies[i].param_data.routingLabel.label, dpc);
            MTP3_RL_SET_DPC_VALUE(ies[i].param_data.routingLabel.label, opc);
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
#if defined (PEPSY_CODEC)
            ies[i].param_length = len;
            memcpy(ies[i].param_data.userData.data, enc, len);
            free(enc);
#elif defined (TCAP_CODEC)
            ies[i].param_length = tpLen;
            memcpy(ies[i].param_data.userData.data, tp, tpLen);
#endif
        }
    }

    hdr.type = ITS_TCAP;

    SCCP_SendUnitData(WHICH_STACK, &hdr, ies, ieCount);

    /* Add to Msg counter -- sent to remote */
    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

void
__TCAP_SendAppReject_CCITT(ITS_CTXT did, TCAP_CPT *comp,
                           ITS_OCTET family, ITS_OCTET reason,
                           ITS_BOOLEAN isLast)
{
    TCAP_CPT cpt;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_EVENT event;

    if (comp == NULL)
    {
        TCAP_ERROR(("SendAppReject: Can't reject non-component.\n"));
        
        /* Incoming Component - Discarding Component - Invalid or Corrupted. */
        return;
    }

    memset(&cpt, 0, sizeof(TCAP_CPT));

    cpt.ptype = TCPPT_TC_L_REJECT;
    cpt.last_component = isLast;
    cpt.u.reject.invoke_id.len = 3;
    cpt.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    cpt.u.reject.invoke_id.data[1] = 1;
    /* What do I use for invoke_id? Answer: the comp. */
    cpt.u.reject.invoke_id.data[2] = 0;

    /* I can get away with this as invoke_id is at the same offset
     * in all components. */
    if (comp)
    {
        cpt.u.reject.invoke_id.data[2] = comp->u.invoke.invoke_id.data[2];
    }

    cpt.u.reject.problem.len = 3;
    cpt.u.reject.problem.data[0] = family;
    cpt.u.reject.problem.data[1] = 1;
    cpt.u.reject.problem.data[2] = reason;

#if 0
    /* Do a Sanity check of a cpt that we (stack) has formatted??
       Should be used only when debugging.
    */

    if (TCAP_VendorComponentSanityCheck(&cpt) != ITS_SUCCESS)
    {
        TCAP_ERROR(("SendAppReject: Sanity check failed.\n"));
        
        /* Incoming Component - Discarding Component - Invalid or Corrupted. */
        return;
    }
#endif

    ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
    event.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&event.data[1], did);
    memcpy(&event.data[1 + sizeof(ITS_CTXT)], &cpt, sizeof(TCAP_CPT));

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        TCAP_DEBUG(("__TCAP_SendAppReject_CCITT: sending INVOKE to app: %04x\n",dest));

        TRANSPORT_PutEvent(dest, &event);
 
    }
    else
    {
        TCAP_DEBUG(("SendAppReject: failed to send L_REJECT:\n"));
        
        /* Incoming Component - Discarding Component - No Route to Application. */
    }

    ITS_EVENT_TERM(&event);
}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

void
__TCAP_SendRemoteReject_CCITT(ITS_CTXT did, TCAP_CPT *comp,
                              ITS_OCTET family, ITS_OCTET reason)
{
    TCAP_CPT cpt;
    ITS_EVENT event;

    if (comp == NULL)
    {
        TCAP_ERROR(("SendAppReject: Can't reject non-component.\n"));

        /* Incoming Component - Discarding Component - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1437, __FILE__, __LINE__, NULL);
        return;
    }

    memset(&cpt, 0, sizeof(TCAP_CPT));

    cpt.ptype = TCPPT_TC_R_REJECT;
    cpt.last_component = ITS_FALSE;
    cpt.u.reject.invoke_id.len = 3;
    cpt.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    cpt.u.reject.invoke_id.data[1] = 1;
    cpt.u.reject.invoke_id.data[2] = 0;

    /* I can get away with this as invoke_id is at the same offset
     * in all components. */
    if (comp)
    {
        cpt.u.reject.invoke_id.data[2] = comp->u.invoke.invoke_id.data[2];
    }

    cpt.u.reject.problem.len = 3;
    cpt.u.reject.problem.data[0] = family;
    cpt.u.reject.problem.data[1] = 1;
    cpt.u.reject.problem.data[2] = reason;

    ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
    event.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&event.data[1], did);
    memcpy(&event.data[1 + sizeof(ITS_CTXT)], &cpt, sizeof(TCAP_CPT));

    DHAHandleCCOMsg_CCITT(&event);

    /* NO ITS_EVENT_TERM().  The call above just queues the event, not
     * transmit */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0170 to R0210      XUDT/XUDTS Implementation
 *
 ****************************************************************************/
ITS_BOOLEAN
FindPTypeAndTID_CCITT(ITS_SCCP_IE *ies, int ieCount,
                      ITS_OCTET *pType,
                      ITS_UINT *tid1, ITS_UINT *tid1Len,
                      ITS_UINT *tid2, ITS_UINT *tid2Len,
                      SCCP_ADDR *cdp, SCCP_ADDR *clp)
{
    int i;
    ITS_OCTET *data, *stop;
    ITS_UINT dummy, dummyLen;

    *pType = 0;
    *tid1 = *tid2 = 0;

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            memcpy(cdp->data, &ies[i].param_data.calledPartyAddr.data,
                   ies[i].param_length);
            cdp->len = ies[i].param_length;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(clp->data, &ies[i].param_data.callingPartyAddr.data,
                   ies[i].param_length);
            clp->len = ies[i].param_length;
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
            *pType = ies[i].param_data.userData.data[0];

            data = &ies[i].param_data.userData.data[1];
            stop = ies[i].param_data.userData.data + ies[i].param_length;
            break;
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        {
            *pType = ies[i].param_data.longData.data[0];

            data = &ies[i].param_data.longData.data[1];
            stop = ies[i].param_data.longData.data +
                   ies[i].param_data.longData.len;
            ies[i].param_length = 2;
            break;
        }
    }

    if (i == ieCount || ies[i].param_length < 1)
    {
        TCAP_ERROR(("FindPTypeAndTID: No SCCP USER_DATA.\n"));

        TCAP_Alarm_CCITT(1429, __FILE__, __LINE__, NULL);

        return (ITS_NO);
    }

    /* get the Transaction length */
    data += TCAP_GetLength(data, &dummy, stop, ITS_TRUE);

    if (data == &ies[i].param_data.userData.data[1])
    {
        return (ITS_NO);
    }

    switch (*pType)
    {
    case TCPPT_TC_UNI:
        return (ITS_YES);

    case TCPPT_TC_BEGIN:
        /* should have the transaction ID identifier */
        if (*data != OTID_IDENT)
        {
            return (ITS_NO);
        }
        data++;

        return TCAP_GetTID(&data, tid1, tid1Len);

    case TCPPT_TC_END:
    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
        /* should have the transaction ID identifier */
        if (*data != DTID_IDENT)
        {
            return (ITS_NO);
        }
        data++;

        return TCAP_GetTID(&data, tid2, tid2Len);

    case TCPPT_TC_CONTINUE:
        /* should have the transaction ID identifier */
        if (*data != OTID_IDENT)
        {
            if (*data == DTID_IDENT)
            {
                TCAP_ERROR(("FindPTypeAndTID: ...but there is a DTID_IDENT.\n"));

                data++;

                TCAP_GetTID(&data, tid2, tid2Len);
            }

            return (ITS_NO);
        }
        data++;

        if (TCAP_GetTID(&data, tid1, tid1Len) != ITS_YES)
        {
            return (ITS_NO);
        }

        /* should have the transaction ID identifier */
        if (*data != DTID_IDENT)
        {
            /* duplicate OTID? */
            if (*data == OTID_IDENT)
            {
                TCAP_ERROR(("FindPTypeAndTID: ...but there is an OTID_IDENT.\n"));

                data++;

                if (TCAP_GetTID(&data, &dummy, &dummyLen) != ITS_YES)
                {
                    return (ITS_NO);
                }

                if (*data != DTID_IDENT)
                {
                    return (ITS_NO);
                }

                data++;

                TCAP_GetTID(&data, tid2, tid2Len);

                return (ITS_NO);
            }
            else
            {
                return (ITS_NO);
            }
        }
        data++;

        return TCAP_GetTID(&data, tid2, tid2Len);

    default:

        *pType = 0;

        if (*data == OTID_IDENT)
        {
            data++;

            TCAP_GetTID(&data, tid1, tid1Len);
        }
        if (*data == DTID_IDENT)
        {
            data++;

            TCAP_GetTID(&data, tid2, tid2Len);
        }

        if (*data == OTID_IDENT)
        {
            data++;

            TCAP_GetTID(&data, tid1, tid1Len);
        }
        if (*data == DTID_IDENT)
        {
            data++;

            TCAP_GetTID(&data, tid2, tid2Len);
        }

        return (ITS_NO);
    }
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      len Note that the "len" parameter is in/out
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
InferPointCodes(ITS_CTXT did, MTP3_HEADER* mtp3, TCAP_DLG* dlg)
{
    ITS_UINT opc, dpc;

    if (mtp3 == NULL)
    {
        TCAP_ERROR(("InferPointCodes: Missing routing label!\n"));

        return;
    }

    opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);

    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        MTP3_PC_SET_VALUE(dlg->u.uni.opc, opc);
        MTP3_PC_SET_VALUE(dlg->u.uni.dpc, dpc);
        break;
    case TCPPT_TC_BEGIN:
        MTP3_PC_SET_VALUE(dlg->u.begin.opc, opc);
        MTP3_PC_SET_VALUE(dlg->u.begin.dpc, dpc);
        break;
    case TCPPT_TC_CONTINUE:
        if (did & TCAP_DIR_BIT)
        {
            MTP3_PC_SET_VALUE(dlg->u.cont.opc, dpc);
        }
        else
        {
            MTP3_PC_SET_VALUE(dlg->u.cont.opc, opc);
        }
        break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static void
UpdateAddrsAndQOS(TCAP_DLG *dlg, SCCP_ADDR *clp, SCCP_ADDR *cdp,
                  MTP3_HEADER *mtp3, TCAP_TRANS_ENTRY *tr,
                  SCCP_PROT_CLASS* pclass)
{
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        /* get the addrs */
        dlg->u.uni.orig_addr.len = clp->len;
        memcpy(dlg->u.uni.orig_addr.data, clp->data, clp->len);
        dlg->u.uni.dest_addr.len = cdp->len;
        memcpy(dlg->u.uni.dest_addr.data, cdp->data, cdp->len);
        dlg->u.uni.qos.indicator = 0;
        if (pclass)
        {
            if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_1)
            {
                dlg->u.uni.qos.indicator |= QOSI_SEQ_CTRL;
            }
            if (pclass->pclass & SCCP_PCLASS_RET_ON_ERR)
            {
                dlg->u.uni.qos.indicator |= QOSI_RET_OPT;
            }
        }
        if (mtp3)
        {
            dlg->u.uni.qos.sls_key = MTP3_RL_GET_SLS(mtp3->label);
            dlg->u.uni.qos.indicator |= QOSI_SLS_KEY;

            dlg->u.uni.qos.priority =
                MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
            dlg->u.uni.qos.indicator |= QOSI_PRIORITY;
        }

        break;

    case TCPPT_TC_BEGIN:
        /* get the addrs */
        dlg->u.begin.orig_addr.len = clp->len;
        memcpy(dlg->u.begin.orig_addr.data, clp->data, clp->len);
        dlg->u.begin.dest_addr.len = cdp->len;
        memcpy(dlg->u.begin.dest_addr.data, cdp->data, cdp->len);
        dlg->u.begin.qos.indicator = 0;
        if (pclass)
        {
            if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_1)
            {
                dlg->u.begin.qos.indicator |= QOSI_SEQ_CTRL;
            }
            if (pclass->pclass & SCCP_PCLASS_RET_ON_ERR)
            {
                dlg->u.begin.qos.indicator |= QOSI_RET_OPT;
            }
        }
        if (mtp3)
        {
            dlg->u.begin.qos.sls_key = MTP3_RL_GET_SLS(mtp3->label);
            dlg->u.begin.qos.indicator |= QOSI_SLS_KEY;

            dlg->u.begin.qos.priority =
                MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
            dlg->u.begin.qos.indicator |= QOSI_PRIORITY;
        }

        /* save off the QOS */
        tr->qos = dlg->u.begin.qos;

        break;

    case TCPPT_TC_CONTINUE:
        /* get the addrs */
        dlg->u.cont.orig_addr.len = clp->len;
        memcpy(dlg->u.cont.orig_addr.data, clp->data, clp->len);
        dlg->u.cont.qos.indicator = 0;
        if (pclass)
        {
            if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_1)
            {
                dlg->u.cont.qos.indicator |= QOSI_SEQ_CTRL;
            }
            if (pclass->pclass & SCCP_PCLASS_RET_ON_ERR)
            {
                dlg->u.cont.qos.indicator |= QOSI_RET_OPT;
            }
        }
        if (mtp3)
        {
            dlg->u.cont.qos.sls_key = MTP3_RL_GET_SLS(mtp3->label);
            dlg->u.cont.qos.indicator |= QOSI_SLS_KEY;

            dlg->u.cont.qos.priority =
                MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
            dlg->u.cont.qos.indicator |= QOSI_PRIORITY;
        }

        /* save off the QOS */
        tr->qos = dlg->u.cont.qos;

        /* update the addrs: MLM (IS THIS RIGHT?) */
        if (tr->state == ITS_TCAP_BEGIN_SENT)
        {
            ITS_UINT tmp;

            tr->daddr = *clp;

            tr->label = *mtp3;
            tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            MTP3_RL_SET_OPC_VALUE(tr->label.label, tmp);
            tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            MTP3_RL_SET_DPC_VALUE(tr->label.label, tmp);
        }
        break;

    case TCPPT_TC_END:
        dlg->u.end.qos.indicator = 0;
        if (pclass)
        {
            if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_1)
            {
                dlg->u.end.qos.indicator |= QOSI_SEQ_CTRL;
            }
            if (pclass->pclass & SCCP_PCLASS_RET_ON_ERR)
            {
                dlg->u.end.qos.indicator |= QOSI_RET_OPT;
            }
        }
        if (mtp3)
        {
            dlg->u.end.qos.sls_key = MTP3_RL_GET_SLS(mtp3->label);
            dlg->u.end.qos.indicator |= QOSI_SLS_KEY;

            dlg->u.end.qos.priority =
                MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
            dlg->u.end.qos.indicator |= QOSI_PRIORITY;
        }

        /* save off the QOS */
        tr->qos = dlg->u.end.qos;

        break;

    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:
        dlg->u.abort.qos.indicator = 0;
        if (pclass)
        {
            if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_1)
            {
                dlg->u.abort.qos.indicator |= QOSI_SEQ_CTRL;
            }
            if (pclass->pclass & SCCP_PCLASS_RET_ON_ERR)
            {
                dlg->u.abort.qos.indicator |= QOSI_RET_OPT;
            }
        }
        if (mtp3)
        {
            dlg->u.abort.qos.sls_key = MTP3_RL_GET_SLS(mtp3->label);
            dlg->u.abort.qos.indicator |= QOSI_SLS_KEY;

            dlg->u.abort.qos.priority =
                MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
            dlg->u.abort.qos.indicator |= QOSI_PRIORITY;
        }

        /* save off the QOS */
        tr->qos = dlg->u.abort.qos;

        break;
    }
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      len Note that the "len" parameter is in/out
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
UpdateDialogueState(ITS_OCTET *pType,
                    TCAP_DLG *dlg,
                    TCAP_TRANS_ENTRY *tr,
                    ITS_CTXT did, ITS_EVENT *event,
                    ITS_SCCP_IE *ies, int ieCount)
{
    switch (*pType)
    {
    case TCPPT_TC_UNI:
        break;

    case TCPPT_TC_BEGIN:
        ITS_C_ASSERT(tr != NULL);
        if (dlg->u.begin.ac_name.len != 0 ||
            dlg->u.begin.user_info.len != 0)
        {
            tr->dstate = ITS_DLG_AARQ_RCVD;
        }
        break;

    case TCPPT_TC_END:
        ITS_C_ASSERT(tr != NULL);
        if (dlg->u.end.ac_name.len != 0 ||
            dlg->u.end.user_info.len != 0)
        {
            if (tr->dstate == ITS_DLG_AARQ_SENT)
            {
                tr->dstate = ITS_DLG_ACTIVE;
            }
            else if (tr->dstate == ITS_DLG_ACTIVE)
            {
                __TCAP_SendAppPAbort_CCITT(did, event,
                                           TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

                __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                             TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

        
                /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1438, __FILE__, __LINE__, NULL);

                return (ITS_EPROTERR);
            }
        }
        else
        {
            if (tr->dstate == ITS_DLG_AARQ_SENT)
            {
                tr->dstate = ITS_DLG_NONE;

                __TCAP_SendAppPAbort_CCITT(did, event,
                                           TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

                /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1438, __FILE__, __LINE__, NULL);

                return (ITS_EPROTERR);
            }
            else if (tr->dstate == ITS_DLG_ACTIVE)
            {
                /* do nothing */
            }
        }
        break;

     case TCPPT_TC_CONTINUE:
        if (dlg->u.cont.ac_name.len != 0 ||
            dlg->u.cont.user_info.len != 0)
        {
            if (tr->dstate == ITS_DLG_AARQ_SENT)
            {
                tr->dstate = ITS_DLG_ACTIVE;
            }
            else
            {
                __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                             TCPPABT_ABNORMAL_DLG);

                __TCAP_SendAppPAbort_CCITT(did, event,
                                           TCPPABT_ABNORMAL_DLG);

                /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1438, __FILE__, __LINE__, NULL);

                return (ITS_EPROTERR);
            }
        }
        else
        {
            if (tr->dstate == ITS_DLG_AARQ_SENT)
            {
                tr->dstate = ITS_DLG_NONE;

                __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                             TCPPABT_ABNORMAL_DLG);

                __TCAP_SendAppPAbort_CCITT(did, event,
                                           TCPPABT_ABNORMAL_DLG);

                /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1438, __FILE__, __LINE__, NULL);

                return (ITS_EPROTERR);
            }
            else if (tr->dstate == ITS_DLG_ACTIVE)
            {
                /* do nothing */
            }
        }
        break;

    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
        ITS_C_ASSERT(tr != NULL);
        if (dlg->u.abort.ac_name.len != 0 ||
            dlg->u.abort.user_info.len != 0)
        {
            if (tr->dstate == ITS_DLG_AARQ_SENT)
            {
                tr->dstate = ITS_DLG_ACTIVE;
            }
            else if (tr->dstate == ITS_DLG_ACTIVE)
            {
                __TCAP_SendAppPAbort_CCITT(did, event,
                                           TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

                /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1438, __FILE__, __LINE__, NULL);

                return (ITS_EPROTERR);
            }
        }
        else
        {
            if (tr->dstate == ITS_DLG_AARQ_SENT)
            {
                tr->dstate = ITS_DLG_NONE;
            }
            else if (tr->dstate == ITS_DLG_ACTIVE)
            {
                if (dlg->ptype == TCPPT_TC_U_ABORT)
                {
                    __TCAP_SendAppPAbort_CCITT(did, event,
                                               TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

                
                    /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
                    TCAP_Alarm_CCITT(1438, __FILE__, __LINE__, NULL);

                    return (ITS_EPROTERR);
                }
            }
        }
        break;
    }

    return (ITS_SUCCESS);
}
/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose: To increment the PEGS for All Dialogue types.
 *           TCPPT_TC_UNI, TCPPT_TC_QUERY_W_PERM, TCPPT_TC_QUERY_WO_PERM,
 *           TCPPT_TC_RESP, TCPPT_TC_CONV_W_PERM, TCPPT_TC_CONV_WO_PERM,
 *           TCPPT_TC_ABORT, TCPPT_TC_NOTICE
 *      None.
 *
 *  Input Parameters:
 *      dlg -> dialogue.
 *
 *  Input/Output Parameters:
 *      None
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
UpdateDlgPeg(TCAP_DLG *dlg)
{
    switch(dlg->ptype)
    {
        case TCPPT_TC_UNI:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_UNI_RCVD);
            break;

        case TCPPT_TC_BEGIN:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_BEGIN_RCVD);
            break;

        case TCPPT_TC_END:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_END_RCVD);

            PEG_DecrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE);
            PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
            break;

        case TCPPT_TC_CONTINUE:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CONT_RCVD);
            break;

        case TCPPT_TC_P_ABORT:
        case TCPPT_TC_U_ABORT:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_ABORT_RCVD);

            PEG_DecrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE);
            PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
            break;
        default:
            break;
    }
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose: To increment the PEGS for All component types.
 *          TCPPT_TC_INVOKE,TCPPT_TC_INVOKE_NL, TCPPT_TC_RESULT, TCPPT_TC_RESULT_NL,
 *          TCPPT_TC_ERROR, TCPPT_TC_REJECT, or TCPPT_TC_CANCEL.
 *
 *      None.
 *
 *  Input Parameters:
 *      cpt -> component.
 *
 *  Input/Output Parameters:
 *      None
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
UpdateCptPeg(TCAP_CPT *cpt)
{
    switch(cpt->ptype)
    {
        case TCPPT_TC_INVOKE:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_INVOKE_RCVD);
            break;

        case TCPPT_TC_RESULT_NL:
        case TCPPT_TC_RESULT_L: 
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_RESULT_RCVD);
            break;

        case TCPPT_TC_U_ERROR:
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_ERROR_RCVD);
            break;

        case TCPPT_TC_U_REJECT:
        case TCPPT_TC_R_REJECT: 
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_REJECT_RCVD);
            break;

        default:
            break;
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static int
ParseTRP(struct type_ITU__TCAP_MessageType **pdu, ITS_OCTET *tp, int wlen)
{
    ITS_OCTET *data;
    ITS_UINT tag, len;
    struct type_ITU__TCAP_MessageType *ret = NULL;

    *pdu = NULL;

    if (!tp)
    {
        return (ITS_EPROTERR);
    }

    /* get the PType */
    data = tp;
    data += TCAP_GetTag(data, &tag, data + wlen);
    if (data == tp)
    {
        return (ITS_EPROTERR);
    }

    /* get the len */
    tp = data;
    data += TCAP_GetLength(data, &len, data + wlen, ITS_TRUE);
    if (data == tp)
    {
        return (ITS_EPROTERR);
    }

    /* allocate PDU */
    ret = (struct type_ITU__TCAP_MessageType *)
            calloc(1, sizeof(struct type_ITU__TCAP_MessageType));

    if (!ret)
    {
        return (ITS_EPROTERR);
    }

    switch (tag)
    {
    case TCPPT_TC_UNI:
        ret->offset = type_ITU__TCAP_MessageType_unidirectional;

        /* allocate TRP */
        ret->un.unidirectional = (struct type_ITU__TCAP_Unidirectional *)
                                    calloc(1, sizeof(struct type_ITU__TCAP_Unidirectional));

        if (!ret->un.unidirectional)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        break;

    case TCPPT_TC_BEGIN:
        ret->offset = type_ITU__TCAP_MessageType_begin;

        /* Allocate TRP */
        ret->un.begin = (struct type_ITU__TCAP_Begin *)
                            calloc(1, sizeof(struct type_ITU__TCAP_Begin));

        if (!ret->un.begin)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != OTID_IDENT)
        {
            free(ret->un.begin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += TCAP_GetTag(data, &tag, data + wlen);
        data += TCAP_GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.begin->otid = (struct type_ITU__TCAP_OrigTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_OrigTransactionID) + wlen);

        if (!ret->un.begin->otid)
        {
            free(ret->un.begin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.begin->otid->qb_forw = ret->un.begin->otid;
        ret->un.begin->otid->qb_back = ret->un.begin->otid;
        ret->un.begin->otid->qb_data = ret->un.begin->otid->qb_base;
        ret->un.begin->otid->qb_len = len;
        memcpy(ret->un.begin->otid->qb_data, data, len);
        break;

    case TCPPT_TC_CONTINUE:
        ret->offset = type_ITU__TCAP_MessageType_contin;

        /* allocate TRP */
        ret->un.contin = (struct type_ITU__TCAP_Continue *)
                            calloc(1, sizeof(struct type_ITU__TCAP_Continue));

        if (!ret->un.contin)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != OTID_IDENT)
        {
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += TCAP_GetTag(data, &tag, data + wlen);
        data += TCAP_GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.contin->otid = (struct type_ITU__TCAP_OrigTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_OrigTransactionID) + wlen);

        if (!ret->un.contin->otid)
        {
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.contin->otid->qb_forw = ret->un.contin->otid;
        ret->un.contin->otid->qb_back = ret->un.contin->otid;
        ret->un.contin->otid->qb_data = ret->un.contin->otid->qb_base;
        ret->un.contin->otid->qb_len = len;
        memcpy(ret->un.contin->otid->qb_data, data, len);

        /* check TID */
        data += len;
        if (*data != DTID_IDENT)
        {
            free(ret->un.contin->otid);
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += TCAP_GetTag(data, &tag, data + wlen);
        data += TCAP_GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.contin->dtid = (struct type_ITU__TCAP_DestTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + wlen);

        if (!ret->un.contin->dtid)
        {
            free(ret->un.contin->otid);
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.contin->dtid->qb_forw = ret->un.contin->dtid;
        ret->un.contin->dtid->qb_back = ret->un.contin->dtid;
        ret->un.contin->dtid->qb_data = ret->un.contin->dtid->qb_base;
        ret->un.contin->dtid->qb_len = len;
        memcpy(ret->un.contin->dtid->qb_data, data, len);
        break;

    case TCPPT_TC_END:
        ret->offset = type_ITU__TCAP_MessageType_end;

        /* Allocate TRP */
        ret->un.end = (struct type_ITU__TCAP_End *)
                        calloc(1, sizeof(struct type_ITU__TCAP_End));

        if (!ret->un.end)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != DTID_IDENT)
        {
            free(ret->un.end);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += TCAP_GetTag(data, &tag, data + wlen);
        data += TCAP_GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.end->dtid = (struct type_ITU__TCAP_DestTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + wlen);

        if (!ret->un.end->dtid)
        {
            free(ret->un.end);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.end->dtid->qb_forw = ret->un.end->dtid;
        ret->un.end->dtid->qb_back = ret->un.end->dtid;
        ret->un.end->dtid->qb_data = ret->un.end->dtid->qb_base;
        ret->un.end->dtid->qb_len = len;
        memcpy(ret->un.end->dtid->qb_data, data, len);
        break;

    case TCPPT_TC_P_ABORT:
        ret->offset = type_ITU__TCAP_MessageType_abort;

        ret->un.abort = (struct type_ITU__TCAP_Abort *)
                           calloc(1, sizeof(struct type_ITU__TCAP_Abort));

        if (!ret->un.abort)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != DTID_IDENT)
        {
            free(ret->un.abort);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += TCAP_GetTag(data, &tag, data + wlen);
        data += TCAP_GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.abort->dtid = (struct type_ITU__TCAP_DestTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + wlen);

        if (!ret->un.abort->dtid)
        {
            free(ret->un.abort);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.abort->dtid->qb_forw = ret->un.abort->dtid;
        ret->un.abort->dtid->qb_back = ret->un.abort->dtid;
        ret->un.abort->dtid->qb_data = ret->un.abort->dtid->qb_base;
        ret->un.abort->dtid->qb_len = len;
        memcpy(ret->un.abort->dtid->qb_data, data, len);
        break;

    default:
        free(ret);
        return (ITS_EPROTERR);
    }

    *pdu = ret;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static int
ParseDLG(struct type_ITU__TCAP_MessageType *pdu,
         ITS_OCTET *dp, ITS_OCTET *stop)
{
    ITS_OCTET *data = dp, *tmp;
    ITS_UINT tag, len;
    int err = PS_ERR_NONE;
    PE pe;

    if (!dp)
    {
        return (ITS_SUCCESS);
    }

    if (TCAP_Variant != TCAP_WHITE_BOOK)
    {
        if (pdu->offset != type_ITU__TCAP_MessageType_abort)
        {
            return (ITS_EPROTERR);
        }
    }

    /* compute length and check tag */
    data += TCAP_GetTag(data, &tag, stop);
    if (data == dp)
    {
        return (ITS_EPROTERR);
    }

    tmp = data;
    data += TCAP_GetLength(data, &len, stop, ITS_TRUE);
    if (data == tmp)
    {
        return (ITS_EPROTERR);
    }

    pe = ssdu2pe((char *)dp, len + (data - dp), NULL, &err);
    if (err != PS_ERR_NONE)
    {
        return (ITS_EPROTERR);
    }

    switch (pdu->offset)
    {
    case type_ITU__TCAP_MessageType_unidirectional:
        pdu->un.unidirectional->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_begin:
        pdu->un.begin->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_contin:
        pdu->un.contin->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_end:
        pdu->un.end->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_abort:
        pdu->un.abort->reason = (struct choice_ITU__TCAP_2 *)
                                    calloc(1, sizeof(struct choice_ITU__TCAP_2));

        if (!pdu->un.abort->reason)
        {
            return (ITS_EPROTERR);
        }

        if (tag == DIALOG_IDENT)
        {
            pdu->un.abort->reason->offset = choice_ITU__TCAP_2_dialoguePortion;
            pdu->un.abort->reason->un.dialoguePortion = pe;
        }
        else if (tag == PABT_IDENT)
        {
            pdu->un.abort->reason->offset = choice_ITU__TCAP_2_p__abort__cause;
            if (decode_ITU__TCAP_P__AbortCause(pe, 1, NULL, NULL, 
                                               (char **)&pdu->un.abort->reason->un.p__abort__cause)
                != OK)
            {
                free(pdu->un.abort->reason);
                pdu->un.abort->reason = NULL;

                return (ITS_EPROTERR);
            }
        }
        else
        {
            free(pdu->un.abort->reason);
            pdu->un.abort->reason = NULL;

            return (ITS_EPROTERR);
        }

        break;

    default:
        pe_free(pe);
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static struct type_ITU__TCAP_ComponentPDU *
GenerateReject(ITS_BOOLEAN derivable, ITS_OCTET *inv_id, ITS_OCTET* stop)
{
    TCAP_CPT rej;
    ITS_UINT tag, len;
    ITS_OCTET *tmp = inv_id;

    memset(&rej, 0, sizeof(TCAP_CPT));
    rej.ptype = TCPPT_TC_L_REJECT;

    if (derivable)
    {
        tmp += TCAP_GetTag(tmp, &tag, stop);
        tmp += TCAP_GetLength(tmp, &len, stop, ITS_FALSE);

        if (tmp != inv_id)
        {
            rej.u.reject.invoke_id.len = len + (tmp - inv_id);
            memcpy(rej.u.reject.invoke_id.data, inv_id, len + (tmp - inv_id));
        }
    }

    rej.u.reject.problem.len = 3;
    rej.u.reject.problem.data[0] = TCPPROB_GENERAL | LOCAL_REJECT_MARKER;
    rej.u.reject.problem.data[1] = 1;
    rej.u.reject.problem.data[2] = TCPPROB_SPEC_GEN_MISTYPED_COMP;

    return TCAP_CvtCPTToComponentPDU_CCITT(&rej);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static int
ParseCMP(struct type_ITU__TCAP_MessageType *pdu,
         ITS_OCTET *cp, ITS_OCTET *stop)
{
    ITS_OCTET *data = cp;
    ITS_UINT tag, len;
    struct type_ITU__TCAP_ComponentPortion *cseq = NULL;

    if (!cp)
    {
        return (ITS_SUCCESS);
    }

    data += TCAP_GetTag(data, &tag, stop);
    if (data == cp)
    {
        return (ITS_EPROTERR);
    }

    cp = data;
    data += TCAP_GetLength(data, &len, stop, ITS_TRUE);
    if (data == cp)
    {
        return (ITS_EPROTERR);
    }

    if (len == 0 || (data[0] == 0 && data[1] == 0))
    {
        if (pdu->offset == type_ITU__TCAP_MessageType_unidirectional)
        {
            return (ITS_EPROTERR);
        }
        else
        {
            return (ITS_SUCCESS);
        }
    }

    while (data < cp + len && data[0] != 0 && data[1] != 0)
    {
        ITS_OCTET *limit = data, *comp, *tmp;
        PE pe;
        int err;
        struct type_ITU__TCAP_ComponentPortion *c, **list;

        limit = data + TCAP_GetSub(data, stop);

        if (limit == data)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        comp = data;

        /* compute length and check tag */
        comp += TCAP_GetTag(comp, &tag, stop);
        if (comp == data)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        tmp = comp;
/* old code was
        comp += ParseCMP(comp, &len, stop);
*/
        comp += TCAP_GetLength(comp, &len, stop, ITS_TRUE);
        if (comp == tmp)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        pe = ssdu2pe((char *)data, len + (comp - data), NULL, &err);
        if (err != PS_ERR_NONE)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        c = (struct type_ITU__TCAP_ComponentPortion *)
                calloc(1, sizeof(struct type_ITU__TCAP_ComponentPortion));

        if (!c)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        if (decode_ITU__TCAP_ComponentPDU(pe, 1, NULL, NULL,
                                          (char **)&c->ComponentPDU) != OK)
        {

            switch (tag)
            {
            case TCPPT_TC_INVOKE:
            case TCPPT_TC_RESULT_L:
            case TCPPT_TC_RESULT_NL:
            case TCPPT_TC_U_ERROR:
                if (*comp == TCPPN_INVOKE_TAG &&
                    (*(comp+1) > 0 && *(comp+1) <= 4))
                {
                    c->ComponentPDU = GenerateReject(ITS_TRUE,
                                                     comp, stop);
                }
                else
                {
                    c->ComponentPDU = GenerateReject(ITS_FALSE,
                                                     NULL, NULL);
                }

                if (!c->ComponentPDU)
                {
                    if (cseq)
                    {
                        free_ITU__TCAP_ComponentPortion(cseq);
                    }

                    return (ITS_EPROTERR);
                }
                break;

            case TCPPT_TC_R_REJECT:
                break;

            default:
                if (cseq)
                {
                    free_ITU__TCAP_ComponentPortion(cseq);
                }

                return (ITS_EPROTERR);
            }
        }

        for (list = &cseq; *list != NULL; list = &(*list)->next)
        {
        }

        *list = c;

        data = comp + len;
    }

    switch (pdu->offset)
    {
    case type_ITU__TCAP_MessageType_unidirectional:
        pdu->un.unidirectional->components = cseq;
        break;

    case type_ITU__TCAP_MessageType_begin:
        pdu->un.begin->components = cseq;
        break;

    case type_ITU__TCAP_MessageType_contin:
        pdu->un.contin->components = cseq;
        break;

    case type_ITU__TCAP_MessageType_end:
        pdu->un.end->components = cseq;
        break;

    default:
        if (cseq)
        {
            free_ITU__TCAP_ComponentPortion(cseq);
        }
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
struct type_ITU__TCAP_MessageType *
CCITT_DecodeTCAPData(ITS_OCTET *data, ITS_USHORT len)
{
    PE pe = NULL;
    struct type_ITU__TCAP_MessageType *pdu = NULL;
    int err = PS_ERR_NONE;
    enum ParseCode pc = PC_PARSE_OK;

    pe = ssdu2pe((char *)data, len, NULL, &err);
    if (err != PS_ERR_NONE)
    {
        TCAP_ERROR(("CCITT_DecodeTCAPData: decode failed.\n"));

        /* Failed to decode TCAP data */
        TCAP_Alarm_CCITT(1439,__FILE__,__LINE__,NULL);  

        return (NULL);
    }

    if (decode_ITU__TCAP_MessageType(pe, 1, NULL, NULL, (char **)&pdu) == OK)
    {
        TCAP_DEBUG(("CCITT_DecodeTCAPData: Package decode successful.\n"));
    }
    else
    {
        ITS_OCTET *tp = NULL, *dp = NULL, *cp = NULL;

        pe_free(pe);

        TCAP_DEBUG(("CCITT_DecodeTCAPData: PE decode failed.  "
                    "Trying partial decode.\n"));

        pc = TCAP_FindParts_CCITT(data, len, &tp, &dp, &cp);

        if (pc != PC_PARSE_OK)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: parser failure.\n"));

            return (NULL);
        }

        if (ParseTRP(&pdu, tp, len) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: TRP parser failure.\n"));

            return (NULL);
        }

        if (ParseDLG(pdu, dp, tp + len) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: DLG parser failure.\n"));

            free_ITU__TCAP_MessageType(pdu);

            return (NULL);
        }

        if (ParseCMP(pdu, cp, tp + len) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: DLG parser failure.\n"));

            free_ITU__TCAP_MessageType(pdu);

            return (NULL);
        }

        return (pdu);
    }

    pe_free(pe);

    return (pdu);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
#if defined (PEPSY_CODEC)
static int
PEPSY_DisassemblePDU(ITS_SCCP_IE *ies, int ieCount, TCAP_TRANS_ENTRY* tr)
{
    TCAP_DLG dlg;
    TCAP_CPT cpt;
    ITS_EVENT event;
    ITS_OCTET pType;
    int i;
    struct type_ITU__TCAP_MessageType *pdu;
    ITS_OCTET *data;
    ITS_USHORT len;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_CTXT did = 0;
    ITS_BOOLEAN isUNI = ITS_FALSE;
    SCCP_PROT_CLASS *pclass = NULL;
    MTP3_HEADER *mtp3 = NULL;

    TCAP_DEBUG(("PEPSY_DisassemblePDU \n"));

    /*
     * Step 0.  Do overhead work
     */
    if (tr)
    {
        did = tr->did;
    }
    else
    {
        /* has to be a UNI */
        TCAP_DEBUG(("PEPSY_DisassemblePDU: No TRANS_CTXT!\n"));
    }


    /*
     * Step 1.  Decode the SCCP message
     */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_RETURN_CAUSE)
        {
            /* TC-NOTICE */
            memset(&dlg, 0, sizeof(TCAP_DLG));

            hdr.type = ITS_TCAP;
            hdr.context.dialogue_id = did;
            dlg.ptype = TCPPT_TC_NOTICE;

            dlg.u.notice.report_cause = ies[i].param_data.returnCause.cause;

            if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
            {
                /* Count it as discarded */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED); 
                TCAP_ERROR(("PEPSY_DisassemblePDU: Sanity check failed.\n"));

                /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */

                return ITS_BADTCAPMESSAGE;
            }

            hdr.type = ITS_TCAP;
            hdr.context.dialogue_id = did;

            ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                           1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
            event.data[0] = ITS_TCAP_DLG;
            ITS_SET_CTXT(&event.data[1], did);
            memcpy(&event.data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                   &dlg, sizeof(TCAP_DLG));

            dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
            if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
            {
                TCAP_DEBUG(("PEPSY_DisassemblePDU: Send NOTICE to %04x\n", dest));

                /* Notice sent toward Application is received by Application */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);

                TRANSPORT_PutEvent(dest, &event);
                TCAP_Alarm_CCITT(1430, __FILE__, __LINE__, NULL);
            }
            else
            {
                /* Notice Discarded */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
                TCAP_ERROR(("PEPSY_DisassemblePDU: Unable to send NOTICE to APP.\n"));

                /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */
            }

            ITS_EVENT_TERM(&event);

            return (ITS_EPROTERR);
        }
        else if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
        {
            pclass = &ies[i].param_data.protocolClass;
        }
        else if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
        {
            mtp3 = &ies[i].param_data.routingLabel;
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
            break;
        }
    }

    if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_0)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD);
    }
    else
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD);
    }

    if (i == ieCount || ies[i].param_length < 1)
    {
        /*
         * can't really reject here, can only discard.
         * The UDT message was malformed. If SCCP is working correctly,
         * this should never happen.
         */
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);

        TCAP_ERROR(("PEPSY_DisassemblePDU: No SCCP user data.\n"));

        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1429, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }
    pType = ies[i].param_data.userData.data[0];

    data = ies[i].param_data.userData.data;
    len = ies[i].param_length;

    /*
     * Step 2.  Decode the transaction
     */
    if (data == NULL || len == 0)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
        TCAP_ERROR(("PEPSY_DisassemblePDU: No SCCP user data.\n"));

        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1429, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    pdu = CCITT_DecodeTCAPData(data, len);
    if (pdu == NULL)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        if (tr != NULL && *data != TCPPT_TC_BEGIN) /* Not a UNI, or BEGIN? */
        {
            __TCAP_SendAppPAbort_CCITT(tr->did, NULL,
                                       TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1431, __FILE__, __LINE__, NULL);
        }

        if (tr != NULL)
        {
            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1431, __FILE__, __LINE__, NULL);
        }

        return (ITS_EPROTERR);
    }

    /*
     * Step 3.  Build the TCAP_DLG and send it to the user
     */
    if (TCAP_CvtMessageToDLG_CCITT(&dlg, pdu, TCAP_Variant) != ITS_SUCCESS)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: Could not recover dialog portion.\n"));

        free_ITU__TCAP_MessageType(pdu);

        if (tr != NULL && *data != TCPPT_TC_BEGIN)
        {
            __TCAP_SendAppPAbort_CCITT(tr->did, NULL,
                                       TCPABT_REASON_INCORRECT_TRANS_PORT);

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1431, __FILE__, __LINE__, NULL);
        }

        if (tr != NULL)
        {
            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_INCORRECT_TRANS_PORT);

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1431, __FILE__, __LINE__, NULL);
        }

        return (ITS_EPROTERR);
    }

    /* Determine QOS params */
    UpdateAddrsAndQOS(&dlg, clp, cdp, mtp3, tr, pclass);

    /* UNI, BEGIN, CONTINUE need point code information */
    InferPointCodes(did, mtp3, &dlg);

    /*
     * uni(s) do not get a transaction context, nor do invokes
     * that they carry get an invoke context.
     */
    if (pType == TCPPT_TC_UNI)
    {
        isUNI = ITS_TRUE;
    }

    if (TCAP_Variant == TCAP_WHITE_BOOK)
    {
        int ret = UpdateDialogueState(&pType, &dlg, tr,
                                      did, &event,
                                      ies, ieCount);

        if (ret != ITS_SUCCESS)
        {
            free_ITU__TCAP_MessageType(pdu);
            return ret;
        }
    }

    if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
    {
        TCAP_ERROR(("PEPSY_DisassemblePDU: Sanity check failed.\n"));

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        free_ITU__TCAP_MessageType(pdu);

        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1432, __FILE__, __LINE__, NULL);

        return ITS_BADTCAPMESSAGE;
    }

    ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
    event.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&event.data[1], did);
    memcpy(&event.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        TCAP_DEBUG(("PEPSY_DisassemblePDU: Send DLG to %04x\n", dest));
        
        /* Add to the peg counters - Msg Received from Remote */
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_DLG_RCVD);
        UpdateDlgPeg(&dlg);

        TRANSPORT_PutEvent(dest, &event);
    }
    else
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: Unable to send DLG to APP.\n"));

        /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */
    }

    ITS_EVENT_TERM(&event);

    /*
     * Step 4.  If any components are  present, build them
     * and send them to CMP
     */
    if (pdu->offset != type_ITU__TCAP_MessageType_abort)
    {
        struct type_ITU__TCAP_ComponentPortion *comp = NULL;

        switch (pdu->offset)
        {
        case type_ITU__TCAP_MessageType_unidirectional:
            comp = pdu->un.unidirectional->components;
            break;
        case type_ITU__TCAP_MessageType_begin:
            comp = pdu->un.begin->components;
            break;
        case type_ITU__TCAP_MessageType_end:
            comp = pdu->un.end->components;
            break;
        case type_ITU__TCAP_MessageType_contin:
            comp = pdu->un.contin->components;
            break;
        }

        while (comp != NULL)
        {
            int ret;

            if ((ret = TCAP_CvtComponentPDUToCPT_CCITT(&cpt, comp->ComponentPDU))
                != ITS_SUCCESS)
            {
                TCAP_ERROR(("PEPSY_DisassemblePDU: Could not recover component "
                            "portion.\n"));

                free_ITU__TCAP_MessageType(pdu);

                __TCAP_SendRemoteReject_CCITT(did, NULL,
                                              TCPPROB_GENERAL,
                                              TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);

                /* Incoming Component - Discarding Component - Rejection Sent by stack. */

                /* UNIDIRECTIONAL are done at this point */
                if (isUNI)
                {
                    /*
                     * TODO TCAP_CleanInvokeContext_CCITT(did);
                     */
                }

                /*
                 * In certain application architectures, we'll want to clean
                 * up the application context.
                 */
                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;
                ROUTE_DeselectApplication(dest, &hdr);

                return ret;
            }

            if (comp->next == NULL)
            {
                cpt.last_component = 1;
            }
            UpdateCptPeg(&cpt);

            /* Add To Component Count for Received Component */
             PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_RCVD);

            /* Send to CMP */
            if ((ret = CCOHandleDHAMsg_CCITT(did, &cpt)) != ITS_SUCCESS)
            {
                TCAP_ERROR(("PEPSY_DisassemblePDU: Could not handle component.\n"));

                free_ITU__TCAP_MessageType(pdu);

                /* UNIDIRECTIONAL are done at this point */
                if (isUNI)
                {
                    /*
                     * TODO TCAP_CleanInvokeContext_CCITT(did);
                     */
                }

                /* Incoming Component - Discarding Component - Invalid or Corrupted. */
                TCAP_Alarm_CCITT(1439, __FILE__, __LINE__, NULL);

                /*
                 * In certain application architectures, we'll want to clean
                 * up the application context.
                 */
                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;
                ROUTE_DeselectApplication(dest, &hdr);

                return ret;
            }

            comp = comp->next;
        }
    }

    /* UNIDIRECTIONAL are done at this point */
    if (isUNI)
    {
        /*
         * TODO TCAP_CleanInvokeContext_CCITT(did);
         */
    }

    /*
     * Step 5.  Clean up and go home
     */
    free_ITU__TCAP_MessageType(pdu);

    /*
     * In certain application architectures, we'll want to clean
     * up the application context.
     */
    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    ROUTE_DeselectApplication(dest, &hdr);

    return (ITS_SUCCESS);
}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *
 *  Revision History:
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     04-07-2005  WSC Bug Id#1170         TCAP decoding fails if the  
 *                                               total TCAP length is 128.  
 *
 * snagesh   04-08-2005  None                    Fix for compilaton issue
 * 
 * sbabu     04-11-2005  HelpDesk ID#742         Indeterminate Length Decode
 *
 * csireesh  20-05-2005  ID::R0140 to R0160      Reassembly Implementation
 *
 * ****************************************************************************/
#if defined (TCAP_CODEC)
static int
TCAP_DisassemblePDU(ITS_SCCP_IE *ies, int ieCount, TCAP_TRANS_ENTRY* tr)
{
    TCAP_DLG dlg;
    TCAP_CPT cpt;
    ITS_EVENT event;
    ITS_OCTET pType;
    int i;
    ITS_OCTET *data, *stop;
    ITS_USHORT len;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_CTXT did = 0;
    ITS_BOOLEAN isUNI = ITS_FALSE;
    SCCP_PROT_CLASS *pclass = NULL;
    MTP3_HEADER *mtp3 = NULL;
    enum ParseCode pc = PC_PARSE_OK;
    ITS_BOOLEAN cpPresent = ITS_FALSE;
    ITS_OCTET *tp = NULL, *dp = NULL, *cp = NULL;
    ITS_OCTET *cpData, *comp;
    ITS_UINT cpTag, cpLen, cTag, cLen;
    int numCpts = 0;
    ITS_UINT cptsLen = 0;
    int extCptOctets = 0;
    int ret;

    TCAP_DEBUG(("TCAP_DisassemblePDU \n"));

    /*
     * Step 0.  Do overhead work
     */
    if (tr)
    {
        did = tr->did;
    }
    else
    {
        /* has to be a UNI */
        TCAP_DEBUG(("DisassemblePDU: No TRANS_CTXT!\n"));
    }

    /*
     * Step 1.  Decode the SCCP message
     */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_RETURN_CAUSE)
        {
            /* TC-NOTICE */
            memset(&dlg, 0, sizeof(TCAP_DLG));

            hdr.type = ITS_TCAP;
            hdr.context.dialogue_id = did;
            dlg.ptype = TCPPT_TC_NOTICE;

            dlg.u.notice.report_cause = ies[i].param_data.returnCause.cause;

            if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
            {
                /* Count it as discarded */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
                TCAP_ERROR(("TCAP_DisassemblePDU: Sanity check failed.\n"));
                
                /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */

                return ITS_BADTCAPMESSAGE;
            }

            hdr.type = ITS_TCAP;
            hdr.context.dialogue_id = did;

            ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                           1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
            event.data[0] = ITS_TCAP_DLG;
            ITS_SET_CTXT(&event.data[1], did);
            memcpy(&event.data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                   &dlg, sizeof(TCAP_DLG));

            dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
            if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
            {
                TCAP_DEBUG(("TCAP_DisassemblePDU: Send NOTICE to %04x\n", dest));

                /* Notice sent toward Application is received by Application */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);

                TRANSPORT_PutEvent(dest, &event);
            }
            else
            {
                /* Notice Discarded */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

                TCAP_ERROR(("TCAP_DisassemblePDU: Unable to send NOTICE to APP.\n"));
                
                /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */
                TCAP_Alarm_CCITT(1430, __FILE__, __LINE__, NULL);

            }

            ITS_EVENT_TERM(&event);

            return (ITS_EPROTERR);
        }
        else if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
        {
            pclass = &ies[i].param_data.protocolClass;
        }
        else if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
        {
            mtp3 = &ies[i].param_data.routingLabel;
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
            pType = ies[i].param_data.userData.data[0];

            data = ies[i].param_data.userData.data;
            len = ies[i].param_length;
            break;
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        {
            pType = ies[i].param_data.longData.data[0];

            data = ies[i].param_data.longData.data;
            len = ies[i].param_data.longData.len;
            break;
        }
    }

    if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_0) 
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD);
    }
    else
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD);
    }

    if (i == ieCount || ies[i].param_length < 1)
    {
        /*
         * can't really reject here, can only discard.
         * The UDT message was malformed. If SCCP is working correctly,
         * this should never happen.
         */
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);

        TCAP_ERROR(("TCAP_DisassemblePDU: No SCCP user data.\n"));
                
        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1429, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    /*
     * Step 2.  Decode the transaction
     */
    if (data == NULL || len == 0)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("TCAP_DisassemblePDU: No SCCP user data.\n"));
        
        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1429, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    /* Parse data */
    pc = TCAP_FindParts_CCITT(data, len, &tp, &dp, &cp);

    if (pc != PC_PARSE_OK)
    {
        TCAP_ERROR(("TCAP_DisassemblePDU: Could not find parts.\n"));

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        if ((tr != NULL && 
            (*data == TCPPT_TC_BEGIN || 
             *data == TCPPT_TC_CONTINUE)))
        {
            if (*data == TCPPT_TC_CONTINUE)
            {
                __TCAP_SendAppPAbort_CCITT(tr->did, NULL,
                                           TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);
            } 
   
            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_BADLY_STRUCT_TRANS_PORT);

        }
        else
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Discarding message.\n"));  
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_CCITT(1431, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    if (cp != NULL && cp[0] == CSEQ_IDENT)
    {
        cpPresent = ITS_TRUE;
    }

    /*
     * Step 3.  Build the TCAP_DLG and send it to the user
     */
    if (TCAP_CvtDataToDLG_CCITT(&dlg, &pType, tp, dp, cpPresent,
                                len, TCAP_Variant) != ITS_SUCCESS)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("TCAP_DisassemblePDU: Could not recover dialog portion.\n"));

        if ((tr != NULL && 
            (*data == TCPPT_TC_BEGIN || 
             *data == TCPPT_TC_CONTINUE)))
        {
            if (*data == TCPPT_TC_CONTINUE)
            {
                if ((TCAP_Variant >= TCAP_WHITE_BOOK) && (dp != NULL))
                {
                     __TCAP_SendAppPAbort_CCITT(tr->did, NULL,
                                                TCPPABT_ABNORMAL_DLG);
                }
                else
                {
                    __TCAP_SendAppPAbort_CCITT(tr->did, NULL,
                                               TCPABT_REASON_INCORRECT_TRANS_PORT);
                }
            }
            if ((TCAP_Variant >= TCAP_WHITE_BOOK) && (dp != NULL))
            {
                __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                             TCPPABT_ABNORMAL_DLG);
            }
            else
            {
                __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                             TCPABT_REASON_INCORRECT_TRANS_PORT);
            }
        }
        else
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Discarding message.\n"));
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_CCITT(1431, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    /* Determine QOS params */
    UpdateAddrsAndQOS(&dlg, clp, cdp, mtp3, tr, pclass);

    /* UNI, BEGIN, CONTINUE need point code information */
    InferPointCodes(did, mtp3, &dlg);

    /*
     * uni(s) do not get a transaction context, nor do invokes
     * that they carry get an invoke context.
     */
    if (pType == TCPPT_TC_UNI)
    {
        isUNI = ITS_TRUE;
    }

    if (TCAP_Variant >= TCAP_WHITE_BOOK)
    {
        int ret = UpdateDialogueState(&pType, &dlg, tr,
                                      did, &event,
                                      ies, ieCount);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Could not update Dialogue State.\n"));
            return ret;
        }
    }

    if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_DisassemblePDU: Sanity check failed.\n"));

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1432, __FILE__, __LINE__, NULL);

        return ITS_BADTCAPMESSAGE;
    }

    ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
    event.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&event.data[1], did);
    memcpy(&event.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        TCAP_DEBUG(("TCAP_DisassemblePDU: Send DLG to %04x\n", dest));

        /* Add to the peg counters - Msg Received from Remote */
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_DLG_RCVD);
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);
        UpdateDlgPeg(&dlg);

        TRANSPORT_PutEvent(dest, &event);
    }
    else
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("TCAP_DisassemblePDU: Unable to send DLG to APP.\n"));

        /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */
    }

    ITS_EVENT_TERM(&event);

    /* Step 3:Parse Components, build then and send them */

    cpData = cp;
    stop = tp + len;

    if (pType != TCPPT_TC_P_ABORT || pType != TCPPT_TC_U_ABORT)
    {
        if (cp != NULL) 
        {
            /* Get Component Portion Tag */
            cpData += TCAP_GetTag(cpData, &cpTag, stop);

            /* Get Component Portion Length */
            cpData += TCAP_GetLength(cpData, &cpLen, stop, ITS_TRUE);

            if (cpLen == 0 || (cpData[0] == 0 && cpData[1] == 0))
            {
                if (isUNI)
                {
                    TCAP_ERROR(("TCAP_DisassemblePDU: Missing mandatory component in UNI.\n"));

                    /* Send an Abort ??*/

                    return (ITS_EPROTERR);
                }
            }

            while (cpData < (cp + cpLen) && cpData[0] != 0 && cpData[1] != 0)
            {
                extCptOctets = 0;
                comp = cpData;

                /* compute Component Type Length and check Component Type tag */
                comp += TCAP_GetTag(comp, &cTag, stop);

                extCptOctets = TCAP_GetLength(comp, &cLen, stop, ITS_TRUE); 
                comp += extCptOctets;

                if ((ret = TCAP_CvtDataToCPT_CCITT(&cpt, comp, cTag, cLen)) != ITS_SUCCESS)
                {

                    TCAP_ERROR(("TCAP_DisassemblePDU: Could not recover component "
                                "portion.\n"));

                    /* 
                     * This in effect enqueues the Reject Component 
                     * to the TCAP Component Queue.
                     * An AppReject, (L_REJECT) is sent to the APP.
                     * The Enqueued component is thus appended with 
                     * the next RESULT message from the user.
                     */

                    __TCAP_SendRemoteReject_CCITT(did, &cpt,
                                                  TCPPROB_GENERAL,
                                                  (ret & 0x0F));

                    __TCAP_SendAppReject_CCITT(did, &cpt,
                                               TCPPROB_GENERAL,
                                               (ret & 0x0F),
                                               ITS_TRUE);

                     PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED); 

                    /* Incoming Component - Discarding Component - Rejection Sent by stack. */

                    /* UNIDIRECTIONAL are done at this point */
                    if (isUNI)
                    {
                        /*
                         *     TODO TCAP_CleanInvokeContext_CCITT(did);
                         */
                    }

                    /*
                     * In certain application architectures, we'll want to clean
                     * up the application context.
                     */
                    hdr.type = ITS_TCAP;
                    hdr.context.dialogue_id = did;
                    ROUTE_DeselectApplication(dest, &hdr);

                    return (ITS_SUCCESS);
                }

                numCpts ++;

                cptsLen += cLen + extCptOctets;

                if ((cptsLen + numCpts) == cpLen ||
                    (cp + cpLen) == (comp + cLen))
                {
                    cpt.last_component = 1;
                }
                
                UpdateCptPeg(&cpt);

                /* Add To Component Count for Received Component */
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_RCVD);
                 
                /* Send to CMP */
                if ((ret = CCOHandleDHAMsg_CCITT(did, &cpt)) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("TCAP_DisassemblePDU: Could not handle component.\n"));


                    /* UNIDIRECTIONAL are done at this point */
                    if (isUNI)
                    {
                        /*
                         * TODO TCAP_CleanInvokeContext_CCITT(did);
                         */
                    }
        
                    /* Incoming Component - Discarding Component - Invalid or Corrupted. */
                    TCAP_Alarm_CCITT(1439, __FILE__, __LINE__, NULL);

                    /*
                     * In certain application architectures, we'll want to clean
                     * up the application context.
                     */
                    hdr.type = ITS_TCAP;
                    hdr.context.dialogue_id = did;
                    ROUTE_DeselectApplication(dest, &hdr);

                    return ret;
                }

                cpData = comp + cLen;
            }
        }
    }

    /* UNIDIRECTIONAL are done at this point */
    if (isUNI)
    {
        /*
         * TODO TCAP_CleanInvokeContext_CCITT(did);
         */ 
    }

    /*
     * In certain application architectures, we'll want to clean
     * up the application context.
     */
    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    ROUTE_DeselectApplication(dest, &hdr);

    return (ITS_SUCCESS);
}
#endif

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      len Note that the "len" parameter is in/out
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
BuildRoutingLabel(TCAP_DLG *dlg,
                  SCCP_ADDR *cdp,
                  SCCP_ADDR *clp,
                  MTP3_HEADER *mtp3,
                  TCAP_TRANS_ENTRY *tx)
{
    ITS_UINT pc = 0;
    ITS_OCTET ssn = SCCP_SSN_NONE;
    ITS_OCTET addrInd = 0;
    ITS_UINT tmp;


    mtp3->sio = MTP3_SIO_SCCP;

    /* prefer the values in the dialog, if present */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        MTP3_RL_SET_OPC(mtp3->label, dlg->u.uni.opc);
        MTP3_RL_SET_DPC(mtp3->label, dlg->u.uni.dpc);
        break;
    case TCPPT_TC_BEGIN:
        MTP3_RL_SET_OPC(mtp3->label, dlg->u.begin.opc);
        MTP3_RL_SET_DPC(mtp3->label, dlg->u.begin.dpc);
        break;
    case TCPPT_TC_CONTINUE:
        /* flip 'em MLM: (is this right) */
        if (tx && (tx->did & TCAP_DIR_BIT))
        {
            tmp = MTP3_RL_GET_OPC_VALUE(tx->label.label);
            MTP3_RL_SET_DPC_VALUE(mtp3->label, tmp);
            tmp = MTP3_RL_GET_DPC_VALUE(tx->label.label);
            MTP3_RL_SET_OPC_VALUE(mtp3->label, tmp);
        }
        else if (tx)
        {
            tmp = MTP3_RL_GET_DPC_VALUE(tx->label.label);
            MTP3_RL_SET_DPC_VALUE(mtp3->label, tmp);
            tmp = MTP3_RL_GET_OPC_VALUE(tx->label.label);
            MTP3_RL_SET_OPC_VALUE(mtp3->label, tmp);
        }

        if (tx->state == ITS_TCAP_BEGIN_RCVD)
        {
            MTP3_RL_SET_OPC(mtp3->label, dlg->u.cont.opc);
        }
        break;

    case TCPPT_TC_END:
    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
        /* flip 'em MLM: (is this right) */
        if (tx && (tx->did & TCAP_DIR_BIT))
        {
            tmp = MTP3_RL_GET_OPC_VALUE(tx->label.label);
            MTP3_RL_SET_DPC_VALUE(mtp3->label, tmp);
            tmp = MTP3_RL_GET_DPC_VALUE(tx->label.label);
            MTP3_RL_SET_OPC_VALUE(mtp3->label, tmp);
        }
        else if (tx)
        {
            tmp = MTP3_RL_GET_DPC_VALUE(tx->label.label);
            MTP3_RL_SET_DPC_VALUE(mtp3->label, tmp);
            tmp = MTP3_RL_GET_OPC_VALUE(tx->label.label);
            MTP3_RL_SET_OPC_VALUE(mtp3->label, tmp);
        }
        break;
    }

    if (cdp)
    {
        SCCP_DecodeAddr(cdp, &addrInd, &pc, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            MTP3_RL_SET_DPC_VALUE(mtp3->label, pc);
        }
        if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            if (BEHAVIORS_GetBehavior(&CCITT_TCAP_Behaviors,
                                      TCAP_B_use_reserved_NI))
            {
                mtp3->sio |= MTP3_NIC_RESERVED;
            }
            else
            {
                mtp3->sio |= MTP3_NIC_NATIONAL;
            }
        }
        else if (BEHAVIORS_GetBehavior(&CCITT_TCAP_Behaviors,
                                       TCAP_B_use_reserved_NI))
        {
            mtp3->sio |= MTP3_NIC_SPARE;
        }
        else
        {
            mtp3->sio |= MTP3_NIC_INTERNATIONAL;
        }
    }

    pc = 0;
    ssn = SCCP_SSN_NONE;
    addrInd = 0;
    if (clp)
    {
        SCCP_DecodeAddr(clp, &addrInd, &pc, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            MTP3_RL_SET_OPC_VALUE(mtp3->label, pc);
        }
        if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            if (BEHAVIORS_GetBehavior(&CCITT_TCAP_Behaviors,
                                      TCAP_B_use_reserved_NI))
            {
                mtp3->sio |= MTP3_NIC_RESERVED;
            }
            else
            {
                mtp3->sio |= MTP3_NIC_NATIONAL;
            }
        }
        else if (BEHAVIORS_GetBehavior(&CCITT_TCAP_Behaviors,
                                       TCAP_B_use_reserved_NI))
        {
            mtp3->sio |= MTP3_NIC_SPARE;
        }
        else
        {
            mtp3->sio |= MTP3_NIC_INTERNATIONAL;
        }
    }

    /* if the user specified an override, use his NI */
    if (dlg->u.begin.qos.indicator & QOSI_NETWK_IND)
    {
        mtp3->sio &= ~MTP3_NIC_MASK;

        mtp3->sio |= dlg->u.begin.qos.networkInd;
    }

    /*
     * if we built the routing label for a Begin,
     * we need to set the routing label of the transaction context.
     */
    if (tx && dlg->ptype == TCPPT_TC_BEGIN)
    {
        tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        MTP3_RL_SET_OPC_VALUE(tx->label.label, tmp);
       
        tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_RL_SET_DPC_VALUE(tx->label.label, tmp);
    }
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      len Note that the "len" parameter is in/out
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
#if defined (PEPSY_CODEC)
static int
PEPSY_AssemblePDU(ITS_CTXT did, TCAP_DLG *dlg, ITS_SCCP_IE *ies, int *ieCount)
{
    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;
    struct type_ITU__TCAP_ComponentPortion *seq = NULL;
    struct type_ITU__TCAP_MessageType *pdu;
    int ret = ITS_SUCCESS;
    PE pe = NULL;
    int len = 0;
    char *enc = NULL;
    TCAP_TRANS_ENTRY *localTx = NULL;
    TCAP_TRANS_ENTRY *sharedTx = NULL;
    int ltid = 0, rtid = 0, rtidLen = 0;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;

    *ieCount = 0;

    TCAP_DEBUG(("PEPSY_AssemblePDU \n"));

    /*
     * Step 1. Get the components, formatting each one
     */
    MQUEUE_Lock(__TCAP_CCITT_primQueue);

    /*
     * Step 1. Get the components, formatting each one
     */
    MQUEUE_Lock(__TCAP_CCITT_primQueue);

    for (entry = LIST_TAIL(__TCAP_CCITT_primQueue);
         entry != NULL;
         entry = prev)
    {
        ITS_CTXT cdid;

        ev = (ITS_EVENT *)entry->data;
        cdid = ITS_GET_CTXT(&ev->data[1]);

        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            struct type_ITU__TCAP_ComponentPortion *tmp;

            MQUEUE_RemoveNoLock(__TCAP_CCITT_primQueue, entry);

            tmp = seq;
            if ((seq =
                (struct type_ITU__TCAP_ComponentPortion *)malloc
                    (sizeof(struct type_ITU__TCAP_ComponentPortion))) == NULL)
            {
                TCAP_ERROR(("PEPSY_AssemblePDU: no memory for comp sequence.\n"));

                /* Memory allocation failed for Component Sequence */

                ret = ITS_ENOMEM;

                continue;
            }

            if (seq)
            {
                TCAP_CPT cpt;
                /* building link list of type_ITU__TCAP_ComponentPortion
                   seq started out as null - copied to tmp before get memory
                   1st time tmp is null, 2nd time tmp is pointer to 1st component etc */
                seq->next = tmp;
                memcpy(&cpt, &ev->data[1 + sizeof(ITS_CTXT)], sizeof(TCAP_CPT));
 
                if (cpt.ptype == TCPPT_TC_INVOKE)
                {
                    switch (cpt.u.invoke.opClass)
                    {
                    case 1:
                        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_1_SENT);
                        break;
                    case 2:
                        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_2_SENT);
                        break;
                    case 3:
                        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_3_SENT);
                        break;
                    case 4:
                        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_4_SENT);
                        break;
                    default:
                        break;
                    }
                }

                switch (cpt.ptype)
                {
                        case TCPPT_TC_INVOKE:
                        case TCPPT_TC_RESULT_L:
                        case TCPPT_TC_RESULT_NL:
                        case TCPPT_TC_L_REJECT:
                        case TCPPT_TC_U_REJECT:
                        case TCPPT_TC_R_REJECT:
                        case TCPPT_TC_U_ERROR:
                        case TCPPT_TC_L_CANCEL:
                        case TCPPT_TC_U_CANCEL:
                                break;

                        default :
                                break;
                 }

                seq->ComponentPDU = TCAP_CvtCPTToComponentPDU_CCITT(&cpt);

                if (seq->ComponentPDU == NULL)
                {
                    TCAP_ERROR(("PEPSY_AssemblePDU: component encode failed.\n"));

                    /* Encode failed for Component Sequence */

                    free(seq);
                    seq = tmp;
                }
            }

            prev = entry->prev;

            /* format and add a new component portion */
            ITS_EVENT_TERM(ev);

            ITS_Free(entry->data);
            ITS_Free(entry);
        }
        else
        {
            prev = entry->prev;
        }
    }

    MQUEUE_Unlock(__TCAP_CCITT_primQueue);

    /* seq now points to a list of components, if it's valid */
    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Encode aborted.\n"));

        free_ITU__TCAP_ComponentPortion(seq);

        localTx = TCAP_FindLocalTx_CCITT(did);

        if (localTx)
        {
             TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                 tidKey, &tidKeyLen);

             TCAP_FreeLocalTx_CCITT(did);
        }

        return (ret);
    }

    /*
     * Step 2. Convert the TCAP_DLG to the pepsy structure.
     */
    /* compute the addrs, allocate transaction context */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        cdp = &dlg->u.uni.dest_addr;
        clp = &dlg->u.uni.orig_addr;
        break;

    case TCPPT_TC_BEGIN:
        cdp = &dlg->u.uni.dest_addr;
        clp = &dlg->u.uni.orig_addr;

        localTx = TCAP_FindLocalTx_CCITT(did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: LocalTx not found for did %d", did));

            free_ITU__TCAP_ComponentPortion(seq);

            return (ITS_BADTCAPMESSAGE);
        }

        ret = TCAP_PopulateLocalTx_CCITT(localTx, did, 0, 0, cdp, clp);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: LocalTx not populated for did %d",
                         did));

            free_ITU__TCAP_ComponentPortion(seq);
            TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_CCITT(did);

            return (ITS_BADTCAPMESSAGE);
        }

        /* save off the qos so we can override everywhere */
        localTx->qos = dlg->u.begin.qos;

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        break;

    case TCPPT_TC_END:
        /* set the dialogue state */

        localTx = TCAP_FindLocalTx_CCITT(did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: Missing transaction context.\n"));

            /* Unable to commit Transaction context to table */
            
            TCAP_Alarm_CCITT(1440,__FILE__,__LINE__,"Dialog-Id %X PType %X", did, dlg->ptype); 

            free_ITU__TCAP_ComponentPortion(seq);

            return (ITS_BADTCAPMESSAGE);
        }

        if (localTx->dir != DLG_INCOMING)
        {
            cdp = &localTx->daddr;
            clp = &localTx->oaddr;
        }
        else
        {
            cdp = &localTx->oaddr;
            clp = &localTx->daddr;
        }

        /*
         * By happenstance, we can use the fact that we know that
         * the QOS parameter is at the same offset in all of the
         * above members of the union.
         */
        dlg->u.end.qos = localTx->qos;

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        if (localTx->state == ITS_TCAP_ACTIVE)
        {
            if (dlg->u.end.ac_name.len != 0 ||
                dlg->u.end.user_info.len != 0)
            {
                TCAP_DEBUG(("PEPSY_AssemblePDU: User attempted to transmit "
                            "user_info or ac_name in invalid dialogue state (END)\n"));

                dlg->u.end.ac_name.len = 0;
                dlg->u.end.user_info.len = 0;
            }
        }

        break;

    case TCPPT_TC_CONTINUE:
        /* set the dialogue state */

        localTx = TCAP_FindLocalTx_CCITT(did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: Missing transaction context.\n"));

            /* Unable to commit Transaction context to table */
            
            TCAP_Alarm_CCITT(1440,__FILE__,__LINE__,"Dialog-Id %X PType %X", did, dlg->ptype);  

            free_ITU__TCAP_ComponentPortion(seq);

            return (ITS_BADTCAPMESSAGE);
        }

        if (localTx->dir != DLG_INCOMING)
        {
            cdp = &localTx->daddr;
            clp = &localTx->oaddr;
        }
        else
        {
            /*
             * Fred: If the state of the trans is Begin Received, and the clp
             * in the Continue is set, we must use the new addr.
             * How about the trans state originating addr? Yes.
             */
            if ((localTx->state == ITS_TCAP_BEGIN_RCVD) &&
                (dlg->u.cont.orig_addr.len > 0))
            {
                clp = &dlg->u.cont.orig_addr;
                localTx->daddr = dlg->u.cont.orig_addr;
            }
            else
            {
                clp = &localTx->daddr;
            }

            cdp = &localTx->oaddr;
        }

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        if (localTx->state == ITS_TCAP_ACTIVE)
        {
            if (dlg->u.cont.ac_name.len != 0 ||
                dlg->u.cont.user_info.len != 0)
            {
                TCAP_DEBUG(("PEPSY_AssemblePDU: User attempted to transmit "
                            "user_info or ac_name in invalid dialogue state (CONT)\n"));

                dlg->u.cont.ac_name.len = 0;
                dlg->u.cont.user_info.len = 0;
            }
        }

        break;
    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:
        /* set the dialogue state */

        localTx = TCAP_FindLocalTx_CCITT(did);

        if (localTx == NULL)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: Missing transaction context.\n"));

            /* Unable to commit Transaction context to table */
            TCAP_Alarm_CCITT(1440,__FILE__,__LINE__,"Dialog-Id %X PType %X", did, dlg->ptype);           
 
            free_ITU__TCAP_ComponentPortion(seq);

            return (ITS_BADTCAPMESSAGE);
        }

        if (localTx->dir != DLG_INCOMING)
        {
            cdp = &localTx->daddr;
            clp = &localTx->oaddr;
        }
        else
        {
            cdp = &localTx->oaddr;
            clp = &localTx->daddr;
        }

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        break;
    }

    /* Fix for LOCAL CANCEL for Pre Arranged End.
     * Don't Build the PDU if it has to be freed for Pre Arranged End.
     */ 
    if (dlg->u.end.termination == TCAP_END_PREARRANGED)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_PREARRANGED_END_SENT);

        PEG_Decrpeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
        PEG_Decrpeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

        TCAP_DEBUG(("PEPSY_AssemblePDU: PreArranged-End received for did"
                    "%d.\n", did));
        if (localTx)
        {
            sharedTx = TCAP_FindTransactionContext_CCITT(localTx->ltid,
                                                         tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("PEPSY_AssemblePDU: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("PEPSY_AssemblePDU: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            TCAP_FreeLocalTx_CCITT(did);
        }

        return (ITS_SUCCESS);
    }

    /*
     * Step 3. Build the PDU.
     */
    pdu = TCAP_CvtDLGToMessage_CCITT(dlg, ltid, rtid,
                                    rtidLen, TCAP_Variant);
    if (!pdu)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Could not convert dialog to package.\n"));

        if (localTx)
        {
            sharedTx = TCAP_FindTransactionContext_CCITT(localTx->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("PEPSY_AssemblePDU: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("PEPSY_AssemblePDU: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            TCAP_FreeLocalTx_CCITT(did);
        }

        free_ITU__TCAP_ComponentPortion(seq);

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_CCITT(1436, __FILE__, __LINE__, NULL);

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        return (ITS_BADTCAPMESSAGE);
    }

    /*
     * Step 3. Build the PDU.  Also, handle the dialogue state
     * machine.
     */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        pdu->un.unidirectional->components = seq;
        break;

    case TCPPT_TC_BEGIN:
        pdu->un.begin->components = seq;

        if (dlg->u.begin.ac_name.len != 0 ||
            dlg->u.begin.user_info.len != 0)
        {
            localTx->dstate = ITS_DLG_AARQ_SENT;
        }

        break;

    case TCPPT_TC_END:
        pdu->un.end->components = seq;

        if (dlg->u.end.ac_name.len != 0 ||
            dlg->u.end.user_info.len != 0)
        {
            if (localTx->dstate == ITS_DLG_AARQ_RCVD)
            {
                localTx->dstate = ITS_DLG_NONE;
            }
        }
        break;
   case TCPPT_TC_CONTINUE:
        pdu->un.contin->components = seq;

        if (dlg->u.cont.ac_name.len != 0 ||
            dlg->u.cont.user_info.len != 0)
        {
            if (localTx->dstate == ITS_DLG_AARQ_RCVD)
            {
                localTx->dstate = ITS_DLG_ACTIVE;
            }
            else if (localTx->dstate == ITS_DLG_ACTIVE)
            {
                /* do nothing */
            }
        }
        break;

    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:
        /* set the dialogue state */
        free_ITU__TCAP_ComponentPortion(seq);

        if (dlg->u.abort.ac_name.len != 0 ||
            dlg->u.abort.user_info.len != 0)
        {
            localTx->dstate = ITS_DLG_NONE;
        }
        break;
    }

    /* perform the encode */
    if (encode_ITU__TCAP_MessageType(&pe, 1, 0, NULL, (void *)pdu)
        == NOTOK)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Could not encode package.\n"));

        free_ITU__TCAP_MessageType(pdu);

        if (localTx && dlg->ptype == TCPPT_TC_BEGIN)
        {
            TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_CCITT(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_CCITT(1436, __FILE__, __LINE__, NULL);
        
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        return (ITS_BADTCAPMESSAGE);
    }

#if defined(LOCAL_DEBUG)
    print_ITU__TCAP_MessageType(pe, 1, 0, NULL, pdu);
#endif

    free_ITU__TCAP_MessageType(pdu);
    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Could not encode package.\n"));

        if (localTx && dlg->ptype == TCPPT_TC_BEGIN)
        {
            TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_CCITT(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_CCITT(1436, __FILE__, __LINE__, NULL);
        
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        return (ITS_BADTCAPMESSAGE);
    }

    if (pe)
    {
        pe_free(pe);
    }

    if (enc == NULL && len == 0)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Encode left no data.\n"));

        if (localTx && dlg->ptype == TCPPT_TC_BEGIN)
        {
            TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_CCITT(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_CCITT(1436, __FILE__, __LINE__, NULL);
        
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        return (ITS_BADTCAPMESSAGE);
    }    

    /*
     * Step 4.  Convert the PDU to SCCP form.
     */
    /* protocol class */
    ies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies[0].param_length = sizeof(SCCP_PROT_CLASS);
    ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    if (dlg->u.uni.qos.indicator & QOSI_SEQ_CTRL)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_1_SENT);
        ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_1;
    }
    else
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_0_SENT);
    }
    if (dlg->u.uni.qos.indicator & QOSI_RET_OPT)
    {
        ies[0].param_data.protocolClass.pclass |=
            SCCP_PCLASS_RET_ON_ERR;
    }

    /*
     * called/calling party addr is filled out in the conversion func
     * ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
     * ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
     */
    ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    memcpy(&ies[1].param_data.calledPartyAddr,
           cdp, sizeof(SCCP_ADDR));
    ies[1].param_length = (ITS_OCTET)ies[1].param_data.calledPartyAddr.len;

    ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    memcpy(&ies[2].param_data.callingPartyAddr,
           clp, sizeof(SCCP_ADDR));
    ies[2].param_length = (ITS_OCTET)ies[2].param_data.callingPartyAddr.len;

    /* unit data */
    ies[3].param_id = SCCP_PRM_DATA;
    ies[3].param_length = len;
    memcpy(ies[3].param_data.userData.data, enc, len);

    /* routing label */
    memset(&ies[4].param_data.routingLabel, 0, sizeof(MTP3_HEADER));

    BuildRoutingLabel(dlg,
                      &ies[1].param_data.calledPartyAddr,
                      &ies[2].param_data.callingPartyAddr,
                      &ies[4].param_data.routingLabel,
                      localTx);

    ies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[4].param_length = sizeof(MTP3_HEADER);

    if (dlg->u.uni.qos.indicator & QOSI_SEQ_CTRL)
    {
        if (dlg->u.uni.qos.indicator & QOSI_SLS_KEY)
        {
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            dlg->u.uni.qos.sls_key);
        }
        else if (dlg->ptype == TCPPT_TC_BEGIN)
        {
            /* FIXME: NOT REENTRANT */
            static ITS_OCTET sls = 0;

            localTx->qos.indicator |= QOSI_SLS_KEY;
            localTx->qos.sls_key = sls;
            dlg->u.uni.qos = localTx->qos;

            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            sls);

            sls++;
        }
        else
        {
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            0);
        }
    }
    else
    {
        /* FIXME: NOT REENTRANT */
        static ITS_OCTET sls = 0;

        MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                        sls);

        sls++;
    }

    if (dlg->u.uni.qos.indicator & QOSI_PRIORITY)
    {
        ies[4].param_data.routingLabel.sio |= dlg->u.uni.qos.priority;
    }

    *ieCount = 5;

    free(enc);

    return ret;
}
#endif

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      len Note that the "len" parameter is in/out
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 *****************************************************************************/
#if defined (TCAP_CODEC)
static int
TCAP_AssemblePDU(ITS_CTXT did, TCAP_DLG *dlg, ITS_SCCP_IE *ies, int *ieCount)
{
    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;
    int ret = ITS_SUCCESS;
    TCAP_TRANS_ENTRY *localTx = NULL;
    TCAP_TRANS_ENTRY *sharedTx = NULL;
    int ltid = 0, rtid = 0, rtidLen = 0;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;
    ITS_OCTET cp[MAX_TCAP_CPT_SIZE];
    ITS_OCTET cpList[MAX_TCAP_CPT_SIZE * MAX_NO_OF_TCAP_CPTS];
    ITS_OCTET tp[MAX_TCAP_TRANS_SIZE];

    ITS_UINT cpLen = 0, cptsLen = 0;
    ITS_UINT tpLen = 0;
    ITS_INT noCpts = 0;

    TCAP_CPT cpt;

    *ieCount = 0;

    TCAP_DEBUG(("TCAP_AssemblePDU \n"));

    /*
     * Step 1. Get the components, formatting each one
     */
    MQUEUE_Lock(__TCAP_CCITT_primQueue);

    for (entry = LIST_TAIL(__TCAP_CCITT_primQueue);
         entry != NULL;
         entry = prev)
    {
        ITS_CTXT cdid;
        
        ev = (ITS_EVENT *)entry->data;
        cdid = ITS_GET_CTXT(&ev->data[1]);
        
        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            MQUEUE_RemoveNoLock(__TCAP_CCITT_primQueue, entry);

            memcpy(&cpt, &ev->data[1 + sizeof(ITS_CTXT)], sizeof(TCAP_CPT));
            
            if (cpt.ptype == TCPPT_TC_INVOKE)
            {
                switch (cpt.u.invoke.opClass)
                {
                case 1:
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_1_SENT);
                    break;
                case 2:
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_2_SENT);
                    break;
                case 3:
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_3_SENT);
                    break;
                case 4:
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_OP_CLASS_4_SENT);
                    break;
                default:
                    break;
                }
            }

            switch (cpt.ptype)
            {
                  case TCPPT_TC_INVOKE:
                  case TCPPT_TC_RESULT_L:
                  case TCPPT_TC_RESULT_NL:
                  case TCPPT_TC_L_REJECT:
                  case TCPPT_TC_U_REJECT:
                  case TCPPT_TC_R_REJECT:
                  case TCPPT_TC_U_ERROR:
                  case TCPPT_TC_L_CANCEL:
                  case TCPPT_TC_U_CANCEL:
                      break;

                  default :
                      break;
            }

            ret = TCAP_CvtCPTToData_CCITT(&cpt, cp, &cpLen);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_AssemblePDU: component encode failed.\n"));
                ret = (!ITS_SUCCESS);
            }
            else
            {
                noCpts++;
                if (noCpts > 1)
                {
                    memmove(&cpList[cpLen], cpList, cptsLen);
                }
                memcpy(cpList, cp, cpLen);
                cptsLen += (cpLen);
            }

            prev = entry->prev;

            /* format and add a new component portion */
            ITS_EVENT_TERM(ev);

            ITS_Free(entry->data);
            ITS_Free(entry);
        }
        else
        {
            prev = entry->prev;
        }
    }

    MQUEUE_Unlock(__TCAP_CCITT_primQueue);

    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Encode aborted.\n"));

        localTx = TCAP_FindLocalTx_CCITT(did);
       
        if (localTx)
        {
             TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                 tidKey, &tidKeyLen);
   
             TCAP_FreeLocalTx_CCITT(did);
        }


        return (ret);
    }

    /*
     * Step 2. Convert the TCAP_DLG.
     */
    /* compute the addrs, allocate transaction context */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        cdp = &dlg->u.uni.dest_addr;
        clp = &dlg->u.uni.orig_addr;
        break;

    case TCPPT_TC_BEGIN:
        cdp = &dlg->u.uni.dest_addr;
        clp = &dlg->u.uni.orig_addr;

        localTx = TCAP_FindLocalTx_CCITT(did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: LocalTx not found for did %d", did));

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            return (ITS_BADTCAPMESSAGE);
        }

        ret = TCAP_PopulateLocalTx_CCITT(localTx, did, 0, 0, cdp, clp);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: LocalTx not populated for did %d", 
                         did));

            TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_CCITT(did);


            return (ITS_BADTCAPMESSAGE);
        }

        /* save off the qos so we can override everywhere */
        localTx->qos = dlg->u.begin.qos;

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        break;

    case TCPPT_TC_END:
        /* set the dialogue state */

        localTx = TCAP_FindLocalTx_CCITT(did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: Missing transaction context.\n"));

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            /* Unable to commit Transaction context to table */
            TCAP_Alarm_CCITT(1440,__FILE__,__LINE__,"Dialog-Id %X PType %X", did, dlg->ptype);            
 
            return (ITS_BADTCAPMESSAGE);
        }
        
        if (localTx->dir != DLG_INCOMING)
        {
            cdp = &localTx->daddr;
            clp = &localTx->oaddr;
        }
        else
        {
            cdp = &localTx->oaddr;
            clp = &localTx->daddr;
        }

        /*
         * By happenstance, we can use the fact that we know that
         * the QOS parameter is at the same offset in all of the
         * above members of the union.
         */
        dlg->u.end.qos = localTx->qos;

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        if (localTx->state == ITS_TCAP_ACTIVE)
        {
            if (dlg->u.end.ac_name.len != 0 ||
                dlg->u.end.user_info.len != 0)
            {
                TCAP_DEBUG(("TCAP_AssemblePDU: User attempted to transmit "
                            "user_info or ac_name in invalid dialogue state (END)\n"));

                dlg->u.end.ac_name.len = 0;
                dlg->u.end.user_info.len = 0;
            }
        }

        break;

    case TCPPT_TC_CONTINUE:
        /* set the dialogue state */

        localTx = TCAP_FindLocalTx_CCITT(did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: Missing transaction context.\n"));

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            /* Unable to commit Transaction context to table */
            TCAP_Alarm_CCITT(1440,__FILE__,__LINE__,"Dialog-Id %X PType %X", did, dlg->ptype);            
 
            return (ITS_BADTCAPMESSAGE);
        }

        if (localTx->dir != DLG_INCOMING)
        {
            cdp = &localTx->daddr;
            clp = &localTx->oaddr;
        }
        else
        {
            /* 
             * Fred: If the state of the trans is Begin Received, and the clp
             * in the Continue is set, we must use the new addr.
             * How about the trans state originating addr? Yes.
             */
            if ((localTx->state == ITS_TCAP_BEGIN_RCVD) &&
                (dlg->u.cont.orig_addr.len > 0))
            {
                clp = &dlg->u.cont.orig_addr;
                localTx->daddr = dlg->u.cont.orig_addr;
            }
            else
            {
                clp = &localTx->daddr;
            }

            cdp = &localTx->oaddr;
        }

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        if (localTx->state == ITS_TCAP_ACTIVE)
        {
            if (dlg->u.cont.ac_name.len != 0 ||
                dlg->u.cont.user_info.len != 0)
            {
                TCAP_DEBUG(("TCAP_AssemblePDU: User attempted to transmit "
                            "user_info or ac_name in invalid dialogue state (CONT)\n"));

                dlg->u.cont.ac_name.len = 0;
                dlg->u.cont.user_info.len = 0;
            }
        }

        break;

    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:
        /* set the dialogue state */

        localTx = TCAP_FindLocalTx_CCITT(did);

        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: Missing transaction context.\n"));

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            TCAP_Alarm_CCITT(1440,__FILE__,__LINE__,"Dialog-Id %X PType %X", did, dlg->ptype);
            return (ITS_BADTCAPMESSAGE);
        }

        if (localTx->dir != DLG_INCOMING)
        {
            cdp = &localTx->daddr;
            clp = &localTx->oaddr;
        }
        else
        {
            cdp = &localTx->oaddr;
            clp = &localTx->daddr;
        }

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        rtidLen = localTx->rtidLen;

        break;
    }

    /* Fix for LOCAL CANCEL for Pre arranged End.
     * Don't build the message for Pre Arranged End, if it has to be freed for Pre arranged End.
     */
    if (dlg->u.end.termination == TCAP_END_PREARRANGED)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_PREARRANGED_END_SENT);
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
        PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
        PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
  
        TCAP_DEBUG(("TCAP_AssemblePDU: PreArranged-End received for did"
                    "%d.\n", did));

        if (localTx)
        {
            sharedTx = TCAP_FindTransactionContext_CCITT(localTx->ltid,
                                                         tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCAP_AssemblePDU: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCAP_AssemblePDU: Freeing DSM Tx for did"
                            "%d.\n", did));
  
                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }
  
            TCAP_FreeLocalTx_CCITT(did);
        }
        return (ITS_SUCCESS);
    }
    
    /*
     * Step 3. Build the message. 
     */
    if (TCAP_CvtDLGToData_CCITT(dlg, tp, &tpLen, cpList, cptsLen,
                                ltid, rtid, rtidLen, TCAP_Variant) != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Could not convert dialog to package.\n"));

        if (localTx)
        {
            sharedTx = TCAP_FindTransactionContext_CCITT(localTx->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCAP_AssemblePDU: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCAP_AssemblePDU: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }
 
            TCAP_FreeLocalTx_CCITT(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_CCITT(1436, __FILE__, __LINE__, NULL);
        
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
        PEG_DecrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE); 

        return (ITS_BADTCAPMESSAGE);
    }

    /*
     * Step 3. handle the dialogue state machine.
     */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        break;

    case TCPPT_TC_BEGIN:

        if (dlg->u.begin.ac_name.len != 0 ||
            dlg->u.begin.user_info.len != 0)
        {
            localTx->dstate = ITS_DLG_AARQ_SENT;
        }

        break;

    case TCPPT_TC_END:

        if (dlg->u.end.ac_name.len != 0 ||
            dlg->u.end.user_info.len != 0)
        {
            if (localTx->dstate == ITS_DLG_AARQ_RCVD)
            {
                localTx->dstate = ITS_DLG_NONE;
            }
        }
        break;

    case TCPPT_TC_CONTINUE:

        if (dlg->u.cont.ac_name.len != 0 ||
            dlg->u.cont.user_info.len != 0)
        {
            if (localTx->dstate == ITS_DLG_AARQ_RCVD)
            {
                localTx->dstate = ITS_DLG_ACTIVE;
            }
            else if (localTx->dstate == ITS_DLG_ACTIVE)
            {
                /* do nothing */
            }
        }
        break;

    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:

        if (dlg->u.abort.ac_name.len != 0 ||
            dlg->u.abort.user_info.len != 0)
        {
            localTx->dstate = ITS_DLG_NONE;
        }
        break;
    }

    if (tp == NULL && tpLen == 0)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Encode left no data.\n"));

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED); 

        if (localTx && dlg->ptype == TCPPT_TC_BEGIN)
        {
            TCAP_FindAndFreeTransactionContext_CCITT(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_CCITT(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_CCITT(1436, __FILE__, __LINE__, NULL);
                

        return (ITS_BADTCAPMESSAGE);
    }

    /*
     * Step 4.  Convert the PDU to SCCP form.
     */
    /* protocol class */
    ies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies[0].param_length = sizeof(SCCP_PROT_CLASS);
    ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    if (dlg->u.uni.qos.indicator & QOSI_SEQ_CTRL)
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_1_SENT);
        ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_1;
    }
    else
    {
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_0_SENT);
    }

    if (dlg->u.uni.qos.indicator & QOSI_RET_OPT)
    {
        ies[0].param_data.protocolClass.pclass |=
            SCCP_PCLASS_RET_ON_ERR;
    }

    /*
     * called/calling party addr is filled out in the conversion func
     * ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
     * ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
     */
    ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    memcpy(&ies[1].param_data.calledPartyAddr,
           cdp, sizeof(SCCP_ADDR));
    ies[1].param_length = (ITS_OCTET)ies[1].param_data.calledPartyAddr.len;

    ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    memcpy(&ies[2].param_data.callingPartyAddr,
           clp, sizeof(SCCP_ADDR));
    ies[2].param_length = (ITS_OCTET)ies[2].param_data.callingPartyAddr.len;

    /* unit data */
    if (tpLen > SCCP_MAX_DATA)
    {
        ies[3].param_id = SCCP_PRM_LONG_DATA;
        ies[3].param_length = 0;
        ies[3].param_data.longData.len = tpLen;
        memcpy(ies[3].param_data.longData.data, tp, tpLen);

        ies[5].param_id = SCCP_PRM_HOP_COUNTER;
        ies[5].param_length = 1;
        ies[5].param_data.hopCount.count = 0x01;

        *ieCount = 6;
    }
    else
    {
        ies[3].param_id = SCCP_PRM_DATA;
        ies[3].param_length = tpLen;
        memcpy(ies[3].param_data.userData.data, tp, tpLen);

        *ieCount = 5;
    }

    if (TRACE_IsLevelOn(TCAP_CCITT_TraceData, TCAP_TRACE_EVENT))
    {
        ITS_EVENT tcapEvent;
        ITS_INT output = 0;

        tcapEvent.src = ITS_APP_PROTOCOL_1;
        tcapEvent.data = (ITS_OCTET*)malloc(sizeof(ITS_OCTET)*tpLen);
        tcapEvent.len = tpLen;
        memcpy(tcapEvent.data, tp, tpLen);

        
        if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
            TCAP_TRACE_EVENT,
            0))
        {
            output += 1;
        }
        if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
            TCAP_TRACE_EVENT,
            1))
        {
            output += 2;
        }

        CTF_TraceEvent(tcapEvent.src, ITS_TCAP_CCITT_SRC,
            output, &tcapEvent); 
        free(tcapEvent.data);
        memset(&tcapEvent, 0, sizeof(ITS_EVENT));
    }

    /* routing label */
    memset(&ies[4].param_data.routingLabel, 0, sizeof(MTP3_HEADER));

    BuildRoutingLabel(dlg,
                      &ies[1].param_data.calledPartyAddr,
                      &ies[2].param_data.callingPartyAddr,
                      &ies[4].param_data.routingLabel,
                      localTx);

    ies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[4].param_length = sizeof(MTP3_HEADER);

    if (dlg->u.uni.qos.indicator & QOSI_SEQ_CTRL)
    {
        if (dlg->u.uni.qos.indicator & QOSI_SLS_KEY)
        {
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            dlg->u.uni.qos.sls_key);
        }
        else if (dlg->ptype == TCPPT_TC_BEGIN)
        {
            /* FIXME: NOT REENTRANT */
            static ITS_OCTET sls = 0;

            localTx->qos.indicator |= QOSI_SLS_KEY;
            localTx->qos.sls_key = sls;
            dlg->u.uni.qos = localTx->qos;

            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            sls);

            sls++;
        }
        else
        {
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            0);
        }
    }
    else
    {
        /* FIXME: NOT REENTRANT */
        static ITS_OCTET sls = 0;

        MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                        sls);

        sls++;
    }

    if (dlg->u.uni.qos.indicator & QOSI_PRIORITY)
    {
        ies[4].param_data.routingLabel.sio |= dlg->u.uni.qos.priority;
    }
            
    return ret;
}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
DHAHandleCCOMsg_CCITT(ITS_EVENT *event)
{
    int ret;

    TCAP_DEBUG(("DHAHandleCCOMsg_CCITT:\n"));

    ret = MQUEUE_Enqueue(__TCAP_CCITT_primQueue, event, sizeof(ITS_EVENT));
    event->data = NULL;
    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
DHAHandleCCOCancelMsg_CCITT(ITS_CTXT did, CPT_INV_ID *invId)
{
    QUEUE_Msg *entry, *tmp;
    ITS_EVENT *ev;
    TCAP_CPT cpt;

    /*
     * Step 1. Get the components, formatting each one
     */
    MQUEUE_Lock(__TCAP_CCITT_primQueue);

    for (entry = LIST_HEAD(__TCAP_CCITT_primQueue);
         entry != NULL;
         entry = tmp)
    {
        ITS_CTXT cdid;
        
        ev = (ITS_EVENT *)entry->data;
        cdid = ITS_GET_CTXT(&ev->data[1]);
        
        tmp = entry->next;

        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            memcpy(&cpt, &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                   sizeof(TCAP_CPT));

            if (cpt.ptype == TCPPT_TC_INVOKE &&
                invId->len == cpt.u.invoke.invoke_id.len &&
                memcmp(invId->data, cpt.u.invoke.invoke_id.data,
                       invId->len) == 0)
            {
                MQUEUE_RemoveNoLock(__TCAP_CCITT_primQueue, entry);

                /* format and add a new component portion */
                ITS_Free(entry->data);
                ITS_Free(entry);
            }
        }
    }

    MQUEUE_Unlock(__TCAP_CCITT_primQueue);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Reset the Timer of an Invoked operation.
 *      ITU White Book 97 variant only.
 *
 *  Input Parameters:
 *      invoke: pointer to the context of the invoked operation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS: if the operation is successful.
 ****************************************************************************/
int
DHAHandleCCOResetTimerMsg_CCITT(TCAP_INVOKE_ENTRY *invoke)
{
    if (invoke == NULL)
    {
        return (ITS_ENULLPTR);
    }

    if (invoke->timeout > 0)
    {

        /* Cancelling the current Timer before restarting it. */
        TIMERS_CancelSharedTimer(invoke->timer);

        if ((invoke->timer =
                TIMERS_StartSharedTimer(ITS_TCAP_SRC, invoke->timeout, 
                                        invoke,
                                        sizeof(TCAP_INVOKE_ENTRY)))
            == 0)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
DHAHandleDIDClean_CCITT(ITS_CTXT did)
{
    LIST_Entry *entry, *next;

    MQUEUE_Lock(__TCAP_CCITT_primQueue);

    for (entry = LIST_HEAD(__TCAP_CCITT_primQueue);
         entry != NULL;
         entry = next)
    {
        ITS_EVENT *ev;
        ITS_CTXT cdid;
        
        next = entry->next;

        ev = (ITS_EVENT *)entry->data;
        cdid = ITS_GET_CTXT(&ev->data[1]);
        
        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            MQUEUE_RemoveNoLock(__TCAP_CCITT_primQueue, entry);

            ITS_Free(entry->data);
            ITS_Free(entry);
        }
    }

    MQUEUE_Unlock(__TCAP_CCITT_primQueue);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
DHAHandleAPPMsg_CCITT(ITS_EVENT *event)
{
    ITS_CTXT did;
    TCAP_DLG dlg;
    ITS_SCCP_IE ies[8];
    int ieCount;
    
    TCAP_DEBUG(("DHAHandleAPPMsg_CCITT:\n"));

    if (event->data[0] != ITS_TCAP_DLG)
    {
        TCAP_ERROR(("DHAHandleAPPMsg_CCITT:  Event is not user dialog: %02x\n",
                    event->data[0]));
        
        /* Received Unrecognized or Invalid Event. */

        return (ITS_SUCCESS);
    }

    did = ITS_GET_CTXT(&event->data[1]);
    memcpy(&dlg, &event->data[1 + sizeof(ITS_CTXT)], sizeof(TCAP_DLG));

    /* assemble the message, send it to TRP */    
    if (AssemblePDU(did, &dlg, ies, &ieCount) == ITS_SUCCESS)
    {
        /* The following clause means !(prearranged end) */

        if (dlg.ptype != TCPPT_TC_END ||
            dlg.u.end.termination != TCAP_END_PREARRANGED)
        {
            return TCOHandleCSLMsg_CCITT(did, ies, ieCount);
        }
        else
        {
            return (ITS_SUCCESS);
        }
    }
    else
    {
        TCAP_ERROR(("DHAHandleAPPMsg_CCITT: Failed to Assemble PDU: did %04x\n",
                    did));

        return (ITS_SUCCESS);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
DHAHandleTCOMsg_CCITT(ITS_SCCP_IE *ies, int ieCount, TCAP_TRANS_ENTRY *tr)
{
    /*
     * disassemble the message, send components to CMP, dlgs to user.
     * An error from this function indicates that a reject should go
     * to SCCP
     */
    TCAP_DEBUG(("DHAHandleTCOMsg.\n"));

    return DisassemblePDU(ies, ieCount, tr);
}
