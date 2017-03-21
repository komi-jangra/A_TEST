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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:58:49  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/26 18:19:09  mmiers
 * LOG: Add dest to deselector
 * LOG:
 * LOG: Revision 6.3  2002/08/26 16:47:39  mmiers
 * LOG: Add deselector hook
 * LOG:
 * LOG: Revision 6.2  2002/04/30 15:56:34  mmiers
 * LOG: Fix up for more flexibility in route selection.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/01/24 21:52:42  mmiers
 * LOG: For app routing, if we aren't adding the entries always
 * LOG: call the callback.  Add transport finding by name.
 * LOG:
 * LOG: Revision 5.3  2001/11/21 21:51:30  hdivoux
 * LOG: Change for iterate hashtable function name.
 * LOG:
 * LOG: Revision 5.2  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/08/13 22:23:04  mmiers
 * LOG: Split routing into two subsystems.
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

#ident "$Id: its_app_route.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*
 * track down race conditions
 */
/* #define LOCAL_DEBUG */

/*
 * the complete table
 */
static HASH_Table   routeDB;

/*
 * gates
 */
static ITS_RWLOCK  gate;
static ITS_RWLOCK  selectorGate;

/*
 * RIDs for different lookup types
 */
#define ID_TO_APP_RID   1
#define APP_TO_ID_RID   2

/*
 * default selector
 */
ITS_USHORT ROUTE_SendToDefault(ITS_HDR*, ITS_EVENT*);

static ROUTE_AppSelector    appSelect = ROUTE_SendToDefault;
static ROUTE_AppDeselector  appDeselect = NULL;

#if defined(LOCAL_DEBUG)

static void
SanitizeApp(ROUTE_AppContext* list)
{
    ROUTE_AppContext* tmp;
    int cnt;

    for (cnt = 0, tmp = list;
         cnt < MAX_NUM_ENTS && tmp != NULL;
         cnt++, tmp = tmp->next)
    {
        if (tmp == (ROUTE_AppContext*)0xdddddddd ||
            tmp->next == (ROUTE_AppContext*)0xdddddddd)
        {
            ITS_C_ASSERT(ITS_FALSE);
        }
    }
}

#endif /* LOCAL_DEBUG */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function defines the behavior for default application routing;
 *      that is, this function determines the application/transport to send
 *      to if the user has NOT set the application selector callback function.
 *
 *  Input Parameters:
 *      h - a pointer to the message context that needs routing.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      This function will always return the instance number identifying
 *          the default application instance, or ITS_DEFAULT_USR_SRC.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_SendToDefault(ITS_HDR* h, ITS_EVENT* ev)
{
#if ROUTE_WANTS_PERFORMANCE
    ITS_TRACE_DEBUG(("ROUTE_SendToDefault: hdr type %02x context %04x\n",
                     h->type, h->context.dialogue_id));

    ROUTE_AddApplication(ITS_DEFAULT_USER_SRC, h);
#endif

    return (ITS_DEFAULT_USER_SRC);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This funtion allows the user to change the application selector
 *      function.  In essence, the application selector is a callback
 *      that is invoked for new units-of-work by IntelliSS7 APIs.
 *
 *  Input Parameters:
 *      ns - a pointer to the new application selector function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the callback was successfully set, a pointer to the last
 *          callback function is returned.
 *      If an error occurs, NULL is returned.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ROUTE_AppSelector
ROUTE_SetApplicationSelector(ROUTE_AppSelector ns)
{
    volatile ROUTE_AppSelector ret;

    ITS_TRACE_DEBUG(("ROUTE_SetApplicationSelector:\n"));

    if (RWLOCK_LockExclusive(&selectorGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SetApplicationSelector: couldn't acquire "
                         "mutex\n"));

        return (NULL);
    }

    ret = appSelect;

    if (ns == NULL)
    {
        ITS_TRACE_ERROR(("ROUTE_SetApplicationSelector: attempt to set "
                         "NULL appSelector\n"));

        ns = ROUTE_SendToDefault;
    }

    appSelect = ns;

    RWLOCK_UnlockExclusive(&selectorGate);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This funtion allows the user to change the application deselector
 *      function.  In essence, the application deselector is a callback
 *      that is invoked to remove units-of-work by IntelliSS7 APIs.
 *
 *  Input Parameters:
 *      ns - a pointer to the new application deselector function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the callback was successfully set, a pointer to the last
 *          callback function is returned (which may be NULL).
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ROUTE_AppDeselector
ROUTE_SetApplicationDeselector(ROUTE_AppDeselector ns)
{
    volatile ROUTE_AppDeselector ret;

    ITS_TRACE_DEBUG(("ROUTE_SetApplicationDeselector:\n"));

    if (RWLOCK_LockExclusive(&selectorGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SetApplicationDeselector: couldn't acquire "
                         "mutex\n"));

        return (NULL);
    }

    ret = appDeselect;

    appDeselect = ns;

    RWLOCK_UnlockExclusive(&selectorGate);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This predicate allows our stack to know when the user
 *      has not overridden the default application selector, and so
 *      can automatically add the default transport as the application
 *      context.
 *
 *  Input Parameters:
 *      ns - a pointer to the new application selector function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the callback was successfully set, a pointer to the last
 *          callback function is returned.
 *      If an error occurs, NULL is returned.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
ROUTE_IsApplicationSelectorDefault()
{
    volatile ITS_BOOLEAN ret = ITS_FALSE;

    ITS_TRACE_DEBUG(("ROUTE_IsApplicationSelectorDefault:\n"));

    if (RWLOCK_LockShared(&selectorGate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SetApplicationSelector: couldn't acquire "
                         "mutex\n"));

        return (ret);
    }

    ret = (appSelect == ROUTE_SendToDefault) ? ITS_TRUE : ITS_FALSE;

    RWLOCK_UnlockShared(&selectorGate);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows the application writer to add an application
 *      to the routing table.  The application MUST provide context information
 *      when adding the route.  Note that the same application instance can
 *      be added multiple times, as long as the context information is
 *      different fer each addition.
 *
 *  Input Parameters:
 *      id - the application/transport instance to add
 *      hdr - a pointer to the context information for this addition
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route is successfully added, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_AddApplication(ITS_USHORT id, ITS_HDR* hdr)
{
    ROUTE_AppContext* ent = NULL, * tmp;
    int ctxt = 0;

    ctxt = hdr->type << 16 | hdr->context.dialogue_id;

    ITS_TRACE_DEBUG(("ROUTE_AddApplication:\n"));

    if (RWLOCK_LockExclusive(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_AddApplication: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* find by context */
    if (HASH_FindEntry(routeDB, APP_TO_ID_RID, ctxt, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        for (tmp = ent; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->context.type == hdr->type &&
                tmp->context.context.dialogue_id ==
                    hdr->context.dialogue_id &&
                tmp->id == id)
            {
                ITS_TRACE_ERROR(("ROUTE_AddApplication: duplicate application "
                                 "context\n"));

                RWLOCK_UnlockExclusive(&gate);

                return (ITS_EROUTEFAIL);
            }
        }
    }

    if ((tmp = (ROUTE_AppContext*)calloc(1, sizeof(ROUTE_AppContext)))
        == NULL)
    {
        ITS_TRACE_ERROR(("ROUTE_AddApplication: out of memory\n"));

        RWLOCK_UnlockExclusive(&gate);

        return (ITS_ENOMEM);
    }

    tmp->next = ent;
    tmp->id = id;
    tmp->context = *hdr;

#if defined(LOCAL_DEBUG)
    SanitizeApp(tmp);
#endif

    HASH_AddEntry(routeDB, APP_TO_ID_RID, ctxt, (ITS_POINTER)tmp);

    /* find by id */
    ent = NULL;
    if (HASH_FindEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        for (tmp = ent; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->context.type == hdr->type &&
                tmp->context.context.dialogue_id ==
                    hdr->context.dialogue_id)
            {
                ITS_TRACE_ERROR(("ROUTE_AddApplication: duplicate application "
                                 "context\n"));

                RWLOCK_UnlockExclusive(&gate);

                return (ITS_EROUTEFAIL);
            }
        }
    }

    if ((tmp = (ROUTE_AppContext*)calloc(1, sizeof(ROUTE_AppContext)))
        == NULL)
    {
        ITS_TRACE_ERROR(("ROUTE_AddApplication: out of memory\n"));

        RWLOCK_UnlockExclusive(&gate);

        return (ITS_ENOMEM);
    }

    tmp->next = ent;
    tmp->id = id;
    tmp->context = *hdr;

#if defined(LOCAL_DEBUG)
    SanitizeApp(tmp);
#endif

    HASH_AddEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER)tmp);

    RWLOCK_UnlockExclusive(&gate);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is used by IntelliSS7 APIs to automatically select
 *      applications to deliver messages to.  The application must have been
 *      added by the user before this function can succeed.
 *
 *  Input Parameters:
 *      hdr - a pointer to the context information to route by
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If a route is found for this context, the application/transport
 *          instance id is returned.
 *      If no route is found, ITS_NO_SRC is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
ROUTE_SelectApplication(ITS_HDR* hdr, ITS_EVENT* ev, ITS_BOOLEAN callCallback)
{
    ROUTE_AppContext* ent = NULL, * tmp;
    int ctxt;
    ITS_USHORT ret = ITS_NO_SRC;

    ctxt = hdr->type << 16 | hdr->context.dialogue_id;

    ITS_TRACE_DEBUG(("ROUTE_SelectApplication: ctxt: %08x\n", ctxt));

    if (RWLOCK_LockShared(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SelectApplication: couldn't acquire mutex\n"));

        if (ev->data)
        {
            ITS_Free(ev->data);

            ev->data = NULL;
        }

        return (ITS_INVALID_SRC);
    }

    /* find by context */
    if (HASH_FindEntry(routeDB, APP_TO_ID_RID, ctxt, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        for (tmp = ent; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->context.type == hdr->type &&
                tmp->context.context.dialogue_id ==
                    hdr->context.dialogue_id)
            {
                volatile ITS_USHORT thisId = tmp->id;

                ITS_TRACE_DEBUG(("ROUTE_SelectApplication: found id %04x "
                                 "for context %08x\n", tmp->id, ctxt));

                RWLOCK_UnlockShared(&gate);

                return thisId;
            }
        }
    }

    RWLOCK_UnlockShared(&gate);

#if !ROUTE_WANTS_PERFORMANCE
    if (callCallback)
#else
    if (ITS_TRUE)
#endif
    {
        ITS_TRACE_DEBUG(("ROUTE_SelectApplication: calling appSelector\n"));

        ret = (*appSelect)(hdr, ev);

        ITS_TRACE_DEBUG(("ROUTE_SelectApplication: appSelector returned %04x\n",
                         ret));
    }

    if (ret == ITS_INVALID_SRC || ret == ITS_NO_SRC)
    {
        if (ev->data)
        {
            ITS_Free(ev->data);

            ev->data = NULL;
        }
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used by IntelliSS7 APIs to deselect
 *      applications after messages have been delivered.
 *
 *  Input Parameters:
 *      hdr - a pointer to the context information to route by
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
 *  Notes:
 *      This function performs no locking.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ROUTE_DeselectApplication(ITS_USHORT id, ITS_HDR *hdr)
{
    if (appDeselect)
    {
        (*appDeselect)(id, hdr);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows an application to remove a route to itself
 *      based on the context by which the route was added.  Applications
 *      should use this function at the end of a unit-of-work to indicate
 *      that it will no longer accept further messages in that context.
 *
 *  Input Parameters:
 *      id - the transport/application instance to remove from the routing
 *          table
 *      hdr - a pointer to the context information for this particular route
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the route is successfully deleted, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_DeleteApplication(ITS_USHORT id, ITS_HDR* hdr)
{
    ROUTE_AppContext* ent = NULL, ** tmp;
    int ctxt;

    ctxt = hdr->type << 16 | hdr->context.dialogue_id;

    ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: ctxt: %08x\n", ctxt));

    if (RWLOCK_LockExclusive(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_DeleteApplication: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* find by context */
    if (HASH_FindEntry(routeDB, APP_TO_ID_RID, ctxt, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        for (tmp = &ent; *tmp != NULL; )
        {
            if ((*tmp)->context.type == hdr->type &&
                (*tmp)->context.context.dialogue_id ==
                    hdr->context.dialogue_id &&
                (*tmp)->id == id)
            {
                ROUTE_AppContext* t = *tmp;

                ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: deleting context "
                                 "for id %04x\n", (*tmp)->id));

                *tmp = (*tmp)->next;

                free(t);

                break;
            }

            if (*tmp)
            {
                tmp = &(*tmp)->next;
            }
        }
    }

    if (ent == NULL)
    {
        ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: deleting dead list\n"));

        HASH_DeleteEntry(routeDB, APP_TO_ID_RID, ctxt);
    }
    else
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: updating altered list\n"));

        HASH_AddEntry(routeDB, APP_TO_ID_RID, ctxt, (ITS_POINTER)ent);
    }

    ent = NULL;

    /* find by id */
    if (HASH_FindEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        for (tmp = &ent; *tmp != NULL; )
        {
            if ((*tmp)->context.type == hdr->type &&
                (*tmp)->context.context.dialogue_id ==
                    hdr->context.dialogue_id &&
                (*tmp)->id == id)
            {
                ROUTE_AppContext* t = *tmp;

                ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: deleting id "
                                 "for id %04x\n", (*tmp)->id));

                *tmp = (*tmp)->next;

                free(t);

                break;
            }

            if (*tmp)
            {
                tmp = &(*tmp)->next;
            }
        }
    }

    if (ent == NULL)
    {
        ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: deleting dead list\n"));

        HASH_DeleteEntry(routeDB, ID_TO_APP_RID, id);
    }
    else
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        ITS_TRACE_DEBUG(("ROUTE_DeleteApplication: updating altered list\n"));

        HASH_AddEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER)ent);
    }

    RWLOCK_UnlockExclusive(&gate);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows IntelliSS7 APIs to determine if an application
 *      has added routes to itself.
 *
 *  Input Parameters:
 *      id - the application/transport instance to search for in the
 *          application routing table
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If an application has registered routes to itself, ITS_TRUE is
 *          returned.
 *      If an error occurs, or no routes have been registered, ITS_FALSE is
 *          returned.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
ROUTE_IsApplication(ITS_USHORT id)
{
    ROUTE_AppContext* ent = NULL;

    ITS_TRACE_DEBUG(("ROUTE_IsApplication: id %04x\n", id));

    if (RWLOCK_LockShared(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_IsApplication: couldn't acquire mutex\n"));

        return (ITS_FALSE);
    }

    /* find by id */
    if (HASH_FindEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        ITS_TRACE_DEBUG(("ROUTE_IsApplication: id is application\n"));

        RWLOCK_UnlockShared(&gate);

        return (ITS_TRUE);
    }

    ITS_TRACE_DEBUG(("ROUTE_IsApplication: id is not application\n"));

    RWLOCK_UnlockShared(&gate);

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is used by IntelliSS7 APIs to automatically select
 *      applications to deliver this event to.
 *
 *  Input Parameters:
 *      hdr - a pointer to the context information to route by
 *      ev - the event to deliver
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If a route is found for this context, the application/transport
 *          instance is used as the destination of the event.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ROUTE_SendToApplication(ITS_HDR* hdr, ITS_EVENT* ev)
{
    ROUTE_AppContext* ent = NULL, * tmp;
    int ctxt;

    ctxt = hdr->type << 16 | hdr->context.dialogue_id;

    ITS_TRACE_DEBUG(("ROUTE_SendToApplication: ctxt %08x\n", ctxt));

    if (RWLOCK_LockShared(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_SendToApplication: couldn't acquire mutex\n"));

        if (ev->data)
        {
            ITS_Free(ev->data);

            ev->data = NULL;
        }

        return (ITS_EBADMUTEX);
    }

    /* find by context */
    if (HASH_FindEntry(routeDB, APP_TO_ID_RID, ctxt, (ITS_POINTER *)&ent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(ent);
#endif

        for (tmp = ent; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->context.type == hdr->type &&
                tmp->context.context.dialogue_id ==
                    hdr->context.dialogue_id)
            {
                volatile ITS_USHORT id = tmp->id;

                ITS_TRACE_DEBUG(("ROUTE_SendToApplication: id %04x\n",
                                 tmp->id));

                RWLOCK_UnlockShared(&gate);

                return TRANSPORT_PutEvent(id, ev);
            }
        }
    }

    RWLOCK_UnlockShared(&gate);

    /* no send happened.  Send to default if no selector is registered */
    ctxt = ITS_ENOTRANSPORT;
    if (ROUTE_IsApplicationSelectorDefault())
    {
        ctxt = TRANSPORT_PutEvent(ITS_DEFAULT_USER_SRC, ev);
    }
    else
    {
        ITS_USHORT ret = ITS_NO_SRC;

        ret = (*appSelect)(hdr, ev);

        if (ret != ITS_INVALID_SRC && ret != ITS_NO_SRC)
        {
            ctxt = TRANSPORT_PutEvent(ret, ev);
        }
    }

    if (ev->data)
    {
        ITS_Free(ev->data);

        ev->data = NULL;
    }

    return (ctxt);
}

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
ROUTE_AppClean(ITS_USHORT id)
{
    ROUTE_AppContext* aent = NULL, ** atmp, **atmp2, * aent2 = NULL;
    int ctxt;

    ITS_TRACE_DEBUG(("ROUTE_Clean: id %04x\n", id));

    if (RWLOCK_LockExclusive(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_Clean: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    aent = NULL;

    /* find by id */
    if (HASH_FindEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER *)&aent)
        == ITS_SUCCESS)
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(aent);
#endif

        for (atmp = &aent; *atmp != NULL; )
        {
            if ((*atmp)->id == id)
            {
                ROUTE_AppContext* t = *atmp;

                *atmp = (*atmp)->next;

                ctxt = t->context.type << 16 | t->context.context.dialogue_id;

                ITS_TRACE_DEBUG(("ROUTE_Clean: delete id ctxt: %08x\n",
                                 ctxt));

                /* find by context */
                aent2 = NULL;
                if (HASH_FindEntry(routeDB, APP_TO_ID_RID, ctxt,
                                   (ITS_POINTER *)&aent2) == ITS_SUCCESS)
                {
#if defined(LOCAL_DEBUG)
                    SanitizeApp(aent2);
#endif

                    for (atmp2 = &aent2; *atmp2 != NULL; )
                    {
                        if ((*atmp2)->context.type == t->context.type &&
                            (*atmp2)->context.context.dialogue_id ==
                                t->context.context.dialogue_id &&
                            (*atmp2)->id == id)
                        {
                            ROUTE_AppContext* t = *atmp2;

                            ITS_TRACE_DEBUG(("ROUTE_Clean: delete ctxt: %08x\n",
                                             ctxt));

                            *atmp2 = (*atmp2)->next;

                            free(t);
                        }

                        if (*atmp2)
                        {
                            atmp2 = &(*atmp2)->next;
                        }
                    }
                }

                if (aent2 == NULL)
                {
                    ITS_TRACE_DEBUG(("ROUTE_Clean: deleting dead list\n"));

                    HASH_DeleteEntry(routeDB, APP_TO_ID_RID, ctxt);
                }
                else
                {
#if defined(LOCAL_DEBUG)
                    SanitizeApp(aent2);
#endif

                    ITS_TRACE_DEBUG(("ROUTE_Clean: saving altered list\n"));

                    HASH_AddEntry(routeDB, APP_TO_ID_RID,
                                  ctxt, (ITS_POINTER)aent2);
                }

                free(t);
            }

            if (*atmp)
            {
                atmp = &(*atmp)->next;
            }
        }
    }

    if (aent == NULL)
    {
        ITS_TRACE_DEBUG(("ROUTE_Clean: deleting dead list\n"));

        HASH_DeleteEntry(routeDB, ID_TO_APP_RID, id);
    }
    else
    {
#if defined(LOCAL_DEBUG)
        SanitizeApp(aent2);
#endif

        ITS_TRACE_DEBUG(("ROUTE_Clean: saving altered list\n"));

        HASH_AddEntry(routeDB, ID_TO_APP_RID, id, (ITS_POINTER)aent);
    }

    RWLOCK_UnlockExclusive(&gate);

    return (ITS_SUCCESS);
}

/****************************************************************************
 *
 * Routing hashtable dump.
 *
 ****************************************************************************/

/* Local contants. */

#define PRINT_DATA_MAX_SIZE     1024
#define HEADER_MAX_SIZE         512
#define FOOTER_MAX_SIZE         256
#define PRINT_BUF_MAX_SIZE      64


static int
DumpEntryDataAppContext(ITS_POINTER data, char** pStrDump)
{
    char printBuf[PRINT_BUF_MAX_SIZE];

    ROUTE_AppContext* appContext = (ROUTE_AppContext*)data;

    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    *pStrDump = (char *)calloc(PRINT_DATA_MAX_SIZE, sizeof(char));

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    while (appContext)
    {
        strcat(*pStrDump, "------------------------------\n");

        /* HDR.type. */

        strcat(*pStrDump, "HDR.type:    <");

        sprintf(printBuf, "%02X", appContext->context.type);
        strcat(*pStrDump, printBuf);
        memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

        strcat(*pStrDump, ">\n");

        /* HDR.context (ITS_USHORT). */

        strcat(*pStrDump, "HDR.context: <");

        sprintf(printBuf, "%u", (unsigned)appContext->context.context.ssn);
        strcat(*pStrDump, printBuf);
        memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

        strcat(*pStrDump, ">\n");

        /* ID. */

        strcat(*pStrDump, "Id:          <");

        sprintf(printBuf, "%u", appContext->id);
        strcat(*pStrDump, printBuf);
        memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

        strcat(*pStrDump, ">\n");

        strcat(*pStrDump, "------------------------------\n");

        appContext = appContext->next;
    }

    return ITS_SUCCESS;
}


/*****************************
 * ROUTE_DumpIdToAppHashtable.
 *****************************/
ITSDLLAPI int 
ROUTE_DumpIdToAppHashtable(char** pStrDump)
{
    char header[HEADER_MAX_SIZE];
    char footer[FOOTER_MAX_SIZE];
    char printBuf[PRINT_BUF_MAX_SIZE];
    size_t vtableSize = 0;
    char* strDumpEntries = NULL;
    int sigma;
    int res;

    ITS_TRACE_DEBUG(("ROUTE_DumpIdToApp:\n"));

    memset(header, 0, HEADER_MAX_SIZE);
    memset(footer, 0, FOOTER_MAX_SIZE);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    *pStrDump = NULL;

    if (RWLOCK_LockShared(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_DumpIdToApp: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    strcat(header, "--------------------------------------------------\n");
    strcat(header, "-- ID to App Application Hashtable Begin --\n");
    strcat(header, "--------------------------------------------------\n");
    strcat(header, "Size: <");

    vtableSize = HASH_VTableSize(routeDB, ID_TO_APP_RID);
    sprintf(printBuf, "%u", vtableSize);
    strcat(header, printBuf);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    strcat(header, ">\n");
    strcat(header, "--------------------------------------------------\n");

    res = HASH_VTableDump(routeDB,
                          ID_TO_APP_RID,
                          &strDumpEntries,
                          DumpEntryDataAppContext);

    if (res != ITS_SUCCESS)
    {
        if (strDumpEntries != NULL)
        {
            free(strDumpEntries);
        }

        RWLOCK_UnlockShared(&gate);

        return res;
    }

    strcat(footer, "--------------------------------------------------\n");
    strcat(footer, "-- ID to App Route Hashtable End --\n");
    strcat(footer, "--------------------------------------------------\n");

    sigma = strlen(header) + strlen(strDumpEntries) + strlen(footer);

    *pStrDump = (char *)calloc(sigma + 1, sizeof(char));

    if (*pStrDump == NULL)
    {
        free(strDumpEntries);

        RWLOCK_UnlockShared(&gate);

        return ITS_ENOMEM;
    }

    strcat(*pStrDump, header);
    strcat(*pStrDump, strDumpEntries);
    strcat(*pStrDump, footer);

    free(strDumpEntries);

    RWLOCK_UnlockShared(&gate);

    return ITS_SUCCESS;
}


/*****************************
 * ROUTE_DUmpAppToIdHashtable.
 *****************************/
ITSDLLAPI int 
ROUTE_DumpAppToIdHashtable(char** pStrDump)
{
    char header[HEADER_MAX_SIZE];
    char footer[FOOTER_MAX_SIZE];
    char printBuf[PRINT_BUF_MAX_SIZE];
    size_t vtableSize = 0;
    char* strDumpEntries = NULL;
    int sigma;
    int res;

    ITS_TRACE_DEBUG(("ROUTE_DumpAppToId:\n"));

    memset(header, 0, HEADER_MAX_SIZE);
    memset(footer, 0, FOOTER_MAX_SIZE);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    *pStrDump = NULL;

    if (RWLOCK_LockShared(&gate) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_DumpAppToId: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    strcat(header, "--------------------------------------------------\n");
    strcat(header, "-- App to Id Application Hashtable Begin --\n");
    strcat(header, "--------------------------------------------------\n");
    strcat(header, "Size: <");

    vtableSize = HASH_VTableSize(routeDB, APP_TO_ID_RID);
    sprintf(printBuf, "%u", vtableSize);
    strcat(header, printBuf);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    strcat(header, ">\n");
    strcat(header, "--------------------------------------------------\n");

    res = HASH_VTableDump(routeDB,
                          APP_TO_ID_RID,
                          &strDumpEntries,
                          DumpEntryDataAppContext);

    if (res != ITS_SUCCESS)
    {
        if (strDumpEntries != NULL)
        {
            free(strDumpEntries);
        }

        RWLOCK_UnlockShared(&gate);

        return res;
    }

    strcat(footer, "--------------------------------------------------\n");
    strcat(footer, "-- App to Id Route Hashtable End --\n");
    strcat(footer, "--------------------------------------------------\n");

    sigma = strlen(header) + strlen(strDumpEntries) + strlen(footer);

    *pStrDump = (char *)calloc(sigma + 1, sizeof(char));

    if (*pStrDump == NULL)
    {
        free(strDumpEntries);

        RWLOCK_UnlockShared(&gate);

        return ITS_ENOMEM;
    }

    strcat(*pStrDump, header);
    strcat(*pStrDump, strDumpEntries);
    strcat(*pStrDump, footer);

    free(strDumpEntries);

    RWLOCK_UnlockShared(&gate);

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the routing subsystem to a ready state.
 *      The routing subsystem will not work correctly if this funtion is
 *      not invoked first.
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
 *      If the routing subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_Terminate()
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    int ret;

    ITS_TRACE_DEBUG(("ROUTE_Initialize:\n"));

    if ((routeDB = HASH_CreateTable()) == NULL)
    {
        ITS_TRACE_ERROR(("ROUTE_Initialize: couldn't create hash table\n"));

        return (ITS_ENOMEM);
    }

    if ((ret = RWLOCK_CreateLock(&gate)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_Initialize: couldn't create mutex\n"));

        HASH_DeleteTable(routeDB);

        return (ret);
    }

    if ((ret = RWLOCK_CreateLock(&selectorGate)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_Initialize: couldn't create selector "
                         "mutex\n"));

        RWLOCK_DeleteLock(&gate);

        HASH_DeleteTable(routeDB);

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete dead app routes before terminating.
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
DeleteAppRoutes(ITS_INT context, ITS_POINTER data,
                void *in, void *out)
{
    free(data);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the routing subystem.  It frees all resources
 *      that have been allocated for routing.
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
 *  Notes:
 *      This function must NOT be called until all routing entities have
 *      terminated.  The results of attempting to route after the routing
 *      subsystem has been terminated is undefined.
 *
 *  See Also:
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("ROUTE_Terminate:\n"));

    RWLOCK_DeleteLock(&selectorGate);
    RWLOCK_DeleteLock(&gate);

    HASH_VTableIterate(routeDB, APP_TO_ID_RID,
                       NULL, NULL, DeleteAppRoutes);

    HASH_VTableIterate(routeDB, ID_TO_APP_RID,
                       NULL, NULL, DeleteAppRoutes);

    HASH_DeleteTable(routeDB);
}

/*
 * the class record
 */
ITSDLLAPI ROUTE_ClassRec itsAPP_ROUTE_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        ROUTE_CLASS_NAME,               /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsAPP_ROUTE_Class = (ITS_Class)&itsAPP_ROUTE_ClassRec;
