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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2.2.2  2005/09/14 16:27:54  lbana
 * LOG: Modified for building mtp2 kernel module on Linux flavors.
 * LOG:
 * LOG: Revision 9.2.2.1  2005/08/29 09:24:15  adutta
 * LOG: Addition of BSSAP stack source
 * LOG:
 * LOG: Revision 9.2  2005/06/02 13:55:14  adutta
 * LOG: New source for Multiple App Binding
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1.6.2.10.4  2005/01/31 11:37:21  snagesh
 * LOG: Added error #defines for link/linkset not found
 * LOG:
 * LOG: Revision 7.2.2.1.6.2.10.3  2004/12/28 13:15:45  mkrishna
 * LOG: SIP code propagated from Current Branch
 * LOG:
 * LOG: Revision 7.2.2.1.6.2.10.2  2004/12/16 03:26:17  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.2.1.6.2.10.1  2004/12/15 07:14:18  adutta
 * LOG: ITS_M2UA_SRC added
 * LOG:
 * LOG: Revision 7.2.2.1.6.2  2004/01/27 05:57:54  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.2.2.1.6.1  2004/01/05 09:24:45  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.2.2.1.2.1  2003/09/05 10:05:28  akumar
 * LOG: New Macros for DSM-GCS.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 08:21:35  ssingh
 * LOG: ISUP related changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/07/03 17:41:07  mmiers
 * LOG: china changes
 * LOG:
 * LOG: Revision 6.4  2002/07/03 16:37:45  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.3  2002/04/29 21:30:19  randresol
 * LOG: add ITS_EDUPLENTRY error code
 * LOG:
 * LOG: Revision 6.2.2.1  2002/04/18 19:24:39  randresol
 * LOG: Add changes for redundant MTP3
 * LOG:
 * LOG: Revision 6.2  2002/04/04 16:42:01  hdivoux
 * LOG: More errors for upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:08  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10  2002/02/06 23:44:57  mmiers
 * LOG: Continued ISUP integration
 * LOG:
 * LOG: Revision 5.9  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.8  2001/12/18 21:56:43  mmiers
 * LOG: Vendor lib clues
 * LOG:
 * LOG: Revision 5.7  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.5  2001/10/18 20:02:52  mmiers
 * LOG: Avoid many version defines, destination parsing.
 * LOG:
 * LOG: Revision 5.4  2001/10/17 18:20:58  mmiers
 * LOG: Convert routing to use link information.
 * LOG:
 * LOG: Revision 5.3  2001/10/05 22:59:15  mmiers
 * LOG: Update from working on NMS MTP2 API
 * LOG:
 * LOG: Revision 5.2  2001/09/05 14:49:36  mmiers
 * LOG: Add bits.  Rename CIC cic.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/27 22:57:42  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:14:25  omayor
 * LOG: Added range of trid for UAL pending QUEUEs.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.22  2001/04/27 17:28:51  mmiers
 * LOG: Preallocate instance numbers, add SCTP fix.
 * LOG:
 * LOG: Revision 3.21  2001/04/10 19:57:19  mmiers
 * LOG: Still debugging.
 * LOG:
 * LOG: Revision 3.20  2001/04/05 16:52:15  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.19  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 3.18  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.17  2001/03/05 23:54:56  mmiers
 * LOG: Prep for dynamic linking.
 * LOG:
 * LOG: Revision 3.16  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 3.15  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.14  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.13  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.12  2001/01/31 00:37:01  mmiers
 * LOG: Third time
 * LOG:
 * LOG: Revision 3.11  2001/01/31 00:35:13  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 3.10  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.9  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.8  2001/01/17 20:34:54  mmiers
 * LOG: Add mask verification function.
 * LOG:
 * LOG: Revision 3.7  2000/11/30 17:55:55  mmiers
 * LOG: Straighten out the defines (we had overlaps)
 * LOG:
 * LOG: Revision 3.6  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.5  2000/09/29 21:37:14  mmiers
 * LOG: Ok, hookup in place.  Now to sanitize and debug.
 * LOG:
 * LOG: Revision 3.4  2000/09/29 17:52:01  mmiers
 * LOG: OK.  Skeleton done, hook things together, rething its_sctp_trans.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:56:30  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:35  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:08  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.14  2000/08/09 00:08:18  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.13  2000/05/26 21:34:18  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes, more SCTP work.
 * LOG:
 * LOG: Revision 2.12  2000/05/25 23:25:31  mmiers
 * LOG:
 * LOG:
 * LOG: Today's SCTP snapshot.
 * LOG:
 * LOG: Revision 2.11  2000/05/23 21:26:33  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot of SCTP.
 * LOG:
 * LOG: Revision 2.10  2000/05/10 23:39:47  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 * LOG: Revision 2.9  2000/05/05 15:51:26  rsonak
 * LOG:
 * LOG: Added SRCs for Vendor Management Interface (VMI)
 * LOG:
 * LOG: Revision 2.8  2000/05/03 21:07:14  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 * LOG: Revision 2.7  2000/04/24 22:20:03  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.
 * LOG:
 * LOG: Revision 2.6  2000/03/28 17:42:50  hdivoux
 * LOG: Added ASN.1 encode and decode error codes.
 * LOG:
 * LOG: Revision 2.5  2000/03/18 21:03:30  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.4  2000/01/25 23:47:21  mmiers
 * LOG:
 * LOG:
 * LOG: More work on RUDP.  This is finally taking shape.
 * LOG:
 * LOG: Revision 2.3  2000/01/24 23:13:48  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating.
 * LOG:
 * LOG: Revision 2.2  2000/01/21 22:12:24  mmiers
 * LOG:
 * LOG: Checkpoint.  Include changes for Rajesh (routing table).
 * LOG:
 * LOG: Revision 2.1  2000/01/14 23:25:43  mmiers
 * LOG:
 * LOG:
 * LOG: Work with RUDP more.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:30  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.91  1999/11/10 00:08:37  mmiers
 * LOG:
 * LOG:
 * LOG: In goes the extension.
 * LOG:
 * LOG: Revision 1.90  1999/10/05 18:58:15  rsonak
 * LOG:
 * LOG: Removed the protocol defines for ANSI AND CCITT from this file.
 * LOG:
 * LOG: Revision 1.89  1999/10/05 15:19:58  mmiers
 * LOG:
 * LOG:
 * LOG: Move protocol source defines to their respective files.
 * LOG:
 * LOG: Revision 1.88  1999/08/11 02:35:29  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.87  1999/08/02 17:02:31  mmiers
 * LOG:
 * LOG:
 * LOG: Document the format string for INI file names.
 * LOG:
 * LOG: Revision 1.86  1999/07/29 00:08:37  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.85  1999/07/13 14:48:19  mmiers
 * LOG:
 * LOG:
 * LOG: Group the environment variables in its.h.  Add environment variable for
 * LOG: trace files (default to cwd).  Remove dbc_command from dbc workspace.
 * LOG:
 * LOG: Revision 1.84  1999/06/28 21:47:30  skarmakar
 * LOG:
 * LOG:
 * LOG: A fix for the namespace craziness.
 * LOG:
 * LOG: Revision 1.83  1999/06/23 21:21:18  rsonak
 * LOG:
 * LOG:
 * LOG: Rework the iterative/dynamic socket server (more tightly coupled
 * LOG: with infrastructure).
 * LOG:
 * LOG: Revision 1.82  1999/06/22 16:26:24  mmiers
 * LOG:
 * LOG:
 * LOG: Document the format string for unnamed transports.
 * LOG:
 * LOG: Revision 1.81  1999/06/15 15:09:47  rsonak
 * LOG:
 * LOG: Added Iterative and Dyanmic transports
 * LOG:
 * LOG: Revision 1.80  1999/03/17 18:41:56  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol updates.
 * LOG:
 * LOG: Revision 1.79  1999/03/17 14:27:38  mmiers
 * LOG:
 * LOG:
 * LOG: More work on simultaneous ANSI and CCITT protocols.  Change the size
 * LOG: of the "type" field of ITS_HDR to be 16 bits.
 * LOG:
 * LOG: Revision 1.78  1999/03/12 23:24:45  mmiers
 * LOG:
 * LOG:
 * LOG: Finish dual protocol family support.
 * LOG:
 * LOG: Revision 1.77  1999/03/12 00:06:09  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.76  1999/02/26 04:09:49  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.75  1999/02/04 22:26:36  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.74  1998/11/18 18:11:24  mmiers
 * LOG: Update comments.
 * LOG:
 * LOG: Revision 1.73  1998/10/16 17:05:00  mmiers
 * LOG: Nother error code for ENOENT.
 * LOG:
 * LOG: Revision 1.72  1998/10/15 01:28:03  mmiers
 * LOG: Add new error code for BADSTATE.
 * LOG:
 * LOG: Revision 1.71  1998/10/13 20:36:42  jpakrasi
 * LOG: Added another error code 'ITS_EINVCHOICE'.
 * LOG:
 * LOG: Revision 1.70  1998/10/06 16:38:27  jpakrasi
 * LOG: Added ErrorCodes from -57 to -62 to support the helper functions being
 * LOG: added for the protocol API's.
 * LOG:
 * LOG: Revision 1.69  1998/09/30 02:40:03  mmiers
 * LOG: Updates for SCCP.  I think I've got the compromises for SCCP routing
 * LOG: down.  Need to add the routing label everywhere.
 * LOG:
 * LOG: Revision 1.68  1998/09/28 22:09:38  mmiers
 * LOG: More support for intelligent transports.
 * LOG:
 * LOG: Revision 1.67  1998/09/28 17:28:45  mmiers
 * LOG: Delete dead event sources (SCCP).
 * LOG:
 * LOG: Revision 1.66  1998/08/03 20:34:16  mmiers
 * LOG: Add cleaner functionality to ITS_Terminate() for transient transports.
 * LOG:
 * LOG: Revision 1.65  1998/07/03 16:09:38  mmiers
 * LOG: SCCP as a thread.
 * LOG:
 * LOG: Revision 1.64  1998/07/02 15:47:18  mmiers
 * LOG: Add SSL to the repository.
 * LOG:
 * LOG: Revision 1.63  1998/07/02 00:11:45  hdivoux
 * LOG: Previously added constants are now unsigned.
 * LOG:
 * LOG: Revision 1.62  1998/07/02 00:10:08  hdivoux
 * LOG: Added constants related to application protocol sources.
 * LOG:
 * LOG: Revision 1.61  1998/07/01 23:34:51  mmiers
 * LOG: Modify the route selection interface slightly.
 * LOG:
 * LOG: Revision 1.60  1998/06/30 20:59:09  mmiers
 * LOG: Update a few comments.
 * LOG:
 * LOG: Revision 1.59  1998/06/24 17:45:06  mmiers
 * LOG: Convert over to using the generated exceptions.
 * LOG:
 * LOG: Revision 1.58  1998/06/24 16:12:30  mmiers
 * LOG: Straighten out the tranport vs. worker issues.
 * LOG:
 * LOG: Revision 1.57  1998/06/19 22:25:00  mmiers
 * LOG: Reaching the end of TCAP.  Initial SCCP implementation.
 * LOG:
 * LOG: Revision 1.56  1998/06/18 23:39:32  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.55  1998/06/17 19:57:04  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.54  1998/06/16 23:40:59  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.53  1998/06/05 16:28:31  whu
 * LOG: Fix transport mask bug.
 * LOG:
 * LOG: Revision 1.52  1998/06/04 23:32:58  mmiers
 * LOG: A massive update to IS634.  This implementation (C++) is nearly complete.
 * LOG:
 * LOG: Revision 1.51  1998/06/02 19:43:12  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.50  1998/06/02 04:00:50  mmiers
 * LOG: Docgen: Split the output into multiple files.
 * LOG:
 * LOG: Revision 1.49  1998/06/01 16:35:13  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.48  1998/05/31 03:14:45  mmiers
 * LOG: Fix compilation errors.
 * LOG:
 * LOG: Revision 1.47  1998/05/29 03:31:28  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.46  1998/05/27 02:18:11  mmiers
 * LOG: Reimplement fifos for NT and Solaris.  Nobody should be affected by this
 * LOG: change (from a user perspective), but ITS_Worker has a new transport type,
 * LOG: depending on whether or not the FIFO transport is reentrant.
 * LOG:
 * LOG: Revision 1.45  1998/05/26 23:38:13  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.44  1998/05/26 16:29:26  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.43  1998/05/26 02:08:07  mmiers
 * LOG: Basic comments.  I really shirked work this weekend.
 * LOG:
 * LOG: Revision 1.42  1998/05/20 20:15:30  mmiers
 * LOG: Get test8 (process framework) compiled and linked.  Not
 * LOG: all code is linked in (no sending yet, which will cause more
 * LOG: undefined externals).
 * LOG:
 * LOG: Revision 1.41  1998/05/20 01:54:34  mmiers
 * LOG: General tree cleanup.
 * LOG:
 * LOG: Revision 1.40  1998/05/15 17:24:37  mmiers
 * LOG: Finish SCCP++.  More work on TCAP++.
 * LOG:
 * LOG: Revision 1.39  1998/05/14 20:41:44  mmiers
 * LOG: Update SCCP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.38  1998/05/14 02:45:27  mmiers
 * LOG: More work on SCCP.  I think I have the encode done OK, still have to
 * LOG: write the decode.  The PTR table in SCCP messages is a bit of a bitch.
 * LOG: If we ever do the same for ISUP, the IEToEvent code could be reused.
 * LOG: That would give us (minus the ever important *PROCEDURES*) the requirement
 * LOG: of MTP3 and below ONLY.  However, ther are a *LOT* of procedures we
 * LOG: don't do (e.g., SST).
 * LOG:
 * LOG: Revision 1.37  1998/05/01 00:24:29  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.36  1998/04/29 22:43:48  mmiers
 * LOG: Make ITS_TCAP_SRC modification.
 * LOG:
 * LOG: Revision 1.35  1998/04/23 17:04:04  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.34  1998/04/22 19:00:09  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.33  1998/04/20 22:04:43  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.32  1998/04/16 19:44:19  mmiers
 * LOG: Start adding transport implementation.
 * LOG:
 * LOG: Revision 1.31  1998/04/16 15:58:59  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.30  1998/04/13 22:24:37  mmiers
 * LOG: Add direction checking for fifos.
 * LOG:
 * LOG: Revision 1.29  1998/04/09 01:47:16  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.28  1998/04/08 17:25:27  mmiers
 * LOG: Work on sockets abstraction.
 * LOG:
 * LOG: Revision 1.27  1998/04/07 15:03:54  mmiers
 * LOG: More work on fifos, which required some new error numbers.
 * LOG:
 * LOG: Revision 1.26  1998/04/03 22:17:52  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.25  1998/03/13 04:12:30  mmiers
 * LOG: Update files with latest data for TCAP implementation.  emlist represents
 * LOG: portable message queues.
 * LOG:
 * LOG: Revision 1.24  1998/03/12 03:50:53  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.23  1998/03/12 00:25:58  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.22  1998/02/26 16:23:09  mmiers
 * LOG: Update the TCAP tests to use the single ITS_Initialize() signature.  The
 * LOG: parameters are now read from a file for NMS.  The signature in its.h has
 * LOG: been consolidated to one platform-independent signature.
 * LOG:
 * LOG: Revision 1.21  1998/02/25 22:12:23  mmiers
 * LOG: sccp.h: Some corrections, a plan for moving the address structure from
 * LOG: tcap.h to sccp.h.  Add SCCP as a possible event source to its.h.  Add
 * LOG: a type for point codes to its_types.h.
 * LOG:
 * LOG: Revision 1.20  1998/02/18 20:50:24  rsonak
 * LOG: Added some more error codes
 * LOG:
 * LOG: Revision 1.19  1998/02/18 16:18:45  rsonak
 * LOG: Corrected the spelling mistakes
 * LOG:
 * LOG: Revision 1.18  1998/02/10 22:32:10  mmiers
 * LOG: Separate out the PART specific stuff from its.h.  Everything is now in
 * LOG: its appropriate place.  The TCAP headers moved from common to TCAP.  The
 * LOG: state machine code has been added to the tree.
 * LOG:
 * LOG: Revision 1.17  1998/02/06 14:40:37  mmiers
 * LOG: Move SCCP interface definition to the SCCP include file
 * LOG:
 * LOG: Revision 1.16  1998/02/06 14:36:49  mmiers
 * LOG: #ifdef guards
 * LOG:
 * LOG: Revision 1.14  1998/02/06 14:15:28  mmiers
 * LOG: Add ISUP msg type macro.
 * LOG:
 * LOG: Revision 1.13  1998/02/05 16:03:51  ite
 * LOG: Added #if defined(NMS) around ITS_Initialize().
 * LOG:
 * LOG: Revision 1.12  1998/02/05 01:45:45  ite
 * LOG: Modified ITS_Terminate signature and added extern before its_debug and its_error.
 * LOG:
 * LOG: Revision 1.11  1998/02/04 23:01:15  rsonak
 * LOG: Merge with repository.
 * LOG:
 * LOG: Revision 1.10  1998/02/03 01:40:55  ite
 * LOG: Missed the boat on indirection levels for ITS_Initialize().
 * LOG:
 * LOG: Revision 1.9  1998/02/03 01:32:05  ite
 * LOG: Add empty prototype for ITS_Initialize().  Need to revisit when working in
 * LOG: C++.
 * LOG:
 * LOG: Revision 1.8  1998/02/03 01:30:43  ite
 * LOG: really add in the ITS_Terminate() prototype.
 * LOG:
 * LOG: Revision 1.6  1998/01/29 01:13:25  rsonak
 * LOG: Added ITS_CAP event source.
 * LOG:
 * LOG: Revision 1.5  1998/01/28 22:23:40  rsonak
 * LOG: Added ITS_AllocateTCAPDialogueId()
 * LOG:
 * LOG: Revision 1.4  1998/01/28 02:00:58  rsonak
 * LOG: Update from NMS integration.
 * LOG:
 * LOG: Revision 1.3  1998/01/24 22:36:57  mmiers
 * LOG: Tree cleanup.
 * LOG:
 * LOG: Revision 1.2  1998/01/21 23:47:14  rsonak
 * LOG: Added the error ITS_BADMESSAGE
 * LOG:
 *
 ***************************************************************************/

#ifndef ITS_H
#define ITS_H

#if defined(WIN32)
#pragma warning(disable:4274)
#endif

#ident "$Id: its.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

/*
 * we're moving to dynamic linking.  Of course on Windows this
 * can't be done in a sane manner, so we have to do this.  NOTE:
 * ALL FUTURE APIs WILL NEED THIS MODIFIER FOR EXPORTED FUNCTIONS.
 */
#if defined(WIN32)

#if defined(ITS_IMPLEMENTATION)
#define ITSDLLAPI __declspec(dllexport)
#else
#define ITSDLLAPI __declspec(dllimport)
#endif

/*
 * we want the stack framework in a DLL too.
 */
#if defined(SS7_IMPLEMENTATION)
#define SS7DLLAPI __declspec(dllexport)
#else
#define SS7DLLAPI __declspec(dllimport)
#endif

/*
 * we want our stack in a DLL too.
 */
#if defined(ITSSS7_IMPLEMENTATION)
#define ITSSS7DLLAPI __declspec(dllexport)
#else
#define ITSSS7DLLAPI __declspec(dllimport)
#endif

/*
 * finally, vendor libs need something unambiguous
 */
#if defined(VSS7_IMPLEMENTATION)
#define VSS7DLLAPI __declspec(dllexport)
#else
#define VSS7DLLAPI __declspec(dllimport)
#endif

#else  /* WIN32 */

#define ITSDLLAPI
#define SS7DLLAPI
#define ITSSS7DLLAPI
#define VSS7DLLAPI

#endif /* WIN32 */

/*
 * standard includes
 */
#include <its_types.h>
#include <its_consts.h>

/*.interface:ITS
 *****************************************************************************
 *  Interface:
 *      ITS_Initialize(), ITS_Terminate()
 *
 *  Purpose:
 *      This interface defines the common IntelliSS7 API functions.  These
 *      are the functions that the user calls for handling API events,
 *      regardless of protocol.  Note that this is true regardless of
 *      whether or not the protocol is being used in a multi-threaded
 *      environment.
 *
 *      In the C++ environment, these functions call methods based on the
 *      object/threading-model underlying the abstraction.  In the C
 *      environment (which currently doesn't fully support multithreading),
 *      the functions typically invoke transport functions directly, depending
 *      on the underlying transport.  See
 *      <A HREF=its_transport.html>ITS_Transport</A>
 *      for details.  NOTE: the use of the ITS_GetEvent(), ITS_PutEvent(),
 *      and ITS_PeekNextEvent() are not recommended for C++.  There are
 *      more efficient functions based on the underlying ITS_Transport objects
 *      that should be used instead.
 *
 *      Regardless of language, ITS_Initialize() and ITS_Terminate() should
 *      be invoked.  Most especially, when using the multithreaded library
 *      in combination with ITS_TRANSPORT_DELAY_CREATE, ITS_Initialize MUST be
 *      called to create the transport for that thread.
 *
 *  Usage:
 *      In general, the usage of the functions is as follows:
 *
 *      ----------------------------------------------------------
 *      ITS_HANDLE handle;
 *
 *       *
 *       * NOTE: When writing multithreaded code, there are ways to 
 *       * recover the mask and instance from objects or structures. *
 *       * When only one consumer of IntelliSS7 is used, the mask
 *       * should contain the flag ITS_TRANSPORT_SINGLE_USER.
 *       * When writing multithreaded code (code based on thread pools),
 *       * you should probably use the flag ITS_TRANSPORT_DELAY_CREATE
 *       * to delay creation of border transports until they call
 *       * ITS_Initialize() in their own thread; this has the effect
 *       * of blocking only the border transport's thread instead of
 *       * the whole process (while waiting for the remote end to
 *       * connect/connecting to the remote end).
 *       *
 *      handle = ITS_Initialize(mask, instance);
 *
 *      if (handle == NULL)
 *      {
 *           * perform FATAL error processing *
 *           * return; or exit(), depending on threading model *
 *      }
 *
 *      for (;;)
 *      {
 *          ITS_EVENT ev;  * For "C" *
 *          its::Event ev;  * For "C++" *
 *
 *           * When using "C" single user. *
 *          if (ITS_GetNextEvent(handle, &ev) != ITS_SUCCESS)
 *          {
 *               *
 *               * something very bad happened.  Act based on the return
 *               * code of ITS_GetNextEvent().
 *               *
 *          }
 *
 *           * For multithreaded "C" *
 *          if (ITS_GetNextEvent(handle, &ev) != ITS_SUCCESS)
 *          {
 *               *
 *               * something very bad happened.  Act based on the return
 *               * code of ITS_GetNextEvent().
 *               *
 *          }
 *
 *           * When using "C++" single user. *
 *          ITS_Transport* trans = ITS_HANDLE_TO_ITS_TRANSPORT(handle);
 *          if (trans->GetNextEvent(ev) != ITS_SUCCESS)
 *          {
 *               *
 *               * something bad happened.  Act based on the return
 *               * code of trans->GetNextEvent().
 *               *
 *          }
 *
 *           * When using "C++" multi threaded. Note that there are other
 *           * ways to recover the ITS_Worker* in this case. *
 *          ITS_Transport* trans = ITS_HANDLE_TO_ITS_TRANSPORT(handle);
 *          ITS_Worker* worker = ITS_Worker::FindWorker(trans->GetInstance());
 *          if (worker->GetNextEvent(ev) != ITS_SUCCESS)
 *          {
 *               *
 *               * something bad happened.  Act based on the return
 *               * code of trans->GetNextEvent().
 *               *
 *          }
 *      }
 *      -------------------------------------------------------
 *
 *      Note that for *some* fatal errors that may occur (such as out of
 *      memory errors), you should call ITS_Terminate(ITS_HANDLE h) to
 *      clean up before exiting.  However, you should NOT call this function
 *      when ITS_Initialize() does not succeed; in that case, the handle
 *      will be NULL, and any necessary cleanup will be performed by
 *      ITS_Initialize() before returning.
 *
 *      However, when processing is complete, or has been interrupted
 *      (due to SIGXXX or <Ctrl-Break> handling), the user should force
 *      calls to ITS_Terminate(), *especially* when using SS7 as a transport.
 *      Failure to do so will cause problems for less advanced SS7 transports
 *      (such as NMS).
 *
 *      Refer to its.h for further details and comments on the usages of
 *      this interface.
 *
 *****************************************************************************/

/*
 * initialization/event type flags
 */
#define ITS_FLAG_MTP2           (1<<0)
#define ITS_FLAG_MTP3           (1<<1)
#define ITS_FLAG_ISUP           (1<<2)
#define ITS_FLAG_SCCP           (1<<3)
#define ITS_FLAG_TUP            (1<<4)
#define ITS_FLAG_DUP            (1<<5)
#define ITS_FLAG_TCAP           (1<<6)
#define ITS_FLAG_ECI            (1<<7)
#define ITS_FLAG_ANSI           (1<<10)
#define ITS_FLAG_CCITT          (1<<11)
#define ITS_FLAG_PRC            (1<<12)
#define ITS_FLAG_TTC            (1<<13)

#define ITS_MTP2_ANSI           (ITS_FLAG_ANSI|ITS_FLAG_MTP2)
#define ITS_MTP3_ANSI           (ITS_FLAG_ANSI|ITS_FLAG_MTP3)
#define ITS_ISUP_ANSI           (ITS_FLAG_ANSI|ITS_FLAG_ISUP)
#define ITS_SCCP_ANSI           (ITS_FLAG_ANSI|ITS_FLAG_SCCP)
#define ITS_TUP_ANSI            (ITS_FLAG_ANSI|ITS_FLAG_TUP)
#define ITS_DUP_ANSI            (ITS_FLAG_ANSI|ITS_FLAG_DUP)
#define ITS_TCAP_ANSI           (ITS_FLAG_ANSI|ITS_FLAG_TCAP)
#define ITS_ECI_ANSI            (ITS_FLAG_ANSI|ITS_FLAG_TCAP)
#define ITS_MTP2_CCITT          (ITS_FLAG_CCITT|ITS_FLAG_MTP2)
#define ITS_MTP3_CCITT          (ITS_FLAG_CCITT|ITS_FLAG_MTP3)
#define ITS_ISUP_CCITT          (ITS_FLAG_CCITT|ITS_FLAG_ISUP)
#define ITS_SCCP_CCITT          (ITS_FLAG_CCITT|ITS_FLAG_SCCP)
#define ITS_TUP_CCITT           (ITS_FLAG_CCITT|ITS_FLAG_TUP)
#define ITS_DUP_CCITT           (ITS_FLAG_CCITT|ITS_FLAG_DUP)
#define ITS_TCAP_CCITT          (ITS_FLAG_CCITT|ITS_FLAG_TCAP)
#define ITS_ECI_CCITT           (ITS_FLAG_CCITT|ITS_FLAG_TCAP)
#define ITS_MTP2_PRC            (ITS_FLAG_PRC|ITS_FLAG_MTP2)
#define ITS_MTP3_PRC            (ITS_FLAG_PRC|ITS_FLAG_MTP3)
#define ITS_ISUP_PRC            (ITS_FLAG_PRC|ITS_FLAG_ISUP)
#define ITS_SCCP_PRC            (ITS_FLAG_PRC|ITS_FLAG_SCCP)
#define ITS_TUP_PRC             (ITS_FLAG_PRC|ITS_FLAG_TUP)
#define ITS_DUP_PRC             (ITS_FLAG_PRC|ITS_FLAG_DUP)
#define ITS_TCAP_PRC            (ITS_FLAG_PRC|ITS_FLAG_TCAP)
#define ITS_ECI_PRC             (ITS_FLAG_PRC|ITS_FLAG_TCAP)
#define ITS_MTP2_TTC            (ITS_FLAG_TTC|ITS_FLAG_MTP2)
#define ITS_MTP3_TTC            (ITS_FLAG_TTC|ITS_FLAG_MTP3)
#define ITS_ISUP_TTC            (ITS_FLAG_TTC|ITS_FLAG_ISUP)
#define ITS_SCCP_TTC            (ITS_FLAG_TTC|ITS_FLAG_SCCP)
#define ITS_TUP_TTC             (ITS_FLAG_TTC|ITS_FLAG_TUP)
#define ITS_DUP_TTC             (ITS_FLAG_TTC|ITS_FLAG_DUP)
#define ITS_TCAP_TTC            (ITS_FLAG_TTC|ITS_FLAG_TCAP)
#define ITS_ECI_TTC             (ITS_FLAG_TTC|ITS_FLAG_TCAP)


/*
 * these flags are left for user defined protocols.  Note
 * that they should NOT be passed into ITS_Initialize() as
 * IntelliSS7 will not recognize these as valid protocols
 * internally; however, the transport and routing mechanisms
 * will respect them as valid values.
 */
#define ITS_APP_PROTOCOL_1      (1<<14)
#define ITS_APP_PROTOCOL_2      (1<<15)
#define ITS_APP_PROTOCOL_3      ((1<<14)|(1<<15))

/*
 * some masking information.
 */
#define ITS_SS7_MASK        (0x00003CFFU)
#define ITS_SS7_MASK_ANSI   (0x000004FFU)
#define ITS_SS7_MASK_CCITT  (0x000008FFU)
#define ITS_SS7_MASK_PRC    (0x000010FFU)
#define ITS_SS7_MASK_TTC    (0x000020FFU)

#define ITS_GET_SS7_FLAGS(x) \
    ((x) & ITS_SS7_MASK)

/*
 * supported variants.  Global to avoid redefinition of
 * values everywhere.
 */
#define ITS_FIRST_GEN               1
#define ITS_SECOND_GEN              2
#define ITS_THIRD_GEN               3
#define ITS_FOURTH_GEN              4

#define ITS_LATEST_GEN              ITS_THIRD_GEN

/*
 * special flags for multithreading
 */
#define ITS_TRANSPORT_DELAY_CREATE  (1<<16)     /* used by threading */
#define ITS_TRANSPORT_SINGLE_USER   (1<<17)     /* don't use workers */
#define ITS_TRANSPORT_DONT_CLEAN    (1<<18)     /* don't clean up the timers
                                                 * or routing table when
                                                 * ITS_Terminate() is called. */
#define ITS_TRANSPORT_SSOCKET_ITER  (1<<19)     /* concurrent socket */
#define ITS_TRANSPORT_SSOCKET_DYN   (1<<20)     /* dynamic child of concurrent
                                                 * socket. */
#define ITS_TRANSPORT_DGRAM_VIRT    (1<<20)     /* overload this flag for datagram */

/* three bits reserved for socket protocol */
#define ITS_TRANSPORT_SOCKP_MASK    (0x07<<21)
#define ITS_TRANSPORT_DATA_SOCKET   (0<<21)     /* use IMAL protocol, no keepalives */
#define ITS_TRANSPORT_GDI_SOCKET    (1<<21)     /* use GDI protocol on this socket */
#define ITS_TRANSPORT_RUDP_SOCKET   (2<<21)     /* use RUDP protocol on this socket */
#define ITS_TRANSPORT_TALI_SOCKET   (3<<21)     /* use TALI protocol on this socket */
#define ITS_TRANSPORT_IMAL_SOCKET   (4<<21)     /* use IMAL protocol on this socket */
#define ITS_TRANSPORT_SCTP_SOCKET   (5<<21)     /* use SCTP protocol on this socket */
#define ITS_TRANSPORT_FLAGS_MASK    (0x00FF0000U)

#define ITS_GET_TRANSPORT_FLAGS(x) \
    ((x) & ITS_TRANSPORT_FLAGS_MASK)

/*
 * transport types
 */
#define ITS_TRANSPORT_SS7           (1<<24)
#define ITS_TRANSPORT_FIFO          (1<<25)
#define ITS_TRANSPORT_GFIFO         (1<<26)
#define ITS_TRANSPORT_CSOCKET       (1<<27)
#define ITS_TRANSPORT_SSOCKET       (1<<28)
#define ITS_TRANSPORT_TQUEUE        (1<<29)
#define ITS_TRANSPORT_DATAGRAM      (1<<30)
/*
 * one bit left for a new transport major.  When
 * that bit is exhausted this field will have to
 * move to a value shifted 24.
 */

#define ITS_TRANSPORT_TYPE_MASK     (0xFF000000U)

#define ITS_GET_TRANSPORT_TYPE(x) \
    ((x) & ITS_TRANSPORT_TYPE_MASK)

/*
 * A few notes about what "instance" means.  Instance identifies
 * the particular transport that a task controls/is associated
 * with.  We used to define ITS_TCAP/ITS_SCCP etc. as sources,
 * but that is no longer appropriate.  Rather, the masks above
 * indicate what *kind* of transport should be built and used
 * for "self" messages, while the instance (must) uniquely
 * identify the transport, so that others can send messages to
 * us.
 *
 * There are a few caveats to this, though.  So called "dispatcher"
 * or "border" transports are half-entities.  That is, transports
 * that are not task queues (task queues are the only sort of process
 * internal, or non-border transports) cannot have process local
 * messages sent to them;  when you perform a "PutEvent" on border
 * transports, you are in reality sending that event across process
 * boundaries.
 *
 * Two sources are non-existent: source 0 (which indicates no such
 * source exists) and source 0xFFFF (which indicates an attempt to
 * send to a bad source).
 */

/*
 * predefined instances
 */
#define ITS_FIRST_USER_SRC          (0x0001U)
#define ITS_LAST_USER_SRC           (0x7FFFU)
#define ITS_DEFAULT_USER_SRC        ITS_FIRST_USER_SRC

#define ITS_NO_SRC                  (0x0000U)
#define ITS_INVALID_SRC             (0xFFFFU)

#define ITS_TIMER_SRC               (0xFFFEU)
#define ITS_TCAP_ANSI_SRC           (0xFFFDU)
#define ITS_TCAP_CCITT_SRC          (0xFFFCU)
#define ITS_SCCP_ANSI_SRC           (0xFFFBU)
#define ITS_SCCP_CCITT_SRC          (0xFFFAU)
#define ITS_ISUP_ANSI_SRC           (0xFFF9U)
#define ITS_ISUP_CCITT_SRC          (0xFFF8U)
#define ITS_MTP3_ANSI_SRC           (0xFFF7U)
#define ITS_MTP3_CCITT_SRC          (0xFFF6U)
#define ITS_MTP2_ANSI_SRC           (0xFFF5U)
#define ITS_MTP2_CCITT_SRC          (0xFFF4U)
#define ITS_TCAP_PRC_SRC            (0xFFF3U)
#define ITS_SCCP_PRC_SRC            (0xFFF2U)
#define ITS_ISUP_PRC_SRC            (0xFFF1U)
#define ITS_MTP3_PRC_SRC            (0xFFF0U)
#define ITS_MTP2_PRC_SRC            (0xFFEFU)
#define ITS_TCAP_TTC_SRC            (0xFFEEU)
#define ITS_SCCP_TTC_SRC            (0xFFEDU)
#define ITS_ISUP_TTC_SRC            (0xFFECU)
#define ITS_MTP3_TTC_SRC            (0xFFEBU)
#define ITS_MTP2_TTC_SRC            (0xFFEAU)
#define ITS_GCS_EVENT_FROM_STACK    (0xFFE9U)
#define ITS_GCS_EVENT_FROM_APPL     (0xFFE8U)
#define ITS_GCS_EVENT_TO_NETWORK    (0xFFE7U)
#define ITS_SCCP_LOCAL_REF_REQUEST  (0xFFE6U)
#define ITS_SCCP_LOCAL_REF_RESPONSE (0xFFE5U)
#define ITS_M2UA_SRC                (0xFFE4U)
#define ITS_SIP_SRC                 (0xFFE3U)
#define ITS_MAB_SRC                 (0xFFE2U)
#define ITS_BSSAP_SRC               (0xFFE1U)
#define ITS_GCS_EVENT_FROM_APPL_CL3I (0xFFE0U)

/* SINGLETONS */

/*
 * keepalive transport tick.
 */
#define ITS_KEEPALIVE_INSTANCE      (0xFE00U)

/*
 * RUDP manager instance
 */
#define RUDP_MANAGER_INSTANCE       (0xFE01U)
#define RUDP_SOURCE_INSTANCE        (0xFE02U)

/*
 * UAL
 */
#define UAL_MANAGER_INSTANCE        (0xFE03U)

/*
 * SRCs for vendors
 */
#define VMI_ASYNCHRONOUS_SRC        (0xFE04U)
#define VMI_SYNCHRONOUS_SRC         (0xFE05U)

/*
 * alarm and health
 */
#define ALARM_MANAGER_INSTANCE      (0xFE06U)
#define HEALTH_MANAGER_INSTANCE     (0xFE07U)

/*
 * M2PA (may merge with UAL)
 */
#define M2PA_MANAGER_INSTANCE       (0xFE08U)

/* RANGES */

/*
 * SCTP manager instance
 */
#define SCTP_MANAGER_INSTANCE       (0xFD01U)
#define SCTP_FIRST_USER             (0xFD02U)
#define SCTP_LAST_USER              (0xFDFFU)

/*
 * dynamic SCTP transport instances
 */
#define SCTPTRAN_FIRST_SRC          (0xFC00U)
#define SCTPTRAN_LAST_SRC           (0xFCFFU)

/*
 * UAL pending queues
 */
#define UAL_PENDING_FIRST_SRC       (0xFB00U)
#define UAL_PENDING_LAST_SRC        (0xFBFFU)

/*
 * Application defined protocols
 */
#define ITS_FIRST_APP_PROTOCOL_SRC  (0xF000U)
#define ITS_LAST_APP_PROTOCOL_SRC   (0xF0FFU)

/*
 * error codes
 */
#define ITS_SUCCESS                     0
#define ITS_ENOMEM                     -1
#define ITS_EIESNULL                   -2
#define ITS_EISUPMSGTOOBIG             -3
#define ITS_EISUPMSGSENDFAIL           -4
#define ITS_ENOPROXY                   -5
#define ITS_ERCVFAIL                   -6
#define ITS_EGETATTRFAIL               -7
#define ITS_ENOMSG                     -8
#define ITS_ESENDFAIL                  -9
#define ITS_ENOQUEUE                   -10
#define ITS_ENOMSGSPACE                -11
#define ITS_EMISSMAND                  -12
#define ITS_ETCAPMSGSENDFAIL           -13
#define ITS_ESCCPMSGSENDFAIL           -14
#define ITS_PIKAERR                    -15
#define ITS_BADTCAPMESSAGE             -16
#define ITS_BADISUPMESSAGE             -17
#define ITS_ETOOMANYDIALOGS            -18
#define ITS_EINVALIDSRC                -19
#define ITS_ENOINVID                   -20
#define ITS_ENOEVENT                   -21
#define ITS_EINDICNOTENABLED           -22
#define ITS_ENOSYNCHVAR                -23
#define ITS_ENOMUTEX                   -24
#define ITS_EBADMUTEX                  -25
#define ITS_ENOSEMAPHORE               -26
#define ITS_EBADSEMAPHORE              -27
#define ITS_ENOLIST                    -28
#define ITS_ENOTHREAD                  -29
#define ITS_ELISTNOTUNIQUE             -30
#define ITS_EENDOFLIST                 -31
#define ITS_ELISTPUTERR                -32
#define ITS_EBADTHREAD                 -33
#define ITS_EBADFIFO                   -34
#define ITS_ENOFIFO                    -35
#define ITS_ENOSOCKET                  -36
#define ITS_EBADHOST                   -37
#define ITS_EBADSOCKET                 -38
#define ITS_EINVALIDARGS               -39
#define ITS_EBINDFAIL                  -40
#define ITS_ELISTENFAIL                -41
#define ITS_ECONNECTFAIL               -42
#define ITS_EBADFIFOMODE               -43
#define ITS_ENOTRANSPORT               -44
#define ITS_ENOLICENSE                 -45
#define ITS_EPROTERR                   -46
#define ITS_ENOROUTE                   -47
#define ITS_EROUTEFAIL                 -48
#define ITS_EOVERFLOW                  -49
#define ITS_EWOULDBLOCK                -50
#define ITS_EBADTRANSPORT              -51
#define ITS_EINITFAIL                  -52
#define ITS_ENOCONN                    -53
#define ITS_EMISSINGRES                -54
#define ITS_EINUSE                     -55
#define ITS_EDESTPROHIBIT              -56
#define ITS_EINVPTYPE                  -57
#define ITS_EINVOPFAM                  -58
#define ITS_EINVOPSPEC                 -59
#define ITS_EINVLEN                    -60
#define ITS_ENULLPTR                   -61
#define ITS_EPARAMPRSNT                -62
#define ITS_EINVCHOICE                 -63
#define ITS_EBADSTATE                  -64
#define ITS_ENOTFOUND                  -65
#define ITS_EASNENCODE                 -66
#define ITS_EASNDECODE                 -67 
#define ITS_EBADCONDVAR                -68
#define ITS_EBADRWLOCK                 -69
#define ITS_EBADCHKSUM                 -70
#define ITS_ETIMEOUT                   -71
#define ITS_EINVOPC                    -72
#define ITS_EINVDPC                    -73
#define ITS_ECICBUSY                   -74
#define ITS_ECICBLOCK                  -75 
#define ITS_ENOTCONFIG                 -76
#define ITS_ENOTCONTRLD                -77
#define ITS_ETIMERSTARTFAIL            -78
#define ITS_EINVCIC                    -79
#define ITS_ENOADDRESS                 -80
#define ITS_EINVISUPMSGTYPE            -81
#define ITS_EINVCONFIG                 -82
#define ITS_EINVNODE                   -83
#define ITS_EINVPROCESS                -84
#define ITS_EINVFTGROUP                -85
#define ITS_EINVINITSTATE              -86
#define ITS_EINVDSMTYPE                -87
#define ITS_EINVFTGROUPMEMBERS         -88
#define ITS_EINVMASTERFTGROUPMEMBERS   -89
#define ITS_EPREINITFAIL               -90
#define ITS_EMISSINGIMPL               -91
#define ITS_EIMPLINITFAIL              -92
#define ITS_EROWNOTLOCKED              -93
#define ITS_EINVTABLE                  -94
#define ITS_EINVJOINSTATE              -95
#define ITS_EINVSYNCSTATE              -96
#define ITS_EGCSMULTICASTFAIL          -97
#define ITS_EGCSJOINFAIL               -98
#define ITS_EGCSLEAVEFAIL              -99
#define ITS_EGCSCONNECTFAIL            -100
#define ITS_EGCSDISCONNECTFAIL         -101
#define ITS_EGCSEVENTINITFAIL          -102
#define ITS_EGCSEVENTQUEUEFAIL         -103
#define ITS_EGCSRECEIVEFAIL            -104
#define ITS_EGCSEVENTATTACHFDFAIL      -105
#define ITS_ENOREMOTE                  -106
#define ITS_ENOVALIDMASTER             -107
#define ITS_ECALLREJECTED              -108
#define ITS_EBADMEMFREE                -109
#define ITS_EDUPLENTRY                 -110
#define ITS_ENODESTINATION             -111
#define ITS_EINVXCHANGE                -112
#define ITS_ENOFEATURE                 -113
#define ITS_EINVVARIANT                -114
#define ITS_EINVARGSLEN                -115
#define ITS_EMISSINGMANDPRM            -116
#define ITS_EMISSINGMANDHDR            -117
#define ITS_ELINKNOTFOUND              -118
#define ITS_ELINKSETNOTFOUND           -119
#define ITS_ELINKSEXIST                -120

/* always last */
#define ITS_EINVALIDERR                -121
#define ITS_MAX_ERROR                  (-(ITS_EINVALIDERR))

/* Only for the user.... */
#ifndef __KERNEL__

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * errno to text
 */
ITSDLLAPI char* ITS_GetErrorText(int err_num);

/*
 * global initialization
 */
ITSDLLAPI int ITS_GlobalStart(ITS_UINT mask);
ITSDLLAPI void ITS_GlobalStop();

ITSDLLAPI ITS_UINT ITS_VerifyMask(ITS_UINT mask);

/*
 * transport setup/teardown
 */
ITSDLLAPI ITS_HANDLE ITS_Initialize(ITS_UINT mask, ITS_USHORT instance);
ITSDLLAPI void ITS_Terminate(ITS_HANDLE handle);

/*
 * event processing interface
 */
ITSDLLAPI int ITS_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *event);
ITSDLLAPI int ITS_PeekNextEvent(ITS_HANDLE handle, ITS_EVENT *event);
ITSDLLAPI int ITS_PutEvent(ITS_HANDLE handle, ITS_EVENT *event);

#if defined(__cplusplus)
}
#endif

/*
 * doesn't matter that this is last, just surprising.  We
 * need FASTCALL defined, but we also want to always have
 * the MEMPOOL interface exposed.
 */
#include <its_mem_pool.h>

#endif /* no kernel */

/*
 * if the user does not set the value via APPL_SetConfigDir(), we'll
 * try to pull it out of this environment variable.  Don't forget the
 * trailing path separator if you set this variable.
 */
#define INTELLISS7_CONFIG_DIR_VAR       "ISS7_CONFIG_DIR"

/*
 * if the user does not set the value for the trace directory, we will
 * by default use the current working directory.  Don't forget the
 * trailing path separator if you set this variable.
 */
#define INTELLISS7_TRACE_DIR_VAR        "ISS7_TRACE_DIR"

/*
 * where libraries should be looked for.  By default, the current working
 * directory.  Don't forget the trailing path separator if you set this
 * variable.
 */
#define INTELLISS7_LIB_DIR_VAR          "ISS7_LIB_DIR"

/*
 * if multiple single-user style transports are created
 * (via ITS_Initialize()), it is useful for them to have
 * different names (so that they can have separate sections
 * in the INI file).  Thus this format string.  It is
 * included here as documentation for INI file writers.
 */
#define ITS_UNNAMED_TRANSPORT_FORMAT_STRING     "Default-Transport%d"

/*
 * The file name format for INI files.  This MUST be followed
 * to successfully format the name of an INI file.  The
 * relevant code is:
 *  sprintf(buf, ITS_INI_FILE_NAME_FORMAT,
 *          APPL_GetConfigDir(), APPL_GetName(),
 *          APPL_GetConfigFileExtension());
 * Note that the user must check to see that APPL_GetConfigDir()
 * and APPL_GetName() do NOT return NULL.  If APPL_GetName()
 * returns NULL, a fatal application error has occurred.
 * If APPL_GetConfigDir() returns NULL, the user can substitute
 * the empty string ("") for APPL_GetConfigDir().
 * If APPL_GetConfigFileExtension() returns NULL, the ALT format
 * string will be used.
 * If APPL_SetConfigDir() is not called, APPL_GetConfigDir() will
 * search the environment for the current setting of
 * "ITS_ISS7_CONFIG_DIR_VAR" (see above).
 */
#define ITS_INI_FILE_NAME_FORMAT_STRING         "%s%s.%s"
#define ITS_ALT_INI_FILE_NAME_FORMAT_STRING     "%s%s"

/*
 * the file name format for trace files.  This must be followed to
 * successfully format the name of a trace file.
 * The relevant code is as follows:
 *  sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
 *          env, (char *)tom->data,
 *          tom->curday % ITS_NUM_TRACE_FILES);
 * The variable "env" will either be the value of APPL_GetTraceDir()
 * (if not null), or "" (the empty string).  tom->data normally has
 * the trace file name when the output is initialized.
 * If the user does not call APPL_SetTraceDir(), the environment will
 * be searched for "INTELLISS7_TRACE_DIR_VAR" (see above).
 */
#define ITS_TRACE_FILE_NAME_FORMAT_STRING       "%s%s%ld"

/*
 * force the fastcall interface (avoid extra function calls).
 * This is for performance reasons and makes a substantial
 * difference.
 */
#define ITS_FASTCALL    ITS_TRUE


 /*
  * Finish up with a couple of macros for event init and
  * destroy.  These should always be used to avoid leaks.
  * Note that the C++ event doesn't need these.
  */
#define ITS_EVENT_INIT(e, s, l)                             \
    do                                                      \
    {                                                       \
        (e)->src = (s);                                     \
        (e)->len = (l);                                     \
        if ((l))                                            \
        {                                                   \
            (e)->data = (ITS_OCTET *)ITS_Malloc((e)->len);  \
            if ((e)->data == NULL)                          \
            {                                               \
                abort();                                    \
            }                                               \
        }                                                   \
        else                                                \
        {                                                   \
            (e)->data = NULL;                               \
        }                                                   \
    }                                                       \
    while (0)

#define ITS_EVENT_TERM(e)                                   \
    do                                                      \
    {                                                       \
        if ((e)->data)                                      \
        {                                                   \
            ITS_Free((e)->data);                            \
            (e)->data = NULL;                               \
        }                                                   \
    }                                                       \
    while (0)

#endif /* ITS_ITS_H */
