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
 *  ID: $Id: ansi-tcap.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
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
 * LOG: Revision 9.2  2005/05/06 09:41:26  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1778) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:36  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.10  2005/03/21 13:53:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.10  2005/02/21 10:22:51  sbabu
 * LOG: Fix for bug 1564 - Inconsistency in displaying output for t*_get_gen_cfg
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.9  2005/02/03 08:45:29  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.8  2005/01/31 10:55:48  snagesh
 * LOG: TCAP OSS APIs added
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.7  2005/01/24 14:31:00  sbabu
 * LOG: OAM Bug fixes for 1430,1431,1432,1469
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.6  2005/01/06 19:46:19  snagesh
 * LOG: Modified TCAP Peg #define
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.5  2005/01/05 13:29:23  craghavendra
 * LOG: Update the Console Functions for Syslog.
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.4  2005/01/05 10:47:13  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.3  2005/01/05 05:51:56  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.2  2005/01/04 13:43:56  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.4.2.1.8.3.6.1  2004/12/31 09:42:56  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.1.8.3  2004/09/15 05:46:43  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.4.2.1.8.2  2004/02/16 12:58:21  yranade
 * LOG: TCAP Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.4.2.1.8.1  2004/02/12 08:44:12  mmanikandan
 * LOG: Redundancy Implementation.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/04/17 20:57:41  rsonak
 * LOG: Create and delete mutexes
 * LOG:
 * LOG: Revision 7.4  2003/02/07 11:42:31  tsanthosh
 * LOG: Modified to add some tcap pegs.
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
 * LOG: Revision 6.17  2002/08/25 23:35:47  ngoel
 * LOG: make mml command consistent
 * LOG:
 * LOG: Revision 6.16  2002/08/22 01:14:09  randresol
 * LOG: fix pointer problem seen in 64bit mode. replace
 * LOG: rinfo = *(ROUTE_InfoPtr *)(tmp->data); by the safer
 * LOG: memcpy(&rinfo, tmp->data, sizeof(rinfo));
 * LOG:
 * LOG: Revision 6.15  2002/08/04 18:29:54  ngoel
 * LOG: take peg type as string
 * LOG:
 * LOG: Revision 6.14  2002/07/25 21:42:43  ngoel
 * LOG: add MML command to set local ssn
 * LOG:
 * LOG: Revision 6.13  2002/07/25 14:12:48  ngoel
 * LOG: Add clear all peg command
 * LOG:
 * LOG: Revision 6.12  2002/07/24 20:00:47  ngoel
 * LOG: change alarm level and trace level to strings for MML
 * LOG:
 * LOG: Revision 6.11  2002/07/17 21:49:26  ngoel
 * LOG: add invalid argument print for MML
 * LOG:
 * LOG: Revision 6.10  2002/07/15 14:45:20  ngoel
 * LOG: Add TCAP MML code
 * LOG:
 * LOG: Revision 6.9  2002/07/03 21:19:48  mmiers
 * LOG: Fixes for DSM, VFrame
 * LOG:
 * LOG: Revision 6.8  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.7  2002/06/03 16:43:50  mmiers
 * LOG: NI fixes, Concerned fixes.
 * LOG:
 * LOG: Revision 6.6  2002/05/29 22:43:47  mmiers
 * LOG: Signature change
 * LOG:
 * LOG: Revision 6.5  2002/05/07 15:44:04  wweng
 * LOG: Rename init/term functions for collision avoidance
 * LOG:
 * LOG: Revision 6.4  2002/04/29 17:00:12  mmiers
 * LOG: Add first cut of mgmt API for TCAP, MTP3.
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
 * LOG: Revision 5.10  2002/01/09 22:36:56  mmiers
 * LOG: Fix hybrid stack build errors.
 * LOG:
 * LOG: Revision 5.9  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 5.8  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.7  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.6  2001/10/18 19:01:40  mmiers
 * LOG: Fallout from the routing changes
 * LOG:
 * LOG: Revision 5.5  2001/09/26 00:31:03  mmiers
 * LOG: Remove a couple of warnings and fixmes
 * LOG:
 * LOG: Revision 5.4  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.3  2001/09/06 15:33:32  mmiers
 * LOG: Cleanup.  Add reserved NI use to TCAP.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/08/07 19:11:45  mmiers
 * LOG: Add MTP3 threads.  Also a little cleanup.
 * LOG:
 * LOG: Revision 4.3  2001/07/10 15:24:08  mmiers
 * LOG: Make sure we aren't exceeding the modified timer context size.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 19:18:38  mmiers
 * LOG: Make the stack participate in HMI
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.9  2001/04/04 15:29:17  mmiers
 * LOG: Remove extraneous traces.
 * LOG:
 * LOG: Revision 3.8  2001/02/06 17:58:42  mmiers
 * LOG: About 90% thread safe.  SCCP connection oriented isn't, neither
 * LOG: are simultaneous messages within a TCAP transaction.
 * LOG:
 * LOG: Revision 3.7  2001/02/06 17:11:48  mmiers
 * LOG: Multithreaded stack layers are there.  Locking needs to be added
 * LOG: to the context structures.
 * LOG:
 * LOG: Revision 3.6  2001/01/18 17:40:52  omayor
 * LOG: Added SCCP flags when creating the TCAP TQUEUE trans. This is to allow the
 * LOG: BuildCPCData callback to build LPC_RID table (in SCCP)
 * LOG:
 * LOG: Revision 3.5  2000/10/05 23:04:32  mmiers
 * LOG: Go back to the old way for now.
 * LOG:
 * LOG: Revision 3.4  2000/09/25 18:31:48  mmiers
 * LOG: Set up for the new routing table.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:56:49  mmiers
 * LOG:
 * LOG:
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 22:33:43  mmiers
 * LOG: Prepare for reentrant SCCP, TCAP, and ISUP warning removal.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:29  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/03/29 18:27:49  mmiers
 * LOG:
 * LOG:
 * LOG: Don't trace for non-errors before trace settings have been established.
 * LOG:
 * LOG: Revision 2.2  2000/02/12 00:41:16  mmiers
 * LOG:
 * LOG: Convert vendor to new CORE code.
 * LOG:
 * LOG: Revision 2.1  1999/12/18 00:21:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:27  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/11/10 23:35:09  lbana
 * LOG:
 * LOG:
 * LOG: Make the trace levels have different file names.
 * LOG:
 * LOG: Revision 1.10  1999/10/25 20:24:48  mmiers
 * LOG:
 * LOG:
 * LOG: Corrections for the new transport class.
 * LOG:
 * LOG: Revision 1.9  1999/10/05 19:01:01  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.8  1999/10/01 14:48:31  mmiers
 * LOG:
 * LOG:
 * LOG: Remove "fileValid" check.  This looks "under the hood" inside
 * LOG: the resource database mechanism and cannot be relied on.
 * LOG:
 * LOG: Revision 1.7  1999/08/27 16:50:11  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.6  1999/08/26 23:44:56  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.5  1999/08/11 23:08:44  mmiers
 * LOG:
 * LOG:
 * LOG: Trace tweak again.
 * LOG:
 * LOG: Revision 1.4  1999/08/11 19:04:43  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for new trace structures.
 * LOG:
 * LOG: Revision 1.3  1999/03/17 23:59:07  mmiers
 * LOG:
 * LOG:
 * LOG: Standardize the names.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 20:55:05  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:44  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.36  1999/03/17 15:09:24  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.35  1999/03/12 21:25:45  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitized build.
 * LOG:
 * LOG: Revision 1.34  1999/02/09 21:46:39  mmiers
 * LOG:
 * LOG:
 * LOG: Use standard thread return type and exit macros.
 * LOG:
 * LOG: Revision 1.33  1998/11/12 00:09:39  mmiers
 * LOG: Debug SSP/SSA.
 * LOG:
 * LOG: Revision 1.32  1998/11/11 03:33:49  mmiers
 * LOG: Do UIS/UOS for TCAP ssn's.
 * LOG:
 * LOG: Revision 1.31  1998/11/10 03:26:39  mmiers
 * LOG: Update/include the string defines.
 * LOG:
 * LOG: Revision 1.30  1998/11/03 03:04:49  mmiers
 * LOG: Only set started flag after complete initialization.
 * LOG:
 * LOG: Revision 1.29  1998/10/30 21:31:35  whu
 * LOG: Disable connection timers, add mutex around reference allocation.
 * LOG:
 * LOG: Revision 1.28  1998/10/23 00:01:28  whu
 * LOG: Fix debugging flags in INI files.
 * LOG: Fix recently introduced bug in SCCP with connection references.
 * LOG:
 * LOG: Revision 1.27  1998/10/14 23:29:37  mmiers
 * LOG: Set trace levels from INI file.
 * LOG:
 * LOG: Revision 1.26  1998/10/02 16:44:10  jrao
 * LOG: Shouldn't have committed this one.
 * LOG:
 * LOG: Revision 1.25  1998/10/02 16:40:58  jrao
 * LOG: Fix cmp handling (missing returns).
 * LOG:
 * LOG: Revision 1.24  1998/09/28 16:30:47  mmiers
 * LOG: Notify on successful initialization.
 * LOG:
 * LOG: Revision 1.23  1998/09/25 23:25:08  mmiers
 * LOG: Add output init flags.
 * LOG:
 * LOG: Revision 1.22  1998/09/25 21:34:43  mmiers
 * LOG: Fix file tracing.
 * LOG:
 * LOG: Revision 1.21  1998/09/25 21:10:58  mmiers
 * LOG: Fixup for trace.
 * LOG:
 * LOG: Revision 1.20  1998/09/23 19:52:40  mmiers
 * LOG: Change ABORT to CRITICAL.  Severity looks wrong, otherwise.
 * LOG:
 * LOG: Revision 1.19  1998/09/22 18:59:11  mmiers
 * LOG: Turn debug trace off by default.
 * LOG:
 * LOG: Revision 1.18  1998/09/21 17:20:10  mmiers
 * LOG: Add tracing into everything.
 * LOG:
 * LOG: Revision 1.17  1998/09/18 23:15:08  mmiers
 * LOG: add level names.
 * LOG:
 * LOG: Revision 1.16  1998/09/18 22:47:59  mmiers
 * LOG: Add tracing.
 * LOG:
 * LOG: Revision 1.15  1998/07/22 15:19:18  ahanda
 * LOG: Added ITS_SS7 for mask during transport creation
 * LOG:
 * LOG: Revision 1.14  1998/07/21 21:28:30  mmiers
 * LOG: Modify SCCP implementation.
 * LOG:
 * LOG: Revision 1.13  1998/07/17 19:32:27  mmiers
 * LOG: Change TCAP to skip dialogue ids after dialog completes.
 * LOG:
 * LOG: Revision 1.12  1998/07/08 16:39:14  mmiers
 * LOG: Start thinking about reject cases.  Group into a common function.
 * LOG:
 * LOG: Revision 1.11  1998/07/07 15:21:21  mmiers
 * LOG: Bug fixes for TCAP.
 * LOG:
 * LOG: Revision 1.10  1998/07/03 19:42:20  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.9  1998/07/01 22:53:36  mmiers
 * LOG: Add timer support in.
 * LOG:
 * LOG: Revision 1.8  1998/06/29 19:27:21  mmiers
 * LOG: Convert TCAP to use SCCP.
 * LOG:
 * LOG: Revision 1.7  1998/06/26 16:31:50  mmiers
 * LOG: Complete the transport conversion.
 * LOG:
 * LOG: Revision 1.6  1998/06/26 15:08:05  mmiers
 * LOG: Convert TCAP to use C style transport.
 * LOG:
 * LOG: Revision 1.5  1998/06/25 15:27:01  ahanda
 * LOG: HLR debugging fixes.
 * LOG:
 * LOG: Revision 1.4  1998/06/23 00:35:37  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:29  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/17 22:19:18  mmiers
 * LOG: Add dialogue allocator.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:32  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.15  1998/06/17 19:57:03  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.14  1998/06/16 00:00:20  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.13  1998/06/12 17:00:10  ahanda
 * LOG: Remove the trace subsystem from TCAP for now.
 * LOG:
 * LOG: Revision 1.12  1998/06/01 23:18:16  mmiers
 * LOG: More documentation.  Custom build steps for TCAP, SCCP.
 * LOG:
 * LOG: Revision 1.11  1998/05/31 22:20:13  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.10  1998/05/26 16:29:26  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.9  1998/05/20 20:15:29  mmiers
 * LOG: Get test8 (process framework) compiled and linked.  Not
 * LOG: all code is linked in (no sending yet, which will cause more
 * LOG: undefined externals).
 * LOG:
 * LOG: Revision 1.8  1998/05/05 20:24:09  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.7  1998/04/29 22:45:02  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_ANSI_SRC.
 * LOG:
 * LOG: Revision 1.6  1998/04/29 21:10:18  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.5  1998/04/28 22:52:00  mmiers
 * LOG: Complete the pepsy<->ITS conversion code.  This is pretty close to
 * LOG: actually working, now.  Must fill in the context management functions
 * LOG: and then debug.
 * LOG:
 * LOG: Revision 1.4  1998/04/23 17:04:02  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.3  1998/04/23 02:33:01  mmiers
 * LOG: More work on our TCAP implementation.  Made this single threaded,
 * LOG: multiple threads didn't buy anything, but did cost a *bunch* of
 * LOG: unnecessary hops between threads.  We're down to 3/2 hops in/out
 * LOG: of a process.
 * LOG:
 * LOG: Revision 1.2  1998/04/16 16:40:03  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:05:35  mmiers
 * LOG: TCAP implementation for ANSI.  Not quite there yet.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <assert.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_thread_pool.h>
#include <its_mutex.h>
#include <its_assertion.h>
#include <its_dsm.h>
#include <its_redundancy.h>
#include <its_ctf.h>

#ident "$Id: ansi-tcap.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#include <ansi/tcap.h>

#include "tcap_intern.h"

TQUEUETRAN_Manager *__TCAP_ANSI_RcvQueue;
extern MLIST_Manager* __TCAP_ANSI_primQueue;

static ITS_CHAR *tcapPegStr[] =
{
 "PEG_TCAP_APP_MSG_SENT",
 "PEG_TCAP_APP_MSG_DISCARDED",
 "PEG_TCAP_APP_CMP_SENT",
 "PEG_TCAP_APP_CMP_DISCARDED",
 "PEG_TCAP_APP_DLG_SENT",
 "PEG_TCAP_REMOTE_DLG_RCVD",
 "PEG_TCAP_REMOTE_CMP_RCVD",
 "PEG_TCAP_REMOTE_CMP_DISCARDED",
 "PEG_TCAP_REMOTE_MSG_RCVD",
 "PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD",
 "PEG_TCAP_REMOTE_MSG_DISCARDED",
 "PEG_TCAP_ACTIVE_DIALOGUE",
 "PEG_TCAP_ACTIVE_TRANSACTIONS",
 "PEG_TCAP_APP_PREARRANGED_END_SENT",
 "PEG_TCAP_INVALID_SCCP_RCVD",
 "PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD",
 "PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD",
 "PEG_TCAP_REMOTE_UNI_RCVD",
 "PEG_TCAP_APP_SCCP_CLASS_0_SENT",
 "PEG_TCAP_APP_SCCP_CLASS_1_SENT",
 "PEG_TCAP_APP_UNI_SENT",
 "PEG_TCAP_APP_ABORT_SENT",
 "PEG_TCAP_REMOTE_ABORT_RCVD",
 "PEG_TCAP_APP_REJECT_SENT",
 "PEG_TCAP_REMOTE_REJECT_RCVD",
 "PEG_TCAP_LOCAL_CANCEL",
 "PEG_TCAP_DLG_SEND_REMOTE_FAIL",
 "PEG_TCAP_DLG_SEND_APP_FAIL",
 "PEG_TCAP_APP_INVOKE_SENT",
 "PEG_TCAP_APP_RESULT_SENT",
 "PEG_TCAP_APP_ERROR_SENT",
 "PEG_TCAP_REMOTE_INVOKE_RCVD",
 "PEG_TCAP_REMOTE_RESULT_RCVD",
 "PEG_TCAP_REMOTE_ERROR_RCVD",

 "PEG_TCAP_APP_OP_CLASS_1_SENT",
 "PEG_TCAP_APP_OP_CLASS_2_SENT",
 "PEG_TCAP_APP_OP_CLASS_3_SENT",
 "PEG_TCAP_APP_OP_CLASS_4_SENT",
 "PEG_TCAP_APP_BEGIN_SENT",
 "PEG_TCAP_REMOTE_BEGIN_RCVD",
 "PEG_TCAP_APP_CONT_SENT",
 "PEG_TCAP_APP_END_SENT",
 "PEG_TCAP_REMOTE_END_RCVD",
 "PEG_TCAP_REMOTE_CONT_RCVD",

 "PEG_TCAP_APP_QWOP_SENT",
 "PEG_TCAP_REMOTE_QWOP_RCVD",
 "PEG_TCAP_APP_QWIP_SENT",
 "PEG_TCAP_REMOTE_QWIP_RCVD",
 "PEG_TCAP_APP_RESP_SENT",
 "PEG_TCAP_REMOTE_RESP_RCVD",
 "PEG_TCAP_APP_CWOP_SENT",
 "PEG_TCAP_REMOTE_CWOP_RCVD",
 "PEG_TCAP_APP_CWIP_SENT",
 "PEG_TCAP_REMOTE_CWIP_RCVD",
  NULL
};

static TRACE_OutputInitializer fileCritTrace =
{
    TCAP_FILE_STRING,
    ITS_TRUE,
    TCAP_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    TCAP_FILE_STRING,
    ITS_TRUE,
    TCAP_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    TCAP_FILE_STRING,
    ITS_TRUE,
    TCAP_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    TCAP_FILE_STRING,
    ITS_TRUE,
    TCAP_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    TCAP_FILE_STRING,
    ITS_TRUE,
    TCAP_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    TCAP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    TCAP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer TCAP_TraceMap[] =
{
    {TCAP_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {TCAP_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {TCAP_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {TCAP_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {TCAP_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

TRACE_Data* TCAP_ANSI_TraceData = NULL;

THREAD_RET_TYPE
ANSI_TCAPThread(void *arg);

static ITS_THREAD   *tcapThread;

static int numThreads = 1;

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  stopped = ITS_FALSE;
static void DumpAllTCAPPegs(DBC_Server *dbc);
static ITS_UINT pegs[PEG_TCAP_NUM_PEGS];
static PEGS_DECL_SUBSYS(ANSI_TCAP, pegs);
PEG_Manager *ANSI_TCAP_Pegs = &ANSI_TCAP_PEGS;

static ITS_BOOLEAN behaviors[TCAP_NUM_BEHAVIORS];
BEHAVIORS_DECL_SUBSYS(ANSI_TCAP, behaviors);

ITS_MUTEX    __localTxGate;

ITS_BOOLEAN isMsgBasedRedundancy = ITS_FALSE;

/*
 * management class record
 */
static TCAP_MgmtClassRec TCAP_MgmtClassRec_ANSI =
{
    /* core part */
    {
        NULL,                           /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        "ANSI TCAPMgmt",                /* class name */
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
        &ANSI_TCAP_PEGS,
        &ANSI_TCAP_Behaviors,
        NULL,
        ANSI_TCAP_Alarms,
    }
};

ITSSS7DLLAPI ITS_Class TCAP_MgmtClass_ANSI =
    (ITS_Class)&TCAP_MgmtClassRec_ANSI;

/*
 * externs
 */
extern int INTELLINET_SendUOS_ANSI(ITS_HANDLE handle, ITS_OCTET ni,
                                   ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SendUIS_ANSI(ITS_HANDLE handle, ITS_OCTET ni,
                                   ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SendUOS_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                    ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SendUIS_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                    ITS_UINT pc, ITS_OCTET ssn);

#if defined(SPLIT_STACK)
#define INTELLINET_SendUIS  INTELLINET_SendUIS_CCITT
#define INTELLINET_SendUOS  INTELLINET_SendUOS_CCITT
#else
#define INTELLINET_SendUIS  INTELLINET_SendUIS_ANSI
#define INTELLINET_SendUOS  INTELLINET_SendUOS_ANSI
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
static void
InitSettings()
{

    BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI,
                          ITS_FALSE);

    /*
     * determine tracing from INI files
     */
    if (TRANSPORT_RES(__TCAP_ANSI_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__TCAP_ANSI_RcvQueue);
        char *name = TRANSPORT_NAME(__TCAP_ANSI_RcvQueue);

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

        /* Should we use the reserved NI */
        if (RESFILE_GetKeyValueOf(res, name, TCAP_USE_RESERVED_NI_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors,
                                  TCAP_B_use_reserved_NI,
                                  strstr(value, "yes") != NULL ||
                                  strstr(value, "YES") != NULL);
        }

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, TCAP_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, TCAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_CRITICAL_STRING,
                                           TCAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_CRITICAL_STRING,
                                           TCAP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_CRITICAL_STRING,
                                           TCAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_CRITICAL_STRING,
                                           TCAP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_CRITICAL_STRING,
                                           TCAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_CRITICAL_STRING,
                                           TCAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, TCAP_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, TCAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_ERROR_STRING,
                                           TCAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_ERROR_STRING,
                                           TCAP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_ERROR_STRING,
                                           TCAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_ERROR_STRING,
                                           TCAP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_ERROR_STRING,
                                           TCAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_ERROR_STRING,
                                           TCAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, TCAP_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, TCAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_WARNING_STRING,
                                           TCAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_WARNING_STRING,
                                           TCAP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_WARNING_STRING,
                                           TCAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_WARNING_STRING,
                                           TCAP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_WARNING_STRING,
                                           TCAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_WARNING_STRING,
                                           TCAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_WARNING_STRING, ITS_FALSE);
            }
        }

        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, TCAP_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, TCAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_DEBUG_STRING,
                                           TCAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_DEBUG_STRING,
                                           TCAP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_DEBUG_STRING,
                                           TCAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_DEBUG_STRING,
                                           TCAP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_DEBUG_STRING,
                                           TCAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_DEBUG_STRING,
                                           TCAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_DEBUG_STRING, ITS_FALSE);
            }
        }

        /* Event */
        if (RESFILE_GetKeyValueOf(res, name, TCAP_TRACE_EVENT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, TCAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_EVENT_STRING,
                                           TCAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_EVENT_STRING,
                                           TCAP_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_EVENT_STRING,
                                           TCAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_EVENT_STRING,
                                           TCAP_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, TCAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_EVENT_STRING,
                                           TCAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                           TCAP_EVENT_STRING,
                                           TCAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_EVENT_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                          TCAP_EVENT_STRING, ITS_FALSE);
            }
        }
    }
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
TCAP_StateChangeCallback_ANSI(ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData)
{
    ITS_EVENT *evt = (ITS_EVENT*)callData;

    if (evt->data[1] == ITS_STATE_PRIMARY)
    {
        TCAP_CRITICAL(("TCAP : Request received for change state to active\n"));
    }
    else
    {
        /* Here we have lot of work to do, changing state from active to
         * back up, clean up the  existing transaction TBD
         */
        TCAP_CRITICAL(("TCAP : Request received for change state to backup\n"));
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method initializes the TCAP subsystem for use.
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
 *      If the subsystem is successfully initialized, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ITCAP_Initialize_ANSI(ITS_SS7_HANDLE handle)
{
    SS7_LinkPtr link;
    int i, j;
    DSM_Queue   *rinfoQ;
    DSMQUEUE_Entry  *temp;
    ROUTE_Info *rinfo, *tmprinfo;
    ITS_UINT count, rcount;
    ITS_Class dbClass;
    ITS_USHORT nodeId;
    ITS_EVENT evt;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;

    if ((TCAP_ANSI_TraceData = TRACE_Constructor("ANSI-TCAP",
                                                 TCAP_TraceMap, 5)) == NULL)
    {
        started = ITS_FALSE;
        
        /* TCAP failed to Intialize -  No Memory. */
        return (ITS_ENOMEM);
    }

    if (TCAP_Init_ANSI() != ITS_SUCCESS)
    {
        TCAP_CRITICAL(("TCAP_Initialize: couldn't context tables.\n"));

        started = ITS_FALSE;
        
        return (ITS_ENOMEM);
    }

    if ((__TCAP_ANSI_RcvQueue = TQUEUETRAN_CreateTransport("ANSI-TCAP",
                                                           ITS_TCAP_ANSI_SRC,
                                                           ITS_TCAP_ANSI |
                                                           ITS_SCCP_ANSI |
                                                           ITS_SCCP_CCITT)) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Initialize: couldn't create transport.\n"));
        
        /* TCAP failed to Intialize -  couldn't create transport. */
        TCAP_Alarm_ANSI(1013, __FILE__, __LINE__, NULL);

        TCAP_Term_ANSI();

        TRACE_Destructor(TCAP_ANSI_TraceData);

        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    if ((__TCAP_ANSI_primQueue = MQUEUE_Create()) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Initialize: couldn't create cpt cache.\n"));
        
        /* TCAP failed to Intialize -  couldn't create transport. */

        TCAP_Term_ANSI();

        TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);

        TRACE_Destructor(TCAP_ANSI_TraceData);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    /* read the INI */
    InitSettings();

    /* 
     * Initialize the mutexes 
     */

     if (MUTEX_CreateMutex(&__localTxGate, 0) != ITS_SUCCESS)
     {
         TCAP_CRITICAL(("Couldn't create Mutex\n"));

         return (ITS_EBADMUTEX);
     }

    if ((tcapThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Init: Couldn't create thread array.\n"));
        
        /* TCAP failed to Intialize -  couldn't create thread array. */
        TCAP_Alarm_ANSI(1013, __FILE__, __LINE__, NULL);

        TCAP_Term_ANSI();

        TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);
        MQUEUE_Delete(__TCAP_ANSI_primQueue);

        TRACE_Destructor(TCAP_ANSI_TraceData);

        started = ITS_FALSE;

        return (ITS_EBADTHREAD);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&tcapThread[i], 0, ANSI_TCAPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            TCAP_CRITICAL(("TCAP_Init: Couldn't create TCAP thread.\n"));
        
        
            /* TCAP failed to Intialize -  couldn't create thread. */
            TCAP_Alarm_ANSI(1013, __FILE__, __LINE__, NULL);

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&tcapThread[j]);

                THREAD_DeleteThread(&tcapThread[j]);
            }

            free(tcapThread);

            TCAP_Term_ANSI();

            TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);
            MQUEUE_Delete(__TCAP_ANSI_primQueue);

            TRACE_Destructor(TCAP_ANSI_TraceData);

            started = ITS_FALSE;

            return (ITS_ENOMEM);
        }
    }

    /*
     * Send UIS for all local subsystems handled
     */
    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        TCAP_CRITICAL(("Couldn't lock link list\n"));

        return (ITS_EBADMUTEX);
    }

    for (link = TRANSPORT_SS7_INFO(__TCAP_ANSI_RcvQueue).linkInfo;
         link != NULL;
         link = link->next)
    {
        rinfoQ = link->linkSet->routes;
        rcount = DSMQUEUE_COUNT(link->linkSet->routes);

        for (count = 0, temp = DSMQUEUE_HEAD(rinfoQ); count < rcount &&
             temp != NULL; count++, temp = DSMQUEUE_NEXT(rinfoQ, temp))
        {
            memcpy(&rinfo, temp->data, sizeof(rinfo));

            for (tmprinfo = rinfo; tmprinfo != NULL; tmprinfo = rinfo->next)
            {
                /* Handle range. */
                if (rinfo->basic.type == LOCAL_ROUTE &&
                    (rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
                     rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN))
                {
                    INTELLINET_SendUIS((ITS_HANDLE)__TCAP_ANSI_RcvQueue,
                                       (ITS_OCTET)(rinfo->basic.criteria.sio &
                                                   ROUTE_NI_MASK),
                                       rinfo->basic.dpc,
                                       (ITS_OCTET)rinfo->basic.criteria.ssn);
                }
                else if (rinfo->basic.type == LOCAL_ROUTE &&
                         (rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                          rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE))
                {
                    ITS_USHORT cnt;
         
                    for (cnt = rinfo->basic.criteria.range.begin;
                         cnt <= rinfo->basic.criteria.range.end;
                         cnt++)
                    {
                        INTELLINET_SendUIS((ITS_HANDLE)__TCAP_ANSI_RcvQueue,
                                           (ITS_OCTET)(rinfo->basic.criteria.sio &
                                                       ROUTE_NI_MASK),
                                           rinfo->basic.dpc,
                                           (ITS_OCTET)cnt);
                    }
                }
            }
        }
    }

    ROUTE_UnlockTable();

    /* TCAP Intialized Successfully. */
    TCAP_Alarm_ANSI(1014, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(TCAP_Console_ANSI);
    }

    /* Message Based Redundancy
       Multicast The nodeId from here.
    */
    nodeId = DSM_GetNodeId();

    ITS_EVENT_INIT(&evt, ITS_TCAP_GCS_REQ, 1 + sizeof (ITS_USHORT));
    evt.data[0] = TCAP_NODE_ID;
    evt.data[1] = nodeId;

    if (DSM_MulticastStackEventToFtGroupMembers(
        DSM_TcapFtGroupId,
        evt,
        ITS_TCAP_GCS_REQ,
        ITS_TCAP_ANSI_SRC) == ITS_SUCCESS)
    {
        isMsgBasedRedundancy = ITS_TRUE;
        TCAP_DEBUG(("TCAP_Init: Message Based Redundancy is ACTIVE\n"));
        TCAP_DEBUG(("TCAP_Init: Succesfully multicasted nodeId %d\n", nodeId));
    }
    else
    {
        isMsgBasedRedundancy = ITS_FALSE;
        TCAP_DEBUG(("TCAP_Init: Message Based Redundancy is INACTIVE\n"));
    }

    ITS_EVENT_TERM(&evt); 

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
                                 TCAP_StateChangeCallback_ANSI, NULL);

            TCAP_DEBUG(("ACTIVE-STANDBY configured registering call back\n"));
        }
        else
        {
            TCAP_DEBUG(("ACTIVE-ACTIVE configured no need to register\n"));
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method handles GCS Events mainly 2, NODE_ID and ALLOCATE_DID 
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
int
TCAP_HandleGcsEvent_ANSI(ITS_EVENT *evt)
{
    ITS_USHORT nodeId, ndId;
    ITS_CTXT did;

    TCAP_DEBUG(("TCAP_HandleGcsEvent_ANSI\n"));

    nodeId = DSM_GetNodeId();

    if (evt->data[0] == TCAP_NODE_ID)
    {
        TCAP_DEBUG(("TCAP_HandleGcsEvent_ANSI: Node Id Event\n"));

        if (!isMsgBasedRedundancy)
        {
            /* Something screwed up */
        }
    }
    else if (evt->data[0] == TCAP_ALLOCATE_DID)
    {
        TCAP_DEBUG(("TCAP_HandleGcsEvent_ANSI: Allocate DID Event\n"));
        ndId = evt->data[1];
        did = ITS_GET_CTXT(&evt->data[2]);

        if (ndId != nodeId)
        {
            if (TCAP_AllocateThisDID_ANSI(did) == ITS_SUCCESS)
            {
                TCAP_DEBUG(("TCAP_HandleGcsEvent_ANSI: Succesfully Allocated DID %d\n", did));
            }
            else
            {
                TCAP_ERROR(("TCAP_HandleGcsEvent_ANSI: Unable to Allocate DID %d\n", did));
            }
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates the TCAP subsystem.  Well behaved
 *      applications should call this function before exiting.
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
 *      If the subsystem is successfully terminated, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ITCAP_Terminate_ANSI(ITS_SS7_HANDLE handle)
{
    ITS_EVENT ev;
    void *status;
    SS7_LinkPtr link;
    DSM_Queue   *rinfoQ;
    DSMQUEUE_Entry  *temp;
    ROUTE_Info *rinfo, *tmprinfo;
    ITS_UINT count, rcount;
    int i;
    ITS_Class dbClass;

    if (!started || stopped)
    {
        return;
    }
    /* TCAP Terminating. */
    TCAP_Alarm_ANSI(1015, __FILE__, __LINE__, NULL);

    stopped = ITS_TRUE;

    TCAP_CRITICAL(("TCAP_Terminate.\n"));

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(TCAP_Console_ANSI);
    }

    ROUTE_LockTable();

    /*
     * Send UOS for all local subsystems handled
     */
    for (link = TRANSPORT_SS7_INFO(__TCAP_ANSI_RcvQueue).linkInfo;
         link != NULL;
         link = link->next)
    {
        rinfoQ = link->linkSet->routes;
        rcount = DSMQUEUE_COUNT(link->linkSet->routes);

        for (count = 0, temp = DSMQUEUE_HEAD(rinfoQ); count < rcount &&
             temp != NULL; count++, temp = DSMQUEUE_NEXT(rinfoQ, temp))
        {
            memcpy(&rinfo, temp->data, sizeof(rinfo));

            for (tmprinfo = rinfo; tmprinfo != NULL; tmprinfo = rinfo->next)
            {
                /* Handle range. */
                if (rinfo->basic.type == LOCAL_ROUTE &&
                    (rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
                     rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN))
                {
                    INTELLINET_SendUOS((ITS_HANDLE)__TCAP_ANSI_RcvQueue,
                                       (ITS_OCTET)(rinfo->basic.criteria.sio &
                                                   ROUTE_NI_MASK),
                                       rinfo->basic.dpc,
                                       (ITS_OCTET)rinfo->basic.criteria.ssn);
                }
                else if (rinfo->basic.type == LOCAL_ROUTE &&
                         (rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                          rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE))
                {
                    ITS_USHORT cnt;
         
                    for (cnt = rinfo->basic.criteria.range.begin;
                         cnt <= rinfo->basic.criteria.range.end;
                         cnt++)
                    {
                        INTELLINET_SendUOS((ITS_HANDLE)__TCAP_ANSI_RcvQueue,
                                           (ITS_OCTET)(rinfo->basic.criteria.sio &
                                                       ROUTE_NI_MASK),
                                           rinfo->basic.dpc,
                                           (ITS_OCTET)cnt);
                    }
                }
            }
        }
    }

    ROUTE_UnlockTable();

    ITS_EVENT_INIT(&ev, ITS_TCAP_ANSI_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_TCAP_ANSI_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&tcapThread[i], &status);

        THREAD_DeleteThread(&tcapThread[i]);
    }

    free(tcapThread);

    assert(__TCAP_ANSI_RcvQueue != NULL);

    TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);

    MUTEX_DeleteMutex(&__localTxGate);

    MQUEUE_Delete(__TCAP_ANSI_primQueue);

    TCAP_Term_ANSI();

    TRACE_Destructor(TCAP_ANSI_TraceData);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the ANSI TCAP thread.
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
 *      TCAP function.
 *
 *  See Also:
 ****************************************************************************/
THREAD_RET_TYPE
ANSI_TCAPThread(void *arg)
{
    ITS_EVENT tcapEvent;
    ITS_BOOLEAN cont;

    if (/*sizeof(TCAP_TRANS_ENTRY) > ITS_MAX_TIMER_CONTEXT ||*//* TBD */
        sizeof(TCAP_INVOKE_ENTRY) > ITS_MAX_TIMER_CONTEXT)
    {
        TCAP_CRITICAL(("Structure overflow\n"));
                
        /* TCAP Aborting  - Structure overflow. */
        TCAP_Alarm_ANSI(1016, __FILE__, __LINE__, NULL);

        abort();
    }

    memset(&tcapEvent, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__TCAP_ANSI_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__TCAP_ANSI_RcvQueue))
                                                        (__TCAP_ANSI_RcvQueue,
                                                         &tcapEvent)
           == ITS_SUCCESS)
    {
        if ( (tcapEvent.src == ITS_SCCP_SRC)       ||
             ((tcapEvent.src != ITS_TCAP_ANSI_SRC) &&
             (tcapEvent.src != ITS_TIMER_SRC)       &&
             (tcapEvent.src != ITS_TCAP_GCS_REQ)    &&
             (tcapEvent.src != ITS_TCAP_DID_REQ) ))

        {
            if (DSM_MulticastStackEventToFtGroupMembers(
                   DSM_TcapFtGroupId,
                   tcapEvent,
                   (tcapEvent.src == ITS_SCCP_SRC)    ?
                         ITS_GCS_EVENT_FROM_STACK     :
                         ITS_GCS_EVENT_FROM_APPL,
                   ITS_TCAP_ANSI_SRC) == ITS_SUCCESS )
            {
                continue;
            }
        }

        switch (tcapEvent.src)
        {
        case ITS_TCAP_GCS_REQ:
            break;

        case ITS_TCAP_DID_REQ:
            TCAP_HandleGcsEvent_ANSI(&tcapEvent);
            break;

        case ITS_GCS_EVENT_FROM_STACK:
        case ITS_SCCP_SRC:
            TCAP_DEBUG(("TCAP_Main: process SCCP event.\n"));

            TRPHandleSCCPMsg_ANSI(&tcapEvent);

            if ((tcapEvent.src == ITS_SCCP_SRC) &&
                (TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT)))
            {
                ITS_INT output = 0;
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
            }

            break;

        case ITS_TCAP_ANSI_SRC:
            TCAP_CRITICAL(("TCAP_Main: termination event.\n"));

            TRANSPORT_IS_ACTIVE(__TCAP_ANSI_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_TIMER_SRC:
            TCAP_DEBUG(("TCAP_Main: process TIMER event.\n"));

            CMPHandleTimeout_ANSI(&tcapEvent);
            break;

        case ITS_GCS_EVENT_FROM_APPL:
        default:
            TCAP_DEBUG(("TCAP_Main: process APP event.\n"));

            /* we accept the message regardless.  This is dangerous, as
             * the user may not have registered their application for sending.
             */
            if (TCAP_MSG_TYPE(&tcapEvent) == ITS_TCAP_DLG)
            {
                TPCPIHandleAPPMsg_ANSI(&tcapEvent);
            }
            else if (TCAP_MSG_TYPE(&tcapEvent) == ITS_TCAP_CPT)
            {            
                CMPHandleAPPMsg_ANSI(&tcapEvent);
            }
            else
            {
                /* user sending funky stuff */
                TCAP_CRITICAL(("TCAP_Main: unrecognized event type.\n"));
    
                /* Received Unrecognized or Invalid Event. */
                TCAP_Alarm_ANSI(1017, __FILE__, __LINE__, NULL);
            }
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__TCAP_ANSI_RcvQueue) = ITS_FALSE;

    THREAD_NORMAL_EXIT;
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
ITSSS7DLLAPI TCAPGeneralCfg*
TCAP_GetGeneralCfg_ANSI()
{
    TCAPGeneralCfg *ret;

    ret = calloc(1, sizeof(TCAPGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      2))) ||
                   (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT) &&
                    (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT,
                                      0) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT,
                                      1) ||
                     TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT,
                                      2)));
    ret->alarmLevel = TCAP_AlarmLevel_ANSI;

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
TCAP_SetGeneralCfg_ANSI(TCAPGeneralCfg *data)
{
    TCAP_AlarmLevel_ANSI = data->alarmLevel;
     
    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                      TCAP_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                      TCAP_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                      TCAP_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                      TCAP_DEBUG_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                      TCAP_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData,
                                      data->traceType, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
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
ITSSS7DLLAPI int
TCAP_SetLocalSSEntry_ANSI(TCAPSubSystemInfo *data)
{
    ROUTE_MatchInfo rinfo;
    int ret;

    rinfo.linkSet = 0;
    rinfo.linkCode = 0;
    rinfo.priority = 0;
    rinfo.sls = 0;
    rinfo.rkey = 0;

    rinfo.basic.type = LOCAL_ROUTE;
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
void
TCAP_Console_ANSI(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "ta_get_gen_cfg", "TCAP Get General Config", "", ""))
    {
        TCAPGeneralCfg *cfg;
        cfg =  TCAP_GetGeneralCfg_ANSI();

        sprintf(buf, "*********** TCAP General Config *************\n");
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
        strcpy(buf, "    TCAP Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
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

           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
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

           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
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

            if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
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
 
           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_EVENT))
           {
               strcpy(buf, "        Event     = ");
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_EVENT,
                                      2))
               {
                    strcat(buf, " syslog");
               } 
           }
           else
           {
               strcpy(buf, "        Event     = null");
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
           strcpy(buf, "        Error    = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Event    = null\n");
           DBC_AppendText(dbc, buf);
       }

       sprintf(buf, "*********** End of TCAP General Config *************\n");
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ta_set_gen_cfg", "TCAP Set General Config", 
                      "<al> <tl>",
                     "<alarm level> <On / Off>"))
    {
        TCAPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];
     
         ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel,traceType,traceOutput,traceOn);

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
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, TCAP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, TCAP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, TCAP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, TCAP_ERROR_STRING);
        }
        else if (strstr(traceType, "EVENT") || strstr(traceType, "event"))
        {
            strcpy(cfg.traceType, TCAP_EVENT_STRING);
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
            strcpy(cfg.traceOutput, TCAP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, TCAP_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, TCAP_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  TCAP_SetGeneralCfg_ANSI(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "*********** TCAP General Config Set*************\n");
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ta_get_behavior", "TCAP Get Behaviors", 

                     "", ""))
    {
        if (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI))
        {
            sprintf(buf, "    TCAP_B_use_reserved_NI    <yes> \n");
        }
        else
        {
            sprintf(buf, "    TCAP_B_use_reserved_NI    <no> \n");
        }
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ta_set_behavior", "TCAP Set Behaviors", 
                     "<rni>", ""))
    {
        int rni;

        ret = sscanf(cmdLine, "%s %d", buf, &rni);

        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (rni < 0 || rni > 1)
        {
            sprintf(buf, "Incorrect input : Valid input 1 or 0\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (rni)
        {
            BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI, ITS_TRUE);
            sprintf(buf, "*******TCAP Behaviors Set*******\n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI, 
                                   ITS_FALSE);
            sprintf(buf, "*******TCAP Behaviors UnSet*******\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ta_get_gen_peg", "Get Pegs", "<Peg Id>", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
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
           (atoi(pgName) == ALL_TCAP_PEGS))
        {
            DumpAllTCAPPegs(dbc);
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

        if ((pgNum >= PEG_TCAP_NUM_GEN_PEGS && pgNum < PEG_TCAP_ANSI_PEGS_START) ||
            (pgNum > PEG_TCAP_ANSI_PEGS_END))
        {
            sprintf(buf, "**** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n", tcapPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(ANSI_TCAP_Pegs, pgNum);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ta_clr_gen_peg", "Clear Peg", "<Peg Id>", "<Peg#> <>"))
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
           (atoi(pgName) == ALL_TCAP_PEGS))
        {
            PEG_ClearBlock(ANSI_TCAP_Pegs);

            sprintf(buf, "Clearing All ANSI TCAP Pegs for Now\n");
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

        if ((pgNum >= PEG_TCAP_NUM_GEN_PEGS && pgNum < PEG_TCAP_ANSI_PEGS_START) ||
            (pgNum > PEG_TCAP_ANSI_PEGS_END))
        {
            sprintf(buf, "**** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "Clearing the Peg for %s Now\n", tcapPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        PEG_ClearPeg(ANSI_TCAP_Pegs, pgNum);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Dump all TCAP pegs.
 *
 *  Input Parameters:
 *      DBC_Server *dbc
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
DumpAllTCAPPegs(DBC_Server *dbc)
{

    char buf[32000];
    memset(buf , 0, 32000);
    
    sprintf(buf, "**************** TCAP Pegs ****************\n");
    DBC_AppendText(dbc, buf);

  
    sprintf(buf, "%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_MSG_SENT],
                               PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf, "%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_MSG_DISCARDED],
                               PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED)); 

    DBC_AppendText(dbc, buf); 

    sprintf(buf, "%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_CMP_SENT],
                               PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_CMP_DISCARDED],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED));

    DBC_AppendText(dbc, buf);
       
    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_DLG_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_DLG_SENT)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_DLG_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_DLG_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_CMP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_CMP_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_CMP_DISCARDED],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_MSG_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_MSG_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_MSG_DISCARDED],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_MSG_DISCARDED)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_ACTIVE_DIALOGUE],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_ACTIVE_TRANSACTIONS],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_ACTIVE_TRANSACTIONS)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_PREARRANGED_END_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_PREARRANGED_END_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_INVALID_SCCP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_INVALID_SCCP_RCVD)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_UNI_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_UNI_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_SCCP_CLASS_0_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_SCCP_CLASS_0_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_SCCP_CLASS_1_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_SCCP_CLASS_1_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_UNI_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_UNI_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_ABORT_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_ABORT_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_ABORT_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_ABORT_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_REJECT_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_REJECT_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_REJECT_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_REJECT_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_LOCAL_CANCEL],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_LOCAL_CANCEL));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_DLG_SEND_REMOTE_FAIL],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_DLG_SEND_REMOTE_FAIL));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_DLG_SEND_APP_FAIL],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_INVOKE_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_INVOKE_SENT)); 

    DBC_AppendText(dbc, buf); 

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_RESULT_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_RESULT_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_ERROR_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_ERROR_SENT)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_INVOKE_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_INVOKE_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_RESULT_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_RESULT_RCVD));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_ERROR_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_ERROR_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_QWOP_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_QWOP_SENT));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_QWOP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_QWOP_RCVD)); 

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_QWIP_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_QWIP_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_QWIP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_QWIP_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_RESP_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_RESP_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_RESP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_RESP_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_CWOP_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_CWOP_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_CWOP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_CWOP_RCVD));

    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_APP_CWIP_SENT],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_CWIP_SENT));
 
    DBC_AppendText(dbc, buf);

    sprintf(buf,"%-40s :%d\n",tcapPegStr[PEG_TCAP_REMOTE_CWIP_RCVD],
                              PEG_GetPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_CWIP_RCVD));

    DBC_AppendText(dbc, buf);

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for ansi tcap.
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
 *  Manikandan  05-05-2005    Bug ID:1778
 *
 ****************************************************************************/

int
INTELLINET_TCAP_Commit_ANSI(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = TCAP_ANSI_TraceData;

    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    if (td != NULL)
    {
        fprintf(fp, "\t\t\t<StackTrace>\n");

        if (TRACE_IsLevelOn(td, TCAP_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(td, TCAP_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, TCAP_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(td, TCAP_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, TCAP_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(td, TCAP_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, TCAP_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(td, TCAP_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, TCAP_TRACE_EVENT))
        {
            if (TRACE_IsOutputOn(td, TCAP_TRACE_EVENT, 0))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_EVENT, 1))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, TCAP_TRACE_EVENT, 2))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"syslog\" />\n");
            }
        }

        fprintf(fp, "\t\t\t</StackTrace>\n");
    }

    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\tuse_reserved_NI = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors,
                                   TCAP_B_use_reserved_NI) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all TCAP General Config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      TCAP_GeneralCfg*    genCfg
 *
 *  Return Value:
 *      None
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
TCAP_OSS_GetGeneralCfg_ANSI(TCAP_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)TCAP_AlarmLevel_ANSI;

    genCfg->debugTrace = TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_DEBUG);
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->debugTraceOutput)
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_WARNING);
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->warningTraceOutput)
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_ERROR);
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->errorTraceOutput)
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_CRITICAL);
    if (genCfg->criticalTrace)
    {
        genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_CRITICAL, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_CRITICAL, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_CRITICAL, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->criticalTraceOutput)
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->eventTrace = TRACE_IsLevelOn(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT);
    if (genCfg->eventTrace)
    {
        genCfg->eventTraceOutput = 0;
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT, 0))
        {
            genCfg->eventTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT, 1))
        {
            genCfg->eventTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT, 2))
        {
            genCfg->eventTraceOutput |= TRACE_TO_SYSLOG;
        }
        else if (!genCfg->eventTraceOutput)
        {
            genCfg->eventTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sets all TCAP General Config
 *
 *  Input Parameters:
 *      TCAP_GeneralCfg*    genCfg
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
TCAP_OSS_SetGeneralCfg_ANSI(TCAP_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    TCAP_AlarmLevel_ANSI = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_DEBUG_STRING,  ITS_TRUE);

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                      TCAP_DEBUG_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_DEBUG_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_DEBUG_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_WARNING_STRING,  ITS_TRUE);

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_WARNING_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_WARNING_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_ERROR_STRING,  ITS_TRUE);

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_ERROR_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_ERROR_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_CRITICAL_STRING,  ITS_TRUE);

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_CRITICAL_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_CRITICAL_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->eventTrace)
    {
        TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_EVENT_STRING,  ITS_TRUE);

        if (genCfg->eventTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(TCAP_ANSI_TraceData,
                                       TCAP_EVENT_STRING,
                                       TCAP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(TCAP_ANSI_TraceData, TCAP_EVENT_STRING,  ITS_FALSE);
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all TCAP Behaviors
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      TCAP_Behaviors* behaviors
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
TCAP_OSS_GetBehaviors_ANSI(TCAP_Behaviors* behaviors)
{
    if (behaviors == NULL)
        return ITS_ENOMEM;

    behaviors->useReservedNI = BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sets specified TCAP Behaviors
 *
 *  Input Parameters:
 *      ITS_UINT        behId
 *      ITS_UINT        behValue
 *      TCAP_Behaviors* behaviors
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
TCAP_OSS_SetBehavior_ANSI(ITS_UINT behId, ITS_BOOLEAN behValue, TCAP_Behaviors* behaviors)
{
    if (behId == TCAP_ALL_BEHAVIORS)
    {
        if (behaviors == NULL)
            return ITS_ENOMEM;

        BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI, behaviors->useReservedNI);
    }
    else
    {
        if (behId >= TCAP_NUM_BEHAVIORS)
        {
            TCAP_ERROR(("Behavior Id %d not found\n", behId));
            return ITS_ENOTFOUND;
        }
        else
        {
            BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, behId, behValue);
        }
    }

    TCAP_DEBUG(("Behavior(s) set\n"));
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all TCAP Pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      TCAP_Pegs*  pegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
TCAP_OSS_GetPegs_ANSI(TCAP_Pegs_ANSI* pegs)
{
    if (pegs == NULL)
        return ITS_ENOMEM;

    pegs->genPegs.appMsgSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
    pegs->genPegs.appMsgDiscarded = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
    pegs->genPegs.appCmpSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
    pegs->genPegs.appCmpDiscarded = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
    pegs->genPegs.appDlgSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_DLG_SENT);
    pegs->genPegs.remDlgRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_DLG_RCVD);
    pegs->genPegs.remCmpRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_RCVD);
    pegs->genPegs.remCmpDiscarded = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);
    pegs->genPegs.remMsgRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_RCVD);
    pegs->genPegs.remUnknownMsgRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);
    pegs->genPegs.remMsgDiscarded = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
    pegs->genPegs.activeDlg = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE);
    pegs->genPegs.activeTransaction = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_ACTIVE_TRANSACTIONS);
    pegs->genPegs.appPreArrangedEndSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_PREARRANGED_END_SENT);
    pegs->genPegs.invalidSccpRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_INVALID_SCCP_RCVD);
    pegs->genPegs.remSccpClass0Rcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD);
    pegs->genPegs.remSccpClass1Rcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD);
    pegs->genPegs.remUniRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_UNI_RCVD);
    pegs->genPegs.appSccpClass0Sent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_0_SENT);
    pegs->genPegs.appSccpClass1Sent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_SCCP_CLASS_1_SENT);
    pegs->genPegs.appUniSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_UNI_SENT);
    pegs->genPegs.appAbortSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);
    pegs->genPegs.remAbortRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_ABORT_RCVD);
    pegs->genPegs.appRejectSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_REJECT_SENT);
    pegs->genPegs.remRejectRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_REJECT_RCVD);
    pegs->genPegs.localCancel = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_LOCAL_CANCEL);
    pegs->genPegs.remDlgSendFailed = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_REMOTE_FAIL);
    pegs->genPegs.appDlgSendFailed = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL);
    pegs->genPegs.appInvokeSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_INVOKE_SENT);
    pegs->genPegs.appResultSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_RESULT_SENT);
    pegs->genPegs.appErrorSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_ERROR_SENT);
    pegs->genPegs.remInvokeRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_INVOKE_RCVD);
    pegs->genPegs.remResultRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_RESULT_RCVD);
    pegs->genPegs.remErrorRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_ERROR_RCVD);

    pegs->appQwopSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_QWOP_SENT);
    pegs->remQwopRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_QWOP_RCVD);
    pegs->appQwipSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_QWIP_SENT);
    pegs->remQwipRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_QWIP_RCVD);
    pegs->appRespSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_RESP_SENT);
    pegs->remRespRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_RESP_RCVD);
    pegs->appCwopSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWOP_SENT);
    pegs->remCwopRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CWOP_RCVD);
    pegs->appCwipSent = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWIP_SENT);
    pegs->remCwipRcvd = 
                    PEG_GetPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CWIP_RCVD);

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Clears specified TCAP Peg or clears all TCAP Pegs
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
TCAP_OSS_ClearPeg_ANSI(ITS_UINT pegId)
{
    if (pegId == TCAP_ALL_PEGS)
    {
        PEG_ClearBlock(ANSI_TCAP_Pegs);
    }
    else
    {
        if ((pegId >= PEG_TCAP_NUM_GEN_PEGS && pegId < PEG_TCAP_ANSI_PEGS_START) ||
            (pegId > PEG_TCAP_ANSI_PEGS_END))
        {
            TCAP_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(ANSI_TCAP_Pegs, pegId);
        }
    }

    TCAP_DEBUG(("Peg(s) cleared\n"));
    return ITS_SUCCESS;
}
