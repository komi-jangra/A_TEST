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
 *  ID: $Id: ttc-mtp3.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:35  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:11  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.2  2005/02/24 03:59:54  dsatish
 * LOG: Commit after deleting the printf
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/18 11:26:52  dsatish
 * LOG: Added Initial version file for TTC
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.9  2005/02/03 08:45:29  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.8  2005/01/31 09:32:45  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.7  2005/01/13 06:04:52  snagesh
 * LOG: XML persistency fix for MTP3_NUM_TIMERS
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.6  2005/01/05 10:47:13  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.5  2005/01/04 13:43:54  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.4  2004/12/31 07:19:26  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.3  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.2  2004/12/06 14:03:05  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.8.2.5.2.4.4.1  2004/12/06 10:41:47  adutta
 * LOG: Commented out SCTP check in DBC
 * LOG:
 * LOG: Revision 7.8.2.5.2.4  2004/10/06 13:26:20  mmanikandan
 * LOG: Issue in redundancy initialization
 * LOG:
 * LOG: Revision 7.8.2.5.2.3  2004/09/15 05:46:44  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.8.2.5.2.2  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.8.2.5.2.1  2004/01/30 11:13:38  sjaddu
 * LOG: Added  support for active-backup redundancy.
 * LOG:
 * LOG: Revision 7.8.2.5  2003/12/08 11:49:43  kannanp
 * LOG: Fix ITU timer peg related bugs.
 * LOG:
 * LOG: Revision 7.8.2.4  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.8.2.3  2003/02/18 07:17:59  ttipatre
 * LOG: Rectify Core problem with pegs when application initializes.
 * LOG:
 * LOG: Revision 7.8.2.2  2003/02/18 01:55:00  randresol
 * LOG: log mtp3 alarms to file
 * LOG:
 * LOG: Revision 7.8.2.1  2003/02/14 07:29:22  randresol
 * LOG: Enhancement for Pegs and Alarms
 * LOG:
 * LOG: Revision 7.8  2003/02/13 10:36:10  ttipatre
 * LOG: New alarms added.
 * LOG:
 * LOG: Revision 7.7  2002/12/24 07:46:47  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.6  2002/12/03 15:04:25  ngoel
 * LOG: use short form (remove compile error)
 * LOG:
 * LOG: Revision 7.5  2002/11/20 05:16:56  ttipatre
 * LOG: Modified to Only protocol specific alarms.
 * LOG:
 * LOG: Revision 7.4  2002/11/14 19:39:59  mmiers
 * LOG: Formatting
 * LOG:
 * LOG: Revision 7.3  2002/11/09 21:52:27  randresol
 * LOG: Add ROUTE Reader/Writer Lock for MTP3 Optimization
 * LOG:
 * LOG: Revision 7.2  2002/09/18 22:23:16  yranade
 * LOG: Avoid coredumps
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.24  2002/08/22 01:14:09  randresol
 * LOG: fix pointer problem seen in 64bit mode. replace
 * LOG: rinfo = *(ROUTE_InfoPtr *)(tmp->data); by the safer
 * LOG: memcpy(&rinfo, tmp->data, sizeof(rinfo));
 * LOG:
 * LOG: Revision 6.23  2002/08/19 18:05:28  mmiers
 * LOG: China build debug
 * LOG:
 * LOG: Revision 6.22  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.21  2002/08/15 20:27:37  mmiers
 * LOG: Don't dereference NULL pointers.
 * LOG:
 * LOG: Revision 6.20  2002/08/15 20:26:11  mmiers
 * LOG: Warning/error removal
 * LOG:
 * LOG: Revision 6.19  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.18  2002/07/12 14:25:11  mmiers
 * LOG: Minor cleanups
 * LOG:
 * LOG: Revision 6.17  2002/07/05 21:12:01  mmiers
 * LOG: Flag fixing
 * LOG:
 * LOG: Revision 6.16  2002/06/21 22:38:02  randresol
 * LOG: Add FTM callback to handle fail over.
 * LOG:
 * LOG: Revision 6.15  2002/06/19 17:11:00  mmiers
 * LOG: Add MTP3 OAM APIs
 * LOG:
 * LOG: Revision 6.14  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.13  2002/06/13 20:32:09  ttipatre
 * LOG: Adding MTP3 Pegs and Alarms
 * LOG:
 * LOG: Revision 6.12  2002/05/15 15:06:48  randresol
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
 * LOG: Revision 6.7  2002/05/07 15:44:05  wweng
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
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.19  2001/12/19 23:52:00  mmiers
 * LOG: Get ADAX MTP2 working.
 * LOG:
 * LOG: Revision 5.18  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.17  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.16  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.15  2001/12/07 23:11:47  mmiers
 * LOG: Fix up ITU MTP3 (start testing it).
 * LOG:
 * LOG: Revision 5.14  2001/12/06 22:39:05  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.13  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.12  2001/10/18 19:01:40  mmiers
 * LOG: Fallout from the routing changes
 * LOG:
 * LOG: Revision 5.11  2001/10/17 18:21:23  mmiers
 * LOG: Move the link map computation into IntelliSS7
 * LOG:
 * LOG: Revision 5.10  2001/10/03 19:42:46  mmiers
 * LOG: Timer cleanup.
 * LOG:
 * LOG: Revision 5.9  2001/10/02 22:13:18  mmiers
 * LOG: Fix non-MTP2 link handling.
 * LOG:
 * LOG: Revision 5.8  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.7  2001/09/24 22:50:23  mmiers
 * LOG: Remove bogus SSN from MTP3 P/R/S messages.  This adds fixmes to
 * LOG: SCMG.
 * LOG:
 * LOG: Revision 5.6  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.5  2001/09/06 00:39:57  mmiers
 * LOG: Work in the MTP2 codec.
 * LOG:
 * LOG: Revision 5.4  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.3  2001/08/31 19:34:33  mmiers
 * LOG: Add coarse locking.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
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
 * LOG: Revision 4.2  2001/08/07 19:11:45  mmiers
 * LOG: Add MTP3 threads.  Also a little cleanup.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.7  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.6  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.5  2000/10/05 23:04:33  mmiers
 * LOG: Go back to the old way for now.
 * LOG:
 * LOG: Revision 3.4  2000/09/25 20:09:46  mmiers
 * LOG: Finish off the route conversion code.
 * LOG:
 * LOG: Revision 3.3  2000/09/25 18:31:48  mmiers
 * LOG: Set up for the new routing table.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:25  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/03/29 18:29:20  mmiers
 * LOG:
 * LOG: Don't trace for non-errors before the trace settings are established.
 * LOG:
 * LOG: Revision 2.3  2000/02/12 00:41:16  mmiers
 * LOG:
 * LOG: Convert vendor to new CORE code.
 * LOG:
 * LOG: Revision 2.2  1999/12/18 00:21:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 23:45:10  mmiers
 * LOG:
 * LOG:
 * LOG: Convert the callback object.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:34  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.6  1999/10/25 20:24:49  mmiers
 * LOG:
 * LOG:
 * LOG: Corrections for the new transport class.
 * LOG:
 * LOG: Revision 1.5  1999/10/05 23:50:55  rsonak
 * LOG:
 * LOG: For the callback functions, removed the check for no-default-route.
 * LOG:
 * LOG: Revision 1.4  1999/08/26 23:44:59  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.3  1999/08/11 23:08:44  mmiers
 * LOG:
 * LOG:
 * LOG: Trace tweak again.
 * LOG:
 * LOG: Revision 1.2  1999/08/11 19:04:43  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for new trace structures.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:47  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_tq_trans.h>
#include <its_assertion.h>
#include <its_timers.h>
#include<its_thread_pool.h>
#include <its_dsm.h>
#include <its_route_rwlock.h>
#include <its_redundancy.h>
#include <its_ctf.h>

#ident "$Id: ttc-mtp3.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#if defined(PRC) || defined(USE_PRC_SCCP)
#undef CCITT
#define PRC
#include <china/mtp3.h>
#elif defined(TTC) || defined(USE_TTC_SCCP)
#undef CCITT
#define TTC
#include <japan/mtp3.h>
#else
#include <itu/mtp3.h>
#endif

#define MTP3_ALARM_FILE_NAME "itu-mtp3alarms.out"

#include <isup_sn.h>
#include <sccp_sn.h>

#include "mtp3_intern.h"

/*
 * local data
 */
static ITS_MUTEX        mtp3Gate;

static ITS_USHORT       userParts[MTP3_MAX_USER_PARTS] = { 0 };

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

static ITS_CHAR* MTP3_CCITT_Timers[] =
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

/* Redunancy class feature*/
ITS_Class ITS_RedundancyClass = NULL;

TRACE_Data* MTP3_CCITT_TraceData = NULL;

static ITS_UINT pegs[PEG_MTP3_NUM_PEGS_CCITT];
static PEGS_DECL_SUBSYS(CCITT_MTP3, pegs);
PEG_Manager *CCITT_MTP3_Pegs = &CCITT_MTP3_PEGS;

TQUEUETRAN_Manager* __MTP3_CCITT_RcvQueue = NULL;

THREAD_RET_TYPE     CCITT_MTP3Thread(void *arg);

int  __ccitt_t1 = 800;
int  __ccitt_t2 = 1400;
int  __ccitt_t3 = 800;
int  __ccitt_t4 = 800;
int  __ccitt_t5 = 800;
int  __ccitt_t6 = 800;
int  __ccitt_t7 = 1000;
int  __ccitt_t8 = 1000;
int  __ccitt_t9 = 0;
int  __ccitt_t10 = 30000;
int  __ccitt_t11 = 30000;
int  __ccitt_t12 = 800;
int  __ccitt_t13 = 800;
int  __ccitt_t14 = 2000;
int  __ccitt_t15 = 2000;
int  __ccitt_t16 = 1400;
int  __ccitt_t17 = 800;
int  __ccitt_t18 = 0;
int  __ccitt_t19 = 480000;
int  __ccitt_t20 = 90000;
int  __ccitt_t21 = 90000;
int  __ccitt_t22 = 30000;
int  __ccitt_t23 = 30000;
int  __ccitt_t24 = 30000;
int  __ccitt_t25 = 30000;
int  __ccitt_t26 = 12000;
int  __ccitt_t27 = 2000;
int  __ccitt_t28 = 3000;
int  __ccitt_t29 = 60000;
int  __ccitt_t30 = 30000;
int  __ccitt_t31 = 10000;
int  __ccitt_t32 = 5000;
int  __ccitt_t33 = 60000;
int  __ccitt_t34 = 5000;
int  __ccitt_slt_t1 = 4000;
int  __ccitt_slt_t2 = 30000;

/*
 * behavior control
 */
ITS_BOOLEAN MTP3_CCITT_HandleSpareNIC = ITS_FALSE;
ITS_BOOLEAN MTP3_CCITT_AutomaticTerminalAllocation = ITS_FALSE;
ITS_BOOLEAN MTP3_CCITT_AutomaticDataLinkAllocation = ITS_FALSE;

/*static ITS_BOOLEAN behaviors[MTP3_NUM_BEHAVIORS];*/
BEHAVIORS_DECL_SUBSYS(CCITT_MTP3, NULL);

/*static ITS_TIME timers[MTP3_NUM_TIMERS];*/
TIMERS_DECL_SUBSYS(CCITT_MTP3, NULL);



/*
 * management class record
 */
static MTP3_MgmtClassRec MTP3_MgmtClassRec_CCITT =
{
    /* core part */
    {
        NULL,                           /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        "CCITT MTP3Mgmt",               /* class name */
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
        &CCITT_MTP3_PEGS,
        &CCITT_MTP3_Behaviors,
        &CCITT_MTP3_Timers,
        CCITT_MTP3_Alarms,

        MTP3_GetGeneralCfg_CCITT,
        MTP3_SetGeneralCfg_CCITT,
        MTP3_GetLinksetEntry_CCITT,
        MTP3_GetAllLinksetEntries_CCITT,
        MTP3_SetLinksetEntry_CCITT,
        MTP3_RemLinksetEntry_CCITT,
        MTP3_GetLinksetStatus_CCITT,
        MTP3_GetLinkInfo_CCITT,
        MTP3_GetAllLinkEntries_CCITT,
        MTP3_SetLinkEntry_CCITT,
        MTP3_RemLinkEntry_CCITT,
        MTP3_GetLinkStatus_CCITT,
        MTP3_GetRouteEntry_CCITT,
        MTP3_GetAllRouteEntries_CCITT,
        MTP3_SetRouteEntry_CCITT,
        MTP3_RemRouteEntry_CCITT,
        MTP3_GetRouteStatus_CCITT,
        MTP3_GetAllDestinationEntries_CCITT,
        MTP3_SetDestinationEntry_CCITT,
        MTP3_RemDestinationEntry_CCITT,
        MTP3_GetDestinationStatus_CCITT,
        MTP3_GetGeneralStats_CCITT,
        MTP3_GetLinksetStats_CCITT,
        MTP3_GetLinkStats_CCITT,
        MTP3_GetRouteStats_CCITT,
        MTP3_GetDestinationStats_CCITT
    }
};

ITSSS7DLLAPI ITS_Class MTP3_MgmtClass_CCITT =
    (ITS_Class)&MTP3_MgmtClassRec_CCITT;


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
STPFunction_CCITT()
{
    return BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction);
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
STPFunctionSet_CCITT(ITS_BOOLEAN isStp)
{
    BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction,
                           isStp);

    BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS);

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
MTP3_EnableUserPart(ITS_OCTET up, ITS_USHORT id)
{
    MTP3_DEBUG(("MTP3_EnableUserPart_CCITT: up: %02x  !!!!id: %04x \n", up, id));

    if (MUTEX_AcquireMutex(&mtp3Gate) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_EnableUserPart_CCITT: Couldn't acquire mutex.\n"));
  
        return (ITS_EBADMUTEX);
    }

    if (up > MTP3_MAX_USER_PARTS)
    {
        MTP3_ERROR(("MTP3_EnableUserPart_CCITT: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&mtp3Gate);

        return (ITS_EINVALIDARGS);
    }

    userParts[up] = id;

    MTP3_DEBUG(("MTP3_EnableUserPart_CCITT: up %02x  !!!id: %04x enabled\n", up, id));

    PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_USERPART_ENABLE);

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
MTP3_DisableUserPart(ITS_OCTET up)
{
    MTP3_DEBUG(("MTP3_DisableUserPart_CCITT: up: %02x\n", up));

    if (MUTEX_AcquireMutex(&mtp3Gate) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_DisableUserPart_CCITT: Couldn't acquire mutex.\n"));

        return (ITS_EBADMUTEX);
    }

    if (up > MTP3_MAX_USER_PARTS)
    {
        MTP3_ERROR(("MTP3_DisableUserPart_CCITT: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&mtp3Gate);

        return (ITS_EINVALIDARGS);
    }

    userParts[up] = ITS_FALSE;

    MTP3_DEBUG(("MTP3_DisableUserPart_CCITT: up %02x disabled\n", up));

    PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_USERPART_DISABLE);

    return MUTEX_ReleaseMutex(&mtp3Gate);
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
ITSSS7DLLAPI ITS_USHORT
MTP3_UserPartOwner(ITS_OCTET up)
{
    volatile ITS_USHORT id;

    MTP3_DEBUG(("MTP3_UserPartOwner_CCITT: up: %02x\n", up));

    if (MUTEX_AcquireMutex(&mtp3Gate) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_UserPartOwner_CCITT: Couldn't acquire mutex.\n"));

        return (ITS_INVALID_SRC);
    }

    if (up > MTP3_MAX_USER_PARTS)
    {
        MTP3_ERROR(("MTP3_UserPartOwner_CCITT: User Part out of range.\n"));

        MUTEX_ReleaseMutex(&mtp3Gate);

        return (ITS_INVALID_SRC);
    }

    id = userParts[up];

    MTP3_DEBUG(("MTP3_UserPartOwner_CCITT: up %02x id %04x\n", up, id));

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
MTP3_GetGeneralCfg_CCITT()
{
    MTP3GeneralCfg *ret;

    ret = calloc(1, sizeof(MTP3GeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }
    ret->traceOn = (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                   MTP3_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      2))) ||
                  (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                   MTP3_TRACE_EVENT) &&
                    (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      2))) ||
                   (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_ABORT) &&
                    (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      0) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      1) ||
                     TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      2)));
    ret->alarmLevel = MTP3_AlarmLevel_CCITT;

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
MTP3_SetGeneralCfg_CCITT(MTP3GeneralCfg *data)
{
    MTP3_AlarmLevel_CCITT = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_EVENT_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_EVENT_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
#if 0
/* Fix for Bug 490 */
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
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
MTP3_GetLinksetEntry_CCITT(ITS_UINT linksetNumber)
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
MTP3_GetAllLinksetEntries_CCITT(ITS_UINT* numEntries,
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
MTP3_SetLinksetEntry_CCITT(MTP3LinksetInfo* data)
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
MTP3_RemLinksetEntry_CCITT(MTP3LinksetInfo* data)
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
MTP3_GetLinksetStatus_CCITT(ITS_UINT linksetNumber,
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
MTP3_GetLinkInfo_CCITT(ITS_UINT ls, ITS_UINT lnk)
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
MTP3_GetAllLinkEntries_CCITT(ITS_UINT* numEntries,
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
MTP3_SetLinkEntry_CCITT(MTP3LinkInfo* data)
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
MTP3_RemLinkEntry_CCITT(MTP3LinkInfo* data)
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
MTP3_GetLinkStatus_CCITT(ITS_UINT ls, ITS_UINT lnk,
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
MTP3_GetRouteEntry_CCITT(ITS_UINT dpc, ITS_OCTET ni,
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
MTP3_GetAllRouteEntries_CCITT(ITS_UINT* numEntries,
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
MTP3_SetRouteEntry_CCITT(MTP3RouteInfo* data)
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
MTP3_RemRouteEntry_CCITT(MTP3RouteInfo* data)
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
MTP3_GetRouteStatus_CCITT(ITS_UINT dpc, ITS_OCTET ni,
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
MTP3_GetAllDestinationEntries_CCITT(ITS_UINT* numEntries, 
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
MTP3_SetDestinationEntry_CCITT(MTP3DestinationInfo* data)
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
MTP3_RemDestinationEntry_CCITT(MTP3DestinationInfo* data)
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
MTP3_GetDestinationStatus_CCITT(ITS_UINT dpc, ITS_OCTET ni, 
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
MTP3_GetGeneralStats_CCITT(ITS_UINT **pegs, ITS_UINT *numPegs)
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
MTP3_GetLinksetStats_CCITT(ITS_UINT linksetNUmber, 
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
MTP3_GetLinkStats_CCITT(ITS_UINT linksetNUmber,
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
MTP3_GetRouteStats_CCITT(ITS_UINT dpc, ITS_OCTET ni,
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
MTP3_GetDestinationStats_CCITT(ITS_UINT dpc, ITS_OCTET ni, 
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
 ****************************************************************************/
static void
MTP3_Pause(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    MTP3_PAUSE_RESUME pause;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Pause_CCITT:\n"));

    /*PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_PAUSE);*/

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_CCITT: link lock failed\n"));
   
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

                for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                     tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                     count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
                {
                    ROUTE_Info *rinfo;
                    ROUTE_MatchInfo minfo;
                    SS7_Destination *dest;
                    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
                    ITS_BOOLEAN allDown = ITS_TRUE;

                    /* select one of concerned destinations */
                    memcpy(&rinfo, tmp->data, sizeof(rinfo));

                    if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                    {
                        continue;
                    }

                    minfo.basic = rinfo->basic;
                    minfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
                    minfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                    minfo.priority = ITS_SS7_DEFAULT_PRI;
                    minfo.sls = ITS_SS7_DEFAULT_SLS;

                    if ((dest = ROUTE_FindBestMatch(&minfo, &whichEntry,
                                                    &firstMatch, &lastMatch,
                                                    &whichLinkCode,
                                                    ITS_TRUE)) == NULL)
                    {
                        MTP3_WARNING(("Configured route not found\n"));

                        continue;
                    }

                    for (i = firstMatch; i <= lastMatch; i++)
                    {
                        if (dest->entries[i]->linkSet->isUp)
                        {
                            allDown = ITS_FALSE;

                            break;
                        }
                    }

                    /* determine if this was the last up route */
                    if (allDown)
                    {
                        MTP3_DEBUG(("MTP3_Pause_CCITT: setting state PC: %08x\n",
                                    rinfo->basic.dpc));

                        MTP3_PC_SET_VALUE(pause.affected, rinfo->basic.dpc);

                        MTP3_Alarm_CCITT(2401, __FILE__, __LINE__,
                                        "affected point code %x", rinfo->basic.dpc);

                        mtp3.sio = link->linkSet->ni;
                        MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                        MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                        MTP3_RL_SET_SLS(mtp3.label, 0);

                        event.src = ITS_MTP3_SRC;
                        MTP3_Encode(&event, MTP3_MSG_PAUSE, &mtp3,
                                    (ITS_OCTET *)&pause, sizeof(MTP3_PAUSE_RESUME));


                        CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                                  (ITS_POINTER)base,
                                                  (ITS_POINTER)&event);

                        ITS_EVENT_TERM(&event);

                        break;
                    }
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
MTP3_Resume(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    MTP3_PAUSE_RESUME resume;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Resume_CCITT:\n"));

    /*PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME);*/

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_CCITT: link lock failed\n"));

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
             * if link set was previously up, walk routes looking for dests to pause.
             */
            if (!wasUp && isUp)
            {
                DSMQUEUE_Entry *tmp;
                ITS_UINT count;

                for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                     tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                     count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
                {
                    ROUTE_Info *rinfo;
                    ROUTE_MatchInfo minfo;
                    SS7_Destination *dest;
                    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
                    ITS_BOOLEAN firstUp = ITS_TRUE;

                    /* select one of concerned destinations */
                    memcpy(&rinfo, tmp->data, sizeof(rinfo));

                    if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                    {
                        continue;
                    }

                    minfo.basic = rinfo->basic;
                    minfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
                    minfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                    minfo.priority = ITS_SS7_DEFAULT_PRI;
                    minfo.sls = ITS_SS7_DEFAULT_SLS;

                    if ((dest = ROUTE_FindBestMatch(&minfo, &whichEntry,
                                                    &firstMatch, &lastMatch,
                                                    &whichLinkCode,
                                                    ITS_TRUE)) == NULL)
                    {
                        MTP3_WARNING(("Configured route not found\n"));

                        continue;
                    }

                    for (i = firstMatch; i <= lastMatch; i++)
                    {
                        if (dest->entries[i]->linkSet->linkSet != link->linkSet->linkSet &&
                            dest->entries[i]->linkSet->isUp)
                        {
                            firstUp = ITS_FALSE;

                            break;
                        }
                    }

                    /* determine if this is a newly up route */
                    if (firstUp)
                    {
                        MTP3_DEBUG(("MTP3_Resume_CCITT: setting state PC: %08x\n",
                                    rinfo->basic.dpc));

                        MTP3_PC_SET_VALUE(resume.affected, rinfo->basic.dpc);

                        MTP3_Alarm_CCITT(2402, __FILE__, __LINE__,
                                        "affected point code %x", rinfo->basic.dpc);

                        mtp3.sio = link->linkSet->ni;
                        MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                        MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                        MTP3_RL_SET_SLS(mtp3.label, 0);

                        event.src = ITS_MTP3_SRC;
                        MTP3_Encode(&event, MTP3_MSG_RESUME, &mtp3,
                                    (ITS_OCTET *)&resume, sizeof(MTP3_PAUSE_RESUME));


                        CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                                  (ITS_POINTER)base,
                                                  (ITS_POINTER)&event);

                        ITS_EVENT_TERM(&event);

                        break;
                    }
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
MTP3_Status(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    ITS_OCTET congLevel = 0;
    MTP3_STATUS status;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Status_CCITT:\n"));

    /*PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_STATUS);*/

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Status_CCITT: link lock failed\n"));

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
                    MTP3_DEBUG(("MTP3_Status_CCITT: get congestion PC: %08x SSN: %02xn\n",
                                rinfo->basic.dpc, rinfo->basic.criteria.ssn));

                    MTP3_PC_SET_VALUE(status.affected, rinfo->basic.dpc);
                    status.congLevel = congLevel;

                    mtp3.sio = 0;
                    MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                    MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                    MTP3_RL_SET_SLS(mtp3.label, 0);

                    event.src = ITS_MTP3_SRC;
                    MTP3_Encode(&event, MTP3_MSG_STATUS, &mtp3,
                                (ITS_OCTET *)&status, sizeof(MTP3_STATUS));

                    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
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
    if (TRANSPORT_MASK(tc) & ITS_SS7_MASK_CCITT &&
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
    if (TRANSPORT_MASK(tc) & ITS_SS7_MASK_CCITT &&
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
static void
CloseAlarmFile(char *data)
{

#if !defined(NO_FILESYSTEM)
    fclose((FILE *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput));
#endif

    TRACE_OUTPUT_DATA(mtp3AlarmsOutput) = NULL;

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
MTP3_Alarms_CCITT(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData
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

    if (alarm.id >= CCITT_MTP3_ALARM_START &&
        alarm.id <= CCITT_MTP3_ALARM_END)
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
                alarm.id, "",
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
    "T27"                         
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
    "MSG_FOR_INVALID_DEST",
    "UNINHIBIT_IMPOSSIBLE",  
    "RESTART",
    "INHIBIT_LINK",
    "DEACTIVATE_LINK",
    "DEACTIVATE_LINK_SET",
    "ACTIVATE_LINK",
    "ACTIVATE_LINK_SET"
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
MTP3_FuncEntry_CCITT(MTP3_SubSystems subsystem, MTP3_SubSystems src,
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

    TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG,
              ("%s", TRACE_Header(MTP3_CCITT_TraceData, file, line)));
    TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG,
              ("  Sub: %s From: %s Trigger: %s\n",
                sub, from, trig));
    TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG,
              ("  LinkSet/Code: %d:%d len: %d\n",
               linkSet, linkCode, len));

    if (sif == NULL)
    {
        TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG,
                  ("  SIF: (null)\n"));
    }
    else
    {
        for (idx = 0; idx < len; idx++)
        {
            TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG,
                      ("%02x ", sif[idx]));

            if (!((idx+1) % 25))
            {
                TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG,
                          ("\n"));
            }
        }
        if ((idx+1) % 25)
        {
            TRACE_RAW(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, ("\n"));
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
    if (TRANSPORT_RES(__MTP3_CCITT_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__MTP3_CCITT_RcvQueue);
        char *name = TRANSPORT_NAME(__MTP3_CCITT_RcvQueue);

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
        CCITT_MTP3_Timers.numTimers = MTP3_NUM_TIMERS;

        CCITT_MTP3_Timers.timers = TIMERS_InitSharedTimerValues (
            DSM_MGMT_REC_CCITT_MTP3_TIMERS, MTP3_NUM_TIMERS);


        if (RESFILE_GetKeyValueOf(res, name, MTP3_T1_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t1 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T2_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t2 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T3_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t3 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T4_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t4 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T5_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t5 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T6_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t6 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T7_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t7 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T8_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t8 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T9_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t9 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T10_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t10 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T11_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t11 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T12_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t12 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T13_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t13 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T14_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t14 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T15_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t15 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T16_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t16 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T17_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t17 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T18_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t18 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T19_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t19 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T20_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t20 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T21_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t21 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T22_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t22 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T23_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t23 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T24_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t24 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T25_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t25 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T26_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t26 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T27_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t27 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T28_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t28 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T29_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t29 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T30_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t30 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T31_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t31 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T32_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t32 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T33_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t33 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_T34_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_t34 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_SLT_T1_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_slt_t1 = RESFILE_ParseNum(value);
        }
        if (RESFILE_GetKeyValueOf(res, name, MTP3_SLT_T2_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            __ccitt_slt_t2 = RESFILE_ParseNum(value);
        }

        /*
         * Set and Commit Timer values
         */

        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T1, __ccitt_t1);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T2, __ccitt_t2);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T3, __ccitt_t3);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T4, __ccitt_t4);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T5, __ccitt_t5);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T6, __ccitt_t6);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T7, __ccitt_t7);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T8, __ccitt_t8);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T9, __ccitt_t9);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T10, __ccitt_t10);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T11, __ccitt_t11);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T12, __ccitt_t12);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T13, __ccitt_t13);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T14, __ccitt_t14);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T15, __ccitt_t15);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T16, __ccitt_t16);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T17, __ccitt_t17);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T18, __ccitt_t18);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T19, __ccitt_t19);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T20, __ccitt_t20);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T21, __ccitt_t21);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T22, __ccitt_t22);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T23, __ccitt_t23);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T24, __ccitt_t24);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T25, __ccitt_t25);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T26, __ccitt_t26);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T27, __ccitt_t27);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T28, __ccitt_t28);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T29, __ccitt_t29);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T30, __ccitt_t30);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T31, __ccitt_t31);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T32, __ccitt_t32);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T33, __ccitt_t33);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_T34, __ccitt_t34);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_SLT_T1, __ccitt_slt_t1);  
        TIMERS_SetTimerValue(&CCITT_MTP3_Timers, MTP3_TIMER_SLT_T2, __ccitt_slt_t2);  

        TIMERS_CommitSharedTimerValues(DSM_MGMT_REC_CCITT_MTP3_TIMERS);

        /* 
         * Initialize behavior control
         */

         CCITT_MTP3_Behaviors.numBehaviors = MTP3_NUM_BEHAVIORS;

         CCITT_MTP3_Behaviors.behaviors = 
              BEHAVIORS_InitSharedBehaviors(DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS,
                                            MTP3_NUM_BEHAVIORS);

         BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction,
                                ITS_FALSE);

         BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_fullRestartNeeded,
                                 ITS_TRUE);

         BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_spRestarting,
                                ITS_FALSE);

         BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_sendingStatus,
                                ITS_FALSE);

         BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS);


        if (RESFILE_GetKeyValueOf(res, name, SPARE_NIC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            MTP3_CCITT_HandleSpareNIC = strstr(value, "yes") != NULL ||
                                        strstr(value, "YES") != NULL;
        }
        if (RESFILE_GetKeyValueOf(res, name, STP_FUNCTION_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN isStpFunction = ITS_FALSE;

            isStpFunction = strstr(value, "yes") != NULL ||
                            strstr(value, "YES") != NULL;

            STPFunctionSet_CCITT(isStpFunction);

        }
        if (RESFILE_GetKeyValueOf(res, name, AUTO_TERM_ALLOC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            MTP3_CCITT_AutomaticTerminalAllocation =
                                        strstr(value, "yes") != NULL ||
                                        strstr(value, "YES") != NULL;
        }
        if (RESFILE_GetKeyValueOf(res, name, AUTO_LINK_ALLOC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            MTP3_CCITT_AutomaticDataLinkAllocation =
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
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_CRITICAL_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                          MTP3_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
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
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_ERROR_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                          MTP3_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
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
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_WARNING_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                          MTP3_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
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
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_DEBUG_STRING,
                                           MTP3_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                          MTP3_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
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
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP3_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
             else
            {
                TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                           MTP3_EVENT_STRING,
                                           MTP3_FILE_STRING, ITS_FALSE);
            }
                                                                                           
            if (std || fil)
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                          MTP3_EVENT_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
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
IMTP3_Initialize_CCITT(ITS_SS7_HANDLE handle)
{
    int i, j;
    ITS_Class dbClass;

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;
    stopped = ITS_FALSE;

    if ((MTP3_CCITT_TraceData = TRACE_Constructor("ITU-MTP3",
                                                  MTP3_TraceMap, 5)) == NULL)
    {
        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if (MUTEX_CreateMutex(&mtp3Gate, 0) != ITS_SUCCESS)
    {
        MTP3_ERROR(("MTP3_Intialize: couldn't create mutex\n"));

        started = ITS_FALSE;

        return (ITS_EBADMUTEX);
    }

    CALLBACK_AddCallback(TRANSPORT_registrations, MTP3_Register, NULL);
    CALLBACK_AddCallback(TRANSPORT_deregistrations, MTP3_Deregister, NULL);
    
    /* register Alarm Callback */
    /* CALLBACK_AddCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL); */


    if ((__MTP3_CCITT_RcvQueue = TQUEUETRAN_CreateTransport("ITU-MTP3",
                                                            ITS_MTP3_SRC,
                                                            ITS_MTP3)) == NULL)
    {
        MTP3_CRITICAL(("MTP3_Initialize: couldn't create transport\n"));

        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Deregister, NULL);

        CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL);

        MUTEX_DeleteMutex(&mtp3Gate);

        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    /* read the INI */
    InitSettings();

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

    if ((mtp3Thread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        MTP3_CRITICAL(("MTP3_Initialize: couldn't create thread array\n"));

        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
        CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Deregister, NULL);
        CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL);

        MUTEX_DeleteMutex(&mtp3Gate);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if ( (routeRWLock = ROUTE_RWLockCreate() ) == NULL)
    {
        MTP3_ERROR(("Cannot Create ROUTE Reader/Writer Lock."));
        return ITS_ENOMEM;
    }


    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&mtp3Thread[i], 0, CCITT_MTP3Thread,
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
            CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL);

            MUTEX_DeleteMutex(&mtp3Gate);

            started = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    //if (ITS_FindFeature("SCTP") == NULL)
    {
        if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
        {
            DBC_AddDoCommand(MTP3_Console_CCITT);
        }
    }

    PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE);

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
 *
 ****************************************************************************/
void
IMTP3_Terminate_CCITT(ITS_SS7_HANDLE handle)
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
            DBC_RemDoCommand(MTP3_Console_CCITT);
        }
    }

    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
    }

    PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE);

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&mtp3Thread[0], &status);

        THREAD_DeleteThread(&mtp3Thread[0]);
    }

    free(mtp3Thread);

    ITS_C_ASSERT(__MTP3_CCITT_RcvQueue != NULL);
    TQUEUETRAN_DeleteTransport(__MTP3_CCITT_RcvQueue);

    CALLBACK_RemCallback(TRANSPORT_deregistrations, MTP3_Deregister, NULL);
    CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
    CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL);

    MUTEX_DeleteMutex(&mtp3Gate);

    TRACE_Destructor(MTP3_CCITT_TraceData);
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
 *  According to spec Q.704 the pegs are incremented for ITU .
 *  The following is the mapping between ITU and ANSI timers.
 *
 *  ITU                 ANSI 
 * 1-17 ---------------  1-17  
 *  T18 ---------------  T22,T23
 *  T19 ---------------  None
 *  T20 ---------------  T24
 *  T21 ---------------  T28
 *  T22 ---------------  T20
 *  T23 ---------------  T21
 *  T24 ---------------  None
 *
 ****************************************************************************/
static int
HandleTimerEvent(ITS_TimerData *td)
{
    MTP3_TimerContext ctxt;
    MTP3_HEADER mtp3;
    ITS_EVENT ev;
    int ret;

    memcpy(&ctxt, td->context, sizeof(MTP3_TimerContext));

    ret = ITS_SUCCESS;

    switch (ctxt.timerId)
    {
    case MTP3_T1:
        /* Increament peg for Timer T1 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T1_EXPIRED);

        /* Delay to avoid message re-sequencing on changeover */
        return TCOC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T1,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T2:
        /* Increament peg for Timer T2 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T2_EXPIRED);

        /* Waiting for changeover acknowledgment */
        return TCOC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T2,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T3:
        /* Increament peg for Timer T3 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T3_EXPIRED);

        /* Time controlled diversion -- delay to avoid
         * mis-sequencing on changeback */
        return TCBC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T3,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T4:
        /* Increament peg for Timer T4 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T4_EXPIRED);

        /* Waiting for changeback acknowledgment (first attempt) */
        return TCBC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T4,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T5:
        /* Increament peg for Timer T5 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T5_EXPIRED);

        /* Waiting for changeback acknowledgment (second attempt) */
        return TCBC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T5,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T6:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T6 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T6_EXPIRED);


        ret = TCRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T6,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        break;

    case MTP3_T7:
        /* Increament peg for Timer T7 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T7_EXPIRED);

        return LSDA_Main_CCITT(MTP3_TIMER, SLM_TRIGGER_T7,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);
 
    case MTP3_T8:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T8 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T8_EXPIRED);

        ret = RTPC_Main_CCITT(MTP3_TIMER, SRM_TRIGGER_T8,
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

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T10 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T10_EXPIRED);

        ret = RSRT_Main_CCITT(MTP3_TIMER, SRM_TRIGGER_T10,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T11:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T11 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T11_EXPIRED);

        ret = TSRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T11,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T12:
        /* Increament peg for Timer T12 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T12_EXPIRED);

        return TLAC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T12,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T13:
        /* Increament peg for Timer T13 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T13_EXPIRED);

        return TLAC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T13,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T14:
        /* Increament peg for Timer T14 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T14_EXPIRED);

        return TLAC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T14,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T15:
        /* Waiting to repeat signalling route set congestion test */
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T15 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T15_EXPIRED);

        ret = TRCC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T11,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_SET);
 
        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T16:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T16 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T16_EXPIRED);

        ret = RCAT_Main_CCITT(MTP3_TIMER, SRM_TRIGGER_T16,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T17:
        /* Increament peg for Timer T17 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T17_EXPIRED);

        return LSAC_Main_CCITT(MTP3_TIMER, SLM_TRIGGER_T17,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);
    case MTP3_T18:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T18 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T18_EXPIRED); */

        ret = RTRC_Main_CCITT(MTP3_TIMER, SRM_TRIGGER_T18,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T19:
        /* Increament peg for Timer T19 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T19_EXPIRED); */

        return LSAC_Main_CCITT(MTP3_TIMER, SLM_TRIGGER_T19,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);
 
    case MTP3_T20:
        /* Increament peg for Timer T22 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T22_EXPIRED);

        /* Increament peg for Timer T20 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T20_EXPIRED); */

        return TLAC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T20,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T21:
        /* Increament peg for Timer T23 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T23_EXPIRED);

        /* Increament peg for Timer T21 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T21_EXPIRED); */

        return TLAC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T21,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T22:
        /* Increament peg for Timer T18 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T18_EXPIRED);

        /* Increament peg for Timer T22 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T22_EXPIRED); */

        return TPRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T22,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T23:
        /* Increament peg for Timer T18 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T18_EXPIRED);

        /* Increament peg for Timer T23 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T23_EXPIRED); */

        return TPRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T23,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T24:
        /* Increament peg for Timer T20 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T20_EXPIRED);

        /* Increament peg for Timer T24 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T24_EXPIRED); */

        return TPRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T24,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);
    case MTP3_T25:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T25 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T25_EXPIRED); */

        return TSRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T25,
                               ev.data, ev.len,
                               ctxt.data.routeInfo.linkSet,
                               ITS_SS7_DEFAULT_LINK_SET);

    case MTP3_T26:
        /* Increament peg for Timer T26 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T26_EXPIRED); */

        return TPRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T26,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T27:
        /* Increament peg for Timer T27 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T27_EXPIRED); */

        return TPRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T27,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

    case MTP3_T28:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T21 expired */
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T21_EXPIRED);

        /* Increament peg for Timer T28 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T28_EXPIRED); */

        ret = TSRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T28,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T29:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T29 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T29_EXPIRED); */

        ret = TSRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T29,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T30:
        MTP3_HDR_SET_SIO(mtp3, ctxt.data.routeInfo.sio);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ctxt.data.routeInfo.pointCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        /* Increament peg for Timer T30 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T30_EXPIRED); */

        ret = TSRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T30,
                              ev.data, ev.len,
                              ctxt.data.routeInfo.linkSet,
                              ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case MTP3_T31:

        /* Increament peg for Timer T31 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T31_EXPIRED); */

        return TSRC_Main_CCITT(MTP3_TIMER, STM_TRIGGER_T31,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T32:
        /* Increament peg for Timer T32 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T32_EXPIRED); */

        return LSAC_Main_CCITT(MTP3_TIMER, SLM_TRIGGER_T32,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T33:
        /* Increament peg for Timer T33 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T33_EXPIRED); */

        return LSAC_Main_CCITT(MTP3_TIMER, SLM_TRIGGER_T33,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_T34:
        /* Increament peg for Timer T34 expired */
        /* PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_T34_EXPIRED); */

        return LSAC_Main_CCITT(MTP3_TIMER, SLM_TRIGGER_T34,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_SLT_T1:
        return SLTC_Main_CCITT(MTP3_TIMER, SLT_TRIGGER_T1,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);

    case MTP3_SLT_T2:
        return SLTC_Main_CCITT(MTP3_TIMER, SLT_TRIGGER_START_TEST,
                               NULL, 0,
                               ctxt.data.linkInfo.linkSet,
                               ctxt.data.linkInfo.linkCode);
        break;

    default:
        MTP3_DEBUG(("HandleTimerEvent: Unknown timer id %d\n",
                    ctxt.timerId));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
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

        mtp3 = (MTP3_HEADER *)&sif[1];
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
 ****************************************************************************/
THREAD_RET_TYPE
CCITT_MTP3Thread(void *arg)
{
    ITS_EVENT mtp3Event;
    ITS_BOOLEAN cont;
    ITS_TimerData *td;

    memset(&mtp3Event, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__MTP3_CCITT_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__MTP3_CCITT_RcvQueue))
                                                        (__MTP3_CCITT_RcvQueue,
                                                         &mtp3Event)
           == ITS_SUCCESS)
    {
        if (TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT))
        {
            if ((mtp3Event.src != ITS_MTP3_SRC) &&
                (mtp3Event.src != ITS_TIMER_SRC))
            {
                ITS_INT output = 0;
                if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      0))
                {
                    output += 1;
                }
                if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      1))
                {
                    output += 2;
                }
                CTF_TraceEvent(mtp3Event.src, ITS_MTP3_CCITT_SRC,
                    output, &mtp3Event);
            }
        }

        switch (mtp3Event.src)
        {
        case ITS_MTP3_SRC:
            MTP3_DEBUG(("MTP3_Main: handle termination event.\n"));

            TRANSPORT_IS_ACTIVE(__MTP3_CCITT_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_SCCP_SRC:
        case ITS_ISUP_SRC:
            MTP3_DEBUG(("MTP3_Main: handle L4 msg.\n"));

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

            SMH_Main_CCITT(MTP3_L4, MTP3_SMH_HMRT,
                           SMH_TRIGGER_L4_L3_MSG,
                           mtp3Event.data, mtp3Event.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ROUTE_UnlockRead(routeRWLock, __MTP3_CCITT_RcvQueue);
            break;

        case ITS_TIMER_SRC:
        {
            MTP3_TimerContext ctxt;
            
            MTP3_DEBUG(("MTP3_Main:handle TIMER msg.\n"));

            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Failed to get route lock\n"));

                break;
            }

            td = (ITS_TimerData *)mtp3Event.data;
            memcpy(&ctxt, td->context, sizeof(MTP3_TimerContext));
            HandleTimerEvent(td);
            
            LINKSET_CommitLinkSet(
                    LINKSET_FindLinkSet(ctxt.data.linkInfo.linkSet));

            
            ROUTE_UnlockWrite(routeRWLock);
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

                SMH_Main_CCITT(MTP3_L4, MTP3_SMH_HMRT,
                               SMH_TRIGGER_L4_L3_MSG,
                               mtp3Event.data, mtp3Event.len,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ROUTE_UnlockRead(routeRWLock, __MTP3_CCITT_RcvQueue );
            }
            else
            {
                ITS_OCTET linkSet, linkCode;
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;

                MTP3_DEBUG(("MTP3_Main: handle L2 msg.\n"));

                if (MTP2_ReceiveData_CCITT(&mtp3Event, &linkSet, &linkCode,
                                           buf, &len) != ITS_SUCCESS)
                {
                    MTP3_WARNING(("Failed to receive L2 data\n"));

                    MTP3_Alarm_CCITT(2405, __FILE__, __LINE__, NULL);
                }
                else
                {
                    ITS_BOOLEAN isLockSet = ITS_FALSE;

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


                    SMH_Main_CCITT(MTP3_L2, MTP3_SMH_HMDT,
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
                        ROUTE_UnlockRead(routeRWLock, __MTP3_CCITT_RcvQueue);
                    }

                }
           
            }

            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__MTP3_CCITT_RcvQueue) = ITS_FALSE;

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
ItsEventToMTP3EventRec_CCITT(ITS_EVENT ev)
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
MTP3EventRecToItsEvent_CCITT(MTP3_EventRec evRec)
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

    MTP3_DEBUG(("SetLinkUnavailable: linkCode:%d  nodeId %d\n", 
            link->linkCode, link->dsmNodeId));
 
    if (link->dsmNodeId == concernedNodeId) 
    {
        /* we need to mark this link unavailable */

        MTP3_DEBUG(("Deactivate link %d \n", link->linkCode));

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_OUT_OF_SERVICE;
        ev.data[1] = link->linkSet->linkSet;
        ev.data[2] = link->linkCode; 

        TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

        return ITS_SUCCESS;  
    

    }

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
MTP3_MembershipChangeCallBack_CCITT(ITS_POINTER object, 
                                    ITS_POINTER userData, 
                                    ITS_POINTER callData)
{

    DSM_MembershipChangeCbData *membershipChangeCbData = 
                        (DSM_MembershipChangeCbData *) callData;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    switch (membershipChangeCbData->membershipChangeType)
    {

    case DSM_FT_GROUP_MEMBER_JOIN:   

        /* Activate links owned by the concerned node */
        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_JOIN nodeID: %d\n", concernedNodeId));

        break;

   
    case DSM_FT_GROUP_MEMBER_LEAVE: 

        /* Deactivate links owned by the concerned node */
        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_LEAVE nodeID: %d\n",concernedNodeId));
        DSM_TableIterate(DSM_Mtp3FtGroupId,
                         DSM_TABLE_LINKS, callData, NULL, SetLinkUnavailable);  
        break;

    
    case DSM_FT_GROUP_MEMBER_DEAD:

        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_DEAD nodeID: %d\n",concernedNodeId));

        break;

    case DSM_FT_GROUP_MEMBER_ALIVE:

        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_ALIVE nodeID: %d\n",concernedNodeId));

        break;

    default:

        MTP3_DEBUG(("DSM_FT_GROUP: Unknown Event nodeID: %d\n",concernedNodeId));
        break;
  
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
int 
MTP3_TransportPostInit_CCITT(TPOOL_THREAD *thr , ITS_HANDLE h)
{
   
    ITS_EVENT ev;
    TRANSPORT_Control *tc = (TRANSPORT_Control *) h;
    SS7_LinkPtr link = NULL;
    int i;

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

        TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for itu mtp3.
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
 ****************************************************************************/

int
INTELLINET_MTP3_Commit_CCITT(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = MTP3_CCITT_TraceData;

    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    fprintf(fp,"\t\t\t\t<StackTrace>\n");

    for (count = 0; count < TRACE_DATA_NUM_LEVELS(td); count++)
    {
        fprintf(fp,"\t\t\t\t\t<%s output=\"%s\"/>\n",
                TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                (TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[0]->trace.isEnabled)?
                TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[0]->trace.name : "");
        fprintf(fp,"\t\t\t\t\t<%s output=\"%s\"/>\n",
                TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                (TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[1]->trace.isEnabled)?
                TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[1]->trace.name : "");
    }

    fprintf(fp,"\t\t\t\t</StackTrace>\n");
    fprintf(fp,"\t\t\t\t<Timers\n");

    for (count = 0; count < (int)CCITT_MTP3_Timers.numTimers; count++)
    {
        fprintf(fp,"\t\t\t\t\t%s = \"%d\"\n",MTP3_CCITT_Timers[count],
                                             CCITT_MTP3_Timers.timers[count]);
    }

    fprintf(fp,"\t\t\t\t/>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\tstpFunction = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_stpFunction) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tfullRestartNeeded = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_fullRestartNeeded) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tspRestarting = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_spRestarting) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tsendingStatus = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_sendingStatus) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}

