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
 *  ID: $Id: tcap_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:32:50  yranade
 * LOG: Implementation of changes based on design doc ACC651-SDS-TCEN-V1.0.02
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:53:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.12.4  2005/01/31 10:44:32  snagesh
 * LOG: Moved TCAP management data from ss7_mgmt.h
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.12.3  2005/01/05 10:47:12  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.12.2  2005/01/04 13:45:43  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.12.1  2004/12/16 15:02:01  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.6.1  2004/10/25 20:34:11  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.5.2.1.6.2  2004/02/16 12:25:43  yranade
 * LOG: TCAP Act-Act Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.5.2.1.6.1  2004/02/16 09:20:36  mmanikandan
 * LOG: Performance Improvement.
 * LOG:
 * LOG: Revision 7.5.2.1  2003/07/14 13:41:36  yranade
 * LOG: Change MAX_CPT_ENTRIES to 8.
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.4  2002/12/04 17:12:31  ngoel
 * LOG: merge PRC code form PR6.1
 * LOG:
 * LOG: Revision 7.3  2002/11/14 22:27:38  omayor
 * LOG: Removed compilation warnings shown by gcc3.2
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:11:58  omayor
 * LOG: Minimization of DSM calls
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.9  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.8  2002/06/14 19:29:02  mmiers
 * LOG: Change signature
 * LOG:
 * LOG: Revision 6.7  2002/06/12 21:32:37  mmiers
 * LOG: Add ANSI abort processing.
 * LOG:
 * LOG: Revision 6.6  2002/04/29 17:00:12  mmiers
 * LOG: Add first cut of mgmt API for TCAP, MTP3.
 * LOG:
 * LOG: Revision 6.5  2002/03/20 20:06:44  mmiers
 * LOG: Move the ASNC library to VFrame (as on UNIX).
 * LOG:
 * LOG: Revision 6.4  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.3  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
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
 * LOG: Revision 5.4  2001/09/26 21:28:44  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/06 15:33:32  mmiers
 * LOG: Cleanup.  Add reserved NI use to TCAP.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.6  2001/04/02 21:20:25  mmiers
 * LOG: Align the string names.
 * LOG:
 * LOG: Revision 3.5  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.4  2001/02/06 18:04:31  mmiers
 * LOG: Add locks for CO SCCP and TCAP contexts.  Next, to use them.
 * LOG:
 * LOG: Revision 3.3  2000/11/29 17:50:59  mmiers
 * LOG: Weird Cisco len fix.
 * LOG:
 * LOG: Revision 3.2  2000/09/06 16:11:42  mmiers
 * LOG: Suspenders and belts work with prim queue.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:43  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/07/14 17:23:21  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:43  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.39  1999/09/10 23:10:24  mmiers
 * LOG:
 * LOG:
 * LOG: Split out white book and blue book variant behavior.
 * LOG:
 * LOG: Revision 1.38  1999/09/08 15:59:46  mmiers
 * LOG:
 * LOG:
 * LOG: Add prototype for CCITT timeout handling.
 * LOG:
 * LOG: Revision 1.37  1999/09/01 16:23:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add in component reject timer.
 * LOG:
 * LOG: Revision 1.36  1999/08/27 16:50:14  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.35  1999/08/26 23:45:04  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.34  1999/08/26 15:24:15  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.33  1999/08/26 02:21:59  mmiers
 * LOG:
 * LOG:
 * LOG: Automate QOS reflection.  Fix UNI handling (newly added code would have
 * LOG: rejected UNIs).  Try to be clearer about the position of the routing
 * LOG: label.  There is still most likely a hole (or more specifically, to
 * LOG: much override) when building a routing label after the user has
 * LOG: overriden certain fields.
 * LOG:
 * LOG: Revision 1.32  1999/06/21 18:53:58  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up ITU TCAP.  Needs extensive testing.
 * LOG:
 * LOG: Revision 1.31  1999/06/15 22:32:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.30  1999/05/27 21:46:08  mmiers
 * LOG:
 * LOG:
 * LOG: Adjust the TID management for sanity.
 * LOG:
 * LOG: Revision 1.29  1999/05/27 15:52:47  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.28  1999/05/18 17:00:18  mmiers
 * LOG:
 * LOG:
 * LOG: Initial coding of ITU TCAP complete.  Much testing and fixme
 * LOG: removal to do.
 * LOG:
 * LOG: Revision 1.27  1999/05/17 23:05:39  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.26  1999/05/12 22:54:13  mmiers
 * LOG:
 * LOG:
 * LOG: Work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.25  1999/05/11 22:45:19  mmiers
 * LOG:
 * LOG:
 * LOG: Work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.24  1999/03/17 21:37:52  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.23  1999/03/17 20:55:08  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.22  1999/03/17 18:40:00  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.21  1999/02/26 04:10:23  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.20  1999/02/17 20:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Get ITU conversion to compile.
 * LOG:
 * LOG: Revision 1.19  1999/02/17 02:29:56  mmiers
 * LOG:
 * LOG:
 * LOG: Update for ITU TCAP.
 * LOG:
 * LOG: Revision 1.18  1998/12/10 20:03:35  rsonak
 * LOG: Reflect the MTP3 header when external systems invoke us.
 * LOG:
 * LOG: Revision 1.17  1998/11/10 03:26:47  mmiers
 * LOG: Update/include the string defines.
 * LOG:
 * LOG: Revision 1.16  1998/10/14 23:29:38  mmiers
 * LOG: Set trace levels from INI file.
 * LOG:
 * LOG: Revision 1.15  1998/10/02 14:40:19  mmiers
 * LOG: Cleanup after mods.
 * LOG:
 * LOG: Revision 1.14  1998/10/02 04:05:45  mmiers
 * LOG: Improve TCAP component handling.  The only thing that needs verification
 * LOG: is reject handling.
 * LOG:
 * LOG: Revision 1.13  1998/10/02 00:42:13  mmiers
 * LOG: Fix some major CPT handling bugs in TCAP (cmp).
 * LOG:
 * LOG: Revision 1.12  1998/09/30 21:54:40  jrao
 * LOG: Make UNI work with invokes.  Basically, we don't allocate an invoke
 * LOG: context for INVOKE's received in a UNI.  Need to verify this with
 * LOG: T1.114.
 * LOG:
 * LOG: Revision 1.11  1998/09/28 20:41:10  jrao
 * LOG: Change verbage after #endif to comment.
 * LOG:
 * LOG: Revision 1.10  1998/09/18 22:47:59  mmiers
 * LOG: Add tracing.
 * LOG:
 * LOG: Revision 1.9  1998/09/06 20:05:49  mmiers
 * LOG: Convert to using ROUTE_SendToApplication where possible.
 * LOG:
 * LOG: Revision 1.8  1998/07/08 20:01:08  mmiers
 * LOG: More work on TCAP rejects.
 * LOG:
 * LOG: Revision 1.7  1998/07/08 16:46:01  mmiers
 * LOG: Restructure the reject method a little differently.
 * LOG:
 * LOG: Revision 1.6  1998/07/08 16:39:15  mmiers
 * LOG: Start thinking about reject cases.  Group into a common function.
 * LOG:
 * LOG: Revision 1.5  1998/07/01 22:53:37  mmiers
 * LOG: Add timer support in.
 * LOG:
 * LOG: Revision 1.4  1998/06/29 19:27:21  mmiers
 * LOG: Convert TCAP to use SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:29  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 23:38:43  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 21:32:29  mmiers
 * LOG: Get Vendor straightened out.
 * LOG:
 * LOG: Revision 1.14  1998/05/05 20:24:09  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.13  1998/04/29 22:45:02  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.
 * LOG:
 * LOG: Revision 1.12  1998/04/29 21:10:19  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.11  1998/04/29 00:23:17  mmiers
 * LOG: Start putting in context functions.  Should be starting debug
 * LOG: tommorrow.
 * LOG:
 * LOG: Revision 1.10  1998/04/28 22:52:00  mmiers
 * LOG: Complete the pepsy<->ITS conversion code.  This is pretty close to
 * LOG: actually working, now.  Must fill in the context management functions
 * LOG: and then debug.
 * LOG:
 * LOG: Revision 1.9  1998/04/27 20:00:24  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.8  1998/04/23 23:53:52  mmiers
 * LOG: More work on TCAP.  Down to about 30 fixme's.
 * LOG:
 * LOG: Revision 1.7  1998/04/23 17:04:03  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.6  1998/04/23 02:33:02  mmiers
 * LOG: More work on our TCAP implementation.  Made this single threaded,
 * LOG: multiple threads didn't buy anything, but did cost a *bunch* of
 * LOG: unnecessary hops between threads.  We're down to 3/2 hops in/out
 * LOG: of a process.
 * LOG:
 * LOG: Revision 1.5  1998/04/22 19:27:16  mmiers
 * LOG: Cleanup.  Approaching useability, somewhat.
 * LOG:
 * LOG: Revision 1.4  1998/04/16 16:40:03  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 16:50:09  mmiers
 * LOG: Update tcap internals.
 * LOG:
 * LOG: Revision 1.2  1998/03/19 16:34:38  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:05:35  mmiers
 * LOG: TCAP implementation for ANSI.  Not quite there yet.
 * LOG:
 * LOG: Revision 1.2  1997/12/08 22:05:04  jpakrasi
 * LOG: Update copyright information for 1998 year.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#ifndef TCAP_INTERN_H
#define TCAP_INTERN_H

#include <its_emlist.h>
#include <its_transports.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_hash.h>
#include <its_timers.h>
#include <its_pegs.h>

#ident "$Id: tcap_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#include "ss7_pegs.h"
#include "ss7_alarms.h"
#include "ss7_timers.h"
#include "ss7_behaviors.h"
#include "ss7_mgmt.h"

#define TCAP_CTX_MAX_CPT_ENTRIES    8
#define TCAP_MAX_TIDS               0xFFFFFFFF

#define TCAP_NODE_ID                0x0001U
#define TCAP_ALLOCATE_DID           0x0002U

#define ITS_TCAP_GCS_REQ            0x0003U
#define ITS_TCAP_DID_REQ            0x0004U

#ifdef __cplusplus
extern "C"
{
#endif

#define TCAP_RACE_CHECKING  1

typedef struct
{
    ITS_CTXT beginInDID;
    ITS_CTXT endInDID;
    ITS_CTXT beginOutDID;
    ITS_CTXT endOutDID;
    ITS_UINT beginTID;
    ITS_UINT endTID;
}
TCAP_TX_RANGES;

extern TCAP_TX_RANGES txRanges;
extern ITS_BOOLEAN splitDIDS;
extern ITS_BOOLEAN splitTIDS;
extern int totalTCAPNodes;
extern int localTCAPNodeID;

/*
 * component interface data structures
 */
typedef enum
{
    /* COMMON */
    ITS_CPT_IDLE,

    /* ANSI */
    ITS_CPT_OP_PENDING,
    ITS_CPT_OP_IN_PROG,

    /* ITU */
    ITS_CPT_OP_CLASS1_SENT,
    ITS_CPT_OP_CLASS2_SENT,
    ITS_CPT_OP_CLASS3_SENT,
    ITS_CPT_OP_CLASS4_SENT,
    ITS_CPT_OP_AWAIT_REJECT
}
ITS_TCAP_CPT_STATE;

typedef struct _invokeEntry
{
    ITS_BOOLEAN           inUse;
    ITS_TCAP_CPT_STATE    state;
    ITS_OCTET             invoke_id;
    ITS_SERIAL            timer;
    ITS_USHORT            timeout;  
    ITS_CTXT              did;
    ITS_UINT              ltid;
    int                   dir;

}
TCAP_INVOKE_ENTRY;

typedef enum
{
    /* common */
    ITS_TCAP_IDLE,

    /* ANSI */
    ITS_TCAP_QWOP_SENT,
    ITS_TCAP_QWIP_SENT,
    ITS_TCAP_QWOP_RCVD,
    ITS_TCAP_QWIP_RCVD,
    ITS_TCAP_CWIP_RCVD,
    ITS_TCAP_CWOP_RCVD,
    ITS_TCAP_CWOP_SENT,
    ITS_TCAP_CWIP_SENT,

    /* ITU */
    ITS_TCAP_BEGIN_SENT,
    ITS_TCAP_BEGIN_RCVD,
    ITS_TCAP_ACTIVE,
    ITS_TCAP_CONT_RCVD
}
TRANS_STATE;

typedef enum
{
    ITS_DLG_NONE,
    ITS_DLG_AARQ_SENT,
    ITS_DLG_AARQ_RCVD,
    ITS_DLG_ACTIVE
}
DIALOGUE_STATE;

/* Update as per Design ID :: D0010
 * Document ID : ACC651-SDS-TCEN-V1.0.02 
 */
typedef struct _cptEntryList
{
    TCAP_INVOKE_ENTRY     cptEntry[TCAP_CTX_MAX_CPT_ENTRIES];
    struct _cptEntryList  *next;
}
TCAP_CPT_LIST;

/*
 * trp interface structures
 */
typedef struct _transEntry
{
    ITS_MUTEX           lock;
    ITS_UINT            ltid;   
    ITS_UINT            rtid;
    ITS_UINT            rtidLen;
    ITS_CTXT            did;
    ITS_INT             dir;
    ITS_TIME            ctime;
    ITS_BOOLEAN         prearranged;
    SCCP_ADDR           oaddr;
    SCCP_ADDR           daddr;
    MTP3_HEADER         label;
    TRANS_STATE         state;
    DIALOGUE_STATE      dstate;
    DLG_QOS             qos;
    ITS_UINT            num_CptList;
    TCAP_CPT_LIST       cptList;
}
TCAP_TRANS_ENTRY;

/*
 * the global control flags defined for TCAP.
 */
extern TRACE_Data* TCAP_ANSI_TraceData;
extern TRACE_Data* TCAP_CCITT_TraceData;

/*.interface:
 *
 * When a message of a certain severity is to be traced, the appropriate
 * macro as defined below shall be called. The arguments to the macros are
 * a "printf" style format string, and a variable list of args.
 *
 * Note that all the format string and the args should be surrounded by 
 * parentheses. For example:
 *
 * TCAP_DEBUG(("Sample trace message: var1 = %d, var2 = %s.\n", var1, var2)); 
 *
 * trace possibilities:
 */
#define TCAP_TRACE_CRITICAL  0
#define TCAP_TRACE_ERROR     1
#define TCAP_TRACE_WARNING   2
#define TCAP_TRACE_DEBUG     3
#define TCAP_TRACE_EVENT     4

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define TCAP_CRITICAL(args) \
    TRACE(TCAP_CCITT_TraceData, TCAP_TRACE_CRITICAL, args)

#define TCAP_ERROR(args) \
    TRACE(TCAP_CCITT_TraceData, TCAP_TRACE_ERROR, args)

#define TCAP_WARNING(args) \
    TRACE(TCAP_CCITT_TraceData, TCAP_TRACE_WARNING, args)

#define TCAP_DEBUG(args) \
    TRACE(TCAP_CCITT_TraceData, TCAP_TRACE_DEBUG, args)

#define TCAP_EVENT(args) \
    TRACE(TCAP_CCITT_TraceData, TCAP_TRACE_EVENT, args)

#elif defined(ANSI)

#define TCAP_CRITICAL(args) \
    TRACE(TCAP_ANSI_TraceData, TCAP_TRACE_CRITICAL, args)

#define TCAP_ERROR(args) \
    TRACE(TCAP_ANSI_TraceData, TCAP_TRACE_ERROR, args)

#define TCAP_WARNING(args) \
    TRACE(TCAP_ANSI_TraceData, TCAP_TRACE_WARNING, args)

#define TCAP_DEBUG(args) \
    TRACE(TCAP_ANSI_TraceData, TCAP_TRACE_DEBUG, args)

#define TCAP_EVENT(args) \
    TRACE(TCAP_ANSI_TraceData, TCAP_TRACE_EVENT, args)

#endif

/*
 * tracing strings
 */
#define TCAP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define TCAP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define TCAP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define TCAP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define TCAP_TRACE_EVENT_STRING     ITS_TRACE_EVENT_STRING

#define TCAP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define TCAP_ERROR_STRING           ITS_ERROR_STRING
#define TCAP_WARNING_STRING         ITS_WARNING_STRING
#define TCAP_DEBUG_STRING           ITS_DEBUG_STRING
#define TCAP_EVENT_STRING           ITS_EVENT_STRING

#define TCAP_STDOUT_STRING          ITS_STDOUT_STRING
#define TCAP_SYSLOG_STRING          ITS_SYSLOG_STRING
#define TCAP_FILE_STRING            ITS_FILE_STRING

#define TCAP_REJECT_TIMEOUT_STRING  "Treject" /* ITU only */
#define TCAP_USE_RESERVED_NI_STRING "useReservedNI"
#define TCAP_VARIANT_STRING         "variant" /* ITU only */

#define TCAP_SPLIT_DIDS_STRING      "useDialogueIdRanges"
#define TCAP_SPLIT_TIDS_STRING      "useTIDRanges"
#define TCAP_TOTAL_NODES_STRING     "tcapNodesCount"
#define TCAP_LOCAL_NODE_ID_STRING   "localTcapNodeId"

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define TCAP_TRACE_CRITICAL_FILE    ".itu-tcap-traceCritical"
#define TCAP_TRACE_ERROR_FILE       ".itu-tcap-traceError"
#define TCAP_TRACE_WARNING_FILE     ".itu-tcap-traceWarning"
#define TCAP_TRACE_DEBUG_FILE       ".itu-tcap-traceDebug"
#define TCAP_TRACE_EVENT_FILE       ".itu-tcap-traceEvent"

#elif defined(ANSI)

#define TCAP_TRACE_CRITICAL_FILE    ".ansi-tcap-traceCritical"
#define TCAP_TRACE_ERROR_FILE       ".ansi-tcap-traceError"
#define TCAP_TRACE_WARNING_FILE     ".ansi-tcap-traceWarning"
#define TCAP_TRACE_DEBUG_FILE       ".ansi-tcap-traceDebug"
#define TCAP_TRACE_EVENT_FILE       ".ansi-tcap-traceEvent"

#endif

/*
 * function prototypes
 */
int TCAP_Init_CCITT();
int TCAP_Init_ANSI();
void TCAP_Term_CCITT();
void TCAP_Term_ANSI();

TCAP_TRANS_ENTRY * TCAP_AllocTransactionContext_CCITT(ITS_UINT ltid, 
                                                      ITS_OCTET *key, 
                                                      int *klen);

TCAP_TRANS_ENTRY * TCAP_AllocTransactionContext_ANSI(ITS_UINT ltid, 
                                                     ITS_OCTET *key, 
                                                     int *klen);

TCAP_TRANS_ENTRY *TCAP_FindTransactionContext_CCITT(ITS_UINT tid, 
                                                    ITS_OCTET *key,
                                                    int *klen);

TCAP_TRANS_ENTRY *TCAP_FindTransactionContext_ANSI(ITS_UINT tid, 
                                                   ITS_OCTET *key,
                                                   int *klen);

void TCAP_FreeDSMTransactionContext_CCITT(TCAP_TRANS_ENTRY *trCtxt);
void TCAP_FreeDSMTransactionContext_ANSI(TCAP_TRANS_ENTRY *trCtxt);

void TCAP_FindAndFreeTransactionContext_CCITT(ITS_UINT tid, 
                                              ITS_OCTET *key,
                                              int *klen);

void TCAP_FindAndFreeTransactionContext_ANSI(ITS_UINT tid, 
                                             ITS_OCTET *key,
                                             int *klen);

TCAP_INVOKE_ENTRY *TCAP_FindInvokeContext_CCITT(ITS_CTXT did,
                                                CPT_INV_ID *invokeId,
                                                int dir);

TCAP_INVOKE_ENTRY *TCAP_FindInvokeContext_ANSI(ITS_CTXT did,
                                               CPT_INV_ID *invokeId,
                                               int dir);

TCAP_INVOKE_ENTRY * TCAP_FindInvokeContextWithTimer_CCITT(ITS_CTXT did,
                                                          ITS_OCTET invokeId, 
                                                          ITS_SERIAL timer);

TCAP_INVOKE_ENTRY * TCAP_FindInvokeContextWithTimer_ANSI(ITS_CTXT did,
                                                         ITS_OCTET invokeId, 
                                                         ITS_SERIAL timer);

int TCAP_AllocInvokeContext_CCITT(ITS_CTXT did, TCAP_CPT *cpt,
                                  TCAP_INVOKE_ENTRY *invoke,
                                  int dir);


int TCAP_AllocInvokeContext_ANSI(ITS_CTXT did, TCAP_CPT *cpt,
                                  TCAP_INVOKE_ENTRY *invoke,
                                  int dir);

void TCAP_FreeInvokeContext_CCITT(TCAP_INVOKE_ENTRY *invoke);
void TCAP_FreeInvokeContext_ANSI(TCAP_INVOKE_ENTRY *invoke);

void TCAP_CleanInvokeContext_CCITT(ITS_CTXT did);
void TCAP_CleanInvokeContext_ANSI(ITS_CTXT did);

ITS_BOOLEAN FindPTypeAndTID_ANSI(ITS_SCCP_IE *ies, int ieCount,
                                 ITS_OCTET *pType,
                                 ITS_UINT *tid1, ITS_UINT *tid2,
                                 SCCP_ADDR *cdp, SCCP_ADDR *clp);

ITS_BOOLEAN FindPTypeAndTID_CCITT(ITS_SCCP_IE *ies, int ieCount,
                                  ITS_OCTET *pType,
                                  ITS_UINT *tid1, ITS_UINT *tid1Len,
                                  ITS_UINT *tid2, ITS_UINT *tid2Len,
                                  SCCP_ADDR *cdp, SCCP_ADDR *clp);

/*
 * portion prototypes
 */
int CMPHandleAPPMsg_ANSI(ITS_EVENT *event);
int CMPHandleTPCPIMsg_ANSI(ITS_CTXT did, TCAP_CPT *cpt);
int CMPHandleTimeout_ANSI(ITS_EVENT *event);

int TPCPIHandleCMPMsg_ANSI(ITS_EVENT *event);
int TPCPIHandleDIDClean_ANSI(ITS_CTXT did);
int TPCPIHandleAPPMsg_ANSI(ITS_EVENT *event);
int TPCPIHandleTRPMsg_ANSI(ITS_SCCP_IE *ies, int ieCount,
                          TCAP_TRANS_ENTRY *tr);

int TRPHandleCMPMsg_ANSI(ITS_EVENT *event);
int TRPHandleTPCPIMsg_ANSI(ITS_CTXT did, ITS_SCCP_IE *ies, int ieCount);
int TRPHandleSCCPMsg_ANSI(ITS_EVENT *event);

void __TCAP_SendReject_ANSI(ITS_CTXT did, TCAP_CPT *comp,
                            ITS_OCTET family, ITS_OCTET reason);
void __TCAP_SendTransReject_ANSI(ITS_SCCP_IE* ies, int ieCount,
                                 ITS_OCTET family, ITS_OCTET reason);
void __TCAP_SendTransAbort_ANSI(ITS_SCCP_IE* ies, int ieCount,
                                ITS_OCTET reason);
void __TCAP_SendAppReject_ANSI(ITS_CTXT did, TCAP_CPT *comp,
                               ITS_OCTET family, ITS_OCTET reason,
                               ITS_BOOLEAN isLast);

int TCOHandleSCCPMsg_CCITT(ITS_EVENT *event);
int TCOHandleCSLMsg_CCITT(ITS_CTXT did, ITS_SCCP_IE *ies, int ieCount);

int TSMHandleTCOCSLMsg_CCITT(ITS_CTXT did, ITS_SCCP_IE *ies, int ieCount);
int TSMHandleTCOSCCPMsg_CCITT(ITS_OCTET pType, ITS_SCCP_IE *ies, int ieCount,
                              TCAP_TRANS_ENTRY **trCtxt);

int DHAHandleCCOMsg_CCITT(ITS_EVENT *ev);
int DHAHandleCCOCancelMsg_CCITT(ITS_CTXT did, CPT_INV_ID *invId);
int DHAHandleCCOResetTimerMsg_CCITT(TCAP_INVOKE_ENTRY *invoke);
int DHAHandleDIDClean_CCITT(ITS_CTXT did);
int DHAHandleAPPMsg_CCITT(ITS_EVENT *event);
int DHAHandleTCOMsg_CCITT(ITS_SCCP_IE* ies, int ieCount,
                          TCAP_TRANS_ENTRY *tr);
int DHAHandleNoticeMsg_CCITT(ITS_SCCP_IE* ies, int ieCount);

int CSLHandleDLGMsg_CCITT(ITS_EVENT *event);

int CCOHandleAPPMsg_CCITT(ITS_EVENT *event);
int CCOHandleDHAMsg_CCITT(ITS_CTXT did, TCAP_CPT *cpt);
int CCOHandleTimeout_CCITT(ITS_EVENT *event);

void __TCAP_SendTransPAbort_CCITT(ITS_SCCP_IE* ies, int ieCount,
                                  ITS_OCTET reason);
void __TCAP_SendAppPAbort_CCITT(ITS_CTXT did, ITS_EVENT *ev,
                                ITS_OCTET reason);
void __TCAP_SendRemoteReject_CCITT(ITS_CTXT did, TCAP_CPT *comp,
                                   ITS_OCTET family, ITS_OCTET reason);
void __TCAP_SendAppReject_CCITT(ITS_CTXT did, TCAP_CPT *comp,
                                ITS_OCTET family, ITS_OCTET reason,
                                ITS_BOOLEAN isLast);

/* DSM optimisation prototypes */
TCAP_TRANS_ENTRY* TCAP_FindLocalTx_CCITT(ITS_CTXT did);
TCAP_TRANS_ENTRY* TCAP_FindLocalTx_ANSI(ITS_CTXT did);

int TCAP_GetNextIDID_CCITT(ITS_CTXT *idid);
int TCAP_GetNextIDID_ANSI(ITS_CTXT *idid);

TCAP_TRANS_ENTRY* TCAP_AllocateLocalTx_CCITT(ITS_CTXT did);
TCAP_TRANS_ENTRY* TCAP_AllocateLocalTx_ANSI(ITS_CTXT did);

int AllocateLTIDinTx_CCITT(TCAP_TRANS_ENTRY* tx);
int AllocateLTIDinTx_ANSI(TCAP_TRANS_ENTRY* tx);

int TCAP_FreeLocalTx_CCITT(ITS_CTXT did);
int TCAP_FreeLocalTx_ANSI(ITS_CTXT did);

int TCAP_PopulateLocalTx_CCITT(TCAP_TRANS_ENTRY *tx, ITS_CTXT did,
                               ITS_UINT tid, ITS_UINT tidLen,
                               SCCP_ADDR *cdp, SCCP_ADDR *clp);
int TCAP_PopulateLocalTx_ANSI(TCAP_TRANS_ENTRY *tx, ITS_CTXT did,
                               ITS_UINT tid, ITS_UINT tidLen,
                               SCCP_ADDR *cdp, SCCP_ADDR *clp);

TCAP_TRANS_ENTRY* TCAP_CopyDSMTxToLocalTx_CCITT(TCAP_TRANS_ENTRY *sharedTx);
TCAP_TRANS_ENTRY* TCAP_CopyDSMTxToLocalTx_ANSI(TCAP_TRANS_ENTRY *sharedTx);

/*
 * For the NEW TCAP redundancy
 */

#define TIMERS_StartSharedTimer   TIMERS_StartTimer
#define TIMERS_StartSharedUTimer  TIMERS_StartUTimer
#define TIMERS_CancelSharedTimer  TIMERS_CancelTimer

#define DSM_LockTable             DSM_LockTableLocal
#define DSM_UnlockTable           DSM_UnlockTableLocal
#define DSM_AllocNoLock           DSM_AllocNoLockLocal
#define DSM_FindNoLock            DSM_FindNoLockLocal
#define DSM_FreeNoLock            DSM_FreeNoLockLocal
#define DSM_CommitNoLock          DSM_CommitNoLockLocal
#define DSM_Alloc                 DSM_AllocLocal
#define DSM_Find                  DSM_FindLocal
#define DSM_Free                  DSM_FreeLocal
#define DSM_Commit                DSM_CommitLocal

int TCAP_AllocateThisDID_CCITT(ITS_CTXT nextDID);
int TCAP_AllocateThisDID_ANSI(ITS_CTXT nextDID);
int TCAP_HandleGcsEvent_CCITT(ITS_EVENT *evt);
int TCAP_HandleGcsEvent_ANSI(ITS_EVENT *evt);

/*****************************************************************************
 *
 * The TCAP Management data.
 *
 *****************************************************************************/
/*
 * management data for TCAP
 */

/*****************************************************************************
 *
 * The TCAP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
TCAPGeneralCfg;

/*
 * prototypes
 */
ITSSS7DLLAPI TCAPGeneralCfg* TCAP_GetGeneralCfg_ANSI();
ITSSS7DLLAPI int             TCAP_SetGeneralCfg_ANSI(TCAPGeneralCfg *data);
ITSSS7DLLAPI TCAPGeneralCfg* TCAP_GetGeneralCfg_CCITT();
ITSSS7DLLAPI int             TCAP_SetGeneralCfg_CCITT(TCAPGeneralCfg *data);


/*****************************************************************************
 *
 * The TCAP Local Subsystem
 *
 *****************************************************************************/
typedef struct
{
    ITS_UINT                  pointcode;
    ITS_OCTET                 ni;
    ITS_OCTET                 ssn;
}
TCAPSubSystemInfo;

/*
 * Prototypes
 */

ITSSS7DLLAPI int TCAP_SetLocalSSEntry_CCITT(TCAPSubSystemInfo *data);
ITSSS7DLLAPI int TCAP_SetLocalSSEntry_ANSI(TCAPSubSystemInfo *data);


typedef struct
{
    /* data part */
    PEG_Manager         *pegs;
    BEHAVIOR_Manager    *behaviors;
    TIMER_Manager       *timers;
    ALARM_Format        **alarms;
}
TCAP_MgmtClassPart;

typedef struct
{
    ITS_CoreClassPart   core;
    TCAP_MgmtClassPart  tcap;
}
TCAP_MgmtClassRec, *TCAP_MgmtClass;

extern ITSSS7DLLAPI ITS_Class TCAP_MgmtClass_ANSI;
extern ITSSS7DLLAPI ITS_Class TCAP_MgmtClass_CCITT;

void TCAP_Console_ANSI(DBC_Server *dbc, const char *cmdLine);
void TCAP_Console_CCITT(DBC_Server *dbc, const char *cmdLine);

#ifdef __cplusplus
}
#endif

#endif /* TCAP_INTERN_H */

