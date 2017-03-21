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
 *  ID:$Id: ansi-isup_alarms.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
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
 * LOG: Revision 9.1  2005/03/23 12:54:30  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:53:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.3.6.1.12.4  2005/02/24 10:15:24  ssingh
 * LOG: bug fix for #1543/1545/1550/1575/1579. (Ramesh KV)
 * LOG:
 * LOG: Revision 7.8.2.3.6.1.12.3  2005/01/05 10:03:28  csireesh
 * LOG: Removed unwanted alarms
 * LOG:
 * LOG: Revision 7.8.2.3.6.1.12.2  2004/12/29 14:22:41  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.3.6.1.12.1  2004/12/06 14:03:04  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.8.2.3.6.1  2004/01/05 10:04:50  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.8.2.3.2.4  2003/12/11 15:10:40  ssingh
 * LOG: Bug #700, Alarm Text and Gatting changed for CQM/CQR related
 * LOG: alarms and Text changed for RangeNStatus check failed alarms.
 * LOG:
 * LOG: Revision 7.8.2.3.2.3  2003/12/11 14:00:42  ssingh
 * LOG: Bug #712 fix. Alarm(3297) text and Error text not correct as per scenario.
 * LOG:
 * LOG: Revision 7.8.2.3.2.2  2003/10/30 14:39:37  sjaddu
 * LOG: Some formats changed.
 * LOG:
 * LOG: Revision 7.8.2.3.2.1  2003/10/17 09:15:03  akumar
 * LOG: Fix for TCS req R480-17.
 * LOG:
 * LOG: Revision 7.8.2.3  2003/06/13 13:14:10  ssingh
 * LOG: New alarms added for CQM/CQR Metrix related.
 * LOG:
 * LOG: Revision 7.8.2.2  2003/05/13 05:58:55  ssingh
 * LOG: Alarms are added for CGUA/CGU,CGBA/CGB missing/abnormal cic Ack cases.
 * LOG:
 * LOG: Revision 7.8.2.1  2003/05/07 10:21:54  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.5  2003/05/06 13:51:35  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.4  2003/04/24 14:02:44  sswami
 * LOG: Bug# 317; Alarm Enhancement related changes.
 * LOG:
 * LOG: Revision 8.3  2003/04/14 06:25:21  ssingh
 * LOG: Alarms are added for CRM/CRA.
 * LOG:
 * LOG: Revision 8.2  2003/03/26 12:11:20  ssingh
 * LOG: Changed done as per ISUPPending List:
 * LOG: ansi-isup_alarms.c  : New Alarms added for HandleMTP3MgmtMsg.
 * LOG: ansi-isup_context.c : Function calls for DPC and Remote ISUP status.
 * LOG:                     : Indication sent; if msg received is on BAD Cic.
 * LOG:                     : Alarms for PAUSE/RESUME/STATUS.
 * LOG: ansi-isup_ifc.c     : Changes to incorporate CIC_INFO changes.
 * LOG: ansi-sprc.c         : CIC_INFO/CIC_MSG_INFO related changes.
 * LOG:                     : SendConfToApp removed, SendIsupIndToApp added.
 * LOG: isup_data.c         : Modified to include CIC_INFO/CIC_MSG_INFO changes.
 * LOG: its-ansi-isup.c     : CIC_INFO related changes.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:21  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.8  2003/02/04 10:01:39  aganguly
 * LOG: Added new Alarms for ISUP.Cleanup of unwanted alarms left for Release 6.4.
 * LOG:
 * LOG: Revision 7.7  2003/01/30 13:06:11  ssingh
 * LOG: Added ANSI-ISUP alarms for ISUP Initialize/Terminate/Abort.
 * LOG: Changed CIC Initialization for ANSI. Now initialized as LBLOCKED.
 * LOG:
 * LOG: Revision 7.6  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.5  2002/12/27 06:49:17  ssingh
 * LOG: Alarm ID 3062 is opened for use.
 * LOG:
 * LOG: Revision 7.4  2002/12/11 14:39:47  ssingh
 * LOG: Alarms been added/removed.
 * LOG:
 * LOG: Revision 7.3  2002/11/22 12:40:25  akumar
 * LOG: Added Alarms for CQM/CQR procedure
 * LOG:
 * LOG: Revision 7.2  2002/11/12 06:19:28  akumar
 * LOG: Added ANSI ISUP Alarms related stuff
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.2  2002/03/20 23:30:17  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.1  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 *
 ****************************************************************************/

#include <its_assertion.h>

#include "ss7_alarms.h"

ITS_UINT ISUP_AlarmLevel_ANSI = ALARM_LVL_OFF;

/* Alarms 3001-To-3004 are replaced by 3257-To-3260 */

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3001,
                    "ISUP Failed to Initialize",
                    ALARM_LVL_CRIT, "Initialize",
                    "ISUPThread", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3002,
                    "ISUP Initialized Successfully",
                    ALARM_LVL_INFO, "Initialize",
                    "ISUPThread", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3003,
                    "ISUP Terminating",
                    ALARM_LVL_INFO, "Terminate",
                    "ISUPThread", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3004,
                    "ISUP Aborting",
                    ALARM_LVL_CRIT, "ISUPThread",
                    "ISUPThread", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3005,
                    "CIC Not provisioned",
                    ALARM_LVL_INFO, "HandleMsg",
                    "Config", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3006,
                    "Message received with bad CIC",
                    ALARM_LVL_INFO, "HandleMsg",
                    "UCIC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3007,
                    "Invalid message from remote",
                    ALARM_LVL_MINOR, "HandleMsg",
                    "Event", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3008,
                    "Message format error",
                    ALARM_LVL_INFO, "HandleMsg",
                    "Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3009,
                    "Remote Congestion Level 1",
                    ALARM_LVL_MINOR, "HandleMsg",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3010,
                    "Remote Congestion Level 2",
                    ALARM_LVL_MAJOR, "HandleMsg",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3011,
                    "Remote Congestion Level 3",
                    ALARM_LVL_CRIT, "HandleMsg",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3012,
                    "Remote Congestion Ceased",
                    ALARM_LVL_INFO, "HandleMsg",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3013,
                    "Destination Unreachable",
                    ALARM_LVL_CRIT, "HandleMsg",
                    "MGMT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3014,
                    "Destination User Part Unavailable",
                    ALARM_LVL_MAJOR, "HandleMTP3MgmtMsg",
                    "MGMT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3015,
                    "Unknown MTP3 Status message",
                    ALARM_LVL_INFO, "HandleMTP3MgmtMsg",
                    "MGMT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3016,
                    "GRA received: CIC remote blocked",
                    ALARM_LVL_INFO, "BlockingCGRSToBLR",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3017,
                    "RSC received: CIC remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCRRToBLR",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3018,
                    "GRS received: CIC remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCGRRToBLR",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3019,
                    "GRA received: CIC remote Unblocked",
                    ALARM_LVL_INFO, "UnblockingCGRSToBLR",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3020,
                    "Rcvd unexpected BLA in state BLS_IDLE",
                    ALARM_LVL_MINOR, "CSC_Received_BLA",
                    "BLS_IDLE", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3021,
                    "Rcvd unexpected BLA : Wait for UBA state",
                    ALARM_LVL_INFO, "CSC_Received_BLA",
                    "BLS_WAIT_FOR_UBA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3022,
                    "Rcvd unexpected BLA from Application",
                    ALARM_LVL_INFO, "CSC_Received_BLA",
                    "BLS_IDLE", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3023,
                    "CGB from remote: RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CGB",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3024,
                    "CGBA from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CGBA",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3025,
                    "Rcvd unexpected CGBA from Application",
                    ALARM_LVL_INFO, "CSC_Received_CGBA",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3026,
                    "CGU from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CGU",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3027,
                    "CGUA from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CGUA",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3028,
                    "GRA from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CGUA",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3029,
                    "GRS from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_GRS",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3030,
                    "CQM from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CQM",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3031,
                    "CQR from remote : RangeStatus check failed",
                    ALARM_LVL_INFO, "CSC_Received_CQR",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3032,
                    "First Blocking timer T12 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT12",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3033,
                    "Second Blocking timer T13 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT13",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3034,
                    "First Unblocking timer T14 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT14",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3035,
                    "Second Unblocking timer T15 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT15",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3036,
                    "First Reset timer T16 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT16",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3037,
                    "Second Reset Timer T17 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT17",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3038,
                    "First CGBA timer T18 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT18",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3039,
                    "second CGBA timer T19 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT19",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3040,
                    "First CGUA timer T20 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT20",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3041,
                    "Second CGUA timer T21 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT21",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3042,
                    "First GRA timer T22 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT22",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3043,
                    "Second GRA timer T23 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT23",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3044,
                    "Wait continuity report timer T24 expired",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutT24",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3045,
                    "Wait continuity report timer T25 expired",
                    ALARM_LVL_INFO, "CSC_Received_TimeoutT25",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3046,
                    "Wait continuity report timer T26 expired",
                    ALARM_LVL_MINOR, "CSC_Received_TimeoutT26",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3047,
                    "COT timer T27 expired in IDLE state",
                    ALARM_LVL_MINOR, "Received_TimeoutT27",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3048,
                    "CQM timer T28 expired in IDLE state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "Circuit Query", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3049,
                    "MTP3 Pause: Destination DPC Unreachable",
                    ALARM_LVL_INFO, "HandleMTP3MgmtMsg",
                    "MGMT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3050,
                    "MTP3 Resume: Destination DPC Reachable",
                    ALARM_LVL_INFO, "HandleMTP3MgmtMsg",
                    "MGMT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3051,
                    "INF timer T33 expired in IDLE state",
                    ALARM_LVL_MINOR, "Received_TimeoutT33",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3052,
                    "MTP3 Status: Destination User Part Inaccess",
                    ALARM_LVL_MAJOR, "HandleMTP3MgmtMsg",
                    "MGMT", ITS_TRUE);

/* For future use, don't support SEG now */

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3053,
                    "Segmentation timer T36 expired in IDLE state",
                    ALARM_LVL_MINOR, "Received_TimeoutT36",
                    "SGM", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3054,
                    "Timer T37 expired",
                    ALARM_LVL_MINOR, "Received_TimeoutT37_ANSI92",
                    "CVT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3055,
                    "TACCr Timer expired",
                    ALARM_LVL_MINOR, "Received_TimeoutTACCr",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3056,
                    "CQM timer T28 expired in WAIT_IN_ANM state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "ANM", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3057,
                    "CQM timer T28 expired in WAIT_IN_RES state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "RES", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3058,
                    "CVT timer TCVT expired in IDLE state",
                    ALARM_LVL_MINOR, "Received_TimeoutTCVT",
                    "CVT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3059,
                    "Rcvd Unexpected Timeout in IDLE state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "Timeout", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3060,
                    "Rcvd UCIC for CIC or Range of CIC",
                    ALARM_LVL_MINOR, "StopWaitingCGRS",
                    "Mutex", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3061,
                    "Unexpected FOT from remote in state RCVD_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_FOT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3062,
                    "Rcvd UCIC for CIC",
                    ALARM_LVL_MINOR, "StopUCICToCRS",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3063,
                    "CQM timer T28 expired in WAIT_IN_RLC stat",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3064,
                    "Unexpected Msg from remote in state RCVD_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3065,
                   "Unexpected Msg from Application in state RCVD_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3066,
                    "Rcvd Unexpected Timeout in RCVD_IN_ANM state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "TimeOut", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3067,
                   "Unexpected FOT from Application in state SENT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_FOT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3068,
                    "Sent RSC for config period of time, No RLC rcvd",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutT17",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3069,
                    "Unexpected CPG from Application in state "
                    "WAIT_FOR_COT_REPORTS",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3070,
                    "Unexpected Msg from remote in state SENT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3071,
                   "Unexpected Msg from Application in state SENT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3072,
                    "Rcvd Unexpected Timeout in SENT_OUT_ANM state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3073,
                   "Unexpected ACM from Application in state WAIT_INCOMING_ACM",
                    ALARM_LVL_INFO, "Received_ACM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3074,
                  "Unexpected ANM from Application in state WAIT_INCOMING_ACM",
                    ALARM_LVL_INFO, "Received_ANM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3075,
                  "Unexpected CPG from Application in state WAIT_INCOMING_ACM",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3076,
                    "----",
                    ALARM_LVL_INFO, "----",
                    "CPC", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3077,
                    "Unexpected Msg from remote in state WAIT_INCOMING_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3078,
                   "Unexpected Msg from Application in state WAIT_INCOMING_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3079,
                    "Rcvd Unexpected Timeout in WAIT_IN_ACM state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3080,
                   "Unexpected ANM from Application in state WAIT_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_ANM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3081,
                    "CQM timer T28 expired in RCVD_IN_ANM state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3082,
                    "CQM timer T28 expired in SENT_OUT_ANM state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3083,
                    "CQM timer T28 expired in WAIT_IN_ACM state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3084,
                    "Unexpected FOT from remote in state WAIT_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_FOT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3085,
                    "Unexpected Msg from remote in state WAIT_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3086,
                   "Unexpected Msg from Application in state WAIT_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3087,
                    "Rcvd Unexpected Timeout in WAIT_IN_ANM state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3088,
                   "Unexpected RES from Application in state WAIT_INCOMING_RES",
                    ALARM_LVL_INFO, "Received_RES",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3089,
                   "Unexpected RLC from Application in state WAIT_INCOMING_RES",
                    ALARM_LVL_INFO, "Received_RLC",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3090,
                    "Unexpected FOT from remote in state WAIT_INCOMING_RES",
                    ALARM_LVL_INFO, "Received_FOT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3091,
                    "Unexpected Msg from remote in state WAIT_INCOMING_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3092,
                   "Unexpected Msg from Application in state WAIT_INCOMING_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3093,
                    "Rcvd Unexpected Timeout in WAIT_IN_RES state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3094,
                   "Unexpected RLC from Application in state WAIT_INCOMING_RLC",
                    ALARM_LVL_INFO, "Received_RLC",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3095,
                    "Unexpected Msg from remote in state WAIT_INCOMING_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3096,
                   "Unexpected Msg from Application in state WAIT_INCOMING_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3097,
                    "Rcvd Unexpected Timeout in WAIT_IN_RLC state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3098,
                    "Unexpected ACM from remote in state WAIT_OUTGOING_ACM",
                    ALARM_LVL_INFO, "Received_ACM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3099,
                    "Unexpected ANM from remote in state WAIT_OUTGOING_ACM",
                    ALARM_LVL_INFO, "Received_ANM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3100,
                    "Unexpected CPG from remote in state WAIT_OUTGOING_ACM",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3101,
                    "Missing Cic Ack in received CGUA from Netwrok",
                    ALARM_LVL_INFO, "CompareCGUAWithCGU",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3102,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3103,
                   "Unexpected Msg from Application in state WAIT_OUTGOING_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3104,
                    "CQM timer T28 expired in WAIT_OUT_ACM state",
                    ALARM_LVL_MINOR, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3105,
                    "Rcvd Unexpected Timeout in WAIT_IN_RLC state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3106,
                    "Unexpected ANM from remote in state WAIT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_ANM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3107,
                    "Abnormal Cic Ack in received CGUA from Network",
                    ALARM_LVL_INFO, "CompareCGUAWithCGU",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3108,
                    " Unexpected CPG from remote in state WAIT_INCOMING_COT",
                    ALARM_LVL_INFO, "Received_CPG ",
                    "CPC", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3109,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_ACM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3110,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3111,
                   "Unexpected Msg from Application in state WAIT_OUTGOING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3112,
                    "CQM timer T28 expired in WAIT_OUT_ANM state",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3113,
                    "Rcvd Unexpected Timeout in WAIT_OUT_ANM state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3114,
                   "Unexpected REL from Application in state WAIT_OUTGOING_GRA",
                    ALARM_LVL_INFO, "Received_REL",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3115,
                    "Unexpected RLC from remote in state WAIT_OUTGOING_GRA",
                    ALARM_LVL_INFO, "Received_RLC",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3116,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_GRA",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3117,
                   "Unexpected Msg from Application in state WAIT_OUTGOING_GRA",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3118,
                    "CQM timer T28 expired in WAIT_OUT_GRA state",
                    ALARM_LVL_MINOR, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3119,
                    "Rcvd Unexpected Timeout in WAIT_OUT_GRA state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3120,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_REL",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3121,
                    "Unexpected Msg from Application WAIT_OUTGOING_REL",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3122,
                    "CQM timer T28 expired in WAIT_OUT_REL state",
                    ALARM_LVL_MINOR, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3123,
                    "Rcvd Unexpected Timeout in WAIT_OUT_REL state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3124,
                    "Unexpected RES from remote in state WAIT_OUTGOING_RES",
                    ALARM_LVL_INFO, "Received_RES",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3125,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3126,
                   "Unexpected Msg from Application in state WAIT_OUTGOING_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3127,
                    "CQM timer T28 expired in WAIT_OUT_RES state",
                    ALARM_LVL_MINOR, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3128,
                    "Rcvd Unexpected Timeout in WAIT_OUT_RES state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3129,
                    "Unexpected REL from Application in state WAIT_OUTGOING_RLC",
                    ALARM_LVL_INFO, "Received_REL",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3130,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3131,
                   "Unexpected Msg from Application in state WAIT_OUTGOING_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3132,
                    "CQM timer T28 expired in WAIT_OUT_RLC state",
                    ALARM_LVL_MINOR, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3133,
                    "Rcvd Unexpected Timeout in WAIT_OUT_RLC state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3134,
                    "Unexpected REL from remote in state WAIT_OUTGOING_RSC",
                    ALARM_LVL_INFO, "Received_REL",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3135,
                    "Unexpected Msg from remote in state WAIT_OUTGOING_RSC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3136,
                   "Unexpected Msg from Application in state WAIT_OUTGOING_RSC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3137,
                    "CQM timer T28 expired in WAIT_OUT_RSC state",
                    ALARM_LVL_MINOR, "Received_TimeoutT28",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3138,
                    "Rcvd Unexpected Timeout in WAIT_OUT_RSC state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3139,
                    "Unexpected Msg from remote in state IDLE",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3140,
                    "Unexpected Msg from Application in state IDLE",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3141,
                    "Unexpected Msg from remote in state RCVD_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3142,
                   "Unexpected Msg from Application in state RCVD_INCOMING_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3143,
                    "Unexpected Msg from remote in state SENT_OUT_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3144,
                    "Unexpected Msg from Application in state SENT_OUT_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3145,
                    "Unexpected Msg from remote in state WAIT_IN_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3146,
                    "Unexpected Msg from Application in state WAIT_IN_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3147,
                    "Unexpected Msg from remote in state WAIT_IN_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3148,
                    "Unexpected Msg from Application in state WAIT_IN_ANM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3149,
                    "Unexpected Msg from remote in state WAIT_IN_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3150,
                    "Unexpected Msg from Application in state WAIT_IN_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3151,
                    "Unexpected Msg from remote in state WAIT_IN_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3152,
                    "Unexpected Msg from Application in state WAIT_IN_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3153,
                    "Unexpected Msg from remote in state WAIT_OUT_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3154,
                    "Unexpected Msg from Application in state WAIT_OUT_ACM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3155,
                    "Unexpected Msg from remote in state WAIT_COT_REPORTS",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3156,
                    "Unexpected Msg from Application in state WAIT_COT_REPORTS",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3157,
                    "Unexpected Msg from remote in state WAIT_OUT_GRA",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3158,
                    "Unexpected Msg from Application in state WAIT_OUT_GRA",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3159,
                    "Unexpected Msg from remote in state WAIT_OUT_REL",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3160,
                    "Unexpected Msg from Application in state WAIT_OUT_REL",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3161,
                    "Unexpected Msg from remote in state WAIT_OUT_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3162,
                    "Unexpected Msg from Application in state WAIT_OUT_RES",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3163,
                    "Unexpected Msg from remote in state WAIT_OUT_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3164,
                    "Unexpected Msg from Application in state WAIT_OUT_RLC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3165,
                    "Unexpected Msg from remote in state WAIT_OUT_RSC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3166,
                    "Unexpected Msg from Application in state WAIT_OUT_RSC",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3167,
                    "Local Congestion Level",
                    ALARM_LVL_MINOR, "CheckLocalCongestion",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3168,
                    "Local Congestion Level",
                    ALARM_LVL_MAJOR, "CheckLocalCongestion",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3169,
                    "Local Congestion Level Ceased",
                    ALARM_LVL_INFO, "CheckLocalCongestion",
                    "Congestion", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3170,
                    "Unexpected REL from remote in state WAIT_IN_COT",
                    ALARM_LVL_INFO, "Received_REL",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3171,
                    "COT check failed ",
                    ALARM_LVL_MAJOR, "Received_COT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3172,
                    "Rcvd Unexpected msg  from remote in state WAIT_IN_COT",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3173,
                    "Unexpected COT from Applicationn state WAIT_INCOMING_COT",
                    ALARM_LVL_INFO, "Received_COT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3174,
                    "Unexpected Msg from remote in state WAIT_INCOMING_COT",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3175,
                   "Unexpected Msg from Application in state WAIT_INCOMING_COT",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3176,
                    "Rcvd Unexpected Timeout in WAIT_INCOMING_COT state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3177,
                    "Unexpected ACM from Application in state WAIT_CONTINUITY_REPORT",
                    ALARM_LVL_INFO, "Received_ACM",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3178,
                    "Unexpected ANM from Application in state WAIT_CONTINUITY_REPORT",
                    ALARM_LVL_INFO, "Received_ANM",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3179,
                    "Unexpected COT from remote in state WAIT_CONTINUITY_REPORT",
                    ALARM_LVL_INFO, "Received_COT",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3180,
                    "Rcvd Unexpected msg  from Application in state WAIT_IN_COT",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3181,
                    "COT check failed in WAIT_INCOMING_COT state",
                    ALARM_LVL_INFO, "Received_COT",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3182,
                    "Unexpected Msg from remote in state WAIT_CONTINUITY_REPORT",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3183,
                    "Unexpected Msg from Application",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3184,
                    "Rcvd Unexpected Timeout in wait_continuity_report state",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3185,
                    "Wait_continuity_report Timer T27 expired",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutT27",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3186,
                    "Wait_continuity_report Timer T34 expired",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutT34",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3187,
                    "Wait_continuity_report TCCR expired",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutTCCRR",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3188,
                    "WAIT_CONTINUITY_REPORT Timer TCCR expired",
                    ALARM_LVL_MAJOR, "CSC_Received_TimeoutTCCR",
                    "COT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3189,
                    "Cic State Mismatch in CQR/CQM: "
                     "FarEndState : CKTS_IDLE_LBLOCKED "
                     "NearEndState: CKTS_IDLE_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateIdleActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3190,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LBLOCKED"
                    "NearEndState: CKTS_IDLE_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateIdleActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3191,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LRBLOCKED"
                    "NearEndState: CKTS_IDLE_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateIdleActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3192,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LBLOCKED "
                    "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3193,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LBLOCKED "
                    "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3194,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LBLOCKED "
                    "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3195,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LRBLOCKED "
                    "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3196,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LRBLOCKED "
                    "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3197,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LRBLOCKED "
                    "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3198,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_UNEQUIPPED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3199,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3200,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3201,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3202,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LRBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3203,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LRBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3204,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LRBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateOutbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3205,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LBLOCKED "
                    "NearEndState: CKTS_IDLE_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3206,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LBLOCKED"
                    "NearEndState: CKTS_IDLE_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3207,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LRBLOCKED "
                    "NearEndState: CKTS_IDLE_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3208,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LRBLOCKED"
                    "NearEndState: CKTS_IDLE_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3209,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LBLOCKED "
                    "NearEndState: CKTS_INBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3210,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LBLOCKED "
                    "NearEndState: CKTS_INBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3211,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LBLOCKED "
                    "NearEndState: CKTS_INBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3212,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LRBLOCKED "
                    "NearEndState: CKTS_INBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3213,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LRBLOCKED "
                    "NearEndState: CKTS_INBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3214,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LRBLOCKED "
                    "NearEndState: CKTS_INBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3215,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3216,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3217,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3218,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_LRBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3219,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_LRBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3220,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_LRBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3221,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_ACTIVE"
                    "NearEndState: CKTS_IDLE_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3222,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_ACTIVE"
                    "NearEndState: CKTS_IDLE_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3223,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_RBLOCKED "
                    "NearEndState: CKTS_IDLE_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3224,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_RBLOCKED"
                    "NearEndState: CKTS_IDLE_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3225,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_UNEQUIPPED "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3226,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_ACTIVE "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3227,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_ACTIVE "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3228,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_ACTIVE "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3229,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_RBLOCKED "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3230,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_RBLOCKED "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3231,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_RBLOCKED "
                    "NearEndState: CKTS_INBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3232,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_UNEQUIPPED "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3233,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_ACTIVE "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3234,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_ACTIVE "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3235,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_ACTIVE "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3236,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_RBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3237,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_RBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3238,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_RBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_RBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3239,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_RBLOCKED"
                    "NearEndState: CKTS_IDLE_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3240,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_ACTIVE "
                    "NearEndState: CKTS_IDLE_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3241,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_ACTIVE"
                    "NearEndState: CKTS_IDLE_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3242,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_RBLOCKED"
                    "NearEndState: CKTS_IDLE_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateIdleLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3243,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_UNEQUIPPED "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3244,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_ACTIVE "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3245,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_ACTIVE "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3246,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_ACTIVE "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3247,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_RBLOCKED "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3248,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_RBLOCKED "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3249,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_RBLOCKED "
                    "NearEndState: CKTS_INBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateInbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3250,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_UNEQUIPPED "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3251,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_ACTIVE "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3252,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_ACTIVE "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3253,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_ACTIVE "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3254,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_IDLE_RBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3255,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_INBUSY_RBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3256,
                    "Cic State Mismatch in CQR/CQM: "
                    "FarEndState : CKTS_OUTBUSY_RBLOCKED "
                    "NearEndState: CKTS_OUTBUSY_LRBLOCKED",
                    ALARM_LVL_INFO, "NearEndStateOutbusyLRBlocked",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3257,
                    "Cic State Mismatch in CQR/CQM: "
                     "FarEndState : CKTS_UNEQUIPPED "
                     "NearEndState: CKTS_IDLE_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateIdleActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3258,
                    "Cic State Mismatch in CQR/CQM: "
                     "FarEndState : CKTS_UNEQUIPPED "
                     "NearEndState: CKTS_INBUSY_ACTIVE",
                    ALARM_LVL_INFO, "NearEndStateInbusyActive",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3259,
                    "Missing Cic Ack in received CGBA from Network",
                    ALARM_LVL_INFO, "CompareCGBAWithCGB",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3260,
                    "Abnormal Cic Ack in received CGBA from Network",
                    ALARM_LVL_INFO, "CompareCGBAWithCGB",
                    "CSC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3261,
                    "Unexpected IAM from Application in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_IAM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3262,
                    "Unexpected CRA from Application in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_CRA",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3263,
                    "Unexpected COT from Network in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_COT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3264,
                    "Unexpected CPG from Application in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3265,
                    "Unexpected Msg from Network in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received__UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3266,
                    "Unexpected Msg from Application in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received__UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3267,
                    "Timer TCRM Expired in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutTCRM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3268,
                    "Timer T24 Expired in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutT24",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3269,
                    "CQM timer T28 expired in WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3270,
                    "Unexpected Timeout in state WAIT_IN_COTREPORTS_AND_CRA",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3271,
                    "Unexpected COT from Network in state WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received_COT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3272,
                    "Unexpected CPG from Application in state WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3273,
                    "Unexpected Msg from Network in state WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received__UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3274,
                    "Unexpected Msg from Application in state WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received__UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3275,
                    "Timer T24 Expired in state WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutT24",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3276,
                    "CQM timer T28 expired in WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3277,
                    "Unexpected Timeout in state WAIT_IN_COTREPORTS_HAVE_CRA",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3278,
                    "Unexpected COT from Application in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_COT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3279,
                    "Unexpected Msg from Netwrok in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_COT",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3280,
                    "Unexpected Msg from Application in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_Unexpected",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3281,
                    "Unexpected CPG from Netwrok in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3282,
                    "Timer T8 Expired in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_TimeoutT8",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3283,
                    "CQM timer T28 expired in WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3284,
                    "Timer TCRA Expired in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_TimeoutTCRA",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3285,
                    "Unexpected Timeout in state WAIT_INCOMING_COT_AND_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3286,
                    "Unexpected IAM from Application in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_IAM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3287,
                    "Unexpected CRA from Application in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_CRA",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3288,
                    "Unexpected CPG from Application in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3289,
                    "Unexpected msg from Network in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3290,
                    "Unexpected msg from Application in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3291,
                    "Timer TCRM Expired in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutTCRM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3292,
                    "CQM timer T28 expired in WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3293,
                    "Unexpected Timeout in state WAIT_INCOMING_CRA",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);
                    
ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3294,
                    "Unexpected IAM from Application in state WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_IAM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3295,
                    "Unexpected msg from Network in state WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3296,
                    "Unexpected msg from Application in state WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3297,
                    "Unexpected CPG from Network in state WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_CPG",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3298,
                    "Timer TCRA Expired in state WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_TimeoutTCRA",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3299,
                    "CQM timer T28 expired in WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3300,
                    "Unexpected Timeout in state WAIT_INCOMING_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3301,
                    "Unexpected IAM from remote in state WAIT_OUTGOING_IAM",
                    ALARM_LVL_INFO, "Received_IAM",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3302,
                    "Unexpected msg from Network in state WAIT_OUTGOING_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3303,
                    "Unexpected msg from Application in state WAIT_OUTGOING_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedMsg",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3304,
                    "CQM timer T28 expired in WAIT_OUTGOING_IAM",
                    ALARM_LVL_INFO, "Received_TimeoutT28",
                    "CPC", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_ISUP, 3305,
                    "Unexpected Timeout in state WAIT_OUTGOING_IAM",
                    ALARM_LVL_INFO, "Received_UnexpectedTimeout",
                    "CPC", ITS_TRUE);

/*static ALARM_Format *ANSI_ISUP_Alarms[] =  Kernel 2.6  */
ALARM_Format *ANSI_ISUP_Alarms[] =
{
    &ALARM_ANSI_ISUP3001, /* previously 3257 */
    &ALARM_ANSI_ISUP3002, /* previously 3258 */
    &ALARM_ANSI_ISUP3003, /* previously 3259 */
    &ALARM_ANSI_ISUP3004, /* previously 3260 */
    &ALARM_ANSI_ISUP3005,
    &ALARM_ANSI_ISUP3006,
    &ALARM_ANSI_ISUP3007,
    &ALARM_ANSI_ISUP3008,
    &ALARM_ANSI_ISUP3009,
    &ALARM_ANSI_ISUP3010,
    &ALARM_ANSI_ISUP3011,
    &ALARM_ANSI_ISUP3012,
    &ALARM_ANSI_ISUP3013,
    &ALARM_ANSI_ISUP3014,
    &ALARM_ANSI_ISUP3015,
    &ALARM_ANSI_ISUP3016,
    &ALARM_ANSI_ISUP3017,
    &ALARM_ANSI_ISUP3018,
    &ALARM_ANSI_ISUP3019,
    &ALARM_ANSI_ISUP3020,
    &ALARM_ANSI_ISUP3021,
    &ALARM_ANSI_ISUP3022,
    &ALARM_ANSI_ISUP3023,
    &ALARM_ANSI_ISUP3024,
    &ALARM_ANSI_ISUP3025,
    &ALARM_ANSI_ISUP3026,
    &ALARM_ANSI_ISUP3027,
    &ALARM_ANSI_ISUP3028,
    &ALARM_ANSI_ISUP3029,
    &ALARM_ANSI_ISUP3030,
    &ALARM_ANSI_ISUP3031,
    &ALARM_ANSI_ISUP3032,
    &ALARM_ANSI_ISUP3033,
    &ALARM_ANSI_ISUP3034,
    &ALARM_ANSI_ISUP3035,
    &ALARM_ANSI_ISUP3036,
    &ALARM_ANSI_ISUP3037,
    &ALARM_ANSI_ISUP3038,
    &ALARM_ANSI_ISUP3039,
    &ALARM_ANSI_ISUP3040,
    &ALARM_ANSI_ISUP3041,
    &ALARM_ANSI_ISUP3042,
    &ALARM_ANSI_ISUP3043,
    &ALARM_ANSI_ISUP3044, 
    &ALARM_ANSI_ISUP3045,
    &ALARM_ANSI_ISUP3046, 
    &ALARM_ANSI_ISUP3047,
    &ALARM_ANSI_ISUP3048,
    &ALARM_ANSI_ISUP3049,
    &ALARM_ANSI_ISUP3050,
    &ALARM_ANSI_ISUP3051,
    &ALARM_ANSI_ISUP3052,
    &ALARM_ANSI_ISUP3053,
    &ALARM_ANSI_ISUP3054, 
    &ALARM_ANSI_ISUP3055,
    &ALARM_ANSI_ISUP3056, 
    &ALARM_ANSI_ISUP3057, 
    &ALARM_ANSI_ISUP3058,
    &ALARM_ANSI_ISUP3059,
    &ALARM_ANSI_ISUP3060, 
    &ALARM_ANSI_ISUP3061,
    &ALARM_ANSI_ISUP3062,
    &ALARM_ANSI_ISUP3063, 
    &ALARM_ANSI_ISUP3064,
    &ALARM_ANSI_ISUP3065,
    &ALARM_ANSI_ISUP3066,
    &ALARM_ANSI_ISUP3067,
    &ALARM_ANSI_ISUP3068,
    &ALARM_ANSI_ISUP3069,
    &ALARM_ANSI_ISUP3070,
    &ALARM_ANSI_ISUP3071,
    &ALARM_ANSI_ISUP3072,
    &ALARM_ANSI_ISUP3073,
    &ALARM_ANSI_ISUP3074,
    &ALARM_ANSI_ISUP3075,
    NULL,                /* &ALARM_ANSI_ISUP3076, */
    &ALARM_ANSI_ISUP3077,
    &ALARM_ANSI_ISUP3078,
    &ALARM_ANSI_ISUP3079,
    &ALARM_ANSI_ISUP3080,
    &ALARM_ANSI_ISUP3081, 
    &ALARM_ANSI_ISUP3082,
    &ALARM_ANSI_ISUP3083, 
    &ALARM_ANSI_ISUP3084,
    &ALARM_ANSI_ISUP3085,
    &ALARM_ANSI_ISUP3086,
    &ALARM_ANSI_ISUP3087,
    &ALARM_ANSI_ISUP3088,
    &ALARM_ANSI_ISUP3089,
    &ALARM_ANSI_ISUP3090,
    &ALARM_ANSI_ISUP3091,
    &ALARM_ANSI_ISUP3092,
    &ALARM_ANSI_ISUP3093,
    &ALARM_ANSI_ISUP3094,
    &ALARM_ANSI_ISUP3095,
    &ALARM_ANSI_ISUP3096,
    &ALARM_ANSI_ISUP3097,
    &ALARM_ANSI_ISUP3098,
    &ALARM_ANSI_ISUP3099,
    &ALARM_ANSI_ISUP3100,
    &ALARM_ANSI_ISUP3101,
    &ALARM_ANSI_ISUP3102,
    &ALARM_ANSI_ISUP3103,
    &ALARM_ANSI_ISUP3104,
    &ALARM_ANSI_ISUP3105,
    &ALARM_ANSI_ISUP3106,
    &ALARM_ANSI_ISUP3107,
    &ALARM_ANSI_ISUP3108,
    &ALARM_ANSI_ISUP3109, 
    &ALARM_ANSI_ISUP3110,
    &ALARM_ANSI_ISUP3111,
    &ALARM_ANSI_ISUP3112,
    &ALARM_ANSI_ISUP3113,
    &ALARM_ANSI_ISUP3114,
    &ALARM_ANSI_ISUP3115,
    &ALARM_ANSI_ISUP3116,
    &ALARM_ANSI_ISUP3117,
    &ALARM_ANSI_ISUP3118,
    &ALARM_ANSI_ISUP3119,
    &ALARM_ANSI_ISUP3120,
    &ALARM_ANSI_ISUP3121,
    &ALARM_ANSI_ISUP3122,
    &ALARM_ANSI_ISUP3123,
    &ALARM_ANSI_ISUP3124,
    &ALARM_ANSI_ISUP3125,
    &ALARM_ANSI_ISUP3126,
    &ALARM_ANSI_ISUP3127,
    &ALARM_ANSI_ISUP3128,
    &ALARM_ANSI_ISUP3129,
    &ALARM_ANSI_ISUP3130,
    &ALARM_ANSI_ISUP3131,
    &ALARM_ANSI_ISUP3132,
    &ALARM_ANSI_ISUP3133,
    &ALARM_ANSI_ISUP3134,
    &ALARM_ANSI_ISUP3135,
    &ALARM_ANSI_ISUP3136,
    &ALARM_ANSI_ISUP3137,
    &ALARM_ANSI_ISUP3138,
    &ALARM_ANSI_ISUP3139,
    &ALARM_ANSI_ISUP3140,
    &ALARM_ANSI_ISUP3141,
    &ALARM_ANSI_ISUP3142,
    &ALARM_ANSI_ISUP3143,
    &ALARM_ANSI_ISUP3144,
    &ALARM_ANSI_ISUP3145,
    &ALARM_ANSI_ISUP3146,
    &ALARM_ANSI_ISUP3147,
    &ALARM_ANSI_ISUP3148,
    &ALARM_ANSI_ISUP3149,
    &ALARM_ANSI_ISUP3150,
    &ALARM_ANSI_ISUP3151,
    &ALARM_ANSI_ISUP3152,
    &ALARM_ANSI_ISUP3153,
    &ALARM_ANSI_ISUP3154,
    &ALARM_ANSI_ISUP3155,
    &ALARM_ANSI_ISUP3156,
    &ALARM_ANSI_ISUP3157,
    &ALARM_ANSI_ISUP3158,
    &ALARM_ANSI_ISUP3159,
    &ALARM_ANSI_ISUP3160,
    &ALARM_ANSI_ISUP3161,
    &ALARM_ANSI_ISUP3162,
    &ALARM_ANSI_ISUP3163,
    &ALARM_ANSI_ISUP3164,
    &ALARM_ANSI_ISUP3165,
    &ALARM_ANSI_ISUP3166,
    &ALARM_ANSI_ISUP3167,
    &ALARM_ANSI_ISUP3168,
    &ALARM_ANSI_ISUP3169,
    &ALARM_ANSI_ISUP3170,
    &ALARM_ANSI_ISUP3171,
    &ALARM_ANSI_ISUP3172, 
    &ALARM_ANSI_ISUP3173,
    &ALARM_ANSI_ISUP3174,
    &ALARM_ANSI_ISUP3175,
    &ALARM_ANSI_ISUP3176,
    &ALARM_ANSI_ISUP3177,
    &ALARM_ANSI_ISUP3178,
    &ALARM_ANSI_ISUP3179,
    &ALARM_ANSI_ISUP3180, 
    &ALARM_ANSI_ISUP3181, 
    &ALARM_ANSI_ISUP3182,
    &ALARM_ANSI_ISUP3183,
    &ALARM_ANSI_ISUP3184,
    &ALARM_ANSI_ISUP3185,
    &ALARM_ANSI_ISUP3186,
    &ALARM_ANSI_ISUP3187,
    &ALARM_ANSI_ISUP3188,
    &ALARM_ANSI_ISUP3189,
    &ALARM_ANSI_ISUP3190,
    &ALARM_ANSI_ISUP3191,
    &ALARM_ANSI_ISUP3192,
    &ALARM_ANSI_ISUP3193,
    &ALARM_ANSI_ISUP3194,
    &ALARM_ANSI_ISUP3195,
    &ALARM_ANSI_ISUP3196,
    &ALARM_ANSI_ISUP3197,
    &ALARM_ANSI_ISUP3198,
    &ALARM_ANSI_ISUP3199,
    &ALARM_ANSI_ISUP3200,
    &ALARM_ANSI_ISUP3201,
    &ALARM_ANSI_ISUP3202,
    &ALARM_ANSI_ISUP3203,
    &ALARM_ANSI_ISUP3204,
    &ALARM_ANSI_ISUP3205,
    &ALARM_ANSI_ISUP3206,
    &ALARM_ANSI_ISUP3207,
    &ALARM_ANSI_ISUP3208,
    &ALARM_ANSI_ISUP3209,
    &ALARM_ANSI_ISUP3210,
    &ALARM_ANSI_ISUP3211,
    &ALARM_ANSI_ISUP3212,
    &ALARM_ANSI_ISUP3213,
    &ALARM_ANSI_ISUP3214,
    &ALARM_ANSI_ISUP3215,
    &ALARM_ANSI_ISUP3216,
    &ALARM_ANSI_ISUP3217,
    &ALARM_ANSI_ISUP3218,
    &ALARM_ANSI_ISUP3219,
    &ALARM_ANSI_ISUP3220,
    &ALARM_ANSI_ISUP3221,
    &ALARM_ANSI_ISUP3222,
    &ALARM_ANSI_ISUP3223,
    &ALARM_ANSI_ISUP3224,
    &ALARM_ANSI_ISUP3225,
    &ALARM_ANSI_ISUP3226,
    &ALARM_ANSI_ISUP3227,
    &ALARM_ANSI_ISUP3228,
    &ALARM_ANSI_ISUP3229,
    &ALARM_ANSI_ISUP3230,
    &ALARM_ANSI_ISUP3231,
    &ALARM_ANSI_ISUP3232,
    &ALARM_ANSI_ISUP3233,
    &ALARM_ANSI_ISUP3234,
    &ALARM_ANSI_ISUP3235,
    &ALARM_ANSI_ISUP3236,
    &ALARM_ANSI_ISUP3237,
    &ALARM_ANSI_ISUP3238,
    &ALARM_ANSI_ISUP3239,
    &ALARM_ANSI_ISUP3240,
    &ALARM_ANSI_ISUP3241,
    &ALARM_ANSI_ISUP3242,
    &ALARM_ANSI_ISUP3243,
    &ALARM_ANSI_ISUP3244,
    &ALARM_ANSI_ISUP3245,
    &ALARM_ANSI_ISUP3246,
    &ALARM_ANSI_ISUP3247,
    &ALARM_ANSI_ISUP3248,
    &ALARM_ANSI_ISUP3249,
    &ALARM_ANSI_ISUP3250,
    &ALARM_ANSI_ISUP3251,
    &ALARM_ANSI_ISUP3252,
    &ALARM_ANSI_ISUP3253,
    &ALARM_ANSI_ISUP3254,
    &ALARM_ANSI_ISUP3255,
    &ALARM_ANSI_ISUP3256,
    &ALARM_ANSI_ISUP3257,
    &ALARM_ANSI_ISUP3258,
    &ALARM_ANSI_ISUP3259,
    &ALARM_ANSI_ISUP3260,
    &ALARM_ANSI_ISUP3261,
    &ALARM_ANSI_ISUP3262,
    &ALARM_ANSI_ISUP3263,
    &ALARM_ANSI_ISUP3264,
    &ALARM_ANSI_ISUP3265,
    &ALARM_ANSI_ISUP3266,
    &ALARM_ANSI_ISUP3267,
    &ALARM_ANSI_ISUP3268,
    &ALARM_ANSI_ISUP3269,
    &ALARM_ANSI_ISUP3270,
    &ALARM_ANSI_ISUP3271,
    &ALARM_ANSI_ISUP3272,
    &ALARM_ANSI_ISUP3273,
    &ALARM_ANSI_ISUP3274,
    &ALARM_ANSI_ISUP3275,
    &ALARM_ANSI_ISUP3276,
    &ALARM_ANSI_ISUP3277,
    &ALARM_ANSI_ISUP3278,
    &ALARM_ANSI_ISUP3279,
    &ALARM_ANSI_ISUP3280,
    &ALARM_ANSI_ISUP3281,
    &ALARM_ANSI_ISUP3282,
    &ALARM_ANSI_ISUP3283,
    &ALARM_ANSI_ISUP3284,
    &ALARM_ANSI_ISUP3285,
    &ALARM_ANSI_ISUP3286,
    &ALARM_ANSI_ISUP3287,
    &ALARM_ANSI_ISUP3288,
    &ALARM_ANSI_ISUP3289,
    &ALARM_ANSI_ISUP3290,
    &ALARM_ANSI_ISUP3291,
    &ALARM_ANSI_ISUP3292,
    &ALARM_ANSI_ISUP3293,
    &ALARM_ANSI_ISUP3294,
    &ALARM_ANSI_ISUP3295,
    &ALARM_ANSI_ISUP3296,
    &ALARM_ANSI_ISUP3297,
    &ALARM_ANSI_ISUP3298,
    &ALARM_ANSI_ISUP3299,
    &ALARM_ANSI_ISUP3300,
    &ALARM_ANSI_ISUP3301,
    &ALARM_ANSI_ISUP3302,
    &ALARM_ANSI_ISUP3303,
    &ALARM_ANSI_ISUP3304,
    &ALARM_ANSI_ISUP3305
}; 

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a ISUP alarm.
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
ISUP_Alarm_ANSI(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= ANSI_ISUP_ALARM_START &&
                 which <= ANSI_ISUP_ALARM_END);

    fmt = ANSI_ISUP_Alarms[which - ANSI_ISUP_ALARM_START];

    if (fmt->severity > ISUP_AlarmLevel_ANSI)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
