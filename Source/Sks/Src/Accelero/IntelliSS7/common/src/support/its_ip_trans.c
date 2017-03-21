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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:02  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.4.1.4.1.6.2  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2.4.1.4.1.6.1  2004/12/16 03:30:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.4.1.4.1  2004/09/29 09:56:14  asingh
 * LOG: Changes for linux ES 30 operating system; compilation issue.
 * LOG:
 * LOG: Revision 7.2.4.1  2003/09/12 22:52:59  lbana
 * LOG: Set isActive flag for remote transports to true|false
 * LOG:
 * LOG: Revision 7.2  2002/09/26 22:59:29  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/07/05 19:58:21  mmiers
 * LOG: Add PRC IP transports
 * LOG:
 * LOG: Revision 6.3  2002/07/05 19:33:59  yranade
 * LOG: Fix flag handling for IP transports.  Warning removal.
 * LOG:
 * LOG: Revision 6.2  2002/03/20 17:12:47  mmiers
 * LOG: Performance improvement.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10  2002/01/09 21:21:59  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.9  2001/11/16 16:40:35  mmiers
 * LOG: Don't block in accept.  Make the dispatchers aware of this.
 * LOG:
 * LOG: Revision 5.8  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.7  2001/11/08 00:37:17  mmiers
 * LOG: Incorrect arg
 * LOG:
 * LOG: Revision 5.6  2001/11/08 00:30:51  mmiers
 * LOG: Need loop counter
 * LOG:
 * LOG: Revision 5.5  2001/11/07 23:50:36  mmiers
 * LOG: Delete half formed remotes if a create failed.
 * LOG:
 * LOG: Revision 5.4  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 00:14:16  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.2  2001/10/17 15:59:41  mmiers
 * LOG: Change GDI, IMAL, TALI so both protocol families can be
 * LOG: used simultaneously.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.7  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.6  2001/06/16 00:34:33  mmiers
 * LOG: Catch zero length writes.
 * LOG:
 * LOG: Revision 4.5  2001/05/16 20:10:53  mmiers
 * LOG: Locating bottlenecks.
 * LOG:
 * LOG: Revision 4.4  2001/05/04 14:30:52  mmiers
 * LOG: A few bug fixes from PR4.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:06:02  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.16  2001/04/25 00:39:54  mmiers
 * LOG: Fix up termination semantics on Linux.
 * LOG:
 * LOG: Revision 3.15  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.14  2001/03/02 22:44:15  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 3.13  2001/02/14 20:44:54  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.12  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.11  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.10  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.9  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.8  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.7  2000/12/21 20:37:00  mmiers
 * LOG: Old bug parsing.
 * LOG:
 * LOG: Revision 3.6  2000/12/19 22:24:40  mmiers
 * LOG: Registration is base class.
 * LOG:
 * LOG: Revision 3.5  2000/12/19 21:30:17  mmiers
 * LOG: Use the right mask
 * LOG:
 * LOG: Revision 3.4  2000/11/16 23:01:55  mmiers
 * LOG: Add the SCTP transport.  Getting close on this...
 * LOG:
 * LOG: Revision 3.3  2000/10/03 21:17:09  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:40  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:31  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.42  2000/08/09 01:03:13  mmiers
 * LOG: Correct linux build.
 * LOG:
 * LOG: Revision 2.41  2000/07/10 22:50:27  mmiers
 * LOG:
 * LOG:
 * LOG: remove printfs.
 * LOG:
 * LOG: Revision 2.40  2000/07/07 22:27:14  mmiers
 * LOG:
 * LOG:
 * LOG: Rework close logic for sockets.
 * LOG:
 * LOG: Revision 2.39  2000/07/05 22:25:36  rsonak
 * LOG:
 * LOG: route: read from global section, not ini name
 * LOG: kasock: add trace saying which down transport sent sltm
 * LOG: iptrans: add debug
 * LOG:
 * LOG: Revision 2.38  2000/07/05 17:53:00  mmiers
 * LOG:
 * LOG:
 * LOG: Avoid overflow attacks.
 * LOG:
 * LOG: Revision 2.37  2000/07/05 17:26:05  mmiers
 * LOG:
 * LOG:
 * LOG: ip_trans: avoid DoS
 * LOG: Makefile: add asncc_v2
 * LOG:
 * LOG: Revision 2.36  2000/06/26 23:07:08  rsonak
 * LOG:
 * LOG:
 * LOG: SetState on dynamics to perform the same actions as other sock types.
 * LOG:
 * LOG: Revision 2.35  2000/06/26 20:50:47  rsonak
 * LOG:
 * LOG:
 * LOG: Don't go true too soon for dynamic.
 * LOG:
 * LOG: Revision 2.34  2000/06/23 19:09:01  rsonak
 * LOG:
 * LOG:
 * LOG: Mucho debugging of shutdown with sockets.
 * LOG:
 * LOG: Revision 2.33  2000/06/22 23:15:30  rsonak
 * LOG: Get the logic right.  Only iterative type is default type.
 * LOG:
 * LOG: Revision 2.32  2000/06/22 23:10:45  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 2.31  2000/06/22 15:30:45  mmiers
 * LOG:
 * LOG:
 * LOG: Fix close twice bug.
 * LOG:
 * LOG: Revision 2.30  2000/06/13 17:03:14  mmiers
 * LOG:
 * LOG: Reconnect and reaccept in clientOpen and serverOpen
 * LOG:
 * LOG: Revision 2.29  2000/06/13 15:52:23  rsonak
 * LOG: Forgot the classpart init.
 * LOG:
 * LOG: Revision 2.28  2000/06/12 23:39:57  rsonak
 * LOG:
 * LOG: Integration bug hunting.
 * LOG:
 * LOG: Revision 2.27  2000/06/12 22:07:45  mmiers
 * LOG:
 * LOG:
 * LOG: Checkpoint.
 * LOG:
 * LOG: Revision 2.26  2000/06/02 17:19:11  mmiers
 * LOG:
 * LOG:
 * LOG: Socket changes.
 * LOG:
 * LOG: Revision 2.25  2000/05/26 21:34:19  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes, more SCTP work.
 * LOG:
 * LOG: Revision 2.24  2000/05/22 23:54:15  mmiers
 * LOG:
 * LOG:
 * LOG: Hardcode endpoints to UDP for now.
 * LOG:
 * LOG: Revision 2.23  2000/05/15 22:34:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.22  2000/05/11 22:48:16  mmiers
 * LOG:
 * LOG:
 * LOG: Update link state when heartbeat detects failure.
 * LOG:
 * LOG: Revision 2.21  2000/05/11 02:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.20  2000/05/10 23:39:50  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 * LOG: Revision 2.19  2000/03/02 16:24:15  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 2.18  2000/02/15 20:34:47  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.17  2000/02/14 19:17:42  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.16  2000/02/10 14:48:11  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 2.15  2000/02/10 02:18:09  mmiers
 * LOG: Fix some nasty bugs that didn't show up on NT.
 * LOG:
 * LOG: Revision 2.14  2000/02/10 00:44:36  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP connections at IDLE now work.  More tomorrow.
 * LOG:
 * LOG: Revision 2.13  2000/02/09 18:51:39  mmiers
 * LOG:
 * LOG:
 * LOG: Debug of EndPoint sockets done.  On to RUDP debug.
 * LOG:
 * LOG: Revision 2.12  2000/02/08 21:43:32  mmiers
 * LOG:
 * LOG:
 * LOG: Visual debugging.
 * LOG:
 * LOG: Revision 2.11  2000/02/08 18:24:27  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up RUDP.  Now to test this mess.
 * LOG:
 * LOG: Revision 2.10  2000/02/02 02:29:23  mmiers
 * LOG:
 * LOG:
 * LOG: Add a find method (mostly for RUDP).
 * LOG:
 * LOG: Revision 2.9  2000/02/01 21:29:24  mmiers
 * LOG:
 * LOG:
 * LOG: Some updates for specific features.
 * LOG:
 * LOG: Revision 2.8  2000/01/26 18:19:16  mmiers
 * LOG:
 * LOG:
 * LOG: Fix Nick's link errors.
 * LOG:
 * LOG: Revision 2.7  2000/01/25 23:47:23  mmiers
 * LOG:
 * LOG:
 * LOG: More work on RUDP.  This is finally taking shape.
 * LOG:
 * LOG: Revision 2.6  2000/01/25 03:05:30  mmiers
 * LOG:
 * LOG:
 * LOG: Let the user add virtual transports.
 * LOG:
 * LOG: Revision 2.5  2000/01/25 02:36:16  mmiers
 * LOG:
 * LOG:
 * LOG: UNIX update.
 * LOG:
 * LOG: Revision 2.4  2000/01/24 22:19:22  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 2.3  2000/01/05 00:24:59  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks for RUDP.
 * LOG:
 * LOG: Revision 2.2  1999/12/22 02:09:02  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:53:03  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.50  1999/11/10 18:27:18  mmiers
 * LOG:
 * LOG:
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.49  1999/11/10 00:09:40  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.48  1999/10/29 20:46:09  mmiers
 * LOG:
 * LOG:
 * LOG: Initial GDI implementation.  Needs work still.
 * LOG:
 * LOG: Revision 1.47  1999/10/25 23:38:50  mmiers
 * LOG:
 * LOG:
 * LOG: Documentation code for the programming impaired.
 * LOG:
 * LOG: Revision 1.46  1999/10/25 18:28:13  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.45  1999/10/14 15:38:36  mmiers
 * LOG:
 * LOG:
 * LOG: Remove memory leaks from socket creation.  Publish
 * LOG: ReConnect/ReAccept APIs.
 * LOG:
 * LOG: Revision 1.44  1999/10/13 20:32:44  labuser
 * LOG:
 * LOG:
 * LOG: More cleanup of teardown code.
 * LOG:
 * LOG: Revision 1.43  1999/10/13 19:55:02  labuser
 * LOG:
 * LOG:
 * LOG: Remove memory leak.
 * LOG:
 * LOG: Revision 1.42  1999/10/12 22:59:57  mmiers
 * LOG:
 * LOG:
 * LOG: Rework termination handling of dynamic sockets.  The transport
 * LOG: control needs to go away when the thread does.
 * LOG:
 * LOG: Revision 1.41  1999/10/07 22:27:59  labuser
 * LOG:
 * LOG:
 * LOG: Find the termination problem with Brite applications.  Due to
 * LOG: not so great signal handling and resource leak.
 * LOG:
 * LOG: Revision 1.40  1999/10/05 19:27:23  mmiers
 * LOG:
 * LOG:
 * LOG: Remove destruction of rendezvous socket if accept fails.
 * LOG:
 * LOG: Revision 1.39  1999/09/10 21:19:18  rsonak
 * LOG:
 * LOG: Changed the condition in while loop. Now if the retryCount is not set,
 * LOG: default is used. If the retryCount is a negative number, it is INFINITE.
 * LOG:
 * LOG: Revision 1.38  1999/09/09 23:00:38  mmiers
 * LOG:
 * LOG:
 * LOG: Add retry count and retry delay as configuration items.
 * LOG:
 * LOG: Revision 1.37  1999/08/12 03:06:55  mmiers
 * LOG:
 * LOG:
 * LOG: Free the accept socket if accept() fails.
 * LOG:
 * LOG: Revision 1.36  1999/07/29 19:37:48  rsonak
 * LOG:
 * LOG:
 * LOG: Remote SOCK_Close() call in Dyname Get/Peek.  Duplicated by the
 * LOG: transport delete code.
 * LOG:
 * LOG: Revision 1.35  1999/07/23 19:45:40  mmiers
 * LOG:
 * LOG:
 * LOG: Remove memory leak in accept.
 * LOG:
 * LOG: Revision 1.34  1999/07/22 18:23:00  mmiers
 * LOG:
 * LOG:
 * LOG: Duplicate the socket handles for the iterative server.
 * LOG:
 * LOG: Revision 1.33  1999/07/22 15:56:59  hdivoux
 * LOG: Added two returns in SOCKTRAN_IterativeAccept.
 * LOG:
 * LOG: Revision 1.32  1999/07/21 21:48:38  hdivoux
 * LOG: Fixed small issue (access violation) at the end of SOCKTRAN_IterativeAccept.
 * LOG:
 * LOG: Revision 1.31  1999/07/12 20:40:02  hdivoux
 * LOG: Removed extra ntohs/htons (cause of stack corruption) and reversed
 * LOG: condition for use of ReturnErrorFunction.
 * LOG:
 * LOG: Revision 1.30  1999/07/12 19:07:44  mmiers
 * LOG:
 * LOG:
 * LOG: Fix new socket code to operate correctly.
 * LOG:
 * LOG: Revision 1.29  1999/07/07 14:26:29  mmiers
 * LOG:
 * LOG:
 * LOG: Fix the bug Rajesh pointed out (ip_trans), try to get the custom
 * LOG: build step to work with nmake (GSMMAP).
 * LOG:
 * LOG: Revision 1.28  1999/06/29 01:28:53  mmiers
 * LOG:
 * LOG:
 * LOG: Portability changes.
 * LOG:
 * LOG: Revision 1.27  1999/06/25 18:39:59  mmiers
 * LOG:
 * LOG:
 * LOG: Update the socket interface to write only the number of bytes it
 * LOG: needs.  Need to do the same with UNIX FIFOs.
 * LOG:
 * LOG: Revision 1.26  1999/06/25 16:06:44  mmiers
 * LOG:
 * LOG:
 * LOG: Rework the berkeley sockets transport classes a little.  Required
 * LOG: modification to the Accept() method to create a transport correctly.
 * LOG:
 * LOG: Revision 1.25  1999/06/23 21:21:19  rsonak
 * LOG:
 * LOG:
 * LOG: Rework the iterative/dynamic socket server (more tightly coupled
 * LOG: with infrastructure).
 * LOG:
 * LOG: Revision 1.24  1999/06/23 20:21:36  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a couple of bugs with dynamic sockets, update TODO list.
 * LOG:
 * LOG: Revision 1.23  1999/06/23 16:21:10  rsonak
 * LOG:
 * LOG: Event handlers for Iterative and Dynamic transports
 * LOG:
 * LOG: Revision 1.22  1999/06/15 16:15:16  rsonak
 * LOG:
 * LOG: DynamicServerTransport modified
 * LOG:
 * LOG: Revision 1.21  1999/06/14 20:55:24  rsonak
 * LOG:
 * LOG: Added Iterative server and Dynamic server transports
 * LOG:
 * LOG: Revision 1.20  1999/03/12 00:06:12  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.19  1999/03/05 22:01:07  mmiers
 * LOG:
 * LOG:
 * LOG: Rework the connect logic for server sockets.
 * LOG:
 * LOG: Revision 1.17.2.2  1999/03/05 21:29:23  mmiers
 * LOG:
 * LOG:
 * LOG: Complete the multithreaded demo for AIN.  Fix connect logic for server
 * LOG: sockets.
 * LOG:
 * LOG: Revision 1.17.2.1  1999/02/25 22:21:08  mmiers
 * LOG:
 * LOG:
 * LOG: Build C files using C++.
 * LOG:
 * LOG: Revision 1.17  1998/12/08 20:40:40  rsonak
 * LOG: Modifications for HNS stabilization.
 * LOG:
 * LOG: Revision 1.16  1998/11/13 16:12:41  mmiers
 * LOG: Add inclusion of netinet/in.h for htons/ntohs
 * LOG:
 * LOG: Revision 1.15  1998/11/13 16:07:15  mmiers
 * LOG: Make this network aware.
 * LOG:
 * LOG: Revision 1.14  1998/11/12 03:10:53  mmiers
 * LOG: Modify IP transports to correctly perform state transitions.
 * LOG:
 * LOG: Revision 1.13  1998/11/12 01:41:54  mmiers
 * LOG: Trying to straighten out SSP/SSA.
 * LOG:
 * LOG: Revision 1.12  1998/11/12 00:09:14  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.11  1998/11/05 21:20:27  mmiers
 * LOG: Small tweaks for DEC compile.
 * LOG:
 * LOG: Revision 1.10  1998/11/05 16:52:15  mmiers
 * LOG: Add in transport pause/resume.
 * LOG: Add connect to sockets.
 * LOG:
 * LOG: Revision 1.9  1998/09/30 20:41:47  jrao
 * LOG: Remove printfs
 * LOG:
 * LOG: Revision 1.8  1998/09/30 20:33:25  jrao
 * LOG: Fix a number of release bugs with pthread_cond_t(s).
 * LOG:
 * LOG: Revision 1.7  1998/09/22 17:28:29  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.6  1998/07/21 20:29:24  ahanda
 * LOG: Added Accept and connect to the server/client creation
 * LOG:
 * LOG: Revision 1.5  1998/07/21 18:38:55  mmiers
 * LOG: Don't forget to delete mutexes on destroy.
 * LOG:
 * LOG: Revision 1.4  1998/07/21 18:37:14  mmiers
 * LOG: Add mutex initialization to ip transports.
 * LOG:
 * LOG: Remove vestigial connection variable from tq transports.
 * LOG:
 * LOG: Add localPC, localSSN processing to the transport base class.
 * LOG:
 * LOG: Revision 1.3  1998/06/26 14:29:58  mmiers
 * LOG: Convert C++ transports to use C versions.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 03:10:09  mmiers
 * LOG: Build on Solaris.  Right now, the NT build is not OK.
 * LOG:
 * LOG: Revision 1.1  1998/06/18 02:37:24  mmiers
 * LOG: More work on the C side for back compat.
 * LOG:
 * LOG: Revision 1.11  1998/06/18 00:25:00  mmiers
 * LOG: Documentation update, C versions of some transports, C version of
 * LOG: resource file manager.
 * LOG:
 * LOG: Revision 1.10  1998/06/16 00:00:26  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.9  1998/05/31 02:59:51  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.8  1998/05/29 22:35:39  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.7  1998/05/29 15:08:59  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.6  1998/05/22 23:18:15  mmiers
 * LOG: #include <stdlib.h> for atoi definition on solaris.
 * LOG:
 * LOG: Revision 1.5  1998/05/20 17:06:08  mmiers
 * LOG: Get the namespace thing right.  You must include its++.h if
 * LOG: you want to use the its namespace.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 17:11:54  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.3  1998/05/14 01:49:25  mmiers
 * LOG: Implement the transport functions.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:38  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:06  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#if defined(unix)
#include <netinet/in.h>
#endif

#include <its.h>
#include <its_route.h>
#include <its_ip_trans.h>
#include <its_trace.h>
#include <its_timers.h>
#include <its_gdi_trans.h>
#include <its_imal_trans.h>
#include <its_tali_trans.h>
#include <its_sctp_trans.h>
#include <its_assertion.h>
#include <its_timers.h>
#include <its_hmi.h>

#ident "$Id: its_ip_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

#if defined(unix)
#include <netinet/in.h>
#endif


static char* sync_data = "ISS7SSI";
static int   sd_len = 7;

/*
 * Rules for servers:
 *
 * Static servers open() into SOURCE (which creates source).
 * They copy SOURCE into CONNECT (pointer wise) and accept()
 * from CONNECT into SOURCE.  When they close(), they
 * SOCK_Close SOURCE and CONNECT.  When they ReAccept(),
 * they accept from CONNECT into SOURCE.
 * Iterative servers open() into SOURCE (which creates source).
 * When they IterativeAccept(), they accept()
 * into CONNECT (which creates CONNECT).
 * Dynamics don't allocate.  They steal iterative's CONNECT
 * into SOURCE.
 */

/*
 * these next two functions essentially represents our protocol for
 * socket communication.  Note the magic number stuff.
 */
static int
ReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    unsigned i, dosCount;
    ITS_USHORT tmp;
    char b;
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    ITS_BOOLEAN firstTime = ITS_TRUE;

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    if (TRANSPORT_EXIT_NOW(ft))
    {
        return (ITS_ERCVFAIL);
    }

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = SOCKTRAN_SOURCE(ft);

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * USEC_PER_MILLISEC);

            if (TRANSPORT_EXIT_NOW(ft))
            {
                return (ITS_ERCVFAIL);
            }

            if (ret < ITS_SUCCESS)
            {
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                TRANSPORT_LAST_UPDATE(ft) = TIMERS_Time();

                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(SOCKTRAN_SOURCE(ft), &b, sizeof(char));

        if (ret != sizeof(char))
        {
            return (ITS_ERCVFAIL);
        }

        if (b != sync_data[i])
        {
            i = ~0U;

            continue;
        }
    }

    /* read the source */
    ret = SOCK_Read(SOCKTRAN_SOURCE(ft), (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ERCVFAIL);
    }

    ev->src = SOCK_NToHS(tmp);

    /* read the length */
    ret = SOCK_Read(SOCKTRAN_SOURCE(ft), (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ERCVFAIL);
    }

    ev->len = SOCK_NToHS(tmp);

    ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);

    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (ev->len)
    {
        ret = SOCK_Read(SOCKTRAN_SOURCE(ft), (char *)ev->data, ev->len);

        if (ret != ev->len)
        {
            ITS_Free(ev->data);
            ev->data = NULL;

            return (ITS_ERCVFAIL);
        }
    }

    TRANSPORT_LAST_UPDATE(ft) = TIMERS_Time();
    TRANSPORT_NUM_RECV(ft)++;

    return (ITS_SUCCESS);
}

static int
WriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    ITS_USHORT tmp;
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    /* synchronize the stream */
    ret = SOCK_Write(SOCKTRAN_SOURCE(ft), sync_data, sd_len);

    if (ret != sd_len)
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the source */
    tmp = SOCK_HToNS(ev->src);

    ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the length */
    tmp = SOCK_HToNS(ev->len);

    ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the data */
    if (ev->len)
    {
        ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char *)ev->data, ev->len);

        if (ret != (int)ev->len)
        {
            return (ITS_ESENDFAIL);
        }
    }

    TRANSPORT_NUM_SENT(ft)++;

    return (ITS_SUCCESS);
}

static SOCKTRAN_ClassExtRec BasicReadWrite =
{
    /* core class */
    {
        ITS_EXT_VERSION
    },
    /* socket class */
    {
        ReadEvent,  /* Read one */
        WriteEvent  /* Write one */
    }
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method does the necessary part of shutting down a bad socket.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Shutdown(SOCKTRAN_Manager *ft)
{
    if (MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("Shutdown: mutex corrupted\n"));
        abort();
    }

    if (!SOCKTRAN_IS_VALID(ft))
    {
        MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));

        return;
    }

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    TRANSPORT_IS_ACTIVE(ft) = ITS_FALSE;
    SOCKTRAN_IS_VALID(ft) = ITS_FALSE;

    TRANSPORT_SetState(TRANSPORT(ft), ITS_FALSE);

    if (ITS_IsInstanceOf((ITS_Class)itsSOCKTRAN_ServerClass,
                         (ITS_Object)ft) ||
        ITS_IsInstanceOf((ITS_Class)itsSOCKTRAN_DynamicServerClass,
                         (ITS_Object)ft))
    {
        SOCKTRAN_SOURCE(ft)->addr = NULL;
    }

    SOCK_Close(SOCKTRAN_SOURCE(ft));

#if defined(linux)
    /*
     * This is hideous, not necessary on NT or Solaris, but I can't
     * convince Linus of that.
     */
    {
        WORKER_Control *work = WORKER_FindWorker(TRANSPORT_INSTANCE(ft));

        if (work != NULL)
        {
            pthread_t thr = work->thread.thread;

            pthread_kill(thr, SIGUSR1);
        }
    }
#endif

    SOCKTRAN_SOURCE(ft) = NULL;

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method does the necessary part of restarting a bad socket.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Restart(SOCKTRAN_Manager *ft)
{
    if (SOCKTRAN_IS_VALID(ft))
    {
        return;
    }

    TRANSPORT_IS_ACTIVE(ft) = ITS_TRUE;
    SOCKTRAN_IS_VALID(ft) = ITS_TRUE;

    if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    TRANSPORT_SetState(TRANSPORT(ft), ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based transport.  Note that this
 *      routine will block until the server side is available.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the socket
 *
 *  See Also:
 ****************************************************************************/
static int
ClientCreate(ITS_Object h, va_list args)
{
    char buf[ITS_PATH_MAX];
    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    ITS_TRACE_DEBUG(("CreateClient:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    /* Get the socket domain */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SOCKET_DOMAIN_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClientCreate: INI is missing "
                         "SOCKET_DOMAIN\n"));

        return (ITS_ENOTRANSPORT);
    }
    else if (strcmp(buf, DOMAIN_INET_STRING) == 0)
    {
        SOCKTRAN_DOMAIN(ret) = INET_DOMAIN;
    }
    else if (strcmp(buf, DOMAIN_UNIX_STRING) == 0)
    {
        SOCKTRAN_DOMAIN(ret) = UNIX_DOMAIN;
    }
    else
    {
        ITS_TRACE_ERROR(("ClientCreate: INI file has bad "
                         "SOCKET_DOMAIN\n"));

        return (ITS_ENOTRANSPORT);
    }

    /* get the server host name */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SERVER_PATH_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClientCreate: INI file is missing "
                         "SERVER_PATH\n"));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_HOST_PATH(ret) = strdup(buf);
    }

    /* get the server port number */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SERVER_PORT_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClientCreate: INI file is missing "
                         "SERVER_PORT\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_PORT(ret) = atoi(buf);
    }

    /* get the retry count */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              RETRY_COUNT_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        SOCKTRAN_RETRY_COUNT(ret) = DEFAULT_RETRY_COUNT;
    }
    else
    {
        SOCKTRAN_RETRY_COUNT(ret) = atoi(buf);
    }

    /* get the retry count */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              RETRY_DELAY_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        SOCKTRAN_RETRY_DELAY(ret) = DEFAULT_RETRY_DELAY;
    }
    else
    {
        SOCKTRAN_RETRY_DELAY(ret) = atoi(buf);
    }

    /* create the guards */
    if (MUTEX_CreateMutex(&SOCKTRAN_RMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClientCreate: couldn't create "
                         "read mutex\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }

    if (MUTEX_CreateMutex(&SOCKTRAN_WMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClientCreate: couldn't create "
                         "write mutex\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }

    /* create the client socket */
    if (SOCK_ClientOpen(&SOCKTRAN_SOURCE(ret), SOCKTRAN_DOMAIN(ret),
                        SOCKTRAN_HOST_PATH(ret), SOCKTRAN_PORT(ret)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClientCreate: failed to open "
                         "client socket\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));
        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }

    SOCKTRAN_READ_EVENT(h) =
		SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(h));
    SOCKTRAN_WRITE_EVENT(h) =
		SOCKTRAN_CLASS_EXT_WRITE_EVENT(ITS_OBJ_CLASS(h));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys a socket transport.
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
static void
ClientDestroy(ITS_Object h)
{
    SOCKTRAN_Manager* ret = (SOCKTRAN_Manager *)h;

    ITS_TRACE_DEBUG(("ClientDestroy:\n"));

    SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ret))(ret);

    free(SOCKTRAN_HOST_PATH(ret));

    MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));
    MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads from the server end of the socket connection to
 *      retrieve an event.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClientGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_CGetNextEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_READ_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CGetNextEvent: attempt to get on "
                         "down socket\n"));

        return (ITS_EBADSOCKET);
    }

retry:
    if (MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CGetNextEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = SOCKTRAN_READ_EVENT(h)(ft, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CGetNextEvent: EOF on socket read\n"));

        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_EBADSOCKET);
        }

        if (SOCKTRAN_ClientReConnect(ft) == ITS_SUCCESS)
        {
            ITS_TRACE_DEBUG(("SOCKTRAN_CGetNextEvent: Client reconnected.\n"));

            goto retry;
        }
        else
        {
            return (ITS_EBADSOCKET);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method peeks at the server end of the socket connection to see
 *      if data is present.  If data is present, it attempts to read the
 *      data into an event.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      If no data is available, ITS_ENOMSG is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClientPeekNextEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_CPeekNextEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_READ_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CPeekNextEvent: attempt to peek on "
                         "down socket\n"));

        return (ITS_EBADSOCKET);
    }

retry:
    if (MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CPeekNextEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (!SOCK_Pending(SOCKTRAN_SOURCE(ft)))
    {
        ITS_TRACE_DEBUG(("SOCKTRAN_CPeekNextEvent: no pending data\n"));

        MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));
        
        return (ITS_ENOMSG);
    }

    ret = SOCKTRAN_READ_EVENT(h)(ft, event);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CGetNextEvent: EOF on socket read\n"));

        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_EBADSOCKET);
        }

        if (SOCKTRAN_ClientReConnect(ft) == ITS_SUCCESS)
        {
            goto retry;
        }
        else
        {
            return (ITS_EBADSOCKET);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based transport.  Note that this
 *      routine will block until the client side connects.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the socket
 *
 *  See Also:
 *      SOCKTRAN_DeleteServerTransport
 ****************************************************************************/
static int
ServerCreate(ITS_Object h, va_list args)
{
    char buf[ITS_PATH_MAX];
    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    ITS_TRACE_DEBUG(("ServerCreate:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    /* Get the socket domain */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SOCKET_DOMAIN_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ServerCreate: INI file is missing "
                         "SOCKET_DOMAIN\n"));

        return (ITS_ENOTRANSPORT);
    }
    else if (strcmp(buf, DOMAIN_INET_STRING) == 0)
    {
        SOCKTRAN_DOMAIN(ret) = INET_DOMAIN;
    }
    else if (strcmp(buf, DOMAIN_UNIX_STRING) == 0)
    {
        SOCKTRAN_DOMAIN(ret) = UNIX_DOMAIN;
    }
    else
    {
        ITS_TRACE_ERROR(("ServerCreate: INI file has bad "
                         "SOCKET_DOMAIN\n"));

        return (ITS_ENOTRANSPORT);
    }

    /* get the server host name */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SERVER_PATH_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ServerCreate: INI file is missing "
                         "SERVER_PATH\n"));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_HOST_PATH(ret) = strdup(buf);
    }

    /* get the server port number */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SERVER_PORT_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ServerCreate: INI file is missing "
                         "SERVER_PORT\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_PORT(ret) = atoi(buf);
    }

    /* get the retry count */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              RETRY_COUNT_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        SOCKTRAN_RETRY_COUNT(ret) = DEFAULT_RETRY_COUNT;
    }
    else
    {
        SOCKTRAN_RETRY_COUNT(ret) = atoi(buf);
    }

    /* get the retry count */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              RETRY_DELAY_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        SOCKTRAN_RETRY_DELAY(ret) = DEFAULT_RETRY_DELAY;
    }
    else
    {
        SOCKTRAN_RETRY_DELAY(ret) = atoi(buf);
    }

    /* create the guards */
    if (MUTEX_CreateMutex(&SOCKTRAN_RMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ServerCreate: couldn't create "
                         "read mutex\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }

    if (MUTEX_CreateMutex(&SOCKTRAN_WMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ServerCreate: couldn't create "
                         "write mutex\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }

    /* create the Server socket */
    if (SOCK_ServerOpen(&SOCKTRAN_SOURCE(ret), SOCKTRAN_DOMAIN(ret),
                        SOCKTRAN_HOST_PATH(ret), SOCKTRAN_PORT(ret)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ServerCreate: couldn't open "
                         "server socket\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));
        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        return (ITS_ENOTRANSPORT);
    }

    SOCKTRAN_READ_EVENT(h) =
                       SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(h));
    SOCKTRAN_WRITE_EVENT(h) =
                       SOCKTRAN_CLASS_EXT_WRITE_EVENT(ITS_OBJ_CLASS(h));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destroys a socket transport.
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
 *      SOCKTRAN_CreateServerTransport()
 ****************************************************************************/
void
ServerDestroy(ITS_Object h)
{
    SOCKTRAN_Manager* ret = (SOCKTRAN_Manager *)h;

    ITS_TRACE_DEBUG(("ServerDelete:\n"));

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret))(ret);
    }

    if (SOCKTRAN_CONNECT(ret))
    {
        SOCK_Close(SOCKTRAN_CONNECT(ret));

        SOCKTRAN_CONNECT(ret) = NULL;
    }

    if (SOCKTRAN_IS_VALID(ret) && SOCKTRAN_SOURCE(ret))
    {
        SOCK_Close(SOCKTRAN_SOURCE(ret));
    }
    SOCKTRAN_SOURCE(ret) = NULL;

    /* can't use Shutdown - bad karma due to iterative */
    SOCKTRAN_IS_VALID(ret) = ITS_FALSE;

    MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));
    MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads from the server end of the socket connection to
 *      retrieve an event.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ServerGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_SGetNextEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_READ_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_SGetNextEvent: attempt to get on "
                         "down socket\n"));

        return (ITS_EBADSOCKET);
    }

retry:
    if (MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_SGetNextEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = SOCKTRAN_READ_EVENT(h)(ft, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_SGetNextEvent: EOF on socket read\n"));

        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_EBADSOCKET);
        }

        if (SOCKTRAN_ServerReAccept(ft) == ITS_SUCCESS)
        {
            goto retry;
        }
        else
        {
            return (ITS_EBADSOCKET);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method peeks at the server end of the socket connection to see
 *      if data is present.  If data is present, it attempts to read the
 *      data into an event.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      If no data is available, ITS_ENOMSG is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ServerPeekNextEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_SPeekNextEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_READ_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_SPeekNextEvent: attempt to peek on "
                         "down socket\n"));

        return (ITS_EBADSOCKET);
    }

retry:
    if (MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_SPeekNextEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (!SOCK_Pending(SOCKTRAN_SOURCE(ft)))
    {
        ITS_TRACE_DEBUG(("SOCKTRAN_SPeekNextEvent: no pending data\n"));

        MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));
        
        return (ITS_ENOMSG);
    }

    ret = SOCKTRAN_READ_EVENT(h)(ft, event);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_SGetNextEvent: EOF on socket read\n"));

        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_EBADSOCKET);
        }

        if (SOCKTRAN_ServerReAccept(ft) == ITS_SUCCESS)
        {
            goto retry;
        }
        else
        {
            return (ITS_EBADSOCKET);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based transport.  Note that this
 *      routine will block until the client side connects.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the socket
 *
 *  See Also:
 *      SOCKTRAN_DeleteServerTransport
 ****************************************************************************/
int
DynamicCreate(ITS_Object h, va_list args)
{
    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    ITS_TRACE_DEBUG(("DynamicCreate:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    /* create the guards */
    if (MUTEX_CreateMutex(&SOCKTRAN_RMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CreateDynamicServerTransport: couldn't "
                         "create read mutex\n"));

        free(SOCKTRAN_SOURCE(ret));

        return (ITS_ENOTRANSPORT);
    }

    if (MUTEX_CreateMutex(&SOCKTRAN_WMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_CreateDynamicServerTransport: couldn't "
                         "create write mutex\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_SOURCE(ret));

        return (ITS_ENOTRANSPORT);
    }

    SOCKTRAN_READ_EVENT(h) =
		SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(h));
    SOCKTRAN_WRITE_EVENT(h) =
		SOCKTRAN_CLASS_EXT_WRITE_EVENT(ITS_OBJ_CLASS(h));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads from the server end of the socket connection to
 *      retrieve an event.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
DynamicGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_DGetNextEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_READ_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_DGetNextEvent: attempt to get on "
                         "down socket\n"));

        return (ITS_EBADSOCKET);
    }

    if (MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_DGetNextEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = SOCKTRAN_READ_EVENT(h)(ft, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_DGetNextEvent: EOF on socket read\n"));

        /* shutdown */
        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        return (ret);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method peeks at the server end of the socket connection to see
 *      if data is present.  If data is present, it attempts to read the
 *      data into an event.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      If no data is available, ITS_ENOMSG is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
DynamicPeekNextEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_DPeekNextEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_READ_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_DPeekNextEvent: attempt to peek on "
                         "down socket\n"));

        return (ITS_EBADSOCKET);
    }

    if (MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_DPeekNextEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (!SOCK_Pending(SOCKTRAN_SOURCE(ft)))
    {
        ITS_TRACE_DEBUG(("SOCKTRAN_DPeekNextEvent: no pending data\n"));

        MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));
        
        return (ITS_ENOMSG);
    }

    ret = SOCKTRAN_READ_EVENT(h)(ft, event);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_DPeekNextEvent: EOF on socket read\n"));

        /* shutdown */
        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        return (ret);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method *writes* to the fifo transport.  For fifos, this implies
 *      writing the event to the client side of the fifo transport (i.e.,
 *      the fifo the *other* end will read from).
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;
    int ret;

    ITS_TRACE_DEBUG(("SOCKTRAN_PutEvent:\n"));

    ITS_C_REQUIRE(SOCKTRAN_WRITE_EVENT(h) != NULL);

    if (!SOCKTRAN_IS_VALID(ft))
    {
        ITS_TRACE_ERROR(("SOCKTRAN_PutEvent: attempt to put on "
                         "down socket\n"));
	 SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ft))(ft);

        return (ITS_ENOMEM);
    }

    if (MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_PutEvent: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = SOCKTRAN_WRITE_EVENT(h)(ft, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));

    if (ret == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_ERROR(("SOCKTRAN_PutEvent: partial write on event\n"));

        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(ft))(ft);

        return (ITS_ENOMEM);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return an error. Used for mapping GetNextEvent, 
 *      PeeknextEvent and PutEvent in the Iterative Server.
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ReturnErrorFunction(ITS_HANDLE h, ITS_EVENT* event)
{
    return !ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method initializes the inheritance class part members.
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
 *      ITS_SUCCESS - initialization successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassPartInit(ITS_Class subClass)
{
    if (SOCKTRAN_CLASS_SHUTDOWN(subClass) == SOCKTRAN_CLASS_SHUTDOWN_INHERIT)
    {
        SOCKTRAN_CLASS_SHUTDOWN(subClass) =
            SOCKTRAN_CLASS_SHUTDOWN(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (SOCKTRAN_CLASS_RESTART(subClass) == SOCKTRAN_CLASS_RESTART_INHERIT)
    {
        SOCKTRAN_CLASS_RESTART(subClass) =
            SOCKTRAN_CLASS_RESTART(ITS_CLASS_SUPERCLASS(subClass));
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function destroys the transport part of a subclass
 *
 *  Input Parameters:
 *      objClass - the class whose part needs destruction.
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
ClassPartDestroy(ITS_Class subClass)
{
}

/*
 * the client class record
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_ClientClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* the root object */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SOCKTRAN_CLIENT_CLASS_NAME,             /* class name */
        ITS_AddFeature,                         /* class initialize */
        ITS_RemFeature,                         /* class destroy */
        ClassPartInit,                          /* class part init */
        ClassPartDestroy,                       /* class part destroy */
        ClientCreate,                           /* instantiate */
        ClientDestroy,                          /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&BasicReadWrite           /* extension */
    },
    /* transport */
    {
        ClientGetNextEvent,                     /* get next */
        ClientPeekNextEvent,                    /* peek next */
        PutEvent,                               /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSOCKTRAN_ClientClass =
    (TRANSPORT_Class)&itsSOCKTRAN_ClientClassRec;

/*
 * the server class record
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_ServerClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* the root object */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SOCKTRAN_SERVER_CLASS_NAME,             /* class name */
        ITS_AddFeature,                         /* class initialize */
        ITS_RemFeature,                         /* class destroy */
        ClassPartInit,                          /* class part init */
        ClassPartDestroy,                       /* class part destroy */
        ServerCreate,                           /* instantiate */
        ServerDestroy,                          /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&BasicReadWrite           /* extension */
    },
    /* transport */
    {
        ServerGetNextEvent,                     /* get next */
        ServerPeekNextEvent,                    /* peek next */
        PutEvent,                               /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSOCKTRAN_ServerClass =
    (TRANSPORT_Class)&itsSOCKTRAN_ServerClassRec;

/*
 * the iterative server class record
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_IterativeServerClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* the root object */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SOCKTRAN_ITERATIVE_CLASS_NAME,          /* class name */
        ITS_AddFeature,                         /* class initialize */
        ITS_RemFeature,                         /* class destroy */
        ClassPartInit,                          /* class part init */
        ClassPartDestroy,                       /* class part destroy */
        ServerCreate,                           /* instantiate */
        ServerDestroy,                          /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&BasicReadWrite           /* extension */
    },
    /* transport */
    {
        ReturnErrorFunction,                    /* get next */
        ReturnErrorFunction,                    /* peek next */
        ReturnErrorFunction,                    /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSOCKTRAN_IterativeServerClass =
    (TRANSPORT_Class)&itsSOCKTRAN_IterativeServerClassRec;

/*
 * the dynamic server class record
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_DynamicServerClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* the root object */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SOCKTRAN_DYNAMIC_CLASS_NAME,            /* class name */
        ITS_AddFeature,                         /* class initialize */
        ITS_RemFeature,                         /* class destroy */
        ClassPartInit,                          /* class part init */
        ClassPartDestroy,                       /* class part destroy */
        DynamicCreate,                          /* instantiate */
        ServerDestroy,                          /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&BasicReadWrite           /* extension */
    },
    /* transport */
    {
        DynamicGetNextEvent,                    /* get next */
        DynamicPeekNextEvent,                   /* peek next */
        PutEvent,                               /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,          /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSOCKTRAN_DynamicServerClass =
    (TRANSPORT_Class)&itsSOCKTRAN_DynamicServerClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based transport.  Note that this
 *      routine will block until the server side is available.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the socket
 *
 *  See Also:
 *      SOCKTRAN_DeleteClientTransport
 ****************************************************************************/
ITSDLLAPI SOCKTRAN_Manager*
SOCKTRAN_CreateClientTransport(const char *name,
                               ITS_USHORT instance,
                               ITS_UINT mask)
{
    SOCKTRAN_Manager *ret = NULL;

    ITS_TRACE_DEBUG(("SOCKTRAN_CreateClientTransport:\n"));

    /* current IMAL */
    if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
        ITS_TRANSPORT_DATA_SOCKET)
    {
        ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsSOCKTRAN_ClientClass,
                                                   name, instance, mask);
    }
    /* GDI */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_GDI_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_ClientClass_ANSI,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_ClientClass_CCITT,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_ClientClass_PRC,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_ClientClass_TTC,
                                                       name, instance, mask);
        }
    }
    /* TALI */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_TALI_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_ClientClass_ANSI,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_ClientClass_CCITT,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_ClientClass_PRC,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_ClientClass_TTC,
                                                       name, instance, mask);
        }
    }
    /* IMAL with heartbeats */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_IMAL_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_ClientClass_ANSI,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_ClientClass_CCITT,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_ClientClass_PRC,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_ClientClass_TTC,
                                                       name, instance, mask);
        }
    }
    /* default */
    else
    {
        ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsSOCKTRAN_ClientClass,
                                                   name, instance, mask);
    }

    if (ret == NULL)
    {
        return (ret);
    }

    /* connect to the server */
    if (SOCK_ClientConnect(SOCKTRAN_SOURCE(ret)) != ITS_SUCCESS)
    {
        if (SOCKTRAN_IS_VALID(ret))
        {
            SOCK_Close(SOCKTRAN_SOURCE(ret));
            SOCKTRAN_SOURCE(ret) = NULL;
        }

        if (SOCKTRAN_ClientReConnect(ret) != ITS_SUCCESS)
        {
            TRANSPORT_Delete((ITS_HANDLE)ret);
        
            return (NULL);
        }
    }
    else
    {
        SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ret))(ret);
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destroys a socket transport.
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
 *      SOCKTRAN_CreateClientTransport()
 ****************************************************************************/
ITSDLLAPI void
SOCKTRAN_DeleteClientTransport(SOCKTRAN_Manager* ret)
{
    ITS_TRACE_DEBUG(("SOCKTRAN_DeleteClientTransport:\n"));

    TRANSPORT_Delete((ITS_HANDLE)ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method attempts to reconnect a client transport.
 *
 *  Input Parameters:
 *      ft - the socket transport pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the socket reconnected.  Any other return code
 *      indicates failure.
 *
 *  Notes:
 *
 *  See Also:
 *      SOCKTRAN_CreateClientTransport()
 ****************************************************************************/
ITSDLLAPI int
SOCKTRAN_ClientReConnect(SOCKTRAN_Manager *ft)
{
    int i;

    if (SOCKTRAN_RETRY_COUNT(ft) == 0)
    {
        return (ITS_EBADSOCKET);
    }

    /* create the client socket */
    i = 0;
    while (SOCKTRAN_RETRY_COUNT(ft) < 0 || i < SOCKTRAN_RETRY_COUNT(ft))
    {
        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_EBADSOCKET);
        }

        if (SOCK_ClientOpen(&SOCKTRAN_SOURCE(ft),
                            SOCKTRAN_DOMAIN(ft),
                            SOCKTRAN_HOST_PATH(ft),
                            SOCKTRAN_PORT(ft)) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SOCKTRAN_ClientReConnect: failed to "
                             "open client socket\n"));

            i++;
            continue;
        }
        /* connect to the server */
        if (SOCK_ClientConnect(SOCKTRAN_SOURCE(ft)) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SOCKTRAN_CreateClientTransport: connect to "
                             "server failed\n"));

            SOCK_Close(SOCKTRAN_SOURCE(ft));
            SOCKTRAN_SOURCE(ft) = NULL;

            TIMERS_Sleep(SOCKTRAN_RETRY_DELAY(ft));

            i++;
            continue;
        }

        SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ft))(ft);

        return (ITS_SUCCESS);
    }

    return (ITS_EBADSOCKET);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based transport.  Note that this
 *      routine will block until the client side connects.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the socket
 *
 *  See Also:
 *      SOCKTRAN_DeleteServerTransport
 ****************************************************************************/
ITSDLLAPI SOCKTRAN_Manager*
SOCKTRAN_CreateServerTransport(const char *name,
                               ITS_USHORT instance,
                               ITS_UINT mask)
{
    SOCKTRAN_Manager *ret = NULL;

    ITS_TRACE_DEBUG(("SOCKTRAN_CreateServerTransport:\n"));

    if (ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SSOCKET_ITER)
    {
        ret = (SOCKTRAN_Manager *)
                TRANSPORT_Create(itsSOCKTRAN_IterativeServerClass,
                                 name, instance, mask);
    }
    else
    {
        /* current IMAL */
        if ((ITS_GET_TRANSPORT_FLAGS(mask) &
             ITS_TRANSPORT_SOCKP_MASK) == ITS_TRANSPORT_DATA_SOCKET)
        {
            ret = (SOCKTRAN_Manager *)
                    TRANSPORT_Create(itsSOCKTRAN_ServerClass,
                                     name, instance, mask);
        }
        /* GDI */
        else if ((ITS_GET_TRANSPORT_FLAGS(mask) &
                  ITS_TRANSPORT_SOCKP_MASK) == ITS_TRANSPORT_GDI_SOCKET)
        {
            if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsGDITRAN_ServerClass_ANSI,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsGDITRAN_ServerClass_CCITT,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsGDITRAN_ServerClass_PRC,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsGDITRAN_ServerClass_TTC,
                                         name, instance, mask);
            }
        }
        /* TALI */
        else if ((ITS_GET_TRANSPORT_FLAGS(mask) &
                  ITS_TRANSPORT_SOCKP_MASK) == ITS_TRANSPORT_TALI_SOCKET)
        {
            if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsTALITRAN_ServerClass_ANSI,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsTALITRAN_ServerClass_CCITT,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsTALITRAN_ServerClass_PRC,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsTALITRAN_ServerClass_TTC,
                                         name, instance, mask);
            }
        }
        /* IMAL with heartbeats */
        else if ((ITS_GET_TRANSPORT_FLAGS(mask) &
                  ITS_TRANSPORT_SOCKP_MASK) == ITS_TRANSPORT_IMAL_SOCKET)
        {
            if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsIMALTRAN_ServerClass_ANSI,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsIMALTRAN_ServerClass_CCITT,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsIMALTRAN_ServerClass_PRC,
                                         name, instance, mask);
            }
            else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
            {
                ret = (SOCKTRAN_Manager *)
                        TRANSPORT_Create(itsIMALTRAN_ServerClass_TTC,
                                         name, instance, mask);
            }
        }
        /* default */
        else
        {
            ret = (SOCKTRAN_Manager *)
                    TRANSPORT_Create(itsSOCKTRAN_ServerClass,
                                     name, instance, mask);
        }
    }
    
    if (ret == NULL)
    {
        return (ret);
    }

    if (!(ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SSOCKET_ITER))
    {
        ITS_SockPollInfo    fd;
        int rc;

        SOCKTRAN_CONNECT(ret) = SOCKTRAN_SOURCE(ret);
        SOCKTRAN_SOURCE(ret) = NULL;

        fd.sinfo = SOCKTRAN_CONNECT(ret);
        fd.lookFor = SOCK_POLL_READ | SOCK_POLL_READ_OOB;

        /* see if someone wants to connect */
        rc = SOCK_Poll(&fd, 1, HMI_GetTimeOutInterval() * USEC_PER_MILLISEC);

        /* Accept Connections */
        if (rc > 0 && fd.wasSet)
        {
            if (SOCK_ServerAccept(SOCKTRAN_CONNECT(ret),
                                  &SOCKTRAN_SOURCE(ret)) != ITS_SUCCESS)
            {
                if (SOCKTRAN_ServerReAccept(ret) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("SOCKTRAN_CreateServerTransport: accept of "
                                     "client failed\n"));

                    TRANSPORT_Delete((ITS_HANDLE)ret);

                    ret = NULL;
                }
            }
            else
            {
                SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ret))(ret);
            }
        }
        else if (!TRANSPORT_EXIT_NOW(ret))
        {
            if (SOCKTRAN_ServerReAccept(ret) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("SOCKTRAN_CreateServerTransport: accept of "
                                 "client failed\n"));

                TRANSPORT_Delete((ITS_HANDLE)ret);

                ret = NULL;
            }
        }
        else
        {
            TRANSPORT_Delete((ITS_HANDLE)ret);

            ret = NULL;
        }
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destroys a socket transport.
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
 *      SOCKTRAN_CreateServerTransport()
 ****************************************************************************/
ITSDLLAPI void
SOCKTRAN_DeleteServerTransport(SOCKTRAN_Manager* ret)
{
    ITS_TRACE_DEBUG(("SOCKTRAN_DeleteServerTransport:\n"));

    TRANSPORT_Delete((ITS_HANDLE)ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based transport from a new connection
 *      on a permanent (or rendezvous) port.
 *
 *  Input Parameters:
 *      sockMan - the existing transport control block for the permanent
 *                connection.
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
ITSDLLAPI SOCKTRAN_Manager *
SOCKTRAN_IterativeAccept(SOCKTRAN_Manager* sockMan,
                         const char *name,
                         ITS_USHORT instance,
                         ITS_UINT mask)
{
    SOCKTRAN_Manager *ret = NULL;

    ITS_TRACE_DEBUG(("SOCKTRAN_IterativeAccept:\n"));

    if (sockMan == NULL ||
        !(ITS_GET_TRANSPORT_FLAGS(TRANSPORT_MASK(sockMan)) &
          ITS_TRANSPORT_SSOCKET_ITER))
    {
        return NULL;
    }

    for (;;)
    {
        ITS_SockPollInfo fd;
        int rc;

        fd.sinfo = SOCKTRAN_SOURCE(sockMan);
        fd.lookFor = SOCK_POLL_READ | SOCK_POLL_READ_OOB;

        if (TRANSPORT_EXIT_NOW(sockMan))
        {
            return NULL;
        }

        rc = SOCK_Poll(&fd, 1, HMI_GetTimeOutInterval() * USEC_PER_MILLISEC);

        if (rc > 0 && fd.wasSet)
        {
            if (SOCK_ServerAccept(SOCKTRAN_SOURCE(sockMan),
                                  &SOCKTRAN_CONNECT(sockMan)) != ITS_SUCCESS)
            {
                return NULL;
            }

            /* got a client, bail out */
            break;
        }
    }

    /* current IMAL */
    if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
        ITS_TRANSPORT_DATA_SOCKET)
    {
        ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsSOCKTRAN_DynamicServerClass,
                                                   name, instance, mask);
    }
    /* GDI */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_GDI_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_DynamicServerClass_ANSI,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_DynamicServerClass_CCITT,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_DynamicServerClass_PRC,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsGDITRAN_DynamicServerClass_TTC,
                                                       name, instance, mask);
        }
    }
    /* TALI */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_TALI_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_DynamicServerClass_ANSI,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_DynamicServerClass_CCITT,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_DynamicServerClass_PRC,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsTALITRAN_DynamicServerClass_TTC,
                                                       name, instance, mask);
        }
    }
    /* IMAL with heartbeats */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_IMAL_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_DynamicServerClass_ANSI,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_DynamicServerClass_CCITT,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_DynamicServerClass_PRC,
                                                       name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsIMALTRAN_DynamicServerClass_TTC,
                                                       name, instance, mask);
        }
    }
    /* default */
    else
    {
        ret = (SOCKTRAN_Manager *)TRANSPORT_Create(itsSOCKTRAN_DynamicServerClass,
                                                   name, instance, mask);
    }

    if (ret == NULL)
    {
        ITS_TRACE_ERROR(("SOCKTRAN_IterativeAccept: transport create failed.\n"));

        SOCK_Close(SOCKTRAN_CONNECT(sockMan));
        SOCKTRAN_CONNECT(sockMan) = NULL;

        return (NULL);
    }

    SOCKTRAN_SOURCE(ret) = SOCKTRAN_CONNECT(sockMan);
    SOCKTRAN_CONNECT(sockMan) = NULL;

    SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ret))(ret);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method reaccepts a connection for a server.  It is assumed
 *      that the source socket is closed when this function is called.
 *
 *  Input Parameters:
 *      sockMan - the existing transport control block for the permanent
 *                connection.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - client was reaccepted.  Any other return code
 *      indicates failure.
 *
 *  Notes:
 *
 *  See Also:
 *      SOCKTRAN_CreateServerTransport
 ****************************************************************************/
ITSDLLAPI int
SOCKTRAN_ServerReAccept(SOCKTRAN_Manager *ft)
{
    int i;

    /* don't attempt if retries disabled */
    if (SOCKTRAN_RETRY_COUNT(ft) == 0)
    {
        return (ITS_EBADSOCKET);
    }

    /* don't attempt if we are dynamic */
    if (ITS_GET_TRANSPORT_FLAGS(TRANSPORT_MASK(ft)) &
        ITS_TRANSPORT_SSOCKET_DYN)
    {
        return (ITS_EBADSOCKET);
    }

    /* create the Server socket */
    i = 0;
    while (SOCKTRAN_RETRY_COUNT(ft) < 0 || i < SOCKTRAN_RETRY_COUNT(ft))
    {
        ITS_SockPollInfo fd;
        int rc;

        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_EBADSOCKET);
        }

        /* avoid leaks */
        if (SOCKTRAN_SOURCE(ft))
        {
            free(SOCKTRAN_SOURCE(ft));
        }
        SOCKTRAN_SOURCE(ft) = NULL;

        fd.sinfo = SOCKTRAN_CONNECT(ft);
        fd.lookFor = SOCK_POLL_READ | SOCK_POLL_READ_OOB;

        rc = SOCK_Poll(&fd, 1, HMI_GetTimeOutInterval() * USEC_PER_MILLISEC);

        if (rc > 0 && fd.lookFor)
        {
            /* Accept Connections */
            if (SOCK_ServerAccept(SOCKTRAN_CONNECT(ft),
                                  &SOCKTRAN_SOURCE(ft)) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("SOCKTRAN_ServerReAccept: accept of "
                                 "client failed\n"));

                i++;

                continue;
            }
        }
        else
        {
            continue;
        }

        SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ft))(ft);

        return (ITS_SUCCESS);
    }

    return (ITS_EBADSOCKET);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an ITS_EVENT from a UDP socket.
 *
 *  Input Parameters:
 *      h - the handle to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 ****************************************************************************/
static int
UDPReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    ITS_SockPollInfo info;

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    if (TRANSPORT_EXIT_NOW(h))
    {
        return (ITS_ERCVFAIL);
    }

repeat:
    memset(&info, 0, sizeof(info));

    info.lookFor = SOCK_POLL_READ;
    info.sinfo = SOCKTRAN_SOURCE(h);

    ret = SOCK_Poll(&info, 1,
                    HMI_GetTimeOutInterval() * USEC_PER_MILLISEC);

    if (TRANSPORT_EXIT_NOW(h))
    {
        return (ITS_ERCVFAIL);
    }

    if (ret < ITS_SUCCESS)
    {
        return (ITS_ERCVFAIL);
    }

    if (ret == 0)
    {
        TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();

        goto repeat;
    }

    ret = SOCK_Recv(SOCKTRAN_SOURCE(h), (char *)ev, sizeof(ITS_EVENT),
                    SOCKTRAN_CONNECT(h)->addr, &SOCKTRAN_CONNECT(h)->asize);

    if (ret != sizeof(ITS_EVENT))
    {
        return (ITS_ERCVFAIL);
    }

    ev->data = ITS_Malloc(ev->len);

    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    ret = SOCK_Recv(SOCKTRAN_SOURCE(h), (char *)ev->data, ev->len,
                    SOCKTRAN_CONNECT(h)->addr, &SOCKTRAN_CONNECT(h)->asize);

    if (ret == ev->len)
    {
        TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();

        TRANSPORT_NUM_RECV(h)++;

        return (ITS_SUCCESS);
    }
    else
    {
        return (ITS_ERCVFAIL);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an ITS_EVENT to a UDP socket.
 *
 *  Input Parameters:
 *      h - the handle to write into
 *      ev - the buffer to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 ****************************************************************************/
static int
UDPWriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    ret = SOCK_Send(SOCKTRAN_SOURCE(h), (char *)ev, sizeof(ITS_EVENT),
                    SOCKTRAN_CONNECT(h)->addr, SOCKTRAN_CONNECT(h)->asize);

    if (ret != sizeof(ITS_EVENT))
    {
        return (ITS_ESENDFAIL);
    }

    ret = SOCK_Send(SOCKTRAN_SOURCE(h), (char *)ev->data, ev->len,
                    SOCKTRAN_CONNECT(h)->addr, SOCKTRAN_CONNECT(h)->asize);

    if (ret == ev->len)
    {
        TRANSPORT_NUM_SENT(h)++;

        return (ITS_SUCCESS);
    }

    return (ITS_ESENDFAIL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds one associated transports that belong to this
 *      LocalEndPoint (e.g., one remote).
 *
 *  Input Parameters:
 *      transportClass - the class to build
 *      name - the transport name
 *      instance - the transport instance
 *      mask - the transport mask
 *      st = the LocalEndPoint
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - transports built.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static TRANSPORT_Control *
ConstructRemote(SOCKTRAN_Class transportClass,
                const char *name, ITS_USHORT instance, ITS_UINT mask,
                SOCKTRAN_Manager* local)
{
    TRANSPORT_Control *transport = NULL;

    if (ITS_GlobalStart(mask) != ITS_SUCCESS)
    {
        return (NULL);
    }

    transport = (TRANSPORT_Control *)
        ITS_ConstructObject((ITS_Class)transportClass, name,
                            instance, mask, local);

    if (transport == NULL)
    {
        return (NULL);
    }

    SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(transport))((SOCKTRAN_Manager *)transport);

    return transport;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds all associated transports that belong to this
 *      LocalEndPoint (e.g., all the remotes).
 *
 *  Input Parameters:
 *      st = the LocalEndPoint
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - transports built.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
BuildAssociatedTRIDs(SOCKTRAN_Manager *st)
{
    char name[ITS_PATH_MAX];
    char var[ITS_PATH_MAX], val[ITS_PATH_MAX];
    ITS_USHORT inst = 0;
    ITS_UINT mask = 0;
    ITS_BOOLEAN haveName, haveInst, haveMask;
    int i;

    SOCKTRAN_REMOTE_MAX(st) = 8;
    SOCKTRAN_REMOTE_COUNT(st) = 0;

    if ((SOCKTRAN_REMOTES(st) = (TRANSPORT_Control **)
                                  calloc(SOCKTRAN_REMOTE_MAX(st),
                                   sizeof(TRANSPORT_Control *))) == NULL)
    {
        return (ITS_ENOMEM);
    }


    RESFILE_Lock(TRANSPORT_RES(st));
    RESFILE_Rewind(TRANSPORT_RES(st), TRANSPORT_NAME(st));

    haveName = haveInst = haveMask = ITS_FALSE;

    while (RESFILE_GetKeyName(TRANSPORT_RES(st), TRANSPORT_NAME(st),
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(TRANSPORT_RES(st), TRANSPORT_NAME(st),
                               val, sizeof(var)) == ITS_SUCCESS)
    {
        if (strcmp(var, ASSOC_TRID_NAME_STRING) == 0)
        {
            haveName = ITS_TRUE;
            strcpy(name, val);
        }
        else if (strcmp(var, ASSOC_TRID_INST_STRING) == 0)
        {
            haveInst = ITS_TRUE;
            inst = (ITS_USHORT)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, ASSOC_TRID_MASK_STRING) == 0)
        {
            haveMask = ITS_TRUE;
            mask = (ITS_UINT)RESFILE_ParseNum(val);
        }

        if (haveName && haveInst && haveMask)
        {
            haveName = haveInst = haveMask = ITS_FALSE;

            if ((SOCKTRAN_REMOTES(st)[SOCKTRAN_REMOTE_COUNT(st)] =
                 ConstructRemote(SOCKTRAN_CLASS_EXT_ASSOCIATE(ITS_OBJ_CLASS(st)),
                                 name, inst, mask, st)) == NULL)
            {
                ITS_TRACE_ERROR(("BuildAssociated: failed to build "
                                 "associated trans :%s:%04x:%08x.\n",
                                 name, inst, mask));

                RESFILE_Unlock(TRANSPORT_RES(st));

                for (i = 0; i < SOCKTRAN_REMOTE_COUNT(st); i++)
                {
                    TRANSPORT_Delete(SOCKTRAN_REMOTES(st)[i]);
                }

                free(SOCKTRAN_REMOTES(st));

                return (ITS_ENOTRANSPORT);
            }

            SOCKTRAN_REMOTE_COUNT(st)++;

            if (SOCKTRAN_REMOTE_COUNT(st) == SOCKTRAN_REMOTE_MAX(st) - 1)
            {
                SOCKTRAN_REMOTE_MAX(st) *= 2;

                if ((SOCKTRAN_REMOTES(st) =
                        (TRANSPORT_Control **)
                            realloc(SOCKTRAN_REMOTES(st),
                                    SOCKTRAN_REMOTE_MAX(st) *
                                        sizeof(TRANSPORT_Control *))) == NULL)
                {
                    RESFILE_Unlock(TRANSPORT_RES(st));

                    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(st); i++)
                    {
                        TRANSPORT_Delete(SOCKTRAN_REMOTES(st)[i]);
                    }

                    free(SOCKTRAN_REMOTES(st));

                    return (ITS_ENOMEM);
                }
            }
        }
    }

    RESFILE_Unlock(TRANSPORT_RES(st));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds a local end point.
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
 *      ITS_SUCCESS - transport built.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalCreate(ITS_Object h, va_list args)
{
    char buf[ITS_PATH_MAX];
    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    ITS_TRACE_DEBUG(("CreateLocal:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    SOCKTRAN_DOMAIN(ret) = INET_DOMAIN;

    if ((SOCKTRAN_CONNECT(ret) =
            (ITS_SocketInfo *)calloc(1,
                                     sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("LocalCreate: out of memory.\n"));

        return (ITS_ENOMEM);
    }

    if (SOCK_CreateAddr(INET_DOMAIN, "0.0.0.0", 0,
                        &SOCKTRAN_CONNECT(ret)->addr,
                        &SOCKTRAN_CONNECT(ret)->asize) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: Out of memory.\n"));

        return (ITS_ENOMEM);
    }

    SOCKTRAN_CONNECT(ret)->type = SPROT_TYPE_UDP;

    /* Get the local addr */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              LOCAL_HOST_NAME_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: INI is missing "
                         "local host name.\n"));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_HOST_PATH(ret) = strdup(buf);
    }

    /* Get the local port */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              LOCAL_PORT_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: INI is missing "
                         "local host name.\n"));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_PORT(ret) = atoi(buf);
    }

    /* create the guards */
    if (MUTEX_CreateMutex(&SOCKTRAN_RMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: couldn't create "
                         "read mutex\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }

    if (MUTEX_CreateMutex(&SOCKTRAN_WMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: couldn't create "
                         "write mutex\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }

    if ((mask & ITS_TRANSPORT_SOCKP_MASK) == ITS_TRANSPORT_SCTP_SOCKET)
    {
        if (SCTPTRAN_Open(ret) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("LocalCreate: couldn't open "
                             "endpoint\n"));

            MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
            MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));

            free(SOCKTRAN_HOST_PATH(ret));

            free(SOCKTRAN_CONNECT(ret)->addr);
            free(SOCKTRAN_CONNECT(ret));

            return (ITS_ENOTRANSPORT);
        }
    }
    else
    {
        if (SOCK_EndPointOpen(&SOCKTRAN_SOURCE(ret),
                              INET_DOMAIN,
                              SOCKTRAN_HOST_PATH(ret),
                              SOCKTRAN_PORT(ret)) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("LocalCreate: couldn't open "
                             "endpoint\n"));

            MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
            MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));

            free(SOCKTRAN_HOST_PATH(ret));

            free(SOCKTRAN_CONNECT(ret)->addr);
            free(SOCKTRAN_CONNECT(ret));

            return (ITS_ENOTRANSPORT);
        }
    }

    if (BuildAssociatedTRIDs(ret) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: couldn't create "
                         "associated transports\n"));

        SOCK_Close(SOCKTRAN_SOURCE(ret));
        SOCKTRAN_SOURCE(ret) = NULL;

        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
        MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }

    SOCKTRAN_READ_EVENT(h) =
		SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(h));
    SOCKTRAN_WRITE_EVENT(h) =
		SOCKTRAN_CLASS_EXT_WRITE_EVENT(ITS_OBJ_CLASS(h));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys a local end point.
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
static void
LocalDestroy(ITS_Object obj)
{
    int i;

    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)obj;

    if (SOCKTRAN_REMOTES(ret))
    {
        for (i = 0; i < SOCKTRAN_REMOTE_COUNT(ret); i++)
        {
            TRANSPORT_Delete(SOCKTRAN_REMOTES(ret)[i]);
        }

        free(SOCKTRAN_REMOTES(ret));
    }

    MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
    MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret))(ret);
    }

    if (SOCKTRAN_SOURCE(ret))
    {
        if ((TRANSPORT_MASK(ret) & ITS_TRANSPORT_SOCKP_MASK) ==
            ITS_TRANSPORT_SCTP_SOCKET)
        {
            SCTPTRAN_Close(ret);
        }
        else
        {
            SOCK_Close(SOCKTRAN_SOURCE(ret));
        }
        SOCKTRAN_SOURCE(ret) = NULL;
    }

    free(SOCKTRAN_HOST_PATH(ret));

    free(SOCKTRAN_CONNECT(ret)->addr);
    free(SOCKTRAN_CONNECT(ret));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds a remote end point.
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
 *      ITS_SUCCESS - transport built.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RemoteCreate(ITS_Object obj, va_list args)
{
    char buf[ITS_PATH_MAX];
    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)obj;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    SOCKTRAN_Manager *local;

    ITS_TRACE_DEBUG(("CreateRemote:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);
    local = va_arg(args, SOCKTRAN_Manager *);

    SOCKTRAN_REMOTE_MAX(ret) = 8;

    if ((SOCKTRAN_REMOTES(ret) = (TRANSPORT_Control **)
                                  calloc(SOCKTRAN_REMOTE_MAX(ret),
                                   sizeof(TRANSPORT_Control *))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* set back pointer to local endpoint */
    SOCKTRAN_REMOTES(ret)[0] = (TRANSPORT_Control *)local;
    SOCKTRAN_REMOTE_COUNT(ret) = 1;

    SOCKTRAN_SOURCE(ret) = SOCKTRAN_SOURCE(local);

    SOCKTRAN_DOMAIN(ret) = INET_DOMAIN;

    /* Get the local addr */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SERVER_PATH_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemoteCreate: INI is missing "
                         "local host name.\n"));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_HOST_PATH(ret) = strdup(buf);
    }

    /* Get the local port */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SERVER_PORT_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemoteCreate: INI is missing "
                         "local host name.\n"));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        SOCKTRAN_PORT(ret) = atoi(buf);
    }

    /* create the remote addr information */
    if ((SOCKTRAN_CONNECT(ret) =
            (ITS_SocketInfo *)calloc(1,
                                     sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("RemoteCreate: out of memory.\n"));

        return (ITS_ENOMEM);
    }

    if (SOCK_CreateAddr(INET_DOMAIN,
                        SOCKTRAN_HOST_PATH(ret), SOCKTRAN_PORT(ret),
                        &SOCKTRAN_CONNECT(ret)->addr,
                        &SOCKTRAN_CONNECT(ret)->asize) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemoteCreate: Out of memory.\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOMEM);
    }

    SOCKTRAN_CONNECT(ret)->type = SPROT_TYPE_UDP;

    /* create the guards */
    if (MUTEX_CreateMutex(&SOCKTRAN_RMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemoteCreate: couldn't create "
                         "read mutex\n"));

        free(SOCKTRAN_HOST_PATH(ret));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }

    if (MUTEX_CreateMutex(&SOCKTRAN_WMUTEX(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemoteCreate: couldn't create "
                         "write mutex\n"));

        MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));

        free(SOCKTRAN_HOST_PATH(ret));

        free(SOCKTRAN_CONNECT(ret)->addr);
        free(SOCKTRAN_CONNECT(ret));

        return (ITS_ENOTRANSPORT);
    }

    SOCKTRAN_READ_EVENT(ret) =
		SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(ret));
    SOCKTRAN_WRITE_EVENT(ret) =
		SOCKTRAN_CLASS_EXT_WRITE_EVENT(ITS_OBJ_CLASS(ret));

    SOCKTRAN_CLASS_RESTART(ITS_OBJ_CLASS(ret))(ret);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys a remote end point.
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
static void
RemoteDestroy(ITS_Object obj)
{
    SOCKTRAN_Manager *ret = (SOCKTRAN_Manager *)obj;

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret))(ret);
    }

    if (SOCKTRAN_REMOTES(ret))
    {
        free(SOCKTRAN_REMOTES(ret));
    }

    MUTEX_DeleteMutex(&SOCKTRAN_RMUTEX(ret));
    MUTEX_DeleteMutex(&SOCKTRAN_WMUTEX(ret));

    free(SOCKTRAN_HOST_PATH(ret));

    free(SOCKTRAN_CONNECT(ret)->addr);
    free(SOCKTRAN_CONNECT(ret));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_READ_EVENT(h)(h, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point, if a message
 *      is pending
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalPeekNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    if (SOCK_Pending(SOCKTRAN_SOURCE(h)))
    {
        ret = SOCKTRAN_READ_EVENT(h)(h, ev);
    }
    else
    {
        ret = ITS_ENOMSG;
    }

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an event to a remote end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RemotePutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_WRITE_EVENT(h)(h, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(h));

    return (ret);
}

/*
 * forward
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_RemoteEndPointClassRec;

static SOCKTRAN_ClassExtRec UDPReadWrite =
{
    /* core class */
    {
        ITS_EXT_VERSION
    },
    /* socket class */
    {
        UDPReadEvent,                       /* Read one */
        UDPWriteEvent,                      /* Write one */
        &itsSOCKTRAN_RemoteEndPointClassRec /* associate */
    }
};

/*
 * the UDP class record(s)
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_LocalEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* the root object */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SOCKTRAN_LOCAL_ENDPOINT_CLASS_NAME,     /* class name */
        ITS_AddFeature,                         /* no class initialize */
        ITS_RemFeature,                         /* no class destructor */
        ClassPartInit,                          /* class part init */
        ClassPartDestroy,                       /* class part destroy */
        LocalCreate,                            /* instantiate */
        LocalDestroy,                           /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&UDPReadWrite             /* extension */
    },
    /* transport */
    {
        LocalGetNextEvent,              /* get next */
        LocalPeekNextEvent,             /* peek next */
        ReturnErrorFunction,            /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSOCKTRAN_LocalEndPointClass =
    (TRANSPORT_Class)&itsSOCKTRAN_LocalEndPointClassRec;

ITSDLLAPI SOCKTRAN_ClassRec itsSOCKTRAN_RemoteEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* the root object */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SOCKTRAN_REMOTE_ENDPOINT_CLASS_NAME,    /* class name */
        ITS_AddFeature,                         /* no class initialize */
        ITS_RemFeature,                         /* no class destructor */
        ClassPartInit,                          /* class part init */
        ClassPartDestroy,                       /* class part destroy */
        RemoteCreate,                           /* instantiate */
        RemoteDestroy,                          /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&UDPReadWrite             /* extension */
    },
    /* transport */
    {
        ReturnErrorFunction,            /* getNext */
        ReturnErrorFunction,            /* peekNext */
        RemotePutEvent,                 /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSOCKTRAN_RemoteEndPointClass =
    (TRANSPORT_Class)&itsSOCKTRAN_RemoteEndPointClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method creates a socket based UDP transport.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the socket
 *
 *  See Also:
 *      SOCKTRAN_DeleteEndPointTransport
 ****************************************************************************/
ITSDLLAPI SOCKTRAN_Manager*
SOCKTRAN_CreateEndPointTransport(const char *name,
                                 ITS_USHORT instance,
                                 ITS_UINT mask)
{
    SOCKTRAN_Manager *ret = NULL;

    ITS_TRACE_DEBUG(("SOCKTRAN_CreateEndPointTransport:\n"));

    /* IMAL */
    if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
        ITS_TRANSPORT_DATA_SOCKET)
    {
        ret = (SOCKTRAN_Manager *)
                TRANSPORT_Create(itsSOCKTRAN_LocalEndPointClass,
                                 name, instance, mask);
    }
    /* IMAL with heartbeats */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_IMAL_SOCKET)
    {
        if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            ret = (SOCKTRAN_Manager *)
                    TRANSPORT_Create(itsIMALTRAN_LocalEndPointClass_ANSI,
                                     name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            ret = (SOCKTRAN_Manager *)
                    TRANSPORT_Create(itsIMALTRAN_LocalEndPointClass_CCITT,
                                     name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            ret = (SOCKTRAN_Manager *)
                    TRANSPORT_Create(itsIMALTRAN_LocalEndPointClass_PRC,
                                     name, instance, mask);
        }
        else if ((ITS_GET_SS7_FLAGS(mask) & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            ret = (SOCKTRAN_Manager *)
                    TRANSPORT_Create(itsIMALTRAN_LocalEndPointClass_TTC,
                                     name, instance, mask);
        }
    }
    /* SCTP */
    else if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK) ==
             ITS_TRANSPORT_SCTP_SOCKET)
    {
        ret = (SOCKTRAN_Manager *)
                TRANSPORT_Create(itsSCTPTRAN_LocalEndPointClass,
                                 name, instance, mask);
    }
    /* default */
    else
    {
        ret = (SOCKTRAN_Manager *)
                TRANSPORT_Create(itsSOCKTRAN_LocalEndPointClass,
                                 name, instance, mask);
    }

    if (ret == NULL)
    {
        return (ret);
    }

    TRANSPORT_SetState(TRANSPORT(ret), ITS_TRUE);

    if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ret)))
    {
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ret))(ret);
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destroys a socket based UDP transport.
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
 *      SOCKTRAN_CreateEndPointTransport
 ****************************************************************************/
ITSDLLAPI void
SOCKTRAN_DeleteEndPointTransport(SOCKTRAN_Manager *ret)
{
    ITS_TRACE_DEBUG(("SOCKTRAN_DeleteServerTransport:\n"));

    TRANSPORT_SetState(TRANSPORT(ret), ITS_FALSE);

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ret))(ret);
    }

    TRANSPORT_Delete((ITS_HANDLE)ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method adds a virtual transport to an endpoint transport
 *
 *  Input Parameters:
 *      st - the UDP transport to add the virtual transport to
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      The resource file is consulted for host and port information for
 *      the virtual transport
 *
 *  See Also:
 *      SOCKTRAN_EndPointRemVirtualTransportTransport
 ****************************************************************************/
ITSDLLAPI int
SOCKTRAN_EndPointAddVirtualTransport(SOCKTRAN_Manager *st,
                                     const char *name,
                                     ITS_USHORT instance, ITS_UINT mask)
{
    if ((SOCKTRAN_REMOTES(st)[SOCKTRAN_REMOTE_COUNT(st)] =
         ConstructRemote(SOCKTRAN_CLASS_EXT_ASSOCIATE(ITS_OBJ_CLASS(st)),
                         name, instance, mask, st)) == NULL)
    {
        ITS_TRACE_ERROR(("AddVirtual: failed to build "
                         "associated trans :%s:%04x:%08x.\n",
                         name, instance, mask));

        return (ITS_ENOTRANSPORT);
    }

    SOCKTRAN_REMOTE_COUNT(st)++;

    if (SOCKTRAN_REMOTE_COUNT(st) == SOCKTRAN_REMOTE_MAX(st) - 1)
    {
        SOCKTRAN_REMOTE_MAX(st) *= 2;

        if ((SOCKTRAN_REMOTES(st) =
                (TRANSPORT_Control **)
                    realloc(SOCKTRAN_REMOTES(st),
                            SOCKTRAN_REMOTE_MAX(st) *
                                sizeof(TRANSPORT_Control *))) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method removes a virtual transport from an endpoint transport
 *
 *  Input Parameters:
 *      st - the UDP transport to add the virtual transport to
 *      instance - the instance id of this transport
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
 *      SOCKTRAN_EndPointAddVirtualTransportTransport
 ****************************************************************************/
ITSDLLAPI int
SOCKTRAN_EndPointRemVirtualTransport(SOCKTRAN_Manager *st,
                                     ITS_USHORT instance)
{
    ITS_USHORT i;

    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(st); i++)
    {
        if (TRANSPORT_INSTANCE(SOCKTRAN_REMOTES(st)[i]) == instance)
        {
            TRANSPORT_IS_ACTIVE(SOCKTRAN_REMOTES(st)[i]) = ITS_FALSE;

            if (i == SOCKTRAN_REMOTE_COUNT(st) - 1)
            {
                SOCKTRAN_REMOTE_COUNT(st)--;

                return (ITS_SUCCESS);
            }
            else
            {
                memmove(&SOCKTRAN_REMOTES(st)[i],
                        &SOCKTRAN_REMOTES(st)[i+1],
                        (SOCKTRAN_REMOTE_COUNT(st) - i - 1) *
                            sizeof(TRANSPORT_Control *));

                SOCKTRAN_REMOTE_COUNT(st)--;

                return (ITS_SUCCESS);
            }
        }
    }

    return (ITS_ENOTRANSPORT);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method finds a virtual transport by index
 *
 *  Input Parameters:
 *      st - the UDP transport to add the virtual transport to
 *      index - the index of this transport in the virtual list
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
ITSDLLAPI TRANSPORT_Control*
SOCKTRAN_EndPointFindVirtualTransport(SOCKTRAN_Manager *st,
                                      ITS_USHORT index)
{
    if (index >= SOCKTRAN_REMOTE_COUNT(st))
    {
        return (NULL);
    }

    return (SOCKTRAN_REMOTES(st)[index]);
}


