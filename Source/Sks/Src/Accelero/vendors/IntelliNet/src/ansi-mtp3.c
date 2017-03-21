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
 *  ID: $Id: ansi-mtp3.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:30  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:05  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/06 09:43:51  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1731, 1780, 1791, 1783) Fix.
 * LOG:
 * LOG: Revision 9.2  2005/04/07 09:35:52  snagesh
 * LOG: Fix for bug #860 and modifications for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.11  2005/03/21 13:53:32  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.8  2005/02/24 11:33:00  mmanikandan
 * LOG: CTF Trace modified.
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.7  2005/02/03 08:45:28  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.6  2005/01/13 06:04:51  snagesh
 * LOG: XML persistency fix for MTP3_NUM_TIMERS
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.5  2005/01/05 10:47:12  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.4  2005/01/04 13:43:54  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.3  2004/12/31 06:38:30  sbabu
 * LOG:  MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.2  2004/12/06 14:03:04  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.6.2.5.2.4.6.1  2004/12/06 10:41:13  adutta
 * LOG: Commented out SCTP check in DBC
 * LOG:
 * LOG: Revision 7.6.2.5.2.4  2004/09/15 05:46:43  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.6.2.5.2.3  2004/08/10 12:14:45  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.6.2.5.2.2  2004/08/06 06:43:46  sswami
 * LOG: SMLC lb-GW Alarm/Alert related changes
 * LOG:
 * LOG: Revision 7.6.2.5.2.1  2004/01/27 14:08:37  sjaddu
 * LOG: Changes for active-back up configuration.
 * LOG:
 * LOG: Revision 7.6.2.5  2003/12/08 11:30:23  kannanp
 * LOG: Changed PEG_MTP3_NUM_PEGS to PEG_MTP3_NUM_PEGS_ANSI.
 * LOG:
 * LOG: Revision 7.6.2.4  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.6.2.3  2003/02/18 07:17:59  ttipatre
 * LOG: Rectify Core problem with pegs when application initializes.
 * LOG:
 * LOG: Revision 7.6.2.2  2003/02/18 01:55:00  randresol
 * LOG: log mtp3 alarms to file
 * LOG:
 * LOG: Revision 7.6.2.1  2003/02/14 07:29:21  randresol
 * LOG: Enhancement for Pegs and Alarms
 * LOG:
 * LOG: Revision 7.6  2003/02/13 10:21:19  ttipatre
 * LOG: new alarms added.
 * LOG:
 * LOG: Revision 7.5  2002/12/24 07:37:51  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 05:04:48  ttipatre
 * LOG: Pegs and Alarms code submission.
 * LOG:
 * LOG: Revision 7.3  2002/11/09 21:52:27  randresol
 * LOG: Add ROUTE Reader/Writer Lock for MTP3 Optimization
 * LOG:
 * LOG: Revision 7.2  2002/09/18 22:23:16  yranade
 * LOG: Avoid coredumps
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.21  2002/08/22 01:14:09  randresol
 * LOG: fix pointer problem seen in 64bit mode. replace
 * LOG: rinfo = *(ROUTE_InfoPtr *)(tmp->data); by the safer
 * LOG: memcpy(&rinfo, tmp->data, sizeof(rinfo));
 * LOG:
 * LOG: Revision 6.20  2002/08/15 20:27:37  mmiers
 * LOG: Don't dereference NULL pointers.
 * LOG:
 * LOG: Revision 6.19  2002/08/15 20:26:11  mmiers
 * LOG: Warning/error removal
 * LOG:
 * LOG: Revision 6.18  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.17  2002/07/12 14:25:11  mmiers
 * LOG: Minor cleanups
 * LOG:
 * LOG: Revision 6.16  2002/07/05 21:12:01  mmiers
 * LOG: Flag fixing
 * LOG:
 * LOG: Revision 6.15  2002/07/02 22:03:09  mmiers
 * LOG: Missing dbc delete
 * LOG:
 * LOG: Revision 6.14  2002/06/19 17:11:00  mmiers
 * LOG: Add MTP3 OAM APIs
 * LOG:
 * LOG: Revision 6.13  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.12  2002/05/15 15:06:47  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.11  2002/05/14 18:03:16  mmiers
 * LOG: Forgot to make it look for itself.
 * LOG:
 * LOG: Revision 6.10  2002/05/14 16:26:28  mmiers
 * LOG: Typo bug
 * LOG:
 * LOG: Revision 6.9  2002/05/13 18:21:48  mmiers
 * LOG: Switch PC order.  Normalize SCCP mgmt API
 * LOG:
 * LOG: Revision 6.8  2002/05/09 19:24:31  mmiers
 * LOG: Get the point codes right.
 * LOG:
 * LOG: Revision 6.7  2002/05/07 15:44:04  wweng
 * LOG: Rename init/term functions for collision avoidance
 * LOG:
 * LOG: Revision 6.6  2002/04/29 21:55:06  mmiers
 * LOG: Make sure we actually init the behaviors.
 * LOG:
 * LOG: Revision 6.5  2002/04/29 21:23:21  randresol
 * LOG: Add InterNode processing and shared booleans
 * LOG:
 * LOG: Revision 6.4  2002/04/29 17:00:12  mmiers
 * LOG: Add first cut of mgmt API for TCAP, MTP3.
 * LOG:
 * LOG: Revision 6.3  2002/03/27 18:38:34  randresol
 * LOG: Remove Visual C++ warnings
 * LOG:
 * LOG: Revision 6.2  2002/03/26 18:28:23  randresol
 * LOG: crBuf, cocbBuf, rtrvBuf and route list are now in DSM
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.42  2001/12/19 23:52:00  mmiers
 * LOG: Get ADAX MTP2 working.
 * LOG:
 * LOG: Revision 5.41  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.40  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.39  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.38  2001/12/04 23:59:50  mmiers
 * LOG: Route testing.
 * LOG:
 * LOG: Revision 5.37  2001/11/20 23:39:57  mmiers
 * LOG: Cut the debug output a bit.
 * LOG:
 * LOG: Revision 5.36  2001/11/15 23:52:27  mmiers
 * LOG: Today's testing.
 * LOG:
 * LOG: Revision 5.35  2001/11/13 16:13:44  vnitin
 * LOG: fixed mgmt activate link and deactivate link
 * LOG:
 * LOG: Revision 5.34  2001/11/09 20:19:54  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.33  2001/10/30 00:16:10  mmiers
 * LOG: Today's debugging session.  Looks close.
 * LOG:
 * LOG: Revision 5.32  2001/10/26 23:53:00  mmiers
 * LOG: Bug chasing
 * LOG:
 * LOG: Revision 5.31  2001/10/26 16:52:40  rsonak
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 5.30  2001/10/23 22:56:44  rsonak
 * LOG: MGMT inhibit trigger added
 * LOG:
 * LOG: Revision 5.29  2001/10/22 21:00:18  rsonak
 * LOG: Typo in trigger names for SLM
 * LOG:
 * LOG: Revision 5.28  2001/10/19 21:32:06  mmiers
 * LOG: Add missing timers.
 * LOG:
 * LOG: Revision 5.27  2001/10/18 19:01:40  mmiers
 * LOG: Fallout from the routing changes
 * LOG:
 * LOG: Revision 5.26  2001/10/17 18:21:23  mmiers
 * LOG: Move the link map computation into IntelliSS7
 * LOG:
 * LOG: Revision 5.25  2001/10/16 17:17:30  mmiers
 * LOG: Add correct behavior for SLT
 * LOG:
 * LOG: Revision 5.24  2001/10/06 23:54:18  mmiers
 * LOG: Missed a few things yesterday.  Fix makefile as well.
 * LOG:
 * LOG: Revision 5.23  2001/10/04 21:31:33  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 5.22  2001/10/03 22:16:39  mmiers
 * LOG: Debugging additions.
 * LOG:
 * LOG: Revision 5.21  2001/10/03 19:42:46  mmiers
 * LOG: Timer cleanup.
 * LOG:
 * LOG: Revision 5.20  2001/10/02 22:13:18  mmiers
 * LOG: Fix non-MTP2 link handling.
 * LOG:
 * LOG: Revision 5.19  2001/10/01 19:12:59  mmiers
 * LOG: arg convention.
 * LOG:
 * LOG: Revision 5.18  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.17  2001/09/24 22:50:23  mmiers
 * LOG: Remove bogus SSN from MTP3 P/R/S messages.  This adds fixmes to
 * LOG: SCMG.
 * LOG:
 * LOG: Revision 5.16  2001/09/17 23:43:37  mmiers
 * LOG: Walkthroughs.
 * LOG:
 * LOG: Revision 5.15  2001/09/14 22:05:45  mmiers
 * LOG: Work on SLT, TSRC
 * LOG:
 * LOG: Revision 5.14  2001/09/13 19:48:05  mmiers
 * LOG: TRCC, TFRC, and TCRC.
 * LOG:
 * LOG: Revision 5.13  2001/09/13 15:17:57  rsonak
 * LOG: Added TLAC timer handling
 * LOG:
 * LOG: Revision 5.12  2001/09/12 22:53:59  mmiers
 * LOG: TPRC
 * LOG:
 * LOG: Revision 5.11  2001/09/12 21:06:03  mmiers
 * LOG: Today's installment.
 * LOG:
 * LOG: Revision 5.10  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.9  2001/09/11 20:25:18  mmiers
 * LOG: More updates
 * LOG:
 * LOG: Revision 5.8  2001/09/06 00:39:57  mmiers
 * LOG: Work in the MTP2 codec.
 * LOG:
 * LOG: Revision 5.7  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.6  2001/08/31 19:34:32  mmiers
 * LOG: Add coarse locking.
 * LOG:
 * LOG: Revision 5.5  2001/08/31 14:22:10  mmiers
 * LOG: Brainstorming fixes.
 * LOG:
 * LOG: Revision 5.4  2001/08/27 19:34:54  mmiers
 * LOG: Revert to old args.
 * LOG:
 * LOG: Revision 5.3  2001/08/23 21:03:38  mmiers
 * LOG: Today's installment.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:26  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.8  2001/08/08 00:55:03  mmiers
 * LOG: Add timer handling.
 * LOG:
 * LOG: Revision 4.7  2001/08/07 22:01:51  mmiers
 * LOG: Add MTP3 API, some timers.
 * LOG:
 * LOG: Revision 4.6  2001/08/07 20:29:05  mmiers
 * LOG: Adjust MTP2 codes.
 * LOG:
 * LOG: Revision 4.5  2001/08/07 20:19:10  mmiers
 * LOG: Convert to byte 1 of the sif being the MTP3 message type.
 * LOG: This ends up working better, as SNMM, SLTM and MTP3 all
 * LOG: assume this.
 * LOG:
 * LOG: Revision 4.4  2001/08/07 20:01:41  mmiers
 * LOG: First pass at message handling.
 * LOG:
 * LOG: Revision 4.3  2001/08/07 19:20:56  mmiers
 * LOG: Add thread bodies.  Needs thinking on.
 * LOG:
 * LOG: Revision 4.2  2001/08/07 19:11:44  mmiers
 * LOG: Add MTP3 threads.  Also a little cleanup.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:02  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.6  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.5  2000/10/05 23:04:31  mmiers
 * LOG: Go back to the old way for now.
 * LOG:
 * LOG: Revision 3.4  2000/09/25 20:09:46  mmiers
 * LOG: Finish off the route conversion code.
 * LOG:
 * LOG: Revision 3.3  2000/09/25 18:31:47  mmiers
 * LOG: Set up for the new routing table.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:22  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/03/29 18:27:48  mmiers
 * LOG:
 * LOG:
 * LOG: Don't trace for non-errors before trace settings have been established.
 * LOG:
 * LOG: Revision 2.3  2000/02/12 00:41:15  mmiers
 * LOG:
 * LOG: Convert vendor to new CORE code.
 * LOG:
 * LOG: Revision 2.2  1999/12/18 00:21:06  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 23:45:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert the callback object.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:22  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.6  1999/10/25 20:24:47  mmiers
 * LOG:
 * LOG:
 * LOG: Corrections for the new transport class.
 * LOG:
 * LOG: Revision 1.5  1999/10/05 23:50:55  rsonak
 * LOG:
 * LOG: For the callback functions, removed the check for no-default-route.
 * LOG:
 * LOG: Revision 1.4  1999/08/26 23:44:52  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.3  1999/08/11 23:08:43  mmiers
 * LOG:
 * LOG:
 * LOG: Trace tweak again.
 * LOG:
 * LOG: Revision 1.2  1999/08/11 19:04:42  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for new trace structures.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:40  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.11  1999/03/17 15:09:23  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.10  1998/11/12 00:09:37  mmiers
 * LOG: Debug SSP/SSA.
 * LOG:
 * LOG: Revision 1.9  1998/11/11 00:45:28  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.8  1998/10/15 01:19:10  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.7  1998/09/30 02:40:59  mmiers
 * LOG: Compromise on what we can do with SCCP.
 * LOG:
 * LOG: Revision 1.6  1998/09/29 21:39:09  mmiers
 * LOG: Revert to previous version.  This needs more thought.
 * LOG:
 * LOG: Revision 1.4  1998/09/29 17:33:04  mmiers
 * LOG: Working on MTP3/SCCP integration.
 * LOG:
 * LOG: Revision 1.3  1998/09/29 01:24:57  mmiers
 * LOG: Implement needed MTP3 functionality.
 * LOG:
 * LOG: Revision 1.2  1998/09/28 17:40:45  mmiers
 * LOG: Add Init, Term methods.
 * LOG:
 * LOG: Revision 1.1  1998/09/28 17:37:51  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.6  1998/09/27 00:53:11  mmiers
 * LOG: Start cleaning up connectionless.
 * LOG:
 * LOG: Revision 1.5  1998/09/27 00:04:18  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:30  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/24 19:24:38  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/09/24 17:31:51  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 16:33:11  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_tq_trans.h>
#include <its_assertion.h>
#include <its_timers.h>
#include <its_dsm.h>
#include <its_route_rwlock.h>
#include <its_redundancy.h>

#ident "$Id: ansi-mtp3.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/mtp3.h>

#include "mtp3_intern.h"
/*NODECARDSTATE set to default state as backup(74)*/
int NODECARDSTATE = 74;
int LeaveTmrSerial = 0;
#define MTP3_ALARM_FILE_NAME "ansi-mtp3alarms.out"
extern ITS_UINT PEER_MTP3_NODE_STATUS;
extern ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];

/*
 * local data
 */
static ITS_MUTEX        mtp3Gate;

static ITS_USHORT       userParts[MTP3_MAX_USER_PARTS] = { ITS_NO_SRC };

static ITS_BOOLEAN      started = ITS_FALSE;
static ITS_BOOLEAN      stopped = ITS_FALSE;

static int numThreads = 1;

static ITS_THREAD* mtp3Thread = NULL;

static TRACE_OutputMethod *mtp3AlarmsOutput = NULL;

static TRACE_OutputInitializer fileCritTrace =
{
    MTP3_FILE_STRING,
    ITS_TRUE,
    MTP3_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    MTP3_FILE_STRING,
    ITS_TRUE,
    MTP3_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    MTP3_FILE_STRING,
    ITS_TRUE,
    MTP3_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    MTP3_FILE_STRING,
    ITS_TRUE,
    MTP3_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    MTP3_FILE_STRING,
    ITS_TRUE,
    MTP3_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    MTP3_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    MTP3_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer MTP3_TraceMap[] =
{
    {MTP3_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace,  &syslogTrace } },
    {MTP3_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace,   &syslogTrace } },
    {MTP3_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace,  &syslogTrace } },
    {MTP3_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {MTP3_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

static ITS_CHAR* MTP3_ANSI_Timers[] =
{
    MTP3_T1_STRING,
    MTP3_T2_STRING,
    MTP3_T3_STRING,
    MTP3_T4_STRING,
    MTP3_T5_STRING,
    MTP3_T6_STRING,
    MTP3_T7_STRING,
    MTP3_T8_STRING,
    MTP3_T9_STRING,
    MTP3_T10_STRING,
    MTP3_T11_STRING,
    MTP3_T12_STRING,
    MTP3_T13_STRING,
    MTP3_T14_STRING,
    MTP3_T15_STRING,
    MTP3_T16_STRING,
    MTP3_T17_STRING,
    MTP3_T18_STRING,
    MTP3_T19_STRING,
    MTP3_T20_STRING,
    MTP3_T21_STRING,
    MTP3_T22_STRING,
    MTP3_T23_STRING,
    MTP3_T24_STRING,
    MTP3_T25_STRING,
    MTP3_T26_STRING,
    MTP3_T27_STRING,
    MTP3_T28_STRING,
    MTP3_T29_STRING,
    MTP3_T30_STRING,
    MTP3_T31_STRING,
    MTP3_T32_STRING,
    MTP3_T33_STRING,
    MTP3_T34_STRING,
    MTP3_SLT_T1_STRING,
    MTP3_SLT_T2_STRING,
    NULL
};

#if 0
static ITS_CHAR *mtp3GPegStr[] =
{
     "PEG_MTP3_MSG_PAUSE",
     "PEG_MTP3_MSG_RESUME",
     "PEG_MTP3_MSG_STATUS",
     "PEG_MTP3_INITIALIZE",
     "PEG_MTP3_TERMINATE",
     "PEG_MTP3_MSG_RECEIVED_INERROR",
     "PEG_MTP3_CHANGEOVER",
     "PEG_MTP3_CHANGEBACK",
     "PEG_MTP3_SL_UNAVAILABLE",
     "PEG_MTP3_LINK_INHIBIT",
     "PEG_MTP3_LINK_UNINHIBIT",
     "PEG_MTP3_LINK_FORCE_UNINHIBIT",
     "PEG_MTP3_CONGESTION",
     "PEG_MTP3_SLS_UNAVAILABLE",
     "PEG_MTP3_TFC_RECEIVED",
     "PEG_MTP3_TFA_RECEIVED",
     "PEG_MTP3_ROUTESET_UNAVAILABLE",
     "PEG_MTP3_ADJECENT_SP_UNACCESIBLE",
     "PEG_MTP3_USERPART_ENABLE",
     "PEG_MTP3_USERPART_DISABLE",
     "PEG_MTP3_T1_EXPIRED",
     "PEG_MTP3_T2_EXPIRED",
     "PEG_MTP3_T3_EXPIRED",
     "PEG_MTP3_T4_EXPIRED",
     "PEG_MTP3_T5_EXPIRED",
     "PEG_MTP3_T6_EXPIRED",
     "PEG_MTP3_T7_EXPIRED",
     "PEG_MTP3_T8_EXPIRED",
     "PEG_MTP3_T9_EXPIRED",
     "PEG_MTP3_T10_EXPIRED",
     "PEG_MTP3_T11_EXPIRED",
     "PEG_MTP3_T12_EXPIRED",
     "PEG_MTP3_T13_EXPIRED",
     "PEG_MTP3_T14_EXPIRED",
     "PEG_MTP3_T15_EXPIRED",
     "PEG_MTP3_T16_EXPIRED",
     "PEG_MTP3_T17_EXPIRED",
     "PEG_MTP3_T18_EXPIRED",
     "PEG_MTP3_T19_EXPIRED",
     "PEG_MTP3_T20_EXPIRED",
     "PEG_MTP3_T21_EXPIRED",
     "PEG_MTP3_T22_EXPIRED",
     "PEG_MTP3_T23_EXPIRED",
     "PEG_MTP3_T24_EXPIRED",
     "PEG_MTP3_T25_EXPIRED",
     "PEG_MTP3_T26_EXPIRED",
     "PEG_MTP3_T27_EXPIRED",
     "PEG_MTP3_T28_EXPIRED",
     "PEG_MTP3_T29_EXPIRED",
     "PEG_MTP3_T30_EXPIRED",
     "PEG_MTP3_T31_EXPIRED",
     "PEG_MTP3_T32_EXPIRED",
     "PEG_MTP3_T33_EXPIRED",
     "PEG_MTP3_T34_EXPIRED",
      NULL
};

static ITS_CHAR *mtp3LPegStr[] =
{
      "PEG_MTP3_LINK_MSU_TX",
      "PEG_MTP3_LINK_MSU_RX",
      "PEG_MTP3_LINK_OCTETS_TX",
      "PEG_MTP3_LINK_OCTETS_RX",
      "PEG_MTP3_LINK_COO_TX",
      "PEG_MTP3_LINK_COO_RX",
      "PEG_MTP3_LINK_COA_TX",
      "PEG_MTP3_LINK_COA_RX" ,
      "PEG_MTP3_LINK_ECO_TX",
      "PEG_MTP3_LINK_ECO_RX",
      "PEG_MTP3_LINK_ECA_TX",
      "PEG_MTP3_LINK_ECA_RX",
      "PEG_MTP3_LINK_CBD_TX",
      "PEG_MTP3_LINK_CBD_RX",
      "PEG_MTP3_LINK_CBA_TX",
      "PEG_MTP3_LINK_CBA_RX",
      "PEG_MTP3_LINK_LIN_TX",
      "PEG_MTP3_LINK_LIN_RX",
      "PEG_MTP3_LINK_LIA_TX",
      "PEG_MTP3_LINK_LIA_RX",
      "PEG_MTP3_LINK_LUN_TX",
      "PEG_MTP3_LINK_LUN_RX",
      "PEG_MTP3_LINK_LUA_TX",
      "PEG_MTP3_LINK_LUA_RX",
      "PEG_MTP3_LINK_LID_TX",
      "PEG_MTP3_LINK_LID_RX",
      "PEG_MTP3_LINK_LFU_TX",
      "PEG_MTP3_LINK_LFU_RX",
      "PEG_MTP3_LINK_LLI_TX",
      "PEG_MTP3_LINK_LLI_RX",
      "PEG_MTP3_LINK_LRI_TX",
      "PEG_MTP3_LINK_LRI_RX",
      "PEG_MTP3_LINK_DLC_TX",
      "PEG_MTP3_LINK_DLC_RX",
      "PEG_MTP3_LINK_CSS_TX",
      "PEG_MTP3_LINK_CSS_RX",
      "PEG_MTP3_LINK_CNS_TX",
      "PEG_MTP3_LINK_CNS_RX",
      "PEG_MTP3_LINK_CNP_TX",
      "PEG_MTP3_LINK_CNP_RX",
      "PEG_MTP3_LINK_UPU_TX",
      "PEG_MTP3_LINK_UPU_RX",
      "PEG_MTP3_LINK_SLTM_TX",
      "PEG_MTP3_LINK_SLTM_RX",
      "PEG_MTP3_LINK_SLTA_TX",
      "PEG_MTP3_LINK_SLTA_RX",
       NULL
};
#endif

/* Redunancy class feature*/
ITS_Class ITS_RedundancyClass = NULL;

TRACE_Data* MTP3_ANSI_TraceData = NULL;

static ITS_UINT pegs[PEG_MTP3_NUM_PEGS_ANSI];
static PEGS_DECL_SUBSYS(ANSI_MTP3, pegs);
PEG_Manager *ANSI_MTP3_Pegs = &ANSI_MTP3_PEGS;

TQUEUETRAN_Manager* __MTP3_ANSI_RcvQueue = NULL;

THREAD_RET_TYPE     ANSI_MTP3Thread(void *arg);

int  __ansi_t1 = 800;
int  __ansi_t2 = 1400;
int  __ansi_t3 = 800;
int  __ansi_t4 = 800;
int  __ansi_t5 = 800;
int  __ansi_t6 = 800;
int  __ansi_t7 = 1000;
int  __ansi_t8 = 1000;
int  __ansi_t9 = 0;
int  __ansi_t10 = 30000;
int  __ansi_t11 = 30000;
int  __ansi_t12 = 800;
int  __ansi_t13 = 800;
int  __ansi_t14 = 2000;
int  __ansi_t15 = 2000;
int  __ansi_t16 = 1400;
int  __ansi_t17 = 800;
int  __ansi_t18 = 0;
int  __ansi_t19 = 480000;
int  __ansi_t20 = 90000;
int  __ansi_t21 = 90000;
int  __ansi_t22 = 30000;
int  __ansi_t23 = 30000;
int  __ansi_t24 = 30000;
int  __ansi_t25 = 30000;
int  __ansi_t26 = 12000;
int  __ansi_t27 = 2000;
int  __ansi_t28 = 3000;
int  __ansi_t29 = 60000;
int  __ansi_t30 = 30000;
int  __ansi_t31 = 10000;
int  __ansi_t32 = 5000;
int  __ansi_t33 = 60000;
int  __ansi_t34 = 5000;
int  __ansi_slt_t1 = 4000;
int  __ansi_slt_t2 = 30000;
int __ansi_leaveTmr = 20000;
/*
 * behavior control
 */
ITS_BOOLEAN MTP3_ANSI_HandleSpareNIC = ITS_FALSE;
ITS_BOOLEAN MTP3_ANSI_AutomaticTerminalAllocation = ITS_FALSE;
ITS_BOOLEAN MTP3_ANSI_AutomaticDataLinkAllocation = ITS_FALSE;

/* FIXME: to be removed: replaced by behaviours */
/*static ITS_BOOLEAN  stpFunction = ITS_FALSE;*/

/*static ITS_BOOLEAN behaviors[MTP3_NUM_BEHAVIORS];*/
BEHAVIORS_DECL_SUBSYS(ANSI_MTP3, NULL);

/*static ITS_TIME timers[MTP3_NUM_TIMERS];*/
TIMERS_DECL_SUBSYS(ANSI_MTP3, NULL);



/*
 * management class record
 */
static MTP3_MgmtClassRec MTP3_MgmtClassRec_ANSI =
{
    /* core part */
    {
        NULL,                           /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        "ANSI MTP3Mgmt",                /* class name */
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
        &ANSI_MTP3_PEGS,
        &ANSI_MTP3_Behaviors,
        &ANSI_MTP3_Timers ,
        ANSI_MTP3_Alarms,

        MTP3_GetGeneralCfg_ANSI,
        MTP3_SetGeneralCfg_ANSI,
        MTP3_GetLinksetEntry_ANSI,
        MTP3_GetAllLinksetEntries_ANSI,
        MTP3_SetLinksetEntry_ANSI,
        MTP3_RemLinksetEntry_ANSI,
        MTP3_GetLinksetStatus_ANSI,
        MTP3_GetLinkInfo_ANSI,
        MTP3_GetAllLinkEntries_ANSI,
        MTP3_SetLinkEntry_ANSI,
        MTP3_RemLinkEntry_ANSI,
        MTP3_GetLinkStatus_ANSI,
        MTP3_GetRouteEntry_ANSI,
        MTP3_GetAllRouteEntries_ANSI,
        MTP3_SetRouteEntry_ANSI,
        MTP3_RemRouteEntry_ANSI,
        MTP3_GetRouteStatus_ANSI,
        MTP3_GetAllDestinationEntries_ANSI,
        MTP3_SetDestinationEntry_ANSI,
        MTP3_RemDestinationEntry_ANSI,
        MTP3_GetDestinationStatus_ANSI,
        MTP3_GetGeneralStats_ANSI,
        MTP3_GetLinksetStats_ANSI,
        MTP3_GetLinkStats_ANSI,
        MTP3_GetRouteStats_ANSI,
        MTP3_GetDestinationStats_ANSI
    }
};

ITSSS7DLLAPI ITS_Class MTP3_MgmtClass_ANSI =
    (ITS_Class)&MTP3_MgmtClassRec_ANSI;


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
STPFunction_ANSI()
{
    return BEHAVIORS_GetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_stpFunction); 
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
STPFunctionSet_ANSI(ITS_BOOLEAN isStp)
{

    BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_stpFunction,
                           isStp);

    BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_ANSI_MTP3_BEHAVIORS);

    return ITS_SUCCESS;
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
MTP3_EnableUserPart_ANSI(ITS_OCTET up, ITS_USHORT id)
{
    MTP3_DEBUG(("MTP3_EnableUserPart_ANSI: up: %02x\n", up));

    if (MUTEX_AcquireMutex(&mtp3Gate) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_EnableUserPart_ANSI: Couldn't acquire mutex.\n"));

        return (ITS_EBADMUTEX);
    }

    if (up > MTP3_MAX_USER_PARTS)
    {
        MTP3_ERROR(("MTP3_EnableUserPart_ANSI: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&mtp3Gate);

        return (ITS_EINVALIDARGS);
    }

    userParts[up] = id;

    MTP3_DEBUG(("MTP3_EnableUserPart_ANSI: up %02x enabled\n", up));

    PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_USERPART_ENABLE);

    return MUTEX_ReleaseMutex(&mtp3Gate);
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
MTP3_DisableUserPart_ANSI(ITS_OCTET up)
{
    MTP3_DEBUG(("MTP3_DisableUserPart_ANSI: up: %02x\n", up));

    if (MUTEX_AcquireMutex(&mtp3Gate) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_DisableUserPart_ANSI: Couldn't acquire mutex.\n"));

        return (ITS_EBADMUTEX);
    }

    if (up > MTP3_MAX_USER_PARTS)
    {
        MTP3_ERROR(("MTP3_DisableUserPart_ANSI: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&mtp3Gate);

        return (ITS_EINVALIDARGS);
    }

    userParts[up] = ITS_NO_SRC;

    MTP3_DEBUG(("MTP3_DisableUserPart_ANSI: up %02x disabled\n", up));

    PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_USERPART_DISABLE);

    return MUTEX_ReleaseMutex(&mtp3Gate);
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
ITSSS7DLLAPI ITS_USHORT
MTP3_UserPartOwner_ANSI(ITS_OCTET up)
{
    volatile ITS_USHORT id;

    MTP3_DEBUG(("MTP3_UserPartOwner_ANSI: up: %02x\n", up));

    if (MUTEX_AcquireMutex(&mtp3Gate) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_UserPartOwner_ANSI: Couldn't acquire mutex.\n"));

        return (ITS_INVALID_SRC);
    }

    if (up > MTP3_MAX_USER_PARTS)
    {
        MTP3_ERROR(("MTP3_UserPartOwner_ANSI: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&mtp3Gate);

        return (ITS_INVALID_SRC);
    }

    id = userParts[up];

    MTP3_DEBUG(("MTP3_UserPartOwner_ANSI: up %02x is %04x\n", up, id));

    MUTEX_ReleaseMutex(&mtp3Gate);

    return (id);
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
ITSSS7DLLAPI MTP3GeneralCfg*
MTP3_GetGeneralCfg_ANSI()
{
    MTP3GeneralCfg *ret;

    ret = calloc(1, sizeof(MTP3GeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(MTP3_ANSI_TraceData,
                                    MTP3_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_ANSI_TraceData,
                                    MTP3_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_ANSI_TraceData,
                                    MTP3_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_ANSI_TraceData,
                                    MTP3_TRACE_EVENT) &&
                    (TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_EVENT,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_EVENT,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_EVENT,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_ANSI_TraceData,
                                    MTP3_TRACE_ABORT) &&
                    (TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_ABORT,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_ABORT,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_ANSI_TraceData,
                                      MTP3_TRACE_ABORT,
                                      2)));
    ret->alarmLevel = (MGMT_AlarmLevel)MTP3_AlarmLevel_ANSI;

    return (ret);
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
MTP3_SetGeneralCfg_ANSI(MTP3GeneralCfg *data)
{
    MTP3_AlarmLevel_ANSI = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      MTP3_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      MTP3_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      MTP3_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      MTP3_DEBUG_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_EVENT_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      MTP3_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       MTP3_EVENT_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
#if 0
/* Fix for Bug 490 */
            TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                      data->traceType, ITS_FALSE);
#endif
        }
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
ITSSS7DLLAPI MTP3LinksetInfo*
MTP3_GetLinksetEntry_ANSI(ITS_UINT linksetNumber)
{
    return (NULL);
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
ITSSS7DLLAPI void
MTP3_GetAllLinksetEntries_ANSI(ITS_UINT* numEntries,
                               MTP3LinksetInfo** entries)
{
    *entries = NULL;
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
MTP3_SetLinksetEntry_ANSI(MTP3LinksetInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_RemLinksetEntry_ANSI(MTP3LinksetInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_GetLinksetStatus_ANSI(ITS_UINT linksetNumber,
                           MTP3LinksetStatus* status)
{
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
ITSSS7DLLAPI MTP3LinkInfo*
MTP3_GetLinkInfo_ANSI(ITS_UINT ls, ITS_UINT lnk)
{
    return (NULL);
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
ITSSS7DLLAPI void
MTP3_GetAllLinkEntries_ANSI(ITS_UINT* numEntries,
                            MTP3LinkInfo** entries)
{
    *entries = NULL;
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
MTP3_SetLinkEntry_ANSI(MTP3LinkInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_RemLinkEntry_ANSI(MTP3LinkInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_GetLinkStatus_ANSI(ITS_UINT ls, ITS_UINT lnk,
                        MTP3LinkStatus* status)
{
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
ITSSS7DLLAPI MTP3RouteInfo*
MTP3_GetRouteEntry_ANSI(ITS_UINT dpc, ITS_OCTET ni,
                        ITS_UINT ls)
{
    return (NULL);
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
ITSSS7DLLAPI void
MTP3_GetAllRouteEntries_ANSI(ITS_UINT* numEntries,
                             MTP3RouteInfo** entries)
{
    *entries = NULL;
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
MTP3_SetRouteEntry_ANSI(MTP3RouteInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_RemRouteEntry_ANSI(MTP3RouteInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_GetRouteStatus_ANSI(ITS_UINT dpc, ITS_OCTET ni,
                         ITS_UINT ls, 
                         MTP3RouteStatus* status)
{
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
ITSSS7DLLAPI void
MTP3_GetAllDestinationEntries_ANSI(ITS_UINT* numEntries, 
                                   MTP3DestinationInfo** entries)
{
    *entries = NULL;
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
MTP3_SetDestinationEntry_ANSI(MTP3DestinationInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_RemDestinationEntry_ANSI(MTP3DestinationInfo* data)
{
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
ITSSS7DLLAPI int
MTP3_GetDestinationStatus_ANSI(ITS_UINT dpc, ITS_OCTET ni, 
                               MTP3DestinationStatus* status)
{
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
ITSSS7DLLAPI int
MTP3_GetGeneralStats_ANSI(ITS_UINT **pegs, ITS_UINT *numPegs)
{
    *pegs = NULL;
    *numPegs = 0;

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
ITSSS7DLLAPI int
MTP3_GetLinksetStats_ANSI(ITS_UINT linksetNUmber, 
                          ITS_UINT **pegs,
                          ITS_UINT *numPegs)
{
    *pegs = NULL;
    *numPegs = 0;

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
ITSSS7DLLAPI int
MTP3_GetLinkStats_ANSI(ITS_UINT linksetNUmber,
                       ITS_UINT lnkNumber,
                       ITS_UINT **pegs,
                       ITS_UINT *numPegs)
{
    *pegs = NULL;
    *numPegs = 0;

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
ITSSS7DLLAPI int
MTP3_GetRouteStats_ANSI(ITS_UINT dpc, ITS_OCTET ni,
                        ITS_UINT linksetNumber,
                        ITS_UINT **pegs,
                        ITS_UINT *numPegs)
{
    *pegs = NULL;
    *numPegs = 0;

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
ITSSS7DLLAPI int
MTP3_GetDestinationStats_ANSI(ITS_UINT dpc, ITS_OCTET ni, 
                              ITS_UINT **pegs,
                              ITS_UINT *numPegs)
{
    *pegs = NULL;
    *numPegs = 0;

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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  Bug Id 860              Resolution for Multiple Pause/
 *                                               Resume bug
 *
 ****************************************************************************/
static void
MTP3_Pause(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    MTP3_PAUSE_RESUME pause;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Pause_ANSI:\n"));

   /* PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_PAUSE);*/

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_ANSI: link lock failed\n"));

        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    /*
     * NOTE: We can only get here if we're NOT MTP2.
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(base).linkInfo;
             link != NULL; link = link->next)
        {
            ITS_BOOLEAN wasUp = ITS_FALSE, isUp = ITS_FALSE;

            /*
             * deactivate this link
             */
            LINKSET_RemoveActiveLink(link->linkSet, link->linkCode);

            /* get old linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &wasUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));

            }

            LINK_SetLinkState(link, ITS_FALSE);

            /* get new linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &isUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));

            }

            /*
             * if link set was previously up, walk routes looking for dests to pause.
             */
            if (wasUp && !isUp)
            {
                DSMQUEUE_Entry *tmp;
                ITS_UINT count;

                ITS_UINT* affectedPcList = NULL;
                ITS_UINT numAffectedPcs = 0;

                affectedPcList = (ITS_UINT*)calloc((numAffectedPcs + 1), sizeof(ITS_UINT));

                for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                     tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                     count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
                {
                    ROUTE_Info *rinfo;
                    ITS_BOOLEAN allDown = ITS_TRUE;
                    ITS_UINT index = 0;

                    /* select one of concerned destinations */
                    memcpy(&rinfo, tmp->data, sizeof(rinfo));

                    if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                    {
                        continue;
                    }

                    for (index = 0 ; index < numAffectedPcs; index++)
                    {
                        if (rinfo->basic.dpc == affectedPcList[index])
                        {
                            allDown = ITS_FALSE;
                            break;
                        }
                    }

                    if (allDown)
                    {
                        if (rinfo->dest)
                        {
                            for (index = 0; index < rinfo->dest->numEntries; index++)
                            {
                                if (rinfo->dest->entries[index]->linkSet->linkSet != link->linkSet->linkSet &&
                                    rinfo->dest->entries[index]->linkSet->isUp)
                                {
                                    allDown = ITS_FALSE;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            MTP3_WARNING(("Configured route not found\n"));
                            continue;
                        }
                    }

                    /* determine if this was the last up route */
                    if (allDown)
                    {
                        affectedPcList = (ITS_UINT*)realloc(affectedPcList,
                                                   (numAffectedPcs + 1) * sizeof(ITS_UINT));
                        affectedPcList[numAffectedPcs++] = rinfo->basic.dpc;

                        MTP3_DEBUG(("MTP3_Pause_ANSI: setting state PC: %08x\n",
                                    rinfo->basic.dpc));

                        MTP3_PC_SET_VALUE(pause.affected, rinfo->basic.dpc);

                        MTP3_Alarm_ANSI(2401, __FILE__, __LINE__,
                                        "affected point code %x", rinfo->basic.dpc);

                        mtp3.sio = link->linkSet->ni;
                        MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                        MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                        MTP3_RL_SET_SLS(mtp3.label, 0);

                        event.src = ITS_MTP3_ANSI_SRC;
                        MTP3_Encode(&event, MTP3_MSG_PAUSE, &mtp3,
                                    (ITS_OCTET *)&pause, sizeof(MTP3_PAUSE_RESUME));

                        CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                                  (ITS_POINTER)base,
                                                  (ITS_POINTER)&event);

                        ITS_EVENT_TERM(&event);
                    }
                }
                free(affectedPcList);
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
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
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  Bug Id 860              Resolution for Multiple Pause/
 *                                               Resume bug
 *
 ****************************************************************************/
static void
MTP3_Resume(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    MTP3_PAUSE_RESUME resume;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Resume_ANSI:\n"));

    /*PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_MSG_RESUME);*/

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_ANSI: link lock failed\n"));

        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    /*
     * NOTE: We can only get here if we're NOT MTP2.
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(base).linkInfo;
             link != NULL; link = link->next)
        {
            ITS_BOOLEAN wasUp = ITS_FALSE, isUp = ITS_FALSE;

            /*
             * activate this link
             */
            LINKSET_AddActiveLink(link->linkSet, link->linkCode);

            /* get old linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &wasUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));
            }

            LINK_SetLinkState(link, ITS_TRUE);

            /* get new linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &isUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));

            }

            /*
             * if link set was previously down, walk routes looking for dests to resume.
             */
            if (!wasUp && isUp)
            {
                DSMQUEUE_Entry *tmp;
                ITS_UINT count;

                ITS_UINT* affectedPcList = NULL;
                ITS_UINT numAffectedPcs = 0;

                affectedPcList = (ITS_UINT*)calloc((numAffectedPcs + 1), sizeof(ITS_UINT));

                for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                     tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                     count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
                {
                    ROUTE_Info *rinfo;
                    ITS_BOOLEAN firstUp = ITS_TRUE;
                    ITS_UINT index = 0;  

                    /* select one of concerned destinations */
                    memcpy(&rinfo, tmp->data, sizeof(rinfo));

                    if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                    {
                        continue;
                    }

                    for (index = 0 ; index < numAffectedPcs; index++)
                    {
                        if (rinfo->basic.dpc == affectedPcList[index])
                        {
                            firstUp = ITS_FALSE;
                            break;
                        }
                    }

                    if (firstUp)
                    {
                        if (rinfo->dest)
                        {
                            for (index = 0; index < rinfo->dest->numEntries; index++)
                            {
                                if (rinfo->dest->entries[index]->linkSet->linkSet != link->linkSet->linkSet &&
                                    rinfo->dest->entries[index]->linkSet->isUp)
                                {
                                    firstUp = ITS_FALSE;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            MTP3_WARNING(("Configured route not found\n"));
                            continue;
                        }
                    }

                    /* determine if this is a newly up route */
                    if (firstUp)
                    {
                        affectedPcList = (ITS_UINT*)realloc(affectedPcList,
                                                   (numAffectedPcs + 1) * sizeof(ITS_UINT));
                        affectedPcList[numAffectedPcs++] = rinfo->basic.dpc;

                        MTP3_DEBUG(("MTP3_Resume_ANSI: setting state PC: %08x\n",
                                    rinfo->basic.dpc));

                        MTP3_PC_SET_VALUE(resume.affected, rinfo->basic.dpc);

                        MTP3_Alarm_ANSI(2402, __FILE__, __LINE__,
                                        "affected point code %x", rinfo->basic.dpc);

                        mtp3.sio = link->linkSet->ni;
                        MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                        MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                        MTP3_RL_SET_SLS(mtp3.label, 0);

                        event.src = ITS_MTP3_ANSI_SRC;
                        MTP3_Encode(&event, MTP3_MSG_RESUME, &mtp3,
                                    (ITS_OCTET *)&resume, sizeof(MTP3_PAUSE_RESUME));

                        CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                                  (ITS_POINTER)base,
                                                  (ITS_POINTER)&event);

                        ITS_EVENT_TERM(&event);
                    }
                }
                free(affectedPcList);
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
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
MTP3_Status(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    ITS_OCTET congLevel = 0;
    MTP3_STATUS status;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Status_ANSI:\n"));

    /*PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_STATUS);*/

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_ANSI: link lock failed\n"));

        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    /*
     * NOTE: We can only get here if we're NOT MTP2.
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(base).linkInfo;
             link != NULL; link = link->next)
        {
            DSMQUEUE_Entry *tmp;
            ITS_UINT count;

            LINK_SetLinkCongestion(link, congLevel);

            /*
             * If not MTP2 link, if congestion deliver MTP3-STATUS.
             */
            for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                 tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
            {
                ROUTE_Info *rinfo;

                /* select one of concerned destinations */
                memcpy(&rinfo, tmp->data, sizeof(rinfo));

                if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                {
                    continue;
                }

                /*
                 * if this route is congested, send a status message
                 * for congestion, always do this.  There's not a lot the
                 * user can do anyway.
                 */
                if (ITS_TRUE)
                {
                    MTP3_DEBUG(("MTP3_Status_ANSI: get congestion PC: %08x SSN: %02xn\n",
                                rinfo->basic.dpc, rinfo->basic.criteria.ssn));

                    MTP3_PC_SET_VALUE(status.affected, rinfo->basic.dpc);
                    status.congLevel = congLevel;

                    mtp3.sio = 0;
                    MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                    MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                    MTP3_RL_SET_SLS(mtp3.label, 0);

                    event.src = ITS_MTP3_ANSI_SRC;
                    MTP3_Encode(&event, MTP3_MSG_STATUS, &mtp3,
                                (ITS_OCTET *)&status, sizeof(MTP3_STATUS));

                    CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                              (ITS_POINTER)base,
                                              (ITS_POINTER)&event);

                    ITS_EVENT_TERM(&event);
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
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
MTP3_Register(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* tc = (TRANSPORT_Control *)object;

    /*
     * avoid MTP2 links by not registering callbacks here
     */
    if (TRANSPORT_MASK(tc) & ITS_SS7_MASK_ANSI &&
        !(TRANSPORT_MASK(tc) & ITS_FLAG_MTP2))
    {
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).pauseCallbacks,
                             MTP3_Pause, NULL);
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).resumeCallbacks,
                             MTP3_Resume, NULL);
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).statusCallbacks,
                             MTP3_Status, NULL);
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
MTP3_Deregister(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* tc = (TRANSPORT_Control *)object;

    /*
     * avoid MTP2 links by not registering callbacks here
     */
    if (TRANSPORT_MASK(tc) & ITS_SS7_MASK_ANSI &&
        !(TRANSPORT_MASK(tc) & ITS_FLAG_MTP2))
    {
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).pauseCallbacks,
                             MTP3_Pause, NULL);
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).resumeCallbacks,
                             MTP3_Resume, NULL);
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).statusCallbacks,
                             MTP3_Status, NULL);
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
OutputAlarmToFile(char *data)
{
    char buf[ITS_PATH_MAX];

    if (mtp3AlarmsOutput == NULL)
    {
        mtp3AlarmsOutput = (TRACE_OutputMethod *) 
                              malloc(sizeof(TRACE_OutputMethod));
        memset(mtp3AlarmsOutput, 0, sizeof(TRACE_OutputMethod));
    }
#if !defined(NO_FILESYSTEM)

    if (!TRACE_OUTPUT_INIT_DONE(mtp3AlarmsOutput) ||
            TRACE_OUTPUT_DATA(mtp3AlarmsOutput) == NULL)
    {
        TRACE_OUTPUT_OUT_NAME(mtp3AlarmsOutput) = MTP3_ALARM_FILE_NAME;

        if (APPL_GetTraceDir() != NULL)
        {
            sprintf(buf,"%s%s",
               APPL_GetTraceDir(), TRACE_OUTPUT_OUT_NAME(mtp3AlarmsOutput)) ;
        }
        else
        {
            sprintf(buf,"%s%s" ,
               "", TRACE_OUTPUT_OUT_NAME(mtp3AlarmsOutput));
        }

        TRACE_OUTPUT_DATA(mtp3AlarmsOutput) = fopen(buf, "a");

        TRACE_OUTPUT_INIT_DONE(mtp3AlarmsOutput) = ITS_TRUE;
    }

#endif

    if (TRACE_OUTPUT_DATA(mtp3AlarmsOutput))
    {
        fprintf((FILE *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput),"%s", data);
        fflush((FILE *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput));
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
/*static void
CloseAlarmFile(char *data)
{

#if !defined(NO_FILESYSTEM)
    fclose((FILE *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput));
#endif

    TRACE_OUTPUT_DATA(mtp3AlarmsOutput) = NULL;

}
*/

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
MTP3_Alarms_ANSI(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData
)
{
    ALARM_Format    alarm;
    char            alarmDesc[ITS_PATH_MAX << 1];
    ITS_EVENT       *event = (ITS_EVENT *)callData;
    char            *token;
    char            alarmText[ITS_PATH_MAX << 2] ;
    int             index = 0;

    time_t now;                   /* Current time */
    struct tm *now_time;

#if !defined(WIN32) && !defined(TANDEM)
    struct tm tbuf;
#endif

#define MTP3_ALARM_OUTPUT 400

    char alarmOutput[MTP3_ALARM_OUTPUT];

    memset(alarmText, 0, ITS_PATH_MAX << 2);
    memset(alarmDesc, 0, ITS_PATH_MAX << 1);
    memset(&alarm, 0, sizeof(ALARM_Format));

    memcpy(alarmText, event->data, event->len);

    token = strtok(alarmText, "|");

    alarm.id = (ITS_UINT)atoi(token);

    if (alarm.id >= ANSI_MTP3_ALARM_START &&
        alarm.id <= ANSI_MTP3_ALARM_END)
    {

        /*MTP3_ERROR(("MTP3_ALARM: %s \n", alarmText));*/

        while ( token != NULL )
        {
            switch ( index )
            {
            case 0:
                alarm.id = (ITS_UINT)atoi(token);
                index++;
                token = strtok(NULL, "|");
                break;
            case 1:         /* Sussystem string */
                alarm.subsys = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 2:         /* Alarm severity */
                alarm.severity = (ITS_UINT)atoi(token);
                index++;
                token = strtok(NULL, "|");
                break;
            case 3:         /* Alarm object */
                alarm.object = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 4:         /* Alarm description */
                alarm.desc  = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 5:         /* Alarm file name */
                index++;
                token = strtok(NULL, "|");
                break;
            case 6:         /* Alarm function*/
                alarm.func = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 7:         /* Alarm line number */
                index++;
                token = strtok(NULL, "|");
                break;
            case 8:         /* Alarm cariable desc*/
                index++;
            strcpy(alarmDesc, alarm.desc);
            strcat(alarmDesc, "\nText: ");
            strcat(alarmDesc, token);
            alarm.desc = alarmDesc;


                token = strtok(NULL, "|");
                break;
            default:
                token = NULL;
                break;
            }
        }

        now = TIMERS_Time();

        memset(alarmOutput, 0, sizeof(MTP3_ALARM_OUTPUT));

#if defined(WIN32) || defined(TANDEM)
        now_time = localtime(&now);

        strftime(alarmOutput, MTP3_ALARM_OUTPUT, "[%b%d %Y %H:%M:%S] ", 
                 now_time); /* [MMMDD YY, HH:MM:SS\0]  */
#else
        now_time = localtime_r(&now, &tbuf);

        strftime(alarmOutput, MTP3_ALARM_OUTPUT, "[%b%d %Y %H:%M:%S] ", 
                 &tbuf); /* [MMMDD YY, HH:MM:SS\0]  */
#endif

        sprintf(alarmText,"\n%s: %6d %10s \n%-25s %s",
                alarm.subsys,
                alarm.id,
                ALARM_LEVEL_TO_TEXT(alarm.severity),
                alarm.func,
                alarm.desc);


        strcat(alarmOutput, alarmText);

        strcat(alarmOutput,"\n---------------------------------------------\n");

        OutputAlarmToFile(alarmOutput);

    }
}


/*
 * Debugging strings
 */
static char *subSystems[] =
{
    "SMH",       /* Major subsystems */
    "STM",
    "SLM",
    "SRM",
    "SLT",
    "MGMT",
    "USER",

    "L2",        /* lower layer */
    "L4",        /* upper layer */
    "TIMER",     /* timer control */

    "SMH_HMDC",  /* SMH subsystems */
    "SMH_HMDT",
    "SMH_HMRT",
    "SMH_HMCG",

    "STM_TLAC",  /* STM subsystems */
    "STM_TSRC",
    "STM_TRCC",
    "STM_TCOC",
    "STM_TCBC",
    "STM_TFRC",
    "STM_TCRC",
    "STM_TSFC",
    "STM_TPRC",

    "SLM_LLSC",  /* SLM subsystems */
    "SLM_LSAC",
    "SLM_LSLA",
    "SLM_LSLR",
    "SLM_LSLD",
    "SLM_LSTA",
    "SLM_LSDA",

    "SRM_RTPC",  /* SRM subsystems */
    "SRM_RTAC",
    "SRM_RSRT",
    "SRM_RTCC",
    "SRM_RCAT",
    "SRM_RTRC",

    "SLT_SLTC"   /* SLT subsystems */
};

static char *smhTriggers[] =
{
    "L2_L3_MSG",              
    "UPDATE_ROUTING_TABLES",  
    "MSG_FOR_ROUTING",        
    "L4_L3_MSG",              
    "ROUTE_MGMT_MSG",         
    "LINK_MGMT_MSG",          
    "TRAFFIC_MGMT_MSG",       
    "TEST_CONTROL_MSG",       
    "L3_L2_MSG"               
};

static char *stmTriggers[] =
{
    "L2_MSG",
    "LINK_AVAILABLE",             
    "LINK_UNAVAILABLE",           
    "INHIBIT_LINK",               
    "UNINHIBIT_LINK",             
    "UNINHIBITING_LINK",          
    "FORCE_INHIBIT_LINK",         
    "FORCE_UNINHIBIT_LINK",       
    "INHIBIT_ALLOWED",            
    "INHIBIT_DENIED",             
    "LOCAL_INHIBIT_ALLOWED",      
    "LOCAL_INHIBIT_DENIED",       
    "REMOTE_INHIBIT_ALLOWED",     
    "REMOTE_INHIBIT_DENIED",      
    "INHIBIT_POSSIBLE",           
    "INHIBIT_IMPOSSIBLE",         
    "UNINHIBIT_POSSIBLE",         
    "UNINHIBIT_IMPOSSIBLE",       
    "INHIBIT_ACK",                
    "UNINHIBIT_ACK",              
    "ADJACENT_SP_RESTARTING",     
    "ADJACENT_SP_RESTARTED",      
    "CHANGEBACK_TERMINATED",      
    "CHANGEOVER_EXECUTED",        
    "CHANGEOVER_NOT_REQD",        
    "LINK_FAILED",                
    "LINK_IN_SERVICE",            
    "RP_OUTAGE",                  
    "RP_RECOVERD",                
    "RB_CLEARED",                 
    "RTB_CLEARED",                
    "RESTART_BEGIN",              
    "RESTART_END",                
    "LOCAL_INHIBIT_TEST",         
    "REMOTE_INHIBIT_TEST",        
    "LOCAL_UNINHIBIT_TEST",       
    "REMOTE_UNINHIBIT_TEST",      
    "EMERG_CHANGEOVER_ORDER",     
    "CHANGEOVER_ORDER",           
    "T12",                        
    "T13",                        
    "T14",                        
    "T20",                        
    "T21",                        
    "ACCESSIBILITY_REQUEST",      
    "ALTERNATE_ROUTE_REQ",        
    "CHANGEOVER_NOT_REQ",         
    "PROCEDURE_TERMINATED",       
    "ROUTE_AVAILABLE",            
    "LOCAL_INHIBIT_REQUESTED",    
    "REMOTE_INHIBIT_REQUESTED",   
    "LINK_INHIBITED",             
    "CANCEL_LINK_INHIBITED",      
    "UNINHIBIT_REQUEST",          
    "TCP",                        
    "ROUTE_UNAVAILABLE",          
    "TCA",                        
    "ROUTE_RESTRICTED",           
    "TCR",                        
    "DANGER_OF_CONGESTION",       
    "T11",                        
    "LINK_CONGESTION_STATUS",     
    "SENDING_STATUS_PHASE",       
    "SEND_TRW",                   
    "TRAFFIC_RESTART_ALLOWED",    
    "T25",                        
    "T28",                        
    "TRAFFIC_RESTART_WAITING",    
    "SEND_STATUS",                
    "T29",                        
    "T30",                        
    "T32",                        
    "T33",                        
    "T34",                        
    "DEST_CONGESTION_STATUS",     
    "DECR_DEST_CONG_STATUS",      
    "ACCESSIBILITY_DATA",         
    "DEST_INACCESS",              
    "CLUST_INACCESS",             
    "T15",                        
    "ALTERNATE_ROUTE_DATA",       
    "BSNT",                       
    "BSNT_NOT_RETRIEVABLE",       
    "T1",                         
    "CHANGEOVER_ACK",             
    "EMERG_CHANGEOVER_ACK",       
    "RETRIEVED_MSGS",             
    "RETRIEVAL_COMPLETE",         
    "RETRIEVAL_NOT_POSSIBLE",     
    "T2",                         
    "CHANGEBACK_DECL",            
    "CHANGEBACK_ACK",             
    "T3",                         
    "T4",                         
    "T5",                         
    "T6",                         
    "DEST_ACCESS",                
    "CLUST_ACCESS",               
    "UPU",                        
    "RESTART_INDIC",              
    "T26",                        
    "T22",                        
    "T23",                        
    "STATUS_SENT",                
    "T24",                        
    "T27",
    "T31",
    "LOCAL_PROCESSOR_OUTAGE",
    "LOCAL_PROCESSOR_RECOVERD"
};

static char *slmTriggers[] =
{
    "L2_MSG",
    "ACTIVATE_LINK_SET",      
    "RESTART_BEGINS",         
    "DEACTIVATE_LINK_SET",    
    "LINK_ACTIVE",            
    "LINK_INACTIVE",          
    "LINK_FAILED",            
    "ACTIVATE_ANOTHER_LINK",  
    "EMERGENCY",              
    "EMERGENCY_CEASES",       
    "ACTIVATE_LINK",          
    "DATA_LINK",              
    "START_LINK",             
    "T17",                    
    "ACTIVATION_UNSUCCESS",   
    "RESTORATION_UNSUCCESS",  
    "T19",                    
    "NOT_POSSIBLE",           
    "DEACTIVATE_LINK",        
    "RESUME",                 
    "CLEAR_BUFFERS",          
    "LINK_LOADED",            
    "LINK_DELOADED",          
    "CHANGEOVER_ORDER",       
    "CHANGEOVER_ORDER_RECVD", 
    "CLEAR_RTB",              
    "STM_READY",              
    "L2_IN_SERVICE",          
    "L2_RPO",                 
    "L2_OUT_OF_SERVICE",      
    "L2_RPR",                 
    "T32",                    
    "T33",                    
    "T34",                    
    "RB_CLEARED",             
    "RTB_CLEARED",            
    "LP_OUTAGE",
    "LP_RECOVERD",
    "START_ACTIVATION",       
    "RESTART_ACTIVATION",     
    "NO_DATA_LINK",           
    "TERMINAL",               
    "NO_TERMINAL",            
    "START_RESTORATION",      
    "RESTART_RESTORATION",    
    "DETERMINE_TERMINAL",     
    "TERMINAL_IDLE",          
    "TERMINAL_AVAILABLE",     
    "DETERMINE_DATA_LINK",    
    "LINK_AVAILABLE",         
    "CONNECTION_ORDER",       
    "ALTERNATE_ROUTING_DATA", 
    "CONNECTION_SUCCESSFUL",  
    "CONNECTION_UNSUCCESS",   
    "CONNECTION_NOT_POSS",    
    "T7"                      
};

static char *srmTriggers[] =
{
    "L2_MSG",
    "TRANSFER_PROHIBIT",      
    "MSG_FOR_INACCESS_SP",    
    "SEND_TRANSFER_PROHIBIT", 
    "NEW_STP_DEST",           
    "DEST_INACCESS",          
    "CONTROLLED_REROUTE_END", 
    "CONTROLLED_REROUTE",     
    "CLUSTER_INACCESS",       
    "MSG_FOR_INACCESS_CLUST", 
    "SEND_TCP",               
    "NEW_STP_FOR_CLUST",      
    "TCP",                    
    "T8",                     
    "TRANSFER_ALLOW",         
    "DEST_ACCESS",            
    "REM_STP_DEST",           
    "SEND_TRANSFER_ALLOW",    
    "FORCED_REROUTE",         
    "FORCED_REROUTE_END",     
    "CLUSTER_ACCESS",         
    "REM_STP_FOR_CLUST",      
    "SEND_TCA",               
    "TCA",                    
    "START_ROUTE_SET_TEST",   
    "ROUTE_AVAILABLE",        
    "T10",                    
    "ROUTE_SET_TEST",         
    "ACCESSIBILITY_DATA",     
    "TCA_RCVD",               
    "TCP_RCVD",               
    "TCR_RCVD",               
    "CLUSTER_ROUTE_SET_TEST", 
    "RESTART_BEGINS",         
    "RESTART_ENDS",           
    "ADJACENT_RESTARTING",    
    "TRANSFER_CONTROL",       
    "USER_PART_UNAVAIL",      
    "SEND_TRANSFER_CONTROL",  
    "START_CONG_TEST",        
    "CONG_TEST",              
    "STOP_CONG_TEST",         
    "T16",                    
    "TRANSFER_RESTRICT",      
    "TCR",                    
    "SEND_TRANSFER_RESTRICT", 
    "DEST_RESTRICT",          
    "CLUSTER_RESTRICT",       
    "SEND_TCR",               
    "MSG_FOR_RESTRICTED_DEST",
    "MSG_FOR_RESTRICTED_CLUST",
    "T18"
};

static char *sltTriggers[] =
{
    "L2_MSG",                 
    "START_TEST",             
    "T1"                      
};

static char *mgmtTriggers[] =
{
    "NO_ROUTING_DATA",       
    "LINK_TEST_PASSED",      
    "LINK_TEST_FAILED",      
    "LINK_ACTIVATION_FAIL",  
    "INHIBIT_REQ_TIMEOUT",   
    "UNINHIBIT_REQ_TIMEOUT", 
    "UNINHIBIT_LINK",        
    "INHIBIT_DENIED",        
    "LINK_INHIBITED",        
    "LINK_REMOTE_UNINHIBIT", 
    "UNINHIBIT_IMPOSSIBLE",  
    "MESSAGE_FOR_INVALID_DEST",
    "RESTART",
    "INHIBIT_LINK",
    "DEACTIVATE_LINK",
    "DEACTIVATE_LINK_SET",
    "ACTIVATE_LINK",
    "ACTIVATE_LINK_SET",
    "LOCAL_PROCESSOR_OUTAGE",
    "LOCAL_PROCESSOR_RECOVERED"
};

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
MTP3_FuncEntry_ANSI(MTP3_SubSystems subsystem, MTP3_SubSystems src,
                    int trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode,
                    char *file, int line)
{
    char *sub = NULL, *from = NULL;
    char *trig = NULL;
    ITS_USHORT idx;

    ITS_C_ASSERT(subsystem >= 0 &&
                 subsystem <= (sizeof(subSystems) / sizeof (char *)));
    sub = subSystems[subsystem];
    ITS_C_ASSERT(src >= 0 &&
                 src <= (sizeof(subSystems) / sizeof (char *)));
    from = subSystems[src];

    switch (subsystem)
    {
    case MTP3_SMH:       /* Major subsystems */
    case MTP3_SMH_HMDC:  /* SMH subsystems */
    case MTP3_SMH_HMDT:
    case MTP3_SMH_HMRT:
    case MTP3_SMH_HMCG:
        ITS_C_ASSERT(trigger >= 0 &&
                     trigger < (sizeof(smhTriggers) / sizeof(char *)));
        trig = smhTriggers[trigger];
        break;

    case MTP3_STM:
    case MTP3_STM_TLAC:  /* STM subsystems */
    case MTP3_STM_TSRC:
    case MTP3_STM_TRCC:
    case MTP3_STM_TCOC:
    case MTP3_STM_TCBC:
    case MTP3_STM_TFRC:
    case MTP3_STM_TCRC:
    case MTP3_STM_TSFC:
    case MTP3_STM_TPRC:
        ITS_C_ASSERT(trigger >= 0 &&
                     trigger < (sizeof(stmTriggers) / sizeof(char *)));
        trig = stmTriggers[trigger];
        break;

    case MTP3_SLM:
    case MTP3_SLM_LLSC:  /* SLM subsystems */
    case MTP3_SLM_LSAC:
    case MTP3_SLM_LSLA:
    case MTP3_SLM_LSLR:
    case MTP3_SLM_LSLD:
    case MTP3_SLM_LSTA:
    case MTP3_SLM_LSDA:
        ITS_C_ASSERT(trigger >= 0 &&
                     trigger < (sizeof(slmTriggers) / sizeof(char *)));
        trig = slmTriggers[trigger];
        break;

    case MTP3_SRM:
    case MTP3_SRM_RTPC:  /* SRM subsystems */
    case MTP3_SRM_RTAC:
    case MTP3_SRM_RSRT:
    case MTP3_SRM_RTCC:
    case MTP3_SRM_RCAT:
    case MTP3_SRM_RTRC:
        ITS_C_ASSERT(trigger >= 0 &&
                     trigger < (sizeof(srmTriggers) / sizeof(char *)));
        trig = srmTriggers[trigger];
        break;

    case MTP3_SLT:
    case MTP3_SLT_SLTC:   /* SLT subsystems */
        ITS_C_ASSERT(trigger >= 0 &&
                     trigger < (sizeof(sltTriggers) / sizeof(char *)));
        trig = sltTriggers[trigger];
        break;

    case MTP3_MGMT:
        ITS_C_ASSERT(trigger >= 0 &&
                     trigger < (sizeof(mgmtTriggers) / sizeof(char *)));
        trig = mgmtTriggers[trigger];
        break;

    case MTP3_USER:
        trig = "NO_TRIGGER";
        break;

    case MTP3_L2:        /* lower layer */
        trig = "L2 message";
        break;

    case MTP3_L4:        /* upper layer */
        trig = "L4 message";
        break;

    case MTP3_TIMER:     /* timer control */
        trig = "Timer message";
        break;

    default:
        trig = "Unknown";
        break;
    }

    TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
              ("%s", TRACE_Header(MTP3_ANSI_TraceData, file, line)));
    TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
              ("  Sub: %s From: %s Trigger: %s\n",
                sub, from, trig));
    TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
              ("  LinkSet/Code: %d:%d len: %d\n",
               linkSet, linkCode, len));

    if (sif == NULL)
    {
        TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
                  ("  SIF: (null)\n"));
    }
    else
    {
        for (idx = 0; idx < len; idx++)
        {
            TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
                      ("%02x ", sif[idx]));

            if (!((idx+1) % 25))
            {
                TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
                          ("\n"));
            }
        }
        if ((idx+1) % 25)
        {
            TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG, ("\n"));
        }
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
     * determine tracing from INI files
     */
    if (TRANSPORT_RES(__MTP3_ANSI_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__MTP3_ANSI_RcvQueue);
        char *name = TRANSPORT_NAME(__MTP3_ANSI_RcvQueue);

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


        /*
         * Timers Initialization
         */
        ANSI_MTP3_Timers.numTimers = MTP3_NUM_TIMERS;

        ANSI_MTP3_Timers.timers = TIMERS_InitSharedTimerValues(
            DSM_MGMT_REC_ANSI_MTP3_TIMERS, MTP3_NUM_TIMERS);


        if (RESFILE_GetKeyValueOf(res, name, MTP3_T1_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t1 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T2_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t2 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T3_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t3 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T4_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t4 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T5_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t5 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T6_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t6 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T7_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t7 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T8_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t8 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T9_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t9 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T10_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t10 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T11_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t11 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T12_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t12 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T13_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t13 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T14_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t14 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T15_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t15 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T16_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t16 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T17_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t17 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T18_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t18 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T19_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t19 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T20_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t20 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T21_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t21 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T22_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t22 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T23_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t23 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T24_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t24 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T25_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t25 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T26_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t26 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T27_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t27 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T28_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t28 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T29_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t29 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T30_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t30 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T31_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t31 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T32_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t32 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T33_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t33 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T34_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_t34 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_SLT_T1_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_slt_t1 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_SLT_T2_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ansi_slt_t2 = RESFILE_ParseNum(value);
        }

        /*
         * Set and Commit Timer values
         */

        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T1, __ansi_t1);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T2, __ansi_t2);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T3, __ansi_t3);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T4, __ansi_t4);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T5, __ansi_t5);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T6, __ansi_t6);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T7, __ansi_t7);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T8, __ansi_t8);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T9, __ansi_t9);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T10, __ansi_t10);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T11, __ansi_t11);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T12, __ansi_t12);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T13, __ansi_t13);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T14, __ansi_t14);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T15, __ansi_t15);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T16, __ansi_t16);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T17, __ansi_t17);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T18, __ansi_t18);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T19, __ansi_t19);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T20, __ansi_t20);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T21, __ansi_t21);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T22, __ansi_t22);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T23, __ansi_t23);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T24, __ansi_t24);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T25, __ansi_t25);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T26, __ansi_t26);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T27, __ansi_t27);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T28, __ansi_t28);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T29, __ansi_t29);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T30, __ansi_t30);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T31, __ansi_t31);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T32, __ansi_t32);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T33, __ansi_t33);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_T34, __ansi_t34);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_SLT_T1, __ansi_slt_t1);  
        TIMERS_SetTimerValue(&ANSI_MTP3_Timers, MTP3_TIMER_SLT_T2, __ansi_slt_t2);  

        TIMERS_CommitSharedTimerValues(DSM_MGMT_REC_ANSI_MTP3_TIMERS);


        /*
         * Initialize behavior control
         */

         ANSI_MTP3_Behaviors.numBehaviors = MTP3_NUM_BEHAVIORS;

         ANSI_MTP3_Behaviors.behaviors =
              BEHAVIORS_InitSharedBehaviors(DSM_MGMT_REC_ANSI_MTP3_BEHAVIORS,
                                            MTP3_NUM_BEHAVIORS);

         BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_stpFunction,
                                ITS_FALSE);

         BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_fullRestartNeeded,
                                 ITS_TRUE);

         BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_spRestarting,
                                ITS_FALSE);

         BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_sendingStatus,
                                ITS_FALSE);

         BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_ANSI_MTP3_BEHAVIORS);


        if (RESFILE_GetKeyValueOf(res, name, SPARE_NIC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            MTP3_ANSI_HandleSpareNIC = strstr(value, "yes") != NULL ||
                                        strstr(value, "YES") != NULL;
        }
        if (RESFILE_GetKeyValueOf(res, name, STP_FUNCTION_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN isStpFunction = ITS_FALSE;

            isStpFunction = strstr(value, "yes") != NULL ||
                            strstr(value, "YES") != NULL;

            STPFunctionSet_ANSI(isStpFunction);

        }
        if (RESFILE_GetKeyValueOf(res, name, AUTO_TERM_ALLOC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            MTP3_ANSI_AutomaticTerminalAllocation =
                                        strstr(value, "yes") != NULL ||
                                        strstr(value, "YES") != NULL;
        }
        if (RESFILE_GetKeyValueOf(res, name, AUTO_LINK_ALLOC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            MTP3_ANSI_AutomaticDataLinkAllocation =
                                        strstr(value, "yes") != NULL ||
                                        strstr(value, "YES") != NULL;
        }

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, MTP3_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP3_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys) 
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, MTP3_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP3_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, MTP3_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP3_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_WARNING_STRING, ITS_FALSE);
            }
        }

        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, MTP3_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP3_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_DEBUG_STRING, ITS_FALSE);
            }
        }

        /* Event */
        if (RESFILE_GetKeyValueOf(res, name, MTP3_TRACE_EVENT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE;
                                                                                           
            if (strstr(value, MTP3_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_ANSI_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
                                                                                           
            if (std || fil)
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_EVENT_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_ANSI_TraceData,
                                          MTP3_EVENT_STRING, ITS_FALSE);
            }
        }
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
IMTP3_Initialize_ANSI(ITS_SS7_HANDLE handle)
{
    int i, j;
    ITS_Class dbClass;

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;
    stopped = ITS_FALSE;

    if ((MTP3_ANSI_TraceData = TRACE_Constructor("ANSI-MTP3",
                                                 MTP3_TraceMap, 5)) == NULL)
    {
        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if (MUTEX_CreateMutex(&mtp3Gate, 0) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_Intialize_ANSI: couldn't create mutex\n"));

        started = ITS_FALSE;

        return (ITS_EBADMUTEX);
    }
        MTP3_ERROR(("MTP3_Intialize_ANSI:  mutex created \n"));

    CALLBACK_AddCallback(TRANSPORT_registrations, MTP3_Register, NULL);
    CALLBACK_AddCallback(TRANSPORT_deregistrations, MTP3_Deregister, NULL);
 
    /* register Alarm Callback */
    /* CALLBACK_AddCallback(ALARM_Callbacks, MTP3_Alarms_ANSI, NULL); */
       MTP3_ERROR(("MTP3_Intialize_ANSI:  ITS_MTP3_ANSI_SRC  created \n"));

    if ((__MTP3_ANSI_RcvQueue = TQUEUETRAN_CreateTransport("ANSI-MTP3",
                                                           ITS_MTP3_ANSI_SRC,
                                                           ITS_MTP3_ANSI)) == NULL)
    {
        MTP3_CRITICAL(("MTP3_Initialize: couldn't create transport\n"));

        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Deregister, NULL);
        CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_ANSI, NULL);

        MUTEX_DeleteMutex(&mtp3Gate);

        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    /* read the INI */
    InitSettings();
    MTP3_CRITICAL(("MTP3_Initialize: InitSettings()\n"));

    /*
     * Find the redundancy configured type,
     */
    ITS_RedundancyClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);
    if (ITS_RedundancyClass != NULL)
    {
        /* Feature is added this is not stub we have do some thing here*/ 
        if (REDUNDANCY_CONFIGURED_TYPE(ITS_RedundancyClass) ==
                                    ITS_ACTIVE_ACTIVE)
        {            
            /* we are active-active no need for this class here*/
            ITS_RedundancyClass = NULL;
        }
    }
    MTP3_ERROR(("MTP3_Initialize: InitSettings()\n"));

    if ((mtp3Thread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        MTP3_CRITICAL(("MTP3_Initialize: couldn't create thread array\n"));

        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Deregister, NULL);
        CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_ANSI, NULL);

        MUTEX_DeleteMutex(&mtp3Gate);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if ( (routeRWLock = ROUTE_RWLockCreate() ) == NULL)
    {
        MTP3_ERROR(("Cannot Create ROUTE Reader/Writer Lock."));
        return ITS_ENOMEM;
    }



        MTP3_CRITICAL(("MTP3_Initialize: Before  For Loop\n"));
    for (i = 0; i < numThreads; i++)
    {
        MTP3_CRITICAL(("MTP3_Initialize: Going to enter For Loop\n"));
        if (THREAD_CreateThread(&mtp3Thread[i], 0, ANSI_MTP3Thread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            MTP3_CRITICAL(("MTP3_Initialize: couldn't create thread\n"));

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&mtp3Thread[j]);

                THREAD_DeleteThread(&mtp3Thread[j]);
            }

            free(mtp3Thread);

            CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
            CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Deregister, NULL);
            CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_ANSI, NULL);

            MUTEX_DeleteMutex(&mtp3Gate);

            started = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    //if (ITS_FindFeature("SCTP") == NULL)
    {
        if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
        {
            DBC_AddDoCommand(MTP3_Console_ANSI);
        }
    }

    PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_INITIALIZE);
    MTP3_CRITICAL(("MTP3_Initialize: So finally returning sucess\n"));

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
void
IMTP3_Terminate_ANSI(ITS_SS7_HANDLE handle)
{
    int i;
    ITS_EVENT ev;
    void *status;
    ITS_Class dbClass;

    if (!started)
    {
        return;
    }

    if (stopped)
    {
        return;
    }

    stopped = ITS_TRUE;
    started = ITS_FALSE;

//    if (ITS_FindFeature("SCTP") == NULL)
    {
        if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
        {
            DBC_RemDoCommand(MTP3_Console_ANSI);
        }
    }

    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &ev);
    }

    PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_TERMINATE);

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&mtp3Thread[0], &status);

        THREAD_DeleteThread(&mtp3Thread[0]);
    }

    free(mtp3Thread);

    ITS_C_ASSERT(__MTP3_ANSI_RcvQueue != NULL);
    TQUEUETRAN_DeleteTransport(__MTP3_ANSI_RcvQueue);

    CALLBACK_RemCallback(TRANSPORT_deregistrations, MTP3_Deregister, NULL);
    CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
    CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_ANSI, NULL);

    MUTEX_DeleteMutex(&mtp3Gate);

    TRACE_Destructor(MTP3_ANSI_TraceData);
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
HandleTimerEvent(ITS_TimerData *td)
{
    MTP3_TimerContext ctxt;
    MTP3_HEADER_ANSI mtp3;
    ITS_EVENT ev;
    int ret;

    memcpy(&ctxt, td->context, sizeof(MTP3_TimerContext));

    ret = ITS_SUCCESS;

    switch (ctxt.timerId)
    {
    case MTP3_T1:
        /* Increament peg for Timer T1 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T1_EXPIRED);

        /* Delay to avoid message re-sequencing on changeover */
               MTP3_ERROR(("Timer T1 Expired @@@@avoid message re-sequencing on changeove@@@\n"));
        return TCOC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T1,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T2:
        /* Increament peg for Timer T2 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T2_EXPIRED);

        /* Waiting for changeover acknowledgment */
               MTP3_ERROR(("Timer T2 Expired @@@@ Waiting for changeover acknowledgment@@@\n"));
        return TCOC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T2,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T3:
        /* Increament peg for Timer T3 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T3_EXPIRED);

        /* Time controlled diversion -- delay to avoid
         * mis-sequencing on changeback */
               MTP3_ERROR(("Timer T3 Expired @@@@ Time controlled diversion -- delay to avoid mis-sequencing on changeback@@@\n"));
        return TCBC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T3,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T4:
        /* Increament peg for Timer T4 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T4_EXPIRED);

        /* Waiting for changeback acknowledgment (first attempt) */
               MTP3_ERROR(("Timer T4 Expired @@@@Waiting for changeback acknowledgment (first attempt)@@@\n"));
        return TCBC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T4,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T5:
        /* Increament peg for Timer T5 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T5_EXPIRED);

        /* Waiting for changeback acknowledgment (second attempt) */
               MTP3_ERROR(("Timer T5 Expired @@@@Waiting for changeback acknowledgment (second attempt)@@@\n"));
        return TCBC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T5,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T6:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);
               MTP3_ERROR(("Timer T6 Expired @@@@Delay to avoid message mis-sequencing on controlled rerouting@@@\n"));

        /* Increament peg for Timer T6 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T6_EXPIRED);

        ret = TCRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T6,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        break;

    case MTP3_T7:
        /* Increament peg for Timer T7 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T7_EXPIRED);
               MTP3_ERROR(("Timer T7 Expired @@@@Wating for signalling data link coonection aclnowlwdgement@@@\n"));

        return LSDA_Main_ANSI(MTP3_TIMER, SLM_TRIGGER_T7,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);
 
    case MTP3_T8:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T8 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T8_EXPIRED);
               MTP3_ERROR(("Timer T8 Expired @@@@Transfer - probhibited inhibted timer @@@\n"));

        ret = RTPC_Main_ANSI(MTP3_TIMER, SRM_TRIGGER_T8,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T9:
        /* NOT USED */
        break;

    case MTP3_T10:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T10 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T10_EXPIRED);
               MTP3_ERROR(("Timer T10 Expired @@@@Wating to repeat signalling RSTM @@@\n"));

        ret = RSRT_Main_ANSI(MTP3_TIMER, SRM_TRIGGER_T10,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T11:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T11 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T11_EXPIRED);
               MTP3_ERROR(("Timer T11 Expired @@@@Transfer restricted timer  @@@\n"));

        ret = TSRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T11,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T12:
        /* Increament peg for Timer T12 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T12_EXPIRED);
               MTP3_ERROR(("Timer T12 Expired @@@@Wating for uninhibit acknowledegment @@@\n"));

        return TLAC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T12,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T13:
        /* Increament peg for Timer T13 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T13_EXPIRED);
               MTP3_ERROR(("Timer T13 Expired @@@@Wating for force uninhibit @@@\n"));

        return TLAC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T13,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T14:
        /* Increament peg for Timer T14 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T14_EXPIRED);
               MTP3_ERROR(("Timer T14 Expired @@@@Wating for inhibit acknowledegement@@@\n"));

        return TLAC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T14,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T15:
        /* Waiting to repeat signalling route set congestion test */
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);
               MTP3_ERROR(("Timer T15 Expired @@@@Waiting to repeat signalling route set congestion test@@@\n"));

        /* Increament peg for Timer T15 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T15_EXPIRED);

        ret = TRCC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T11,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_SET);
 
        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T16:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T16 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T16_EXPIRED);
               MTP3_ERROR(("Timer T16 Expired @@@@Waiting for route set  congestion status update @@@\n"));

        ret = RCAT_Main_ANSI(MTP3_TIMER, SRM_TRIGGER_T16,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T17:
        /* Increament peg for Timer T17 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T17_EXPIRED);
               MTP3_ERROR(("Timer T17 Expired @@@@Link restart alignment ls|lc %d|%d@@@\n",ctxt.data.linkInfo.linkSet,ctxt.data.linkInfo.linkCode));

        return LSAC_Main_ANSI(MTP3_TIMER, SLM_TRIGGER_T17,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);
 
    case MTP3_T18:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T18 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T18_EXPIRED);
               MTP3_ERROR(("Timer T18 Expired @@@@Repeat TFR once by response method  @@@\n"));

        ret = RTRC_Main_ANSI(MTP3_TIMER, SRM_TRIGGER_T18,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T19:
        /* Increament peg for Timer T19 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T19_EXPIRED);
               MTP3_ERROR(("Timer T19 Expired @@@@Failed link craft referral timer@@@\n"));

        return LSAC_Main_ANSI(MTP3_TIMER, SLM_TRIGGER_T19,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);
 
    case MTP3_T20:
        /* Increament peg for Timer T20 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T20_EXPIRED);
               MTP3_ERROR(("Timer T20 Expired @@@@Wating to repeat local inhibit test@@@\n"));

        return TLAC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T20,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T21:
        /* Increament peg for Timer T21 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T21_EXPIRED);
               MTP3_ERROR(("Timer T21 Expired @@@@Wating to repeat remote inhibit test@@@\n"));

        return TLAC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T21,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T22:
        /* Increament peg for Timer T22 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T22_EXPIRED);
               MTP3_ERROR(("Timer T22 Expired @@@@Timer at Restarting SP wating for signalling links to become available@@@\n"));

        return TPRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T22,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T23:
        /* Increament peg for Timer T23 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T23_EXPIRED);
               MTP3_ERROR(("Timer T23 Expired @@@@Timer at Restarting SP started after aT22 wating to receive all TRA message@@@\n"));

        return TPRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T23,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T24:
        /* Increament peg for Timer T24 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T24_EXPIRED);
               MTP3_ERROR(("Timer T24 Expired @@@@Timer at Restarting STP started after aT23 wating to broadcast all TRA message@@@\n"));

        return TPRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T24,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T25:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T25 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T25_EXPIRED);
               MTP3_ERROR(("Timer T25 Expired @@@@Timer at Restarting SP and SP adjacent to restarting SP waiting for TRA@@@\n"));

        return TSRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T25,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_SET);

    case MTP3_T26:
        /* Increament peg for Timer T26 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T26_EXPIRED);
               MTP3_ERROR(("Timer T26 Expired @@@@Timer at Restarting SP wating to repeat TRW message @@@\n"));

        return TPRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T26,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T27:
        /* Increament peg for Timer T27 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T27_EXPIRED);
               MTP3_ERROR(("Timer T27 Expired @@@@Minimum duration of unavailablity for full restart@@@\n"));

        return TPRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T27,
                              NULL, 0,
                              ITS_SS7_DEFAULT_LINK_SET,
                              ITS_SS7_DEFAULT_LINK_CODE);

    case MTP3_T28:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T28 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T28_EXPIRED);
               MTP3_ERROR(("Timer T28 Expired @@@@Timer at SP adjacent to restarting SP wating for TRW message@@@\n"));

        ret = TSRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T28,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T29:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T29 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T29_EXPIRED);
               MTP3_ERROR(("Timer T29 Expired @@@@Timer started when TRA sent in response to unexpected TRA or TRW message@@@\n"));

        ret = TSRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T29,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T30:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* Increament peg for Timer T30 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T30_EXPIRED);
               MTP3_ERROR(("Timer T30 Expired @@@@Timer to limit sending of TFPs and TFRs in response to unexpected TRA or TRW message@@@\n"));

        ret = TSRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T30,
                             ev.data, ev.len,
                             ctxt.data.routeInfo.linkSet,
                             ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T31:
        /* Increament peg for Timer T31 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T31_EXPIRED);
               MTP3_ERROR(("Timer T31 Expired @@@@False link congestion detection timer @@@\n"));

        return TSRC_Main_ANSI(MTP3_TIMER, STM_TRIGGER_T31,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T32:
        /* Increament peg for Timer T32 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T32_EXPIRED);
               MTP3_ERROR(("Timer T32 Expired @@@@ link oscillation timer @@@\n"));

        return LSAC_Main_ANSI(MTP3_TIMER, SLM_TRIGGER_T32,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T33:
        /* Increament peg for Timer T33 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T33_EXPIRED);
               MTP3_ERROR(("Timer T33 Expired @@@@ probation timer for link oscillation@@@\n"));

        return LSAC_Main_ANSI(MTP3_TIMER, SLM_TRIGGER_T33,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_T34:
        /* Increament peg for Timer T34 expired */
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_T34_EXPIRED);
               MTP3_ERROR(("Timer T34 Expired @@@@suspension timer for link  oscillation@@@\n"));

        return LSAC_Main_ANSI(MTP3_TIMER, SLM_TRIGGER_T34,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_SLT_T1:
               MTP3_ERROR(("Timer SLT_T1  Expired @@@@@@@\n"));
        return SLTC_Main_ANSI(MTP3_TIMER, SLT_TRIGGER_T1,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);

    case MTP3_SLT_T2:
               MTP3_ERROR(("Timer SLT_T2  Expired @@@@@@@\n"));
        return SLTC_Main_ANSI(MTP3_TIMER, SLT_TRIGGER_START_TEST,
                              NULL, 0,
                              ctxt.data.linkInfo.linkSet,
                              ctxt.data.linkInfo.linkCode);
        break;

    case MTP3_LEAVE_TMR:
            MTP3_DEBUG(("MTP3_Main: handle LEAVE TIMER msg.:NODECARDSTATE[%d]\n",NODECARDSTATE));
            if(NODECARDSTATE == 74)
            {
              MTP3_DEBUG(("MTP3_Main: REBOOTING BACKUP:ON LEAVE TIMER EXPIRY\n"));
              MTP3_DEBUG(("MTP3_Main: REBOOTING BACKUP:ON LEAVE TIMER EXPIRY\n"));
              MTP3_DEBUG(("MTP3_Main: REBOOTING BACKUP:ON LEAVE TIMER EXPIRY\n"));
              MTP3_DEBUG(("MTP3_Main: REBOOTING BACKUP:ON LEAVE TIMER EXPIRY\n"));
              abort();     
            }
            else
            {
              MTP3_DEBUG(("MTP3_Main: since Node state is ACTIVE:do nothing\n"));
            }
            break;
       
    default:
        MTP3_DEBUG(("HandleTimerEvent: Unknown timer id %d\n",
                    ctxt.timerId));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    /* NOTREACHED */
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
ITS_BOOLEAN 
NeedLock(ITS_OCTET *sif)
{
    if (sif[0] != L2_L3_DATA)
    {
        return ITS_TRUE;
    }
    else
    {

        MTP3_HEADER *mtp3;
        ITS_OCTET sio;

        mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
        sio = MTP3_HDR_GET_SIO(*mtp3);
        switch (sio & MTP3_SIO_UP_MASK)
        {
        case MTP3_SIO_SNMM:
        case MTP3_SIO_SLTM_REG:
        case MTP3_SIO_SLTM_SPEC:

            return ITS_TRUE;

        default:

            /* user data message */
            return ITS_FALSE;

        }

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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  Bug Id 972              Resolution for multiple RP
 *                                               recovery alarms/traces bug
 * Mani      05-05-2005  Bug Id 1731
 *
 ****************************************************************************/
THREAD_RET_TYPE
ANSI_MTP3Thread(void *arg)
{
    ITS_EVENT mtp3Event,ev;
    ITS_BOOLEAN cont;
    ITS_TimerData *td;
/***** ANSI Change for same Node Start Here ****/
    ITS_UINT threadId = THREAD_GetCurrentThreadID() % MAX_THREADS;
    SS7_LinkSetPtr ls=NULL;
    SS7_LinkPtr ln=NULL;
    ITS_OCTET sio,ret=0;
    MTP3_HEADER *mtp3_hed;
    ITS_OCTET flag=0,Act_flag=0;
    ITS_USHORT dest;
    MTP3_HEADER *mtp3;
    MTP3_TimerContext tc;
/***** ANSI Change for same Node Ends Here ****/

    memset(&mtp3Event, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__MTP3_ANSI_RcvQueue) = ITS_TRUE;
    MTP3_ERROR(("MTP3_Main: ANSI_MTP3Thread Created Sucessfully.\n"));

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__MTP3_ANSI_RcvQueue))
                                                        (__MTP3_ANSI_RcvQueue,
                                                         &mtp3Event)
           == ITS_SUCCESS)
    {
        switch (mtp3Event.src)
        {
        case ITS_MTP3_ANSI_SRC:
            MTP3_DEBUG(("MTP3_Main: handle termination event.\n"));

            TRANSPORT_IS_ACTIVE(__MTP3_ANSI_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;
        case ITS_SCCP_ANSI_SRC:
        case ITS_ISUP_ANSI_SRC:
            if (MTP3_MSG_TYPE(&mtp3Event) != MTP3_MSG_USER_DATA)
            {
                MTP3_DEBUG(("MTP3_Main: message type is not user data: %d\n",
                            MTP3_MSG_TYPE(&mtp3Event)));

                break;
            }

            if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Failed to get route lock\n"));

                break;
            }

            SMH_Main_ANSI(MTP3_L4, MTP3_SMH_HMRT, SMH_TRIGGER_L4_L3_MSG,
                          mtp3Event.data, mtp3Event.len,
                          ITS_SS7_DEFAULT_LINK_SET,
                          ITS_SS7_DEFAULT_LINK_CODE);

            ROUTE_UnlockRead(routeRWLock, __MTP3_ANSI_RcvQueue);
            break;

        case ITS_TIMER_SRC:
        {
            MTP3_TimerContext ctxt;
            MTP3_DEBUG(("MTP3_Main: handle TIMER msg.\n"));

            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Failed to get route lock\n"));

                break;
            }

            td = (ITS_TimerData *)mtp3Event.data;
            memcpy(&ctxt, td->context, sizeof(MTP3_TimerContext));
            HandleTimerEvent(td);

            LINKSET_CommitLinkSet(
                    LINKSET_FindLinkSet( ctxt.data.linkInfo.linkSet));


            ROUTE_UnlockWrite(routeRWLock);
            break;
        }
        case HEALTH_MANAGER_INSTANCE: 
             {
               /*Fix for standalone issue on tcp break and reconnect: Starting Leave Timer if node backup, 
               on expiry rebooting backup*/
               MTP3_DEBUG((" MTP3 : NODECARDSTATE [%d] ",NODECARDSTATE));
               if(NODECARDSTATE == 74)
               {
                 MTP3_DEBUG((" MTP3 CARD is BACKUP , so starting  LEAVE TIMER "));
                 tc.timerId = MTP3_LEAVE_TMR;
                 tc.data.linkInfo.linkSet = 255;
                 tc.data.linkInfo.linkCode = 255;

                 LeaveTmrSerial = TIMERS_StartTimer_MSEC(ITS_MTP3_SRC,
                                 __ansi_leaveTmr * USEC_PER_MILLISEC,
                                 &tc, sizeof(MTP3_TimerContext));
                  MTP3_DEBUG(("MTP3 START LEAVE TIMER ON BACKUP : Timer SERIAL [%d]\n",LeaveTmrSerial));
               }
               else
               {
                  MTP3_DEBUG((" MTP3 CARD is ACTIVE , so no LEAVE TIMER is started"));

               }
                PEER_NODELEAVEOP(&mtp3Event);
                break;
             }
        default:

            if (MTP3_MSG_TYPE(&mtp3Event) == MTP3_MSG_USER_DATA)
            {
                MTP3_DEBUG(("MTP3_Main: handle L4 msg.\n"));

                if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Failed to get route lock\n"));

                    break;
                }


                SMH_Main_ANSI(MTP3_L4, MTP3_SMH_HMRT, SMH_TRIGGER_L4_L3_MSG,
                              mtp3Event.data, mtp3Event.len,
                              ITS_SS7_DEFAULT_LINK_SET,
                              ITS_SS7_DEFAULT_LINK_CODE);

                ROUTE_UnlockRead(routeRWLock, __MTP3_ANSI_RcvQueue );
 
            }
            else
            {
                ITS_OCTET linkSet, linkCode;
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;

                if (MTP2_ReceiveData_ANSI(&mtp3Event, &linkSet, &linkCode,
                                          buf, &len) != ITS_SUCCESS)
                {
                    MTP3_WARNING(("Failed to receive L2 data\n"));

                    MTP3_Alarm_ANSI(2405, __FILE__, __LINE__, NULL);
                }
                else
                {
                    if ((ITS_RedundancyClass != NULL)&&(buf[0] == L2_L3_DATA))
                       {    mtp3 = (MTP3_HEADER *)&buf[1];
                            sio = MTP3_HDR_GET_SIO(*mtp3);
                         switch((sio & MTP3_SIO_UP_MASK))
                         {
                          case MTP3_SIO_SNMM:
                          case MTP3_SIO_SLTM_REG:
                          case MTP3_SIO_SLTM_SPEC:
                          break;
                          default : 
                                if (REDUNDANCY_GET_NODE_STATE(ITS_RedundancyClass) == ITS_STATE_PRIMARY)
                                 {
                                   dest = MTP3_UserPartOwner((ITS_OCTET)(sio & MTP3_SIO_UP_MASK));
                                    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
                                  {
                                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                                    if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA, mtp3,
                                         buf + sizeof(MTP3_HEADER) + sizeof(ITS_OCTET),(ITS_USHORT)
                                        (len - sizeof(MTP3_HEADER) -sizeof(ITS_OCTET)))) != ITS_SUCCESS)
                                       {
                                        MTP3_DEBUG(("HMDT_Main_CCITT: MTP3 encode failed.\n"));
                                        MTP3_Alarm_ANSI(2501, __FILE__, __LINE__, "Destination %d", dest);
                                        return (ret);
                                       }
                                   }
                                    TRANSPORT_PutEvent(dest, &ev);
                                    Act_flag=1;
                                 }
                           break;
                        }
                       } 
                   if(Act_flag ==1)
                   {
                      Act_flag=0;
                      MTP3_DEBUG(("Sucessfully Put the DATA to SCCP: on ACTIVE NODE \n"));
                      break;
                   }
                /****************************************************************************
                  As we are taking RW/Lock on Backup node too
                  To reduce number of RW/Lock we shall be Taking this Lock Only on Active node
                  and IN case of Managment message at backup node
                 *****************************************************************************/
                    if ((ITS_RedundancyClass != NULL)&&(buf[0] == L2_L3_DATA))
                       {
                            mtp3_hed = (MTP3_HEADER *)&buf[1];
                            sio = MTP3_HDR_GET_SIO(*mtp3_hed);
                         switch((sio & MTP3_SIO_UP_MASK))
                         {
                          case MTP3_SIO_SNMM:
                          case MTP3_SIO_SLTM_REG:
                          case MTP3_SIO_SLTM_SPEC:
                          break;
                          default : 
                         /* Now we have to check the user part state*/
                         if (REDUNDANCY_GET_NODE_STATE(ITS_RedundancyClass) == ITS_STATE_BACKUP)
                          {
                           TRANSPORT_Control *trCtl = NULL;
                           /* Put the event on the inter node
                            * hopefully we find some nicer way to do it
                            * TBD
                            */
                           trCtl = TRANSPORT_FindTransportByName( MTP3_INTER_NODE_STRING);
                           if (trCtl == NULL)
                           {
                            MTP3_DEBUG(("MTP3 Transport Find fail\n"));
                           }
                      
                           ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                            if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA, mtp3_hed,
                                         buf + sizeof(MTP3_HEADER) + sizeof(ITS_OCTET),(ITS_USHORT)
                                        (len - sizeof(MTP3_HEADER) -sizeof(ITS_OCTET)))) != ITS_SUCCESS)
                                       {
                                        MTP3_DEBUG(("HMDT_Main_CCITT: MTP3 encode failed.\n"));
                                        MTP3_Alarm_ANSI(2501, __FILE__, __LINE__, "Destination %d", dest);
                                        return (ret);
                                       }
                           ev.src = sio & MTP3_SIO_UP_MASK;
                           MTP3_DEBUG(("Node is Backup ev.src %d\n",ev.src));
                                  
                           ret = TRANSPORT_PutEvent(TRANSPORT_INSTANCE(trCtl), &ev);
                           if (ret != ITS_SUCCESS)
                           {
                            MTP3_DEBUG(("HMDT_Main_CCITT: No Inter node connection \n"));
                           }
                           else
                              {
                                MTP3_DEBUG(("Node is Backup Sending to Internode\n"));
                              }
                            flag=1;
                            TRANSPORT_UnfindTransport(trCtl);
                            //return ret;
                         }
                         break;
                        }
                      
                      }

                   if(flag ==1)
                   {
                      flag=0;
                       //  MTP3_DEBUG(("HMDT_Main_CCITT:o Inter node connection \n"));
                       break;
                   }
               /*********************************************************************************************/
                    ITS_BOOLEAN isLockSet = ITS_FALSE;

                    if (buf[0] != L2_L3_REMOTE_PROCESSOR_REC)
                    {
                        MTP3_DEBUG(("MTP3_Main: handle L2 msg.\n"));
                    }

                    if (NeedLock(buf))
                    {
                        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
                        {
                            MTP3_ERROR(("Failed to get route lock\n"));

                            break;
                        }
                        isLockSet = ITS_TRUE;
                    }
                    else
                    {
                        if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
                        {
                            MTP3_ERROR(("Failed to get route lock\n"));

                            break;
                        }
                    }

                    SMH_Main_ANSI(MTP3_L2, MTP3_SMH_HMDT,
                                  SMH_TRIGGER_L2_L3_MSG,
                                  buf, len,
                                  linkSet, linkCode);
                    if (isLockSet)
                    {
                        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
                        ROUTE_UnlockWrite(routeRWLock);
                    }
                    else
                    {
                        ROUTE_UnlockRead(routeRWLock, __MTP3_ANSI_RcvQueue);
                    }

                }
            }

            break;
        }
    sched_yield(); 
    }

    TRANSPORT_IS_ACTIVE(__MTP3_ANSI_RcvQueue) = ITS_FALSE;

    THREAD_NORMAL_EXIT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert an ITS_EVENT to MTP3_EventRec
 *
 *  Input Parameters:
 *      ITS_EVENT
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
ITSSS7DLLAPI MTP3_EventRec
ItsEventToMTP3EventRec_ANSI(ITS_EVENT ev)
{
    MTP3_EventRec evRec;

    ITS_UINT seqNoSize = sizeof(evRec.seqNo);

    ITS_EVENT_INIT(&evRec.event, ev.src, ev.len - seqNoSize);

    memcpy(&evRec.seqNo, ev.data, seqNoSize);
    memcpy(evRec.event.data, &ev.data[seqNoSize], ev.len - seqNoSize);

    return evRec;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert a MTP3_EventRec to an ITS_EVENT
 *
 *  Input Parameters:
 *      MTP3_EventRec
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
ITSSS7DLLAPI ITS_EVENT
MTP3EventRecToItsEvent_ANSI(MTP3_EventRec evRec)
{
    ITS_EVENT ev;

    ITS_UINT seqNoSize = sizeof(evRec.seqNo);

    ITS_EVENT_INIT(&ev, evRec.event.src, evRec.event.len + seqNoSize);

    memcpy(ev.data, &evRec.seqNo, seqNoSize);
    memcpy(&ev.data[seqNoSize], evRec.event.data, evRec.event.len);

    return ev;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *
 *  Input Parameters:
 *     
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
SetLinkUnavailable(ITS_POINTER data, void *in, void *out)
{

    ITS_EVENT ev;
    SS7_Link *link = (SS7_Link *)data;
    DSM_MembershipChangeCbData *membershipChangeCbData = 
                        (DSM_MembershipChangeCbData *) in;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    MTP3_DEBUG(("SetLinkUnavailable: linkCode:%d  nodeId %d\n", link->linkCode, link->dsmNodeId));
 
//    if (link->dsmNodeId == concernedNodeId) 
//    {
        /* we need to mark this link unavailable */

        MTP3_DEBUG(("Deactivate link %d \n", link->linkCode));
        if (link->id == 20002)
           {       
                    MTP3_DEBUG (("\nFor linkset =%d,link Code =%d   FILE:%s LINE:%d\n", link->linkSet->linkSet,link->linkCode , __FILE__, __LINE__));
        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC, 3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_OUT_OF_SERVICE;
        ev.data[1] = link->linkSet->linkSet;
        ev.data[2] = link->linkCode; 

        TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &ev);

        return ITS_SUCCESS;  
        }
    

//    }

    return ITS_SUCCESS;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *
 *  Input Parameters:
 *    
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
#if 0
static int
SetLinkAvailable(ITS_POINTER data, void *in, void *out)
{

    SS7_Link *link = (SS7_Link *)data;
    DSM_MembershipChangeCbData *membershipChangeCbData =
                        (DSM_MembershipChangeCbData *) in;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    MTP3_DEBUG(("SetLinkAvailable: linkCode:%d  nodeId %d \n",
            link->linkCode, link->dsmNodeId));

    if (link->dsmNodeId == concernedNodeId)
    {
        /* we need to mark this link unavailable */
        MTP3_DEBUG(("***Activate link %d ***\n", link->linkCode));
    }

    return ITS_SUCCESS;


}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *
 *  Input Parameters:
 *      
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
MTP3_MembershipChangeCallBack_ANSI(ITS_POINTER object, 
                                   ITS_POINTER userData, 
                                   ITS_POINTER callData)
{
    char *tmp;
    ITS_EVENT mtp3Event;

    DSM_MembershipChangeCbData *membershipChangeCbData = 
                        (DSM_MembershipChangeCbData *) callData;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    switch (membershipChangeCbData->membershipChangeType)
    {

    case DSM_FT_GROUP_MEMBER_JOIN:   

        /* Activate links owned by the concerned node */
      tmp = getenv ("Node");
      MTP3_CRITICAL (("DSM_FT_GROUP_MEMBER_JOIN nodeID: concernedNodeId [%d] SelfNodeID [%s]\n", concernedNodeId,tmp));
      MTP3_DEBUG (("DSM_FT_GROUP_MEMBER_JOIN nodeID:[%d] PEER_MTP3_NODE_STATUS[%d] \n", concernedNodeId,PEER_MTP3_NODE_STATUS));

        break;

   
    case DSM_FT_GROUP_MEMBER_LEAVE: 

        /* Deactivate links owned by the concerned node */
        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_LEAVE nodeID: %d\n",concernedNodeId));
/** REDUNANCY CHANGES START HERE **/
//        DSM_TableIterate(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS, callData, NULL, SetLinkUnavailable);  
//        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_LEAVE nodeID: %d\n",concernedNodeId));
          PEER_MTP3_NODE_STATUS = 1;
/** REDUNANCY CHANGES ENDS HERE **/
        break;

    
    case DSM_FT_GROUP_MEMBER_DEAD:
/** REDUNANCY CHANGES START HERE **/
         PEER_MTP3_NODE_STATUS = 1;
         MTP3_DEBUG(("MTP3 DSM_FT_GROUP_MEMBER_DEAD nodeID: %d\n",concernedNodeId));
         /**************************************************************************************************/
          ITS_EVENT_INIT(&mtp3Event,HEALTH_MANAGER_INSTANCE,sizeof(ITS_OCTET));
          mtp3Event.data[0]=DSM_FT_GROUP_MEMBER_DEAD;
          TRANSPORT_PutEvent(ITS_MTP3_SRC, &mtp3Event);
          MTP3_DEBUG (("Event put to MTP3 Queue\n"));
          TRANSPORT_PutEvent (ITS_SCCP_SRC, &mtp3Event);
          MTP3_DEBUG (("Event put to SCCP Queue\n"));

        /**************************************************************************************************/


        break;

    case DSM_FT_GROUP_MEMBER_ALIVE:
        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_ALIVE nodeID: %d\n",concernedNodeId));

        break;

    default:

        MTP3_DEBUG(("DSM_FT_GROUP: Unknown Event nodeID: %d\n",concernedNodeId));
        break;
  
    }

    
}
 
PEER_NODELEAVEOP(ITS_EVENT *evt)
{
    MTP3_PAUSE_RESUME resume;
    MTP3_HEADER mtp3;
    ITS_INT i=0,j=0,k=0,l=0,ret=0,m=0;
    ITS_UINT lscount=0,cnt=0,Dpc=0,status=0,lscnt=0;
    ITS_OCTET linkset[MAX_LINKSETS];
    ITS_BOOLEAN LINKSET_STATUS = ITS_FALSE;
    SS7_LinkSetPtr ls,lsEntry;
    SS7_LinkPtr ln;
    ITS_EVENT  event;
    ITS_INT LINK_REM_FLAG = ITS_FALSE;
    
    

     /*Find No of Links*/
     for (k = 0; k < MAX_LINKSETS; k++)
       {
         for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
           {
             if(linkTransportMapDB[k][l] >0)
               {
                if( k > 0 && k < 252)
                  {
                    lscount++;
                    linkset[cnt++]=k;
                    break;
                 }
               }
            }
       }
      MTP3_ERROR(("PEER_NODE LEAVE No of LinkSet =%d",lscount));
/*Patch:29-Nov-10:Case:When peer node goes down before ln_add on self node*/
    if(lscount == 0)
		{
      MTP3_ERROR((" No of LinkSet =%d,Therefore checking DSM entry ",lscount));
						for (m = 0; m < MAX_LINKSETS; m++)
						{
               if( m > 0 && m < 252)
               {
                if((lsEntry = LINKSET_FindLinkSet(m)) != NULL)
                 {
                   lscount++;
                   linkset[lscnt++]=m;
                 }
               }
                      
						}
          
      MTP3_ERROR(("PEER_NODE LEAVE :No of LinkSet =%d found in DSM",lscount));
		}
/*Patch:29-Nov-10:End*/

     /*Delete 20002 id links for all linkset*/ 
     for (i = 0; i < lscount; i++)
		 {
						 if((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[i])) == NULL)/*Find linkset Pointer*/
						 {
										 MTP3_ERROR(("MTP3LEAVE::Failed to find link set %d \n",i));
										 return (ITS_EINVALIDARGS);
						 }
						 for(j = 0; j < MAX_LINKS_PER_LINKSET; j++)
						 {
										 //if(linkTransportMapDB[(ITS_OCTET)linkset[i]][j]== 20002)
										 //  {
										 if((ln = LINK_FindLink ((ITS_OCTET)linkset[i], j)) != NULL)
										 {
														 MTP3_ERROR (("MTP3LEAVE:For link instance id =%d status %d FILE:%s LINE:%d\n", ln->id,ln->isUp, __FILE__, __LINE__));
                             if (ln->activityState == LINK_ACTIVITY_ACTIVE)
                                {
                                  status=1;
                                }
														 if(ln->id == 20002)
														 {
                                     if(ln->isUp!=ITS_FALSE)
                                      { 
                                        MTP3_Alarm_ANSI(2509, __FILE__, __LINE__, "linkset:linkcode %d:%d",linkset[i],j);
                                      }
																		 ret = LINK_RemLink((ITS_OCTET)linkset[i], ln);
																		 if (ret != ITS_SUCCESS)
																		 {
																						 MTP3_ERROR(("MTP3LEAVE:;link del Fail"));
																		 }
                                     else
                                     {
                                         LINK_REM_FLAG = ITS_TRUE;
																				 MTP3_ERROR(("MTP3LEAVE:;link del Success"));
                                     }
																		 MTP3_ERROR (("MTP3LEAVE:ls|lc %d|%d Instance id = %d removed Sucessfully\n",linkset[i],ln->linkCode,ln->id));
														 }
										 }
										 // }
						 }
						 MTP3_ERROR (("MTP3LEAVE:ls| %d|  LinkCode Loop Exited\n",linkset[i]));
						 /***To Generate PAUSE*/
						 for(j = 0; j < ls->numLinks; j++)
						 {
										 MTP3_DEBUG(("MTP3LEAVE::Link i %d ls->links[i]->isUp  %d \n",j,ls->links[j]->isUp));
										 if(ls->links[j]->isUp!=ITS_FALSE)
										 {
														 MTP3_DEBUG(("MTP3LEAVE::Link set %d is not Out of Service\n",ls->linkSet));
														 LINKSET_STATUS = ITS_TRUE;
										 }
						 }
						 if((LINKSET_STATUS == ITS_FALSE &&  ls->numLinks !=0) || (LINK_REM_FLAG == ITS_TRUE && ls->numLinks == 0 ))
						 {
										 MTP3_ERROR(("Link set %d Out of Service\n",ls->linkSet));
										 /*Generation Of Alarm*/
										 MTP3_Alarm_ANSI(2800, __FILE__, __LINE__, "LinkSet %d Out of Service", ls->linkSet);
										 MTP3_ERROR(("MTP3LEAVE:: Link set %d Out of Service PC %d \n",ls->linkSet,ls->adjacent));
										 /* mark all routes unavailable */
                     Dpc = ls->adjacent;
						//				 DSM_TableIterate(DSM_Mtp3FtGroupId, DSM_TABLE_DESTINATIONS, &Dpc,NULL, MarkAllRoutesUnAvailable);
										// DSM_TableIterate(DSM_Mtp3FtGroupId, DSM_TABLE_DESTINATIONS, NULL, NULL, MarkAllRoutesUnAvailable);
										 /*Indication of pause*/
                     MTP3_ERROR(("MarkAllRoutesUnAvailable::Status %d\n",status));
                     if(status == 1 )
                     {
										  mtp3.sio = ls->ni;/*fill ni*/
										  MTP3_RL_SET_OPC_VALUE(mtp3.label, ls->adjacent);/*this will created a problem with indirect PC*/
										  MTP3_RL_SET_DPC_VALUE(mtp3.label, ls->lpc);
										  MTP3_RL_SET_SLS(mtp3.label, 0);
										  MTP3_PC_SET_VALUE(resume.affected, ls->adjacent);/*this will created a problem with indirect PC*/
										  event.src = ITS_MTP3_SRC;
										  MTP3_Encode(&event, MTP3_MSG_PAUSE, &mtp3,(ITS_OCTET *)&resume, sizeof(MTP3_PAUSE_RESUME));
										  CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,NULL,(ITS_POINTER)&event);
										  ITS_EVENT_TERM(&event);
                      LINK_REM_FLAG = ITS_FALSE;
                      status=0; 
										  MTP3_ERROR(("MTP3LEAVE::  PAUSE SEND SUCCESSFULLY \n"));
                     }
						 }
						 /*End of PAUSE Changes*/
						 MTP3_ERROR(("Exiting Linkset Loop\n"));

		 }

/*performed required action if any*/
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
int 
MTP3_TransportPostInit_ANSI(TPOOL_THREAD *thr , ITS_HANDLE h)
{
   
    ITS_EVENT ev;
    TRANSPORT_Control *tc = (TRANSPORT_Control *) h;
    SS7_LinkPtr link = NULL;

    /* protect from bad ITS_Initialize calls. */
    if (h == NULL)
    {
        return (ITS_EINITFAIL);
    }

    /* FIXE ME: we have to wait until all links are configured 
     * before telling MTP3 to active links. This timer will give
     * Border transports enough time to configure to links.
     */
    TIMERS_Sleep(3);

    for (link = TRANSPORT_SS7_INFO(tc).linkInfo; link != NULL; link = link->next)
    {
#if 0
        /* Initialise Pegs for this Link */
        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            link->pegs[i] = 0;
        }
        link->MTP3_LINK_PEGS.name = "MTP3";
        link->MTP3_LINK_PEGS.numPegs =
                            sizeof(link->pegs) / sizeof(ITS_UINT);
        link->MTP3_LINK_PEGS.pegs = link->pegs;
#endif

        /* Send a message to MTP3 in order to reactivate link */
        MTP3_DEBUG(("Activate link %d \n", link->linkCode));

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_OUT_OF_SERVICE;
        ev.data[1] = link->linkSet->linkSet;
        ev.data[2] = link->linkCode;

        TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &ev);

    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for ansi mtp3.
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
 *  Manikandan  05-05-2005  Bug ID:1780, 1791,
 *                                 1783
 *
 ****************************************************************************/

int
INTELLINET_MTP3_Commit_ANSI(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = MTP3_ANSI_TraceData;

    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    if (td != NULL)
    {
        fprintf(fp, "\t\t\t<StackTrace>\n");

        if (TRACE_IsLevelOn(td, MTP3_TRACE_ABORT))
        {
            if (TRACE_IsOutputOn(td, MTP3_TRACE_ABORT, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_ABORT, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_ABORT, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, MTP3_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(td, MTP3_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, MTP3_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(td, MTP3_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, MTP3_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(td, MTP3_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(td, MTP3_TRACE_EVENT))
        {
            if (TRACE_IsOutputOn(td, MTP3_TRACE_EVENT, 0))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_EVENT, 1))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(td, MTP3_TRACE_EVENT, 2))
            {
                fprintf(fp, "\t\t\t\t<Event output = \"syslog\" />\n");
            }
        }

        fprintf(fp, "\t\t\t</StackTrace>\n");
    }

    fprintf(fp,"\t\t\t\t<Timers\n");

    for (count = 0; count < (int)ANSI_MTP3_Timers.numTimers; count++)
    {
        fprintf(fp,"\t\t\t\t\t%s = \"%lu\"\n",MTP3_ANSI_Timers[count],
                                             ANSI_MTP3_Timers.timers[count]);
    }

    fprintf(fp,"\t\t\t\t/>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\t%s = \"%s\"\n",STP_FUNCTION_STRING,
            (BEHAVIORS_GetBehavior(&ANSI_MTP3_Behaviors,
                                   MTP3_B_stpFunction) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}
void Disable_Default_Readflag()
  {
   ITS_INT  error;
      ITS_UINT nodeId   = DSM_GetNodeId();
      ITS_UINT threadId = THREAD_GetCurrentThreadID() % MAX_THREADS;

      ROUTE_RWLock *lock;


          ITS_UINT key = DSM_MGMT_REC_ROUTERWLOCK;

        DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

          lock = (ROUTE_RWLock *) DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                          DSM_TABLE_MGMT_DATA,
                          (ITS_OCTET*)&key,
                          sizeof(key), &error);

          if ( (lock != NULL) && (error == ITS_SUCCESS) )
          {

                  /*
                   * make sure this is set to false to allow the writer that
                   * already lock the ROUTE_Table to proceede.
                   */
                  ITS_TRACE_DEBUG(("Disable_Default_Readflag#%d: Setting "
                                          "thisInstanceIsReading to "
                                          "ITS_FALSE... \n", threadId));
                  lock->thisInstanceIsReading[nodeId][threadId] = ITS_FALSE;

                  /* commit lock to DSM*/
                  DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                                  DSM_TABLE_MGMT_DATA,
                                  (ITS_OCTET *)&key, sizeof(key),
                                  lock) ;
                  ITS_TRACE_DEBUG(("Disable_Default_Readflag#%d: thisInstanceIsReading "
                                          "is now set to ITS_FALSE\n", threadId));

                  DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
          }
          else
          {
                  ITS_TRACE_DEBUG(("ERROR: Disable_Default_Readflag lock == NULL; "
                                          "error %d", error));
                  DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);
          }


  }

