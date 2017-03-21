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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:24  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:52:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2002/09/18 20:51:00  yranade
 * LOG: Remove dead var
 * LOG:
 * LOG: Revision 7.2  2002/09/18 20:42:35  yranade
 * LOG: Bad free
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.16  2002/02/15 23:13:28  ssharma
 * LOG: Forgot to build the list of links associated with a transport.
 * LOG:
 * LOG: Revision 5.15  2002/02/06 23:44:58  mmiers
 * LOG: Continued ISUP integration
 * LOG:
 * LOG: Revision 5.14  2002/01/24 21:52:42  mmiers
 * LOG: For app routing, if we aren't adding the entries always
 * LOG: call the callback.  Add transport finding by name.
 * LOG:
 * LOG: Revision 5.13  2002/01/10 17:37:38  mmiers
 * LOG: Finish off the refcounting code.
 * LOG:
 * LOG: Revision 5.12  2002/01/10 16:51:35  mmiers
 * LOG: Finish the transport refcounting effort.  Move vframe from
 * LOG: vendors to here.
 * LOG:
 * LOG: Revision 5.11  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.10  2001/12/07 18:45:14  mmiers
 * LOG: Remove mutex in CheckExpiry, don't exit if it fails.
 * LOG:
 * LOG: Revision 5.9  2001/12/07 17:08:19  mmiers
 * LOG: Add link count to licensing.
 * LOG:
 * LOG: Revision 5.8  2001/11/20 17:42:01  mmiers
 * LOG: Finish DBC conversion.
 * LOG:
 * LOG: Revision 5.7  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.6  2001/10/18 19:01:09  mmiers
 * LOG: Rework the link/route division.  It's easier if they're in
 * LOG: a single table.
 * LOG:
 * LOG: Revision 5.5  2001/09/24 22:51:21  mmiers
 * LOG: Work on MTP3 integration.
 * LOG:
 * LOG: Revision 5.4  2001/09/18 22:18:58  mmiers
 * LOG: Add internal transports API
 * LOG:
 * LOG: Revision 5.3  2001/09/05 23:06:41  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/08/14 15:26:19  mmiers
 * LOG: Start making room for MTP3.
 * LOG:
 * LOG: Revision 4.5  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.4  2001/06/16 00:34:33  mmiers
 * LOG: Catch zero length writes.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 19:06:02  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.2  2001/05/02 00:01:51  mmiers
 * LOG: Finish alarm implementation.  HMI just needs the monitor
 * LOG: algorithm.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.38  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.37  2001/04/25 01:17:01  mmiers
 * LOG: Better encapsulation.  We need the lock anyway.
 * LOG:
 * LOG: Revision 3.36  2001/04/25 01:04:24  mmiers
 * LOG: Before PR4 is cut, add in the HMI requirements for transport.
 * LOG:
 * LOG: Revision 3.35  2001/03/16 23:18:46  mmiers
 * LOG: Ok, everything done but the parser.
 * LOG:
 * LOG: Revision 3.34  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.33  2001/03/02 23:35:44  mmiers
 * LOG: Couple of routing bug fixes.
 * LOG:
 * LOG: Revision 3.32  2001/03/02 23:04:04  mmiers
 * LOG: Cross platform cleanup.
 * LOG:
 * LOG: Revision 3.31  2001/03/02 22:44:15  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 3.30  2001/02/23 22:27:12  mmiers
 * LOG: Use proper API
 * LOG:
 * LOG: Revision 3.29  2001/02/16 22:18:20  hxing
 * LOG: Little bug fixed
 * LOG:
 * LOG: Revision 3.28  2001/02/14 20:44:54  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.27  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.26  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.25  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.24  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.23  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.22  2001/01/17 20:34:40  mmiers
 * LOG: Get the flags right.
 * LOG:
 * LOG: Revision 3.21  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.20  2000/12/29 17:35:01  mmiers
 * LOG: This should work
 * LOG:
 * LOG: Revision 3.19  2000/12/29 17:15:11  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 3.18  2000/12/29 16:42:04  mmiers
 * LOG: Change the flag settings.
 * LOG:
 * LOG: Revision 3.17  2000/12/22 00:36:26  mmiers
 * LOG: First message through
 * LOG:
 * LOG: Revision 3.16  2000/12/22 00:09:31  mmiers
 * LOG: Alter defaults a bit
 * LOG:
 * LOG: Revision 3.15  2000/12/21 23:53:01  mmiers
 * LOG: Duh
 * LOG:
 * LOG: Revision 3.14  2000/12/21 23:50:51  mmiers
 * LOG: Traces & bugs
 * LOG:
 * LOG: Revision 3.13  2000/12/19 18:57:57  mmiers
 * LOG: Typo in route parsing
 * LOG:
 * LOG: Revision 3.12  2000/11/22 18:03:45  mmiers
 * LOG: More SCTP integration.
 * LOG:
 * LOG: Revision 3.11  2000/11/15 22:43:23  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.10  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.10  2000/11/09 23:04:27  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.9  2000/10/05 23:05:34  mmiers
 * LOG: New routing scheme.
 * LOG:
 * LOG: Revision 3.8  2000/10/04 16:48:28  omayor
 * LOG:  Added Duplicate PC and Duplicate SSN to TRANSPORT_RegisterSS7Data
 * LOG:  in order to implement SOR SOG SCMG procedures.
 * LOG:
 * LOG: Revision 3.7  2000/09/28 21:49:50  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.6  2000/09/25 20:09:27  mmiers
 * LOG: About done.  Need to convert route.c itself now.
 * LOG:
 * LOG: Revision 3.5  2000/09/25 19:56:52  mmiers
 * LOG: Set up for new route style.
 * LOG:
 * LOG: Revision 3.4  2000/09/22 00:21:58  mmiers
 * LOG: Fix PR3 bug in current.
 * LOG:
 * LOG: Revision 3.3  2000/09/14 17:27:47  mmiers
 * LOG: Avoid less than clueful users.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:42  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:46  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.20  2000/07/17 16:30:34  hxing
 * LOG:
 * LOG:
 * LOG: Move register() into Create.
 * LOG:
 * LOG: Revision 2.19  2000/07/04 00:14:58  rsonak
 * LOG:
 * LOG:
 * LOG: Debug, bad route delete, transport route ls/lc collection
 * LOG:
 * LOG: Revision 2.18  2000/06/02 02:05:18  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.17  2000/05/16 00:05:22  mmiers
 * LOG:
 * LOG:
 * LOG: Add concept of route by linkset to routing table.
 * LOG:
 * LOG: Revision 2.16  2000/05/15 22:34:03  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.15  2000/04/25 23:30:01  mmiers
 * LOG:
 * LOG:
 * LOG: Platform cleanup.
 * LOG:
 * LOG: Revision 2.14  2000/03/02 16:24:16  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 2.13  2000/02/14 19:17:45  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.12  2000/02/10 02:19:08  mmiers
 * LOG:
 * LOG: Update trace text
 * LOG:
 * LOG: Revision 2.11  2000/02/10 00:44:37  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP connections at IDLE now work.  More tomorrow.
 * LOG:
 * LOG: Revision 2.10  2000/02/09 18:51:40  mmiers
 * LOG:
 * LOG:
 * LOG: Debug of EndPoint sockets done.  On to RUDP debug.
 * LOG:
 * LOG: Revision 2.9  2000/02/02 02:20:53  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.8  2000/01/24 22:19:23  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 2.7  2000/01/21 22:48:16  mmiers
 * LOG:
 * LOG: Had to add separate up/allowed variables.
 * LOG:
 * LOG: Revision 2.6  2000/01/21 22:14:45  mmiers
 * LOG:
 * LOG: Checkpoint changes.  Include routing behavior changes for Rajesh.
 * LOG:
 * LOG: Revision 2.5  1999/12/22 02:09:04  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.4  1999/12/16 02:19:22  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.3  1999/12/16 00:53:04  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 02:44:23  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 23:44:47  mmiers
 * LOG:
 * LOG:
 * LOG: Convert to the new object format.  Only callback is done so far.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:21  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.64  1999/11/10 18:29:22  mmiers
 * LOG:
 * LOG:
 * LOG: Change pointer type back.
 * LOG:
 * LOG: Revision 1.63  1999/11/10 15:04:05  mmiers
 * LOG:
 * LOG:
 * LOG: Build problems on Solaris.
 * LOG:
 * LOG: Revision 1.62  1999/11/10 00:09:41  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.61  1999/11/05 20:30:08  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up first cut of GDI, remove volatile qualifier from
 * LOG: FindTransport.
 * LOG:
 * LOG: Revision 1.60  1999/10/25 23:38:51  mmiers
 * LOG:
 * LOG:
 * LOG: Documentation code for the programming impaired.
 * LOG:
 * LOG: Revision 1.59  1999/10/25 20:59:45  mmiers
 * LOG:
 * LOG:
 * LOG: Watch infinite recursion.
 * LOG:
 * LOG: Revision 1.58  1999/10/25 18:55:27  mmiers
 * LOG:
 * LOG:
 * LOG: Cross platform build.
 * LOG:
 * LOG: Revision 1.57  1999/10/25 18:28:16  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.56  1999/10/12 18:34:47  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with non-zero code.
 * LOG:
 * LOG: Revision 1.55  1999/10/07 17:52:36  mmiers
 * LOG:
 * LOG:
 * LOG: Add protos (ISUP) fix bug (transports).
 * LOG:
 * LOG: Revision 1.54  1999/08/11 02:35:33  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.53  1999/08/02 17:02:31  mmiers
 * LOG:
 * LOG:
 * LOG: Document the format string for INI file names.
 * LOG:
 * LOG: Revision 1.52  1999/07/29 00:08:40  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.51  1999/07/23 20:07:58  mmiers
 * LOG:
 * LOG:
 * LOG: Separate out registration/deregistration of the SS7 routing info.
 * LOG: This makes this callable for dynamic style transports.
 * LOG:
 * LOG: Revision 1.50  1999/07/22 22:40:06  rsonak
 * LOG:
 * LOG: Fixed a brainfart...if (Application_name==NULL){return ENOTRANSPORT}
 * LOG: instead of return ret. ret could be ITS_SUCCESS from the earlier 'if' block.
 * LOG:
 * LOG: Revision 1.49  1999/06/23 23:24:31  labuser
 * LOG:
 * LOG:
 * LOG: NO SIDE EFFECTS IN ASSERT STATEMENTS!
 * LOG:
 * LOG: Revision 1.48  1999/06/23 21:21:20  rsonak
 * LOG:
 * LOG:
 * LOG: Rework the iterative/dynamic socket server (more tightly coupled
 * LOG: with infrastructure).
 * LOG:
 * LOG: Revision 1.47  1999/06/18 21:31:36  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a couple of minor bugs with the resource file parsing.
 * LOG:
 * LOG: Revision 1.46  1999/05/24 21:07:09  mmiers
 * LOG:
 * LOG:
 * LOG: Enable the transports to parse hex strings.
 * LOG:
 * LOG: Revision 1.45  1999/03/17 14:27:39  mmiers
 * LOG:
 * LOG:
 * LOG: More work on simultaneous ANSI and CCITT protocols.  Change the size
 * LOG: of the "type" field of ITS_HDR to be 16 bits.
 * LOG:
 * LOG: Revision 1.44  1999/03/12 18:20:16  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.43  1999/03/12 00:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.42  1999/02/25 22:57:14  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.41  1999/02/04 22:57:42  mmiers
 * LOG:
 * LOG:
 * LOG: Some tweaks, detail improvement.
 * LOG:
 * LOG: Revision 1.40  1999/02/04 22:26:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.39  1998/12/08 20:40:45  rsonak
 * LOG: Modifications for HNS stabilization.
 * LOG:
 * LOG: Revision 1.38  1998/11/19 00:36:32  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.37  1998/11/18 21:07:39  mmiers
 * LOG: Minor build tweaks.
 * LOG:
 * LOG: Revision 1.36  1998/11/13 02:52:14  mmiers
 * LOG: Note that we should not be doing all of this in certain cases.
 * LOG:
 * LOG: Revision 1.35  1998/11/12 00:09:17  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.34  1998/11/11 00:44:49  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.33  1998/11/06 17:52:35  rsonak
 * LOG: Need to initialize the callbackManagers after allocating them.
 * LOG:
 * LOG: Revision 1.32  1998/11/05 03:27:08  mmiers
 * LOG: Add serialization counters to transports.
 * LOG:
 * LOG: Revision 1.31  1998/11/04 20:00:31  mmiers
 * LOG: Change this around a bit.
 * LOG:
 * LOG: Revision 1.30  1998/11/04 19:48:38  mmiers
 * LOG: Add callback invocation to TRANSPORT_SetState() and
 * LOG: TRANSPORT_SetCongestion()
 * LOG:
 * LOG: Revision 1.29  1998/11/04 02:47:33  mmiers
 * LOG: Remove ITS_SS7_LOCAL_ROUTE, it is irrelevant, we don't do that.
 * LOG: Add congestion callback list, it will be used for SS7.
 * LOG: Update TODO to reflect what needs to be added.
 * LOG:
 * LOG: Revision 1.28  1998/11/03 19:11:32  mmiers
 * LOG: Add callback creation/destruction to transports.
 * LOG:
 * LOG: Revision 1.27  1998/11/03 15:18:18  mmiers
 * LOG: Fix build bugs due to missing prototypes, typos.
 * LOG:
 * LOG: Revision 1.26  1998/11/03 02:56:30  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.25  1998/10/27 16:58:00  mmiers
 * LOG: Fix debug output.
 * LOG:
 * LOG: Revision 1.24  1998/09/29 20:22:35  mmiers
 * LOG: Add route state into the picture.
 * LOG:
 * LOG: Revision 1.23  1998/09/28 22:46:02  mmiers
 * LOG: Note transient nature of current tranport enabling.
 * LOG:
 * LOG: Revision 1.22  1998/09/28 22:42:45  mmiers
 * LOG: More work enhancing MTP3-ish support.
 * LOG:
 * LOG: Revision 1.21  1998/09/28 22:09:41  mmiers
 * LOG: More support for intelligent transports.
 * LOG:
 * LOG: Revision 1.20  1998/09/22 18:51:22  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.19  1998/08/03 20:34:19  mmiers
 * LOG: Add cleaner functionality to ITS_Terminate() for transient transports.
 * LOG:
 * LOG: Revision 1.18  1998/07/22 15:24:54  mmiers
 * LOG: Reorder PC/SSN slightly.
 * LOG:
 * LOG: Revision 1.17  1998/07/21 18:37:14  mmiers
 * LOG: Add mutex initialization to ip transports.
 * LOG:
 * LOG: Remove vestigial connection variable from tq transports.
 * LOG:
 * LOG: Add localPC, localSSN processing to the transport base class.
 * LOG:
 * LOG: Revision 1.16  1998/06/26 16:31:26  mmiers
 * LOG: Complete the transport conversion.
 * LOG:
 * LOG: Revision 1.15  1998/06/26 14:30:00  mmiers
 * LOG: Convert C++ transports to use C versions.
 * LOG:
 * LOG: Revision 1.14  1998/06/23 00:36:12  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.13  1998/06/22 16:11:43  mmiers
 * LOG: Add transport PC/SSN settings.
 * LOG:
 * LOG: Revision 1.12  1998/06/18 23:39:35  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.11  1998/06/18 01:02:42  mmiers
 * LOG: More "C" style transports.
 * LOG:
 * LOG: Revision 1.10  1998/06/16 23:41:02  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.9  1998/06/09 21:32:33  whu
 * LOG: fifo_trans: Use ITS_Fifo, not ITS_GatedFifo.
 * LOG:
 * LOG: transports: remove printf().
 * LOG:
 * LOG: Revision 1.8  1998/06/09 21:00:32  whu
 * LOG: Make thread pool threads suspended on creation.  This removes a race
 * LOG: condition where the worker thread has not reached the suspended state
 * LOG: before the main thread dispatches work to it; in this case, the worker
 * LOG: suspends *before* the work is started, resulting in a wasted dispatch.
 * LOG:
 * LOG: Also fixed a bug where we were adding and removing threads from the
 * LOG: avail list twice.  Had to add a new parameter to the THREAD interface;
 * LOG: document this.
 * LOG:
 * LOG: Revision 1.7  1998/06/01 16:35:39  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.6  1998/05/29 23:53:15  mmiers
 * LOG: More documentation.  I'm nearing the finish on the support subsystem.
 * LOG:
 * LOG: Revision 1.5  1998/05/20 17:06:14  mmiers
 * LOG: Get the namespace thing right.  You must include its++.h if
 * LOG: you want to use the its namespace.
 * LOG:
 * LOG: Revision 1.4  1998/04/23 01:34:08  mmiers
 * LOG: Update after building on Solaris.
 * LOG:
 * LOG: Revision 1.3  1998/04/20 22:04:47  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.2  1998/04/16 15:59:01  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  1998/04/16 14:43:30  mmiers
 * LOG: Get the file type right.
 * LOG:
 * LOG: Revision 1.1  1998/04/16 04:35:27  mmiers
 * LOG: New file.
 * LOG:
 *
 ****************************************************************************/

/*
 * transport handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_transports.h>
#include <its_iniparse.h>
#include <its_route.h>
#include <its_trace.h>
#include <its_license.h>
#include <its_app.h>
#include <its_tq_trans.h>
#include <its_assertion.h>
#include <its_timers.h>

#ident "$Id: its_transports.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

static TRANSPORT_Manager transportManager;

ITSDLLAPI CALLBACK_Manager* TRANSPORT_registrations = NULL;
ITSDLLAPI CALLBACK_Manager* TRANSPORT_deregistrations = NULL;

static void Delete(ITS_Object h);

/*
 * slot reservation special value
 */
#define TRANSPORT_SLOT_RESERVED     ((TRANSPORT_Control *)-1)

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function registers a transport with the transport subsystem.
 *      Once this function has been called, entities within an application
 *      can find a transport by its instance id.
 *
 *  Input Parameters:
 *      name - the name of this transport.  It need not be unique.
 *      id - the instance id of this transport.
 *      trans - callback data specific to this transport
 *      pf - the callback function to use to send data to this transport
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the transport was successfully added, ITS_SUCCESS is returned
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      TRANSPORT_DeregisterTransport()
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_RegisterTransport(TRANSPORT_Control* tc)
{
    ITS_TRACE_DEBUG(("TRANSPORT_RegisterTransport:\n"));

    if (TRANSPORT_INSTANCE(tc) == 0)
    {
        ITS_TRACE_ERROR(("TRANSPORT_RegisterTransport: bad id\n"));

        return (ITS_ENOLIST);
    }

    if (RWLOCK_LockExclusive(&transportManager.transportGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_RegisterTransport: counldn't lock\n"));

        return (ITS_EBADMUTEX);
    }

    if (transportManager.arrayOfTransports[TRANSPORT_INSTANCE(tc)] != NULL &&
        transportManager.arrayOfTransports[TRANSPORT_INSTANCE(tc)] != TRANSPORT_SLOT_RESERVED)
    {
        ITS_TRACE_ERROR(("TRANSPORT_RegisterTransport: transport "
                         "already registered\n"));

        RWLOCK_UnlockExclusive(&transportManager.transportGate);

        return (ITS_ELISTNOTUNIQUE);
    }

    TRANSPORT_REFCNT(tc)++;

    transportManager.arrayOfTransports[TRANSPORT_INSTANCE(tc)] = tc;

    CALLBACK_CallCallbackList(TRANSPORT_registrations,
                              (ITS_POINTER)tc,
                              NULL);

    TRANSPORT_IS_ACTIVE(tc) = ITS_FALSE;
    TRANSPORT_LAST_UPDATE(tc) = TIMERS_Time();

    if (transportManager.listHead == NULL && transportManager.listTail == NULL)
    {
        TRANSPORT_HMI_PREV(tc) = NULL;
        TRANSPORT_HMI_NEXT(tc) = NULL;
        transportManager.listHead = transportManager.listTail = tc;
    }
    else
    {
        ITS_C_REQUIRE(transportManager.listTail != NULL);

        TRANSPORT_HMI_NEXT(transportManager.listTail) = tc;
        TRANSPORT_HMI_PREV(tc) = transportManager.listTail;
        TRANSPORT_HMI_NEXT(tc) = NULL;
        transportManager.listTail = tc;
    }

    RWLOCK_UnlockExclusive(&transportManager.transportGate);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes a transport from the transport subsystem.
 *      Once this function has been called for a transport, entities will
 *      no longer be able to find this transport by its instance id.
 *
 *  Input Parameters:
 *      id - the instance id of the transport to deregister
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the transport was successfully removed, ITS_SUCCESS is returned
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      TRANSPORT_RegisterTransport()
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_DeregisterTransport(ITS_USHORT id)
{
    TRANSPORT_Control *tc;

    ITS_TRACE_DEBUG(("TRANSPORT_DeregisterTransport:\n"));

    if (id == 0)
    {
        ITS_TRACE_ERROR(("TRANSPORT_DeregisterTransport: bad id\n"));

        return (ITS_ENOLIST);
    }

    if (RWLOCK_LockExclusive(&transportManager.transportGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_DeregisterTransport: couldn't lock\n"));

        return (ITS_EBADMUTEX);
    }

    tc = transportManager.arrayOfTransports[id];

    TRANSPORT_REFCNT(tc)--;

    if (TRANSPORT_REFCNT(tc) != 0)
    {
        RWLOCK_UnlockExclusive(&transportManager.transportGate);

        return (ITS_EINUSE);
    }

    if (tc == NULL)
    {
        ITS_TRACE_ERROR(("TRANSPORT_DeregisterTransport: transport "
                         "not registered\n"));

        RWLOCK_UnlockExclusive(&transportManager.transportGate);

        return (ITS_ENOTRANSPORT);
    }

    if (TRANSPORT_INSTANCE(tc) != id)
    {
        ITS_TRACE_ERROR(("TRANSPORT_DeregisterTransport: transport id "
                         "mismatch\n"));

        RWLOCK_UnlockExclusive(&transportManager.transportGate);

        return (ITS_ENOLIST);
    }

    CALLBACK_CallCallbackList(TRANSPORT_deregistrations,
                              (ITS_POINTER)tc,
                              NULL);

    transportManager.arrayOfTransports[id] = NULL;

    /* one entry list? */
    if (tc == transportManager.listHead && tc == transportManager.listTail)
    {
        transportManager.listHead = transportManager.listTail = NULL;
    }
    /* list head? */
    else if (tc == transportManager.listHead)
    {
        transportManager.listHead = TRANSPORT_HMI_NEXT(tc);
        if (TRANSPORT_HMI_NEXT(tc) != NULL)
        {
            TRANSPORT_HMI_PREV(TRANSPORT_HMI_NEXT(tc)) = NULL;
        }
    }
    /* list tail? */
    else if (tc == transportManager.listTail)
    {
        transportManager.listTail = TRANSPORT_HMI_PREV(tc);
        if (TRANSPORT_HMI_PREV(tc) != NULL)
        {
            TRANSPORT_HMI_NEXT(TRANSPORT_HMI_PREV(tc)) = NULL;
        }
    }
    /* safely buried in list */
    else
    {
        ITS_C_ASSERT(TRANSPORT_HMI_PREV(tc) != NULL &&
                     TRANSPORT_HMI_NEXT(tc) != NULL);

        TRANSPORT_HMI_NEXT(TRANSPORT_HMI_PREV(tc)) = TRANSPORT_HMI_NEXT(tc);
        TRANSPORT_HMI_PREV(TRANSPORT_HMI_NEXT(tc)) = TRANSPORT_HMI_PREV(tc);
        TRANSPORT_HMI_PREV(tc) = TRANSPORT_HMI_NEXT(tc) = NULL;
    }

    RWLOCK_UnlockExclusive(&transportManager.transportGate);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function locates a transport's information in the transport
 *      table.
 *
 *  Input Parameters:
 *      id - the instance id of this transport.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - the transport does not exist
 *             otherwise, the handle of the transport.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI TRANSPORT_Control *
TRANSPORT_FindTransport(ITS_USHORT instance)
{
    volatile TRANSPORT_Control *ret = NULL;

    ITS_TRACE_DEBUG(("TRANSPORT_FindTransport:\n"));

    if (RWLOCK_LockExclusive(&transportManager.transportGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_FindTransport: couldn't acquire mutex\n"));

        return (NULL);
    }

    ret = transportManager.arrayOfTransports[instance];

    if (ret && ret != TRANSPORT_SLOT_RESERVED)
    {
        TRANSPORT_REFCNT(ret)++;
    }

    RWLOCK_UnlockExclusive(&transportManager.transportGate);

    return ((TRANSPORT_Control *)ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function locates a transport's information in the transport
 *      table.
 *
 *  Input Parameters:
 *      name - the name of this transport.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - the transport does not exist
 *             otherwise, the handle of the transport.
 *
 *  Notes:
 *
 *  See Also:
 *      This function assumes that the transport names are unique.  User
 *      beware.
 ****************************************************************************/
ITSDLLAPI TRANSPORT_Control*
TRANSPORT_FindTransportByName(const char *name)
{
    volatile TRANSPORT_Control *ret = NULL;
    ITS_USHORT i;

    ITS_TRACE_DEBUG(("TRANSPORT_FindTransport:\n"));

    if (RWLOCK_LockExclusive(&transportManager.transportGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_FindTransport: couldn't acquire mutex\n"));

        return (NULL);
    }

    ret = NULL;
    for (i = 1; i < ITS_MAX_EVENT_QUEUES; i++)
    {
        ret = transportManager.arrayOfTransports[i];

        if (ret == TRANSPORT_SLOT_RESERVED ||
            ret == NULL)
        {
            continue;
        }

        if (name && TRANSPORT_NAME(ret) &&
            strcmp(name, TRANSPORT_NAME(ret)) == 0)
        {
            break;
        }
    }
    if (i == ITS_MAX_EVENT_QUEUES)
    {
        ret = NULL;
    }

    if (ret)
    {
        TRANSPORT_REFCNT(ret)++;
    }

    RWLOCK_UnlockExclusive(&transportManager.transportGate);

    return ((TRANSPORT_Control *)ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function locates a transport's information in the transport
 *      table.
 *
 *  Input Parameters:
 *      id - the instance id of this transport.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - the transport does not exist
 *             otherwise, the handle of the transport.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
TRANSPORT_UnfindTransport(TRANSPORT_Control *ret)
{
    volatile ITS_UINT refcnt;

    ITS_TRACE_DEBUG(("TRANSPORT_UnfindTransport:\n"));

    if (ret == NULL)
    {
        return;
    }

    if (RWLOCK_LockExclusive(&transportManager.transportGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_FindTransport: couldn't acquire mutex\n"));

        return;
    }

    TRANSPORT_REFCNT(ret)--;
    refcnt = TRANSPORT_REFCNT(ret);

    RWLOCK_UnlockExclusive(&transportManager.transportGate);

    if (refcnt == 0)
    {
        TRANSPORT_Delete(ret);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method is really overkill.  It just wrappers ITS_GetNextEvent().
 *
 *  Input Parameters:
 *      base - the transport to fetch from
 *      entry - the event to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the is sent successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_GetNextEvent(TRANSPORT_Control *base, ITS_EVENT *ev)
{
    return ITS_GetNextEvent((ITS_HANDLE)base, ev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method is really overkill.  It just wrappers ITS_PeekNextEvent().
 *
 *  Input Parameters:
 *      base - the transport to fetch from
 *      entry - the event to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the is sent successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_PeekNextEvent(TRANSPORT_Control *base, ITS_EVENT *ev)
{
    return ITS_PeekNextEvent((ITS_HANDLE)base, ev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function provides the mapping mechanism from transport instance
 *      id to actual transport.  It uses a mapping table and a callback
 *      function to convert the instance id to a function for placing the
 *      event on the proper transport.
 *
 *  Input Parameters:
 *      id - the transport instance to send this event to
 *      entry - the event to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the is sent successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_PutEvent(ITS_USHORT id, ITS_EVENT* entry)
{
    TRANSPORT_Control *tr;
    int (*fptr)(ITS_HANDLE h, ITS_EVENT* ev);
    ITS_BOOLEAN isTaskQueue = ITS_FALSE;
    int ret;

    ITS_TRACE_DEBUG(("TRANSPORT_PutEvent:\n"));

    if (LICENSE_CheckExpiry() != ITS_SUCCESS)
    {
        return (ITS_ENOLICENSE);
    }

    /* use the transport gate to ensure that a transport is not being
     * registered or deregistered while we're trying to put an event on
     * the target transport */
    if (RWLOCK_LockShared(&transportManager.transportGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_DeregisterTransport: couldn't lock\n"));

        if (entry->data)
        {
            ITS_Free(entry->data);

            entry->data = NULL;
        }

        return (ITS_EBADMUTEX);
    }

    tr = transportManager.arrayOfTransports[id];

    if (tr == NULL ||
        TRANSPORT_INSTANCE(tr) != id ||
        ITS_OBJ_CLASS(tr) == NULL ||
        TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(tr)) == NULL)
    {
        ITS_TRACE_ERROR(("TRANSPORT_PutEvent: transport invalid\n"));

        RWLOCK_UnlockShared(&transportManager.transportGate);

        if (entry->data)
        {
            ITS_Free(entry->data);

            entry->data = NULL;
        }

        return (ITS_ENOTRANSPORT);
    }

    /*
     * copy the transport put function pointer.  We can get away with this
     * even if the transport dies after the mutex release.  However, nothing
     * says that a user cannot blow himself up when using instance variables
     * on a deleted transport.
     *
     * We need to do this so that blocking put calls do not idle the entire
     * process, so we call *after* we release the mutex.
     *
     * Addenda: even though we now use RWLOCKs, the objection above still
     * holds.  We release *before* putting, as a blocked reader would deadlock
     * a writer (specifically, a transport going away needs an exclusive lock,
     * and we wouldn't want him blocked waiting for a blocked reader).
     */
    fptr = TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(tr));
    if (ITS_IsInstanceOf((ITS_Class)itsTQUEUETRAN_Class,
                         (ITS_Object)tr))
    {
        isTaskQueue = ITS_TRUE;
    }

    RWLOCK_UnlockShared(&transportManager.transportGate);

    ret = (*fptr)(tr, entry);

    if (ret != ITS_SUCCESS || !isTaskQueue)
    {
        ITS_Free(entry->data);
    }

    entry->data = NULL;
    entry->len = 0;

    return (ret);
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
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_RegisterSS7Data(TRANSPORT_Control *base)
{
    ITS_TRACE_DEBUG(("TRANSPORT_RegisterSS7Data: processing link "
                     "information\n"));

    if (!TRANSPORT_RES(base))
    {
        ITS_TRACE_ERROR(("TRANSPORT_RegisterSS7Data: transport is missing "
                         "an INI\n"));

        return (ITS_EMISSINGRES);
    }

    return LINK_ParseLinkInfo(base);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function deletes the route info of a "C" transport.
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to cleanup.
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
ITSDLLAPI void
TRANSPORT_DeregisterSS7Data(TRANSPORT_Control* base)
{
    SS7_LinkPtr link, tmp;

    for (link = TRANSPORT_SS7_INFO(base).linkInfo;
         link != NULL;
         link = tmp)
    {
        tmp = link->next;

        if (link->linkSet)
        {
            link = LINK_FindLink(link->linkSet->linkSet,
                                 link->linkCode);

            if (link)
            {
                LINK_RemLink(link->linkSet->linkSet,
                             link);
            }
        }

        /* Note: we don't free these anymore (not here, anyway).  They
         * might be in DSM
         */
    }

    TRANSPORT_SS7_INFO(base).linkInfo = NULL;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the number of events sent on this transport.
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to query.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The number of events sent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
TRANSPORT_GetNumSent(TRANSPORT_Control* base)
{
    return TRANSPORT_NUM_SENT(base);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the number of events received on this transport
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to query.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The number of events received.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
TRANSPORT_GetNumRecv(TRANSPORT_Control* base)
{
    return TRANSPORT_NUM_RECV(base);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function clears the number of events sent on this transport.
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to set.
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
ITSDLLAPI void
TRANSPORT_ClearNumSent(TRANSPORT_Control* base)
{
    TRANSPORT_NUM_SENT(base) = 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function clears the number of events received on this transport
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to set.
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
ITSDLLAPI void
TRANSPORT_ClearNumRecv(TRANSPORT_Control* base)
{
    TRANSPORT_NUM_RECV(base) = 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates the base part of a "C" transport.
 *
 *  Input Parameters:
 *      name - the name of the transport
 *      instance - the transport instance
 *      mask - the transport mask
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the transport is created successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Create(ITS_Object transport, va_list args)
{
    TRANSPORT_Control *base = (TRANSPORT_Control *)transport;
    char buf[ITS_PATH_MAX];
    const char *name;
    int ret;
    ITS_USHORT instance;
    ITS_UINT mask;

    name = va_arg(args, char *);
    instance = va_arg(args, ITS_UINT);
    mask = ITS_VerifyMask(va_arg(args, ITS_UINT));

    ITS_C_REQUIRE(name != NULL);

    ITS_TRACE_DEBUG(("Create(transport): name %s instance %04x mask %08x\n",
                     name, instance, mask));

    TRANSPORT_INSTANCE(base) = instance;
    TRANSPORT_MASK(base) = mask;

    TRANSPORT_CUR_INIT_INVOKE(base) = ~0;
    TRANSPORT_CUR_TERM_INVOKE(base) = 0;

    /* initialize the callback managers */
    if ((TRANSPORT_SS7_INFO(base).resumeCallbacks =
         CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't init resCallbacks\n"));

        return (ITS_ENOMEM);
    }

    if ((TRANSPORT_SS7_INFO(base).pauseCallbacks =
         CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't init resCallbacks\n"));

        CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).resumeCallbacks);

        return (ITS_ENOMEM);
    }

    if ((TRANSPORT_SS7_INFO(base).statusCallbacks =
         CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't init resCallbacks\n"));

        CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).pauseCallbacks);
        CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).resumeCallbacks);

        return (ITS_ENOMEM);
    }


    /* create the resource file */
    if (APPL_GetName() == NULL)
    {
        ITS_TRACE_ERROR(("Create: No application name!\n"));

        CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).pauseCallbacks);
        CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).resumeCallbacks);

        return (ITS_ENOTRANSPORT);
    }

    if (APPL_GetConfigFileName())
    {
        strcpy(buf, APPL_GetConfigFileName());
    }

    TRANSPORT_RES(base) = RESFILE_CreateResourceManager(buf);

    if (name)
    {
        TRANSPORT_NAME(base) = strdup(name);
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    TRANSPORT_SS7_INFO(base).linkInfo = NULL;
    if (mask & ITS_SS7_MASK)
    {
        if ((ret = LICENSE_AddLink()) != ITS_SUCCESS)
        {
            Delete((ITS_Object)base);

            return (ret);
        }

        if ((ret = TRANSPORT_RegisterSS7Data(base)) != ITS_SUCCESS)
        {
            Delete((ITS_Object)base);

            LICENSE_RemLink();

            return (ret);
        }
    }

    /* register this transport */
    if ((ret = TRANSPORT_RegisterTransport(base)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Create: couldn't register this "
                         "transport\n"));

        Delete((ITS_Object)base);

        if (mask & ITS_SS7_MASK)
        {
            LICENSE_RemLink();
        }

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function deletes the base part of a "C" transport.
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to cleanup.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the transport is deleted successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Delete(ITS_Object h)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)h;

    ITS_TRACE_DEBUG(("Delete:\n"));

    if (TRANSPORT_DeregisterTransport(TRANSPORT_INSTANCE(base)))
    {
        /* we can't bail, someone else has a reference */
        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        TRANSPORT_DeregisterSS7Data(base);

        LICENSE_RemLink();
    }

    /* clean up the callbacks */
    CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).resumeCallbacks);
    CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).pauseCallbacks);
    CALLBACK_DestroyManager(TRANSPORT_SS7_INFO(base).statusCallbacks);

    if (TRANSPORT_NAME(base))
    {
        free(TRANSPORT_NAME(base));
    }

    if (TRANSPORT_RES(base))
    {
        RESFILE_DeleteResourceManager(TRANSPORT_RES(base));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Fallback function.  Note that it is absurd to actually use this,
 *      as normally it would imply infinite recursion (thus the check
 *      to enforce that the method called is not this method).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
GetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)h;

    if (ITS_OBJ_CLASS(tc) &&
        TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(tc)) &&
        TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(tc)) != GetNextEvent)
    {
        return TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(tc))(h, ev);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Fallback function.  Note that it is absurd to actually use this,
 *      as normally it would imply infinite recursion (thus the check
 *      to enforce that the method called is not this method).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PeekNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)h;

    if (ITS_OBJ_CLASS(tc) &&
        TRANSPORT_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(tc)) &&
        TRANSPORT_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(tc)) != PeekNextEvent)
    {
        return TRANSPORT_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(tc))(h, ev);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Fallback function.  Note that it is absurd to actually use this,
 *      as normally it would imply infinite recursion (thus the check
 *      to enforce that the method called is not this method).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)h;

    if (ITS_OBJ_CLASS(tc) &&
        TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(tc)) &&
        TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(tc)) != PutEvent)
    {
        return TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(tc))(h, ev);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Fallback function.  Note that it is absurd to actually use this,
 *      as normally it would imply infinite recursion (thus the check
 *      to enforce that the method called is not this method).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
OnConnect(ITS_HANDLE h)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)h;

    if (ITS_OBJ_CLASS(tc) &&
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(tc)) &&
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(tc)) != OnConnect)
    {
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(tc))(h);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Fallback function.  Note that it is absurd to actually use this,
 *      as normally it would imply infinite recursion (thus the check
 *      to enforce that the method called is not this method).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
OnDisconnect(ITS_HANDLE h)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)h;

    if (ITS_OBJ_CLASS(tc) &&
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(tc)) &&
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(tc)) != OnDisconnect)
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(tc))(h);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function constructs any transport
 *
 *  Input Parameters:
 *      transportClass - the class to instantiate
 *      transport - the transport to construct
 *      name - the name of the transport to initialize
 *      instance - the transport instance
 *      mask - the transport mask
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
ClassInit(ITS_Class subClass)
{
    int res;

    ITS_TRACE_DEBUG(("TRANSPORT_Initialize:\n"));

    res = RWLOCK_CreateLock(&transportManager.transportGate);

    if (res != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TRANSPORT_Initialize: couldn't create mutex\n"));

        return (res);
    }

    if ((TRANSPORT_registrations = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("TRANSPORT_Initialize: couldn't allocate dregList\n"));

        RWLOCK_DeleteLock(&transportManager.transportGate);

        return (ITS_ENOMEM);
    }

    if ((TRANSPORT_deregistrations = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("TRANSPORT_Initialize: couldn't allocate dregList\n"));

        CALLBACK_DestroyManager(TRANSPORT_registrations);

        RWLOCK_DeleteLock(&transportManager.transportGate);

        return (ITS_ENOMEM);
    }

    return res;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function constructs any transport
 *
 *  Input Parameters:
 *      transportClass - the class to instantiate
 *      transport - the transport to construct
 *      name - the name of the transport to initialize
 *      instance - the transport instance
 *      mask - the transport mask
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
ClassDestroy(ITS_Class subClass)
{
    ITS_TRACE_DEBUG(("TRANSPORT_Terminate:\n"));

    if (TRANSPORT_registrations)
    {
        CALLBACK_DestroyManager(TRANSPORT_registrations);
    }

    if (TRANSPORT_deregistrations)
    {
        CALLBACK_DestroyManager(TRANSPORT_deregistrations);
    }

    RWLOCK_DeleteLock(&transportManager.transportGate);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function constructs the transport part of a subclass
 *
 *  Input Parameters:
 *      objClass - the class whose part needs construction
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
ClassPartInit(ITS_Class subClass)
{
    if (TRANSPORT_CLASS_GET_NEXT_EVENT(subClass) ==
        TRANSPORT_INHERIT_EVENT_PROC)
    {
        TRANSPORT_CLASS_GET_NEXT_EVENT(subClass) =
            TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_CLASS_SUPERCLASS(subClass));
    }
    
    if (TRANSPORT_CLASS_PEEK_NEXT_EVENT(subClass) ==
        TRANSPORT_INHERIT_EVENT_PROC)
    {
        TRANSPORT_CLASS_PEEK_NEXT_EVENT(subClass) =
            TRANSPORT_CLASS_PEEK_NEXT_EVENT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (TRANSPORT_CLASS_PUT_EVENT(subClass) ==
        TRANSPORT_INHERIT_EVENT_PROC)
    {
        TRANSPORT_CLASS_PUT_EVENT(subClass) =
            TRANSPORT_CLASS_PUT_EVENT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (TRANSPORT_CLASS_ON_CONNECT(subClass) ==
        TRANSPORT_INHERIT_HANDLE_PROC)
    {
        TRANSPORT_CLASS_ON_CONNECT(subClass) =
            TRANSPORT_CLASS_ON_CONNECT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (TRANSPORT_CLASS_ON_DISCONNECT(subClass) ==
        TRANSPORT_INHERIT_HANDLE_PROC)
    {
        TRANSPORT_CLASS_ON_DISCONNECT(subClass) =
            TRANSPORT_CLASS_ON_DISCONNECT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (TRANSPORT_CLASS_SET_EXIT(subClass) ==
        TRANSPORT_INHERIT_EXIT_PROC)
    {
        TRANSPORT_CLASS_SET_EXIT(subClass) =
            TRANSPORT_CLASS_SET_EXIT(ITS_CLASS_SUPERCLASS(subClass));
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
 * the base transport class object
 */
ITSDLLAPI TRANSPORT_ClassRec itsTRANSPORT_BaseClassRec =
{
    /* core */
    {
        &itsCORE_ClassRec,          /* Core superclass */
        sizeof(TRANSPORT_Control),  /* Widget size */
        ITS_FALSE,                  /* class not initted */
        0,                          /* initial ref count */
        TRANSPORT_CLASS_NAME,       /* class name */
        ClassInit,                  /* class initialize */
        ClassDestroy,               /* class destruct */
        ClassPartInit,              /* initialize the class part */
        ClassPartDestroy,           /* destruct the class part */
        Create,                     /* standard create */
        Delete,                     /* standard destroy */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no meaningful extension */
    },
    /* transport */
    {
        GetNextEvent,               /* default GetNextEvent */
        PeekNextEvent,              /* default PeekNextEvent */
        PutEvent,                   /* default PutEvent */
        OnConnect,                  /* default OnConnect proc */
        OnDisconnect                /* default OnDisconnect proc */
    }
};

ITSDLLAPI ITS_Class itsTRANSPORT_BaseClass =
    (ITS_Class)&itsTRANSPORT_BaseClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function initializes any transport
 *
 *  Input Parameters:
 *      transportClass - the class to instantiate
 *      name - the name of the transport to initialize
 *      instance - the transport instance
 *      mask - the transport mask
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
ITSDLLAPI ITS_HANDLE
TRANSPORT_Create(TRANSPORT_Class transportClass, const char *name,
                 ITS_USHORT instance, ITS_UINT mask)
{
    TRANSPORT_Control *transport = NULL;

    ITS_C_ASSERT(transportClass != NULL);

    if (ITS_GlobalStart(mask) != ITS_SUCCESS)
    {
        return (NULL);
    }

    transport = (TRANSPORT_Control *)
        ITS_ConstructObject((ITS_Class)transportClass, name, instance, mask);

    return (ITS_HANDLE)transport;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function deletes the base part of a "C" transport.
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to cleanup.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the transport is deleted successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
TRANSPORT_Delete(ITS_HANDLE h)
{
    ITS_TRACE_DEBUG(("TRANSPORT_Delete:\n"));

    ITS_C_REQUIRE(h != NULL);

    ITS_DestructObject((ITS_Object)h);

    ITS_GlobalStop();
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function sets the state of the routes through this transport
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to cleanup.
 *      isUp - are the destinations reachable
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the state is set successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_SetState(TRANSPORT_Control* base, ITS_BOOLEAN isUp)
{
    ITS_TRACE_DEBUG(("TRANSPORT_SetState: %d\n", isUp));

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SetState: Couldn't get link lock\n"));

        return (ITS_EBADMUTEX);
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) &&
        TRANSPORT_SS7_INFO(base).linkInfo)
    {
        if (isUp)
        {
            CALLBACK_CallCallbackList(TRANSPORT_SS7_INFO(base).resumeCallbacks,
                                      (ITS_POINTER)base, NULL);
        }
        else
        {
            CALLBACK_CallCallbackList(TRANSPORT_SS7_INFO(base).pauseCallbacks,
                                      (ITS_POINTER)base, NULL);
        }
    }

    ROUTE_UnlockTable();

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function sets the congestion level of routes through this
 *      transport.
 *
 *  Input Parameters:
 *      base - a pointer to the TRANSPORT to cleanup.
 *      congLevel - the congestion level to set
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the congLevel is set successfully, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_SetCongestion(TRANSPORT_Control* base, ITS_OCTET congLevel)
{
    ITS_TRACE_DEBUG(("TRANSPORT_SetCongestion:\n"));

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SetState: Couldn't get link lock\n"));

        return (ITS_EBADMUTEX);
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) &&
        TRANSPORT_SS7_INFO(base).linkInfo)
    {
        CALLBACK_CallCallbackList(TRANSPORT_SS7_INFO(base).statusCallbacks,
                                  (ITS_POINTER)base, NULL);
    }

    ROUTE_UnlockTable();

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method returns the exit flag of a transport.
 *
 *  Input Parameters:
 *      base - the transport
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - the transport has been marked to exit
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRANSPORT_GetExit(TRANSPORT_Control* base)
{
    if (base)
    {
        return TRANSPORT_EXIT_NOW(base);
    }

    return (ITS_TRUE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method sets the exit flag on a transport.
 *
 *  Input Parameters:
 *      base - the transport
 *      doExit - ITS_TRUE marks the transport to exit.
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
ITSDLLAPI void
TRANSPORT_SetExit(TRANSPORT_Control* base, ITS_BOOLEAN doExit)
{
    if (base)
    {
        TRANSPORT_EXIT_NOW(base) = doExit;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This (private) function returns a pointer to the transport
 *      manager.
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
ITSDLLAPI TRANSPORT_Manager *
TRANSPORT_GetManager()
{
    return &transportManager;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This (private) function returns a locks the transport manager
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
ITSDLLAPI int
TRANSPORT_LockManager()
{
    return RWLOCK_LockExclusive(&transportManager.transportGate);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This (private) function returns a locks the transport manager
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
ITSDLLAPI int
TRANSPORT_UnlockManager()
{
    return RWLOCK_UnlockExclusive(&transportManager.transportGate);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function locates a transport's information in the transport
 *      table.
 *
 *  Input Parameters:
 *      id - the instance id of this transport.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - the transport does not exist
 *             otherwise, the handle of the transport.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI TRANSPORT_Control *
TRANSPORT_FindTransportNoLock(ITS_USHORT instance)
{
    volatile TRANSPORT_Control *ret = NULL;

    ITS_TRACE_DEBUG(("TRANSPORT_FindTransportNoLock:\n"));

    ret = transportManager.arrayOfTransports[instance];

    return ((TRANSPORT_Control *)ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function reserves a slot in the transport table.
 *
 *  Input Parameters:
 *      id - the instance id of this transport.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - the transport does not exist
 *             otherwise, the handle of the transport.
 *
 *  Notes:
 *      It is assumed that a lock is already held.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TRANSPORT_ReserveSlot(ITS_USHORT instance)
{
    if (transportManager.arrayOfTransports[instance] != NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    transportManager.arrayOfTransports[instance] = TRANSPORT_SLOT_RESERVED;

    return (ITS_SUCCESS);
}
