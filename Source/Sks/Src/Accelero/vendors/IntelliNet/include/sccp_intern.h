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
 *  ID: $Id: sccp_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.3  2007/06/25 04:43:07  ashutosh.singh
 * LOG: Bug 629 :related to multiple RLSD continously
 * LOG:
 * LOG: Revision 1.2  2007/04/17 08:25:26  ashutosh.singh
 * LOG: logger lib related  changes
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2.2.1  2005/09/21 13:01:29  adutta
 * LOG: Addition of ssn in CO call context
 * LOG:
 * LOG: Revision 9.2  2005/06/09 05:59:01  adutta
 * LOG: XUDT implementation in ANSI
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:21  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1.2.3.12.4  2005/01/31 10:43:57  snagesh
 * LOG: Moved SCCP management data from ss7_mgmt.h
 * LOG:
 * LOG: Revision 7.2.2.1.2.3.12.3  2005/01/05 10:47:12  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.2.2.1.2.3.12.2  2005/01/04 13:45:43  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.2.2.1.2.3.12.1  2004/12/16 15:02:01  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.2.1.2.3.6.1  2004/10/25 20:34:11  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.2.2.1.2.3  2004/06/22 11:49:34  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.2.2.1.2.2  2004/02/17 13:00:15  mmanikandan
 * LOG: RepeatRelease and Interval timers are added.
 * LOG:
 * LOG: Revision 7.2.2.1.2.1  2004/01/27 05:45:20  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/11/17 18:11:28  hcho
 * LOG: Update to large context.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.11  2002/08/22 20:51:23  omayor
 * LOG: If defined PRC then FAMILY_ITU becomes FAMILY_CHINA. This was needed to
 * LOG: substitute the ITU family with CHINA in the routing subsystem calls.
 * LOG:
 * LOG: Revision 6.10  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.9  2002/06/05 15:48:57  mmiers
 * LOG: More SCMG work
 * LOG:
 * LOG: Revision 6.8  2002/04/24 15:55:37  mmiers
 * LOG: Add SCCP management interface.
 * LOG:
 * LOG: Revision 6.7  2002/04/05 16:55:13  mmiers
 * LOG: Dead function removal
 * LOG:
 * LOG: Revision 6.6  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.5  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 6.4  2002/03/11 20:59:46  mmiers
 * LOG: It builds.  Now for the hard part.
 * LOG:
 * LOG: Revision 6.3  2002/03/07 17:42:30  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.2  2002/03/01 23:12:06  mmiers
 * LOG: Start the DSM/pegs/alarms merge.  ANSI-TCAP done, 3 left.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2002/02/01 22:12:26  mmiers
 * LOG: ISUP integration
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/09/25 01:03:24  mmiers
 * LOG: Notes on concerned and duplicate routes.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/11 21:42:39  mmiers
 * LOG: Pass the label to the callbacks.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:53:58  mmiers
 * LOG: Add user intervention callbacks.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.5  2001/04/02 21:20:24  mmiers
 * LOG: Align the string names.
 * LOG:
 * LOG: Revision 3.4  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.3  2001/02/06 18:04:31  mmiers
 * LOG: Add locks for CO SCCP and TCAP contexts.  Next, to use them.
 * LOG:
 * LOG: Revision 3.2  2000/11/14 00:18:19  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/10/20 22:23:15  omayor
 * LOG: Add SOR, SOG SCMG procedure for duplicate SSN. Also LUDT, LUDTS
 * LOG: procedures for ITU SCCP
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:11  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.39.2.1  1999/12/06 21:27:32  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.39  1999/08/27 00:51:22  mmiers
 * LOG:
 * LOG:
 * LOG: Commit more work, mostly just formatting, but include ies in
 * LOG: GTT callback.  User can really get himself in trouble now.
 * LOG:
 * LOG: Revision 1.38  1999/08/26 23:45:03  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.37  1999/08/26 19:58:49  rsonak
 * LOG:
 * LOG:
 * LOG: Some protocol fixes.
 * LOG:
 * LOG: Revision 1.36  1999/06/29 15:24:23  mmiers
 * LOG:
 * LOG:
 * LOG: Modify global title behavior a bit (allow setting of DPC only).
 * LOG:
 * LOG: Revision 1.35  1999/03/24 22:46:35  mmiers
 * LOG:
 * LOG:
 * LOG: Clean up the SST queue when terminating.
 * LOG:
 * LOG: Revision 1.34  1999/03/17 20:55:08  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.33  1999/03/17 18:39:54  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.32  1998/11/13 17:05:42  mmiers
 * LOG: Fix bad timer message.
 * LOG:
 * LOG: Revision 1.31  1998/11/13 02:49:42  mmiers
 * LOG: Do SST.
 * LOG:
 * LOG: Revision 1.30  1998/11/11 03:47:27  mmiers
 * LOG: Clean up some SCCP stuff.
 * LOG:
 * LOG: Revision 1.29  1998/11/11 00:45:30  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.28  1998/11/10 03:26:39  mmiers
 * LOG: Update/include the string defines.
 * LOG:
 * LOG: Revision 1.27  1998/11/10 02:23:02  mmiers
 * LOG: Fix IT timers, rework stack-sent messages, add guard timer, add
 * LOG: behavior control.
 * LOG:
 * LOG: Revision 1.26  1998/11/09 23:30:23  mmiers
 * LOG: Put in intermediate node code.
 * LOG:
 * LOG: Revision 1.25  1998/10/28 23:51:47  mmiers
 * LOG: Halfway through SCMG.
 * LOG:
 * LOG: Revision 1.24  1998/10/20 02:29:40  mmiers
 * LOG: Add prototype for SCMG function.
 * LOG:
 * LOG: Revision 1.23  1998/10/19 00:40:37  mmiers
 * LOG: Strengthen for PCLASS_3
 * LOG:
 * LOG: Revision 1.22  1998/10/16 20:45:22  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.21  1998/10/15 01:45:03  mmiers
 * LOG: Add -D_REENTRANT for alpha.  Add connRef to SCCP_CONN_CTXT.
 * LOG:
 * LOG: Revision 1.20  1998/10/15 01:19:16  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.19  1998/10/14 23:29:37  mmiers
 * LOG: Set trace levels from INI file.
 * LOG:
 * LOG: Revision 1.18  1998/09/30 02:41:01  mmiers
 * LOG: Compromise on what we can do with SCCP.
 * LOG:
 * LOG: Revision 1.17  1998/09/29 01:24:58  mmiers
 * LOG: Implement needed MTP3 functionality.
 * LOG:
 * LOG: Revision 1.16  1998/09/28 17:37:52  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.15  1998/09/28 16:25:24  mmiers
 * LOG: Add information to debug output.
 * LOG:
 * LOG: Revision 1.14  1998/09/27 00:53:11  mmiers
 * LOG: Start cleaning up connectionless.
 * LOG:
 * LOG: Revision 1.13  1998/09/27 00:04:10  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.12  1998/09/25 21:10:57  mmiers
 * LOG: Fixup for trace.
 * LOG:
 * LOG: Revision 1.11  1998/09/24 23:27:30  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.10  1998/09/24 19:24:38  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/09/24 17:31:50  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.8  1998/09/24 16:33:11  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG: Revision 1.7  1998/09/18 22:47:58  mmiers
 * LOG: Add tracing.
 * LOG:
 * LOG: Revision 1.6  1998/09/10 21:00:25  whu
 * LOG: Must have point code when handling UDT, XUDT messages in SCCP.  Need to
 * LOG: check that the PC received in a UDT is the "localPC" in TCAP.  HOLE.
 * LOG:
 * LOG: Revision 1.5  1998/09/06 20:05:48  mmiers
 * LOG: Convert to using ROUTE_SendToApplication where possible.
 * LOG:
 * LOG: Revision 1.4  1998/07/21 21:28:29  mmiers
 * LOG: Modify SCCP implementation.
 * LOG:
 * LOG: Revision 1.3  1998/07/03 19:42:19  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.2  1998/06/30 22:47:00  mmiers
 * LOG: Start adding SCCP-as-a-thread infrastructure.
 * LOG:
 * LOG: Revision 1.1  1998/06/22 14:58:33  mmiers
 * LOG: Forgot to add this file.
 * LOG:
 *
 ****************************************************************************/

#ifndef SCCP_INTERN_H
#define SCCP_INTERN_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <its_timers.h>
#include <its_trace.h>
#include <its_ss7_trans.h>
#include <its_pegs.h>

#ident "$Id: sccp_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#include <ansi/mtp3.h>
#include <itu/mtp3.h>
#include <china/mtp3.h>
#include <japan/mtp3.h>

#include "ss7_mgmt.h"
#include "ss7_pegs.h"
#include "ss7_alarms.h"
#include "ss7_timers.h"
#include "ss7_behaviors.h"

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif

#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif


#if defined(PRC)
#define FAMILY_ITU       FAMILY_CHINA
#endif

#if defined(TTC)
#define FAMILY_ITU       FAMILY_JAPAN
#endif

/*
 * SCCP RIDs
 */
#define SCCP_CONN_RID    1
#define SCCP_CPC_RID     2
#define SCCP_LPC_RID     3
#define SCCP_REASM_RID   4
#define NumTries         0x02

    
/*
 * SCCP Tracing information
 */
#if defined ( CCITT)
extern TRACE_Data* SCCP_CCITT_TraceData;
#else
extern TRACE_Data* SCCP_ANSI_TraceData;
#endif

#define SCCP_TRACE_CRITICAL  0
#define SCCP_TRACE_ERROR     1
#define SCCP_TRACE_WARNING   2
#define SCCP_TRACE_DEBUG     3
#define SCCP_TRACE_EVENT     4

#if defined(CCITT) || defined(PRC) ||  defined(TTC)

#ifdef LOGGER_IMR
#define SCCP_CRITICAL(args) \
    LOG_PRINT_CRITICAL args;
#else
#define SCCP_CRITICAL(args) \
    TRACE(SCCP_CCITT_TraceData, SCCP_TRACE_CRITICAL, args)
#endif


#ifdef LOGGER_IMR
#define SCCP_ERROR(args) \
     LOG_PRINT_CRITICAL args;
#else
#define SCCP_ERROR(args) \
    TRACE(SCCP_CCITT_TraceData, SCCP_TRACE_ERROR, args)
#endif


#ifdef LOGGER_IMR
#define SCCP_WARNING(args) \
    LOG_PRINT_MAJOR args;
#else
#define SCCP_WARNING(args) \
    TRACE(SCCP_CCITT_TraceData, SCCP_TRACE_WARNING, args)
#endif

#ifdef LOGGER_IMR
#define SCCP_DEBUG(args) \
    LOG_PRINT_DEBUG args;
#else
#define SCCP_DEBUG(args) \
    TRACE(SCCP_CCITT_TraceData, SCCP_TRACE_DEBUG, args)
#endif


#define SCCP_EVENT(args) \
    TRACE(SCCP_CCITT_TraceData, SCCP_TRACE_EVENT, args)

#elif defined(ANSI)

#ifdef LOGGER_IMR
#define SCCP_CRITICAL(args) \
    LOG_PRINT_CRITICAL args;
#else
#define SCCP_CRITICAL(args) \
    TRACE(SCCP_ANSI_TraceData, SCCP_TRACE_CRITICAL, args)
#endif

#ifdef LOGGER_IMR
#define SCCP_ERROR(args) \
     LOG_PRINT_CRITICAL args;
#else
#define SCCP_ERROR(args) \
    TRACE(SCCP_ANSI_TraceData, SCCP_TRACE_ERROR, args)
#endif

#ifdef LOGGER_IMR
#define SCCP_WARNING(args) \
    LOG_PRINT_MAJOR args;
#else
#define SCCP_WARNING(args) \
    TRACE(SCCP_ANSI_TraceData, SCCP_TRACE_WARNING, args)
#endif

#ifdef LOGGER_IMR
#define SCCP_DEBUG(args) \
    LOG_PRINT_DEBUG args;
#else
#define SCCP_DEBUG(args) \
    TRACE(SCCP_ANSI_TraceData, SCCP_TRACE_DEBUG, args)
#endif

#define SCCP_EVENT(args) \
    TRACE(SCCP_ANSI_TraceData, SCCP_TRACE_EVENT, args)

#endif

/*
 * resource file keys
 */
#define SCCP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define SCCP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define SCCP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define SCCP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define SCCP_TRACE_EVENT_STRING     ITS_TRACE_EVENT_STRING

#define SCCP_TSTAT_INFO_STRING      "TstatInfo"
#define SCCP_TCOORD_CHG_STRING      "TcoordChg"
#define SCCP_TIGNORE_SST_STRING     "TignoreSST"
#define SCCP_TRTG_STAT_INFO_STRING  "TrtgStatInfo"
#define SCCP_TCONN_STRING           "Tconnect"
#define SCCP_TRESET_STRING          "Treset"
#define SCCP_TRELEASE_STRING        "Trelease"
#define SCCP_TINACT_SEND_STRING     "Tias"
#define SCCP_TINACT_RECV_STRING     "Tiar"
#define SCCP_TGUARD_STRING          "Tguard"
#define SCCP_TREASSEM_STRING        "Treassembly"
#define SCCP_TINTERVAL_STRING       "Tinterval"
#define SCCP_TREPEAT_REL_STRING     "TrepeatRelease"


#define SCCP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define SCCP_ERROR_STRING           ITS_ERROR_STRING
#define SCCP_WARNING_STRING         ITS_WARNING_STRING
#define SCCP_DEBUG_STRING           ITS_DEBUG_STRING
#define SCCP_EVENT_STRING           ITS_EVENT_STRING

#define SCCP_STDOUT_STRING          ITS_STDOUT_STRING
#define SCCP_SYSLOG_STRING          ITS_SYSLOG_STRING
#define SCCP_FILE_STRING            ITS_FILE_STRING

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define SCCP_TRACE_CRITICAL_FILE    ".itu-sccp-traceCritical"
#define SCCP_TRACE_ERROR_FILE       ".itu-sccp-traceError"
#define SCCP_TRACE_WARNING_FILE     ".itu-sccp-traceWarning"
#define SCCP_TRACE_DEBUG_FILE       ".itu-sccp-traceDebug"
#define SCCP_TRACE_EVENT_FILE       ".itu-sccp-traceEvent"

#elif defined(ANSI)

#define SCCP_TRACE_CRITICAL_FILE    ".ansi-sccp-traceCritical"
#define SCCP_TRACE_ERROR_FILE       ".ansi-sccp-traceError"
#define SCCP_TRACE_WARNING_FILE     ".ansi-sccp-traceWarning"
#define SCCP_TRACE_DEBUG_FILE       ".ansi-sccp-traceDebug"
#define SCCP_TRACE_EVENT_FILE       ".ansi-sccp-traceEvent"

#endif

#define SCCP_PROPAGATE_ERR_STRING   "PropagateERR"
#define SCCP_PROPAGATE_IT_STRING    "PropagateIT"
#define SCCP_PROPAGATE_SCMG_STRING  "PropagateSCMG"
#define SCCP_ENABLE_SCMG_STRING     "EnableSCMG"

/*
 * states
 */
typedef enum
{
    SCCP_CONN_IDLE,
    SCCP_CONN_IN_PEND,
    SCCP_CONN_OUT_PEND,
    SCCP_DATA_TRANSFER,
    SCCP_IN_RESET_PEND,
    SCCP_OUT_RESET_PEND,
    SCCP_IN_RELEASE_PEND,
    SCCP_OUT_RELEASE_PEND
}
SCCP_CONN_STATE;

typedef enum
{
    SCCP_DATA_NORMAL,
    SCCP_DATA_IN_ED,
    SCCP_DATA_OUT_ED,
    SCCP_DATA_BOTH_ED
}
SCCP_DATA_STATE;

/*
 * fragmentation/reassembly
 */
typedef struct _SCCP_Frag
{
    ITS_UINT  nextFragKey;
    ITS_USHORT           len;
    ITS_OCTET           data[SCCP_LONG_DATA_MAX];
}
SCCP_DATA_FRAG;

/*
 * connection context
 */
typedef struct
{
    ITS_OCTET       type;
    ITS_MUTEX       lock;
    MTP3_HEADER     inLabel;
    MTP3_HEADER     outLabel;
    ITS_CTXT        connRef;
    ITS_CTXT        assocRef;
    SCCP_CONN_STATE state;
    SCCP_DATA_STATE dataState;
    ITS_SERIAL      connectTimer;
    ITS_SERIAL      releaseTimer;
    ITS_SERIAL      repeatReleaseTimer;
    ITS_SERIAL      intervalTimer;
    ITS_SERIAL      resetTimer;
    ITS_SERIAL      sendInactivity;
    ITS_SERIAL      receiveInactivity;
    ITS_OCTET       rlsdntries;   /*change for bug 629 (multiple rlsd)*/
    ITS_OCTET       reprlsdntries;/*change for bug 629 (multiple rlsd)*/
    ITS_OCTET       resetntries;/*change for bug 629 (multiple rlsd)*/
    ITS_BOOLEAN     isIntermediate;
    ITS_BOOLEAN     sequenceOn;
    ITS_UINT        slref;
    ITS_UINT        dlref;
    ITS_UINT        totalDataLen;
    ITS_UINT        startFragKey;
    SCCP_ADDR       oaddr;
    SCCP_ADDR       daddr;
    ITS_OCTET       sequenceSLS;
    ITS_OCTET       windowSize;
    ITS_OCTET       pclass;
    ITS_OCTET       fsn;
    ITS_OCTET       rsn;
    ITS_OCTET       lssn;
}
SCCP_CONN_CTXT;


#define    SCOC_TIMER_TYPE          0x01
#define    SCLC_TIMER_TYPE          0x02
#define    MAX_SEG_REF_LEN          4
typedef struct
{
    ITS_OCTET     type;
    ITS_INT       refno;
    ITS_UINT       maxDataLen;
    ITS_SERIAL    reasmTimer;
    ITS_OCTET     remainingSegment;
    ITS_UINT      totalDataLen;
    ITS_OCTET     startFragKey[SCCP_MAX_ADDR_LEN + MAX_SEG_REF_LEN];
    ITS_OCTET     keyLen;
}
SCCP_REASM_CTXT;

/*
 * generic SCCP functions.
 */
void SCCP_DeleteLocalReference_ANSI(ITS_CTXT cref);
void SCCP_DeleteLocalReference_CCITT(ITS_CTXT cref);
int  SCCP_AddSegmentRef_CCITT(ITS_OCTET *dsmKey,
                              ITS_OCTET keyLen, ITS_INT maxDataLen, 
                              ITS_OCTET remainingSegment,
                              ITS_OCTET dataLen, 
                              ITS_OCTET *data,
                              ITS_INT segRefNum);
void SCCP_DeleteSegmentRef_CCITT(ITS_OCTET *dsmKey,
                                 ITS_OCTET keyLen, 
                                 SCCP_REASM_CTXT *ctxt);

int SCCP_AddSegmentRef_ANSI(ITS_OCTET *dsmKey,
                              ITS_OCTET keyLen, ITS_INT maxDataLen,
                              ITS_OCTET remainingSegment,
                              ITS_OCTET dataLen,
                              ITS_OCTET *data,
                              ITS_INT segRefNum);

void SCCP_DeleteSegmentRef_ANSI(ITS_OCTET *dsmKey,
                                 ITS_OCTET keyLen,
                                 SCCP_REASM_CTXT *ctxt);

int SCLC_PutDataInFragList(ITS_OCTET *dsmKey,
                           ITS_OCTET dsmKeyLen, 
                           SCCP_REASM_CTXT *ctxt,
                           ITS_OCTET *data,
                           ITS_OCTET len);
int SCOC_PutDataInFragList(ITS_UINT *startIndex,
                           ITS_UINT segRefNum, 
                           ITS_OCTET *data,
                           ITS_OCTET len);

int SCOC_GetDataFromFragList(ITS_OCTET *data, ITS_UINT *startIndex);
int SCLC_GetDataFromFragList(ITS_OCTET *data, ITS_OCTET *startKey,
                             ITS_OCTET keyLen);

int  SCLC_GetFirstSegmentData(ITS_OCTET *data,
                              ITS_OCTET *startKey, ITS_OCTET keyLen);
void SCLC_FreeFragList(ITS_OCTET *startKey, ITS_OCTET keyLen);

int ANSI_SCCPHandleAPPMsg_ANSI(ITS_EVENT *ev);
int ANSI_SCCPHandleMTP3Msg_ANSI(ITS_EVENT *ev);

int SCCPHandleAPPMsg_CCITT(ITS_EVENT *ev);
int SCCPHandleMTP3Msg_CCITT(ITS_EVENT *ev);

int SCCP_GTTTranslate_ANSI(MTP3_HEADER_ANSI *mtp3,
                           ITS_UINT *dpc, ITS_OCTET ai,
                           ITS_UINT pc, ITS_OCTET ssn,
                           ITS_OCTET* gttInfo, ITS_USHORT gttLen,
                           SCCP_ADDR* transAddr,
                           ITS_SCCP_IE *ies, int ieCount);
int SCCP_GTTTranslate_CCITT(MTP3_HEADER *mtp3,
                            ITS_UINT *dpc, ITS_OCTET ai,
                            ITS_UINT pc, ITS_OCTET ssn,
                            ITS_OCTET* gttInfo, ITS_USHORT gttLen,
                            SCCP_ADDR* transAddr,
                            ITS_SCCP_IE *ies, int ieCount);

int SCCP_UserIntervention_ANSI(MTP3_HEADER_ANSI *mtp3,
                               ITS_OCTET addrInd,
                               ITS_UINT pc, ITS_OCTET ssn,
                               ITS_OCTET* gttInfo, ITS_USHORT gttLen,
                               SCCP_ADDR* transAddr,
                               ITS_SCCP_IE *ies, int ieCount);
int SCCP_UserIntervention_CCITT(MTP3_HEADER *mtp3,
                                ITS_OCTET addrInd,
                                ITS_UINT pc, ITS_OCTET ssn,
                                ITS_OCTET* gttInfo, ITS_USHORT gttLen,
                                SCCP_ADDR* transAddr,
                                ITS_SCCP_IE *ies, int ieCount);
#ifdef DT1_LOCAL
void SCCP_DeleteLocalReference_CCITTLoclRef(ITS_CTXT cref);
int INTELLINET_GetSCCPNextRef_CCITT_LoclRef(SCCP_CONN_CTXT *Ctxt);
#endif
#ifdef CR_CC_LOCAL
void CreateLocalCtxtDb(ITS_CTXT RefNum);
void UpdateLocalConTbl(SCCP_CONN_CTXT *Ctxt);
int INTELLINET_GetSCCPNextRef_CCITT_GblRef(SCCP_CONN_CTXT *Ctxt);
void CreateGlobalCtxtDb(ITS_CTXT RefNum);
#endif




/*
 * SCRC functions
 */
int SCRCHandleMTP3Msg_ANSI(ITS_EVENT* ev);
int SCRCHandleSCLCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_SCCP_IE* ies, int ieCount);
int SCRCHandleSCOCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_SCCP_IE* ies, int ieCount,
                           SCCP_ADDR* cdp);

/*
 * SCLC functions
 */
int SCLCHandleRoutingFailure_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                  ITS_SCCP_IE* ies, int ieCount,
                                  ITS_OCTET reason);
int SCLCHandleSCRCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_SCCP_IE* ies, int ieCount,
                           ITS_UINT pc, ITS_OCTET ssn);
int SCLCHandleSCMGMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_SCCP_IE* ies, int ieCount);
int SCLCHandleAPPMsg_ANSI(ITS_EVENT* ev);

/*
 * SCOC functions
 */
int SCOCHandleRoutingFailure_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                  ITS_SCCP_IE* ies, int ieCount,
                                  ITS_OCTET reason);
int SCOCHandleSCRCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_SCCP_IE* ies, int ieCount,
                           ITS_UINT pc, ITS_OCTET ssn, ITS_BOOLEAN needCouple);
int SCOCHandleAPPMsg_ANSI(ITS_EVENT* ev);
int SCOCHandleTimer_ANSI(ITS_TimerData* td);

/*
 * SCMG functions
 */
int SCMGSSPCHandleMsgForProhibitedSSN_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                           ITS_SCCP_IE* ies, int ieCount,
                                           ITS_UINT pc, ITS_OCTET ssn,
                                           ITS_OCTET reason);
int SCMGHandleSCLCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_SCCP_IE* ies, int ieCount);
int SCMGHandleMTP3Msg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                           ITS_OCTET* data, ITS_USHORT len);
int SCMGHandleSSTTimeout_ANSI();
ITS_BOOLEAN SCMGIsSSTPending_ANSI(ROUTE_Info *rinfo);

void SSTCStopSST(MTP3_HEADER* mtp3, ITS_UINT pc, ITS_OCTET ssn,ITS_BOOLEAN tmrflag);

/*
 * SCRC functions
 */
int SCRCHandleMTP3Msg_CCITT(ITS_EVENT* ev);
int SCRCHandleSCLCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_SCCP_IE* ies, int ieCount);
int SCRCHandleSCOCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_SCCP_IE* ies, int ieCount,
                            SCCP_ADDR* cdp);

/*
 * SCLC functions
 */
int SCLCHandleRoutingFailure_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                   ITS_SCCP_IE* ies, int ieCount,
                                   ITS_OCTET reason);
int SCLCHandleSCRCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_SCCP_IE* ies, int ieCount,
                            ITS_UINT pc, ITS_OCTET ssn);
int SCLCHandleSCMGMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_SCCP_IE* ies, int ieCount);
int SCLCHandleAPPMsg_CCITT(ITS_EVENT* ev);
int SCLCHandleReasmTimer_CCITT(ITS_TimerData* td);


/*
 * SCOC functions
 */
int SCOCHandleRoutingFailure_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                   ITS_SCCP_IE* ies, int ieCount,
                                   ITS_OCTET reason);
int SCOCHandleSCRCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_SCCP_IE* ies, int ieCount,
                            ITS_UINT pc, ITS_OCTET ssn, ITS_BOOLEAN needCouple);
int SCOCHandleAPPMsg_CCITT(ITS_EVENT* ev);
int SCOCHandleTimer_CCITT(ITS_TimerData* td);

/*
 * SCMG functions
 */
int SCMGSSPCHandleMsgForProhibitedSSN_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                            ITS_SCCP_IE* ies, int ieCount,
                                            ITS_UINT pc, ITS_OCTET ssn,
                                            ITS_OCTET reason);
int SCMGHandleSCLCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_SCCP_IE* ies, int ieCount);
int SCMGHandleMTP3Msg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                            ITS_OCTET* data, ITS_USHORT len);
int SCMGHandleSSTTimeout_CCITT();
ITS_BOOLEAN SCMGIsSSTPending_CCITT(ROUTE_Info *rinfo);

extern ITS_BOOLEAN gcsMessageBasedRedundancyIsActive;


/*****************************************************************************
 *
 * The SCCP Management data.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * The SCCP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR       traceType[ITS_PATH_MAX];
    ITS_CHAR       traceOutput[ITS_PATH_MAX];
}
SCCPGeneralCfg;

/*
 * prototypes
 */
ITSSS7DLLAPI SCCPGeneralCfg* SCCP_GetGeneralCfg_ANSI();
ITSSS7DLLAPI int             SCCP_SetGeneralCfg_ANSI(SCCPGeneralCfg *data);
ITSSS7DLLAPI SCCPGeneralCfg* SCCP_GetGeneralCfg_CCITT();
ITSSS7DLLAPI int             SCCP_SetGeneralCfg_CCITT(SCCPGeneralCfg *data);

/*
 * input: sspc -- subsystem point code
 *         ssn -- subsystem number
 *
 * output: pointer to SCCPSubsystemInfo
 *
 * Note:
 *    Only used in if exact is true, return the exact SCCPSubsystemInfo
 *    that matches sspc and ssn, return NULL if exact match not found.
 */
ITSSS7DLLAPI SCCPSubSystemInfo* SCCP_GetSSEntry_ANSI(ITS_UINT sspc,
                                                     ITS_OCTET ni,
                                                     ITS_OCTET ssn);
ITSSS7DLLAPI SCCPSubSystemInfo* SCCP_GetSSEntry_CCITT(ITS_UINT sspc,
                                                      ITS_OCTET ni,
                                                      ITS_OCTET ssn);

/*
 * This function is used to get all the subsystem entries from the routing
 * subsytem database which will be used for getnext.
 *
 * output: entries -- array of SCCPSubsystemInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void    SCCP_GetAllSSEntries_ANSI(ITS_UINT* numEntries,
                                               SCCPSubSystemInfo** entries);
ITSSS7DLLAPI int     SCCP_SetSSEntry_ANSI(SCCPSubSystemInfo *data);
ITSSS7DLLAPI int     SCCP_RemSSEntry_ANSI(SCCPSubSystemInfo *data);
ITSSS7DLLAPI void    SCCP_GetAllSSEntries_CCITT(ITS_UINT* numEntries,
                                                SCCPSubSystemInfo** entries);
ITSSS7DLLAPI int     SCCP_SetSSEntry_CCITT(SCCPSubSystemInfo *data);
ITSSS7DLLAPI int     SCCP_RemSSEntry_CCITT(SCCPSubSystemInfo *data);


/*****************************************************************************
 *
 * SCCP Pointcode Entry
 * Entry for SCCP pointcode table
 *
 *****************************************************************************/
typedef struct
{
    ITS_UINT            pointCode;
    ITS_OCTET           ni;
    ITS_INT             variant;
    ITS_BOOLEAN         isPointcodeProhibited; /* allowed(0) or prohibited(1) */
    ITS_UINT            pcCongestLevel; /* pointcode congestion level: 0..8 */
    ITS_BOOLEAN         isAdjacent;
    ITS_OCTET           linkSet;
}
SCCPPointCodeInfo;

/*
 * input: pc -- point code
 *
 * output: pointer to SCCPPointCodeInfo
 *
 * Note:
 *    Only used if exact is true, return the exact SCCPPointCodeInfo that
 *    matches pc, return NULL if exact match not found.
 */
ITSSS7DLLAPI SCCPPointCodeInfo* SCCP_GetPointCodeEntry_ANSI(ITS_OCTET ni,
                                                            ITS_UINT pc);
ITSSS7DLLAPI SCCPPointCodeInfo* SCCP_GetPointCodeEntry_CCITT(ITS_OCTET ni,
                                                             ITS_UINT pc);

/*
 * This function is used to get all the pointcode entries from the routing
 * subsytem database which will be used for getnext.
 *
 * output: entries -- array of SCCPPointcodeInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void    SCCP_GetAllPointCodeEntries_ANSI(ITS_UINT* numEntries,
                                                      SCCPPointCodeInfo** entries);
ITSSS7DLLAPI int     SCCP_SetPointCodeEntry_ANSI(SCCPPointCodeInfo *data);
ITSSS7DLLAPI int     SCCP_RemPointCodeEntry_ANSI(SCCPPointCodeInfo *data);
ITSSS7DLLAPI void    SCCP_GetAllPointCodeEntries_CCITT(ITS_UINT* numEntries,
                                                       SCCPPointCodeInfo** entries);
ITSSS7DLLAPI int     SCCP_SetPointCodeEntry_CCITT(SCCPPointCodeInfo *data);
ITSSS7DLLAPI int     SCCP_RemPointCodeEntry_CCITT(SCCPPointCodeInfo *data);

/*****************************************************************************
 *
 * SCCP Concerned Pointcode Entry
 * Entry for SCCP Concerned Pointcode table
 *
 *****************************************************************************/
typedef struct
{
    ITS_UINT            sspc;
    ITS_OCTET           ni;
    ITS_OCTET           ssn;
    ITS_UINT            cpc;
}
SCCPConcernedPCInfo;

/*
 * input:
 *        sspc -- subsystem point code
 *         ssn -- subsystem number
 *         cpc -- concerned point code
 *
 * output: return ITS_TRUE if entry found, otherwise ITS_FALSE
 *
 * Note:
 *     Used when get exact, but since there is no extra info besides the key,
 *     Check exist will just do.
 */
ITSSS7DLLAPI SCCPConcernedPCInfo* SCCP_GetConcernedPC_ANSI(ITS_UINT sspc,
                                                           ITS_OCTET ni,
                                                           ITS_OCTET ssn,
                                                           ITS_UINT cpc);
ITSSS7DLLAPI SCCPConcernedPCInfo* SCCP_GetConcernedPC_CCITT(ITS_UINT sspc,
                                                            ITS_OCTET ni,
                                                            ITS_OCTET ssn,
                                                            ITS_UINT cpc);

/*
 * This function is used to get all the CPC entries from the routing
 * subsytem database which will be used for getnext.
 *
 * output: entries -- array of SCCPConcernedPCInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void   SCCP_GetAllCPCEntries_ANSI(ITS_UINT* numEntries,
                                               SCCPConcernedPCInfo** entries);
ITSSS7DLLAPI int    SCCP_SetConcernedPC_ANSI(SCCPConcernedPCInfo* entry);
ITSSS7DLLAPI int    SCCP_RemConcernedPC_ANSI(SCCPConcernedPCInfo* entry);
ITSSS7DLLAPI void   SCCP_GetAllCPCEntries_CCITT(ITS_UINT* numEntries,
                                                SCCPConcernedPCInfo** entries);
ITSSS7DLLAPI int    SCCP_SetConcernedPC_CCITT(SCCPConcernedPCInfo* entry);
ITSSS7DLLAPI int    SCCP_RemConcernedPC_CCITT(SCCPConcernedPCInfo* entry);

/*
 * input:
 *         pc  -- concern point code
 *         ssn -- concern subsystem number
 *         cpc -- concerned point code
 *        cssn -- concerned subsystem number
 *
 * output: return ITS_TRUE if entry found, also populate inservice field
 *         inservice  -- concerned subsystem is in service or not
 *
 * Note:
 *     Used when get exact, but since there is no extra info besides the key and
 *     the field inservice, check exist will just do.
 */
ITSSS7DLLAPI SCCPConcernedSSInfo* SCCP_GetConcernedSS_ANSI(ITS_UINT pc,
                                                           ITS_OCTET ni,
                                                           ITS_OCTET ssn,
                                                           ITS_UINT cpc,
                                                           ITS_OCTET cssn);
ITSSS7DLLAPI SCCPConcernedSSInfo* SCCP_GetConcernedSS_CCITT(ITS_UINT pc,
                                                           ITS_OCTET ni,
                                                           ITS_OCTET ssn,
                                                           ITS_UINT cpc,
                                                           ITS_OCTET cssn);

ITSSS7DLLAPI int     SCCP_SendSCMG_CCITT(SCCPConcernedSSInfo *data);
ITSSS7DLLAPI int     SCCP_SendSCMG_ANSI(SCCPConcernedSSInfo *data);

ITSSS7DLLAPI int     SCCP_SendSST_CCITT(SCCPConcernedSSInfo *data);
ITSSS7DLLAPI int     SCCP_SendSST_ANSI(SCCPConcernedSSInfo *data);

/*
 * This function is used to get all the CSS entries from the routing
 * subsytem database which will be used for getnext.
 *
 * output: entries -- array of SCCPConcernedSSInfo (not ordered)
 *         numEntries -- number of entries in the array
 *
 * This function should allocate memory for entries and the user should
 * be responsible of deallocating the memory.
 */
ITSSS7DLLAPI void    SCCP_GetAllCSSEntries_ANSI(ITS_UINT* numEntries,
                                                SCCPConcernedSSInfo** entries);
ITSSS7DLLAPI int     SCCP_SetConcernedSS_ANSI(SCCPConcernedSSInfo *entry);
ITSSS7DLLAPI int     SCCP_RemConcernedSS_ANSI(SCCPConcernedSSInfo *entry);
ITSSS7DLLAPI void    SCCP_GetAllCSSEntries_CCITT(ITS_UINT* numEntries,
                                                 SCCPConcernedSSInfo** entries);
ITSSS7DLLAPI int     SCCP_SetConcernedSS_CCITT(SCCPConcernedSSInfo *entry);
ITSSS7DLLAPI int     SCCP_RemConcernedSS_CCITT(SCCPConcernedSSInfo *entry);

/*
 * class part for SCCP management.  Note the pointer packaging for data
 * and functions
 */
typedef struct
{
    /* data part */
    PEG_Manager           *pegs;
    BEHAVIOR_Manager      *behaviors;
    TIMER_Manager         *timers;
    ALARM_Format          **alarms;

    /* function part */
    SCCPGeneralCfg*       (*GetGeneralCfg)();
    int                   (*SetGeneralCfg)(SCCPGeneralCfg *data);

    SCCPSubSystemInfo*    (*GetSSEntry)(ITS_UINT sspc, ITS_OCTET ni,
                                        ITS_OCTET ssn);
    void                  (*GetAllSSEntries)(ITS_UINT* numEntries,
                                             SCCPSubSystemInfo** entries);
    int                   (*SetSSEntry)(SCCPSubSystemInfo *data);
    int                   (*RemSSEntry)(SCCPSubSystemInfo *data);

    SCCPPointCodeInfo*    (*GetPointCodeEntry)(ITS_OCTET ni, ITS_UINT pc);
    void                  (*GetAllPointCodeEntries)(ITS_UINT* numEntries,
                                                    SCCPPointCodeInfo** entries);
    int                   (*SetPointCodeEntry)(SCCPPointCodeInfo *data);
    int                   (*RemPointCodeEntry)(SCCPPointCodeInfo *data);

    SCCPConcernedPCInfo*  (*GetConcernedPC)(ITS_UINT sspc, ITS_OCTET ni,
                                            ITS_OCTET ssn, ITS_UINT cpc);
    void                  (*GetAllCPCEntries)(ITS_UINT* numEntries,
                                              SCCPConcernedPCInfo** entries);
    int                   (*SetConcernedPC)(SCCPConcernedPCInfo* entry);
    int                   (*RemConcernedPC)(SCCPConcernedPCInfo* entry);

    SCCPConcernedSSInfo*  (*GetConcernedSS)(ITS_UINT pc, ITS_OCTET ni,
                                            ITS_OCTET ssn,
                                            ITS_UINT cpc, ITS_OCTET cssn);
    void                  (*GetAllCSSEntries)(ITS_UINT* numEntries,
                                              SCCPConcernedSSInfo** entries);
    int                   (*SetConcernedSS)(SCCPConcernedSSInfo *entry);
    int                   (*RemConcernedSS)(SCCPConcernedSSInfo *entry);
    int                   (*SendSCMG)(SCCPConcernedSSInfo *data);
    int                   (*SendSST)(SCCPConcernedSSInfo *data);
    int                   (*AddConcernedSubSystem)(ROUTE_Info *linfo,
                                                   ROUTE_Info *cinfo);
    int                   (*RemConcernedSubSystem)(ROUTE_Info *linfo,
                                                   ROUTE_Info *cinfo);
    int                   (*AddDuplicatedSubSystem)(ROUTE_Info *rinfo);
    int                   (*RemDuplicatedSubSystem)(ROUTE_Info *rinfo);
}
SCCP_MgmtClassPart;

typedef struct
{
    ITS_CoreClassPart   core;
    SCCP_MgmtClassPart  sccp;
}
SCCP_MgmtClassRec, *SCCP_MgmtClass;

typedef struct
{
  ROUTE_Info routeInfo;
  MTP3_HEADER sourceHdr;
  ITS_SERIAL serial;
  ITS_UINT SSTSuccessFlag;
  ITS_OCTET dsmNodeId;
}
SST_Info ;

/*
 * SST key
 */

typedef struct
{
  ITS_UINT opc;
  ITS_UINT dpc;
  ITS_OCTET sio;
  ITS_OCTET ssn;
  ITS_OCTET  type;
  ITS_OCTET dsmNodeId;
}
SST_Key;
extern ITSSS7DLLAPI ITS_Class SCCP_MgmtClass_ANSI;
extern ITSSS7DLLAPI ITS_Class SCCP_MgmtClass_CCITT;

void SCCP_Console_ANSI(DBC_Server *dbc, const char *cmdLine);
void SCCP_Console_CCITT(DBC_Server *dbc, const char *cmdLine);


#define TIMERS_StartSharedTimer   TIMERS_StartTimer
#define TIMERS_StartSharedUTimer  TIMERS_StartUTimer
#define TIMERS_CancelSharedTimer TIMERS_CancelTimer

#if defined(__cplusplus)
}
#endif

#endif /* SCCP_INTERN_H */
