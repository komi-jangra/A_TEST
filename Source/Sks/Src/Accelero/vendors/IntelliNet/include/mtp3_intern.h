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
 *  ID: $Id: mtp3_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/25 06:06:56  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.2  2007/04/17 08:25:25  ashutosh.singh
 * LOG: logger lib related  changes
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2  2005/04/07 07:25:43  snagesh
 * LOG: Modification for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1.2.2.8.4  2005/01/31 10:42:44  snagesh
 * LOG: Moved MTP3 management data from ss7_mgmt.h
 * LOG:
 * LOG: Revision 7.1.4.1.2.2.8.3  2005/01/05 10:47:12  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.1.4.1.2.2.8.2  2005/01/04 13:45:43  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.1.4.1.2.2.8.1  2004/12/16 15:02:01  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.4.1.2.2  2004/08/10 11:50:59  kannanp
 * LOG: Changes for MTP3 pegs & alarms - propagated from TCS.
 * LOG:
 * LOG: Revision 7.1.4.1.2.1  2004/01/30 05:04:08  sjaddu
 * LOG: Added inter node string for active-backup config.
 * LOG:
 * LOG: Revision 7.1.4.1  2003/11/13 12:13:05  kannanp
 * LOG: MTP3 MML API.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.10  2002/08/22 20:51:23  omayor
 * LOG: If defined PRC then FAMILY_ITU becomes FAMILY_CHINA. This was needed to
 * LOG: substitute the ITU family with CHINA in the routing subsystem calls.
 * LOG:
 * LOG: Revision 6.9  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.8  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.7  2002/06/13 20:28:53  ttipatre
 * LOG: adding its_pegs.h file
 * LOG:
 * LOG: Revision 6.6  2002/05/15 15:05:54  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.5  2002/04/29 21:23:21  randresol
 * LOG: Add InterNode processing and shared booleans
 * LOG:
 * LOG: Revision 6.4  2002/03/26 18:12:40  randresol
 * LOG: Add conversion functions: ITS_EVENT <--> CO/CB Queue Entry
 * LOG:
 * LOG: Revision 6.3  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2002/02/01 22:12:26  mmiers
 * LOG: ISUP integration
 * LOG:
 * LOG: Revision 5.38  2002/02/01 21:57:12  mmiers
 * LOG: Missing include, corrections.
 * LOG:
 * LOG: Revision 5.37  2002/01/29 19:56:41  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.36  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.35  2001/12/11 23:49:53  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.34  2001/12/06 22:39:05  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.33  2001/11/22 00:05:27  mmiers
 * LOG: Todays fixes.
 * LOG:
 * LOG: Revision 5.32  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.31  2001/11/06 21:55:32  mmiers
 * LOG: More changes for CB.
 * LOG:
 * LOG: Revision 5.30  2001/11/02 23:03:32  mmiers
 * LOG: Convert to new event queuing.
 * LOG:
 * LOG: Revision 5.29  2001/10/30 00:16:10  mmiers
 * LOG: Today's debugging session.  Looks close.
 * LOG:
 * LOG: Revision 5.28  2001/10/24 22:16:38  mmiers
 * LOG: Add current route logic.
 * LOG:
 * LOG: Revision 5.27  2001/10/04 21:31:34  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 5.26  2001/10/03 22:16:39  mmiers
 * LOG: Debugging additions.
 * LOG:
 * LOG: Revision 5.25  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.24  2001/09/26 22:43:14  mmiers
 * LOG: Add checking to SLM
 * LOG:
 * LOG: Revision 5.23  2001/09/26 21:28:44  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.22  2001/09/17 23:43:37  mmiers
 * LOG: Walkthroughs.
 * LOG:
 * LOG: Revision 5.21  2001/09/14 17:38:53  rsonak
 * LOG: Changeback code is an ITS_OCTET, so max 255
 * LOG:
 * LOG: Revision 5.20  2001/09/13 15:50:30  mmiers
 * LOG: Arg format.
 * LOG:
 * LOG: Revision 5.19  2001/09/12 22:53:59  mmiers
 * LOG: TPRC
 * LOG:
 * LOG: Revision 5.18  2001/09/12 22:02:45  rsonak
 * LOG: Solidify TLAC
 * LOG:
 * LOG: Revision 5.17  2001/09/12 21:06:03  mmiers
 * LOG: Today's installment.
 * LOG:
 * LOG: Revision 5.16  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.15  2001/09/11 20:14:15  mmiers
 * LOG: SRM is as done as far as I can get it.
 * LOG:
 * LOG: Revision 5.14  2001/09/06 15:33:32  mmiers
 * LOG: Cleanup.  Add reserved NI use to TCAP.
 * LOG:
 * LOG: Revision 5.13  2001/09/05 23:05:45  mmiers
 * LOG: Working MTP2 into the scene.
 * LOG:
 * LOG: Revision 5.12  2001/08/31 14:22:10  mmiers
 * LOG: Brainstorming fixes.
 * LOG:
 * LOG: Revision 5.11  2001/08/30 19:29:44  mmiers
 * LOG: Work on SRM
 * LOG:
 * LOG: Revision 5.10  2001/08/28 21:25:50  rsonak
 * LOG: More triggers
 * LOG:
 * LOG: Revision 5.9  2001/08/28 21:04:45  mmiers
 * LOG: Merge.
 * LOG:
 * LOG: Revision 5.8  2001/08/28 20:47:49  mmiers
 * LOG: More MTP3 work
 * LOG:
 * LOG: Revision 5.7  2001/08/27 22:57:05  mmiers
 * LOG: Updates from ANSI-96 SDL.
 * LOG:
 * LOG: Revision 5.6  2001/08/27 19:34:55  mmiers
 * LOG: Revert to old args.
 * LOG:
 * LOG: Revision 5.5  2001/08/23 23:03:37  rsonak
 * LOG: TLAC sheet 6
 * LOG:
 * LOG: Revision 5.4  2001/08/22 17:18:52  mmiers
 * LOG: Finish typing the STM functions.
 * LOG:
 * LOG: Revision 5.3  2001/08/22 17:01:01  mmiers
 * LOG: Snapshot (arg types for STM).
 * LOG:
 * LOG: Revision 5.2  2001/08/21 20:21:31  mmiers
 * LOG: Start adding in the missing code.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.23  2001/08/14 23:10:47  mmiers
 * LOG: A little cleanup.  Deep thought underway.
 * LOG:
 * LOG: Revision 4.22  2001/08/09 22:25:56  mmiers
 * LOG: TSRC is in.  TLAC is left.
 * LOG:
 * LOG: Revision 4.21  2001/08/09 01:08:04  mmiers
 * LOG: Fill in the rest of STM.  Only TLAC and TSRC left.
 * LOG:
 * LOG: Revision 4.20  2001/08/08 22:35:09  mmiers
 * LOG: Update with STM implementation.
 * LOG:
 * LOG: Revision 4.19  2001/08/08 00:55:03  mmiers
 * LOG: Add timer handling.
 * LOG:
 * LOG: Revision 4.18  2001/08/07 22:01:51  mmiers
 * LOG: Add MTP3 API, some timers.
 * LOG:
 * LOG: Revision 4.17  2001/08/06 23:05:39  rsonak
 * LOG: Added more triggers
 * LOG:
 * LOG: Revision 4.16  2001/08/06 21:28:00  rsonak
 * LOG: Added more STM, SMH triggers
 * LOG:
 * LOG: Revision 4.15  2001/08/03 21:47:03  rsonak
 * LOG: Added MTP3 timers, timer-states and STM triggers/prototypes
 * LOG:
 * LOG: Revision 4.14  2001/08/03 19:51:06  mmiers
 * LOG: Final variable rename.
 * LOG:
 * LOG: Revision 4.13  2001/08/03 19:45:49  mmiers
 * LOG: Rename a few things.
 * LOG:
 * LOG: Revision 4.12  2001/08/03 19:38:25  mmiers
 * LOG: First pass complete.  Off to read specs for a while.
 * LOG:
 * LOG: Revision 4.11  2001/08/02 23:14:32  mmiers
 * LOG: Updates.
 * LOG:
 * LOG: Revision 4.10  2001/08/02 22:02:37  mmiers
 * LOG: Add SLT and MGMT for MTP3.
 * LOG:
 * LOG: Revision 4.9  2001/08/02 21:43:36  mmiers
 * LOG: SMH and SRM are converted to the new form.
 * LOG:
 * LOG: Revision 4.8  2001/08/02 17:00:21  mmiers
 * LOG: Add sif, len to srm and slt mains.
 * LOG:
 * LOG: Revision 4.7  2001/08/02 16:55:35  mmiers
 * LOG: Restructured for new layout.
 * LOG:
 * LOG: Revision 4.6  2001/08/01 21:50:29  mmiers
 * LOG: Note triggers and subsystems.
 * LOG:
 * LOG: Revision 4.5  2001/07/27 15:06:54  mmiers
 * LOG: Start SLM.
 * LOG:
 * LOG: Revision 4.4  2001/07/26 23:20:06  mmiers
 * LOG: More MTP3.  Just about got SRM.
 * LOG:
 * LOG: Revision 4.3  2001/06/07 21:49:43  mmiers
 * LOG: Make sure it builds.
 * LOG:
 * LOG: Revision 4.2  2001/06/07 21:35:06  mmiers
 * LOG: Start MTP3.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2001/04/02 21:20:24  mmiers
 * LOG: Align the string names.
 * LOG:
 * LOG: Revision 3.2  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/07/13 15:40:48  mmiers
 * LOG:
 * LOG:
 * LOG: Make trace file names consistent.
 * LOG:
 * LOG: Revision 1.3  1999/03/17 18:39:51  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.2  1998/11/11 00:45:29  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.1  1998/09/29 01:24:57  mmiers
 * LOG: Implement needed MTP3 functionality.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef MTP3_INTERN_H
#define MTP3_INTERN_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <its_trace.h>

#ident "$Id: mtp3_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#include <ansi/mtp2.h>
#include <itu/mtp2.h>
#include <its_pegs.h>

#include "ss7_pegs.h"
#include "ss7_mgmt.h"
#include "ss7_alarms.h"
#include "ss7_timers.h"
#include "ss7_behaviors.h"

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_msgdef.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif


#if defined(PRC)
#define FAMILY_ITU       FAMILY_CHINA
#endif

#if defined(TTC)
#define FAMILY_ITU       FAMILY_JAPAN
#endif

#define MTP3_INTER_NODE_STRING       "MTP3 InterNode"

#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

/*
 * MTP3 Tracing information
 */
extern TRACE_Data* MTP3_CCITT_TraceData;
extern TRACE_Data* MTP3_ANSI_TraceData;

/*
 * these should be the ONLY globals
 */
extern int  __ansi_t1;
extern int  __ansi_t2;
extern int  __ansi_t3;
extern int  __ansi_t4;
extern int  __ansi_t5;
extern int  __ansi_t6;
extern int  __ansi_t7;
extern int  __ansi_t8;
extern int  __ansi_t9;
extern int  __ansi_t10;
extern int  __ansi_t11;
extern int  __ansi_t12;
extern int  __ansi_t13;
extern int  __ansi_t14;
extern int  __ansi_t15;
extern int  __ansi_t16;
extern int  __ansi_t17;
extern int  __ansi_t18;
extern int  __ansi_t19;
extern int  __ansi_t20;
extern int  __ansi_t21;
extern int  __ansi_t22;
extern int  __ansi_t23;
extern int  __ansi_t24;
extern int  __ansi_t25;
extern int  __ansi_t26;
extern int  __ansi_t27;
extern int  __ansi_t28;
extern int  __ansi_t29;
extern int  __ansi_t30;
extern int  __ansi_t31;
extern int  __ansi_t32;
extern int  __ansi_t33;
extern int  __ansi_t34;
extern int  __ansi_slt_t1;
extern int  __ansi_slt_t2;
extern int  __ansi_leaveTmr;

extern int  __ccitt_t1;
extern int  __ccitt_t2;
extern int  __ccitt_t3;
extern int  __ccitt_t4;
extern int  __ccitt_t5;
extern int  __ccitt_t6;
extern int  __ccitt_t7;
extern int  __ccitt_t8;
extern int  __ccitt_t9;
extern int  __ccitt_t10;
extern int  __ccitt_t11;
extern int  __ccitt_t12;
extern int  __ccitt_t13;
extern int  __ccitt_t14;
extern int  __ccitt_t15;
extern int  __ccitt_t16;
extern int  __ccitt_t17;
extern int  __ccitt_t18;
extern int  __ccitt_t19;
extern int  __ccitt_t20;
extern int  __ccitt_t21;
extern int  __ccitt_t22;
extern int  __ccitt_t23;
extern int  __ccitt_t24;
extern int  __ccitt_t25;
extern int  __ccitt_t26;
extern int  __ccitt_t27;
extern int  __ccitt_t28;
extern int  __ccitt_t29;
extern int  __ccitt_t30;
extern int  __ccitt_t31;
extern int  __ccitt_t32;
extern int  __ccitt_t33;
extern int  __ccitt_t34;
extern int  __ccitt_slt_t1;
extern int  __ccitt_slt_t2;
extern int __ccitt_leaveTmr;
/*
 * behavior control
 */
extern ITS_BOOLEAN MTP3_ANSI_HandleSpareNIC;
extern ITS_BOOLEAN MTP3_ANSI_AutomaticTerminalAllocation;
extern ITS_BOOLEAN MTP3_ANSI_AutomaticDataLinkAllocation;

extern ITS_BOOLEAN MTP3_CCITT_HandleSpareNIC;
extern ITS_BOOLEAN MTP3_CCITT_AutomaticTerminalAllocation;
extern ITS_BOOLEAN MTP3_CCITT_AutomaticDataLinkAllocation;

/*
 * tracing
 */
#define MTP3_TRACE_ABORT     0
#define MTP3_TRACE_ERROR     1
#define MTP3_TRACE_WARNING   2
#define MTP3_TRACE_DEBUG     3
#define MTP3_TRACE_EVENT     4

#if defined(CCITT) || defined(PRC) || defined(TTC)

#ifdef LOGGER_IMR 
#define MTP3_CRITICAL(args) \
    LOG_PRINT_CRITICAL args;
#else
#define MTP3_CRITICAL(args) \
    TRACE(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, args)
#endif

#ifdef LOGGER_IMR 
#define MTP3_ERROR(args) \
    LOG_PRINT_CRITICAL args;
#else
#define MTP3_ERROR(args) \
    TRACE(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, args)
#endif

#ifdef LOGGER_IMR 
#define MTP3_WARNING(args) \
    LOG_PRINT_MAJOR args;
#else
#define MTP3_WARNING(args) \
        TRACE(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, args)
#endif

#ifdef LOGGER_IMR 
#define MTP3_DEBUG(args) \
    LOG_PRINT_DEBUG args;
#else
#define MTP3_DEBUG(args) \
    TRACE(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, args)
#endif



#define MTP3_EVENT(args) \
    TRACE(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, args)


#elif defined(ANSI)
/*****Changes for CRITICAL TRACE*****/
#ifdef LOGGER_IMR 
#define MTP3_CRITICAL(args) \
    LOG_PRINT_CRITICAL args;
#else

#define MTP3_CRITICAL(args) \
    TRACE(MTP3_ANSI_TraceData, MTP3_TRACE_ABORT, args)
#endif
/*****Ends Changes for CRITICAL TRACE*****/

/*****Changes for ERROR TRACE*****/
#ifdef LOGGER_IMR 
#define MTP3_ERROR(args) \
    LOG_PRINT_CRITICAL args;
#else
#define MTP3_ERROR(args) \
    TRACE(MTP3_ANSI_TraceData, MTP3_TRACE_ERROR, args)
#endif
/*****Ends Changes for ERROR  TRACE*****/

/*****Changes for WARNING  TRACE*****/
#ifdef LOGGER_IMR 
#define MTP3_WARNING(args) \
    LOG_PRINT_MAJOR args;
#else
#define MTP3_WARNING(args) \
    TRACE(MTP3_ANSI_TraceData, MTP3_TRACE_WARNING, args)
#endif
/*****Ends Changes for WARNING  TRACE*****/

/*****Changes for DEBUG  TRACE*****/
#ifdef LOGGER_IMR 
#define MTP3_DEBUG(args) \
    LOG_PRINT_DEBUG args;
#else
#define MTP3_DEBUG(args) \
    TRACE(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG, args)
#endif
/*****Ends Changes for DEBUG  TRACE*****/
#define MTP3_EVENT(args) \
    TRACE(MTP3_ANSI_TraceData, MTP3_TRACE_EVENT, args)

#endif

/*
 * resource strings
 */
#define MTP3_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define MTP3_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define MTP3_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define MTP3_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define MTP3_TRACE_EVENT_STRING     ITS_TRACE_EVENT_STRING

#define MTP3_CRITICAL_STRING        ITS_CRITICAL_STRING
#define MTP3_ERROR_STRING           ITS_ERROR_STRING
#define MTP3_WARNING_STRING         ITS_WARNING_STRING
#define MTP3_DEBUG_STRING           ITS_DEBUG_STRING
#define MTP3_EVENT_STRING           ITS_EVENT_STRING

#define MTP3_STDOUT_STRING          ITS_STDOUT_STRING
#define MTP3_SYSLOG_STRING          ITS_SYSLOG_STRING
#define MTP3_FILE_STRING            ITS_FILE_STRING

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define MTP3_TRACE_CRITICAL_FILE    ".itu-mtp3-traceCritical"
#define MTP3_TRACE_ERROR_FILE       ".itu-mtp3-traceError"
#define MTP3_TRACE_WARNING_FILE     ".itu-mtp3-traceWarning"
#define MTP3_TRACE_DEBUG_FILE       ".itu-mtp3-traceDebug"
#define MTP3_TRACE_EVENT_FILE       ".itu-mtp3-traceEvent"

#elif defined(ANSI)

#define MTP3_TRACE_CRITICAL_FILE    ".ansi-mtp3-traceCritical"
#define MTP3_TRACE_ERROR_FILE       ".ansi-mtp3-traceError"
#define MTP3_TRACE_WARNING_FILE     ".ansi-mtp3-traceWarning"
#define MTP3_TRACE_DEBUG_FILE       ".ansi-mtp3-traceDebug"
#define MTP3_TRACE_EVENT_FILE       ".ansi-mtp3-traceEvent"

#endif

#define MTP3_T1_STRING      "T1"
#define MTP3_T2_STRING      "T2"
#define MTP3_T3_STRING      "T3"
#define MTP3_T4_STRING      "T4"
#define MTP3_T5_STRING      "T5"
#define MTP3_T6_STRING      "T6"
#define MTP3_T7_STRING      "T7"
#define MTP3_T8_STRING      "T8"
#define MTP3_T9_STRING      "T9"
#define MTP3_T10_STRING     "T10"
#define MTP3_T11_STRING     "T11"
#define MTP3_T12_STRING     "T12"
#define MTP3_T13_STRING     "T13"
#define MTP3_T14_STRING     "T14"
#define MTP3_T15_STRING     "T15"
#define MTP3_T16_STRING     "T16"
#define MTP3_T17_STRING     "T17"
#define MTP3_T18_STRING     "T18"
#define MTP3_T19_STRING     "T19"
#define MTP3_T20_STRING     "T20"
#define MTP3_T21_STRING     "T21"
#define MTP3_T22_STRING     "T22"
#define MTP3_T23_STRING     "T23"
#define MTP3_T24_STRING     "T24"
#define MTP3_T25_STRING     "T25"
#define MTP3_T26_STRING     "T26"
#define MTP3_T27_STRING     "T27"
#define MTP3_T28_STRING     "T28"
#define MTP3_T29_STRING     "T29"
#define MTP3_T30_STRING     "T30"
#define MTP3_T31_STRING     "T31"
#define MTP3_T32_STRING     "T32"
#define MTP3_T33_STRING     "T33"
#define MTP3_T34_STRING     "T34"

#define MTP3_SLT_T1_STRING  "SLT-T1"
#define MTP3_SLT_T2_STRING  "SLT-T2"

#define SPARE_NIC_STRING        "HandleSpareNIC"
#define STP_FUNCTION_STRING     "STPFunction"
#define AUTO_TERM_ALLOC_STRING  "AutomaticTerminalAllocation"
#define AUTO_LINK_ALLOC_STRING  "AutomaticDataLinkAllocation"

/* For rpc commands */
#define PRINT_DATA_MAX_SIZE     16384
#define PRINT_BUF_MAX_SIZE      64
#define REMOTE_ROUTE            2
#define LOCAL_ROUTE             1

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

#define YES_NO(x) (x ? "yes" : "no")

#define STATUS_STR(x) ((x==DESTINATION_UNAVAILABLE)?"DESTINATION_UNAVAILABLE":\
                      ((x==DESTINATION_RESTRICTED) ? "DESTINATION_RESTRICTED":\
                      ((x==DESTINATION_AVAILABLE)  ? "DESTINATION_AVAILABLE" :\
                      "UNKNOWN")))

#define PEG_MTP3_GLOBAL_PEGS 20
#define PEG_MTP3_TIMER_PEGS  34

/*
 * MTP3 Timers
 */
typedef enum
{
    MTP3_T1,
    MTP3_T2,
    MTP3_T3,
    MTP3_T4,
    MTP3_T5,
    MTP3_T6,
    MTP3_T7,
    MTP3_T8,
    MTP3_T9,
    MTP3_T10,
    MTP3_T11,
    MTP3_T12,
    MTP3_T13,
    MTP3_T14,
    MTP3_T15,
    MTP3_T16,
    MTP3_T17,
    MTP3_T18,
    MTP3_T19,
    MTP3_T20,
    MTP3_T21,
    MTP3_T22,
    MTP3_T23,
    MTP3_T24,
    MTP3_T25,
    MTP3_T26,
    MTP3_T27,
    MTP3_T28,
    MTP3_T29,
    MTP3_T30,
    MTP3_T31,
    MTP3_T32,
    MTP3_T33,
    MTP3_T34,

    MTP3_SLT_T1,
    MTP3_SLT_T2,
    MTP3_LEAVE_TMR
}
MTP3_TIMER_ID;

/*
 * MTP3 Timer States
 */
typedef enum
{
    MTP3_TIMER_STOPPED,
    MTP3_TIMER_STARTED,
    MTP3_TIMER_EXPIRED,
    MTP3_TIMER_RETRYING
}
MTP3_TIMER_STATE;

/*
 * MTP3 timer context
 */
typedef struct
{
    MTP3_TIMER_ID timerId;
    union
    {
        struct
        {
            ITS_OCTET linkSet;
            ITS_OCTET linkCode;
        }
        linkInfo;
        struct
        {
            ITS_UINT    pointCode;
            ITS_OCTET   linkSet;
            ITS_OCTET   sio;
        }
        routeInfo;
    }
    data;    
}
MTP3_TimerContext;

/*
 * SMH triggers
 */
typedef enum
{
    /* HMDC */
    SMH_TRIGGER_L2_L3_MSG,              /* from L2 */

    /* HMDT */
    /* SMH_TRIGGER_L2_L3_MSG */         /* from HMDC */

    /* HMRT */
    SMH_TRIGGER_UPDATE_ROUTING_TABLES,  /* from STM */
    SMH_TRIGGER_MSG_FOR_ROUTING,        /* from HMDC */
    SMH_TRIGGER_L4_L3_MSG,              /* from L4 */
    SMH_TRIGGER_ROUTE_MGMT_MSG,         /* from SRM */
    SMH_TRIGGER_LINK_MGMT_MSG,          /* from SLM */
    SMH_TRIGGER_TRAFFIC_MGMT_MSG,       /* from STM */
    SMH_TRIGGER_TEST_CONTROL_MSG,       /* from SLTC */

    /* HMCG */
    SMH_TRIGGER_L3_L2_MSG               /* from HMRT */
}
SMH_Triggers;

/*
 * STM triggers
 */
typedef enum
{
    /* There needs to be a generic trigger for HMDT sending to STM */
    STM_TRIGGER_L2_MSG,

    STM_TRIGGER_LINK_AVAILABLE,             /* for TCOC, TSRC, TPRC from TLAC */
    STM_TRIGGER_LINK_UNAVAILABLE,           /* for TCOC, TSRC, TPRC from TLAC */

    /* TLAC */
    STM_TRIGGER_INHIBIT_LINK,               /* from MGMT */
    STM_TRIGGER_UNINHIBIT_LINK,             /* from MGMT, TSRC */
    STM_TRIGGER_UNINHIBITING_LINK,          /* from TSRC */
    STM_TRIGGER_FORCE_INHIBIT_LINK,         /* from HMDT */
    STM_TRIGGER_FORCE_UNINHIBIT_LINK,       /* from HMDT */
    STM_TRIGGER_INHIBIT_ALLOWED,            /* from HMDT */
    STM_TRIGGER_INHIBIT_DENIED,             /* from HMDT */
    STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,      /* 10: from TSRC */
    STM_TRIGGER_LOCAL_INHIBIT_DENIED,       /* from TSRC */
    STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,     /* from TSRC */
    STM_TRIGGER_REMOTE_INHIBIT_DENIED,      /* from TSRC */
    STM_TRIGGER_INHIBIT_POSSIBLE,           /* from TSRC */
    STM_TRIGGER_INHIBIT_IMPOSSIBLE,         /* from TSRC */
    STM_TRIGGER_UNINHIBIT_POSSIBLE,         /* from TSRC */
    STM_TRIGGER_UNINHIBIT_IMPOSSIBLE,       /* from TSRC */
    STM_TRIGGER_INHIBIT_ACK,                /* from HMDT */
    STM_TRIGGER_UNINHIBIT_ACK,              /* from HMDT */
    STM_TRIGGER_ADJACENT_SP_RESTARTING,     /* 20: from TSRC */
    STM_TRIGGER_ADJACENT_SP_RESTARTED,      /* from TSRC */
    STM_TRIGGER_CHANGEBACK_TERMINATED,      /* from TCBC */
    STM_TRIGGER_CHANGEOVER_EXECUTED,        /* from TCOC */
    STM_TRIGGER_CHANGEOVER_NOT_REQD,        /* from TCOC */
    STM_TRIGGER_LINK_FAILED,                /* from SLM */
    STM_TRIGGER_LINK_IN_SERVICE,            /* from SLM */
    STM_TRIGGER_RP_OUTAGE,                  /* from SLM */
    STM_TRIGGER_RP_RECOVERD,                /* from SLM */
    STM_TRIGGER_RB_CLEARED,                 /* from SLM */
    STM_TRIGGER_RTB_CLEARED,                /* 30: from SLM */
    STM_TRIGGER_RESTART_BEGIN,              /* from TPRC */
    STM_TRIGGER_RESTART_END,                /* from TPRC */
    STM_TRIGGER_LOCAL_INHIBIT_TEST,         /* from HMDT */
    STM_TRIGGER_REMOTE_INHIBIT_TEST,        /* from HMDT */
    STM_TRIGGER_LOCAL_UNINHIBIT_TEST,       /* from HMDT */
    STM_TRIGGER_REMOTE_UNINHIBIT_TEST,      /* from HMDT */
    STM_TRIGGER_EMERG_CHANGEOVER_ORDER,     /* from HMDT */
    STM_TRIGGER_CHANGEOVER_ORDER,           /* from HMDT */
    STM_TRIGGER_T12,                        /* from timer control */
    STM_TRIGGER_T13,                        /* 40: from timer control */    
    STM_TRIGGER_T14,                        /* from timer control */
    STM_TRIGGER_T20,                        /* from timer control */
    STM_TRIGGER_T21,                        /* from timer control */    

    /* TSRC */
    /* STM_TRIGGER_RESTART_END */           /* from TPRC */
    /* STM_TRIGGER_RESTART_BEGIN */         /* from TPRC */
    STM_TRIGGER_ACCESSIBILITY_REQUEST,      /* from RSRT, TRCC */
    STM_TRIGGER_ALTERNATE_ROUTE_REQ,        /* from TCOC, TCBC, TFRC, TCRC, LSDA */
    STM_TRIGGER_CHANGEOVER_NOT_REQ,         /* from TCOC */
    /* STM_TRIGGER_CHANGEOVER_EXECUTED */   /* from TCOC */
    STM_TRIGGER_PROCEDURE_TERMINATED,       /* from TCBC, TFRC, TCRC */
    STM_TRIGGER_ROUTE_AVAILABLE,            /* from RTAC */
    STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,    /* 50: from TLAC */
    STM_TRIGGER_REMOTE_INHIBIT_REQUESTED,   /* from TLAC */
    STM_TRIGGER_LINK_INHIBITED,             /* from TLAC */
    STM_TRIGGER_CANCEL_LINK_INHIBITED,      /* from TLAC */
    STM_TRIGGER_UNINHIBIT_REQUEST,          /* from TLAC */
    /* STM_TRIGGER_LINK_UNAVAILABLE */      /* from TLAC */
    STM_TRIGGER_TCP,                        /* from RTPC */
    STM_TRIGGER_ROUTE_UNAVAILABLE,          /* from RTPC */
    /* STM_TRIGGER_LINK_AVAILABLE */        /* from TLAC */
    STM_TRIGGER_TCA,                        /* from RTAC */
    STM_TRIGGER_ROUTE_RESTRICTED,           /* from RTRC */
    STM_TRIGGER_TCR,                        /* from RTRC */
    STM_TRIGGER_DANGER_OF_CONGESTION,       /* 60: from HMDC */
    STM_TRIGGER_T11,                        /* from timer control */
    STM_TRIGGER_LINK_CONGESTION_STATUS,     /* implementation dependent */
    STM_TRIGGER_SENDING_STATUS_PHASE,       /* from TPRC */
    STM_TRIGGER_SEND_TRW,                   /* from TPRC */
    STM_TRIGGER_TRAFFIC_RESTART_ALLOWED,    /* from TPRC */
    STM_TRIGGER_T25,                        /* from timer control */
    STM_TRIGGER_T28,                        /* from timer control */
    STM_TRIGGER_TRAFFIC_RESTART_WAITING,    /* from HMDT */
    STM_TRIGGER_SEND_STATUS,                /* from TPRC */
    STM_TRIGGER_T29,                        /* 70: from timer control */
    STM_TRIGGER_T30,                        /* from timer control */
    STM_TRIGGER_T32,                        /* from timer control */
    STM_TRIGGER_T33,                        /* from timer control */
    STM_TRIGGER_T34,                        /* from timer control */

    /* TRCC */
    STM_TRIGGER_DEST_CONGESTION_STATUS,     /* from RTCC */
    STM_TRIGGER_DECR_DEST_CONG_STATUS,      /* from RCAT */
    STM_TRIGGER_ACCESSIBILITY_DATA,         /* from TSRC */
    STM_TRIGGER_DEST_INACCESS,              /* from TSRC */
    STM_TRIGGER_CLUST_INACCESS,             /* from TSRC */
    STM_TRIGGER_T15,                        /* 80: from timer control */

    /* TCOC */
    /* STM_TRIGGER_LINK_UNAVAILABLE */      /* from TLAC */
    /* STM_TRIGGER_LINK_AVAILABLE */        /* from TLAC */
    /* STM_TRIGGER_EMERG_CHANGEOVER_ORDER *//* from TLAC */
    STM_TRIGGER_ALTERNATE_ROUTE_DATA,       /* from TSRC */
    /* STM_TRIGGER_LINK_AVAILABLE */        /* from TLAC */
    /* STM_TRIGGER_CHANGEOVER_ORDER */      /* from TLAC */
    STM_TRIGGER_BSNT,                       /* from L2 */
    STM_TRIGGER_BSNT_NOT_RETRIEVABLE,       /* from L2 */
    STM_TRIGGER_T1,                         /* from timer control */
    STM_TRIGGER_CHANGEOVER_ACK,             /* from HMDT */
    STM_TRIGGER_EMERG_CHANGEOVER_ACK,       /* from HMDT */
    STM_TRIGGER_RETRIEVED_MSGS,             /* from L2 */
    STM_TRIGGER_RETRIEVAL_COMPLETE,         /* from L2 */
    STM_TRIGGER_RETRIEVAL_NOT_POSSIBLE,     /* from L2 */
    STM_TRIGGER_T2,                         /* 90: from timer control */

    /* TCBC */
    /* STM_TRIGGER_LINK_AVAILABLE */        /* from TLAC */
    STM_TRIGGER_CHANGEBACK_DECL,            /* from HMDT */
    STM_TRIGGER_CHANGEBACK_ACK,             /* from HMDT */
    /* STM_TRIGGER_ALTERNATE_ROUTE_DATA */  /* from TSRC */
    STM_TRIGGER_T3,                         /* from timer control */
    STM_TRIGGER_T4,                         /* from timer control */
    STM_TRIGGER_T5,                         /* from timer control */

    /* TFRC */
    /* STM_TRIGGER_ROUTE_UNAVAILABLE */     /* from TSRC */
    /* STM_TRIGGER_ALTERNATE_ROUTE_DATA */  /* from TSRC */
    /* STM_TRIGGER_ROUTE_AVAILABLE */       /* from RTAC */

    /* TCRC */
    /* STM_TRIGGER_ROUTE_RESTRICTED */      /* from TSRC */
    /* STM_TRIGGER_ROUTE_AVAILALBLE */      /* from RTAC, TSRC */
    /* STM_TRIGGER_ALTERNATE_ROUTE_DATA */  /* from TSRC */
    STM_TRIGGER_T6,                         /* from timer control */

    /* TSFC */
    /* STM_TRIGGER_DEST_CONGESTION_STATUS *//* from TRCC, RTCC, TSRC */
    /* STM_TRIGGER_DEST_INACCESS */         /* from TSRC */
    /* STM_TRIGGER_CLUST_INACCESS */        /* from TSRC */
    STM_TRIGGER_DEST_ACCESS,                /* from TSRC */
    STM_TRIGGER_CLUST_ACCESS,               /* from TSRC */
    STM_TRIGGER_UPU,                        /* from RTCC */
    /* STM_TRIGGER_RESTART_BEGIN */         /* from TPRC */
    /* STM_TRIGGER_RESTART_END */           /* from TPRC */

    /* TPRC */
    /* STM_TRIGGER_TRAFFIC_RESTART_ALLOWED *//* from HMDT */
    STM_TRIGGER_RESTART_INDIC,              /* 100: from MGMT */
    STM_TRIGGER_T26,                        /* from timer control */
    STM_TRIGGER_T22,                        /* from timer control */
    /* STM_TRIGGER_LINK_AVAILABLE */        /* from TLAC */
    /* STM_TRIGGER_LINK_UNAVAILABLE */      /* from TLAC */
    STM_TRIGGER_T23,                        /* from timer control */
    STM_TRIGGER_STATUS_SENT,                /* from TSRC */
    STM_TRIGGER_T24,                        /* from timer control */
    STM_TRIGGER_T27,                        /* from timer control */

    /* missing from TSRC */
    STM_TRIGGER_T31,                        /* from timer control */
    STM_TRIGGER_LP_OUTAGE,                  /* From SLM */
    STM_TRIGGER_LP_RECOVERD                 /* From SLM */
}
STM_Triggers;

/*
 * SLM triggers
 */
typedef enum
{
    /* There needs to be a generic trigger for HMDT sending to SLM */
    SLM_TRIGGER_L2_MSG,

    /* LLSC */
    SLM_TRIGGER_ACTIVATE_LINK_SET,      /* from MGMT */
    SLM_TRIGGER_RESTART_BEGINS,         /* from TPRC */
    SLM_TRIGGER_DEACTIVATE_LINK_SET,    /* from MGMT */
    SLM_TRIGGER_LINK_ACTIVE,            /* from LSAC */
    SLM_TRIGGER_LINK_INACTIVE,          /* from LSAC */
    SLM_TRIGGER_LINK_FAILED,            /* from LSAC */
    SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,  /* from LSAC */
    SLM_TRIGGER_EMERGENCY,              /* from TSRC */
    SLM_TRIGGER_EMERGENCY_CEASES,       /* from TSRC */

    /* LSAC */
    SLM_TRIGGER_ACTIVATE_LINK,          /* 10: from LLSC, from MGMT */
    SLM_TRIGGER_DATA_LINK,              /* from LSDA */
    /* SLM_TRIGGER_EMERGENCY */         /* from LLSC */
    /* SLM_TRIGGER_EMERGENCY_CEASES */  /* from LLSC */
    SLM_TRIGGER_START_LINK,             /* from LSLA, from LSLR */
    SLM_TRIGGER_T17,                    /* from timer control */
    SLM_TRIGGER_ACTIVATION_UNSUCCESS,   /* from LSLA */
    SLM_TRIGGER_RESTORATION_UNSUCCESS,  /* from LSLR */
    SLM_TRIGGER_T19,                    /* from timer control */
    SLM_TRIGGER_NOT_POSSIBLE,           /* from LSLA */
    SLM_TRIGGER_DEACTIVATE_LINK,        /* from LLSC, from LSLA, from MGMT */
    SLM_TRIGGER_RESUME,                 /* from TLAC */
    SLM_TRIGGER_CLEAR_BUFFERS,          /* 20: from TLAC */
    SLM_TRIGGER_LINK_LOADED,            /* from TSRC */
    SLM_TRIGGER_LINK_DELOADED,          /* from TSRC */
    SLM_TRIGGER_CHANGEOVER_ORDER,       /* from TLAC */
    SLM_TRIGGER_CHANGEOVER_ORDER_RECVD, /* from TLAC */
    SLM_TRIGGER_CLEAR_RTB,              /* from TLAC */
    SLM_TRIGGER_STM_READY,              /* optional from STM */
    SLM_TRIGGER_L2_IN_SERVICE,          /* from L2 */
    SLM_TRIGGER_L2_RPO,                 /* from L2 */
    SLM_TRIGGER_L2_OUT_OF_SERVICE,      /* from L2 */
    SLM_TRIGGER_L2_RPR,                 /* 30: from L2 */
    SLM_TRIGGER_T32,                    /* from timer control */
    SLM_TRIGGER_T33,                    /* from timer control */
    SLM_TRIGGER_T34,                    /* from timer control */
    SLM_TRIGGER_RB_CLEARED,             /* from L2 */
    SLM_TRIGGER_RTB_CLEARED,            /* from L2 */
    SLM_TRIGGER_LP_OUTAGE,              /* from MGMT */
    SLM_TRIGGER_LP_RECOVERD,            /* from MGMT */

    /* LSLA */
    SLM_TRIGGER_START_ACTIVATION,       /* from LSAC */
    SLM_TRIGGER_RESTART_ACTIVATION,     /* from LSAC */
    /* SLM_TRIGGER_DATA_LINK */         /* from LSDA */
    SLM_TRIGGER_NO_DATA_LINK,           /* from LSDA */
    /* SLM_TRIGGER_DEACTIVATE_LINK */   /* from LSAC */
    SLM_TRIGGER_TERMINAL,               /* from LSTA */
    SLM_TRIGGER_NO_TERMINAL,            /* 40: from LSTA */

    /* LSLR */
    SLM_TRIGGER_START_RESTORATION,      /* from LSAC */
    SLM_TRIGGER_RESTART_RESTORATION,    /* from LSAC */
    /* SLM_TRIGGER_TERMINAL */          /* from LSTA */
    /* SLM_TRIGGER_NO_TERMINAL */       /* from LSTA */
    /* SLM_TRIGGER_DATA_LINK */         /* from LSDA */
    /* SLM_TRIGGER_NO_DATA_LINK */      /* from LSDA */

    /* LSLD */
    /* SLM_TRIGGER_DEACTIVATE_LINK */   /* from LSAC */

    /* LSTA */
    SLM_TRIGGER_DETERMINE_TERMINAL,     /* from LSLA, from LSLR */
    SLM_TRIGGER_TERMINAL_IDLE,          /* from LSLD */
    SLM_TRIGGER_TERMINAL_AVAILABLE,     /* from LSAC */

    /* LSDA */
    SLM_TRIGGER_DETERMINE_DATA_LINK,    /* from LSLA, from LSLR */
    SLM_TRIGGER_LINK_AVAILABLE,         /* from LSLD */
    SLM_TRIGGER_CONNECTION_ORDER,       /* from HMDT */
    SLM_TRIGGER_ALTERNATE_ROUTING_DATA, /* from TSRC */
    SLM_TRIGGER_CONNECTION_SUCCESSFUL,  /* 50: from HMDT */
    SLM_TRIGGER_CONNECTION_UNSUCCESS,   /* from HMDT */
    SLM_TRIGGER_CONNECTION_NOT_POSS,    /* from HMDT */
    SLM_TRIGGER_T7                      /* from timer control */
}
SLM_Triggers;

/*
 * SRM triggers
 */
typedef enum
{
    /* There needs to be a generic trigger for HMDT sending to SRM */
    SRM_TRIGGER_L2_MSG,

    /* RTPC */
    SRM_TRIGGER_TRANSFER_PROHIBIT,      /* from HMDT            args: SIF (incoming TFP)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_MSG_FOR_INACCESS_SP,    /* from HMRT            args: SIF (incoming msg),   */
                                        /*                            ls  (adjacent src)    */
    SRM_TRIGGER_SEND_TRANSFER_PROHIBIT, /* from RSRT            args: SIF (dpc),            */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_NEW_STP_DEST,           /* from TSRC            args: SIF (dpc),            */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_DEST_INACCESS,          /* from TSRC            args: SIF (destination),    */
    SRM_TRIGGER_CONTROLLED_REROUTE_END, /* from TCRC            args: SIF (destination),    */
                                        /*                            ls  (which route)     */
    SRM_TRIGGER_CONTROLLED_REROUTE,     /* from TCRC            args: SIF (destination),    */
                                        /*                            ls  (which route)     */
    SRM_TRIGGER_CLUSTER_INACCESS,       /* from TSRC            args: SIF (destination)     */     
    SRM_TRIGGER_MSG_FOR_INACCESS_CLUST, /* from HMRT            args: SIF (incoming msg)    */
                                        /*                            ls  (adjacent src)    */
    SRM_TRIGGER_SEND_TCP,               /* 10: from RSRT        args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_NEW_STP_FOR_CLUST,      /* from TSRC            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_TCP,                    /* from HMDT            args: SIF (incoming TCP)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_T8,                     /* from timer control */

    /* RTAC */
    SRM_TRIGGER_TRANSFER_ALLOW,         /* from HMRT            args: SIF (incoming TFA)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_DEST_ACCESS,            /* from TSRC            args: SIF (dpc)             */
    SRM_TRIGGER_REM_STP_DEST,           /* from TSRC            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_SEND_TRANSFER_ALLOW,    /* from RSRT            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_FORCED_REROUTE,         /* from TSRC            args: SIF (destination)     */
                                        /*                            ls  (which route)     */
    SRM_TRIGGER_FORCED_REROUTE_END,     /* from TFRC            args: SIF (destination)     */
                                        /*                            ls  (which route)     */
    SRM_TRIGGER_CLUSTER_ACCESS,         /* 20: from TSRC        args: SIF (dpc)             */
    SRM_TRIGGER_REM_STP_FOR_CLUST,      /* from TSRC            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_SEND_TCA,               /* from RSRT            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_TCA,                    /* from HMDT            args: SIF (incoming TCA)    */
                                        /*                            ls  (which adjacent)  */

    /* RSRT */
    SRM_TRIGGER_START_ROUTE_SET_TEST,   /* from RTRC, RTPC, TSRC args: SIF (dpc)            */
                                        /*                             ls  (adjacent dest)  */
    SRM_TRIGGER_ROUTE_AVAILABLE,        /* from RTAC */
    SRM_TRIGGER_T10,                    /* from timer control */
    SRM_TRIGGER_ROUTE_SET_TEST,         /* from HMDT */
    SRM_TRIGGER_ACCESSIBILITY_DATA,     /* from TSRC */
    SRM_TRIGGER_TCA_RCVD,               /* from RTAC */
    SRM_TRIGGER_TCP_RCVD,               /* 30: from TSRC */
    SRM_TRIGGER_TCR_RCVD,               /* from TSRC */
    SRM_TRIGGER_CLUSTER_ROUTE_SET_TEST, /* from HMDT */
    SRM_TRIGGER_RESTART_BEGINS,         /* from TPRC */
    SRM_TRIGGER_RESTART_ENDS,           /* from TPRC */
    SRM_TRIGGER_ADJACENT_RESTARTING,    /* from TSRC */

    /* RTCC */
    SRM_TRIGGER_TRANSFER_CONTROL,       /* from HMDT            args: SIF (incoming TFC)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_USER_PART_UNAVAIL,      /* from HMDT            args: SIF (incoming UPU)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_SEND_TRANSFER_CONTROL,  /* from HMCG            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */

    /* RCAT */
    SRM_TRIGGER_START_CONG_TEST,        /* from TRCC */
    SRM_TRIGGER_CONG_TEST,              /* 40: from HMDT */
    SRM_TRIGGER_STOP_CONG_TEST,         /* from TRCC */
    SRM_TRIGGER_T16,                    /* from timer control */

    /* RTRC */
    SRM_TRIGGER_TRANSFER_RESTRICT,      /* from HMDT            args: SIF (incoming TFR)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_TCR,                    /* from HMDT            args: SIF (incoming TCR)    */
                                        /*                            ls  (which adjacent)  */
    SRM_TRIGGER_SEND_TRANSFER_RESTRICT, /* from RSRT, from TSRC args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_DEST_RESTRICT,          /* from TSRC            args: SIF (dpc)             */
    SRM_TRIGGER_CLUSTER_RESTRICT,       /* from TSRC            args: SIF (dpc)             */
    SRM_TRIGGER_SEND_TCR,               /* from RSRT            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_MSG_FOR_RESTRICTED_DEST,/* from HMRT            args: SIF (incoming msg)    */
                                        /*                            ls  (adjacent src)    */
    SRM_TRIGGER_MSG_FOR_RESTRICTED_CLUST,/* 50: same args as above */
    /* SRM_TRIGGER_FORCED_REROUTE */    /* from TSRC            args: SIF (destination)     */
                                        /*                            ls  (which route)     */
    /* SRM_TRIGGER_FORCED_REROUTE_END *//* from TFRC            args: SIF (destination)     */
                                        /*                            ls  (which route)     */
    /* SRM_TRIGGER_CONTROLLED_REROUTE_END* from TCRC            args: SIF (destination)     */
                                        /*                            ls  (which route)     */
    /* SRM_TRIGGER_CONTROLLED_REROUTE *//* from TCRC            args: SIF (destination)     */
                                        /*                            ls  (which route)     */
    /* SRM_TRIGGER_REM_STP_DEST */      /* from TSRC            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    /* SRM_TRIGGER_REM_STP_FOR_CLUST */ /* from TSRC            args: SIF (dpc)             */
                                        /*                            ls  (adjacent dest)   */
    SRM_TRIGGER_T18
}
SRM_Triggers;

/*
 * SLT triggers
 */
typedef enum
{
    /* There needs to be a generic trigger for HMDT sending to SLT */
    SLT_TRIGGER_L2_MSG,                 /* from HMDT */

    SLT_TRIGGER_START_TEST,             /* from MGMT */
    SLT_TRIGGER_T1                      /* from timer control */
}
SLT_Triggers;

/*
 * trigger sources
 */
typedef enum
{
    MTP3_SMH,       /* Major subsystems */
    MTP3_STM,
    MTP3_SLM,
    MTP3_SRM,
    MTP3_SLT,
    MTP3_MGMT,
    MTP3_USER,

    MTP3_L2,        /* lower layer */
    MTP3_L4,        /* upper layer */
    MTP3_TIMER,     /* timer control */

    MTP3_SMH_HMDC,  /* 10: SMH subsystems */
    MTP3_SMH_HMDT,
    MTP3_SMH_HMRT,
    MTP3_SMH_HMCG,

    MTP3_STM_TLAC,  /* 14: STM subsystems */
    MTP3_STM_TSRC,
    MTP3_STM_TRCC,
    MTP3_STM_TCOC,
    MTP3_STM_TCBC,
    MTP3_STM_TFRC,
    MTP3_STM_TCRC,
    MTP3_STM_TSFC,
    MTP3_STM_TPRC,

    MTP3_SLM_LLSC,  /* 23: SLM subsystems */
    MTP3_SLM_LSAC,
    MTP3_SLM_LSLA,
    MTP3_SLM_LSLR,
    MTP3_SLM_LSLD,
    MTP3_SLM_LSTA,
    MTP3_SLM_LSDA,

    MTP3_SRM_RTPC,  /* 30: SRM subsystems */
    MTP3_SRM_RTAC,
    MTP3_SRM_RSRT,
    MTP3_SRM_RTCC,
    MTP3_SRM_RCAT,
    MTP3_SRM_RTRC,

    MTP3_SLT_SLTC   /* 36: SLT subsystems */
}
MTP3_SubSystems;

/*
 * implementation prototypes
 */
/*
 * find the adjacent an SNMM message came from, which MAY
 * not be the same as the linkSet it arrived on.
 */
ITS_OCTET MTP3_FindAdjacent_ANSI(ITS_OCTET ni, ITS_UINT pc,
                                 ITS_OCTET linkSet);
ITS_OCTET MTP3_FindAdjacent_CCITT(ITS_OCTET ni, ITS_UINT pc,
                                  ITS_OCTET linkSet);

/*
 * SMH
 */
int SMH_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
                  SMH_Triggers trigger,
                  ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode);

int HMDC_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int HMDT_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int HMRT_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int HMCG_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode,
                   ITS_UINT whichEntry);

int SMH_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
                   SMH_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int HMDC_Main_CCITT(MTP3_SubSystems src, SMH_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int HMDT_Main_CCITT(MTP3_SubSystems src, SMH_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int HMRT_Main_CCITT(MTP3_SubSystems src, SMH_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int HMCG_Main_CCITT(MTP3_SubSystems src, SMH_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode,
                    ITS_UINT whichEntry);

/*
 * STM
 */
int STM_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
                  STM_Triggers trigger,
                  ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode);

int TLAC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TSRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TRCC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TCOC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TCBC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TFRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TCRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TSFC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int TPRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int STM_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
                   STM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int TLAC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TSRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TRCC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TCOC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TCBC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TFRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TCRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TSFC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int TPRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);

/*
 * SLM
 */
int SLM_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
                  SLM_Triggers trigger,
                  ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode);

int LLSC_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSAC_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSLA_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSLR_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSLD_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSTA_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSDA_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int SLM_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
                   SLM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int LLSC_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSAC_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSLA_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSLR_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSLD_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSTA_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int LSDA_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);

/*
 * SRM
 */
int SRM_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
                  SRM_Triggers trigger,
                  ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode);

int RTPC_Main_ANSI(MTP3_SubSystems src, SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int RTAC_Main_ANSI(MTP3_SubSystems src, SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int RSRT_Main_ANSI(MTP3_SubSystems src, SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int RTCC_Main_ANSI(MTP3_SubSystems src, SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int RCAT_Main_ANSI(MTP3_SubSystems src, SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);
int RTRC_Main_ANSI(MTP3_SubSystems src, SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int SRM_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
                   SRM_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int RTPC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int RTAC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int RSRT_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int RTCC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int RCAT_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);
int RTRC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);

/*
 * SLT
 */
int SLT_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
                  SLT_Triggers trigger,
                  ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode);

int SLTC_Main_ANSI(MTP3_SubSystems src, SLT_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int SLT_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
                   SLT_Triggers trigger,
                   ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode);

int SLTC_Main_CCITT(MTP3_SubSystems src, SLT_Triggers trigger,
                    ITS_OCTET *sif, ITS_USHORT len,
                    ITS_OCTET linkSet, ITS_OCTET linkCode);

/*
 * behavior control
 */
ITS_BOOLEAN STPFunction_ANSI();
ITS_BOOLEAN SPRestarting_ANSI();
ITS_BOOLEAN STPFunction_CCITT();
ITS_BOOLEAN SPRestarting_CCITT();

/*
 * behaviour control boolean key in DSM
 */
typedef struct
{
    ITS_OCTET type;
    ITS_OCTET var;
}
MTP3_BehaviourKey;

/*
 * tracing
 */
void MTP3_FuncEntry_ANSI(MTP3_SubSystems sub, MTP3_SubSystems src,
                         int trigger,
                         ITS_OCTET *sif, ITS_USHORT len,
                         ITS_OCTET linkSet, ITS_OCTET linkCode,
                         char *file, int line);
void MTP3_FuncEntry_CCITT(MTP3_SubSystems sub, MTP3_SubSystems src,
                          int trigger,
                          ITS_OCTET *sif, ITS_USHORT len,
                          ITS_OCTET linkSet, ITS_OCTET linkCode,
                          char *file, int line);

/*
 * L2 interface.
 */
int MTP2_SendData_ANSI(ITS_OCTET linkSet, ITS_OCTET linkCode,
                       ITS_OCTET command,
                       ITS_OCTET *data, ITS_USHORT len);
int MTP2_ReceiveData_ANSI(ITS_EVENT *ev,
                          ITS_OCTET *linkSet, ITS_OCTET *linkCode,
                          ITS_OCTET *data, ITS_USHORT *len);
int MTP2_SendData_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode,
                        ITS_OCTET command,
                        ITS_OCTET *data, ITS_USHORT len);
int MTP2_ReceiveData_CCITT(ITS_EVENT *ev,
                           ITS_OCTET *linkSet, ITS_OCTET *linkCode,
                           ITS_OCTET *data, ITS_USHORT *len);


/*
 * a data structure for CO/CB buffer contents.
 */
typedef struct
{
    ITS_UINT    seqNo;
    ITS_EVENT   event;
}
MTP3_EventRec;

/* 
 * conversion functions ITS_EVENT <--> CO/CB buffer contents 
 */
ITSSS7DLLAPI MTP3_EventRec ItsEventToMTP3EventRec_CCITT(ITS_EVENT ev);
ITSSS7DLLAPI MTP3_EventRec ItsEventToMTP3EventRec_ANSI(ITS_EVENT ev);

ITSSS7DLLAPI ITS_EVENT MTP3EventRecToItsEvent_CCITT(MTP3_EventRec evRec);
ITSSS7DLLAPI ITS_EVENT MTP3EventRecToItsEvent_ANSI(MTP3_EventRec evRec);


/*****************************************************************************
 *
 * The MTP3 Management data.
 *
 *****************************************************************************/
/*
 * MGMT triggers
 */
typedef enum
{
    MGMT_TRIGGER_NO_ROUTING_DATA,       /* from HMRT */
    MGMT_TRIGGER_LINK_TEST_PASSED,      /* from SLTC */
    MGMT_TRIGGER_LINK_TEST_FAILED,      /* from SLTC */
    MGMT_TRIGGER_LINK_ACTIVATION_FAIL,  /* from LSAC */
    MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT,   /* from TLAC */
    MGMT_TRIGGER_UNINHIBIT_REQ_TIMEOUT, /* from TLAC */
    MGMT_TRIGGER_UNINHIBIT_LINK,        /* from TLAC */
    MGMT_TRIGGER_INHIBIT_DENIED,        /* from TLAC */
    MGMT_TRIGGER_LINK_INHIBITED,        /* from TLAC */
    MGMT_TRIGGER_LINK_REMOTE_UNINHIBIT, /* from TLAC */
    MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,  /* from TLAC */
    MGMT_TRIGGER_MSG_FOR_INVALID_DEST,  /* from HMRT */
    MGMT_TRIGGER_RESTART,               /* from USER */
    MGMT_TRIGGER_INHIBIT_LINK,               /* from USER */
    MGMT_TRIGGER_DEACTIVATE_LINK,          /* from USER */
    MGMT_TRIGGER_DEACTIVATE_LINK_SET,   /* from USER */
    MGMT_TRIGGER_ACTIVATE_LINK,               /* from USER */
    MGMT_TRIGGER_ACTIVATE_LINK_SET,     /* from USER */
    MGMT_TRIGGER_LP_OUTAGE,            /* from USER */
    MGMT_TRIGGER_LP_RECOVERD           /* from USER */
}
MGMT_Triggers;

/*
 * MGMT
 */
ITSSS7DLLAPI int MGMT_Main_ANSI(MTP3_SubSystems src, MGMT_Triggers trigger,
                                ITS_OCTET *sif, ITS_USHORT len,
                                ITS_OCTET linkSet, ITS_OCTET linkCode);

ITSSS7DLLAPI int MGMT_Main_CCITT(MTP3_SubSystems src, MGMT_Triggers trigger,
                                 ITS_OCTET *sif, ITS_USHORT len,
                                 ITS_OCTET linkSet, ITS_OCTET linkCode);


/*----------------------------------------------------------------------
 * The mtp3General family. 
 *----------------------------------------------------------------------*/
typedef struct
{
    ITS_UINT        nodeType;
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;
    ITS_CHAR       traceType[ITS_PATH_MAX];
    ITS_CHAR       traceOutput[ITS_PATH_MAX];
}
MTP3GeneralCfg;

/* return NULL if not successful, user will free the allocated memory */
ITSSS7DLLAPI MTP3GeneralCfg* MTP3_GetGeneralCfg_ANSI();
ITSSS7DLLAPI MTP3GeneralCfg* MTP3_GetGeneralCfg_CCITT();

/* return ITS_SUCCESS if set succeeded */
ITSSS7DLLAPI int MTP3_SetGeneralCfg_ANSI(MTP3GeneralCfg *data);
ITSSS7DLLAPI int MTP3_SetGeneralCfg_CCITT(MTP3GeneralCfg *data);

/*----------------------------------------------------------------------
 * The linksetEntry family. 
 *----------------------------------------------------------------------*/
typedef struct 
{
    ITS_UINT        number;      /* linkset number */
    ITS_UINT        lpc;
    ITS_UINT        apc;
    ITS_OCTET       ni;
    ITS_UINT        maxActiveLink;
    ITS_UINT        numOfRoutes;
}
MTP3LinksetInfo;

typedef struct 
{
    ITS_UINT        numOfActiveLink;
    ITS_UINT        numOfCongestedLink;
    ITS_BOOLEAN     isCongested;
    ITS_BOOLEAN     isActive;          /* linkset state: active or disabled */
}
MTP3LinksetStatus;

/*
 * input: linksetNumber 
 *
 * output: pointer to MTP3LinksetInfo
 *
 * Note:
 *    Only used in if exact is true, return the exact MTP3LinksetInfo
 *    that matches the input, return NULL if exact match not found.
 */
ITSSS7DLLAPI MTP3LinksetInfo* MTP3_GetLinksetEntry_ANSI(ITS_UINT linksetNumber);
ITSSS7DLLAPI MTP3LinksetInfo* MTP3_GetLinksetEntry_CCITT(ITS_UINT linksetNumber);

/*
 * This function is used to get all the linkset entries which will be used 
 * for getnext.
 *
 * output: entries -- array of MTP3LinksetInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void MTP3_GetAllLinksetEntries_ANSI(ITS_UINT* numEntries,
                                                 MTP3LinksetInfo** entries);
ITSSS7DLLAPI void MTP3_GetAllLinksetEntries_CCITT(ITS_UINT* numEntries,
                                                  MTP3LinksetInfo** entries);

/* return ITS_SUCCESS if operation succeeded */
ITSSS7DLLAPI int MTP3_SetLinksetEntry_ANSI(MTP3LinksetInfo* data);
ITSSS7DLLAPI int MTP3_RemLinksetEntry_ANSI(MTP3LinksetInfo* data);
ITSSS7DLLAPI int MTP3_SetLinksetEntry_CCITT(MTP3LinksetInfo* data);
ITSSS7DLLAPI int MTP3_RemLinksetEntry_CCITT(MTP3LinksetInfo* data);

/*
 * input: linksetNumber 
 *
 * output: status -- pointer to MTP3LinksetStatus
 *
 * return:
 *    ITS_SUCCESS if operation succeeds 
 */
ITSSS7DLLAPI int MTP3_GetLinksetStatus_ANSI(ITS_UINT linksetNumber,
                                            MTP3LinksetStatus* status);
ITSSS7DLLAPI int MTP3_GetLinksetStatus_CCITT(ITS_UINT linksetNumber,
                                             MTP3LinksetStatus* status);

/*----------------------------------------------------------------------
 * The linkEntry family. 
 *----------------------------------------------------------------------*/
typedef enum
{
    MTP3_LINK_INACTIVE,
    MTP3_LINK_CONNECTING,
    MTP3_LINK_ACTIVE,
    MTP3_LINK_FAILED,
    MTP3_LINK_WAIT_CONNECT
}
MTP3LinkState;

typedef struct 
{
    ITS_UINT        linkNumber;
    ITS_UINT        linksetNumber;
    ITS_UINT        variant;        /* ANSI or ITU */
    ITS_UINT        adjPC;
    ITS_UINT        slc;
    ITS_UINT        priority;
    ITS_UINT        msgSize;
    ITS_UINT        maxSLTtry;
    ITS_UINT        p0Qlen;
    ITS_UINT        p1Qlen;
    ITS_UINT        p2Qlen;
    ITS_UINT        p3Qlen;
    ITS_UINT        discPriority;
} 
MTP3LinkInfo;

typedef struct 
{
    MTP3LinkState   state;
    ITS_BOOLEAN     isBlocked;
    ITS_BOOLEAN     isLocalBlocked;
    ITS_BOOLEAN     isLocalInhibit;
    ITS_BOOLEAN     isRemoteInhibit;
    ITS_BOOLEAN     isCongested;
} 
MTP3LinkStatus;

/*
 * input:  ls -- linkset number 
 *        lnk -- link number 
 *
 * output: pointer to MTP3LinkInfo
 *
 * Note:
 *    Only used in if exact is true, return the exact MTP3LinkInfo
 *    that matches the input, return NULL if exact match not found.
 */
ITSSS7DLLAPI MTP3LinkInfo* MTP3_GetLinkInfo_ANSI(ITS_UINT ls, ITS_UINT lnk);
ITSSS7DLLAPI MTP3LinkInfo* MTP3_GetLinkInfo_CCITT(ITS_UINT ls, ITS_UINT lnk);


/*
 * This function is used to get all the link entries which will be used 
 * for getnext.
 *
 * output: entries -- array of MTP3LinkInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void MTP3_GetAllLinkEntries_ANSI(ITS_UINT* numEntries,
                                              MTP3LinkInfo** entries);
ITSSS7DLLAPI void MTP3_GetAllLinkEntries_CCITT(ITS_UINT* numEntries,
                                               MTP3LinkInfo** entries);

/* return ITS_SUCCESS if operation succeeded */
ITSSS7DLLAPI int MTP3_SetLinkEntry_ANSI(MTP3LinkInfo* data);
ITSSS7DLLAPI int MTP3_RemLinkEntry_ANSI(MTP3LinkInfo* data);
ITSSS7DLLAPI int MTP3_SetLinkEntry_CCITT(MTP3LinkInfo* data);
ITSSS7DLLAPI int MTP3_RemLinkEntry_CCITT(MTP3LinkInfo* data);

/*
 * input:  ls -- linkset number 
 *        lnk -- link number 
 *
 * output: status -- pointer to MTP3LinkStatus
 *
 * return:
 *    ITS_SUCCESS if operation succeeds 
 */
ITSSS7DLLAPI int MTP3_GetLinkStatus_ANSI(ITS_UINT ls, ITS_UINT lnk,
                                         MTP3LinkStatus* status);
ITSSS7DLLAPI int MTP3_GetLinkStatus_CCITT(ITS_UINT ls, ITS_UINT lnk,
                                          MTP3LinkStatus* status);

/*----------------------------------------------------------------------
 * The routeEntry family. 
 *----------------------------------------------------------------------*/
typedef enum
{
    MTP3_LOCAL,
    MTP3_REMOTE 
}
MTP3RouteDirection;

typedef enum
{
    MTP3_AVAILABLE,
    MTP3_UNAVAILABLE,
    MTP3_RESTRICTED 
}
MTP3RouteState;

typedef struct 
{
    ITS_UINT            dpc;
    ITS_OCTET           ni;
    ITS_UINT            linksetNumber;
    ITS_UINT            priority;
    MTP3RouteDirection  direction;
    ITS_UINT            variant;
    ITS_BOOLEAN         rteToAdjSp;
    ITS_BOOLEAN         rteToCluster;
} 
MTP3RouteInfo;

typedef struct 
{
    ITS_UINT            numActiveLinksets;    
    ITS_UINT            numCongestedLinksets;
    MTP3RouteState      state;
    ITS_BOOLEAN         isCongested;
    ITS_BOOLEAN         spRestartFlag; /* true: waiting to send TRA to this 
                                          destination; false: not waiting to 
                                          send TRA to this destination */
} 
MTP3RouteStatus;

/*
 * input: dpc -- route destination point code
 *         ni -- network indicator 
 *         ls -- linkset Number 
 *
 * output: pointer to MTP3RouteInfo
 *
 * Note:
 *    Only used in if exact is true, return the exact MTP3RouteInfo
 *    that matches the input, return NULL if exact match not found.
 */
ITSSS7DLLAPI MTP3RouteInfo* MTP3_GetRouteEntry_ANSI(ITS_UINT dpc, ITS_OCTET ni,
                                                    ITS_UINT ls);
ITSSS7DLLAPI MTP3RouteInfo* MTP3_GetRouteEntry_CCITT(ITS_UINT dpc, ITS_OCTET ni,
                                                     ITS_UINT ls);


/*
 * This function is used to get all the linkset entries which will be used 
 * for getnext.
 *
 * output: entries -- array of MTP3RouteInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void MTP3_GetAllRouteEntries_ANSI(ITS_UINT* numEntries,
                                               MTP3RouteInfo** entries);
ITSSS7DLLAPI void MTP3_GetAllRouteEntries_CCITT(ITS_UINT* numEntries,
                                                MTP3RouteInfo** entries);

/* return ITS_SUCCESS if operation succeeded */
ITSSS7DLLAPI int MTP3_SetRouteEntry_ANSI(MTP3RouteInfo* data);
ITSSS7DLLAPI int MTP3_RemRouteEntry_ANSI(MTP3RouteInfo* data);
ITSSS7DLLAPI int MTP3_SetRouteEntry_CCITT(MTP3RouteInfo* data);
ITSSS7DLLAPI int MTP3_RemRouteEntry_CCITT(MTP3RouteInfo* data);

/*
 * input: dpc -- route destination point code
 *         ni -- network indicator 
 *         ls -- linkset Number 
 *
 * output: status -- pointer to MTP3RouteStatus
 *
 * return:
 *    ITS_SUCCESS if operation succeeds 
 */
ITSSS7DLLAPI int MTP3_GetRouteStatus_ANSI(ITS_UINT dpc, ITS_OCTET ni,
                                          ITS_UINT ls, 
                                          MTP3RouteStatus* status);
ITSSS7DLLAPI int MTP3_GetRouteStatus_CCITT(ITS_UINT dpc, ITS_OCTET ni,
                                           ITS_UINT ls, 
                                           MTP3RouteStatus* status);

/*----------------------------------------------------------------------
 * The destEntry family. 
 *----------------------------------------------------------------------*/
typedef struct 
{
    ITS_UINT            dpc;
    ITS_OCTET           ni;
} 
MTP3DestinationInfo;

typedef MTP3RouteState MTP3DestinationStatus;

/*
 * input: dpc -- route destination point code
 *         ni -- network indicator 
 *
 * output: pointer to MTP3DestinationInfo
 *
 * Note:
 *    Only used in if exact is true, return the exact MTP3DestinationInfo
 *    that matches the input, return NULL if exact match not found.
 */
ITSSS7DLLAPI MTP3DestinationInfo* MTP3_GetDestinationInfo_ANSI(ITS_UINT dpc,
                                                               ITS_OCTET ni);
ITSSS7DLLAPI MTP3DestinationInfo* MTP3_GetDestinationInfo_CCITT(ITS_UINT dpc,
                                                                ITS_OCTET ni);


/*
 * This function is used to get all the destination entries which will be used 
 * for getnext.
 *
 * output: entries -- array of MTP3DestinationInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void MTP3_GetAllDestinationEntries_ANSI(ITS_UINT* numEntries, 
                                                     MTP3DestinationInfo** entries);
ITSSS7DLLAPI void MTP3_GetAllDestinationEntries_CCITT(ITS_UINT* numEntries, 
                                                      MTP3DestinationInfo** entries);

/* return ITS_SUCCESS if operation succeeded */
ITSSS7DLLAPI int MTP3_SetDestinationEntry_ANSI(MTP3DestinationInfo* data);
ITSSS7DLLAPI int MTP3_RemDestinationEntry_ANSI(MTP3DestinationInfo* data);
ITSSS7DLLAPI int MTP3_SetDestinationEntry_CCITT(MTP3DestinationInfo* data);
ITSSS7DLLAPI int MTP3_RemDestinationEntry_CCITT(MTP3DestinationInfo* data);

/*
 * input: dpc -- route destination point code
 *         ni -- network indicator 
 *
 * output: status -- pointer to MTP3DestinationStatus
 *
 * return:
 *    ITS_SUCCESS if operation succeeds 
 */
ITSSS7DLLAPI int MTP3_GetDestinationStatus_ANSI(ITS_UINT dpc, ITS_OCTET ni, 
                                                MTP3DestinationStatus* status);
ITSSS7DLLAPI int MTP3_GetDestinationStatus_CCITT(ITS_UINT dpc, ITS_OCTET ni, 
                                                 MTP3DestinationStatus* status);

/**************************************
 * Statistics API
 ***************************************/

/*
 * The General Statistics 
 */
ITSSS7DLLAPI int MTP3_GetGeneralStats_ANSI(ITS_UINT **pegs, ITS_UINT *numPegs); 
ITSSS7DLLAPI int MTP3_GetGeneralStats_CCITT(ITS_UINT **pegs, ITS_UINT *numPegs); 

/*
 * The Linkset Statistics
 */
ITSSS7DLLAPI int MTP3_GetLinksetStats_ANSI(ITS_UINT linksetNUmber, 
                                           ITS_UINT **pegs,
                                           ITS_UINT *numPegs); 
ITSSS7DLLAPI int MTP3_GetLinksetStats_CCITT(ITS_UINT linksetNUmber, 
                                            ITS_UINT **pegs,
                                            ITS_UINT *numPegs); 

/*
 * The Link Statistics 
 */
ITSSS7DLLAPI int MTP3_GetLinkStats_ANSI(ITS_UINT linksetNUmber,
                                        ITS_UINT lnkNumber,
                                        ITS_UINT **pegs,
                                        ITS_UINT *numPegs); 
ITSSS7DLLAPI int MTP3_GetLinkStats_CCITT(ITS_UINT linksetNUmber,
                                         ITS_UINT lnkNumber,
                                         ITS_UINT **pegs,
                                         ITS_UINT *numPegs); 

/*
 * The Route Statistics 
 */
ITSSS7DLLAPI int MTP3_GetRouteStats_ANSI(ITS_UINT dpc, ITS_OCTET ni,
                                         ITS_UINT linksetNumber,
                                         ITS_UINT **pegs,
                                         ITS_UINT *numPegs); 
ITSSS7DLLAPI int MTP3_GetRouteStats_CCITT(ITS_UINT dpc, ITS_OCTET ni,
                                          ITS_UINT linksetNumber,
                                          ITS_UINT **pegs,
                                          ITS_UINT *numPegs); 

/*
 * The Destination Statistics
 */
ITSSS7DLLAPI int MTP3_GetDestinationStats_ANSI(ITS_UINT dpc, ITS_OCTET ni, 
                                               ITS_UINT **pegs,
                                               ITS_UINT *numPegs); 
ITSSS7DLLAPI int MTP3_GetDestinationStats_CCITT(ITS_UINT dpc, ITS_OCTET ni, 
                                                ITS_UINT **pegs,
                                                ITS_UINT *numPegs); 

/*
 * console
 */
void MTP3_Console_ANSI(DBC_Server *dbc, const char *cmdLine);
void MTP3_Console_CCITT(DBC_Server *dbc, const char *cmdLine);

/*
 * management data for MTP3
 */
typedef struct
{
    /* data part */
    PEG_Manager         *pegs;
    BEHAVIOR_Manager    *behaviors;
    TIMER_Manager       *timers;
    ALARM_Format        **alarms;

    MTP3GeneralCfg*     (*GetGeneralCfg)();
    int                 (*SetGeneralCfg)(MTP3GeneralCfg *data);
    MTP3LinksetInfo*    (*GetLinksetEntry)(ITS_UINT linksetNumber);
    void                (*GetAllLinksetEntries)(ITS_UINT* numEntries,
                                                MTP3LinksetInfo** entries);
    int                 (*SetLinksetEntry)(MTP3LinksetInfo* data);
    int                 (*RemLinksetEntry)(MTP3LinksetInfo* data);
    int                 (*GetLinksetStatus)(ITS_UINT linksetNumber,
                                            MTP3LinksetStatus* status);
    MTP3LinkInfo*       (*GetLinkInfo)(ITS_UINT ls, ITS_UINT lnk);
    void                (*GetAllLinkEntries)(ITS_UINT* numEntries,
                                             MTP3LinkInfo** entries);
    int                 (*SetLinkEntry)(MTP3LinkInfo* data);
    int                 (*RemLinkEntry)(MTP3LinkInfo* data);
    int                 (*GetLinkStatus)(ITS_UINT ls, ITS_UINT lnk,
                                         MTP3LinkStatus* status);
    MTP3RouteInfo*      (*GetRouteEntry)(ITS_UINT dpc, ITS_OCTET ni,
                                         ITS_UINT ls);
    void                (*GetAllRouteEntries)(ITS_UINT* numEntries,
                                              MTP3RouteInfo** entries);
    int                 (*SetRouteEntry)(MTP3RouteInfo* data);
    int                 (*RemRouteEntry)(MTP3RouteInfo* data);
    int                 (*GetRouteStatus)(ITS_UINT dpc, ITS_OCTET ni,
                                          ITS_UINT ls, 
                                          MTP3RouteStatus* status);
    void                (*GetAllDestinationEntries)(ITS_UINT* numEntries, 
                                                    MTP3DestinationInfo** entries);
    int                 (*SetDestinationEntry)(MTP3DestinationInfo* data);
    int                 (*RemDestinationEntry)(MTP3DestinationInfo* data);
    int                 (*GetDestinationStatus)(ITS_UINT dpc, ITS_OCTET ni, 
                                                MTP3DestinationStatus* status);
    int                 (*GetGeneralStats)(ITS_UINT **pegs, ITS_UINT *numPegs); 
    int                 (*GetLinksetStats)(ITS_UINT linksetNUmber, 
                                           ITS_UINT **pegs,
                                           ITS_UINT *numPegs); 
    int                 (*GetLinkStats)(ITS_UINT linksetNUmber,
                                        ITS_UINT lnkNumber,
                                        ITS_UINT **pegs,
                                        ITS_UINT *numPegs); 
    int                 (*GetRouteStats)(ITS_UINT dpc, ITS_OCTET ni,
                                         ITS_UINT linksetNumber,
                                         ITS_UINT **pegs,
                                         ITS_UINT *numPegs); 
    int                 (*GetDestinationStats)(ITS_UINT dpc, ITS_OCTET ni, 
                                               ITS_UINT **pegs,
                                               ITS_UINT *numPegs); 
}
MTP3_MgmtClassPart;

typedef struct
{
    ITS_CoreClassPart   core;
    MTP3_MgmtClassPart  mtp3;
}
MTP3_MgmtClassRec, *MTP3_MgmtClass;

extern ITSSS7DLLAPI ITS_Class MTP3_MgmtClass_ANSI;
extern ITSSS7DLLAPI ITS_Class MTP3_MgmtClass_CCITT;

/*
 * for now
 */
/* #define LOCAL_DEBUG */

#if defined(LOCAL_DEBUG)
#define MTP3_TRACE_ENTRY_ANSI(f, o, t, s, l, ls, lc) \
    MTP3_FuncEntry_ANSI(f, o, (int)t, s, l, ls, lc, __FILE__, __LINE__);
#define MTP3_TRACE_ENTRY_CCITT(f, o, t, s, l, ls, lc) \
    MTP3_FuncEntry_CCITT(f, o, (int)t, s, l, ls, lc, __FILE__, __LINE__);
#else
#define MTP3_TRACE_ENTRY_ANSI(f, o, t, s, l, ls, lc)
#define MTP3_TRACE_ENTRY_CCITT(f, o, t, s, l, ls, lc)
#endif

#if defined(__cplusplus)
}
#endif

#endif /* MTP3_INTERN_H */
