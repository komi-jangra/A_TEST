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
 *  ID:$Id: ansi-sccp_alarms.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:30  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.4.3.6.3  2005/02/21 09:00:30  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.3.2.1.4.3.6.2  2005/01/04 16:06:11  snagesh
 * LOG: Changed default alarm level to OFF
 * LOG:
 * LOG: Revision 7.3.2.1.4.3.6.1  2004/12/29 13:29:41  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.3.2.1.4.3  2004/09/02 11:55:54  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.3.2.1.4.2  2004/08/27 09:38:47  csireesh
 * LOG: Changes in Alarm Description
 * LOG:
 * LOG: Revision 7.3.2.1.4.1  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/08/27 14:15:25  hcho
 * LOG: Added alarm number not present in the alarm list.
 * LOG:
 * LOG: Revision 7.3  2003/02/03 07:00:39  aganguly
 * LOG: Changes for SCCP Alarms- Clean up of unwanted alarms still to be done in Release 6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.5  2002/03/20 23:30:17  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.4  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 6.3  2002/03/07 17:42:30  mmiers
 * LOG: Most of ANSI SCCP merged.
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

ITS_UINT SCCP_AlarmLevel_ANSI = ALARM_LVL_OFF;


/*Intermediate alarms removed between 01 to 15 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 416,
                    "SCCP failed to Intialize -",
                    ALARM_LVL_CRIT,         "Initialize",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 17 to 21 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 422,
                    "SCCP Initialized Successfully",
                    ALARM_LVL_INFO,         "Initialize",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 423,
                    "SCCP Terminating",
                    ALARM_LVL_CRIT,         "Terminate",
                    "SCCP", ITS_TRUE);
 
/*Intermediate alarms removed between 24 to 26 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 427,
                    "ANSI SCCP License not found.",
                    ALARM_LVL_CRIT,         "EncodeMTP3",
                    "License", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 428,
                    "User Out of Service (UOS) Message from application:",
                    ALARM_LVL_INFO,         "SendUserOutOfService",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 429,
                    "User In Service (UIS) Message from application:",
                    ALARM_LVL_INFO,         "SendUserInService",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 430,
                    "User Congested Message from application:",
                    ALARM_LVL_INFO,         "SendSetCongestion",
                    "SCMG", ITS_FALSE);

 /*Intermediate alarms removed between 31 to 35 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 436,
                    "Signaling Point Accessible MTP3-RESUME received for remote node:",
                    ALARM_LVL_INFO,         "SCMGHandleMTP3Msg_ANSI",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 437,
                    "Signaling Point Inaccessible MTP3-PAUSE received for remote node:",
                    ALARM_LVL_INFO,         "SCMGHandleMTP3Msg_ANSI",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 438,
                    "Signaling Point Congested MTP3-STATUS received for remote node:",
                    ALARM_LVL_INFO,         "SCMGHandleMTP3Msg_ANSI",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 439,
                    "Malformed MTP3 management message received",
                    ALARM_LVL_MINOR,         "SCMGHandleMTP3Msg_ANSI",
                    "SCMG", ITS_FALSE);

 /*Intermediate alarms removed between 40 to 42 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 443,
                    "Subsystem Allowed(SSA) message received from remote subsystem:",
                    ALARM_LVL_CRIT,         "SCMGHandleSCLCMsg_ANSI",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 444,
                    "Subsystem Prohibted(SSP) message received from remote subsystem:",
                    ALARM_LVL_CRIT,        "SCMGHandleSCLCMsg_ANSI",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 445,
                    "Subsystem Congested(SSC) message received from remote subsystem:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 446,
                    "Subsystem Allowed(SSA) message received",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 447,
                    "Subsystem Prohibted(SSP) message received",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 448,
                    "Subsystem Congested(SSC) message received",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCMG Table", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 449,
                    "Unknown SCMG message received from remote:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 450,
                    "Malformed SCMG message received from remote",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 451,
                    "User In Service (UIS) message received from application for ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 452,
                    "User Out Of Service (UOS) message received from application for ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCMG", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 453,
                    "User Out Of Service message received from remote:",
                    ALARM_LVL_MINOR,       "SCMGHandleSCLC",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 454,
                    "User In Service message received from remote:",
                    ALARM_LVL_INFO,       "SCMGHandleSCLC",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 455,
                    "Subsystem status Changed to Allowed:",
                    ALARM_LVL_INFO,       "SCMGHandleSSTTimeout",
                    "SCMG", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 456,
                    "Subsystem status changed to Prohibited:",
                    ALARM_LVL_INFO,       "SCMGHandleSCLC",
                    "SCMG", ITS_TRUE);

 /*Intermediate alarms removed between 57 to 99 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 500,
                    "SCCP Remote Subsystem Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 501,
                    "SCCP Remote Subsystem Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);
#if 0
ALARM_FORMAT_SUBSYS(ANSI_SCCP, 102,
                    "SCCP Remote Point Code Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 103,
                    "SCCP Remote Point Code Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 104,
                    "SCCP Concerned Point Code Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 105,
                    "SCCP Concerned Point Code Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 506,
                    "SCCP Concerned subsystem Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 507,
                    "SCCP Concerned subsystem Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

 /*Intermediate alarms removed between 108 to 231; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 632,
                    "Message for unknown Destination- No Route to remote:",
                    ALARM_LVL_MAJOR,       "SCLCHandleSCRCMsg_ANSI",
                    "Routing", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 633,
                    "Discarding Message from Application- Missing Routing Information.",
                    ALARM_LVL_MAJOR,       "SCLCHandleAPPMsg_ANSI",
                    "Routing", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 634,
                    "Unknown message type received form application ",
                    ALARM_LVL_MAJOR,       "SCOCHandleAPPMsg_ANSI",
                    "Routing", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(ANSI_SCCP, 235,
                    "SCCP-CL Message from application- unknown message type ",
                    ALARM_LVL_MAJOR,       "SCLCHandleAPPMsg_ANSI",
                    "Routing ", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 636,
       	            "Unknown message type received from remote ",
                    ALARM_LVL_MAJOR,       "SCOCHandleTimer_ANSI",
                    "Routing ", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(ANSI_SCCP, 637,
                    "SCCP-CL Message from remote- unknown .",
                    ALARM_LVL_MAJOR,       "SCLCHandleSCRCMsg",
                    "Routing", ITS_TRUE);
#endif

 /*Intermediate alarms removed between 238 to 242 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 643,
                    "Message received from remote for unavailable subsystem:",
                    ALARM_LVL_MAJOR,       "SCRCDeliverMTP3Ind",
                    "Routing ", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 644,
                    "Discarding Message - No SSN in Called Party Address.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverLocal",
                    "Routing ", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 645,
                    "SCCP Routing:Global Title Translation failed.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverByGTT",
                    "Routing", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 646,
                    "GTT: Error in translated address.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverByGTT",
                    "Routing", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 647,
                    "Discarding message - Called party address absent in SCCP message received from remote.",
                    ALARM_LVL_MINOR,       "SCRCHandleMTP3Msg_ANSI",
                    "Routing", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 648,
                    "Message for inaccessible remote subsystem:",
                    ALARM_LVL_MAJOR,       "SCRCDeliverRemote",
                    "Routing ", ITS_TRUE);

 /*Intermediate alarms removed between 249 to 255 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 656,
                    "CC received from remote end  in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownCC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 657,
                    "CREF  received from remote end  in invalid state ",
                    ALARM_LVL_MINOR,       "HandleDownCREF",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 658,
                    "RLSD received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownRLSD",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 659,
                    "RLC received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownRLC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,660,
                    "DT1 received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 661,
                    "DT1 received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 662,
                    "DT2 received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 663,
                    "DT2 received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 664,
                    "AK received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 665,
                   "AK received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 666,
                    "ED received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,667,
                    "ED received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,668, 
                    "EA received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,669,
                    "EA received from remote end in invalid state.",
                    ALARM_LVL_MINOR,        "HandleDownEA",
                    "Subsystem", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,670,
                    "UDT received from remote with invalid Protocol Class ",
                    ALARM_LVL_MAJOR,       "SCRCHandleMTP3Msg",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,671,
                    "RSR received from application with invalid Protocol Class ",
                    ALARM_LVL_MAJOR,       "HandleAppRSR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,672,
                    "DT1 received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,673,
                    "DT1 received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,674,
                    "DT2 received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,675,
                    "DT2 received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,676,
                    "AK received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,677,
                    "AK received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,678,
                    "ED received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,679,
                    "EA received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,680,
                    "ED received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,681,
                    "EA received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,682,
                    "RSR received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownRSR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,683,
                    "RSC received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppRSC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,684,
                    "RSC received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownRSC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,685,
                    "CR received from remote with invalid Protocol Class ",
                    ALARM_LVL_MAJOR,       "HandleDownCR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,686,
                    "CR received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppCR",
                    "SCCP-CO", ITS_TRUE);

 /* Alarms removed between 287 to 382 ; not used in PR 6.4.1 */


ALARM_Format *ANSI_SCCP_Alarms[] =
{
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //410
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP416,
        NULL,
        NULL,
        NULL,
        NULL, //420
        NULL,
        &ALARM_ANSI_SCCP422,
        &ALARM_ANSI_SCCP423,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP427,
        &ALARM_ANSI_SCCP428,
        &ALARM_ANSI_SCCP429,
        &ALARM_ANSI_SCCP430,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP436,
        &ALARM_ANSI_SCCP437,
        &ALARM_ANSI_SCCP438,
        &ALARM_ANSI_SCCP439,
        NULL, //440
        NULL,
        NULL,
        &ALARM_ANSI_SCCP443,
        &ALARM_ANSI_SCCP444,
        &ALARM_ANSI_SCCP445,
        &ALARM_ANSI_SCCP446,
        &ALARM_ANSI_SCCP447,
        &ALARM_ANSI_SCCP448,
        &ALARM_ANSI_SCCP449,
        &ALARM_ANSI_SCCP450,
        &ALARM_ANSI_SCCP451,
        &ALARM_ANSI_SCCP452,
        &ALARM_ANSI_SCCP453,
        &ALARM_ANSI_SCCP454,
        &ALARM_ANSI_SCCP455,
        &ALARM_ANSI_SCCP456,
        NULL,
        NULL,
        NULL,
        NULL, //460
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //470
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //480
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //490
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP500,
        &ALARM_ANSI_SCCP501,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP506,
        &ALARM_ANSI_SCCP507,
        NULL,
        NULL,
        NULL, //510
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //515
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //520
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //530
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //540
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //550
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //560
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //570
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //580
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //590
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //600
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //610
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //620
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //630
        NULL,
        &ALARM_ANSI_SCCP632,
        &ALARM_ANSI_SCCP633,
        &ALARM_ANSI_SCCP634,
        NULL,
        &ALARM_ANSI_SCCP636,
        NULL,
        NULL,
        NULL,
        NULL, //640
        NULL,
        NULL,
        &ALARM_ANSI_SCCP643,
        &ALARM_ANSI_SCCP644,
        &ALARM_ANSI_SCCP645,
        &ALARM_ANSI_SCCP646,
        &ALARM_ANSI_SCCP647,
        &ALARM_ANSI_SCCP648,
        NULL,
        NULL, //650
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP656,
        &ALARM_ANSI_SCCP657,
        &ALARM_ANSI_SCCP658,
        &ALARM_ANSI_SCCP659,
        &ALARM_ANSI_SCCP660,
        &ALARM_ANSI_SCCP661,
        &ALARM_ANSI_SCCP662,
        &ALARM_ANSI_SCCP663,
        &ALARM_ANSI_SCCP664,
        &ALARM_ANSI_SCCP665,
        &ALARM_ANSI_SCCP666,
        &ALARM_ANSI_SCCP667,
        &ALARM_ANSI_SCCP668,
        &ALARM_ANSI_SCCP669,
        &ALARM_ANSI_SCCP670,
        &ALARM_ANSI_SCCP671,
        &ALARM_ANSI_SCCP672,
        &ALARM_ANSI_SCCP673,
        &ALARM_ANSI_SCCP674,
        &ALARM_ANSI_SCCP675,
        &ALARM_ANSI_SCCP676,
        &ALARM_ANSI_SCCP677,
        &ALARM_ANSI_SCCP678,
        &ALARM_ANSI_SCCP679,
        &ALARM_ANSI_SCCP680,
        &ALARM_ANSI_SCCP681,
        &ALARM_ANSI_SCCP682,
        &ALARM_ANSI_SCCP683,
        &ALARM_ANSI_SCCP684,
        &ALARM_ANSI_SCCP685,
        &ALARM_ANSI_SCCP686
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a SCCP alarm.
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
SCCP_Alarm_ANSI(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= ANSI_SCCP_ALARM_START &&
                 which <= ANSI_SCCP_ALARM_END);

    fmt = ANSI_SCCP_Alarms[which - ANSI_SCCP_ALARM_START];
    if (fmt  != NULL)
    {
        if (fmt->severity > SCCP_AlarmLevel_ANSI)
        {
            return;
        }
    }
    else
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
