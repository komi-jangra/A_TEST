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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.3  2007/12/29 06:58:17  bsccs2
 * LOG: Send the  NACK for already configured  route
 * LOG:
 * LOG: Revision 1.1.1.1.4.1  2007/12/29 03:59:58  ashutosh.singh
 * LOG: change for rt_add NACK for dulicate entry
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/06 05:27:44  adutta
 * LOG: MTP route pegs definition
 * LOG:
 * LOG: Revision 9.3  2005/05/04 12:06:01  yranade
 * LOG: Fix for priority based routes. PBN Issue Id: 1810.
 * LOG:
 * LOG: Revision 9.2  2005/04/05 10:35:04  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:52:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.12.2.5.8.2.6.3  2004/12/28 11:19:59  adutta
 * LOG: Check linkset pointer before comparing
 * LOG:
 * LOG: Revision 7.12.2.5.8.2.6.2  2004/12/15 15:41:15  asingh
 * LOG: Merged Kineto fixes into this
 * LOG:
 * LOG: Revision 7.12.2.5.8.2.6.1  2004/12/10 11:26:11  yranade
 * LOG: Back out 7.12.2.5.8.1.
 * LOG:
 * LOG:
 * LOG: Revision 7.12.2.5.8.2  2004/09/02 11:59:05  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.12.2.5.8.1  2004/05/03 12:29:45  ssingh
 * LOG: Bug#798; Duplicate routingKey route configuration blocked.
 * LOG:
 * LOG: Revision 7.12.2.5  2003/04/10 19:01:14  randresol
 * LOG: Fix bugs in RemEntry function
 * LOG:
 * LOG: Revision 7.12.2.4  2003/03/28 15:48:00  randresol
 * LOG: Move ROUTE_Console function $ITS_ROOT/ENGINE/src/resources.c
 * LOG:
 * LOG: Revision 7.12.2.3  2003/03/27 19:55:39  randresol
 * LOG: Add Debug Console commands for ROUTE subsystem
 * LOG:
 * LOG: Revision 7.12.2.2  2003/03/26 06:36:14  randresol
 * LOG: Increase buffer size for ROUTE_DumpSS7ToIdHashtable
 * LOG:
 * LOG: Revision 7.12.2.1  2003/02/14 07:13:50  randresol
 * LOG: Add LINK_DumpLinkInfo and Enhance dump display
 * LOG:
 * LOG: Revision 7.12  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.11  2002/12/20 20:33:14  omayor
 * LOG: Make sure the linkSet pointer is NULL for routing key routes.
 * LOG: NOTE: When adding a RKRoute always use default linkSet and linkCode. This
 * LOG: ensure that the linkSet pointer is never accessed.
 * LOG:
 * LOG: Revision 7.10  2002/12/06 23:14:02  randresol
 * LOG: Make sure we get the right link->id: invoke LINK_GetTransportId
 * LOG:
 * LOG: Revision 7.9  2002/11/09 21:35:23  randresol
 * LOG: Create ROUTE_RWLock and use ROUTE_RWLock API for lookups
 * LOG:
 * LOG: Revision 7.8  2002/10/28 18:42:51  mmiers
 * LOG: Warning removal for 64 bit platforms.
 * LOG:
 * LOG: Revision 7.7  2002/10/22 15:32:13  mmiers
 * LOG: Routing key fix
 * LOG:
 * LOG: Revision 7.6  2002/09/30 22:43:12  yranade
 * LOG: Found an ordering bug.
 * LOG:
 * LOG: Revision 7.5  2002/09/26 22:59:29  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.4  2002/09/18 20:57:37  yranade
 * LOG: Type difference
 * LOG:
 * LOG: Revision 7.3  2002/09/03 13:54:41  mmiers
 * LOG: typo
 * LOG:
 * LOG: Revision 7.2  2002/08/29 15:50:09  mmiers
 * LOG: Make add return error on duplicate, but handle that as well.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.21  2002/07/24 17:47:33  randresol
 * LOG: Fix bugs found during MTP3 redundant functionality testing
 * LOG:
 * LOG: Revision 6.20  2002/07/17 15:47:08  mmiers
 * LOG: Looks like one escaped.
 * LOG:
 * LOG: Revision 6.19  2002/07/03 19:34:22  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.18  2002/06/27 22:19:23  ssharma
 * LOG: Add family to dumps
 * LOG:
 * LOG: Revision 6.17  2002/06/23 18:12:49  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.16  2002/06/21 22:49:10  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.15  2002/06/12 19:17:22  hcho
 * LOG: Prevent linkset contains null link ptr.
 * LOG:
 * LOG: Revision 6.14  2002/06/05 19:19:47  mmiers
 * LOG: Formatting
 * LOG:
 * LOG: Revision 6.13  2002/06/03 18:44:52  hcho
 * LOG: Iterate not overwrite.
 * LOG:
 * LOG: Revision 6.12  2002/05/31 20:42:25  mmiers
 * LOG: Fixes for concerned routes
 * LOG:
 * LOG: Revision 6.11  2002/05/29 15:48:03  mmiers
 * LOG: Bit twiddling bugs noticed by Ricardo
 * LOG:
 * LOG: Revision 6.10  2002/05/20 15:39:28  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.9  2002/05/17 17:37:53  lbana
 * LOG: fix typo in ROUTE_FindRoutingKeyInfo
 * LOG:
 * LOG: Revision 6.8  2002/05/06 21:30:44  mmiers
 * LOG: Loop control variable deleted.
 * LOG:
 * LOG: Revision 6.7  2002/04/30 15:56:34  mmiers
 * LOG: Fix up for more flexibility in route selection.
 * LOG:
 * LOG: Revision 6.6  2002/04/29 22:00:31  randresol
 * LOG: Various bug fixes in links and routes in DSM
 * LOG:
 * LOG: Revision 6.5  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/03/28 00:05:06  mmiers
 * LOG: Performance optimizations.
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:08:43  randresol
 * LOG: The queues crBuf, cocbBuf, rtrvBuf and routes are now in DSM
 * LOG:
 * LOG: Revision 6.2  2002/03/08 22:55:06  mmiers
 * LOG: first pass of routing in DSM
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.49.2.2  2002/05/06 21:32:50  hcho
 * LOG: Delete loop control variable.
 * LOG:
 * LOG: Revision 5.49.2.1  2002/04/09 22:07:44  sjaddu
 * LOG: Fix the wildcarding error found during ISUP integration (Mitch)
 * LOG:
 * LOG: Revision 5.49  2002/02/27 19:25:05  mmiers
 * LOG: A blivet bug that only showed on Solaris Forte when optimized.
 * LOG:
 * LOG: Revision 5.48  2002/02/25 22:54:00  mmiers
 * LOG: Issue error if user config is screwed.
 * LOG:
 * LOG: Revision 5.47  2002/01/10 20:16:02  mmiers
 * LOG: Remove some fixme's that have been.
 * LOG:
 * LOG: Revision 5.46  2001/12/04 00:16:34  mmiers
 * LOG: Get route grouping to work.
 * LOG:
 * LOG: Revision 5.45  2001/11/21 21:51:30  hdivoux
 * LOG: Change for iterate hashtable function name.
 * LOG:
 * LOG: Revision 5.44  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.43  2001/11/08 16:16:12  mmiers
 * LOG: Make sure things compile without its_bc.h.  Fix MutexGuard.
 * LOG:
 * LOG: Revision 5.42  2001/11/08 01:20:52  mmiers
 * LOG: Actually set the destination info.
 * LOG:
 * LOG: Revision 5.41  2001/11/01 21:00:15  mmiers
 * LOG: Rethink direct routing.
 * LOG:
 * LOG: Revision 5.40  2001/11/01 01:40:29  mmiers
 * LOG: Debugging changeback.
 * LOG:
 * LOG: Revision 5.39  2001/10/25 16:50:51  mmiers
 * LOG: Return the index even when the route was explicit.
 * LOG:
 * LOG: Revision 5.38  2001/10/24 20:55:37  mmiers
 * LOG: Put the current route logic in.
 * LOG:
 * LOG: Revision 5.37  2001/10/24 17:33:40  mmiers
 * LOG: Deep thought about current routes, and queue puts.
 * LOG:
 * LOG: Revision 5.36  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.35  2001/10/18 20:02:52  mmiers
 * LOG: Avoid many version defines, destination parsing.
 * LOG:
 * LOG: Revision 5.34  2001/10/18 19:01:09  mmiers
 * LOG: Rework the link/route division.  It's easier if they're in
 * LOG: a single table.
 * LOG:
 * LOG: Revision 5.33  2001/10/17 22:03:47  mmiers
 * LOG: Remove some bugs I just added.
 * LOG:
 * LOG: Revision 5.32  2001/10/17 20:28:07  mmiers
 * LOG: More work on bit rotation
 * LOG:
 * LOG: Revision 5.31  2001/10/17 18:20:58  mmiers
 * LOG: Convert routing to use link information.
 * LOG:
 * LOG: Revision 5.30  2001/10/16 22:45:42  mmiers
 * LOG: Remove SLS shift.  It's fairly useless, and if it belongs
 * LOG: anywhere it's on the link set.
 * LOG:
 * LOG: Revision 5.29  2001/10/16 22:18:37  mmiers
 * LOG: Export the SLS bit rotation functions.
 * LOG:
 * LOG: Revision 5.28  2001/10/05 00:51:24  mmiers
 * LOG: Add fields for CO/CB/CR.
 * LOG:
 * LOG: Revision 5.27  2001/10/04 21:30:10  mmiers
 * LOG: More bug fixing.
 * LOG:
 * LOG: Revision 5.26  2001/10/03 18:54:16  mmiers
 * LOG: A couple of thinko fixes.
 * LOG:
 * LOG: Revision 5.25  2001/10/02 22:36:18  mmiers
 * LOG: Routing bug.
 * LOG:
 * LOG: Revision 5.24  2001/10/02 21:44:25  mmiers
 * LOG: dead route style removal
 * LOG:
 * LOG: Revision 5.23  2001/10/01 20:12:27  mmiers
 * LOG: struct rename
 * LOG:
 * LOG: Revision 5.22  2001/09/28 21:32:32  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.21  2001/09/25 22:48:17  mmiers
 * LOG: Modifications for SCMG routing.
 * LOG:
 * LOG: Revision 5.20  2001/09/21 00:31:37  mmiers
 * LOG: Add back pointer from route to destination.
 * LOG:
 * LOG: Revision 5.19  2001/09/06 20:04:33  mmiers
 * LOG: Update.
 * LOG:
 * LOG: Revision 5.18  2001/08/31 22:13:23  mmiers
 * LOG: IsUp/IsAllowed handling.
 * LOG:
 * LOG: Revision 5.17  2001/08/30 18:47:32  mmiers
 * LOG: Add match style ranges.
 * LOG:
 * LOG: Revision 5.16  2001/08/30 00:17:50  mmiers
 * LOG: More cleanup.  Work needs to be done on the match ranges
 * LOG: allowed for specific types.  A unit tester is really needed
 * LOG: for this thing at this point.
 * LOG:
 * LOG: Revision 5.15  2001/08/29 22:22:11  mmiers
 * LOG: order sort the masks.
 * LOG:
 * LOG: Revision 5.14  2001/08/29 17:26:54  mmiers
 * LOG: Add maskable routing.  Bug fix for SCTP clients.  Abort if
 * LOG: timer context too large.
 * LOG:
 * LOG: Revision 5.13  2001/08/28 20:47:01  mmiers
 * LOG: More routing.
 * LOG:
 * LOG: Revision 5.12  2001/08/28 00:33:01  mmiers
 * LOG: First pass at the link selector.
 * LOG:
 * LOG: Revision 5.11  2001/08/24 21:09:32  mmiers
 * LOG: Stabilize the routing interface.  Still need to write the link
 * LOG: selection logic.
 * LOG:
 * LOG: Revision 5.10  2001/08/24 17:10:25  mmiers
 * LOG: Routing, take three.
 * LOG:
 * LOG: Revision 5.9  2001/08/23 22:55:33  mmiers
 * LOG: Now routing is *really* messed up.  For MTP3 you have to qualify
 * LOG: a route by the destination *and* the linkset to reach it by.
 * LOG: None of the routing code reflects this yet.
 * LOG:
 * LOG: Revision 5.8  2001/08/21 20:21:54  mmiers
 * LOG: More routing changes for the stack.
 * LOG:
 * LOG: Revision 5.7  2001/08/21 00:03:22  mmiers
 * LOG: Build bug, dead var.
 * LOG:
 * LOG: Revision 5.6  2001/08/20 23:28:54  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.5  2001/08/17 22:15:43  mmiers
 * LOG: Special case routing key routes.
 * LOG:
 * LOG: Revision 5.4  2001/08/17 22:08:57  mmiers
 * LOG: Never route to duplicated or routing key routes.
 * LOG:
 * LOG: Revision 5.3  2001/08/17 21:08:56  mmiers
 * LOG: Add LINKSET class record.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/15 20:48:54  mmiers
 * LOG: Bad allocation size.
 * LOG:
 * LOG: Revision 4.2  2001/08/14 15:26:19  mmiers
 * LOG: Start making room for MTP3.
 * LOG:
 * LOG: Revision 4.1  2001/08/13 22:23:04  mmiers
 * LOG: Split routing into two subsystems.
 * LOG:
 * LOG: Revision 4.9  2001/06/25 17:05:59  mmiers
 * LOG: Must allow exact matches when not doing route selection.
 * LOG:
 * LOG: Revision 4.8  2001/06/22 00:03:30  mmiers
 * LOG: Put string in right place
 * LOG:
 * LOG: Revision 4.7  2001/06/22 00:00:50  mmiers
 * LOG: More bugs.
 * LOG:
 * LOG: Revision 4.6  2001/06/21 23:52:50  mmiers
 * LOG: Debug of print
 * LOG:
 * LOG: Revision 4.5  2001/06/21 00:54:40  mmiers
 * LOG: Re-enable printing.
 * LOG:
 * LOG: Revision 4.4  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.3  2001/06/19 21:12:35  mmiers
 * LOG: Use id when setting isUp.
 * LOG:
 * LOG: Revision 4.2  2001/06/08 21:04:57  mmiers
 * LOG: Fix missing send for application logic.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.34  2001/04/30 20:30:41  mmiers
 * LOG: Olivier spotted a bug (off by one) adding routes.
 * LOG:
 * LOG: Revision 3.33  2001/03/30 18:44:37  mmiers
 * LOG: Off by one bug, bad start for qsort.
 * LOG:
 * LOG: Revision 3.32  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.31  2001/03/02 23:35:44  mmiers
 * LOG: Couple of routing bug fixes.
 * LOG:
 * LOG: Revision 3.30  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.29  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.28  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.27  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.26  2001/01/20 00:05:39  mmiers
 * LOG: Tweaks.
 * LOG:
 * LOG: Revision 3.25  2001/01/11 21:19:26  omayor
 * LOG: Remove typo in adding the route.
 * LOG:
 * LOG: Revision 3.24  2000/12/29 17:35:01  mmiers
 * LOG: This should work
 * LOG:
 * LOG: Revision 3.23  2000/12/29 17:15:11  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 3.22  2000/12/29 16:42:04  mmiers
 * LOG: Change the flag settings.
 * LOG:
 * LOG: Revision 3.21  2000/12/22 00:36:26  mmiers
 * LOG: First message through
 * LOG:
 * LOG: Revision 3.20  2000/12/22 00:09:31  mmiers
 * LOG: Alter defaults a bit
 * LOG:
 * LOG: Revision 3.19  2000/12/21 23:50:51  mmiers
 * LOG: Traces & bugs
 * LOG:
 * LOG: Revision 3.18  2000/12/21 23:08:45  mmiers
 * LOG: Trace
 * LOG:
 * LOG: Revision 3.17  2000/12/21 23:01:45  mmiers
 * LOG: Missing unlock
 * LOG:
 * LOG: Revision 3.16  2000/12/21 22:55:38  mmiers
 * LOG: Better logic
 * LOG:
 * LOG: Revision 3.15  2000/12/21 22:52:07  mmiers
 * LOG: Alter logic to look more like PR3
 * LOG:
 * LOG: Revision 3.14  2000/12/21 22:36:49  mmiers
 * LOG: Trace
 * LOG:
 * LOG: Revision 3.13  2000/12/21 22:33:31  mmiers
 * LOG: Trace
 * LOG:
 * LOG: Revision 3.12  2000/12/19 19:01:10  mmiers
 * LOG: Off by one error
 * LOG:
 * LOG: Revision 3.11  2000/12/19 18:17:30  mmiers
 * LOG: Get the equals right
 * LOG:
 * LOG: Revision 3.10  2000/12/05 17:01:43  mmiers
 * LOG: Typos/trace
 * LOG:
 * LOG: Revision 3.9  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.8  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.17  2000/11/09 23:04:26  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.16  2000/11/09 01:32:35  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.15  2000/11/09 00:48:42  mmiers
 * LOG: Today's installment.  Also an IMAL fix.
 * LOG:
 * LOG: Revision 3.14  2000/11/08 16:58:53  mmiers
 * LOG: Pseudocode.
 * LOG:
 * LOG: Revision 3.13  2000/11/07 23:35:01  mmiers
 * LOG: Think about with and without event a bit more.
 * LOG:
 * LOG: Revision 3.12  2000/11/07 22:55:45  mmiers
 * LOG: Structure's in place.  Fill in the gaps.
 * LOG:
 * LOG: Revision 3.11  2000/11/06 23:32:21  mmiers
 * LOG: More work on the routing changes.
 * LOG:
 * LOG: Revision 3.10  2000/11/03 22:51:02  mmiers
 * LOG: More work on the routing changes.
 * LOG:
 * LOG: Revision 3.9  2000/11/03 21:57:36  mmiers
 * LOG: Start working on the routing changes.
 * LOG:
 * LOG: Revision 3.8  2000/10/09 16:53:19  mmiers
 * LOG: Set up for testing...
 * LOG:
 * LOG: Revision 3.7  2000/10/05 23:05:34  mmiers
 * LOG: New routing scheme.
 * LOG:
 * LOG: Revision 3.6  2000/09/25 20:09:27  mmiers
 * LOG: About done.  Need to convert route.c itself now.
 * LOG:
 * LOG: Revision 3.5  2000/09/25 19:56:52  mmiers
 * LOG: Set up for new route style.
 * LOG:
 * LOG: Revision 3.4  2000/09/14 21:03:48  mmiers
 * LOG: Fix up route deletion (link set safety).
 * LOG:
 * LOG: Revision 3.3  2000/09/13 20:35:15  mmiers
 * LOG: Update useNext when deleting routes.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:41  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.18  2000/07/05 22:25:37  rsonak
 * LOG:
 * LOG: route: read from global section, not ini name
 * LOG: kasock: add trace saying which down transport sent sltm
 * LOG: iptrans: add debug
 * LOG:
 * LOG: Revision 2.17  2000/07/04 00:14:57  rsonak
 * LOG:
 * LOG:
 * LOG: Debug, bad route delete, transport route ls/lc collection
 * LOG:
 * LOG: Revision 2.16  2000/06/28 22:52:20  mmiers
 * LOG:
 * LOG:
 * LOG: Modify routing mechanism to select by link.
 * LOG:
 * LOG: Revision 2.15  2000/06/22 23:10:46  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 2.14  2000/06/17 03:42:32  mmiers
 * LOG:
 * LOG:
 * LOG: I *think* I found the routing problem.  We weren't circularizing the
 * LOG: list.
 * LOG:
 * LOG: Revision 2.13  2000/06/17 02:21:34  rsonak
 * LOG:
 * LOG:
 * LOG: Debug info.
 * LOG:
 * LOG: Revision 2.12  2000/06/17 01:19:56  rsonak
 * LOG:
 * LOG:
 * LOG: Integration bug hunting (follow nextLink).
 * LOG:
 * LOG: Revision 2.11  2000/06/02 02:05:17  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.10  2000/05/16 00:05:21  mmiers
 * LOG:
 * LOG:
 * LOG: Add concept of route by linkset to routing table.
 * LOG:
 * LOG: Revision 2.9  2000/05/11 22:17:25  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for link sets.
 * LOG:
 * LOG: Revision 2.8  2000/02/14 19:17:44  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.7  2000/02/04 00:27:55  mmiers
 * LOG:
 * LOG:
 * LOG: ID check should look at PC AND SSN.
 * LOG:
 * LOG: Revision 2.6  2000/02/02 02:20:51  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.5  2000/01/26 03:04:10  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.4  2000/01/25 02:36:17  mmiers
 * LOG:
 * LOG:
 * LOG: UNIX update.
 * LOG:
 * LOG: Revision 2.3  2000/01/21 22:48:15  mmiers
 * LOG:
 * LOG: Had to add separate up/allowed variables.
 * LOG:
 * LOG: Revision 2.2  2000/01/21 22:14:44  mmiers
 * LOG:
 * LOG: Checkpoint changes.  Include routing behavior changes for Rajesh.
 * LOG:
 * LOG: Revision 2.1  2000/01/20 17:47:42  mmiers
 * LOG:
 * LOG: Forward link the routes for V7M.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:55  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.43  1999/09/17 16:44:51  mmiers
 * LOG:
 * LOG:
 * LOG: More information for route trace.
 * LOG:
 * LOG: Revision 1.42  1999/08/30 18:15:31  mmiers
 * LOG:
 * LOG:
 * LOG: Correct printing functions.
 * LOG:
 * LOG: Revision 1.41  1999/08/26 15:07:23  mmiers
 * LOG:
 * LOG:
 * LOG: Add a predicate for determination of the default app selector.
 * LOG:
 * LOG: Revision 1.40  1999/08/11 17:30:59  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.39  1998/12/18 01:14:29  rsonak
 * LOG: Fix a mutex release problem that could lock a process.
 * LOG:
 * LOG: Revision 1.38  1998/11/19 02:17:32  mmiers
 * LOG: Straighten out a few potential bugs.
 * LOG:
 * LOG: Revision 1.37  1998/11/19 00:36:28  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.36  1998/11/17 03:30:39  mmiers
 * LOG: Deal with gethostbyaddr() when appropriate.
 * LOG:
 * LOG: Revision 1.35  1998/11/12 00:09:14  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.34  1998/11/11 00:44:48  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.33  1998/11/04 02:47:29  mmiers
 * LOG: Remove ITS_SS7_LOCAL_ROUTE, it is irrelevant, we don't do that.
 * LOG: Add congestion callback list, it will be used for SS7.
 * LOG: Update TODO to reflect what needs to be added.
 * LOG:
 * LOG: Revision 1.32  1998/11/03 02:56:17  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.31  1998/10/05 15:01:36  whu
 * LOG: Finally found the "race condition" bug.  It wasn't.  The entries for
 * LOG: application routes were being corrupted when the application thread
 * LOG: terminated (ROUTE_Clean() bug).
 * LOG:
 * LOG: Revision 1.30  1998/10/01 20:00:29  mmiers
 * LOG: Capitalization errorr.
 * LOG:
 * LOG: Revision 1.29  1998/10/01 17:39:52  mmiers
 * LOG: Try to find the race condition with routing.
 * LOG:
 * LOG: Revision 1.28  1998/10/01 00:01:53  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.27  1998/09/29 21:38:49  mmiers
 * LOG: Bug fixes for new SCCP support.
 * LOG:
 * LOG: Revision 1.26  1998/09/29 20:22:34  mmiers
 * LOG: Add route state into the picture.
 * LOG:
 * LOG: Revision 1.25  1998/09/28 22:42:44  mmiers
 * LOG: More work enhancing MTP3-ish support.
 * LOG:
 * LOG: Revision 1.24  1998/09/28 22:09:40  mmiers
 * LOG: More support for intelligent transports.
 * LOG:
 * LOG: Revision 1.23  1998/09/26 02:47:01  mmiers
 * LOG: Linux code base cleanup.
 * LOG:
 * LOG: Revision 1.22  1998/09/22 18:51:20  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.21  1998/09/22 17:28:31  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.20  1998/09/16 15:50:14  whu
 * LOG: Found a long standing bug in the routing table where context was not
 * LOG: being set correctly after deleting an entry.  This applied to both
 * LOG: application and route entries.
 * LOG:
 * LOG: Revision 1.19  1998/08/27 23:28:14  hdivoux
 * LOG: Added functions to dump hashtables.
 * LOG:
 * LOG: Revision 1.18  1998/08/03 20:34:18  mmiers
 * LOG: Add cleaner functionality to ITS_Terminate() for transient transports.
 * LOG:
 * LOG: Revision 1.17  1998/07/30 14:52:38  mmiers
 * LOG: Duplicate update.  Added functions so that an app can send an event
 * LOG: without worry of the destination disappearing between lookup and
 * LOG: transmission.
 * LOG:
 * LOG: Revision 1.16  1998/07/17 20:18:03  ahanda
 * LOG: Fixe for Route Delete Entry
 * LOG:
 * LOG: Revision 1.15  1998/07/03 19:41:43  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.14  1998/07/02 23:12:30  hdivoux
 * LOG: Minor correction.
 * LOG:
 * LOG: Revision 1.13  1998/07/01 23:34:53  mmiers
 * LOG: Modify the route selection interface slightly.
 * LOG:
 * LOG: Revision 1.12  1998/06/25 00:22:08  ahanda
 * LOG: Allow for pad bytes in the context structure.
 * LOG:
 * LOG: Revision 1.11  1998/06/23 22:02:46  hdivoux
 * LOG: Minor correction.
 * LOG:
 * LOG: Revision 1.10  1998/06/23 00:36:12  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/06/18 23:39:34  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.8  1998/06/16 23:41:01  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.7  1998/06/16 21:52:12  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.6  1998/06/03 19:00:49  mmiers
 * LOG: Remove a flag and a callback pointer from global scope.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 16:35:34  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.4  1998/05/28 17:28:43  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 * LOG: Revision 1.3  1998/05/28 02:59:13  mmiers
 * LOG: More documentation, make application route selection single threaded,
 * LOG: and remove nasty tab characters from StandardHeaders.
 * LOG:
 * LOG: Revision 1.2  1998/05/27 22:08:08  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.1  1998/05/20 21:31:37  mmiers
 * LOG: Reimplement this in C for performance.
 * LOG:
 * LOG: Revision 1.5  1998/05/20 17:06:10  mmiers
 * LOG: Get the namespace thing right.  You must include its++.h if
 * LOG: you want to use the its namespace.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 19:59:45  ahanda
 * LOG: Added the Application Routing Code
 * LOG:
 * LOG: Revision 1.3  1998/05/19 17:11:56  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.2  1998/05/05 20:24:12  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/05/01 00:24:38  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:07  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <its.h>
#include <its_app.h>
#include <its_route.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_rwlock.h>
#include <its_transports.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_route_rwlock.h>

#ident "$Id: its_ss7_route.c,v 1.4 2008-01-02 13:09:37 bsccs2 Exp $"

/*
 * entry table control variables
 */
#define INIT_MAX_ENT            8
#define LINK_SET_GROWTH_FACTOR  2

/*
 * bit shifting defines
 */
#define UPPER_BITS      0xE0U
#define MIDDLE_BITS     0x1EU
#define LOWER_BITS      0x01U
#define UPPER_SHIFT     1
#define MIDDLE_SHIFT    1
#define LOWER_SHIFT     4

/*
 * only used locally
 */
#define ROUTE_FAMILY_MASK   0x3FU

/*
 * gating
 *
 * Addenda:  we've converted to a RWLOCK to avoid latency issues.  Side
 * effect is table modifiers *must* lock exclusive, while table readers
 * *should* lock shared.  Note: further enhancement: writers could lock
 * shared until they find out if a particular entry is present, then
 * upgrade the lock to exclusive.  Too much work for now.
 */
static ITS_RWLOCK  selectorGate;

static ROUTE_SS7Selector   ss7Select = ROUTE_SendToSS7;

/*
 * printing help
 */
static char *types[] =
{
    "Don't care",
    "Local route",
    "Remote route",
    "Concerned route",
    "SCMG Duplicate route",
    "Routing key route"
};

#define TYPE_TO_TEXT(x)                                   \
    (((int)(x) < 0 || (int)(x) > (int)ROUTING_KEY_ROUTE)  \
        ? "Bad"                                           \
        : types[(int)(x)])

static char *styles[] =
{
    "DPC, NI",
    "DPC, OPC, NI",
    "DPC, SIO",
    "DPC, OPC, SIO",
    "DPC, SIO, SSN Range",
    "DPC, SIO, CIC Range",
    "DPC, OPC, SIO, SSN Range",
    "DPC, OPC, SIO, CIC Range",
    "DPC, SIO, SSN",
    "DPC, SIO, CIC",
    "DPC, OPC, SIO, SSN",
    "DPC, OPC, SIO, CIC",
    NULL
};

#define STYLE_TO_TEXT(x)                                 \
    (((int)(x) < 0 || (int)(x) > (int)ROUTE_DPC_UDEF)    \
        ? "Bad"                                          \
        : styles[(int)(x)])

static char *families[] =
{
    "ANSI",
    "ITU",
    "CHINA",
    "JAPAN"
};

#define FAMILY_TO_TEXT(x)                                 \
    (((int)(x) < 0 || (int)(x) > (int)FAMILY_JAPAN)       \
        ? "Bad"                                           \
        : families[(int)(x)])

/*
 * array for masking.
 */
#define ROUTE_MAX_MASKS 32

static ITS_UINT masks[ROUTE_MAX_MASKS] =
{
    ITS_SS7_DEFAULT_ROUTE_MASK,
    0
};
static ITS_UINT numMasks = 1;

/*
 * entry types
 */
#define ENT_TYPE_RKEY   0x0001
#define ENT_TYPE_ROUTE  0x0002
#define ENT_TYPE_RCONT  0x0003

/*
 * key types for DSM.
 */
typedef struct
{
    ITS_UINT    type;
    ITS_UINT    niDPC;
    ITS_UINT    numEntries;
}
ROUTE_EntryArrayKey;

typedef struct
{
    ITS_UINT    type;
    ITS_UINT    niDPC;
    ITS_UINT    fakeIndex;
}
ROUTE_EntryKey;

#define INode_BT  20002/*same value used at ISIL*/
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Lock the relevent routing tables
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_LockTable()
{
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

#if 0
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_ROUTE_ARRAYS) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_ROUTES) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return (ITS_EBADMUTEX);
    }

#endif

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Lock the relevent routing tables
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_UnlockTable()
{
/*
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);
*/
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dump a route match info record to trace.
 *
 *  Input Parameters:
 *      rinfo - the routing tuple
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DumpRouteMatchInfo(ROUTE_MatchInfo *rinfo)
{
#if !defined(DISABLE_TRACE)
    switch (rinfo->basic.style)
    {
    case ROUTE_DPC_NI:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x ni %02x\n",
                         styles[ROUTE_DPC_NI], rinfo->basic.dpc,
                         rinfo->basic.criteria.sio));
        break;

    case ROUTE_DPC_SIO:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x sio %02x\n",
                         styles[ROUTE_DPC_SIO], rinfo->basic.dpc,
                         rinfo->basic.criteria.sio));
        break;

    case ROUTE_DPC_SIO_SSN_RANGE:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x sio %02x range %d:%d\n",
                         styles[ROUTE_DPC_SIO_SSN_RANGE], rinfo->basic.dpc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.range.begin,
                         rinfo->basic.criteria.range.end));
        break;

    case ROUTE_DPC_SIO_CIC_RANGE:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x sio %02x range %d:%d\n",
                         styles[ROUTE_DPC_SIO_CIC_RANGE], rinfo->basic.dpc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.range.begin,
                         rinfo->basic.criteria.range.end));
        break;

    case ROUTE_DPC_SIO_SSN:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x sio %02x ssn %02x\n",
                         styles[ROUTE_DPC_SIO_SSN], rinfo->basic.dpc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.ssn));
        break;

    case ROUTE_DPC_SIO_CIC:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x sio %02x cic %04x\n",
                         styles[ROUTE_DPC_SIO_CIC], rinfo->basic.dpc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.cic));
        break;

    case ROUTE_DPC_OPC_NI:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x opc %08x ni %02x\n",
                         styles[ROUTE_DPC_OPC_NI], rinfo->basic.dpc,
                         rinfo->basic.criteria.opc,
                         rinfo->basic.criteria.sio));
        break;

    case ROUTE_DPC_OPC_SIO:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x opc %08x sio %02x\n",
                         styles[ROUTE_DPC_OPC_SIO], rinfo->basic.dpc,
                         rinfo->basic.criteria.opc,
                         rinfo->basic.criteria.sio));
        break;

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x opc %08x sio %02x "
                         "range %d:%d\n",
                         styles[ROUTE_DPC_OPC_SIO_SSN_RANGE], rinfo->basic.dpc,
                         rinfo->basic.criteria.opc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.range.begin,
                         rinfo->basic.criteria.range.end));
        break;

    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x opc %08x sio %02x "
                         "range %d:%d\n",
                         styles[ROUTE_DPC_OPC_SIO_CIC_RANGE], rinfo->basic.dpc,
                         rinfo->basic.criteria.opc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.range.begin,
                         rinfo->basic.criteria.range.end));
        break;

    case ROUTE_DPC_OPC_SIO_SSN:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x opc %08x sio %02x "
                         "ssn %02x\n",
                         styles[ROUTE_DPC_OPC_SIO_SSN], rinfo->basic.dpc,
                         rinfo->basic.criteria.opc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.ssn));
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x opc %08x sio %02x "
                         "cic %04x\n",
                         styles[ROUTE_DPC_OPC_SIO_CIC], rinfo->basic.dpc,
                         rinfo->basic.criteria.opc,
                         rinfo->basic.criteria.sio,
                         rinfo->basic.criteria.cic));
        break;

    case ROUTE_DPC_UDEF:
        ITS_TRACE_DEBUG(("RINFO: style %s dpc %08x\n",
                         styles[ROUTE_DPC_UDEF], rinfo->basic.dpc));
        break;

    default:
        break;
    }

    ITS_TRACE_DEBUG(("RINFO: linkSet %d linkCode %d priority %d sls %d\n",
                     rinfo->linkSet, rinfo->linkCode,
                     rinfo->priority, rinfo->sls));
#endif
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dump a route match info record to trace.
 *
 *  Input Parameters:
 *      rinfo - the routing tuple
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DumpRouteInfo(ROUTE_Info *rinfo)
{
    ROUTE_MatchInfo match;

    match.basic.type = rinfo->basic.type;
    match.basic.style = rinfo->basic.style;
    match.basic.family = rinfo->basic.family;
    match.basic.dpc = rinfo->basic.dpc;
    match.basic.mask = rinfo->basic.mask;
    match.basic.criteria = rinfo->basic.criteria;
    if (rinfo->linkSet)
    {
        match.linkSet = rinfo->linkSet->linkSet;
    }
    else
    {
        match.linkSet = ITS_SS7_DEFAULT_LINK_SET;
    }
    match.priority = rinfo->priority;

    DumpRouteMatchInfo(&match);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Qualify the link information for a route
 *
 *  Input Parameters:
 *      rinfo - the routing tuple
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
QualifyLink(SS7_Destination *ent, int start, int finish,
            int *whichLinkCode, ROUTE_MatchInfo *copy)
{
    int i, j;

    if (copy->linkSet != ITS_SS7_DEFAULT_LINK_SET)
    {
        for (i = start; i <= finish; i++)
        {
            if (ent->entries[i]->linkSet->linkSet == copy->linkSet)
            {
                if (copy->linkCode != ITS_SS7_DEFAULT_LINK_CODE)
                {
                    for (j = 0; j < (int)ent->entries[i]->linkSet->numLinks; j++)
                    {
                        if (ent->entries[i]->linkSet->links[j]->linkCode ==
                            copy->linkCode)
                        {
                            *whichLinkCode = j;

                            return (i);
                        }
                    }

                    if (j == (int)ent->entries[i]->linkSet->numLinks)
                    {
                        return (-1);
                    }
                }
                else
                {
                    *whichLinkCode = 0;

                    return (i);
                }
            }
        }

        if (i > finish)
        {
            *whichLinkCode = -1;

            return (-1);
        }
    }
    else
    {
        for (i = start; i <= finish; i++)
        {
            if (copy->linkCode != ITS_SS7_DEFAULT_LINK_CODE)
            {
                for (j = 0; j < (int)ent->entries[i]->linkSet->numLinks; j++)
                {
                    if (ent->entries[i]->linkSet->links[j]->linkCode ==
                        copy->linkCode)
                    {
                        *whichLinkCode = j;

                        return (i);
                    }
                }
            }
            else
            {
                *whichLinkCode = 0;

                return (i);
            }
        }

        if (i > finish)
        {
            *whichLinkCode = -1;

            return (-1);
        }
    }

    /* NOTREACHED */
    return (-1);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the best match for a given routing tuple
 *
 *  Input Parameters:
 *      rinfo - the routing tuple
 *      ev - (possibly) the event the tuple came from (or NULL)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The first best match route record, or NULL if no match found.
 *
 *  Notes:
 *      The lock must be held before calling this function.
 *      Only a subset of the routing styles are valid for the info
 *      passed.  These are:
 *          DPC_OPC_SIO_SSN
 *          DPC_OPC_SIO_CIC
 *          DPC_OPC_SIO
 *          DPC_SIO_SSN
 *          DPC_SIO_CIC
 *          DPC_SIO
 *          DPC_ONLY
 *      All other types simply aren't valid here.
 *
 *      This does not guarantee that the route will be up.  Only that
 *      if it's present it's returned.
 *
 *  See Also:
 ****************************************************************************/
static SS7_Destination *
FindBestMatchOfEntry(SS7_Destination *ent, ROUTE_MatchInfo *rinfo,
                     int *whichEntry, int *firstMatch, int *lastMatch,
                     int *whichLinkCode,
                     ITS_BOOLEAN rangeAllowed, ITS_BOOLEAN routingKeyAllowed)
{
    ROUTE_MatchInfo copy;
    int i, finish;
    ITS_UINT opc, dpc, mask;
    ITS_OCTET ssn, sio, linkSet;
    ITS_USHORT cic;

    *whichEntry = -1;
    *whichLinkCode = -1;
    *firstMatch = -1;
    *lastMatch = -1;

    ITS_TRACE_DEBUG(("FindBestMatchOfEntry\n"));

    DumpRouteMatchInfo(rinfo);

    /* only certain types can be handled here */
    if (!rangeAllowed)
    {
        switch (rinfo->basic.style)
        {
        case ROUTE_DPC_NI:
        case ROUTE_DPC_OPC_NI:
        case ROUTE_DPC_SIO:
        case ROUTE_DPC_OPC_SIO:
            break;

        case ROUTE_DPC_SIO_SSN:
        case ROUTE_DPC_SIO_CIC:
            break;

        case ROUTE_DPC_OPC_SIO_SSN:
        case ROUTE_DPC_OPC_SIO_CIC:
            break;

        default:
            ITS_TRACE_DEBUG(("Bad style\n"));

            return (NULL);
        }
    }

    /*
     * "the beast"
     */
    for (i = (int)ent->numEntries - 1; i >= 0; i--)
    {
        ROUTE_Info *ri = ent->entries[i];

        /* never select CONCERNED_ROUTEs, DUPLICATED, or ROUTING_KEY */
        if (ri->basic.type == CONCERNED_ROUTE ||
            ri->basic.type == DUPLICATED_ROUTE)
        {
            continue;
        }

        /* only allow routing key routes in special circumstances */
        if (!routingKeyAllowed &&
            ri->basic.type == ROUTING_KEY_ROUTE)
        {
            continue;
        }

        /*
         * if the route has no transports ignore it.
         */
        /*
         * anything past this point has to have a link set,
         * except for routing key routes
         */
        if (!routingKeyAllowed)
        {
            ITS_C_ASSERT(ri->linkSet != NULL);
        }

        /* eliminate wildcards from consideration of the ent */
        dpc = ri->basic.dpc;
        mask = ri->basic.mask;

        sio = ri->basic.criteria.sio;
        if (sio == ITS_SS7_DEFAULT_SIO)
        {
            sio = rinfo->basic.criteria.sio;
        }

        opc = ri->basic.criteria.opc;
        if (opc == ITS_SS7_DEFAULT_POINT_CODE)
        {
            opc = rinfo->basic.criteria.opc;
        }

        ssn = ri->basic.criteria.ssn;
        if (ssn == ITS_SS7_DEFAULT_SSN)
        {
            ssn = rinfo->basic.criteria.ssn;
        }

        cic = ri->basic.criteria.cic;
        if (cic == ITS_SS7_DEFAULT_CIC)
        {
            cic = rinfo->basic.criteria.cic;
        }

        if (ri->linkSet)
        {
            linkSet = ri->linkSet->linkSet;
            if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
            {
                linkSet = rinfo->linkSet;
            }
        }
        else
        {
            linkSet = ITS_SS7_DEFAULT_LINK_SET;
        }

        /* now eliminate wildcards from the matcher */
        copy = *rinfo;

        if (copy.basic.criteria.opc == ITS_SS7_DEFAULT_POINT_CODE)
        {
            copy.basic.criteria.opc = opc;
        }

        if (copy.basic.criteria.sio == ITS_SS7_DEFAULT_SIO)
        {
            copy.basic.criteria.sio = sio;
        }

        if (copy.basic.criteria.ssn == ITS_SS7_DEFAULT_SSN)
        {
            copy.basic.criteria.ssn = ssn;
        }

        if (copy.basic.criteria.cic == ITS_SS7_DEFAULT_CIC)
        {
            copy.basic.criteria.cic = cic;
        }

        if (copy.linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            copy.linkSet = linkSet;
        }

        /* ok, figure it out. */
        switch (ri->basic.style)
        {
        case ROUTE_DPC_UDEF:
            /* this isn't valid here */
            break;

        case ROUTE_DPC_NI:
            if ((copy.basic.style == ROUTE_DPC_NI ||
                 copy.basic.style == ROUTE_DPC_OPC_NI) &&
                (copy.basic.dpc & mask) == dpc &&
                (copy.basic.criteria.sio & ROUTE_NI_MASK) == sio)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if ((copy.basic.criteria.sio & ROUTE_NI_MASK) != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_OPC_NI:
            if (copy.basic.style == ROUTE_DPC_OPC_NI &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.opc == opc &&
                (copy.basic.criteria.sio & ROUTE_NI_MASK) == sio)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    opc = pri->basic.criteria.opc;
                    if (opc == ITS_SS7_DEFAULT_POINT_CODE)
                    {
                        opc = rinfo->basic.criteria.opc;
                    }

                    if (copy.basic.criteria.opc != opc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if ((copy.basic.criteria.sio & ROUTE_NI_MASK) != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_SIO:
            if ((copy.basic.style == ROUTE_DPC_SIO ||
                 copy.basic.style == ROUTE_DPC_OPC_SIO) &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.sio == sio)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);
                return (ent);
            }
            break;

        case ROUTE_DPC_OPC_SIO:
            if (copy.basic.style == ROUTE_DPC_OPC_SIO &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.opc == opc &&
                copy.basic.criteria.sio == sio)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    opc = pri->basic.criteria.opc;
                    if (opc == ITS_SS7_DEFAULT_POINT_CODE)
                    {
                        opc = rinfo->basic.criteria.opc;
                    }

                    if (copy.basic.criteria.opc != opc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_SIO_SSN:
            if ((copy.basic.style == ROUTE_DPC_SIO_SSN ||
                 copy.basic.style == ROUTE_DPC_OPC_SIO_SSN) &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.ssn == ssn)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    ssn = pri->basic.criteria.ssn;
                    if (ssn == ITS_SS7_DEFAULT_SSN)
                    {
                        ssn = rinfo->basic.criteria.ssn;
                    }

                    if (copy.basic.criteria.ssn != ssn)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_OPC_SIO_SSN:
            if (copy.basic.style == ROUTE_DPC_OPC_SIO_SSN &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.opc == opc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.ssn == ssn)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    opc = pri->basic.criteria.opc;
                    if (opc == ITS_SS7_DEFAULT_POINT_CODE)
                    {
                        opc = rinfo->basic.criteria.opc;
                    }

                    if (copy.basic.criteria.opc != opc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    ssn = pri->basic.criteria.ssn;
                    if (ssn == ITS_SS7_DEFAULT_SSN)
                    {
                        ssn = rinfo->basic.criteria.ssn;
                    }

                    if (copy.basic.criteria.ssn != ssn)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_SIO_SSN_RANGE:
            if ((copy.basic.style == ROUTE_DPC_SIO_SSN ||
                 copy.basic.style == ROUTE_DPC_OPC_SIO_SSN) &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.ssn >=
                ri->basic.criteria.range.begin &&
                copy.basic.criteria.ssn <=
                ri->basic.criteria.range.end)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    if (pri->basic.criteria.range.begin !=
                        ri->basic.criteria.range.end)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            else if ((copy.basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                      copy.basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE) &&
                     (copy.basic.dpc & mask) == dpc &&
                     copy.basic.criteria.sio == sio &&
                     copy.basic.criteria.range.begin ==
                     ri->basic.criteria.range.begin &&
                     copy.basic.criteria.range.end ==
                     ri->basic.criteria.range.end)
            {
                *firstMatch = i;
                *lastMatch = i;
                *whichEntry = QualifyLink(ent, i, i,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_OPC_SIO_SSN_RANGE:
            if (copy.basic.style == ROUTE_DPC_OPC_SIO_SSN &&
                copy.basic.dpc == dpc &&
                copy.basic.criteria.opc == opc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.ssn >=
                ri->basic.criteria.range.begin &&
                copy.basic.criteria.ssn <=
                ri->basic.criteria.range.end)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    if (pri->basic.criteria.range.begin !=
                        ri->basic.criteria.range.end)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    opc = pri->basic.criteria.opc;
                    if (opc == ITS_SS7_DEFAULT_POINT_CODE)
                    {
                        opc = rinfo->basic.criteria.opc;
                    }

                    if (copy.basic.criteria.opc != opc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            else if (copy.basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE &&
                     (copy.basic.dpc & mask) == dpc &&
                     copy.basic.criteria.sio == sio &&
                     copy.basic.criteria.range.begin ==
                     ri->basic.criteria.range.begin &&
                     copy.basic.criteria.range.end ==
                     ri->basic.criteria.range.end)
            {
                *firstMatch = i;
                *lastMatch = i;
                *whichEntry = QualifyLink(ent, i, i,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_SIO_CIC:
            if ((copy.basic.style == ROUTE_DPC_SIO_CIC ||
                 copy.basic.style == ROUTE_DPC_OPC_SIO_CIC) &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.cic == cic)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    cic = pri->basic.criteria.cic;
                    if (cic == ITS_SS7_DEFAULT_CIC)
                    {
                        cic = rinfo->basic.criteria.cic;
                    }

                    if (copy.basic.criteria.cic != cic)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_OPC_SIO_CIC:
            if (copy.basic.style == ROUTE_DPC_OPC_SIO_CIC &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.opc == opc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.cic == cic)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    opc = pri->basic.criteria.opc;
                    if (opc == ITS_SS7_DEFAULT_POINT_CODE)
                    {
                        opc = rinfo->basic.criteria.opc;
                    }

                    if (copy.basic.criteria.opc != opc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    cic = pri->basic.criteria.cic;
                    if (cic == ITS_SS7_DEFAULT_CIC)
                    {
                        cic = rinfo->basic.criteria.cic;
                    }

                    if (copy.basic.criteria.cic != cic)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_SIO_CIC_RANGE:
            if ((copy.basic.style == ROUTE_DPC_SIO_CIC ||
                 copy.basic.style == ROUTE_DPC_OPC_SIO_CIC) &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.cic >=
                ri->basic.criteria.range.begin &&
                copy.basic.criteria.cic <=
                ri->basic.criteria.range.end)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    if (pri->basic.criteria.range.begin !=
                        ri->basic.criteria.range.end)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            else if ((copy.basic.style == ROUTE_DPC_SIO_CIC_RANGE ||
                      copy.basic.style == ROUTE_DPC_OPC_SIO_CIC_RANGE) &&
                     (copy.basic.dpc & mask) == dpc &&
                     copy.basic.criteria.sio == sio &&
                     copy.basic.criteria.range.begin ==
                     ri->basic.criteria.range.begin &&
                     copy.basic.criteria.range.end ==
                     ri->basic.criteria.range.end)
            {
                *firstMatch = i;
                *lastMatch = i;
                *whichEntry = QualifyLink(ent, i, i,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;

        case ROUTE_DPC_OPC_SIO_CIC_RANGE:
            if (copy.basic.style == ROUTE_DPC_OPC_SIO_CIC &&
                (copy.basic.dpc & mask) == dpc &&
                copy.basic.criteria.opc == opc &&
                copy.basic.criteria.sio == sio &&
                copy.basic.criteria.cic >=
                ri->basic.criteria.range.begin &&
                copy.basic.criteria.cic <=
                ri->basic.criteria.range.end)
            {
                finish = i;

                while (i > 0)
                {
                    ROUTE_Info *pri = ent->entries[i - 1];

                    ri = ent->entries[i];

                    if (pri->basic.style != ri->basic.style)
                    {
                        break;
                    }

                    if (pri->basic.criteria.range.begin !=
                        ri->basic.criteria.range.end)
                    {
                        break;
                    }

                    dpc = pri->basic.dpc;
                    mask = pri->basic.mask;

                    if ((copy.basic.dpc & mask) != dpc)
                    {
                        break;
                    }

                    opc = pri->basic.criteria.opc;
                    if (opc == ITS_SS7_DEFAULT_POINT_CODE)
                    {
                        opc = rinfo->basic.criteria.opc;
                    }

                    if (copy.basic.criteria.opc != opc)
                    {
                        break;
                    }

                    sio = pri->basic.criteria.sio;
                    if (sio == ITS_SS7_DEFAULT_SIO)
                    {
                        sio = rinfo->basic.criteria.sio;
                    }

                    if (copy.basic.criteria.sio != sio)
                    {
                        break;
                    }

                    i--;
                }

                *firstMatch = i;
                *lastMatch = finish;
                *whichEntry = QualifyLink(ent, i, finish,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            else if (copy.basic.style == ROUTE_DPC_OPC_SIO_CIC_RANGE &&
                     (copy.basic.dpc & mask) == dpc &&
                     copy.basic.criteria.sio == sio &&
                     copy.basic.criteria.range.begin ==
                     ri->basic.criteria.range.begin &&
                     copy.basic.criteria.range.end ==
                     ri->basic.criteria.range.end)
            {
                *firstMatch = i;
                *lastMatch = i;
                *whichEntry = QualifyLink(ent, i, i,
                                          whichLinkCode,
                                          &copy);

                return (ent);
            }
            break;
        }
    }

    ITS_TRACE_DEBUG(("No match found for rinfo\n"));

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Do SLS bit rotation for MTP3.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      sls - the original SLS value
 *
 *  Output Parameters:
 *      linkSetSelect - 0 or 1,  representing the linkSet to use
 *      linkSelect - a number smaller than 16 or 128 (depending on the use
 *              of 8 bit SLS values), representing the SLS map index to use
 *
 *  Return Value:
 *      New SLS value.
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for 64 link support 
 *                     ID::D0020                   and load balancing 
 ****************************************************************************/
ITSDLLAPI ITS_OCTET
ROUTE_SLSRotate(ITS_BOOLEAN do8Bit, ITS_OCTET sls,
                ITS_OCTET *linkSetSelect, ITS_OCTET *linkSelect,
                SS7_Destination *match, ITS_OCTET numlinkSet,
                ITS_OCTET firstMatch)
{
    ITS_OCTET linkSet, link, newSLS, upper;
    ITS_OCTET totnumlinks = 0;
    ITS_OCTET count = 0;
    ITS_OCTET index = 0;
    ITS_OCTET lsindex = 0;
    ITS_OCTET iterate = 0;
    ITS_BOOLEAN isfound = ITS_FALSE;
                
    /* get the total num of active links */
    for (index = firstMatch; index < numlinkSet; ++index)
    {
       if  ((match->entries[index]->linkSet->isUp) &&
            (match->entries[index]->isAllowed))
       {
           totnumlinks += match->entries[index]->linkSet->numLinks;
       }
    }

    /* initialize the count */
    if (sls)
    {
        count = 1;
    }

    /* check if numlinks is not 0 */
    if (totnumlinks)
    {
        iterate = (sls/totnumlinks) + 1;
    }

    /* sls is distributed among the links/linkset */
    for(index = 0; index < iterate; ++index)
    {
        for(lsindex = firstMatch; lsindex < numlinkSet; ++lsindex)
        {
            if((!match->entries[lsindex]->linkSet->isUp) ||
                  (!match->entries[lsindex]->isAllowed))
            {
               continue;
            }

            /* check whether sls is less than the numLinks
             * for a given linkset.
             */
            if ((sls - count) <
                    match->entries[lsindex]->linkSet->numLinks)
            {
                if (linkSetSelect)
                {
                   *linkSetSelect = lsindex - firstMatch;
                }

                /* get the link from the selected linkset */
                link = sls % match->entries[lsindex]->linkSet->numLinks;             
                if (linkSelect)
                {
                   *linkSelect = link;
                }

                isfound = ITS_TRUE;
                break;
            }
            else
            {
                /* increment the count with numLinks for the given
                 * linkset.
                 */
                count = count +
                    match->entries[lsindex]->linkSet->numLinks;
            }
        }

        /* stop searching if link is found */
        if (isfound)
          break;
    }

    /* To get the new sls old logic is retained
     * because MTP3 uses ROUTE_SLSUnrotate function
     * to get the oldSLS
     */

    /* capture the upper bits */
    upper = sls & UPPER_BITS;

    /* get the lowest bit of SLS */
    linkSet = sls & LOWER_BITS;

    /* get the lower bits of the SLS */
    link = (sls & MIDDLE_BITS) >> MIDDLE_SHIFT;

    /* new SLS is combination of the shifted entities */
    newSLS = upper | (linkSet << LOWER_SHIFT) | link;

    return (newSLS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Undo SLS bit rotation for MTP3.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      slsShift - number of bits to shift this SLS value
 *      sls - the original SLS value
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Old SLS value.
 ****************************************************************************/
ITSDLLAPI ITS_OCTET
ROUTE_SLSUnrotate(ITS_BOOLEAN do8Bit, ITS_OCTET sls)
{
    ITS_OCTET linkSet, link, oldSLS, upper;

    upper = sls & UPPER_BITS;

    linkSet = (sls >> LOWER_SHIFT) & LOWER_BITS;
    link = (sls << MIDDLE_SHIFT) & MIDDLE_BITS;
    if (do8Bit)
    {
        oldSLS = upper | link | linkSet;
    }
    else
    {
        oldSLS = link | linkSet;
    }

    return (oldSLS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find the best match for a given routing tuple
 *
 *  Input Parameters:
 *      rinfo - the routing tuple
 *      ev - (possibly) the event the tuple came from (or NULL)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The best match route record, or NULL if no match found.
 *
 *  Notes:
 *      The lock must be held before calling this function.
 *      Only a subset of the routing styles are valid for the info
 *      passed.  These are:
 *          DPC_OPC_SIO_SSN
 *          DPC_OPC_SIO_CIC
 *          DPC_OPC_SIO
 *          DPC_SIO_SSN
 *          DPC_SIO_CIC
 *          DPC_SIO
 *          DPC_ONLY
 *      All other types simply aren't valid here.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI SS7_Destination *
ROUTE_FindBestMatch(ROUTE_MatchInfo *rinfo,
                    int *whichEntry,
                    int *firstMatch, int *lastMatch,
                    int *whichLinkCode, ITS_BOOLEAN rangeAllowed)
{
    SS7_Destination *ent = NULL;
    ITS_UINT i;
    ITS_UINT key;
    int error;

    /* work out the key */
    key = rinfo->basic.dpc |
            ((rinfo->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
            (rinfo->basic.family << 24);

    /* find by point code */
    for (i = 0; i < numMasks; i++)
    {
        ITS_UINT tkey;

        tkey = key & (masks[i] | ((ROUTE_NI_MASK|ROUTE_FAMILY_MASK) << 24));

        ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                             DSM_TABLE_DESTINATIONS,
                             (ITS_OCTET *)&tkey,
                             sizeof(ITS_UINT),
                             &error);

        if (error == ITS_SUCCESS && ent != NULL)
        {
            break;
        }
    }

    if (i == numMasks)
    {
        return (NULL);
    }

    return FindBestMatchOfEntry(ent, rinfo,
                                whichEntry,
                                firstMatch, lastMatch,
                                whichLinkCode,
                                rangeAllowed, ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Given a routing match record, set the "current" route to matches
 *      at that priority.
 *
 *  Input Parameters:
 *      userInfo - the match record
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_SetCurrentRoute(ROUTE_MatchInfo *rinfo)
{
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
    SS7_Destination *rc;

    /* get the match itself */
    if ((rc = ROUTE_FindBestMatch(rinfo, &whichEntry,
                                  &firstMatch, &lastMatch,
                                  &whichLinkCode,
                                  ITS_FALSE)) == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    /* calculate the begin/end */
    if (rc->entries[whichEntry]->linkSet->linkSet == rinfo->linkSet)
    {
        for (i = whichEntry; i >= 0; i--)
        {
            if (rc->entries[i]->priority !=
                rc->entries[whichEntry]->priority)
            {
                break;
            }
        }

        if (i != whichEntry)
        {
            i++;
        }

        rc->currentStart = (ITS_UINT)i;

        for (i = whichEntry; i < (int)rc->numEntries; i++)
        {
            if (rc->entries[i]->priority !=
                rc->entries[whichEntry]->priority)
            {
                break;
            }
        }

        if (i != whichEntry)
        {
            i--;
        }

        rc->currentStop = (ITS_UINT)i;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Given a routing record, determine the next link to use in a link
 *      set.
 *
 *  Input Parameters:
 *      match - the "match" destination
 *      whichEntry - the index of the beginning of the link set.
 *      firstMatch - the index of the first route matching
 *      lastMatch - the index of the last route matching
 *      whichLinkCode - possibly an explicit link code
 *
 *  Input/Output Parameters:
 *      userInfo - the match context.  The linkSet and linkCode fields
 *          are overridden with the selected values here.
 *      sls - specifies the input sls and the rotated result sls.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      the transport id associated with a particular link in the link
 *      set.  If nothing is available, ITS_NO_SRC is returned.
 *
 *  Notes:
 *      The sls is input/output.  Also, note that we don't check link
 *      status.  That's because a link shouldn't be present in the
 *      linkSet code map if it's not up.
 *      THE CALLER MUST HOLD THE TABLE LOCK BEFORE CALLING THIS FUNCTION.
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for 64 link support 
 *                         ID::D0020               and load balancing 
 *   yranade   05-04-2005  PBN Issue ID: 1810      Priority Based Routing Fix 
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_SelectLink(SS7_Destination *match, ROUTE_MatchInfo *userInfo,
                 int whichEntry, int firstMatch, int lastMatch,
                 int whichLinkCode, ITS_OCTET *sls)
{
    volatile ITS_USHORT ret;
    SS7_LinkSetPtr ls;
    ITS_OCTET ent, slsIdx = 1, newSLS = 0;
    ITS_UINT i;
    ITS_OCTET numlinkSet = 0;
    ITS_OCTET linkIndex = 0;
    ITS_BOOLEAN isrotateSLS = ITS_TRUE;

    ITS_TRACE_DEBUG(("SelectLink:\n"));

    ITS_C_ASSERT(whichEntry >= 0);
    ITS_C_ASSERT(firstMatch >= 0);
    ITS_C_ASSERT(lastMatch >= 0);
    ITS_C_ASSERT(whichLinkCode >= 0);

    /* no match? */
    if (whichEntry < 0)
    {
        return (ITS_NO_SRC);
    }

    /* does the user care about the link code? */
    if (userInfo->linkCode != ITS_SS7_DEFAULT_LINK_CODE)
    {
        SS7_LinkPtr link;
        
        link = match->entries[whichEntry]->linkSet->
                            links[whichLinkCode];

        /*
         * it does.  Find the correct entry.
         * We were checking && link->isAllowed, but I think that's too
         * tough, in light of MTP3 requirements.
         */
        if (link->isUp) 
        {
            userInfo->linkSet = match->entries[whichEntry]->linkSet->linkSet;
            userInfo->rkey = whichEntry;
            ret = LINK_GetTransportId(link);
        }
        else
        {
            userInfo->rkey = whichEntry;
            ret = ITS_INVALID_SRC;
        }

        return (ret);
    }

    userInfo->rkey = whichEntry;

    ret = ITS_INVALID_SRC;

    /*
     * Points of interest.  firstMatch and lastMatch point at
     * the beginning and the end of matches, but that covers
     * the entire priority range.
     *
     * However, on the destination record we have currentStart
     * and currentStop (if this is really an MTP3 route).  We
     * must use those limits (again, if this is really an MTP3
     * route).
     *
     * Finally, we have to deal with the case where the limits
     * are set but the route is down (bad route), or a queue
     * put is called for.  For the former, I think INVALID_SRC
     * is fine.  For the latter, we override the meaning of
     * the rkey member in the MatchInfo to be the selected
     * index.  The caller can then examine this for a qPut
     * setting.
     */

    /*
     * we do have to limit first and last match to
     * currentStart and currentStop if the routing is MTP3
     * based.
     */
    if (userInfo->basic.type == REMOTE_ROUTE &&
        (userInfo->basic.style == ROUTE_DPC_NI ||
         userInfo->basic.style == ROUTE_DPC_OPC_NI))
    {
        if ((ITS_UINT)whichEntry < match->currentStart ||
            (ITS_UINT)whichEntry > match->currentStop)
        {
            return (ITS_INVALID_SRC);
        }

        if ((ITS_UINT)firstMatch < match->currentStart)
        {
            firstMatch = (int)match->currentStart;
        }

        if ((ITS_UINT)lastMatch > match->currentStop)
        {
            lastMatch = (int)match->currentStop;
        }
    }

    /*
     * get the next link, based on ROUTE_MatchInfo and the route
     * information (which includes SLS)
     */
    while (firstMatch <= lastMatch &&
           (!match->entries[firstMatch]->linkSet->isUp ||
            !match->entries[firstMatch]->isAllowed))
    {
        firstMatch++;
    }

    /* nothing up? */
    if (firstMatch > lastMatch)
    {
        return (ITS_INVALID_SRC);
    }
    
    /*
     * something's up.  Use the highest priority entry, this should be
     * firstMatch.  'whichEntry' is changed here to be the last match
     * within the same priority routes.
     */
    whichEntry = firstMatch;
    while (whichEntry < lastMatch &&
           match->entries[whichEntry]->priority ==
           match->entries[whichEntry + 1]->priority)
    {
        whichEntry++;
    }
           
    /*
     * now we have the range firstMatch to whichEntry at the same
     * priority level.  Recall that some might be down.  Get then
     * ent within the range from the SLS shift.
     */

    ent = 0;
    numlinkSet = whichEntry + 1;
    linkIndex = firstMatch;
    newSLS = ROUTE_SLSRotate(ITS_TRUE, *sls, &ent, &slsIdx,
                             match , numlinkSet, linkIndex);
    /*
     * check for overflow of ent (SLS shift asked for more than
     * we have).
     */
    if (firstMatch + ent >= whichEntry)
    {
        ent = whichEntry - firstMatch;
    }

    /*
     * find an up route.  Hopefully the first, but we'll work in the
     * range firstMatch to whichEntry.  We want to use the firstMatch
     * + ent entry, but it may not be up, so check that.
     */
    ls = NULL;
    if (match->entries[firstMatch + ent]->linkSet->isUp &&
        match->entries[firstMatch + ent]->isAllowed)
    {
        /* good match */
        ls = match->entries[firstMatch + ent]->linkSet;
        userInfo->linkSet = match->entries[firstMatch + ent]->linkSet->linkSet;
        userInfo->rkey = firstMatch + ent;
        ent = 0;
        isrotateSLS = ITS_FALSE;
    }
    else
    {
       /*
         * ent wasn't up.  Scan the rest of the range looking for
         * one that is up.
         */
        ent = 0;

        for (i = 0; i < (ITS_UINT)(whichEntry - firstMatch + 1); i++)
        {
            if (match->entries[firstMatch + ent]->linkSet->isUp &&
                match->entries[firstMatch + ent]->isAllowed)
            {
                ls = match->entries[firstMatch + ent]->linkSet;
                userInfo->linkSet = match->entries[firstMatch + ent]->linkSet->linkSet;
                userInfo->rkey = firstMatch + ent;
                break;
            }
            ent++;
        }
    }
    
    /* if we don't have a link set we're toast */
    if (ls == NULL)
    {
        return (ITS_INVALID_SRC);
    }

    /*check whether SLS rotate is required */
    if (isrotateSLS)
    {
        /*
         * rotate the bits again to get the link,we have the linkset
         * now we are looking for link.
         */

        linkIndex = firstMatch + ent;
        newSLS = ROUTE_SLSRotate(!ls->is5Bit, *sls, &ent, &slsIdx,
                                 match, numlinkSet, linkIndex);
    }

    if (!ls->isC)
    {
        *sls = newSLS;
    }

    /*
     * find the link.
     * NOTE: The code map contains the link index, not code.
     */
    i = ls->codeMap[slsIdx];

    if (ls->numLinks == 0 || ls->links[i] == 0)
    {
        return (ITS_INVALID_SRC);
    }

    ret = LINK_GetTransportId(ls->links[i]);
    userInfo->linkCode = ls->links[i]->linkCode;


    if (!ls->links[i]->isUp || !ls->links[i]->isAllowed ||
        (ret == ITS_INVALID_SRC) || (ret == ITS_NO_SRC) )
    {
        /* well, the exact match didn't work.  Try ansy another link */

        ret = ITS_INVALID_SRC;
        userInfo->linkCode = ITS_SS7_DEFAULT_LINK_CODE; 

        for (i = 0; i < ls->numLinks; i++)
        {
            if (ls->links[i]->isUp &&
                ls->links[i]->isAllowed)
            {
                ret = LINK_GetTransportId(ls->links[i]);

                if ( (ret == ITS_NO_SRC) || (ret == ITS_INVALID_SRC) )
                {
                    continue;
                }

           
                userInfo->linkCode = ls->links[i]->linkCode;

                return (ret);
            }
        }
    }

#if 0
    /*
     * keep this code around for the time being.
     * The above should be enough, though.
     */
    /* find the link code */
    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->linkCode == slsIdx)
        {
            if (ls->links[i]->isUp &&
                ls->links[i]->isAllowed)
            {
                ret = LINK_GetTransportId(ls->links[i]);

                return (ret);
            }
        }
    }

    /* well, the exact match didn't work.  Try another link */
    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isUp &&
            ls->links[i]->isAllowed)
        {
            ret = LINK_GetTransportId(ls->links[i]);

            return (ret);
        }
    }
#endif

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Given a routing record, convert it into the wild card version of
 *      same.
 *
 *  Input Parameters:
 *      match - the "match" record
 *      which - the index of the beginning of the link set.
 *      userInfo - the original request record
 *      ev - (possibly) the event the original request came from (or NULL).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      the transport id associated with a particular link in the link
 *      set.  If nothing is available, ITS_NO_SRC is returned.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
MakeIntoWildCard(ROUTE_MatchInfo *rinfo)
{
    rinfo->basic.dpc = ITS_SS7_DEFAULT_POINT_CODE;

    switch (rinfo->basic.style)
    {
    case ROUTE_DPC_UDEF:
    default:
        break;

    case ROUTE_DPC_NI:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        break;
        
    case ROUTE_DPC_OPC_NI:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        rinfo->basic.criteria.opc = ITS_SS7_DEFAULT_POINT_CODE;
        break;

    case ROUTE_DPC_SIO:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        break;

    case ROUTE_DPC_OPC_SIO:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        rinfo->basic.criteria.opc = ITS_SS7_DEFAULT_POINT_CODE;
        break;

    case ROUTE_DPC_SIO_SSN:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        rinfo->basic.criteria.ssn = ITS_SS7_DEFAULT_SSN;
        break;

    case ROUTE_DPC_OPC_SIO_SSN:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        rinfo->basic.criteria.opc = ITS_SS7_DEFAULT_POINT_CODE;
        rinfo->basic.criteria.ssn = ITS_SS7_DEFAULT_SSN;
        break;

    case ROUTE_DPC_SIO_CIC:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        rinfo->basic.criteria.cic = ITS_SS7_DEFAULT_CIC;
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        rinfo->basic.criteria.sio = ITS_SS7_DEFAULT_SIO;
        rinfo->basic.criteria.opc = ITS_SS7_DEFAULT_POINT_CODE;
        rinfo->basic.criteria.cic = ITS_SS7_DEFAULT_CIC;
        break;

    /* these four are illegal, so fall thru */
    case ROUTE_DPC_SIO_SSN_RANGE:
    case ROUTE_DPC_SIO_CIC_RANGE:
    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        break;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function defines the behavior for default ss7 routing;
 *      that is, this function determines the transport to send
 *      to if the user has NOT set the SS7 selector callback function.
 *
 *  Input Parameters:
 *      h - a pointer to the message context that needs routing.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      This function will always return the instance number identifying
 *          the default transport instance, or ITS_INVALID_SRC.
 *
 *  Notes:
 *      Recurses for wild cards.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_SendToSS7(ROUTE_MatchInfo* rinfo, ITS_EVENT* ev)
{
    SS7_Destination *tmp;
    int whichEntry, whichLinkCode;
    int firstMatch, lastMatch;
    ITS_USHORT ret;

    ITS_TRACE_DEBUG(("ROUTE_SendToSS7:\n"));

    /*
     * ignore the event.  The match info has all the data we need
     * in a protocol family agnostic form.
     */

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    /* Reevaluate the suitability of this function */
    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_FALSE);
    
    if (tmp == NULL || whichEntry < 0)
    {
        if (rinfo->basic.dpc != ITS_SS7_DEFAULT_POINT_CODE)
        {
            ITS_UINT dpc;
            ITS_OCTET ni;

            dpc = rinfo->basic.dpc;
            ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;

            MakeIntoWildCard(rinfo);

            tmp = ROUTE_FindBestMatch(rinfo,
                                      &whichEntry, &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE);
    
            if (tmp == NULL || whichEntry < 0)
            {
                ITS_TRACE_WARNING(("No route found to NI %02x DPC %08x\n",
                                   ni, dpc));

                ret = ITS_INVALID_SRC;
            }
            else
            {
                ret = ROUTE_SelectLink(tmp, rinfo,
                                       whichEntry, firstMatch, lastMatch,
                                       whichLinkCode,
                                       &rinfo->sls);
            }
        }
        else
        {
            ITS_TRACE_WARNING(("No route found to NI %02x DPC %08x\n",
                               rinfo->basic.criteria.sio & ROUTE_NI_MASK,
                               rinfo->basic.dpc));

            ret = ITS_INVALID_SRC;
        }
    }
    else
    {
        ret = ROUTE_SelectLink(tmp, rinfo,
                               whichEntry, firstMatch, lastMatch,
                               whichLinkCode,
                               &rinfo->sls);
    }

    ROUTE_UnlockRead(routeRWLock, NULL); 

    ITS_TRACE_DEBUG(("ROUTE_SendToSS7: returning %d\n", ret));

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This predicate allows our stack to know when the user
 *      has not overridden the default application selector, and so
 *      can automatically add the default transport as the application
 *      context.
 *
 *  Input Parameters:
 *      ns - a pointer to the new application selector function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the callback was successfully set, a pointer to the last
 *          callback function is returned.
 *      If an error occurs, NULL is returned.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
ROUTE_IsSS7SelectorDefault()
{
    volatile ITS_BOOLEAN ret = ITS_FALSE;

    ITS_TRACE_DEBUG(("ROUTE_IsSS7SelectorDefault:\n"));

    if (RWLOCK_LockShared(&selectorGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SetSS7Selector: couldn't acquire "
                         "mutex\n"));

        return (ret);
    }

    ret = (ss7Select == ROUTE_SendToSS7) ? ITS_TRUE : ITS_FALSE;

    RWLOCK_UnlockShared(&selectorGate);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This funtion allows the user to change the application selector
 *      function.  In essence, the application selector is a callback
 *      that is invoked for new units-of-work by IntelliSS7 APIs.
 *
 *  Input Parameters:
 *      ns - a pointer to the new application selector function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the callback was successfully set, a pointer to the last
 *          callback function is returned.
 *      If an error occurs, NULL is returned.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ROUTE_SS7Selector
ROUTE_SetSS7Selector(ROUTE_SS7Selector ns)
{
    volatile ROUTE_SS7Selector ret;

    ITS_TRACE_DEBUG(("ROUTE_SetSS7Selector:\n"));

    if (RWLOCK_LockExclusive(&selectorGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SetSS7Selector: couldn't acquire "
                         "mutex\n"));

        return (NULL);
    }

    ret = ss7Select;

    if (ns == NULL)
    {
        ITS_TRACE_ERROR(("ROUTE_SetSS7Selector: attempt to set "
                         "NULL appSelector\n"));

        ns = ROUTE_SendToSS7;
    }

    ss7Select = ns;

    RWLOCK_UnlockExclusive(&selectorGate);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function converts a varargs list into the ROUTE_Info data
 *      structure.
 *
 *  Input Parameters:
 *      rinfoa, rinfob - structures to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RouteInfoMatches(ROUTE_Info *rinfoa, ROUTE_Info *rinfob)
{
    ITS_TRACE_DEBUG(("RouteInfoMatches\n"));

    /* this function assumes this to be true */
    ITS_C_REQUIRE(rinfoa->basic.dpc == rinfob->basic.dpc);

    /* inexact match */
    if (rinfoa->basic.style == rinfob->basic.style &&
        rinfoa->basic.family == rinfob->basic.family)
    {
        switch (rinfoa->basic.style)
        {
        case ROUTE_DPC_NI:
            if ((rinfoa->basic.criteria.sio & ROUTE_NI_MASK) ==
                (rinfob->basic.criteria.sio & ROUTE_NI_MASK))
            {
                if (rinfoa->linkSet && rinfob->linkSet)
                {
                    if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                    {
                        return (rinfoa->priority - rinfob->priority);
                    }
                    return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                }
            }

            return ((rinfoa->basic.criteria.sio & ROUTE_NI_MASK) -
                    (rinfob->basic.criteria.sio & ROUTE_NI_MASK));

        case ROUTE_DPC_OPC_NI:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if ((rinfoa->basic.criteria.sio & ROUTE_NI_MASK) ==
                    (rinfob->basic.criteria.sio & ROUTE_NI_MASK))
                {
                    if (rinfoa->linkSet && rinfob->linkSet)
                    {   
                        if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                        {
                            return (rinfoa->priority - rinfob->priority);
                        }
                        return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                    }
                }

                return ((rinfoa->basic.criteria.sio & ROUTE_NI_MASK) -
                        (rinfob->basic.criteria.sio & ROUTE_NI_MASK));
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->linkSet && rinfob->linkSet)
                {
                    if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                    {
                        return (rinfoa->priority - rinfob->priority);
                    }
                    return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                }
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->linkSet && rinfob->linkSet)
                    {
                        if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                        {
                            return (rinfoa->priority - rinfob->priority);
                        }
                        return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                    }
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_SSN:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->basic.criteria.ssn ==
                    rinfob->basic.criteria.ssn)
                {
                    /* Routing keys do not have a linkSet ie linkSet ptr is set
                       to NULL. Refer: AddOneRoute
                     */
                    if (rinfoa->linkSet && rinfob->linkSet)
                    {

                        if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                        {
                            return (rinfoa->priority - rinfob->priority);
                        }

                        return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                    }
                }

                return (rinfoa->basic.criteria.ssn - rinfob->basic.criteria.ssn);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_SSN:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->basic.criteria.ssn ==
                        rinfob->basic.criteria.ssn)
                    {
                        if (rinfoa->linkSet && rinfob->linkSet)
                        {
                            if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                            {
                                return (rinfoa->priority - rinfob->priority);
                            }

                            return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                        }
                    }

                    return (rinfoa->basic.criteria.ssn - rinfob->basic.criteria.ssn);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_CIC:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->basic.criteria.cic ==
                    rinfob->basic.criteria.cic)
                {
                    if (rinfoa->linkSet && rinfob->linkSet)
                    {
                        if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                        {
                            return (rinfoa->priority - rinfob->priority);
                        }

                        return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                    }
                }

                return (rinfoa->basic.criteria.cic - rinfob->basic.criteria.cic);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_CIC:
            if (rinfoa->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->basic.criteria.cic ==
                        rinfob->basic.criteria.cic)
                    {
                        if (rinfoa->linkSet && rinfob->linkSet)
                        {   
                            if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                            {
                                return (rinfoa->priority - rinfob->priority);
                            }

                            return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                        }
                    }

                    return (rinfoa->basic.criteria.cic - rinfob->basic.criteria.cic);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_SSN_RANGE:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->basic.criteria.range.begin ==
                    rinfob->basic.criteria.range.begin)
                {
                    if (rinfoa->basic.criteria.range.end ==
                        rinfob->basic.criteria.range.end)
                    {
                        if (rinfoa->linkSet && rinfob->linkSet)
                        {
                            if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                            {
                                return (rinfoa->priority - rinfob->priority);
                            }

                            return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                        }
                    }

                    return (rinfoa->basic.criteria.range.end -
                            rinfob->basic.criteria.range.end);
                }

                return (rinfoa->basic.criteria.range.begin -
                        rinfob->basic.criteria.range.begin);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_SSN_RANGE:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->basic.criteria.range.begin ==
                        rinfob->basic.criteria.range.begin)
                    {
                        if (rinfoa->basic.criteria.range.end ==
                            rinfob->basic.criteria.range.end)
                        {

                            if (rinfoa->linkSet && rinfob->linkSet)
                            {
                                if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                                {
                                    return (rinfoa->priority - rinfob->priority);
                                }

                                return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                            }
                        }

                        return (rinfoa->basic.criteria.range.end -
                                rinfob->basic.criteria.range.end);
                    }

                    return (rinfoa->basic.criteria.range.begin -
                            rinfob->basic.criteria.range.begin);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_CIC_RANGE:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->basic.criteria.range.begin ==
                    rinfob->basic.criteria.range.begin)
                {
                    if (rinfoa->basic.criteria.range.end ==
                        rinfob->basic.criteria.range.end)
                    {
                        if (rinfoa->linkSet && rinfob->linkSet)
                        {
                            if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                            {
                                return (rinfoa->priority - rinfob->priority);
                            }

                            return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                        }
                    }

                    return (rinfoa->basic.criteria.range.end -
                            rinfob->basic.criteria.range.end);
                }

                return (rinfoa->basic.criteria.range.begin -
                        rinfob->basic.criteria.range.begin);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_CIC_RANGE:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->basic.criteria.range.begin ==
                        rinfob->basic.criteria.range.begin)
                    {
                        if (rinfoa->basic.criteria.range.end ==
                            rinfob->basic.criteria.range.end)
                        {
                            if (rinfoa->linkSet && rinfob->linkSet)
                            {  
                                if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                                {
                                    return (rinfoa->priority - rinfob->priority);
                                }

                                return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                            }
                        }

                        return (rinfoa->basic.criteria.range.end -
                                rinfob->basic.criteria.range.end);
                    }

                    return (rinfoa->basic.criteria.range.begin -
                            rinfob->basic.criteria.range.begin);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_UDEF:
        default:
            if (rinfoa->basic.criteria.userDefLen ==
                rinfob->basic.criteria.userDefLen &&
                memcmp(rinfoa->basic.criteria.userDefined,
                       rinfob->basic.criteria.userDefined,
                       rinfoa->basic.criteria.userDefLen) == 0)
            {
                if (rinfoa->linkSet && rinfob->linkSet)
                {
                    if (rinfoa->linkSet->linkSet == rinfob->linkSet->linkSet)
                    {
                        return (rinfoa->priority - rinfob->priority);
                    }

                    return (rinfoa->linkSet->linkSet - rinfob->linkSet->linkSet);
                }
            }

            return (rinfoa->basic.criteria.userDefLen -
                    rinfob->basic.criteria.userDefLen);
        }
    }

    return (rinfoa->basic.style - rinfob->basic.style);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Determine if a route is a member of a route group.
 *
 *  Input Parameters:
 *      rinfoa, rinfob - structures to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RouteInGroup(ROUTE_Info *rinfoa, ROUTE_Info *rinfob)
{
    ITS_TRACE_DEBUG(("RouteInGroup\n"));

    /* this function assumes this to be true */
    ITS_C_REQUIRE(rinfoa->basic.dpc == rinfob->basic.dpc);

    /* inexact match */
    if (rinfoa->basic.style == rinfob->basic.style &&
        rinfoa->basic.family == rinfob->basic.family)
    {
        switch (rinfoa->basic.style)
        {
        case ROUTE_DPC_NI:
            return ((rinfoa->basic.criteria.sio & ROUTE_NI_MASK) -
                    (rinfob->basic.criteria.sio & ROUTE_NI_MASK));

        case ROUTE_DPC_OPC_NI:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                return ((rinfoa->basic.criteria.sio & ROUTE_NI_MASK) -
                        (rinfob->basic.criteria.sio & ROUTE_NI_MASK));
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO:
            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_SSN:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                return (rinfoa->basic.criteria.ssn - rinfob->basic.criteria.ssn);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_SSN:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    return (rinfoa->basic.criteria.ssn - rinfob->basic.criteria.ssn);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_CIC:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                return (rinfoa->basic.criteria.cic - rinfob->basic.criteria.cic);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_CIC:
            if (rinfoa->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    return (rinfoa->basic.criteria.cic - rinfob->basic.criteria.cic);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_SSN_RANGE:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->basic.criteria.range.begin ==
                    rinfob->basic.criteria.range.begin)
                {
                    return (rinfoa->basic.criteria.range.end -
                            rinfob->basic.criteria.range.end);
                }

                return (rinfoa->basic.criteria.range.begin -
                        rinfob->basic.criteria.range.begin);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_SSN_RANGE:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->basic.criteria.range.begin ==
                        rinfob->basic.criteria.range.begin)
                    {
                        return (rinfoa->basic.criteria.range.end -
                                rinfob->basic.criteria.range.end);
                    }

                    return (rinfoa->basic.criteria.range.begin -
                            rinfob->basic.criteria.range.begin);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_SIO_CIC_RANGE:
            if (rinfoa->basic.criteria.sio ==
                rinfob->basic.criteria.sio)
            {
                if (rinfoa->basic.criteria.range.begin ==
                    rinfob->basic.criteria.range.begin)
                {
                    return (rinfoa->basic.criteria.range.end -
                            rinfob->basic.criteria.range.end);
                }

                return (rinfoa->basic.criteria.range.begin -
                        rinfob->basic.criteria.range.begin);
            }

            return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);

        case ROUTE_DPC_OPC_SIO_CIC_RANGE:
            if (rinfoa->basic.criteria.opc ==
                rinfob->basic.criteria.opc)
            {
                if (rinfoa->basic.criteria.sio ==
                    rinfob->basic.criteria.sio)
                {
                    if (rinfoa->basic.criteria.range.begin ==
                        rinfob->basic.criteria.range.begin)
                    {
                        return (rinfoa->basic.criteria.range.end -
                                rinfob->basic.criteria.range.end);
                    }

                    return (rinfoa->basic.criteria.range.begin -
                            rinfob->basic.criteria.range.begin);
                }

                return (rinfoa->basic.criteria.sio - rinfob->basic.criteria.sio);
            }

            return (rinfoa->basic.criteria.opc -
                    rinfob->basic.criteria.opc);

        case ROUTE_DPC_UDEF:
        default:
            if (rinfoa->basic.criteria.userDefLen ==
                rinfob->basic.criteria.userDefLen)
            {
                return memcmp(rinfoa->basic.criteria.userDefined,
                              rinfob->basic.criteria.userDefined,
                              rinfoa->basic.criteria.userDefLen);
            }

            return (rinfoa->basic.criteria.userDefLen -
                    rinfob->basic.criteria.userDefLen);
        }
    }

    return (rinfoa->basic.style - rinfob->basic.style);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Sort the routes by priority order
 *
 *  Input Parameters:
 *      r1, r2 - pointers to route information.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_AddRouteContext().
 ****************************************************************************/
static int
PriorityOrder(const void *r1, const void *r2)
{
    ROUTE_Info **a = (ROUTE_Info **)r1;
    ROUTE_Info **b = (ROUTE_Info **)r2;

    return ((int)(*a)->priority - (int)(*b)->priority);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds a route.
 *
 *  Input Parameters:
 *      type - RKEY, RCONT, or ROUTE
 *      key - key to add for
 *      info - match info to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      It is assumed that the caller commits changes this function
 *      makes to the destination.
 *
 *  See Also:
 ****************************************************************************/
static ROUTE_Info *
AddOneRoute(ITS_UINT type, ITS_UINT key,
            ROUTE_MatchInfo *rinfo, ITS_UINT rkey,
            SS7_Destination *dest)
{
    ROUTE_EntryKey newKey;
    ROUTE_Info *add;
    int error;

    ITS_TRACE_DEBUG(("AddOneRoute: type %d key %08x\n", type, key));

    /* lock the table */
    if (DSM_LockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES) != ITS_SUCCESS)
    {
        return (NULL);
    }

    /* initialize the key */
    newKey.type = type;
    newKey.niDPC = key;
    newKey.fakeIndex = rkey;

    /* sanity check: make sure it doesn't already exist */
    add = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_ROUTES,
                         (ITS_OCTET *)&newKey,
                         sizeof(ROUTE_EntryKey),
                         &error);

    if (error != ITS_ENOTFOUND ||
        (error == ITS_SUCCESS && add != NULL))
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

        return (NULL);
    }

    /* allocate the new entry */
    add = (ROUTE_Info *)DSM_AllocNoLock(DSM_RoutingFtGroupId,
                                        DSM_TABLE_ROUTES,
                                        (ITS_OCTET *)&newKey,
                                        sizeof(ROUTE_EntryKey),
                                        sizeof(ROUTE_Info),
                                        &error);

    if (error != ITS_SUCCESS || add == NULL)
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

        return (NULL);
    }

    add->basic = rinfo->basic;
    add->priority = rinfo->priority;
    add->isAllowed = ITS_TRUE;
    add->inUse = ITS_TRUE;
    add->rkey = rkey;
    add->dest = dest; /* must be committed */

    if (type == ENT_TYPE_ROUTE)
    {
        add->crBuf = DSMQUEUE_Create(ENT_TYPE_CRBUF | (rkey << 16), key);

        add->linkSet = LINKSET_FindLinkSetNoLock(rinfo->linkSet);

        if (add->linkSet == NULL ||
            add->linkSet->family != add->basic.family)
        {
            ITS_TRACE_ERROR(("Couldn't find link set for route\n"));

            DSM_FreeNoLock(DSM_RoutingFtGroupId,
                           DSM_TABLE_ROUTES,
                           (ITS_OCTET *)&key,
                           sizeof(ITS_UINT),
                           add);

            DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

            return (NULL);
        }

        if ((add->basic.criteria.sio & ROUTE_NI_MASK) !=
            (add->linkSet->ni & ROUTE_NI_MASK))
        {
            ITS_TRACE_ERROR(("Route NI and linkSet NI MUST match\n"));

            DSM_FreeNoLock(DSM_RoutingFtGroupId,
                           DSM_TABLE_ROUTES,
                           (ITS_OCTET *)&key,
                           sizeof(ITS_UINT),
                           add);

            DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

            return (NULL);
        }

        if (LINKSET_AddRoute(add->linkSet, add) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Error adding route to link set\n"));

            DSM_FreeNoLock(DSM_RoutingFtGroupId,
                           DSM_TABLE_ROUTES,
                           (ITS_OCTET *)&key,
                           sizeof(ITS_UINT),
                           add);

            DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

            return (NULL);
        }
        if (dest->status != DESTINATION_AVAILABLE && add->linkSet->isUp) 
        {
            dest->status = DESTINATION_AVAILABLE;
        }
    }
    else
    {
        /*
         * routing keys do not have a linkSet so set the linkSet ptr to NULL
         * When adding a routing key route, one must use the default linkSet
         * and default linkCode. This ensure that the linkSet ptr will never
         * be accessed.
         */

        add->linkSet = NULL;
    }

    /* commit the route */
    DSM_CommitNoLock(DSM_RoutingFtGroupId,
                     DSM_TABLE_ROUTES,
                     (ITS_OCTET *)&newKey,
                     sizeof(ROUTE_EntryKey),
                     add);
  
    /* unlock the table */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

    return (add);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds a route.
 *
 *  Input Parameters:
 *      type - RKEY, RCONT, or ROUTE
 *      key - key to add for
 *      info - match info to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      It is assumed that the caller commits changes this function
 *      makes to the destination.
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
DelOneRoute(ITS_UINT type, ITS_UINT key, ITS_UINT rkey)
{
    ROUTE_EntryKey oldKey;
    ROUTE_Info *ri;
    int error;

    /* lock table */
    if (DSM_LockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES) != ITS_SUCCESS)
    {
        return (ITS_FALSE);
    }

    /* build key */
    oldKey.type = type;
    oldKey.niDPC = key;
    oldKey.fakeIndex = rkey;

    /* find entry */
    ri = DSM_FindNoLock(DSM_RoutingFtGroupId,
                        DSM_TABLE_ROUTES,
                        (ITS_OCTET *)&oldKey,
                        sizeof(ROUTE_EntryKey),
                        &error);

    if (error != ITS_SUCCESS || ri == NULL)
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

        return (ITS_FALSE);
    }

    /* clean up link set info */
    if (ri->basic.type == LOCAL_ROUTE ||
        ri->basic.type == REMOTE_ROUTE)
    {
        LINKSET_RemRoute(ri->linkSet, ri);
    }

    /* FIXME: free the crBuf */
    DSMQUEUE_Delete(ri->crBuf);
    ri->crBuf = NULL;
    /* delete it */
    DSM_FreeNoLock(DSM_RoutingFtGroupId,
                   DSM_TABLE_ROUTES,
                   (ITS_OCTET *)&oldKey,
                   sizeof(ROUTE_EntryKey),
                   ri);

    /* unlock table */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds a route entry in sort order.
 *
 *  Input Parameters:
 *      dest - the destination to add this route for.
 *      add - the route to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      It is assumed that the caller commits changes this function
 *      makes to the destination.
 *
 *  See Also:
 ****************************************************************************/
static void
AddSortedRoute(SS7_Destination *dest, ROUTE_Info *add)
{
    ITS_UINT i;
    int start, last, current;

    /* determine where to add */
    last = -1;
    start = -1;

    for (start = 0, i = 0; i < dest->numEntries; i++)
    {
        if (add->basic.style != dest->entries[i]->basic.style)
        {
            break;
        }

        /* handle the route group case */
        if ((current = RouteInGroup(dest->entries[i], add)) == 0)
        {
            start = (int)i;

            i++;

            if (i < dest->numEntries)
            {
                while (i < dest->numEntries &&
                       RouteInGroup(dest->entries[i], add) == 0)
                {
                    i++;
                }
            }

            break;
        }

        if (last < 0 && current > 0)
        {
            break;
        }
    }

    /* ok, "i" contains the index of the position to add. */
    if (i != dest->numEntries)
    {
//        memmove(&dest->entries[i+1], &dest->entries[i],dest->numEntries * sizeof(ROUTE_Info *));
    }

//    dest->entries[i] = add;
    dest->entries[dest->numEntries] = add;
    dest->numEntries++;

    /* now adjust the priority order, if necessary */
    if (start >= 0 && i > (ITS_UINT)start)
    {
        last = i;

        qsort(&dest->entries[start], last - start + 1,
              sizeof(ROUTE_Info *),
              PriorityOrder);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function grows the entry table (if necessary) when adding.
 *
 *  Input Parameters:
 *      type - RKEY, RCONT, or ROUTE
 *      key - table primary key
 *      dest - destination involved
 *      newEnt - entry to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      It is assumed that the caller commits changes this function
 *      makes to the destination.
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
AddEntry(ITS_UINT type, ITS_UINT key, SS7_Destination *dest,
         ROUTE_Info *newEnt)
{
    ROUTE_Info **ents;
    ROUTE_EntryArrayKey oldKey, newKey;
    int error;

    ITS_TRACE_CRITICAL(("AddEntry: type %d key %08x\n", type, key));

    /* lock the table */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_ROUTE_ARRAYS) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("AddEntry: Unable to lock DSM_TABLE_ROUTE_ARRAYS\n"));
        return (ITS_FALSE);
    }

    /* generate the old key info */
    oldKey.type = type;
    oldKey.niDPC = key;
    oldKey.numEntries = dest->maxEntries;

    /* if we don't need to grow, just bail out */
    if (dest->maxEntries && (dest->numEntries < dest->maxEntries - 1 ))
    {
        if (type != ENT_TYPE_ROUTE)
        {
            dest->entries[dest->numEntries] = newEnt;
            dest->numEntries++;
        }
        else
        {
            AddSortedRoute(dest, newEnt);
        }

        DSM_CommitNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_ROUTE_ARRAYS,
                         (ITS_OCTET *)&oldKey,
                         sizeof(ROUTE_EntryArrayKey),
                         dest->entries);

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

        return (ITS_TRUE);
    }

    if (dest->maxEntries)
    {
        dest->maxEntries <<= 1;
    }
    else
    {
        dest->maxEntries = INIT_MAX_ENT;
    }

    newKey.type = type;
    newKey.niDPC = key;
    newKey.numEntries = dest->maxEntries;

    /* sanity check 1: make sure the new entry doesn't already exist */
    ents = (ROUTE_Info **)DSM_FindNoLock(DSM_RoutingFtGroupId,
                                         DSM_TABLE_ROUTE_ARRAYS,
                                         (ITS_OCTET *)&newKey,
                                         sizeof(ROUTE_EntryArrayKey),
                                         &error);

    if (error != ITS_ENOTFOUND ||
        (error == ITS_SUCCESS && ents != NULL))
    {
        ITS_TRACE_CRITICAL(("AddEntry:  Entry either duplicate or not found table DSM_TABLE_ROUTE_ARRAYS %d new key\n",error));
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

        return (ITS_FALSE);
    }

    /* sanity check 2: make sure the old entry matches what's in the dest */
    ents = (ROUTE_Info **)DSM_FindNoLock(DSM_RoutingFtGroupId,
                                         DSM_TABLE_ROUTE_ARRAYS,
                                         (ITS_OCTET *)&oldKey,
                                         sizeof(ROUTE_EntryArrayKey),
                                         &error);

    /* NOTE: entries may be NULL */
    if (ents != dest->entries)
    {
        ITS_TRACE_CRITICAL(("AddEntry:  Entry not match DSM_TABLE_ROUTE_ARRAYS %d old key\n",error));
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

        return (ITS_FALSE);
    }

    /* allocate the new entries */
    ents = (ROUTE_Info **)DSM_AllocNoLock(DSM_RoutingFtGroupId,
                                          DSM_TABLE_ROUTE_ARRAYS,
                                          (ITS_OCTET *)&newKey,
                                          sizeof(ROUTE_EntryArrayKey),
                                          sizeof(ROUTE_Info *) * newKey.numEntries,
                                          &error);

    if (error != ITS_SUCCESS || ents ==NULL)
    {
        ITS_TRACE_CRITICAL(("AddEntry:  Unable to allocate DSM_TABLE_ROUTE_ARRAYS %d \n",error));
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

        return (ITS_FALSE);
    }

    /* copy over the old entries */
    if (dest->entries )
    {
        memcpy(ents, dest->entries, sizeof(ROUTE_Info *) * oldKey.numEntries);
    }

    /* release the old range */
    if (dest->entries)
    {
        DSM_FreeNoLock(DSM_RoutingFtGroupId,
                       DSM_TABLE_ROUTE_ARRAYS,
                       (ITS_OCTET *)&oldKey,
                       sizeof(ROUTE_EntryArrayKey),
                       dest->entries);
    }

    /* set new array */
    dest->entries = ents;

    /* add the new element */
    if (type != ENT_TYPE_ROUTE)
    {
        dest->entries[dest->numEntries] = newEnt;
        dest->numEntries++;
    }
    else
    {
        AddSortedRoute(dest, newEnt);
    }

    /* commit the new array */
    DSM_CommitNoLock(DSM_RoutingFtGroupId,
                     DSM_TABLE_ROUTE_ARRAYS,
                     (ITS_OCTET *)&newKey,
                     sizeof(ROUTE_EntryArrayKey),
                     ents);

    /* unlock the table */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an entry from the array
 *
 *  Input Parameters:
 *      type - RKEY, RCONT, or ROUTE
 *      key - table primary key
 *      dest - destination involved
 *      idx - index of entry to remove
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      It is assumed that the caller commits changes this function
 *      makes to the destination.
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
RemEntry(ITS_UINT type, ITS_UINT key, SS7_Destination *dest,
         ITS_UINT idx)
{
    ROUTE_EntryArrayKey oldKey;
    ROUTE_Info **ents;
    int error, i;

    /* lock the table */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_ROUTE_ARRAYS) != ITS_SUCCESS)
    {
        return (ITS_FALSE);
    }

    /* generate the old key info */
    oldKey.type = type;
    oldKey.niDPC = key;
    oldKey.numEntries = dest->maxEntries;

    /* sanity check: make sure entry matches */
    ents = (ROUTE_Info **)DSM_FindNoLock(DSM_RoutingFtGroupId,
                                         DSM_TABLE_ROUTE_ARRAYS,
                                         (ITS_OCTET *)&oldKey,
                                         sizeof(ROUTE_EntryArrayKey),
                                         &error);

    if (error == ITS_ENOTFOUND ||
        (error == ITS_SUCCESS && ents != dest->entries))
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

        return (ITS_FALSE);
    }

    /* delete the entry */
    if (idx < dest->numEntries - 1)
    {
        memmove(&dest->entries[idx],
                &dest->entries[idx+1],
                (dest->numEntries - 1 - idx) * sizeof(ROUTE_Info *));
    }

    dest->numEntries--;

    /* need to update destination status if no other via this
     * destination is up
     */
    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->entries[i]->linkSet->isUp)
        {
            dest->status = DESTINATION_AVAILABLE; 
            break;
        }
    }

    if (i == dest->numEntries)
    {
        dest->status = DESTINATION_UNAVAILABLE;
    }

    if (dest->numEntries > 0)
    {
        /* commit the new array */
        DSM_CommitNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_ROUTE_ARRAYS,
                         (ITS_OCTET *)&oldKey,
                         sizeof(ROUTE_EntryArrayKey),
                         ents);
    }
    else
    {
        DSM_FreeNoLock(DSM_RoutingFtGroupId,
                       DSM_TABLE_ROUTE_ARRAYS,
                       (ITS_OCTET *)&oldKey,
                       sizeof(ROUTE_EntryArrayKey),
                       ents);

        dest->entries = NULL;
    }

    /* unlock the table */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function searches an array for an already present entry.
 *
 *  Input Parameters:
 *      dest - destination involved
 *      entry - entry to find
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      It is assumed that the caller commits changes this function
 *      makes to the destination.
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
EntryExists(ITS_UINT type, ITS_UINT key, SS7_Destination *dest,
            ROUTE_Info *rinfo, ITS_UINT *which)
{
    ROUTE_EntryArrayKey oldKey;
    ROUTE_Info **ents;
    ITS_UINT i;
    int error;

    /* locking */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_ROUTE_ARRAYS) != ITS_SUCCESS)
    {
        return (ITS_FALSE);
    }

    /* generate the old key info */
    oldKey.type = type;
    oldKey.niDPC = key;
    oldKey.numEntries = dest->maxEntries;

    /* sanity check: make sure entry matches */
    ents = (ROUTE_Info **)DSM_FindNoLock(DSM_RoutingFtGroupId,
                                         DSM_TABLE_ROUTE_ARRAYS,
                                         (ITS_OCTET *)&oldKey,
                                         sizeof(ROUTE_EntryArrayKey),
                                         &error);

    if (error != ITS_SUCCESS || ents != dest->entries)
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

        return (ITS_FALSE);
    }

    /* Need to lock the route table */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_ROUTES) != ITS_SUCCESS)
    {
        return (ITS_FALSE);
    }

    /* sanity check: matching pointers */
    for (i = 0; i < dest->numEntries; i++)
    {
        if (RouteInfoMatches(dest->entries[i], rinfo) == 0)
        {
            ITS_TRACE_DEBUG(("EntryExists: duplicate route info.\n"));

            *which = dest->entries[i]->rkey;

            DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

            DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

            return (ITS_TRUE);
        }
    }

    /* unlock the tables */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTE_ARRAYS);

    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function selects a destination transport based on the
 *      contents of the ROUTE_MatchInfo structure passed to it.
 *
 *  Input Parameters:
 *      rinfo - information to base the routing decision on.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_INVALID_SRC, ITS_NO_SRC - can't route.
 *      any other value is a transport identifier.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_USHORT
SelectRouteContext(ROUTE_MatchInfo *rinfo, ITS_EVENT *ev)
{
    ITS_USHORT ret;

    ITS_TRACE_DEBUG(("SelectRouteContext\n"));

    if (RWLOCK_LockShared(&selectorGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SelectRouteContext: couldn't acquire "
                         "selector mutex\n"));
    }

    ret = (*ss7Select)(rinfo, ev);

    ITS_TRACE_DEBUG(("SelectRouteContext: routeSelector returned %04x\n",
                     ret));

    RWLOCK_UnlockShared(&selectorGate);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function converts a varargs list into the ROUTE_Info data
 *      structure.
 *
 *  Input Parameters:
 *      rinfo - structure to parse into
 *      type - route type
 *      style - routing style
 *      alist - the args to parse
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ParseBasicRouteInfo(ROUTE_BasicInfo *rinfo, ITS_UINT pointCode,
                    ROUTE_TYPE type, ROUTE_CRITERIA style,
                    SS7_Family family, va_list *alist)
{
    ITS_TRACE_DEBUG(("ParseRouteInfo\n"));

    /* static info */
    rinfo->type = type;
    rinfo->style = style;
    rinfo->dpc = pointCode;
    rinfo->family = family;

    /* collected info */
    switch (style)
    {
    case ROUTE_DPC_NI:
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT) &
                                ROUTE_NI_MASK;
        break;

    case ROUTE_DPC_OPC_NI:
        rinfo->criteria.opc = va_arg(*alist, ITS_UINT);
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT) &
                                ROUTE_NI_MASK;
        break;

    case ROUTE_DPC_SIO:
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_OPC_SIO:
        rinfo->criteria.opc = va_arg(*alist, ITS_UINT);
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_SIO_SSN:
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_SCCP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.ssn = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_OPC_SIO_SSN:
        rinfo->criteria.opc = va_arg(*alist, ITS_UINT);
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_SCCP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.ssn = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_SIO_CIC:
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_ISUP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.cic = (ITS_USHORT)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        rinfo->criteria.opc = va_arg(*alist, ITS_UINT);
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_ISUP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.cic = (ITS_USHORT)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_SIO_SSN_RANGE:
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_SCCP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.range.begin = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        rinfo->criteria.range.end = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
        rinfo->criteria.opc = va_arg(*alist, ITS_UINT);
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_SCCP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.range.begin = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        rinfo->criteria.range.end = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_SIO_CIC_RANGE:
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_ISUP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.range.begin = (ITS_USHORT)va_arg(*alist, ITS_UINT);
        rinfo->criteria.range.end = (ITS_USHORT)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        rinfo->criteria.opc = va_arg(*alist, ITS_UINT);
        rinfo->criteria.sio = (ITS_OCTET)va_arg(*alist, ITS_UINT);
        if ((rinfo->criteria.sio & ROUTE_UP_MASK) != ROUTE_SIO_ISUP)
        {
            return (ITS_EINVALIDARGS);
        }
        rinfo->criteria.range.begin = (ITS_USHORT)va_arg(*alist, ITS_UINT);
        rinfo->criteria.range.end = (ITS_USHORT)va_arg(*alist, ITS_UINT);
        break;

    case ROUTE_DPC_UDEF:
    default:
        rinfo->criteria.userDefined = va_arg(*alist, ITS_OCTET *);
        break;

    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function converts a varargs list into the ROUTE_Info data
 *      structure.
 *
 *  Input Parameters:
 *      rinfo - structure to parse into
 *      type - route type
 *      style - routing style
 *      alist - the args to parse
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_ParseRouteMatchInfo(ROUTE_MatchInfo *rinfo, ITS_UINT pointCode,
                          ROUTE_TYPE type, ROUTE_CRITERIA style,
                          SS7_Family family, va_list *alist)
{
    int ret;

    if ((ret = ParseBasicRouteInfo(&rinfo->basic, pointCode,
                                   type, style,
                                   family, alist)) != ITS_SUCCESS)
    {
        return (ret);
    }

    rinfo->linkSet = (ITS_OCTET)va_arg(*alist, ITS_UINT);
    rinfo->linkCode = (ITS_OCTET)va_arg(*alist, ITS_UINT);
    rinfo->priority = (ITS_OCTET)va_arg(*alist, ITS_UINT);
    rinfo->sls = (ITS_OCTET)va_arg(*alist, ITS_UINT);
    rinfo->rkey = (ITS_UINT)va_arg(*alist, ITS_UINT);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function converts a varargs list into the ROUTE_Info data
 *      structure.
 *
 *  Input Parameters:
 *      rinfo - structure to parse into
 *      type - route type
 *      style - routing style
 *      alist - the args to parse
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_ParseRouteMatchInfoArgs(ROUTE_MatchInfo *rinfo, ITS_UINT pointCode,
                              ROUTE_TYPE type, ROUTE_CRITERIA style,
                              SS7_Family family, ...)
{
    va_list alist;
    int ret;

    va_start(alist, family);

    ret = ROUTE_ParseRouteMatchInfo(rinfo, pointCode, type, style,
                                    family, &alist);

    va_end(alist);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a routing key
 *
 *  Input Parameters:
 *      rkey - the key to add
 *      rinfo - the routing info to add
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_AddRoutingKeyInfo(ITS_UINT rkey, ROUTE_MatchInfo *add)
{
    SS7_Destination *ent, *ent2;
    ROUTE_Info *tmp, *tmp2, ri;
    ITS_UINT key, which;
    int error;

    /* Routing keys do not have a linkSet so set the linkSet ptr to NULL
       Refer: AddOneRoute
    */
    ri.basic = add->basic;
    ri.linkSet = NULL;
    ri.priority = add->priority;

    ITS_TRACE_DEBUG(("AddRoutingKeyInfo: rkey %d %d\n", rkey, add->rkey));

    /* find by point code */
    ent = (SS7_Destination *)DSM_Find(DSM_RoutingFtGroupId, 
                                      DSM_TABLE_RKEYS,
                                      (ITS_OCTET *)&rkey,
                                      sizeof(ITS_UINT),
                                      &error);

    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        ent = (SS7_Destination *)DSM_Alloc(DSM_RoutingFtGroupId,
                                           DSM_TABLE_RKEYS,
                                           (ITS_OCTET *)&rkey,
                                           sizeof(ITS_UINT),
                                           sizeof(SS7_Destination),
                                           &error);

        if (error != ITS_SUCCESS || ent == NULL)
        {
            ITS_TRACE_ERROR(("AddRoutingKeyInfo: Out of memory\n"));

            return (ITS_ENOMEM);
        }
    }
    else if (error != ITS_SUCCESS || ent == NULL)
    {
        ITS_TRACE_ERROR(("Couldn't find/create dest\n"));

        return (ITS_ENOMEM);
    }

    /* if the entry already exists, it's a duplicate */
    if (EntryExists(ENT_TYPE_RKEY, rkey, ent, &ri, &which))
    {
        /* In a muti-node configuration duplicate entries are common */

        ITS_TRACE_WARNING(("ROUTE_AddRoutingKeyInfo: Duplicate Entry\n"));

        DSM_Commit(DSM_RoutingFtGroupId,
                   DSM_TABLE_RKEYS,
                   (ITS_OCTET *)&rkey,
                   sizeof(ITS_UINT),
                   ent);

        return (!ITS_SUCCESS);
    }

    tmp = AddOneRoute(ENT_TYPE_RKEY, rkey, add, rkey, ent);
    if (tmp == NULL)
    {
        ITS_TRACE_ERROR(("Out of memory\n"));

        return (ITS_ENOMEM);
    }

    /* add the entry */
    if (!AddEntry(ENT_TYPE_RKEY, rkey, ent, tmp))
    {
        ITS_TRACE_ERROR(("AddRoutingKeyInfo: Out of memory\n"));

        DelOneRoute(ENT_TYPE_RKEY, rkey, rkey);

        DSM_Free(DSM_RoutingFtGroupId,
                 DSM_TABLE_RKEYS,
                 (ITS_OCTET *)&rkey,
                 sizeof(ITS_UINT),
                 ent);

        return (ITS_ENOMEM);
    }

    /* NOTE: we delay the commit of ent until we know the key has been added */

    /* work out the pkey */
    key = add->basic.dpc |
            ((add->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
            (add->basic.family << 24);

    /* find by point code */
    ent2 = DSM_Find(DSM_RoutingFtGroupId,
                    DSM_TABLE_RCONTEXTS,
                    (ITS_OCTET *)&key,
                    sizeof(ITS_UINT),
                    &error);

    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        ent2 = (SS7_Destination *)DSM_Alloc(DSM_RoutingFtGroupId,
                                            DSM_TABLE_RCONTEXTS,
                                            (ITS_OCTET *)&key,
                                            sizeof(ITS_UINT),
                                            sizeof(SS7_Destination),
                                            &error);

        if (error != ITS_SUCCESS || ent2 == NULL)
        {
            DelOneRoute(ENT_TYPE_RKEY, rkey, rkey);

            RemEntry(ENT_TYPE_RKEY, rkey, ent, 0);

            DSM_Free(DSM_RoutingFtGroupId,
                     DSM_TABLE_RKEYS,
                     (ITS_OCTET *)&rkey,
                     sizeof(ITS_UINT),
                     ent);

            return (ITS_ENOMEM);
        }
    }
    else if (error != ITS_SUCCESS || ent2 == NULL)
    {
        DelOneRoute(ENT_TYPE_RKEY, rkey, rkey);

        RemEntry(ENT_TYPE_RKEY, rkey, ent, 0);

        DSM_Free(DSM_RoutingFtGroupId,
                 DSM_TABLE_RKEYS,
                 (ITS_OCTET *)&rkey,
                 sizeof(ITS_UINT),
                 ent);

        return (ITS_ENOMEM);
    }

    /* add the entry for RCONT */
    tmp2 = AddOneRoute(ENT_TYPE_RCONT, key, add, rkey, ent2);
    if (tmp2 == NULL)
    {
        DelOneRoute(ENT_TYPE_RKEY, rkey, rkey);

        RemEntry(ENT_TYPE_RKEY, rkey, ent, 0);

        DSM_Free(DSM_RoutingFtGroupId,
                 DSM_TABLE_RKEYS,
                 (ITS_OCTET *)&rkey,
                 sizeof(ITS_UINT),
                 ent);

        return (ITS_ENOMEM);
    }

    if (!AddEntry(ENT_TYPE_RCONT, key, ent2, tmp2))
    {
        DSM_Commit(DSM_RoutingFtGroupId,
                   DSM_TABLE_RCONTEXTS,
                   (ITS_OCTET *)&key,
                   sizeof(ITS_UINT),
                   ent2);

        DelOneRoute(ENT_TYPE_RCONT, key, rkey);
        DelOneRoute(ENT_TYPE_RKEY, rkey, rkey);

        RemEntry(ENT_TYPE_RKEY, rkey, ent, 0);

        DSM_Free(DSM_RoutingFtGroupId,
                 DSM_TABLE_RKEYS,
                 (ITS_OCTET *)&rkey,
                 sizeof(ITS_UINT),
                 ent);

        return (ITS_ENOMEM);
    }

    /* commit the destinations */
    DSM_Commit(DSM_RoutingFtGroupId,
               DSM_TABLE_RKEYS,
               (ITS_OCTET *)&rkey,
               sizeof(ITS_UINT),
               ent);

    DSM_Commit(DSM_RoutingFtGroupId,
               DSM_TABLE_RCONTEXTS,
               (ITS_OCTET *)&key,
               sizeof(ITS_UINT),
               ent2);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a routing key
 *
 *  Input Parameters:
 *      rkey - the key to add
 *      pointCode - the point code
 *      style - the routing style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_AddRoutingKey(ITS_UINT rkey, ITS_UINT pointCode,
                    ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("ROUTE_AddRoutingKey: rkey %d\n", rkey));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_AddRoutingKeyInfo(rkey, &rinfo);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a particular routing key
 *
 *  Input Parameters:
 *      rkey - the key to add
 *      pointCode - the point code
 *      style - the routing style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *      The lock MUST be held before calling this.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_FindRoutingKeyInfo(ITS_UINT rkey, ROUTE_Info ***rinfo)
{
    SS7_Destination *ent;
    int error;

    ITS_TRACE_DEBUG(("FindRoutingKey\n"));

    /* find by rkey */
    ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_RKEYS,
                         (ITS_OCTET *)&rkey,
                         sizeof(ITS_UINT),
                         &error);

    if (error != ITS_SUCCESS || ent == NULL)
    {
        ITS_TRACE_ERROR(("FindRoutingKeyInfo: Hash error.\n"));

        return (ITS_ENOTFOUND);
    }

    *rinfo = ent->entries;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a particular routing key by route information
 *
 *  Input Parameters:
 *      rinfo - the ROUTE_Info to find
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      rkey - the key of the info
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_FindRoutingKeyByInfo(ITS_UINT *rkey, ROUTE_MatchInfo *rinfo)
{
    SS7_Destination *ent;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    ITS_UINT key;
    int error;

    ITS_TRACE_DEBUG(("FindRoutingKeyByInfo\n"));

    DumpRouteMatchInfo(rinfo);

    /* lock the gate */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_RCONTEXTS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* work out the pkey */
    key = rinfo->basic.dpc |
            ((rinfo->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
            (rinfo->basic.family << 24);

    /* find by point code */
    ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_RCONTEXTS,
                         (ITS_OCTET *)&key,
                         sizeof(ITS_UINT),
                         &error);

    if (error != ITS_SUCCESS || ent == NULL)
    {
        ITS_TRACE_WARNING(("FindRoutingKeyByInfo: entry not found.\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);

        return (ITS_ENOTFOUND);
    }

    ent = FindBestMatchOfEntry(ent, rinfo,
                               &whichEntry, &firstMatch, &lastMatch,
                               &whichLinkCode,
                               ITS_TRUE, ITS_TRUE);

    if (ent == NULL || whichEntry < 0)
    {
        ITS_TRACE_DEBUG(("Match not found\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);

        return (ITS_ENOTFOUND);
    }

    if (ent->entries[whichEntry]->basic.type == ROUTING_KEY_ROUTE)
    {
        *rkey = ent->entries[whichEntry]->rkey;

        ITS_TRACE_DEBUG(("Return key of %d\n", *rkey));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);

        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_DEBUG(("Routing key not found\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);

        return (ITS_ENOTFOUND);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a particular routing key varargs
 *
 *  Input Parameters:
 *      pointCode - the point code
 *      type - the route type
 *      style - the routing style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      rkey - the key to find
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was found.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_FindRoutingKey(ITS_UINT *rkey, ITS_UINT pointCode,
                     ROUTE_TYPE type, ROUTE_CRITERIA style,
                     SS7_Family family, ...)
{
    va_list alist;
    ROUTE_MatchInfo rinfo;
    int ret;

    ITS_TRACE_DEBUG(("FindRoutingKey\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, type,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    ret = ROUTE_FindRoutingKeyByInfo(rkey, &rinfo);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a particular routing key
 *
 *  Input Parameters:
 *      rkey - the key to add
 *      pointCode - the point code
 *      style - the routing style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_DeleteRoutingKey(ITS_UINT rkey)
{
    SS7_Destination *ent, *ent2;
    ITS_UINT key;
    int error;

    ITS_TRACE_DEBUG(("DeleteRoutingKey\n"));

    /* lock the gate */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_RKEYS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* find by rkey */
    ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_RKEYS,
                         (ITS_OCTET *)&rkey,
                         sizeof(ITS_UINT),
                         &error);

    if (error != ITS_SUCCESS || ent == NULL)
    {
        ITS_TRACE_ERROR(("DeleteRoutingKey: Hash error.\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RKEYS);

        return (ITS_ENOTFOUND);
    }

    /* FIXME: racy */
    key = ent->entries[0]->basic.dpc | 
            ((ent->entries[0]->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
            (ent->entries[0]->basic.family << 24);

    /* delete it */
    RemEntry(ENT_TYPE_RKEY, rkey, ent, 0);

    DelOneRoute(ENT_TYPE_RKEY, rkey, rkey);

    DSM_FreeNoLock(DSM_RoutingFtGroupId,
                   DSM_TABLE_RKEYS,
                   (ITS_OCTET *)&rkey,
                   sizeof(ITS_UINT),
                   ent);

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RKEYS);

    /* now hit the other table */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_RCONTEXTS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* find by rcont */
    ent2 = DSM_FindNoLock(DSM_RoutingFtGroupId,
                          DSM_TABLE_RCONTEXTS,
                          (ITS_OCTET *)&key,
                          sizeof(ITS_UINT),
                          &error);

    if (error != ITS_SUCCESS || ent == NULL)
    {
        ITS_TRACE_ERROR(("DeleteRoutingKey: Hash error.\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);

        return (ITS_ENOTFOUND);
    }

    RemEntry(ENT_TYPE_RCONT, key, ent2, rkey);

    DelOneRoute(ENT_TYPE_RCONT, key, rkey);

    if (ent2->numEntries > 0)
    {
        DSM_CommitNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_RCONTEXTS,
                         (ITS_OCTET *)&key,
                         sizeof(ITS_UINT),
                         ent2);
    }
    else
    {
        DSM_FreeNoLock(DSM_RoutingFtGroupId,
                       DSM_TABLE_RCONTEXTS,
                       (ITS_OCTET *)&key,
                       sizeof(ITS_UINT),
                       ent2);
    }

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add a mask for lookup.
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
MaskOrder(const void *m1, const void *m2)
{
    ITS_UINT *a = (ITS_UINT *)m1;
    ITS_UINT *b = (ITS_UINT *)m2;

    return ((*b) - (*a));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add a mask for lookup.
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
AddMask(ITS_UINT mask)
{
    ITS_UINT i;

    ITS_TRACE_DEBUG(("Adding mask %08x\n", mask));

    ITS_C_ASSERT(mask <= ITS_SS7_DEFAULT_ROUTE_MASK);

    for (i = 0; i < numMasks; i++)
    {
        if (masks[i] == mask)
        {
            return;
        }
    }

    ITS_C_ASSERT(numMasks < ROUTE_MAX_MASKS);

    masks[numMasks] = mask;
    numMasks++;

    qsort(masks, numMasks, sizeof(ITS_UINT), MaskOrder);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add the route context identified by "add"
 *
 *  Input Parameters:
 *      add - the ROUTE_SS7Entry to add.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      an error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_AddRouteContext().
 ****************************************************************************/
ITSDLLAPI int
ROUTE_AddRouteContextInfo(ROUTE_MatchInfo *rinfo)
{
    SS7_Destination *ent;
    ROUTE_Info *add, ri;
    ITS_UINT key, which;
    int error;
    int i;

    ITS_TRACE_CRITICAL(("AddRouteContextInfo:\n"));

    /* collect what we need */
    ri.basic = rinfo->basic;
    ri.linkSet = LINKSET_FindLinkSet(rinfo->linkSet);
    ri.priority = rinfo->priority;

    /* work out the pkey */
    key = rinfo->basic.dpc |
            ((rinfo->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
            (rinfo->basic.family << 24);
    /* lock the gate */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("AddRouteContextInfo: Unable to Lock DSM_TABLE_DESTINATIONS\n"));
        return (ITS_EBADMUTEX);
    }

    /* maybe add the mask */
    AddMask(rinfo->basic.mask);

    /* find by point code */
    ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_DESTINATIONS,
                         (ITS_OCTET *)&key,
                         sizeof(ITS_UINT),
                         &error);

    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        ent = (SS7_Destination *)DSM_AllocNoLock(DSM_RoutingFtGroupId,
                                                 DSM_TABLE_DESTINATIONS,
                                                 (ITS_OCTET *)&key,
                                                 sizeof(ITS_UINT),
                                                 sizeof(SS7_Destination),
                                                 &error);

        if (error != ITS_SUCCESS || ent == NULL)
        {
            ITS_TRACE_ERROR(("AddRoute: Out of memory\n"));

            DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

            return (ITS_ENOMEM);
        }

        /* Now Initialise Pegs for this DPC */
        for (i = 0; i < PEG_MTP3_DPC_NUM_PEGS; i++)
        {
            ent->pegs[i] = 0;
        }
        ent->MTP3_DPC_PEGS.name = "MTP3-Route";
        ent->MTP3_DPC_PEGS.numPegs =
                            sizeof(ent->pegs) / sizeof(ITS_UINT);
        ent->MTP3_DPC_PEGS.pegs = ent->pegs;

    }
    else if (error != ITS_SUCCESS || ent == NULL)
    {
        ITS_TRACE_CRITICAL(("AddRouteContextInfo: Entry already present for DSM_TABLE_DESTINATIONS\n"));
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return (ITS_ENOMEM);
    }

    /* if the entry already exists, it's a duplicate */
    if (EntryExists(ENT_TYPE_ROUTE, key, ent, &ri, &which))
    {
        /* In a muti-node configuration duplicate entries are common */
        
        ITS_TRACE_CRITICAL(("ROUTE_AddRouteContextInfo: Duplicate Entry\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);
  
        return (!ITS_SUCCESS);
    }

    ent->nextRoute++;
    add = AddOneRoute(ENT_TYPE_ROUTE, key, rinfo, ent->nextRoute, ent);
    if (add ==  NULL)
    {
        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);
        ITS_TRACE_CRITICAL(("ROUTE_AddRouteContextInfo:  Cannot Add Route"));
        return ITS_ENOMEM;
    }

    DumpRouteInfo(add);

    /* expand if necessary */
    if (!AddEntry(ENT_TYPE_ROUTE, key, ent, add))
    {
        ITS_TRACE_CRITICAL(("ROUTE_AddRouteContextInfo: Cannot Add Entry\n"));
        DelOneRoute(ENT_TYPE_ROUTE, key, ent->nextRoute);

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return (ITS_ENOMEM);
    }

    ITS_C_ASSERT(add->dest != NULL);

    /* commit changes */
    DSM_CommitNoLock(DSM_RoutingFtGroupId,
                     DSM_TABLE_DESTINATIONS,
                     (ITS_OCTET *)&key,
                     sizeof(ITS_UINT),
                     ent);

    /* let go of the gate */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a routing entry
 *
 *  Input Parameters:
 *      id - the transport to add this route for
 *      pointCode - the DPC.
 *      type - local, remote, concerned or duplicate
 *      style - the route style
 *      ... - determined by the route style
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was added.  Any other value indicates
 *      a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_AddRouteContextInfo()
 ****************************************************************************/
ITSDLLAPI int
ROUTE_AddRouteContext(ITS_UINT pointCode,
                      ROUTE_TYPE type, ROUTE_CRITERIA style,
                      SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("ROUTE_AddRouteContext:\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, type,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_AddRouteContextInfo(&rinfo);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Select a transport based on routing information.
 *
 *  Input Parameters:
 *      rinfo - the routing information for the decision
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_INVALID_SRC, ITS_NO_SRC - no route could be found.
 *      Any other return value is the transport id that matches the selection.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SelectRouteContext()
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_SelectRouteContextInfo(ROUTE_MatchInfo *rinfo)
{
    return SelectRouteContext(rinfo, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Select a destination transport based on routing information.
 *
 *  Input Parameters:
 *      pointCode - the DPC
 *      style - the route style
 *      ... - determined by the route style.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_INVALID_SRC, ITS_NO_SRC - no route could be found.
 *      Any other return value is the transport id that matches the selection.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SelectRouteContextInfo()
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_SelectRouteContext(ITS_UINT pointCode, ROUTE_CRITERIA style,
                         SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("SelectRouteContext\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_INVALID_SRC);
    }

    va_end(alist);

    return ROUTE_SelectRouteContextInfo(&rinfo);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a destination based on routing information
 *
 *  Input Parameters:
 *      pointCode - the DPC
 *      ni - network indicator
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      A pointer to the destination.  The caller should hold the
 *      route table lock.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI SS7_Destination *
ROUTE_FindDestination(ITS_UINT pointCode, ITS_OCTET ni, SS7_Family family)
{
    ITS_UINT key;
    SS7_Destination *ent;
    int error;

    /* work out the pkey */
    key = pointCode | ((ni & ROUTE_NI_MASK) << 24) | (family << 24);

    ent = NULL;

    ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_DESTINATIONS,
                         (ITS_OCTET *)&key,
                         sizeof(ITS_UINT),
                         &error);

    if (error != ITS_SUCCESS)
    {
        return (NULL);
    }

    return (ent);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit destination information.
 *
 *  Input Parameters:
 *      pointCode - the DPC
 *      ni - network indicator
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      A pointer to the destination.  The caller should hold the
 *      route table lock.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_CommitDestination(SS7_Destination *dest,
                        ITS_UINT dpc, ITS_OCTET ni,
                        SS7_Family family)
{
    ITS_UINT key;
    int ret;

    /* work out the pkey */
    key = dpc | ((ni & ROUTE_NI_MASK) << 24) | (family << 24);

    ret = DSM_CommitNoLock(DSM_RoutingFtGroupId,
                           DSM_TABLE_DESTINATIONS,
                           (ITS_OCTET *)&key,
                           sizeof(ITS_UINT),
                           dest);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit destination information.
 *
 *  Input Parameters:
 *      pointCode - the DPC
 *      ni - network indicator
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      A pointer to the destination.  The caller should hold the
 *      route table lock.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_CommitRoute(ROUTE_Info *rinfo)
{
    ROUTE_EntryKey newKey;
    ROUTE_Info *rEntry;
    int ret, error;

    /* initialize the key */
    newKey.type = ENT_TYPE_ROUTE;
    newKey.niDPC = rinfo->basic.dpc |
                    ((rinfo->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
                    (rinfo->basic.family << 24);
    newKey.fakeIndex = rinfo->rkey;

    rEntry = (ROUTE_Info *) DSM_FindNoLock(DSM_RoutingFtGroupId,
                                           DSM_TABLE_ROUTES,
                                          (ITS_OCTET *)&newKey,
                                          sizeof(ROUTE_EntryKey),
                                          &error);

    if (error != ITS_SUCCESS || rEntry == NULL)
    {
        ITS_TRACE_ERROR(("ROUTE_CommitRoute: Error Cannot Find RouteEntry\n"));
        return ITS_SUCCESS;
    }

    ret = DSM_CommitNoLock(DSM_RoutingFtGroupId,
                           DSM_TABLE_ROUTES,
                           (ITS_OCTET *)&newKey,
                           sizeof(ROUTE_EntryKey),
                           rEntry);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete a route context
 *
 *  Input Parameters:
 *      id - the transport to delete the route from
 *      rinfo - the route info to delete
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was successfully removed.  Any other return
 *      value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_DeleteRouteContext()
 ****************************************************************************/
ITSDLLAPI int
ROUTE_DeleteRouteContextInfo(ROUTE_MatchInfo *rinfo)
{
    SS7_Destination *ent;
    ROUTE_Info ri;
    ITS_UINT key, which;
    ITS_BOOLEAN found = ITS_FALSE;
    int error, i;

    ITS_TRACE_DEBUG(("DeleteRouteContextInfo\n"));

    ri.basic = rinfo->basic;
    ri.linkSet = LINKSET_FindLinkSet(rinfo->linkSet);
    ri.priority = rinfo->priority;

    /* work out the pkey */
    key = rinfo->basic.dpc |
            ((rinfo->basic.criteria.sio & ROUTE_NI_MASK) << 24) |
            (rinfo->basic.family << 24);
    /* lock the gate */
    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* this is easier.  We require exact matches */
    ent = DSM_FindNoLock(DSM_RoutingFtGroupId,
                         DSM_TABLE_DESTINATIONS,
                         (ITS_OCTET *)&key,
                         sizeof(ITS_UINT),
                         &error);

    if (error == ITS_SUCCESS && ent != NULL)
    {
        if (EntryExists(ENT_TYPE_ROUTE, key, ent, &ri, &which))
        {
            int idx = 0;

            DelOneRoute(ENT_TYPE_ROUTE, key, which);

            /* The index to the entry must be passed to
             * RemEntry, not the rkey.
             */
            for (i = 0; i < ent->numEntries; i++)
            {
                if (ent->entries[i]->rkey == which)
                {
                   idx = i;
                }
            }

            RemEntry(ENT_TYPE_ROUTE, key, ent, idx);

            if (ent->numEntries == 0)
            {
                DSM_FreeNoLock(DSM_RoutingFtGroupId,
                              DSM_TABLE_DESTINATIONS,
                               (ITS_OCTET *)&key,
                               sizeof(ITS_UINT),
                               ent);
            }
            else
            {
                DSM_CommitNoLock(DSM_RoutingFtGroupId,
                                 DSM_TABLE_DESTINATIONS,
                                 (ITS_OCTET *)&key,
                                 sizeof(ITS_UINT),
                                 ent);
            }
            found = ITS_TRUE; 
        }
    }

    /* let go of the gate */
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

    if (found)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        return (ITS_ENOTFOUND);
    } 

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the route was successfully removed.  Any other return
 *      value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_DeleteRouteContextInfo()
 ****************************************************************************/
ITSDLLAPI int
ROUTE_DeleteRouteContext(ITS_UINT pointCode,
                         ROUTE_TYPE type, ROUTE_CRITERIA style,
                         SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("DeleteRouteContext\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, type,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_DeleteRouteContextInfo(&rinfo);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function delivers an event based on the routing information.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *      ev - the event to deliver
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the event was successfully sent.  Any other return
 *      value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SendToRouteContext()
 ****************************************************************************/
ITSDLLAPI int
ROUTE_SendToRouteContextInfo(ROUTE_MatchInfo *rinfo, ITS_EVENT *ev)
{
    ITS_USHORT dest;

    ITS_TRACE_DEBUG(("SendToRouteContextInfo\n"));

    dest = SelectRouteContext(rinfo, ev);

    if (dest != ITS_NO_SRC && dest != ITS_INVALID_SRC && dest==INode_BT)
    {
        printf("Dest Value for put event to =%x\n",dest);
        return TRANSPORT_PutEvent(dest, ev);
    }

    return (ITS_ENOTRANSPORT);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function sends an event based on the routing information
 *      given.
 *
 *  Input Parameters:
 *      pc - the DPC
 *      ev - the event to deliver
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS - the event was successfully sent.  Any other return
 *      value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SendToRouteContextInfo()
 ****************************************************************************/
ITSDLLAPI int
ROUTE_SendToRouteContext(ITS_UINT pc, ITS_EVENT *ev,
                         ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("SendToRouteContext\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pc, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_SendToRouteContextInfo(&rinfo, ev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function takes a pointCode/SSN pair and attempts to find an
 *      instance/transport that can route to that destination.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If a transport is identified as having a route to this destination,
 *          the transport/instance id is returned.
 *      If no route is available, ITS_NO_SRC is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_RouteContextExists()
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_RouteContextInfoExists(ROUTE_MatchInfo *rinfo)
{
    ITS_USHORT ret;

    ITS_TRACE_DEBUG(("RouteContextInfoExists\n"));

    ret = SelectRouteContext(rinfo, NULL);

    if (ret == ITS_INVALID_SRC)
    {
        return (ITS_NO_SRC);
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function takes a pointCode/SSN pair and attempts to find an
 *      instance/transport that can route to that destination.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If a transport is identified as having a route to this destination,
 *          the transport/instance id is returned.
 *      If no route is available, ITS_NO_SRC is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_RouteContextInfoExists()
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_RouteContextExists(ITS_UINT pointCode, ROUTE_CRITERIA style,
                         SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("RouteContextExists\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_INVALID_SRC);
    }

    va_end(alist);

    return ROUTE_RouteContextInfoExists(&rinfo);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and gets the
 *      paused/resumed state.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isUp - if the dest route is up
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *      Recurses for wild cards.
 *
 *  See Also:
 *      ROUTE_GetRouteContextState()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextInfoState(ROUTE_MatchInfo *rinfo, ITS_BOOLEAN *isUp)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int i;
    ITS_BOOLEAN gotMatch = ITS_FALSE;
    int ret = ITS_SUCCESS;

    ITS_TRACE_DEBUG(("GetRouteContextInfoState\n"));

    DumpRouteMatchInfo(rinfo);

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    if (isUp)
    {
        *isUp = ITS_FALSE;
    }

    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.  Here, we walk the link
     * set and see if even one is up.
     */
    if (tmp != NULL && whichEntry >= 0)
    {
        ITS_TRACE_DEBUG(("Got match\n"));

        /* check 'em */
        for (i = firstMatch; i <= lastMatch; i++)
        {
            gotMatch = ITS_TRUE;

            if (tmp->entries[i]->linkSet->isUp &&
                tmp->entries[i]->isAllowed)
            {
                if (isUp)
                {
                    ITS_TRACE_DEBUG(("IsUp\n"));

                    *isUp = ITS_TRUE;
                }

                break;
            }
        }
    }
    else
    {
        ret = ITS_ENOROUTE;
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return ret;
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and gets the
 *      paused/resumed state.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isUp - if the dest route is up
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextInfoState(), ROUTE_SetRouteContextState()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextState(ITS_UINT pointCode, ITS_BOOLEAN* isUp,
                           ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("GetRouteContextState\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_GetRouteContextInfoState(&rinfo, isUp);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and sets the
 *      paused/resumed state.
 *
 *  Input Parameters:
 *      isUp - if the dest is up
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextState()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteContextInfoState(ROUTE_MatchInfo *rinfo, ITS_BOOLEAN isUp)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;

    ITS_TRACE_DEBUG(("SetRouteContextInfoState\n"));

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.
     */
    if (tmp == NULL || whichEntry < 0)
    {
        ROUTE_UnlockRead(routeRWLock, NULL);

        return (ITS_ENOTFOUND);
    }

    /* check 'em */
    tmp->entries[whichEntry]->linkSet->isUp = isUp;

    LINKSET_CommitLinkSet(tmp->entries[whichEntry]->linkSet);

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and sets the
 *      paused/resumed state.
 *
 *  Input Parameters:
 *      instance - the transport instance to change
 *      isUp - if the dest is up
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextInfoState(), ROUTE_GetRouteContextState()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteContextState(ITS_BOOLEAN isUp,
                           ITS_UINT pointCode, ROUTE_CRITERIA style,
                           SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("SetRouteContextState\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_SetRouteContextInfoState(&rinfo, isUp);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and gets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isAllowed - if the dest route is allowed
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextInfoStatus(ROUTE_MatchInfo *rinfo,
                                ITS_BOOLEAN* isAllowed)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int i;
    ITS_BOOLEAN gotMatch = ITS_FALSE;

    ITS_TRACE_DEBUG(("GetRouteContextInfoStatus\n"));

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    if (isAllowed)
    {
        *isAllowed = ITS_FALSE;
    }

    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.  Here, we walk the link
     * set and see if even one is allowed.
     */
    if (tmp != NULL && whichEntry >= 0)
    {
        /* check 'em */
        for (i = firstMatch; i <= lastMatch; i++)
        {
            ITS_TRACE_DEBUG(("Checking %d\n", i));

            gotMatch = ITS_TRUE;

            if (tmp->entries[i]->isAllowed)
            {
                if (isAllowed)
                {
                    ITS_TRACE_DEBUG(("One is allowed\n"));

                    *isAllowed = ITS_TRUE;
                }

                break;
            }
        }
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    if (gotMatch)
    {
        ITS_TRACE_DEBUG(("Route found but not up\n"));

        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_DEBUG(("No route found\n"));

        return (ITS_ENOROUTE);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and gets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isAllowed - if the dest route is allowed
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextInfoStatus(), ROUTE_SetRouteContextStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextStatus(ITS_UINT pointCode, ITS_BOOLEAN* isAllowed,
                            ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("GetRouteContextStatus\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_GetRouteContextInfoStatus(&rinfo, isAllowed);
}

/*.implementation:extern
 ************************************************************************
*  Purpose:
 *      This method takes routing information and gets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isAllowed - if the dest route is allowed
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteAdminInfoStatus(ROUTE_MatchInfo *rinfo,
                                ITS_BOOLEAN* isUse)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int i;
    ITS_BOOLEAN gotMatch = ITS_FALSE;

    ITS_TRACE_DEBUG(("GetRouteContextInfoStatus\n"));

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    if (isUse)
    {
        *isUse = ITS_FALSE;
    }

    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.  Here, we walk the link
     * set and see if even one is allowed.
     */
    if (tmp != NULL && whichEntry >= 0)
    {
        /* check 'em */
        for (i = firstMatch; i <= lastMatch; i++)
        {
            ITS_TRACE_DEBUG(("Checking %d\n", i));

            gotMatch = ITS_TRUE;

            if (tmp->entries[i]->inUse)
            {
                if (isUse)
                {
                    ITS_TRACE_DEBUG(("One is allowed\n"));

                    *isUse = ITS_TRUE;
                }

                break;
            }
        }
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    if (gotMatch)
    {
        ITS_TRACE_DEBUG(("Route found but not up\n"));

        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_DEBUG(("No route found\n"));

        return (ITS_ENOROUTE);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and gets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isAllowed - if the dest route is allowed
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextInfoStatus(), ROUTE_SetRouteContextStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteAdminStatus(ITS_UINT pointCode, ITS_BOOLEAN* isUse,
                            ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("GetRouteContextStatus\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_GetRouteAdminInfoStatus(&rinfo, isUse);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and sets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *      isAllowed - if the dest is allowed
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextInfoStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteAdminInfoStatus(ROUTE_MatchInfo *rinfo,
                                ITS_BOOLEAN isUse)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;

    ITS_TRACE_DEBUG(("SetRouteContextInfoStatus\n"));

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.
     */
    if (tmp == NULL || whichEntry < 0)
    {
        ROUTE_UnlockWrite(routeRWLock);

        return (ITS_ENOTFOUND);
    }

    /* check 'em */
    tmp->entries[whichEntry]->inUse = isUse;
    ROUTE_CommitRoute(tmp->entries[whichEntry]);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}
/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and sets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      isAllowed - if the dest is allowed
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextStatus(), ROUTE_GetRouteContextStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteAdminStatus(ITS_UINT pointCode, ITS_BOOLEAN isUse,
                            ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("SetRouteContextStatus\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_SetRouteAdminInfoStatus(&rinfo, isUse);
}
/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and sets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *      isAllowed - if the dest is allowed
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextInfoStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteContextInfoStatus(ROUTE_MatchInfo *rinfo,
                                ITS_BOOLEAN isAllowed)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;

    ITS_TRACE_DEBUG(("SetRouteContextInfoStatus\n"));

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.
     */
    if (tmp == NULL || whichEntry < 0)
    {
        ROUTE_UnlockWrite(routeRWLock);

        return (ITS_ENOTFOUND);
    }

    /* check 'em */
    tmp->entries[whichEntry]->isAllowed = isAllowed;
    ROUTE_CommitRoute(tmp->entries[whichEntry]);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing information and sets the
 *      allowed/prohibited state for that route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      isAllowed - if the dest is allowed
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextStatus(), ROUTE_GetRouteContextStatus()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteContextStatus(ITS_UINT pointCode, ITS_BOOLEAN isAllowed,
                            ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("SetRouteContextStatus\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_SetRouteContextInfoStatus(&rinfo, isAllowed);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing info and determines if it is a local
 *      route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isLocal - if the dest is local/remote
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextLocal()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextInfoLocal(ROUTE_MatchInfo *rinfo,
                               ITS_BOOLEAN* isLocal)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;

    ITS_TRACE_DEBUG(("GetRouteContextInfoLocal\n"));

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    if (isLocal)
    {
        *isLocal = ITS_FALSE;
    }

    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.
     */
    if (tmp == NULL || whichEntry < 0)
    {
        ROUTE_UnlockRead(routeRWLock, NULL);

        return (ITS_ENOTFOUND);
    }

    /* check 'em */
    if (tmp->entries[whichEntry]->basic.type == LOCAL_ROUTE)
    {
        if (isLocal)
        {
            *isLocal = ITS_TRUE;
        }
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing info and determines if it is a local
 *      route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      isLocal - if the dest is local/remote
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextInfoLocal()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextLocal(ITS_UINT pointCode, ITS_BOOLEAN* isLocal,
                           ROUTE_CRITERIA style, SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    ITS_TRACE_DEBUG(("GetRouteContextLocal\n"));

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_GetRouteContextInfoLocal(&rinfo, isLocal);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing info and gets the congestion level
 *      for that route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      congLevel - the congestion level
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextCongestion()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextInfoCongestion(ROUTE_MatchInfo *rinfo,
                                    ITS_OCTET* congLevel)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    ITS_BOOLEAN gotMatch = ITS_FALSE;

    ITS_TRACE_DEBUG(("GetRouteContextInfoCongestion\n"));

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    if (congLevel)
    {
        *congLevel = 0;
    }

    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.
     */
    if (tmp != NULL && whichEntry >= 0)
    {
        gotMatch = ITS_TRUE;

        *congLevel = tmp->entries[whichEntry]->congLevel;
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing info and gets the congestion level
 *      for that route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      congLevel - the congestion level
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_GetRouteContextInfoCongestion(),
 *      ROUTE_SetRouteContextCongestion()
 ************************************************************************/
ITSDLLAPI int
ROUTE_GetRouteContextCongestion(ITS_UINT pointCode, ITS_OCTET* congLevel,
                                ROUTE_CRITERIA style, SS7_Family family,
                                ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_GetRouteContextInfoCongestion(&rinfo, congLevel);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing info and sets the congestion level
 *      for that route.
 *
 *  Input Parameters:
 *      rinfo - the route information to check
 *      congLevel - the congestion level
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextCongestion()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteContextInfoCongestion(ROUTE_MatchInfo *rinfo,
                                    ITS_OCTET congLevel)
{
    SS7_Destination *tmp;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }


    tmp = ROUTE_FindBestMatch(rinfo,
                              &whichEntry, &firstMatch, &lastMatch,
                              &whichLinkCode,
                              ITS_TRUE);

    /*
     * this one is slightly different.
     */
    if (tmp == NULL || whichEntry < 0)
    {
        ROUTE_UnlockWrite(routeRWLock);

        return (ITS_ENOTFOUND);
    }

    /* check 'em */
    tmp->entries[whichEntry]->congLevel = congLevel;
    ROUTE_CommitRoute(tmp->entries[whichEntry]);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This method takes routing info and sets the congestion level
 *      for that route.
 *
 *  Input Parameters:
 *      pointCode - the point code to send to
 *      congLevel - the congestion level
 *      style - the route style
 *      ... - determined by the style
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route exists, ITS_SUCCESS is returned.
 *      Any other return value indicates a processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_SetRouteContextInfoCongestion(),
 *      ROUTE_GetRouteContextCongestion()
 ************************************************************************/
ITSDLLAPI int
ROUTE_SetRouteContextCongestion(ITS_UINT pointCode,
                                ITS_OCTET congLevel, ROUTE_CRITERIA style,
                                SS7_Family family, ...)
{
    ROUTE_MatchInfo rinfo;
    va_list alist;

    va_start(alist, family);

    if (ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist) != ITS_SUCCESS)
    {
        va_end(alist);
        
        return (ITS_EINVALIDARGS);
    }

    va_end(alist);

    return ROUTE_SetRouteContextInfoCongestion(&rinfo, congLevel);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is used to clean the routing table for a worker
 *      after it has performed its task.  The intention is to clean up
 *      after the user to make sure that no dangling routing information
 *      is left either by mistake or due to abnormal termination.
 *
 *  Input Parameters:
 *      id - the instance id of the transport adding this route
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the instance is successfully cleaned, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This function is obsolete; however, it is preserved for backward
 *      compatibility reasons.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_SS7Clean(ITS_USHORT id)
{
    ITS_TRACE_DEBUG(("ROUTE_Clean: id %04x\n", id));

    return (ITS_SUCCESS);
}

/****************************************************************************
 *
 * Routing hashtable dump.
 *
 ****************************************************************************/

/* Local contants. */

#define PRINT_DATA_MAX_SIZE     16384 
#define HEADER_MAX_SIZE         512
#define FOOTER_MAX_SIZE         256
#define PRINT_BUF_MAX_SIZE      64

#define YES_NO(x) (x ? "yes" : "no")

#define STATUS_STR(x) ((x==DESTINATION_UNAVAILABLE)?"DESTINATION_UNAVAILABLE":\
                      ((x==DESTINATION_RESTRICTED) ? "DESTINATION_RESTRICTED":\
                      ((x==DESTINATION_AVAILABLE)  ? "DESTINATION_AVAILABLE" :\
                      "UNKNOWN")))

/* Hashtable entries dump functions. */
static int
DumpEntryDataSS7Context(ITS_POINTER data, void *in, void *out)
{
    char** pStrDump = (char **)in;
    char printBuf[PRINT_BUF_MAX_SIZE];
    ITS_UINT i;
    SS7_Destination* ss7Context = (SS7_Destination*)data;

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        strcat(*pStrDump, "------------------------------\n");

        /* Type */
        strcat(*pStrDump, "Type:        <");
        strcat(*pStrDump,
               TYPE_TO_TEXT(ss7Context->entries[i]->basic.type));
        strcat(*pStrDump, ">\n");

        /* Style */
        strcat(*pStrDump, "Style:       <");
        strcat(*pStrDump,
               STYLE_TO_TEXT(ss7Context->entries[i]->basic.style));
        strcat(*pStrDump, ">\n");

        /* Family */
        strcat(*pStrDump, "Family:      <");
        strcat(*pStrDump,
               FAMILY_TO_TEXT(ss7Context->entries[i]->basic.family));
        strcat(*pStrDump, ">\n");

        /* PointCode. */
        strcat(*pStrDump, "DPC:         <");
        sprintf(printBuf, "%u", ss7Context->entries[i]->basic.dpc);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* SIO */
        strcat(*pStrDump, "SIO:         <");
        sprintf(printBuf, "%u",
                ss7Context->entries[i]->basic.criteria.sio);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* OPC */
        strcat(*pStrDump, "OPC:         <");
        sprintf(printBuf, "%u",
                ss7Context->entries[i]->basic.criteria.opc);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* CIC */
        strcat(*pStrDump, "CIC:         <");
        sprintf(printBuf, "%u",
                ss7Context->entries[i]->basic.criteria.cic);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* SSN. */
        strcat(*pStrDump, "SSN:         <");
        sprintf(printBuf, "0x%02X",
                ss7Context->entries[i]->basic.criteria.ssn);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* Range begin. */
        strcat(*pStrDump, "Range begin: <");
        sprintf(printBuf, "%u",
                ss7Context->entries[i]->basic.criteria.range.begin);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* Range end. */
        strcat(*pStrDump, "Range end:   <");
        sprintf(printBuf, "%u",
                ss7Context->entries[i]->basic.criteria.range.end);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* isAllowed. */
        strcat(*pStrDump, "IsAllowed:   <");
        sprintf(printBuf, "%s", YES_NO(ss7Context->entries[i]->isAllowed));
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* isUp. */
        strcat(*pStrDump, "IsUp:        <");
        sprintf(printBuf, "%s", YES_NO(ss7Context->entries[i]->linkSet->isUp));
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* congLevel. */
        strcat(*pStrDump, "CongLevel:   <");
        sprintf(printBuf, "%u", ss7Context->entries[i]->congLevel);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* routingKeyId. */
        strcat(*pStrDump, "RKeyId:      <");
        sprintf(printBuf, "%u", ss7Context->entries[i]->rkey);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        /* status . */
        strcat(*pStrDump, "status:      <");
        sprintf(printBuf, "%s", STATUS_STR(ss7Context->status));
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, ">\n");

        strcat(*pStrDump, "------------------------------\n");
    }

    return ITS_SUCCESS;
}

/*****************************
 * ROUTE_DumpSS7ToIdHashtable.
 *****************************/
ITSDLLAPI int 
ROUTE_DumpSS7ToIdHashtable(char** pStrDump)
{
    char header[HEADER_MAX_SIZE];
    char footer[FOOTER_MAX_SIZE];
    char printBuf[PRINT_BUF_MAX_SIZE];
    ITS_UINT vtableSize = 0;
    char* strDumpEntries = NULL;
    int sigma;
    int res;

    ITS_TRACE_DEBUG(("ROUTE_DumpSS7ToId:\n"));

    memset(header, 0, HEADER_MAX_SIZE);
    memset(footer, 0, FOOTER_MAX_SIZE);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    *pStrDump = NULL;

    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_DumpSS7ToId: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    strcat(header, "--------------------------------------------------\n");
    strcat(header, "-- SS7 to ID Route Hashtable Begin --\n");
    strcat(header, "--------------------------------------------------\n");
    strcat(header, "Size: <");

    DSM_TableGetSize(
        DSM_RoutingFtGroupId, 
        DSM_TABLE_DESTINATIONS, 
        &vtableSize);
    sprintf(printBuf, "%u", vtableSize);
    strcat(header, printBuf);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    strcat(header, ">\n");
    strcat(header, "--------------------------------------------------\n");

    strDumpEntries = (char *)calloc(PRINT_DATA_MAX_SIZE, sizeof(char));

    res = DSM_TableIterate(DSM_RoutingFtGroupId,
                           DSM_TABLE_DESTINATIONS,
                           &strDumpEntries,
                           NULL,
                           DumpEntryDataSS7Context);

    if (res != ITS_SUCCESS)
    {
        if (strDumpEntries != NULL)
        {
            free(strDumpEntries);
        }

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return res;
    }

    strcat(footer, "--------------------------------------------------\n");
    strcat(footer, "-- SS7 to ID Route Hashtable End --\n");
    strcat(footer, "--------------------------------------------------\n");

    sigma = strlen(header) + strlen(strDumpEntries) + strlen(footer);

    *pStrDump = (char *)calloc(sigma + 1, sizeof(char));

    if (*pStrDump == NULL)
    {
        free(strDumpEntries);

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return ITS_ENOMEM;
    }

    strcat(*pStrDump, header);
    strcat(*pStrDump, strDumpEntries);
    strcat(*pStrDump, footer);

    free(strDumpEntries);

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

    return ITS_SUCCESS;
}

#if 0

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      DBC command proc for the Routing subsystem.
 *
 *  Notes:
 *
 ****************************************************************************/
void
ROUTE_Console(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;

    if (DBC_Cmd(dbc, "rt_add", "add a Route", "", ""))
    {
        char direction[20];
        char style[20];
        char family[10];
        char parameters[50];
        ROUTE_MatchInfo rinfo;
        ITS_UINT dpc, opc;
        ITS_UINT sio;
        ITS_UINT ssn, beginSSN, endSSN;
        ITS_UINT cic, beginCIC, endCIC;
    

        ITS_UINT linkSet;

        memset(&rinfo, 0, sizeof(rinfo));

        /* addRoute dirrection style paremeters */

        ret = sscanf(cmdLine, "%s %s %s %d %s %[^\n]",
                     buf, direction, family, &linkSet, style, parameters);

        sprintf(buf, "*********** Adding a Route *************\n");

        DBC_AppendText(dbc, buf);
	
	if (ret != 6)
        {
            sprintf(buf, "*** Error: Invalid parameters, try help rt_add \n");
            DBC_AppendText(dbc, buf);
	    return;

        }


        sprintf(buf, "         direction:  %s \n"
               "         family:     %s \n"
               "         linkSet:    %d \n"
               "         style:      %s \n"
               "         parameters: %s \n",
               direction, family, linkSet, style, parameters);

        DBC_AppendText(dbc, buf);

        /*** process direction ***/

        if (strcmp(direction, ROUTE_TYPE_LOCAL_STRING) == 0)
        {
            rinfo.basic.type = LOCAL_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_REMOTE_STRING) == 0)
        {
            rinfo.basic.type = REMOTE_ROUTE;
        }
        else
        {
            sprintf(buf,"Error: direction must be remoteRoute or localRoute\n");
	    DBC_AppendText(dbc, buf);
            return;
        }

       /*** process family ***/

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }


       /*** process route style ****/

        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_NI;

            ret = sscanf(parameters,"%d %d", &dpc, &sio);
	    if (ret != 2)
            {
                sprintf(buf, "Error: Missing dpc or ni value\n"); 
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_NI;

            ret = sscanf(parameters,"%d %d %d", &dpc, &opc,  &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO;

            ret = sscanf(parameters,"%d %d", &dpc, &sio);
            if (ret != 2)
            {
                sprintf(buf, "Error: Missing dpc or sio value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio; 

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO;

            ret = sscanf(parameters,"%d %d %d", &dpc, &opc, &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or sio value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &ssn);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &ssn);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d",
                         &dpc, &sio, &beginSSN, &endSSN);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginSSN, &endSSN);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &cic);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &cic);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d", 
                         &dpc, &sio, &beginCIC, &endCIC);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginCIC, &endCIC);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else
        {
            sprintf(buf, "Error: Invalid routing style\n");
            DBC_AppendText(dbc,buf);
            return;
        }

        rinfo.linkSet = (ITS_OCTET) linkSet;
        rinfo.linkCode = 0;
        rinfo.priority = 0;
        rinfo.sls  = 0;
        rinfo.rkey = 0;
        rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

        if ( (ret = ROUTE_AddRouteContextInfo(&rinfo)) != ITS_SUCCESS)
        {
            sprintf(buf, "Error %d: Route cannot be added\n", ret);
            DBC_AppendText(dbc,buf);
            return;
        }

    }
    else if (DBC_Cmd(dbc, "rt_del", "delete a Route", "", ""))
    {
        char direction[20];
        char style[20];
        char family[10];
        char parameters[50];
        ROUTE_MatchInfo rinfo;
        ITS_UINT opc, dpc;
        ITS_UINT sio;
        ITS_UINT ssn, beginSSN, endSSN;
        ITS_UINT cic, beginCIC, endCIC;
        ITS_UINT linkSet;

        /* dirrection style paremeters */

        ret = sscanf(cmdLine, "%s %s %s %d %s %[^\n]", 
                     buf, direction, family, &linkSet, style, parameters);

        sprintf(buf, "*********** Deleting a Route *************\n");

        DBC_AppendText(dbc, buf);

        if (ret != 6)
	{
	    sprintf(buf,"*** Error: Invalid parameters, try help rt_del\n");
            DBC_AppendText(dbc, buf);
            return; 
        }

        sprintf(buf, "         direction:  %s \n"
               "         family:     %s \n"
               "         linkSet:    %d \n"
               "         style:      %s \n"
               "         parameters: %s \n",
               direction, family, linkSet, style, parameters);

        DBC_AppendText(dbc, buf);

        /*** process direction ***/


        if (strcmp(direction, ROUTE_TYPE_LOCAL_STRING) == 0)
        {
            rinfo.basic.type = LOCAL_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_REMOTE_STRING) == 0)
        {
            rinfo.basic.type = REMOTE_ROUTE;
        }
        else
        {
            sprintf(buf,"Error: direction must be remoteRoute or localRoute\n");
            DBC_AppendText(dbc, buf);
            return;
        }

       /*** process family ***/

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
	   DBC_AppendText(dbc, buf);
	   return;
       }


       /*** process route style ****/

        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_NI;

            sscanf(parameters,"%d %d", &dpc, &sio);
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_NI;
            ret = sscanf(parameters,"%d %d %d", &dpc, &opc,  &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO;

            ret = sscanf(parameters,"%d %d", &dpc, &sio);
            if (ret != 2)
            {
                sprintf(buf, "Error: Missing dpc or sio value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO;

            ret = sscanf(parameters,"%d %d %d", &dpc, &opc, &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &ssn);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &ssn);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d",
                         &dpc, &sio, &beginSSN, &endSSN);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginSSN, &endSSN);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &cic);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &cic);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d", 
                         &dpc, &sio, &beginCIC, &endCIC);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginCIC, &endCIC);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else
        {
            sprintf(buf, "Error: Invalid routing style\n");
            DBC_AppendText(dbc,buf);
            return;
        }

        rinfo.linkSet = (ITS_OCTET) linkSet;
        rinfo.linkCode = 0;
        rinfo.priority = 0;
        rinfo.sls  = 0;
        rinfo.rkey = 0;
        rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

        if (ROUTE_DeleteRouteContextInfo(&rinfo) != ITS_SUCCESS)
        {
            sprintf(buf, "Error %d: Route cannot be deleted\n", ret);
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "rt_dump", "Dump Routes Info", "<>", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockForWrite(routeRWLock);

        ROUTE_DumpSS7ToIdHashtable(&dump);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
            free(dump);
	 }
    }

}

#endif




/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds one route
 *
 *  Input Parameters:
 *      rinfo - the route to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - route added.  Any other return value indicates
 *      a processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
AddParsedRoute(ITS_UINT rkey, ROUTE_MatchInfo *rinfo)
{
    ITS_TRACE_DEBUG(("AddParsedRoute: adding link\n"));

    if (rinfo->basic.type == LOCAL_ROUTE ||
        rinfo->basic.type == REMOTE_ROUTE ||
        rinfo->basic.type == DUPLICATED_ROUTE ||
        rinfo->basic.type == CONCERNED_ROUTE)
    {
        ITS_TRACE_DEBUG(("Adding local/remote route\n"));

        if (ROUTE_AddRouteContextInfo(rinfo) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("AddParsedRoute: bad route\n"));

            return (ITS_EINVALIDARGS);
        }
    }

    if (rinfo->basic.type == ROUTING_KEY_ROUTE)
    {

        ITS_TRACE_DEBUG(("Adding routing key\n"));

        if (rkey == 0)
        {
            ITS_TRACE_ERROR(("AddParsedRoute: no routing key\n"));

            return (ITS_EINVALIDARGS);
        }

        if (ROUTE_AddRoutingKeyInfo(rkey, rinfo) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("AddParsedRoute: bad route\n"));

            return (ITS_EINVALIDARGS);
        }
    }

    /* initially no congestion */
    if (rinfo->basic.type == LOCAL_ROUTE ||
        rinfo->basic.type == REMOTE_ROUTE)
    {
        ROUTE_SetRouteContextInfoCongestion(rinfo, 0);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function register SS7 information for a transport
 *
 *  Input Parameters:
 *      base - the transport to register information for
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If registration is successful, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 * Route styles ROUTE_DPC_OPC_SIO_SSN and ROUTE_DPC_OPC_SIO_SSN_RANGE are
 * allowed for concerned routes. In all of these, the OPC route info member
 * is used to store the local point code and the CIC member is used to store
 * the local SSN. The range type refers to the remote SSN values, not the
 * local.
 *
 * For local routes, all four types are allowed.  When computing the CPC list
 * for a given SSN (or range):
 *  a) if the route style for the local route is DPC_SIO_SSN, then concerned
 *     routes with the OPC == DPC of the local route and the local SSN (aka
 *     CIC of the concerned route) == SSN are on the CPC list for this
 *     PC/SSN.
 *  b) if the route style for the local route is DPC_OPC_SIO_SSN, then
 *     concerned routes with the OPC == the DPC of the local route, the
 *     DPC == the OPC of the local route, and the local SSN (aka the CIC
 *     of the concerned route) == SSN are on the CPC list for this PC/SSN.
 *  c) if the route style for the local route is DPC_SIO_SSN_RANGE, then
 *     concerned routes with the OPC == the DPC of the local route and the
 *     local SSN (aka the CIC of the concerned route) in the SSN range are
 *     on the CPC list for this PC/SSN range.
 *  d) if the route style for the local route is DPC_OPC_SIO_SSN_RANGE,
 *     then concerned routes with the OPC == the DPC of the local route, the
 *     DPC == the OPC of the local route, and the local SSN (aka the CIC
 *     of the concerned route) == in the SSN range are on the CPC list for
 *     this PC/SSN.
 *
 * Duplicate routes are another story.  These require styles of only
 * ROUTE_DPC_OPC_SIO_SSN for both the local and duplicate routes.  This is
 * required as otherwise it is ambiguous as to which duplicated subsystem
 * should take over for which local subsystem.
 *
 *  See Also:
 ****************************************************************************/
static int
RegisterRoutes(RESFILE_Manager *res, const char *section)
{
    char var[ITS_PATH_MAX];
    char val[ITS_PATH_MAX];
    ITS_BOOLEAN haveDPC, haveOPC;
    ITS_BOOLEAN haveSIO, haveSSN, haveCIC;
    ITS_BOOLEAN haveBEGIN, haveEND;
    ITS_BOOLEAN haveLS, havePRI;
    ITS_BOOLEAN haveStyle;
    ITS_BOOLEAN haveLPC, haveLSSN, haveFamily;
    ITS_UINT rkey;
    ITS_BOOLEAN inRoute;
    ROUTE_MatchInfo rinfo;

    ITS_C_ASSERT(res != NULL);

    ITS_TRACE_DEBUG(("RegisterRoutes: processing route "
                     "information\n"));

    inRoute = ITS_FALSE;

    haveDPC = haveOPC = ITS_FALSE;
    haveSIO = ITS_FALSE;
    haveSSN = ITS_FALSE;
    haveCIC = ITS_FALSE;
    haveBEGIN = ITS_FALSE;
    haveEND = ITS_FALSE;
    haveLS = ITS_FALSE;
    havePRI = ITS_FALSE;
    haveStyle = ITS_FALSE;
    haveLPC = ITS_FALSE;
    haveLSSN = ITS_FALSE;
    haveFamily = ITS_FALSE;
    rkey = 0;

    memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    /* Initialize ROUTE reader/writer lock */
    if ( (routeRWLock = ROUTE_RWLockCreate() ) == NULL)
    {
        ITS_TRACE_ERROR(("Cannot Create ROUTE Reader/Writer Lock."));
        return ITS_ENOMEM;
    }


    while (RESFILE_GetKeyName(res, section,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        /* get the type */
        if (strcmp(var, ROUTE_TYPE_STRING) == 0)
        {
            /* local */
            if (strcmp(val, ROUTE_TYPE_LOCAL_STRING) == 0)
            {
                if (inRoute)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: nested route!\n"));

                    continue;
                }

                inRoute = ITS_TRUE;

                rinfo.basic.type = LOCAL_ROUTE;
            }
            /* remote */
            else if (strcmp(val, ROUTE_TYPE_REMOTE_STRING) == 0)
            {
                if (inRoute)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: nested route!\n"));

                    continue;
                }

                inRoute = ITS_TRUE;

                rinfo.basic.type = REMOTE_ROUTE;
            }
            /* concerned */
            else if (strcmp(val, ROUTE_TYPE_CONCERNED_STRING) == 0)
            {
                if (inRoute)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: nested route!\n"));

                    continue;
                }

                inRoute = ITS_TRUE;

                rinfo.basic.type = CONCERNED_ROUTE;
            }
            /* duplicate */
            else if (strcmp(val, ROUTE_TYPE_DUPLICATE_STRING) == 0)
            {
                if (inRoute)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: nested route!\n"));

                    continue;
                }

                inRoute = ITS_TRUE;

                rinfo.basic.type = DUPLICATED_ROUTE;
            }
            /* routing key */
            else if (strcmp(val, ROUTE_TYPE_ROUTING_KEY_STRING) == 0)
            {
                if (inRoute)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: nested route!\n"));

                    continue;
                }

                inRoute = ITS_TRUE;

                rinfo.basic.type = ROUTING_KEY_ROUTE;
            }
            /* end of route.  Add it if it's good */
            else if (strcmp(val, ROUTE_TYPE_END_OF_STRING) == 0)
            {
                if (!inRoute)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: end of no route!\n"));

                    continue;
                }

                inRoute = ITS_FALSE;

                if (!haveStyle)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: route style not "
                                     "specified\n"));

                    continue;
                }

                if (!haveLS)
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: no link set for route\n"));

                    RESFILE_Unlock(res);

                    return (ITS_EINVALIDARGS);
                }

                if (!haveFamily)
                {
                    ITS_TRACE_WARNING(("Assuming ANSI family for route\n"));
                }

                if (!havePRI)
                {
                    ITS_TRACE_WARNING(("Default priority assumed for route\n"));
                }

                if ((rinfo.basic.type == CONCERNED_ROUTE &&
                     rinfo.basic.style != ROUTE_DPC_OPC_SIO_SSN &&
                     rinfo.basic.style != ROUTE_DPC_OPC_SIO_SSN_RANGE) ||
                    (rinfo.basic.type == DUPLICATED_ROUTE &&
                     rinfo.basic.style != ROUTE_DPC_OPC_SIO_SSN))
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: improper concerned route.\n"));

                    RESFILE_Unlock(res);

                    return (ITS_EINVALIDARGS);
                }
                else if (((rinfo.basic.type == CONCERNED_ROUTE &&
                           (rinfo.basic.style == ROUTE_DPC_OPC_SIO_SSN ||
                            rinfo.basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)) ||
                          (rinfo.basic.type == DUPLICATED_ROUTE &&
                           rinfo.basic.style == ROUTE_DPC_OPC_SIO_SSN)) &&
                         (!haveLPC || !haveLSSN))
                {
                    ITS_TRACE_ERROR(("RegisterRoutes: improper concerned route.\n"));

                    RESFILE_Unlock(res);

                    return (ITS_EINVALIDARGS);
                }

                /* validate route */
                switch (rinfo.basic.style)
                {
                case ROUTE_DPC_UDEF:
                    if (haveDPC)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC\n"));
                    }
                    break;

                case ROUTE_DPC_NI:
                    if (haveDPC && haveSIO)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC or "
                                         "SIO\n"));
                    }
                    break;

                case ROUTE_DPC_OPC_NI:
                    if (haveDPC && haveOPC && haveSIO)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "OPC, or SIO\n"));
                    }
                    break;

                case ROUTE_DPC_SIO:
                    if (haveDPC && haveSIO)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC or "
                                         "SIO\n"));
                    }
                    break;

                case ROUTE_DPC_OPC_SIO:
                    if (haveDPC && haveOPC && haveSIO)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "OPC, or SIO\n"));
                    }
                    break;

                case ROUTE_DPC_SIO_SSN:
                    if (haveDPC && haveSIO && haveSSN)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "SIO, or SSN\n"));
                    }
                    break;

                case ROUTE_DPC_OPC_SIO_SSN:
                    if ((rinfo.basic.type != CONCERNED_ROUTE &&
                         haveDPC && haveOPC && haveSIO && haveSSN) ||
                        (rinfo.basic.type == CONCERNED_ROUTE &&
                         haveDPC && haveLPC && haveSIO && haveSSN && haveLSSN))
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "OPC, SIO, or SSN\n"));
                    }
                    break;

                case ROUTE_DPC_SIO_CIC:
                    if (haveDPC && haveSIO && haveCIC)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "SIO, or CIC\n"));
                    }
                    break;

                case ROUTE_DPC_OPC_SIO_CIC:
                    if (haveDPC && haveOPC && haveSIO && haveCIC)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "OPC, SIO, or CIC\n"));
                    }
                    break;

                case ROUTE_DPC_SIO_SSN_RANGE:
                case ROUTE_DPC_SIO_CIC_RANGE:
                    if (haveDPC && haveSIO && haveBEGIN && haveEND)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "SIO, BEGIN, or END\n"));
                    }
                    break;

                case ROUTE_DPC_OPC_SIO_SSN_RANGE:
                case ROUTE_DPC_OPC_SIO_CIC_RANGE:
                    if (haveDPC && haveOPC && haveSIO && haveBEGIN && haveEND)
                    {
                        if (AddParsedRoute(rkey, &rinfo) != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("RegisterRoutes: addRoute failed\n"));

                            RESFILE_Unlock(res);

                            return (ITS_ENOMEM);
                        }
                    }
                    else
                    {
                        ITS_TRACE_ERROR(("RegisterRoutes: missing DPC, "
                                         "OPC, SIO, BEGIN, or END\n"));
                    }
                    break;

                default:
                    ITS_TRACE_CRITICAL(("RegisterRoutes: code explosion\n"));
                    break;
                }

                /* RESET */
                haveDPC = haveOPC = ITS_FALSE;
                haveSIO = ITS_FALSE;
                haveSSN = ITS_FALSE;
                haveCIC = ITS_FALSE;
                haveBEGIN = ITS_FALSE;
                haveEND = ITS_FALSE;
                haveLS = ITS_FALSE;
                havePRI = ITS_FALSE;
                haveStyle = ITS_FALSE;
                haveLPC = ITS_FALSE;
                haveLSSN = ITS_FALSE;
                haveFamily = ITS_FALSE;
                rkey = 0;

                memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));
                rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
            }
            else
            {
                ITS_TRACE_ERROR(("RegisterRoutes: unknow route type\n"));

                continue;
            }
        }
        else if (!inRoute)
        {
            /* don't know what it is */
            continue;
        }
        else if (strcmp(var, ROUTE_STYLE_STRING) == 0)
        {
            haveStyle = ITS_TRUE;
            if (strcmp(val, ROUTE_STYLE_DPC_NI_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_NI;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_NI;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_SIO_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_SSN;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_CIC;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;
            }
            else if (strcmp(val, ROUTE_STYLE_DPC_UDEF_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_UDEF;
            }
            else
            {
                ITS_TRACE_ERROR(("RegisterRoutes: unknown route style\n"));

                haveStyle = ITS_FALSE;
            }
        }
        else if (strcmp(var, ROUTING_KEY_STRING) == 0)
        {
            rkey = RESFILE_ParseNum(val);

            rinfo.rkey = rkey;
        }
        else if (strcmp(var, DEST_POINT_CODE_STRING) == 0)
        {
            haveDPC = ITS_TRUE;

            rinfo.basic.dpc = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, ORIG_POINT_CODE_STRING) == 0)
        {
            haveOPC = ITS_TRUE;

            rinfo.basic.criteria.opc = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LOCAL_POINT_CODE_STRING) == 0)
        {
            if (rinfo.basic.type == CONCERNED_ROUTE)
            {
                haveLPC = ITS_TRUE;

                rinfo.basic.criteria.opc = RESFILE_ParseNum(val);
            }
        }
        else if (strcmp(var, ROUTE_MASK_STRING) == 0)
        {
            rinfo.basic.mask = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, SIO_STRING) == 0)
        {
            haveSIO = ITS_TRUE;

            rinfo.basic.criteria.sio = RESFILE_ParseNum(val) &
                                        (ROUTE_NI_MASK | ROUTE_UP_MASK);
        }
        else if (strcmp(var, NI_STRING) == 0)
        {
            haveSIO = ITS_TRUE;

            rinfo.basic.criteria.sio = RESFILE_ParseNum(val) &
                                        ROUTE_NI_MASK;
        }
        else if (strcmp(var, SSN_STRING) == 0)
        {
            haveSSN = ITS_TRUE;

            rinfo.basic.criteria.ssn = (ITS_OCTET)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LOCAL_SSN_STRING) == 0)
        {
            if (rinfo.basic.type == CONCERNED_ROUTE)
            {
                haveLSSN = ITS_TRUE;

                rinfo.basic.criteria.cic = (ITS_USHORT)RESFILE_ParseNum(val);
            }
        }
        else if (strcmp(var, CIC_STRING) == 0)
        {
            haveCIC = ITS_TRUE;

            rinfo.basic.criteria.cic = (ITS_USHORT)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, RANGE_BEGIN_STRING) == 0)
        {
            haveBEGIN = ITS_TRUE;

            rinfo.basic.criteria.range.begin = (ITS_USHORT)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, RANGE_END_STRING) == 0)
        {
            haveEND = ITS_TRUE;

            rinfo.basic.criteria.range.end = (ITS_USHORT)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LINKSET_SET_STRING) == 0)
        {
            haveLS = ITS_TRUE;

            rinfo.linkSet = (ITS_OCTET)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, PRIORITY_STRING) == 0)
        {
            havePRI = ITS_TRUE;

            rinfo.priority = (ITS_OCTET)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, FAMILY_STRING) == 0)
        {
            haveFamily = ITS_TRUE;

            if (strcmp(val, FAMILY_ANSI_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_ANSI;
            }
            else if (strcmp(val, FAMILY_CCITT_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_ITU;
            }
            else if (strcmp(val, FAMILY_CHINA_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_CHINA;
            }
            else if (strcmp(val, FAMILY_JAPAN_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_JAPAN;
            }
        }
    }

    RESFILE_Unlock(res);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function updates the variant information for each SS7
 *      destination.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - information updated.  Any other return value indicates
 *      a processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
UpdateDestinations(RESFILE_Manager *res, const char *section)
{
    char var[ITS_PATH_MAX], val[ITS_PATH_MAX];
    SS7_Destination *tmp = NULL;
    ITS_INT mtp3Var, isupVar, sccpVar, tcapVar, tupVar, dupVar;
    ITS_UINT pc;
    ITS_OCTET sio;
    ITS_BOOLEAN havePC, haveSIO;
    SS7_Family family;

    mtp3Var = ITS_LATEST_GEN;
    isupVar = ITS_LATEST_GEN;
    sccpVar = ITS_LATEST_GEN;
    tcapVar = ITS_LATEST_GEN;
    tupVar = ITS_LATEST_GEN;
    dupVar = ITS_LATEST_GEN;
    havePC = ITS_FALSE;
    haveSIO = ITS_FALSE;
    family  = FAMILY_ANSI;

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    pc = 0;
    sio = 0;

    while (RESFILE_GetKeyName(res, section,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        /* get the type */
        if (strcmp(var, DEST_INFO_STRING) == 0)
        {
            if (strcmp(val, DI_BEGIN_STRING) == 0)
            {
                tmp = NULL;
            }
            else if (strcmp(val, DI_END_STRING) == 0)
            {
                if (DSM_LockTable(
                        DSM_RoutingFtGroupId, 
                        DSM_TABLE_DESTINATIONS) == ITS_SUCCESS)
                {
                    if (!havePC || !haveSIO)
                    {
                        ITS_TRACE_ERROR(("Can't set variant: missing pc or sio\n"));
                    }
                    else
                    {
                        tmp = ROUTE_FindDestination(pc, sio, family);
                    }

                    if (tmp)
                    {
                        tmp->mtp3Variant = mtp3Var;
                        tmp->isupVariant = isupVar;
                        tmp->sccpVariant = sccpVar;
                        tmp->tcapVariant = tcapVar;
                        tmp->tupVariant = tupVar;
                        tmp->dupVariant = dupVar;
                        tmp->family = family;

                        ROUTE_CommitDestination(tmp, pc, sio, family);
                    }

                    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);
                }

                mtp3Var = ITS_LATEST_GEN;
                isupVar = ITS_LATEST_GEN;
                sccpVar = ITS_LATEST_GEN;
                tcapVar = ITS_LATEST_GEN;
                tupVar = ITS_LATEST_GEN;
                dupVar = ITS_LATEST_GEN;
                havePC = ITS_FALSE;
                haveSIO = ITS_FALSE;
                tmp = NULL;
            }
        }
        else if (strcmp(var, DEST_POINT_CODE_STRING) == 0)
        {
            pc = RESFILE_ParseNum(val);
            havePC = ITS_TRUE;
        }
        else if (strcmp(var, SIO_STRING) == 0)
        {
            sio = (ITS_OCTET)(RESFILE_ParseNum(val) & ROUTE_NI_MASK);
            haveSIO = ITS_TRUE;
        }
        else if (strcmp(var, DI_MTP3_VAR_STRING) == 0)
        {
            mtp3Var = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, DI_ISUP_VAR_STRING) == 0)
        {
            isupVar = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, DI_SCCP_VAR_STRING) == 0)
        {
            sccpVar = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, DI_TCAP_VAR_STRING) == 0)
        {
            tcapVar = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, DI_TUP_VAR_STRING) == 0)
        {
            tupVar = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, DI_DUP_VAR_STRING) == 0)
        {
            dupVar = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, FAMILY_STRING) == 0)
        {
            if (strcmp(val, FAMILY_ANSI_STRING) == 0)
            {
                family = FAMILY_ANSI;
            }
            else if (strcmp(val, FAMILY_CCITT_STRING) == 0)
            {
                family = FAMILY_ITU;
            }
            else if (strcmp(val, FAMILY_CHINA_STRING) == 0)
            {
                family = FAMILY_CHINA;
            }
            else if (strcmp(val, FAMILY_JAPAN_STRING) == 0)
            {
                family = FAMILY_JAPAN;
            }
        }
    }
    
    RESFILE_Unlock(res);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the routing subsystem to a ready state.
 *      The routing subsystem will not work correctly if this funtion is
 *      not invoked first.
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
 *      If the routing subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_Terminate()
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    RESFILE_Manager *globalRes = NULL;
    const char *name = APPL_GetConfigFileName();
    int ret;

    ITS_TRACE_DEBUG(("ROUTE_Initialize:\n"));

    if ((ret = RWLOCK_CreateLock(&selectorGate)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_Initialize: couldn't create selector "
                         "mutex\n"));

        return (ret);
    }

    /* get resources */
    globalRes = RESFILE_CreateResourceManager(name);

    ret = RegisterRoutes(globalRes, NULL);

    if (ret == ITS_SUCCESS)
    {
        return UpdateDestinations(globalRes, NULL);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete dead app routes before terminating.
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if 0
/* warning avoidance */
static int
DeleteSS7Info(ITS_INT context, ITS_POINTER data,
              void *in, void *out)
{
    SS7_Destination *dest = (SS7_Destination *)data;
    ITS_UINT i;

    for (i = 0; i < dest->numEntries; i++)
    {
        /* No need to free crBuf.  These kind don't have them */
        free(dest->entries[i]);
    }

    free(dest);

    return (ITS_SUCCESS);
}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the routing subystem.  It frees all resources
 *      that have been allocated for routing.
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
 *  Notes:
 *      This function must NOT be called until all routing entities have
 *      terminated.  The results of attempting to route after the routing
 *      subsystem has been terminated is undefined.
 *
 *  See Also:
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("ROUTE_Terminate:\n"));

    /* FIXME: figure out how to get rid of these */
#if 0
    DSM_TableIterate(DSM_RoutingFtGroupId,
                     DSM_TABLE_RKEYS,
                     NULL, NULL, DeleteSS7Info);

    DSM_TableIterate(DSM_RoutingFtGroupId,
                     DSM_TABLE_RCONTEXTS,
                     NULL, NULL, DeleteSS7Info);
#endif
    
    RWLOCK_DeleteLock(&selectorGate);
}

/*
 * the class record
 */
ITSDLLAPI ROUTE_ClassRec itsSS7_ROUTE_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        ROUTE_CLASS_NAME,               /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsSS7_ROUTE_Class = (ITS_Class)&itsSS7_ROUTE_ClassRec;
