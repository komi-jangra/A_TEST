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
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:32  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2.8.3  2006/09/14 15:58:50  sjaddu
 * LOG: Commiting with Emergency Fix.
 * LOG:
 * LOG: Revision 9.2.8.1  2006/07/04 12:42:22  gdevanand
 * LOG: Fix for MTP3 Emergency Alignment (Magesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/01 12:01:22  ssingh
 * LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.1.8.2  2004/08/10 12:25:40  kannanp
 * LOG: modify the conter  PEG_MTP3_LINK_NUM_PEGS - propagated from TCS.
 * LOG:
 * LOG: Revision 7.8.2.1.8.1  2004/07/09 07:32:07  dsatish
 * LOG: Merging activity for timeslot changes
 * LOG:
 * LOG: Revision 7.8.2.1  2003/02/14 07:15:15  randresol
 * LOG: Add interface LINK_DumpLinkInfo
 * LOG:
 * LOG: Revision 7.8  2003/02/13 10:43:58  ttipatre
 * LOG: Peg value modified.
 * LOG:
 * LOG: Revision 7.7  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.6  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.5  2002/12/24 07:32:40  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/12/20 21:07:52  randresol
 * LOG: Add LINK_GetTransportId interface
 * LOG:
 * LOG: Revision 7.3  2002/12/06 22:55:39  randresol
 * LOG: Add LINK_GetTransportId interface
 * LOG:
 * LOG: Revision 7.2  2002/11/09 21:16:26  randresol
 * LOG: Add definitions for Route Reader/Writer lock in DSM
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.11  2002/07/24 17:20:53  randresol
 * LOG: Fix bugs found during functionality testing
 * LOG:
 * LOG: Revision 6.10  2002/06/21 20:14:23  randresol
 * LOG: Add function LINKSET_ParseRoutes
 * LOG:
 * LOG: Revision 6.9  2002/06/19 18:38:07  mmiers
 * LOG: Add family
 * LOG:
 * LOG: Revision 6.8  2002/06/06 15:35:51  mmiers
 * LOG: Move pegs to proper API.  Think next time.
 * LOG:
 * LOG: Revision 6.7  2002/06/06 15:34:26  mmiers
 * LOG: Duplicate field.
 * LOG:
 * LOG: Revision 6.6  2002/06/05 19:53:04  mmiers
 * LOG: Add pegs
 * LOG:
 * LOG: Revision 6.5  2002/05/14 18:51:56  omayor
 * LOG: Add LINK_AddLinkInfoToTransport function for the UAL.
 * LOG:
 * LOG: Revision 6.4  2002/04/29 21:35:18  randresol
 * LOG: Add changes for redundant MTP3
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:02:54  randresol
 * LOG: Define cocbBuf, rtrvBuf, crBuf and routes list in shared memory
 * LOG:
 * LOG: Revision 6.2  2002/03/08 22:55:06  mmiers
 * LOG: first pass of routing in DSM
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.47  2002/02/15 23:13:47  ssharma
 * LOG: Change function signature for practicality
 * LOG:
 * LOG: Revision 5.46  2002/02/04 18:16:00  mmiers
 * LOG: Dump function
 * LOG:
 * LOG: Revision 5.45  2002/01/21 20:25:00  mmiers
 * LOG: Add distributed MTP3 awareness.
 * LOG:
 * LOG: Revision 5.44  2002/01/10 20:30:37  mmiers
 * LOG: Add SAAL capability
 * LOG:
 * LOG: Revision 5.43  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.42  2001/11/16 23:37:03  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.41  2001/11/07 01:14:54  mmiers
 * LOG: A few fields not needed anymore.
 * LOG:
 * LOG: Revision 5.40  2001/11/06 21:55:01  mmiers
 * LOG: Add needed parts for CB.  At some point when I'm feeling
 * LOG: energetic I need to split the MTP3 specific parts out of
 * LOG: link into a separate structure (and allocate that structure
 * LOG: in any MTP2 analog).
 * LOG:
 * LOG: Revision 5.39  2001/11/02 23:04:07  mmiers
 * LOG: Add a few fields for the CB logic.
 * LOG:
 * LOG: Revision 5.38  2001/10/30 23:53:01  mmiers
 * LOG: Today's fixes.
 * LOG:
 * LOG: Revision 5.37  2001/10/30 00:16:42  mmiers
 * LOG: Added fields.
 * LOG:
 * LOG: Revision 5.36  2001/10/24 17:33:40  mmiers
 * LOG: Deep thought about current routes, and queue puts.
 * LOG:
 * LOG: Revision 5.35  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.34  2001/10/18 19:01:09  mmiers
 * LOG: Rework the link/route division.  It's easier if they're in
 * LOG: a single table.
 * LOG:
 * LOG: Revision 5.33  2001/10/17 20:28:07  mmiers
 * LOG: More work on bit rotation
 * LOG:
 * LOG: Revision 5.32  2001/10/17 18:20:58  mmiers
 * LOG: Convert routing to use link information.
 * LOG:
 * LOG: Revision 5.31  2001/10/16 16:29:20  mmiers
 * LOG: Add code maps
 * LOG:
 * LOG: Revision 5.30  2001/10/05 00:51:24  mmiers
 * LOG: Add fields for CO/CB/CR.
 * LOG:
 * LOG: Revision 5.29  2001/10/03 19:42:37  mmiers
 * LOG: Missing timer.
 * LOG:
 * LOG: Revision 5.28  2001/09/28 21:32:32  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.27  2001/09/24 22:51:21  mmiers
 * LOG: Work on MTP3 integration.
 * LOG:
 * LOG: Revision 5.26  2001/09/24 21:37:37  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.25  2001/09/20 22:50:01  mmiers
 * LOG: Fields and flags from todays discussion.
 * LOG:
 * LOG: Revision 5.24  2001/09/19 23:36:14  mmiers
 * LOG: New fields and flags
 * LOG:
 * LOG: Revision 5.23  2001/09/18 22:24:28  mmiers
 * LOG: Field fixups.
 * LOG:
 * LOG: Revision 5.22  2001/09/18 21:58:00  mmiers
 * LOG: Add TLAC state
 * LOG:
 * LOG: Revision 5.21  2001/09/14 21:58:02  mmiers
 * LOG: Add SLT timers
 * LOG:
 * LOG: Revision 5.20  2001/09/14 19:09:46  mmiers
 * LOG: Add a few flags and fields
 * LOG:
 * LOG: Revision 5.19  2001/09/14 17:36:21  rsonak
 * LOG: Add T4, T5
 * LOG:
 * LOG: Revision 5.18  2001/09/13 22:33:21  mmiers
 * LOG: timers, dead state
 * LOG:
 * LOG: Revision 5.17  2001/09/13 21:41:53  vnitin
 * LOG: Updating TCOC flag
 * LOG:
 * LOG: Revision 5.16  2001/09/13 21:18:40  mmiers
 * LOG: Add a few fields
 * LOG:
 * LOG: Revision 5.15  2001/09/13 15:12:13  rsonak
 * LOG: Added more STM flag bits
 * LOG:
 * LOG: Revision 5.14  2001/09/12 21:05:17  mmiers
 * LOG: Today's update.
 * LOG:
 * LOG: Revision 5.13  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.12  2001/09/11 22:08:03  mmiers
 * LOG: Additional fields.
 * LOG:
 * LOG: Revision 5.11  2001/09/06 20:04:33  mmiers
 * LOG: Update.
 * LOG:
 * LOG: Revision 5.10  2001/09/04 23:04:40  mmiers
 * LOG: MTP3 work.
 * LOG:
 * LOG: Revision 5.9  2001/08/31 22:14:03  mmiers
 * LOG: IsUp/IsAllowed handling
 * LOG:
 * LOG: Revision 5.8  2001/08/31 14:23:10  mmiers
 * LOG: Brainstorming on MTP3, routing fixes.
 * LOG:
 * LOG: Revision 5.7  2001/08/30 20:04:06  vnitin
 * LOG: May have some extra routines.
 * LOG:
 * LOG: Revision 5.6  2001/08/29 22:37:07  mmiers
 * LOG: Add local point code to link set.
 * LOG:
 * LOG: Revision 5.5  2001/08/29 16:39:37  rsonak
 * LOG: Added relevant Timer States for a link
 * LOG:
 * LOG: Revision 5.4  2001/08/24 22:18:22  vnitin
 * LOG: More Link flags and data functions
 * LOG:
 * LOG: Revision 5.3  2001/08/21 22:50:46  mmiers
 * LOG: End of today's work.
 * LOG:
 * LOG: Revision 5.2  2001/08/21 20:21:54  mmiers
 * LOG: More routing changes for the stack.
 * LOG:
 * LOG: Revision 5.1  2001/08/17 20:19:21  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 *
 ****************************************************************************/

/*******************************************************************************
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Changes along with code change
 *                                       propagated in its_ss7_link.c
 *                                       Functions added:
 *                                       - LINK_CommitLinkNoLock(..)
 *                                       - LINK_LockTables()
 *                                       - LINK_UnlockTables()
 *                                       Structure Modified:
 *                                       - SS7_Link
 *
 ******************************************************************************/

#ifndef ITS_LINK_H
#define ITS_LINK_H

#include <stdarg.h>

#include <its.h>
#include <its_iniparse.h>
#include <its_object.h>
#include <its_list.h>
#include <its_dsmqueue.h>
#include <its_pegs.h>

#ident "$Id: its_link.h,v 1.2 2007-12-28 03:45:05 bsccs2 Exp $"

/*
 * strings
 */
#define LINKSET_INFO_STRING         "linkSetInfo"
#define LINKSET_BEGIN_STRING        "linkSetBegin"
#define LINKSET_END_STRING          "linkSetEnd"
#define LINKSET_SET_STRING          "linkSet"
#define LINKSET_NUM_TO_START_STRING "numToActivate"
#define LINKSET_ADJ_STP_STRING      "adjacentSTP"
#define LINKSET_IS_CLINK_STRING     "isCLinkSet"
#define LINKSET_IS_5BIT_STRING      "is5Bit"
#define LINK_INFO_STRING            "linkInfo"
#define LINK_BEGIN_STRING           "linkBegin"
#define LINK_END_STRING             "linkEnd"
#define LINK_CODE_STRING            "linkCode"
#define LINK_INIT_ACTIVE_STRING     "initiallyActive"
#define LINK_TERMINAL_FIXED_STRING  "terminalFixed"
#define LINK_FIXED_STRING           "dataLinkFixed"
#define LINK_TERMINAL_STRING        "terminal"
#define LINK_DATA_LINK_STRING       "timeslot"
#define LINK_SAAL_LINK_STRING       "isSAAL"
#define LINK_LOCAL_STRING           "isLocal"

/* family information.  Looks like it's time for this */
typedef enum
{
    FAMILY_ANSI,
    FAMILY_ITU,
    FAMILY_CHINA,
    FAMILY_JAPAN
}
SS7_Family;

/* forwards */
typedef struct __SS7_Link       *SS7_LinkPtr;
typedef struct __SS7_LinkSet    *SS7_LinkSetPtr;
typedef struct _ROUTE_Info      *ROUTE_InfoPtr;

/*
 * LSAC state
 */
typedef enum
{
    LINK_ACTIVITY_INACTIVE,
    LINK_ACTIVITY_ACTIVE,
    LINK_ACTIVITY_FAILED,
    LINK_ACTIVITY_ACTIVATING_RESTORING,
    LINK_ACTIVITY_WAIT_1,
    LINK_ACTIVITY_WAIT_4,
    LINK_ACTIVITY_DEACTIVE
}
LINK_ActivityState;

/*
 * LSLA state.
 */
typedef enum
{
    LINK_ACTIVATION_IDLE,
    LINK_ACTIVATION_WAIT_1,
    LINK_ACTIVATION_WAIT_2
}
LINK_ActivationState;

/*
 * LSLR state
 */
typedef enum
{
    LINK_RESTORATION_IDLE,
    LINK_RESTORATION_WAIT_1,
    LINK_RESTORATION_WAIT_2
}
LINK_RestorationState;

/*
 * LSTA state
 */
typedef enum
{
    TERMINAL_ALLOCATION_IDLE,
    TERMINAL_ALLOCATION_WAIT
}
LINK_TerminalState;

/*
 * LSDA state
 */
typedef enum
{
    LINK_ALLOCATION_IDLE,
    LINK_ALLOCATION_WAIT_1,
    LINK_ALLOCATION_WAIT_2,
    LINK_ALLOCATION_WAIT_3
}
LINK_AllocationState;

/*
 * TLAC state
 */
typedef enum
{
    LINK_UNAVAILABLE,
    LINK_AVAILABLE
}
LINK_AvailableState;

/*
 * TCBC state
 */
typedef enum
{
    CHANGEBACK_IDLE,
    CHANGEBACK_WAIT_FOR_DATA,
    CHANGEBACK_FIRST_ATTEMPT,
    CHANGEBACK_SECOND_ATTEMPT,
    CHANGEBACK_TIME_CONTROLLED_DIVERT
}
LINK_ChangebackState;

/*
 * TCOC state
 */
typedef enum
{
    CHANGEOVER_IDLE,
    CHANGEOVER_WAIT_1,
    CHANGEOVER_WAIT_2,
    CHANGEOVER_WAIT_FOR_ACK,
    CHANGEOVER_RETRIEVING,
    CHANGEOVER_WAIT_5,
    CHANGEOVER_WAIT_6,
    CHANGEOVER_WAIT_7,
    CHANGEOVER_WAIT_8
}
LINK_ChangeoverState;

/*
 * timer state
 */
typedef struct
{
    ITS_BOOLEAN     t12RetryOnOff;
    ITS_BOOLEAN     t13RetryOnOff;
    ITS_BOOLEAN     t14RetryOnOff;
    ITS_BOOLEAN     t20RetryOnOff;
    ITS_BOOLEAN     t21RetryOnOff;
}
LINK_TimerRetryState;

/*
 * flag bits
 */
#define LINK_LOC_BLOCKED                            (1U<<1)     /* TLAC */
#define LINK_REM_BLOCKED                            (1U<<2)     /* TLAC */
#define LINK_LOC_INHIBITED                          (1U<<3)     /* TLAC */
#define LINK_REM_INHIBITED                          (1U<<4)     /* TLAC */
#define LINK_INACTIVE                               (1U<<5)     /* TLAC */
#define LINK_FAILED                                 (1U<<6)     /* TLAC */
#define LINK_LIP                                    (1U<<7)     /* TLAC */
#define LINK_RIP                                    (1U<<8)     /* TLAC */
#define LINK_LBP                                    (1U<<9)     /* TLAC */
#define LINK_RBP                                    (1U<<10)    /* TLAC */
#define LINK_COP                                    (1U<<11)    /* TLAC */
#define LINK_CBP                                    (1U<<12)    /* TLAC */
#define LINK_COO                                    (1U<<13)    /* TLAC */
#define LINK_CBO                                    (1U<<14)    /* TLAC */
#define LINK_ECOO                                   (1U<<15)    /* TLAC */
#define LINK_INHIBIT_RETRY                          (1U<<16)    /* TLAC */
#define LINK_REMOTE_BSNT_RETRIEVED                  (1U<<18)    /* TCOC */
#define LINK_LOCAL_BSNT_RETRIEVED                   (1U<<19)    /* TCOC */
#define LINK_IS_UNAVAILABLE                         (1U<<20)    /* TCOC */
#define LINK_INHIBITED                              (1U<<21)    /* TSRC */
#define LINK_CHANGEOVER_COMPLETE                    (1U<<22)    /* TSRC */
#define LINK_MGMT_UNINHIBIT_REQ                     (1U<<23)    /* TLAC */
#define LINK_RTB_CLEAR_REQ                          (1U<<24)    /* TLAC */
#define LINK_RTB_CLEAR_PENDING                      (1U<<25)    /* TLAC */
#define LINK_RB_CLEAR_REQ                           (1U<<26)    /* TLAC */
#define LINK_RB_CLEAR_PENDING                       (1U<<27)    /* TLAC */
#define LINK_LOCAL_LIR                              (1U<<28)    /* TSRC */
#define LINK_REMOTE_LIR                             (1U<<29)    /* TSRC */
#define LINK_COMING_AVAILABLE                       (1U<<30)    /* TSRC */
#define LINK_CHANGE_OVER_RECEIVED                   (1U<<31)    /* TCOC */

/* SLM flags */
#define LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL    (1U<<0)     /* LSAC */
#define LINK_IS_ACTIVATING                          (1U<<1)     /* LSAC */
#define LINK_IS_RESTORING                           (1U<<2)     /* LSAC */
#define LINK_ACTIVATION_NOT_POSSIBLE                (1U<<3)     /* LSAC */
#define LINK_FIRST_FAILURE                          (1U<<4)     /* LSAC */
#define LINK_LOADED                                 (1U<<5)     /* LSAC */
#define LINK_TERMINAL_DETERMINED                    (1U<<6)     /* LSTA */
#define LINK_DATA_LINK_DETERMINED                   (1U<<7)     /* LSDA */
#define LINK_IS_AVAILABLE                           (1U<<8)     /* LSDA */
#define LINK_TERMINAL_IDLE                          (1U<<9)     /* LSTA */
#define LINK_TERMINAL_AVAILABLE                     (1U<<10)    /* LSTA */
#define LINK_EMERGENCY                              (1U<<11)    /* LSAC */
#define LINK_DATA_LINK_CONSIDERED                   (1U<<12)    /* LSDA */
#define LINK_TERMINAL_CONSIDERED                    (1U<<13)    /* LSTA */

/* SLTM flags */
#define LINK_TEST_FIRST_ATTEMPT                     (1U<<0)
#define LINK_TEST_SECOND_ATTEMPT                    (1U<<1)

/*
 * test pattern max size.  Matches value in SLTM
 */
#define LINK_MAX_PATTERN    16

/*
 * this is only relevent for true SS7.
 */
#define MAX_LINKS   16

#define MAX_LINKSETS 256
#define MAX_LINKS_PER_LINKSET 16

/* Keep this adjusted */
#define PEG_MTP3_LINK_NUM_PEGS      72  

/*
 * structure for a link.
 */
typedef struct __SS7_Link
{
    struct __SS7_Link       *next, *prev;/* transport linked list */
    /* configuration */
    ITS_BOOLEAN             initActive; /* activate when link set activates */
    ITS_BOOLEAN             termFixed;  /* terminal predetermined */
    ITS_BOOLEAN             linkFixed;  /* data link predetermined */
    ITS_BOOLEAN             isSAAL;     /* uses SAAL */
    ITS_BOOLEAN             localLink;  /* link is on local node */
    ITS_OCTET               linkCode;   /* signalling link code */
    ITS_OCTET               priority;   /* priority in this link set */
    ITS_USHORT              id;         /* transport: local data */
    ITS_USHORT              terminal;   /* signalling terminal */
    ITS_USHORT              dataLink;   /* data link identity */
    ITS_USHORT              dsmNodeId;  /* link owner        */
    ITS_USHORT              refCount;   /* reference counter on this link */
    SS7_Family              family;     /* protocol family */

    /* link set */
    SS7_LinkSetPtr          linkSet;    /* back pointer to link set */

    /* status */
    ITS_BOOLEAN             isUp;       /* active link */
    ITS_BOOLEAN             isAllowed;  /* usable link */
    ITS_OCTET               active;     /* from routing perspective */
    ITS_OCTET               congLevel;  /* congestion level */
    ITS_OCTET               cbLinkSet;  /* link set used for CBD */
    ITS_OCTET               pad;

    /* run time state */
    ITS_UINT                stFlags;    /* traffic link flags */
    ITS_UINT                slFlags;    /* management link flags */
    ITS_UINT                sltFlags;   /* testing flags */
    ITS_BOOLEAN             testPassed; /* SLTM/SLTA says ok */
    ITS_BOOLEAN             qPut;       /* transmit or enqueue */
    ITS_UINT                localBSN;   /* Changeover FSN retrived from L2 */
    ITS_UINT                remoteBSN;  /* Remote BSN received in Changeover */
    ITS_USHORT              needCBA;    /* CBD was sent for this link mask */
    ITS_USHORT              gotCBA;     /* CBA received mask */
    DSM_Queue               *cocbBuf;   /* changeover/changeback buffer queue */
    DSM_Queue               *rtrvBuf;   /* retrieval buffer queue */

    /* MTP3 needs to maintain state information */
    LINK_AvailableState     availableState;
    LINK_ChangeoverState    changeoverState;
    LINK_ChangebackState    changebackState;
    LINK_TimerRetryState    timerRetryState;
    LINK_ActivityState      activityState;
    LINK_ActivationState    activationState;
    LINK_RestorationState   restorationState;
    LINK_TerminalState      terminalState;
    LINK_AllocationState    allocationState;

    /* timer serials */
    ITS_SERIAL  t1;
    ITS_SERIAL  t2;
    ITS_SERIAL  t3;
    ITS_SERIAL  t4;
    ITS_SERIAL  t5;
    ITS_SERIAL  t7;
    ITS_SERIAL  t12;
    ITS_SERIAL  t13;
    ITS_SERIAL  t14;
    ITS_SERIAL  t17;
    ITS_SERIAL  t19;
    ITS_SERIAL  t20;
    ITS_SERIAL  t21;
    ITS_SERIAL  t32;
    ITS_SERIAL  t33;
    ITS_SERIAL  t34;

    /* test timers */
    ITS_SERIAL  slt1;
    ITS_SERIAL  slt2;

    /* test pattern */
    ITS_OCTET   testPattern[LINK_MAX_PATTERN];

    /* counters */
    ITS_UINT    pegs[PEG_MTP3_LINK_NUM_PEGS];

    /* Link Level pegs for MTP3 */
    PEG_Manager MTP3_LINK_PEGS;
}
SS7_Link;


/*
 * SLS balancing defines
 */
#define MAX_SLS_8BIT_VALUE  127
#define MAX_SLS_5BIT_VALUE  15
#define SLS_5BIT_ARRAY_SIZE (MAX_SLS_5BIT_VALUE+1)
#define SLS_8BIT_ARRAY_SIZE (MAX_SLS_8BIT_VALUE+1)

/*
 * restart state
 */
typedef enum
{
    RESTART_IDLE,
    RESTART_WAIT_1,
    RESTART_WAIT_2,
    RESTART_WAIT_3
}
LINKSET_RestartState;


/*
 * structure for a link set
 */
typedef struct __SS7_LinkSet
{
    ITS_UINT                adjacent;   /* adjacent point code */
    ITS_UINT                lpc;        /* local point code for link set */
    ITS_UINT                numLinks;   /* number of entries in link set */
    ITS_UINT                maxLinks;   /* number of slots */
    ITS_UINT                numToStart; /* number of links that should be active */
    ITS_BOOLEAN             adjSTP;     /* adjacent is an STP */
    ITS_BOOLEAN             isC;        /* do bit rotation or not */
    ITS_BOOLEAN             is5Bit;     /* is 5 bit rotation */
    ITS_OCTET               linkSet;    /* link set id */
    ITS_OCTET               ni;         /* network indicator */
    ITS_USHORT              pad;        /* explicit padding */
    SS7_Family              family;     /* protocol family */

    /* object mapping pointers and state */
    SS7_LinkPtr             *links;     /* link information */
    DSM_Queue               *routes;    /* pointer to route list */
    ITS_BOOLEAN             isUp;       /* link set is active */
/* Magesh 28-Jun-06 */

    ITS_BOOLEAN             firstLink;  /* first link in linkset to go INS */

/* End */
    /* non-configuration items */
    ITS_UINT                useNext;    /* round robin counter */
    LINKSET_RestartState    state;      /* only one on this guy */
    ITS_BOOLEAN             adjRestart; /* adjacent is restarting */
    ITS_BOOLEAN             gotTRA;     /* got TRA from adjacent */
    ITS_UINT                seqNum;     /* current sequence number */
    ITS_OCTET               *defaultMap;/* SLS balancing map */
    ITS_OCTET               *codeMap;   /* SLS map to SLCs */
    ITS_OCTET               *lastDown;  /* down ordering */
    ITS_UINT                ldIdx;      /* queue top */

    /* linkset timers */
    ITS_SERIAL  t22;
    ITS_SERIAL  t23;
    ITS_SERIAL  t24;
    ITS_SERIAL  t26;
}
SS7_LinkSet;

typedef int (*LINKSET_ParseFunc) (ROUTE_InfoPtr rinfo);

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * NOTE: This subsystem shares the routing lock with the ROUTE
 * API.
 */

/*
 * link set API
 */
ITSDLLAPI int               LINKSET_ParseLinkSetInfo(RESFILE_Manager *res,
                                                     const char *section);
ITSDLLAPI int               LINKSET_AddLinkSet(SS7_LinkSetPtr linkSet);
ITSDLLAPI SS7_LinkSetPtr    LINKSET_FindLinkSet(ITS_OCTET linkSet);
ITSDLLAPI int               LINKSET_RemLinkSet(SS7_LinkSetPtr linkSet);
ITSDLLAPI int               LINKSET_CommitLinkSet(SS7_LinkSetPtr linkSet);
ITSDLLAPI int               LINKSET_SetLinkSetState(SS7_LinkSetPtr link,
                                                    ITS_BOOLEAN isUp);
/* Magesh 28-Jun-06*/

ITSDLLAPI int               LINKSET_SetLinkSetFirstLink(SS7_LinkSetPtr linkSet,
                                                        ITS_BOOLEAN firstLink);

/* End */
ITSDLLAPI int               LINKSET_GetLinkSetState(SS7_LinkSetPtr link,
                                                    ITS_BOOLEAN *isUp);
ITSDLLAPI void              LINKSET_AddActiveLink(SS7_LinkSetPtr ls,
                                                  ITS_OCTET linkCode);
ITSDLLAPI void              LINKSET_RemoveActiveLink(SS7_LinkSetPtr ls,
                                                     ITS_OCTET linkCode);
ITSDLLAPI void              LINKSET_PrintCodeMap(SS7_LinkSetPtr ls);

ITSDLLAPI int               LINKSET_DumpLinkSetHashtable(char** pStrDump);
ITSDLLAPI int LINK_DumpLinkInfo(char **pStrDump, ITS_OCTET ls, ITS_OCTET lc);
/*
 * internal use only
 */
ITSDLLAPI SS7_LinkSetPtr    LINKSET_FindLinkSetNoLock(ITS_OCTET linkSet);
ITSDLLAPI int               LINKSET_AddRoute(SS7_LinkSetPtr linkSet,
                                             ROUTE_InfoPtr rinfo);
ITSDLLAPI int               LINKSET_RemRoute(SS7_LinkSetPtr linkSet,
                                             ROUTE_InfoPtr rinfo);

ITSDLLAPI int LINKSET_ParseRoutes(SS7_LinkSetPtr ls, LINKSET_ParseFunc func);

/*
 * Link API.  Note the parse interface uses a void pointer
 * that really resolves to TRANSPORT_Control *.  Using the
 * correct type is counterindicated due to a circular dependency.
 */
ITSDLLAPI int           LINK_ParseLinkInfo(void *tc);
ITSDLLAPI int           LINK_AddLink(ITS_OCTET linkSet, SS7_LinkPtr link);
ITSDLLAPI SS7_LinkPtr   LINK_FindLink(ITS_OCTET linkSet, ITS_OCTET linkCode);
ITSDLLAPI SS7_LinkPtr   LINK_FindLinkNoLock(ITS_OCTET linkSet, ITS_OCTET linkCode);
ITSDLLAPI ITS_USHORT LINK_GetTransportId(SS7_LinkPtr link);
ITSDLLAPI int LINK_SetLinkQPut(SS7_LinkPtr link, ITS_BOOLEAN isQ);
ITSDLLAPI int           LINK_RemLink(ITS_OCTET linkSet, SS7_LinkPtr link);
ITSDLLAPI int           LINK_CommitLink(SS7_LinkPtr link);
ITSDLLAPI int           LINK_CommitLinkNoLock(SS7_LinkPtr link);
ITSDLLAPI int           LINK_LockTables();
ITSDLLAPI int           LINK_UnlockTables();
ITSDLLAPI int           LINK_SetLinkState(SS7_LinkPtr link,
                                          ITS_BOOLEAN isUp);
ITSDLLAPI int           LINK_GetLinkState(SS7_LinkPtr link,
                                          ITS_BOOLEAN *isUp);
ITSDLLAPI int           LINK_SetLinkStatus(SS7_LinkPtr link,
                                           ITS_BOOLEAN isAllowed);
ITSDLLAPI int           LINK_GetLinkStatus(SS7_LinkPtr link,
                                           ITS_BOOLEAN *isAllowed);
ITSDLLAPI int           LINK_SetLinkCongestion(SS7_LinkPtr link,
                                               ITS_OCTET congLevel);
ITSDLLAPI int           LINK_GetLinkCongestion(SS7_LinkPtr link,
                                               ITS_OCTET *congLevel);

ITSDLLAPI void LINK_AddLinkInfoToTransport(void *trans, SS7_LinkPtr lp);
ITSDLLAPI void LINK_RemLinkInfoFromTransport(SS7_LinkPtr lp);

typedef ITS_ClassRec        LINKSET_ClassRec;

#define LINKSET_CLASS_NAME  "LINKSET_CLASS"

ITSDLLAPI extern LINKSET_ClassRec     itsLINKSET_ClassRec;
ITSDLLAPI extern ITS_Class            itsLINKSET_Class;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_LINK_H */
