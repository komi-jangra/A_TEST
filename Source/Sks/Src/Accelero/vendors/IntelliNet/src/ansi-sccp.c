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
 ****************************************************************************
 *
 *  ID: $Id: ansi-sccp.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:30  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/30 11:33:02  adutta
 * LOG: XUDT implementation in ANSI
 * LOG:
 * LOG: Revision 9.3  2005/05/06 13:35:36  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix. (1804, 1798, 1781, 1784, 1749, 1801,
 * LOG: 1802, 1803).
 * LOG:
 * LOG: Revision 9.2  2005/05/06 09:48:01  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1783, 1778) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:32  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.11  2005/02/25 13:12:20  mmanikandan
 * LOG: XML Persistency bugs fixing.
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.10  2005/02/21 08:54:11  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.9  2005/02/03 08:45:29  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.8  2005/01/31 11:00:02  snagesh
 * LOG: SCCP OSS APIs added
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.7  2005/01/25 07:17:40  csireesh
 * LOG: Validation bug fix and removed Tab spaces
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.6  2005/01/05 12:40:21  craghavendra
 * LOG: Update the Console Functions for Syslog.
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.5  2005/01/05 10:47:12  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.4  2005/01/05 09:53:19  csireesh
 * LOG: Removed unwanted alarm
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.3  2005/01/04 13:43:55  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.2  2004/12/30 07:48:52  csireesh
 * LOG: Bug 1296: Core dump while printing the raw bytes (manikandan)
 * LOG:
 * LOG: Revision 7.8.2.1.4.13.2.1  2004/12/29 13:27:37  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.1.4.13  2004/11/30 12:00:29  sjaddu
 * LOG: redundancy Declaration moved up.
 * LOG:
 * LOG: Revision 7.8.2.1.4.12  2004/11/25 16:43:45  sjaddu
 * LOG: Backup node will not allow to go msgs out.
 * LOG:
 * LOG: Revision 7.8.2.1.4.11  2004/11/22 12:45:35  yranade
 * LOG: Printing Hex Dumps change done by Abhijit.
 * LOG:
 * LOG: Revision 7.8.2.1.4.10  2004/09/15 05:53:23  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.8.2.1.4.9  2004/09/13 07:19:17  csireesh
 * LOG: Bug Fix:1107,1147,1148
 * LOG:
 * LOG: Revision 7.8.2.1.4.8  2004/09/02 11:53:28  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.8.2.1.4.7  2004/08/25 11:03:07  mmanikandan
 * LOG: Adding different concerned route for same SSN.
 * LOG:
 * LOG: Revision 7.8.2.1.4.6  2004/07/26 06:14:00  sswami
 * LOG: Hex dump traces enabled for SCCP, MTP
 * LOG:
 * LOG: Revision 7.8.2.1.4.5  2004/07/06 10:41:44  csireesh
 * LOG: MML Commands Updated
 * LOG:
 * LOG: Revision 7.8.2.1.4.4  2004/06/23 11:54:42  csireesh
 * LOG: PEGS UPDATED.
 * LOG:
 * LOG: Revision 7.8.2.1.4.3  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.8.2.1.4.2  2004/02/12 08:42:09  mmanikandan
 * LOG: Redundancy Implementation.
 * LOG:
 * LOG: Revision 7.8.2.1.4.1  2004/01/27 05:45:21  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.8.2.1  2003/09/18 11:13:42  aganguly
 * LOG: fix for SCCP-CO bugs
 * LOG:
 * LOG: Revision 7.8  2003/02/03 11:09:05  aganguly
 * LOG: Alarms rework after code review
 * LOG:
 * LOG: Revision 7.7  2003/02/03 06:45:30  aganguly
 * LOG: Changes for SCCP Alarms: cleanup of unwanted alarms still left - to be done in 6.4
 * LOG:
 * LOG: Revision 7.6  2003/01/20 20:10:47  ngoel
 * LOG: rename ssn state define to avoid conflict
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.4  2002/12/26 22:53:53  ngoel
 * LOG: add mml control for each trace level
 * LOG:
 * LOG: Revision 7.3  2002/12/03 16:02:02  ngoel
 * LOG: remove print ssn state for concerned route in mml
 * LOG:
 * LOG: Revision 7.2  2002/11/09 21:54:19  randresol
 * LOG: Add ROUTE Reader/Writer Lock for MTP3 Optimization
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.43  2002/08/26 21:22:07  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.42  2002/08/26 13:19:42  ngoel
 * LOG: last minute correction
 * LOG:
 * LOG: Revision 6.41  2002/08/25 23:10:41  ngoel
 * LOG: add mml error handling
 * LOG:
 * LOG: Revision 6.40  2002/08/15 20:26:11  mmiers
 * LOG: Warning/error removal
 * LOG:
 * LOG: Revision 6.39  2002/08/04 18:28:08  ngoel
 * LOG: take peg type as string
 * LOG:
 * LOG: Revision 6.38  2002/07/26 19:43:20  ngoel
 * LOG: add linkset for get_all_ss and get_all_pc commands
 * LOG:
 * LOG: Revision 6.37  2002/07/25 21:47:56  ngoel
 * LOG: remove warning
 * LOG:
 * LOG: Revision 6.36  2002/07/25 12:57:40  ngoel
 * LOG: Add clear all pegs command
 * LOG:
 * LOG: Revision 6.35  2002/07/17 21:54:28  ngoel
 * LOG: add MML code for Get/Set Timers
 * LOG:
 * LOG: Revision 6.34  2002/07/17 15:24:29  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 6.33  2002/07/15 15:03:00  ngoel
 * LOG: remove warnings
 * LOG:
 * LOG: Revision 6.32  2002/07/09 18:25:00  mmiers
 * LOG: Finish removing warnings.
 * LOG:
 * LOG: Revision 6.31  2002/07/09 17:07:04  ngoel
 * LOG: remove warnings
 * LOG:
 * LOG: Revision 6.30  2002/07/08 01:03:53  ngoel
 * LOG: add MML code
 * LOG:
 * LOG: Revision 6.29  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.28  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.27  2002/06/13 18:27:52  mmiers
 * LOG: Change IsSSNAllowed to return true if we don't maintain
 * LOG: status for that SSN.  This will surely bite me later
 * LOG: when people complain about SCMG...
 * LOG:
 * LOG: Revision 6.26  2002/06/05 15:48:48  mmiers
 * LOG: More SCMG work
 * LOG:
 * LOG: Revision 6.25  2002/06/04 20:34:42  hxing
 * LOG: More mgmt debugging
 * LOG:
 * LOG: Revision 6.24  2002/06/04 16:53:38  hxing
 * LOG: Fix some management bugs.  Not completely done
 * LOG:
 * LOG: Revision 6.23  2002/06/03 17:08:47  mmiers
 * LOG: Get CPC
 * LOG:
 * LOG: Revision 6.22  2002/06/03 16:43:50  mmiers
 * LOG: NI fixes, Concerned fixes.
 * LOG:
 * LOG: Revision 6.21  2002/05/28 21:23:00  mmiers
 * LOG: Only look for the right PF
 * LOG:
 * LOG: Revision 6.20  2002/05/28 19:04:04  hxing
 * LOG: Take the ent address after allocation.
 * LOG:
 * LOG: Revision 6.19  2002/05/20 21:11:50  mmiers
 * LOG: Flip PCs.  Add OAM implementation.  Try chaining fix.
 * LOG:
 * LOG: Revision 6.18  2002/05/13 18:21:48  mmiers
 * LOG: Switch PC order.  Normalize SCCP mgmt API
 * LOG:
 * LOG: Revision 6.17  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.16  2002/05/07 16:29:10  mmiers
 * LOG: Names
 * LOG:
 * LOG: Revision 6.15  2002/05/07 15:44:04  wweng
 * LOG: Rename init/term functions for collision avoidance
 * LOG:
 * LOG: Revision 6.14  2002/05/06 20:11:17  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.13  2002/05/03 19:57:55  hxing
 * LOG: Modify SCCP Mgmt function signatures.
 * LOG:
 * LOG: Revision 6.12  2002/04/29 16:40:12  mmiers
 * LOG: Finish off pass 1 of the mgmt API
 * LOG:
 * LOG: Revision 6.11  2002/04/29 15:42:29  mmiers
 * LOG: Add SCCP management class records
 * LOG:
 * LOG: Revision 6.10  2002/04/24 15:55:37  mmiers
 * LOG: Add SCCP management interface.
 * LOG:
 * LOG: Revision 6.9  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.8  2002/04/03 23:24:51  mmiers
 * LOG: SCMG timers in DSM
 * LOG:
 * LOG: Revision 6.7  2002/03/27 22:05:46  mmiers
 * LOG: Put SST/SSP/SSA into DSM properly.  TODO: put the serials
 * LOG: in DSM as well.
 * LOG:
 * LOG: Revision 6.6  2002/03/21 20:58:09  mmiers
 * LOG: Add CPC API, rework CPC lists so that they may actually
 * LOG: function.
 * LOG:
 * LOG: Revision 6.5  2002/03/14 22:52:31  mmiers
 * LOG: Convert TCAP and SCCP to OAM
 * LOG:
 * LOG: Revision 6.4  2002/03/11 20:59:46  mmiers
 * LOG: It builds.  Now for the hard part.
 * LOG:
 * LOG: Revision 6.3  2002/03/08 21:31:27  mmiers
 * LOG: Formatting complete.  TODO: CPC lists.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 22:21:30  mmiers
 * LOG: Merge ITU SCCP.  Doesn't build (have to work on CPC impl).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.16  2002/02/08 21:48:15  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.15  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.14  2001/12/19 18:03:02  mmiers
 * LOG: Adax testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 5.13  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.12  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.11  2001/11/09 20:19:54  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.10  2001/10/01 20:12:42  mmiers
 * LOG: struct rename
 * LOG:
 * LOG: Revision 5.9  2001/09/26 00:31:03  mmiers
 * LOG: Remove a couple of warnings and fixmes
 * LOG:
 * LOG: Revision 5.8  2001/09/25 21:35:20  mmiers
 * LOG: Fix up SCCP routing and SCMG.
 * LOG:
 * LOG: Revision 5.7  2001/09/25 01:03:24  mmiers
 * LOG: Notes on concerned and duplicate routes.
 * LOG:
 * LOG: Revision 5.6  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.5  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
 * LOG:
 * LOG: Revision 5.4  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.3  2001/08/28 21:11:15  mmiers
 * LOG: Watch the arg lists.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:26  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/08/07 19:11:44  mmiers
 * LOG: Add MTP3 threads.  Also a little cleanup.
 * LOG:
 * LOG: Revision 4.5  2001/07/10 15:24:08  mmiers
 * LOG: Make sure we aren't exceeding the modified timer context size.
 * LOG:
 * LOG: Revision 4.4  2001/06/20 19:18:38  mmiers
 * LOG: Make the stack participate in HMI
 * LOG:
 * LOG: Revision 4.3  2001/05/15 20:26:20  mmiers
 * LOG: Don't add routes for every ref.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:53:58  mmiers
 * LOG: Add user intervention callbacks.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:02  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.12  2001/04/18 22:34:25  mmiers
 * LOG: Fix zero copy bug.
 * LOG:
 * LOG: Revision 3.11  2001/04/04 15:29:17  mmiers
 * LOG: Remove extraneous traces.
 * LOG:
 * LOG: Revision 3.10  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.9  2001/02/06 17:11:48  mmiers
 * LOG: Multithreaded stack layers are there.  Locking needs to be added
 * LOG: to the context structures.
 * LOG:
 * LOG: Revision 3.8  2000/11/14 00:18:19  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.8  2000/10/20 22:23:13  omayor
 * LOG: Add SOR, SOG SCMG procedure for duplicate SSN. Also LUDT, LUDTS
 * LOG: procedures for ITU SCCP
 * LOG:
 * LOG: Revision 3.7  2000/10/05 23:04:32  mmiers
 * LOG: Go back to the old way for now.
 * LOG:
 * LOG: Revision 3.6  2000/09/25 20:09:46  mmiers
 * LOG: Finish off the route conversion code.
 * LOG:
 * LOG: Revision 3.5  2000/09/25 18:36:38  mmiers
 * LOG: Fix typos.
 * LOG:
 * LOG: Revision 3.4  2000/09/25 18:31:47  mmiers
 * LOG: Set up for the new routing table.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:56:48  mmiers
 * LOG:
 * LOG:
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 22:33:42  mmiers
 * LOG: Prepare for reentrant SCCP, TCAP, and ISUP warning removal.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.8  2000/03/29 18:27:48  mmiers
 * LOG:
 * LOG:
 * LOG: Don't trace for non-errors before trace settings have been established.
 * LOG:
 * LOG: Revision 2.7  2000/02/12 00:41:15  mmiers
 * LOG:
 * LOG: Convert vendor to new CORE code.
 * LOG:
 * LOG: Revision 2.6  2000/01/26 03:05:45  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.5  2000/01/21 23:31:04  mmiers
 * LOG:
 * LOG: Tweak for semantic correctness.
 * LOG:
 * LOG: Revision 2.4  2000/01/21 22:49:54  mmiers
 * LOG:
 * LOG: Use separate up/allowed functions.
 * LOG:
 * LOG: Revision 2.3  1999/12/18 00:21:07  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.2  1999/12/10 23:45:09  mmiers
 * LOG:
 * LOG:
 * LOG: Convert the callback object.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:07  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.10.2.1  1999/12/06 21:27:25  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.10  1999/10/25 20:24:48  mmiers
 * LOG:
 * LOG:
 * LOG: Corrections for the new transport class.
 * LOG:
 * LOG: Revision 1.9  1999/10/01 14:48:30  mmiers
 * LOG:
 * LOG:
 * LOG: Remove "fileValid" check.  This looks "under the hood" inside
 * LOG: the resource database mechanism and cannot be relied on.
 * LOG:
 * LOG: Revision 1.8  1999/08/26 23:44:53  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.7  1999/08/26 20:34:00  mmiers
 * LOG:
 * LOG:
 * LOG: Fix warnings.
 * LOG:
 * LOG: Revision 1.6  1999/08/26 15:24:12  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.5  1999/08/11 23:08:43  mmiers
 * LOG:
 * LOG:
 * LOG: Trace tweak again.
 * LOG:
 * LOG: Revision 1.4  1999/08/11 19:04:42  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for new trace structures.
 * LOG:
 * LOG: Revision 1.3  1999/06/22 16:17:24  mmiers
 * LOG:
 * LOG:
 * LOG: Add in global title translation.
 * LOG:
 * LOG: Revision 1.2  1999/03/24 22:46:34  mmiers
 * LOG:
 * LOG:
 * LOG: Clean up the SST queue when terminating.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:41  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.66  1999/03/17 15:09:24  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.65  1999/03/12 21:25:44  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitized build.
 * LOG:
 * LOG: Revision 1.64  1999/02/26 04:10:21  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.63  1999/02/09 21:46:39  mmiers
 * LOG:
 * LOG:
 * LOG: Use standard thread return type and exit macros.
 * LOG:
 * LOG: Revision 1.62  1998/11/19 01:31:43  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.61  1998/11/17 22:37:38  mmiers
 * LOG: Propagate SCMG (SSP/SSA)
 * LOG:
 * LOG: Revision 1.60  1998/11/13 17:05:41  mmiers
 * LOG: Fix bad timer message.
 * LOG:
 * LOG: Revision 1.59  1998/11/13 15:11:01  mmiers
 * LOG: Clean up some overnight changes.
 * LOG:
 * LOG: Revision 1.58  1998/11/13 02:49:41  mmiers
 * LOG: Do SST.
 * LOG:
 * LOG: Revision 1.57  1998/11/12 03:16:56  mmiers
 * LOG: Start adding SST timer into SCCP.
 * LOG:
 * LOG: Revision 1.56  1998/11/12 00:09:38  mmiers
 * LOG: Debug SSP/SSA.
 * LOG:
 * LOG: Revision 1.55  1998/11/11 03:47:26  mmiers
 * LOG: Clean up some SCCP stuff.
 * LOG:
 * LOG: Revision 1.54  1998/11/11 03:23:52  mmiers
 * LOG: Finish up SCMG.  Still need SST, but that is lower priority.
 * LOG:
 * LOG: Revision 1.53  1998/11/11 00:45:29  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.52  1998/11/10 16:10:11  mmiers
 * LOG: More work on SCMG.
 * LOG:
 * LOG: Revision 1.51  1998/11/10 03:26:36  mmiers
 * LOG: Update/include the string defines.
 * LOG:
 * LOG: Revision 1.50  1998/11/10 02:23:01  mmiers
 * LOG: Fix IT timers, rework stack-sent messages, add guard timer, add
 * LOG: behavior control.
 * LOG:
 * LOG: Revision 1.49  1998/11/09 23:30:23  mmiers
 * LOG: Put in intermediate node code.
 * LOG:
 * LOG: Revision 1.48  1998/11/04 20:13:37  mmiers
 * LOG: Work on pause/resume/status.
 * LOG:
 * LOG: Revision 1.47  1998/11/04 19:00:36  mmiers
 * LOG: Register the pause/resume/status callbacks.
 * LOG:
 * LOG: Revision 1.46  1998/11/04 15:22:21  mmiers
 * LOG: Prep for MTP-PAUSE/RESUME.
 * LOG:
 * LOG: Revision 1.45  1998/11/03 03:04:47  mmiers
 * LOG: Only set started flag after complete initialization.
 * LOG:
 * LOG: Revision 1.44  1998/10/23 00:01:28  whu
 * LOG: Fix debugging flags in INI files.
 * LOG: Fix recently introduced bug in SCCP with connection references.
 * LOG:
 * LOG: Revision 1.43  1998/10/22 22:35:25  whu
 * LOG: Be less agressive about reusing connection numbers.  Wait until
 * LOG: we've processed 64K connections before reusing them.
 * LOG:
 * LOG: Revision 1.42  1998/10/20 01:40:23  mmiers
 * LOG: include all SCCP timers.  More work on inactivity test.  Thinking
 * LOG: about SCMG.
 * LOG:
 * LOG: Revision 1.41  1998/10/19 00:40:36  mmiers
 * LOG: Strengthen for PCLASS_3
 * LOG:
 * LOG: Revision 1.40  1998/10/16 23:10:26  mmiers
 * LOG: Get the timers from the INI file.
 * LOG:
 * LOG: Revision 1.39  1998/10/16 20:45:21  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.38  1998/10/15 03:39:29  mmiers
 * LOG: Get the names right (source), make sure GTT is present (Makefile).
 * LOG:
 * LOG: Revision 1.37  1998/10/15 01:45:03  mmiers
 * LOG: Add -D_REENTRANT for alpha.  Add connRef to SCCP_CONN_CTXT.
 * LOG:
 * LOG: Revision 1.36  1998/10/15 01:20:49  mmiers
 * LOG: Oops, add global timer defaults.
 * LOG:
 * LOG: Revision 1.35  1998/10/15 01:19:12  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.34  1998/10/14 23:29:36  mmiers
 * LOG: Set trace levels from INI file.
 * LOG:
 * LOG: Revision 1.33  1998/09/30 14:22:44  mmiers
 * LOG: Fix some overnight bugs from home.
 * LOG:
 * LOG: Revision 1.32  1998/09/30 02:40:59  mmiers
 * LOG: Compromise on what we can do with SCCP.
 * LOG:
 * LOG: Revision 1.31  1998/09/29 20:40:14  mmiers
 * LOG: Temporary update for MTP3 changes.
 * LOG:
 * LOG: Revision 1.30  1998/09/29 17:33:05  mmiers
 * LOG: Working on MTP3/SCCP integration.
 * LOG:
 * LOG: Revision 1.29  1998/09/29 01:43:46  mmiers
 * LOG: We need PC in IsSSNAllowed() as our SCCP is process-distributed.
 * LOG:
 * LOG: Revision 1.28  1998/09/28 17:37:51  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.27  1998/09/28 16:30:46  mmiers
 * LOG: Notify on successful initialization.
 * LOG:
 * LOG: Revision 1.26  1998/09/28 16:27:55  mmiers
 * LOG: Tweaks for Arun's bugs.
 * LOG:
 * LOG: Revision 1.25  1998/09/28 00:41:25  mmiers
 * LOG: More work on connection-oriented.
 * LOG:
 * LOG: Revision 1.24  1998/09/25 23:25:07  mmiers
 * LOG: Add output init flags.
 * LOG:
 * LOG: Revision 1.23  1998/09/25 21:34:42  mmiers
 * LOG: Fix file tracing.
 * LOG:
 * LOG: Revision 1.22  1998/09/25 21:10:56  mmiers
 * LOG: Fixup for trace.
 * LOG:
 * LOG: Revision 1.21  1998/09/24 23:27:29  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.20  1998/09/24 16:33:11  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG: Revision 1.19  1998/09/23 19:52:40  mmiers
 * LOG: Change ABORT to CRITICAL.  Severity looks wrong, otherwise.
 * LOG:
 * LOG: Revision 1.18  1998/09/22 18:59:11  mmiers
 * LOG: Turn debug trace off by default.
 * LOG:
 * LOG: Revision 1.17  1998/09/21 17:20:10  mmiers
 * LOG: Add tracing into everything.
 * LOG:
 * LOG: Revision 1.16  1998/09/18 23:15:07  mmiers
 * LOG: add level names.
 * LOG:
 * LOG: Revision 1.15  1998/09/18 22:48:49  mmiers
 * LOG: correct trace file name
 * LOG:
 * LOG: Revision 1.14  1998/09/18 22:47:58  mmiers
 * LOG: Add tracing.
 * LOG:
 * LOG: Revision 1.13  1998/09/01 00:32:33  whu
 * LOG: Debugging SCCP when a transport is both a route and an application.
 * LOG:
 * LOG: Revision 1.12  1998/07/22 15:24:12  mmiers
 * LOG: Add ITS_SS7 to SCCP initialize.
 * LOG:
 * LOG: Revision 1.11  1998/07/21 21:28:28  mmiers
 * LOG: Modify SCCP implementation.
 * LOG:
 * LOG: Revision 1.10  1998/07/18 00:13:36  ahanda
 * LOG: Don't exit if one of the dispatch procedures doesn't succeed.
 * LOG:
 * LOG: Revision 1.9  1998/07/03 19:42:18  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.8  1998/06/30 22:47:00  mmiers
 * LOG: Start adding SCCP-as-a-thread infrastructure.
 * LOG:
 * LOG: Revision 1.7  1998/06/30 01:52:36  mmiers
 * LOG: Remove compile-time warning on Linux.
 * LOG:
 * LOG: Revision 1.6  1998/06/24 16:11:38  mmiers
 * LOG: Debugging SCCP; also straighten out the ITS_Transport issues.
 * LOG:
 * LOG: Revision 1.5  1998/06/23 00:35:37  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/06/19 22:25:28  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/06/17 21:32:28  mmiers
 * LOG: Get Vendor straightened out.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:32  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.8  1998/06/17 19:57:03  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.7  1998/06/15 16:29:05  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.6  1998/06/05 20:08:57  mmiers
 * LOG: Tweaking things for the release.  Now to retag.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 22:32:00  mmiers
 * LOG: Raw documentation for SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/05/14 20:41:44  mmiers
 * LOG: Update SCCP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.3  1998/05/05 00:00:03  mmiers
 * LOG: Add new signatures, remove TCSM code from tcap.h.
 * LOG:
 * LOG: Revision 1.2  1998/05/04 22:57:37  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.1  1998/05/01 14:04:22  mmiers
 * LOG: Update with interface routines.  Need to fill in checks for mandatory
 * LOG: parms, and call ifc routines.
 * LOG:
 * LOG: Revision 1.2  1998/04/07 15:51:54  mmiers
 * LOG: Update library to reflect vendor changes.
 * LOG:
 * LOG: Revision 1.1  1998/02/25 21:42:28  mmiers
 * LOG: Add in initial implementation of SCCP interface.
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_thread_pool.h>
#include <its_timers.h>
#include <its_assertion.h>
#include <its_route_rwlock.h>
#include <its_redundancy.h>
#include <sccp_pegs.h>
#include <its_ctf.h>
#include <engine.h>
/*Patch:Itika:1-nov-10:Redundancy Merge fix*/
#include <sched.h>
/*Patch:Itika:1-nov-10:End*/

#ident "$Id: ansi-sccp.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/sccp.h>

#include "sccp_intern.h"
 HASH_Table _PC_Table;
  HASH_Table SST_HashTable ;
ITS_INT SCLCHandleReasmTimer_ANSI(ITS_TimerData* td);
int SendSCMG(MTP3_HEADER* mtp3, SCCP_SCMG_ANSI* scmg, ITS_UINT toSSN);
int SSTCStartSST_ANSI(MTP3_HEADER* mtp3, ITS_UINT pc, ITS_OCTET ssn);
/*
 * global data
 */
TQUEUETRAN_Manager* __SCCP_ANSI_RcvQueue = NULL;
#define NO_REDUNDANCY 1

/*
 * for threading SCCP.
 */
TPOOL *             __SCCP_ANSI_ThreadPool = NULL;

/*
 * local data
 */
THREAD_RET_TYPE ANSI_SCCPThread(void *arg);
static ITS_MUTEX        sccpGate;
static ITS_USHORT       userParts[SCCP_MAX_USER_PARTS] = { 0 };

static ITS_THREAD   *sccpThread;
static int GatherLocal(ITS_POINTER data, void *in, void *out);
static void FreeList(ROUTE_Info* list);
static void DumpAllSCCPPegs(DBC_Server *dbc);
static int HandlePeerDeadEvent(ITS_EVENT *evt);
static ITS_BOOLEAN  initialized = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;
//ITSSS7DLLAPI int SCCP_EnableUserPart_ANSI(ITS_OCTET up, ITS_USHORT id);
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
ITS_UINT LocalRoutePc  = 0;
ITS_UINT RemoteRoutePc  = 0;
ITS_UINT RemoteRouteNi  = 0;
extern void Disable_Default_Readflag();
extern ITS_UINT SccpAllowedFlag;
/*Patch:Itika :end*/

ITS_UINT  __local_seg_ref_number = 0;

static ITS_CHAR *sccpPegStr[] =
{
    "PEG_SCCP_USER_MSG_SENT",
    "PEG_SCCP_REMOTE_MSG_RECEIVED",
    "PEG_SCCP_ROUTING_FAILURE",
    "PEG_SCCP_REMOTE_GTT_REQUEST",
    "PEG_SCCP_REMOTE_GTT_SUCCESS",
    "PEG_SCCP_REMOTE_GTT_FAILURE",
    "PEG_SCCP_REMOTE_MSG_DECODE_ERR",
    "PEG_SCCP_USER_MSG_ENCODE_ERR",
    "PEG_SCCP_REMOTE_REASSEMBLE_ERR",
    "PEG_SCCP_HOP_COUNTER_VIOLATION_ERR",
    "PEG_SCCP_USER_SEGMENTATION_ERR",
    "PEG_SCCP_TIMER_TIAR_EXPIRY",
    "PEG_SCCP_USER_INITIATED_RLS",
    "PEG_SCCP_USER_INITITATED_RESET",
    "PEG_SCCP_REMOTE_UDT_RCVD",
    "PEG_SCCP_REMOTE_XUDT_RCVD",
    "PEG_SCCP_REMOTE_UDTS_RCVD",
    "PEG_SCCP_REMOTE_XUDTS_RCVD",
    "PEG_SCCP_REMOTE_LUDT_RCVD",
    "PEG_SCCP_REMOTE_LUDTS_RCVD",
    "PEG_SCCP_USER_UDT_SENT",
    "PEG_SCCP_USER_XUDT_SENT",
    "PEG_SCCP_USER_UDTS_SENT",
    "PEG_SCCP_USER_XUDTS_SENT",
    "PEG_SCCP_USER_LUDT_SENT",
    "PEG_SCCP_USER_LUDTS_SENT",
    "PEG_SCCP_USER_CR_SENT",
    "PEG_SCCP_CREF_TO_REMOTE_SENT",
    "PEG_SCCP_RSR_TO_REMOTE_SENT",
    "PEG_SCCP_ERR_TO_REMOTE_SENT",
    "PEG_SCCP_REMOTE_CR_RCVD",
    "PEG_SCCP_REMOTE_CREF_RCVD",
    "PEG_SCCP_REMOTE_RSR_RCVD",
    "PEG_SCCP_REMOTE_ERR_RCVD",
    "PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD",
    "PEG_SCCP_USER_DT1_SENT",
    "PEG_SCCP_REMOTE_DT1_RCVD",
    "PEG_SCCP_USER_DT2_SENT",
    "PEG_SCCP_REMOTE_DT2_RCVD",
    "PEG_SCCP_USER_ED_SENT",
    "PEG_SCCP_REMOTE_ED_RCVD",
    "PEG_SCCP_REMOTE_SSP_RCVD",
    "PEG_SCCP_REMOTE_SSA_RCVD",
    "PEG_SCCP_REMOTE_SSC_RCVD",
    "PEG_SCCP_LOCAL_SS_PROHIBITED",
    "PEG_SCCP_LOCAL_SS_ALLOWED",
    "PEG_SCCP_LOCAL_SS_CONGESTED",
    NULL
};

static ITS_CHAR* SCCP_ANSI_Timers[]=
{
    SCCP_TSTAT_INFO_STRING,
    SCCP_TCOORD_CHG_STRING,
    SCCP_TIGNORE_SST_STRING,
    SCCP_TRTG_STAT_INFO_STRING,
    SCCP_TCONN_STRING,
    SCCP_TRELEASE_STRING,
    SCCP_TRESET_STRING,
    SCCP_TINACT_SEND_STRING,
    SCCP_TINACT_RECV_STRING,
    SCCP_TGUARD_STRING,
    SCCP_TREASSEM_STRING,
    SCCP_TINTERVAL_STRING,
    SCCP_TREPEAT_REL_STRING,
    NULL
};

static TRACE_OutputInitializer fileCritTrace =
{
    SCCP_FILE_STRING,
    ITS_TRUE,
    SCCP_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    SCCP_FILE_STRING,
    ITS_TRUE,
    SCCP_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    SCCP_FILE_STRING,
    ITS_TRUE,
    SCCP_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    SCCP_FILE_STRING,
    ITS_TRUE,
    SCCP_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    SCCP_FILE_STRING,
    ITS_TRUE,
    SCCP_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    SCCP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    SCCP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer SCCP_TraceMap[] =
{
    {SCCP_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {SCCP_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {SCCP_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {SCCP_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {SCCP_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

static int numThreads = 1;

TRACE_Data* SCCP_ANSI_TraceData = NULL;

ITS_BOOLEAN gcsMessageBasedRedundancyIsActive = ITS_FALSE;

static ITS_UINT pegs[PEG_SCCP_NUM_PEGS];
static PEGS_DECL_SUBSYS(ANSI_SCCP, pegs);
PEG_Manager *ANSI_SCCP_Pegs = &ANSI_SCCP_PEGS;

static ITS_TIME timers[SCCP_NUM_TIMERS];
TIMERS_DECL_SUBSYS(ANSI_SCCP, timers);

static ITS_BOOLEAN behaviors[SCCP_NUM_BEHAVIORS];
BEHAVIORS_DECL_SUBSYS(ANSI_SCCP, behaviors);

/*
 * management class record
 */
static SCCP_MgmtClassRec SCCP_MgmtClassRec_ANSI =
{
    /* core part */
    {
        NULL,                           /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        "ANSI SCCPMgmt",                /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* management part */
    {
        /* data part */
        &ANSI_SCCP_PEGS,
        &ANSI_SCCP_Behaviors,
        &ANSI_SCCP_Timers,
        ANSI_SCCP_Alarms,

        /* function part */
        SCCP_GetGeneralCfg_ANSI,
        SCCP_SetGeneralCfg_ANSI,
        SCCP_GetSSEntry_ANSI,
        SCCP_GetAllSSEntries_ANSI,
        SCCP_SetSSEntry_ANSI,
        SCCP_RemSSEntry_ANSI,
        SCCP_GetPointCodeEntry_ANSI,
        SCCP_GetAllPointCodeEntries_ANSI,
        SCCP_SetPointCodeEntry_ANSI,
        SCCP_RemPointCodeEntry_ANSI,
        SCCP_GetConcernedPC_ANSI,
        SCCP_GetAllCPCEntries_ANSI,
        SCCP_SetConcernedPC_ANSI,
        SCCP_RemConcernedPC_ANSI,
        SCCP_GetConcernedSS_ANSI,
        SCCP_GetAllCSSEntries_ANSI,
        SCCP_SetConcernedSS_ANSI,
        SCCP_RemConcernedSS_ANSI,
        SCCP_SendSCMG_ANSI,
        SCCP_SendSST_ANSI,
        SCCP_AddConcernedSubSystem_ANSI,
        SCCP_RemConcernedSubSystem_ANSI,
        SCCP_AddDuplicatedSubSystem_ANSI,
        SCCP_RemDuplicatedSubSystem_ANSI
    }
};

ITSSS7DLLAPI ITS_Class SCCP_MgmtClass_ANSI =
    (ITS_Class)&SCCP_MgmtClassRec_ANSI;

/*.implementation:notForExport
 ****************************************************************************
 *  Purpose:
 *      This function removes a connection from consideration.
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
 *      To implement the guard timer, we should not free the structure,
 *      but rather compute the guard timeout (freezeRelease) and not
 *      reallocate this id until the current time is greater than the
 *      freezeRelease time.
 *      Too expensive.  That would take ~6.5M.  A better approach may be
 *      to use a fixed size array of expiry times, indexed by reference
 *      number.
 *
 *  See Also:
 ****************************************************************************/
void
SCCP_DeleteLocalReference_ANSI(ITS_CTXT cref)
{
    SCCP_CONN_CTXT *foundCtxt;
    ITS_INT error;

    SCCP_DEBUG(("DeleteLocalRef: cref %04x\n", cref));
#ifdef NO_REDUNDANCY
    DSM_LockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

    foundCtxt = (SCCP_CONN_CTXT *)DSM_FindNoLockLocal(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&cref,
                                           sizeof(cref), &error);
#else
   DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

   foundCtxt = (SCCP_CONN_CTXT *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&cref,
                                           sizeof(cref), &error);

#endif
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("DeleteLocalRef: Couldn't acquire mutex.\n"));
            
            break;

        case (ITS_ENOTFOUND):
            SCCP_WARNING(("DeleteLocalRef: Could not find context.\n"));

            break;

        case (ITS_EINUSE):
            SCCP_ERROR(("DeleteLocalRef: DSM Row Locked.\n"));

            break;
        }

#ifdef NO_REDUNDANCY
        DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#else
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#endif

        return;
    }

#ifdef NO_REDUNDANCY
    error = DSM_FreeNoLockLocal(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_CTXT,
                     (ITS_OCTET *)&cref,
                     sizeof(cref), foundCtxt);
#else

    error = DSM_FreeNoLock(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_CTXT,
                     (ITS_OCTET *)&cref,
                     sizeof(cref), foundCtxt);
#endif

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("DeleteLocalRef: DSM unable to free Reference.\n"));
    }

#ifdef NO_REDUNDANCY
    DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#else
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#endif

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
static int
SCCCP_GetNextSharedConnRefNum(ITS_CTXT *connRefNum)
{
    ITS_CTXT *nextConnRefNum = NULL;
    int error = 0 , ret;

    ITS_UINT key;

    key = DSM_ANSI_SCCP_NEXT_REF_NUM;
/*Patch:Itika:2-nov-10:Sccp Enhancement Merge fix*/
//#ifdef REDUNDANCY_PATCH
#ifdef NO_REDUNDANCY
/*Patch:Itika:1-nov-10:End*/

    DSM_LockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);

    nextConnRefNum = (ITS_CTXT *) DSM_FindNoLockLocal(DSM_SccpFtGroupId,
                                                 DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                                                 (ITS_OCTET *) &key,
                                                 sizeof(key),
                                                 &error);

#else
    DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
   
    nextConnRefNum = (ITS_CTXT *) DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                                                 (ITS_OCTET *) &key,
                                                 sizeof(key),
                                                 &error);

#endif
    if (nextConnRefNum == NULL || error != ITS_SUCCESS)
    {
/*Patch:Itika:2-nov-10:Sccp Enhancement Merge fix*/
//#ifdef REDUNDANCY_PATCH
#ifdef NO_REDUNDANCY
/*Patch:Itika:1-nov-10:End*/
        DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#else
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#endif

        return ITS_ENOMEM;
    }

    (*nextConnRefNum)++;

    *connRefNum = *nextConnRefNum;

/*Patch:Itika:2-nov-10:Sccp Enhancement Merge fix*/
//#ifdef REDUNDANCY_PATCH
#ifdef NO_REDUNDANCY
/*Patch:Itika:1-nov-10:End*/
    ret = DSM_CommitNoLockLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                           (ITS_OCTET *) &key,
                           sizeof(key),
                           (void*) nextConnRefNum);

#else
   ret = DSM_CommitNoLock(DSM_SccpFtGroupId,
                           DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                           (ITS_OCTET *) &key,
                           sizeof(key),
                           (void*) nextConnRefNum);

#endif
    if (ret != ITS_SUCCESS)
    {
/*Patch:Itika:2-nov-10:Sccp Enhancement Merge fix*/
//#ifdef REDUNDANCY_PATCH
#ifdef NO_REDUNDANCY
/*Patch:Itika:1-nov-10:End*/
        DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#else
         DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#endif

        return ITS_ENOMEM;
    }
/*Patch:Itika:2-nov-10:Sccp Enhancement Merge fix*/
//#ifdef REDUNDANCY_PATCH
#ifdef NO_REDUNDANCY
/*Patch:Itika:1-nov-10:End*/

    DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#else
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#endif

    return ITS_SUCCESS;

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the next available local reference number.
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
 *      If the value is non-zero, it is the next available local reference
 *      number.  A return value of zero indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_GetSCCPNextRef_ANSI(ITS_SS7_HANDLE handle,
                               ITS_CTXT *cref)
{
    /*static ITS_CTXT nextUnique = 1;*/
    ITS_CTXT nextUnique;
    SCCP_CONN_CTXT *foundCtxt = NULL, *newCtxt = NULL;
    ITS_UINT size = sizeof(SCCP_CONN_CTXT);
    int error;
    int i;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    SCCP_DEBUG(("GetNextLocalRef:.\n"));


    if (redunClass)
    {
        if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
        {
            SCCP_ERROR(("Backup Node Cannot Initiate Messages.\n"));

            *cref = 0;

            return (ITS_EINVINITSTATE);
        }
    }

#ifdef NO_REDUNDANCY
    if (DSM_LockTableLocal(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CTXT) != ITS_SUCCESS)
#else
    if (DSM_LockTable(DSM_SccpFtGroupId,DSM_TABLE_ANSI_SCCP_CTXT) != ITS_SUCCESS)
#endif
    {
        ITS_TRACE_ERROR(("GetNextLocalRef: Can't acquire at least the local lock\n"));

        return (ITS_EBADMUTEX);
    }
 
    for (i = 0; i < 65536; i++ )
    {

        if (SCCCP_GetNextSharedConnRefNum(&nextUnique) != ITS_SUCCESS)
        {

            ITS_TRACE_ERROR(("GetNextLocalRef: Cannot Get Next ConnRefNum\n"));

            return ITS_ENOMEM;
        }

#ifdef NO_REDUNDANCY
        foundCtxt = (SCCP_CONN_CTXT *)DSM_FindNoLockLocal(DSM_SccpFtGroupId,
                                                     DSM_TABLE_ANSI_SCCP_CTXT,
                                                     (ITS_OCTET *)&nextUnique, 
                                                     sizeof(nextUnique), &error);
#else
       foundCtxt = (SCCP_CONN_CTXT *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                     DSM_TABLE_ANSI_SCCP_CTXT,
                                                     (ITS_OCTET *)&nextUnique,
                                                     sizeof(nextUnique), &error);

#endif
        if (error == ITS_ENOTFOUND)
        {

#ifdef NO_REDUNDANCY
            newCtxt =
                (SCCP_CONN_CTXT *)DSM_AllocNoLockLocal(DSM_SccpFtGroupId,
                                                  DSM_TABLE_ANSI_SCCP_CTXT, 
                                                  (ITS_OCTET *)&nextUnique, 
                                                  sizeof(nextUnique),
                                                  size, &error);
#else
       newCtxt =(SCCP_CONN_CTXT *)DSM_AllocNoLock(DSM_SccpFtGroupId,
                                                  DSM_TABLE_ANSI_SCCP_CTXT,
                                                  (ITS_OCTET *)&nextUnique,
                                                  sizeof(nextUnique),
                                                  size, &error);

#endif
            if (error != ITS_SUCCESS)
            {
                switch(error)
                {
                case (ITS_ENOMEM):
                    SCCP_CRITICAL(("GetNextLocalRef: No Memory.\n"));

                    break;

                default:

                    SCCP_CRITICAL(("GetNextLocalRef: Unknown error DSM_AllocNoLock.\n"));
                    break;
                }
#ifdef NO_REDUNDANCY

                DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#else
                 DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#endif

                return (error);
            }


            *cref = nextUnique;

            newCtxt->type = SCOC_TIMER_TYPE;

            newCtxt->connRef = *cref;
            newCtxt->state = SCCP_CONN_OUT_PEND;
            newCtxt->dataState = SCCP_DATA_NORMAL;
            newCtxt->connectTimer = 0;
            newCtxt->releaseTimer = 0;
            newCtxt->resetTimer = 0;
            newCtxt->sequenceOn = ITS_FALSE;
            newCtxt->sequenceSLS = 0;
            newCtxt->slref = *cref;
            newCtxt->dlref = 0;
            newCtxt->isIntermediate = ITS_FALSE;
#ifdef NO_REDUNDANCY

            error = DSM_CommitNoLockLocal(DSM_SccpFtGroupId,
                                DSM_TABLE_ANSI_SCCP_CTXT,
                                (ITS_OCTET *)&nextUnique, 
                                sizeof(nextUnique), newCtxt);
#else
          error = DSM_CommitNoLock(DSM_SccpFtGroupId,
                                     DSM_TABLE_ANSI_SCCP_CTXT,
                                     (ITS_OCTET *)&nextUnique,
                                     sizeof(nextUnique), newCtxt);

#endif

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("GetNextLocalRef: Couldn't add context.\n"));

                nextUnique++;    /* don't want to hit this one next time */

#ifdef NO_REDUNDANCY
                DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#else

                DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#endif

                return (error);
            }

#ifdef NO_REDUNDANCY
            DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#else
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#endif

#if ROUTE_WANTS_PERFORMANCE
            if (ROUTE_IsApplicationSelectorDefault())
            {
                ITS_HDR hdr;

                hdr.context.conref = *cref;
                hdr.type = ITS_SCCP_ANSI;
                ROUTE_AddApplication(ITS_DEFAULT_USER_SRC, &hdr);
            }
#endif

            /*nextUnique++;*/

            SCCP_DEBUG(("GetNextLocalRef: returns ref %04x.\n", *cref));
            return (ITS_SUCCESS);
        }
        else
        {
            /*nextUnique++;*/

        }
    }

#ifdef NO_REDUNDANCY
    DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#else
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);
#endif

    return (ITS_ENOMSGSPACE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function requests the next Local Ref num from the SCCP Stack.
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
 *      If the value is non-zero, it is the next available local reference
 *      number.  A return value of zero indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SCCP_GetSharedLocalRef_ANSI(void *ctxtData,
                             int len)
{
    ITS_EVENT ev;

    ITS_EVENT_INIT(&ev, ITS_SCCP_LOCAL_REF_REQUEST , len);
    memcpy(ev.data, ctxtData, len);

    return TRANSPORT_PutEvent(ITS_SCCP_SRC, &ev);
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
ITS_BOOLEAN
SCCP_IsSSNEquipped_ANSI(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_BOOLEAN isLocal = ITS_FALSE;

    SCCP_DEBUG(("SCCP_IsSSNEquipped:: pc %x, ssn %x, ni %x\n", pc, ssn, ni));

    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG) && ssn == SCCP_SSN_SCCPMGMT)
    {
        return (ITS_TRUE);
    }
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
#if 0
    if (ROUTE_GetRouteContextLocal(pc, &isLocal,
                                   ROUTE_DPC_SIO_SSN,
                                   FAMILY_ANSI,
                                   ROUTE_SIO_SCCP | ni,
                                   ssn,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE,
                                   ITS_SS7_DEFAULT_PRI,
                                   ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_IsSSNEquipped::Route context status lookup Fail::LOCAL \n"));

        return (ITS_FALSE);
    }

 //   SCCP_DEBUG(("SCCP_IsSSNEquipped::Route context status lookup success\n"));

    return (isLocal);
#endif
       if(pc == LocalRoutePc)
         {
           SCCP_DEBUG(("SCCP_IsSSNEquipped:: pc %x, ssn %x, ni %x ITS_TRUE\n", pc, ssn, ni));
           return (ITS_TRUE);
         }
       else 
         {
           SCCP_DEBUG(("SCCP_IsSSNEquipped:: pc %x, ssn %x, ni %x ITS_FALSE\n", pc, ssn, ni));
           return (ITS_FALSE);
         }
/*Patch:Itika :end*/
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
ITS_BOOLEAN
SCCP_IsSSNAllowed_ANSI(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_BOOLEAN isAllowed;

    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG) && ssn == SCCP_SSN_SCCPMGMT)
    {
        return (ITS_TRUE);
    }
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
#if 0
    if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        SCCP_DEBUG(("SCCP_IsSSNAllowed::Route context status lookup failed\n"));

        return (ITS_FALSE);
    }

    return (isAllowed);
#endif
      if(pc == LocalRoutePc)
      {
        SCCP_DEBUG(("SCCP_IsSSNAllowed:: Local PC, Therefore Allowed is always TRUE\n"));
        return (ITS_TRUE);
      }
      if(SccpAllowedFlag == 1) 
      {    
        SCCP_DEBUG(("SCCP_IsSSNAllowed::Route context status lookup success\n"));
        return (ITS_TRUE);
      }
      else
      {
        SCCP_DEBUG(("SCCP_IsSSNAllowed::Route context status lookup failed\n"));
        return (ITS_FALSE);

      }
/*Patch:Itika :end*/
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
ITS_OCTET
SCCP_IsSSNCongested_ANSI(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_OCTET congLevel;

    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG) && ssn == SCCP_SSN_SCCPMGMT)
    {
        return (0);
    }

    if (ROUTE_GetRouteContextCongestion(pc, &congLevel,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        return (0);
    }

    return (congLevel);
}

/*
 * lists for CPC data
 *
 * NOTES
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
 * When generating information for SST, ranges must be expanded.
 * This is so tests can stop for subsystems that have become available.
 * This isn't too expensive anyway (max 254 SSNs). Update: actually, no,
 * because we have literal information to work from for SST.
 *
 * Ensure this scheme is sufficient.  We may have to reject the
 * use of CPC ranges in order to ensure that remote SSNs are up.
 * I have to relearn some of the CPC code.
 */
static ROUTE_Info *cpcList = NULL;
static ROUTE_Info *lpcList = NULL;
static ROUTE_Info *dpcList = NULL;
static ITS_BOOLEAN  initializing = ITS_FALSE;

static ITS_BOOLEAN
CheckForCSS_ANSI(ROUTE_Info *linfo)
{
    ITS_UINT apc = linfo->basic.dpc;
    ITS_OCTET ni = linfo->basic.criteria.sio & ROUTE_NI_MASK;
    ITS_INT ctxt = apc | (ni << 24);
    ITS_OCTET cssn = linfo->basic.criteria.ssn;
    ITS_INT error;
    ROUTE_Info* rinfo;
    ROUTE_Info* trinfo;

    /*
     * Lock the tables we need
     */
    if (linfo->basic.type == LOCAL_ROUTE)
    {
        if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC)
                                                                != ITS_SUCCESS)
        {
            SCCP_ERROR(("Can't lock table\n"));

            return (ITS_FALSE);
        }

        rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_ANSI_SCCP_LPC,
                                                 (ITS_OCTET *)&ctxt,
                                                 sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
           DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

           return (ITS_FALSE);
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
    }
    else
    {
        /* Get the local from remote */
        if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC)
                                                                != ITS_SUCCESS)
        {
            SCCP_ERROR(("Can't lock table\n"));

            return (ITS_FALSE);
        }

        rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_ANSI_SCCP_CPC,
                                                 (ITS_OCTET *)&ctxt,
                                                 sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
           DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);

           return (ITS_FALSE);
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        apc = rinfo->basic.dpc;
        ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
        ctxt = apc | (ni << 24);

        /* Get the cpc list from local */
        if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC)
                                                                != ITS_SUCCESS)
        {
            SCCP_ERROR(("Can't lock table\n"));

            return (ITS_FALSE);
        }

        rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_ANSI_SCCP_LPC,
                                                 (ITS_OCTET *)&ctxt,
                                                 sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
           DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

           return (ITS_FALSE);
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        for (trinfo = rinfo; trinfo != NULL; trinfo = trinfo->next)
        {
            if (trinfo->basic.criteria.ssn == cssn)
            {
                return (ITS_TRUE);
            }
        }
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function determines if a concerned subsystem is valid for
 *      a local subsystem.
 *
 *  Input Parameters:
 *      linfo = the local route
 *      cinfo = the concerned route
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
static ITS_BOOLEAN
IsConcerned(ROUTE_Info *linfo, ROUTE_Info *cinfo)
{
    /* NOTE: OPC and CIC are overloaded for concerned routes */
    if (linfo->basic.style == ROUTE_DPC_SIO_SSN)
    {
        if (linfo->basic.dpc == cinfo->basic.criteria.opc &&
            linfo->basic.criteria.ssn == cinfo->basic.criteria.cic)
        {
            return (ITS_TRUE);
        }
    }
    else if (linfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
    {
        if (linfo->basic.dpc == cinfo->basic.criteria.opc &&
            linfo->basic.criteria.opc == cinfo->basic.dpc &&
            linfo->basic.criteria.ssn == cinfo->basic.criteria.cic)
        {
            return (ITS_TRUE);
        }
    }
    else if (linfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE)
    {
        if (linfo->basic.dpc == cinfo->basic.criteria.opc &&
            cinfo->basic.criteria.cic >= linfo->basic.criteria.range.begin &&
            cinfo->basic.criteria.cic <= linfo->basic.criteria.range.end)
        {
            return (ITS_TRUE);
        }
    }
    else if (linfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
    {
        if (linfo->basic.dpc == cinfo->basic.criteria.opc &&
            linfo->basic.criteria.opc == cinfo->basic.dpc &&
            cinfo->basic.criteria.cic >= linfo->basic.criteria.range.begin &&
            cinfo->basic.criteria.cic <= linfo->basic.criteria.range.end)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds a node to the relevent table
 *
 *  Input Parameters:
 *      table - table to add to
 *      current - the current list
 *      node - the node to add
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
static int
AddNode(ITS_UINT table, ITS_INT ctxt, ROUTE_Info *current, ROUTE_Info *node)
{
    ROUTE_Info *alloc;
    int error;

    /* allocate the node */
    if ((alloc = (ROUTE_Info *)DSM_AllocNoLock(DSM_SccpFtGroupId, 
                                               table,
                                               (ITS_OCTET *)&ctxt,
                                               sizeof(ITS_INT),
                                               sizeof(ROUTE_Info),
                                               &error)) == NULL)
    {
        SCCP_ERROR(("Failed to allocate row for table\n"));

        return (ITS_ENOMEM);
    }

    *alloc = *node;

    alloc->next = current->next;
    current->next = alloc;

    /* we changed both, so we need to commit both */
    DSM_CommitNoLock(DSM_SccpFtGroupId,
                     table,
                     (ITS_OCTET *)&ctxt,
                     sizeof(ITS_INT),
                     alloc);
    DSM_CommitNoLock(DSM_SccpFtGroupId,
                     table,
                     (ITS_OCTET *)&ctxt,
                     sizeof(ITS_INT),
                     current);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds a node to the relevent table
 *
 *  Input Parameters:
 *      table - table to add to
 *      current - the current list
 *      node - the node to add
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
static int
RemNode(ITS_UINT table, ROUTE_Info *current, ROUTE_Info *node)
{
    ITS_INT ctxt = current->basic.dpc |
                    (current->basic.criteria.sio & MTP3_NIC_MASK) << 24;
    ROUTE_Info **list, *prev;
    int ret = ITS_SUCCESS;

    /*
     * this is a little tricky.  Watch out for prev, it's one node behind
     * the current pointer
     */
    for (list = &current, prev = NULL;
         *list;
         prev = *list, list = &(*list)->next)
    {
        if (*list == node)
        {
            *list = node->next;
            break;
        }
    }

    /* free the node we have to free */
    DSM_FreeNoLock(DSM_SccpFtGroupId,
                   table,
                   (ITS_OCTET *)&ctxt, sizeof(ITS_UINT),
                   node);

    /*
     * if prev is non-null, it points at the node that's got a new next
     * pointer.  But, we still have to watch out.
     */
    if (current == NULL) /* empty list now */
    {
        return (ITS_SUCCESS);
    }
    else if (prev != NULL) /* node whose next pointer was changed */
    {
        ret = DSM_CommitNoLock(DSM_SccpFtGroupId,
                               table,
                               (ITS_OCTET *)&ctxt, sizeof(ITS_UINT),
                               prev);
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a concerned subsystem (or range) to the local subsystem
 *      (or range).
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
ITSSS7DLLAPI int
SCCP_AddConcernedSubSystem_ANSI(ROUTE_Info *linfo, ROUTE_Info *cinfo)
{
    ITS_INT ctxt = linfo->basic.dpc |
                    (linfo->basic.criteria.sio & MTP3_NIC_MASK) << 24;
    ROUTE_Info *current;
    int error, ret = ITS_SUCCESS;

    /*
     * lock the relevent tables
     */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        /* complain */
        SCCP_ERROR(("Failed to lock the LPC table\n"));

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        /* complain */
        SCCP_ERROR(("Failed to lock the CPC table\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return (ITS_EBADMUTEX);
    }

    /* see if we need to record this info locally (for termination) */
    if (!initializing)
    {
        /* ok, management's doing it.  We need to record the action */

        /* copy linfo */
        current = (ROUTE_Info *)malloc(sizeof(ROUTE_Info));
        if (current == NULL)
        {
            SCCP_ERROR(("Out of memory\n"));
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ITS_ENOMEM);
        }

        memcpy(current, linfo, sizeof(ROUTE_Info));

        current->next = lpcList;
        lpcList = current;

        /* copy cinfo */
        current = (ROUTE_Info *)malloc(sizeof(ROUTE_Info));
        if (current == NULL)
        {
            SCCP_ERROR(("Out of memory\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ITS_ENOMEM);
        }

        memcpy(current, cinfo, sizeof(ROUTE_Info));

        current->next = cpcList;
        cpcList = current;
    }

    /*
     * merge or add concerned info to local table.
     */
    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_INT),
                                                &error)) != NULL)
    {
        ret = AddNode(DSM_TABLE_ANSI_SCCP_LPC, ctxt, current, cinfo);

        if (ret != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to add concerned route to local table\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ret);
        }
            SCCP_ERROR((" Add concerned route to local table Sucess ANSI \n"));
    }
    else
    {
        if ((current = (ROUTE_Info *)DSM_AllocNoLock(DSM_SccpFtGroupId,
                                                     DSM_TABLE_ANSI_SCCP_LPC,
                                                     (ITS_OCTET *)&ctxt,
                                                     sizeof(ITS_INT),
                                                     sizeof(ROUTE_Info),
                                                     &error)) == NULL)
        {
            /* Houston, we have a problem */
            SCCP_ERROR(("Unable to add concerned info for local subsys\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ITS_ENOMEM);
        }

        *current = *cinfo;
        current->next = NULL;
            SCCP_ERROR((" Add concerned route to local table LPC Sucess ANSI \n"));

        DSM_CommitNoLock(DSM_SccpFtGroupId,
                         DSM_TABLE_ANSI_SCCP_LPC,
                         (ITS_OCTET *)&ctxt,
                         sizeof(ITS_INT),
                         current);
    }

    /*
     * merge or add local table to concerned table
     */
    ctxt = cinfo->basic.dpc |
            (cinfo->basic.criteria.sio & MTP3_NIC_MASK) << 24;
    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_INT),
                                                &error)) != NULL)
    {
        ret = AddNode(DSM_TABLE_ANSI_SCCP_CPC, ctxt, current, linfo);

        if (ret != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to add local route to concerned table\n"));
        }
    }
    else
    {
        if ((current = DSM_AllocNoLock(DSM_SccpFtGroupId,
                                       DSM_TABLE_ANSI_SCCP_CPC,
                                       (ITS_OCTET *)&ctxt,
                                       sizeof(ITS_INT),
                                       sizeof(ROUTE_Info),
                                       &error)) == NULL)
        {
            /* Houston, we have a problem */
            SCCP_ERROR(("Unable to add concerned info for local subsys\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ITS_ENOMEM);
        }

        *current = *linfo;
        current->next = NULL;
            SCCP_ERROR((" Add concerned route to local table CPC Sucess ANSI \n"));

        ret = DSM_CommitNoLock(DSM_SccpFtGroupId,
                               DSM_TABLE_ANSI_SCCP_CPC,
                               (ITS_OCTET *)&ctxt,
                               sizeof(ITS_INT),
                               current);
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a concerned item to the local 
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
ITSSS7DLLAPI int
SCCP_RemConcernedSubSystem_ANSI(ROUTE_Info *linfo, ROUTE_Info *cinfo)
{
    ITS_INT ctxt = linfo->basic.dpc |
                    (linfo->basic.criteria.sio & MTP3_NIC_MASK) << 24;
    ROUTE_Info *current;
    int error, ret;

    /*
     * lock the relevent tables
     */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        /* complain */
        SCCP_ERROR(("Failed to lock the LPC table\n"));

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        /* complain */
        SCCP_ERROR(("Failed to lock the CPC table\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return (ITS_EBADMUTEX);
    }

    /*
     * delete concerned info from local table.
     */
    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_INT),
                                                &error)) != NULL)
    {
        ret = RemNode(DSM_TABLE_ANSI_SCCP_LPC, current, cinfo);

        if (ret != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to rem concerned route from local table\n"));
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ret);
        }
    }

    /*
     * delete local table from concerned table
     */
    ctxt = cinfo->basic.dpc |
            (cinfo->basic.criteria.sio & MTP3_NIC_MASK) << 24;
    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId, 
                                                DSM_TABLE_ANSI_SCCP_CPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_INT),
                                                &error)) != NULL)
    {
        ret = RemNode(DSM_TABLE_ANSI_SCCP_CPC, current, linfo);

        if (ret != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to rem local route from concerned table\n"));

        }
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a duplicated subsystem to the local 
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
 *      This function relies on the overloading of the cic and opc
 *      fields in the ROUTE_Info structure.  The local point code
 *      and SSN shall be store in the opc and cic fields, respectively,
 *      before calling this function.
 *
 ****************************************************************************/
ITSSS7DLLAPI int
SCCP_AddDuplicatedSubSystem_ANSI(ROUTE_Info *rinfo)
{
    ITS_INT ctxt = (rinfo->basic.criteria.cic << 24) |
                    rinfo->basic.criteria.opc;
    void *dummy;
    int error;

    /* use a table lock */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_DUPS) != ITS_SUCCESS)
    {
        /* complain */
        SCCP_ERROR(("Failed to lock dup table\n"));


        return (ITS_EBADMUTEX);
    }

    /* see if we need to record the action */
    if (!initializing)
    {
        ROUTE_Info *current;

        /* copy rinfo */
        current = (ROUTE_Info *)malloc(sizeof(ROUTE_Info));
        if (current == NULL)
        {
            SCCP_ERROR(("Out of memory\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return (ITS_ENOMEM);
        }

        memcpy(current, rinfo, sizeof(ROUTE_Info));

        current->next = dpcList;
        dpcList = current;
    }

    /* if the entry already exists, it's a semi-error */
    if ((dummy = DSM_FindNoLock(DSM_SccpFtGroupId, 
                                DSM_TABLE_ANSI_SCCP_DUPS,
                                (ITS_OCTET *)&ctxt, sizeof(ITS_INT),
                                &error)) != NULL)
    {
        /*
         * We used to warn here.  Don't any longer, DSM means that another
         * node may have added the dup already.
         */
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_DUPS);

        return (ITS_EINUSE);
    }

    if ((dummy = DSM_AllocNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_ANSI_SCCP_DUPS,
                                 (ITS_OCTET *)&ctxt, sizeof(ITS_INT),
                                 sizeof(*rinfo), &error)) == NULL)
    {
        SCCP_ERROR(("Failed to add duplicated route\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_DUPS);

        return (ITS_ENOMEM);
    }

    *(ROUTE_Info *)dummy = *rinfo;
    ((ROUTE_Info *)dummy)->next = NULL;

    DSM_CommitNoLock(DSM_SccpFtGroupId, 
                     DSM_TABLE_ANSI_SCCP_DUPS,
                     (ITS_OCTET *)&ctxt, sizeof(ITS_INT),
                     dummy);

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_DUPS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete a duplicated subsystem from the local 
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
 *      This function relies on the overloading of the cic and opc
 *      fields in the ROUTE_Info structure.  The local point code
 *      and SSN shall be store in the opc and cic fields, respectively,
 *      before calling this function.
 *
 ****************************************************************************/
ITSSS7DLLAPI int
SCCP_RemDuplicatedSubSystem_ANSI(ROUTE_Info *rinfo)
{
    ITS_INT ctxt = (rinfo->basic.criteria.cic << 24) |
                    rinfo->basic.criteria.opc;
    void *dummy;
    int error;

    /*
     * just delete it.  Don't warn if it doesn't exist, another node
     * might have deleted it already
     */
    if ((dummy = DSM_Find(DSM_SccpFtGroupId,
                          DSM_TABLE_ANSI_SCCP_DUPS,
                          (ITS_OCTET *)&ctxt, sizeof(ITS_INT),
                          &error)) != NULL)
    {
        DSM_Free(DSM_SccpFtGroupId,
                 DSM_TABLE_ANSI_SCCP_DUPS,
                 (ITS_OCTET *)&ctxt, sizeof(ITS_INT),
                 dummy);
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
ITSSS7DLLAPI SCCPGeneralCfg*
SCCP_GetGeneralCfg_ANSI()
{
    SCCPGeneralCfg *ret;

    ret = calloc(1, sizeof(SCCPGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      2))) ||
                   (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_EVENT) &&
                    (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_EVENT,
                                      0) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_EVENT,
                                      1) ||
                     TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_EVENT,
                                      2)));
    ret->alarmLevel = SCCP_AlarmLevel_ANSI;

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
ITSSS7DLLAPI int
SCCP_SetGeneralCfg_ANSI(SCCPGeneralCfg *data)
{
    SCCP_AlarmLevel_ANSI = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    { 
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                      SCCP_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                      SCCP_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                      SCCP_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                      SCCP_DEBUG_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                      SCCP_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
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
ITSSS7DLLAPI SCCPSubSystemInfo*
SCCP_GetSSEntry_ANSI(ITS_UINT sspc, ITS_OCTET ni, ITS_OCTET ssn)
{
    SCCPSubSystemInfo *ret;
    ITS_BOOLEAN isAllowed;
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
#if 0
    if (ROUTE_GetRouteContextStatus(sspc, &isAllowed,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ni | MTP3_SIO_SCCP,
                                    ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        return (NULL);
    }
#endif
/*Patch:Itika:2-Nov-10:End*/
   isAllowed = ITS_TRUE; 

    /* alloc return region */
    ret = (SCCPSubSystemInfo *)calloc(1, sizeof(SCCPSubSystemInfo));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->pointcode = sspc;
    ret->ni = ni;
    ret->ssn = ssn;
    ret->inService = isAllowed;
    ret->testOn = SCMGIsSSTPending_ANSI(NULL);
    ret->variant = ITS_THIRD_GEN;       /* FIXME */
    ret->hasConcernPC = ITS_FALSE;      /* FIXME */
    ret->maxHops = 0;                   /* FIXME */
    ret->backupStatus = SSN_STANDALONE;     /* FIXME */
    ret->backupPC = 0;                  /* FIXME */
    ret->backupNI = ni;
    ret->backupSSN = 0;                 /* FIXME */
    ret->backupSSNState = ITS_FALSE;    /* FIXME */

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
ITSSS7DLLAPI int
SCCP_SendSST_ANSI(SCCPConcernedSSInfo *data)
{
    ITS_UINT cpc = data->cpc;
    ITS_UINT pc =  data->pc;
    ITS_OCTET ni = data->ni;
    ITS_OCTET cssn = data->cssn;
    MTP3_HEADER hdr;
    ITS_INT error;

    MTP3_HDR_SET_SIO(hdr,ni | MTP3_SIO_SCCP);
    MTP3_RL_SET_DPC_VALUE(hdr.label,pc);
    MTP3_RL_SET_OPC_VALUE(hdr.label,cpc);

    error = SSTCStartSST_ANSI(&hdr, cpc, cssn);

    return (error);
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
ITSSS7DLLAPI int
SCCP_SendSCMG_ANSI(SCCPConcernedSSInfo *data)
{
    ITS_UINT apc = data->pc;
    ITS_OCTET ni = data->ni;
    ITS_INT ctxt = apc | (ni << 24);
    SCCP_SCMG scmg;
    ROUTE_Info* rinfo, *tinfo;
    MTP3_HEADER hdr;
    ITS_INT error;

    if (!SCCP_IsSSNEquipped(ni, apc, data->ssn))
    {  
       return (ITS_ENOTCONFIG);
    }
    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                               SCCP_B_propagate_SCMG))
    { 
        return (ITS_ENOTCONFIG);
    }

    /*
     * Lock the tables we need
     */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));
        return (ITS_EBADMUTEX);
    }

    rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                         DSM_TABLE_ANSI_SCCP_LPC,
                                         (ITS_OCTET *)&ctxt,
                                         sizeof(ctxt), &error);
    if (error != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
        return (ITS_ENOTFOUND);
    }

    /* build SCMG info */
    if (!data->inservice)
    {
        scmg.type = SCCP_SCMG_SS_PROHIBIT;
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_PROHIBITED);
    }
    else
    {
        scmg.type = SCCP_SCMG_SS_ALLOWED;
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_ALLOWED);
    }
    scmg.ssn = data->ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, apc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    MTP3_RL_SET_OPC_VALUE(hdr.label, apc);

    error = ITS_ENOTFOUND;

    /* send to all concerned */
    for (tinfo = rinfo; tinfo != NULL; tinfo = tinfo->next)
    {
        if ((tinfo->basic.criteria.ssn == data->cssn) && 
                           (tinfo->basic.dpc == data->cpc))
        {
            MTP3_RL_SET_DPC_VALUE(hdr.label, tinfo->basic.dpc);
            MTP3_RL_SET_SLS(hdr.label, 0);
            hdr.sio = data-> ni | MTP3_SIO_SCCP;

            error = SendSCMG(&hdr, &scmg, tinfo->basic.criteria.ssn);

            break;
        }
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
    return (error);
}

/*
 * parser struct
 */
typedef struct
{
    SCCPSubSystemInfo   **entries;
    ITS_UINT            *numEntries;
}
SubSysIterStruct;

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
static int
GetAllSSNRoutes(ITS_POINTER entry, void *in, void *out)
{
    ROUTE_Info *rinfo = (ROUTE_Info *)entry;
    SubSysIterStruct *iter = (SubSysIterStruct *)in;

    if (rinfo->basic.family != FAMILY_ANSI)
    {
        return (ITS_SUCCESS);
    }

    if ((rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
        rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN) &&
        (rinfo->basic.type != ROUTING_KEY_ROUTE) &&
        (rinfo->basic.type != CONCERNED_ROUTE) &&
        (rinfo->basic.type != DUPLICATED_ROUTE))

    {
        ITS_UINT which = *iter->numEntries;
        SCCPSubSystemInfo *ent;

        (*iter->numEntries)++;
        (*iter->entries) = (SCCPSubSystemInfo *)realloc(*iter->entries,
                                                        *iter->numEntries *
                                                         sizeof(SCCPSubSystemInfo));
        ent = &(*iter->entries)[which];

        if (*iter->entries != NULL)
        {
            if (rinfo->basic.type == LOCAL_ROUTE)
            {
                ent->isLocal = ITS_TRUE;
            }
            else
            {
                ent->isLocal = ITS_FALSE;
            }
            ent->pointcode = rinfo->basic.dpc;
            ent->ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
            ent->ssn = rinfo->basic.criteria.ssn;
            ent->inService = rinfo->isAllowed;
            ent->testOn = SCMGIsSSTPending_ANSI(rinfo);
            ent->variant = ITS_THIRD_GEN;       /* FIXME */
            ent->hasConcernPC = CheckForCSS_ANSI(rinfo);
            ent->maxHops = 0;                   /* FIXME */
            ent->backupStatus = SSN_STANDALONE;     /* FIXME */
            ent->backupPC = 0;                  /* FIXME */
            ent->backupNI = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
            ent->backupSSN = 0;                 /* FIXME */
            ent->backupSSNState = ITS_FALSE;    /* FIXME */
            ent->linkSet = rinfo->linkSet->linkSet;
        }
    }
    else if ((rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
             rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE) &&
             (rinfo->basic.type != ROUTING_KEY_ROUTE) &&
             (rinfo->basic.type != CONCERNED_ROUTE) &&
             (rinfo->basic.type != DUPLICATED_ROUTE))

    {
        ITS_USHORT ind;

        for (ind = rinfo->basic.criteria.range.begin;
             ind <= rinfo->basic.criteria.range.end;
             ind++)
        {
            ITS_UINT which = *iter->numEntries;
            SCCPSubSystemInfo *ent;

            (*iter->numEntries)++;
            (*iter->entries) = (SCCPSubSystemInfo *)realloc(*iter->entries,
                                                            *iter->numEntries *
                                                             sizeof(SCCPSubSystemInfo));
            ent = &(*iter->entries)[which];

            if (*iter->entries != NULL)
            {
                if (rinfo->basic.type == LOCAL_ROUTE)
                {
                    ent->isLocal = ITS_TRUE;
                }
                else
                {
                    ent->isLocal = ITS_FALSE;
                }
                ent->pointcode = rinfo->basic.dpc;
                ent->ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
                ent->ssn = (ITS_OCTET)ind;
                ent->inService = rinfo->isAllowed;
                ent->testOn = SCMGIsSSTPending_ANSI(rinfo);
                ent->variant = ITS_THIRD_GEN;       /* FIXME */
                ent->hasConcernPC = ITS_FALSE;      /* FIXME */
                ent->maxHops = 0;                   /* FIXME */
                ent->backupStatus = SSN_STANDALONE;     /* FIXME */
                ent->backupPC = 0;                  /* FIXME */
                ent->backupNI = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
                ent->backupSSN = 0;                 /* FIXME */
                ent->backupSSNState = ITS_FALSE;    /* FIXME */
                ent->linkSet = rinfo->linkSet->linkSet;
            }
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
ITSSS7DLLAPI void
SCCP_GetAllSSEntries_ANSI(ITS_UINT* numEntries,
                          SCCPSubSystemInfo** entries)
{
    SubSysIterStruct iter;

    *entries = NULL;
    *numEntries = 0;

    iter.entries = entries;
    iter.numEntries = numEntries;

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES,
                     &iter, NULL, GetAllSSNRoutes);

    ROUTE_UnlockTable();
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
ITSSS7DLLAPI int
SCCP_SetSSEntry_ANSI(SCCPSubSystemInfo *data)
{
    ROUTE_MatchInfo rinfo;
    int ret;

    rinfo.linkSet = data->linkSet;
    rinfo.linkCode = 0;
    rinfo.priority = 0;
    rinfo.sls = 0;
    rinfo.rkey = 0;

    if (data->isLocal)
    {
        rinfo.basic.type = LOCAL_ROUTE;
    }
    else
    {
        rinfo.basic.type = REMOTE_ROUTE;
    }
    rinfo.basic.style = ROUTE_DPC_SIO_SSN;
    rinfo.basic.family = FAMILY_ANSI;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.dpc = data->pointcode;
    rinfo.basic.criteria.sio = data->ni & ROUTE_NI_MASK;
    rinfo.basic.criteria.sio |= ROUTE_SIO_SCCP;
    rinfo.basic.criteria.ssn = data->ssn;

    ret = ROUTE_AddRouteContextInfo(&rinfo);

    if (ret != ITS_SUCCESS)
    {
        return ret;
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
ITSSS7DLLAPI int
SCCP_RemSSEntry_ANSI(SCCPSubSystemInfo *data)
{
    ROUTE_MatchInfo rinfo;

    rinfo.linkSet = data->linkSet;
    rinfo.linkCode = 0;
    rinfo.priority = 0;
    rinfo.sls = 0;
    rinfo.rkey = 0;

    if (data->isLocal)
    {
        rinfo.basic.type = LOCAL_ROUTE;
    }
    else
    {
        rinfo.basic.type = REMOTE_ROUTE;
    }

    rinfo.basic.style = ROUTE_DPC_SIO_SSN;
    rinfo.basic.family = FAMILY_ANSI;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.dpc = data->pointcode;
    rinfo.basic.criteria.ssn = data->ssn;
    rinfo.basic.criteria.sio = data->ni | ROUTE_SIO_SCCP;

    return (ROUTE_DeleteRouteContextInfo(&rinfo));
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
ITSSS7DLLAPI SCCPPointCodeInfo*
SCCP_GetPointCodeEntry_ANSI(ITS_OCTET ni, ITS_UINT pc)
{
    SCCPPointCodeInfo *ret;
    SS7_Destination *dest;
    ITS_UINT i;

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return (NULL);
    }

    dest = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);
    if (dest == NULL)
    {
        ROUTE_UnlockTable();

        return (NULL);
    }

    if ((ret = (SCCPPointCodeInfo *)calloc(1, sizeof(SCCPPointCodeInfo))) ==
        NULL)
    {
        ROUTE_UnlockTable();

        return (NULL);
    }

    ret->pointCode = pc;
    ret->ni = ni;
    ret->isPointcodeProhibited = 0;
    ret->pcCongestLevel = 0;
    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->entries[i]->basic.style == ROUTE_DPC_NI ||
            dest->entries[i]->basic.style == ROUTE_DPC_OPC_NI)
        {
            if (dest->entries[i]->linkSet->adjacent == pc)
            {
                ret->isAdjacent = ITS_TRUE;

                break;
            }
        }
    }

    ROUTE_UnlockTable();

    return (ret);
}

/*
 * parser struct
 */
typedef struct
{
    SCCPPointCodeInfo   **entries;
    ITS_UINT            *numEntries;
}
PCIterStruct;

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
static int
GetAllDests(ITS_POINTER entry, void *in, void *out)
{
    SS7_Destination *dest = (SS7_Destination *)entry;
    PCIterStruct *iter = (PCIterStruct *)in;
    ITS_UINT i;

    for (i = 0; i < dest->numEntries; i++)
    {
        ROUTE_Info *rinfo = dest->entries[i];

        if (rinfo->basic.family != FAMILY_ANSI)
        {
            continue;
        }

        if (rinfo->basic.type != ROUTING_KEY_ROUTE)
        {
            ITS_UINT which = *iter->numEntries;
            SCCPPointCodeInfo *ent;

            (*iter->numEntries)++;
            (*iter->entries) = (SCCPPointCodeInfo *)realloc(*iter->entries,
                                                            *iter->numEntries *
                                                             sizeof(SCCPPointCodeInfo));
            ent = &(*iter->entries)[which];

            if (*iter->entries != NULL)
            {
                ent->pointCode = rinfo->basic.dpc;
                ent->ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
                ent->variant = ITS_THIRD_GEN;       /* FIXME */
                ent->isPointcodeProhibited = 0;
                ent->isAdjacent = (rinfo->linkSet->adjacent ==
                                   rinfo->basic.dpc);
                ent->linkSet = rinfo->linkSet->linkSet;
            }

            break;
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
ITSSS7DLLAPI void
SCCP_GetAllPointCodeEntries_ANSI(ITS_UINT* numEntries,
                                 SCCPPointCodeInfo** entries)
{
    PCIterStruct iter;

    *entries = NULL;
    *numEntries = 0;

    iter.entries = entries;
    iter.numEntries = numEntries;

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS,
                     &iter, NULL, GetAllDests);

    ROUTE_UnlockTable();
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
ITSSS7DLLAPI int
SCCP_SetPointCodeEntry_ANSI(SCCPPointCodeInfo *data)
{
    ROUTE_MatchInfo rinfo;
    int ret;

    rinfo.linkSet = data->linkSet;
    rinfo.linkCode = 0;
    rinfo.priority = 0;
    rinfo.sls = 0;
    rinfo.rkey = 0;

    rinfo.basic.type = REMOTE_ROUTE;
    rinfo.basic.style = ROUTE_DPC_NI;
    rinfo.basic.family = FAMILY_ANSI;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.dpc = data->pointCode;
    rinfo.basic.criteria.sio = data->ni & ROUTE_NI_MASK;

    ret = ROUTE_AddRouteContextInfo(&rinfo);

    if (ret != ITS_SUCCESS)
    {
        return ret;
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
ITSSS7DLLAPI int
SCCP_RemPointCodeEntry_ANSI(SCCPPointCodeInfo *data)
{
    ROUTE_MatchInfo rinfo;
    int ret;

    rinfo.linkSet = data->linkSet;
    rinfo.linkCode = 0;
    rinfo.priority = 0;
    rinfo.sls = 0;
    rinfo.rkey = 0;

    rinfo.basic.type = REMOTE_ROUTE;
    rinfo.basic.style = ROUTE_DPC_NI;
    rinfo.basic.family = FAMILY_ANSI;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.dpc = data->pointCode;
    /* rinfo.basic.criteria.sio = data->ni & ROUTE_NI_MASK; */
    rinfo.basic.criteria.sio = data->ni | 0x03;

    ret = ROUTE_DeleteRouteContextInfo(&rinfo);

    if (ret != ITS_SUCCESS)
    {
        return ret;
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
ITSSS7DLLAPI SCCPConcernedPCInfo*
SCCP_GetConcernedPC_ANSI(ITS_UINT sspc, ITS_OCTET ni,
                         ITS_OCTET ssn, ITS_UINT cpc)
{
    ITS_INT ctxt = sspc | (ni & MTP3_NIC_MASK) << 24;
    ROUTE_Info *current;
    SCCPConcernedPCInfo *ret;
    int error;
    
    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return (NULL);
    }

    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_UINT),
                                                &error)) != NULL)
    {
        while (current != NULL)
        {
            if (current->basic.dpc == cpc)
            {
                ret = (SCCPConcernedPCInfo *)malloc(sizeof(SCCPConcernedPCInfo));

                if (ret == NULL)
                {
                    ROUTE_UnlockTable();

                    return (NULL);
                }

                ret->sspc = sspc;
                ret->ni = ni;
                ret->ssn = ssn;
                ret->cpc = cpc;

                ROUTE_UnlockTable();

                return (ret);
            }

            current = current->next;
        }
    }

    ROUTE_UnlockTable();

    return (NULL);
}

/*
 * parser struct
 */
typedef struct
{
    SCCPConcernedPCInfo **entries;
    ITS_UINT            *numEntries;
}
CPCIterStruct;

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
static int
GetAllConcerned(ITS_POINTER entry, void *in, void *out)
{
    ROUTE_Info *rinfo = (ROUTE_Info *)entry;
    CPCIterStruct *iter = (CPCIterStruct *)in;
    ITS_UINT which;
    SCCPConcernedPCInfo *ent;

    if (rinfo->basic.family != FAMILY_ANSI)
    {
        return (ITS_SUCCESS);
    }

    while (rinfo != NULL)
    {
        which = *iter->numEntries;

        (*iter->numEntries)++;
        (*iter->entries) = (SCCPConcernedPCInfo *)realloc(*iter->entries,
                                                          *iter->numEntries *
                                                           sizeof(SCCPConcernedPCInfo));
        ent = &(*iter->entries)[which];

        if (*iter->entries != NULL)
        {
            ent->sspc = rinfo->basic.criteria.opc;
            ent->ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
            ent->ssn = (ITS_OCTET)rinfo->basic.criteria.cic;
            ent->cpc = rinfo->basic.dpc;
        }

        rinfo = rinfo->next;
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
ITSSS7DLLAPI void
SCCP_GetAllCPCEntries_ANSI(ITS_UINT* numEntries,
                           SCCPConcernedPCInfo** entries)
{
    CPCIterStruct iter;

    *entries = NULL;
    *numEntries = 0;

    iter.entries = entries;
    iter.numEntries = numEntries;

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC,
                     &iter, NULL, GetAllConcerned);

    ROUTE_UnlockTable();
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
ITSSS7DLLAPI int
SCCP_SetConcernedPC_ANSI(SCCPConcernedPCInfo* data)
{
    ROUTE_Info* rinfo, cinfo, *tlList;
    ITS_INT error;

    memset(&cinfo, 0, sizeof(cinfo));

    cinfo.basic.type = CONCERNED_ROUTE;
   // cinfo.basic.style = ROUTE_DPC_SIO_SSN;
    cinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
    cinfo.basic.family = FAMILY_ANSI;
    cinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
    cinfo.basic.dpc = data->cpc;
    cinfo.basic.criteria.sio = data->ni & ROUTE_NI_MASK;
    cinfo.basic.criteria.sio |= ROUTE_SIO_SCCP;
    cinfo.basic.criteria.opc = data->sspc;
    cinfo.basic.criteria.ssn = data->ssn;
    cinfo.basic.criteria.cic = data->ssn;


    if ((error = DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS)) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to lock destinations table\n"));

        return error;
    }

    FreeList(lpcList);
    lpcList = NULL;
    /*
     * build local list
     */
    if ((error = DSM_TableIterate(DSM_RoutingFtGroupId,
                         DSM_TABLE_DESTINATIONS,
                         NULL, NULL, GatherLocal)) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_SetConcernedPC: Can't dump local routes\n"));

        FreeList(lpcList);
        lpcList = NULL;

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return error;
    }

    if (lpcList == NULL)
    {
        SCCP_WARNING(("SCCP_SetConcernedPC: Have concerned information, but no "
                      "associated local SSN.  Config problem\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return ITS_ENOTCONFIG;
    }

    tlList = lpcList;
    lpcList = NULL;

    for (rinfo = tlList; rinfo != NULL; rinfo = rinfo->next)
    {

        if (IsConcerned(rinfo, &cinfo))
        {
            error = SCCP_AddConcernedSubSystem_ANSI(rinfo, &cinfo);
            if (error != ITS_SUCCESS)
            {
                DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

                return (error);
            }
        }
    }

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

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
ITSSS7DLLAPI int
SCCP_RemConcernedPC_ANSI(SCCPConcernedPCInfo* data)
{
    ITS_INT ctxt = data->sspc | (data->ni & MTP3_NIC_MASK) << 24;
    ROUTE_Info *current;
    ROUTE_Info *prev = NULL;
    int error;
    
    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_UINT),
                                                &error)) != NULL)
    {
        while (current != NULL)
        {

            if (current->basic.dpc == data->cpc)
            {
                if (prev != NULL)
                {
                    prev->next = current->next;

                    error = DSM_CommitNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_LPC,
                                             (ITS_OCTET *)&ctxt, 
                                             sizeof(ITS_UINT), prev);

                    if (error != ITS_SUCCESS)
                    {
                        ROUTE_UnlockTable();

                        return error;
                    }
                }
                  DSM_FreeNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_UINT),
                                                current);

                break;
            }

            prev = current;
            current = current->next;
        }
    }

    ctxt = data->cpc | (data->ni & MTP3_NIC_MASK) << 24;
    prev = NULL;

    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_UINT),
                                                &error)) != NULL)
    {
        while (current != NULL)
        {

            if (current->basic.dpc == data->sspc && 
              current->basic.criteria.ssn == data->ssn)
            {
                if (prev != NULL)
                {
                    prev->next = current->next;

                    error = DSM_CommitNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_CPC,
                                             (ITS_OCTET *)&ctxt, 
                                             sizeof(ITS_UINT), prev);

                    if (error != ITS_SUCCESS)
                    {
                        ROUTE_UnlockTable();

                        return error;
                    }
                }

                 DSM_FreeNoLock(DSM_SccpFtGroupId,
                                DSM_TABLE_ANSI_SCCP_CPC,
                                (ITS_OCTET *)&ctxt,
                                 sizeof(ITS_UINT),
                                  current);

                ROUTE_UnlockTable();

                return ITS_SUCCESS;
            }

            prev = current;

            current = current->next;
        }
    }

    ROUTE_UnlockTable();

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
ITSSS7DLLAPI SCCPConcernedSSInfo*
SCCP_GetConcernedSS_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn, 
                         ITS_UINT cpc, ITS_OCTET cssn)
{
    ITS_INT ctxt = pc | (ni & MTP3_NIC_MASK) << 24;
    ROUTE_Info *current;
    SCCPConcernedSSInfo *ret;
    ITS_OCTET sio = ni | ROUTE_SIO_SCCP;
    int error;
    
    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return (NULL);
    }

    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&ctxt,
                                                sizeof(ITS_UINT),
                                                &error)) != NULL)
    {
        while (current != NULL)
        {
            if (current->basic.dpc == cpc &&
                (ITS_OCTET)current->basic.criteria.ssn == cssn &&
                 current->basic.criteria.opc == pc &&
                  current->basic.criteria.sio == sio)
            {
                ret = (SCCPConcernedSSInfo *)malloc(sizeof(SCCPConcernedSSInfo));

                if (ret == NULL)
                {
                    ROUTE_UnlockTable();

                    return (NULL);
                }

                ret->pc = pc;
                ret->ni = ni;
                ret->ssn = ssn;
                ret->cpc = cpc;
                ret->cssn = cssn;

                ROUTE_UnlockTable();

                return (ret);
            }

            current = current->next;
        }
    }

    ROUTE_UnlockTable();

    return (NULL);
}

/*
 * parser struct
 */
typedef struct
{
    SCCPConcernedSSInfo **entries;
    ITS_UINT            *numEntries;
}
CSSIterStruct;

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
static int
GetAllConcernedSS(ITS_POINTER entry, void *in, void *out)
{
    ROUTE_Info *rinfo = (ROUTE_Info *)entry;
    CSSIterStruct *iter = (CSSIterStruct *)in;
    ITS_UINT which;
    SCCPConcernedSSInfo *ent;
    ITS_BOOLEAN inService;

    if (rinfo->basic.family != FAMILY_ANSI)
    {
        return (ITS_SUCCESS);
    }

    while (rinfo != NULL)
    {
        which = *iter->numEntries;

        (*iter->numEntries)++;
        (*iter->entries) = (SCCPConcernedSSInfo *)realloc(*iter->entries,
                                                          *iter->numEntries *
                                                           sizeof(SCCPConcernedSSInfo));
        ent = &(*iter->entries)[which];

        if (*iter->entries != NULL)
        {
            ent->cpc = rinfo->basic.dpc;
            ent->cssn = rinfo->basic.criteria.ssn;
            ent->ni = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
            ent->ssn = (ITS_OCTET)rinfo->basic.criteria.cic;
            ent->pc = rinfo->basic.criteria.opc;

            inService = SCCP_IsSSNAllowed_ANSI(ent->ni,ent->cpc,ent->cssn); 
            ent->inservice = inService;
        }

        rinfo = rinfo->next;
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
ITSSS7DLLAPI void
SCCP_GetAllCSSEntries_ANSI(ITS_UINT* numEntries,
                           SCCPConcernedSSInfo** entries)
{
    CSSIterStruct iter;

    *entries = NULL;
    *numEntries = 0;

    iter.entries = entries;
    iter.numEntries = numEntries;

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC,
                     &iter, NULL, GetAllConcernedSS);

    ROUTE_UnlockTable();
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
ITSSS7DLLAPI int
SCCP_SetConcernedSS_ANSI(SCCPConcernedSSInfo *data)
{
    ROUTE_Info* rinfo, cinfo, *tlList;
    SCCPConcernedSSInfo* tmp = NULL;
    ITS_BOOLEAN found = ITS_FALSE;
    ITS_INT error;
    SCCP_ERROR(("Entering SCCP_SetConcernedSS_ANSI\n"));
    tmp = SCCP_GetConcernedSS_ANSI(data->pc,
                                   data->ni,
                                   data->ssn,
                                   data->cpc,
                                   data->cssn);
    if (tmp)
    {
        return ITS_EDUPLENTRY;
    }

    memset(&cinfo, 0, sizeof(cinfo));

    cinfo.basic.type = CONCERNED_ROUTE;
    /*cinfo.basic.style = ROUTE_DPC_SIO_SSN;*/
    cinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
    cinfo.basic.family = FAMILY_ANSI;
    cinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
    cinfo.basic.dpc = data->cpc;
    cinfo.basic.criteria.sio = data->ni & ROUTE_NI_MASK;
    cinfo.basic.criteria.sio |= ROUTE_SIO_SCCP;
    cinfo.basic.criteria.opc = data->pc;
    cinfo.basic.criteria.ssn = data->cssn;
    cinfo.basic.criteria.cic = data->ssn;


    if ((error = DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS)) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to lock destinations table\n"));

        return error;
    }

    FreeList(lpcList);
    lpcList = NULL;
    /*
     * build local list
     */
    if ((error = DSM_TableIterate(DSM_RoutingFtGroupId,
                         DSM_TABLE_DESTINATIONS,
                         NULL, NULL, GatherLocal)) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_SetConcernedSS: Can't dump local routes\n"));
        
        FreeList(lpcList);
        lpcList = NULL;

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return error;
    }

    if (lpcList == NULL)
    {
        SCCP_WARNING(("SCCP_SetConcernedSS: Have concerned information, but no "
                      "associated local SSN.  Config problem\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return ITS_ENOTCONFIG;
    }

   tlList = lpcList;
   lpcList = NULL;
    for (rinfo = tlList; rinfo != NULL; rinfo = rinfo->next)
    {

        if (IsConcerned(rinfo, &cinfo))
        {
            error = SCCP_AddConcernedSubSystem_ANSI(rinfo, &cinfo);
            if (error != ITS_SUCCESS)
            {
                DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

                return (ITS_EDUPLENTRY);
            }
            found = ITS_TRUE;
        }
    }

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

    if (found == ITS_TRUE)
    {
        return (ITS_SUCCESS);
    }
    else
    {
        return ITS_ENOTFOUND;
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
ITSSS7DLLAPI int
SCCP_RemConcernedSS_ANSI(SCCPConcernedSSInfo *data)
{
    ITS_INT CPC_ctxt = data->cpc | (data->ni & MTP3_NIC_MASK) << 24;
    ITS_INT LPC_ctxt ;
    ROUTE_Info *current;
    ROUTE_Info *prev = NULL;
    int error,count = 0;
    ITS_BOOLEAN found = ITS_FALSE;
    
    if ((error = ROUTE_LockTable()) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_RemConcernedSS_ANSI:Unable to fetch lock for Destination table[25] from ROUTE_LockTable  \n"));
        return (error);
    }
     SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:Removing Route for  data->pc[%d]:data->cpc[%d]:data->cssn[%d]:data->ssn[%d]:data->ni[%d]:",data->pc,data->cpc,data->cssn,data->ssn,data->ni));

for (count=1; count<=4 ; count++)
{
 switch(count)
 {
   case 1:
     data->ni = MTP3_NIC_INTERNATIONAL ;
     SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:  DELETING FOR NI VALUE[%d]:ISIL_NIC_INTERNATIONAL",data->ni));
     break;
   case 2:
     data->ni = MTP3_NIC_NATIONAL;
     SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:  DELETING FOR NI VALUE[%d]:ISIL_NIC_NATIONAL",data->ni));
     break;
   case 3:
     data->ni = MTP3_NIC_SPARE ;
     SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:  DELETING FOR NI VALUE[%d]:ISIL_NIC_SPARE",data->ni));
     break;
   case 4:
     data->ni = MTP3_NIC_RESERVED ;
     SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:  DELETING FOR NI VALUE[%d]:ISIL_NIC_RESERVED",data->ni));
     break;
   default:
     SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:  Default Case:wrong NI value"));
 }
    LPC_ctxt = data->pc | (data->ni & MTP3_NIC_MASK) << 24;
    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&LPC_ctxt,
                                                sizeof(ITS_UINT),
                                                &error)) != NULL)
    {
        while (current != NULL)
        {

            if (current->basic.dpc == data->cpc &&
               current->basic.criteria.ssn == data->cssn)
            {
                if (prev != NULL)
                {
                    prev->next = current->next;

                    error = DSM_CommitNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_LPC,
                                             (ITS_OCTET *)&LPC_ctxt, 
                                             sizeof(ITS_UINT), prev);

                    if (error != ITS_SUCCESS)
                    {
                        SCCP_ERROR(("SCCP_RemConcernedSS_ANSI:Unable to commit in DSM_TABLE_ANSI_SCCP_LPC \n"));
                        ROUTE_UnlockTable();

                        return error;
                    }
                }
                  DSM_FreeNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_LPC,
                                                (ITS_OCTET *)&LPC_ctxt,
                                                sizeof(ITS_UINT),
                                                current);
                found = ITS_TRUE;
                break;
            }

            prev = current;
            current = current->next;
        }
    }
    if (!found)
    {
        SCCP_ERROR(("SCCP_RemConcernedSS_ANSI:No Entry found in DSM_TABLE_ANSI_SCCP_LPC:found[%d] \n",found));
        return (ITS_ENOTFOUND);
    }
    found = ITS_FALSE;
}

    SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:ALL LPC Node DELETED SUCCESSFULLY \n"));
    prev = NULL;
    count = 0;
   for(count = 1; count<=4; count++)
  {
        SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI:Going to delete Entry from DSM_TABLE_ANSI_SCCP_CPC:CPC_ctxt[%d]: DPC[%d]:SSN[%d]:count[%d]\n",CPC_ctxt,data->pc,data->ssn,count));
    if ((current = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CPC,
                                                (ITS_OCTET *)&CPC_ctxt,
                                                sizeof(ITS_UINT),
                                                &error)) != NULL)
    {
        while (current != NULL)
        {

            if (current->basic.dpc == data->pc && 
              current->basic.criteria.ssn == data->ssn)
            {
                if (prev != NULL)
                {
                    prev->next = current->next;

                    error = DSM_CommitNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_CPC,
                                             (ITS_OCTET *)&CPC_ctxt, 
                                             sizeof(ITS_UINT), prev);

                    if (error != ITS_SUCCESS)
                    {
                        ROUTE_UnlockTable();

                        return error;
                    }
                }
                 DSM_FreeNoLock(DSM_SccpFtGroupId,
                                DSM_TABLE_ANSI_SCCP_CPC,
                                (ITS_OCTET *)&CPC_ctxt,
                                 sizeof(ITS_UINT),
                                  current);
              if(count == 4)
							{
									ROUTE_UnlockTable();
							  	SCCP_DEBUG(("SCCP_RemConcernedSS_ANSI: ALL CPC Entry DELETED Successfully  \n"));
									return (ITS_SUCCESS);
							}
              break;
            }

            prev = current;

            current = current->next;
        }
    }
   
   }
   
    ROUTE_UnlockTable();

    return (ITS_ENOTFOUND);
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
static void
FreeList(ROUTE_Info* list)
{
    ROUTE_Info* tmp, *tmp2;

    if (!list)
    {
        return;
    }

    for (tmp = list; tmp != NULL; tmp = tmp2)
    {
        tmp2 = tmp->next;

        free(tmp);
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
static int
GatherConcerned(ITS_POINTER data,
                void *in, void *out)
{
    SS7_Destination *ent = (SS7_Destination *)data;
    ROUTE_Info *tmp, *rinfo;
    ITS_UINT i;

    for (i = 0; i < ent->numEntries; i++)
    {
        rinfo = ent->entries[i];

        if (rinfo->basic.family == FAMILY_ANSI &&
            rinfo->basic.type == CONCERNED_ROUTE &&
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN ||
             rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE))
        {
            if ((tmp = (ROUTE_Info *)malloc(sizeof(ROUTE_Info))) == NULL)
            {
                SCCP_CRITICAL(("GatherConcerned: Out of memory\n"));


                FreeList(cpcList);

                return (ITS_ENOMEM);
            }

            *tmp = *rinfo;
            tmp->next = cpcList;
            cpcList = tmp;
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
static int
GatherLocal(ITS_POINTER data,
            void *in, void *out)
{
    SS7_Destination *ent = (SS7_Destination *)data;
    ROUTE_Info *tmp, *rinfo;
    ITS_UINT i;

    for (i = 0; i < ent->numEntries; i++)
    {
        rinfo = ent->entries[i];

        if (rinfo->basic.family == FAMILY_ANSI &&
            rinfo->basic.type == LOCAL_ROUTE &&
            (rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
             rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN ||
             rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
             rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE))
        {
            if ((tmp = (ROUTE_Info *)malloc(sizeof(ROUTE_Info))) == NULL)
            {
                SCCP_CRITICAL(("GatherLocal: Out of memory\n"));

                FreeList(lpcList);


                return (ITS_ENOMEM);
            }

            *tmp = *rinfo;
            tmp->next = lpcList;
            lpcList = tmp;
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
static int
GatherDuplicated(ITS_POINTER data,
                 void *in, void *out)
{
    SS7_Destination *ent = (SS7_Destination *)data;
    ROUTE_Info *tmp, *rinfo;
    ITS_UINT i;

    for (i = 0; i < ent->numEntries; i++)
    {
        rinfo = ent->entries[i];

        if (rinfo->basic.family == FAMILY_ANSI &&
            rinfo->basic.type == DUPLICATED_ROUTE &&
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN ||
             rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE))
        {
            if ((tmp = (ROUTE_Info *)malloc(sizeof(ROUTE_Info))) == NULL)
            {
                SCCP_CRITICAL(("GatherLocal: Out of memory\n"));

                FreeList(dpcList);
                return (ITS_ENOMEM);
            }

            *tmp = *rinfo;
            tmp->next = dpcList;
            dpcList = tmp;
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
static void
BuildCPCData()
{
    ROUTE_Info* rinfo;
    ROUTE_Info* tcList, *tlList;
    SCCPConcernedSSInfo* tmp = NULL;

    SCCP_DEBUG(("BuildCPCData: Build information\n"));

    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to lock destinations table\n"));


        return;
    }

    /*
     * build concerned list
     */
    if (DSM_TableIterate(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS,
            NULL, NULL, GatherConcerned) != ITS_SUCCESS)
    {
        SCCP_ERROR(("BuildCPCData: Can't dump concerned routes\n"));

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return;
    }

    initializing = ITS_TRUE;

    /*
     * if we're not concerned about anybody, we won't be sending
     * SST/SSP/SSA messages to them, so bail out.
     */
    if (cpcList == NULL)
    {
        SCCP_DEBUG(("BuildCPCData: Not concerned about any external ssn(s)\n"));

        initializing = ITS_FALSE;

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return;
    }

    /*
     * build local list
     */
    if (DSM_TableIterate(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS,
                         NULL, NULL, GatherLocal) != ITS_SUCCESS)
    {
        SCCP_ERROR(("BuildCPCData: Can't dump local routes\n"));

        FreeList(cpcList);
        cpcList = NULL;
        FreeList(lpcList);
        lpcList = NULL;

        initializing = ITS_FALSE;

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return;
    }

    /*
     * If we have no local list, the user misconfigured us.
     */
    if (lpcList == NULL)
    {
        SCCP_WARNING(("BuildCPCData: Have concerned information, but no "
                      "associated local SSN.  Config problem\n"));

        FreeList(cpcList);
        cpcList = NULL;

        initializing = ITS_FALSE;

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return;
    }

    /*
     * walk the two lists, adding concerned and local entries
     * as appropriate.  This is a O(N^2) operation, but we
     * only perform it at startup, so I can live with it.
     */
    tcList = cpcList;
    tlList = lpcList;
    cpcList = NULL;
    lpcList = NULL;
    for (rinfo = tlList; rinfo != NULL; rinfo = rinfo->next)
    {
        ROUTE_Info *cinfo;

        for (cinfo = tcList; cinfo != NULL; cinfo = cinfo->next)
        {
            /* check it */
            if (IsConcerned(rinfo, cinfo))
            {
                tmp = SCCP_GetConcernedSS_ANSI(rinfo->basic.dpc,
                                  cinfo->basic.criteria.sio,
                                  rinfo->basic.criteria.ssn,
                                  cinfo->basic.dpc,
                                  cinfo->basic.criteria.ssn);
                if (!tmp)
                {
                    SCCP_AddConcernedSubSystem_ANSI(rinfo, cinfo);
                }
                else
                {
                    SCCP_WARNING(("Duplicate concerned subsystem"));
                }
            }
        }
    }

    initializing = ITS_FALSE;

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);
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
static void
DeleteCPCData()
{
    ROUTE_Info* rinfo;

    SCCP_DEBUG(("DeleteCPCData: Delete information\n"));

    /*
     * walk the two lists, adding concerned and local entries
     * as appropriate.  This is a O(N^2) operation, but we
     * only perform it at startup, so I can live with it.
     */
    for (rinfo = lpcList; rinfo != NULL; rinfo = rinfo->next)
    {
        ROUTE_Info *cinfo;

        for (cinfo = cpcList; cinfo != NULL; cinfo = cinfo->next)
        {
            /* check it */
            if (IsConcerned(rinfo, cinfo))
            {
                SCCP_RemConcernedSubSystem_ANSI(rinfo, cinfo);
            }
        }
    }

    FreeList(cpcList);
    cpcList = NULL;
    FreeList(lpcList);
    lpcList = NULL;
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
static void
BuildDupData()
{
    ROUTE_Info *rinfo;
    ROUTE_Info *tdList;

    if (DSM_LockTable(
            DSM_RoutingFtGroupId, 
            DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to lock destinations table\n"));

        return;
    }

    initializing = ITS_TRUE;

    /*
     * now do the duplicated routes
     */
    if (DSM_TableIterate(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS,
                         NULL, NULL, GatherDuplicated) != ITS_SUCCESS)
    {
        SCCP_ERROR(("BuildCPCData: Can't dump concerned routes\n"));

        initializing = ITS_FALSE;

        DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

        return;
    }

    /* for each duplicated route, store local info */
    tdList = dpcList;
    dpcList = NULL;
    for (rinfo = tdList; rinfo != NULL; rinfo = rinfo->next)
    {
        SCCP_AddDuplicatedSubSystem_ANSI(rinfo);
    }

    initializing = ITS_FALSE;

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);
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
static void
DeleteDupData()
{
    ROUTE_Info *rinfo;

    /* for each duplicated route, delete local info */
    for (rinfo = dpcList; rinfo != NULL; rinfo = rinfo->next)
    {
        SCCP_RemDuplicatedSubSystem_ANSI(rinfo);
    }

    FreeList(dpcList);
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
static void
HandleMTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT* ev = (ITS_EVENT *)callData;
    ITS_EVENT tmp;

    ITS_EVENT_INIT(&tmp, ev->src, ev->len);
    memcpy(tmp.data, ev->data, ev->len);

    if (TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, ev) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&tmp);
    }
    else
    {
        *ev = tmp;
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
static void
CheckTimeout(ITS_TimerData *td)
{
    ITS_SERIAL *serial;
    ITS_UINT key;
    int error;
    SST_Info *tmp=NULL;
    SST_Key  Skey;
   ITS_INT SSTkey;

        SCCP_ERROR((" ANSI:: Handle Timer Expiry\n"));
    /* lock it. */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_MGMT_DATA_SCCP_SST) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't get serial data\n"));

        return;
    }

//    key = DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL;
/*    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA,
                                 (ITS_OCTET *)&key, sizeof(ITS_UINT),
                                 &error)) != NULL &&
        error == ITS_SUCCESS)*/
    memcpy(&Skey,td->context,sizeof(SST_Key));
    SCCP_DEBUG(("dpc %d ssn %d ",Skey.dpc,Skey.ssn));
    SSTkey=Skey.dpc|(Skey.sio << 24)|(DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL <<16);
    if ((tmp = DSM_FindNoLock (DSM_SccpFtGroupId,DSM_TABLE_ANSI_SCMG,
                                (ITS_OCTET *) &SSTkey, sizeof (ITS_INT),
                                                 &error)) != NULL)

    {
        if (td->serial == tmp->serial)
        {
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_SST);
        SCCP_ERROR((" ANSI:: Handle SST Timer Expiry\n"));

            SCMGHandleSSTTimeout_ANSI(td);

            return;
        }
    }

    key = DSM_MGMT_REC_ANSI_SCCP_SOR_SERIAL;
    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA_SCCP_SST,
                                 (ITS_OCTET *)&key, sizeof(ITS_UINT),
                                 &error)) != NULL &&
        error == ITS_SUCCESS)
    {
        if (td->serial == *serial)
        {
            /* Handle SOR Timeouts */
            SCCP_DEBUG(("SOR Timer expired. \n"));
 

            *serial = 0;

            DSM_CommitNoLock(DSM_SccpFtGroupId,
                             DSM_TABLE_MGMT_DATA_SCCP_SST,
                             (ITS_OCTET *)&key, sizeof(ITS_UINT),
                             serial);

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_SST);

            return;
        }
    }

    key = DSM_MGMT_REC_ANSI_SCCP_SST_IGNORE_SERIAL;
    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA_SCCP_SST,
                                 (ITS_OCTET *)&key, sizeof(ITS_UINT),
                                 &error)) != NULL &&
        error == ITS_SUCCESS)
    {
        if (td->serial == *serial)
        {
            SCCP_DEBUG(("SST Ignore Timer Expired.\n"));


            *serial = 0;

            DSM_CommitNoLock(DSM_SccpFtGroupId,
                             DSM_TABLE_MGMT_DATA_SCCP_SST,
                             (ITS_OCTET *)&key, sizeof(ITS_UINT),
                             serial);

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_SST);

            return;
        }
    }

    /* release the table */
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_SST);

    /* default handling */
    if (((SCCP_REASM_CTXT *)(td->context))->type == SCLC_TIMER_TYPE)
    {
        SCCP_DEBUG(("XUDT Reassembly Timer Expired.\n"));

        SCLCHandleReasmTimer_ANSI(td);
    }
    else if(((SCCP_CONN_CTXT *)(td->context))->type== SCOC_TIMER_TYPE )
    {
      SCCP_DEBUG(("CO Timer Expired.\n"));
       SCOCHandleTimer_ANSI(td);
    }
   else
    {
      SCCP_ERROR(("Neither CO and CL Timer Expired.\n"));
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
static void
InitSettings()
{
    /*
     * timers
     */
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_statInfo, 30);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_coordChg, 30);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ignoreSST, 30);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_rtgStatInfo, 30);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_conn, 180);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_release, 10);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reset, 20);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ias, 300);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_iar, 660);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_guard, 240);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reassembly, 10);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_interval, 30);
    TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_repeatRelease, 10);

    /*
     * behavior control
     */
    BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT,
                          ITS_FALSE);
    BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR,
                          ITS_FALSE);
    BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG,
                          ITS_TRUE);
    BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_use_SCMG,
                          ITS_TRUE);

    /*
     * determine tracing from INI files
     */
    if (TRANSPORT_RES(__SCCP_ANSI_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__SCCP_ANSI_RcvQueue);
        char *name = TRANSPORT_NAME(__SCCP_ANSI_RcvQueue);

        /* get the number of threads */
        if (RESFILE_GetKeyValueOf(res, name, NUM_THREADS_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            numThreads = atoi(value);
            if (numThreads < 1)
            {
                numThreads = 1;
            }
        }

        /* get the timers */
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TSTAT_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_statInfo,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TCOORD_CHG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_coordChg,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TIGNORE_SST_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ignoreSST,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRTG_STAT_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_rtgStatInfo,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TCONN_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_conn,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRESET_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reset,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRELEASE_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_release,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TINACT_SEND_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ias,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TINACT_RECV_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_iar,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TGUARD_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_guard,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TREASSEM_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reassembly,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TINTERVAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_interval,
                                 atoi(value));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TREPEAT_REL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_repeatRelease,
                                 atoi(value));
        }


        /* See if ERR and IT go to the user */
        if (RESFILE_GetKeyValueOf(res, name, SCCP_PROPAGATE_IT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors,
                                  SCCP_B_propagate_IT,
                                  (strcmp(value, "yes") == 0 ||
                                   strcmp(value, "YES") == 0));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_PROPAGATE_ERR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors,
                                  SCCP_B_propagate_ERR,
                                  (strcmp(value, "yes") == 0 ||
                                   strcmp(value, "YES") == 0));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_PROPAGATE_SCMG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors,
                                  SCCP_B_propagate_SCMG,
                                  (strcmp(value, "yes") == 0 ||
                                   strcmp(value, "YES") == 0));
        }
        if (RESFILE_GetKeyValueOf(res, name, SCCP_ENABLE_SCMG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors,
                                  SCCP_B_use_SCMG,
                                  !(strcmp(value, "no") == 0 ||
                                    strcmp(value, "NO") == 0));
        }

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, SCCP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_CRITICAL_STRING,
                                           SCCP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_CRITICAL_STRING,
                                           SCCP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_CRITICAL_STRING,
                                           SCCP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_CRITICAL_STRING,
                                           SCCP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_CRITICAL_STRING,
                                           SCCP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_CRITICAL_STRING,
                                           SCCP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys) 
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, SCCP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_ERROR_STRING,
                                           SCCP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_ERROR_STRING,
                                           SCCP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_ERROR_STRING,
                                           SCCP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_ERROR_STRING,
                                           SCCP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_ERROR_STRING,
                                           SCCP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_ERROR_STRING,
                                           SCCP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE,  sys = ITS_FALSE;

            if (strstr(value, SCCP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_WARNING_STRING,
                                           SCCP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_WARNING_STRING,
                                           SCCP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_WARNING_STRING,
                                           SCCP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_WARNING_STRING,
                                           SCCP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_WARNING_STRING,
                                           SCCP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_WARNING_STRING,
                                           SCCP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_WARNING_STRING, ITS_FALSE);
            }
        }

        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE,  sys = ITS_FALSE;

            if (strstr(value, SCCP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_DEBUG_STRING,
                                           SCCP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_DEBUG_STRING,
                                           SCCP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_DEBUG_STRING,
                                           SCCP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_DEBUG_STRING,
                                           SCCP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_DEBUG_STRING,
                                           SCCP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_DEBUG_STRING,
                                           SCCP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_DEBUG_STRING, ITS_FALSE);
            }
        }

        /* Event */

        if (RESFILE_GetKeyValueOf(res, name, SCCP_TRACE_EVENT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE,  sys = ITS_FALSE;

            if (strstr(value, SCCP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_EVENT_STRING,
                                           SCCP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_EVENT_STRING,
                                           SCCP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_EVENT_STRING,
                                           SCCP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_EVENT_STRING,
                                           SCCP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, SCCP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_EVENT_STRING,
                                           SCCP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                           SCCP_EVENT_STRING,
                                           SCCP_SYSLOG_STRING, ITS_FALSE);
            }                     
                                                          
            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_EVENT_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData,
                                          SCCP_EVENT_STRING, ITS_FALSE);
            }
        } 
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a generic SCCP message.
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
void
ISCCP_Terminate_ANSI(ITS_SS7_HANDLE handle)
{
    ITS_EVENT ev;
    void *status;
    //ITS_UINT key;
    //ITS_SERIAL *serial;
    int i;
    //int  error;
    ITS_Class dbClass;

    if (!initialized || terminated)
    {
        return;
    }

    terminated = ITS_TRUE;

    SCCP_CRITICAL(("SCCP_Terminate:\n"));

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(SCCP_Console_ANSI);
    }

    DeleteDupData();
    DeleteCPCData();

    CALLBACK_RemCallback(MTP3_ANSI_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    ITS_EVENT_INIT(&ev, ITS_SCCP_ANSI_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&sccpThread[0], &status);

        THREAD_DeleteThread(&sccpThread[0]);
    }
#if 0 /* for redundant mode, we don't want to free the shared memory. */

    /* free the serials */
    key = DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL;
    if ((serial = DSM_Find(DSM_SccpFtGroupId,
                           DSM_TABLE_MGMT_DATA_SCCP_SST,
                           (ITS_OCTET *)&key, sizeof(ITS_UINT),
                           &error)) != NULL &&
        error == ITS_SUCCESS)
    {
        DSM_Free(
            DSM_SccpFtGroupId, 
            DSM_TABLE_MGMT_DATA_SCCP_SST, 
            (ITS_OCTET *)&key, 
            sizeof(ITS_UINT), serial);
    }

    key = DSM_MGMT_REC_ANSI_SCCP_SOR_SERIAL;
    if ((serial = DSM_Find(DSM_SccpFtGroupId,
                           DSM_TABLE_MGMT_DATA_SCCP_SST,
                           (ITS_OCTET *)&key, sizeof(ITS_UINT),
                           &error)) != NULL &&
        error == ITS_SUCCESS)
    {
        DSM_Free(
            DSM_SccpFtGroupId,
            DSM_TABLE_MGMT_DATA_SCCP_SST, 
            (ITS_OCTET *)&key, 
            sizeof(ITS_UINT), serial);
    }

    key = DSM_MGMT_REC_ANSI_SCCP_SST_IGNORE_SERIAL;
    if ((serial = DSM_Find(DSM_SccpFtGroupId,
                           DSM_TABLE_MGMT_DATA_SCCP_SST,
                           (ITS_OCTET *)&key, sizeof(ITS_UINT),
                           &error)) != NULL &&
        error == ITS_SUCCESS)
    {
        DSM_Free(
            DSM_SccpFtGroupId,
            DSM_TABLE_MGMT_DATA_SCCP_SST, 
            (ITS_OCTET *)&key, 
            sizeof(ITS_UINT), 
            serial);
    }
#endif

    free(sccpThread);

    assert(__SCCP_ANSI_RcvQueue != NULL);
    TQUEUETRAN_DeleteTransport(__SCCP_ANSI_RcvQueue);
    SCCP_Alarm_ANSI(423, __FILE__, __LINE__, NULL);

    TRACE_Destructor(SCCP_ANSI_TraceData);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This is a call back method state changes
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
SCCP_StateChangeCallback_ANSI(ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData)
{
    ITS_EVENT *evt = (ITS_EVENT*)callData;

    if (evt->data[1] == ITS_STATE_PRIMARY)
    {
        SCCP_CRITICAL(("SCCP : Request received for change state to active\n"));
    }
    else
    {
        /* Here we have lot of work to do, changing state from active to
         * back up, clean up the  existing transaction TBD
         */
        SCCP_CRITICAL(("SCCP : Request received for change state to backup\n"));
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function starts the SCCP subsystem.
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
 *      If the subsystem is successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ISCCP_Initialize_ANSI(ITS_SS7_HANDLE handle)
{
    int i, j;
    ITS_UINT key;
    ITS_SERIAL *serial;
    int error;
    ITS_Class dbClass;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    if (initialized)
    {
        return (ITS_SUCCESS);
    }

    initialized = ITS_TRUE;

    if ((SCCP_ANSI_TraceData = TRACE_Constructor("ANSI-SCCP",
                                                 SCCP_TraceMap, 5)) == NULL)
    {
        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if (MUTEX_CreateMutex(&sccpGate, 0) != ITS_SUCCESS)
    {
        SCCP_ERROR(("MTP3_Intialize: couldn't create mutex\n"));

        initialized = ITS_FALSE;

        return (ITS_EBADMUTEX);
    }

    memset(userParts, 0, sizeof(userParts));

    if ((__SCCP_ANSI_RcvQueue = TQUEUETRAN_CreateTransport("ANSI-SCCP",
                                                           ITS_SCCP_ANSI_SRC,
                                                           ITS_SCCP_ANSI)) == NULL)
    {
        SCCP_CRITICAL(("SCCP_Initialize: couldn't create transport\n"));
        SCCP_Alarm_ANSI(416, __FILE__, __LINE__, NULL);

        initialized = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    /* read the INI */
    InitSettings();

    if ((sccpThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        SCCP_CRITICAL(("SCCP_Initialize: couldn't create thread array\n"));
        SCCP_Alarm_ANSI(416, __FILE__, __LINE__,NULL);

        TQUEUETRAN_DeleteTransport(__SCCP_ANSI_RcvQueue);

        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&sccpThread[i], 0, ANSI_SCCPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            SCCP_CRITICAL(("SCCP_Initialize: couldn't create thread\n"));

            /* SCCP failed to Intialize -  couldn't create thread */
            /* SCCP_Alarm_ANSI(421, __FILE__, __LINE__, NULL); */

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&sccpThread[j]);

                THREAD_DeleteThread(&sccpThread[j]);
            }

            free(sccpThread);

            TQUEUETRAN_DeleteTransport(__SCCP_ANSI_RcvQueue);

            initialized = ITS_FALSE;
            SCCP_Alarm_ANSI(416, __FILE__, __LINE__,NULL);

            return (ITS_EBADTHREAD);
        }
    }

    CALLBACK_AddCallback(MTP3_ANSI_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    BuildCPCData();
    BuildDupData();
      _PC_Table=HASH_CreateTable();
       SST_HashTable = HASH_CreateTable();

    /* allocate the serials */
    key = DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL;
   
    if (DSM_FindNoLock(DSM_SccpFtGroupId,
                       DSM_TABLE_MGMT_DATA_SCCP_SST,
                       (ITS_OCTET *) &key, sizeof(key), &error) == NULL  ||
         error == ITS_ENOTFOUND)

    {
        SCCP_DEBUG(("DSM Find for SST \n"));

        if ((serial = DSM_Alloc(DSM_SccpFtGroupId,
                                DSM_TABLE_MGMT_DATA_SCCP_SST,
                                (ITS_OCTET *)&key, sizeof(ITS_UINT),
                                sizeof(ITS_SERIAL), &error)) == NULL ||
            error != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to allocate SST serial\n"));

            SCCP_Alarm_ANSI(416, __FILE__, __LINE__,NULL);


            ISCCP_Terminate_ANSI(handle);

            return (ITS_ENOMEM);
        }
        DSM_Commit(
            DSM_SccpFtGroupId, 
            DSM_TABLE_MGMT_DATA_SCCP_SST, 
            (ITS_OCTET *)&key, 
            sizeof(ITS_UINT), serial);

    }

    key = DSM_MGMT_REC_ANSI_SCCP_SOR_SERIAL;

    if (DSM_FindNoLock(DSM_SccpFtGroupId,
                       DSM_TABLE_MGMT_DATA_SCCP_SST,
                       (ITS_OCTET *) &key, sizeof(key), &error) == NULL  ||
         error == ITS_ENOTFOUND)

    {

        if ((serial = DSM_Alloc(DSM_SccpFtGroupId,
                                DSM_TABLE_MGMT_DATA_SCCP_SST,
                                (ITS_OCTET *)&key, sizeof(ITS_UINT),
                                sizeof(ITS_SERIAL), &error)) == NULL ||
            error != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to allocate SOR serial\n"));
            SCCP_Alarm_ANSI(416, __FILE__, __LINE__,NULL);

            ISCCP_Terminate_ANSI(handle);

            return (ITS_ENOMEM);
        }
        DSM_Commit(
            DSM_SccpFtGroupId, 
            DSM_TABLE_MGMT_DATA_SCCP_SST, 
            (ITS_OCTET *)&key, 
            sizeof(ITS_UINT), serial);
    }

    key = DSM_MGMT_REC_ANSI_SCCP_SST_IGNORE_SERIAL;

    if (DSM_FindNoLock(DSM_SccpFtGroupId,
                       DSM_TABLE_MGMT_DATA_SCCP_SST,
                       (ITS_OCTET *) &key, sizeof(key), &error) == NULL  ||
         error == ITS_ENOTFOUND)

    {
        if ((serial = DSM_Alloc(DSM_SccpFtGroupId,
                                DSM_TABLE_MGMT_DATA_SCCP_SST,
                                (ITS_OCTET *)&key, sizeof(ITS_UINT),
                                sizeof(ITS_SERIAL), &error)) == NULL ||
            error != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to allocate SST IGN serial\n"));


            SCCP_Alarm_ANSI(416, __FILE__, __LINE__, NULL);
            ISCCP_Terminate_ANSI(handle);

            return (ITS_ENOMEM);
        }
        DSM_Commit(
            DSM_SccpFtGroupId,
            DSM_TABLE_MGMT_DATA_SCCP_SST, 
            (ITS_OCTET *)&key, 
            sizeof(ITS_UINT), 
            serial);
    }


/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
#ifdef NO_REDUNDANCY
    DSM_LockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#else
    DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);

#endif

    key = DSM_ANSI_SCCP_NEXT_REF_NUM;

#ifdef NO_REDUNDANCY
    if (DSM_FindNoLockLocal(DSM_SccpFtGroupId,
                       DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                       (ITS_OCTET *) &key, sizeof(key), &error) == NULL  ||
         error == ITS_ENOTFOUND)
#else
    if (DSM_FindNoLock(DSM_SccpFtGroupId,
                       DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                       (ITS_OCTET *) &key, sizeof(key), &error) == NULL  ||
         error == ITS_ENOTFOUND)
#endif

    {

        ITS_CTXT *connRefNum = NULL;

#ifdef NO_REDUNDANCY
        connRefNum = (ITS_CTXT *) DSM_AllocNoLockLocal(DSM_SccpFtGroupId,
                                            DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                                            (ITS_OCTET *)&key, sizeof(key),
                                            sizeof(ITS_CTXT),
                                            &error);
#else
        connRefNum = (ITS_CTXT *) DSM_AllocNoLock(DSM_SccpFtGroupId,
                                            DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                                            (ITS_OCTET *)&key, sizeof(key),
                                            sizeof(ITS_CTXT),
                                            &error);
#endif

        if (error != ITS_SUCCESS || connRefNum == NULL)
        {
            SCCP_ERROR(("Failed to allocate SCCP REF NUM serial\n"));
            ISCCP_Terminate_ANSI(handle);
            SCCP_Alarm_ANSI(416, __FILE__, __LINE__, NULL);

#ifdef NO_REDUNDANCY
            DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#else
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#endif

            return (ITS_ENOMEM);

        }

        *connRefNum = 0;

#ifdef NO_REDUNDANCY
        DSM_CommitNoLockLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                   (ITS_OCTET *) &key, sizeof(key), (void *) connRefNum);
#else
        DSM_CommitNoLock(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT,
                   (ITS_OCTET *) &key, sizeof(key), (void *) connRefNum);
#endif

    }


#ifdef NO_REDUNDANCY
    DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#else
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA_SCCP_CTXT);
#endif
/*Patch:Itika:2-Nov-10:End*/


    /* INFORMATIONAL - SCCP Intialized Successfully */
    SCCP_Alarm_ANSI(422, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(SCCP_Console_ANSI);
    }

    /*Check what kind of reduancy type is configured, could be stub also*/
    if (redunClass != NULL)
    {
        /* Means this not stub, it could be either active-standby or
         * active-active, find what config from redundancy class
         */
        if (REDUNDANCY_CONFIGURED_TYPE(redunClass)  == ITS_ACTIVE_STANDBY)
        {
            /* active-stand is configured , register a call back
             * to receive state changes
             */
            CALLBACK_AddCallback(REDUNDANCY_CALLBACK_MGR(redunClass),
                                 SCCP_StateChangeCallback_ANSI, NULL);

            SCCP_DEBUG(("ACTIVE-STANDBY configured registering call back\n"));
        }
        else
        {
            SCCP_DEBUG(("ACTIVE-ACTIVE configured no need to register\n"));
        }
    }
            SCCP_ERROR(("ISCCP_Initialize_ANSI SUCCESS\n"));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the ANSI SCCP thread.
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
 *      This method should be considered an undocumented internal
 *      SCCP function.
 *
 *  See Also:
 ****************************************************************************/
THREAD_RET_TYPE
ANSI_SCCPThread(void *arg)
{
    ITS_EVENT sccpEvent;
    ITS_BOOLEAN cont;
    ITS_TimerData *td;
    int i,ret = 0;

    ITS_INT count=0;
    ITS_OCTET *buff;
    ITS_OCTET TempBuffer[10];
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);
    SCCP_ERROR(("ANSI_SCCPThread Created\n"));

    ITS_C_ASSERT(sizeof(SCCP_CONN_CTXT) <= ITS_MAX_TIMER_CONTEXT);

    MTP3_EnableUserPart_ANSI(MTP3_SIO_SCCP, ITS_SCCP_ANSI_SRC);

    memset(&sccpEvent, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__SCCP_ANSI_RcvQueue) = ITS_TRUE;
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
    Disable_Default_Readflag();
/*Patch:Itika:2-Nov-10:End*/
    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__SCCP_ANSI_RcvQueue))
                                                        (__SCCP_ANSI_RcvQueue,
                                                         &sccpEvent)
           == ITS_SUCCESS)
    {
      if(sccpEvent.src == HEALTH_MANAGER_INSTANCE)
      {
         SCCP_CRITICAL(("HEALTH_MANAGER_INSTANCE: sccpEvent.src = %d",sccpEvent.src));
      }

/*      if((sccpEvent.data[0] != MTP3_MSG_USER_DATA) || (sccpEvent.src == ITS_TIMER_SRC))
       {
            SCCP_DEBUG(("Management message %x\n",sccpEvent.data[0]));
        if (DSM_MulticastStackEventToFtGroupMembers(
               DSM_SccpFtGroupId,
               sccpEvent,
               (sccpEvent.src == ITS_MTP3_SRC)                 ?
                     ITS_GCS_EVENT_FROM_STACK                  :
                (sccpEvent.src == ITS_SCCP_LOCAL_REF_REQUEST   ?
                 ITS_SCCP_LOCAL_REF_RESPONSE                   :
                     ITS_GCS_EVENT_FROM_APPL),
               ITS_SCCP_ANSI_SRC) == ITS_SUCCESS )
        {
            gcsMessageBasedRedundancyIsActive = ITS_TRUE;
            continue;
        }
      }*/

/*Patch:Itika:1-nov-10:Redundancy Merge fix*/
            //SCCP_CRITICAL(("1. Management message 0x%x sccpEvent.src 0x%x\n",sccpEvent.data[0],sccpEvent.src));
//      if((sccpEvent.data[0] == SCCP_MSG_UDT) || (sccpEvent.src == ITS_TIMER_SRC))
      //if((sccpEvent.data[0] == SCCP_MSG_UDT) && (sccpEvent.src == ITS_BSSAP_SRC ))
      if(sccpEvent.src != HEALTH_MANAGER_INSTANCE)
      {
      if(sccpEvent.data[0] == SCCP_MSG_UDT)
      {
            SCCP_CRITICAL((" SCCP_MSG_UDT : ITS_BSSAP_SRC ::len = %d SRC=%d \n",sccpEvent.len,sccpEvent.src));

      }
   if(((sccpEvent.data[0] == SCCP_MSG_UDT) && ((sccpEvent.src != 13072 ) && (sccpEvent.src != 4099))) || (sccpEvent.src == ITS_TIMER_SRC ||sccpEvent.data[0] == MTP3_MSG_PAUSE || sccpEvent.data[0] == MTP3_MSG_RESUME || sccpEvent.data[0] == MTP3_MSG_STATUS))
      {
        // if(sccpEvent.data[0] != MTP3_MSG_USER_DATA) 
        // {
              SCCP_CRITICAL(("Multicasting message %x\n SRC = %d",sccpEvent.data[0],sccpEvent.src));
              if (DSM_MulticastStackEventToFtGroupMembers(
                  DSM_SccpFtGroupId,
                   sccpEvent,
                      (sccpEvent.src == ITS_MTP3_SRC)                 ?
                         ITS_GCS_EVENT_FROM_STACK                  :
                          (sccpEvent.src == ITS_SCCP_LOCAL_REF_REQUEST   ?
                            ITS_SCCP_LOCAL_REF_RESPONSE                   :
                               ITS_GCS_EVENT_FROM_APPL),
                                  ITS_SCCP_ANSI_SRC) == ITS_SUCCESS )

             {
                     gcsMessageBasedRedundancyIsActive = ITS_TRUE;
                     continue;
             }
         // }
        }
        }
/*Patch:Itika:1-nov-10:End*/
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
    /*    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to get route lock\n"));
            break;
        }*/
/*Patch:Itika:2-Nov-10:End*/

        switch (sccpEvent.src)
        {

        case ITS_SCCP_LOCAL_REF_REQUEST:
        case ITS_SCCP_LOCAL_REF_RESPONSE:
        {
            ITS_HDR hdr;
            ITS_EVENT event;
            ITS_UINT dest;

            /*printf("$$$$ Event: GetSCCP Ref Num $$$$\n");*/

            hdr.type = ITS_SCCP;

            if (INTELLINET_GetSCCPNextRef_ANSI(NULL,
                                        &hdr.context.conref) != ITS_SUCCESS)
            {
                SCCP_ERROR(("Out of local ConnectionReference numbers\n"));
                break;
            }

            /*printf("$$$ SCCP GetNextRefNum: 0x%x\n", hdr.context.conref);*/

            ITS_EVENT_INIT(&event,
                           ITS_SCCP_LOCAL_REF_RESPONSE,
                           sizeof(ITS_CTXT) + sccpEvent.len);

            memcpy(event.data, &hdr.context.conref, sizeof(ITS_CTXT));
            memcpy(&event.data[sizeof(ITS_CTXT)], sccpEvent.data, sccpEvent.len);

            dest = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);

            if (dest != ITS_NO_SRC && dest != ITS_INVALID_SRC)
            {

                /*printf("$$$ SCCP GetNextRefNum: 0x%x\n", hdr.context.conref);*/
                TRANSPORT_PutEvent(dest, &event);
            }


            break;

        }

        case ITS_MTP3_ANSI_SRC:
        case ITS_GCS_EVENT_FROM_STACK:
            //SCCP_DEBUG(("SCCP_Main: handle MTP3 msg.\n"));
            if (sccpEvent.src == ITS_GCS_EVENT_FROM_STACK)
             {
                 SCCP_DEBUG(("SCCP Received from ITS_GCS_EVENT_FROM_STACK\n"));
             }   
            else
             {
               SCCP_DEBUG(("SCCP_Main: handle MTP3 msg.\n"));
             }


            if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_DEBUG))
            {
               buff = (ITS_OCTET*)calloc(sccpEvent.len*6+1,sizeof(ITS_OCTET));
               for (count = 1; count < sccpEvent.len; count++)
               {
                   sprintf(TempBuffer, "0x%02x ",sccpEvent.data[count]);
                   strcat(buff,TempBuffer);
                   if (!((count) % 15))
                   {
                      strcat(buff,"\n");
                   }
               }
               SCCP_DEBUG(("\n\nData received from MTP: \n\n%s\n\n",buff));
               free(buff);
            }

            if (TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT))
            {
                ITS_UINT output = 0;
                if(TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                    SCCP_TRACE_EVENT,
                    0))
                {
                    output += 1;
                }
                if(TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                    SCCP_TRACE_EVENT,
                    1))
                {
                    output += 2;
                }
                
                CTF_TraceEvent(sccpEvent.src, ITS_SCCP_ANSI_SRC,
                        output, &sccpEvent);
            }

            sccpEvent.src = ITS_MTP3_SRC;
            SCRCHandleMTP3Msg_ANSI(&sccpEvent);
            break;

        case ITS_SCCP_ANSI_SRC:
            SCCP_DEBUG(("SCCP_Main: handle termination event.\n"));

            TRANSPORT_IS_ACTIVE(__SCCP_ANSI_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case HEALTH_MANAGER_INSTANCE:
             {
                  SCCP_DEBUG(("DEAD EVENT RECEIVED AT SCCP\n"));
                ret = HandlePeerDeadEvent(&sccpEvent);
                if(ret != ITS_SUCCESS)
                {
                  SCCP_ERROR(("Fail to Handle DEAD Event at SCCP\n"));
                }
             }
         break;

        case ITS_TIMER_SRC:
            SCCP_DEBUG(("SCCP_Main: handle TIMER msg.\n"));


            td = (ITS_TimerData*)sccpEvent.data;

            CheckTimeout(td);
            break;

        case ITS_GCS_EVENT_FROM_APPL:
        default:
            //SCCP_DEBUG(("SCCP_Main: handle APP msg.\n"));
            if (sccpEvent.src == ITS_GCS_EVENT_FROM_APPL)
            {
                SCCP_DEBUG(("SCCP Received from ITS_GCS_EVENT_FROM_APPL\n"));
            }
            else 
             {
               SCCP_DEBUG(("SCCP_Main: handle APP msg.\n"));
             }

            /* Checking if the Event Trace is Enabled*/
            if (TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT))
            {
                ITS_UINT output = 0;
                ITS_UINT gmask = 0;
                ITS_USHORT src = sccpEvent.src;
                
                if(TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                    SCCP_TRACE_EVENT,
                    0))
                {
                    output += 1;
                }
                if(TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                    SCCP_TRACE_EVENT,
                    1))
                {
                    output += 2;
                }
                
                gmask = ENGINE_APP_GS_MASK(application);
                
                if ((gmask & ITS_TCAP_ANSI) == ITS_TCAP_ANSI)
                {
                    src = ITS_TCAP_ANSI_SRC;
                }
                else if ((gmask & ITS_TCAP_CCITT) == ITS_TCAP_CCITT)
                {
                    src = ITS_TCAP_CCITT_SRC;
                }
                else if ((gmask & ITS_TCAP_PRC) == ITS_TCAP_PRC)
                {
                    src = ITS_TCAP_PRC_SRC;
                }
                
                CTF_TraceEvent(src, ITS_SCCP_ANSI_SRC,
                    output, &sccpEvent);
            }

            sccpEvent.src = 0;
            switch (SCCP_MSG_TYPE(&sccpEvent))
            {
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
            case SCCP_MSG_LUDT:
            case SCCP_MSG_LUDTS:  
                SCLCHandleAPPMsg_ANSI(&sccpEvent);
                break;

            case SCCP_MSG_CR:
            case SCCP_MSG_CC:
            case SCCP_MSG_CREF:
            case SCCP_MSG_RLSD:
            case SCCP_MSG_RLC:
            case SCCP_MSG_DT1:
            case SCCP_MSG_DT2:
            case SCCP_MSG_AK:
            case SCCP_MSG_ED:
            case SCCP_MSG_EA:
            case SCCP_MSG_RSR:
            case SCCP_MSG_RSC:
            case SCCP_MSG_ERR:
            case SCCP_MSG_IT:
                SCOCHandleAPPMsg_ANSI(&sccpEvent);
                break;

            default:
                SCCP_ERROR(("SCRCHandleMTP3Msg: invalid message type\n"));
          /*    SCCP_Alarm_ANSI(634, __FILE__, __LINE__,
                                "Message Type: %d", SCCP_MSG_TYPE(&sccpEvent)); */
                return (ITS_EINVALIDARGS);
            }
        }

/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
/*        ROUTE_UnlockRead(routeRWLock, __SCCP_ANSI_RcvQueue);*/
/*Patch:Itika:2-Nov-10:End*/
/*Patch:Itika:1-nov-10:Redundancy Merge fix*/
       sched_yield();
/*Patch:Itika:1-nov-10:End*/
    }

    TRANSPORT_IS_ACTIVE(__SCCP_ANSI_RcvQueue) = ITS_FALSE;

    MTP3_DisableUserPart_ANSI(MTP3_SIO_SCCP);

    THREAD_NORMAL_EXIT;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
ITS_INT
SCCP_AddSegmentRef_ANSI(ITS_OCTET *dsmKey,
                         ITS_OCTET keyLen, ITS_INT maxDataLen,
                         ITS_OCTET remainingSegment, ITS_OCTET dataLen,
                         ITS_OCTET *data, ITS_INT segRefNum)
{
    SCCP_REASM_CTXT* ctxt;
    ITS_UINT         size = sizeof(SCCP_REASM_CTXT);
    ITS_INT          error;

    SCCP_DEBUG(("AddSegmentRefrence :.\n"));

    if (DSM_LockTable(
            DSM_SccpFtGroupId,
            DSM_TABLE_ANSI_SCCP_CTXT) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Can't acquire at least the local lock\n"));

        return (ITS_EBADMUTEX);
    }

    ctxt = (SCCP_REASM_CTXT *) DSM_FindNoLock(DSM_SccpFtGroupId,
                                       DSM_TABLE_ANSI_SCCP_CTXT,
                                       (ITS_OCTET *)dsmKey,
                                       keyLen, &error);

    if (error != ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("AddSegmentRef: Couldn't get segment refrence.\n"));

        return (ITS_ENOMEM);
    }

    if (error == ITS_ENOTFOUND)
    {
        ctxt = (SCCP_REASM_CTXT *) DSM_AllocNoLock(DSM_SccpFtGroupId,
                                                   DSM_TABLE_ANSI_SCCP_CTXT,
                                                   (ITS_OCTET *)dsmKey,
                                                   keyLen, size, &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_CRITICAL(("GetNextLocalRef: Couldn't acquire"
                                       " mutex.\n"));

                    break;

                case (ITS_ENOMEM):

                    SCCP_CRITICAL(("GetNextLocalRef: No Memory.\n"));

                    break;
             }

                DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

                return (error);
            }
        }

        error = DSM_LockRowNoLock(DSM_SccpFtGroupId, ctxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_CRITICAL(("GetNextLocalRef: DSM_LockRowNoLock failed\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

            return (error);
        }

        ctxt->type = SCLC_TIMER_TYPE;
        ctxt->refno = segRefNum;
        ctxt->maxDataLen = maxDataLen;;
        ctxt->remainingSegment = remainingSegment;
        ctxt->totalDataLen = dataLen;

        if(SCLC_PutDataInFragList(dsmKey, keyLen, ctxt,
                             data, dataLen) != ITS_SUCCESS)
        {
            SCCP_CRITICAL(("AddSegmentRef: Couldn't add data in frag list.\n"));

            SCCP_DeleteSegmentRef_ANSI(dsmKey, keyLen, ctxt);

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

            return (ITS_ENOMSGSPACE);
        }

        ctxt->reasmTimer =
            TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                    TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                         SCCP_T_reassembly),
                                    ctxt, sizeof(SCCP_REASM_CTXT));

        error = DSM_CommitNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_ANSI_SCCP_CTXT,
                                 (ITS_OCTET *)dsmKey,
                                 keyLen, ctxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("AddSegmentRef: Couldn't add context.\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

            return (error);
        }

        SCCP_DEBUG(("AddSegmentRef: returns ref %04x.\n", segRefNum));

        error = DSM_UnlockRowNoLock(DSM_SccpFtGroupId, ctxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_CRITICAL(("GetNextLocalRef: DSM_UnlockRowNoLock failed\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

            return (error);
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

        return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
void
SCCP_DeleteSegmentRef_ANSI(ITS_OCTET *dsmKey, ITS_OCTET keyLen,
                            SCCP_REASM_CTXT *ctxt)
{
    ITS_INT   error;

    SCCP_DEBUG(("SCCP_DeleteSegmentRef: cref %04x\n", ctxt->refno));

    error = TIMERS_CancelTimer(ctxt->reasmTimer);
    if(error != ITS_SUCCESS)
    {
       SCCP_ERROR(("SCCP_DeleteSegmentRef_ANSI:FAIL To CANCEL reasmTimer : SERIAL [%d]\n", ctxt->reasmTimer));
    }

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_CTXT,
                     (ITS_OCTET *)dsmKey,
                     keyLen, ctxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("DeleteSegmentRef: DSM unable to free Reference.\n"));
    }
}

/*.implementation:extern
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  04-04-2005  IssueID::1784,1781     SCCP Timer Check and 
 *                                               LinkSet parameter added 
 *                                               for si_set_rssn.
 *
 ****************************************************************************/
void
SCCP_Console_ANSI(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    ITS_INT ret;
    ITS_UINT pc, cpc;
    ITS_UINT ssn, cssn, ni;
    ITS_UINT i; 

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "sa_get_gen_cfg", "SCCP Get General Config", "", ""))
    {
        SCCPGeneralCfg *cfg;
        cfg =  SCCP_GetGeneralCfg_ANSI();

        sprintf(buf, "*********** SCCP General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "    Alarm Level = CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "    Alarm Level = MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "    Alarm Level = MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "    Alarm Level = INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "    Alarm Level = OFF\n");
            break;

            default :
                sprintf(buf, "    Alarm Level Not Set\n");
            break;
        }

       DBC_AppendText(dbc, buf);

       strcpy(buf, "    SCCP Trace -\n");
       DBC_AppendText(dbc, buf);

       if ( cfg->traceOn)
       {
           if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Debug     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      2))
               {
                    strcat(buf, " syslog");
               }               
           }
           else
           {
               strcpy(buf, "        Critical  = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_WARNING,
                                      2))
               {
                    strcat(buf, " syslog");
               }

           }
           else
           {
               strcpy(buf, "        Warning   = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_ERROR,
                                      2))
               {
                    strcat(buf, " syslog");
               }

           }
           else
           {
               strcpy(buf, "        Error     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                                    SCCP_TRACE_EVENT))
           {
               strcpy(buf, "        Event   = ");
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_EVENT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_EVENT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(SCCP_ANSI_TraceData,
                                      SCCP_TRACE_EVENT,
                                      2))
               {
                    strcat(buf, " syslog");
               }

           }
           else
           {
               strcpy(buf, "        Event   = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);
       }
       else
       {
           strcpy(buf, "        Debug     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Critical  = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Warning   = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Error     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Event     = null\n");
           DBC_AppendText(dbc, buf);
       }



       sprintf(buf, "*********** End of SCCP General Config *************\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_set_gen_cfg", "SCCP Set General Config", 
                      "<al> <trType> <trOutput> <on/off>", 
                     "<Alarm Level> <Trace Type> <Trace Output> <On / Off>"))

    {
        SCCPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType, 
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL || 
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") || 
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") || 
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") || 
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "Invalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        
        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, SCCP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, SCCP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, SCCP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, SCCP_ERROR_STRING);
        }
        else if (strstr(traceType, "EVENT") || strstr(traceType, "event"))
        {
            strcpy(cfg.traceType, SCCP_EVENT_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, SCCP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, SCCP_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, SCCP_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  SCCP_SetGeneralCfg_ANSI(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "*********** SCCP General Config Set*************\n");
       DBC_AppendText(dbc, buf);

    }

#if 0
    else if (DBC_Cmd(dbc, "sa_get_ss", "SCCP Get Subsystem Entry", 
                     "<sspc> <ni> <ssn>",
                     "<point code> <network indicator> <subsystem>"))

    {
        SCCPSubSystemInfo* info;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ni, &ssn);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetSSEntry_ANSI( (ITS_UINT)pc, (ITS_OCTET)ni, 
                                    (ITS_OCTET)ssn);

        if (info)
        {
            sprintf(buf, "*********** SCCP Found SSN Entry*************\n");
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    pointcode          <%d>\n", info->pointcode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni                 <%d>\n", info->ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ssn                <%d>\n", info->ssn);
            DBC_AppendText(dbc, buf);

            if (info->inService == ITS_FALSE)
            {
                sprintf(buf, "    inService          <no>\n");
            }
            else
            {
                sprintf(buf, "    inService          <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (info->testOn == ITS_FALSE)
            {
                sprintf(buf, "    SSTtestOn           <no>\n");
            }
            else
            {
                sprintf(buf, "    SSTtestOn           <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (info->hasConcernPC == ITS_FALSE)
            {
                sprintf(buf, "    hasConcernPC       <no>\n");
            }
            else
            {
                sprintf(buf, "    hasConcernPC       <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    maxHops            <%d>\n", info->maxHops);
            DBC_AppendText(dbc, buf);

            if (info->backupStatus == SSN_STANDALONE)
            {
                sprintf(buf, "    backupStatus       <standalone>\n");
            }
            else if (info->backupStatus == SSN_PRIMARY)
            {
                sprintf(buf, "    backupStatus       <primary>\n");
            }
            else if (info->backupStatus == SSN_SECONDARY)
            {
                sprintf(buf, "    backupStatus       <secondary>\n");
            }
            else if (info->backupStatus == SSN_MATED)
            {
                sprintf(buf, "    backupStatus       <mated>\n");
            }
            else
            {
                sprintf(buf, "    backupStatus       <standalone>\n");
            }

            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupPC           <%d>\n", info->backupPC);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupNI           <%d>\n", info->backupNI);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupSSN          <%d>\n", info->backupSSN);
            DBC_AppendText(dbc, buf);

            if (info->backupSSNState == ITS_FALSE)
            {
                sprintf(buf, "    backupSSNState     <down>\n");
            }
            else
            {
                sprintf(buf, "    backupSSNState     <up>\n");
            }
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "*********** SCCP SSN Entry Not Found***********\n");
            DBC_AppendText(dbc, buf);
        }

    }
#endif

    else if (DBC_Cmd(dbc, "sa_get_all_ssn", "SCCP Get All Subsystem Entries", 
                     "", ""))
    {
        SCCPSubSystemInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllSSEntries_ANSI( &numEntries, &entry);

        sprintf(buf, "    Total Entries  <%d>\n", numEntries);
        DBC_AppendText(dbc, buf);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    pointcode      <%d>\n", entry[i].pointcode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni             <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ssn            <%d>\n", entry[i].ssn);
            DBC_AppendText(dbc, buf);
            if (entry[i].isLocal == ITS_TRUE)
            {
                sprintf(buf, "    isLocal        <yes>\n");
            }
            else
            {
                sprintf(buf, "    isLocal        <no>\n");
            }
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    linkset        <%d>\n", entry[i].linkSet);
            DBC_AppendText(dbc, buf);

            if (entry[i].inService == ITS_FALSE)
            {
                sprintf(buf, "    inService      <no>\n");
            }
            else
            {
                sprintf(buf, "    inService      <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (entry[i].testOn == ITS_FALSE)
            {
                sprintf(buf, "    SSTtestOn      <no>\n");
            }
            else
            {
                sprintf(buf, "    SSTtestOn      <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (entry[i].hasConcernPC == ITS_FALSE)
            {
                sprintf(buf, "    hasConcernPC   <no>\n");
            }
            else
            {
                sprintf(buf, "    hasConcernPC   <yes>\n");
            }
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "sa_rem_lssn", "SCCP Remove Local Subsystem Entry",
                     "<pc> <ni> <ssn>",
                     "<pc> <ni> <subsystem>"))

    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset = 0;

        ret = sscanf(cmdLine, "%s %d %d %d ", buf, &pc, &ni, &ssn);
        if (ret != 4)
        {
            sprintf(buf, "\n*** Invalid Command Arguments ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ssn > 256)
        {
            sprintf(buf, "\n*** Invalid ssn ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointcode = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.linkSet = linkset;
        info.isLocal = ITS_TRUE;

        ret = SCCP_RemSSEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\n*** SCCP Remove SSN Entry Failed ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n*** SCCP Local Subsystem Entry Removed ***\n");
        DBC_AppendText(dbc, buf);
    }
    else if(DBC_Cmd(dbc, "sa_rem_rssn", "SCCP Remove Remote Subsystem Entry",
                     "<sspc> <ni> <ssn> ",
                     "<point code> <ni> <subsystem>"))
    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset = 0;
        ITS_INT routeId;
        SS7_Destination* destPtr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ni, &ssn);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ssn > 256)
        {
            sprintf(buf, "\n*** Invalid ssn ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ni != MTP3_NIC_INTERNATIONAL &&
            ni != MTP3_NIC_SPARE         &&
            ni != MTP3_NIC_NATIONAL      &&
            ni != MTP3_NIC_RESERVED)
        {
            sprintf(buf, "\n*** Invalid NI ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }


        destPtr = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);
        if (destPtr == NULL)
        {
            sprintf(buf, "\n*** Invalid PC/NI ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        ROUTE_CommitDestination(destPtr, pc, ni, FAMILY_ANSI);

        for(routeId = 0; routeId < destPtr->numEntries; routeId++)
        {
            if (destPtr->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN &&
                destPtr->entries[routeId]->basic.type == REMOTE_ROUTE)
            {
                linkset = destPtr->entries[routeId]->linkSet->linkSet;
            }
        }

        if (linkset == 0 && routeId == destPtr->numEntries)
        {
            sprintf(buf, "\n*** DPC-SIO-SSN route not found. ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.linkSet = linkset;
        info.pointcode = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.isLocal = ITS_FALSE;

        ret = SCCP_RemSSEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "*** SCCP Remove SSN Entry Failed ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n*** SCCP Remote Subsystem Entry Removed ***\n");
        DBC_AppendText(dbc, buf);

        SCCP_Alarm_ANSI(500, __FILE__, __LINE__, " PC %x, SSN %d", pc, ssn);
    }
    else if(DBC_Cmd(dbc, "sa_set_rssn", "SCCP Set Remote Subsystem Entry",
                     "<sspc> <ni> <ssn> [<linkset>]",
                     "<point code> <ni> <ssn> [<linkset>]"))
    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset = -1;
        ITS_INT routeId = 0;
        SS7_Destination* destPtr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &linkset);
        if ((ret != 4) && (ret != 5))
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ssn > 256)
        {
            sprintf(buf, "\n*** Invalid ssn ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ni != MTP3_NIC_INTERNATIONAL &&
            ni != MTP3_NIC_SPARE         &&
            ni != MTP3_NIC_NATIONAL      &&
            ni != MTP3_NIC_RESERVED)
        {
            sprintf(buf, "\n*** Invalid NI ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }


        destPtr = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);
        if (destPtr == NULL)
        {
            sprintf(buf, "\n*** Invalid PC/NI. Add a DPC-NI route first ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        ROUTE_CommitDestination(destPtr, pc, ni, FAMILY_ANSI);

        if (linkset == -1)
        {
            for(routeId = 0; routeId < destPtr->numEntries; routeId++)
            {
                if (destPtr->entries[routeId]->basic.style == ROUTE_DPC_NI &&
                    destPtr->entries[routeId]->basic.type == REMOTE_ROUTE)
                {
                    linkset = destPtr->entries[routeId]->linkSet->linkSet;
                }
            }
        }

        if ((linkset == -1) && (routeId == destPtr->numEntries))
        {
            sprintf(buf, "\n*** DPC-NI route not found. Add a DPC-NI route first ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointcode = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.linkSet = linkset;
        info.isLocal = ITS_FALSE;

        ret = SCCP_SetSSEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\n*** SCCP SSN Set Entry Failed ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*** SCCP Remote Subsystem Entry Set ***\n");
        DBC_AppendText(dbc, buf);

        SCCP_Alarm_ANSI(501, __FILE__, __LINE__, " PC %x, SSN %d", pc, ssn);
    }
    else if (DBC_Cmd(dbc, "sa_set_lssn", "SCCP Set Local Subsystem Entry",
                     "<pc> <ni> <lssn>","<pc> <ni> <lssn>"))

    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset = 0;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d ", buf, &pc, &ni, &ssn);
        if (ret != 4)
        {
            sprintf(buf, "\n*** Invalid Command Arguments ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ssn > 256)
        {
            sprintf(buf, "\n*** Invalid ssn ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "\n*** Invalid Linkset ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointcode = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.linkSet = linkset;
        info.isLocal =ITS_TRUE;

        ret = SCCP_SetSSEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_EDUPLENTRY)
            {
                sprintf(buf, "\n*** Duplicate entry not allowed ***");
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf, "\n*** SCCP SSN Set Entry Failed ***");
                DBC_AppendText(dbc, buf);
            }
            return;
        }

        sprintf(buf, "\n********* SCCP Local Subsystem Entry Set *********\n");
        DBC_AppendText(dbc, buf);
    }

#if 0
    else if (DBC_Cmd(dbc, "sa_rem_ss", "SCCP Remove Subsystem Entry", 
                     "<sspc> <ssn> <linkset>",
                     "<point code> <subsystem> <linkset>"))

    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ssn, &linkset);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.linkSet = linkset;
        info.pointcode = pc;
        info.ni = lptr->ni;
        info.ssn = ssn;

       ret = SCCP_RemSSEntry_ANSI(&info);
       if (ret != ITS_SUCCESS)
       {
           sprintf(buf, "********* SCCP Remove SSN Entry Failed***********\n");
           DBC_AppendText(dbc, buf);
           return;
       }

        sprintf(buf, "********* SCCP Subsystem Entry Removed********\n");
        SCCP_Alarm_ANSI(500, __FILE__, __LINE__, " PC %x, SSN %d", pc, ssn);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "sa_set_ss", "SCCP Set Subsystem Entry", 
                     "<sspc> <ssn> <linkset> ",
                     "<point code> <ssn> <linkset>"))

    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ssn, &linkset);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ssn > 256)
        {
            sprintf(buf, "\n*** Invalid ssn ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointcode = pc;
        info.ni = lptr->ni;
        info.ssn = ssn;
        info.linkSet = linkset;

        ret = SCCP_SetSSEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "********* SCCP SSN Set Entry Failed***********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

         sprintf(buf, "********* SCCP Subsystem Entry Set********\n");
         SCCP_Alarm_ANSI(501, __FILE__, __LINE__, " PC %x, SSN %d", pc, ssn);

         DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "sa_get_pc", "SCCP Get Point Code Entry", 
                     "<sspc> <ni>",
                     "<point code> <network indicator>"))

    {
        SCCPPointCodeInfo* info;

        ret = sscanf(cmdLine, "%s %d %d ", buf, &pc, &ni);
        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetPointCodeEntry_ANSI((ITS_OCTET)ni, pc);

        if (info)
        {
            sprintf(buf, "********* SCCP Found Point Code Entry**********\n");
            sprintf(buf, "    pointCode              <%d>\n", info->pointCode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni                     <%d>\n", info->ni);
            DBC_AppendText(dbc, buf);

            if (info->isPointcodeProhibited == ITS_FALSE)
            {
                sprintf(buf, "    isPointcodeProhibited  <no>\n");
            }
            else
            {
                sprintf(buf, "    isPointcodeProhibited  <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    pcCongestLevel         <%d>\n", 
                   info->pcCongestLevel);
            DBC_AppendText(dbc, buf);
            
            if (info->isAdjacent == ITS_FALSE)
            {
                sprintf(buf, "    isAdjacent             <no>\n");
            }
            else
            {
                sprintf(buf, "    isAdjacent             <yes>\n");
            }
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "********* SCCP Point Code Entry Not Found******\n");
            DBC_AppendText(dbc, buf);
        }

    }
    else if (DBC_Cmd(dbc, "sa_get_all_pc", "SCCP Get All Point Code Entries", 
                     "", ""))

    {
        SCCPPointCodeInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllPointCodeEntries_ANSI( &numEntries, &entry);

        sprintf(buf, "    Total Entries          <%d>\n", numEntries);
        DBC_AppendText(dbc, buf);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    pointCode              <%d>\n", entry[i].pointCode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni                     <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    linkset                <%d>\n", entry[i].linkSet);
            DBC_AppendText(dbc, buf);

            if (entry[i].isPointcodeProhibited == ITS_FALSE)
            {
                sprintf(buf, "    isPointcodeProhibited  <no>\n");
            }
            else
            {
                sprintf(buf, "    isPointcodeProhibited  <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    pcCongestLevel         <%d>\n", 
                    entry[i].pcCongestLevel);
            DBC_AppendText(dbc, buf);

            if (entry[i].isAdjacent == ITS_FALSE)
            {
                sprintf(buf, "    isAdjacent             <no>\n");
            }
            else
            {
                sprintf(buf, "    isAdjacent             <yes>\n");
            }
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "sa_set_pc", "SCCP Set Point Code Entry", 
                     "<sspc> <linkset>",
                   "<point code> <linkset>"))
    {
        ITS_INT linkset;
        SCCPPointCodeInfo info;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &pc,  &linkset);

        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointCode = pc;
        info.ni = lptr->ni;
        info.linkSet = linkset;

        ret = SCCP_SetPointCodeEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP PC Set Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "********* SCCP Point Code Entry Set********\n");
        SCCP_Alarm_ANSI(502, __FILE__, __LINE__, "PC %x", pc);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_rem_pc", "SCCP Remove Point Code Entry", 
                     "<sspc> <linkset> <ia>",
                   "<point code> <linkset>"))

    {
        ITS_INT linkset;
        SCCPPointCodeInfo info;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &pc, &linkset);

        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointCode = pc;
        info.ni = lptr->ni;
        info.linkSet = (ITS_OCTET)linkset;

        ret = SCCP_RemPointCodeEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP PC Remove Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "********* SCCP Point Code Entry Removed********\n");
        SCCP_Alarm_ANSI(503, __FILE__, __LINE__, "PC %x", pc);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_get_cpc", "SCCP Get Concerned Point Code Entry", 
                     "<sspc> <ni> <ssn> <cpc>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code>"))

    {
        SCCPConcernedPCInfo* info;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &cpc);
        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetConcernedPC_ANSI( (ITS_UINT)pc, (ITS_OCTET)ni, 
                                        (ITS_OCTET)ssn, (ITS_UINT)cpc);

        if (info)
        {
            sprintf(buf, "******** SCCP Found CPC Entry*************\n");
        }
        else
        {
            sprintf(buf, "*********** SCCP CPC Entry Not Found*************\n");
        }
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_get_all_cpc", "SCCP Get All CPC Entries", 
                     "", ""))

    {
        SCCPConcernedPCInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllCPCEntries_ANSI( &numEntries, &entry);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "sspc    <%d>\n", entry[i].sspc);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "ni      <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "ssn     <%d>\n", entry[i].ssn);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "cpc     <%d>\n", entry[i].cpc);
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "sa_set_cpc", "SCCP Set Concerned Point Code Entry", 
                     "<sspc> <ni> <ssn> <cpc>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code>"))

    {
        SCCPConcernedPCInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &cpc);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.sspc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;

        ret = SCCP_SetConcernedPC_ANSI(&info);
        if (ret == ITS_ENOTFOUND)
        {
             sprintf(buf, "No Local Route Found For pc=%d, ni=%d, ssn=%d\n",
                     pc, ni, ssn);
             DBC_AppendText(dbc, buf);
             sprintf(buf, "********* SCCP Set CPC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP CPC Set Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "******* SCCP Concerned Point Code Entry Set********\n");
        SCCP_Alarm_ANSI(504, __FILE__, __LINE__, "PC %x, SSN %d", pc, ssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_rem_cpc", "SCCP Remove CPC Entry", 
                     "<sspc> <ni> <ssn> <cpc>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code>"))

    {
        SCCPConcernedPCInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &cpc);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.sspc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;

        ret = SCCP_RemConcernedPC_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP CPC Remove Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "****** SCCP Concerned Point Code Entry Removed***\n");
        SCCP_Alarm_ANSI(505, __FILE__, __LINE__, "PC %x, SSN %d", pc, ssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_get_cssn", "SCCP Get Concerned SSN Entry", 
                     "<sspc> <ni> <ssn> <cpc> <cssn>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code> <concerned ssn>"))

    {
        SCCPConcernedSSInfo* info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &pc, &ni, &ssn, &cpc,
                     &cssn);
        if (ret != 6)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetConcernedSS_ANSI( (ITS_UINT)pc, (ITS_OCTET)ni, 
                                         (ITS_OCTET)ssn, (ITS_UINT)cpc, 
                                         (ITS_OCTET)cssn);

        if (info)
        {
            sprintf(buf, "*********** SCCP Found CSSN Entry*************\n");
        }
        else
        {
            sprintf(buf, "******** SCCP CSSN Entry Not Found************\n");
        }
        DBC_AppendText(dbc, buf);

    }
#endif

    else if (DBC_Cmd(dbc, "sa_get_all_cssn", "SCCP Get All Concerned SSN Entry",
                     "", ""))

    {
        SCCPConcernedSSInfo *entry;
        ITS_UINT numEntries = 0;

        SCCP_GetAllCSSEntries_ANSI( &numEntries, &entry);

        if (!numEntries)
        {
            sprintf(buf, "No Concerned SSN Entry Found\n");
            DBC_AppendText(dbc, buf);
        }

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "pc           <%d>\n", entry[i].pc);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "ni           <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "ssn          <%d>\n", entry[i].ssn);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "cpc          <%d>\n", entry[i].cpc);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "cssn         <%d>\n", entry[i].cssn);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "inservice    <%s>\n", (entry[i].inservice)? "yes" : "no");
            DBC_AppendText(dbc, buf);
        }

    }
    else if (DBC_Cmd(dbc, "sa_set_cssn", "SCCP Set Concerned SSN Entry", 
                     "<sspc> <ni> <ssn> <cpc> <cssn>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code> <concerned ssn"))

    {
        SCCPConcernedSSInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &pc, 
                     &ni, &ssn, &cpc, 
                     &cssn);

        if (ret != 6)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ssn > 256) || (cssn > 256 ))
        {
            sprintf(buf, "\n*** Invalid ssn ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;

        ret = SCCP_SetConcernedSS_ANSI(&info);
        if (ret == ITS_ENOTFOUND)
        {
             sprintf(buf, "No Local Route Found For pc=%d, ni=%d, ssn=%d\n",
                     pc, ni, ssn);
             DBC_AppendText(dbc, buf);
             sprintf(buf, "********* SCCP Set CPC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP CSSN Set Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "********* SCCP Concerned Subsystem Entry Set*******\n");
        SCCP_Alarm_ANSI(506, __FILE__, __LINE__, " PC %x SSN %d", cpc, cssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_rem_cssn", "SCCP Remove Concerned SSN Entry", 
                     "<sspc> <ni> <ssn> <cpc> <cssn>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code> <concerned ssn"))

    {
        SCCPConcernedSSInfo info;
        ITS_INT inservice = ITS_FALSE;
        MTP3_HEADER hdr;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &pc, &ni, &ssn, &cpc, 
                     &cssn);

        if (ret != 6)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;
        info.inservice = inservice;

        ret = SCCP_RemConcernedSS_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP CSSN Remove Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ni =  ni | 0x03;

        hdr.sio =  ni;
        MTP3_RL_SET_DPC_VALUE(hdr.label, cpc);
        MTP3_RL_SET_OPC_VALUE(hdr.label, cpc);
        MTP3_RL_SET_SLS(hdr.label, 0);

       // SSTCStopSST(&hdr, cpc, cssn);

        sprintf(buf, "****** SCCP Concerned Subsystem Entry Removed*****\n");
        SCCP_Alarm_ANSI(507, __FILE__, __LINE__, " PC %x SSN %d", cpc, cssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_get_behavior", "SCCP Get Behaviors", 
                     "", ""))

    {
        if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_use_SCMG))
        {
            sprintf(buf, "    SCCP_B_use_SCMG          <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_use_SCMG          <no> \n");
        }
        DBC_AppendText(dbc, buf);

        if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
        {
            sprintf(buf, "    SCCP_B_propagate_SCMG    <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_propagate_SCMG    <no> \n");
        }
        DBC_AppendText(dbc, buf);

        if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT))
        {
            sprintf(buf, "    SCCP_B_propagate_IT      <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_propagate_IT      <no> \n");
        }
        DBC_AppendText(dbc, buf);

        if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR))
        {
            sprintf(buf, "    SCCP_B_propagate_ERR     <yes> \n");
 
        }
        else
        {
            sprintf(buf, "    SCCP_B_propagate_ERR     <no> \n");
        }
        DBC_AppendText(dbc, buf);


    }
    else if (DBC_Cmd(dbc, "sa_set_behavior", "SCCP Set Behaviors", 
                     "<ps> <us> <pi> <pe>", ""))

    {
        char ps[ITS_PATH_MAX];
        char us[ITS_PATH_MAX];
        char pi[ITS_PATH_MAX];
        char pe[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, ps, us, pi, pe);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(us, "YES") != NULL || strstr(us, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_use_SCMG, 
                                  ITS_TRUE);
        }
        else if (strstr(us, "NO") != NULL || strstr(us, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_use_SCMG, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, "Invalid Value Of Use SCMG Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(ps, "YES") != NULL || strstr(ps, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG, 
                                  ITS_TRUE);
        }
        else if (strstr(ps, "NO") != NULL || strstr(ps, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, "Invalid Value Propogate SCMG Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if  (strstr(pi, "YES") != NULL || strstr(pi, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT, 
                                  ITS_TRUE);
        }
        else if (strstr(pi, "NO") != NULL || strstr(pi, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, 
                   "Invalid Value Propogate Inactivity Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if  (strstr(pe, "YES") != NULL || strstr(pe, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR, 
                                  ITS_TRUE);
        }
        else if (strstr(pe, "NO") != NULL || strstr(pe, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, "Invalid Value Propogate Error Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*******SCCP Behaviors Set*******\n");
        DBC_AppendText(dbc, buf);



    }
    else if (DBC_Cmd(dbc, "sa_get_tmr", "SCCP Get Timers", 
                     "", ""))
    {
        int value = 0;

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_statInfo);
        sprintf(buf, "    SCCP_T_statInfo       <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_coordChg);
        sprintf(buf, "    SCCP_T_coordChg       <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ignoreSST);
        sprintf(buf, "    SCCP_T_ignoreSST      <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_rtgStatInfo);
        sprintf(buf, "    SCCP_T_rtgStatInfo    <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_conn);
        sprintf(buf, "    SCCP_T_conn           <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_release);
        sprintf(buf, "    SCCP_T_release        <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reset);
        sprintf(buf, "    SCCP_T_reset          <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ias);
        sprintf(buf, "    SCCP_T_ias            <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_iar);
        sprintf(buf, "    SCCP_T_iar            <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_guard);
        sprintf(buf, "    SCCP_T_guard          <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reassembly);
        sprintf(buf, "    SCCP_T_reassembly     <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_interval);
        sprintf(buf, "    SCCP_T_interval       <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_repeatRelease);
        sprintf(buf, "    SCCP_T_repeatRelease  <%d> \n", value);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_set_tmr", "SCCP Set Timer", 
                     "<tmr> <value>", "<Timer#> <value>"))

    {
        int tr, value = 0;

        ret = sscanf(cmdLine, "%s %d %d", buf, &tr, &value);

        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (tr > 12)
        {
            sprintf(buf, "\n*** Invalid Timer ID ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, tr, value);

        sprintf(buf, "    Timer # %d Set \n", tr);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "sa_get_gen_peg", "Get Pegs", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_INT pgNum;
        ITS_UINT value;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
             return;
        }

        if((strncmp(pgName, "ALL", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_SCCP_PEGS))
        {
            DumpAllSCCPPegs(dbc);
            return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        pgNum = atoi(pgName);

        if (pgNum >= PEG_SCCP_NUM_PEGS)
        {
            sprintf(buf, "**** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n", sccpPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(ANSI_SCCP_Pegs, pgNum);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }

#if 0

    else if (DBC_Cmd(dbc, "sa_show_all_pegs", "Dump All SCCP Pegs", "<>", "<>"))
    {
        DumpAllSCCPPegs(dbc);

    }

#endif

    else if (DBC_Cmd(dbc, "sa_clr_gen_peg", "Clear Peg", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_INT pgNum;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf, "**** Invalid Command Arguments *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        if((strncmp(pgName, "ALL", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_SCCP_PEGS))
        {
            PEG_ClearBlock(ANSI_SCCP_Pegs);

            sprintf(buf, "Clearing All ANSI SCCP Pegs for  Now\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        pgNum = atoi(pgName);

        if (pgNum >= PEG_SCCP_NUM_PEGS)
        {
            sprintf(buf, "**** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Clearing the Pegs for %s Now\n", sccpPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        PEG_ClearPeg(ANSI_SCCP_Pegs, pgNum);
    }

#if 0

    else if (DBC_Cmd(dbc, "sa_clr_all_pegs", "Clear All Pegs", "<> ", "<>"))
    {
        PEG_ClearBlock(ANSI_SCCP_Pegs);

        sprintf(buf, "Clearing All ANSI SCCP Pegs for  Now\n");
        DBC_AppendText(dbc, buf);

    }

#endif

    else if (DBC_Cmd(dbc, "sa_send_ssp", "SCCP Send Sub System Prohibited",
                     "<sspc> <ni> <ssn> <cpc> <cssn> ", "<>"))
    {
        SCCPConcernedSSInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d ", buf, &pc,
                     &ni, &ssn, &cpc, &cssn);
        if (ret != 6)
        {
            sprintf(buf, "\n*** Invalid Command Arguments ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;
        info.inservice = ITS_FALSE;


        ret = SCCP_SendSCMG_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "\n*** SCCP SSP Send Failed ***");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "\n*** SCCP SSP Send ***\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "sa_send_ssa", "SCCP Send Sub System Allowed",
                     "<sspc> <ni> <ssn> <cpc> <cssn> ", "<>"))
    {
        SCCPConcernedSSInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d ", buf, &pc,
                     &ni, &ssn, &cpc, &cssn);
        if (ret != 6)
        {
            sprintf(buf, "\n*** Invalid Command Arguments ***");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;
        info.inservice = ITS_TRUE;


        ret = SCCP_SendSCMG_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "\n*** SCCP SSA Send Failed ***");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "\n*** SCCP SSA Send ***");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "sa_send_sst", "SCCP Send Sub System Test",
                     "<sspc> <ni> <ssn> <cpc> <cssn> ", "<>"))
    {
        SCCPConcernedSSInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d ", buf, &pc,
                     &ni, &ssn, &cpc, &cssn);
        if (ret != 6)
        {
            sprintf(buf, "\n*** Invalid Command Arguments ***");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;
        info.inservice = ITS_TRUE;


        ret = SCCP_SendSST_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "\n*** SCCP SST Send Failed ***");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "\n*** SCCP SST Send ***");
        DBC_AppendText(dbc, buf);
    }
}


/*.implementation:extern
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
ITSSS7DLLAPI int
SCCP_GetAllPegs(SCCP_Pegs *genPegs)
{

    if (genPegs == NULL)
    {
        SCCP_ERROR(("SCCP_GetAllPegs: SCCP Peg object is NULL\n"));

        return ITS_ENOMEM;

    }

    genPegs->userMsgsSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_MSG_SENT);
    genPegs->remoteMsgsRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);
    genPegs->routingFailure = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);
    genPegs->remoteGTTRequest = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_REQUEST);
    genPegs->remoteGTTSucc = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_SUCCESS);
    genPegs->remoteGTTFail = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_FAILURE);

    genPegs->remoteMsgsDecodeErr = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_DECODE_ERR);
    genPegs->userMsgsEncodeErr = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_MSG_ENCODE_ERR);

    genPegs->remoteReassembleErr = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_REASSEMBLE_ERR);
    genPegs->hopCounterVilotionErr = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);
    genPegs->userSegmentationErr = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_SEGMENTATION_ERR);
    genPegs->timerTiarExpiry = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_TIMER_TIAR_EXPIRY);
    genPegs->userInitiatedRLSD = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_INITIATED_RLS);
    genPegs->userInitiatedReset = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_INITITATED_RESET);
    genPegs->remoteUDTRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_UDT_RCVD);
    genPegs->remoteXUDTRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_XUDT_RCVD);
    genPegs->remoteUDTSRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_UDTS_RCVD);
    genPegs->remoteXUDTSRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_XUDTS_RCVD);
    genPegs->remoteLUDTRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_LUDT_RCVD);
    genPegs->remoteLUDTSRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_LUDTS_RCVD);
    genPegs->userUDTSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_UDT_SENT);
    genPegs->userXUDTSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_XUDT_SENT);
    genPegs->userUDTSSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_UDTS_SENT);
    genPegs->userXUDTSSent= PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_XUDTS_SENT);
    genPegs->userLUDTSent= PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_LUDT_SENT);
    genPegs->userLUDTSSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_LUDTS_SENT);
    genPegs->userCRSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_CR_SENT);
    genPegs->sentCREFToRemote = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_CREF_TO_REMOTE_SENT);
    genPegs->sentRSRToRemote = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_RSR_TO_REMOTE_SENT);
    genPegs->sentERRToRemote = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_ERR_TO_REMOTE_SENT);
    genPegs->remoteCRRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_CR_RCVD);
    genPegs->remoteCREFRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_CREF_RCVD);
    genPegs->remoteRSRRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_RSR_RCVD);
    genPegs->remoteERRRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_ERR_RCVD);
    genPegs->remoteMsgsForLocalSSRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD);
    genPegs->userDT1Sent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_DT1_SENT);
    genPegs->remoteDT1Rcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_DT1_RCVD);
    genPegs->userDT2Sent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_DT2_SENT);
    genPegs->remoteDT2Rcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_DT2_RCVD);
    genPegs->userEDSent = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_ED_SENT);
    genPegs->remoteEDRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_ED_RCVD);
    genPegs->remoteSSPRcvd= PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSP_RCVD);
    genPegs->remoteSSARcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSA_RCVD);
    genPegs->remoteSSCRcvd = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSC_RCVD);
    genPegs->localSSProhibited = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_PROHIBITED);
    genPegs->localSSAllowed = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_ALLOWED);
    genPegs->localSSCongested = PEG_GetPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_CONGESTED);

    return ITS_SUCCESS;
}

/*.implementation:extern
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
ITSSS7DLLAPI int
SCCP_ClearPegs()
{
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_MSG_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_REQUEST);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_SUCCESS);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_FAILURE);

    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_DECODE_ERR);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_MSG_ENCODE_ERR);

    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_REASSEMBLE_ERR);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_SEGMENTATION_ERR);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_TIMER_TIAR_EXPIRY);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_INITIATED_RLS);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_INITITATED_RESET);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_UDT_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_XUDT_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_UDTS_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_XUDTS_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_LUDT_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_LUDTS_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_UDT_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_XUDT_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_UDTS_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_XUDTS_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_LUDT_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_LUDTS_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_CR_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_CREF_TO_REMOTE_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_RSR_TO_REMOTE_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_ERR_TO_REMOTE_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_CR_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_CREF_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_RSR_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_ERR_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_DT1_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_DT1_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_DT2_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_DT2_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_ED_SENT);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_ED_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSP_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSA_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSC_RCVD);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_PROHIBITED);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_ALLOWED);
    PEG_ClearPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_CONGESTED);

    return ITS_SUCCESS;
}

/*.implementation:extern
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
ITSSS7DLLAPI int
SCCP_ClearPeg(ITS_UINT pegId)
{

    return ITS_SUCCESS;
}

/*.implementation:extern
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
static void
DumpAllSCCPPegs(DBC_Server *dbc)
{

    SCCP_Pegs sccpPegs;

    char buf[32000];
    char buf1[32000];

    memset(buf , 0, 32000);
    memset(buf1, 0, 32000);

    SCCP_GetAllPegs(&sccpPegs);

    sprintf(buf, "**************** SCCP Pegs ****************\n");
    strcat(buf1, buf);

    sprintf(buf, "PEG_SCCP_USER_MSG_SENT                  :%d\n", sccpPegs.userMsgsSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_MSG_RECEIVED            :%d\n", sccpPegs.remoteMsgsRcvd);
    strcat(buf1, buf);
/*    sprintf(buf, "PEG_SCCP_REMOTE_MSG_RECEIVED            :%d\n", sccpPegs.routingFailure); */
    sprintf(buf, "PEG_SCCP_ROUTING_FAILURE            :%d\n", sccpPegs.routingFailure);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_GTT_REQUEST             :%d\n", sccpPegs.remoteGTTRequest);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_GTT_SUCCESS             :%d\n", sccpPegs.remoteGTTSucc);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_GTT_FAILURE             :%d\n", sccpPegs.remoteGTTFail);
    strcat(buf1, buf);

    sprintf(buf, "PEG_SCCP_REMOTE_MSG_DECODE_ERR          :%d\n", sccpPegs.remoteMsgsDecodeErr);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_MSG_ENCODE_ERR            :%d\n", sccpPegs.userMsgsEncodeErr);
    strcat(buf1, buf);

    sprintf(buf, "PEG_SCCP_REMOTE_REASSEMBLE_ERR          :%d\n", sccpPegs.remoteReassembleErr);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_HOP_COUNTER_VIOLATION_ERR      :%d\n", sccpPegs.hopCounterVilotionErr);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_SEGMENTATION_ERR          :%d\n", sccpPegs.userSegmentationErr);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_TIMER_TIAR_EXPIRY              :%d\n", sccpPegs.timerTiarExpiry);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_INITIATED_RLS             :%d\n", sccpPegs.userInitiatedRLSD);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_INITITATED_RESET          :%d\n", sccpPegs.userInitiatedReset);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_UDT_RCVD                :%d\n", sccpPegs.remoteUDTRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_XUDT_RCVD               :%d\n", sccpPegs.remoteXUDTRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_UDTS_RCVD               :%d\n", sccpPegs.remoteUDTSRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_XUDTS_RCVD              :%d\n", sccpPegs.remoteXUDTSRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_LUDT_RCVD               :%d\n", sccpPegs.remoteLUDTRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_LUDTS_RCVD              :%d\n", sccpPegs.remoteLUDTSRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_UDT_SENT                  :%d\n", sccpPegs.userUDTSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_XUDT_SENT                 :%d\n", sccpPegs.userXUDTSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_UDTS_SENT                 :%d\n", sccpPegs.userUDTSSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_XUDTS_SENT                :%d\n", sccpPegs.userXUDTSSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_LUDT_SENT                 :%d\n", sccpPegs.userLUDTSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_LUDTS_SENT                :%d\n", sccpPegs.userLUDTSSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_CR_SENT                   :%d\n", sccpPegs.userCRSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_CREF_TO_REMOTE_SENT            :%d\n", sccpPegs.sentCREFToRemote);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_RSR_TO_REMOTE_SENT             :%d\n", sccpPegs.sentRSRToRemote);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_ERR_TO_REMOTE_SENT             :%d\n", sccpPegs.sentERRToRemote);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_CR_RCVD                 :%d\n", sccpPegs.remoteCRRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_CREF_RCVD               :%d\n", sccpPegs.remoteCREFRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_RSR_RCVD                :%d\n", sccpPegs.remoteRSRRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_ERR_RCVD                :%d\n", sccpPegs.remoteERRRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD   :%d\n", sccpPegs.remoteMsgsForLocalSSRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_DT1_SENT                  :%d\n", sccpPegs.userDT1Sent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_DT1_RCVD                :%d\n", sccpPegs.remoteDT1Rcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_DT2_SENT                  :%d\n", sccpPegs.userDT2Sent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_DT2_RCVD                :%d\n", sccpPegs.remoteDT2Rcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_USER_ED_SENT                   :%d\n", sccpPegs.userEDSent);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_ED_RCVD                 :%d\n", sccpPegs.remoteEDRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_SSP_RCVD                :%d\n", sccpPegs.remoteSSPRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_SSA_RCVD                :%d\n", sccpPegs.remoteSSARcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_REMOTE_SSC_RCVD                :%d\n", sccpPegs.remoteSSCRcvd);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_LOCAL_SS_PROHIBITED            :%d\n", sccpPegs.localSSProhibited);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_LOCAL_SS_ALLOWED               :%d\n", sccpPegs.localSSAllowed);
    strcat(buf1, buf);
    sprintf(buf, "PEG_SCCP_LOCAL_SS_CONGESTED             :%d\n", sccpPegs.localSSCongested);
    strcat(buf1, buf);

    DBC_AppendText(dbc, buf1);

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for ansi sccp.
 *
 *  Input Parameters:
 *      Pointer to a file.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the stack informations written successfully on the given file
 *      it returns ITS_SUCCESS else if file pointer is null it will return
 *      ITS_ENULLPTR.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1783, 1778
 *
 ****************************************************************************/

int
INTELLINET_SCCP_Commit_ANSI(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = SCCP_ANSI_TraceData;

    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    if (td != NULL)
    {
        fprintf(fp, "\t\t\t<StackTrace>\n");

        if (TRACE_IsLevelOn(td, SCCP_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(td, SCCP_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, SCCP_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(td, SCCP_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, SCCP_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(td, SCCP_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, SCCP_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(td, SCCP_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, SCCP_TRACE_EVENT))
        {
            if (TRACE_IsOutputOn(td, SCCP_TRACE_EVENT, 0))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_EVENT, 1))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, SCCP_TRACE_EVENT, 2))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"syslog\" />\n");
            }
        }

        fprintf(fp, "\t\t\t</StackTrace>\n");
    }

    fprintf(fp,"\t\t\t\t<Timers\n");

    for (count = 0; count < (int)ANSI_SCCP_Timers.numTimers; count++)
    {
        fprintf(fp,"\t\t\t\t\t%s = \"%d\"\n",SCCP_ANSI_Timers[count],
                                             ANSI_SCCP_Timers.timers[count]);
    }

    fprintf(fp,"\t\t\t\t/>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\t%s = \"%s\"\n", SCCP_PROPAGATE_SCMG_STRING,
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                                   SCCP_B_propagate_SCMG)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\t%s = \"%s\"\n", SCCP_ENABLE_SCMG_STRING,
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                                   SCCP_B_use_SCMG)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\t%s = \"%s\"\n", SCCP_PROPAGATE_ERR_STRING,
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                                   SCCP_B_propagate_ERR)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\t%s = \"%s\"\n", SCCP_PROPAGATE_IT_STRING,
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                                   SCCP_B_propagate_IT)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all SCCP General Config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SCCP_GeneralCfg*    genCfg
 *
 *  Return Value:
 *      None
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_GetGeneralCfg_ANSI(SCCP_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)SCCP_AlarmLevel_ANSI;

    genCfg->debugTrace = TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_DEBUG);
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->debugTraceOutput)
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_WARNING);
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->warningTraceOutput)
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_ERROR);
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->errorTraceOutput)
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
       }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_CRITICAL);
    if (genCfg->criticalTrace)
    {
        genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_CRITICAL, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_CRITICAL, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_CRITICAL, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->criticalTraceOutput)
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->eventTrace = TRACE_IsLevelOn(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT);
    if (genCfg->eventTrace)
    {
        genCfg->eventTraceOutput = 0;
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT, 0))
        {
            genCfg->eventTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT, 1))
        {
            genCfg->eventTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT, 2))
        {
            genCfg->eventTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->eventTraceOutput)
        {
            genCfg->eventTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sets all SCCP General Config
 *
 *  Input Parameters:
 *      SCCP_GeneralCfg*    genCfg
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_SetGeneralCfg_ANSI(SCCP_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    SCCP_AlarmLevel_ANSI = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_DEBUG_STRING,  ITS_TRUE);

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_DEBUG_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_DEBUG_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_WARNING_STRING,  ITS_TRUE);

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_WARNING_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_WARNING_STRING,  ITS_FALSE);
        }

    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_ERROR_STRING,  ITS_TRUE);

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_ERROR_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_ERROR_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_CRITICAL_STRING,  ITS_TRUE);

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_CRITICAL_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_CRITICAL_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->eventTrace)
    {
        TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_EVENT_STRING,  ITS_TRUE);

        if (genCfg->eventTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(SCCP_ANSI_TraceData,
                                       SCCP_EVENT_STRING,
                                       SCCP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(SCCP_ANSI_TraceData, SCCP_EVENT_STRING,  ITS_FALSE);
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all SCCP Behaviors
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SCCP_Behaviors* behaviors
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_GetBehaviors_ANSI(SCCP_Behaviors* behaviors)
{
    if (behaviors == NULL)
        return ITS_ENOMEM;

    behaviors->useSCMG = 
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_use_SCMG);
    behaviors->propogateSCMG = 
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG);
    behaviors->propogateIT = 
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT);
    behaviors->propogateERR = 
            BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sets specified SCCP Behaviors
 *
 *  Input Parameters:
 *      ITS_UINT        behId
 *      ITS_UINT        behValue
 *      SCCP_Behaviors* behaviors
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_SetBehavior_ANSI(ITS_UINT behId, ITS_BOOLEAN behValue, SCCP_Behaviors* behaviors)
{
    if (behId == SCCP_ALL_BEHAVIORS)
    {
        if (behaviors == NULL)
            return ITS_ENOMEM;

        BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT, behaviors->useSCMG);
        BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR, behaviors->propogateSCMG);
        BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG, behaviors->propogateIT);
        BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_use_SCMG, behaviors->propogateERR);
    }
    else
    {
        if (behId >= SCCP_NUM_BEHAVIORS)
        {
            SCCP_ERROR(("Behavior Id %d not found\n", behId));
            return ITS_ENOTFOUND;
        }
        else
        {
            BEHAVIORS_SetBehavior(&ANSI_SCCP_Behaviors, behId, behValue);
        }
    }

    SCCP_DEBUG(("Behavior(s) set\n"));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Adds a local SSN entry
 *
 *  Input Parameters:
 *      ITS_UINT        pc
 *      ITS_OCTET       ni
 *      ITS_OCTET       ssn
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_AddLocalSSN_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn)
{
    ITS_INT             ret;
    SCCPSubSystemInfo   info;

    info.pointcode = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.linkSet = 0;
    info.isLocal =ITS_TRUE;

    ret = SCCP_SetSSEntry_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("Local Subsystem %d Addition Error %d\n", ssn, ret));
        return ret;
    }

    SCCP_DEBUG(("Local Subsystem %d Added\n", ssn));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Removes a local SSN entry
 *
 *  Input Parameters:
 *      ITS_UINT        pc
 *      ITS_OCTET       ni
 *      ITS_OCTET       ssn
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_RemoveLocalSSN_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn)
{
    ITS_INT             ret;
    SCCPSubSystemInfo   info;

    info.pointcode = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.linkSet = 0;
    info.isLocal = ITS_TRUE;

    ret = SCCP_RemSSEntry_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("Local Subsystem %d Removal Error %d\n", ssn, ret));
        return ret;
    }

    SCCP_DEBUG(("Local Subsystem %d Removed\n", ssn));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Adds a remote SSN entry
 *
 *  Input Parameters:
 *      ITS_UINT        pc
 *      ITS_OCTET       ni
 *      ITS_OCTET       ssn
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_AddRemoteSSN_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn)
{
    ITS_INT             ret;
    SCCPSubSystemInfo   info;
    ITS_OCTET           linkset = 0;
    ITS_INT             routeId;
    SS7_Destination*    destPtr = NULL;

    if (ni != MTP3_NIC_INTERNATIONAL &&
        ni != MTP3_NIC_SPARE         &&
        ni != MTP3_NIC_NATIONAL      &&
        ni != MTP3_NIC_RESERVED)
    {
        SCCP_ERROR(("Invalid NI\n"));
        return ITS_EINVALIDARGS;
    }

    destPtr = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);
    if (destPtr == NULL)
    {
        SCCP_ERROR(("Invalid PC/NI. Add a DPC-NI route first\n"));
        return ITS_ENOTFOUND;
    }
    ROUTE_CommitDestination(destPtr, pc, ni, FAMILY_ANSI);

    for(routeId = 0; routeId < destPtr->numEntries; routeId++)
    {
        if (destPtr->entries[routeId]->basic.style == ROUTE_DPC_NI &&
            destPtr->entries[routeId]->basic.type == REMOTE_ROUTE)
        {
                linkset = destPtr->entries[routeId]->linkSet->linkSet;
        }
    }

    if (linkset == 0 && routeId == destPtr->numEntries)
    {
        SCCP_ERROR(("DPC-NI route not found. Add a DPC-NI route first\n"));
        return ITS_ENOTFOUND;
    }

    info.pointcode = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.linkSet = linkset;
    info.isLocal =ITS_FALSE;

    ret = SCCP_SetSSEntry_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("Remote Subsystem %d Addition Error %d\n", ssn, ret));
        return ret;
    }

    SCCP_DEBUG(("Remote Subsystem %d Added\n", ssn));

    SCCP_Alarm_ANSI(501, __FILE__, __LINE__, " PC %x, SSN %d", pc, ssn);

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Removes a remote SSN entry
 *
 *  Input Parameters:
 *      ITS_UINT        pc
 *      ITS_OCTET       ni
 *      ITS_OCTET       ssn
 *
 *  Output Parameters:
 *      None.
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_RemoveRemoteSSN_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn)
{
    ITS_INT             ret;
    SCCPSubSystemInfo   info;
    ITS_OCTET           linkset = 0;
    ITS_INT             routeId;
    SS7_Destination*    destPtr = NULL;

    if (ni != MTP3_NIC_INTERNATIONAL &&
        ni != MTP3_NIC_SPARE         &&
        ni != MTP3_NIC_NATIONAL      &&
        ni != MTP3_NIC_RESERVED)
    {
        SCCP_ERROR(("Invalid NI\n"));
        return ITS_EINVALIDARGS;
    }

    destPtr = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);
    if (destPtr == NULL)
    {
        SCCP_ERROR(("Invalid PC/NI\n"));
        return ITS_ENOTFOUND;
    }
    ROUTE_CommitDestination(destPtr, pc, ni, FAMILY_ANSI);

    for(routeId = 0; routeId < destPtr->numEntries; routeId++)
    {
        if (destPtr->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN &&
            destPtr->entries[routeId]->basic.type == REMOTE_ROUTE)
        {
            linkset = destPtr->entries[routeId]->linkSet->linkSet;
        }
    }

    if (linkset == 0 && routeId == destPtr->numEntries)
    {
        SCCP_ERROR(("DPC-SIO-SSN route not found\n"));
        return ITS_ENOTFOUND;
    }

    info.linkSet = linkset;
    info.pointcode = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.isLocal = ITS_FALSE;

    ret = SCCP_RemSSEntry_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("Remote Subsystem %d Removal Error %d\n", ssn, ret));
        return ret;
    }

    SCCP_DEBUG(("Remote Subsystem %d Removed\n", ssn));

    SCCP_Alarm_ANSI(500, __FILE__, __LINE__, " PC %x, SSN %d", pc, ssn);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all SSN entries
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SCCPSubSystemInfo*      entries
 *      ITS_INT*                numEntries
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_GetAllSSN_ANSI(SCCPSubSystemInfo** entries, ITS_UINT* numEntries)
{
    SCCP_GetAllSSEntries_ANSI(numEntries, entries);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Adds a concerned SSN entry
 *
 *  Input Parameters:
 *      ITS_UINT        pc
 *      ITS_OCTET       ni
 *      ITS_OCTET       ssn
 *      ITS_UINT        cpc
 *      ITS_OCTET       cssn
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_AddConcernedSSN_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn, ITS_UINT cpc, ITS_OCTET cssn)
{
    ITS_INT             ret;
    SCCPConcernedSSInfo info;

    info.pc = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.cpc = cpc;
    info.cssn = cssn;

    ret = SCCP_SetConcernedSS_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("Concerned Subsystem %d Addition Error %d\n", cssn, ret));
        return ret;
    }

    SCCP_DEBUG(("Concerned Subsystem %d Added\n", cssn));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Removes a concerned SSN entry
 *
 *  Input Parameters:
 *      ITS_UINT        pc
 *      ITS_OCTET       ni
 *      ITS_OCTET       ssn
 *      ITS_UINT        cpc
 *      ITS_OCTET       cssn
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_RemoveConcernedSSN_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn, ITS_UINT cpc, ITS_OCTET cssn)
{
    ITS_INT             ret;
    SCCPConcernedSSInfo info;
    MTP3_HEADER         hdr;

    info.pc = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.cpc = cpc;
    info.cssn = cssn;
    info.inservice = ITS_FALSE;

    ret = SCCP_RemConcernedSS_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("Concerned Subsystem %d Removal Error %d\n", cssn, ret));
        return ret;
    }

    ni =  ni | 0x03;

    hdr.sio =  ni;
    MTP3_RL_SET_DPC_VALUE(hdr.label, cpc);
    MTP3_RL_SET_OPC_VALUE(hdr.label, cpc);
    MTP3_RL_SET_SLS(hdr.label, 0);

   // SSTCStopSST(&hdr, cpc, cssn);

    SCCP_DEBUG(("Concerned Subsystem %d Removed\n", cssn));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all Concerned SSN Entries
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SCCPConcernedSSInfo*    entries
 *      ITS_INT*                numEntries
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_GetConcernedSSN_ANSI(SCCPConcernedSSInfo** entries, ITS_UINT* numEntries)
{
    SCCP_GetAllCSSEntries_ANSI(numEntries, entries);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all SCCP Pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SCCP_Pegs*  pegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_GetPegs_ANSI(SCCP_Pegs* sccpPegs)
{
    if (sccpPegs == NULL)
        return ITS_ENOMEM;

    SCCP_GetAllPegs(sccpPegs);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Clears specified SCCP Peg or clears all SCCP Pegs
 *
 *  Input Parameters:
 *      ITS_UINT    pegId
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_ClearPeg_ANSI(ITS_UINT pegId)
{
    if (pegId == SCCP_ALL_PEGS)
    {
        PEG_ClearBlock(ANSI_SCCP_Pegs);
    }
    else
    {
        if (pegId >= PEG_SCCP_NUM_PEGS)
        {
            SCCP_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(ANSI_SCCP_Pegs, pegId);
        }
    }

    SCCP_DEBUG(("Peg(s) cleared\n"));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all SCCP Timers
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SCCP_Timers*    timers
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_GetTimers_ANSI(SCCP_Timers* timers)
{

    if (timers == NULL)
        return ITS_ENOMEM;

    timers->statInfo = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_statInfo);
    timers->coordChg = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_coordChg);
    timers->ignoreSST = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ignoreSST);
    timers->rtgStatInfo = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_rtgStatInfo);
    timers->conn = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_conn);
    timers->release = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_release);
    timers->reset = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reset);
    timers->ias = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ias);
    timers->iar = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_iar);
    timers->guard = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_guard);
    timers->reassembly = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reassembly);
    timers->interval = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_interval);
    timers->repeatRelease = TIMERS_GetTimerValue(&ANSI_SCCP_Timers, SCCP_T_repeatRelease);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sets specified SCCP Timer
 *
 *  Input Parameters:
 *      ITS_UINT        timerId
 *      ITS_UINT        timerValue
 *      SCCP_Timers*    timers
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_SetTimer_ANSI(ITS_UINT timerId, ITS_UINT timerValue, SCCP_Timers* timers)
{
    if (timerId == SCCP_ALL_TIMERS)
    {
        if (timers == NULL)
            return ITS_ENOMEM;

        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_statInfo, timers->statInfo);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_coordChg, timers->coordChg);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ignoreSST, timers->ignoreSST);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_rtgStatInfo, timers->rtgStatInfo);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_conn, timers->conn);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_release, timers->release);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reset, timers->reset);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_ias, timers->ias);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_iar, timers->iar);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_guard, timers->guard);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_reassembly, timers->reassembly);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_interval, timers->interval);
        TIMERS_SetTimerValue(&ANSI_SCCP_Timers, SCCP_T_repeatRelease, timers->repeatRelease);
    }
    else
    {
        if (timerId >= SCCP_NUM_TIMERS)
        {
            SCCP_ERROR(("Timer Id %d not found\n", timerId));
            return ITS_ENOTFOUND;
        }
        else
        {
            TIMERS_SetTimerValue(&ANSI_SCCP_Timers, timerId, timerValue);
        }
    }

    SCCP_DEBUG(("Timer(s) set\n"));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sends SSA
 *
 *  Input Parameters:
 *      ITS_UINT    pc
 *      ITS_OCTET   ni
 *      ITS_OCTET   ssn
 *      ITS_UINT    cpc
 *      ITS_OCTET   cssn
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_SendSSA_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn, ITS_UINT cpc, ITS_OCTET cssn)
{
    ITS_INT             ret;
    SCCPConcernedSSInfo info;

    info.pc = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.cpc = cpc;
    info.cssn = cssn;
    info.inservice = ITS_TRUE;

    ret = SCCP_SendSCMG_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("SSA Send Error %d\n", ret));
        return ret;
    }

SCCP_DEBUG(("SSA Sent\n"));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sends SSP
 *
 *  Input Parameters:
 *      ITS_UINT    pc
 *      ITS_OCTET   ni
 *      ITS_OCTET   ssn
 *      ITS_UINT    cpc
 *      ITS_OCTET   cssn
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_SendSSP_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn, ITS_UINT cpc, ITS_OCTET cssn)
{
    ITS_INT             ret;
    SCCPConcernedSSInfo info;

    info.pc = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.cpc = cpc;
    info.cssn = cssn;
    info.inservice = ITS_FALSE;

    ret = SCCP_SendSCMG_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("SSP Send Error %d\n", ret));
        return ret;
    }

    SCCP_DEBUG(("SSP Sent\n"));
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sends SST
 *
 *  Input Parameters:
 *      ITS_UINT    pc
 *      ITS_OCTET   ni
 *      ITS_OCTET   ssn
 *      ITS_UINT    cpc
 *      ITS_OCTET   cssn
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
SCCP_OSS_SendSST_ANSI(ITS_UINT pc, ITS_OCTET ni, ITS_OCTET ssn, ITS_UINT cpc, ITS_OCTET cssn)
{
    ITS_INT             ret;
    SCCPConcernedSSInfo info;

    info.pc = pc;
    info.ni = ni;
    info.ssn = ssn;
    info.cpc = cpc;
    info.cssn = cssn;
    info.inservice = ITS_TRUE;

    ret = SCCP_SendSST_ANSI(&info);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("SST Send Error %d\n", ret));
        return ret;
    }

    SCCP_DEBUG(("SST Sent\n"));
    return ITS_SUCCESS;
}
ITSSS7DLLAPI int
SCCP_EnableUserPart_ANSI(ITS_OCTET up, ITS_USHORT id)
{
    SCCP_DEBUG(("SCCP_EnableUserPart_ANSI: up: %02x\n ", up));

    if (MUTEX_AcquireMutex(&sccpGate) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_EnableUserPart_ANSI: Couldn't acquire mutex.\n"));

        return (ITS_EBADMUTEX);
    }

    if (up > (SCCP_MAX_USER_PARTS-1))
    {
        SCCP_ERROR(("SCCP_EnableUserPart_ANSI: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&sccpGate);

        return (ITS_EINVALIDARGS);
    }

    userParts[up] = id;

    SCCP_DEBUG(("SCCP_EnableUserPart_ANSI: up %02x enabled\n", up));

    return MUTEX_ReleaseMutex(&sccpGate);
}

ITSSS7DLLAPI int
SCCP_DisableUserPart_ANSI(ITS_OCTET up)
{
    SCCP_DEBUG(("SCCP_DisableUserPart_ANSI: up: %02x\n ", up));

    if (MUTEX_AcquireMutex(&sccpGate) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_DisableUserPart_ANSI: Couldn't acquire mutex.\n"));

        return (ITS_EBADMUTEX);
    }

    if (up > (SCCP_MAX_USER_PARTS-1))
    {
        SCCP_ERROR(("SCCP_DisableUserPart_ANSI: User Part out of range.\n"));
        MUTEX_ReleaseMutex(&sccpGate);
        return (ITS_EINVALIDARGS);
    }

    userParts[up] = ITS_FALSE;

    SCCP_DEBUG(("SCCP_DisableUserPart_ANSI: up %02x enabled\n", up));

    return MUTEX_ReleaseMutex(&sccpGate);
}


ITSSS7DLLAPI ITS_USHORT SCCP_UserPartOwner_ANSI(ITS_OCTET up)
{
    volatile ITS_USHORT id;

    SCCP_DEBUG(("SCCP_UserPartOwner_ANSI: up: %02x\n", up));

    if (MUTEX_AcquireMutex(&sccpGate) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCCP_UserPartOwner_ANSI: Couldn't acquire mutex.\n"));

        return (ITS_INVALID_SRC);
    }

    if (up > (SCCP_MAX_USER_PARTS-1))
    {
        SCCP_ERROR(("SCCP_UserPartOwner_ANSI: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&sccpGate);

        return (ITS_INVALID_SRC);
    }

    id = userParts[up];

    SCCP_DEBUG(("SCCP_UserPartOwner_ANSI: up %02x id %04x\n", up, id));

    MUTEX_ReleaseMutex(&sccpGate);
    return (id);
}
static int GetRoutestatus()
{
 ITS_OCTET Ssn;
 SS7_Destination *dest = NULL;
 Ssn = 254; 
 ITS_INT routeId = 0;
 dest = ROUTE_FindDestination (RemoteRoutePc, RemoteRouteNi, FAMILY_ANSI);
 if(dest != NULL)
 {
  for (routeId = 0; routeId < dest->numEntries; routeId++)
    {
        if (dest->entries[routeId]->basic.dpc == RemoteRoutePc
                    && dest->entries[routeId]->basic.criteria.ssn == Ssn
                  && dest->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN)
               {
                  SCCP_DEBUG (("GetRoutestatus:PCSTAUTS=%d\n", dest->status));
                  if (dest->status == DESTINATION_AVAILABLE)
                    {
                      SCCP_DEBUG (("GetRoutestatus:PC UP \n"));
                      return ITS_TRUE;
                    }
                  else if (dest->status == DESTINATION_UNAVAILABLE)
                    {
                      SCCP_DEBUG (("GetRoutestatus:PC DWN \n"));
                      return ITS_FALSE;
                    }
               }
    }
 }
 else
 {
     SCCP_DEBUG (("GetRoutestatus:dest pointer NULL \n"));
     return ITS_FALSE;
 }

}
static int HandlePeerDeadEvent(ITS_EVENT *evt)
{
    ITS_INT SSTkey;
    int error,ret;
    SST_Key key;
    SST_Info *tmp;
    ITS_UINT opc;

   /*
    * lock the table
    */
   
    if (DSM_LockTable (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG) != ITS_SUCCESS)
    {
	SCCP_ERROR (("Failed to lock SCMG table\n"));
	return (ITS_EBADMUTEX);
    }
    memset (&key, 0, sizeof (key));
    key.dpc = RemoteRoutePc;
    key.ssn = 254;
    key.dsmNodeId=DSM_GetNodeId();
    key.sio = (RemoteRouteNi|0x01);
    SSTkey =  key.dpc | ( key.sio << 24)|(DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL << 16);
    SCCP_DEBUG (("HandlePeerDeadEvent:Find RemoteRoutePc[%d] key.sio[%d] SSTkey=[%d]\n",RemoteRoutePc,key.sio,SSTkey));

    if ((tmp = DSM_FindNoLock (DSM_SccpFtGroupId,DSM_TABLE_ANSI_SCMG,(ITS_OCTET *) &SSTkey, sizeof (ITS_INT),
                                                                 &error)) != NULL)
    {
       SCCP_DEBUG (("HandlePeerDeadEvent:Entry found in DSM_TABLE_ANSI_SCMG Table\n"));
       SCCP_DEBUG (("HandlePeerDeadEvent:tmp->SSTSuccessFlag[%d]:tmp->dsmNodeId[%d]\n",tmp->SSTSuccessFlag,tmp->dsmNodeId));
        if((tmp->SSTSuccessFlag == 0) &&  (tmp->dsmNodeId != DSM_GetNodeId()))
        {
           SCCP_DEBUG (("HandlePeerDeadEvent:No SSA received on Peer Card, therefore starting SST Again\n"));
           key.type=SCLC_TIMER_TYPE;
           key.opc=LocalRoutePc;
           SCCP_DEBUG (("HandlePeerDeadEvent:key.opc[%d]\n",key.opc));
           key.dsmNodeId=DSM_GetNodeId();
           tmp->dsmNodeId = DSM_GetNodeId();
           SCCP_DEBUG (("HandlePeerDeadEvent:STARTING SST Timer on NodeID[%d]\n",tmp->dsmNodeId));
           tmp->serial = TIMERS_StartSharedTimer (ITS_SCCP_SRC,
                                                  (TIMERS_GetTimerValue (&ANSI_SCCP_Timers,SCCP_T_statInfo)),
                                                  (void*)&key, sizeof(key));
           SCCP_DEBUG (("HandlePeerDeadEvent:START the SST Timer with SERIAL [%d] dpc=[%d] dsmNodeId[%d]",tmp->serial,key.dpc,key.dsmNodeId));

           DSM_CommitNoLock (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG,(ITS_OCTET *) & SSTkey, sizeof (ITS_INT), tmp);
           SCCP_DEBUG (("HandlePeerDeadEvent:value of SSTkey for commit:%d\n", SSTkey));
        }
        else
        {
          SCCP_DEBUG (("HandlePeerDeadEvent: SST Running on Self Card or SSA has been received on PEER card:do nothing\n"));
        }
    }
    else
    {
          SCCP_DEBUG (("HandlePeerDeadEvent:No entry in DSM_TABLE_ANSI_SCMG Table:\n"));
       ret = GetRoutestatus();
       if(ret == ITS_TRUE)
       {
          SCCP_DEBUG (("HandlePeerDeadEvent:GetRoutestatus TRUE:Starting SST Again\n"));
          /* Adding Entry in SCMG table*/
          if ((tmp = (SST_Info *) DSM_AllocNoLock (DSM_SccpFtGroupId,
                                                    DSM_TABLE_ANSI_SCMG,(ITS_OCTET *) & SSTkey, sizeof (ITS_INT),
                                                    sizeof (SST_Info), &error)) == NULL)
           {
               SCCP_ERROR (("HandlePeerDeadEvent:Fail to alloc : Out of DSM\n"));
               DSM_UnlockTable (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);
               return (ITS_ENOMEM);
           }
           tmp->routeInfo.basic.type = REMOTE_ROUTE;
           tmp->SSTSuccessFlag = 0;
           tmp->routeInfo.basic.dpc = key.dpc;
           tmp->routeInfo.basic.criteria.ssn = key.ssn;
           tmp->routeInfo.basic.criteria.sio = key.sio;
           MTP3_RL_SET_DPC_VALUE (tmp->sourceHdr.label, key.dpc);
           MTP3_RL_SET_OPC_VALUE (tmp->sourceHdr.label, LocalRoutePc);
           MTP3_HDR_SET_SIO (tmp->sourceHdr, RemoteRouteNi | MTP3_SIO_SCCP);
           MTP3_RL_SET_SLS(tmp->sourceHdr.label, 0);
             
           /*Starting SST Timer */
           key.type=SCLC_TIMER_TYPE;
           key.opc=LocalRoutePc;
           SCCP_DEBUG (("HandlePeerDeadEvent:key.opc[%d]\n",key.opc));
           key.dsmNodeId=DSM_GetNodeId();
           tmp->dsmNodeId = DSM_GetNodeId();
           SCCP_DEBUG (("HandlePeerDeadEvent:STARTING SST Timer on NodeID[%d]\n",tmp->dsmNodeId));
           tmp->serial = TIMERS_StartSharedTimer (ITS_SCCP_SRC,
                                                  (TIMERS_GetTimerValue (&ANSI_SCCP_Timers,SCCP_T_statInfo)),
                                                  (void*)&key, sizeof(key));
           SCCP_DEBUG (("HandlePeerDeadEvent:START the SST Timer with SERIAL [%d] dpc=[%d] dsmNodeId[%d]",tmp->serial,key.dpc,key.dsmNodeId));

           DSM_CommitNoLock (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG,(ITS_OCTET *) & SSTkey, sizeof (ITS_INT), tmp);
           SCCP_DEBUG (("HandlePeerDeadEvent:value of SSTkey for commit:%d\n", SSTkey));

       }
       else
       {
          SCCP_DEBUG (("HandlePeerDeadEvent:GetRoutestatus FALSE:do nothing\n"));
       }
    }
    /* done with this table now */
    DSM_UnlockTable (DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);
    return (ITS_SUCCESS);
}
