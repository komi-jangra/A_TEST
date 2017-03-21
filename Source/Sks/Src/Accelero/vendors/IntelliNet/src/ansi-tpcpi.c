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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ansi-tpcpi.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/30 11:36:13  adutta
 * LOG: XUDT implementation in ANSI
 * LOG:
 * LOG: Revision 9.3  2005/05/05 06:47:33  adutta
 * LOG: Fix for #1566
 * LOG:
 * LOG: Revision 9.2  2005/04/08 07:30:25  adutta
 * LOG: Fix for Bug#529
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.29  2005/03/21 13:53:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.7  2005/02/22 06:46:55  sbabu
 * LOG: TCAP OAM Bug Fix
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.6  2005/02/21 14:48:17  sbabu
 * LOG: TCAP OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.5  2005/02/21 11:37:33  mmanikandan
 * LOG: output is modified for CTF.
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.4  2005/02/03 10:20:17  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.3  2005/01/31 09:32:45  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.2  2005/01/04 13:43:56  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.13.2.19.2.1.12.1  2004/12/31 09:23:38  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.13.2.19.2.1  2004/02/16 09:18:57  mmanikandan
 * LOG: Performance Improvement.
 * LOG:
 * LOG: Revision 7.13.2.19  2003/11/25 06:37:44  ssingh
 * LOG: Bug #679, Unknown Message received from Network with
 * LOG: RTID not derivable is discarded. Changed function SendTransAbort.
 * LOG:
 * LOG: Revision 7.13.2.18  2003/08/08 05:39:29  yranade
 * LOG: Get the SendReject fix right.
 * LOG:
 * LOG: Revision 7.13.2.17  2003/08/07 14:47:28  yranade
 * LOG: Fix for issue seen on tandem, in SendReject function.
 * LOG:
 * LOG: Revision 7.13.2.16  2003/07/25 10:10:07  yranade
 * LOG: For cpt related errors, just enqueue the reject cpt and
 * LOG: send an indication to the user rather than ending the trans.
 * LOG: with a RESP/Reject. T1.114.4-14.
 * LOG:
 * LOG: Revision 7.13.2.15  2003/05/20 03:50:22  vjatti
 * LOG: Fix typo.
 * LOG:
 * LOG: Revision 7.13.2.14  2003/04/09 08:55:37  yranade
 * LOG: ITS_CTXT related updates.
 * LOG:
 * LOG: Revision 7.13.2.13  2003/04/08 15:09:57  yranade
 * LOG: Coding standards.
 * LOG:
 * LOG: Revision 7.13.2.12  2003/04/08 13:51:42  vjatti
 * LOG: code cleanup for PEPSY & TCAP codecs.
 * LOG: removal of warnings. warning- unused variable.
 * LOG:
 * LOG: Revision 7.13.2.11  2003/04/07 09:18:11  vjatti
 * LOG: Fix for Bug 220 &
 * LOG: Added the Function ValidateDialogueForAppCtxtAndProtVer(),
 * LOG: to validate thd dialogue, & to send P-Abort for messages after
 * LOG: 2 and backward conversation containing AC/PV.
 * LOG:
 * LOG: Revision 7.13.2.10  2003/04/01 10:53:15  vjatti
 * LOG: Fix for sending Decode Rejct on problems in component portion.
 * LOG: Code changes to Decode Abort/Decode Rejct & changed the did format to ITS_CTXT.
 * LOG:
 * LOG: Revision 7.13.2.9  2003/03/24 10:27:13  vjatti
 * LOG: Code changes for passing correct cause values to Decode Abort/Reject.
 * LOG:
 * LOG: Revision 7.13.2.8  2003/03/24 09:21:04  vjatti
 * LOG: Code changes in FindParts return value for sending the exact causes to Abort/Reject.
 * LOG:
 * LOG: Revision 7.13.2.7  2003/03/20 10:33:56  vjatti
 * LOG: Fix for Bug 239.
 * LOG:
 * LOG: Revision 7.13.2.6  2003/03/13 12:42:34  vjatti
 * LOG: Code enhancement for Extended len support for components.
 * LOG:
 * LOG: Revision 7.13.2.5  2003/03/11 08:39:32  vjatti
 * LOG: Fix for Decode Reject to peer.
 * LOG:
 * LOG: Revision 7.13.2.4  2003/03/04 12:57:21  yranade
 * LOG: Get the missing reorder/list traversal bug fix right.
 * LOG:
 * LOG: Revision 7.13.2.3  2003/03/03 22:22:13  mmiers
 * LOG: Missing reorder/list traversal bug fix.
 * LOG:
 * LOG: Revision 7.13.2.2  2003/02/28 04:42:17  vjatti
 * LOG: Code clean up and coding standards
 * LOG:
 * LOG: Revision 7.13.2.1  2003/02/26 06:55:20  vjatti
 * LOG: Fix for LOCAL CANCEL. for a Pre Arranged End free the tx without building the PDU
 * LOG:
 * LOG: Revision 7.13  2003/02/13 13:04:28  yranade
 * LOG: Cleanup.
 * LOG:
 * LOG: Revision 7.12  2003/02/07 15:18:53  yranade
 * LOG: Removed warnings shown by gcc -Wall.
 * LOG:
 * LOG: Revision 7.11  2003/02/07 11:46:21  tsanthosh
 * LOG: Modified to add some tcap alarms and tcap pegs.
 * LOG:
 * LOG: Revision 7.10  2003/02/06 10:14:20  vjatti
 * LOG: PR 6.2 Fixes propagated
 * LOG:
 * LOG: Revision 7.9  2003/02/05 14:22:09  yranade
 * LOG: Renamed FindParts to TCAP_FindParts, since it's in Global Scope.
 * LOG: Removed warnings seen on windows.
 * LOG:
 * LOG: Revision 7.8  2003/02/04 16:37:45  mmiers
 * LOG: Error if codec not defined.
 * LOG:
 * LOG: Revision 7.7  2003/02/04 07:28:14  vjatti
 * LOG: Manual TCAP Codec Integration.
 * LOG:
 * LOG: Revision 7.6  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.5  2002/11/14 22:27:20  omayor
 * LOG: Removed compilation warnings shown by gcc3.2
 * LOG:
 * LOG: Revision 7.4  2002/11/05 22:51:11  omayor
 * LOG: Coding standards!
 * LOG:
 * LOG: Revision 7.3  2002/10/15 19:40:34  omayor
 * LOG: Use correct includes
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:22:39  omayor
 * LOG: Minimization of DSM calls
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.14  2002/08/26 18:18:48  mmiers
 * LOG: Add dest
 * LOG:
 * LOG: Revision 6.13  2002/08/26 16:54:13  mmiers
 * LOG: Add deselector hook.
 * LOG:
 * LOG: Revision 6.12  2002/08/05 14:58:00  labuser
 * LOG: Block the memory leak per message. (clin)
 * LOG:
 * LOG: Revision 6.11  2002/07/29 17:57:35  ngoel
 * LOG: increment total message peg
 * LOG:
 * LOG: Revision 6.10  2002/07/16 16:22:40  labuser
 * LOG: Get the right MTP3->sio for cdp and clp. (clin)
 * LOG:
 * LOG: Revision 6.9  2002/07/09 14:28:36  omayor
 * LOG: ANSI-96 changes after testing in PR5 ported to current. Now to be tested.
 * LOG:
 * LOG: Revision 6.8  2002/06/14 19:29:02  mmiers
 * LOG: Change signature
 * LOG:
 * LOG: Revision 6.7  2002/06/12 21:32:37  mmiers
 * LOG: Add ANSI abort processing.
 * LOG:
 * LOG: Revision 6.6  2002/05/22 18:37:39  mmiers
 * LOG: Add newline at end of file.  Fix parenthesis problem.
 * LOG:
 * LOG: Revision 6.5  2002/05/08 15:49:18  mmiers
 * LOG: Add user setting of NI
 * LOG:
 * LOG: Revision 6.4  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 23:08:26  mmiers
 * LOG: TCAP behaviors.
 * LOG:
 * LOG: Revision 6.2  2002/03/01 23:12:06  mmiers
 * LOG: Start the DSM/pegs/alarms merge.  ANSI-TCAP done, 3 left.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.11  2002/02/13 00:07:58  mmiers
 * LOG: Get it right this time.
 * LOG:
 * LOG: Revision 5.10  2002/02/13 00:00:00  mmiers
 * LOG: Walk prim list in tail to head order to fix reordering bug.
 * LOG:
 * LOG: Revision 5.9  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.8  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.7  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
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
 * LOG: Revision 3.10  2001/03/14 01:49:49  mmiers
 * LOG: Cleanup.
 * LOG:
 * LOG: Revision 3.9  2001/02/06 17:58:42  mmiers
 * LOG: About 90% thread safe.  SCCP connection oriented isn't, neither
 * LOG: are simultaneous messages within a TCAP transaction.
 * LOG:
 * LOG: Revision 3.8  2001/01/18 23:51:50  mmiers
 * LOG: Replace list allocator
 * LOG:
 * LOG: Revision 3.7  2001/01/03 17:30:34  mmiers
 * LOG: Don't check tr (pointer may be uninitialized).
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
 * LOG: Revision 3.3  2000/08/24 23:07:23  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 17:28:17  mmiers
 * LOG: Ancient memory leak plugged.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/06/28 23:32:46  mmiers
 * LOG:
 * LOG:
 * LOG: Add some traces.
 * LOG:
 * LOG: Revision 2.3  2000/05/26 22:28:14  mmiers
 * LOG:
 * LOG:
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 2.2  2000/04/17 21:36:32  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes to ANSI TCAP.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 18:23:33  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.22  1999/10/05 19:01:02  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.21  1999/09/10 23:10:23  mmiers
 * LOG:
 * LOG:
 * LOG: Split out white book and blue book variant behavior.
 * LOG:
 * LOG: Revision 1.20  1999/09/07 21:02:30  ite
 * LOG:
 * LOG:
 * LOG: Change interface for TCAP such that the dialogue id is not memcpy'd.
 * LOG: This fixes a reject bug.
 * LOG:
 * LOG: Revision 1.19  1999/08/27 16:50:11  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.18  1999/08/26 23:44:57  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.17  1999/08/26 15:24:12  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.16  1999/08/26 02:21:56  mmiers
 * LOG:
 * LOG:
 * LOG: Automate QOS reflection.  Fix UNI handling (newly added code would have
 * LOG: rejected UNIs).  Try to be clearer about the position of the routing
 * LOG: label.  There is still most likely a hole (or more specifically, to
 * LOG: much override) when building a routing label after the user has
 * LOG: overriden certain fields.
 * LOG:
 * LOG: Revision 1.15  1999/08/25 22:40:52  mmiers
 * LOG:
 * LOG:
 * LOG: Sanity checks.
 * LOG:
 * LOG: Revision 1.14  1999/08/20 19:32:56  mmiers
 * LOG:
 * LOG:
 * LOG: Typo in code copied from ITU version.
 * LOG:
 * LOG: Revision 1.13  1999/08/20 17:10:13  ite
 * LOG:
 * LOG:
 * LOG: Dialogue encoding bugs (RETOPT, SLS, etc.)
 * LOG:
 * LOG: Revision 1.12  1999/08/19 22:44:05  mmiers
 * LOG:
 * LOG:
 * LOG: Fix PAbort generation problem.
 * LOG:
 * LOG: Revision 1.11  1999/08/05 17:04:50  mmiers
 * LOG:
 * LOG:
 * LOG: Provision for dumping PDUs.
 * LOG:
 * LOG: Revision 1.10  1999/06/18 22:15:40  mmiers
 * LOG:
 * LOG:
 * LOG: Remove extraneous deletes
 * LOG:
 * LOG: Revision 1.9  1999/06/15 22:41:17  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for codec function signatures.
 * LOG:
 * LOG: Revision 1.8  1999/06/15 22:32:06  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.7  1999/05/27 21:46:07  mmiers
 * LOG:
 * LOG:
 * LOG: Adjust the TID management for sanity.
 * LOG:
 * LOG: Revision 1.6  1999/05/27 15:52:46  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.5  1999/05/24 20:31:19  mmiers
 * LOG:
 * LOG:
 * LOG: Codecs have moved into shared library.
 * LOG:
 * LOG: Revision 1.4  1999/05/17 23:05:36  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.3  1999/04/05 20:51:53  mmiers
 * LOG:
 * LOG:
 * LOG: Make sure last_component is set correctly.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:50  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 20:55:06  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.24  1999/03/17 18:40:00  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.23  1999/02/26 04:10:23  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.22  1999/02/17 20:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Get ITU conversion to compile.
 * LOG:
 * LOG: Revision 1.21  1999/01/27 17:59:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add support for separate specifictation of OPC/DPC in TCAP.
 * LOG:
 * LOG: Revision 1.20  1998/12/11 21:44:16  rsonak
 * LOG: Fix bug building MTP3 header.
 * LOG:
 * LOG: Revision 1.19  1998/11/02 17:09:33  mmiers
 * LOG: Fix initialization of routing label that is sent to SCCP.
 * LOG:
 * LOG: Revision 1.18  1998/10/19 22:08:36  mmiers
 * LOG: Add QOS management for TCAP.
 * LOG:
 * LOG: Revision 1.17  1998/10/15 01:19:26  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.16  1998/10/02 16:43:04  jrao
 * LOG: Remove assert on assemble PDU.
 * LOG:
 * LOG: Revision 1.15  1998/10/02 14:40:19  mmiers
 * LOG: Cleanup after mods.
 * LOG:
 * LOG: Revision 1.14  1998/10/02 04:05:46  mmiers
 * LOG: Improve TCAP component handling.  The only thing that needs verification
 * LOG: is reject handling.
 * LOG:
 * LOG: Revision 1.13  1998/09/30 21:54:41  jrao
 * LOG: Make UNI work with invokes.  Basically, we don't allocate an invoke
 * LOG: context for INVOKE's received in a UNI.  Need to verify this with
 * LOG: T1.114.
 * LOG:
 * LOG: Revision 1.12  1998/09/21 17:20:11  mmiers
 * LOG: Add tracing into everything.
 * LOG:
 * LOG: Revision 1.11  1998/09/18 21:54:35  whu
 * LOG: Fix for handling pdu size > 127
 * LOG:
 * LOG: Revision 1.10  1998/09/17 19:25:27  whu
 * LOG: Reject fix.
 * LOG:
 * LOG: Revision 1.9  1998/07/08 20:01:08  mmiers
 * LOG: More work on TCAP rejects.
 * LOG:
 * LOG: Revision 1.8  1998/07/08 16:46:01  mmiers
 * LOG: Restructure the reject method a little differently.
 * LOG:
 * LOG: Revision 1.7  1998/07/08 16:39:15  mmiers
 * LOG: Start thinking about reject cases.  Group into a common function.
 * LOG:
 * LOG: Revision 1.6  1998/07/01 23:34:20  mmiers
 * LOG: Finish coding INVOKE timers.  Now to debug.
 * LOG:
 * LOG: Revision 1.5  1998/06/29 19:27:22  mmiers
 * LOG: Convert TCAP to use SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/06/25 00:22:58  ahanda
 * LOG: Make sure the source for an event is defined (ITS_TCAP).
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:30  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 23:38:44  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:33  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.20  1998/06/16 21:52:10  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.19  1998/06/16 00:00:22  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.18  1998/05/31 22:20:13  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.17  1998/05/20 20:15:30  mmiers
 * LOG: Get test8 (process framework) compiled and linked.  Not
 * LOG: all code is linked in (no sending yet, which will cause more
 * LOG: undefined externals).
 * LOG:
 * LOG: Revision 1.16  1998/05/19 18:04:51  mmiers
 * LOG: More on TCAP++.
 * LOG:
 * LOG: Revision 1.15  1998/05/05 20:24:10  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.14  1998/04/29 22:45:03  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.
 * LOG:
 * LOG: Revision 1.13  1998/04/29 21:10:19  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.12  1998/04/29 00:23:17  mmiers
 * LOG: Start putting in context functions.  Should be starting debug
 * LOG: tommorrow.
 * LOG:
 * LOG: Revision 1.11  1998/04/27 20:00:24  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.10  1998/04/23 23:53:53  mmiers
 * LOG: More work on TCAP.  Down to about 30 fixme's.
 * LOG:
 * LOG: Revision 1.9  1998/04/23 17:04:03  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.8  1998/04/23 02:33:02  mmiers
 * LOG: More work on our TCAP implementation.  Made this single threaded,
 * LOG: multiple threads didn't buy anything, but did cost a *bunch* of
 * LOG: unnecessary hops between threads.  We're down to 3/2 hops in/out
 * LOG: of a process.
 * LOG:
 * LOG: Revision 1.7  1998/04/23 00:11:31  mmiers
 * LOG: Working on TCAP now.
 * LOG:
 * LOG: Revision 1.6  1998/04/16 16:40:04  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.5  1998/03/20 02:47:46  mmiers
 * LOG: More work on TCAP.  I think I've got the way for TPCPI to talk to TRP, and
 * LOG: TRP to talk to SCCP.  Need to translate to/from SCCP_IE sooner than I thought.
 * LOG: May need to have a non-standard way to talk to/from TPCPI to TRP (dialogue id,
 * LOG: pType).
 * LOG:
 * LOG: Revision 1.4  1998/03/19 16:34:39  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/03/13 04:46:45  mmiers
 * LOG: For the most part, TCAP modifications.  Quite a few of these files are false
 * LOG: positive due to timestamps.
 * LOG:
 * LOG: Revision 1.2  1998/03/13 04:15:07  mmiers
 * LOG: More on the TCAP implementation.  By the end of the weekend, I expect a
 * LOG: preliminary implementation of ANSI TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:05:36  mmiers
 * LOG: TCAP implementation for ANSI.  Not quite there yet.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#undef CCITT
#undef PRC
#undef TTC
#undef ANSI
#define ANSI

#include <its.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_dsm.h>
#include <its_ctf.h>

#ident "$Id: ansi-tpcpi.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#include <ansi/tcap.h>

#include "sccp_intern.h"
#include "tcap_intern.h"

#if defined(SPLIT_STACK)
#if defined(USE_TTC_SCCP)
#define WHICH_STACK     (ITS_HANDLE)ISS7_TTC_Stack
#elif defined(USE_PRC_SCCP)
#define WHICH_STACK     (ITS_HANDLE)ISS7_PRC_Stack
#else
#define WHICH_STACK     (ITS_HANDLE)ISS7_CCITT_Stack
#endif
#else
#define WHICH_STACK     (ITS_HANDLE)ISS7_ANSI_Stack
#endif

#define TCPPN_SEQUENCE_TAG  (0x30U) 

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

MLIST_Manager *__TCAP_ANSI_primQueue;

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
__TCAP_SendAppReject_ANSI(ITS_CTXT did, TCAP_CPT *comp,
                          ITS_OCTET family, ITS_OCTET reason,
                          ITS_BOOLEAN isLast)
{
    ITS_EVENT ev;
    TCAP_CPT err;
    ITS_HDR hdr;

    TCAP_DEBUG(("__TCAP_SendAppReject.\n"));

    if (did == 0)
    {
        return;
    }

    if (comp == NULL)
    {
        TCAP_ERROR(("SendAppReject: Can't reject non-component.\n"));

        return;
    }

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;

    /* build reject */
    memset(&err, 0, sizeof(TCAP_CPT));

    err.ptype = TCPPT_TC_REJECT;

    /* Added invoke_id in the Reject component?*/

    err.last_component = isLast;
    err.u.reject.invoke_id.len = 3;
    err.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    err.u.reject.invoke_id.data[1] = 1;
    /* What do I use for invoke_id? Answer: the event. */
    err.u.reject.invoke_id.data[2] = 0;

    /* I can get away with this as invoke_id is at the same offset
     * in all components. */
    if (comp)
    {
        err.u.reject.invoke_id.data[2] = comp->u.invoke.invoke_id.data[2];
    }

    err.u.reject.problem.len = 4;
    err.u.reject.problem.data[0] = TCPPROB_IDENT;
    err.u.reject.problem.data[1] = 2;
    err.u.reject.problem.data[2] = family;
    err.u.reject.problem.data[3] = reason;

    /* send to APP */
    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
    ev.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&ev.data[1], did);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &err, sizeof(TCAP_CPT));

    if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
    {
        TCAP_WARNING(("CMPHandleTPCPIMsg: unable to send reject.\n"));

        /* Discarding Dialogue - No Route to Application. */
    }
    
    ITS_EVENT_TERM(&ev);
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
void
__TCAP_SendReject_ANSI(ITS_CTXT did, TCAP_CPT *comp,
                       ITS_OCTET family, ITS_OCTET reason)
{
    ITS_EVENT ev;
    TCAP_CPT cpt;

    if (comp == NULL)
    {
        TCAP_ERROR(("__TCAP_SendReject_ANSI: Can't reject non-component.\n"));

        /* Incoming Component - Discarding Component - Invalid or Corrupted. */
        return;
    }

    TCAP_DEBUG(("__TCAP_SendReject.\n"));

    if (did == 0)
    {
        return;
    }

    /* build reject */
    memset(&cpt, 0, sizeof(TCAP_CPT));

    cpt.ptype = TCPPT_TC_REJECT;
    cpt.last_component = ITS_FALSE;
    cpt.u.reject.invoke_id.len = 3;
    cpt.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    cpt.u.reject.invoke_id.data[1] = 1;

    /* I can get away with this as invoke_id is at the same offset
     * in all components. */
    if (comp)
    {
        cpt.u.reject.invoke_id.data[2] = comp->u.invoke.invoke_id.data[2];
    }

    cpt.u.reject.problem.len = 4;
    cpt.u.reject.problem.data[0] = TCPPROB_IDENT;
    cpt.u.reject.problem.data[1] = 2;
    cpt.u.reject.problem.data[2] = family;
    cpt.u.reject.problem.data[3] = reason;

    /* send to TPCPI */
    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
    ev.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&ev.data[1], did);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &cpt, sizeof(TCAP_CPT));

    TPCPIHandleCMPMsg_ANSI(&ev);

    /* Above: DO NOT TERM THIS EVENT.  A copy of the event is queued, not
     * transmitted.  We must not free the data pointer */

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
void
__TCAP_SendDecodeReject_ANSI(TCAP_CPT *cpt, ITS_SCCP_IE *ies, int ieCount,
                             ITS_OCTET family, ITS_OCTET reason)
{
    ITS_EVENT ev;
    TCAP_CPT err;
    TCAP_DLG dlg;
    ITS_OCTET pType;
    ITS_UINT tid1, tid2, tmp;
    SCCP_ADDR cdp, clp;
    ITS_CTXT did = 0;
    TCAP_TRANS_ENTRY* trCtxt = NULL;
    ITS_HDR hdr;
    ITS_OCTET tidKey[4];
    int keyLen = 0;
    int ret = ITS_SUCCESS;
    int i = 0;
    ITS_OCTET ssn;
#if defined (PEPSY_CODEC)
    struct type_ANSI__TCAP_PackageType *pdu;
    char *enc = NULL;
    PE pe;
    int len = 0;
#elif defined (TCAP_CODEC) 
    ITS_OCTET cp[MAX_TCAP_CPT_SIZE];
    ITS_OCTET tp[MAX_TCAP_TRANS_SIZE];
    ITS_UINT cpLen = 0;
    ITS_UINT tpLen = 0;
#endif    

    TCAP_DEBUG(("__TCAP_SendDecodeReject.\n"));

    if (FindPTypeAndTID_ANSI(ies, ieCount, &pType, &tid1, &tid2,
                             &cdp, &clp) == ITS_NO)
    {
        /* The Incomming Message we want to reject is just too corrupt */
        TCAP_ERROR(("__TCAP_SendDecodeReject can't parse.\n"));

        return;
    }
    switch (pType)
    {
    case TCPPT_TC_UNI:
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:

    /* DSM Tx needed? */
    case TCPPT_TC_RESP:
        if ((trCtxt = TCAP_FindTransactionContext_ANSI(tid2,
                                                       tidKey, &keyLen)) == NULL)
        {
            TCAP_ERROR(("__TCAP_SendDecodeReject failed to find context.\n"));

            return;
        }
        break;
    }

    /* flip otid and dtid around */
    tmp = tid1;
    tid1 = tid2;
    tid2 = tmp;

    if (trCtxt)
    {
        did = trCtxt->did;

        ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ANSI_TCAP_DLG,
                         tidKey, keyLen,
                         (void *)trCtxt);
        if (ret != ITS_SUCCESS)
        {

            TCAP_ERROR(("__TCAP_SendDecodeReject_ANSI: DSM_Commit Failed "
                        "error code, %d\n", ret));

            /* Unable to Commit Transaction Context to Table. */
        }
    }

    /* build reject */
    memset(&err, 0, sizeof(TCAP_CPT));

    /* Added invoke_id in the Reject component?*/
    err.last_component = 1;
    err.u.reject.invoke_id.len = 3;
    err.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    err.u.reject.invoke_id.data[1] = 1;
    /* What do I use for invoke_id? Answer: cpt. */
    err.u.reject.invoke_id.data[2] = 0;

    if (cpt != NULL && cpt->u.invoke.invoke_id.len)
    {
         err.u.reject.invoke_id.data[2] = cpt->u.invoke.invoke_id.data[2];
    }

    err.ptype = TCPPT_TC_REJECT;
    err.u.reject.problem.len = 4;
    err.u.reject.problem.data[0] = TCPPROB_IDENT;
    err.u.reject.problem.data[1] = 2;
    err.u.reject.problem.data[2] = family;
    err.u.reject.problem.data[3] = reason;

    if (TCAP_VendorComponentSanityCheck(&err) != ITS_SUCCESS)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: Sanity check failed.\n"));

        return;
    }

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;

    /* build end */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    dlg.ptype = TCPPT_TC_RESP;
    dlg.u.end.cpt_present = 1;
#if defined (PEPSY_CODEC)
    pdu = TCAP_CvtDLGToPackage_ANSI(&dlg, tid1, tid2);

    if (!pdu)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: Could not convert dialog to package.\n"));

        return;
    }

    /* perform the encode */
    if (encode_ANSI__TCAP_PackageType(&pe, 1, 0, NULL, (void *)pdu)
        == NOTOK)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: Could not encode package.\n"));

        free_ANSI__TCAP_PackageType(pdu);

        return;
    }
    
#if defined(LOCAL_DEBUG)
    print_ANSI__TCAP_PackageType(pe, 1, 0, NULL, pdu);
#endif

    free_ANSI__TCAP_PackageType(pdu);

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: Could not encode package.\n"));
        pe_free(pe);

        return;
    }

    if (pe)
    {
        pe_free(pe);
    }

    if (enc == NULL && len == 0)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: Encode left no data.\n"));

        return;
    }
#elif defined (TCAP_CODEC)

    /* Build the Reject Message to send to Remote End */
    ret = TCAP_CvtCPTToData_ANSI(&err, cp, &cpLen);

    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: component encode failed.\n"));
        ret = (!ITS_SUCCESS);
    }
    else 
    {
        /* note that this is legal for all components as they all have
         * cpt_present in the same place in their structure 
         */
        dlg.u.uni.cpt_present = 1;
    }

    if (TCAP_CvtDLGToData_ANSI(&dlg, tp, &tpLen, cp, cpLen, tid1, tid2) != ITS_SUCCESS)
    {
        TCAP_ERROR(("__TCAP_SendDecodeReject: Could not convert dialog to package.\n"));
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

    SCCP_SendUnitData(WHICH_STACK, &hdr,
                      ies, ieCount);
    
    /* also send to the user if we have a context */
    if (trCtxt)
    {
        /* send to TPCPI */
        ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                       1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
        ev.data[0] = ITS_TCAP_CPT;
        ITS_SET_CTXT(&ev.data[1], did);
        memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &err, sizeof(TCAP_CPT));

        if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
        {
            TCAP_WARNING(("__TCAP_SendDecodeReject: unable to send reject.\n"));

            /* Discarding Component - No Route to Application. */

        }
        else
        {
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_REJECT_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT); 

        }
         
        /* Free the context if it exists */
        TCAP_FreeDSMTransactionContext_ANSI(trCtxt);

        ITS_EVENT_TERM(&ev);
    }
    return;
}


void
__TCAP_SendDecodeAbort_ANSI(ITS_SCCP_IE *ies, int ieCount,
                            ITS_OCTET reason)
{
    ITS_EVENT ev;
    TCAP_DLG dlg;
    ITS_OCTET pType;
    ITS_UINT tid1, tid2, tmp;
    SCCP_ADDR cdp, clp;
    ITS_CTXT did = 0;
    TCAP_TRANS_ENTRY* trCtxt = NULL;
    ITS_HDR hdr;
    int i = 0;
    ITS_OCTET ssn;
    ITS_OCTET tidKey[4];
    int keyLen = 0;
#if defined (PEPSY_CODEC)
    struct type_ANSI__TCAP_PackageType *pdu;
    char *enc = NULL;
    PE pe;
    int len = 0;
#elif defined (TCAP_CODEC)
    ITS_OCTET tp[MAX_TCAP_TRANS_SIZE];
    ITS_UINT tpLen = 0;
#endif

    TCAP_DEBUG(("__TCAP_SendDecodeAbort.\n"));

    if (FindPTypeAndTID_ANSI(ies, ieCount, &pType, &tid1, &tid2,
                             &cdp, &clp) == ITS_NO)
    {
        /* The Incomming Message we want to reject is just too corrupt */

        TCAP_ERROR(("__TCAP_SendDecodeAbort can't parse.\n"));

        return;
    }

    switch (pType)
    {
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
    /* DSM Tx needed? */
        if ((trCtxt = TCAP_FindTransactionContext_ANSI(tid2,
                                                       tidKey, &keyLen)) == NULL)
        {
            TCAP_ERROR(("__TCAP_SendDecodeAbort failed to find context.\n"));

            return;
        }
        break;

    default:

        /* specs says ignore */
 
        return;
    }
   
    /* flip otid and dtid around */
    tmp = tid1;
    tid1 = tid2;
    tid2 = tmp;

    if (trCtxt)
    {
        did = trCtxt->did;
    }
    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;

    /* build end */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    dlg.ptype = TCPPT_TC_ABORT;
    dlg.u.abort.abort_reason = reason;

#if defined (PEPSY_CODEC)
    pdu = TCAP_CvtDLGToPackage_ANSI(&dlg, tid1, tid2);

    if (!pdu)
    {
        TCAP_ERROR(("__TCAP_SendDecodeAbort: Could not convert dialog to package.\n"));

        return;
    }

    /* perform the encode */
    if (encode_ANSI__TCAP_PackageType(&pe, 1, 0, NULL, (void *)pdu)
        == NOTOK)
    {
        TCAP_ERROR(("__TCAP_SendDecodeAbort: Could not encode package.\n"));

        free_ANSI__TCAP_PackageType(pdu);

        return;
    }
    
#if defined(LOCAL_DEBUG)
    print_ANSI__TCAP_PackageType(pe, 1, 0, NULL, pdu);
#endif

    free_ANSI__TCAP_PackageType(pdu);

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        TCAP_ERROR(("__TCAP_SendDecodeAbort: Could not encode package.\n"));

        pe_free(pe);

        return;
    }

    if (pe)
    {
        pe_free(pe);
    }

    if (enc == NULL && len == 0)
    {
        TCAP_ERROR(("__TCAP_SendDecodeAbort: Encode left no data.\n"));

        return;
    }
#elif defined (TCAP_CODEC)

    if (TCAP_CvtDLGToData_ANSI(&dlg, tp, &tpLen, NULL, 0, tid1, tid2) != ITS_SUCCESS)
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

    SCCP_SendUnitData(WHICH_STACK, &hdr,
                      ies, ieCount);
     
    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

    /* also send to the user if we have a context */

    if (trCtxt)
    {
        hdr.type = ITS_TCAP;
        hdr.context.dialogue_id = did;

        ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                       1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));

        ev.data[0] = ITS_TCAP_DLG;
        ITS_SET_CTXT(&ev.data[1], did);

        memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

        if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
        {
            TCAP_WARNING(("__TCAP_SendDecodeAbort: unable to send Abort resp.\n"));
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
        }
        else
        {
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);
        }
        /* Free the context if it exists */
        TCAP_FreeDSMTransactionContext_ANSI(trCtxt);

        /* Free local context, if there */
        TCAP_FreeLocalTx_ANSI(did);

        ITS_EVENT_TERM(&ev);
    }

    return;
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
void
__TCAP_SendTransReject_ANSI(ITS_SCCP_IE* ies, int ieCount,
                            ITS_OCTET family, ITS_OCTET reason)
{
    ITS_EVENT ev;
    TCAP_CPT err;
    TCAP_DLG dlg;
    ITS_OCTET pType;
    ITS_UINT tid1, tid2;
    SCCP_ADDR cdp, clp;
    ITS_CTXT did = 0;
    TCAP_TRANS_ENTRY* trCtxt = NULL;
    ITS_OCTET tidKey[4];
    int keyLen = 0;
    int ret = ITS_SUCCESS;

    TCAP_DEBUG(("__TCAP_SendTransReject.\n"));

    if (FindPTypeAndTID_ANSI(ies, ieCount, &pType, &tid1, &tid2,
                             &cdp, &clp) == ITS_NO)
    {
        if (reason != TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI)
        {
            TCAP_ERROR(("__TCAP_SendDecodeReject can't parse.\n"));

            return;
        }
    }

    switch (pType)
    {
    case TCPPT_TC_UNI:
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
    case TCPPT_TC_RESP:
    /* DSM Tx needed? */
        if ((trCtxt = TCAP_FindTransactionContext_ANSI(tid2,
                                                       tidKey, &keyLen)) == NULL)
        {
            TCAP_ERROR(("__TCAP_SendTransReject failed to find context.\n"));

            return;
        }
        break;
    }

    if (trCtxt)
    {
        did = trCtxt->did;

        ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ANSI_TCAP_DLG, 
                         tidKey, keyLen, 
                         (void *)trCtxt);
        if (ret != ITS_SUCCESS)
        {   
            TCAP_ERROR(("__TCAP_SendTransReject_ANSI: DSM_Commit Failed "
                        "error code, %d\n", ret));
            
            /* Unable to Commit Transaction Context to Table. */
          
        }
    }

    /* build end */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    dlg.ptype = TCPPT_TC_RESP;
    dlg.u.end.cpt_present = 1;

    /* build reject */
    memset(&err, 0, sizeof(TCAP_CPT));
    err.last_component = 1;
    err.ptype = TCPPT_TC_REJECT;
    err.u.reject.problem.len = 4;
    err.u.reject.problem.data[0] = TCPPROB_IDENT;
    err.u.reject.problem.data[1] = 2;
    err.u.reject.problem.data[2] = family;
    err.u.reject.problem.data[3] = reason;

    /* send to TPCPI */

    CMPHandleTPCPIMsg_ANSI(did, &err);
    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_REJECT_SENT);

    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));
    ev.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&ev.data[1], did);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

    TPCPIHandleAPPMsg_ANSI(&ev);
    
    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

    ITS_EVENT_TERM(&ev);
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
void
__TCAP_SendTransAbort_ANSI(ITS_SCCP_IE* ies, int ieCount,
                           ITS_OCTET reason)
{
    ITS_EVENT ev;
    TCAP_DLG dlg;
    ITS_OCTET pType;
    ITS_UINT tid1, tid2, tmp;
    SCCP_ADDR cdp, clp;
    ITS_CTXT did = 0;
    TCAP_TRANS_ENTRY* trCtxt = NULL;
    ITS_HDR hdr;
    struct type_ANSI__TCAP_PackageType *pdu;
    char *enc = NULL;
    PE pe;
    int len = 0, i = 0;
    ITS_OCTET ssn;
    ITS_OCTET tidKey[4];
    int keyLen = 0;
    ITS_BOOLEAN sendLocal = ITS_TRUE;
    ITS_BOOLEAN sendRemote = ITS_TRUE;

    TCAP_DEBUG(("__TCAP_SendTransAbort.\n"));

    if (FindPTypeAndTID_ANSI(ies, ieCount, &pType, &tid1, &tid2,
                             &cdp, &clp) == ITS_NO)
    {
        if (reason != TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI)
        {
            TCAP_ERROR(("__TCAP_SendTransAbort can't parse.\n"));

            return;
        }
    }

    switch (pType)
    {
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        if (reason == TCPPROB_SPEC_TRANS_UNREC_TRANS_ID)
        {
            sendLocal = ITS_FALSE;
            break;
        }
        /* DSM Tx needed? */
        if ((trCtxt = TCAP_FindTransactionContext_ANSI(tid2,
                                                       tidKey, &keyLen)) == NULL)
        {
            TCAP_ERROR(("__TCAP_SendTransAbort failed to find context.\n"));

            return;
        }

        /* flip otid and dtid around */
        tmp = tid1;
        tid1 = tid2;
        tid2 = tmp;

        break;

    default:
        if (ANSI_TCAP_Variant < ANSI_TCAP_1996)
        {
            /* specs says ignore */
            return;
        }
        else if (ANSI_TCAP_Variant == ANSI_TCAP_1996)
        {
            /* ANSI-96 specs say see if the tids are derivable and take action
               based on them. */

            if (!tid1)
            {
                sendRemote = ITS_FALSE;
            }
            if (!tid2)
            {
                /* Unknown Msg, 
                 * RTID not derivable 
                 */
                TCAP_ERROR(("__TCAP_SendTransAbort Discard.\n"));

                return;
            }

            if (sendLocal && sendRemote)
            {
                /* Unknown Msg, 
                 * RTID derivable and (assigned / not assigned)
                 * OTID derivable
                 */
                TCAP_DEBUG(("__TCAP_SendTransAbort Send Both.\n"));

                /* DSM Tx needed? */
                if ((trCtxt = TCAP_FindTransactionContext_ANSI(tid2, tidKey, &keyLen)) 
                                                               == NULL)
                {
                    TCAP_ERROR(("__TCAP_SendTransAbort failed to find context.\n"));

                    return;
                }

                /* flip otid and dtid around */
                tmp = tid1;
                tid1 = tid2;
                tid2 = tmp;
            }
            else if (!sendLocal && !sendRemote)
            {
                TCAP_ERROR(("__TCAP_SendTransAbort Discard.\n"));

                return;
            }
        }
    }

    if (trCtxt)
    {
        did = trCtxt->did;
    }

    /* build abort */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    dlg.ptype = TCPPT_TC_ABORT;
    dlg.u.abort.abort_reason = reason;

    if (sendRemote)
    {
        pdu = TCAP_CvtDLGToPackage_ANSI(&dlg, tid1, tid2);
        if (!pdu)
        {
            TCAP_ERROR(("SendAbort: Could not convert dialog to package.\n"));

            return;
        }

        /* perform the encode */
        if (encode_ANSI__TCAP_PackageType(&pe, 1, 0, NULL, (void *)pdu)
            == NOTOK)
        {
            TCAP_ERROR(("SendAbort: Could not encode package.\n"));

            free_ANSI__TCAP_PackageType(pdu);

            return;
        }

#if defined(LOCAL_DEBUG)
    print_ANSI__TCAP_PackageType(pe, 1, 0, NULL, pdu);
#endif

        free_ANSI__TCAP_PackageType(pdu);

        if (pe2ssdu(pe, &enc, &len) != OK)
        {
            TCAP_ERROR(("SendAbort: Could not encode package.\n"));

            pe_free(pe);

            return;
        }

        if (pe)
        {
            pe_free(pe);
        }

        if (enc == NULL && len == 0)
        {
            TCAP_ERROR(("SendAbort: Encode left no data.\n"));

            return;
        }

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
                ies[i].param_length = len;
                memcpy(ies[i].param_data.userData.data, enc, len);
            }
        }

        free(enc);

        hdr.type = ITS_TCAP;

        SCCP_SendUnitData(WHICH_STACK, &hdr,
                          ies, ieCount);

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

    }

    if (trCtxt && sendLocal)
    {
        hdr.type = ITS_TCAP;
        hdr.context.dialogue_id = did;
        hdr.context.ssn = 0;
        ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                       1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));

        ev.data[0] = ITS_TCAP_DLG;
        ITS_SET_CTXT(&ev.data[1], did);
        memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

        if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
        {
            TCAP_WARNING(("Decodeect: unable to send reject resp.\n"));

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);

        }
        else
        {
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);
        }
        /* Free the context if it exists */
        TCAP_FreeDSMTransactionContext_ANSI(trCtxt);
    }

    return;
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
 *  csireesh  30-05-2005  ID::R0170 to R0210      XUDT/XUDTS Implementation
 *
 ****************************************************************************/

ITS_BOOLEAN
FindPTypeAndTID_ANSI(ITS_SCCP_IE *ies, int ieCount,
                     ITS_OCTET *pType,
                     ITS_UINT *tid1, ITS_UINT *tid2,
                     SCCP_ADDR *cdp, SCCP_ADDR *clp)
{
    int i;
    ITS_OCTET *data;
    int len;
    int tidLen;

    *pType = 0;

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
            break;
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        {
            *pType = ies[i].param_data.longData.data[0];

            data = &ies[i].param_data.longData.data[1];
            ies[i].param_length = 2;
            break;
        }
    }

    if (i == ieCount || ies[i].param_length < 1)
    {
        TCAP_ERROR(("FindPTypeAndTID: No SCCP USER_DATA.\n"));

        TCAP_Alarm_ANSI(1029, __FILE__, __LINE__, NULL);

        return (ITS_NO);
    }

    /* get the Transaction length */
    len = *data;
    if (len == EXT_LEN_FLAG)
    {
        TCAP_ERROR(("FindPTypeAndTID: Indeterminate length specification not allowed.\n"));

        return (ITS_NO);
    }
    else if (len > EXT_LEN_FLAG)
    {
        int tlen = len & ~EXT_LEN_FLAG;

        len = 0;
        if (tlen > 4)
        {
            TCAP_ERROR(("FindPTypeAndTID: length is greater than 2**32.\n"));

            return (ITS_NO);
        }
        data++;
        while (tlen > 0)
        {
            len <<= 8;
            len = *data;
            tlen--;
            data++;
        }
    }
    else
    {
        data++;
    }

    /* should have the transaction ID identifier */
    if (*data != TID_IDENT)
    {
        TCAP_ERROR(("FindPTypeAndTID: Bad or missing TID ID.\n"));

        return (ITS_NO);
    }
    data++;

    /* tid length must be 0, 4, or 8 */
    if (*data != 0 && *data != 4 && *data != 8)
    {
        TCAP_ERROR(("FindPTypeAndTID: Bad or missing TID length.\n"));

        return (ITS_NO);
    }

    switch (*pType)
    {
    case TCPPT_TC_UNI:
        /* Must have no TID in UNIs */
        if (*data != 0)
        {
            *tid1 = *tid2 = 0;

            TCAP_ERROR(("FindPTypeAndTID: UNI has no TIDs.\n"));

            return (ITS_NO);
        }
        return (ITS_YES);

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        /* queries have only one TID */
        if (*data != 4)
        {
            TCAP_ERROR(("FindPTypeAndTID: QW(O)P has 1 TID only.\n"));

            return (ITS_NO);
        }
        *tid1 = *tid2 = 0;

        /* get TID1 */
        data++;
        *tid1 |= *data;
        *tid1 <<= 8;

        data++;
        *tid1 |= *data;
        *tid1 <<= 8;

        data++;
        *tid1 |= *data;
        *tid1 <<= 8;

        data++;
        *tid1 |= *data;

        return (ITS_YES);

    case TCPPT_TC_RESP:
    case TCPPT_TC_ABORT:
        /* response has two tids */
        if (*data != 4)
        {
            TCAP_ERROR(("FindPTypeAndTID: RESP has 1 TID only.\n"));

            return (ITS_NO);
        }
        *tid1 = *tid2 = 0;

        /* get TID2 */
        data++;
        *tid2 |= *data;
        *tid2 <<= 8;

        data++;
        *tid2 |= *data;
        *tid2 <<= 8;

        data++;
        *tid2 |= *data;
        *tid2 <<= 8;

        data++;
        *tid2 |= *data;
        return (ITS_YES);

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        /* conv has two tids */
        if (*data != 8)
        {
            TCAP_ERROR(("FindPTypeAndTID: CW(O)P must have 2 TIDs.\n"));

            return (ITS_NO);
        }
        *tid1 = *tid2 = 0;

        /* get TID1 */
        data++;
        *tid1 |= *data;
        *tid1 <<= 8;

        data++;
        *tid1 |= *data;
        *tid1 <<= 8;

        data++;
        *tid1 |= *data;
        *tid1 <<= 8;

        data++;
        *tid1 |= *data;

        /* get TID2 */
        data++;
        *tid2 |= *data;
        *tid2 <<= 8;

        data++;
        *tid2 |= *data;
        *tid2 <<= 8;

        data++;
        *tid2 |= *data;
        *tid2 <<= 8;

        data++;
        *tid2 |= *data;

        return (ITS_YES);

    default:
        TCAP_ERROR(("FindPTypeAndTID: Unknown pType.\n"));
        if (ANSI_TCAP_Variant < ANSI_TCAP_1996)
        {
            return (ITS_NO);
        }
        else
        {
            *pType = 0;

            /* See if TID's are derivable */
            if (*data != 4 && *data != 8)
            {
                return (ITS_NO);
            }
            tidLen = *data;

            if (tidLen >= 4)
            {
                *tid1 = *tid2 = 0;

                /* get TID1 */
                data++;
                *tid1 |= *data;
                *tid1 <<= 8;

                data++;
                *tid1 |= *data;
                *tid1 <<= 8;

                data++;
                *tid1 |= *data;
                *tid1 <<= 8;

                data++;
                *tid1 |= *data;

                if (tidLen == 4)
                {
                    return (ITS_NO);
                }

                /* get TID2 */
                data++;
                *tid2 |= *data;
                *tid2 <<= 8;

                data++;
                *tid2 |= *data;
                *tid2 <<= 8;

                data++;
                *tid2 |= *data;
                *tid2 <<= 8;

                data++;
                *tid2 |= *data;

                return (ITS_NO);
            }

            return (ITS_NO);
        }
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
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        MTP3_PC_SET_VALUE(dlg->u.begin.opc, opc);
        MTP3_PC_SET_VALUE(dlg->u.begin.dpc, dpc);
        break;
    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
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
UpdateAddrsAndQOS(TCAP_DLG* dlg, SCCP_ADDR* clp, SCCP_ADDR *cdp,
                  MTP3_HEADER *mtp3, TCAP_TRANS_ENTRY *tr,
                  SCCP_PROT_CLASS *pclass)
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

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
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

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        /* get the addrs */
        dlg->u.cont.orig_addr.len = clp->len;
        memcpy(dlg->u.cont.orig_addr.data, clp->data, clp->len);

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

        break;

    case TCPPT_TC_RESP:
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

    case TCPPT_TC_ABORT:
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
ValidateDialogueForAppCtxtAndProtVer(ITS_OCTET *pType,
                                     TCAP_DLG *dlg,
                                     TCAP_TRANS_ENTRY *tr,
                                     ITS_CTXT did, ITS_EVENT *event,
                                     ITS_SCCP_IE *ies, int ieCount)
{
    switch (*pType)
    {
    case TCPPT_TC_UNI:
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        break;

    case TCPPT_TC_RESP:
        if (dlg->u.end.qos.indicator & QOSI_PROT_VER ||
            dlg->u.end.ac_name.len != 0)
        {
            __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                        TCAP_ABT_REASON_INCONSIST_DLG_PORT_ANSI);
            return (ITS_EPROTERR);
        }
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        if (dlg->u.cont.qos.indicator & QOSI_PROT_VER ||
            dlg->u.cont.ac_name.len != 0)
        {
            if (tr != NULL)
            {
                if (tr->state == ITS_TCAP_CWIP_SENT ||
                    tr->state == ITS_TCAP_CWOP_SENT)
                {
                    __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                                TCAP_ABT_REASON_INCONSIST_DLG_PORT_ANSI);
                    return (ITS_EPROTERR);
               }
            }
        }
        break;

    case TCPPT_TC_ABORT:
        if (dlg->u.abort.qos.indicator & QOSI_PROT_VER ||
            dlg->u.abort.ac_name.len != 0)
        {
           if (tr != NULL)
           {
               if (tr->state == ITS_TCAP_CWIP_SENT ||
                   tr->state == ITS_TCAP_CWOP_SENT)
               {
                   __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                               TCAP_ABT_REASON_INCONSIST_DLG_PORT_ANSI);
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
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_UNI_RCVD);
            break;

        case TCPPT_TC_QUERY_W_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_QWIP_RCVD);
            break;

        case TCPPT_TC_QUERY_WO_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_QWOP_RCVD);
            break;

        case TCPPT_TC_RESP:
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_RESP_RCVD);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
            break;

        case TCPPT_TC_CONV_W_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CWIP_RCVD);
            break;
        case TCPPT_TC_CONV_WO_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CWOP_RCVD);
            break;

        case TCPPT_TC_ABORT:
           PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_ABORT_RCVD);

           PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
           PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

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
        case TCPPT_TC_INVOKE_NL:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_INVOKE_RCVD);
            break;

        case TCPPT_TC_RESULT_L:
        case TCPPT_TC_RESULT_NL: 
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_RESULT_RCVD);
            break;

        case TCPPT_TC_ERROR:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_ERROR_RCVD);
            break;

        case TCPPT_TC_REJECT:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_REJECT_RCVD);
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
 *
 *
 *  Revision History:
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     04-06-2005  BCGI Helpdesk# 529      Fix for stack indication of
 *                                               component present for a new
 *                                               dialogue id
 *
 * csireesh  30-05-2005  ID::R0140 to R0160      Reassembly Implementation
 *
 ****************************************************************************/
#if defined (TCAP_CODEC)
static int
TCAP_DisassemblePDU(ITS_SCCP_IE *ies, int ieCount, TCAP_TRANS_ENTRY* tr)
{
    TCAP_DLG dlg;
    TCAP_CPT cpt;
    ITS_EVENT event;
    ITS_OCTET pType;
    int i;
    ITS_OCTET *data;
    ITS_USHORT len;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_CTXT did = 0;
    ITS_BOOLEAN isUNI = ITS_FALSE;
    SCCP_PROT_CLASS *pclass = NULL;
    MTP3_HEADER *mtp3 = NULL;
    ITS_BOOLEAN cpPresent = ITS_FALSE;
    ITS_OCTET *tp = NULL, *dp = NULL, *cp = NULL;
    ITS_OCTET *cpData, *comp;
    ITS_UINT cpTag, cpLen, cTag, cLen;
    int numCpts = 0;
    ITS_UINT cptsLen = 0;
    int extCptOctets = 0;
    int ret;
    ITS_BOOLEAN noticeReqd = ITS_FALSE;
    ITS_OCTET cause;
 
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
        TCAP_DEBUG(("TCAP_DisassemblePDU: No TRANS_CTXT!\n"));
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
            noticeReqd = ITS_TRUE;
            cause = ies[i].param_data.returnCause.cause;
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

    if (noticeReqd == ITS_TRUE)
    {
        /* TC-NOTICE */
        memset(&dlg, 0, sizeof(TCAP_DLG));

        hdr.type = ITS_TCAP;
        hdr.context.dialogue_id = did;
        dlg.u.notice.report_cause = cause;

        dlg.u.notice.orig_addr.len = clp->len;
        memcpy(dlg.u.notice.orig_addr.data, clp->data, clp->len);
        dlg.u.notice.dest_addr.len = cdp->len;
        memcpy(dlg.u.notice.dest_addr.data, cdp->data, cdp->len);

        dlg.ptype = TCPPT_TC_NOTICE;

        if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Sanity check failed.\n"));

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            /* Incoming Message - Discarding Message - Invalid or Corrupted.  */
            TCAP_Alarm_ANSI(1032, __FILE__, __LINE__,
                            "Dialog-Id %X, Dialog-Type %X",
                            did, dlg.ptype);

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

        /* Notice sent toward Application is received by Application */

        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            TCAP_DEBUG(("TCAP_DisassemblePDU: Send NOTICE to %04x\n", dest));

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);

            TRANSPORT_PutEvent(dest, &event);
        }
        else
        {
           /* Notice Discarded */
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            TCAP_ERROR(("TCAP_DisassemblePDU: Unable to send NOTICE to APP.\n"));

            /* Incoming Message - Discarding Message - No Route to Application. */
        }

        ITS_EVENT_TERM(&event);

        return (ITS_EPROTERR);
    }
    if ((pclass->pclass & SCCP_PCLASS_MASK) == SCCP_PCLASS_0) 
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD);
    }
    else
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD);
    }

    if (i == ieCount || ies[i].param_length < 1)
    {
        /*
         * can't really reject here, can only discard.
         * The UDT message was malformed. If SCCP is working correctly,
         * this should never happen.
         */
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);

        TCAP_ERROR(("TCAP_DisassemblePDU: No SCCP user data.\n"));

        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1029, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    /*
     * Step 2.  Decode the transaction
     */
    if (data == NULL || len == 0)
    {
        TCAP_ERROR(("TCAP_DisassemblePDU: No SCCP user data.\n"));

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);    
         
        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1029, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    /* Step 1: Parse data */
    ret = TCAP_FindParts_ANSI(data, len, &tp, &dp, &cp);

    if(ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_DisassemblePDU: Could not find parts.\n"));

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED); 

        if (pType == TCPPT_TC_UNI && (ANSI_TCAP_Variant > ANSI_TCAP_1992))
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Discarding UNI Message - Invalid or Corrupted.\n"));

            /* Incoming Message - Discarding Message - Invalid or Corrupted. */

            return (ITS_EPROTERR);
        }

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                        ret);
        }
        else
        {
            __TCAP_SendDecodeReject_ANSI(&cpt, ies, ieCount,
                                         TCPPROB_TRANS_PORTION,
                                         ret);
        }


            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1031, __FILE__, __LINE__,
                        "Reason %X Dialog-Id %X", ret, did);

        return (ITS_EPROTERR);
    }
     /*
     * ANSI does not allow to send Dialogue without Component
     * you got to have at least Dlg Portion if not Component present
     */
    if (cp == NULL && dp == NULL)
    {
        __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                    TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);

        TCAP_Alarm_ANSI(1031, __FILE__, __LINE__,
                        "Reason %X Dialog-Id %X", ret, did);

        return (ITS_EPROTERR);
    }
    else if (cp != NULL && cp[0] == CSEQ_IDENT)
    {
        cpPresent = ITS_TRUE;
    }  

    /*
     * Step 3.  Build the TCAP_DLG and send it to the user
     */
    if ((ret = TCAP_CvtDataToDLG_ANSI(&dlg, &pType, tp, dp, cpPresent, len)) != ITS_SUCCESS)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
  
        TCAP_ERROR(("TCAP_DisassemblePDU: Could not recover dialog portion.\n"));

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                        ret);
        }
        else
        {
            __TCAP_SendDecodeReject_ANSI(&cpt, ies, ieCount,
                                         TCPPROB_TRANS_PORTION,
                                         ret);
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_ANSI(1031, __FILE__, __LINE__,
                        "Reason %X Dialog-Id %X", ret, did);

        return (ITS_EPROTERR);
    }

    /* Update the address and QOS info */
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

    /* If variant == ANSI-88, send ABORT for 
     * conversation mesgs after 1st backward conversation
     */

    if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
    {
        ret = ValidateDialogueForAppCtxtAndProtVer(&pType, &dlg, tr,
                                                   did, &event,
                                                   ies, ieCount);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Could not Validate the Dialogue.\n"));
            return ret;
        }
    }

    ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));

    event.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&event.data[1], did);
    memcpy(&event.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

    if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("TCAP_DisassemblePDU: Sanity check failed.\n"));

        /* UNIDIRECTIONAL are done at this point */
        if (isUNI)
        {
            /* TBD
            TCAP_CleanInvokeContext_ANSI(did);
            */
        }

        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1032, __FILE__, __LINE__,
                        "Dialog-Id %X, Dialog-Type %X", did, dlg.ptype);

        return ITS_BADTCAPMESSAGE;
    }
    
    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        TCAP_DEBUG(("TCAP_DisassemblePDU: Send DLG to %04x\n", dest));
        
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_DLG_RCVD);
        UpdateDlgPeg(&dlg);

        TRANSPORT_PutEvent(dest, &event);
    }
    else
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("TCAP_DisassemblePDU: Unable to send DLG to APP.\n"));

        /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */
    
    }

    ITS_EVENT_TERM(&event);

    /*
     * Step 4.  If any components are  present, build them
     * and send them to CMP
     * cp --> Component Portion
     */

    cpData = cp;
    if (pType != TCPPT_TC_ABORT && cp != NULL)
    {
        /* Get Compnt Sequence Tag */
        cpData += TCAP_GetTag(cpData, &cpTag, tp + len);

        /* Get Component Sequence length cpLen */
        cpData += TCAP_GetLength(cpData, &cpLen, tp + len, ITS_TRUE); 

        if((cpLen == 0) || ((cpData[0] == 0) && (cpData[1] == 0)))
        {
            if(isUNI)
            {
                /* error Handling */
            }
        }

        /* cpData:Component Sequence :: Parse Components one by one  */
        while (cpData < (cp + cpLen) && cpData[0] != 0 && cpData[1] != 0)
        {
            extCptOctets = 0;
            comp = cpData;

            /* Get Component Type Identifier */
            comp += TCAP_GetTag(comp, &cTag, tp + len);

            /* Get Component Length */
            extCptOctets = TCAP_GetLength(comp, &cLen, tp + len, ITS_TRUE);
            comp += extCptOctets;

            if ((ret = TCAP_CvtDataToCPT_ANSI(&cpt, comp, cTag, cLen))!= ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_DisassemblePDU: Could not recover component "
                            "portion.\n"));

                /*
                 * This in effect enqueues the Reject Component
                 * to the TCAP Component Queue.
                 * An AppReject, (REJECT) is sent to the APP.
                 * The Enqueued component is thus appended with
                 * the next message from the user.
                 */

                __TCAP_SendReject_ANSI(did, &cpt,
                                       TCPPROB_GENERAL,
                                       ret);

                __TCAP_SendAppReject_ANSI(did, &cpt,
                                          TCPPROB_GENERAL,
                                          ret,
                                          ITS_TRUE);

                /* Incoming Component - Discarding Component - Rejection Sent by stack. */

                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

                /* UNIDIRECTIONAL are done at this point */
                if (isUNI)
                {
                    /* TBD
                    TCAP_CleanInvokeContext_ANSI(did);
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

            numCpts ++;
            cptsLen += cLen + extCptOctets;

            if (cptsLen + numCpts == cpLen)
            {
                cpt.last_component = 1;
            }

            UpdateCptPeg(&cpt);
          /* Add To Component Count for Received Component */
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_RCVD);

            /* Send to CMP */
            if ((ret = CMPHandleTPCPIMsg_ANSI(did, &cpt)) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_DisassemblePDU: Could not handle component.\n"));

                /* UNIDIRECTIONAL are done at this point */
                if (isUNI)
                {
                    /* TBD
                    TCAP_CleanInvokeContext_ANSI(did);
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

            /* Move to next Component cLen Previous component Length*/
            cpData = comp + cLen; 
        }
    }

    /* UNIDIRECTIONAL are done at this point */
    if (isUNI)
    {
        /* TBD
        TCAP_CleanInvokeContext_ANSI(did);
        */
    }

    /*
     * Step 5.  Clean up and go home
     */
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
 ****************************************************************************/
#if defined (PEPSY_CODEC)
static int
PEPSY_DisassemblePDU(ITS_SCCP_IE *ies, int ieCount, TCAP_TRANS_ENTRY* tr)
{
    TCAP_DLG dlg;
    TCAP_CPT cpt;
    ITS_EVENT event;
    ITS_OCTET pType;
    PE pe;
    int err, i;
    struct type_ANSI__TCAP_PackageType *pdu;
    ITS_OCTET *data;
    ITS_USHORT len;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_CTXT did = 0;
    ITS_BOOLEAN isUNI = ITS_FALSE;
    SCCP_PROT_CLASS *pclass = NULL;
    MTP3_HEADER *mtp3 = NULL;

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
                TCAP_ERROR(("PEPSY_DisassemblePDU: Sanity check failed.\n"));
        
                /* Incoming Message - Discarding Message - Invalid or Corrupted. */
                TCAP_Alarm_ANSI(1029, __FILE__, __LINE__, NULL);

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

            /* Notice sent toward Application is received by Application */

            if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
            {
                TCAP_DEBUG(("PEPSY_DisassemblePDU: Send NOTICE to %04x\n", dest));

                TRANSPORT_PutEvent(dest, &event);

                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);
            }
            else
            {

                /* Notice Discarded */
               PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
               PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);

                TCAP_ERROR(("PEPSY_DisassemblePDU: Unable to send NOTICE to APP.\n"));
        
                /* Incoming Message - Discarding Message - No Route to Application. */

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
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD);
    }
    else
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD);
    }

    if (i == ieCount || ies[i].param_length < 1)
    {
        /*
         * can't really reject here, can only discard.
         * The UDT message was malformed. If SCCP is working correctly,
         * this should never happen.
         */
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: No SCCP user data.\n"));
                
        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1029, __FILE__, __LINE__, NULL);

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
        TCAP_ERROR(("PEPSY_DisassemblePDU: No SCCP user data.\n"));
        
        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1029, __FILE__, __LINE__, NULL);

        return (ITS_EPROTERR);
    }

    pe = ssdu2pe((char *)data, len, NULL, &err);
    if (err != PS_ERR_NONE)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: decode failed.\n"));

        if (pType == TCPPT_TC_UNI && (ANSI_TCAP_Variant > ANSI_TCAP_1992))
        {
            TCAP_ERROR(("PEPSY_DisassemblePDU: Discarding UNI Message - Invalid or Corrupted.\n"));

            /* Incoming Message - Discarding Message - Invalid or Corrupted. */

            return (ITS_EPROTERR);
        }

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                        TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI);
        }
        else
        {
            __TCAP_SendDecodeReject_ANSI(&cpt, ies, ieCount,
                                         TCPPROB_TRANS_PORTION,
                                         TCPPROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT);
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_ANSI(1031, __FILE__, __LINE__,
                        "Reason %X Dialog-Id %X",
                        ret, did);

        return (ITS_EPROTERR);
    }
    if (decode_ANSI__TCAP_PackageType(pe, 1, NULL, NULL, (char **)&pdu) == OK)
    {
        TCAP_DEBUG(("PEPSY_DisassemblePDU: Package decode successful.\n"));
    }
    else
    {
        pe_free(pe);

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: PE decode failed.\n"));
        if (pType == TCPPT_TC_UNI && (ANSI_TCAP_Variant > ANSI_TCAP_1992))
        {
            TCAP_ERROR(("PEPSY_DisassemblePDU: Discarding UNI Message - Invalid or Corrupted.\n"));

            /* Incoming Message - Discarding Message - Invalid or Corrupted. */

            return (ITS_EPROTERR);
        }

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                        TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI);
        }
        else
        {
            __TCAP_SendDecodeReject_ANSI(&cpt, ies, ieCount,
                                         TCPPROB_TRANS_PORTION,
                                         TCPPROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT);
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_ANSI(1031, __FILE__, __LINE__, "Reason %X Dialog-Id %X",
                        ret, did);
 

        return (ITS_EPROTERR);
    }
    pe_free(pe);

    /*
     * Step 3.  Build the TCAP_DLG and send it to the user
     */
    if (TCAP_CvtPackageToDLG_ANSI(&dlg, pdu) != ITS_SUCCESS)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: Could not recover dialog portion.\n"));

        free_ANSI__TCAP_PackageType(pdu);

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            __TCAP_SendDecodeAbort_ANSI(ies, ieCount,
                                        TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI);
        }
        else
        {
            __TCAP_SendDecodeReject_ANSI(&cpt, ies, ieCount,
                                         TCPPROB_TRANS_PORTION,
                                         TCPPROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT);
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_ANSI(1031, __FILE__, __LINE__, "Reason %X Dialog-Id %X",
                        ret, did); 

        return (ITS_EPROTERR);
    }

    /* Update the address and QOS info */
    UpdateAddrsAndQOS(&dlg, clp, cdp, mtp3, tr, pclass);


    /* UNI, BEGIN, CONTINUE need point code information */
    InferPointCodes(did, mtp3, &dlg);

    /*
     * uni(s) do not get a transaction context, nor do invokes
     * that they carry get an invoke context.
     */
    if (dlg.ptype == TCPPT_TC_UNI)
    {
        isUNI = ITS_TRUE;
    }

    /* If variant == ANSI-88, send ABORT 
     * for transactions after first backward containing AC/PV
     */
    if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
    {
        int ret = ValidateDialogueForAppCtxtAndProtVer(&pType, &dlg, tr,
                                                       did, &event,
                                                       ies, ieCount);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_DisassemblePDU: Could not Validate the Dialogue.\n"));
            free_ANSI__TCAP_PackageType(pdu);
            return ret;
        }
    }

    ITS_EVENT_INIT(&event, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));

    event.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&event.data[1], did);
    memcpy(&event.data[1 + sizeof(ITS_CTXT)], &dlg, sizeof(TCAP_DLG));

    if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
 
        TCAP_ERROR(("PEPSY_DisassemblePDU: Sanity check failed.\n"));

        free_ANSI__TCAP_PackageType(pdu);

        /* UNIDIRECTIONAL are done at this point */
        if (isUNI)
        {
            /* TBD
            TCAP_CleanInvokeContext_ANSI(did);
            */
        }
        
        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1032, __FILE__, __LINE__,
                        "Dialog-Id %X, Dialog-Type %X", did, dlg.ptype);

        return ITS_BADTCAPMESSAGE;
    }
    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = did;
    dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        TCAP_DEBUG(("PEPSY_DisassemblePDU: Send DLG to %04x\n", dest));
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_DLG_RCVD);
        UpdateDlgPeg(&dlg);

        TRANSPORT_PutEvent(dest, &event);
    }
    else
    {
       PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);
       PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_ERROR(("PEPSY_DisassemblePDU: Unable to send DLG to APP.\n"));
        
        /* Incoming Dialogue - Discarding Dialogue - No Route to Application. */
    }

    ITS_EVENT_TERM(&event);

    /*
     * Step 4.  If any components are  present, build them
     * and send them to CMP
     */
    if (pdu->offset != type_ANSI__TCAP_PackageType_abort &&
        pdu->un.unidirectional->componentSequence != NULL)
    {
        struct type_ANSI__TCAP_ComponentSequence *comp =
            pdu->un.unidirectional->componentSequence;

        while (comp != NULL)
        {
            int ret;

            if ((ret = TCAP_CvtComponentPDUToCPT_ANSI(&cpt, comp->ComponentPDU))
                != ITS_SUCCESS)
            {
                TCAP_ERROR(("PEPSY_DisassemblePDU: Could not recover component "
                            "portion.\n"));
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

                free_ANSI__TCAP_PackageType(pdu);

                __TCAP_SendDecodeReject_ANSI(&cpt, ies, ieCount,
                                             TCPPROB_GENERAL,
                                             TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        
                /* Incoming Component - Discarding Component - Rejection Sent by stack. */

                /* UNIDIRECTIONAL are done at this point */
                if (isUNI)
                {
                    /* TBD
                    TCAP_CleanInvokeContext_ANSI(did);
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
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_RCVD);

            /* Send to CMP */
            if ((ret = CMPHandleTPCPIMsg_ANSI(did, &cpt)) != ITS_SUCCESS)
            {
                TCAP_ERROR(("PEPSY_DisassemblePDU: Could not handle component.\n"));

                free_ANSI__TCAP_PackageType(pdu);

                /* UNIDIRECTIONAL are done at this point */
                if (isUNI)
                {
                    /* TBD
                    TCAP_CleanInvokeContext_ANSI(did);
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

            comp = comp->next;
        }
    }

    /* UNIDIRECTIONAL are done at this point */
    if (isUNI)
    {
        /* TBD
           TCAP_CleanInvokeContext_ANSI(did);
        */
    }

    /*
     * Step 5.  Clean up and go home
     */
    free_ANSI__TCAP_PackageType(pdu);

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
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        MTP3_RL_SET_OPC(mtp3->label, dlg->u.begin.opc);
        MTP3_RL_SET_DPC(mtp3->label, dlg->u.begin.dpc);
        break;
    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        MTP3_RL_SET_OPC(mtp3->label, dlg->u.cont.opc);
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
            if (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors,
                                      TCAP_B_use_reserved_NI))
            {
                mtp3->sio |= MTP3_NIC_RESERVED;
            }
            else
            {
                mtp3->sio |= MTP3_NIC_NATIONAL;
            }
        }
        else
        {
            if (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors,
                                      TCAP_B_use_reserved_NI))
            {
                mtp3->sio |= MTP3_NIC_SPARE;
            }
            else
            {
                mtp3->sio |= MTP3_NIC_INTERNATIONAL;
            }
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
            if (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors,
                                      TCAP_B_use_reserved_NI))
            {
                mtp3->sio |= MTP3_NIC_RESERVED;
            }
            else
            {
                mtp3->sio |= MTP3_NIC_NATIONAL;
            }
        }
        else
        {
            if (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors,
                                      TCAP_B_use_reserved_NI))
            {
                mtp3->sio |= MTP3_NIC_SPARE;
            }
            else
            {
                mtp3->sio |= MTP3_NIC_INTERNATIONAL;
            }
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
    if (tx &&
        (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
         dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
#if defined (TCAP_CODEC)
static int
TCAP_AssemblePDU(ITS_CTXT did, TCAP_DLG *dlg, ITS_SCCP_IE *ies, int *ieCount)
{
    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;
    int ret = ITS_SUCCESS;
    TCAP_TRANS_ENTRY *localTx = NULL;
    TCAP_TRANS_ENTRY *sharedTx = NULL;
    ITS_INT ltid = 0, rtid = 0;
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

    /*
     * Step 1. Get the components, formatting each one
     */
    MQUEUE_Lock(__TCAP_ANSI_primQueue);

    for (entry = LIST_TAIL(__TCAP_ANSI_primQueue);
         entry != NULL;
         entry = prev)
    {
        ITS_CTXT cdid;
        ev = (ITS_EVENT *)entry->data;
        if ( ev->data == NULL)
        {
            continue;
        }
        cdid = ITS_GET_CTXT(&ev->data[1]);

        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            MQUEUE_RemoveNoLock(__TCAP_ANSI_primQueue, entry);

            memcpy(&cpt, &ev->data[1 + sizeof(ITS_CTXT)], sizeof(TCAP_CPT));

            ret = TCAP_CvtCPTToData_ANSI(&cpt, cp, &cpLen);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_AssemblePDU: component encode failed.\n"));

                TCAP_Alarm_ANSI(1037,__FILE__,__LINE__,"Dialog-Id %X", did);

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

                /* note that this is legal for all components as they all have
                 * cpt_present in the same place in their structure 
                 */
                dlg->u.uni.cpt_present = 1;
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
    MQUEUE_Unlock(__TCAP_ANSI_primQueue);

    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Encode aborted.\n"));

        TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, "Dialog-Id %X", did); 

        localTx = TCAP_FindLocalTx_ANSI(did);

        if (localTx)
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                 tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }

        return (ret);
    }

    /* Count TCAP Messages Sent */

    /*
     * Step 2. Convert the TCAP_DLG to the PDU.
     */
    /* find the addrs */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */

        cdp = &dlg->u.uni.dest_addr;
        clp = &dlg->u.uni.orig_addr;
        break;

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        cdp = &dlg->u.begin.dest_addr;
        clp = &dlg->u.begin.orig_addr;

        localTx = TCAP_FindLocalTx_ANSI(did);

        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: LocalTx not found for did %d", did));
            TCAP_Alarm_ANSI(1040, __FILE__, __LINE__,
                            "Dialog-Id %X PType %X",did, dlg->ptype);

            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_DISCARDED);
 
            return (ITS_BADTCAPMESSAGE);
        }

        ret = TCAP_PopulateLocalTx_ANSI(localTx, did, 0, 0, cdp, clp);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: LocalTx not populated for did %d",
                         did));

            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);

            return (ITS_BADTCAPMESSAGE);
        }

        /* save of the qos so we can override everywhere */
        localTx->qos = dlg->u.begin.qos;

        ltid = localTx->ltid;
        rtid = localTx->rtid;
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
    case TCPPT_TC_RESP:
    case TCPPT_TC_ABORT:
        localTx = TCAP_FindLocalTx_ANSI(did);

        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AssemblePDU: Missing transaction context.\n"));

            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_DISCARDED);
 
            TCAP_Alarm_ANSI(1040, __FILE__, __LINE__,
                            "Dialog-Id %X PType %X",did, dlg->ptype);

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
#if 0
        dlg->u.end.qos = localTx->qos;
#endif
        localTx->qos = dlg->u.end.qos;
        ltid = localTx->ltid;
        rtid = localTx->rtid;
        break;
    }

    TCAP_DEBUG(("TCAP_AssemblePDU: did %d, ltid = %08x, rtid = %08x.\n", did, ltid, rtid));

    /*  Fix for LOCAL CANCEL
     *  Don't build the PDU if has to be freed for Pre Arranged End.
     */
    if (dlg->ptype == TCPPT_TC_RESP)
    {
        if (dlg->u.end.termination == TCAP_END_PREARRANGED)
        {
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_PREARRANGED_END_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
  
            TCAP_DEBUG(("TCAP_AssemblePDU: PreArranged-End received for did"
                         "%d.\n", did));

            if (localTx)
            {
                sharedTx = TCAP_FindTransactionContext_ANSI(localTx->ltid,
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

                    TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
                }

                TCAP_FreeLocalTx_ANSI(did);
            }
            return (ITS_SUCCESS);
        }
    }

    /*
     * Step 3. Build the PDU.
     */
    if (TCAP_CvtDLGToData_ANSI(dlg, tp, &tpLen, cpList, cptsLen,ltid, rtid) != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Could not convert dialog to package.\n"));

         PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_DISCARDED); 
         PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            sharedTx = TCAP_FindTransactionContext_ANSI(localTx->ltid, tidKey,
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

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            TCAP_FreeLocalTx_ANSI(did);
        }

        return (ITS_BADTCAPMESSAGE);
    }

    if (tp == NULL || tpLen == 0)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Encode left no data.\n"));

        PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_DISCARDED);
          
        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */

        TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, "Dialog-Id %X", did); 

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
        ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_1;
    }

    if (dlg->u.uni.qos.indicator & QOSI_RET_OPT)
    {
        ies[0].param_data.protocolClass.pclass |=
            SCCP_PCLASS_RET_ON_ERR;
    }

    /*
     * ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
     * ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
     */
    if (cdp == NULL || clp == NULL)
    {
        TCAP_ERROR(("TCAP_AssemblePDU: Missing address.\n"));

        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
        TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, NULL);

        return (ITS_BADTCAPMESSAGE);
    }

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

    if (TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT))
    {
        ITS_EVENT tcapEvent;
        ITS_INT output = 0;

        tcapEvent.src = ITS_APP_PROTOCOL_1;
        tcapEvent.data = (ITS_OCTET*)malloc(sizeof(ITS_OCTET)*tpLen);
        tcapEvent.len = tpLen;
        memcpy(tcapEvent.data, tp, tpLen);

        
        if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
            TCAP_TRACE_EVENT,
            0))
        {
            output += 1;
        }
        if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
            TCAP_TRACE_EVENT,
            1))
        {
            output += 2;
        }

        CTF_TraceEvent(tcapEvent.src, ITS_TCAP_ANSI_SRC,
            output, &tcapEvent); 
        free(tcapEvent.data);
        memset(&tcapEvent, 0, sizeof(ITS_EVENT));
    }

    /* routing label */
    memset(&ies[4].param_data.routingLabel, 0,
           sizeof(MTP3_HEADER));

    BuildRoutingLabel(dlg,
                      &ies[1].param_data.calledPartyAddr,
                      &ies[2].param_data.callingPartyAddr,
                      &ies[4].param_data.routingLabel,
                      localTx);

    ies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[4].param_length = sizeof(MTP3_HEADER);

    if (dlg->u.uni.qos.indicator & QOSI_SEQ_CTRL)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_1_SENT);

        if (dlg->u.uni.qos.indicator & QOSI_SLS_KEY)
        {
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            dlg->u.uni.qos.sls_key);
        }
        else if (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
                 dlg->ptype == TCPPT_TC_QUERY_WO_PERM)
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
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,0);
        }
    }
    else
    {
        /* FIXME: NOT REENTRANT */
        static ITS_OCTET sls = 0;

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_0_SENT);

        MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,sls);
        sls++;
    }

    if (dlg->u.uni.qos.indicator & QOSI_PRIORITY)
    {
        ies[4].param_data.routingLabel.sio |= dlg->u.uni.qos.priority;
    }

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
 ****************************************************************************/
#if defined (PEPSY_CODEC)
static int
PEPSY_AssemblePDU(ITS_CTXT did, TCAP_DLG *dlg, ITS_SCCP_IE *ies, int *ieCount)
{
    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;
    struct type_ANSI__TCAP_ComponentSequence *seq = NULL;
    struct type_ANSI__TCAP_PackageType *pdu;
    int ret = ITS_SUCCESS;
    PE pe = NULL;
    int len = 0;
    char *enc = NULL;
    TCAP_TRANS_ENTRY *localTx = NULL;
    TCAP_TRANS_ENTRY *sharedTx = NULL;
    ITS_INT ltid = 0, rtid = 0;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;

    *ieCount = 0;

    /*
     * Step 1. Get the components, formatting each one
     */
    MQUEUE_Lock(__TCAP_ANSI_primQueue);

    for (entry = LIST_TAIL(__TCAP_ANSI_primQueue);
         entry != NULL;
         entry = prev)
    {
        ITS_CTXT cdid;
        
        ev = (ITS_EVENT *)entry->data;
        cdid = ITS_GET_CTXT(&ev->data[1]);
        
        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            struct type_ANSI__TCAP_ComponentSequence *tmp;

            MQUEUE_RemoveNoLock(__TCAP_ANSI_primQueue, entry);

            tmp = seq;
            if ((seq =
                (struct type_ANSI__TCAP_ComponentSequence *)malloc
                    (sizeof(struct type_ANSI__TCAP_ComponentSequence))) == NULL)
            {
                TCAP_ERROR(("PEPSY_AssemblePDU: no memory for comp sequence.\n"));

                /* Memory allocation failed for Component Sequence */
                TCAP_Alarm_ANSI(1036, __FILE__, __LINE__,
                                "Dialog-Id %X", did);
                
                ret = ITS_ENOMEM;
            }

            if (seq)
            {
                TCAP_CPT cpt;

                seq->next = tmp;
                memcpy(&cpt, &ev->data[1 + sizeof(ITS_CTXT)], sizeof(TCAP_CPT));
                seq->ComponentPDU = TCAP_CvtCPTToComponentPDU_ANSI(&cpt);

                if (seq->ComponentPDU == NULL)
                {
                    TCAP_ERROR(("PEPSY_AssemblePDU: component encode failed.\n"));
                    
                    /* Encode failed for Component Sequence */
                    TCAP_Alarm_ANSI(1037,__FILE__,__LINE__,
                                    "Dialog-Id %X", did);

                    free(seq);
                    seq = tmp;
                }
                /* Add to component count for total component */

                /* note that this is legal for all components as they all have
                 * cpt_present in the same place in their structure */
                dlg->u.uni.cpt_present = 1;
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

    MQUEUE_Unlock(__TCAP_ANSI_primQueue);

    /* seq now points to a list of components, if it's valid */
    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Encode aborted.\n"));
        free_ANSI__TCAP_ComponentSequence(seq);
        localTx = TCAP_FindLocalTx_ANSI(did);

        if (localTx)
        {
             TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
             TCAP_FreeLocalTx_ANSI(did);
        }

        return (ret);
    }
    /* Count TCAP Messages Sent */

    /*
     * Step 2. Convert the TCAP_DLG to the pepsy structure.
     */
    /* find the addrs */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        /* Incoming Dialogue - Discarding Dialogue - Invalid or Corrupted. */
        cdp = &dlg->u.uni.dest_addr;
        clp = &dlg->u.uni.orig_addr;
        break;

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        cdp = &dlg->u.begin.dest_addr;
        clp = &dlg->u.begin.orig_addr;
        localTx = TCAP_FindLocalTx_ANSI(did);
 
        if (localTx == NULL)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: LocalTx not found for did %d", did));
             TCAP_Alarm_ANSI(1040, __FILE__, __LINE__,
                            "Dialog-Id %X PType %X",did, dlg->ptype);
             
            /* Unable to commit transaction context to Table */
            free_ANSI__TCAP_ComponentSequence(seq);
            return (ITS_BADTCAPMESSAGE);
        }

        ret = TCAP_PopulateLocalTx_ANSI(localTx, did, 0, 0, cdp, clp);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: LocalTx not populated for did %d",
                         did));
            free_ANSI__TCAP_ComponentSequence(seq);
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
            return (ITS_BADTCAPMESSAGE);
        }

        /* save of the qos so we can override everywhere */
        localTx->qos = dlg->u.begin.qos;
        ltid = localTx->ltid;
        rtid = localTx->rtid;
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
    case TCPPT_TC_RESP:
    case TCPPT_TC_ABORT:
        localTx = TCAP_FindLocalTx_ANSI(did);

        if (localTx == NULL)
        {
            TCAP_ERROR(("PEPSY_AssemblePDU: Missing transaction context.\n"));
             TCAP_Alarm_ANSI(1040, __FILE__, __LINE__,
                            "Dialog-Id %X PType %X",did, dlg->ptype);
  
            /* Unable to commit transaction context to Table */
            free_ANSI__TCAP_ComponentSequence(seq);
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
#if 0
        dlg->u.end.qos = localTx->qos;
#endif
        localTx->qos = dlg->u.end.qos;
        ltid = localTx->ltid;
        rtid = localTx->rtid;
        break;
    }

    TCAP_DEBUG(("PEPSY_AssemblePDU: did %d, ltid = %08x, rtid = %08x.\n", did, ltid, rtid));

    /*  Fix for LOCAL CANCEL
     *  Don't build the PDU if has to be freed for Pre Arranged End.
     */
    if (dlg->ptype == TCPPT_TC_RESP)
    {
        if (dlg->u.end.termination == TCAP_END_PREARRANGED)
        {
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_PREARRANGED_END_SENT);

            PEG_DecrPeg(ANSI_TCAP_pegs,PEG_TCAP_ACTIVE_DIALOGUE);
            PEG_DecrPeg(ANSI_TCAP_pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

            TCAP_DEBUG(("PEPSY_AssemblePDU: PreArranged-End received for did"
                         "%d.\n", did));

            if (localTx)
            {
                sharedTx = TCAP_FindTransactionContext_ANSI(localTx->ltid,
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
                    TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
                }

                TCAP_FreeLocalTx_ANSI(did);
            }

            return (ITS_SUCCESS);
        }
    }

    /*
     * Step 3. Build the PDU.
     */
    pdu = TCAP_CvtDLGToPackage_ANSI(dlg, ltid, rtid);

    if (!pdu)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Could not convert dialog to package.\n"));
        TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, "Dialog-Id %X", did);

        /* Unable to convert dialog to package */

        free_ANSI__TCAP_ComponentSequence(seq);

        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            sharedTx = TCAP_FindTransactionContext_ANSI(localTx->ltid, tidKey,
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
                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            TCAP_FreeLocalTx_ANSI(did);
        }

        return (ITS_BADTCAPMESSAGE);
    }

    if (pdu->offset != type_ANSI__TCAP_PackageType_abort &&
        pdu->un.unidirectional != NULL)
    {
        pdu->un.unidirectional->componentSequence = seq;
    }

    if (encode_ANSI__TCAP_PackageType(&pe, 1, 0, NULL, (void *)pdu)
        == NOTOK)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Could not encode package.\n"));

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
         TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, "Dialog-Id %X", did); 

        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }
        free_ANSI__TCAP_PackageType(pdu);
        return (ITS_BADTCAPMESSAGE);
    }

#if defined(LOCAL_DEBUG)
    print_ANSI__TCAP_PackageType(pe, 1, 0, NULL, pdu);
#endif

    free_ANSI__TCAP_PackageType(pdu);

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Could not encode package.\n"));

        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
         TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, "Dialog-Id %X", did); 

        return (ITS_BADTCAPMESSAGE);
    }

    if (pe)
    {
        pe_free(pe);
    }

    if (enc == NULL && len == 0)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Encode left no data.\n"));

        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
         TCAP_Alarm_ANSI(1036, __FILE__, __LINE__, "Dialog-Id %X", did); 

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
        ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_1;
    }

    if (dlg->u.uni.qos.indicator & QOSI_RET_OPT)
    {
        ies[0].param_data.protocolClass.pclass |=
            SCCP_PCLASS_RET_ON_ERR;
    }

    /*
     * ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
     * ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
     */
    if (cdp == NULL || clp == NULL)
    {
        TCAP_ERROR(("PEPSY_AssemblePDU: Missing address.\n"));

        if (localTx &&
            (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
             dlg->ptype == TCPPT_TC_QUERY_WO_PERM))
        {
            TCAP_FindAndFreeTransactionContext_ANSI(localTx->ltid,
                                                     tidKey, &tidKeyLen);
            TCAP_FreeLocalTx_ANSI(did);
        }

        /* Outgoing Dialogue - Discarding Dialogue - Invalid or Corrupted */
       

        return (ITS_BADTCAPMESSAGE);
    }

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
    memset(&ies[4].param_data.routingLabel, 0,
           sizeof(MTP3_HEADER));

    BuildRoutingLabel(dlg,
                      &ies[1].param_data.calledPartyAddr,
                      &ies[2].param_data.callingPartyAddr,
                      &ies[4].param_data.routingLabel,
                      localTx);

    ies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[4].param_length = sizeof(MTP3_HEADER);

    if (dlg->u.uni.qos.indicator & QOSI_SEQ_CTRL)
    {
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_1_SENT);

        if (dlg->u.uni.qos.indicator & QOSI_SLS_KEY)
        {
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,
                            dlg->u.uni.qos.sls_key);
        }
        else if (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
                 dlg->ptype == TCPPT_TC_QUERY_WO_PERM)
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
            MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,0);
        }
    }
    else
    {
        /* FIXME: NOT REENTRANT */
        static ITS_OCTET sls = 0;

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_0_SENT);

        MTP3_RL_SET_SLS(ies[4].param_data.routingLabel.label,sls);
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
TPCPIHandleCMPMsg_ANSI(ITS_EVENT *event)
{
    int ret;

    TCAP_DEBUG(("TPCPIHandleCMP:\n"));

    ret = MQUEUE_Enqueue(__TCAP_ANSI_primQueue, event, sizeof(ITS_EVENT));
    event->data = NULL;

    if (ret != ITS_SUCCESS)
    {
        /* Unable to Enqueue to TCAP primQueue */
        
    }

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
TPCPIHandleDIDClean_ANSI(ITS_CTXT did)
{
    LIST_Entry *entry, *next;

    MQUEUE_Lock(__TCAP_ANSI_primQueue);

    for (entry = LIST_HEAD(__TCAP_ANSI_primQueue);
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
            MQUEUE_RemoveNoLock(__TCAP_ANSI_primQueue, entry);
            ITS_Free(entry->data);
            ITS_Free(entry);
        }
    }

    MQUEUE_Unlock(__TCAP_ANSI_primQueue);

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
TPCPIHandleAPPMsg_ANSI(ITS_EVENT *event)
{
    ITS_CTXT did;
    TCAP_DLG dlg;
    ITS_SCCP_IE ies[8];
    int ieCount;
    
    TCAP_DEBUG(("TPCPIHandleAPP:\n"));

    if (event->data[0] != ITS_TCAP_DLG)
    {
        TCAP_ERROR(("TPCPIHandleAPP:  Event is not user dialog: %02x\n",
                    event->data[0]));

        /* Received Unrecognized or Invalid Event. */

        return (ITS_SUCCESS);
    }

    did = ITS_GET_CTXT(&event->data[1]);
    memcpy(&dlg, &event->data[1 + sizeof(ITS_CTXT)], sizeof(TCAP_DLG));

    /* assemble the message, send it to TRP */    
    if (AssemblePDU(did, &dlg, ies, &ieCount) == ITS_SUCCESS)
    {
        if (dlg.ptype != TCPPT_TC_RESP ||
            dlg.u.end.termination != TCAP_END_PREARRANGED)
        {
            return TRPHandleTPCPIMsg_ANSI(did, ies, ieCount);
        }
        else
        {
            return (ITS_SUCCESS);
        }
    }
    else
    {
        TCAP_ERROR(("TPCPIHandleAPP: Failed to Assemble PDU: did %04x\n",
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
TPCPIHandleTRPMsg_ANSI(ITS_SCCP_IE *ies, int ieCount, TCAP_TRANS_ENTRY *tr)
{
    /*
     * disassemble the message, send components to CMP, dlgs to user.
     * An error from this function indicates that a reject should go
     * to SCCP
     */
    TCAP_DEBUG(("TPCPIHandleTRPMsg.\n"));

    return DisassemblePDU(ies, ieCount, tr);
}
