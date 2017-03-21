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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/09 05:50:45  ssingh
 * LOG: Added error description for new return types.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/04 16:42:20  hdivoux
 * LOG: More errors for upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2002/02/07 00:20:52  mmiers
 * LOG: Add error text
 * LOG:
 * LOG: Revision 5.2  2002/02/06 23:44:58  mmiers
 * LOG: Continued ISUP integration
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:03  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/08/09 00:08:21  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.4  2000/05/23 21:26:34  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot of SCTP.
 * LOG:
 * LOG: Revision 2.3  2000/04/24 22:20:05  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.
 * LOG:
 * LOG: Revision 2.2  2000/03/28 17:42:50  hdivoux
 * LOG: Added ASN.1 encode and decode error codes.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:49  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:21  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:11  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.21  1998/10/16 17:05:00  mmiers
 * LOG: Nother error code for ENOENT.
 * LOG:
 * LOG: Revision 1.20  1998/10/15 01:28:04  mmiers
 * LOG: Add new error code for BADSTATE.
 * LOG:
 * LOG: Revision 1.19  1998/10/07 17:31:04  whu
 * LOG: People need to watch it when they add ITS error codes.  A text string
 * LOG: needs to be added to its_error.c for each new code.
 * LOG:
 * LOG: Revision 1.18  1998/09/28 22:09:39  mmiers
 * LOG: More support for intelligent transports.
 * LOG:
 * LOG: Revision 1.17  1998/07/03 16:09:39  mmiers
 * LOG: SCCP as a thread.
 * LOG:
 * LOG: Revision 1.16  1998/06/24 17:45:08  mmiers
 * LOG: Convert over to using the generated exceptions.
 * LOG:
 * LOG: Revision 1.15  1998/06/19 22:25:01  mmiers
 * LOG: Reaching the end of TCAP.  Initial SCCP implementation.
 * LOG:
 * LOG: Revision 1.14  1998/06/16 23:41:01  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.13  1998/05/31 03:14:46  mmiers
 * LOG: Fix compilation errors.
 * LOG:
 * LOG: Revision 1.12  1998/05/26 23:46:38  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.11  1998/05/26 23:38:13  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.10  1998/05/14 02:45:28  mmiers
 * LOG: More work on SCCP.  I think I have the encode done OK, still have to
 * LOG: write the decode.  The PTR table in SCCP messages is a bit of a bitch.
 * LOG: If we ever do the same for ISUP, the IEToEvent code could be reused.
 * LOG: That would give us (minus the ever important *PROCEDURES*) the requirement
 * LOG: of MTP3 and below ONLY.  However, ther are a *LOT* of procedures we
 * LOG: don't do (e.g., SST).
 * LOG:
 * LOG: Revision 1.9  1998/05/01 00:24:37  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.8  1998/04/23 17:04:06  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.7  1998/04/22 19:00:12  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.6  1998/04/16 15:59:01  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  1998/04/13 22:24:37  mmiers
 * LOG: Add direction checking for fifos.
 * LOG:
 * LOG: Revision 1.4  1998/04/08 17:25:27  mmiers
 * LOG: Work on sockets abstraction.
 * LOG:
 * LOG: Revision 1.3  1998/04/07 15:03:55  mmiers
 * LOG: More work on fifos, which required some new error numbers.
 * LOG:
 * LOG: Revision 1.2  1998/04/06 15:26:49  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.1  1998/03/20 02:45:26  mmiers
 * LOG: Add one file for the error_num to error_text translation.  Get this out of
 * LOG: the vendor tree, it is shared.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ident "$Id: its_error.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*
 * text for error strings
 */
static char *error_text[] = {
    "No error",
    "Out of memory",
    "NULL Information Elements",
    "ISUP message too big",
    "ISUP message send failed",
    "Couldn't create driver process",
    "Error receiving message from driver",
    "Couldn't peek at message queue",
    "No messages on the queue",
    "Couldn't send message",
    "Couldn't create message queue",            /* 10 */
    "No message space available for SS7",
    "Mandatory information elements missing",
    "TCAP message send failed",
    "SCCP message send failed",
    "Voice card error",
    "Bad or malformed TCAP message",
    "Bad or malformed ISUP message",
    "Too many active dialogs",
    "Invalid event source",
    "Bad or missing invoke id",                 /* 20 */
    "No event to fetch",
    "Indications are not enabled",
    "No synchronization variable available",
    "No mutex available",
    "Error with mutex or mutex function",
    "No semaphore available",
    "Error with semaphore or semaphore function",
    "No list matches that id",
    "No thread available",
    "List is not uniquely identified",          /* 30 */
    "End of list reached",
    "Error adding entry to list",
    "Bad or invalid thread",
    "Bad or corrupt fifo",
    "Invalid or missing fifo",
    "No socket available",
    "Bad or unresolvable host name",
    "Bad or corrupt socket",
    "Invalid arguments to function",
    "Bind failed",                              /* 40 */
    "Listen failed",
    "Connect failed",
    "Invalid FIFO mode for operation",
    "No matching transport for this id",
    "Bad, missing, or expired license",
    "Protocol error",
    "No route to destination",
    "Routing failure",
    "Overflow in numeric constant",
    "Operation would cause caller to block",    /* 50 */
    "Error with transport",
    "Initialization failed for unknown reasons",
    "No connection has been allocated with this number",
    "Resource file missing",
    "Resource currently in use",
    "Destination address is currently prohibited",
    "Invalid package type",
    "Invalid operation family",
    "Invalid operation specifier",
    "Invalid length",                           /* 60 */
    "NULL pointer detected",
    "Parameter present",
    "Invalid choice",
    "Bad state for this operation",
    "Value or parameter not present",
    "ASN.1 encode error",
    "ASN.1 decode error",
    "Invalid condition variable",
    "Invalid reader/writer lock",
    "Bad checksum",                             /* 70 */
    "Condition timed out",
    "Invalid originating point code",
    "Invalid destination point code",
    "CIC is busy",
    "CIC is blocked",
    "Item not configured",
    "Item not controlled",
    "Failed to start timer",
    "Invalid CIC",
    "No address",                               /* 80 */
    "Invalid msg type",
    "Invalid configuration",
    "Invalid node",
    "Invalid process",
    "Invalid FtGroup",
    "Invalid initialization state",
    "Invalid DSM type",
    "Invalid FtGroup members",
    "Invalid master FtGroup members",
    "Preinitialization failed",                 /* 90 */
    "Missing implementation",
    "Implementation initialization failed",
    "Row not locked",
    "Invalid table",
    "Invalid join state",
    "Invalid sync state",
    "GCS multicast failed",
    "GCS join failed",
    "GCS leave failed",
    "GCS connect failed",                       /* 100 */
    "GCS disconnect failed",
    "GCS event initialization failed",
    "GCS event queue failed",
    "GCS receive failed",
    "GCS event attach failed",
    "No remote",
    "No valid master",
    "Function call rejected",
    "Bad memory free",
    "Duplicate entry",                          /* 110 */
    "Destination not exists",
    "Invalid exchange type",
    "Feature not found",
    "Invalid variant",                          /* 114 */
    "Invalid error number"
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The purpose of this function is to take an IntelliSS7 return code
 *      and convert it into a string description about that error.
 *
 *  Input Parameters:
 *      err_num - the error code to translate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, this function returns a pointer to the descriptive string.
 *      On failure, this function returns a pointer to a default error string.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI char *
ITS_GetErrorText(int err_num)
{
    if (err_num < 0)
    {
        err_num = -err_num;
    }

    if (err_num < 0 || err_num > ITS_MAX_ERROR)
    {
        return error_text[ITS_MAX_ERROR];
    }

    return error_text[err_num];
}
