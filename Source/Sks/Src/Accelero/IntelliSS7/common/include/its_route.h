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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.4  2005/05/06 05:21:40  adutta
 * LOG: MTP route pegs definition
 * LOG:
 * LOG: Revision 9.3  2005/04/08 07:54:17  adutta
 * LOG: Fix for Bug#516
 * LOG:
 * LOG: Revision 9.2  2005/04/05 10:17:33  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.4  2003/01/07 15:27:42  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.3  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.2  2002/08/27 19:44:44  mmiers
 * LOG: Bad args
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.8  2002/08/26 18:19:09  mmiers
 * LOG: Add dest to deselector
 * LOG:
 * LOG: Revision 6.7  2002/08/26 16:47:39  mmiers
 * LOG: Add deselector hook
 * LOG:
 * LOG: Revision 6.6  2002/06/27 22:33:45  ssharma
 * LOG: Change from Family to family.
 * LOG:
 * LOG: Revision 6.5  2002/06/21 22:49:10  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.4  2002/06/19 18:38:07  mmiers
 * LOG: Add family
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:02:54  randresol
 * LOG: Define cocbBuf, rtrvBuf, crBuf and routes list in shared memory (DSM_Queue)
 * LOG:
 * LOG: Revision 6.2  2002/03/08 22:55:06  mmiers
 * LOG: first pass of routing in DSM
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.45  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.44  2001/12/05 23:40:58  mmiers
 * LOG: Add flag back.
 * LOG:
 * LOG: Revision 5.43  2001/10/30 01:54:17  mmiers
 * LOG: Mark field deprecated.
 * LOG:
 * LOG: Revision 5.42  2001/10/24 17:33:40  mmiers
 * LOG: Deep thought about current routes, and queue puts.
 * LOG:
 * LOG: Revision 5.41  2001/10/24 16:31:10  mmiers
 * LOG: Destinations need to mark a curent route.
 * LOG:
 * LOG: Revision 5.40  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.39  2001/10/18 19:01:09  mmiers
 * LOG: Rework the link/route division.  It's easier if they're in
 * LOG: a single table.
 * LOG:
 * LOG: Revision 5.38  2001/10/17 18:20:58  mmiers
 * LOG: Convert routing to use link information.
 * LOG:
 * LOG: Revision 5.37  2001/10/16 22:45:42  mmiers
 * LOG: Remove SLS shift.  It's fairly useless, and if it belongs
 * LOG: anywhere it's on the link set.
 * LOG:
 * LOG: Revision 5.36  2001/10/16 22:18:37  mmiers
 * LOG: Export the SLS bit rotation functions.
 * LOG:
 * LOG: Revision 5.35  2001/10/02 21:44:25  mmiers
 * LOG: dead route style removal
 * LOG:
 * LOG: Revision 5.34  2001/10/01 21:31:00  mmiers
 * LOG: Destination timers.
 * LOG:
 * LOG: Revision 5.33  2001/10/01 20:12:27  mmiers
 * LOG: struct rename
 * LOG:
 * LOG: Revision 5.32  2001/09/24 21:37:37  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.31  2001/09/21 00:31:37  mmiers
 * LOG: Add back pointer from route to destination.
 * LOG:
 * LOG: Revision 5.30  2001/09/20 22:50:01  mmiers
 * LOG: Fields and flags from todays discussion.
 * LOG:
 * LOG: Revision 5.29  2001/09/19 23:36:14  mmiers
 * LOG: New fields and flags
 * LOG:
 * LOG: Revision 5.28  2001/09/18 22:52:12  mmiers
 * LOG: Extra flags.
 * LOG:
 * LOG: Revision 5.27  2001/09/14 20:53:47  mmiers
 * LOG: Add timers.
 * LOG:
 * LOG: Revision 5.26  2001/09/14 19:11:54  mmiers
 * LOG: Add flags.
 * LOG:
 * LOG: Revision 5.25  2001/09/14 19:09:46  mmiers
 * LOG: Add a few flags and fields
 * LOG:
 * LOG: Revision 5.24  2001/09/13 22:33:21  mmiers
 * LOG: timers, dead state
 * LOG:
 * LOG: Revision 5.23  2001/09/13 21:18:40  mmiers
 * LOG: Add a few fields
 * LOG:
 * LOG: Revision 5.22  2001/09/13 14:22:15  mmiers
 * LOG: Add a timer.
 * LOG:
 * LOG: Revision 5.21  2001/09/11 23:48:36  mmiers
 * LOG: Remove old functions (their use would be undefined).
 * LOG:
 * LOG: Revision 5.20  2001/09/11 22:08:03  mmiers
 * LOG: Additional fields.
 * LOG:
 * LOG: Revision 5.19  2001/09/11 20:15:14  mmiers
 * LOG: Add route timers.
 * LOG:
 * LOG: Revision 5.18  2001/09/06 20:04:33  mmiers
 * LOG: Update.
 * LOG:
 * LOG: Revision 5.17  2001/09/06 17:24:39  mmiers
 * LOG: Closing in.
 * LOG:
 * LOG: Revision 5.16  2001/09/04 23:04:40  mmiers
 * LOG: MTP3 work.
 * LOG:
 * LOG: Revision 5.15  2001/08/31 22:14:03  mmiers
 * LOG: IsUp/IsAllowed handling
 * LOG:
 * LOG: Revision 5.14  2001/08/30 19:10:29  mmiers
 * LOG: ForceSecondary -> ForcePrimary
 * LOG:
 * LOG: Revision 5.13  2001/08/30 00:17:50  mmiers
 * LOG: More cleanup.  Work needs to be done on the match ranges
 * LOG: allowed for specific types.  A unit tester is really needed
 * LOG: for this thing at this point.
 * LOG:
 * LOG: Revision 5.12  2001/08/29 22:30:08  mmiers
 * LOG: Added mask.
 * LOG:
 * LOG: Revision 5.11  2001/08/29 17:26:54  mmiers
 * LOG: Add maskable routing.  Bug fix for SCTP clients.  Abort if
 * LOG: timer context too large.
 * LOG:
 * LOG: Revision 5.10  2001/08/28 20:47:01  mmiers
 * LOG: More routing.
 * LOG:
 * LOG: Revision 5.9  2001/08/24 21:09:32  mmiers
 * LOG: Stabilize the routing interface.  Still need to write the link
 * LOG: selection logic.
 * LOG:
 * LOG: Revision 5.8  2001/08/24 17:10:25  mmiers
 * LOG: Routing, take three.
 * LOG:
 * LOG: Revision 5.7  2001/08/23 22:55:33  mmiers
 * LOG: Now routing is *really* messed up.  For MTP3 you have to qualify
 * LOG: a route by the destination *and* the linkset to reach it by.
 * LOG: None of the routing code reflects this yet.
 * LOG:
 * LOG: Revision 5.6  2001/08/21 21:18:13  mmiers
 * LOG: More route flags.
 * LOG:
 * LOG: Revision 5.5  2001/08/21 20:21:54  mmiers
 * LOG: More routing changes for the stack.
 * LOG:
 * LOG: Revision 5.4  2001/08/20 23:28:54  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.3  2001/08/20 22:51:15  mmiers
 * LOG: Get this in line with new routing scheme
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:19:21  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/08/14 15:26:19  mmiers
 * LOG: Start making room for MTP3.
 * LOG:
 * LOG: Revision 4.5  2001/08/13 22:23:04  mmiers
 * LOG: Split routing into two subsystems.
 * LOG:
 * LOG: Revision 4.4  2001/06/27 22:57:42  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.3  2001/06/20 22:01:25  mmiers
 * LOG: Get DSM building as a DLL.  Correct some namespace bugs.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.16  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 3.15  2001/03/16 17:13:59  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 3.14  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.13  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.12  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.11  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.10  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.9  2000/12/22 00:37:21  mmiers
 * LOG: Remove dead header
 * LOG:
 * LOG: Revision 3.8  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.7  2000/11/22 18:03:45  mmiers
 * LOG: More SCTP integration.
 * LOG:
 * LOG: Revision 3.6  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.14  2000/11/09 23:04:24  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.13  2000/11/09 01:32:33  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.12  2000/11/09 00:48:41  mmiers
 * LOG: Today's installment.  Also an IMAL fix.
 * LOG:
 * LOG: Revision 3.11  2000/11/07 23:35:01  mmiers
 * LOG: Think about with and without event a bit more.
 * LOG:
 * LOG: Revision 3.10  2000/11/07 22:55:44  mmiers
 * LOG: Structure's in place.  Fill in the gaps.
 * LOG:
 * LOG: Revision 3.9  2000/11/06 23:32:20  mmiers
 * LOG: More work on the routing changes.
 * LOG:
 * LOG: Revision 3.8  2000/11/03 22:51:01  mmiers
 * LOG: More work on the routing changes.
 * LOG:
 * LOG: Revision 3.7  2000/11/03 21:57:33  mmiers
 * LOG: Start working on the routing changes.
 * LOG:
 * LOG: Revision 3.6  2000/10/09 16:53:16  mmiers
 * LOG: Set up for testing...
 * LOG:
 * LOG: Revision 3.5  2000/10/05 23:04:58  mmiers
 * LOG: New routing scheme.
 * LOG:
 * LOG: Revision 3.4  2000/10/04 16:41:07  omayor
 * LOG:  Added DUPLICATE route type for SCMG procedures.
 * LOG:
 * LOG: Revision 3.3  2000/09/25 19:56:51  mmiers
 * LOG: Set up for new route style.
 * LOG:
 * LOG: Revision 3.2  2000/09/25 15:40:21  mmiers
 * LOG: Set up for SUA, M3UA.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:20  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.10  2000/06/28 22:52:20  mmiers
 * LOG:
 * LOG:
 * LOG: Modify routing mechanism to select by link.
 * LOG:
 * LOG: Revision 2.9  2000/05/16 00:05:20  mmiers
 * LOG:
 * LOG:
 * LOG: Add concept of route by linkset to routing table.
 * LOG:
 * LOG: Revision 2.8  2000/05/11 22:17:24  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for link sets.
 * LOG:
 * LOG: Revision 2.7  2000/03/18 21:03:32  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.6  2000/02/14 19:17:36  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.5  2000/02/02 15:52:58  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.4  2000/02/02 02:20:48  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.3  2000/01/21 23:01:35  mmiers
 * LOG:
 * LOG: Fix the C++ API.
 * LOG:
 * LOG: Revision 2.2  2000/01/21 22:48:15  mmiers
 * LOG:
 * LOG: Had to add separate up/allowed variables.
 * LOG:
 * LOG: Revision 2.1  2000/01/21 22:13:14  mmiers
 * LOG:
 * LOG: Checkpoint changes.  Include routing behavior change for
 * LOG: Rajesh.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.35  1999/08/26 15:07:22  mmiers
 * LOG:
 * LOG:
 * LOG: Add a predicate for determination of the default app selector.
 * LOG:
 * LOG: Revision 1.34  1999/08/11 17:30:57  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.33  1999/07/29 02:11:42  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build errors after addressing Hubert's comments.
 * LOG:
 * LOG: Revision 1.32  1999/07/29 01:58:18  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.31  1999/07/27 22:35:17  mmiers
 * LOG:
 * LOG:
 * LOG: Oops, make this static.
 * LOG:
 * LOG: Revision 1.30  1999/07/27 22:34:19  mmiers
 * LOG:
 * LOG:
 * LOG: Update the infrastructure tests.
 * LOG:
 * LOG: Revision 1.29  1998/11/11 00:44:46  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.28  1998/11/04 02:47:21  mmiers
 * LOG: Remove ITS_SS7_LOCAL_ROUTE, it is irrelevant, we don't do that.
 * LOG: Add congestion callback list, it will be used for SS7.
 * LOG: Update TODO to reflect what needs to be added.
 * LOG:
 * LOG: Revision 1.27  1998/09/29 20:22:33  mmiers
 * LOG: Add route state into the picture.
 * LOG:
 * LOG: Revision 1.26  1998/09/28 22:42:43  mmiers
 * LOG: More work enhancing MTP3-ish support.
 * LOG:
 * LOG: Revision 1.25  1998/09/28 22:09:39  mmiers
 * LOG: More support for intelligent transports.
 * LOG:
 * LOG: Revision 1.24  1998/09/18 22:15:56  mmiers
 * LOG: Use pointers, not structs.  Convert routing class to static methods.
 * LOG:
 * LOG: Revision 1.23  1998/08/27 23:28:13  hdivoux
 * LOG: Added functions to dump hashtables.
 * LOG:
 * LOG: Revision 1.22  1998/08/03 20:34:17  mmiers
 * LOG: Add cleaner functionality to ITS_Terminate() for transient transports.
 * LOG:
 * LOG: Revision 1.21  1998/07/30 14:49:20  mmiers
 * LOG: Update routing functions so that destinations cannot be removed when
 * LOG: attempting to send.
 * LOG:
 * LOG: Revision 1.20  1998/07/10 16:03:36  mmiers
 * LOG: Add some warnings about throwing exceptions from the app selector callback.
 * LOG: Add a method to the threadpool for returning an entry to the pool
 * LOG: without dispatching it.
 * LOG:
 * LOG: Revision 1.19  1998/07/01 23:34:52  mmiers
 * LOG: Modify the route selection interface slightly.
 * LOG:
 * LOG: Revision 1.18  1998/06/26 14:30:39  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.17  1998/06/02 19:43:14  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.16  1998/06/01 16:35:18  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.15  1998/05/31 22:20:13  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.14  1998/05/29 03:31:31  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.13  1998/05/29 00:32:54  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.12  1998/05/28 17:28:41  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 * LOG: Revision 1.11  1998/05/28 02:59:13  mmiers
 * LOG: More documentation, make application route selection single threaded,
 * LOG: and remove nasty tab characters from StandardHeaders.
 * LOG:
 * LOG: Revision 1.10  1998/05/27 23:42:54  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.9  1998/05/27 23:36:54  mmiers
 * LOG: Doc updates.
 * LOG:
 * LOG: Revision 1.8  1998/05/22 22:46:51  whu
 * LOG: Add static initialization methods.
 * LOG:
 * LOG: Revision 1.7  1998/05/20 20:15:30  mmiers
 * LOG: Get test8 (process framework) compiled and linked.  Not
 * LOG: all code is linked in (no sending yet, which will cause more
 * LOG: undefined externals).
 * LOG:
 * LOG: Revision 1.6  1998/05/20 16:16:51  ahanda
 * LOG: ..
 * LOG:
 * LOG: Revision 1.5  1998/05/19 17:50:25  ahanda
 * LOG: Fix thread usage problems.
 * LOG:
 * LOG: Revision 1.2  1998/05/05 20:24:11  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/05/01 00:24:33  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 19:00:10  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_ROUTE_H
#define ITS_ROUTE_H

#include <stdarg.h>

#include <its.h>
#include <its_object.h>
#include <its_link.h>
#include <its_hash.h>
#include <its_dsmqueue.h>
#include <its_pegs.h>

#ident "$Id: its_route.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * resource file strings for transports
 */
#define ROUTE_TYPE_STRING                           "routeType"
# define ROUTE_TYPE_LOCAL_STRING                    "localRoute"
# define ROUTE_TYPE_REMOTE_STRING                   "remoteRoute"
# define ROUTE_TYPE_CONCERNED_STRING                "concernedRoute"
# define ROUTE_TYPE_DUPLICATE_STRING                "duplicateRoute"
# define ROUTE_TYPE_ROUTING_KEY_STRING              "routingKeyRoute"
# define ROUTE_TYPE_END_OF_STRING                   "endOfRoute"
#define ROUTE_STYLE_STRING                          "routeStyle"
# define ROUTE_STYLE_DPC_NI_STRING                  "dpc-ni"
# define ROUTE_STYLE_DPC_OPC_NI_STRING              "dpc-opc-ni"
# define ROUTE_STYLE_DPC_SIO_STRING                 "dpc-sio"
# define ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING       "dpc-sio-ssn-range"
# define ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING       "dpc-sio-cic-range"
# define ROUTE_STYLE_DPC_SIO_SSN_STRING             "dpc-sio-ssn"
# define ROUTE_STYLE_DPC_SIO_CIC_STRING             "dpc-sio-cic"
# define ROUTE_STYLE_DPC_OPC_SIO_STRING             "dpc-opc-sio"
# define ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING   "dpc-opc-sio-ssn-range"
# define ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING   "dpc-opc-sio-cic-range"
# define ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING         "dpc-opc-sio-ssn"
# define ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING         "dpc-opc-sio-cic"
# define ROUTE_STYLE_DPC_UDEF_STRING                "user-defined"
#define ROUTING_KEY_STRING                          "routingKey"
#define ROUTE_MASK_STRING                           "routeMask"
#define DEST_POINT_CODE_STRING                      "DPC"
#define ORIG_POINT_CODE_STRING                      "OPC"
#define ADJ_POINT_CODE_STRING                       "APC"
#define LOCAL_POINT_CODE_STRING                     "LPC"
#define NI_STRING                                   "NI"
#define SIO_STRING                                  "SIO"
#define SSN_STRING                                  "SSN"
#define LOCAL_SSN_STRING                            "LSSN"
#define CIC_STRING                                  "CIC"
#define PRIORITY_STRING                             "priority"
#define RANGE_BEGIN_STRING                          "RangeBegin"
#define RANGE_END_STRING                            "RangeEnd"
#define FAMILY_STRING                               "family"
# define FAMILY_ANSI_STRING                         "ANSI"
# define FAMILY_CCITT_STRING                        "ITU"
# define FAMILY_CHINA_STRING                        "CHINA"
# define FAMILY_JAPAN_STRING                        "JAPAN"

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * for wildcard routing
 */
#define ITS_SS7_DEFAULT_SIO         0xCFU
#define ITS_SS7_DEFAULT_POINT_CODE  0x00FFFFFF
#define ITS_SS7_DEFAULT_SSN         0xFFFFU
#define ITS_SS7_DEFAULT_CIC         0xFFFFU
#define ITS_SS7_DEFAULT_LINK_SET    0xFFU
#define ITS_SS7_DEFAULT_LINK_CODE   0xFFU
#define ITS_SS7_DEFAULT_LINK_PRI    0x00U
#define ITS_SS7_DEFAULT_SLS         0x00U
#define ITS_SS7_DEFAULT_PRI         0x00U
#define ITS_SS7_DEFAULT_ROUTE_MASK  0x00FFFFFFU

/* DPC relagted pegs for MTP3 */
#define PEG_MTP3_DPC_NUM_PEGS       10

/*
 * route types.
 */
typedef enum
{
    DONT_CARE,
    LOCAL_ROUTE,        /* route is to entity inside this process */
    REMOTE_ROUTE,       /* route is to entity outside this process */
    CONCERNED_ROUTE,    /* route is SCMG managed (if SCMG enabled) */
    DUPLICATED_ROUTE,   /* route to the duplicated subsystem (SCMG managed) */ 
    ROUTING_KEY_ROUTE
}
ROUTE_TYPE;

/*
 * route matching types.  Note that route matching is done in the
 * reverse order of declaration.
 */
typedef enum
{
    ROUTE_DPC_NI,
    ROUTE_DPC_OPC_NI,
    ROUTE_DPC_SIO,
    ROUTE_DPC_OPC_SIO,
    ROUTE_DPC_SIO_SSN_RANGE,
    ROUTE_DPC_SIO_CIC_RANGE,
    ROUTE_DPC_OPC_SIO_SSN_RANGE,
    ROUTE_DPC_OPC_SIO_CIC_RANGE,
    ROUTE_DPC_SIO_SSN,
    ROUTE_DPC_SIO_CIC,
    ROUTE_DPC_OPC_SIO_SSN,
    ROUTE_DPC_OPC_SIO_CIC,
    ROUTE_DPC_UDEF
}
ROUTE_CRITERIA;

/*
 * routing table data.
 */

/*
 * match criteria for routing
 */
typedef struct
{
    ITS_UINT        opc;            /* OPC based routing */
    ITS_USHORT      cic;            /* CIC based routing */
    ITS_OCTET       sio;            /* SIO based routing */
    ITS_OCTET       ssn;            /* SSN based routing */
    struct
    {
        ITS_USHORT  begin;          /* range begin */
        ITS_USHORT  end;            /* range end */
    }
    range;
    ITS_OCTET       *userDefined;   /* user info */
    ITS_UINT        userDefLen;     /* user info len */
    ITS_OCTET      ssnstatus ;       /*maintain the ssn status*/
    ITS_OCTET      ssn_cong_level ;   /*maintain the ssn cong level status*/
}
ROUTE_PatternInfo;

/*
 * common to routes and route matching
 */
typedef struct
{
    ROUTE_TYPE          type;           /* type of route */
    ROUTE_CRITERIA      style;          /* based on what info */
    ITS_UINT            dpc;            /* destination point code */
    ITS_UINT            mask;           /* routing mask (bit select) */
    SS7_Family          family;         /* protocol family */
    ROUTE_PatternInfo   criteria;       /* routing details */
}
ROUTE_BasicInfo;

typedef enum
{
    CONT_REROUTING_IDLE,
    CONT_REROUTING_WAIT_1,
    CONT_REROUTING_WAIT_2
}
ROUTE_ControlledReroutingState;

typedef enum
{
    FORCE_REROUTING_IDLE,
    FORCE_REROUTING_WAIT_1
}
ROUTE_ForcedReroutingState;

typedef enum
{
    CONGESTION_IDLE,
    CONGESTION_WAIT_1,
    CONGESTION_WAIT_2,
    CONGESTION_WAIT_3
}
ROUTE_CongestionState;

typedef enum
{
    ROUTING_IDLE,
    ROUTING_WAIT_1,
    ROUTING_WAIT_2,
    ROUTING_WAIT_3,
    ROUTING_WAIT_4
}
ROUTE_RoutingState;

typedef enum
{
    ROUTE_TEST_IDLE,
    ROUTE_TEST_WAIT_1,
    ROUTE_TEST_WAIT_2,
    ROUTE_TEST_WAIT_3,
    ROUTE_TEST_WAIT_4,
    ROUTE_TEST_WAIT_5
}
ROUTE_TestState;

/*
 * routes.  Must be globally unique.
 */
typedef struct _ROUTE_Info
{
    struct _ROUTE_Info  *next;          /* SCCP needs this for CPC lists */
    struct _ss7_context *dest;          /* back pointer to destination */
    ROUTE_BasicInfo     basic;          /* common header */
    ITS_UINT            priority;       /* priority of this route */
    ITS_UINT            rkey;           /* routing keys for ASPs */
    ITS_BOOLEAN         sendTFP;        /* administrative broadcast for this SP */

    /* the rest are run time variable */
    ITS_UINT            flags;
    ITS_BOOLEAN         isAllowed;      /* route is available */
    ITS_BOOLEAN         isRestricted;   /* route is restricted */
    ITS_BOOLEAN         inUse;          /* route is in use (dead) */
    ITS_BOOLEAN         qPut;           /* enqueue or transmit */
    SS7_LinkSetPtr      linkSet;        /* which linkset this route is attached to */
    DSM_Queue           *crBuf;         /* controlled rerouting buffer */
    ITS_OCTET           congLevel;      /* congestion level */
    ITS_OCTET           pad[3];         /* explicit padding */

    /* MTP3 state */
    ROUTE_ControlledReroutingState  controlledState;
    ROUTE_ForcedReroutingState      forcedState;
    ROUTE_CongestionState           congestionState;
    ROUTE_RoutingState              routingState;
    ROUTE_TestState                 testState;

    /* timers */
    ITS_SERIAL      t6;
    ITS_SERIAL      t8;
    ITS_SERIAL      t10;
    ITS_SERIAL      t11;
    ITS_SERIAL      t15;
    ITS_SERIAL      t16;
    ITS_SERIAL      t18;
    ITS_SERIAL      t25;
    ITS_SERIAL      t28;
    ITS_SERIAL      t29;
    ITS_SERIAL      t30;
}
ROUTE_Info;

/*
 * route flags
 */
#define ROUTE_CONTROLLED_REROUTING      (1U<<0)
#define ROUTE_FORCED_REROUTING          (1U<<1)
#define ROUTE_TEST_FOR_PROHIBITED       (1U<<2)
#define ROUTE_TEST_FOR_RESTRICTED       (1U<<3)
#define ROUTE_SENT_TFR_ONCE             (1U<<4)
#define ROUTE_SENT_TFR_TWICE            (1U<<5)
#define ROUTE_TRANSFER_PROHIBITED       (1U<<6)
#define ROUTE_TRANSFER_ALLOWED          (1U<<7)
#define ROUTE_TRANSFER_RESTRICTED       (1U<<8)
#define ROUTE_STP_IN_USE                (1U<<9)
#define ROUTE_USED                      (1U<<10)

/*
 * route pattern matching.
 */
typedef struct
{
    ROUTE_BasicInfo     basic;          /* common header */
    ITS_OCTET           linkSet;        /* specific link set */
    ITS_OCTET           linkCode;       /* specific link code */
    ITS_OCTET           priority;       /* congestion level */
    ITS_OCTET           sls;            /* sls key */
    ITS_UINT            rkey;           /* UALs only. */
}
ROUTE_MatchInfo;

/*
 * destination status
 */
typedef enum
{
    DESTINATION_UNAVAILABLE,
    DESTINATION_RESTRICTED,
    DESTINATION_AVAILABLE
}
DEST_Status;

/*
 * destination strings
 */
#define DEST_INFO_STRING    "destInfo"
#define DI_BEGIN_STRING     "beginDest"
#define DI_END_STRING       "endDest"
#define DI_MTP3_VAR_STRING  "mtp3Variant"
#define DI_ISUP_VAR_STRING  "isupVariant"
#define DI_SCCP_VAR_STRING  "sccpVariant"
#define DI_TCAP_VAR_STRING  "tcapVariant"
#define DI_TUP_VAR_STRING   "tupVariant"
#define DI_DUP_VAR_STRING   "dupVariant"

/*
 * routing table entry
 */
typedef struct _ss7_context
{
    ITS_UINT                numEntries;     /* num in use */
    ITS_UINT                maxEntries;     /* buffer size */
    ROUTE_Info              **entries;      /* route info */
    ITS_UINT                nextRoute;      /* key info */
    SS7_Family              family;         /* protocol family */

    /* MTP3 state */
    DEST_Status             status;         /* MTP3 status */
    ITS_UINT                currentStart;   /* current route start */
    ITS_UINT                currentStop;    /* current route stop */
    ITS_INT                 mtp3Variant;    /* MTP3 variant */
    ITS_INT                 isupVariant;    /* ISUP variant */
    ITS_INT                 sccpVariant;    /* SCCP variant */
    ITS_INT                 tcapVariant;    /* TCAP variant */
    ITS_INT                 tupVariant;     /* TUP variant (unused) */
    ITS_INT                 dupVariant;     /* DUP variant (unused) */

    /* timers */
    ITS_SERIAL              t8;
    ITS_SERIAL              t16;
    ITS_SERIAL              t18;

    /* peg counter */

    ITS_UINT    pegs[PEG_MTP3_DPC_NUM_PEGS];
    
    /* Route pegs for MTP3 */
    PEG_Manager MTP3_DPC_PEGS;
}
SS7_Destination;

/*
 * this needs to be public
 */
#define SS7_LINKSET_RID 1

typedef struct _app_context
{
    struct _app_context*    next;       /* link for transports that has to this bucket */
    ITS_HDR                 context;    /* app context for this route */
    ITS_USHORT              id;         /* transport associated with this app context */
}
ROUTE_AppContext;

/*.interface:ROUTE
 *****************************************************************************
 *  Interface:
 *      ROUTE_*
 *
 *  Purpose:
 *      The route interface is essential to message steering in the
 *      the multithreaded environment.  Routing (in this sense) is decision
 *      framework for deciding which task should get a particular message.
 *
 *      There are two types of automatic routing that IntelliSS7 provides
 *      SS7 routing (by destination point code, SIO, originating point code,
 *      SSN, CIC, SSN ranges and CIC ranges), and application routing, which
 *      is only automatic once an application has specified which ITS_HDR
 *      (or context information) is associated with which thread of execution.
 *
 *      It is mandatory that the reader understand what ITS_Transport(s)
 *      do and don't do; see
 *      <A HREF=its_transport.html>ITS_Transport</A>
 *      for details.
 *
 *      SS7 routing is automatic; when a transport indicates that it will
 *      carry routeable SS7 information (that is, when the transport is
 *      created with flags indicating SS7 transport: one or more of
 *      ITS_ISUP, ITS_TCAP, ITS_SCCP, or ITS_MTP3), then the resource DB
 *      will specify which SS7 destinations are reachable via that transport.
 *      In other words, the application configuration defines what destination
 *      routes are available.
 *
 *      The abstraction has grown over time in the following ways:
 *      a) The top level abstraction is now SS7_Destinations, which
 *      is defined by a point code and NI value.  However, they do
 *      not _have_ to be added.  Adding a route will automatically
 *      create a destination if it doesn't already exist.
 *      b) Routes (now global configuration objects) are defined for
 *      every path by which a destination can be reached.
 *      c) Different paths to a destination are characterized by having
 *      different link sets (different adjacent nodes).
 *      d) LinkSets are characterized by having one or more links.
 *
 *      In its current form, the Link object (see
 *      <A HREF=its_link.html>SS7_Link</A>
 *      for details) has a meaningful correlation with a transport.
 *      A transport is associated with one or more links.
 *
 *      A "default" route can also be specified.  This means that IF a
 *      default route is registered, and no other registered route can
 *      satisfy a route request, the links associated with the default
 *      route will be used to transport that SS7 message.
 *
 *      During transport creation, the transports must register their
 *      link information with the routing subsystem, via LINK_AddLink().
 *      When a transport is destroyed, they must remove this information
 *      from the routing subsystem (LINK_RemLink()).
 *
 *      Application routing is a slightly different beast.  Most SS7
 *      protocols have a "unit of work" that makes persistent, or
 *      long duration tasks undesirable from the application programmer's
 *      point of view.  Consider a single call in ISUP, or a connection
 *      in SCCP, or a transaction in TCAP.  In all of those situations,
 *      the easiest way to handle each unit-of-work is to treat it as if
 *      it were the only unit-of-work that had to be handled.  A different
 *      way of saying that is imagine if we were to write an ISUP message
 *      handler that only dealt with messages related to one call, or
 *      a TCAP transaction handler that only dealt with one transaction,
 *      or an SCCP connection handler that only dealt with one connection.
 *      Such beasts are relatively easy to code, you might guess, but
 *      are of little practical use -- they only handle one unit-of-work,
 *      right?  Well, if you add multithreading to the mix, you'd be
 *      wrong.  Why not dispatch each unit-of-work to a different thread?
 *      Then, you could write your more trivial, one unit-of-work code,
 *      but have multiple threads each handling one unit-of-work --
 *      which gives the same effect as writing more complicated code
 *      that handles multiple simultaneous units-of-work.
 *
 *      That's where application routing comes in.  At the start of a
 *      unit-of-work, IntelliSS7 has no idea which thread should handle
 *      the new unit-of-work (or "task"), so the application programmer
 *      must decide this based on resources available to him/her.
 *      How to make this decision is based on how many threads (if any)
 *      are available to the programmer.
 *
 *      There is a function that is invoked at the beginning of each task,
 *      called the "application route selector".  By default, the routing
 *      system is configured to send all new tasks to the same destination --
 *      the ITS_DEFAULT_USR_SRC.  This is exactly the behavior that a single
 *      threaded environment would expect -- send all new units-of-work, or
 *      tasks, to the same destination -- so applications written single
 *      threaded need never be aware of the routing system.
 *
 *      However, in a multi-threaded environment, the user can override
 *      this "application route selector" by defining a new function
 *      to be invoked at the beginning of a task -- and can then force the
 *      routing system to use this via ROUTE_SetApplicationSelector().
 *      NOTE: The selector function specified need NOT be thread safe:
 *      IntelliSS7 will ensure that the selector function executes
 *      in a "critical section" -- it need not be concerned with other
 *      entities that need to make a routing decision simultaneously.
 *      In fact, setting the route selector is guaranteed to be an
 *      atomic operation as well.  The selector function should add new
 *      application threads as the destination via ROUTE_AddApplication().
 *      You should understand that in a multi-threaded environment, a
 *      thread is identified by its transport -- see
 *      <A HREF=its_worker.html>ITS_Worker,</A>
 *      <A HREF=its_thread.html>ITS_Thread,</A> and
 *      <A HREF=its_transport.html>ITS_Transport</A>
 *      for detailed information on what this means.
 *
 *      There is one additional point that must be made.  When a thread
 *      has finished its unit-of-work, the task needs to remove its
 *      routing information from the table, so that new units-of-work that
 *      share the same context do not get dispatched to the same task
 *      without application intervention.  The thread should do this
 *      via ROUTE_DeleteApplication().
 *
 *  Usage:
 *
 *      Note that the methods in the routing subsystem are thread-safe
 *      and reentrant.
 *
 *      Usage for SS7 transports is as follows:
 *      ----------------------------------------------------------------
 *      * before anything else *
 *      if (ITS_GlobalStart(0) != ITS_SUCCESS)
 *      {
 *          * THIS IS A FATAL ERROR!!! *
 *          exit(EXIT_FAILURE);
 *      }
 *
 *      ...
 *
 *      * global route objects *
 *      if (ROUTE_AddRouteContext(REMOTE_ROUTE, ROUTE_DPC_SIO_SSN,
 *                                pointCode, ROUTE_SIO_SCCP, ssn) != ITS_SUCCESS)
 *      {
 *          * error adding destination *
 *      }
 *
 *      ...
 *
 *      * callers that need routing information can use the following *
 *      instance = ROUTE_SelectRoute(pointCode, ssn);
 *      if (instance == ITS_INVALID_SRC || instance == ITS_NO_SRC)
 *      {
 *          * no route to destination exists *
 *      }
 *
 *      * or *
 *      if (!ROUTE_IsRoute(instance))
 *      {
 *          * instance is not an SS7 route *
 *      }
 *
 *      ...
 *
 *      * when a transport terminates, it should delete itself *
 *      if (ROUTE_DeleteRoute(instance, pointCode, ssn) != ITS_SUCCESS)
 *      {
 *          * an error occurred deleting the route *
 *      }
 *
 *      ...
 *
 *      * when an application terminates, it should try to call *
 *      ROUTE_Termination();
 *      * when that function is invoked, no further routing should be
 *      * attempted. *
 *      -------------------------------------------------------------------
 *
 *      Application routing follows a slightly different path:
 *
 *      -------------------------------------------------------------------
 *      * the routing subsystem should already be initialized *
 *
 *      ...
 *
 *      * the routing selector should be set:
 *      ITS_USHORT
 *      newRouteSelector(ITS_HDR* context)
 *      {
 *          * decide somehow which application to dispatch to *
 *          if (ROUTE_AddApplication(instance, context) != ITS_SUCCESS)
 *          {
 *              * an error occurred adding the app route *
 *          }
 *
 *          return instance;
 *      }
 *
 *      ...
 *
 *      * when an application thread is no longer relevant *
 *      ROUTE_DeleteApplication(instance, context);
 *
 *      ...
 *
 *      * IntelliSS7 APIs will call the following:
 *      if (ROUTE_SelectApplication(context) != ITS_SUCCESS)
 *      {
 *          *
 *          * a routing failure has occurred.  As part of the call
 *          * to ROUTE_SelectApplication(), if an application route does
 *          * NOT exist, the ApplicationSelector callback will be invoked
 *          * in an attempt to get the application to create a NEW route.
 *          *
 *      }
 *
 *      if (!ROUTE_IsApplication(instance))
 *      {
 *          * instance is not an application route *
 *      }
 *      ------------------------------------------------------------------
 *
 *      Again, all of this code is thread-safe and reentrant.
 *
 *      Addendum: As of PR4, the routing table has completely changed
 *      in terms of the implementation and matching algorithms for SS7
 *      routing (it has not changed at all for application routing).
 *
 *      You may now specify SSN and CIC ranges (but ONLY when adding
 *      routes, deleting routes, or setting a route state).
 *
 *      1) You may now specify SIO, DPC, OPC, and SSN or CIC as the routing
 *      criteria (these are sanity checked; for example, you cannot
 *      specify an SIO of ISUP and try to match an SSN).
 *
 *      2) You may now specify SIO, DPC, and OPC as the routing criteria.
 *
 *      3) You may now specify SIO and DPC as the routing criteria.
 *
 *      4) You may now specify DPC and OPC as the routing criteria.
 *
 *      5) You may now specify DPC only as the routing criteria.
 *
 *      The order (1-5) above is the matching order.  That is, the
 *      tightest match is the one taken.
 *
 *      The syntax for using the varargs interface is as follows, wherever
 *      you see the argument "style" (ellipsis is for the preceding args):
 *
 *
 *      ..., ROUTE_DPC_ONLY, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_SIO, ROUTE_SIO_SCCP,  // note that the complete
 *           linkSet, linkCode, linkPri);    // defines appear in mtp3.h
 *
 *      ..., ROUTE_DPC_SIO_SSN_RANGE, ROUTE_SIO_SCCP, // mandatory
 *           startSSN, endSSN, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_SIO_CIC_RANGE, ROUTE_SIO_ISUP, // mandatory
 *           startCIC, endCIC, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_SIO_SSN, ROUTE_SIO_SCCP, ssn,  // SIO mandatory
 *           linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_SIO_CIC, ROUTE_SIO_ISUP, cic,  // SIO mandatory
 *           linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_OPC, 0x00123456, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_OPC_SIO, 0x00123456, ROUTE_SIO_SCCP,
 *           linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_OPC_SIO_SSN_RANGE, 0x00123456,
 *           ROUTE_SIO_SCCP, startSSN, endSSN, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_OPC_SIO_CIC_RANGE, 0x00123456,
 *           ROUTE_SIO_ISUP, startCIC, endCIC, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_OPC_SIO_SSN, 0x00123456,
 *           ROUTE_SIO_SCCP, ssn, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_OPC_SIO_CIC, 0x00123456,
 *           ROUTE_SIO_ISUP, cic, linkSet, linkCode, linkPri);
 *
 *      ..., ROUTE_DPC_UDEF, userData, userDataLen,
 *           linkSet, linkCode, linkPri);
 *          // note that in this case only the *pointer* is copied.
 *          // the default pattern matcher does *not* handle this case.
 *
 *      Note: wherever you see linkSet, linkCode above, the user can
 *      ITS_SS7_DEFAULT_LINK_SET, ITS_SS7_DEFAULT_LINK_CODE if no specific
 *      linkSet/linkCode is desired.  This will normally be the case; the
 *      exception will be ISUP and SCCP pclass 1, which will want to ensure
 *      ordering between subsequent messages.  Even in this case, the link
 *      set will normally be a don't care (as there will typically be only
 *      one link set anyway).
 *
 *      Update: For PR6, the SIO parameter has become mandatory.  That
 *      means that DPC_ONLY and DPC_OPC route styles are obsolete.  Further,
 *      the user had better specify a network indicator value in the SIO
 *      field, or it may get used for the wrong purposes.
 *
 *      As of PR6, a ROUTE_MASK may be specified.  This is a mask that will
 *      be AND'd with a DPC for coarser route matching.  The algorithm for
 *      route lookup is as follows:
 *      1) Look for raw DPC first.  If found, return route.
 *      2) For each mask,
 *          lookupDPC = DPC & mask
 *          Look for lookkupDPC.  If found, return route.
 *      There may be up to 32 unique masks.  In practice, you will find
 *      you seldom need more than one or two.
 *
 *****************************************************************************/

/*
 * for SS7.  These are defined locally for backwards compatibility.
 * The full list (and the network indicators) can be found in mtp3.h.
 */
#define ROUTE_SIO_SCCP  3
#define ROUTE_SIO_ISUP  5
#define ROUTE_UP_MASK   0x0FU
#define ROUTE_PRI_MASK  0x30U
#define ROUTE_NI_MASK   0xC0U

/*
 * user may want to fetch the routing records (think UALs).
 * Note that the lock is a shared one, so be careful what you
 * do while holding it.
 */
ITSDLLAPI int                 ROUTE_LockTable();
ITSDLLAPI int                 ROUTE_UnlockTable();

/*
 * route numbering (again, think UALs)
 */
ITSDLLAPI int         ROUTE_AddRoutingKey(ITS_UINT rkey,
                                          ITS_UINT pointCode,
                                          ROUTE_CRITERIA style,
                                          SS7_Family family, ...);

ITSDLLAPI int         ROUTE_AddRoutingKeyInfo(ITS_UINT rkey,
                                              ROUTE_MatchInfo *rinfo);

ITSDLLAPI int         ROUTE_FindRoutingKeyInfo(ITS_UINT rkey,
                                               ROUTE_Info ***rinfo);

ITSDLLAPI int         ROUTE_FindRoutingKey(ITS_UINT *rkey,
                                           ITS_UINT pointCode,
                                           ROUTE_TYPE type,
                                           ROUTE_CRITERIA style,
                                           SS7_Family family,
                                           ...);

ITSDLLAPI int         ROUTE_FindRoutingKeyByInfo(ITS_UINT *rkey,
                                                 ROUTE_MatchInfo *rinfo);

ITSDLLAPI int         ROUTE_DeleteRoutingKey(ITS_UINT rkey);

/*
 * common parser
 */
ITSDLLAPI int         ROUTE_ParseRouteMatchInfoArgs(ROUTE_MatchInfo *rinfo,
                                                    ITS_UINT pointCode,
                                                    ROUTE_TYPE type,
                                                    ROUTE_CRITERIA style,
                                                    SS7_Family family,
                                                    ...);
ITSDLLAPI int         ROUTE_ParseRouteMatchInfo(ROUTE_MatchInfo *rinfo,
                                                ITS_UINT pointCode,
                                                ROUTE_TYPE type,
                                                ROUTE_CRITERIA style,
                                                SS7_Family family,
                                                va_list *args);

/* addition */
ITSDLLAPI int         ROUTE_AddRouteContextInfo(ROUTE_MatchInfo *add);

ITSDLLAPI int         ROUTE_AddRouteContext(ITS_UINT pointCode,
                                            ROUTE_TYPE type, ROUTE_CRITERIA style,
                                            SS7_Family family, ...);

/* selection */
ITSDLLAPI ITS_USHORT  ROUTE_SelectRouteContextInfo(ROUTE_MatchInfo *rinfo);

ITSDLLAPI ITS_USHORT  ROUTE_SelectRouteContext(ITS_UINT pc,
                                               ROUTE_CRITERIA style,
                                               SS7_Family family,
                                               ...);

/* deletion */
ITSDLLAPI int         ROUTE_DeleteRouteContextInfo(ROUTE_MatchInfo *rinfo);

ITSDLLAPI int         ROUTE_DeleteRouteContext(ITS_UINT pointCode,
                                               ROUTE_TYPE type,
                                               ROUTE_CRITERIA style,
                                               SS7_Family family,
                                               ...);

/* dispatch */
ITSDLLAPI int         ROUTE_SendToRouteContextInfo(ROUTE_MatchInfo *rinfo,
                                                   ITS_EVENT *ev);

ITSDLLAPI int         ROUTE_SendToRouteContext(ITS_UINT pc, ITS_EVENT *ev,
                                               ROUTE_CRITERIA style,
                                               SS7_Family family, ...);

/* existence */
ITSDLLAPI ITS_USHORT  ROUTE_RouteContextInfoExists(ROUTE_MatchInfo *rinfo);

ITSDLLAPI ITS_USHORT  ROUTE_RouteContextExists(ITS_UINT pointCode,
                                               ROUTE_CRITERIA style,
                                               SS7_Family family, ...);

/* state means pause/resumed */
ITSDLLAPI int         ROUTE_SetRouteContextInfoState(ROUTE_MatchInfo *rinfo,
                                                     ITS_BOOLEAN isAllowed);

ITSDLLAPI int         ROUTE_SetRouteContextState(ITS_BOOLEAN isAllowed,
                                                 ITS_UINT pointCode,
                                                 ROUTE_CRITERIA style,
                                                 SS7_Family family,
                                                 ...);

ITSDLLAPI int         ROUTE_GetRouteContextInfoState(ROUTE_MatchInfo *rinfo,
                                                     ITS_BOOLEAN* isAllowed);

ITSDLLAPI int         ROUTE_GetRouteContextState(ITS_UINT pointCode,
                                                 ITS_BOOLEAN* isAllowed,
                                                 ROUTE_CRITERIA style,
                                                 SS7_Family family,
                                                 ...);

ITSDLLAPI int         ROUTE_SetRouteAdminInfoStatus(ROUTE_MatchInfo *rinfo,
                                                      ITS_BOOLEAN isAllowed);

ITSDLLAPI int         ROUTE_SetRouteAdminStatus(ITS_UINT pointCode,
                                                  ITS_BOOLEAN isAllowed,
                                                  ROUTE_CRITERIA style,
                                                  SS7_Family family,
                                                  ...);

ITSDLLAPI int         ROUTE_GetRouteAdminInfoStatus(ROUTE_MatchInfo *rinfo,
                                                      ITS_BOOLEAN *isAllowed);

ITSDLLAPI int         ROUTE_GetRouteAdminStatus(ITS_UINT pointCode,
                                                  ITS_BOOLEAN* isAllowed,
                                                  ROUTE_CRITERIA style,
                                                  SS7_Family family,
                                                  ...);


/* status means allowed/prohibited */
ITSDLLAPI int         ROUTE_SetRouteContextInfoStatus(ROUTE_MatchInfo *rinfo,
                                                      ITS_BOOLEAN isAllowed);

ITSDLLAPI int         ROUTE_SetRouteContextStatus(ITS_UINT pointCode,
                                                  ITS_BOOLEAN isAllowed,
                                                  ROUTE_CRITERIA style,
                                                  SS7_Family family,
                                                  ...);

ITSDLLAPI int         ROUTE_GetRouteContextInfoStatus(ROUTE_MatchInfo *rinfo,
                                                      ITS_BOOLEAN *isAllowed);

ITSDLLAPI int         ROUTE_GetRouteContextStatus(ITS_UINT pointCode,
                                                  ITS_BOOLEAN* isAllowed,
                                                  ROUTE_CRITERIA style,
                                                  SS7_Family family,
                                                  ...);

ITSDLLAPI int         ROUTE_GetRouteContextInfoLocal(ROUTE_MatchInfo *rinfo,
                                                     ITS_BOOLEAN *isLocal);

ITSDLLAPI int         ROUTE_GetRouteContextLocal(ITS_UINT pointCode,
                                                 ITS_BOOLEAN* isLocal,
                                                 ROUTE_CRITERIA style,
                                                 SS7_Family family,
                                                 ...);

ITSDLLAPI int         ROUTE_SetRouteContextInfoCongestion(ROUTE_MatchInfo *rinfo,
                                                          ITS_OCTET congLevel);

ITSDLLAPI int         ROUTE_SetRouteContextCongestion(ITS_UINT pointCode,
                                                      ITS_OCTET congLevel,
                                                      ROUTE_CRITERIA style,
                                                      SS7_Family family,
                                                      ...);

ITSDLLAPI int         ROUTE_GetRouteContextInfoCongestion(ROUTE_MatchInfo *rinfo,
                                                          ITS_OCTET *congLevel);

ITSDLLAPI int         ROUTE_GetRouteContextCongestion(ITS_UINT pointCode,
                                                      ITS_OCTET* congLevel,
                                                      ROUTE_CRITERIA style,
                                                      SS7_Family family,
                                                      ...);


/*
 * selection functions.  Most aren't for use by the user.
 */

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
ITSDLLAPI ITS_OCTET ROUTE_SLSRotate(ITS_BOOLEAN do8Bit, ITS_OCTET sls,
                                    ITS_OCTET *linkSetSelect,
                                    ITS_OCTET *linkSelect,
                                    SS7_Destination *match,
                                    ITS_OCTET numLinkset,
                                    ITS_OCTET firstMatch);

ITSDLLAPI ITS_OCTET ROUTE_SLSUnrotate(ITS_BOOLEAN do8Bit, ITS_OCTET sls);

/*
 * find the best match, based on the routing information
 */
ITSDLLAPI SS7_Destination *ROUTE_FindBestMatch(ROUTE_MatchInfo *rinfo,
                                               int *whichEntry,
                                               int *firstMatch,
                                               int *lastMatch,
                                               int *whichLinkCode,
                                               ITS_BOOLEAN rangeAllowed);

/*
 * set the "current" route (to be used by MTP3).  Note the route
 * may be up, but events might be queued instead of transmitted.
 */
ITSDLLAPI int ROUTE_SetCurrentRoute(ROUTE_MatchInfo *rinfo);

/*
 * find/commit a destination or a route
 */
ITSDLLAPI SS7_Destination *ROUTE_FindDestination(ITS_UINT pointCode,
                                                 ITS_OCTET ni,
                                                 SS7_Family family);
ITSDLLAPI int              ROUTE_CommitDestination(SS7_Destination *dest,
                                                   ITS_UINT dpc,
                                                   ITS_OCTET ni,
                                                   SS7_Family family);
ITSDLLAPI int              ROUTE_CommitRoute(ROUTE_Info *rinfo);

/*
 * select the next link to use.
 */
ITSDLLAPI ITS_USHORT ROUTE_SelectLink(SS7_Destination *match,
                                      ROUTE_MatchInfo *userInfo,
                                      int whichEntry,
                                      int firstMatch, int lastMatch,
                                      int whichLinkCode,
                                      ITS_OCTET *sls);

/*
 * for applications
 */
ITSDLLAPI int         ROUTE_AddApplication(ITS_USHORT id, ITS_HDR* hdr);
ITSDLLAPI ITS_USHORT  ROUTE_SelectApplication(ITS_HDR* hdr, ITS_EVENT* ev,
                                              ITS_BOOLEAN callCallback);
ITSDLLAPI int         ROUTE_DeleteApplication(ITS_USHORT id, ITS_HDR* hdr);
ITSDLLAPI void        ROUTE_DeselectApplication(ITS_USHORT id, ITS_HDR *hdr);
ITSDLLAPI ITS_BOOLEAN ROUTE_IsApplicationSelectorDefault();
ITSDLLAPI ITS_BOOLEAN ROUTE_IsSS7SelectorDefault();

/*
 * application routing is dynamic, so we provide a callback hook
 * for application writers to modify the application routing
 * tables.
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 *   DO NOT THROW EXCEPTIONS FROM THIS CALL.  THE CALLER IS A "C" FUNCTION
 *   THAT HAS A LOCKED MUTEX.  AN UNCAUGHT EXCEPTION ORIGINATING FROM THIS
 *   FUNCTION MEANS THE MUTEX WILL STAY LOCKED, EFFECTIVELY BLOCKING ANY NEW
 *   TCAP TRANSACTION OR SCCP CONNECTION FROM THE PROGRAM.  YOU HAVE BEEN
 *   WARNED.
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 */
typedef ITS_USHORT  (*ROUTE_AppSelector)(ITS_HDR* hdr, ITS_EVENT* ev);
typedef ITS_USHORT  (*ROUTE_SS7Selector)(ROUTE_MatchInfo* rinfo, ITS_EVENT *ev);
typedef void        (*ROUTE_AppDeselector)(ITS_USHORT id, ITS_HDR *hdr);

/*
 * default functions for the above
 */
ITSDLLAPI ITS_USHORT    ROUTE_SendToDefault(ITS_HDR* h, ITS_EVENT* ev);
ITSDLLAPI ITS_USHORT    ROUTE_SendToSS7(ROUTE_MatchInfo* rinfo, ITS_EVENT* ev);

ITSDLLAPI ROUTE_AppSelector     ROUTE_SetApplicationSelector(ROUTE_AppSelector);
ITSDLLAPI ROUTE_AppDeselector   ROUTE_SetApplicationDeselector(ROUTE_AppDeselector);
ITSDLLAPI ROUTE_SS7Selector     ROUTE_SetSS7Selector(ROUTE_SS7Selector);

/*
 * predicates
 */
ITSDLLAPI ITS_BOOLEAN ROUTE_IsApplication(ITS_USHORT id);
ITSDLLAPI ITS_BOOLEAN ROUTE_IsRoute(ITS_USHORT id);

/*
 * the use of these routines is recommended when sending to transient
 * routes or applications.  These routines assure that the application/route
 * is still available before sending the information.
 */
ITSDLLAPI int ROUTE_SendToApplication(ITS_HDR* hdr, ITS_EVENT* event);

ITSDLLAPI int ROUTE_Clean(ITS_USHORT instance);
ITSDLLAPI int ROUTE_AppClean(ITS_USHORT instance);
ITSDLLAPI int ROUTE_SS7Clean(ITS_USHORT instance);

/*
 * Dump of routing hashtables (debug purpose).
 */

ITSDLLAPI int ROUTE_DumpIdToSS7Hashtable(char** pStrDump);
ITSDLLAPI int ROUTE_DumpSS7ToIdHashtable(char** pStrDump);
ITSDLLAPI int ROUTE_DumpIdToAppHashtable(char** pStrDump);
ITSDLLAPI int ROUTE_DumpAppToIdHashtable(char** pStrDump);

/*
 * class record
 */
typedef ITS_ClassRec        ROUTE_ClassRec;

#define ROUTE_CLASS_NAME    "ROUTE_CLASS"

ITSDLLAPI extern ROUTE_ClassRec       itsAPP_ROUTE_ClassRec;
ITSDLLAPI extern ITS_Class            itsAPP_ROUTE_Class;

ITSDLLAPI extern ROUTE_ClassRec       itsSS7_ROUTE_ClassRec;
ITSDLLAPI extern ITS_Class            itsSS7_ROUTE_Class;

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_mutex.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:RoutingMap
 *****************************************************************************
 *  Interface:
 *      RoutingMap
 *
 *  Purpose:
 *      For those programmers more comfortable working in C++, an object has
 *      been provided that wrappers the C-API to the routing subsystem.
 *      The signatures of methods in this class are exactly the same as their
 *      C counterparts.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * a structure for manipulating ss7 data
 */
class RoutingMap
{
public:
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method sets the new application selector.
     *
     *  Input Parameters:
     *      selector - the new application selector callback.
     *
     ************************************************************************/
    static ROUTE_AppSelector
    SetApplicationSelector(ROUTE_AppSelector s)
    {
        return ROUTE_SetApplicationSelector(s);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method sets the new application selector.
     *
     *  Input Parameters:
     *      selector - the new application selector callback.
     *
     ************************************************************************/
    static ROUTE_SS7Selector
    SetSS7Selector(ROUTE_SS7Selector s)
    {
        return ROUTE_SetSS7Selector(s);
    }

    /* SS7 routing functions */
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method is used by SS7-capable transports to add routes
     *      for automatic SS7 routing.
     *
     *  Input Parameters:
     *      id - the instance id of the transport adding this route
     *      pointCode - the pointCode of the route to be added
     *      type - local, remote, or concerned
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If the route is successfully added, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      It is possible to add several routes to the same point code, but
     *      with different routing info.  An attempt to add the same route
     *      twice (all data the same) will result in an error.
     *
     ************************************************************************/
    static int
    AddRouteContext(ITS_USHORT id, ITS_UINT pointCode,
                    ROUTE_TYPE type, ROUTE_CRITERIA style,
                    SS7_Family family, ...)
    {
        ROUTE_MatchInfo tmp;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&tmp, pointCode, type, style,
                                  family, &alist);

        va_end(alist);

        return ROUTE_AddRouteContextInfo(&tmp);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and attempts to find an
     *      instance/transport that can route to that destination.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If a transport is identified as having a route to this destination,
     *          the transport/instance id is returned.
     *      If no route is available, ITS_NO_SRC is returned.
     *      Any other return value indicates a processing error.
     *
     *  See Also:
     *      ROUTE_SelectRouteContext()
     ************************************************************************/
    static ITS_USHORT
    SelectRouteContext(ITS_UINT pointCode, ROUTE_CRITERIA style,
                       SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE, style,
                                  family, &alist);

        va_end(alist);

        return ROUTE_SelectRouteContextInfo(&rinfo);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method allows the user to find out if the default selector
     *      function has been overridden.
     *
     *  Return Value:
     *      ITS_TRUE - selector has been overriden.  ITS_FALSE otherwise.
     *
     *  See Also:
     ************************************************************************/
    static ITS_BOOLEAN
    IsAppSelectorDefault()
    {
        return ROUTE_IsApplicationSelectorDefault();
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method allows the user to find out if the default selector
     *      function has been overridden.
     *
     *  Return Value:
     *      ITS_TRUE - selector has been overriden.  ITS_FALSE otherwise.
     *
     *  See Also:
     ************************************************************************/
    static ITS_BOOLEAN
    IsSS7SelectorDefault()
    {
        return ROUTE_IsSS7SelectorDefault();
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and attempts to find an
     *      instance/transport that can route to that destination.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If a transport is identified as having a route to this destination,
     *          the transport/instance id is returned.
     *      If no route is available, ITS_NO_SRC is returned.
     *      Any other return value indicates a processing error.
     *
     ************************************************************************/
    static ITS_USHORT
    RouteContextExists(ITS_UINT pointCode, ROUTE_CRITERIA style,
                       SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE, style,
                                  family, &alist);

        va_end(alist);

        return ROUTE_RouteContextInfoExists(&rinfo);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and sets the
     *      paused/resumed state.
     *
     *  Input Parameters:
     *      id - the transport to change the state of this route for
     *      pointCode - the point code to send to
     *      isUp - if the dest is paused/resumed
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  Notes:
     *
     *  See Also:
     *      ROUTE_GetRouteContextState()
     ************************************************************************/
    static int
    SetRouteContextState(ITS_BOOLEAN isUp, ITS_UINT pointCode,
                         ROUTE_CRITERIA style, SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_SetRouteContextInfoState(&rinfo, isUp);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and gets the
     *      paused/resumed state.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Output Parameters:
     *      isUp - if the dest is allowed/prohibited
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  See Also:
     *      ROUTE_SetRouteContextState()
     ************************************************************************/
    static int
    GetRouteContextState(ITS_UINT pointCode, ITS_BOOLEAN* isUp,
                         ROUTE_CRITERIA style, SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_GetRouteContextInfoState(&rinfo, isUp);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and sets the
     *      allowed/prohibited state.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      isAllowed - if the dest is allowed/prohibited
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  See Also:
     *      ROUTE_GetRouteContextState()
     ************************************************************************/
    static int
    SetRouteContextStatus(ITS_UINT pointCode, ITS_BOOLEAN isAllowed,
                          ROUTE_CRITERIA style, SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_SetRouteContextInfoStatus(&rinfo, isAllowed);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and gets the
     *      allowed/prohibited state.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Output Parameters:
     *      isAllowed - if the dest is allowed/prohibited
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  See Also:
     *      ROUTE_SetRouteContextState()
     ************************************************************************/
    static int
    GetRouteContextStatus(ITS_UINT pointCode, ITS_BOOLEAN* isAllowed,
                          ROUTE_CRITERIA style, SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_GetRouteContextInfoStatus(&rinfo, isAllowed);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and gets the
     *      local/remote state.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Output Parameters:
     *      isLocal - if the dest is local/remote
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     ************************************************************************/
    static int
    GetRouteContextLocal(ITS_UINT pointCode, ITS_BOOLEAN* isLocal,
                         ROUTE_CRITERIA style, SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_GetRouteContextInfoLocal(&rinfo, isLocal);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and sets the
     *      congestion level.
     *
     *  Input Parameters:
     *      id - the link to set the congestion level for
     *      pointCode - the point code to send to
     *      congLevel - the congestion level
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  See Also:
     *      ROUTE_GetRouteContextCongestion()
     ************************************************************************/
    static int
    SetRouteContextCongestion(ITS_UINT pointCode,
                              ITS_OCTET congLevel, ROUTE_CRITERIA style,
                              SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_SetRouteContextInfoCongestion(&rinfo, congLevel);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This method takes a pointCode/SSN pair and gets the
     *      allowed/prohibited state.
     *
     *  Input Parameters:
     *      pointCode - the point code to send to
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Output Parameters:
     *      congLevel - the congestion level
     *
     *  Return Value:
     *      If the state is set, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  Notes:
     *
     *  See Also:
     *      ROUTE_SetRouteCongestion()
     ************************************************************************/
    static int
    GetRouteContextCongestion(ITS_UINT pointCode, ITS_OCTET* congLevel,
                              ROUTE_CRITERIA style, SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, DONT_CARE,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_GetRouteContextInfoCongestion(&rinfo, congLevel);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows a transport to remove a route from service.
     *      Transports should call this function when they terminate.
     *
     *  Input Parameters:
     *      id - the id of the transport being removed.
     *      pointCode - the DPC to remove from routing
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If the route is successfully deleted, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     *  See Also:
     *      ROUTE_DeleteRoute()
     ************************************************************************/
    static int
    DeleteRouteContext(ITS_UINT pointCode,
                       ROUTE_TYPE type, ROUTE_CRITERIA style,
                       SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pointCode, type,
                                  style, family, &alist);

        va_end(alist);

        return ROUTE_DeleteRouteContextInfo(&rinfo);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows the caller to determine if a transport instance
     *      has registered SS7 routes.
     *
     *  Input Parameters:
     *      id - the instance number of the transport to test.
     *
     *  Return Value:
     *      If the instance has registered routes, ITS_TRUE is returned.
     *      If an error occurred or there are no SS7 routes registered for this
     *          instance, ITS_FALSE is returned.
     *
     *  See Also:
     *      ROUTE_IsRoute()
     ************************************************************************/
    static ITS_BOOLEAN
    IsRoute(ITS_USHORT id)
    {
        return ROUTE_IsRoute(id);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows the programmer to send a message to a
     *      context description, without necessarily being aware of the
     *      actual destination.
     *
     *  Input Parameters:
     *      pointCode - the DPC to remove from routing
     *      ev - a reference to the event to be sent.
     *      style - the route style
     *      ... - determined by the route style
     *
     *  Return Value:
     *      If the event is successfully transmitted, ITS_SUCCESS is
     *          returned.
     *      Else an IntelliSS7 processing error is returned.
     *
     *  See Also:
     *      ROUTE_IsApplication()
     ************************************************************************/
    static int
    SendToRouteContext(ITS_UINT pc, Event& ev, ROUTE_CRITERIA style,
                       SS7_Family family, ...)
    {
        ROUTE_MatchInfo rinfo;
        va_list alist;

        va_start(alist, family);

        ROUTE_ParseRouteMatchInfo(&rinfo, pc, DONT_CARE, style,
                                  family, &alist);

        va_end(alist);

        return ROUTE_SendToRouteContextInfo(&rinfo, &ev.GetEvent());
    }

    /* application routing functions */
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows the application writer to add an application
     *      to the routing table.  The application MUST provide context
     *      informationwhen adding the route.  Note that the same application
     *      instance can be added multiple times, as long as the context
     *      information is different fer each addition.
     *
     *  Input Parameters:
     *      id - the application/transport instance to add
     *      hdr - a pointer to the context information for this addition
     *
     *  Return Value:
     *      If the route is successfully added, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 processing error.
     *
     *  See Also:
     *      ROUTE_AddApplication()
     ************************************************************************/
    static int
    AddApplication(ITS_USHORT id, ITS_HDR* hdr)
    {
        return ROUTE_AddApplication(id, hdr);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function is used by IntelliSS7 APIs to automatically select
     *      applications to deliver messages to.  The application must have been
     *      added by the user before this function can succeed.
     *
     *  Input Parameters:
     *      hdr - a pointer to the context information to route by
     *
     *  Return Value:
     *      If a route is found for this context, the application/transport
     *          instance id is returned.
     *      If no route is found, ITS_NO_SRC is returned.
     *      Any other return value indicates an IntelliSS7 processing error.
     *
     *  See Also:
     *      ROUTE_SelectApplication()
     ************************************************************************/
    static ITS_USHORT
    SelectApplication(ITS_HDR* hdr, Event& ev, ITS_BOOLEAN callCallback)
    {
        return ROUTE_SelectApplication(hdr, &ev.GetEvent(), callCallback);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows an application to remove a route to itself
     *      based on the context by which the route was added.  Applications
     *      should use this function at the end of a unit-of-work to indicate
     *      that it will no longer accept further messages in that context.
     *
     *  Input Parameters:
     *      id - the transport/application instance to remove from the routing
     *          table
     *      hdr - a pointer to the context information for this particular route
     *
     *  Return Value:
     *      If the route is successfully deleted, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 processing error.
     *
     *  See Also:
     *      ROUTE_DeleteApplication()
     ************************************************************************/
    static int
    DeleteApplication(ITS_USHORT id, ITS_HDR* hdr)
    {
        return ROUTE_DeleteApplication(id, hdr);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows IntelliSS7 APIs to determine if an application
     *      has added routes to itself.
     *
     *  Input Parameters:
     *      id - the application/transport instance to search for in the
     *          application routing table
     *
     *  Return Value:
     *      If an application has registered routes to itself, ITS_TRUE is
     *          returned.
     *      If an error occurs, or no routes have been registered, ITS_FALSE is
     *          returned.
     *
     *  See Also:
     *      ROUTE_IsApplication()
     ************************************************************************/
    static ITS_BOOLEAN
    IsApplication(ITS_USHORT id)
    {
        return ROUTE_IsApplication(id);
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function allows the programmer to send a message to a
     *      context description, without necessarily being aware of the
     *      actual destination.
     *
     *  Input Parameters:
     *      hdr - a pointer to the context information for this particular route
     *      ev - a reference to the event to be sent.
     *
     *  Return Value:
     *      If the event is successfully transmitted, ITS_SUCCESS is
     *          returned.
     *      Else an IntelliSS7 processing error is returned.
     *
     *  See Also:
     *      ROUTE_IsApplication()
     ************************************************************************/
    static int
    SendToApplication(ITS_HDR* hdr, Event& ev)
    {
        return ROUTE_SendToApplication(hdr, &ev.GetEvent());
    }
    /*.implementation:public,inline,RoutingMap
     ************************************************************************
     *  Purpose:
     *      This function cleans routes from service.
     *
     *  Input Parameters:
     *      id - the id of the transport being removed.
     *
     *  Return Value:
     *      If the routes are successfully deleted, ITS_SUCCESS is returned.
     *      Any other return value indicates a processing error.
     *
     ************************************************************************/
    static int
    Clean(ITS_USHORT id)
    {
        return ROUTE_Clean(id);
    }

private:
    RoutingMap() { }
    RoutingMap(RoutingMap& copy) { }
    RoutingMap& operator=(RoutingMap& copy) { return (*this); }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif  /* USE_CPLUSPLUS */

#endif  /* ITS_ROUTE_H */
