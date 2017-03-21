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
 *  ID:$Id: itu-isup_alarms.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.10.1.12.4  2005/02/22 11:54:18  ssingh
 * LOG: Bug fix for #1592/1593/1594/1595/1596/1597/1598/1599/1600
 * LOG: (Ramesh KV)
 * LOG:
 * LOG: Revision 7.5.10.1.12.3  2005/01/05 10:03:08  csireesh
 * LOG: Removed unwanted alarms
 * LOG:
 * LOG: Revision 7.5.10.1.12.2  2004/12/29 14:15:01  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.5.10.1.12.1  2004/12/06 14:03:05  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.5.10.1  2004/01/05 10:04:51  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.5.4.3  2003/12/12 09:21:11  ssingh
 * LOG: Alarm Text changed for some "RangeAndStatus check failed" Alarms.
 * LOG:
 * LOG: Revision 7.5.4.2  2003/10/30 14:39:37  sjaddu
 * LOG: Some formats changed.
 * LOG:
 * LOG: Revision 7.5.4.1  2003/10/17 07:16:09  akumar
 * LOG: Fixed req no R480-17 for TCS.
 * LOG:
 * LOG: Revision 7.5  2003/02/04 10:06:33  aganguly
 * LOG: Added new alarms for ISUP.Cleanup of unwanted alarms to be done in Release 6.4.
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.3  2002/10/24 08:51:40  ssingh
 * LOG: Removed extra comments.
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:54:38  sjaddu
 * LOG: Added ITU ISUP Alarms.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.2  2002/03/20 23:30:18  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.1  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 *
 ****************************************************************************/

#include <its_assertion.h>

#include "ss7_alarms.h"

ITS_UINT ISUP_AlarmLevel_CCITT = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(CCITT_ISUP,  3401,
                    "ISUP Failed to initialize",
                    ALARM_LVL_CRIT,"Initialize",
                    "ISUP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3402,
                    "ISUP Intialized Successfully",
                    ALARM_LVL_INFO, "Initialize",
                    "ISUP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3403,
                    "ISUP Terminating",
                    ALARM_LVL_INFO, "Terminate",
                    "ISUP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3404,
                    "ISUP Aborting",
                    ALARM_LVL_CRIT, "ISUPThread",
                    "ISUP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3405,
                    "Could not find config info:OPC,DPC,NI,CIC",
                    ALARM_LVL_MAJOR, "HandleMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3406,
                    "Message received with bad CIC",
                    ALARM_LVL_MINOR, "HandleMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3407,
                    "Bad Message received from remote",
                    ALARM_LVL_MINOR, "HandleMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3408,
                    "Unrecognised Info: CIC released",
                    ALARM_LVL_INFO, "HandleMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3409,
                    "Destination Unreachable",
                    ALARM_LVL_CRIT, "HandleMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3410,
                    "Remote User Part Unavailable",
                    ALARM_LVL_CRIT, "HandleMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3411,
                    "Rcvd MTP3 Pause: Destination not Reachable",
                    ALARM_LVL_CRIT, "HandleMTP3MgmtMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3412,
                    "Rcvd MTP3 Resume: Destination Reachable",
                    ALARM_LVL_INFO, "HandleMTP3MgmtMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3413,
                    "Rcvd MTP3 Status: Remote User Part Inaccess",
                    ALARM_LVL_MINOR, "HandleMTP3MgmtMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3414,
                    "Rcvd MTP3 Status: Remote User Part Unequipped",
                    ALARM_LVL_MINOR, "HandleMTP3MgmtMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3415,
                    "Received Reset conformation: CIC IDLE",
                    ALARM_LVL_INFO, "Received_RLC",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3416,
                    "----",
                    ALARM_LVL_INFO, "----",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3417,
                    "GRA received: CIC remote blocked",
                    ALARM_LVL_INFO, "BlockingCGRSToBLR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3418,
                    "Reset received: CIC remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCRRToBLR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3419,
                    "ANM timer T9 expired in WAIT_INCOMING_ANM state",
                    ALARM_LVL_MINOR, "Received_TimeoutT9",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3420,
                    "Group Reset Rcvd: CIC remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCGRRToBLR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3421,
                    "CIC remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCPCIToBLR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3422,
                    "Local Congestion Level1",
                    ALARM_LVL_MINOR, "CheckLocalCongestion",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3423,
                    "Local Congestion Level2",
                    ALARM_LVL_MAJOR, "CheckLocalCongestion",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3424,
                    "Local Congestion Level Ceased",
                    ALARM_LVL_INFO, "CheckLocalCongestion",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3425,
                    "Reset rcvd: CIC Hw Remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCRRToHRB",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3426,
                    "----",
                    ALARM_LVL_INFO, "----",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3427,
                    "Group Reset rcvd: CIC Hw Remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCGRRToHRB",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3428,
                    "CIC HW Remotely Unblocked",
                    ALARM_LVL_INFO, "UnblockingCPCIToHRB",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3429,
                    "Second RLC timer T5  expired in WAIT_OUT_REL state",
                    ALARM_LVL_MINOR, "Received_TimeoutT5",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3430,
                    "Rcvd unexpected BLA",
                    ALARM_LVL_MINOR, "CSC_Received_BLA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3431,
                    "Rcvd BLA from remote : CIC Local Blocked",
                    ALARM_LVL_INFO, "CSC_Received_BLA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3432,
                    "Rcvd BLA from Application. : CIC Remote Blocked",
                    ALARM_LVL_INFO, "CSC_Received_BLA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3433,
                    "CGB from remote : RangeStatus check failed ",
                    ALARM_LVL_MINOR, "CSC_Received_CGB",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3434,
                    "CGBA from Application : CIC Remotely Blocked",
                    ALARM_LVL_INFO, "CSC_Received_CGBA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3435,
                    "CGBA from Application : RangeStatus check failed",
                    ALARM_LVL_MAJOR, "CSC_Received_CGBA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3436,
                    "CGBA from remote : Invalid Acknowledgement",
                    ALARM_LVL_INFO, "CSC_Received_CGBA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3437,
                    "CGBA from remote : CIC Locally Blocked.",
                    ALARM_LVL_INFO, "CSC_Received_CGBA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3438,
                    "CGU from remote: RangeStatus check failed ",
                    ALARM_LVL_MINOR, "CSC_Received_CGU",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3439,
                    "CGUA from remote : RangeStatus check failed ",
                    ALARM_LVL_MAJOR, "CSC_Received_CGUA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3440,
                    "CGUA from remote : Invalid Acknowledgement",
                    ALARM_LVL_MAJOR, "CSC_Received_CGUA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3441,
                    "CGUA from remote : CIC's Locally Unblocked",
                    ALARM_LVL_MINOR, "CSC_Received_CGUA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3442,
                    "CGUA from Application : CIC Remotely Unblocked",
                    ALARM_LVL_MINOR, "CSC_Received_CGUA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3443,
                    "GRA from remote : RangeStatus check failed ",
                    ALARM_LVL_MAJOR, "CSC_Received_GRA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3444,
                    "GRA from remote : Invalid Acknowledgement",
                    ALARM_LVL_MAJOR, "CSC_Received_GRA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3445,
                    "GRA from remote : CICs reseted",
                    ALARM_LVL_INFO, "CSC_Received_GRA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3446,
                    "GRA from Application : CIC reseted",
                    ALARM_LVL_INFO, "CSC_Received_GRA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3447,
                    "GRS from remote : RangeStatus check failed",
                    ALARM_LVL_MAJOR, "CSC_Received_GRS",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3448,
                    "UBA from remote : CIC Locally Unblocked",
                    ALARM_LVL_INFO, "CSC_Received_UBA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3449,
                    "UBA Received from Application : CIC Remotely Unblocked",
                    ALARM_LVL_MINOR, "CSC_Received_UBA",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3450,
                    "First Blocking timer T12 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT12",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3451,
                    "Second Blocking timer T13 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT13",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3452,
                    "First Unblocking timer T14 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT14",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3453,
                    "Second Unblocking timer T15 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT15",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3454,
                    "First Reset timer T16 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT16",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3455,
                    "Second Reset Timer T17 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT17",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3456,
                    "First CGBA timer T18 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT18",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3457,
                    "second CGBA timer T19 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT19",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3458,
                    "First CGUA timer T20 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT20",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3459,
                    "Second CGUA timer T21 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT21",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3460,
                    "First GRA timer T22 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT22",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3461,
                    "Second GRA timer T23 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT23",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3462,
                    "CCR Receive timer T27 expired in IDLE state",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutT27",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3463,
                    "CQM timer T28 expired",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3464,
                    "Timer T33 expired in WAIT_INCOMING_ACM state",
                    ALARM_LVL_MAJOR, "Received_TimeoutT33",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3465,
                    "Timer T36 expired in WAIT_INCOMING_COT/IDLE state",
                    ALARM_LVL_MAJOR, "Received_TimeoutT36",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3466,
                    "Timer T39 expired in IDLE state",
                    ALARM_LVL_MAJOR, "Received_TimeoutT39",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3467,
                    "Rcvd Unexpected Timeout",
                    ALARM_LVL_MINOR, "Received_UnexpectedTimeout",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3468,
                    "COT timer T8 expired in IDLE state",
                    ALARM_LVL_INFO, "Received_TimeoutT8",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3469,
                    "ACM timer T7 expired in WAIT_INCOMING_ACM state",
                    ALARM_LVL_MINOR, "Received_TimeoutT7",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3470,
                    "Resume timer T6 expired in WAIT_INCOMING_RES state",
                    ALARM_LVL_MINOR, "Received_TimeoutT6",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3471,
                    "Second RLC timer T5  expired in WAIT_IN_RLC state",
                    ALARM_LVL_MINOR, "Received_TimeoutT5",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3472,
                    "Congestion timer T3 expired in IDLE state",
                    ALARM_LVL_MINOR, "Received_TimeoutT3",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3473,
                    "Suspend timer T2 expired in WAIT_INCOMING_RES state",
                    ALARM_LVL_MINOR, "Received_TimeoutT2",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3474,
                    "First RLC timer T1 expired in WAIT_IN_RLC state",
                    ALARM_LVL_INFO, "Received_TimeoutT1",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3475,
                    "ANM timer T9 expired in WAIT_INCOMING_ACM state",
                    ALARM_LVL_MINOR, "Received_TimeoutT9",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3476,
                    "CQM RangeStatus check failed",
                    ALARM_LVL_INFO, "Received_CQM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3477,
                    "CQR RangeStatus check failed",
                    ALARM_LVL_MINOR, "Received_CQR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3478,
                    "Incoming IAM discarded; CIC blocked",
                    ALARM_LVL_INFO, "Received_IAM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3479,
                    "Outgoing IAM discarded; CIC invalid state",
                    ALARM_LVL_INFO, "Received_IAM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3480,
                    "Unexpected RLC from remote in IDLE state: ",
                    ALARM_LVL_INFO, "Received_RLC",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3481,
                    "Received unexpected msg from remote in IDLE state:",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3482,
                    "Received unexpected INF msg from Application"
                    " in RCVD_INCOMING_ANM state",
                    ALARM_LVL_INFO, "Received_INF",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3483,
                    "Received unexpected INF msg from remote"
                    " in WAIT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_INF",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3484,
                    "Received unexpected ACM msg from Application"
                    "in WAIT_INCOMING_ACM state ",
                    ALARM_LVL_INFO, "Received_ACM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3485,
                    "Received unexpected CPG msg from Application"
                    "in WAIT_INCOMING_ACM state ",
                    ALARM_LVL_INFO, "Received_CPG",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3486,
                    "Received unexpected CON msg from Application"
                    "in WAIT_INCOMING_ACM state ",
                    ALARM_LVL_INFO, "Received_CON",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3487,
                    "Received unexpected INR msg from remote"
                    "in WAIT_INCOMING_ACM state ",
                    ALARM_LVL_INFO, "Received_INR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3488,
                    "Received unexpected SAM msg from remote"
                    "in WAIT_INCOMING_ACM state ",
                    ALARM_LVL_INFO, "Received_SAM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3489,
                    "Received unexpected ANM msg from remote"
                    "in WAIT_INCOMING_ANM state",
                    ALARM_LVL_INFO, "Received_ANM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3490,
                    "Received unexpected REL msg from Application"
                    "in WAIT_INCOMING_RES state",
                    ALARM_LVL_INFO, "Received_REL",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3491,
                    "Received unexpected RES msg from Application"
                    "in WAIT_INCOMING_RES state",
                    ALARM_LVL_INFO, "Received_RES",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3492,
                    "Unexpected RLC from Application"
                    "in WAIT_INCOMING_RES state",
                    ALARM_LVL_INFO, "Received_RLC",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3493,
                    "Received unexpected ACM msg from Application"
                    " in WAIT_CONTINUITY_REPORT state ",
                    ALARM_LVL_INFO, "Received_ACM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3494,
                    "Received unexpected CPG msg from remote"
                    " in WAIT_OUTGOING_ACM state",
                    ALARM_LVL_INFO, "Received_CPG",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3495,
                    "Received unexpected CON msg from remote"
                    "in WAIT_OUTGOING_ACM state",
                    ALARM_LVL_INFO, "Received_CON",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3496,
                    "Received unexpected INR msg from Application"
                    "in WAIT_OUTGOING_ACM state",
                    ALARM_LVL_INFO, "Received_INR",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3497,
                    "Received unexpected SAM msg from Application"
                    "in WAIT_OUTGOING_ACM state",
                    ALARM_LVL_INFO, "Received_SAM",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3498,
                    "Received unexpected RES msg from remote"
                    "in WAIT_OUTGOING_ACM state",
                    ALARM_LVL_INFO, "Received_RES",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_ISUP, 3499,
                    "Timer T4 expired",
                    ALARM_LVL_MINOR, "Received_TimeoutT4_ITU93",
                    "Mutex", ITS_TRUE);


/*static ALARM_Format *CCITT_ISUP_Alarms[] = */
ALARM_Format *CCITT_ISUP_Alarms[] =
{
    &ALARM_CCITT_ISUP3401,
    &ALARM_CCITT_ISUP3402,
    &ALARM_CCITT_ISUP3403,
    &ALARM_CCITT_ISUP3404,
    &ALARM_CCITT_ISUP3405,
    &ALARM_CCITT_ISUP3406,
    &ALARM_CCITT_ISUP3407,
    &ALARM_CCITT_ISUP3408,
    &ALARM_CCITT_ISUP3409,
    &ALARM_CCITT_ISUP3410,
    &ALARM_CCITT_ISUP3411,
    &ALARM_CCITT_ISUP3412,
    &ALARM_CCITT_ISUP3413,
    &ALARM_CCITT_ISUP3414,
    &ALARM_CCITT_ISUP3415,
    &ALARM_CCITT_ISUP3416, /* not used */
    &ALARM_CCITT_ISUP3417,
    &ALARM_CCITT_ISUP3418, 
    &ALARM_CCITT_ISUP3419, /* not used */
    &ALARM_CCITT_ISUP3420,
    &ALARM_CCITT_ISUP3421, /* not being called */
    &ALARM_CCITT_ISUP3422, /* not used */
    &ALARM_CCITT_ISUP3423, /* not used */
    &ALARM_CCITT_ISUP3424, /* not used */
    &ALARM_CCITT_ISUP3425,
    &ALARM_CCITT_ISUP3426, /* not used */
    &ALARM_CCITT_ISUP3427,
    &ALARM_CCITT_ISUP3428, /* not being called */
    &ALARM_CCITT_ISUP3429, /* not used */
    &ALARM_CCITT_ISUP3430,
    &ALARM_CCITT_ISUP3431,
    &ALARM_CCITT_ISUP3432,
    &ALARM_CCITT_ISUP3433,
    &ALARM_CCITT_ISUP3434,
    &ALARM_CCITT_ISUP3435,
    &ALARM_CCITT_ISUP3436,
    &ALARM_CCITT_ISUP3437,
    &ALARM_CCITT_ISUP3438,
    &ALARM_CCITT_ISUP3439,
    &ALARM_CCITT_ISUP3440,
    &ALARM_CCITT_ISUP3441,
    &ALARM_CCITT_ISUP3442,
    &ALARM_CCITT_ISUP3443,
    &ALARM_CCITT_ISUP3444,
    &ALARM_CCITT_ISUP3445,
    &ALARM_CCITT_ISUP3446,
    &ALARM_CCITT_ISUP3447,
    &ALARM_CCITT_ISUP3448,
    &ALARM_CCITT_ISUP3449,
    &ALARM_CCITT_ISUP3450,
    &ALARM_CCITT_ISUP3451,
    &ALARM_CCITT_ISUP3452,
    &ALARM_CCITT_ISUP3453,
    &ALARM_CCITT_ISUP3454,
    &ALARM_CCITT_ISUP3455,
    &ALARM_CCITT_ISUP3456,
    &ALARM_CCITT_ISUP3457,
    &ALARM_CCITT_ISUP3458,
    &ALARM_CCITT_ISUP3459,
    &ALARM_CCITT_ISUP3460,
    &ALARM_CCITT_ISUP3461,
    &ALARM_CCITT_ISUP3462,
    &ALARM_CCITT_ISUP3463,
    &ALARM_CCITT_ISUP3464,
    &ALARM_CCITT_ISUP3465,
    &ALARM_CCITT_ISUP3466,
    &ALARM_CCITT_ISUP3467,
    &ALARM_CCITT_ISUP3468,
    &ALARM_CCITT_ISUP3469,
    &ALARM_CCITT_ISUP3470,
    &ALARM_CCITT_ISUP3471,
    &ALARM_CCITT_ISUP3472,
    &ALARM_CCITT_ISUP3473,
    &ALARM_CCITT_ISUP3474,
    &ALARM_CCITT_ISUP3475,
    &ALARM_CCITT_ISUP3476,
    &ALARM_CCITT_ISUP3477,
    &ALARM_CCITT_ISUP3478,
    &ALARM_CCITT_ISUP3479,
    &ALARM_CCITT_ISUP3480,
    &ALARM_CCITT_ISUP3481,
    &ALARM_CCITT_ISUP3482,
    &ALARM_CCITT_ISUP3483,
    &ALARM_CCITT_ISUP3484,
    &ALARM_CCITT_ISUP3485,
    &ALARM_CCITT_ISUP3486,
    &ALARM_CCITT_ISUP3487,
    &ALARM_CCITT_ISUP3488,
    &ALARM_CCITT_ISUP3489,
    &ALARM_CCITT_ISUP3490,
    &ALARM_CCITT_ISUP3491,
    &ALARM_CCITT_ISUP3492,
    &ALARM_CCITT_ISUP3493,
    &ALARM_CCITT_ISUP3494,
    &ALARM_CCITT_ISUP3495,
    &ALARM_CCITT_ISUP3496,
    &ALARM_CCITT_ISUP3497,
    &ALARM_CCITT_ISUP3498,
    &ALARM_CCITT_ISUP3499

};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a TCAP alarm.
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
ITSSS7DLLAPI void
ISUP_Alarm_CCITT(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= CCITT_ISUP_ALARM_START &&
                 which <= CCITT_ISUP_ALARM_END);

    fmt = CCITT_ISUP_Alarms[which - CCITT_ISUP_ALARM_START];

    if (fmt->severity > ISUP_AlarmLevel_CCITT)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
