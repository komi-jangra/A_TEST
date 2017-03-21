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
 *  ID:$Id: itu-tcap_alarms.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:34  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.38.2  2005/02/28 10:54:42  sbabu
 * LOG: TCAP OAM Bug Fix
 * LOG:
 * LOG: Revision 7.3.38.1  2004/12/31 09:47:50  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.3  2003/02/07 13:57:46  tsanthosh
 * LOG: Changes for Pegs & Alarms
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
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

ITS_UINT TCAP_AlarmLevel_CCITT = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1401,
                    "Discarding Component - Reject Sent to Application:",
                    ALARM_LVL_MINOR,        "CCOHandleAPPMsg_CCITT",
                    "Outgoing Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1403,
                    "Discarding Reset Timer Request from Application for non-existent invoke operation:",
                    ALARM_LVL_MINOR,        "CCOHandleAPPMsg_CCITT",
                    "Invoke Timer", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1404,
                    "Discarding Component - Component sanity check failed:",
                    ALARM_LVL_MINOR,        "CCOHandleDHAMsg_CCITT",
                    "Incoming Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1406,
                    "Discarding Incoming Component - Reject Sent to App & Remote:",
                    ALARM_LVL_MINOR,        "CCOHandleDHAMsg_CCITT",
                    "INV Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1413,
                    "TCAP failed to Initialize.",
                    ALARM_LVL_CRIT,         "TCAP_Initialize_CCITT",
                    "CCITT TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1414,
                    "TCAP Initialized Successfully.",
                    ALARM_LVL_INFO,         "TCAP_Initialize_CCITT",
                    "CCITT TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1415,
                    "TCAP Terminating.",
                    ALARM_LVL_INFO,         "TCAP_Terminate_CCITT",
                    "CCITT TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1416,
                    "TCAP Aborting.",
                    ALARM_LVL_CRIT,         "CCITT_TCAPThread",
                    "TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1417,
                    "Received Unrecognized event from User:Neither Dialogue nor Component",
                    ALARM_LVL_CRIT,         "CCITT_TCAPThread",
                    "EVENT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1429,
                    "Discarding Incoming Message - Malformed SCCP UDT.", 
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1430,
                    "SCCP Return Error -TC_NOTICE sent to User.", 
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1431,
                    "Error in decoding message from remote - Abort initiated from stack with reason:",
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Dialogue", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1432,
                    "Discarding Message - Dialogue sanity check failed.",
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1436,
                    "Failed to encode package from Application:",
                    ALARM_LVL_MINOR,        "AssemblePDU",
                    "Outgoing Dialogue", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1437,
                    "Failed to encode outgoing Component from Application.",
                    ALARM_LVL_MINOR,        "AssemblePDU",
                    "Outgoing Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1438,
                    "Attempt to send User Info or AC-Name from User in invalid dialog state TC_ACTIVE.",
                    ALARM_LVL_MINOR,        "UpdateDialogueState",
                    "Incoming Dialogue", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1439,
                    "Failed to Decode TCAP Data.",
                    ALARM_LVL_MINOR,        "DisassemblePDU",
                    "Incoming Component", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1440,
                    "Missing Transaction Context for Message from User:",
                    ALARM_LVL_MAJOR,        "AssemblePDU",
                    "DLG Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1443,
                    "Invalid PType received from Application for state TC_IDLE:",
                    ALARM_LVL_MINOR,        "TSMHandleTCOCSLMsg_CCITT",
                    "Outgoing Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1444,
                    "Invalid PType received from Application for state TC_BEGIN_RCVD:",
                    ALARM_LVL_MAJOR,        "TSMHandleTCOCSLMsg_CCITT",
                    "DLG Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1445,
                    "Invalid PType received from Application for  state TC_BEGIN_SENT:",
                    ALARM_LVL_MAJOR,        "TCOHandleSCCPMsg_CCITT",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1446,
                    "Invalid PType received from Application for state TC_ACTIVE:",
                    ALARM_LVL_MINOR,        "TCOHandleSCCPMsg_CCITT",
                    "Incoming Message", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1447,
                    "No Transaction Context for message from remote:",
                    ALARM_LVL_MAJOR,        "TCOHandleSCCPMsg_CCITT",
                    "DLG Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1448,
                    "Unknown Package Type received from remote - Aborting transaction:",
                    ALARM_LVL_MINOR,        "TCOHandleSCCP",
                    "Incoming Dialogue", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1450,
                    "Invalid PType received from Remote for state TC_BEGIN_RCVD:",
                    ALARM_LVL_CRIT,         "TCOHandleSCCP",
                    "CCITT TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1451,
                    "Invalid PType received from Remote for state TC_BEGIN_SENT:",
                    ALARM_LVL_CRIT,         "TCOHandleSCCP",
                    "DIDS Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1452,
                    "Invalid PType received from Remote for state TC_ACTIVE:",
                    ALARM_LVL_INFO,         "TCOHandleSCCP",
                    "CCITT TCAP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1453,
                    "Bad or missing TID for message from remote:",
                    ALARM_LVL_CRIT,         "TCOHandleSCCP",
                    "DIDS Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_TCAP, 1455,
                    "Unable to allocate fresh DID to the user.",
                    ALARM_LVL_CRIT,         "TCAP_AllocateDialogueId_CCITT",
                    "DIDS Table", ITS_TRUE);


ALARM_Format *CCITT_TCAP_Alarms[] =
{
    &ALARM_CCITT_TCAP1401,
    NULL,
    &ALARM_CCITT_TCAP1403,
    &ALARM_CCITT_TCAP1404,
    NULL,
    &ALARM_CCITT_TCAP1406,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ALARM_CCITT_TCAP1413,
    &ALARM_CCITT_TCAP1414,
    &ALARM_CCITT_TCAP1415,
    &ALARM_CCITT_TCAP1416,
    &ALARM_CCITT_TCAP1417,
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
    &ALARM_CCITT_TCAP1429,
    &ALARM_CCITT_TCAP1430,
    &ALARM_CCITT_TCAP1431,
    &ALARM_CCITT_TCAP1432,
    NULL,
    NULL,
    NULL,
    &ALARM_CCITT_TCAP1436,
    &ALARM_CCITT_TCAP1437,
    &ALARM_CCITT_TCAP1438,
    &ALARM_CCITT_TCAP1439,
    &ALARM_CCITT_TCAP1440,
    NULL,
    NULL,
    &ALARM_CCITT_TCAP1443,
    &ALARM_CCITT_TCAP1444,
    &ALARM_CCITT_TCAP1445,
    &ALARM_CCITT_TCAP1446,
    &ALARM_CCITT_TCAP1447,
    &ALARM_CCITT_TCAP1448,
    NULL,
    &ALARM_CCITT_TCAP1450,
    &ALARM_CCITT_TCAP1451,
    &ALARM_CCITT_TCAP1452,
    &ALARM_CCITT_TCAP1453,
    NULL,
    &ALARM_CCITT_TCAP1455
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
TCAP_Alarm_CCITT(int which, const char *file, const int line,
                 char *format, ...)
{

    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= CCITT_TCAP_ALARM_START &&
                 which <= CCITT_TCAP_ALARM_END);

    fmt = CCITT_TCAP_Alarms[which - CCITT_TCAP_ALARM_START];

    if (fmt->severity > TCAP_AlarmLevel_CCITT)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
