/*********************************-*-C-*-************************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:07  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:02  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.11  2001/08/13 22:26:58  mmiers
 * LOG: Still one shared function.
 * LOG:
 * LOG: Revision 4.9  2001/06/25 17:05:59  mmiers
 * LOG: Must allow exact matches when not doing route selection.
 * LOG:
 * LOG: Revision 4.8  2001/06/22 00:03:30  mmiers
 * LOG: Put string in right place
 * LOG:
 * LOG: Revision 4.7  2001/06/22 00:00:50  mmiers
 * LOG: More bugs.
 * LOG:
 * LOG: Revision 4.6  2001/06/21 23:52:50  mmiers
 * LOG: Debug of print
 * LOG:
 * LOG: Revision 4.5  2001/06/21 00:54:40  mmiers
 * LOG: Re-enable printing.
 * LOG:
 * LOG: Revision 4.4  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.3  2001/06/19 21:12:35  mmiers
 * LOG: Use id when setting isUp.
 * LOG:
 * LOG: Revision 4.2  2001/06/08 21:04:57  mmiers
 * LOG: Fix missing send for application logic.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.34  2001/04/30 20:30:41  mmiers
 * LOG: Olivier spotted a bug (off by one) adding routes.
 * LOG:
 * LOG: Revision 3.33  2001/03/30 18:44:37  mmiers
 * LOG: Off by one bug, bad start for qsort.
 * LOG:
 * LOG: Revision 3.32  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.31  2001/03/02 23:35:44  mmiers
 * LOG: Couple of routing bug fixes.
 * LOG:
 * LOG: Revision 3.30  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.29  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.28  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.27  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.26  2001/01/20 00:05:39  mmiers
 * LOG: Tweaks.
 * LOG:
 * LOG: Revision 3.25  2001/01/11 21:19:26  omayor
 * LOG: Remove typo in adding the route.
 * LOG:
 * LOG: Revision 3.24  2000/12/29 17:35:01  mmiers
 * LOG: This should work
 * LOG:
 * LOG: Revision 3.23  2000/12/29 17:15:11  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 3.22  2000/12/29 16:42:04  mmiers
 * LOG: Change the flag settings.
 * LOG:
 * LOG: Revision 3.21  2000/12/22 00:36:26  mmiers
 * LOG: First message through
 * LOG:
 * LOG: Revision 3.20  2000/12/22 00:09:31  mmiers
 * LOG: Alter defaults a bit
 * LOG:
 * LOG: Revision 3.19  2000/12/21 23:50:51  mmiers
 * LOG: Traces & bugs
 * LOG:
 * LOG: Revision 3.18  2000/12/21 23:08:45  mmiers
 * LOG: Trace
 * LOG:
 * LOG: Revision 3.17  2000/12/21 23:01:45  mmiers
 * LOG: Missing unlock
 * LOG:
 * LOG: Revision 3.16  2000/12/21 22:55:38  mmiers
 * LOG: Better logic
 * LOG:
 * LOG: Revision 3.15  2000/12/21 22:52:07  mmiers
 * LOG: Alter logic to look more like PR3
 * LOG:
 * LOG: Revision 3.14  2000/12/21 22:36:49  mmiers
 * LOG: Trace
 * LOG:
 * LOG: Revision 3.13  2000/12/21 22:33:31  mmiers
 * LOG: Trace
 * LOG:
 * LOG: Revision 3.12  2000/12/19 19:01:10  mmiers
 * LOG: Off by one error
 * LOG:
 * LOG: Revision 3.11  2000/12/19 18:17:30  mmiers
 * LOG: Get the equals right
 * LOG:
 * LOG: Revision 3.10  2000/12/05 17:01:43  mmiers
 * LOG: Typos/trace
 * LOG:
 * LOG: Revision 3.9  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.8  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.17  2000/11/09 23:04:26  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.16  2000/11/09 01:32:35  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.15  2000/11/09 00:48:42  mmiers
 * LOG: Today's installment.  Also an IMAL fix.
 * LOG:
 * LOG: Revision 3.14  2000/11/08 16:58:53  mmiers
 * LOG: Pseudocode.
 * LOG:
 * LOG: Revision 3.13  2000/11/07 23:35:01  mmiers
 * LOG: Think about with and without event a bit more.
 * LOG:
 * LOG: Revision 3.12  2000/11/07 22:55:45  mmiers
 * LOG: Structure's in place.  Fill in the gaps.
 * LOG:
 * LOG: Revision 3.11  2000/11/06 23:32:21  mmiers
 * LOG: More work on the routing changes.
 * LOG:
 * LOG: Revision 3.10  2000/11/03 22:51:02  mmiers
 * LOG: More work on the routing changes.
 * LOG:
 * LOG: Revision 3.9  2000/11/03 21:57:36  mmiers
 * LOG: Start working on the routing changes.
 * LOG:
 * LOG: Revision 3.8  2000/10/09 16:53:19  mmiers
 * LOG: Set up for testing...
 * LOG:
 * LOG: Revision 3.7  2000/10/05 23:05:34  mmiers
 * LOG: New routing scheme.
 * LOG:
 * LOG: Revision 3.6  2000/09/25 20:09:27  mmiers
 * LOG: About done.  Need to convert route.c itself now.
 * LOG:
 * LOG: Revision 3.5  2000/09/25 19:56:52  mmiers
 * LOG: Set up for new route style.
 * LOG:
 * LOG: Revision 3.4  2000/09/14 21:03:48  mmiers
 * LOG: Fix up route deletion (link set safety).
 * LOG:
 * LOG: Revision 3.3  2000/09/13 20:35:15  mmiers
 * LOG: Update useNext when deleting routes.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:41  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.18  2000/07/05 22:25:37  rsonak
 * LOG:
 * LOG: route: read from global section, not ini name
 * LOG: kasock: add trace saying which down transport sent sltm
 * LOG: iptrans: add debug
 * LOG:
 * LOG: Revision 2.17  2000/07/04 00:14:57  rsonak
 * LOG:
 * LOG:
 * LOG: Debug, bad route delete, transport route ls/lc collection
 * LOG:
 * LOG: Revision 2.16  2000/06/28 22:52:20  mmiers
 * LOG:
 * LOG:
 * LOG: Modify routing mechanism to select by link.
 * LOG:
 * LOG: Revision 2.15  2000/06/22 23:10:46  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 2.14  2000/06/17 03:42:32  mmiers
 * LOG:
 * LOG:
 * LOG: I *think* I found the routing problem.  We weren't circularizing the
 * LOG: list.
 * LOG:
 * LOG: Revision 2.13  2000/06/17 02:21:34  rsonak
 * LOG:
 * LOG:
 * LOG: Debug info.
 * LOG:
 * LOG: Revision 2.12  2000/06/17 01:19:56  rsonak
 * LOG:
 * LOG:
 * LOG: Integration bug hunting (follow nextLink).
 * LOG:
 * LOG: Revision 2.11  2000/06/02 02:05:17  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.10  2000/05/16 00:05:21  mmiers
 * LOG:
 * LOG:
 * LOG: Add concept of route by linkset to routing table.
 * LOG:
 * LOG: Revision 2.9  2000/05/11 22:17:25  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for link sets.
 * LOG:
 * LOG: Revision 2.8  2000/02/14 19:17:44  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.7  2000/02/04 00:27:55  mmiers
 * LOG:
 * LOG:
 * LOG: ID check should look at PC AND SSN.
 * LOG:
 * LOG: Revision 2.6  2000/02/02 02:20:51  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.5  2000/01/26 03:04:10  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.4  2000/01/25 02:36:17  mmiers
 * LOG:
 * LOG:
 * LOG: UNIX update.
 * LOG:
 * LOG: Revision 2.3  2000/01/21 22:48:15  mmiers
 * LOG:
 * LOG: Had to add separate up/allowed variables.
 * LOG:
 * LOG: Revision 2.2  2000/01/21 22:14:44  mmiers
 * LOG:
 * LOG: Checkpoint changes.  Include routing behavior changes for Rajesh.
 * LOG:
 * LOG: Revision 2.1  2000/01/20 17:47:42  mmiers
 * LOG:
 * LOG: Forward link the routes for V7M.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:55  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.43  1999/09/17 16:44:51  mmiers
 * LOG:
 * LOG:
 * LOG: More information for route trace.
 * LOG:
 * LOG: Revision 1.42  1999/08/30 18:15:31  mmiers
 * LOG:
 * LOG:
 * LOG: Correct printing functions.
 * LOG:
 * LOG: Revision 1.41  1999/08/26 15:07:23  mmiers
 * LOG:
 * LOG:
 * LOG: Add a predicate for determination of the default app selector.
 * LOG:
 * LOG: Revision 1.40  1999/08/11 17:30:59  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.39  1998/12/18 01:14:29  rsonak
 * LOG: Fix a mutex release problem that could lock a process.
 * LOG:
 * LOG: Revision 1.38  1998/11/19 02:17:32  mmiers
 * LOG: Straighten out a few potential bugs.
 * LOG:
 * LOG: Revision 1.37  1998/11/19 00:36:28  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.36  1998/11/17 03:30:39  mmiers
 * LOG: Deal with gethostbyaddr() when appropriate.
 * LOG:
 * LOG: Revision 1.35  1998/11/12 00:09:14  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.34  1998/11/11 00:44:48  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.33  1998/11/04 02:47:29  mmiers
 * LOG: Remove ITS_SS7_LOCAL_ROUTE, it is irrelevant, we don't do that.
 * LOG: Add congestion callback list, it will be used for SS7.
 * LOG: Update TODO to reflect what needs to be added.
 * LOG:
 * LOG: Revision 1.32  1998/11/03 02:56:17  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.31  1998/10/05 15:01:36  whu
 * LOG: Finally found the "race condition" bug.  It wasn't.  The entries for
 * LOG: application routes were being corrupted when the application thread
 * LOG: terminated (ROUTE_Clean() bug).
 * LOG:
 * LOG: Revision 1.30  1998/10/01 20:00:29  mmiers
 * LOG: Capitalization errorr.
 * LOG:
 * LOG: Revision 1.29  1998/10/01 17:39:52  mmiers
 * LOG: Try to find the race condition with routing.
 * LOG:
 * LOG: Revision 1.28  1998/10/01 00:01:53  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.27  1998/09/29 21:38:49  mmiers
 * LOG: Bug fixes for new SCCP support.
 * LOG:
 * LOG: Revision 1.26  1998/09/29 20:22:34  mmiers
 * LOG: Add route state into the picture.
 * LOG:
 * LOG: Revision 1.25  1998/09/28 22:42:44  mmiers
 * LOG: More work enhancing MTP3-ish support.
 * LOG:
 * LOG: Revision 1.24  1998/09/28 22:09:40  mmiers
 * LOG: More support for intelligent transports.
 * LOG:
 * LOG: Revision 1.23  1998/09/26 02:47:01  mmiers
 * LOG: Linux code base cleanup.
 * LOG:
 * LOG: Revision 1.22  1998/09/22 18:51:20  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.21  1998/09/22 17:28:31  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.20  1998/09/16 15:50:14  whu
 * LOG: Found a long standing bug in the routing table where context was not
 * LOG: being set correctly after deleting an entry.  This applied to both
 * LOG: application and route entries.
 * LOG:
 * LOG: Revision 1.19  1998/08/27 23:28:14  hdivoux
 * LOG: Added functions to dump hashtables.
 * LOG:
 * LOG: Revision 1.18  1998/08/03 20:34:18  mmiers
 * LOG: Add cleaner functionality to ITS_Terminate() for transient transports.
 * LOG:
 * LOG: Revision 1.17  1998/07/30 14:52:38  mmiers
 * LOG: Duplicate update.  Added functions so that an app can send an event
 * LOG: without worry of the destination disappearing between lookup and
 * LOG: transmission.
 * LOG:
 * LOG: Revision 1.16  1998/07/17 20:18:03  ahanda
 * LOG: Fixe for Route Delete Entry
 * LOG:
 * LOG: Revision 1.15  1998/07/03 19:41:43  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.14  1998/07/02 23:12:30  hdivoux
 * LOG: Minor correction.
 * LOG:
 * LOG: Revision 1.13  1998/07/01 23:34:53  mmiers
 * LOG: Modify the route selection interface slightly.
 * LOG:
 * LOG: Revision 1.12  1998/06/25 00:22:08  ahanda
 * LOG: Allow for pad bytes in the context structure.
 * LOG:
 * LOG: Revision 1.11  1998/06/23 22:02:46  hdivoux
 * LOG: Minor correction.
 * LOG:
 * LOG: Revision 1.10  1998/06/23 00:36:12  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/06/18 23:39:34  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.8  1998/06/16 23:41:01  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.7  1998/06/16 21:52:12  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.6  1998/06/03 19:00:49  mmiers
 * LOG: Remove a flag and a callback pointer from global scope.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 16:35:34  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.4  1998/05/28 17:28:43  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 * LOG: Revision 1.3  1998/05/28 02:59:13  mmiers
 * LOG: More documentation, make application route selection single threaded,
 * LOG: and remove nasty tab characters from StandardHeaders.
 * LOG:
 * LOG: Revision 1.2  1998/05/27 22:08:08  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.1  1998/05/20 21:31:37  mmiers
 * LOG: Reimplement this in C for performance.
 * LOG:
 * LOG: Revision 1.5  1998/05/20 17:06:10  mmiers
 * LOG: Get the namespace thing right.  You must include its++.h if
 * LOG: you want to use the its namespace.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 19:59:45  ahanda
 * LOG: Added the Application Routing Code
 * LOG:
 * LOG: Revision 1.3  1998/05/19 17:11:56  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.2  1998/05/05 20:24:12  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/05/01 00:24:38  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:07  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <its_route.h>
#include <its_hash.h>
#include <its_mutex.h>
#include <its_rwlock.h>
#include <its_transports.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_route.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is used to clean the routing table for a worker
 *      after it has performed its task.  The intention is to clean up
 *      after the user to make sure that no dangling routing information
 *      is left either by mistake or due to abnormal termination.
 *
 *  Input Parameters:
 *      id - the instance id of the transport adding this route
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the instance is successfully cleaned, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_Clean(ITS_USHORT id)
{
    int ret;

    if ((ret = ROUTE_SS7Clean(id)) != ITS_SUCCESS)
    {
        return (ret);
    }

    return ROUTE_AppClean(id);
}
