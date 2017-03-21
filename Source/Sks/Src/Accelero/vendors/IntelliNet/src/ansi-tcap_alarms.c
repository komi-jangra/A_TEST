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
 *  ID:$Id: ansi-tcap_alarms.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.38.2  2005/02/28 10:54:21  sbabu
 * LOG: TCAP OAM Bug Fix
 * LOG:
 * LOG: Revision 7.3.38.1  2004/12/31 08:03:51  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.3  2003/02/07 11:43:18  tsanthosh
 * LOG: Modified to add the tcap alarms.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.5  2002/04/29 17:00:12  mmiers
 * LOG: Add first cut of mgmt API for TCAP, MTP3.
 * LOG:
 * LOG: Revision 6.4  2002/03/20 23:30:18  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.3  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 6.2  2002/03/01 20:32:03  mmiers
 * LOG: These build now.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 23:28:43  mmiers
 * LOG: Add alarms.  Pegs here are going to be short-lived.
 * LOG:
 *
 ****************************************************************************/

#include <its_assertion.h>

#include "ss7_alarms.h"

ITS_UINT TCAP_AlarmLevel_ANSI = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1001,
                    "Discarding  Component - Reject Sent to Application:",
                    ALARM_LVL_MINOR,        "CMPHandleAPPMsg_ANSI",
                    "Outgoing Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1004,
                    "Discarding  Component - Component sanity check failed:",
                    ALARM_LVL_MINOR,        "CMPHandleTPCPIMsg_ANSI",
                    "Incoming Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1006,
                    "Discarding Incoming Component-Reject sent to App & Remote:",
                    ALARM_LVL_MINOR,        "CMPHandleTPCPIMsg_ANSI",
                    "Incoming Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1013,
                    "TCAP failed to Initialize.",
                    ALARM_LVL_CRIT,         "TCAP_Initialize_ANSI",
                    "TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1014,
                    "TCAP Initialized Successfully.",
                    ALARM_LVL_INFO,         "TCAP_Initialize_ANSI",
                    "TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1015,
                    "TCAP Terminating.",
                    ALARM_LVL_INFO,"TCAP_Terminate_ANSI",
                    "TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1016,
                    "TCAP Aborting. ",
                    ALARM_LVL_CRIT,         "ANSI_TCAPThread",
                    "TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1017,
                    "Received Unrecognized event from User: neither Dialogue nor component",
                    ALARM_LVL_CRIT,         "ANSI_TCAPThread",
                    "EVENT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1029,
                    "Discarding incoming  Message - Malformed SCCP UDT.",
                    ALARM_LVL_MINOR,       "DisassemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1031,
                    "Error in decoding message from remote-Abort initiated from stack With reason:",
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1032,
                    "Discarding  Message - Dialogue sanity check failed:",
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1036,
                    "Failed to encode Package from application:",
                    ALARM_LVL_MINOR,        "AssemblePDU",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1037,
                    "Failed to encode outgoing Component from Application:",
                    ALARM_LVL_MINOR,        "AssemblePDU",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1040,
                    "Missing Transaction Context for Message from User:",
                    ALARM_LVL_MAJOR,        "AssemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1041,
                    "Invalid PType received from Application for state TC_CWOP_SENT/RCVD:",
                    ALARM_LVL_MINOR,        "TRPHandleCMPMsg_ANSI",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1042,
                    "Invalid PType received from Application for state  TC_CWIP_SENT/RCVD:",
                    ALARM_LVL_MINOR,        "TRPHandleTPCPIMsg_ANSI",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1043,
                    "Invalid PType received from Application for state TC_IDLE:",
                    ALARM_LVL_MINOR,        "TRPHandleTPCPIMsg_ANSI",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1044,
                    "Invalid PType received from Application for  state TC_QWOP_SENT/RCVD:",
                    ALARM_LVL_MAJOR,        "TRPHandleTPCPIMsg_ANSI",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1045,
                    "Invalid PType received from Application for state  TC_QWIP_SENT/RCVD:",
                    ALARM_LVL_MAJOR,        "TRPHandleSCCPMsg_ANSI",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1047,
                    "No Transaction Context for Message from Remote:",
                    ALARM_LVL_MAJOR,        "TRPHandleSCCPMsg_ANSI",
                    "DLG Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1048,
                    "Unknown Package Type Rcvd from remote. Aborting Transaction:",
                    ALARM_LVL_MINOR,        "TRPHandleSCCPMsg_ANSI",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1053,
                    "Bad/Missing TID for Message from Remote:",
                    ALARM_LVL_CRIT,         "TRPHandleSCCPMsg_ANSI",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1055,
                    "Unable to Allocate fresh DID to the user.",
                    ALARM_LVL_CRIT,         "TCAP_AllocateDialogueId_ANSI",
                    "DIDS Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1056,
                    "Invalid PType received from remote for QWOP_SENT state",
                    ALARM_LVL_MAJOR,         "TRPHandleSCCPMsg",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1057,
                    "Invalid PType received from Remote for State QWIP_SENT/RCVD:",
                    ALARM_LVL_CRIT,         "TCAP_AllocateDialogueId_ANSI",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1058,
                    "Invalid PType received from Remote for State CWOP_SENT/RCVD:",
                    ALARM_LVL_CRIT,         "TRPHandleSCCPMsg_ANSI",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_TCAP, 1059,
                    "Invalid PType received from Remote for State CWIP_SENT/RCVD:",
                    ALARM_LVL_CRIT,         "TRPHandleSCCPMsg_ANSI",
                    "Incoming Message", ITS_TRUE);

ALARM_Format *ANSI_TCAP_Alarms[] =
{
    &ALARM_ANSI_TCAP1001,
    NULL,
    NULL,
    &ALARM_ANSI_TCAP1004,
    NULL,
    &ALARM_ANSI_TCAP1006,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ALARM_ANSI_TCAP1013,
    &ALARM_ANSI_TCAP1014,
    &ALARM_ANSI_TCAP1015,
    &ALARM_ANSI_TCAP1016,
    &ALARM_ANSI_TCAP1017,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ALARM_ANSI_TCAP1029,
    NULL,
    &ALARM_ANSI_TCAP1031,
    &ALARM_ANSI_TCAP1032,
    NULL,
    NULL,
    NULL,
    &ALARM_ANSI_TCAP1036,
    &ALARM_ANSI_TCAP1037,
    NULL,
    NULL,
    &ALARM_ANSI_TCAP1040,
    &ALARM_ANSI_TCAP1041,
    &ALARM_ANSI_TCAP1042,
    &ALARM_ANSI_TCAP1043,
    &ALARM_ANSI_TCAP1044,
    &ALARM_ANSI_TCAP1045,
    NULL,
    &ALARM_ANSI_TCAP1047,
    &ALARM_ANSI_TCAP1048,
    NULL,
    NULL,
    NULL,
    NULL,
    &ALARM_ANSI_TCAP1053,
    NULL,
    &ALARM_ANSI_TCAP1055,
    &ALARM_ANSI_TCAP1056,
    &ALARM_ANSI_TCAP1057,
    &ALARM_ANSI_TCAP1058,
    &ALARM_ANSI_TCAP1059
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
void
TCAP_Alarm_ANSI(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= ANSI_TCAP_ALARM_START &&
                 which <= ANSI_TCAP_ALARM_END);

    fmt = ANSI_TCAP_Alarms[which - ANSI_TCAP_ALARM_START];

    if (fmt->severity > TCAP_AlarmLevel_ANSI)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
