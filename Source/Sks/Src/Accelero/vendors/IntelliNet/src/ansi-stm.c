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
 *  ID: $Id: ansi-stm.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
 * 
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/16 21:04:55  randresol
 * LOG: Fix problem 1733: UNINHIBIT not happening after LPO LPR set
 * LOG:
 * LOG: Revision 9.3  2005/05/09 09:44:20  kshah
 * LOG: Modifications for LPR fixes for bug #1733
 * LOG:
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/16 21:04:55  randresol
 * LOG: Fix problem 1733: UNINHIBIT not happening after LPO LPR set
 * LOG:
 * LOG: Revision 9.3  2005/04/07 09:44:20  snagesh
 * LOG: Modifications for LPO Feature and fixes for bug #972, bug #860
 * LOG:
 * LOG: Revision 9.2  2005/04/05 11:27:21  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.12  2005/03/21 13:53:37  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.8.2.4.8.5  2005/02/08 08:53:17  snagesh
 * LOG: OAM bug fixes for bugs 1528,1529-Link Inhibit and Link Uninhibit pegs
 * LOG:
 * LOG: Revision 7.8.2.8.2.4.8.4  2005/01/25 11:34:26  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.8.2.8.2.4.8.3  2005/01/05 14:29:07  sbabu
 * LOG: Alarm 2523 Changes to 2123
 * LOG:
 * LOG: Revision 7.8.2.8.2.4.8.2  2005/01/05 12:55:50  sbabu
 * LOG: Removed unwanted alarms
 * LOG:
 * LOG: Revision 7.8.2.8.2.4.8.1  2004/12/31 06:57:51  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.8.2.4  2004/09/07 05:21:37  sswami
 * LOG: Fix given for text changes for alert Id 2128
 * LOG:
 * LOG: Revision 7.8.2.8.2.3  2004/09/03 09:43:59  sswami
 * LOG: Fix for Generating Alarm Ids 2001,2002 & text changes.
 * LOG:
 * LOG: Revision 7.8.2.8.2.2  2004/08/11 09:59:33  kannanp
 * LOG: Changes for MTP3 pegs .
 * LOG:
 * LOG: Revision 7.8.2.8.2.1  2004/08/10 12:14:45  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.8.2.8  2003/12/12 11:55:06  kannanp
 * LOG: Fix bug 592 Peg Counts MSG_STATUS,CONGESTION not incrementing.
 * LOG:
 * LOG: Revision 7.8.2.7  2003/12/08 10:57:48  kannanp
 * LOG: Fix bug 582 Inhibition not working when done on both sides.
 * LOG:
 * LOG: Revision 7.8.2.6  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.8.2.5  2003/09/18 05:11:24  ttipatre
 * LOG: Fix Core for incoming TRW message.
 * LOG:
 * LOG: Revision 7.8.2.4  2003/04/28 12:04:25  ttipatre
 * LOG: Add one more check to fix core problem for adding dummy linkSet and route.
 * LOG:
 * LOG: Revision 7.8.2.3  2003/04/22 09:38:15  ttipatre
 * LOG: Fix core problem after adding dummy linkSet and route.
 * LOG:
 * LOG: Revision 7.8.2.2  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.8.2.1  2003/02/14 07:29:21  randresol
 * LOG: Enhancement for Pegs and Alarms
 * LOG:
 * LOG: Revision 7.8  2003/02/13 10:33:46  ttipatre
 * LOG: Pegs are Modified.
 * LOG:
 * LOG: Revision 7.7  2002/12/24 19:59:03  randresol
 * LOG: Fix message lost problem during change over
 * LOG:
 * LOG: Revision 7.6  2002/12/24 07:43:36  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.5  2002/11/28 04:53:09  ttipatre
 * LOG: Fix the core problem for incoming TFA.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 11:52:13  ttipatre
 * LOG: fix the problem reported for not sending second CBD.
 * LOG:
 * LOG: Revision 7.3  2002/11/20 05:13:44  ttipatre
 * LOG: Alarms and Pegs code submission.
 * LOG:
 * LOG: Revision 7.2  2002/11/09 22:16:25  randresol
 * LOG: Fix various bugs
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.13  2002/08/22 01:14:09  randresol
 * LOG: fix pointer problem seen in 64bit mode. replace
 * LOG: rinfo = *(ROUTE_InfoPtr *)(tmp->data); by the safer
 * LOG: memcpy(&rinfo, tmp->data, sizeof(rinfo));
 * LOG:
 * LOG: Revision 6.12  2002/08/17 00:28:53  randresol
 * LOG: Fix Routing Label for MTP3 indications
 * LOG:
 * LOG: Revision 6.11  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.10  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.9  2002/05/17 19:50:33  randresol
 * LOG: Fix MTP3_STATUS to show USER_PART_INACCESSIBLE
 * LOG:
 * LOG: Revision 6.8  2002/05/15 15:06:47  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.7  2002/05/06 20:11:17  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.6  2002/04/29 21:23:21  randresol
 * LOG: Add InterNode processing and shared booleans
 * LOG:
 * LOG: Revision 6.5  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/03/27 18:38:34  randresol
 * LOG: Remove Visual C++ warnings
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:28:23  randresol
 * LOG: crBuf, cocbBuf, rtrvBuf and route list are now in DSM
 * LOG:
 * LOG: Revision 6.2  2002/03/11 20:59:46  mmiers
 * LOG: It builds.  Now for the hard part.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.141  2002/02/19 21:51:53  mmiers
 * LOG: bounds checking.
 * LOG:
 * LOG: Revision 5.140  2002/02/19 19:29:20  mmiers
 * LOG: Fix bug spotted by Ricardo
 * LOG:
 * LOG: Revision 5.139  2002/02/12 23:29:03  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 5.138  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.137  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.136  2002/02/01 20:25:56  mmiers
 * LOG: Fix subsystem call
 * LOG:
 * LOG: Revision 5.135  2002/01/29 19:58:01  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.134  2002/01/29 19:56:26  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.133  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 5.132  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.131  2001/12/06 23:40:31  mmiers
 * LOG: Todays debugging.
 * LOG:
 * LOG: Revision 5.130  2001/12/06 22:39:04  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.129  2001/12/05 23:41:58  mmiers
 * LOG: Continuing with STP testing.
 * LOG:
 * LOG: Revision 5.128  2001/12/04 23:59:50  mmiers
 * LOG: Route testing.
 * LOG:
 * LOG: Revision 5.127  2001/12/04 00:15:55  mmiers
 * LOG: STP testing.
 * LOG:
 * LOG: Revision 5.126  2001/11/30 23:43:14  mmiers
 * LOG: Start testing config-d (route management).
 * LOG:
 * LOG: Revision 5.125  2001/11/29 23:43:24  mmiers
 * LOG: All config A tests passed (by kicking the INET).
 * LOG:
 * LOG: Revision 5.124  2001/11/22 00:05:27  mmiers
 * LOG: Todays fixes.
 * LOG:
 * LOG: Revision 5.123  2001/11/21 21:51:54  hdivoux
 * LOG: Change for iterate hashtable function name.
 * LOG:
 * LOG: Revision 5.122  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 5.121  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.120  2001/11/16 02:26:37  mmiers
 * LOG: Compile error that's accepted on NT.
 * LOG:
 * LOG: Revision 5.119  2001/11/15 23:52:27  mmiers
 * LOG: Today's testing.
 * LOG:
 * LOG: Revision 5.118  2001/11/14 23:17:13  mmiers
 * LOG: Many changes from conformance testing.
 * LOG:
 * LOG: Revision 5.117  2001/11/12 23:29:14  mmiers
 * LOG: Fixme removal
 * LOG:
 * LOG: Revision 5.116  2001/11/09 00:17:39  mmiers
 * LOG: Needed destination
 * LOG:
 * LOG: Revision 5.115  2001/11/07 23:41:50  mmiers
 * LOG: More STP functionality debugging
 * LOG:
 * LOG: Revision 5.114  2001/11/07 22:42:26  vnitin
 * LOG: Fixed Inhibit unhibit path
 * LOG:
 * LOG: Revision 5.113  2001/11/07 18:05:52  mmiers
 * LOG: Fixes for changeback.  Finally working.
 * LOG:
 * LOG: Revision 5.112  2001/11/07 01:14:40  mmiers
 * LOG: Fix CBD logic.
 * LOG:
 * LOG: Revision 5.111  2001/11/06 23:53:53  mmiers
 * LOG: Typos in CBD
 * LOG:
 * LOG: Revision 5.110  2001/11/06 22:17:37  mmiers
 * LOG: Alternate route data changed assert.
 * LOG:
 * LOG: Revision 5.109  2001/11/06 21:55:32  mmiers
 * LOG: More changes for CB.
 * LOG:
 * LOG: Revision 5.108  2001/11/05 22:53:13  mmiers
 * LOG: Move traffic from changing link to new link
 * LOG:
 * LOG: Revision 5.107  2001/11/02 23:03:31  mmiers
 * LOG: Convert to new event queuing.
 * LOG:
 * LOG: Revision 5.106  2001/11/01 20:22:06  vnitin
 * LOG: isUp and TCOC fixes
 * LOG:
 * LOG: Revision 5.105  2001/11/01 01:41:04  mmiers
 * LOG: Debugging changeback
 * LOG:
 * LOG: Revision 5.104  2001/10/31 02:03:59  mmiers
 * LOG: Add retrieved transmission
 * LOG:
 * LOG: Revision 5.103  2001/10/30 23:54:43  mmiers
 * LOG: Rajesh's fix done slightly differently.
 * LOG:
 * LOG: Revision 5.102  2001/10/30 19:27:11  rsonak
 * LOG: Check for different linksets when you compare the priorities in routingChanged
 * LOG:
 * LOG: Revision 5.101  2001/10/30 00:16:10  mmiers
 * LOG: Today's debugging session.  Looks close.
 * LOG:
 * LOG: Revision 5.100  2001/10/29 16:05:08  vnitin
 * LOG: Some Changeover fixes in TLAC TSRC and TCOC
 * LOG:
 * LOG: Revision 5.98  2001/10/26 17:40:12  mmiers
 * LOG: Bug fixes for pulling the plug.
 * LOG:
 * LOG: Revision 5.97  2001/10/26 16:52:40  rsonak
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 5.94  2001/10/25 21:44:22  mmiers
 * LOG: Fix routingchanged and findalternateroute functions
 * LOG:
 * LOG: Revision 5.93  2001/10/25 20:24:40  mmiers
 * LOG: Extra comments removed.
 * LOG:
 * LOG: Revision 5.92  2001/10/25 19:52:48  mmiers
 * LOG: Add buffering into STM
 * LOG:
 * LOG: Revision 5.91  2001/10/25 16:51:32  mmiers
 * LOG: SLT timer context bug.  T28 timer context bug.  Fix bugs in
 * LOG: SMH I added yesterday.
 * LOG:
 * LOG: Revision 5.90  2001/10/24 23:01:41  vnitin
 * LOG: Modified ChangeoverRequired
 * LOG:
 * LOG: Revision 5.89  2001/10/24 22:41:18  rsonak
 * LOG: Inhibit bugs
 * LOG:
 * LOG: Revision 5.88  2001/10/23 22:56:13  rsonak
 * LOG: Inhibit from MGMT doesnt need mtp3 label
 * LOG:
 * LOG: Revision 5.87  2001/10/22 20:56:53  rsonak
 * LOG: Mark COP and CBP before the triggers are sent to TCOC and TCBC respectively
 * LOG:
 * LOG: Revision 5.86  2001/10/22 19:35:50  mmiers
 * LOG: Missing checks Rajesh found
 * LOG:
 * LOG: Revision 5.85  2001/10/22 17:16:00  rsonak
 * LOG: Fixed some TLAC state-management bugs
 * LOG:
 * LOG: Revision 5.84  2001/10/19 22:39:12  rsonak
 * LOG: Dont send ALTER_ROUTING_DATA to new Link. Send to the original one.
 * LOG: Link restoration also working with this fix
 * LOG:
 * LOG: Revision 5.83  2001/10/19 21:28:13  rsonak
 * LOG: In TSRC, do we need bogus routing label wjen CO not reqd is received. Do nothing.
 * LOG: Otherwise crashes.
 * LOG:
 * LOG: Revision 5.82  2001/10/19 20:44:18  rsonak
 * LOG: Fixed bugs in FindAlternateRoute
 * LOG:
 * LOG: Revision 5.81  2001/10/17 22:03:12  mmiers
 * LOG: More debugging
 * LOG:
 * LOG: Revision 5.80  2001/10/16 20:38:55  mmiers
 * LOG: Get multiple links working.
 * LOG:
 * LOG: Revision 5.79  2001/10/15 21:53:51  mmiers
 * LOG: All SNMM messages go at highest priority except for
 * LOG: congestion test.
 * LOG: Use MTP2_SendData to send messages.
 * LOG: Various debugging to get MTP3 up and running.
 * LOG:
 * LOG: Revision 5.78  2001/10/12 23:14:52  mmiers
 * LOG: Fun with NMS.  The MTP2 API now works.
 * LOG:
 * LOG: Revision 5.77  2001/10/12 22:41:11  vnitin
 * LOG: Update state change in TCOC
 * LOG:
 * LOG: Revision 5.76  2001/10/09 23:24:42  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 5.75  2001/10/06 23:54:18  mmiers
 * LOG: Missed a few things yesterday.  Fix makefile as well.
 * LOG:
 * LOG: Revision 5.74  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.73  2001/10/04 21:44:31  mmiers
 * LOG: Core dump avoidance.  Requires more thought (procedure terminated).
 * LOG:
 * LOG: Revision 5.72  2001/10/04 21:31:33  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 5.71  2001/10/03 22:16:39  mmiers
 * LOG: Debugging additions.
 * LOG:
 * LOG: Revision 5.70  2001/10/03 19:42:46  mmiers
 * LOG: Timer cleanup.
 * LOG:
 * LOG: Revision 5.69  2001/10/03 18:54:27  mmiers
 * LOG: More testing.
 * LOG:
 * LOG: Revision 5.68  2001/10/02 22:57:20  mmiers
 * LOG: Today's bug fixes for STM.
 * LOG:
 * LOG: Revision 5.67  2001/10/02 21:06:44  mmiers
 * LOG: Status correction
 * LOG:
 * LOG: Revision 5.66  2001/10/01 22:28:48  mmiers
 * LOG: Comments.
 * LOG:
 * LOG: Revision 5.65  2001/10/01 20:12:42  mmiers
 * LOG: struct rename
 * LOG:
 * LOG: Revision 5.64  2001/10/01 19:28:12  rsonak
 * LOG: Solidify getting correct linkSet/linkCode
 * LOG:
 * LOG: Revision 5.63  2001/10/01 19:12:59  mmiers
 * LOG: arg convention.
 * LOG:
 * LOG: Revision 5.62  2001/09/28 22:15:21  vnitin
 * LOG: Fixed getting correct Linkset and Linkcode from TCOC SNMM
 * LOG:
 * LOG: Revision 5.61  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.60  2001/09/28 19:06:03  rsonak
 * LOG: Extract appropriate linkset for incoming SNMM messages for TCBC
 * LOG:
 * LOG: Revision 5.59  2001/09/27 22:13:52  rsonak
 * LOG: Extract appropriate linkset for incoming SNMM messages for TLAC
 * LOG:
 * LOG: Revision 5.58  2001/09/26 21:28:44  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.57  2001/09/24 22:50:23  mmiers
 * LOG: Remove bogus SSN from MTP3 P/R/S messages.  This adds fixmes to
 * LOG: SCMG.
 * LOG:
 * LOG: Revision 5.56  2001/09/21 00:31:20  mmiers
 * LOG: Fix errors (bandaid).
 * LOG:
 * LOG: Revision 5.55  2001/09/20 22:52:37  mmiers
 * LOG: From todays discussion.  Doesn't compile.
 * LOG:
 * LOG: Revision 5.54  2001/09/19 23:37:40  mmiers
 * LOG: Update
 * LOG:
 * LOG: Revision 5.53  2001/09/18 22:52:28  mmiers
 * LOG: Extra flags.
 * LOG:
 * LOG: Revision 5.52  2001/09/18 21:47:25  mmiers
 * LOG: Getting states right.
 * LOG:
 * LOG: Revision 5.51  2001/09/17 23:49:02  mmiers
 * LOG: Syntax build.
 * LOG:
 * LOG: Revision 5.50  2001/09/17 23:43:37  mmiers
 * LOG: Walkthroughs.
 * LOG:
 * LOG: Revision 5.49  2001/09/17 19:09:41  vnitin
 * LOG: implemented functions used by TCOC
 * LOG:
 * LOG: Revision 5.48  2001/09/17 14:56:28  vnitin
 * LOG: Identified fixme in TCOC
 * LOG:
 * LOG: Revision 5.47  2001/09/14 22:52:17  rsonak
 * LOG: Unnecessary fixme's removed
 * LOG:
 * LOG: Revision 5.46  2001/09/14 22:05:45  mmiers
 * LOG: Work on SLT, TSRC
 * LOG:
 * LOG: Revision 5.45  2001/09/14 19:23:19  rsonak
 * LOG: Fixed SNMM messages for TLAC/TCBC, Added CB Code allocation for TCBC
 * LOG:
 * LOG: Revision 5.44  2001/09/14 19:20:43  vnitin
 * LOG: TCOC Update
 * LOG:
 * LOG: Revision 5.43  2001/09/14 17:30:59  mmiers
 * LOG: TSRC update.
 * LOG:
 * LOG: Revision 5.42  2001/09/13 22:36:47  mmiers
 * LOG: More TSRC.
 * LOG:
 * LOG: Revision 5.41  2001/09/13 21:40:54  vnitin
 * LOG: Updating TCOC
 * LOG:
 * LOG: Revision 5.40  2001/09/13 21:29:20  mmiers
 * LOG: SRM almost done (RSRT).  Start filling TSRC
 * LOG:
 * LOG: Revision 5.39  2001/09/13 19:48:06  mmiers
 * LOG: TRCC, TFRC, and TCRC.
 * LOG:
 * LOG: Revision 5.38  2001/09/13 16:41:33  rsonak
 * LOG: LPO not needed
 * LOG:
 * LOG: Revision 5.37  2001/09/13 15:56:02  mmiers
 * LOG: Accessibility exceptions
 * LOG:
 * LOG: Revision 5.36  2001/09/13 15:50:30  mmiers
 * LOG: Arg format.
 * LOG:
 * LOG: Revision 5.35  2001/09/13 14:59:05  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 5.34  2001/09/13 14:58:19  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 5.33  2001/09/13 14:22:44  mmiers
 * LOG: Add T6.
 * LOG:
 * LOG: Revision 5.32  2001/09/12 22:53:59  mmiers
 * LOG: TPRC
 * LOG:
 * LOG: Revision 5.31  2001/09/12 22:02:45  rsonak
 * LOG: Solidify TLAC
 * LOG:
 * LOG: Revision 5.30  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.29  2001/09/11 20:14:15  mmiers
 * LOG: SRM is as done as far as I can get it.
 * LOG:
 * LOG: Revision 5.28  2001/09/06 20:06:05  mmiers
 * LOG: Cleanup.
 * LOG:
 * LOG: Revision 5.27  2001/09/06 15:33:32  mmiers
 * LOG: Cleanup.  Add reserved NI use to TCAP.
 * LOG:
 * LOG: Revision 5.26  2001/09/06 00:39:57  mmiers
 * LOG: Work in the MTP2 codec.
 * LOG:
 * LOG: Revision 5.25  2001/09/04 23:03:40  mmiers
 * LOG: MTP3 work.
 * LOG:
 * LOG: Revision 5.24  2001/08/31 23:46:19  mmiers
 * LOG: More work
 * LOG:
 * LOG: Revision 5.23  2001/08/31 19:29:04  mmiers
 * LOG: Remove explicit locks.  Need to add this to the main.
 * LOG:
 * LOG: Revision 5.22  2001/08/31 14:22:10  mmiers
 * LOG: Brainstorming fixes.
 * LOG:
 * LOG: Revision 5.21  2001/08/30 20:12:09  vnitin
 * LOG: Merge results.
 * LOG:
 * LOG: Revision 5.20  2001/08/30 16:23:18  rsonak
 * LOG: Change adminState to isAllowed.
 * LOG:
 * LOG: Revision 5.19  2001/08/29 16:42:34  rsonak
 * LOG: Filled up TLAC (almost). Moving to fill up TSRC.
 * LOG:
 * LOG: Revision 5.18  2001/08/28 21:04:45  mmiers
 * LOG: Merge.
 * LOG:
 * LOG: Revision 5.17  2001/08/28 19:40:24  rsonak
 * LOG: TLAC is in.
 * LOG:
 * LOG: Revision 5.16  2001/08/28 16:53:30  rsonak
 * LOG: TLAC Sheet 8 done. Should finish TLAC today/tomorrow (if I dont get pulled into
 * LOG: other things)
 * LOG:
 * LOG: Revision 5.15  2001/08/28 16:00:48  rsonak
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 5.14  2001/08/27 22:57:05  mmiers
 * LOG: Updates from ANSI-96 SDL.
 * LOG:
 * LOG: Revision 5.13  2001/08/27 19:34:55  mmiers
 * LOG: Revert to old args.
 * LOG:
 * LOG: Revision 5.12  2001/08/24 22:19:19  vnitin
 * LOG: Updating TCOC
 * LOG:
 * LOG: Revision 5.11  2001/08/24 21:29:01  mmiers
 * LOG: Merge.
 * LOG:
 * LOG: Revision 5.10  2001/08/24 15:57:18  rsonak
 * LOG: C comments only
 * LOG:
 * LOG: Revision 5.9  2001/08/23 23:03:37  rsonak
 * LOG: TLAC sheet 6
 * LOG:
 * LOG: Revision 5.8  2001/08/23 22:56:15  mmiers
 * LOG: Fix the code to not break with the modified routing API.  The
 * LOG: calls in MTP3 need to be modified to include a link set where
 * LOG: appropriate.
 * LOG:
 * LOG: Revision 5.7  2001/08/23 21:03:38  mmiers
 * LOG: Today's installment.
 * LOG:
 * LOG: Revision 5.6  2001/08/23 19:51:58  rsonak
 * LOG: Completed sheet 4
 * LOG:
 * LOG: Revision 5.5  2001/08/22 22:38:29  mmiers
 * LOG: More work.
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
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.9  2001/08/09 22:25:56  mmiers
 * LOG: TSRC is in.  TLAC is left.
 * LOG:
 * LOG: Revision 4.8  2001/08/09 01:08:04  mmiers
 * LOG: Fill in the rest of STM.  Only TLAC and TSRC left.
 * LOG:
 * LOG: Revision 4.7  2001/08/08 22:35:09  mmiers
 * LOG: Update with STM implementation.
 * LOG:
 * LOG: Revision 4.6  2001/08/08 00:58:32  mmiers
 * LOG: Add comments from initial review.  Guys, *please* pay attention.
 * LOG: Ask Hubert about DSC if you think I'm being over-picky.  Feel
 * LOG: free to delete from the ChangeLog if this message bothers you.
 * LOG:
 * LOG: Revision 4.5  2001/08/08 00:44:26  mmiers
 * LOG: Cross platform build.
 * LOG:
 * LOG: Revision 4.4  2001/08/06 23:06:04  rsonak
 * LOG: Code reorg till sheet 3
 * LOG:
 * LOG: Revision 4.3  2001/08/06 21:28:47  rsonak
 * LOG: Code reorg
 * LOG:
 * LOG: Revision 4.2  2001/07/27 22:29:40  rsonak
 * LOG: Some logical problems due to the intermediate states.
 * LOG:
 * LOG: Revision 4.1  2001/07/27 19:46:01  rsonak
 * LOG: First 2 sheets compiling
 * LOG:
 * LOG: Revision 4.2  2001/07/26 22:58:02  rsonak
 * LOG: Commit at end-of-day. Implemented 2 sheets on TLAC
 * LOG:
 * LOG: Revision 4.1  2001/07/26 20:18:41  rsonak
 * LOG: First shot at Signalling Traffic Management
 * LOG: Started with TLAC
 * LOG:
 ****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_types.h>
#include <its_timers.h>

#ident "$Id: ansi-stm.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#include <ansi/snmm.h>
#include <ansi/sltm.h>
#include <ansi/mtp3.h>

#include "mtp3_intern.h"

extern ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
/*
 * local globals: FIXME -- No longer needed; replaced by behaviors
 *
static ITS_BOOLEAN       spRestarting = ITS_FALSE;
static ITS_BOOLEAN       fullRestartNeeded = ITS_TRUE;
static ITS_BOOLEAN       sendingStatus = ITS_FALSE;

 */

/*
 * T22: Timer at restarting SP waiting for signalling links to become
 *      available
 * T23: Timer at restarting SP, started after T22, waiting to receive
 *      all traffic restart allowed messages.
 * T24: Timer at restarting SP with transfer function, started after T23,
 *      waiting to broadcast all traffic restart allowed messages
 * T25: Timer at SP adjacent to restarting SP,
 *      waiting for traffic restart allowed message
 * T26: Timer at restarting SP waiting to repeat traffic restart waiting
 *      message
 * T27: Minimum duration of unavailability for full restart
 */
static ITS_SERIAL   t27 = TIMER_BAD_SERIAL;
/*   TIMERS_CancelSharedTimer is not working so changing it with TIMERS_CancelTimer
     as it is able to remove the timer from local hash too if it is unable to find the
     timer in the DSM*/
#define TIMERS_CancelSharedTimer TIMERS_CancelTimer
#define TIMERS_StartSharedUTimer TIMERS_StartTimer_MSEC
#define TIMERS_StartSharedTimer TIMERS_StartTimer_MSEC

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
SPRestarting_ANSI()
{
    return BEHAVIORS_GetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_spRestarting);
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
SPRestartingSet_ANSI(ITS_BOOLEAN isRestarting)
{

    BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_spRestarting,
                           isRestarting);

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
ITS_BOOLEAN
FullRestartNeeded_ANSI()
{
    return BEHAVIORS_GetBehavior(&ANSI_MTP3_Behaviors, 
                                  MTP3_B_fullRestartNeeded);
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
FullRestartNeededSet_ANSI(ITS_BOOLEAN restartNeeded)
{

    BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_fullRestartNeeded,
                           restartNeeded);

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
ITS_BOOLEAN
SendingStatus_ANSI()
{
    return BEHAVIORS_GetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_sendingStatus);
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
SendingStatusSet_ANSI(ITS_BOOLEAN status) 
{
    BEHAVIORS_SetBehavior(&ANSI_MTP3_Behaviors, MTP3_B_sendingStatus,
                           status);

    BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_ANSI_MTP3_BEHAVIORS);

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
int 
STM_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
              STM_Triggers trigger,
              ITS_OCTET *sif, ITS_USHORT len,
              ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                              sizeof(ITS_OCTET)];

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM, src, trigger, sif, len,
                          linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    if (trigger == SRM_TRIGGER_L2_MSG)
    {
        switch (SNMM_HC0_GET_ANSI(*snmm))
        {
        case SNMM_HC0_CHM_ANSI:  /* changeover/changeback */
            switch (SNMM_HC1_GET_ANSI(*snmm))
            {
            case SNMM_HC1_COO_ANSI:   /* changeover */
                 MTP3_DEBUG(("Changeover Received \n"));
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ORDER,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_COA_ANSI:   /* changeover ack */
                MTP3_DEBUG(("Changeover Ack Received \n"));
                return TCOC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_XCO_ANSI:   /* changeover */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ORDER,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_XCA_ANSI:   /* changeover ack */
                return TCOC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_CBD_ANSI:   /* changeback */
                 MTP3_DEBUG(("CBD Received \n"));
                return TCBC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEBACK_DECL,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_CBA_ANSI:   /* changeback ack */
                 MTP3_DEBUG(("CBA Received \n"));
                return TCBC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEBACK_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET_ANSI(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_ECM_ANSI:  /* emergency changeover */
            switch (SNMM_HC1_GET_ANSI(*snmm))
            {
            case SNMM_HC1_ECO_ANSI:   /* emergency changeover */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_ECA_ANSI:   /* emergency changeover ack */
                return TCOC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_EMERG_CHANGEOVER_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET_ANSI(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_MIM_ANSI:  /* management inhibit */
            switch (SNMM_HC1_GET_ANSI(*snmm))
            {
            case SNMM_HC1_LIN_ANSI:   /* link inhibit */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_INHIBIT_LINK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LUN_ANSI:   /* link uninhibit */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_UNINHIBIT_LINK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LIA_ANSI:   /* link inhibit ack */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_INHIBIT_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LUA_ANSI:   /* link uninhibit ack */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_UNINHIBIT_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LID_ANSI:   /* link inhibit denied */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_INHIBIT_DENIED,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LFU_ANSI:   /* link force uninhibit */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_FORCE_UNINHIBIT_LINK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LLI_ANSI:   /* link local inhibit test */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_LOCAL_INHIBIT_TEST,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LRI_ANSI:   /* link remote inhibit test */
                return TLAC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_REMOTE_INHIBIT_TEST,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET_ANSI(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_TRM_ANSI:  /* traffic restart */
            switch (SNMM_HC1_GET_ANSI(*snmm))
            {
            case SNMM_HC1_TRA_ANSI:   /* traffic restart allowed */
                MTP3_DEBUG(("Traffic Restart Allowed Msg Received \n"));
                return TPRC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_TRAFFIC_RESTART_ALLOWED,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_TRW_ANSI:   /* traffer restart waiting */
                return TSRC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_TRAFFIC_RESTART_WAITING,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET_ANSI(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_UFC_ANSI:  /* user flow control */
            switch (SNMM_HC1_GET_ANSI(*snmm))
            {
            case SNMM_HC1_UPU_ANSI:   /* user part unavailable */
                if (ln)
                {
                  /* Increament Link Peg for UPU Received */
                  PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_UPU_RX );
                }
                return TSFC_Main_ANSI(MTP3_SMH_HMDT,
                                      STM_TRIGGER_UPU,
                                      sif, len,
                                      linkSet, linkCode);/* Pass UPU */

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET_ANSI(*snmm)));
                break;
            }
            break;

        default:
            MTP3_DEBUG(("Invalid HC0 code %d\n",
                        SNMM_HC0_GET_ANSI(*snmm)));
            break;
        }
    }

    MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
    PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
    return (ITS_EINVALIDARGS);
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
FindAlternateRoute(SS7_Destination *ent, MTP3_HEADER_ANSI *mtp3,
                   int whichEntry, int firstMatch, int lastMatch,
                   ITS_OCTET linkSet, ITS_OCTET linkCode,
                   ITS_OCTET *nls, ITS_OCTET *nlc,
                   ITS_EVENT *ev)
{
    ITS_UINT i, cnt;
    int idx;
    ITS_OCTET alts[MAX_LINKS];
    ITS_BOOLEAN gotMatch = ITS_FALSE;

    /*
     * obtain alternative routing data
     */
    *nls = ITS_SS7_DEFAULT_LINK_SET;
    *nlc = ITS_SS7_DEFAULT_LINK_CODE;

    /*
     * Try to find an alternate link first.
     */
    cnt = 0;
    MTP3_ERROR(("linkset %d No of Links %d isAllowed %d",ent->entries[whichEntry]->linkSet->linkSet,ent->entries[whichEntry]->linkSet->numLinks,ent->entries[whichEntry]->isAllowed));
    for (i = 0; i < ent->entries[whichEntry]->linkSet->numLinks && i < MAX_LINKS; i++)
    {
        if (ent->entries[whichEntry]->isAllowed)
        {
            SS7_LinkPtr ln = ent->entries[whichEntry]->linkSet->links[i];
            MTP3_ERROR(("linkset %d linkcode %d isUp %d isAllowed %d testPassed %d\n",ent->entries[whichEntry]->linkSet->linkSet,ln->linkCode,ln->isUp,ln->isAllowed,ln->testPassed));

            if (ln && ln->linkCode != linkCode &&
                ln->isUp && ln->isAllowed && ln->testPassed)
            {
                *nls = ent->entries[whichEntry]->linkSet->linkSet;

                if (*nlc == ITS_SS7_DEFAULT_LINK_CODE)
                {
                    *nlc = ln->linkCode;
                    gotMatch = ITS_TRUE;
                }
                else
                {
                    alts[cnt] = ln->linkCode;
                    cnt++;
                }
            }
        }
    }

    /*
     * handle no alternate link
     */
    if (i == ent->entries[whichEntry]->linkSet->numLinks && !gotMatch)
    {
        /*
         * Do I have a route to this destination? Look at
         * all the ROUTE_Info records and determine if there is
         * at least one allowed route, whose link set is *not*
         * the same as the requester's.
         */
        for (idx = firstMatch; idx <= lastMatch; idx++)
        {
            if (ent->entries[idx]->isAllowed &&
                ent->entries[idx]->linkSet->linkSet != linkSet)
            {
                /*
                 * Try to find an alternate link first.
                 */
                for (i = 0; i < ent->entries[idx]->linkSet->numLinks; i++)
                {
                    SS7_LinkPtr ln = ent->entries[idx]->linkSet->links[i];

                    if (ln && ln->linkCode != linkCode &&
                        ln->isUp && ln->isAllowed && ln->testPassed)
                    {
                        if (*nlc == ITS_SS7_DEFAULT_LINK_CODE)
                        {
                            *nls = (ITS_OCTET)ent->entries[idx]->linkSet->linkSet;

                            *nlc = ln->linkCode;

                            gotMatch = ITS_TRUE;
                        }
                        else
                        {
                            alts[cnt] = ln->linkCode;
                            cnt++;
                        }
                    }
                }

                /*
                 * make sure we have a link
                 */
                if (gotMatch)
                {
                    break;
                }
            }
        }

        /*
         * if no match is found, then there is no alternate route
         * data.  Indicate that by passing the input linkSet as
         * the matching entry (signalling no routing change).
         */
        if (idx > lastMatch)
        {
            MTP3_DEBUG(("No match found for alternate route  for linkSet "
                        "%d\n", linkSet));
            MTP3_Alarm_ANSI(2466, __FILE__, __LINE__,"%x",linkSet);
        }
    }

    /* build the event by hand.  It's weird anyway */
    ITS_EVENT_INIT(ev, ITS_MTP3_ANSI_SRC,
                   2 * sizeof(MTP3_HEADER_ANSI) + 3 * sizeof(ITS_OCTET) + cnt);

    ev->data[0] = MTP3_MSG_USER_DATA;
    memcpy(&ev->data[1], mtp3, sizeof(MTP3_HEADER_ANSI));
    memcpy(&ev->data[sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET)],
           mtp3, sizeof(MTP3_HEADER_ANSI));
    ev->data[2 * sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET)] = linkSet;
    ev->data[2 * sizeof(MTP3_HEADER_ANSI) + 2 * sizeof(ITS_OCTET)] = linkCode;
    if (cnt)
    {
        memcpy(&ev->data[2 * sizeof(MTP3_HEADER_ANSI) + 3 * sizeof(ITS_OCTET)],
               alts, cnt);
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
static int
SetLinkUnavailable(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    int ret = ITS_SUCCESS;
    SS7_LinkPtr ln;

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                         STM_TRIGGER_LINK_UNAVAILABLE,
                         NULL, 0,
                         linkSet, linkCode);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Mark these states before sending link_unavailable to TCOC and TSRC */

    /*ln->stFlags |= LINK_COP; */

    if (SPRestarting_ANSI())
    {
        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                             STM_TRIGGER_LINK_UNAVAILABLE,
                             NULL, 0,
                             linkSet, linkCode);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Mark these states before sending link_unavailable to TCOC and TSRC */

        /* ln->availableState = LINK_UNAVAILABLE; */
    }
    else
    {
        /* ln->availableState = LINK_UNAVAILABLE; */
    }

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
static int
ForceUninhibitLink(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;

    MTP3_TimerContext tc;
    MTP3_HEADER_ANSI omtp3;
    SNMM_MESSAGE snmm;
    ITS_EVENT ev;

    int ret = ITS_SUCCESS;
    
    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));

        return (ITS_EINVALIDARGS);
    }

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }
    
    /* Build SNMM FORCE UNINHIBIT LINK */
    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LFU_ANSI);

    SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
    
    /* Increament Link Peg for LFU Transmitted */
    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

    ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                         SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                         ev.data, ev.len,
                         linkSet, linkCode);
    
    ITS_EVENT_TERM(&ev);

    /* Increament the peg for Link ForceUnInhibit */
     PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

    tc.timerId = MTP3_T13;
    tc.data.linkInfo.linkSet = linkSet;
    tc.data.linkInfo.linkCode = linkCode;

    ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                 __ansi_t13 * USEC_PER_MILLISEC,
                                 &tc, sizeof(MTP3_TimerContext));

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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  Bug Id 972              Resolution for multiple RP
 *                                               recovery alarms/traces bug
 * snagesh   04-04-2005  ACC651-SDS-MTPL-1.0.02  Added handling of STM triggers
 *                       ID::D0010               for LPO feature
 *
 ****************************************************************************/
int
TLAC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    MTP3_HEADER_ANSI omtp3;    
    SNMM_MESSAGE snmm, *snmm_ptr;
    ITS_UINT pc1;
    ITS_OCTET ni;
    ITS_EVENT ev;
    MTP3_TimerContext tc;
    int ret = ITS_SUCCESS;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;    
    ITS_OCTET i, j;
    SS7_Destination *dest;
    ROUTE_MatchInfo mi;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    ITS_OCTET nls, nlc;
    /* Default Loop optimization changes start*/
    ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];
    ITS_UINT k=0,l=0;
    /* Default Loop optimization changes end*/

    /* seems to want linkSet, linkCode */
    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TLAC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* For debugging now */
    ln = LINK_FindLink(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));
    }
    else
    {
        if (trigger != STM_TRIGGER_RP_RECOVERD)
        {
            MTP3_DEBUG(("TLAC state : %d, TLAC flags : %08x\n",
                        ln->availableState, ln->stFlags));
        }
    }
    
    switch (trigger)
    {
    case STM_TRIGGER_INHIBIT_LINK:           /* from MGMT, HMDT */

        if (src == MTP3_SMH_HMDT)
        {
            ni = MTP3_HDR_GET_SIO(*mtp3);
            pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                        sizeof(ITS_OCTET));

            linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

            if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
            {
                MTP3_ERROR(("Can't find adjacent linkSet\n"));

                MTP3_Alarm_ANSI(2471, __FILE__, __LINE__,"Adjacent link %x not found", linkSet);

                return (ITS_EINVALIDARGS);
            }

            linkCode = SNMM_INHIBIT_GET_SLC_ANSI(snmm_ptr->data.managementInhibit);

            MTP3_DEBUG(("TLAC: linkSet = %d, linkCode = %d\n",
                         linkSet, linkCode));

            /* Linkset Pointer */
            ls = LINKSET_FindLinkSet(linkSet);
            if (ls == NULL)
            {
                MTP3_DEBUG(("Can't find link set %d\n", linkSet));

                return (ITS_EINVALIDARGS);
            }

            /* Link Pointer */
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
                MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));
 
                return (ITS_EINVALIDARGS);
            }

            /* Increament Link Peg for LIN Received */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);

            ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_REMOTE_INHIBIT_REQUESTED,
                                 NULL, 0,
                                 ls->linkSet, ln->linkCode);

            MTP3_Alarm_ANSI(2516, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",linkSet,linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }           
        }
        else if (src == MTP3_MGMT)
        {
            /* Increament Link Peg for LIN Received */
            /*PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);*/

            ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,
                                 NULL, 0,
                                 linkSet, linkCode);

            MTP3_Alarm_ANSI(2517, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",linkSet,linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }            
        }

        break;

    case STM_TRIGGER_UNINHIBITING_LINK:
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (src == MTP3_STM_TSRC)
        {
            if (ln->availableState == LINK_UNAVAILABLE)
            {
                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_LOC_BLOCKED) ||
                    (ln->stFlags & LINK_REM_BLOCKED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    if (ln->stFlags & LINK_LOC_INHIBITED)
                    {
                        /*Build and send SNMM UNINHIBIT LINK */

                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                        SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

                        SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                        SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                        /* Increament Link Peg for LUN Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                        MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        	        linkSet,ln->linkCode);

                        ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                             SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                             ev.data, ev.len,
                                             linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                        
                        tc.timerId = MTP3_T12;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                                     __ansi_t12 * USEC_PER_MILLISEC,
                                                     &tc, sizeof(MTP3_TimerContext));

                        if (ln->stFlags & LINK_REM_INHIBITED)
                        {
                            ForceUninhibitLink(linkSet, linkCode);

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                        else
                        {
                            ln->availableState = LINK_UNAVAILABLE;
                        }
                    }
                    else
                    {                            
                        ForceUninhibitLink(linkSet, linkCode);

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                }
            }
        }

        break;

    case STM_TRIGGER_UNINHIBIT_LINK:         /* from HMDT, MGMT, TSRC */

        if (src == MTP3_SMH_HMDT)
        {                        
            ni = MTP3_HDR_GET_SIO(*mtp3);
            pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                                sizeof(ITS_OCTET));

            linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

            if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
            {
                MTP3_ERROR(("Can't find adjacent linkSet\n"));

                return (ITS_EINVALIDARGS);
            }

            linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                       (snmm_ptr->data.managementInhibit);

            /* Linkset Pointer */
            ls = LINKSET_FindLinkSet(linkSet);
            if (ls == NULL)
            {
                MTP3_DEBUG(("Can't find link set %d\n", linkSet));

                return (ITS_EINVALIDARGS);
            }

            /* Link Pointer */
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
                MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));


                return (ITS_EINVALIDARGS);
            }

            /* Increament Link Peg for LUN Received */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);

            if (ln->availableState == LINK_AVAILABLE)
            {
                /* Build and send SNMM UNINHIBIT ACK */
                
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUA_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for LUA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Increament the peg for Link UnInhibit */
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

                /* Stop T13 and Cancel T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;
                TIMERS_CancelSharedTimer(ln->t13);
                ln->t13 = TIMER_BAD_SERIAL;

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);
                
                ln->availableState = LINK_AVAILABLE;
            }
            else if (ln->availableState == LINK_UNAVAILABLE)
            {
                ln->stFlags &= ~LINK_REM_INHIBITED;

                /* Build and send SNMM UNINHIBIT ACK */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUA_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for LUA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                    SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                    ev.data, ev.len,
                                    linkSet, linkCode);

                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_LINK_REMOTE_UNINHIBIT,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Increament the peg for Link UnInhibit */
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

                /* Stop T13 and Cancel T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;
                TIMERS_CancelSharedTimer(ln->t13);

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                ln->t13 = TIMER_BAD_SERIAL;

                if (ln->stFlags & LINK_LOC_INHIBITED)
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_CANCEL_LINK_INHIBITED,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    if ((ln->stFlags & LINK_FAILED) ||
                        (ln->stFlags & LINK_LOC_BLOCKED) ||
                        (ln->stFlags & LINK_REM_BLOCKED))
                    {
                        ln->availableState = LINK_UNAVAILABLE;
                    }
                    else
                    {
                        ln->stFlags |= LINK_CBP;
                        ln->availableState = LINK_AVAILABLE;

                        ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        

                        ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    
                        if (SPRestarting_ANSI())
                        {
                            ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                                 STM_TRIGGER_LINK_AVAILABLE,
                                                 NULL, 0,
                                                 linkSet, linkCode);

                            if (ret != ITS_SUCCESS)
                            {
                                break;
                            }                            
                        }                              
                    }
                }
            }
        }
        else if (src == MTP3_MGMT)
        {
            /* Linkset Pointer */
            ls = LINKSET_FindLinkSet(linkSet);
            if (ls == NULL)
            {
                MTP3_DEBUG(("Can't find link set %d\n", linkSet));

                return (ITS_EINVALIDARGS);
            }

            /* Link Pointer */
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
                MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

                return (ITS_EINVALIDARGS);
            }

            /* Increament Link Peg for LUN Received */
            /*PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);*/

            if (ln->availableState == LINK_AVAILABLE)
            {
                ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_LINK,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
            }
            else if (ln->availableState == LINK_UNAVAILABLE)
            {
                /* Mark management request */

                ln->stFlags |= LINK_MGMT_UNINHIBIT_REQ;

                ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_UNINHIBIT_REQUEST,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* MLM: Seems to be a brain-fart: ln->availableState = LINK_AVAILABLE; */
            }
        }
        break;
    
    case STM_TRIGGER_LOCAL_INHIBIT_ALLOWED:  /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM INHIBIT LINK */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LIN_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_SUCCESS);

            MTP3_Alarm_ANSI(2518, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",linkSet,ln->linkCode);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->stFlags |= LINK_LIP;

            tc.timerId = MTP3_T14;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t14 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t14 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Build SNMM INHIBIT LINK */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LIN_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
            
            tc.timerId = MTP3_T14;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t14 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t14 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_LOCAL_INHIBIT_DENIED:   /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_ANSI(2520, __FILE__, __LINE__,"linkset:linkcode %x:%x", 
                        linkSet,linkCode);

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_DENY);

        if (ln->availableState == LINK_AVAILABLE)
        {
            ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_INHIBIT_ALLOWED:  /* from HMDT */
        break;

    case STM_TRIGGER_INHIBIT_DENIED:   /* from HMDT */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                   (snmm_ptr->data.managementInhibit);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LID Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);
        
        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_DENY);
        
        if (ln->availableState == LINK_AVAILABLE)
        {
            ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->stFlags &= ~LINK_LIP;

            /* Stop T14 */
            TIMERS_CancelSharedTimer(ln->t14);
            ln->t14 = TIMER_BAD_SERIAL;

            ln->stFlags &= ~LINK_INHIBIT_RETRY;

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_REMOTE_INHIBIT_ALLOWED: /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_SUCCESS);

        if (ln->availableState == LINK_AVAILABLE)
        {
            ln->stFlags |= LINK_REM_INHIBITED;

            /* Build SNMM INHIBIT ACK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LIA_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_ANSI(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Increament the peg for Link Inhibit */
             PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);

            /* Start T21 */
            tc.timerId = MTP3_T21;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t21 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t21 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            if (ln->stFlags & LINK_CBP)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;


                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_UNAVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);

                /* FIX: isUp should be re-set to true to allow SLT 
                 *      messages on that link.
                 */
                 LINK_SetLinkState(ln, ITS_TRUE);
            }          
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags |= LINK_REM_INHIBITED;

            /* Build SNMM INHIBIT ACK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LIA_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_ANSI(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Increament the peg for Link Inhibit */
             PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);

            /* Start T21 */
            tc.timerId = MTP3_T21;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t21 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t21 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_REMOTE_INHIBIT_DENIED:  /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_ANSI(2521, __FILE__, __LINE__,
                        "linkset:linkcode %x:%x",linkSet,linkCode);

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_DENY);

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM INHIBIT DENIED and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LID_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LID Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Build SNMM INHIBIT DENIED and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LID_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LID Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_INHIBIT_ACK:            /* from HMDT */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));
 
            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                   (snmm_ptr->data.managementInhibit);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LIA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);

        if (ln->availableState == LINK_AVAILABLE)
        {

            if (!(ln->stFlags & LINK_LIP))
            {
                ln->availableState = LINK_AVAILABLE;
                return ITS_SUCCESS;
            }

            /* local inhibit is in progress */

            ln->stFlags |= LINK_LOC_INHIBITED;

            ln->stFlags &= ~LINK_LIP;

            ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_ANSI(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

           /* Stop T14 */
            TIMERS_CancelSharedTimer(ln->t14);
            ln->t14 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link Inhibit */
             PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);

            /* Start T20 */
            tc.timerId = MTP3_T20;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t20 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ansi_t20 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->stFlags &= ~LINK_INHIBIT_RETRY;

            if (ln->stFlags & LINK_CBP)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;

                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_UNAVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);

                /* FIX: isUp should be re-set to true to allow SLT 
                 *      messages on that link.
                 */
                 LINK_SetLinkState(ln, ITS_TRUE);

            }          
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags |= LINK_LOC_INHIBITED;

            ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_ANSI(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Stop T14 */
            TIMERS_CancelSharedTimer(ln->t14);
            ln->t14 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link Inhibit */
             PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT); 

            /* Start T20 */
            tc.timerId = MTP3_T20;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t20 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t20 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->stFlags &= ~LINK_INHIBIT_RETRY;
            
            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_UNINHIBIT_ACK:            /* from HMDT */

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                   (snmm_ptr->data.managementInhibit);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LUA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);

        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_UNINHIBIT_SUCCESS);

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Stop T12 */
            TIMERS_CancelSharedTimer(ln->t12);
            ln->t12 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link UnInhibit */
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

            /* Cancel T13 retry */

            ln->timerRetryState.t13RetryOnOff = ITS_FALSE;

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Cancel locally inhibited management request */
            ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;
            ln->stFlags &= ~LINK_LOC_INHIBITED;

            ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_UNINHIBIT_LINK,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }            

            /* Stop T12 */
            TIMERS_CancelSharedTimer(ln->t12);
            ln->t12 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link UnInhibit */
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

            /* Cancel T12 retry */

            ln->timerRetryState.t12RetryOnOff = ITS_FALSE;

            if (ln->stFlags & LINK_REM_INHIBITED)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ret = TSRC_Main_ANSI(MTP3_STM_TLAC, 
                                     STM_TRIGGER_CANCEL_LINK_INHIBITED,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_LOC_BLOCKED) ||
                    (ln->stFlags & LINK_REM_BLOCKED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                
                    if (SPRestarting_ANSI())
                    {
                        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }                         
                }            
            }
        }

        break;

    case STM_TRIGGER_INHIBIT_POSSIBLE:       /* from TSRC */
        break;

    case STM_TRIGGER_INHIBIT_IMPOSSIBLE:     /* from TSRC */
        break;

    case STM_TRIGGER_UNINHIBIT_POSSIBLE:      /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Build SNMM UNINHIBIT LINK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
            /* Increament Link Peg for LUN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

            MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                            linkSet,ln->linkCode);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
            
            /* Start T12 */
            tc.timerId = MTP3_T12;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t12 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_UNAVAILABLE;
        }

        break;

    case STM_TRIGGER_UNINHIBIT_IMPOSSIBLE:    /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));
 
            return (ITS_EINVALIDARGS);
        }

        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_FAILURE);

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if ((ln->stFlags & LINK_FAILED) ||
                (ln->stFlags & LINK_LOC_BLOCKED) ||
                (ln->stFlags & LINK_REM_BLOCKED))
            {
                ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Cancel Management request */
                ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
               /* Build SNMM UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for LUN Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);            

                MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode "
                                "%x:%x", linkSet, ln->linkCode);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                
                /* Start T12 */
                tc.timerId = MTP3_T12;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t12 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
        }

        break;

    case STM_TRIGGER_ADJACENT_SP_RESTARTING: /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        /* Here you may not get a linkCode. So loop for all the links in this linkSet */

        for (j = 0; j < ls->numLinks; j++)
        {            
            ln = ls->links[j];        

            if (ln->availableState == LINK_AVAILABLE)
            {
                /*
                 * Action: mark adjacent SP restarting.  Not necessary, TSRC
                 * marks this.
                 */

                /*Cancel all inhibiting marks and timers */

                if (ln->stFlags & LINK_LOC_INHIBITED)
                {
                    ln->stFlags &= ~LINK_LOC_INHIBITED;
                }
            
                if (ln->stFlags & LINK_REM_INHIBITED)
                {
                    ln->stFlags &= ~LINK_REM_INHIBITED;
                }

                if (ln->stFlags & LINK_LIP)
                {
                    ln->stFlags &= ~LINK_LIP;
                }

                if (ln->stFlags & LINK_RIP)
                {
                    ln->stFlags &= ~LINK_RIP;
                }

                /* Cancel T12, T13, T14, T20, T21 */

                /* Stop T12 */
                TIMERS_CancelSharedTimer(ln->t12);
                ln->t12 = TIMER_BAD_SERIAL;
            
                /* Stop T13 */
                TIMERS_CancelSharedTimer(ln->t13);
                ln->t13 = TIMER_BAD_SERIAL;

                /* Stop T14 */
                TIMERS_CancelSharedTimer(ln->t14);
                ln->t14 = TIMER_BAD_SERIAL;

                /* Stop T20 */
                TIMERS_CancelSharedTimer(ln->t20);
                ln->t20 = TIMER_BAD_SERIAL;

                /* Stop T21 */
                TIMERS_CancelSharedTimer(ln->t21);
                ln->t21 = TIMER_BAD_SERIAL;

                ln->availableState = LINK_AVAILABLE;
            }
            else if (ln->availableState == LINK_UNAVAILABLE)
            {
                /*
                 * Action: mark adjacent SP restarting.  Not necessary, TSRC
                 * marks this.
                 */

                /*Cancel all inhibiting marks and timers */

                if (ln->stFlags & LINK_LOC_INHIBITED)
                {
                    ln->stFlags &= ~LINK_LOC_INHIBITED;
                }
            
                if (ln->stFlags & LINK_REM_INHIBITED)
                {
                    ln->stFlags &= ~LINK_REM_INHIBITED;
                }

                if (ln->stFlags & LINK_LIP)
                {
                    ln->stFlags &= ~LINK_LIP;
                }

                if (ln->stFlags & LINK_RIP)
                {
                    ln->stFlags &= ~LINK_RIP;
                }

                /* Cancel T12, T13, T14, T20, T21 */

                /* Stop T12 */
                TIMERS_CancelSharedTimer(ln->t12);
                ln->t12 = TIMER_BAD_SERIAL;
            
                /* Stop T13 */
                TIMERS_CancelSharedTimer(ln->t13);
                ln->t13 = TIMER_BAD_SERIAL;

                /* Stop T14 */
                TIMERS_CancelSharedTimer(ln->t14);
                ln->t14 = TIMER_BAD_SERIAL;

                /* Stop T20 */
                TIMERS_CancelSharedTimer(ln->t20);
                ln->t20 = TIMER_BAD_SERIAL;

                /* Stop T21 */
                TIMERS_CancelSharedTimer(ln->t21);
                ln->t21 = TIMER_BAD_SERIAL;

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_LOC_BLOCKED) ||
                    (ln->stFlags & LINK_REM_BLOCKED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_AVAILABLE;
                }
            }
        }

        break;

    case STM_TRIGGER_ADJACENT_SP_RESTARTED:  /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            /*
             * Action: cancel adjacent SP restarting.  Not necessary, TSRC
             * marks this.
             */
            if (ls->adjRestart)
            {
                ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_AVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->stFlags |= LINK_CBP;
            }

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /*
             * Action: cancel adjacent SP restarting.  Not necessary, TSRC
             * marks this.
             */

            ln->availableState = LINK_UNAVAILABLE;
        }

        break;

    case STM_TRIGGER_CHANGEBACK_TERMINATED:  /* from TCBC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            ln->stFlags &= ~LINK_CBP;
            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_CBP;

            if (src == MTP3_STM_TCBC)
            {
                if (ln->stFlags & LINK_COO)
                {
                    ln->availableState = LINK_UNAVAILABLE;
                    ln->stFlags |= LINK_COP;


                    ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_CHANGEOVER_ORDER,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ln->stFlags &= ~(LINK_ECOO|LINK_COO);

                    ret = SetLinkUnavailable(linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    /* Increament the counter for Link Unavailable */
                    PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
                }
                else
                {
                    if (ln->stFlags & LINK_ECOO)
                    {
                        ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }
                    else
                    {
                        ln->availableState = LINK_UNAVAILABLE;
                        ln->stFlags |= LINK_COP;


                        ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_UNAVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }

                    ln->stFlags &= ~(LINK_ECOO|LINK_COO);

                    ret = SetLinkUnavailable(linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }                         
                    /* Increament the counter for Link Unavailable */
                    PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
                }
            }
            else
            {
                /* Nothing to do!! */
            }
        }
        break;

    case STM_TRIGGER_CHANGEOVER_EXECUTED:    /* from TCOC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_COP;

            if (ln->stFlags & LINK_RTB_CLEAR_REQ)
            {
                ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                     SLM_TRIGGER_CLEAR_RTB,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Mark RTB clear pending */
                ln->stFlags |= LINK_RTB_CLEAR_PENDING;

                /* Cancel RTB clear request */
                ln->stFlags &= ~LINK_RTB_CLEAR_REQ;

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_REM_BLOCKED) ||
                    (ln->stFlags & LINK_LOC_INHIBITED) ||
                    (ln->stFlags & LINK_REM_INHIBITED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_ANSI())
                    {
                        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }                    
                }
            }
        }
        break;

    case STM_TRIGGER_CHANGEOVER_NOT_REQD:    /* from TCOC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_COP;

            if ((ln->stFlags & LINK_FAILED) ||
                (ln->stFlags & LINK_REM_BLOCKED) ||
                (ln->stFlags & LINK_LOC_INHIBITED) ||
                (ln->stFlags & LINK_REM_INHIBITED))
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_AVAILABLE;

                ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_AVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                
                if (SPRestarting_ANSI())
                {
                    ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }                    
                }                
            }
        }
        break;

    case STM_TRIGGER_LINK_FAILED:            /* from SLM */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            MTP3_DEBUG(("TLAC: LINK_FAILED: link was available\n"));

            ln->stFlags |= LINK_FAILED;

            if (ln->stFlags & LINK_CBP)
            {
                MTP3_DEBUG(("TLAC: LINK_FAILED: changeback in progress\n"));

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;
                MTP3_DEBUG(("TLAC: LINK_FAILED: Changeover in progress\n"));

                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_UNAVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

#if 0
                if (ret != ITS_SUCCESS)
                {
                    break;
                }
#endif

                ret = SetLinkUnavailable(linkSet, linkCode);

#if 0
                if (ret != ITS_SUCCESS)
                {
                    break;
                }
#endif
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);

            }                    
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            MTP3_DEBUG(("TLAC: LINK_FAILED: link was unavailable\n"));

            ln->stFlags |= LINK_FAILED;

            ln->stFlags &= ~LINK_REM_BLOCKED;
            ln->stFlags &= ~LINK_LOC_BLOCKED;

            ln->availableState = LINK_UNAVAILABLE;

            /*
             * we MUST do this.  LSAC will ignore it if it's
             * not in the right state, but if we fail to do
             * this LSAC will NOT start restoration.
             */
            MTP3_DEBUG(("SLM_TRIGGER_STM_READY -- FILE %s LINE %d\n",__FILE__,__LINE__));
            LSAC_Main_ANSI(MTP3_STM_TLAC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);
        }

        break;

    case STM_TRIGGER_LINK_IN_SERVICE:        /* from SLM */
        MTP3_Alarm_ANSI(2526, __FILE__, __LINE__,
               "linkset:linkcode %x:%x",linkSet,linkCode);

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Cancel link failed */

        ln->stFlags &= ~LINK_FAILED;
            
        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (!(ln->stFlags & LINK_LOC_INHIBITED) &&
                !(ln->stFlags & LINK_REM_INHIBITED))
            {
                if (ln->stFlags & LINK_COP)
                {
                    ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;
                    MTP3_ERROR(("ln->availableState = LINK_AVAILABLE\n"));

                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }                    

                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_ANSI())
                    {
												MTP3_ERROR(("SPRestarting_ANSI\n"));
                        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }
                    
                }                
            }
        }

        break;

    case STM_TRIGGER_RP_OUTAGE:              /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_ANSI(2403, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        ln->stFlags |= LINK_REM_BLOCKED;

        if (ln->stFlags & LINK_CBP)
        {
            ln->availableState = LINK_UNAVAILABLE;
        }
        else
        {
            ln->availableState = LINK_UNAVAILABLE;
            ln->stFlags |= LINK_COP;

            ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_UNAVAILABLE,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = SetLinkUnavailable(linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
            /* Increament the counter for Link Unavailable */
            PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
        }                    
        break;

    case STM_TRIGGER_RP_RECOVERD:            /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (!(ln->stFlags & LINK_REM_BLOCKED))
        {
            break;
        }

        MTP3_Alarm_ANSI(2404, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet, linkCode);

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_REM_BLOCKED;

            /*If RTB or RB clear pending */
            if (ln->stFlags & LINK_RTB_CLEAR_PENDING ||
                ln->stFlags & LINK_RB_CLEAR_PENDING)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                if (ln->stFlags & LINK_COP)
                {
                    if ((ln ->stFlags & LINK_LOC_INHIBITED) ||
                        (ln ->stFlags & LINK_REM_INHIBITED))
                    {
                        /* Mark RTB clear request */
                        ln->stFlags |= LINK_RTB_CLEAR_REQ;

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                    else
                    {
                        /* If Adjacent SP restaring */
                        if (ls->adjRestart)
                        {
                            /* Mark RTB clear request */
                            ln->stFlags |= LINK_RTB_CLEAR_REQ;

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                        else
                        {
                            ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                                 SLM_TRIGGER_RESUME,
                                                 NULL, 0,
                                                 linkSet, linkCode);

                            if (ret != ITS_SUCCESS)
                            {
                                break;
                            }

                            ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                                 STM_TRIGGER_LINK_AVAILABLE,
                                                 NULL, 0,
                                                 linkSet, linkCode);

                            if (ret != ITS_SUCCESS)
                            {
                                break;
                            }

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                    }
                }
                else /* else for 'is COP?' */
                {
                    ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                         SLM_TRIGGER_CLEAR_RTB,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
            }
        }

        break;

    case STM_TRIGGER_LP_OUTAGE:              /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_ANSI(2524, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        ln->stFlags |= LINK_LOC_BLOCKED;

        if (ln->stFlags & LINK_CBP)
        {
            ln->availableState = LINK_UNAVAILABLE;
        }
        else
        {
            ln->availableState = LINK_UNAVAILABLE;
            /*ln->stFlags |= LINK_COP;*/
/*
            ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_UNAVAILABLE,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
*/
            ret = SetLinkUnavailable(linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            LSAC_Main_ANSI(MTP3_STM_TSRC,
                           SLM_TRIGGER_LINK_DELOADED,
                           NULL, 0,
                           linkSet, linkCode);

            /* Increament the counter for Link Unavailable */
            PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
        }                    
        break;

    case STM_TRIGGER_LP_RECOVERD:            /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (!(ln->stFlags & LINK_LOC_BLOCKED))
        {
            break;
        }
       

        MTP3_Alarm_ANSI(2525, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_LOC_BLOCKED;

            if ((ln ->stFlags & LINK_LOC_INHIBITED) ||
               (ln ->stFlags & LINK_REM_INHIBITED))
            {
                ln->availableState = LINK_UNAVAILABLE;

            }
            else
            {  
           
               ln->availableState = LINK_AVAILABLE;

               ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                    STM_TRIGGER_LINK_AVAILABLE,
                                    NULL, 0,
                                    linkSet, linkCode);
           }
        }
        break;

    case STM_TRIGGER_RB_CLEARED:             /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Cancel RB clear pending */
            ln->stFlags &= ~LINK_RB_CLEAR_PENDING;
            
            /* If RTB clear pending */
            if (ln->stFlags | LINK_RTB_CLEAR_PENDING)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_REM_BLOCKED) ||
                    (ln->stFlags & LINK_LOC_INHIBITED) ||
                    (ln->stFlags & LINK_REM_INHIBITED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_ANSI())
                    {
                        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }                    
                }
            }
        }

        break;

    case STM_TRIGGER_RTB_CLEARED:            /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Cancel RTB clear pending */
            ln->stFlags &= ~LINK_RTB_CLEAR_PENDING;
            
            /* If RB clear pending */
            if (ln->stFlags | LINK_RB_CLEAR_PENDING)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_REM_BLOCKED) ||
                    (ln->stFlags & LINK_LOC_INHIBITED) ||
                    (ln->stFlags & LINK_REM_INHIBITED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_ANSI())
                    {
                        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }                    
                }
            }
        }

        break;

    case STM_TRIGGER_RESTART_BEGIN:          /* from TPRC */        

        /* Default Loop optimization changes start*/
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
       // MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (k = 0; k < MAX_LINKSETS; k++)
         {
          for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
          {
            if(linkTransportMapDB[k][l] >0) 
             {  
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               if( k > 0 && k < 252)
               {
                lscount++;
                linkset[cnt++]=k;
                MTP3_ERROR((" linkset = %d\n",k));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));
        /* Default Loop optimization changes end*/
        for (i = 0; i < (lscount ); i++)
        {

            if ((ls = LINKSET_FindLinkSet(linkset[i])) == NULL ||
                 ls->adjacent == 0)
            {
                continue;
            }

            for (j = 0; j < ls->numLinks; j++)
            {                 
                ln = ls->links[j];

                if (ln->availableState == LINK_AVAILABLE)
                {
                    /* Mark SP restaring */
                    /* this action is taken by TPRC */

                    /*Cancel all inhibiting marks and timers */

                    if (ln->stFlags & LINK_LOC_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_LOC_INHIBITED;
                    }
            
                    if (ln->stFlags & LINK_REM_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_REM_INHIBITED;
                    }

                    if (ln->stFlags & LINK_LIP)
                    {
                        ln->stFlags &= ~LINK_LIP;
                    }

                    if (ln->stFlags & LINK_RIP)
                    {
                        ln->stFlags &= ~LINK_RIP;
                    }

                    /* Stop T12 */
                    TIMERS_CancelSharedTimer(ln->t12);
                    ln->t12 = TIMER_BAD_SERIAL;
            
                    /* Stop T13 */
                    TIMERS_CancelSharedTimer(ln->t13);
                    ln->t13 = TIMER_BAD_SERIAL;

                    /* Stop T14 */
                    TIMERS_CancelSharedTimer(ln->t14);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T20 */
                    TIMERS_CancelSharedTimer(ln->t20);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T21 */
                    TIMERS_CancelSharedTimer(ln->t21);
                    ln->t21 = TIMER_BAD_SERIAL;
            
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_AVAILABLE;
                }
                else if (ln->availableState == LINK_UNAVAILABLE)
                {
                    /* Mark SP restaring */
                    /* this action is taken by TPRC */

                    /*Cancel all inhibiting marks and timers */

                    if (ln->stFlags & LINK_LOC_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_LOC_INHIBITED;
                    }
            
                    if (ln->stFlags & LINK_REM_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_REM_INHIBITED;
                    }

                    if (ln->stFlags & LINK_LIP)
                    {
                        ln->stFlags &= ~LINK_LIP;
                    }

                    if (ln->stFlags & LINK_RIP)
                    {
                        ln->stFlags &= ~LINK_RIP;
                    }

                    /* Stop T12 */
                    TIMERS_CancelSharedTimer(ln->t12);
                    ln->t12 = TIMER_BAD_SERIAL;
            
                    /* Stop T13 */
                    TIMERS_CancelSharedTimer(ln->t13);
                    ln->t13 = TIMER_BAD_SERIAL;

                    /* Stop T14 */
                    TIMERS_CancelSharedTimer(ln->t14);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T20 */
                    TIMERS_CancelSharedTimer(ln->t20);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T21 */
                    TIMERS_CancelSharedTimer(ln->t21);
                    ln->t21 = TIMER_BAD_SERIAL;

                   /*
                    * if fullRestart and spRestarting, assume the links are down
                    * until proven otherwise.  Otherwise, check the status we think
                    * they have.
                    */
                    if ((FullRestartNeeded_ANSI() && SPRestarting_ANSI()) ||
                        (ln->stFlags & LINK_FAILED) ||
                        (ln->stFlags & LINK_LOC_BLOCKED) ||
                        (ln->stFlags & LINK_REM_BLOCKED))
                    {
                        /* If LPO */
                        if (SPRestarting_ANSI())
                        {
                            /* If LPO duration > T1 OR unknown */
                            if (ITS_TRUE)
                            {
                                ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                                     SLM_TRIGGER_CLEAR_BUFFERS,
                                                     NULL, 0,
                                                     ls->linkSet,
                                                     ln->linkCode);

                                if (ret != ITS_SUCCESS)
                                {
                                    break;
                                }

                                /* Mark RTB clear pending and RB clear pending */
                                ln->stFlags |= LINK_RTB_CLEAR_PENDING;
                                ln->stFlags |= LINK_RB_CLEAR_PENDING;

                                ln->availableState = LINK_UNAVAILABLE;
                            }
                            else
                            {
                                if (ln->stFlags & LINK_REM_BLOCKED)
                                {
                                    ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                                     SLM_TRIGGER_CLEAR_BUFFERS,
                                                     NULL, 0,
                                                     ls->linkSet,
                                                     ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    /* Mark RTB clear pending and RB clear pending */
                                    ln->stFlags |= LINK_RTB_CLEAR_PENDING;
                                    ln->stFlags |= LINK_RB_CLEAR_PENDING;

                                    ln->availableState = LINK_UNAVAILABLE;
                                }
                                else
                                {
                                    ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                                         SLM_TRIGGER_RESUME,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                                         STM_TRIGGER_LINK_AVAILABLE,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                                         STM_TRIGGER_LINK_AVAILABLE,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                                         STM_TRIGGER_LINK_AVAILABLE,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ln->availableState = LINK_AVAILABLE;
                                }
                            }
                        }
                        else
                        {
                            /* Typo in TLAC sheet 11 */
                            /* Should be GOTO 23 of sheet 11 and NOT 23 of sheet 10 */

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                    }
                    else
                    {
                        ln->availableState = LINK_AVAILABLE;

                        ret = TCBC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             ls->linkSet, ln->linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }

                        ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             ls->linkSet, ln->linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }

                        ret = TPRC_Main_ANSI(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             ls->linkSet, ln->linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }     
                }
            }                                
        }
        break;

    case STM_TRIGGER_RESTART_END:            /* from TPRC */
        /* Default Loop optimization changes start*/
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
       // MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (k = 0; k < MAX_LINKSETS; k++)
         {
          for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
          {
            if(linkTransportMapDB[k][l] >0) 
             {  
        //       MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               if( k > 0 && k < 252)
               {
                lscount++;
                linkset[cnt++]=k;
                MTP3_ERROR((" linkset = %d\n",k));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));
        /* Default Loop optimization changes end*/

        for (i = 0; i < (lscount); i++)
        {

            if ((ls = LINKSET_FindLinkSet(linkset[i])) == NULL ||
                 ls->adjacent == 0)
            {
                continue;
            }

            for (j = 0; j < ls->numLinks; j++)
            {
                /* clear flags */
                ln = ls->links[j];
                if (ln->availableState == LINK_AVAILABLE)
                {
                    /*
                     * Action: cancel SP restarting.  This is not necessary, TPRC
                     * does this.
                     */
                    ln->availableState = LINK_AVAILABLE;
                }
                else if (ln->availableState == LINK_UNAVAILABLE)
                {
                    /*
                     * Action: cancel SP restarting.  This is not necessary, TPRC
                     * does this.
                     */
                    ln->availableState = LINK_UNAVAILABLE;
                }
            }
        }
        
        break;

    case STM_TRIGGER_LOCAL_INHIBIT_TEST:           /* from SMH */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                    sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                   (snmm_ptr->data.managementInhibit);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LLI Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_LLI_RX );

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM FORCE UNINHIBIT LINK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LFU_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
            /* Increament Link Peg for LFU Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Increament the peg for Link ForceUnInhibit */
             PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

            /* Start T13 */
            tc.timerId = MTP3_T13;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t13 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_REM_INHIBITED)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ForceUninhibitLink(linkSet, linkCode);

                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_LOCAL_UNINHIBIT_TEST:         /* from SMH */
        break;

    case STM_TRIGGER_FORCE_UNINHIBIT_LINK:          /* from HMDT */
       
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                   (snmm_ptr->data.managementInhibit);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LFU Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_LFU_RX );

        /* Build SNMM UNINHIBIT LINK and send */

        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
        SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

        SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
        
        /* Increament Link Peg for LUN Transmitted */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

        MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,ln->linkCode);

        ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                             SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                             ev.data, ev.len,
                             linkSet, linkCode);
        ITS_EVENT_TERM(&ev);

        if (ret != ITS_SUCCESS)
        {
            break;
        }

        /* Increament the peg for Link ForceUnInhibit */
         PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

        /* Start T12 */
        tc.timerId = MTP3_T12;
        tc.data.linkInfo.linkSet = linkSet;
        tc.data.linkInfo.linkCode = linkCode;

        ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                     __ansi_t12 * USEC_PER_MILLISEC,
                                     &tc, sizeof(MTP3_TimerContext));

        ln->availableState = LINK_UNAVAILABLE;          

        break;

    case STM_TRIGGER_REMOTE_INHIBIT_TEST:           /* from SMH */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_INHIBIT_GET_SLC_ANSI
                   (snmm_ptr->data.managementInhibit);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LRI Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_LRI_RX );

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM UNINHIBIT LINK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

            SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
            /* Increament Link Peg for LUN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

            MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                            linkSet,ln->linkCode);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);
            
            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Start T12 */
            tc.timerId = MTP3_T12;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                         __ansi_t12 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_LOC_INHIBITED)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                /* Build SNMM UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LUN Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                                linkSet,ln->linkCode);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            
                if (ret != ITS_SUCCESS)
                {
                    break;
                }
            
                /* Start T12 */
                tc.timerId = MTP3_T12;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t12 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
        }

        break;

    case STM_TRIGGER_REMOTE_UNINHIBIT_TEST:         /* from SMH */
        break;

    case STM_TRIGGER_CHANGEOVER_ORDER:  /* from SMH */

        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                STM_TRIGGER_CHANGEOVER_ORDER"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_CHANGEOVER_GET_SLC_ANSI(snmm_ptr->data.changeOver);

        MTP3_Alarm_ANSI(2510, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for COO Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);

        if (ln->availableState == LINK_AVAILABLE)
        {
            MTP3_DEBUG(("*****TLAC: CHANGE_OVER_ORDER: link was available\n"));
            ln->stFlags |= LINK_FAILED;

            ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                 SLM_TRIGGER_CHANGEOVER_ORDER_RECVD,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {

                MTP3_DEBUG(("*****TLAC --> LSAC FAILS\n"));

                break;
            }
            
            if (ln->stFlags & LINK_CBP)
            {
                MTP3_DEBUG(("\n*****CHANGE BACK in PROGRESS\n"));
                ln->stFlags |= LINK_COO;
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;
                MTP3_DEBUG(("\n ln->activityState %d \n",ln->activityState));
                MTP3_DEBUG(("\n*****SET CHANGE OVER in PROGRESS\n"));

                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    MTP3_DEBUG(("TLAC ---> TCOC FAILED\n"));
                    break;
                }

                MTP3_DEBUG(("\n****** SETLINKUNAVAILABLE\n"));
                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    MTP3_DEBUG(("\n****** SETLINKUNAVAILABLE FAILS\n"));
                    break;
                }
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
            }                    
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            MTP3_DEBUG(("*****TLAC: CHANGE_OVER_ORDER: link was unavailable\n"));

            if (ln->stFlags & LINK_COP)
            {
                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                return (ITS_SUCCESS);
            }
            else
            {
                /*Simply fall thru */
            }
            
            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));
 
                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &nls, &nlc, &ev);

            ITS_EVENT_TERM(&ev);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_ECM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_ECA_ANSI);

            SNMM_EMERG_CHANGEOVER_SET_SLC_ANSI(snmm.data.emergencyChangeOver, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
        
            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 nls, nlc);

            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
        }

        break;

    case STM_TRIGGER_EMERG_CHANGEOVER_ORDER:       /* from SMH */

        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No ECO message in trigger \
                STM_TRIGGER_EMERG_CHANGEOVER_ORDER"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI
                   (snmm_ptr->data.emergencyChangeOver);

        MTP3_Alarm_ANSI(2512, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln)
        {
        /* Increament Link Peg for ECO Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            ln->stFlags |= LINK_FAILED;

            ret = LSAC_Main_ANSI(MTP3_STM_TLAC,
                                 SLM_TRIGGER_CHANGEOVER_ORDER_RECVD,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            if (ln->stFlags & LINK_CBP)
            {
                ln->stFlags |= LINK_ECOO;
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;

                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
            }                    
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_COP)
            {
                ret = TCOC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
            }
            else
            {
                /* Simply fall thru */
            
            
            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            /* Send ECA */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &nls, &nlc, &ev);

            ITS_EVENT_TERM(&ev);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_ECM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_ECA_ANSI);

            SNMM_EMERG_CHANGEOVER_SET_SLC_ANSI(snmm.data.emergencyChangeOver, ln->linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
        
            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 nls, nlc);
            ITS_EVENT_TERM(&ev);
           
            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
           }/*Sandeep changed for ECA as it is sending multiple ECA on receving ECO */
        }

        break;

    case STM_TRIGGER_T12:                    /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }  

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            if (ln->timerRetryState.t12RetryOnOff)
            {
                /* Cancel T12 retry */

                ln->timerRetryState.t12RetryOnOff = ITS_FALSE;

                ln->availableState = LINK_AVAILABLE;
            }
            else
            {
                /* Mark T12 retry */
                ln->timerRetryState.t12RetryOnOff = ITS_TRUE;

                /* Build SNMM UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LUN Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                                linkSet,ln->linkCode);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Start T12 */
                tc.timerId = MTP3_T12;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t12 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));
            }
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->timerRetryState.t12RetryOnOff)
            {
                /* Cancel T12 retry */
                ln->timerRetryState.t12RetryOnOff = ITS_FALSE;
                
                if (ln->stFlags & LINK_MGMT_UNINHIBIT_REQ)
                {
                    ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                         MGMT_TRIGGER_UNINHIBIT_REQ_TIMEOUT,
                                         sif, len,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    /* Cancel MGMT request */
                    ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;
    
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                     sif, len,
                                     linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
            }
            else
            {
                /* Mark T12 retry */
                ln->timerRetryState.t12RetryOnOff = ITS_TRUE;

                if (ln->stFlags & LINK_MGMT_UNINHIBIT_REQ)
                {
                    ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                         STM_TRIGGER_UNINHIBIT_REQUEST,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    if ((ln->stFlags & LINK_FAILED) ||
                        (ln->stFlags & LINK_LOC_BLOCKED) ||
                        (ln->stFlags & LINK_REM_BLOCKED))
                    {
                        ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                             MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                             sif, len,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }

                        /* Cancel Management request */
                        ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                    else
                    {
                       /* Build SNMM UNINHIBIT LINK and send */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                        SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LUN_ANSI);

                        SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                        SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                        /* Increament Link Peg for LUN Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                        MTP3_Alarm_ANSI(2519, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                                        linkSet,ln->linkCode);

                        ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                             SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                             ev.data, ev.len,
                                             linkSet, linkCode);
                        ITS_EVENT_TERM(&ev);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                
                        /* Start T12 */
                        tc.timerId = MTP3_T12;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                                     __ansi_t12 * USEC_PER_MILLISEC,
                                                     &tc, sizeof(MTP3_TimerContext));

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                }                
            }
        }
        break;

    case STM_TRIGGER_T13:                    /* from timer control */    

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            if (ln->timerRetryState.t13RetryOnOff)
            {
                /* Cancel T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;

                ln->availableState = LINK_AVAILABLE;
            }
            else
            {
                /* Mark T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_TRUE;

                /* Build SNMM FORCE UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LFU_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LFU Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                /* Start T13 */
                tc.timerId = MTP3_T13;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t13 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));
            }
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->timerRetryState.t13RetryOnOff)
            {
                /* Cancel T13 retry */

                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;

                ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                /* Mark T13 retry */

                ln->timerRetryState.t13RetryOnOff = ITS_TRUE;

                /* Build SNMM FORCE UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LFU_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LFU Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                /* Start T13 */
                tc.timerId = MTP3_T13;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t13 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_T14:                    /* from timer control */
        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {            
            ITS_C_ASSERT(ln->stFlags & LINK_LIP);
        
            ln->stFlags &= ~LINK_LIP;

            if (ln->stFlags & LINK_INHIBIT_RETRY)
            {
                ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->stFlags &= ~LINK_INHIBIT_RETRY;
                ln->availableState = LINK_AVAILABLE;
            }
            else
            {
                ln->stFlags |= LINK_INHIBIT_RETRY;

                ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->availableState = LINK_AVAILABLE;
            }
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_INHIBIT_RETRY)
            {
                ret = MGMT_Main_ANSI(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->stFlags &= ~LINK_INHIBIT_RETRY;
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->stFlags |= LINK_INHIBIT_RETRY;

                ret = TSRC_Main_ANSI(MTP3_STM_TLAC,
                                     STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_T20:                    /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_LOC_INHIBITED)
            {
                /* Build SNMM LOCAL INHIBIT TEST and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LLI_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LLI Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX);

                MTP3_Alarm_ANSI(2522, __FILE__, __LINE__,"linkset:linkcode %x:%x", linkSet,linkCode);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Start T20 */
                tc.timerId = MTP3_T20;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t20 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t20 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_T21:                    /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_REM_INHIBITED)
            {
                /* Build SNMM REMOTE INHIBIT TEST and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_MIM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_LRI_ANSI);

                SNMM_INHIBIT_SET_SLC_ANSI(snmm.data.managementInhibit, ln->linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LRI Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);

                MTP3_Alarm_ANSI(2523, __FILE__, __LINE__, "linkset:linkcode "
                                "%x:%x", linkSet, linkCode);

                ret = HMRT_Main_ANSI(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Start T21 */
                tc.timerId = MTP3_T21;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t21 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                             __ansi_t21 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if an SP is accessible, via any route/linkSet
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
static ITS_BOOLEAN
AdjacentAccessible(SS7_LinkSetPtr ls)
{
    ROUTE_MatchInfo mi;
    SS7_Destination *ent;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

    if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ls->ni,
                                      ls->linkSet,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        MTP3_ERROR(("Can't parse route info\n"));

        return (ITS_FALSE);
    }

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find route\n"));

        return (ITS_FALSE);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i]->linkSet->isUp &&
            ent->entries[i]->isAllowed)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Determine if an adjacent is directly accessible
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
static ITS_BOOLEAN
LinkSetAvailable(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isAllowed)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
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
static ITS_BOOLEAN
AlternateLink(SS7_LinkSetPtr ls, SS7_LinkPtr ln)
{
    ITS_UINT i;

    ITS_C_ASSERT(ls != NULL && ln != NULL);

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isUp &&
            ls->links[i]->isAllowed &&
            ls->links[i]->testPassed &&
            ls->links[i]->linkCode != ln->linkCode)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if SP is accessible via any other linkSet than this one.
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
static ITS_BOOLEAN
AlternateRoute(ROUTE_Info *ri)
{
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
    SS7_Destination *ent;
    ROUTE_MatchInfo mi;

    ITS_C_ASSERT(ri != NULL);

    mi.basic = ri->basic;
    mi.linkSet = ri->linkSet->linkSet;
    mi.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
    mi.priority = ITS_SS7_DEFAULT_PRI;
    mi.sls = ITS_SS7_DEFAULT_SLS;

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find match\n"));

        return (ITS_FALSE);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        MTP3_DEBUG(("AlternateRoute: pc %08x vs %08x ri %08x cmp %08x ls %d vs %d\n"
                    "up %d allowed %d\n",
                    ri->basic.dpc, ent->entries[i]->basic.dpc,
                    ri, ent->entries[i], ri->linkSet->linkSet,
                    ent->entries[i]->linkSet->linkSet,
                    ent->entries[i]->linkSet->isUp,
                    ent->entries[i]->isAllowed));

        if (ent->entries[i] != ri &&
            ent->entries[i]->isAllowed
#if 1
            && ent->entries[i]->linkSet->isUp
#endif
            )
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if SP is accessible via any other linkSet than this one.
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
static ROUTE_Info *
GetAlternateRoute(ROUTE_Info *ri)
{
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
    SS7_Destination *ent;
    ROUTE_MatchInfo mi;

    ITS_C_ASSERT(ri != NULL);

    mi.basic = ri->basic;
    mi.linkSet = ri->linkSet->linkSet;
    mi.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
    mi.priority = ITS_SS7_DEFAULT_PRI;
    mi.sls = ITS_SS7_DEFAULT_SLS;

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find match\n"));

        return (NULL);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i] != ri &&
            ent->entries[i]->isAllowed
#if 1
            && ent->entries[i]->linkSet->isUp
#endif
            )
        {
            return (ent->entries[i]);
        }
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test link set might congest.
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
static ITS_BOOLEAN
DangerOfCongestion(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->congLevel > 0)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
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
MarkAllRoutesAvailable(ITS_POINTER entry,
                       void *in, void *out)
{
    SS7_Destination *dest = (SS7_Destination *)entry;
    ITS_UINT i;

    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->family == FAMILY_ANSI &&
            dest->entries[i]->basic.type == REMOTE_ROUTE &&
            (dest->entries[i]->basic.style == ROUTE_DPC_NI ||
             dest->entries[i]->basic.style == ROUTE_DPC_OPC_NI) &&
            dest->entries[i]->linkSet->adjacent != 0)
        {
            dest->entries[i]->isAllowed = ITS_TRUE;
            dest->entries[i]->isRestricted = ITS_FALSE;
        }

        dest->status = DESTINATION_AVAILABLE;
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
static ITS_BOOLEAN
RemoteSPAccessible(ITS_UINT pc, ITS_OCTET ni)
{
    ROUTE_MatchInfo mi;
    SS7_Destination *ent;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

    if (ROUTE_ParseRouteMatchInfoArgs(&mi, pc,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ni,
                                      ITS_SS7_DEFAULT_LINK_SET,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        MTP3_ERROR(("Can't parse route info\n"));

        return (ITS_FALSE);
    }

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find route\n"));

        return (ITS_FALSE);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i]->linkSet->isUp &&
            ent->entries[i]->isAllowed)
        {
            return (ITS_TRUE);
        }
    }
#if 0
    /* this should be equivalent and is a better test.  However... */
    if (ent->status != DESTINATION_UNAVAILABLE)
    {
        return (ITS_TRUE);
    }
#endif

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test link set might congest.
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
static ITS_BOOLEAN
EmergencyState(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;

    /* 12.2.4 */
    /*
     * the conditions for emergency restart may vary between different
     * applications of the signalling system.  Possibilities include:
     * 1) signalling traffic that may be conveyed over the link set to
     *    be restarted is blocked
     * 2) the remote SP is inaccessible.
     */
    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        return (ITS_FALSE);
    }

    /* we can at least do (2) */
    if (!SPRestarting_ANSI() && !RemoteSPAccessible(ls->adjacent, ls->ni))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
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
TryInhibitLink(SS7_LinkPtr ln)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    ITS_UINT count;

    /* link available */
    if (!ln->isAllowed)
    {
        /* obtain accessibility data for remote SP */

        /* if remote is accessible */
        if (AdjacentAccessible(ln->linkSet))
        {
            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;

                /* mark link inhibited */
                ln->stFlags |= LINK_INHIBITED;
            }
        }
        else
        {
            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_DENIED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_DENIED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;
            }
        }
    }
    else
    {
        /* if alternative link in link set */
        if (AlternateLink(ln->linkSet, ln))
        {
            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;

                /* mark link inhibited */
                ln->stFlags |= LINK_INHIBITED;
            }
        }
        else
        {
            /* while not last destination */
            for (count = 0, tmp = DSMQUEUE_HEAD(ln->linkSet->routes);
                 tmp != NULL && count < DSMQUEUE_COUNT(ln->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(ln->linkSet->routes, tmp) )
            {
                /* select one of concerned destinations */
                memcpy(&ri, tmp->data, sizeof(ri));

                /* if no alternative link set for dest */
                if (!AlternateRoute(ri))
                {
                    /* if inhibit request is local */
                    if (ln->stFlags & LINK_LOCAL_LIR)
                    {
                        TLAC_Main_ANSI(MTP3_STM_TSRC,
                                       STM_TRIGGER_LOCAL_INHIBIT_DENIED,
                                       NULL, 0,
                                       ln->linkSet->linkSet, ln->linkCode);

                        /* cancel local inhibit request */
                        ln->stFlags &= ~LINK_LOCAL_LIR;
                    }
                    else
                    {
                        TLAC_Main_ANSI(MTP3_STM_TSRC,
                                       STM_TRIGGER_REMOTE_INHIBIT_DENIED,
                                       NULL, 0,
                                       ln->linkSet->linkSet, ln->linkCode);

                        /* cancel remote inhibit request */
                        ln->stFlags &= ~LINK_REMOTE_LIR;
                    }

                    return;
                }
            }

            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;

                /* mark link inhibited */
                ln->stFlags |= LINK_INHIBITED;
            }
        }
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
static void
AvailableRoute(SS7_LinkPtr ln,
               SS7_Destination *ent, int whichEntry,
               int firstMatch, int lastMatch)
{
    int i, current;
    ROUTE_Info *ri = ent->entries[whichEntry];
    MTP3_POINT_CODE pc;
    ITS_EVENT ev;
    MTP3_HEADER_ANSI mtp3;

    /* gather PC */
    MTP3_PC_SET_VALUE(pc, ent->entries[whichEntry]->basic.dpc);

    /*
     * NOTE: I reversed the search order (so that if an alternate route
     * is really in use it shows up as the active STP.  This may break
     * other tests (it fixes 9.4.2).  FIXME.
     */
    /* find current entry */
    for (current = -1, i = lastMatch; i >= firstMatch; i--)
    {
        if (ent->entries[i]->flags & ROUTE_STP_IN_USE)
        {
            current = i;

            break;
        }
    }

    MTP3_DEBUG(("######### AvailableRoute: dest %08x pri %d cur %d\n",
                ri->basic.dpc, ri->priority, current));

    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);

    MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                     &mtp3, NULL, 0);

    /* if priority >= that of current route */
    if (current < 0 ||
        ri->priority <= ent->entries[current]->priority)
    {
        /* mark STP in use for destination (cluster) */
        MTP3_ERROR(("ROUTE_STP_IN_USE SET FILE %s LINE %d \n",__FILE__,__LINE__));
        ri->flags |= ROUTE_STP_IN_USE;

        /* prohibit new STP. */
        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TCP,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }
        else
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        /* if STP no longer used for destination (cluster)
         *
         * Watch it here.  This is too much like ITU and not enough
         * like ANSI.  Don't forget that you don't remove STPs for
         * combined linksets (equal priority routes).
         */
        if (current >= 0 && whichEntry != current && 
           ent->entries[current]->priority != ent->entries[whichEntry]->priority)
        {
            /* Mark STP not in use for destination (cluster) */
            ent->entries[current]->flags &= ~ROUTE_STP_IN_USE;

            /* if new route normal */
            if (ri->priority == 0)
            {
                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_FOR_CLUST,
                                   ev.data, ev.len,
                                   ent->entries[current]->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_DEST,
                                   ev.data, ev.len,
                                   ent->entries[current]->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
            else
            {
                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_FOR_CLUST,
                                   ev.data, ev.len,
                                   ent->entries[current]->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_DEST,
                                   ev.data, ev.len,
                                   ent->entries[current]->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
        }

        /* if new route normal route */
        if (ri->priority == 0)
        {
            /* if T11 running */
            if (ri->t11 == TIMER_BAD_SERIAL)
            {
                /* stop T11 */
                TIMERS_CancelSharedTimer(ri->t11);
                ri->t11 = TIMER_BAD_SERIAL;
            }

            /* if not destination (cluster) accessible */
            if (!AlternateRoute(ri) || ent->status == DESTINATION_RESTRICTED)
            {
                /* if link becoming available */
                if (ln && ln->stFlags & LINK_COMING_AVAILABLE)
                {
                    MTP3_DEBUG(("link becoming available\n"));
                    /* if danger of congestion possible in normal link set */
                    if (DangerOfCongestion(ln->linkSet))
                    {
                     MTP3_DEBUG(("Danger of congestion in link becoming available\n"));
                        /* if not destination (cluster) restricted */
                        if (ent->status != DESTINATION_RESTRICTED)
                        {
                            /* mark destination (cluster) restricted */
                            ent->status = DESTINATION_RESTRICTED;

                            /* if cluster */
                            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                            {
                                TSFC_Main_ANSI(MTP3_STM_TSRC,
                                               STM_TRIGGER_CLUST_ACCESS,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }
                            else
                            {
                                TSFC_Main_ANSI(MTP3_STM_TSRC,
                                               STM_TRIGGER_DEST_ACCESS,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }            

                            if (!SPRestarting_ANSI())
                            {
                                /* if cluster */
                                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                                {
                                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                                   SRM_TRIGGER_CLUSTER_RESTRICT,
                                                   ev.data, ev.len,
                                                   ri->linkSet->linkSet,
                                                   ITS_SS7_DEFAULT_LINK_CODE);
                                }
                                else
                                {
                                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                                   SRM_TRIGGER_DEST_RESTRICT,
                                                   ev.data, ev.len,
                                                   ri->linkSet->linkSet,
                                                   ITS_SS7_DEFAULT_LINK_CODE);
                                }
                            }
                        }
                        else
                        {
                            if (ln == NULL || !(ln->stFlags & LINK_COMING_AVAILABLE))
                            {
                                /*
                                 * note: the order is changed here.  There's no point
                                 * in doing TCRC first, as the calls to RTAC and RTRC
                                 * will not have been made.  Since TCRC may REROUTE_END
                                 * before returning, we need to adjust the order.
                                 * therefore, move this.
                                 */
                                RTPC_Main_ANSI(MTP3_STM_TSRC,
                                               SRM_TRIGGER_CONTROLLED_REROUTE,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);

                                RTRC_Main_ANSI(MTP3_STM_TSRC,
                                               SRM_TRIGGER_CONTROLLED_REROUTE,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);

                                /* moved to here */
                                TCRC_Main_ANSI(MTP3_STM_TSRC,
                                               STM_TRIGGER_ROUTE_RESTRICTED,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }
                        }
            
                        return;
                    }
                }
                
                /* mark destination (cluster) accessible */
                ent->status = DESTINATION_AVAILABLE;
                
                MTP3_DEBUG(("ROUTE_CommitDestination RESUME %d \n", __LINE__));
                ROUTE_CommitDestination(ent,ri->basic.dpc, ri->linkSet->ni,FAMILY_ANSI);
                MTP3_DEBUG(("Marking destination DESTINATION_AVAILABLE  & generating RESUME\n"));

                /* if cluster */
                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    TSFC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_CLUST_ACCESS,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    TSFC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_DEST_ACCESS,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                if (!SPRestarting_ANSI())
                {
                    /* if cluster */
                    if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                    {
                        RTAC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CLUSTER_ACCESS,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                    else
                    {
                        RTAC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_DEST_ACCESS,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                }
            }
            else /* there is an alternate route or dest isn't restricted */
            {
                /* if not link becoming available */
                if (ln == NULL || !(ln->stFlags & LINK_COMING_AVAILABLE))
                {
                    MTP3_DEBUG(("AvailableRoute: It's where I wondered it would be.\n"));

                    /*
                     * note: the order is changed here.  There's no point
                     * in doing TCRC first, as the calls to RTAC and RTRC
                     * will not have been made.  Since TCRC may REROUTE_END
                     * before returning, we need to adjust the order.
                     * therefore, move this.
                     */
                    RTPC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    /* moved to here */
                    TCRC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_ROUTE_AVAILABLE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
        }
        else /* this isn't a normal route */
        {
            /* if not destination (cluster) restricted */
            if (ent->status != DESTINATION_RESTRICTED)
            {
                /* mark destination (cluster) restricted */
                ent->status = DESTINATION_RESTRICTED;

                /* if cluster */
                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    TSFC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_CLUST_ACCESS,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    TSFC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_DEST_ACCESS,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                if (!SPRestarting_ANSI())
                {
                    /* if cluster */
                    if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                    {
                        RTRC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CLUSTER_RESTRICT,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                    else
                    {
                        RTRC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_DEST_RESTRICT,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                }
            }
            else
            {
                if (ln == NULL ||
                    !(ln->stFlags & LINK_COMING_AVAILABLE))
                {
                    MTP3_DEBUG(("AvailableRoute: It's where I think it is.\n"));

                    /*
                     * note: the order is changed here.  There's no point
                     * in doing TCRC first, as the calls to RTAC and RTRC
                     * will not have been made.  Since TCRC may REROUTE_END
                     * before returning, we need to adjust the order.
                     * therefore, move this.
                     */
                    RTPC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TCRC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_ROUTE_RESTRICTED,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
        }
    }

    ITS_EVENT_TERM(&ev);
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
RestrictedRoute(SS7_LinkPtr ln,
                SS7_Destination *ent, int whichEntry,
                int firstMatch, int lastMatch)
{
    ROUTE_Info *ri = ent->entries[whichEntry];
    MTP3_POINT_CODE pc;
    int i, current;
    ITS_EVENT ev;
    MTP3_HEADER_ANSI mtp3;

    /* gather PC */
    MTP3_PC_SET_VALUE(pc, ent->entries[whichEntry]->basic.dpc);

    /* find current entry */
    for (current = -1, i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i]->isAllowed)
        {
            current = i;

            break;
        }
    }

    MTP3_DEBUG(("######### RestrictedRoute: dest %08x pri %d cur %d\n",
                ri->basic.dpc, ri->priority, current));

    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);

    MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                     &mtp3, NULL, 0);

    /* if destination (cluster) inaccessible */
    if (!AlternateRoute(ri))
    {
        if (!SPRestarting_ANSI())
        {
            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                TSFC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_CLUST_ACCESS,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_CLUSTER_RESTRICT,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                TSFC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_DEST_ACCESS,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_RESTRICT,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
        }

        /* if not link becoming available */
        if (ln && !(ln->stFlags & LINK_COMING_AVAILABLE))
        {
            TCRC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_ROUTE_RESTRICTED,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
            
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
            
            RTRC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        /* mark destination (cluster) restricted */
        ent->status = DESTINATION_RESTRICTED;

        /* mark STP in use for destination (cluster) */
        MTP3_ERROR(("ROUTE_STP_IN_USE SET FILE %s LINE %d \n",__FILE__,__LINE__));
        ri->flags |= ROUTE_STP_IN_USE;
    }
    else
    {
        /* if not restricted route lower priority than current route */
        if (current >= 0 &&
            !(ri->priority > ent->entries[current]->priority))
        {
            /* if restricted route higher priority than current route */
            if (current >= 0 &&
                ri->priority < ent->entries[current]->priority)
            {
                /* mark STP not in use for destination (cluster) */
                MTP3_ERROR(("UnSetting ROUTE_STP_IN_USE FLAG for ri->flags %d\n",__LINE__)); 
                ent->entries[current]->flags &= ~ROUTE_STP_IN_USE;

                /* if new route normal route */
                if (ri->priority == 0)
                {
                    if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                    {
                        RTAC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_REM_STP_FOR_CLUST,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                    else
                    {
                        RTAC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_REM_STP_DEST,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }

                    /* if T11 running */
                    if (ri->t11 != TIMER_BAD_SERIAL)
                    {
                        /* stop T11 */
                        TIMERS_CancelSharedTimer(ri->t11);
                        ri->t11 = TIMER_BAD_SERIAL;
                    }
                }
                else
                {
                    if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                    {
                        RTRC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_REM_STP_FOR_CLUST,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                    else
                    {
                        RTRC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_REM_STP_DEST,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                }

                /* if not link becoming available */
                if (!(ln->stFlags & LINK_COMING_AVAILABLE))
                {
                    TCRC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_ROUTE_RESTRICTED,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTPC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                /* mark destination (cluster) restricted */
                ent->status = DESTINATION_RESTRICTED;

                /* mark STP in use for destination (cluster) */
        MTP3_ERROR(("ROUTE_STP_IN_USE SET FILE %s LINE %d \n",__FILE__,__LINE__));
                ri->flags |= ROUTE_STP_IN_USE;
            }
            else
            {
                /* if restricted route in use */
                if (ri->isRestricted && ri->flags & ROUTE_STP_IN_USE)
                {
                    /* if equal priority route available (not restricted) */
                    {
                        TCRC_Main_ANSI(MTP3_STM_TSRC,
                                       STM_TRIGGER_ROUTE_RESTRICTED,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RTPC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CONTROLLED_REROUTE,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RTRC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CONTROLLED_REROUTE,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                    /* else */
                    {
                        /* if not destination (cluster) restricted */
                        if (ent->status != DESTINATION_RESTRICTED)
                        {
                            /* mark destination (cluster) restricted */
                            ent->status = DESTINATION_RESTRICTED;

                            if (!SPRestarting_ANSI())
                            {
                                /* if cluster */
                                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                                {
                                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                                   SRM_TRIGGER_CLUSTER_RESTRICT,
                                                   ev.data, ev.len,
                                                   ri->linkSet->linkSet,
                                                   ITS_SS7_DEFAULT_LINK_CODE);
                                }
                                else
                                {
                                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                                   SRM_TRIGGER_DEST_RESTRICT,
                                                   ev.data, ev.len,
                                                   ri->linkSet->linkSet,
                                                   ITS_SS7_DEFAULT_LINK_CODE);
                                }
                            }
                        }

                        /* if equal priority route restricted and not in use */
                        if (ri->isRestricted && !(ri->flags & ROUTE_STP_IN_USE))
                        {
                            /* if not link becoming available */
                            if (!(ln->stFlags & LINK_COMING_AVAILABLE))
                            {
                                TCRC_Main_ANSI(MTP3_STM_TSRC,
                                               STM_TRIGGER_ROUTE_RESTRICTED,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }

                            /* mark destination (cluster) restricted */
                            ent->status = DESTINATION_RESTRICTED;

                            /* mark STP in use for destination (cluster) */
        MTP3_ERROR(("ROUTE_STP_IN_USE SET FILE %s LINE %d \n",__FILE__,__LINE__));
                            ri->flags |= ROUTE_STP_IN_USE;
                        }
                    }
                }
                else
                {
                    /* if current route restricted */
                    if (ri->isRestricted)
                    {
                        /* if not link becoming available */
                        if (!(ln->stFlags & LINK_COMING_AVAILABLE))
                        {
                            TCRC_Main_ANSI(MTP3_STM_TSRC,
                                           STM_TRIGGER_ROUTE_RESTRICTED,
                                           ev.data, ev.len,
                                           ri->linkSet->linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);
                        }

                        /* mark destination (cluster) restricted */
                        ent->status = DESTINATION_RESTRICTED;

                        /* mark STP in use for destination (cluster) */
        MTP3_ERROR(("ROUTE_STP_IN_USE SET FILE %s LINE %d \n",__FILE__,__LINE__));
                        ri->flags |= ROUTE_STP_IN_USE;
                    }
                }
            }
        }
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
static void
UnavailableRoute(ROUTE_Info *ri)
{
    ROUTE_Info *oldri;
    MTP3_POINT_CODE_ANSI pc;
    MTP3_HEADER_ANSI mtp3;
    ITS_EVENT ev;
    MTP3_TimerContext tc;
    SS7_Destination *ent;
    ITS_BOOLEAN firstLoop = ITS_TRUE;

    MTP3_DEBUG(("UnavailableRoute: Consider route %08x pri %d inUse %d\n",
                ri->basic.dpc, ri->priority, ri->flags & ROUTE_STP_IN_USE));
/********NO PAUSE ISSUE***********/
#if 0
    if (!(ri->flags & ROUTE_STP_IN_USE))
    {
        MTP3_DEBUG(("UnavailableRoute: STP_IN_USE not set: %08x\n",
                    ri->basic.dpc));
        return;
    }
#endif
    ent = ri->dest;

    MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC(mtp3.label, pc);

    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
    
    MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                     &mtp3, NULL, 0);

    /* if alternative link set */
    if (AlternateRoute(ri))
    {
        MTP3_DEBUG(("UnavailableRoute: have alternate route: %08x\n",
                    ri->basic.dpc));

        oldri = ri;
        ri = GetAlternateRoute(ri);

        MTP3_DEBUG(("UnavailableRoute: new STP? pc %08x ripri %d oldripri %d\n",
                    ri->basic.dpc, ri->priority, oldri->priority));
        MTP3_DEBUG(("UnavailableRoute: adjSTP? %d riSTP %d oldriSTP %d\n",
                    ri->linkSet->adjSTP, ri->flags & ROUTE_STP_IN_USE,
                    oldri->flags & ROUTE_STP_IN_USE));

        /* if new STP to be used for dest */
        if (ri && ri->linkSet->adjSTP &&
            ri->priority > oldri->priority &&
            !(ri->flags & ROUTE_STP_IN_USE))
        {
            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                RTPC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_SEND_TCP,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTPC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            /* mark STP in use for destination (cluster) */
        MTP3_ERROR(("ROUTE_STP_IN_USE SET FILE %s LINE %d \n",__FILE__,__LINE__));
            ri->flags |= ROUTE_STP_IN_USE;

            /* if destination (cluster) restricted */
            if (ent->status == DESTINATION_RESTRICTED)
            {
                MTP3_DEBUG(("UnavailableRoute: destination restricted: %08x\n",
                            ri->basic.dpc));

                return;
            }

            /* if new STP lower priority */
            if (ri->priority > oldri->priority)
            {
                if (SPRestarting_ANSI())
                {
                    /* mark destination (cluster) restricted */
                    ent->status = DESTINATION_RESTRICTED;

                    MTP3_DEBUG(("UnavailableRoute: mark destination restricted: %08x\n",
                                ri->basic.dpc));

                    return;
                }
                else
                {
                    /* start T11 */
                    tc.timerId = MTP3_T11;
                    tc.data.routeInfo.pointCode = MTP3_PC_GET_VALUE(pc);
                    tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
                    tc.data.routeInfo.sio = ri->linkSet->ni;

                    ri->t11 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t11 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    return;
                }
            }
            else
            {
                /* if new route restricted */
                if (ri->isRestricted)
                {
                    if (SPRestarting_ANSI())
                    {
                        /* mark destination (cluster) restricted */
                        ent->status = DESTINATION_RESTRICTED;

                        MTP3_DEBUG(("UnavailableRoute: mark destination restricted2: %08x\n",
                                    ri->basic.dpc));

                        return;
                    }
                    else
                    {
                        /* if cluster */
                        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                        {
                            RTRC_Main_ANSI(MTP3_STM_TSRC,
                                           SRM_TRIGGER_CLUSTER_RESTRICT,
                                           ev.data, ev.len,
                                           ri->linkSet->linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);
                        }
                        else
                        {
                            RTRC_Main_ANSI(MTP3_STM_TSRC,
                                           SRM_TRIGGER_DEST_RESTRICT,
                                           ev.data, ev.len,
                                           ri->linkSet->linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);
                        }

                        /* mark destination (cluster) restricted */
                        ent->status = DESTINATION_RESTRICTED;
                    }
                }
                else
                {
                    MTP3_DEBUG(("UnavailableRoute: route not restricted: %08x\n",
                                ri->basic.dpc));

                    return;
                }
            }
        }
        else
        {
            MTP3_DEBUG(("UnavailableRoute: new STP not to be used: %08x\n",
                        ri->basic.dpc));

            return;
        }
    }
    else /* (no alternative link set) */
    {
        ITS_UINT i;

        MTP3_DEBUG(("UnavailableRoute: no alternate link set: %08x\n",
                    ri->basic.dpc));

        /* mark destination (cluster) inaccessible */
        ent->status = DESTINATION_UNAVAILABLE;
            /***************************    ROUTE COMMIT PAUSE          **************************/
            /*ROUTE_CommitDestination(SS7_Destination *dest,ITS_UINT dpc,ITS_OCTET ni,SS7_Family family)*/
            MTP3_DEBUG(("UnavailableRoute: ROUTE_CommitDestination PAUSE\n"));
            ROUTE_CommitDestination(ent,ri->basic.dpc, ri->linkSet->ni,FAMILY_ANSI);
            /***************************    ROUTE COMMIT PAUSE         **************************/

        /*
         * we should do this only once, as we don't need to uninhibit
         * for every destination.
         */
        if (firstLoop)
        {
            /* if any links inhibited */
            /* loop through links in link set.  If any marked
             * inhibited, send this trigger */
            for (i = 0; i < ri->linkSet->numLinks; i++)
            {
                if (ri->linkSet->links[i]->stFlags & LINK_INHIBITED)
                {
                    TLAC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_UNINHIBITING_LINK,
                                   NULL, 0,
                                   ri->linkSet->linkSet,
                                   ri->linkSet->links[i]->linkCode);
                }
            }

            firstLoop = ITS_FALSE;
        }

        if (!SPRestarting_ANSI())
        {
            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                RTPC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_CLUSTER_INACCESS,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTPC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_INACCESS,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
        }

        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            TSFC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_CLUST_INACCESS,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }
        else
        {
            TSFC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_INACCESS,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        /* stop T11 */
        if (ri->t11 != TIMER_BAD_SERIAL)
        {
            TIMERS_CancelSharedTimer(ri->t11);
            ri->t11 = TIMER_BAD_SERIAL;
        }
    }

    ITS_EVENT_TERM(&ev);
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
DeactivateLinkSet(SS7_LinkSetPtr ls)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    ITS_UINT count;
   /* ######Changes for mantis 15939############ Start*/
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri_ptr ;
    SS7_Destination *ent;
   /* ######Changes for mantis 15939############ End*/
    
    MTP3_DEBUG(("DeactivateLinkSet: %d\n", ls->linkSet));

    /* while affected destinations or clusters */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        /* select an affected destination or cluster */
        memcpy(&ri, tmp->data, sizeof(ri));
        /* ######Changes for mantis 15939############ Start*/
        rinfo.basic = ri->basic;
        rinfo.linkSet = ri->linkSet->linkSet;
        rinfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
        rinfo.priority = ITS_SS7_DEFAULT_PRI;
        rinfo.sls = ITS_SS7_DEFAULT_SLS;
        if ((ent = ROUTE_FindBestMatch(&rinfo,&whichEntry,&firstMatch,&lastMatch,&whichLinkCode,ITS_FALSE)) == NULL)
          {
           MTP3_ERROR(("DeactivateLinkSet :Can't find match\n"));
           //return (ITS_FALSE);
          }
        /* ######Changes for mantis 15939############ End*/
          ri_ptr = ent->entries[whichEntry];
        if(ri->basic.style == ROUTE_DPC_NI)
        {
          MTP3_DEBUG(("\n Changed for sending Extra LFU ROUTE_DPC_NI\n"));
          UnavailableRoute(ri_ptr);
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
UpdateInaccessibleRestricted(SS7_LinkSetPtr ls)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    MTP3_POINT_CODE_ANSI pc;
    MTP3_HEADER_ANSI mtp3;
    ITS_EVENT ev;
    ITS_UINT count;

    /* while any inaccessible destinations or clusters */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        memcpy(&ri, tmp->data, sizeof(ri));

        if (!(ri->flags & ROUTE_TRANSFER_PROHIBITED))
        {
            continue;
        }

        MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

        MTP3_HDR_SET_SIO(mtp3, ls->ni);
        MTP3_RL_SET_DPC(mtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TCP,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_SET);
        }
        else
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_SET);
        }

        ITS_EVENT_TERM(&ev);
    }

    /* while any restricted destinations or clusters */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        memcpy(&ri, tmp->data, sizeof(ri));

        if (!(ri->isRestricted))
        {
            continue;
        }

        MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

        MTP3_HDR_SET_SIO(mtp3, ls->ni);
        MTP3_RL_SET_DPC(mtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            RTRC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TCR,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_SET);
        }
        else
        {
            RTRC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TRANSFER_RESTRICT,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_SET);
        }

        ITS_EVENT_TERM(&ev);
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
UpdateAdjacent(SS7_LinkSetPtr ls)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    MTP3_POINT_CODE_ANSI pc;
    MTP3_HEADER_ANSI mtp3;
    ITS_EVENT ev;
    ITS_UINT count;

    /* while any destination or cluster normally routed via adjacent SP */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        memcpy(&ri, tmp->data, sizeof(ri));

        if (ri->priority != 0)
        {
            continue;
        }

        MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

        MTP3_HDR_SET_SIO(mtp3, ls->ni);
        MTP3_RL_SET_DPC(mtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &mtp3, NULL, 0);

        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TCP,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_SET);
        }
        else
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_SET);
        }

        ITS_EVENT_TERM(&ev);
    }

    UpdateInaccessibleRestricted(ls);
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
StartTrafficRestart(ROUTE_Info *ri)
{
    MTP3_TimerContext tc;
    MTP3_HEADER_ANSI mtp3;
    SNMM_MESSAGE snmm;
    ITS_EVENT ev;
    DSMQUEUE_Entry *tmp;
    MTP3_POINT_CODE pc;
    ITS_UINT count;

    /* if T29 or T30 running */
    if (ri->t29 != TIMER_BAD_SERIAL || ri->t30 != TIMER_BAD_SERIAL)
    {
        return;
    }

    if (STPFunction_ANSI())
    {
        /* Build SNMM traffic restart waiting */
        MTP3_HDR_SET_SIO(mtp3, MTP3_SIO_SNMM | ri->linkSet->ni | MTP3_MPC_PRI_3);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, ri->linkSet->lpc);

        SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_TRM_ANSI);
        SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_TRW_ANSI);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        SNMM_Encode_ANSI(&ev, &mtp3, &snmm);


        HMRT_Main_ANSI(MTP3_STM_TSRC,
                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        /* start T30 */
        tc.timerId = MTP3_T30;
        tc.data.routeInfo.pointCode = ri->basic.dpc;
        tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
        tc.data.routeInfo.sio = ri->linkSet->ni;

        ri->t30 =
            TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                               __ansi_t30 * USEC_PER_MILLISEC,
                               &tc, sizeof(MTP3_TimerContext));

        /*
         * for each destination or cluster currently routed via originator of
         * TRW, TRA (HERE)
         */
        for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes); 
             tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
             count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
        {
            memcpy(&ri, tmp->data, sizeof(ri));

            MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
            MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &mtp3, NULL, 0);
            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                RTPC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_SEND_TCP,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTPC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            ITS_EVENT_TERM(&ev);
        }

        if (ri->basic.dpc == ri->linkSet->adjacent)
        {
            UpdateInaccessibleRestricted(ri->linkSet);
        }
    }
    else
    {
        /* Build SNMM traffic restart allowed */
        MTP3_HDR_SET_SIO(mtp3, MTP3_SIO_SNMM | ri->linkSet->ni | MTP3_MPC_PRI_3);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, ri->linkSet->lpc);

        SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_TRM_ANSI);
        SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_TRA_ANSI);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        SNMM_Encode_ANSI(&ev, &mtp3, &snmm);

        HMRT_Main_ANSI(MTP3_STM_TSRC,
                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        /* start T29 */
        tc.timerId = MTP3_T29;
        tc.data.routeInfo.pointCode = ri->basic.dpc;
        tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
        tc.data.routeInfo.sio = ri->linkSet->ni;

        ri->t29 =
            TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                               __ansi_t29 * USEC_PER_MILLISEC,
                               &tc, sizeof(MTP3_TimerContext));
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
StatusIterate(ITS_POINTER entry,
              void *in, void *out)
{
    SS7_Destination *dest = (SS7_Destination *)entry;
    ITS_EVENT ev;
    MTP3_HEADER_ANSI omtp3;
    MTP3_POINT_CODE_ANSI pc;
    ITS_UINT dpc;

    if (dest->family != FAMILY_ANSI ||
        dest->numEntries == 0 ||
        dest->entries[0]->basic.type != REMOTE_ROUTE ||
        (dest->entries[0]->basic.style != ROUTE_DPC_NI &&
         dest->entries[0]->basic.style != ROUTE_DPC_OPC_NI))
    {
        /* skip it */
        return (ITS_SUCCESS);
    }

    dpc = dest->entries[0]->basic.dpc;
    MTP3_PC_SET_VALUE(pc, dpc);

    /* destination or cluster inaccessible */
    if (dest->status == DESTINATION_UNAVAILABLE)
    {
        /* The DPC needs to have NI */
        MTP3_HDR_SET_SIO(omtp3, dest->entries[0]->basic.criteria.sio &
                         MTP3_NIC_MASK);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, dpc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &omtp3, NULL, 0);

        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_CLUSTER_INACCESS,
                           ev.data, ev.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            TSFC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_CLUST_INACCESS,
                           ev.data, ev.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }
        else
        {
            RTPC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_DEST_INACCESS,
                           ev.data, ev.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            TSFC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_INACCESS,
                           ev.data, ev.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        ITS_EVENT_TERM(&ev);
    }
    /* destination or cluster restricted */
    else if (dest->status == DESTINATION_RESTRICTED)
    {
        MTP3_HDR_SET_SIO(omtp3, dest->entries[0]->basic.criteria.sio &
                                MTP3_NIC_MASK);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, dpc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &omtp3, NULL, 0);

        /* if cluster */
        if (MTP3_PC_IS_CLUSTER_ANSI(pc))
        {
            RTRC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_CLUSTER_RESTRICT,
                           ev.data, ev.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }
        else
        {
            RTRC_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_DEST_RESTRICT,
                           ev.data, ev.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        ITS_EVENT_TERM(&ev);
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
TrafficRestart(ROUTE_Info *ri)
{
    ITS_UINT i;
    ITS_EVENT ev;
    MTP3_HEADER_ANSI mtp3;
    MTP3_POINT_CODE pc;
    DSMQUEUE_Entry *tmp;
    ITS_UINT count ,RES_FLG =0;

    /* cancel adjacent SP restarting */
    ri->linkSet->adjRestart = ITS_FALSE;

    MTP3_PC_SET_VALUE(pc, ri->linkSet->adjacent);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC(mtp3.label, pc);

    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

    MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                     &mtp3, NULL, 0);

    /* for each link of the linkset */
    for (i = 0; i < ri->linkSet->numLinks; i++)
    {
        TLAC_Main_ANSI(MTP3_STM_TSRC,
                       STM_TRIGGER_ADJACENT_SP_RESTARTED,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ri->linkSet->links[i]->linkCode);
         if(ri->linkSet->links[i]->testPassed == ITS_TRUE)
           {
            RES_FLG = ITS_TRUE;
           }

    }
    if(RES_FLG == ITS_TRUE)
      {
    MTP3_DEBUG((" Generate Resume from TrafficRestart %d  \n",__LINE__));
    TSFC_Main_ANSI(MTP3_STM_TSRC,
                   STM_TRIGGER_DEST_ACCESS,
                   ev.data, ev.len,
                   ri->linkSet->linkSet,
                   ITS_SS7_DEFAULT_LINK_CODE);
        RES_FLG = ITS_FALSE ;
      }

    /* if danger of congestion possible in normal link set */
    if (DangerOfCongestion(ri->linkSet))
    {
        /* mark destination restricted */
        ri->dest->status = DESTINATION_RESTRICTED;

        RTRC_Main_ANSI(MTP3_STM_TSRC,
                       SRM_TRIGGER_DEST_RESTRICT,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);
    }
    else
    {
        RTAC_Main_ANSI(MTP3_STM_TSRC,
                       SRM_TRIGGER_DEST_ACCESS,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);
    }

    ITS_EVENT_TERM(&ev);

    /* for each destination (cluster) */
    for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes);
         tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
    {
        ROUTE_InfoPtr rt;

        memcpy(&rt, tmp->data, sizeof(ri));

        /* Mark the destination status as DESTINATION_AVAILABLE since
         * this status needs to be updated if RESUME needs to be sent
         * for all reachable destinations
         */
        if (rt->isAllowed && !rt->isRestricted)
        {
            SS7_Destination* dest = NULL;

            dest = ROUTE_FindDestination(rt->basic.dpc,
                                         rt->basic.criteria.sio,
                                         FAMILY_ANSI);

            if (dest)
            {
                dest->status = DESTINATION_AVAILABLE;
            }
            else
            {
             MTP3_ERROR(("Destination Available Ponter is NULL\n"));
            }
            /***************************    ROUTE COMMIT RESUME          **************************/
            /*ROUTE_CommitDestination(SS7_Destination *dest,ITS_UINT dpc,ITS_OCTET ni,SS7_Family family)*/
            MTP3_DEBUG(("TrafficRestart: ROUTE_CommitDestination RESUME\n"));
            ROUTE_CommitDestination(dest,rt->basic.dpc, ri->linkSet->ni,FAMILY_ANSI);
            /***************************    ROUTE COMMIT RESUME          **************************/
        }

        /* if STP no longer used for destination (cluster) */
        if (!(rt->flags & ROUTE_STP_IN_USE))
        {
            MTP3_PC_SET_VALUE(pc, rt->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, rt->linkSet->ni);
            MTP3_RL_SET_DPC(mtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &mtp3, NULL, 0);

            if (rt->priority == 0)
            {
                /* if cluster */
                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_FOR_CLUST,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_DEST,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
            else
            {
                /* if cluster */
                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_FOR_CLUST,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_DEST,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }

            ITS_EVENT_TERM(&ev);
        }
    }

    /* while any destination or cluster becoming available */
    for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
    {
        ROUTE_Info *ri;
        SS7_LinkSetPtr ls;
        SS7_Destination *dest;

        memcpy(&ri, tmp->data, sizeof(ri));
        ls = ri->linkSet;

        dest = ROUTE_FindDestination(ri->basic.dpc,
                                     ri->basic.criteria.sio,
                                     FAMILY_ANSI);

        if (dest && dest->status == DESTINATION_AVAILABLE)
        {
            /* if adjacent */
            if (ri->basic.dpc == ls->adjacent)
            {
                UpdateAdjacent(ls);
            }

            MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, ls->ni);
            MTP3_RL_SET_DPC(mtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &mtp3, NULL, 0);

            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                /* if danger of congestion possible in normal link set */
                if (ri->priority == 0 &&
                    DangerOfCongestion(ri->linkSet))
                {
                    ri->dest->status = DESTINATION_RESTRICTED;

                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CLUSTER_RESTRICT,
                                   ev.data, ev.len,
                                   ls->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CLUSTER_ACCESS,
                                   ev.data, ev.len,
                                   ls->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                TSFC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_CLUST_ACCESS,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                /* if danger of congestion possible in normal link set */
                if (ri->priority == 0 &&
                    DangerOfCongestion(ri->linkSet))
                {
                    ri->dest->status = DESTINATION_RESTRICTED;

                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_DEST_RESTRICT,
                                   ev.data, ev.len,
                                   ls->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
                else
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_DEST_ACCESS,
                                   ev.data, ev.len,
                                   ls->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                if (ri->basic.dpc != ls->adjacent)
                {
                    TSFC_Main_ANSI(MTP3_STM_TSRC,
                                   STM_TRIGGER_DEST_ACCESS,
                                   ev.data, ev.len,
                                   ls->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

            }

            ITS_EVENT_TERM(&ev);
        }
    }

    /* while any prohibited destination or cluster becoming restricted */
    for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
    {
        ROUTE_Info *ri;
        SS7_LinkSetPtr ls;
        SS7_Destination *dest;

        memcpy(&ri, tmp->data, sizeof(ri));
        ls = ri->linkSet;

        dest = ROUTE_FindDestination(ri->basic.dpc,
                                     ri->basic.criteria.sio,
                                     FAMILY_ANSI);

        if (dest && dest->status == DESTINATION_RESTRICTED)
        {
            /* if adjacent */
            if (ri->basic.dpc == ls->adjacent)
            {
                UpdateAdjacent(ls);
            }

            MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, ls->ni);
            MTP3_RL_SET_DPC(mtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &mtp3, NULL, 0);

            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_CLUSTER_RESTRICT,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TSFC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_CLUST_ACCESS,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_RESTRICT,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TSFC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_DEST_ACCESS,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            ITS_EVENT_TERM(&ev);
        }
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
TSRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1], omtp3;
    MTP3_TimerContext tc;
    MTP3_POINT_CODE dpc;
    ITS_UINT pc;
    ITS_OCTET ni, nls, nlc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri = NULL;
    ITS_UINT i, j, count;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    SNMM_MESSAGE osnmm;
    ITS_EVENT ev;
    ITS_BOOLEAN allowed;
    DSMQUEUE_Entry *tmp;
    int idx;
    ITS_BOOLEAN isUp = ITS_FALSE;
    ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TSRC, src, trigger, sif, len,
                          linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    /* sometimes wants linkSet,linkCode, sometimes wants point code for route?*/
    switch (trigger)
    {
    case STM_TRIGGER_RESTART_END:               /* from TPRC */
        /*
         * Action: clear SP restarting.  Not necessary, TPRC does
         * this.
         */

        /* one message for each adjacent SP */
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (i = 0; i < MAX_LINKSETS; i++)
         {
          for(j = 0;j < MAX_LINKS_PER_LINKSET ;j++)
          {
            if(linkTransportMapDB[i][j] >0) 
             {  
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",i,j,linkTransportMapDB[i][j]));
               if( i > 0 && i < 252)
               {
                lscount++;
                linkset[cnt++]=i;
                MTP3_ERROR((" linkset = %d\n",i));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));
        for (i = 0; i < (lscount); i++)
        {
            ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[i]);
            //ls = LINKSET_FindLinkSet((ITS_OCTET)i);

            if (ls && ls->adjacent != 0)
            {
                /* Build SNMM traffic restart allowed */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(osnmm, SNMM_HC0_TRM_ANSI);
                SNMM_HC1_SET_ANSI(osnmm, SNMM_HC1_TRA_ANSI);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &osnmm);


                HMRT_Main_ANSI(MTP3_STM_TSRC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
        }
        SendingStatusSet_ANSI(ITS_FALSE);

        break;

    case STM_TRIGGER_RESTART_BEGIN:             /* from TPRC */

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_RESTART);
        if (SPRestarting_ANSI())
        {
            /*
             * Action: mark SP restarting.  Not necessary, TPRC does
             * this.
             */

            /* mark all routes available */
            DSM_TableIterate(DSM_Mtp3FtGroupId,
                             DSM_TABLE_DESTINATIONS,
                             NULL, NULL, MarkAllRoutesAvailable);


       // MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (i = 0; i < MAX_LINKSETS; i++)
         {
          for(j = 0;j < MAX_LINKS_PER_LINKSET ;j++)
          {
            if(linkTransportMapDB[i][j] >0) 
             {  
        //       MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",i,j,linkTransportMapDB[i][j]));
               if( i > 0 && i < 252)
               {
                lscount++;
                linkset[cnt++]=i;
                MTP3_ERROR((" linkset = %d\n",i));
                break;
               }
             }
          }
         }
            /* cancel all inhibited links and inhibit requests */
            //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
         //  MTP3_ERROR((" Total Linkset %d found\n", lscount));
            for (i = 0; i < (lscount); i++)
            {
                ls = LINKSET_FindLinkSet((ITS_OCTET)i);

                if (ls && ls->adjacent != 0)
                {
                    for (j = 0; j < ls->numLinks; j++)
                    {
                        SS7_LinkPtr ln = ls->links[j];

                        ln->stFlags &= ~(LINK_INHIBITED|
                                         LINK_LOCAL_LIR|
                                         LINK_REMOTE_LIR);
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_ACCESSIBILITY_REQUEST:     /* from RSRT, TRCC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /*
         * obtain accessibility data for concerned destination
         *
         * Do I have a route to this destination? Look at
         * all the ROUTE_Info records and determine if there is
         * at least one allowed route.
         */
        allowed = ITS_FALSE;
        for (idx = firstMatch; idx <= lastMatch; idx++)
        {
            if (ent->entries[idx]->isAllowed)
            {
                allowed = ITS_TRUE;

                break;
            }
        }

        if (src == MTP3_SRM_RSRT)
        {
            /* NOTE: the status is being sent via the link code arg */
            RSRT_Main_ANSI(MTP3_STM_TSRC,
                           SRM_TRIGGER_ACCESSIBILITY_DATA,
                           sif, len,
                           linkSet, (ITS_OCTET)allowed);
        }
        else if (src == MTP3_STM_TRCC)
        {
            /* NOTE: the status is being sent via the link code arg */
            TRCC_Main_ANSI(MTP3_STM_TRCC,
                           STM_TRIGGER_ACCESSIBILITY_DATA,
                           sif, len,
                           linkSet, (ITS_OCTET)allowed);
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_REQ:       /* from TCOC, TCBC, TFRC, TCRC, LSDA */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni,
#if 1
    /* THIS IS A LARGE CHANGE.  IT PROBABLY BREAKS THINGS. */
                                                 linkSet, linkCode,
#else
                                                 ITS_SS7_DEFAULT_LINK_SET,
                                                 ITS_SS7_DEFAULT_LINK_CODE,
#endif
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Status not maintained for NI:PC %02x:%08x\n",
                        ni, pc));

            return ITS_ENOTFOUND;
        }

        FindAlternateRoute(ent, mtp3,
                           whichEntry, firstMatch, lastMatch,
                           linkSet, linkCode,
                           &nls, &nlc,
                           &ev);
				MTP3_ERROR(("\n linkSet:linkCode %d:%d nls:nlc %d:%d\n",linkSet,linkCode,nls,nlc));

        if (src == MTP3_STM_TCOC)
        {
            TCOC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_STM_TCBC)
        {
            TCBC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_STM_TFRC)
        {
            TFRC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_STM_TCRC)
        {
            TCRC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_SLM_LSDA)
        {
            LSDA_Main_ANSI(MTP3_STM_TSRC,
                           SLM_TRIGGER_ALTERNATE_ROUTING_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }

        ITS_EVENT_TERM(&ev);
        break;

    case STM_TRIGGER_CHANGEOVER_NOT_REQD:        /* from TCOC */
        /* nothing needed */
        break;

    case STM_TRIGGER_CHANGEOVER_EXECUTED:       /* from TCOC */
        /* mark changeover completed for new link */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }
        //ITS_C_ASSERT(ln != NULL);

        ln->stFlags |= LINK_CHANGEOVER_COMPLETE;
        /* Increament the peg for ChangeOver */
        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEOVER);

        /* if signalling links loaded */
        if (ln->isUp && ln->isAllowed && ln->testPassed)
        {
            LSAC_Main_ANSI(MTP3_STM_TSRC,
                           SLM_TRIGGER_LINK_LOADED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else
        {
            LSAC_Main_ANSI(MTP3_STM_TSRC,
                           SLM_TRIGGER_LINK_DELOADED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_PROCEDURE_TERMINATED:      /* from TCBC, TFRC, TCRC */
        /* cancel changeover completed */
        if (src == MTP3_STM_TCBC || src == MTP3_STM_TCOC)
        {
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
               MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));
               return (ITS_EINVALIDARGS);
            }
        //    ITS_C_ASSERT(ln != NULL);

            ln->stFlags &= ~LINK_CHANGEOVER_COMPLETE;

            /* if signalling links loaded */
            if (ln->isUp && ln->isAllowed && ln->testPassed)
            {
                LSAC_Main_ANSI(MTP3_STM_TSRC,
                               SLM_TRIGGER_LINK_LOADED,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSAC_Main_ANSI(MTP3_STM_TSRC,
                               SLM_TRIGGER_LINK_DELOADED,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        else /* TFRC or TCRC */
        {
            ls = LINKSET_FindLinkSet(linkSet);

            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                /* if signalling links loaded */
                if (ln->isUp && ln->isAllowed && ln->testPassed)
                {
                    LSAC_Main_ANSI(MTP3_STM_TSRC,
                                   SLM_TRIGGER_LINK_LOADED,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    LSAC_Main_ANSI(MTP3_STM_TSRC,
                                   SLM_TRIGGER_LINK_DELOADED,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
            }
        }
        break;

    case STM_TRIGGER_ROUTE_AVAILABLE:           /* from RTAC */
    case STM_TRIGGER_TCA:                       /* from RTAC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, /* linkSet; FIXME:
                                                 linkSet; default???
                                                 all we need to know here
                                                 is if the status of this
                                                 route is maintained.
                                                 Do we need to specify the link
                                                 we got the message from??? */
                                                 ITS_SS7_DEFAULT_LINK_SET,
                                                 ITS_SS7_DEFAULT_LINK_CODE,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        /* if route in use */
        if (ri->flags & ROUTE_STP_IN_USE)
        {
            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: STP in use\n"));

            /* if not route already marked available */
            if (!ri->isAllowed)
            {
                MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: route not allowed\n"));

                /* if any links in route available */
                if (LinkSetAvailable(ri->linkSet))
                {
                    MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: link set available\n"));

                    if (SPRestarting_ANSI())
                    {
                        /* mark route available */
                        ri->isAllowed = ITS_TRUE;
                        ri->isRestricted = ITS_FALSE;

                        AvailableRoute(NULL,
                                       ent, whichEntry,
                                       firstMatch, lastMatch);
                    }
                    else
                    {
                        MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: not SP restarting\n"));

                        /* if not adjacent SP accessible */
                        if (!AdjacentAccessible(ri->linkSet))
                        {
                            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: available route\n"));

                            /* mark route available */
                            ri->isAllowed = ITS_TRUE;
                            ri->isRestricted = ITS_FALSE;

                            AvailableRoute(NULL,
                                           ent, whichEntry,
                                           firstMatch, lastMatch);
                        }
                        else
                        {
                            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: not available route\n"));

                            /* mark route available */
                            ri->isAllowed = ITS_TRUE;
                            ri->isRestricted = ITS_FALSE;

                            UpdateAdjacent(ri->linkSet);

                            AvailableRoute(NULL,
                                           ent, whichEntry,
                                           firstMatch, lastMatch);
                        }
                    }
                }
            }
        }
        else
        {
            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: STP NOT in use\n"));
        }
        break;

    case STM_TRIGGER_LOCAL_INHIBIT_REQUESTED:   /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark local inhibit request */
        ln->stFlags |= LINK_LOCAL_LIR;

        TryInhibitLink(ln);
        break;

    case STM_TRIGGER_REMOTE_INHIBIT_REQUESTED:  /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark remote inhibit request */
        ln->stFlags |= LINK_REMOTE_LIR;

        TryInhibitLink(ln);
        break;

    case STM_TRIGGER_LINK_INHIBITED:            /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark link inhibited */
        ln->stFlags |= LINK_INHIBITED;
        break;

    case STM_TRIGGER_CANCEL_LINK_INHIBITED:     /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {

            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* cancel link inhibited */
        ln->stFlags &= ~LINK_INHIBITED;
        break;

    case STM_TRIGGER_UNINHIBIT_REQUEST:         /* from TLAC */
        /* obtain accessibility information for remote */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_ERROR(("Link available for no link set\n"));

            return (ITS_SUCCESS);
        }

        /* if SP accessible */
        if (AdjacentAccessible(ls))
        {
            TLAC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_UNINHIBIT_POSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else
        {
            TLAC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_LINK_UNAVAILABLE:          /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark link unavailable */
        LINK_SetLinkStatus(ln, ITS_FALSE);
        
        /*
         * NOTE: This may cause the linkSet to transition to !isUp.
         * See STM_TRIGGER_LINK_AVAILABLE.
         */
        LINK_SetLinkState(ln, ITS_FALSE);

         /* get new linkSet state */
        if (LINKSET_GetLinkSetState(ln->linkSet, &isUp) != ITS_SUCCESS)
            MTP3_ERROR(("Can't find link set %d\n", ln->linkSet->linkSet));

         /* Increament the counter for Link Failure */
        if (!isUp) 
            PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_SLS_UNAVAILABLE);

        /* if any traffic on link */
        {
            /* if emergency */
            if (EmergencyState(linkSet, linkCode))
            {
                LLSC_Main_ANSI(MTP3_STM_TSRC,
                               SLM_TRIGGER_EMERGENCY,
                               NULL, 0,
                               linkSet, linkCode);
            }

            /* if not any alternative link in link set */
            if (!AlternateLink(ln->linkSet, ln))
            {
                DeactivateLinkSet(ln->linkSet);
            }
        }
        break;

    case STM_TRIGGER_TCP:                       /* from RTPC */
    case STM_TRIGGER_ROUTE_UNAVAILABLE:         /* from RTPC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        /* if route used */
        if (ri->flags & ROUTE_STP_IN_USE)
        {
            MTP3_DEBUG(("TSRC_Main: STP in use.\n"));

            /* mark route unavailable */
            ri->isAllowed = ITS_FALSE;

            /* All of these want destination */
            if (trigger == STM_TRIGGER_TCP)
            {
                RSRT_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_TCP_RCVD,
                               sif, len,
                               linkSet, linkCode);
            }

            /* FIXME: the difference, please: if route currently in use */
            if (ri->flags & ROUTE_STP_IN_USE)
            {
                /*
                 * note: the order is changed here.  There's no point
                 * in doing TFRC first, as the calls to RTAC and RTRC
                 * will not have been made since TFRC is synchronous.
                 * therefore, move this.
                 */
                RTAC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_FORCED_REROUTE,
                               sif, len,
                               linkSet, linkCode);

                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_FORCED_REROUTE,
                               sif, len,
                               linkSet, linkCode);

                /* moved to here */
                TFRC_Main_ANSI(MTP3_STM_TSRC,
                               STM_TRIGGER_ROUTE_UNAVAILABLE,
                               sif, len,
                               linkSet, linkCode);

                /* FIXME: if option */
                if (ITS_FALSE)
                {
                    RTAC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   sif, len,
                                   linkSet, linkCode);

                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   sif, len,
                                   linkSet, linkCode);
                }
            }

            if (ri->basic.dpc == ri->linkSet->adjacent)
            {
                DeactivateLinkSet(ri->linkSet);
            }
            else
            {
								MTP3_ERROR(("ri->basic.dpc = %d ri->linkSet->adjacent %d ",ri->basic.dpc ,ri->linkSet->adjacent));
                UnavailableRoute(ri);
            }
        }
        else
        {
            MTP3_DEBUG(("TSRC_Main: STP NOT in use.\n"));
        }
        break;

    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);

        if (ln == NULL)
        {
            MTP3_ERROR(("Cant find link\n"));

            return (ITS_EINVALIDARGS);
        }

        if (!SendingStatus_ANSI())
        {
            /* mark link available */
            /*ln->isAllowed = ITS_TRUE;*/
            LINK_SetLinkStatus(ln, ITS_TRUE);

            /* if not emergency */
            if (!EmergencyState(linkSet, linkCode))
            {
                LLSC_Main_ANSI(MTP3_STM_TSRC,
                               SLM_TRIGGER_EMERGENCY_CEASES,
                               NULL, 0,
                               linkSet, linkCode);
            }

            /* if no other links available in link set */
            if (!AlternateLink(ln->linkSet, ln))
            {
                /* if not adjacent SP inaccessible */
                if (AdjacentAccessible(ln->linkSet))
                {
                    MTP3_DEBUG(("TSRC_Main: adjacent not accessible %d\n", ln->linkCode));

                    /* FIXME: Network option:  Start route set test: RSRT */

                    /* mark link becoming available */
                    ln->stFlags |= LINK_COMING_AVAILABLE;

                    /*
                     * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                     * and isAllowed, but until this function call, the
                     * linkSet is not up!
                     */
                    LINK_SetLinkState(ln, ITS_TRUE);

                    /* for each destination (cluster) for which link set may be used */
                    for (count = 0, tmp = DSMQUEUE_HEAD(ln->linkSet->routes);
                         tmp != NULL && count < DSMQUEUE_COUNT(ln->linkSet->routes);
                         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
                    {
                        /* select one of concerned destinations */
                        memcpy(&ri, tmp->data, sizeof(ri));

                        rinfo.basic = ri->basic;
                        rinfo.linkSet = ri->linkSet->linkSet;
                        rinfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                        rinfo.priority = ITS_SS7_DEFAULT_PRI;
                        rinfo.sls = ITS_SS7_DEFAULT_SLS;

                        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                       &firstMatch, &lastMatch,
                                                       &whichLinkCode,
                                                       ITS_FALSE)) == NULL)
                        {
                            MTP3_ERROR(("Can't find match\n"));

                            return (ITS_FALSE);
                        }

                        /** FIXME **/
                        /* Fix core problem after adding dummy route-linkSet, 
                           we should verify that whichEntry is always positive.
                        */

                        if (whichEntry < 0)
                        {
                            MTP3_ERROR(("Can't find link with associated route \n"));
                            return (ITS_FALSE);
                        }

                        /* if route status is available */
                        if (ri->isAllowed && !ri->isRestricted)
                        {
                            AvailableRoute(ln,
                                           ent, whichEntry,
                                           firstMatch, lastMatch);
                        }
                        /* else if route status is restricted */
                        else if (ri->isRestricted)
                        {
                            RestrictedRoute(ln,
                                            ent, whichEntry,
                                            firstMatch, lastMatch);
                        }
                    }

                    /* cancel link becoming available */
                    ln->stFlags &= ~LINK_COMING_AVAILABLE;
                }
                else
                {
                    MTP3_DEBUG(("TSRC_Main: !AdjacentAccessible %d\n", ln->linkCode));

                    /*
                     * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                     * and isAllowed, but until this function call, the
                     * linkSet is not up!
                     */
                    LINK_SetLinkState(ln, ITS_TRUE);


                    if (!SPRestarting_ANSI())
                    {
                        MTP3_DEBUG(("TSRC_Main: !SP Restart\n "));
                        ls = LINKSET_FindLinkSet(linkSet);
                        if (ls == NULL)
                        {
                            MTP3_ERROR(("Link available for no link set\n"));

                            return (ITS_SUCCESS);
                        }

                        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, ls->adjacent,
                                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                                 FAMILY_ANSI,
                                                                 ls->ni, ls->linkSet,
                                                                 ITS_SS7_DEFAULT_LINK_CODE,
                                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
                        {
                            MTP3_DEBUG(("Unable to parse destination %08x\n", ls->adjacent));
                            return (ret);
                        }

                        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                       &firstMatch, &lastMatch,
                                                       &whichLinkCode,
                                                       ITS_FALSE)) == NULL)
                        {
                            MTP3_ERROR(("Can't find match\n"));

                            return (ITS_FALSE);
                        }

                        ri = ent->entries[whichEntry];

                        /* cancel inhibited links to adjacent point */
                        for (i = 0; i < ls->numLinks; i++)
                        {
                            ls->links[i]->stFlags &= ~LINK_INHIBITED;
                        }

                        /* mark adjacent SP restarting */
                        ls->adjRestart = ITS_TRUE;

                        MTP3_HDR_SET_SIO(omtp3, ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                                         &omtp3, NULL, 0);

                        RSRT_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_ADJACENT_RESTARTING,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        TLAC_Main_ANSI(MTP3_STM_TSRC,
                                       STM_TRIGGER_ADJACENT_SP_RESTARTING,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        /* start T28 */
                        tc.timerId = MTP3_T28;
                        tc.data.routeInfo.pointCode = ls->adjacent;
                        tc.data.routeInfo.linkSet = linkSet;
                        tc.data.routeInfo.sio = ri->linkSet->ni;

                        ri->t28 =
                            TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                               __ansi_t28 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));

                        /* Build SNMM traffic restart waiting */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET_ANSI(osnmm, SNMM_HC0_TRM_ANSI);
                        SNMM_HC1_SET_ANSI(osnmm, SNMM_HC1_TRW_ANSI);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                        SNMM_Encode_ANSI(&ev, &omtp3, &osnmm);


                        HMRT_Main_ANSI(MTP3_STM_TSRC,
                                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        UpdateAdjacent(ls);

                        /* stop T30 */
                        if (ri->t30 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelSharedTimer(ri->t30);
                            ri->t30 = TIMER_BAD_SERIAL;
                        }

                        /* Build SNMM traffic restart allowed */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET_ANSI(osnmm, SNMM_HC0_TRM_ANSI);
                        SNMM_HC1_SET_ANSI(osnmm, SNMM_HC1_TRA_ANSI);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                        SNMM_Encode_ANSI(&ev, &omtp3, &osnmm);


                        HMRT_Main_ANSI(MTP3_STM_TSRC,
                                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        /* start T29 */
                        tc.timerId = MTP3_T29;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ri->t29 =
                            TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                               __ansi_t29 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));
                    }
                    else /* SP is restarting */
                    {
                        MTP3_DEBUG(("TSRC_Main: SP Restart\n "));
                        /* Maintenance: this is the same code as if the SP wasn't
                         * accessible (above) */

                        /* mark link becoming available */
                        ln->stFlags |= LINK_COMING_AVAILABLE;

                        /*
                         * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                         * and isAllowed, but until this function call, the
                         * linkSet is not up!
                         */
                        LINK_SetLinkState(ln, ITS_TRUE);

                        /* for each destination (cluster) for which link set may be used */
                        for (count = 0, tmp = DSMQUEUE_HEAD(ln->linkSet->routes);
                             tmp != NULL && count < DSMQUEUE_COUNT(ln->linkSet->routes);
                             count++, tmp = DSMQUEUE_NEXT(ln->linkSet->routes, tmp) )
                        {
                            /* select one of concerned destinations */
                            memcpy(&ri, tmp->data, sizeof(ri));

                            rinfo.basic = ri->basic;
                            rinfo.linkSet = ri->linkSet->linkSet;
                            rinfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                            rinfo.priority = ITS_SS7_DEFAULT_PRI;
                            rinfo.sls = ITS_SS7_DEFAULT_SLS;

                            if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                           &firstMatch, &lastMatch,
                                                           &whichLinkCode,
                                                           ITS_FALSE)) == NULL)
                            {
                                MTP3_ERROR(("Can't find match\n"));

                                return (ITS_FALSE);
                            }

                            /** FIXME **/
                            /* Fix core problem after adding dummy route-linkSet,
                               we should verify that whichEntry is always positive.
                            */

                            if (whichEntry < 0)
                            {
                                MTP3_ERROR(("Can't find link with associated route \n"));
                                return (ITS_FALSE);
                            }

                            /* if route status is available */
                            if (ri->isAllowed && !ri->isRestricted)
                            {
                                MTP3_ERROR(("AvailableRoute itu-stm.c %d \n",__LINE__));
                                AvailableRoute(ln,
                                               ent, whichEntry,
                                               firstMatch, lastMatch);
                            }
                            /* else if route status is restricted */
                            else if (ri->isRestricted)
                            {
                                RestrictedRoute(ln,
                                                ent, whichEntry,
                                                firstMatch, lastMatch);
                            }
                        }

                        /* cancel link becoming available */
                        ln->stFlags &= ~LINK_COMING_AVAILABLE;
                    }
                }
            }
            else
            {
                MTP3_DEBUG(("TSRC_Main: AlternativeLink %d\n", ln->linkCode));

                /*
                 * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                 * and isAllowed, but until this function call, the
                 * linkSet is not up!
                 */
                if(ln->testPassed)/* to mark the isUp flag it should pass the SLTm/SLTA/test*/
                {
                LINK_SetLinkState(ln, ITS_TRUE);
                }

                /* if danger of congestion on normal link set subsides */
                if (!DangerOfCongestion(ln->linkSet))
                {
                    MTP3_POINT_CODE pc;

                    if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, ln->linkSet->adjacent,
                                                             REMOTE_ROUTE, ROUTE_DPC_NI,
                                                             FAMILY_ANSI,
                                                             ln->linkSet->ni,
                                                             ln->linkSet->linkSet,
                                                             ln->linkCode,
                                                             ITS_SS7_DEFAULT_LINK_PRI,
                                                             ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
                    {
                        MTP3_DEBUG(("Unable to parse destination %08x\n", ln->linkSet->adjacent));

                        return (ret);
                    }

                    if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                   &firstMatch, &lastMatch,
                                                   &whichLinkCode,
                                                   ITS_FALSE)) == NULL)
                    {
                        MTP3_ERROR(("Can't find match\n"));

                        return (ITS_FALSE);
                    }

                    ri = ent->entries[whichEntry];

                    /* mark destination (cluster) accessible */
                    ri->dest->status = DESTINATION_AVAILABLE;

                    MTP3_PC_SET_VALUE(pc, ln->linkSet->adjacent);

                    MTP3_HDR_SET_SIO(omtp3, ln->linkSet->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ln->linkSet->adjacent);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                    MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                                     &omtp3, NULL, 0);

                    /* if cluster */
                    if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                    {
                        RTAC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CLUSTER_ACCESS,
                                       ev.data, ev.len,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        RTAC_Main_ANSI(MTP3_STM_TSRC,
                                       SRM_TRIGGER_DEST_ACCESS,
                                       ev.data, ev.len,
                                       linkSet, linkCode);
                    }

                    ITS_EVENT_TERM(&ev);
                }
            }
        }
        else /* sending status */
        {
            /* if no other links available in link set */
            if (!AlternateLink(ln->linkSet, ln))
            {
                /*
                 * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                 * and isAllowed, but until this function call, the
                 * linkSet is not up!
                 */
                LINK_SetLinkState(ln, ITS_TRUE);

                /* Build SNMM traffic restart waiting */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ln->linkSet->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ln->linkSet->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ln->linkSet->lpc);

                SNMM_HC0_SET_ANSI(osnmm, SNMM_HC0_TRM_ANSI);
                SNMM_HC1_SET_ANSI(osnmm, SNMM_HC1_TRW_ANSI);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                SNMM_Encode_ANSI(&ev, &omtp3, &osnmm);


                HMRT_Main_ANSI(MTP3_STM_TSRC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               linkSet, linkCode);

                ITS_EVENT_TERM(&ev);
            }
            else
            {
                /*
                 * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                 * and isAllowed, but until this function call, the
                 * linkSet is not up!
                 */
                LINK_SetLinkState(ln, ITS_TRUE);
            }
        }
        break;

    case STM_TRIGGER_ROUTE_RESTRICTED:          /* from RTRC */
    case STM_TRIGGER_TCR:                       /* from RTRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        /* if route used */
        if (ri->flags & ROUTE_STP_IN_USE)
        {
            /* if not route marked restricted */
            if (!(ri->isRestricted))
            {
                /* mark route restricted */
                ri->isRestricted = ITS_TRUE;

                /* if any links in route available */
                if (LinkSetAvailable(ri->linkSet))
                {
                    if (SPRestarting_ANSI())
                    {
                        RestrictedRoute(NULL,
                                        ent, whichEntry,
                                        firstMatch, lastMatch);
                    }
                    else
                    {
                        /* if not adjacent SP inaccessible */
                        if (!AdjacentAccessible(ri->linkSet))
                        {
                            RestrictedRoute(NULL,
                                            ent, whichEntry,
                                            firstMatch, lastMatch);
                        }
                        else
                        {
                            UpdateAdjacent(ri->linkSet);

                            RestrictedRoute(NULL,
                                            ent, whichEntry,
                                            firstMatch, lastMatch);
                        }
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_DANGER_OF_CONGESTION:      /* from HMDC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        /* is alternate link set in use */
        if (ent->entries[whichEntry]->priority != 0)
        {
            /* if not destination marked restricted */
            if (ent->status != DESTINATION_RESTRICTED)
            {
                /* stop T11 */
                if (ri->t11 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ri->t11);
                    ri->t11 = TIMER_BAD_SERIAL;
                }

                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_RESTRICT,
                               NULL, 0,
                               linkSet, linkCode);

                /* mark destination restricted */
                ent->status = DESTINATION_RESTRICTED;
            }
        }
        else
        {
            /* if link set partially failed */
            {
                /* if cluster */
                {
                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_MSG_FOR_RESTRICTED_CLUST,
                                   sif, len,
                                   linkSet, linkCode);
                }
                /* else */
                {
                    RTRC_Main_ANSI(MTP3_STM_TSRC,
                                   SRM_TRIGGER_MSG_FOR_RESTRICTED_DEST,
                                   sif, len,
                                   linkSet, linkCode);
                }
            }
        }
        break;

    case STM_TRIGGER_T11:                       /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        /* while affected destination (cluster) remain */
        for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes);
             tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
             count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
        {
            ROUTE_InfoPtr ri;

            /* select an effected destination (cluster) */
            memcpy(&ri, tmp->data, sizeof(ri));

            /* mark destination (cluster) restricted */
            ri->dest->status = DESTINATION_RESTRICTED;

            MTP3_PC_SET_VALUE(dpc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(omtp3, ri->linkSet->ni);
            MTP3_RL_SET_DPC(omtp3.label, dpc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);

            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(dpc))
            {
                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_CLUSTER_RESTRICT,
                               ev.data, ev.len,
                               linkSet, linkCode);
            }
            else
            {
                RTRC_Main_ANSI(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_RESTRICT,
                               ev.data, ev.len,
                               linkSet, linkCode);
            }

            ITS_EVENT_TERM(&ev);
        }
        break;

    case STM_TRIGGER_LINK_CONGESTION_STATUS:    /* implementation dependent */
        /* determine affected destinations */

        ls = LINKSET_FindLinkSet(linkSet);

        if (ls != NULL)
        {
            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);

            if (sif[0] == L2_L3_CONGESTION_ONSET)
            {
                /* FIXME: If relevent, start T31 */
                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_FLOW_CONTROL_START,
                                   NULL, 0);
            }
            else if (sif[0] == L2_L3_CONGESTION_ABATES)
            {
                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_FLOW_CONTROL_STOP,
                                   NULL, 0);
            }

            TSFC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_CONGESTION_STATUS,
                           ev.data, ev.len,
                           linkSet, linkCode);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case STM_TRIGGER_SENDING_STATUS_PHASE:      /* from TPRC */
        SendingStatusSet_ANSI(ITS_TRUE);
        break;

    case STM_TRIGGER_SEND_TRW:                  /* from TPRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Build SNMM traffic restart waiting */
        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        SNMM_HC0_SET_ANSI(osnmm, SNMM_HC0_TRM_ANSI);
        SNMM_HC1_SET_ANSI(osnmm, SNMM_HC1_TRW_ANSI);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        SNMM_Encode_ANSI(&ev, &omtp3, &osnmm);


        HMRT_Main_ANSI(MTP3_STM_TSRC,
                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                       ev.data, ev.len,
                       linkSet, linkCode);

        ITS_EVENT_TERM(&ev);
        break;

    case STM_TRIGGER_TRAFFIC_RESTART_ALLOWED:   /* from TPRC */
        pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        else
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ret);
        }

        /* if from adjacent restarting SP */
        if (ri->basic.dpc == ri->linkSet->adjacent || 
            ri->linkSet->adjRestart)
        {
            /* stop T28 */
            if (ri->t28 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t28);
                ri->t28 = TIMER_BAD_SERIAL;
            }

            /* stop T25 */
            if (ri->t25 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t25);
                ri->t25 = TIMER_BAD_SERIAL;
            }
            MTP3_DEBUG(("Traffic Restart Received and now call TrafficRestart Func\n"));
            TrafficRestart(ri);
        }
        else
        {
            MTP3_DEBUG(("Traffic Restart Received and now call StartTrafficRestart Func\n"));
            StartTrafficRestart(ri);
        }
        break;

    case STM_TRIGGER_T25:                       /* from timer control */
    case STM_TRIGGER_T28:                       /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        if (trigger == STM_TRIGGER_T25)
        {
            ri->t25 = TIMER_BAD_SERIAL;
        }
        else
        {
            ri->t28 = TIMER_BAD_SERIAL;
        }

        TrafficRestart(ri);
        break;

    case STM_TRIGGER_TRAFFIC_RESTART_WAITING:   /* from HMDT */
        pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* may be from non-adjacent */
        linkSet = MTP3_FindAdjacent_ANSI(ni, pc, linkSet);

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            if (whichEntry < 0)
            {
                return (ITS_EINVALIDARGS);
            }
            ri = ent->entries[whichEntry];
        }

        if (ent == NULL || ri == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* if from adjacent SP */
        if (ri->basic.dpc == ri->linkSet->adjacent)
        {
            /* stop T28 */
            if (ri->t28 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t28);
                ri->t28 = TIMER_BAD_SERIAL;
            }

#if 0
            /* stop T25 */
            if (ri->t25 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t25);
                ri->t25 = TIMER_BAD_SERIAL;
            }
#endif
                /* start T25 */
                tc.timerId = MTP3_T25;
                tc.data.routeInfo.pointCode = ri->basic.dpc;
                tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
                tc.data.routeInfo.sio = ri->linkSet->ni;

                ri->t25 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t25 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
        }
        else
        {
            if (SPRestarting_ANSI())
            {
                /* start T25 */
                tc.timerId = MTP3_T25;
                tc.data.routeInfo.pointCode = ri->basic.dpc;
                tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
                tc.data.routeInfo.sio = ri->linkSet->ni;

                ri->t25 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t25 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

            }
            else
            {
                StartTrafficRestart(ri);
            }
        }
        break;

    case STM_TRIGGER_SEND_STATUS:               /* from TPRC */
        if (SendingStatus_ANSI())
        {
            DSM_TableIterate(DSM_Mtp3FtGroupId,
                             DSM_TABLE_DESTINATIONS,
                             NULL, NULL, StatusIterate);

            TPRC_Main_ANSI(MTP3_STM_TSRC,
                           STM_TRIGGER_STATUS_SENT,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_T29:
    case STM_TRIGGER_T30:
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        if (ri)
        {
            if (trigger == STM_TRIGGER_T29)
            {
                ri->t29 = TIMER_BAD_SERIAL;
            }
            else if (trigger == STM_TRIGGER_T30)
            {
                ri->t30 = TIMER_BAD_SERIAL;
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
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
int
TRCC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1], omtp3;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                              sizeof(ITS_OCTET)];
    MTP3_TimerContext tc;
    ITS_UINT pc;
    ITS_OCTET ni, congLevel;
    ITS_EVENT ev;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri;

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TRCC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* wants a point code to get a route? */    
    switch (trigger)
    {
    case STM_TRIGGER_DEST_CONGESTION_STATUS:    /* from RTCC */
        pc = SNMM_TRANSFER_CONTROL_GET_DEST_ANSI(snmm->data.transferControl);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2477, __FILE__, __LINE__, "dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        congLevel = SNMM_TRANSFER_CONTROL_GET_STATUS_ANSI(snmm->data.transferControl);

        MTP3_HDR_SET_SIO(omtp3, ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &omtp3, NULL, 0);

        if (ri->congestionState == CONGESTION_IDLE)
        {
            /* store destination congestion status */
            ri->congLevel = congLevel;

            ri->congestionState = CONGESTION_WAIT_1;
            
            TSRC_Main_ANSI(MTP3_STM_TRCC,
                           STM_TRIGGER_ACCESSIBILITY_REQUEST,
                           ev.data, ev.len,
                           linkSet, linkCode);

        }
        else if (ri->congestionState == CONGESTION_WAIT_1)
        {
            /* if new congestion status greater */
            if (congLevel > ri->congLevel)
            {
                /* store congestion status */
                ri->congLevel = congLevel;
            }
        }
        else if (ri->congestionState == CONGESTION_WAIT_2)
        {
            /* if new congestion status greater */
            if (congLevel > ri->congLevel)
            {
                /* update congestion status */
                ri->congLevel = congLevel;
                
                TSFC_Main_ANSI(MTP3_STM_TRCC,
                               STM_TRIGGER_DEST_CONGESTION_STATUS,
                               ev.data, ev.len,
                               linkSet, linkCode);
                
                /* stop T15 */
                if (ri->t15 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ri->t15);
                }

                /* start T15 */
                tc.timerId = MTP3_T15;
                tc.data.routeInfo.pointCode = pc;
                tc.data.routeInfo.linkSet = linkSet;
                tc.data.routeInfo.sio = ni;

                ri->t15 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t15 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
            /* else if new congestion status equal */
            else if (congLevel == ri->congLevel)
            {
                /* stop T15 */
                if (ri->t15 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ri->t15);
                    ri->t15 = TIMER_BAD_SERIAL;
                }

                /* start T15 */
                tc.timerId = MTP3_T15;
                tc.data.routeInfo.pointCode = pc;
                tc.data.routeInfo.linkSet = linkSet;
                tc.data.routeInfo.sio = ni;

                ri->t15 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t15 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
        }
        else if (ri->congestionState == CONGESTION_WAIT_3)
        {
            RCAT_Main_ANSI(MTP3_STM_TRCC,
                           SRM_TRIGGER_STOP_CONG_TEST,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
            /* if new congestion status different */
            if (congLevel != ri->congLevel)
            {
                /* update congestion status */
                ri->congLevel = congLevel;
                
                TSFC_Main_ANSI(MTP3_STM_TRCC,
                               STM_TRIGGER_DEST_CONGESTION_STATUS,
                               ev.data, ev.len,
                               linkSet, linkCode);
            }
            
            /* start T15 */
            tc.timerId = MTP3_T15;
            tc.data.routeInfo.pointCode = pc;
            tc.data.routeInfo.linkSet = linkSet;
            tc.data.routeInfo.sio = ni;

            ri->t15 =
                TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_t15 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            
            ri->congestionState = CONGESTION_WAIT_2;
        }
        break;
        
    case STM_TRIGGER_DECR_DEST_CONG_STATUS:     /* from RCAT */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2477, __FILE__, __LINE__, "dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_3)
        {
            /* decrement congestion status */
            ri->congLevel--;
            
            TSFC_Main_ANSI(MTP3_STM_TRCC,
                           STM_TRIGGER_DEST_CONGESTION_STATUS,
                           sif, len,
                           linkSet, linkCode);
        
            /* if congestion status equal zero */
            if (ri->congLevel == 0)
            {
                ri->congestionState = CONGESTION_IDLE;
            }
            else
            {
                RCAT_Main_ANSI(MTP3_STM_TRCC,
                               SRM_TRIGGER_START_CONG_TEST,
                               sif, len,
                               linkSet, linkCode);
            }
        }
        break;
        
    case STM_TRIGGER_ACCESSIBILITY_DATA:        /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2477, __FILE__, __LINE__, "dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_1)
        {
            ITS_BOOLEAN accessible = linkCode;

            /*
             * NOTE: The linkCode contains a boolean indicating if the
             * destination is accessible.
             */
            if (accessible)
            {
                /* update congestion status */
                ri->congLevel = 0;
                
                TSFC_Main_ANSI(MTP3_STM_TRCC,
                               STM_TRIGGER_DEST_CONGESTION_STATUS,
                               sif, len,
                               linkSet, linkCode);
                
                /* start T15 */
                tc.timerId = MTP3_T15;

                TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_t15 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

                ri->congestionState = CONGESTION_WAIT_2;
            }
        }
        break;
        
    case STM_TRIGGER_DEST_INACCESS:             /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));
 
            MTP3_Alarm_ANSI(2477, __FILE__, __LINE__, "dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_1)
        {
            ri->congestionState = CONGESTION_IDLE;
        }
        else if (ri->congestionState == CONGESTION_WAIT_2)
        {
            /* update congestion status to zero */
            ri->congLevel = 0;
            
            /* stop T15 */
            if (ri->t15 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t15);
                ri->t15 = TIMER_BAD_SERIAL;
            }
            
            ri->congestionState = CONGESTION_IDLE;
        }
        else if (ri->congestionState == CONGESTION_WAIT_3)
        {
            /* update congestion status to zero */
            ri->congLevel = 0;
            
            RCAT_Main_ANSI(MTP3_STM_TRCC,
                           SRM_TRIGGER_STOP_CONG_TEST,
                           sif, len,
                           linkSet, linkCode);
            
            ri->congestionState = CONGESTION_IDLE;
        }
        break;
        
    case STM_TRIGGER_CLUST_INACCESS:            /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2477, __FILE__, __LINE__, "dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_1)
        {
            ri->congestionState = CONGESTION_IDLE;
        }
        else if (ri->congestionState == CONGESTION_WAIT_2)
        {
            /* update congestion status to zero */
            ri->congLevel = 0;
            
            /* stop T15 */
            if (ri->t15 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t15);
                ri->t15 = TIMER_BAD_SERIAL;
            }
            
            ri->congestionState = CONGESTION_IDLE;
        }
        else if (ri->congestionState == CONGESTION_WAIT_3)
        {
            /* update congestion status to zero */
            ri->congLevel = 0;
            
            RCAT_Main_ANSI(MTP3_STM_TRCC,
                           SRM_TRIGGER_STOP_CONG_TEST,
                           sif, len,
                           linkSet, linkCode);
            
            ri->congestionState = CONGESTION_IDLE;
        }
        break;
        
    case STM_TRIGGER_T15:                       /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2477, __FILE__, __LINE__, "dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_2)
        {
            RCAT_Main_ANSI(MTP3_STM_TRCC,
                           SRM_TRIGGER_CONG_TEST,
                           NULL, 0,
                           linkSet, linkCode);
            
            ri->congestionState = CONGESTION_WAIT_3;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
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
static ITS_BOOLEAN
ChangeoverRequired(SS7_LinkPtr ln)
{   
    if (ln != NULL)
    {
        /* is signalling Link Loaded */
        return ( (ln->isUp && ln->isAllowed) || (ln->stFlags & LINK_COP) );
    }

    MTP3_DEBUG(("ChangeoverRequired: Link Pointer is NULL"));

    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Build ChangeOver Message
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
static ITS_BOOLEAN
BuildChangeOverMsg(MTP3_HEADER_ANSI *mtp3,
                   SNMM_MESSAGE *snmm, SS7_LinkSetPtr ls, 
                   SS7_LinkPtr ln, ITS_OCTET hc0, 
                   ITS_OCTET hc1)
{
    MTP3_HDR_SET_SIO(*mtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
    MTP3_RL_SET_DPC_VALUE(mtp3->label, ls->adjacent);
    MTP3_RL_SET_OPC_VALUE(mtp3->label, ls->lpc);
    
    switch (hc0) 
    {
    case SNMM_HC0_CHM:
        /* Build SNMM changeover ack */

        SNMM_HC0_SET(*snmm, SNMM_HC0_CHM);

        if (hc1 == SNMM_HC1_COA)
        {
            if (ln->isSAAL)
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_XCA);
            }
            else
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_COA);
            }
        }
        else if (hc1 == SNMM_HC1_COO)
        {
            if (ln->isSAAL)
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_XCO);
            }
            else
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_COO);
            }
        }    
        
        /* Initialize slc and fsn to 0 */
        snmm->data.changeOver.slc_fsn[0] = 0;
        snmm->data.changeOver.slc_fsn[1] = 0;

        SNMM_CHANGEOVER_SET_SLC(snmm->data.changeOver, ln->linkCode);
        if (ln->isSAAL)
        {
            SNMM_CHANGEOVER_SET_FSN_SAAL_ANSI(snmm->data.changeOver, ln->localBSN);
        }
        else
        {
            SNMM_CHANGEOVER_SET_FSN_ANSI(snmm->data.changeOver, ln->localBSN);
        }
  
        break;
    
    case SNMM_HC0_ECM:

        SNMM_HC0_SET(*snmm, SNMM_HC0_ECM);

        if (hc1 == SNMM_HC1_ECO)
        {
            SNMM_HC1_SET(*snmm, SNMM_HC1_ECO);
        }
        else if (hc1 == SNMM_HC1_ECA)
        {        
            SNMM_HC1_SET(*snmm, SNMM_HC1_ECA);
        }

        SNMM_EMERG_CHANGEOVER_SET_SLC(snmm->data.emergencyChangeOver,
                                      ln->linkCode);
        break;
    }
    return (ITS_TRUE);
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
static ITS_BOOLEAN
RoutingChanged(ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *req, *resp;
    ITS_OCTET reqLS, reqLC, ni;
    ITS_UINT pc, i;
    SS7_Destination *dest;
    ITS_UINT ols, nls;
    SS7_LinkPtr ln=NULL;

    /*
     * if we get this, there is *no* alternate route at all.
     * This falls under 6.2.5.
     */
    if (linkSet == ITS_SS7_DEFAULT_LINK_SET &&
        linkCode == ITS_SS7_DEFAULT_LINK_CODE)
    {
        return (ITS_TRUE);
    }

    ITS_C_ASSERT(len >= (sizeof(ITS_OCTET) +
                         2 * sizeof(MTP3_HEADER_ANSI) +
                         2 * sizeof(ITS_OCTET)));

    resp = (MTP3_HEADER_ANSI *)&sif[sizeof(ITS_OCTET)];
    req = (MTP3_HEADER_ANSI *)&sif[sizeof(ITS_OCTET) +
                                   sizeof(MTP3_HEADER_ANSI)];
    reqLS = sif[sizeof(ITS_OCTET) +
                2 * sizeof(MTP3_HEADER_ANSI)];
    reqLC = sif[sizeof(ITS_OCTET) +
                2 * sizeof(MTP3_HEADER_ANSI) +
                sizeof(ITS_OCTET)];
    /*chage for check the lincode test passed in case chageover 07 March 08*/   
    ln = LINK_FindLink(reqLS ,reqLC);
     if(ln != NULL) 
       {
        if( !ln->testPassed)
      	{
        		MTP3_DEBUG(("Link Up: = %02d :\n",ln->testPassed));
        		return (ITS_FALSE);
      	}
       }

    /*
     * if the link set is the same, the routing is different
     * if the link is different (alternate link).
     */
    if (reqLS == linkSet && reqLC != linkCode)
    {
        return (ITS_TRUE);
    }

    pc = MTP3_RL_GET_DPC_VALUE(resp->label);
    ni = MTP3_HDR_GET_SIO(*resp) & MTP3_NIC_MASK;

    dest = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);

    ols = nls = (ITS_UINT)-1;
    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->entries[i]->basic.type == REMOTE_ROUTE &&
            (dest->entries[i]->basic.style == ROUTE_DPC_NI ||
             dest->entries[i]->basic.style == ROUTE_DPC_OPC_NI))
        {
            if (dest->entries[i]->linkSet->linkSet == linkSet)
            {
                nls = i;
            }
            if (dest->entries[i]->linkSet->linkSet == reqLS)
            {
                ols = i;
            }
        }
    }

    if (dest->entries[nls]->priority < dest->entries[ols]->priority)
    {
        return (ITS_FALSE);
    }

    return (MTP3_RL_GET_DPC_VALUE(req->label) !=
            MTP3_RL_GET_DPC_VALUE(resp->label) ||
            reqLS != linkSet ||
            reqLC != linkCode);
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
TCOC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TimerContext tc;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1], *slsUnshift;
    MTP3_HEADER_ANSI omtp3;
    SNMM_MESSAGE snmm, *snmm_ptr;
    ITS_EVENT ev, *fetched, *cocbEv;
    MTP3_EventRec evRec;
    ITS_UINT pc1;
    ITS_OCTET ni, sls, tls, tlc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    SS7_Destination *dest;
    ROUTE_MatchInfo mi;

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TCOC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* DO NOT RETURN HERE. */
    ln = LINK_FindLink(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));
    }

    /* Do Not return, LinkSet sent by TSRC (alternate routing data)might be 
     * default linkset 
     */
    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_DEBUG(("Can't find link set %d\n", linkSet));
    }

    if (ln != NULL)
    {
       MTP3_DEBUG(("**** TCOC: trigger: %d state:%d ***\n", trigger, ln->changeoverState));
    }

    /* Wants a link, I think */    
    switch (trigger)
    {
    case STM_TRIGGER_LINK_UNAVAILABLE:          /* from TLAC */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_IDLE)
        {
            /* buffer messages for affected link */
            /*ln->qPut = ITS_TRUE;*/
            LINK_SetLinkQPut(ln, ITS_TRUE);

            /* alternate route request */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            
            ln->changeoverState = CHANGEOVER_WAIT_1;

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            
            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);
            MTP3_DEBUG(("TCOC:  changeoverState CHANGEOVER_IDLE ->> CHANGEOVER_WAIT_1\n" ));
            
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len, /* Tmp RL */
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        else if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            MTP3_DEBUG(("TCOC:  changeoverState CHANGEOVER_RETRIEVING\n" ));
            /* mark link unavailable */
            ln->stFlags |= LINK_IS_UNAVAILABLE;
        }
        else
        {
         MTP3_DEBUG(("TCOC: invalid changeoverState reached\n" ));
        }
        break;
        
    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_WAIT_1)
        {
            /* stop T1 */
            TIMERS_CancelSharedTimer(ln->t1);
            ln->t1 = TIMER_BAD_SERIAL;

            /* these tasks should be carried out in the order shown */

            /*
             * NOTE: this order is backwards, but necessary.  MTP2_SendData
             * examines the qPut variable to determine if it should queue
             * or transmit the messages.
             *
             * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
             * this.  The second platform might transmit while we are.  This
             * could be avoided by not committing the link info until the
             * queue is cleared.
             */

            /* stop buffering messages on restored link */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);

            /*
             * send buffered messages on restored link
             *
             * ROTATION COMMENT
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            ln->changeoverState = CHANGEOVER_IDLE;    

            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);
                
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_2 ||
                 ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK ||
                 ln->changeoverState == CHANGEOVER_WAIT_5 ||
                 ln->changeoverState == CHANGEOVER_WAIT_6 ||
                 ln->changeoverState == CHANGEOVER_WAIT_8)
        {
            /*
             * NOTE: this order is backwards, but necessary.  MTP2_SendData
             * examines the qPut variable to determine if it should queue
             * or transmit the messages.
             *
             * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
             * this.  The second platform might transmit while we are.  This
             * could be avoided by not committing the link info until the
             * queue is cleared.
             */

            /* stop buffering messages on restored link */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);

            /*
             * send buffered messages on restored link
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            ln->changeoverState = CHANGEOVER_IDLE;      
            
            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);
                
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);          
        }
        else if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            /* Cancel Link Unavailable */
            ln->stFlags &= (~LINK_IS_UNAVAILABLE);
        }
        break;
        
    case STM_TRIGGER_EMERG_CHANGEOVER_ORDER:    /* from TLAC */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_EMER_CHANGEOVER  );
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_EMERG_CH_OVER);

        if (ln->changeoverState == CHANGEOVER_IDLE)
        {
            /* cancel remote BSNT retrieved */
            ln->stFlags &= (~LINK_REMOTE_BSNT_RETRIEVED);

            /* buffer messages for affected link */
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);
            
            ln->changeoverState = CHANGEOVER_WAIT_5;
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_1) 
        {
            /* do nothing */
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* stop T2 */
            TIMERS_CancelSharedTimer(ln->t2);
            ln->t2 = TIMER_BAD_SERIAL;
            ln->changeoverState = CHANGEOVER_IDLE;
            /* Increament the peg for ChangeOver */
            // PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEOVER);

            if (ln->stFlags & LINK_LOCAL_BSNT_RETRIEVED)
            {                              
                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM,
                                                            SNMM_HC1_COA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ANSI,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));

                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for COA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
                
                ITS_EVENT_TERM(&ev);
            }
            else
            {
                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                            SNMM_HC1_ECA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ANSI,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));

                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for ECA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
            }

            MTP3_DEBUG(("SLM_TRIGGER_STM_READY -- FILE %s LINE %d\n",__FILE__,__LINE__));
            LSAC_Main_ANSI(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * do this first to avoid circular transmission
             */
            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * ROTATION COMMENT
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                MTP3_RL_SET_SLS(slsUnshift->label, sls);

                HMRT_Main_ANSI(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_7)
        {
            /* cancel FSNC available */
            ln->stFlags &= (~LINK_REMOTE_BSNT_RETRIEVED);
            
            /* stop T1 */
            TIMERS_CancelSharedTimer(ln->t1);
            ln->t1 = TIMER_BAD_SERIAL;
            
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);
            
            ln->changeoverState = CHANGEOVER_WAIT_8;
        }
        /*
         * Note that ECO can arrive from the remote while
         * state is WAIT_2 (wait for BSNT from L2).  In this case
         * we really should be marking this as ECO pending. 
         */
        else if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* SDL save construct: we save the information and
             * set the flag.
             */
            ln->stFlags |= LINK_CHANGE_OVER_RECEIVED;

            /* cancel FSNC available */
            ln->stFlags &= (~LINK_REMOTE_BSNT_RETRIEVED);

        }

        break;
        
    case STM_TRIGGER_ALTERNATE_ROUTE_DATA:      /* from TSRC */
        tls = sif[2 * sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET)];
        tlc = sif[2 * sizeof(MTP3_HEADER_ANSI) + 2 * sizeof(ITS_OCTET)];

        ln = LINK_FindLink(tls, tlc);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", tls, tlc));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(tls);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", tls));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changeoverState == CHANGEOVER_WAIT_1)
        {
            if (ChangeoverRequired(ln))
            {
                MTP3_DEBUG(("Changeover Required %d:%d!\n", tls, tlc));

                if (linkSet != ITS_SS7_DEFAULT_LINK_SET &&
                    linkCode != ITS_SS7_DEFAULT_LINK_CODE &&
                    !(ln->stFlags & (LINK_REM_INHIBITED|LINK_LOC_INHIBITED|
                                     LINK_REM_BLOCKED|LINK_LOC_BLOCKED)))
                {
                    /* There is alternate, Route to exchange CO messages */

                    MTP2_SendData_ANSI(tls, tlc,
                                       L3_L2_RETRIEVE_BSNT, NULL, 0);
                    
                    ln->changeoverState = CHANGEOVER_WAIT_2;
                    MTP3_DEBUG(("TCOC_Main_CCITT:L3_L2_RETRIEVE_BSNT Sent Succefully CHANGEOVER_WAIT_1 ->> CHANGEOVER_WAIT_2\n"));
                }
                else
                {
                    ln->changeoverState = CHANGEOVER_WAIT_7;
                   MTP3_DEBUG(("TCOC_Main_CCITT: CHANGEOVER_WAIT_1 ->> CHANGEOVER_WAIT_7 Start T1\n"));

                   MTP3_DEBUG(("SLM_TRIGGER_STM_READY -- FILE %s LINE %d\n",__FILE__,__LINE__));
                    LSAC_Main_ANSI(MTP3_STM_TCOC,
                                   SLM_TRIGGER_STM_READY,
                                   NULL, 0,
                                   tls, tlc);
                    
                    /* start T1 */
                    tc.timerId = MTP3_T1;
                    tc.data.linkInfo.linkSet = tls;
                    tc.data.linkInfo.linkCode = tlc;

                    ln->t1 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                                __ansi_t1 * USEC_PER_MILLISEC,
                                                &tc, sizeof(MTP3_TimerContext));
                    
                }
            }
            else
            {
                MTP3_DEBUG(("Changeover NOT Required %d:%d!", tls, tlc));

                LSAC_Main_ANSI(MTP3_STM_TCOC,
                               SLM_TRIGGER_STM_READY,
                               NULL, 0,
                               tls, tlc);
                
                /*
                 * NOTE: this order is backwards, but necessary.  MTP2_SendData
                 * examines the qPut variable to determine if it should queue
                 * or transmit the messages.
                 *
                 * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
                 * this.  The second platform might transmit while we are.  This
                 * could be avoided by not committing the link info until the
                 * queue is cleared.
                 */

                /* stop buffering messages on restored link */
                /*ln->qPut = ITS_FALSE;*/
                LINK_SetLinkQPut(ln, ITS_FALSE);

                /*
                 * send buffered messages on restored link
                 *
                 * NOTE: SLS unshifting not required here, as this is
                 * recovery (link bounce).
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                    fetched = &evRec.event;

                    MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                       L2_LINK_CODE(fetched),
                                       L2_MSG_TYPE(fetched),
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)));

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
                MTP3_DEBUG(("TCOC_Main_CCITT: CHANGEOVER_WAIT_1 ->> CHANGEOVER_IDLE  Nochageover Required\n"));
                
                TLAC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
                
                TSRC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
            }
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_6)
        {
            if (ChangeoverRequired(ln))
            {
                if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED)
                {
                    MTP2_SendData_ANSI(tls, tlc,
                                       L3_L2_RETRIEVE_MSGS,
                                       (ITS_OCTET *)&ln->remoteBSN, 
                                       sizeof(ITS_UINT));
            
                    /* mark link unavailable */
                    ln->stFlags |= LINK_IS_UNAVAILABLE;
            
                    ln->changeoverState = CHANGEOVER_RETRIEVING;
         MTP3_DEBUG(("TCOC_Main_CCITT:L3_L2_RETRIEVE_MSG Sent Succefully CHANGEOVER_WAIT_6 ->> CHANGEOVER_RETRIEVING\n"));
                }
                else
                {
         MTP3_DEBUG(("TCOC_Main_CCITT:CHANGEOVER_WAIT_6 ->> CHANGEOVER_IDLE \n"));
                    ln->changeoverState = CHANGEOVER_IDLE;
            MTP3_DEBUG(("SLM_TRIGGER_STM_READY -- FILE %s LINE %d\n",__FILE__,__LINE__));

                    LSAC_Main_ANSI(MTP3_STM_TCOC,
                                   SLM_TRIGGER_STM_READY,
                                   NULL, 0,
                                   tls, tlc);

                    /*
                     * do this first to avoid a circle.
                     */
                    HMRT_Main_ANSI(MTP3_STM_TCOC,
                                   SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                                   NULL, 0,
                                   tls, tlc);
            
                    /*
                     * send buffered messages on alternative links
                     *
                     * SLS unshifting *is* required here.  It's not terribly
                     * awful, though.
                     */
                    while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                    {
                        evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                        fetched = &evRec.event;

                        /* if this fails we're toast. */
                        ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                        ITS_C_ASSERT(ls != NULL);

                        slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                        sls = MTP3_RL_GET_SLS(slsUnshift->label);

                        sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                        MTP3_RL_SET_SLS(slsUnshift->label, sls);

                        HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                       SMH_TRIGGER_MSG_FOR_ROUTING,
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)),
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        ITS_EVENT_TERM(cocbEv);
                        ITS_Free(cocbEv);
                    }

                    TLAC_Main_ANSI(MTP3_STM_TCOC,
                                   STM_TRIGGER_CHANGEOVER_EXECUTED,
                                   NULL, 0,
                                   tls, tlc);
            
                    TSRC_Main_ANSI(MTP3_STM_TCOC,
                                   STM_TRIGGER_CHANGEOVER_EXECUTED,
                                   NULL, 0,
                                   tls, tlc);
                }
            }
            else
            {
                ln->changeoverState = CHANGEOVER_IDLE;
                MTP3_DEBUG(("TCOC_Main_CCITT:CHANGEOVER_WAIT_6 ->> CHANGEOVER_IDLE\n"));

                LSAC_Main_ANSI(MTP3_STM_TCOC,
                               SLM_TRIGGER_STM_READY,
                               NULL, 0,
                               tls, tlc);
                
                /*
                 * NOTE: this order is backwards, but necessary.  MTP2_SendData
                 * examines the qPut variable to determine if it should queue
                 * or transmit the messages.
                 *
                 * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
                 * this.  The second platform might transmit while we are.  This
                 * could be avoided by not committing the link info until the
                 * queue is cleared.
                 */

                /* stop buffering messages on restored link */
                /*ln->qPut = ITS_FALSE;*/
                LINK_SetLinkQPut(ln, ITS_FALSE);

                /*
                 * send buffered messages on restored link
                 *
                 * NOTE: SLS unshifting not required here, as this is
                 * recovery (link bounce).
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {

                    evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                    fetched = &evRec.event;

                    MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                       L2_LINK_CODE(fetched),
                                       L2_MSG_TYPE(fetched),
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)));

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }
                
                TLAC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
                
                TSRC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
            }
        }
        break;
                
    case STM_TRIGGER_CHANGEOVER_ORDER:          /* from TLAC */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_NORMAL_CH_OVER);

        /* Assume that TLAC is giving correct linkSet and LinkCode */


        if (ln->changeoverState == CHANGEOVER_IDLE)
        {
            /* mark remote BSNT retrieved */
            ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;

            ln->changeoverState = CHANGEOVER_WAIT_5;

            ln->stFlags |= LINK_CHANGE_OVER_RECEIVED;
            /* Retrieve and save FSNC (Remote BSN) */
            if (sif == NULL)
            {
                MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                    STM_TRIGGER_CHANGEOVER_ORDER"));

                return (~ITS_SUCCESS);
            }
            /* Retrieve and save FSNC (Remote BSN) */

            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                          sizeof(ITS_OCTET)); 
            if (ln->isSAAL)
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN_SAAL(snmm_ptr->data.changeOver);
            }
            else
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN(snmm_ptr->data.changeOver);
            }

            /* buffer messages for affected link */
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);

        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* Retrieve and save FSNC (Remote BSN) */

            if (src != MTP3_STM_TCOC)
            {
                if (sif == NULL) 
                {
                    MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                        STM_TRIGGER_CHANGEOVER_ORDER"));

                    return (~ITS_SUCCESS);
                }
                /* Retrieve and save FSNC (Remote BSN) */

                snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                                        sizeof(ITS_OCTET));
                if (ln->isSAAL)
                {
                    ln->remoteBSN = 
                        SNMM_CHANGEOVER_GET_FSN_SAAL_ANSI(snmm_ptr->data.changeOver);
                }
                else
                {
                    ln->remoteBSN = 
                        SNMM_CHANGEOVER_GET_FSN_ANSI(snmm_ptr->data.changeOver);
                }

                /* mark remote BSNT retrieved */
                ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;
            }

            /* stop T2 */
            TIMERS_CancelSharedTimer(ln->t2);
            ln->t2 = TIMER_BAD_SERIAL;
            ln->changeoverState = CHANGEOVER_RETRIEVING;
            /* Increament the peg for ChangeOver */
            //PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
            
            if (ln->stFlags & LINK_LOCAL_BSNT_RETRIEVED)
            {

                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM,
                                                            SNMM_HC1_COA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ANSI,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));

                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for COA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
                
                ITS_EVENT_TERM(&ev);
            }
            else
            {
                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                            SNMM_HC1_ECA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ANSI,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));

                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for ECA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
                
                ITS_EVENT_TERM(&ev);
            }
            
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_RETRIEVE_MSGS, 
                               (ITS_OCTET *)&ln->remoteBSN, 
                               sizeof(ITS_UINT));
            
            /* mark link unavailable */
            ln->stFlags |= LINK_IS_UNAVAILABLE;
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_7)
        {
            if (sif == NULL)
            {
                MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                    STM_TRIGGER_CHANGEOVER_ORDER"));

                return (~ITS_SUCCESS);
            }
            /* Retrieve and save FSNC (Remote BSN) */

            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                                        sizeof(ITS_OCTET));
            if (ln->isSAAL)
            {
                ln->remoteBSN = 
                    SNMM_CHANGEOVER_GET_FSN_SAAL_ANSI(snmm_ptr->data.changeOver);
            }
            else
            {
                ln->remoteBSN = 
                    SNMM_CHANGEOVER_GET_FSN_ANSI(snmm_ptr->data.changeOver);
            }

            /* mark FSNC available */
            ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;
            
            /* stop T1 */
            TIMERS_CancelSharedTimer(ln->t1);
            ln->t1 = TIMER_BAD_SERIAL;
            
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);
            
            ln->changeoverState = CHANGEOVER_WAIT_8;
        }
        /*
         * Note that COO can arrive from the remote while
         * state is WAIT_2 (wait for BSNT from L2).  In this case
         * we really should be marking this as CO pending. 
         */
        else if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* SDL save construct: we save the information and
             * set the flag.
             */
            ln->stFlags |= LINK_CHANGE_OVER_RECEIVED;
            /* Retrieve and save FSNC (Remote BSN) */
            if (sif == NULL)
            {
                MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                    STM_TRIGGER_CHANGEOVER_ORDER"));

                return (~ITS_SUCCESS);
            }
            /* Retrieve and save FSNC (Remote BSN) */

            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                                        sizeof(ITS_OCTET));
            if (ln->isSAAL)
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN_SAAL_ANSI(snmm_ptr->data.changeOver);
            }
            else
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN_ANSI(snmm_ptr->data.changeOver);
            }

            /* mark remote BSNT retrieved */
            ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;

        }


        break;
            
    case STM_TRIGGER_BSNT:                      /* from L2 */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 

        /* Retrieve Local BSNT from the message */
        /*ln->localBSN = (sif[1] << 24) | (sif[2] << 16) | (sif[3] << 8) | sif[4];Sandeep As bsnt is one byte recevied form mtp2*/

        ln->localBSN = (sif[1]);
        MTP3_DEBUG(("**** STM_TRIGGER_BSNT: bsnt=%d ****\n", ln->localBSN));


        if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* mark local BSNT received */
            ln->stFlags |= LINK_LOCAL_BSNT_RETRIEVED;
            ln->changeoverState = CHANGEOVER_WAIT_FOR_ACK;
            
            /* Build SNMM CHANGEOVER ORDER message */
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln,
                               SNMM_HC0_CHM, SNMM_HC1_COO);

            MTP3_Alarm_ANSI(2513, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x", 
                             linkSet,linkCode);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for COO Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);

            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            /* start T2 */
            tc.timerId = MTP3_T2;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t2 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                        __ansi_t2 * USEC_PER_MILLISEC,
                                        &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("BSNTRetrieved:CHANGEOVER_WAIT_2-->> CHANGEOVER_WAIT_FOR_ACK COO Sent T2 Started %d\n",__ansi_t2));

            /* This flag is set if the COO is recieved while in
             * state CHANGEOVER_WAIT_2. But the COO is processed
             * in CHANGEOVER_WAIT_FOR_ACK state. Therefore TCOC
             * re-generate the COO event after the local BSN is processed
             */
            if (ln->stFlags & LINK_CHANGE_OVER_RECEIVED)
            {
                /* cancel LINK_CHANGE_OVER_RECEIVED */
                ln->stFlags &= (~LINK_CHANGE_OVER_RECEIVED);

                if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED)
                {
                    MTP3_DEBUG(("CHANGEOVER Already Received\n"));
                    TCOC_Main_ANSI(MTP3_STM_TCOC,
                                    STM_TRIGGER_CHANGEOVER_ORDER,
                                    NULL, 0,
                                    linkSet, linkCode);
                }
                else
                {
                    MTP3_DEBUG(("EMERGENCY CHANGEOVER Already Received\n"));
                    TCOC_Main_ANSI(MTP3_STM_TCOC, 
                                    STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                    NULL, 0,
                                    linkSet, linkCode);
                }
            }

        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_5)
        {
            ln->changeoverState = CHANGEOVER_WAIT_6;

            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM,
                                                        SNMM_HC1_COA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for COA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
       
            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);
             MTP3_DEBUG(("CHANGEOVER_WAIT_5 --> CHANGEOVER_WAIT_6 COA SENT\n"));
            

            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len, /* Tmp RL */
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_8)
        {
            MTP3_DEBUG(("CHANGEOVER_WAIT_8\n"));
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM, 
                                                        SNMM_HC1_COA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for COA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED) /* FSNCAvailable */
            {
                /* Neet to send FSNC to L2 to retrieve buffers */

                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_RETRIEVE_MSGS,
                                   (ITS_OCTET *)&ln->remoteBSN, 
                                   sizeof(ITS_UINT));
            
                /* mark link unavailable */
                ln->stFlags = LINK_IS_UNAVAILABLE;
            
                ln->changeoverState = CHANGEOVER_RETRIEVING;
            }
            else
            {
                /*
                 * do this first to avoid circular transmission.
                 */
                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               NULL, 0,
                               linkSet, linkCode);
            
                /*
                 * send buffered messages on alternative links
                 *
                 * SLS unshifting *is* required here.  It's not terribly
                 * awful, though.
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                    fetched = &evRec.event;

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                    MTP3_RL_SET_SLS(slsUnshift->label, sls);

                    HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
            
                TLAC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
                TSRC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
            }
        }
        break;
        
    case STM_TRIGGER_BSNT_NOT_RETRIEVABLE:      /* from L2 */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* cancel local BSNT retrieved */
            ln->stFlags &= (~LINK_LOCAL_BSNT_RETRIEVED);
            ln->changeoverState = CHANGEOVER_WAIT_FOR_ACK;
            
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                        SNMM_HC1_ECO);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                            &firstMatch, &lastMatch,
                                            &whichLinkCode,
                                            ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for ECO Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);

            MTP3_Alarm_ANSI(2515, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",
                             tls,tlc);

            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            /* start T2 */
            tc.timerId = MTP3_T2;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t2 = TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                        __ansi_t2 * USEC_PER_MILLISEC,
                                        &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("BSNTRet NOT POSSIBLE CHANGEOVER_WAIT_2-->> CHANGEOVER_WAIT_FOR_ACK ECO Sent T2\n"));
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_5)
        {
            ln->changeoverState = CHANGEOVER_WAIT_6;

            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                        SNMM_HC1_ECA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);

            ITS_EVENT_TERM(&ev);

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);

            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len, /* Tmp RL */
                           linkSet, linkCode);
            MTP3_DEBUG(("BSNTRet NOT POSSIBLE CHANGEOVER_WAIT_5-->> CHANGEOVER_WAIT_6 ECA Sent T2\n"));

            ITS_EVENT_TERM(&ev);
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_8)
        {
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                        SNMM_HC1_ECA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ANSI,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_ANSI(2482, __FILE__, __LINE__, "%08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED) /* FSNCAvailable */
            {
                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_RETRIEVE_MSGS, 
                                   (ITS_OCTET *)&ln->remoteBSN, 
                                   sizeof(ITS_UINT));

            
                /* mark link unavailable */
                ln->stFlags |= LINK_IS_UNAVAILABLE;
            
                ln->changeoverState = CHANGEOVER_RETRIEVING;
            }
            else
            {
                /*
                 * do this first to avoid circular transmission.
                 */
                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               NULL, 0,
                               linkSet, linkCode);
            
                /*
                 * send buffered messages on alternative links
                 *
                 * SLS unshifting *is* required here.  It's not terribly
                 * awful, though.
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                    fetched = &evRec.event;

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                    MTP3_RL_SET_SLS(slsUnshift->label, sls);

                    HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
            
                TLAC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
                TSRC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
            }
        }
        break;
        
    case STM_TRIGGER_T1:                        /* from timer control */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_WAIT_7)
        {
            /*
             * do this first to avoid circular transmission.
             */
            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {

                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                MTP3_RL_SET_SLS(slsUnshift->label, sls);

                HMRT_Main_ANSI(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            ln->changeoverState = CHANGEOVER_IDLE;
            MTP3_ERROR(("T1 Expires CHANGEOVER_WAIT_7 ->>CHANGEOVER_IDLE \n"));

            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            /* TSRC wants destination information */

            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);

            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        break;
        
    case STM_TRIGGER_CHANGEOVER_ACK:            /* from HMDT */

        /* Get correct Linkset and Link using opc dpc and slc in SNMM */
        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No COA message in trigger \
                STM_TRIGGER_CHANGEOVER_ACK"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                                    sizeof(ITS_OCTET));

        /* Linkset */
        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            return (ITS_EINVALIDARGS);
        }

        /* Link */
        linkCode = SNMM_CHANGEOVER_GET_SLC_ANSI(snmm_ptr->data.changeOver);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for COA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);

        if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* stop T2 */
               /*********CANCEL TIMER ISSUE SANDEEP**********/
            if (ln->id != 20002) 
               {
                /*********CANCEL TIMER ISSUE SANDEEP**********/
                MTP3_DEBUG(("MTP3 CANCEL T2 Timer SERIAL [%d]\n",ln->t2));
                TIMERS_CancelSharedTimer(ln->t2);
                ln->t2 = TIMER_BAD_SERIAL;
                /*********CANCEL TIMER ISSUE SANDEEP**********/
               }
               /*********CANCEL TIMER ISSUE SANDEEP**********/
            
            /* Increament the peg for ChangeOver */
            //PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
            MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_RETRIEVE_MSGS, 
                               (ITS_OCTET *)&ln->remoteBSN, sizeof(ITS_UINT));
            
            /* mark link unavailable */
            ln->stFlags |= LINK_IS_UNAVAILABLE;
            
            ln->changeoverState = CHANGEOVER_RETRIEVING;
					MTP3_DEBUG(("COA REC CHANGEOVER_WAIT_FOR_ACK -->> CHANGEOVER_RETRIEVING T2 Stop L3_L2_RETRIEVE_MSGS Sent \n", linkSet, linkCode));
        }
        break;
        
    case STM_TRIGGER_EMERG_CHANGEOVER_ACK:      /* from HMDT */

        /* Get correct Linkset and Link using opc dpc and slc in SNMM */
        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No ECA message in trigger \
                STM_TRIGGER_EMERG_CHANGEOVER_ACK"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) + 
                                                    sizeof(ITS_OCTET));

        /* Linkset */
        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            return (ITS_EINVALIDARGS);
        }

        /* Link */
        linkCode = SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI
                        (snmm_ptr->data.emergencyChangeOver);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }
        /* Increament Link Peg for ECA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);

        if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* stop T2 */
            MTP3_DEBUG(("MTP3 CANCEL T2 Timer SERIAL [%d]\n",ln->t2));
            /*********CANCEL TIMER ISSUE SANDEEP**********/
            if (ln->id != 20002) 
               {
                /*********CANCEL TIMER ISSUE SANDEEP**********/
                TIMERS_CancelSharedTimer(ln->t2);
                ln->t2 = TIMER_BAD_SERIAL;
               }
            ln->changeoverState = CHANGEOVER_IDLE;

            /* Increament the peg for ChangeOver */
            //PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEOVER);

            LSAC_Main_ANSI(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * do this first to avoid circular transmission.
             */
            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                MTP3_RL_SET_SLS(slsUnshift->label, sls);

                HMRT_Main_ANSI(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;
        
    case STM_TRIGGER_RETRIEVED_MSGS:            /* from L2 */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, len + 3 * sizeof(ITS_OCTET) );

            L2_MSG_TYPE(&ev) = L3_L2_DATA;
            L2_LINK_SET(&ev) = linkSet;
            L2_LINK_CODE(&ev) = linkCode;

            if (len)
            {
                memcpy(L2_LINK_DATA(&ev), sif, len);
            }

            /* save retrieved messages */
            return DSMQUEUE_Enqueue(ln->rtrvBuf, ev);
        }
        break;
        
    case STM_TRIGGER_RETRIEVAL_COMPLETE:        /* from L2 */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            if (ln->stFlags & LINK_IS_UNAVAILABLE) /* LinkUnavailable */
            {
                MTP3_ERROR(("STM_TRIGGER_RETRIEVAL_COMPLETE LINK_IS_UNAVAILABLE \n"));
                /* send retrieved messages on alternate link */
                while (DSMQUEUE_Dequeue(ln->rtrvBuf, &fetched) == ITS_SUCCESS)
                {

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                    MTP3_RL_SET_SLS(slsUnshift->label, sls);

                    HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_Free(fetched);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
                MTP3_DEBUG(("RETRIVIVAL COMPLETE CHANGEOVER_RETRIEVING->CHANGEOVER_IDLE\n"));
                
                LSAC_Main_ANSI(MTP3_STM_TCOC,
                               SLM_TRIGGER_STM_READY,
                               NULL, 0,
                               linkSet, linkCode);

                /*
                 * do this first to avoid circular transmission.
                 */
                HMRT_Main_ANSI(MTP3_STM_TCOC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               NULL, 0,
                               linkSet, linkCode);
            
                /*
                 * send buffered messages on alternative links
                 *
                 * SLS unshifting *is* required here.  It's not terribly
                 * awful, though.
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                    fetched = &evRec.event;

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                    MTP3_RL_SET_SLS(slsUnshift->label, sls);

                    HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }
            
                TLAC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
                TSRC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                /* these tasks should be carried out in the order shown */
                /* send retrieved messages on restored link */
                while (DSMQUEUE_Dequeue(ln->rtrvBuf, &fetched) == ITS_SUCCESS)
                {

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                    MTP3_RL_SET_SLS(slsUnshift->label, sls);

                    HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_Free(fetched);
                }

                /*
                 * NOTE: this order is backwards, but necessary.  MTP2_SendData
                 * examines the qPut variable to determine if it should queue
                 * or transmit the messages.
                 *
                 * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
                 * this.  The second platform might transmit while we are.  This
                 * could be avoided by not committing the link info until the
                 * queue is cleared.
                 */

                /* stop buffering messages on restored link */
                /*ln->qPut = ITS_FALSE;*/
                LINK_SetLinkQPut(ln, ITS_FALSE);

                /*
                 * send buffered messages on restored link
                 *
                 * NOTE: SLS unshifting not required here, as this is
                 * recovery (link bounce).
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                    fetched = &evRec.event;

                    MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                       L2_LINK_CODE(fetched),
                                       L2_MSG_TYPE(fetched),
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)));

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }
                
                ln->changeoverState = CHANGEOVER_IDLE;

                TLAC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               linkSet, linkCode);
                
                TSRC_Main_ANSI(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               linkSet, linkCode);
                
            }
        }
        break;
        
    case STM_TRIGGER_RETRIEVAL_NOT_POSSIBLE:    /* from L2 */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            ln->changeoverState = CHANGEOVER_IDLE;

            LSAC_Main_ANSI(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * do this first to avoid circular transmission.
             */
            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                MTP3_RL_SET_SLS(slsUnshift->label, sls);

                HMRT_Main_ANSI(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;
        
    case STM_TRIGGER_T2:                        /* from timer control */
          if(ln==NULL)
          {
            MTP3_DEBUG(("TCOC:LINK NULL\n"));

            return (ITS_EINVALIDARGS);
          } 
        if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            ln->changeoverState = CHANGEOVER_IDLE;

            LSAC_Main_ANSI(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * have to do this first, otherwise we send to ourselves.
             */
            HMRT_Main_ANSI(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                MTP3_RL_SET_SLS(slsUnshift->label, sls);

                HMRT_Main_ANSI(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            TLAC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_ANSI(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}

/*
 * sequence number wrapping.
 */
#define MAX_SEQNO   0xFFFFFFFFU
#define IS_SEQNO_WRAPPED(a, b)                      \
    ((((a) > (b)) && (((a) - (b)) < ((MAX_SEQNO) >> 1))) || \
     (((b) > (a)) && (((b) - (a)) > ((MAX_SEQNO) >> 1))))

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
static int
InsertEvent(QUEUE_Entry *prev, QUEUE_Entry *next, QUEUE_Entry *item)
{
    MTP3_EventRec here, there, before;

    /* emtpy list? */
    if (prev == NULL && next == NULL)
    {
        return (ITS_TRUE);
    }

    /*
     * less than head?
     */
    if (prev == NULL)
    {
        here  = ItsEventToMTP3EventRec_ANSI(item->data);
        there = ItsEventToMTP3EventRec_ANSI(next->data);

        /*
         * sequence number can wrap, so be careful
         */
        if (IS_SEQNO_WRAPPED(here.seqNo, there.seqNo))
        {
            /*
             * it wrapped, so even though here->seqNo < there->seqNo,
             * we have to consider it as greater.
             */
            return (ITS_FALSE);
        }
        else if (here.seqNo < there.seqNo)
        {
            return (ITS_TRUE);
        }

        /* default is it's greater */
        return (ITS_FALSE);
    }

    /*
     * at end of list?  Always insert
     */
    if (next == NULL)
    {
        return (ITS_TRUE);
    }

    /*
     * hard case.  Middle of list.
     */
    here = ItsEventToMTP3EventRec_ANSI(item->data);
    there = ItsEventToMTP3EventRec_ANSI(next->data);
    before = ItsEventToMTP3EventRec_ANSI(prev->data);

    /*
     * we still have to check wrappage.
     */
    if (IS_SEQNO_WRAPPED(here.seqNo, there.seqNo))
    {
        /* insert after */
        return (ITS_FALSE);
    }

    /*
     * weird case.  This may fall into a gap between
     * UINT_MAX and low numbers.  We know that next is ok in this case,
     * or we would have tripped the condition above.
     */
    if (IS_SEQNO_WRAPPED(here.seqNo, before.seqNo))
    {
        /*
         * now, or later
         */
        if (here.seqNo < there.seqNo)
        {
            return (ITS_TRUE);
        }

        /* no, keep going. */
        return (ITS_FALSE);
    }

    /* normal case.  Range check. */
    if (here.seqNo > before.seqNo && here.seqNo < there.seqNo)
    {
        return (ITS_TRUE);
    }

    /* give up */
    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert a DSMQUEUE_Entry to a MTP3_EventRec
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
static MTP3_EventRec 
DsmQueueEntryToMTP3EventRec_ANSI(DSMQUEUE_Entry entry)
{
    MTP3_EventRec evRec;

    ITS_UINT seqNoSize = sizeof(evRec.seqNo);

    ITS_EVENT_INIT(&evRec.event, entry.src, entry.len - seqNoSize);

    memcpy(&evRec.seqNo, entry.data, seqNoSize);
    memcpy(evRec.event.data, &entry.data[seqNoSize], entry.len - seqNoSize);

    return evRec;

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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for 64 link support 
 *                     ID::D0020                   and load balancing 
 ****************************************************************************/
static void
MoveTraffic(SS7_LinkSetPtr ls, ITS_OCTET linkCode)
{
    ITS_UINT i, idx;
    SS7_LinkPtr ln, nln;
    DSMQUEUE_Entry *ent; 
    MTP3_EventRec evRec;
    MTP3_HEADER_ANSI *mtp3;
    ITS_OCTET linkSel, sls;

    /*
     * find the link index
     */
    nln = NULL;
    for (idx = 0; idx < ls->numLinks; idx++)
    {
        if (ls->links[idx]->linkCode == linkCode)
        {
            nln = ls->links[idx];
            break;
        }
    }

    /*
     * if the link isn't found, ditch
     */
    if (idx == ls->numLinks || nln == NULL)
    {
        return;
    }

    /*
     * for each link
     */
    for (i = 0; i < ls->numLinks; i++)
    {
        ln = ls->links[i];

        /*
         * if the linkCode is not self
         */
        if (ls->links[i]->linkCode != linkCode)
        {
            ITS_UINT i;
            ITS_UINT msgCount = ln->cocbBuf->numEntries;
            /*
             * for each message in the buffer
             */
            for (i = 0, ent = &ln->cocbBuf->entries[ln->cocbBuf->firstEntry];
                 ent != NULL && i < msgCount ;
                 i++)
            {
                evRec = DsmQueueEntryToMTP3EventRec_ANSI(*ent);

                mtp3 = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(&evRec.event) +
                                            sizeof(ITS_OCTET));
                sls = MTP3_RL_GET_SLS(mtp3->label) & MTP3_NIC_MASK;

                /*
                 * unrotate it to retrieve original value
                 */
                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);

                /*
                 * rotate again to find index.  Key point; we don't have
                 * to change the SLS value in the message, it is already
                 * right.  We had to do this unrotate/rotate to find the
                 * link offset.
                 */

                /* commenting the  ROUTE_SLSRotate API , because we are not 
                 * having required parameters SS7_Destination, numlinkSet,
                 * firstMatch. We will use sls MOD (number of links) to get 
                 * the link offset.
                 */

                /* ROUTE_SLSRotate(!ls->is5Bit, sls, &dummy, &linkSel); */

                linkSel = sls % ls->numLinks;

                /*
                 * if the codeMap has this sls belonging to the changing
                 * back link
                 */
                if (ls->codeMap[linkSel] == idx)
                {
                    /*
                     * move it to the new link
                     */
                    DSMQUEUE_Unlink(ln->cocbBuf, ent);
                    DSMQUEUE_Insert(nln->cocbBuf, InsertEvent,
                                MTP3EventRecToItsEvent_ANSI(evRec) );

                    ITS_EVENT_TERM(&evRec.event);

                }
                else
                {
                    /*
                     * let's compare with the next entry
                     */
                    ent = (ent == &ln->cocbBuf->entries[
                                   ln->cocbBuf->key.maxQueueSize-1]) ?
                    ln->cocbBuf->entries                             :
                    ent + 1;
                }

               

               ITS_EVENT_TERM(&evRec.event);

            }
        }
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
TCBC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{    
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    MTP3_TimerContext tc;
    ITS_UINT pc1;
    ITS_OCTET ni;
    MTP3_HEADER_ANSI omtp3;
    SNMM_MESSAGE snmm;
    SNMM_MESSAGE* isnmm;
    ITS_EVENT ev, *fetched, *cocbEv;
    MTP3_EventRec evRec;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;
    ITS_OCTET changeBackCode, tls, tlc;

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TCBC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* wants a link, I think */
    switch (trigger)
    {
    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_IDLE)
        {
            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            
            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);
                        
            ln->changebackState = CHANGEBACK_WAIT_FOR_DATA;
            
            TSRC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        break;

    case STM_TRIGGER_CHANGEBACK_DECL:           /* from HMDT */
        tls = linkSet;
        tlc = linkCode;

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        isnmm = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_CHANGEBACK_GET_SLC_ANSI(isnmm->data.changeBack);

        MTP3_Alarm_ANSI(2511, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CBD Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEBACK);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_CHANGE_BACK);

        if (ln->changebackState == CHANGEBACK_IDLE ||
            ln->changebackState == CHANGEBACK_TIME_CONTROLLED_DIVERT ||
            ln->changebackState == CHANGEBACK_FIRST_ATTEMPT ||
            ln->changebackState == CHANGEBACK_SECOND_ATTEMPT)
        {
            /* Extract the CB Code */
            ITS_C_ASSERT(sif != NULL);
            isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                         sizeof(ITS_OCTET)];
            changeBackCode = SNMM_CHANGEBACK_GET_CODE_ANSI(isnmm->data.changeBack);

            /* Build SNMM changeback ACK */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_CHM_ANSI);
            SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CBA_ANSI);

            SNMM_CHANGEBACK_SET_SLC_ANSI(snmm.data.changeBack, ln->linkCode);
            SNMM_CHANGEBACK_SET_CODE_ANSI(snmm.data.changeBack, changeBackCode);
            
            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

            /* Increament Link Peg for CBA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);

            HMRT_Main_ANSI(MTP3_STM_TCBC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
        }
        break;

    case STM_TRIGGER_CHANGEBACK_ACK:            /* from HMDT */
        tls = linkSet;
        tlc = linkCode;

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        isnmm = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_CHANGEBACK_GET_SLC_ANSI(isnmm->data.changeBack);
        changeBackCode = SNMM_CHANGEBACK_GET_CODE_ANSI(isnmm->data.changeBack);

        /* this is invariant in our stack */
        tlc = changeBackCode;

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CBA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);

        ln->gotCBA |= (1 << tlc);

        if (ln->changebackState == CHANGEBACK_FIRST_ATTEMPT &&
            ln->gotCBA == ln->needCBA)
        {
            /* stop T4 */
            MTP3_DEBUG(("MTP3 CANCEL T4 Timer SERIAL [%d]\n",ln->t4));
            /*********CANCEL TIMER ISSUE SANDEEP**********/
            if(ln->id != 20002)
             {
               TIMERS_CancelSharedTimer(ln->t4);
               ln->t4 = TIMER_BAD_SERIAL;
             }
            /*********CANCEL TIMER ISSUE SANDEEP**********/

            /* Increament the peg for ChangeBack */
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEBACK);

            /* reset masks */
            ln->gotCBA = ln->needCBA = 0;

            /*
             * I love this paragraph: 4.3.2:
             *
             * "In the case that multiple links in the link set are unavailable,
             * traffic in addition to that for which the newly available link
             * is the normal one may be transferred to the newly available link
             * in order to distribute traffic among available links as evenly
             * as possible. If this option is implemented, implementation-
             * dependent safeguards must be employed to prevent missequencing
             * or excessive delay of messages when additional links within the
             * link set become available while changeback is still in progress."
             *
             * I had to go and get ambitious.
             *
             * This requires deep thought.  Consider this case:
             * 1. Changeback is in progress, we buffer messages for this link
             * based on SLS map recomputation.
             * 2. Another link becomes available.  Recompute the SLS map again.
             * 3. The second link gets the CBA before the first link.
             *
             * Now, consider.  *Unless* the SLS map computation is such that
             * _no_ SLS value transferred to the second link was previously
             * transferred to the first link, the possibility for missequencing
             * exists.
             *
             * This means that the algorithm (as earlier thought) MUST NOT move
             * SLS values for changing back links until the changeback occurs.
             *
             ****************************************************************
             *
             * Here's an approach:
             *
             * 1. When a link starts changeback, balance the SLS map with
             * this link included.
             * 2. If another link starts changeback before the procedure
             * finishes, rebalance the map.
             * 3. In case 2, if any SLS code represented the link referred
             * to in 1, walk the CB buffer for that link, looking for matching
             * SLS values.  If found, move the message to (2).
             * 4. Since we'll be moving messages from possibly multiple sources,
             * we'll need a global sequence number (can you say TSN).  When
             * performing 3, the CB buffer will need sorting by this sequence
             * number.
             * 5. If changeover completes while any of this is in progress,
             * we'll have to distribute the SLS values of the failed link
             * among all links, even if they are changing back.
             *
             ****************************************************************
             *
             * restart traffic on link buffered messages first
             *
             * ROTATION COMMENT
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_ANSI(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        else if (ln->changebackState == CHANGEBACK_SECOND_ATTEMPT &&
                 ln->gotCBA == ln->needCBA)
        {
            /* stop T5 */
              MTP3_DEBUG(("MTP3 CANCEL T5 Timer SERIAL [%d]\n",ln->t5));
            /*********CANCEL TIMER ISSUE SANDEEP**********/
            if(ln->id != 20002)
             {
               TIMERS_CancelSharedTimer(ln->t5);
               ln->t5 = TIMER_BAD_SERIAL;
             }
            /*********CANCEL TIMER ISSUE SANDEEP**********/

            /* Increament the peg for ChangeBack */
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_CHANGEBACK);

            /* reset masks */
            ln->needCBA = ln->gotCBA = 0;

            /*
             * restart traffic on link buffered messages first
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_ANSI(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_DATA:      /* from TSRC */
        tls = sif[2 * sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET)];
        tlc = sif[2 * sizeof(MTP3_HEADER_ANSI) + 2 * sizeof(ITS_OCTET)];

        ln = LINK_FindLink(tls, tlc);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", tls, tlc));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(tls);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", tls));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_WAIT_FOR_DATA)
        {
            if (!RoutingChanged(sif, len, linkSet, linkCode))
            {
                MTP3_DEBUG(("TCBC_Main: Routing didn't change for %d %d: %d %d\n",
                            tls, tlc, linkSet, linkCode));

                ln->changebackState = CHANGEBACK_IDLE;

                TLAC_Main_ANSI(MTP3_STM_TCBC,
                               STM_TRIGGER_CHANGEBACK_TERMINATED,
                               NULL, 0,
                               tls, tlc);

                TSRC_Main_ANSI(MTP3_STM_TCBC,
                               STM_TRIGGER_PROCEDURE_TERMINATED,
                               sif, len,
                               tls, tlc);
            }
            else
            {
                MTP3_DEBUG(("TCBC_Main: Routing did change for %d %d: %d %d\n",
                            tls, tlc, linkSet, linkCode));

                /* buffer concerned messages in changeback buffer */
                /* reset the SLS map */
                LINKSET_AddActiveLink(ls, ln->linkCode);

                /* move traffic from other CO/CB buffers to this link */
                MoveTraffic(ls, ln->linkCode);

                /* NOTE this tells SMH to queue instead of transmit */
                /*ln->qPut = ITS_TRUE;*/
                LINK_SetLinkQPut(ln, ITS_TRUE);

                pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

                if (/*RemoteSPAccessible(pc1, ni)*/linkSet == tls)
                {
                    int nextras = (int)len - (int)(2 * sizeof(MTP3_HEADER_ANSI) +
                                                   3 * sizeof(ITS_OCTET));
                    ITS_OCTET *extras = &sif[2 * sizeof(MTP3_HEADER_ANSI) +
                                             3 * sizeof(ITS_OCTET)];
                    int i;
                    SS7_LinkPtr tln;

                    MTP3_DEBUG(("TCBC_Main: RemoteSPAccessible for %d %d\n", tls, tlc));

                    ITS_C_ASSERT(nextras >= 0);

                    /* Build SNMM changeback for each available link */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_CHM_ANSI);
                    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CBD_ANSI);

                    /*
                     * we did an alternate route request, but we're the only
                     * link available.
                     * FIXME: What if the link drops then immediately comes
                     * back.  This should go into time-controlled but doesn't.
                     * Think about how this really happens.
                     * This seems to be when there is no alternate link.
                     */
                    if (linkSet == ITS_SS7_DEFAULT_LINK_SET &&
                        linkCode == ITS_SS7_DEFAULT_LINK_CODE)
                    {
                        return (ITS_SUCCESS);
                    }

                    /*
                     * In this case, the SP MUST be accessible, so linkSet/linkCode
                     * MUST be valid
                     */
                    tln = LINK_FindLink(linkSet, linkCode);
                     if ( tln == NULL)
                    {
                       MTP3_Alarm_ANSI(2123, __FILE__, __LINE__,
                                       "Link %x:%x not found", linkSet,linkCode);
                       ITS_C_ASSERT(tln != NULL);
                    }

                    /*
                     * Massive simplification.  The changeback code is
                     * simply the link this message should be sent on.  Ehm.  Right?
                     */
                    MTP3_ERROR(("ln->linkCode %d linkCode %d\n",ln->linkCode,linkCode));
                    SNMM_CHANGEBACK_SET_SLC_ANSI(snmm.data.changeBack, ln->linkCode);
                    SNMM_CHANGEBACK_SET_CODE_ANSI(snmm.data.changeBack, linkCode);
                    

                    /* update management info */
                    ln->needCBA |= 1 << linkCode;
                    ln->cbLinkSet = linkSet;

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

#if 1
/* To fix the problem reported for not sending second CBD if first 
   CBD is not acknowledged.
*/ 
                    /* Increament Link Peg for CBD Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);

                    MTP3_Alarm_ANSI(2514, __FILE__, __LINE__,
                                    "linkset:linkcode %x:%x",linkSet,linkCode);

                    HMRT_Main_ANSI(MTP3_STM_TCBC,
                                   SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                   ev.data, ev.len,
                                   linkSet, linkCode);
#endif

                    ITS_EVENT_TERM(&ev);

                    /*
                     * send messages on other links
                     */
                    MTP3_ERROR(("nextras = %d ",nextras));
                    for (i = 0; i < nextras; i++)
                    {
                        /* Build SNMM changeback for each available link */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_CHM_ANSI);
                        SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CBD_ANSI);

                        /*
                         * In this case, the SP MUST be accessible, so linkSet/linkCode
                         * MUST be valid
                         */
                        tln = LINK_FindLink(linkSet, extras[i]);
                    if ( tln == NULL)
                    {

                        ITS_C_ASSERT(tln != NULL);
                    }

                        SNMM_CHANGEBACK_SET_SLC_ANSI(snmm.data.changeBack, ln->linkCode);
                        SNMM_CHANGEBACK_SET_CODE_ANSI(snmm.data.changeBack, extras[i]);

                        /* update management info */
                        ln->needCBA |= 1 << extras[i];

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                        SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                        /* Increament Link Peg for CBD Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);

                        MTP3_Alarm_ANSI(2514, __FILE__, __LINE__,
                                    "linkset:linkcode %x:%x",linkSet,extras[i]);

                        HMRT_Main_ANSI(MTP3_STM_TCBC,
                                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                       ev.data, ev.len,
                                       linkSet, extras[i]);

                        ITS_EVENT_TERM(&ev);
                    }

                    /* start T4 */
                    tc.timerId = MTP3_T4;
                    tc.data.linkInfo.linkSet = tls;
                    tc.data.linkInfo.linkCode = tlc;

                    ln->t4 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t4 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ln->changebackState = CHANGEBACK_FIRST_ATTEMPT;
                }
                else
                {
                    MTP3_DEBUG(("TCBC_Main: RemoteSPNotAccessible for %d %d\n", tls, tlc));

                    /* start T3 */
                    tc.timerId = MTP3_T3;
                    tc.data.linkInfo.linkSet = tls;
                    tc.data.linkInfo.linkCode = tlc;

                    ln->t3 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t3 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ln->changebackState = CHANGEBACK_TIME_CONTROLLED_DIVERT;
                }
            }
        }
        else
        {
            MTP3_DEBUG(("TCBC_Main: Bad state for %d %d\n",
                        tls, tlc));

            MTP3_Alarm_ANSI(2487, __FILE__, __LINE__, 
                            "Bad state detected for %d %d",tls, tlc);
        }
        break;

    case STM_TRIGGER_T3:                        /* from timer control */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_TIME_CONTROLLED_DIVERT)
        {
            /* reset masks */
            ln->needCBA = ln->gotCBA = 0;

            /*
             * restart traffic on link buffered messages first
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_ANSI(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        break;

    case STM_TRIGGER_T4:                        /* from timer control */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_FIRST_ATTEMPT)
        {
            SS7_LinkPtr tln;
            ITS_USHORT i;

            for (i = 0; i < MAX_LINKS; i++)
            {
                if ((ln->needCBA & (1 << i)) && !(ln->gotCBA & (1 << i)))
                {
                    /* Build SNMM changeback */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_CHM_ANSI);
                    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CBD_ANSI);

                    tln = LINK_FindLink(ln->cbLinkSet, (ITS_OCTET)i);
                    ITS_C_ASSERT(tln != NULL);

                    SNMM_CHANGEBACK_SET_SLC_ANSI(snmm.data.changeBack, ln->linkCode);
                    SNMM_CHANGEBACK_SET_CODE_ANSI(snmm.data.changeBack, i);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CBD Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);

                    MTP3_Alarm_ANSI(2514, __FILE__, __LINE__,
                                   "linkset:linkcode %x:%x",ln->cbLinkSet,(ITS_OCTET)i);

                    HMRT_Main_ANSI(MTP3_STM_TCBC,
                                   SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                   ev.data, ev.len,
                                   ln->cbLinkSet, (ITS_OCTET)i);

                    ITS_EVENT_TERM(&ev);
                }
            }

            /* start T5 */
            tc.timerId = MTP3_T5;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t5 =
                TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_t5 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            ln->changebackState = CHANGEBACK_SECOND_ATTEMPT;
        }
        else if(ln->changebackState == CHANGEBACK_IDLE)
             {
              MTP3_DEBUG(("MTP3: CBA is received on peer node No need to start T5  for ls|lc %d|%d \n",linkSet,linkCode));
             }
        break;

    case STM_TRIGGER_T5:                        /* from timer control */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_SECOND_ATTEMPT)
        {
            /* reset masks */
            ln->needCBA = ln->gotCBA = 0;

            /*
             * restart traffic on link buffered messages first
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_ANSI(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_ANSI(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_ANSI(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_ANSI(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
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
int
TFRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1], *nmtp3;
    ITS_UINT pc, oldPC;
    ITS_OCTET ni, oldNI, oldLS, oldLC;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri, *newri;

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TFRC, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    case STM_TRIGGER_ROUTE_UNAVAILABLE:         /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2489, __FILE__, __LINE__, "%08x",pc);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->forcedState == FORCE_REROUTING_IDLE)
        {
            /*
             * Buffer concerned traffic in forced rerouting buffer
             *
             * NOTE: This is irrelevent in our implementation.  Additional
             * messages for this destination are piling up in our input
             * queue.
             */
            ri->forcedState = FORCE_REROUTING_WAIT_1;
            
            TSRC_Main_ANSI(MTP3_STM_TFRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           sif, len,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_DATA:      /* from TSRC */

        /* new route */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* get the *old* RL */
        nmtp3 = (MTP3_HEADER_ANSI *)&sif[sizeof(ITS_OCTET) +
                                         sizeof(MTP3_HEADER_ANSI)];
        oldLS = sif[sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER_ANSI)];
        oldLC = sif[2 * sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER_ANSI)];

        oldPC = MTP3_RL_GET_DPC_VALUE(nmtp3->label);
        oldNI = MTP3_HDR_GET_SIO(*nmtp3) & MTP3_NIC_MASK;

        /* old route rec */
        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, oldPC,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 oldNI, oldLS, oldLC,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_ANSI(2489, __FILE__, __LINE__, "%08x",pc);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->forcedState == FORCE_REROUTING_WAIT_1)
        {
            MTP3_HEADER_ANSI omtp3;
            ITS_EVENT ev;

            if (RoutingChanged(sif, len, linkSet, linkCode))
            {
                /* new route rec */
                if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                         REMOTE_ROUTE, ROUTE_DPC_NI,
                                                         FAMILY_ANSI,
                                                         ni, linkSet, linkCode,
                                                         ITS_SS7_DEFAULT_LINK_PRI,
                                                         ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
                {
                    MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

                    MTP3_Alarm_ANSI(2489, __FILE__, __LINE__, "%08x",pc);

                    return (ret);
                }

                if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

                    return (ITS_EINVALIDARGS);
                }

                newri = ent->entries[whichEntry];

                if (!newri->isAllowed)
                {
                    /* 
                     * Discard messages in forced rerouting buffer
                     * NOTE: This will happen automatically
                     */
                }
                else
                {
                    /*
                     * start straffic on newly available route, buffer first.
                     * NOTE: This will happen automatically
                     */
                }

                HMRT_Main_ANSI(MTP3_STM_TFRC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               sif, len,
                               linkSet, linkCode);
            }

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_HDR_SET_SIO(omtp3, oldNI);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, oldPC);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);

            TSRC_Main_ANSI(MTP3_STM_TFRC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           ev.data, ev.len,
                           oldLS, oldLC);

            RTAC_Main_ANSI(MTP3_STM_TFRC,
                           SRM_TRIGGER_FORCED_REROUTE_END,
                           ev.data, ev.len,
                           oldLS, oldLC);

            RTRC_Main_ANSI(MTP3_STM_TFRC,
                           SRM_TRIGGER_FORCED_REROUTE_END,
                           ev.data, ev.len,
                           oldLS, oldLC);

            ITS_EVENT_TERM(&ev);

            ri->forcedState = FORCE_REROUTING_IDLE;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
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
int
TCRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    MTP3_HEADER_ANSI *nmtp3, omtp3, *slsUnshift;
    MTP3_TimerContext tc;
    ITS_UINT pc, oldPC;
    ITS_OCTET ni, oldNI, oldLS, oldLC, sls;
    ITS_EVENT ev, *fetched;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri;
    SS7_LinkSetPtr ls;

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TCRC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* needs a point code to get a route? */    
    switch (trigger)
    {
    case STM_TRIGGER_ROUTE_RESTRICTED:      /* from TSRC */
    case STM_TRIGGER_ROUTE_AVAILABLE:       /* from RTAC, TSRC */
    case STM_TRIGGER_ROUTE_UNAVAILABLE:
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->controlledState == CONT_REROUTING_IDLE)
        {
            ri->controlledState = CONT_REROUTING_WAIT_1;

            TSRC_Main_ANSI(MTP3_STM_TCRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           sif, len,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_DATA: /* from TSRC */

        /* new route */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* get the *old* RL */
        nmtp3 = (MTP3_HEADER_ANSI *)&sif[sizeof(ITS_OCTET) +
                                         sizeof(MTP3_HEADER_ANSI)];
        oldLS = sif[sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER_ANSI)];
        oldLC = sif[2 * sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER_ANSI)];

        oldPC = MTP3_RL_GET_DPC_VALUE(nmtp3->label);
        oldNI = MTP3_HDR_GET_SIO(*nmtp3) & MTP3_NIC_MASK;

        /* old route rec */
        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, oldPC,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 oldNI, oldLS, oldLC,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        if (ri->controlledState == CONT_REROUTING_WAIT_1)
        {
            if (!RoutingChanged(sif, len, linkSet, linkCode))
            {
                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

                MTP3_HDR_SET_SIO(omtp3, oldNI);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, oldPC);

                MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                                 &omtp3, NULL, 0);

                TSRC_Main_ANSI(MTP3_STM_TCRC,
                               STM_TRIGGER_PROCEDURE_TERMINATED,
                               ev.data, ev.len,
                               oldLS, oldLC);

                RTPC_Main_ANSI(MTP3_STM_TCRC,
                               SRM_TRIGGER_CONTROLLED_REROUTE_END,
                               ev.data, ev.len,
                               oldLS, oldLC);

                ITS_EVENT_TERM(&ev);

                ri->controlledState = CONT_REROUTING_IDLE;
            }
            else
            {
                /*
                 * buffer concerned traffic in controlled rerouting buffer
                 * NOTE: This signals HMCG to queue instead of transmitting.
                 */
                ri->qPut = ITS_TRUE;

                /* start T6 */
                tc.timerId = MTP3_T6;
                tc.data.routeInfo.pointCode = oldPC;
                tc.data.routeInfo.linkSet = oldLS;
                tc.data.routeInfo.sio = oldNI;

                ri->t6 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t6 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ri->controlledState = CONT_REROUTING_WAIT_2;
            }
        }
        break;

    case STM_TRIGGER_T6:                    /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ANSI,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        ri->t6 = TIMER_BAD_SERIAL;

        /* stop buffering on this route */
        ri->qPut = ITS_FALSE;

        if (ri->controlledState == CONT_REROUTING_WAIT_2)
        {
            /*
             * start traffic on new route buffered messages first
             *
             * ROTATION COMMENT
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ri->crBuf, &fetched) == ITS_SUCCESS)
            {
                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                if ( ls == NULL)
                {
                    ITS_C_ASSERT(ls != NULL);
                }

                slsUnshift = (MTP3_HEADER_ANSI *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);
                MTP3_RL_SET_SLS(slsUnshift->label, sls);

                HMRT_Main_ANSI(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            HMRT_Main_ANSI(MTP3_STM_TCRC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           sif, len,
                           linkSet, linkCode);

            TSRC_Main_ANSI(MTP3_STM_TCRC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           sif, len,
                           linkSet, linkCode);

            RTPC_Main_ANSI(MTP3_STM_TCRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE_END,
                           sif, len,
                           linkSet, linkCode);

            RTAC_Main_ANSI(MTP3_STM_TCRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE_END,
                           sif, len,
                           linkSet, linkCode);

            RTRC_Main_ANSI(MTP3_STM_TCRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE_END,
                           sif, len,
                           linkSet, linkCode);

            ri->controlledState = CONT_REROUTING_IDLE;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
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
int
TSFC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3=NULL;
    SNMM_MESSAGE *snmm=NULL;
    MTP3_PAUSE_RESUME_ANSI pr;
    MTP3_STATUS_ANSI stat;
    ITS_UINT apc=0, opc=0, dpc=0;
    SS7_LinkSetPtr ls;
    ITS_EVENT ev;
    int ret;

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TSFC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* For MTP3 indications the Routing Label is build as follow:
     * OPC = The affected Destination
     * DPC = Local Point code                           
     */
    if (sif != NULL)
    {
        mtp3 = (MTP3_HEADER *)&sif[1];
        snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                              sizeof(ITS_OCTET)];
    

        /* For MTP3 indications the Routing Label is build as follow:
         * OPC = The affected Destination
         * DPC = Local Point code
         */
        opc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        if ( ( ls = LINKSET_FindLinkSet(linkSet) ) != NULL)
        {
            dpc = ls->lpc;
        }
    }

    /* this looks like it wants a point code, maybe a user part (for UPU) */
    switch (trigger)
    {
    case STM_TRIGGER_DEST_CONGESTION_STATUS:    /* from TRCC, RTCC, TSRC */
        /* Stop signalling traffic to concerned destination with msg
         * priority less than congestion status */
        /* Generate MTP3 status indication to each user part
         */
        MTP3_ERROR(("Callback for CONGESTION(STATUS) is called\n"));
        apc = SNMM_TRANSFER_CONTROL_GET_DEST_ANSI(snmm->data.transferControl);
        MTP3_PC_SET_VALUE(stat.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 
        stat.cause = MTP3_STATUS_CONGESTED;
        stat.congLevel = SNMM_TRANSFER_CONTROL_GET_STATUS_ANSI(snmm->data.transferControl);

        if ((ret = MTP3_Encode_ANSI(&ev, MTP3_MSG_STATUS, mtp3,
                                    (ITS_OCTET *)&stat, sizeof(stat))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_STATUS);

        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_CONGESTION);

        return CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_DEST_INACCESS:             /* from TSRC */
    case STM_TRIGGER_CLUST_INACCESS:            /* from TSRC */
        /* Stop signalling traffic to concerned destination */
        /* Generate MTP3 PAUSE indication to each user part */
        MTP3_ERROR(("Callback PAUSE is called\n"));
        apc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_PC_SET_VALUE(pr.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 

        if ((ret = MTP3_Encode_ANSI(&ev, MTP3_MSG_PAUSE, mtp3,
                                    (ITS_OCTET *)&pr, sizeof(pr))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_MSG_PAUSE); 

        /* Increament the peg for Adjecent SP UNACCESIBLE*/
        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);

        /* Increament the peg for Route Set Unavailable */
        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE);

        MTP3_Alarm_ANSI(2401, __FILE__, __LINE__,
                        "affected point code %x",apc);

        return CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_DEST_ACCESS:               /* from TSRC */
    case STM_TRIGGER_CLUST_ACCESS:              /* from TSRC */
        /* Start signalling traffic to concerned destination */
        /* Generate MTP3 RESUME indication to each user part */
        MTP3_ERROR(("Callback RESUME is called\n"));
        apc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_PC_SET_VALUE(pr.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 

        if ((ret = MTP3_Encode_ANSI(&ev, MTP3_MSG_RESUME, mtp3,
                                    (ITS_OCTET *)&pr, sizeof(pr))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_MSG_RESUME);

        MTP3_Alarm_ANSI(2402, __FILE__, __LINE__,
                        "affected point code %x",apc);

        return CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_UPU:                       /* from RTCC */
        /* Build a MTP3_STATUS message and send to all user parts */
        apc = SNMM_USER_PART_UNAVAIL_GET_DEST_ANSI
               (snmm->data.userPartUnavailable);

        MTP3_PC_SET_VALUE(stat.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 

        if (SNMM_USER_PART_UNAVAIL_GET_CAUSE_ANSI(
                   snmm->data.userPartUnavailable) == SNMM_UPU_CAUSE_INACCESS)
        {
            stat.cause = MTP3_STATUS_UPU_INACCESS;
        }
        else
        {
            stat.cause = MTP3_STATUS_UPU_UNEQUIP;
        }

        stat.congLevel = 0;

        if ((ret = MTP3_Encode_ANSI(&ev, MTP3_MSG_STATUS, mtp3,
                                    (ITS_OCTET *)&stat, sizeof(stat))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_MSG_STATUS);

        return CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_RESTART_BEGIN:             /* from TPRC */
        /* The SDL says send a restart indication to L4.  What's the point. */
        break;

    case STM_TRIGGER_RESTART_END:               /* from TPRC */
        /* The SDL says send a restart end indication to L4.  What's the point */
        /* newer SDL says send a resume for all reachable destinations if in
         * idle state. */
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
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
static ITS_BOOLEAN
FullRestartNeeded()
{
    MTP3_TimerContext tc;
 
    if (FullRestartNeeded_ANSI())
    {
        MTP3_DEBUG(("T27 Have Started\n"));
        tc.timerId = MTP3_T27;
        MTP3_ERROR(("T27 timer Started \n")); 

        t27 =
            TIMERS_StartSharedTimer(ITS_MTP3_ANSI_SRC,
                              __ansi_t27 * MILLISEC_PER_SEC,
                              &tc, sizeof(MTP3_TimerContext));
    }

    return (FullRestartNeeded_ANSI());
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
static ITS_BOOLEAN
AllExpectedTRAs()
{
    ITS_UINT i;
    SS7_LinkSetPtr ls;
    /* Default Loop optimization changes start*/
    ITS_UINT k=0,l=0;
    ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (k = 0; k < MAX_LINKSETS; k++)
         {
          for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
          {            if(linkTransportMapDB[k][l] >0) 
             {  
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               if( k > 0 && k < 252)
               {
                lscount++;
                linkset[cnt++]=k;
                MTP3_ERROR((" linkset = %d\n",k));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));
        /* Default Loop optimization changes end*/

    for (i = 0; i <= (lscount); i++)
    {
        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[i])) != NULL &&
            ls->adjacent != 0)
        {
            if ((ls->isUp && !ls->gotTRA) ||
                !ls->isUp)
            {
                return (ITS_FALSE);
            }
        }
    }

    return (ITS_TRUE);
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
static ITS_BOOLEAN
FirstLinkAvailable(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    ITS_UINT i;

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Can't find link set %d\n", linkSet));

        return (ITS_FALSE);
    }

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isUp &&
            ls->links[i]->isAllowed &&
            ls->links[i]->testPassed &&
            ls->links[i]->linkCode != linkCode)
        {
            return (ITS_FALSE);
        }
    }

    return (ITS_TRUE);
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
static ITS_BOOLEAN
SufficientLinksAvailable(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    ITS_UINT i, numWanted;

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));

        return (ITS_FALSE);
    }

    numWanted = 0;
    for (i = 0; i < ls->numToStart; i++)
    {
        if (ls->links[i]->linkCode == linkCode ||
            (ls->links[i]->isUp && ls->links[i]->isAllowed))
        {
            numWanted++;
        }
    }

    if (numWanted >= (ls->numToStart - 1))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

static ITS_BOOLEAN statusFirstTime = ITS_TRUE;

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
TPRC_Main_ANSI(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    MTP3_TimerContext tc;
    ITS_UINT pc, i;
    ITS_OCTET ni;
    SS7_LinkSetPtr ls;
    /* Default Loop optimization changes start*/
    ITS_UINT k=0,l=0; 
    ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];
    /* Default Loop optimization changes end*/

    MTP3_TRACE_ENTRY_ANSI(MTP3_STM_TPRC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* this looks like it doesn't want args at all */
    /* no, link available/unavailable needs linkset linkcode */
    /* turns out it mostly needs linkSet */
    switch (trigger)
    {
    case STM_TRIGGER_T27: /* from timer control */
        /* have to wait until t27 expires to continue */
        SPRestartingSet_ANSI(ITS_TRUE);
        statusFirstTime = ITS_TRUE;
        /* Default Loop optimization changes start*/
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (k = 0; k < MAX_LINKSETS; k++)
         {
          for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
          {
            if(linkTransportMapDB[k][l] >0) 
             {  
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               if( k > 0 && k < 252)
               {
                lscount++;
                linkset[cnt++]=k;
                MTP3_ERROR((" linkset = %d\n",k));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));
        /* Default Loop optimization changes end*/

        for (i = 0; i <= (lscount); i++)
        {
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[i])) != NULL)
            {
                ls->gotTRA = ITS_FALSE;
                ls->state = RESTART_WAIT_1;
            }
        }

        /*LLSC_Main_ANSI(MTP3_STM_TPRC,
                       SLM_TRIGGER_RESTART_BEGINS,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);*/

        TSRC_Main_ANSI(MTP3_STM_TPRC,
                       STM_TRIGGER_RESTART_BEGIN,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        TSFC_Main_ANSI(MTP3_STM_TPRC,
                       STM_TRIGGER_RESTART_BEGIN,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        TLAC_Main_ANSI(MTP3_STM_TPRC,
                       STM_TRIGGER_RESTART_BEGIN,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        RSRT_Main_ANSI(MTP3_STM_TPRC,
                       SRM_TRIGGER_RESTART_BEGINS,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);
        break;

    case STM_TRIGGER_TRAFFIC_RESTART_ALLOWED:   /* from HMDT */
        pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* may be from non-adjacent */
        linkSet = MTP3_FindAdjacent_ANSI(ni, pc, linkSet);

        ls = LINKSET_FindLinkSet(linkSet);

        if (ls == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if (ls->state == RESTART_IDLE)
        {
            TSRC_Main_ANSI(MTP3_STM_TPRC,
                           STM_TRIGGER_TRAFFIC_RESTART_ALLOWED,
                           sif, len,
                           linkSet, linkCode);
        }
        else if (ls->state == RESTART_WAIT_1)
        {
            /* mark TRA received */
            ls->gotTRA = ITS_TRUE;
        }
        else if (ls->state == RESTART_WAIT_2)
        {
            /* mark TRA recieved */
            if (AllExpectedTRAs())
            {
                ITS_C_ASSERT(ls != NULL);

                /* stop T23 */
                if (ls->t23 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ls->t23);
                    ls->t23 = TIMER_BAD_SERIAL;
                }

                if (STPFunction_ANSI())
                {
                    ls->state = RESTART_WAIT_3;

                    if (statusFirstTime)
                    {
                        TSRC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_SENDING_STATUS_PHASE,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSRC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_SEND_STATUS,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        statusFirstTime = ITS_FALSE;
                    }

                    /* start T24 */
                    tc.timerId = MTP3_T24;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                    ls->t24 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t24 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));
                }
                else
                {
                    /* stop T26 */
                    if (ls->t26 != TIMER_BAD_SERIAL)
                    {
                        TIMERS_CancelSharedTimer(ls->t26);
                        ls->t26 = TIMER_BAD_SERIAL;
                    }

                    ls->state = RESTART_IDLE;

                    if (SPRestarting_ANSI())
                    {
                        TSRC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSFC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TLAC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RSRT_Main_ANSI(MTP3_STM_TPRC,
                                       SRM_TRIGGER_RESTART_ENDS,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        MTP3_DEBUG(("2.Sp Restart Set Flase\n"));
                        SPRestartingSet_ANSI(ITS_FALSE);
                        /* FIXME: Clear fullRestartNeeded? */
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_RESTART_INDIC:             /* from MGMT */
       /* cancel all marks */
        if (!FullRestartNeeded())
        {
            statusFirstTime = ITS_TRUE;
        /* Default Loop optimization changes start*/
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (k = 0; k < MAX_LINKSETS; k++)
         {
          for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
          {
            if(linkTransportMapDB[k][l] >0) 
             {  
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               if( k > 0 && k < 252)
               {
                lscount++;
                linkset[cnt++]=k;
                MTP3_ERROR((" linkset = %d\n",k));
                break;
               }
             }
          }
         }
        // MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));
        /* Default Loop optimization changes end*/

            for (i = 0; i <= (lscount); i++)
            {
                if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[i])) != NULL)
                {
                    ls->state = RESTART_IDLE;
                }
            }


            TSRC_Main_ANSI(MTP3_STM_TPRC,
                           STM_TRIGGER_RESTART_END,
                           NULL, 0,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            TSFC_Main_ANSI(MTP3_STM_TPRC,
                           STM_TRIGGER_RESTART_END,
                           NULL, 0,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

                        MTP3_DEBUG(("3.Sp Restart Set Flase\n"));
            SPRestartingSet_ANSI(ITS_FALSE);
            /* FIXME: Clear fullRestartNeeded? */
        }
        break;

    case STM_TRIGGER_T26:                       /* from timer control */
       /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t26 = TIMER_BAD_SERIAL;

        if (SPRestarting_ANSI())
        {
            if (ls->state == RESTART_WAIT_1 ||
                ls->state == RESTART_WAIT_2 ||
                ls->state == RESTART_WAIT_3)
            {
                TSRC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_SEND_TRW,
                               NULL, 0,
                               linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                /* start T26 */
                tc.timerId = MTP3_T26;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
 
                ls->t26 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t26 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
        }
        break;

    case STM_TRIGGER_T22:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t22 = TIMER_BAD_SERIAL;

        if (ls->state == RESTART_WAIT_1)
        {
            if (!AllExpectedTRAs())
            {
                /* start T23 */
                tc.timerId = MTP3_T23;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                ls->t23 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t23 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ls->state = RESTART_WAIT_2;
            }
            else
            {
                if (STPFunction_ANSI())
                {
                    ls->state = RESTART_WAIT_3;

                    if (statusFirstTime)
                    {
                        TSRC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_SENDING_STATUS_PHASE,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSRC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_SEND_STATUS,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        statusFirstTime = ITS_FALSE;
                    }

                    /* start T24 */
                    tc.timerId = MTP3_T24;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                    ls->t24 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t24 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));
                }
                else
                {
                    /* stop T26 */
                    if (ls->t26 != TIMER_BAD_SERIAL)
                    {
                        TIMERS_CancelSharedTimer(ls->t26);
                        ls->t26 = TIMER_BAD_SERIAL;
                    }

                    ls->state = RESTART_IDLE;

                    if (SPRestarting_ANSI())
                    {
                        TSRC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSFC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TLAC_Main_ANSI(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RSRT_Main_ANSI(MTP3_STM_TPRC,
                                       SRM_TRIGGER_RESTART_ENDS,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        SPRestartingSet_ANSI(ITS_FALSE);
                        MTP3_DEBUG(("4.Sp Restart Set Flase\n"));
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        if (ls->state == RESTART_WAIT_1)
        {
            /* mark link available */
            if (FirstLinkAvailable(linkSet, linkCode))
            {
                TSRC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_SEND_TRW,
                               NULL, 0,
                               linkSet,
                               linkCode);

                /* start T26 */
                tc.timerId = MTP3_T26;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                /* This needs to be on a link */
                if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
                {
                    return (ITS_SUCCESS);
                }

                ls->t26 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t26 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                /* start T22 */
                tc.timerId = MTP3_T22;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                ls->t22 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t22 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }

            if (SufficientLinksAvailable(linkSet, linkCode))
            {
                if (ls->t22 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ls->t22);
                    ls->t22 = TIMER_BAD_SERIAL;
                }

                if (!AllExpectedTRAs())
                {
                    /* start T23 */
                    tc.timerId = MTP3_T23;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                    ls->t23 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t23 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ls->state = RESTART_WAIT_2;
                }
                else
                {
                    if (STPFunction_ANSI())
                    {
                        ls->state = RESTART_WAIT_3;

                        if (statusFirstTime)
                        {
                            TSRC_Main_ANSI(MTP3_STM_TPRC,
                                           STM_TRIGGER_SENDING_STATUS_PHASE,
                                           NULL, 0,
                                           linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            TSRC_Main_ANSI(MTP3_STM_TPRC,
                                           STM_TRIGGER_SEND_STATUS,
                                           NULL, 0,
                                           linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            statusFirstTime = ITS_FALSE;
                        }

                        /* start T24 */
                        tc.timerId = MTP3_T24;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                        ls->t24 =
                            TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                               __ansi_t24 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));
                    }
                    else
                    {
                        /* stop T26 */
                        if (ls->t26 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelSharedTimer(ls->t26);
                            ls->t26 = TIMER_BAD_SERIAL;
                        }

                        ls->state = RESTART_IDLE;

                        if (SPRestarting_ANSI())
                        {
                            TSRC_Main_ANSI(MTP3_STM_TPRC,
                                           STM_TRIGGER_RESTART_END,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            TSFC_Main_ANSI(MTP3_STM_TPRC,
                                           STM_TRIGGER_RESTART_END,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            TLAC_Main_ANSI(MTP3_STM_TPRC,
                                           STM_TRIGGER_RESTART_END,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            RSRT_Main_ANSI(MTP3_STM_TPRC,
                                           SRM_TRIGGER_RESTART_ENDS,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            SPRestartingSet_ANSI(ITS_FALSE);
                        MTP3_DEBUG(("5.Sp Restart Set Flase\n"));
                        }
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_LINK_UNAVAILABLE:          /* from TLAC */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        if (ls->state == RESTART_WAIT_1)
        {
            /* cancel link available */
        }
        break;

    case STM_TRIGGER_T23:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t23 = TIMER_BAD_SERIAL;

        if (ls->state == RESTART_WAIT_2)
        {
            if (STPFunction_ANSI())
            {
                ls->state = RESTART_WAIT_3;

                if (statusFirstTime)
                {
                    TSRC_Main_ANSI(MTP3_STM_TPRC,
                                   STM_TRIGGER_SENDING_STATUS_PHASE,
                                   NULL, 0,
                                   linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TSRC_Main_ANSI(MTP3_STM_TPRC,
                                   STM_TRIGGER_SEND_STATUS,
                                   NULL, 0,
                                   linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    statusFirstTime = ITS_FALSE;
                }

                /* start T24 */
                tc.timerId = MTP3_T24;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                ls->t24 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t24 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
            else
            {
                /* stop T26 */
                if (ls->t26 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ls->t26);
                    ls->t26 = TIMER_BAD_SERIAL;
                }

                ls->state = RESTART_IDLE;

                if (SPRestarting_ANSI())
                {
                    TSRC_Main_ANSI(MTP3_STM_TPRC,
                                   STM_TRIGGER_RESTART_END,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TSFC_Main_ANSI(MTP3_STM_TPRC,
                                   STM_TRIGGER_RESTART_END,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TLAC_Main_ANSI(MTP3_STM_TPRC,
                                   STM_TRIGGER_RESTART_END,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RSRT_Main_ANSI(MTP3_STM_TPRC,
                                   SRM_TRIGGER_RESTART_ENDS,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    SPRestartingSet_ANSI(ITS_FALSE);
                        MTP3_DEBUG(("6.Sp Restart Set Flase\n"));
                }
            }
        }
        break;

    case STM_TRIGGER_STATUS_SENT:               /* from TSRC */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        if (ls->state == RESTART_WAIT_3)
        {
            /* stop T24 */
            if (ls->t24 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ls->t24);
                ls->t23 = TIMER_BAD_SERIAL;
            }

            /* stop T26 */
            if (ls->t26 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ls->t26);
                ls->t26 = TIMER_BAD_SERIAL;
            }

            ls->state = RESTART_IDLE;

            if (SPRestarting_ANSI())
            {
                TSRC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TSFC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TLAC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                RSRT_Main_ANSI(MTP3_STM_TPRC,
                               SRM_TRIGGER_RESTART_ENDS,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                SPRestartingSet_ANSI(ITS_FALSE);
                        MTP3_DEBUG(("7.Sp Restart Set Flase\n"));
            }
        }
        break;

    case STM_TRIGGER_T24:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t24 = TIMER_BAD_SERIAL;

        if (ls->state == RESTART_WAIT_3)
        {
            /* stop T26 */
            if (ls->t26 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ls->t26);
                ls->t26 = TIMER_BAD_SERIAL;
            }

            ls->state = RESTART_IDLE;

            if (SPRestarting_ANSI())
            {
                TSRC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TSFC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TLAC_Main_ANSI(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                RSRT_Main_ANSI(MTP3_STM_TPRC,
                               SRM_TRIGGER_RESTART_ENDS,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                SPRestartingSet_ANSI(ITS_FALSE);
                        MTP3_DEBUG(("8.Sp Restart Set Flase\n"));
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}
