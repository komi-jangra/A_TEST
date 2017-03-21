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
 *  ID: $Id: ss7_timers.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
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
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.48.1  2005/01/13 06:03:33  snagesh
 * LOG: XML persistency fix for MTP3_NUM_TIMERS
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 *
 ****************************************************************************/

#if !defined(_SS7_TIMERS_H_)
#define _SS7_TIMERS_H_

#include <its_timers.h>

/*
 * TCAP
 */
extern TIMER_Manager    CCITT_TCAP_Timers;
/* ANSI TCAP defines no timers */

#define TCAP_T_reject   0

#define TCAP_NUM_TIMERS 1

/*
 * SCCP
 */
extern TIMER_Manager    CCITT_SCCP_Timers;
extern TIMER_Manager    ANSI_SCCP_Timers;

#define SCCP_T_statInfo         0
#define SCCP_T_coordChg         1
#define SCCP_T_ignoreSST        2
#define SCCP_T_rtgStatInfo      3
#define SCCP_T_conn             4
#define SCCP_T_release          5
#define SCCP_T_reset            6
#define SCCP_T_ias              7
#define SCCP_T_iar              8
#define SCCP_T_guard            9
#define SCCP_T_reassembly       10
#define SCCP_T_interval         11
#define SCCP_T_repeatRelease    12

#define SCCP_NUM_TIMERS         13

/*
 * MTP3
 */
extern TIMER_Manager    CCITT_MTP3_Timers;
extern TIMER_Manager    ANSI_MTP3_Timers;

#define MTP3_TIMER_T1   0
#define MTP3_TIMER_T2   1
#define MTP3_TIMER_T3   2
#define MTP3_TIMER_T4   3
#define MTP3_TIMER_T5   4
#define MTP3_TIMER_T6   5
#define MTP3_TIMER_T7   6
#define MTP3_TIMER_T8   7
#define MTP3_TIMER_T9   8
#define MTP3_TIMER_T10  9
#define MTP3_TIMER_T11  10
#define MTP3_TIMER_T12  11
#define MTP3_TIMER_T13  12
#define MTP3_TIMER_T14  13
#define MTP3_TIMER_T15  14
#define MTP3_TIMER_T16  15
#define MTP3_TIMER_T17  16
#define MTP3_TIMER_T18  17
#define MTP3_TIMER_T19  18
#define MTP3_TIMER_T20  19
#define MTP3_TIMER_T21  20
#define MTP3_TIMER_T22  21
#define MTP3_TIMER_T23  22
#define MTP3_TIMER_T24  23
#define MTP3_TIMER_T25  24
#define MTP3_TIMER_T26  25
#define MTP3_TIMER_T27  26
#define MTP3_TIMER_T28  27
#define MTP3_TIMER_T29  28
#define MTP3_TIMER_T30  29
#define MTP3_TIMER_T31  30
#define MTP3_TIMER_T32  31
#define MTP3_TIMER_T33  32
#define MTP3_TIMER_T34  33

#define MTP3_TIMER_SLT_T1  34
#define MTP3_TIMER_SLT_T2  35

#define MTP3_NUM_TIMERS 36

#endif /* _SS7_TIMERS_H_ */
