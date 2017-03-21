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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:44  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:41  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:00  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2003/07/29 19:08:21  mmiers
 * LOG: Warning removal (ss7_route).  Decouple ENGINE and DBC (WIN32 build
 * LOG: issue).  Whoever added this might want to make sure this works for
 * LOG: them.
 * LOG:
 * LOG: Revision 8.1  2003/02/27 15:46:56  mmiers
 * LOG: Implementation was getting too large.  Split into
 * LOG: manageable chunks.
 * LOG:
 * LOG:
 * LOG: ----------------- Previously in engine.c: ---------------------
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:42:59  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.8  2003/01/29 13:15:53  yranade
 * LOG: Missing argument inst to ConstructObject in function EndTransport.
 * LOG:
 * LOG: Revision 7.7  2003/01/09 11:28:19  yranade
 * LOG: Avoid a core dump, which otherwise happening if the variables are not
 * LOG: defined in the XML file
 * LOG:
 * LOG: Revision 7.6  2002/12/31 09:04:53  akumar
 * LOG: Code to Parse the XML file and dump it in DMP file for variables
 * LOG: exchange_type and segmentation_supported
 * LOG:
 * LOG: Revision 7.5  2002/12/26 22:31:21  mmiers
 * LOG: Let the user specify the instance if they really know what they're
 * LOG: doing.  Don't document this feature, it's mostly for us.
 * LOG:
 * LOG: Revision 7.4  2002/12/04 02:42:17  randresol
 * LOG: Add PRC mask for MTP2 modifier
 * LOG:
 * LOG: Revision 7.3  2002/09/26 22:59:44  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.2  2002/08/29 15:46:33  mmiers
 * LOG: Add the deselector to the DTD
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:41  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.23  2002/08/22 20:34:03  omayor
 * LOG: Missing CHINA in Getting the mask for GlobalStart.
 * LOG:
 * LOG: Revision 6.22  2002/08/22 14:32:43  mmiers
 * LOG: Add china dispatchers
 * LOG:
 * LOG: Revision 6.21  2002/08/12 23:05:07  randresol
 * LOG: fix bug in StartPool for the workItemPool creation
 * LOG:
 * LOG: Revision 6.20  2002/07/30 16:52:56  mmiers
 * LOG: Avoid a core dump
 * LOG:
 * LOG: Revision 6.19  2002/07/05 22:24:12  yranade
 * LOG: Fix flag bug.
 * LOG:
 * LOG: Revision 6.18  2002/07/02 21:26:36  mmiers
 * LOG: Work on getting debug console interface added to engine.
 * LOG:
 * LOG: Revision 6.17  2002/06/27 22:38:34  ssharma
 * LOG: Bug fix for family.
 * LOG:
 * LOG: Revision 6.16  2002/06/21 22:49:20  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.15  2002/05/31 20:42:05  mmiers
 * LOG: Fixes for concerned routes
 * LOG:
 * LOG: Revision 6.14  2002/05/20 15:21:41  sjaddu
 * LOG: Merge from PR6 to current.
 * LOG:
 * LOG: Revision 6.13  2002/05/17 17:36:59  lbana
 * LOG: pass routing jkey value while constructing engine route object
 * LOG:
 * LOG: Revision 6.12  2002/05/15 16:27:55  hdivoux
 * LOG: Replaced functionName by function.
 * LOG:
 * LOG: Revision 6.11  2002/05/06 21:15:53  hdivoux
 * LOG: Cleanup after FT/HA integration.
 * LOG:
 * LOG: Revision 6.10  2002/04/30 15:31:20  hdivoux
 * LOG: Removed <<<<.
 * LOG:
 * LOG: Revision 6.9  2002/04/29 21:39:20  randresol
 * LOG: Add isInterNode flag in Border Transports definition
 * LOG:
 * LOG: Revision 6.8  2002/04/16 21:21:09  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.7  2002/04/15 21:06:58  hdivoux
 * LOG: Added configurable FtGroups.
 * LOG:
 * LOG: Revision 6.6  2002/04/09 22:45:44  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.5.2.1  2002/04/18 19:05:04  randresol
 * LOG: Add "isInterNode" field in Border Transports configuration
 * LOG:
 * LOG: Revision 6.5  2002/04/08 21:52:17  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.4  2002/04/05 23:29:19  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.3  2002/04/04 23:38:26  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 16:20:36  mmiers
 * LOG: Typo in GDI parse code.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.26.2.1  2002/03/22 17:29:58  ssharma
 * LOG: Fix the ISUP Attributes section.
 * LOG:
 * LOG: Revision 5.26  2002/02/14 19:43:14  mmiers
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 5.25  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.24  2002/02/01 22:47:00  mmiers
 * LOG: Bad strings.
 * LOG:
 * LOG: Revision 5.23  2002/01/30 16:09:45  mmiers
 * LOG: Add termination function.
 * LOG:
 * LOG: Revision 5.22  2002/01/21 20:27:21  mmiers
 * LOG: Add distribution awareness.
 * LOG:
 * LOG: Revision 5.21  2002/01/10 20:30:36  mmiers
 * LOG: Add SAAL capability
 * LOG:
 * LOG: Revision 5.20  2001/11/20 17:58:34  mmiers
 * LOG: Add debug console.
 * LOG:
 * LOG: Revision 5.19  2001/11/15 23:53:55  mmiers
 * LOG: Today's testing of MTP3.
 * LOG:
 * LOG: Revision 5.18  2001/11/13 17:37:29  mmiers
 * LOG: Make it work with windows too.
 * LOG:
 * LOG: Revision 5.17  2001/11/13 17:28:23  mmiers
 * LOG: NDEBUG isn't defined by Forte.
 * LOG:
 * LOG: Revision 5.16  2001/10/19 22:45:12  mmiers
 * LOG: Use strings for variant names.
 * LOG:
 * LOG: Revision 5.15  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.14  2001/10/18 22:06:42  mmiers
 * LOG: Add MTP2 capability to the SS7 dispatchers.
 * LOG:
 * LOG: Revision 5.13  2001/10/18 21:33:40  mmiers
 * LOG: Update engine to use destinations.
 * LOG:
 * LOG: Revision 5.12  2001/10/18 19:16:42  mmiers
 * LOG: Get engine in sync, add missing C++ guards in headers.
 * LOG:
 * LOG: Revision 5.11  2001/10/17 00:56:57  mmiers
 * LOG: Remove SLS stuff from engine.
 * LOG:
 * LOG: Revision 5.10  2001/10/16 20:25:07  hdivoux
 * LOG: Change in memset of static rinfo object to use sizeof of correct type.
 * LOG:
 * LOG: Revision 5.9  2001/10/02 21:44:10  mmiers
 * LOG: Dead route style removal.
 * LOG:
 * LOG: Revision 5.8  2001/09/24 21:37:17  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.7  2001/09/21 16:23:14  hdivoux
 * LOG: Update for comments.
 * LOG:
 * LOG: Revision 5.6  2001/09/20 19:16:15  hdivoux
 * LOG: Update for XML GCS configuration attributes.
 * LOG:
 * LOG: Revision 5.5  2001/08/31 14:23:09  mmiers
 * LOG: Brainstorming on MTP3, routing fixes.
 * LOG:
 * LOG: Revision 5.4  2001/08/24 17:10:24  mmiers
 * LOG: Routing, take three.
 * LOG:
 * LOG: Revision 5.3  2001/08/20 23:28:40  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.2  2001/08/20 22:50:54  mmiers
 * LOG: Get this in line with new routing scheme.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.31  2001/08/14 15:26:45  mmiers
 * LOG: Add link priority.
 * LOG:
 * LOG: Revision 4.30  2001/08/13 20:42:00  mmiers
 * LOG: Add routing key.
 * LOG:
 * LOG: Revision 4.29  2001/08/10 19:53:08  lbana
 * LOG: Remove tabs.
 * LOG:
 * LOG: Revision 4.28  2001/08/10 19:43:18  lbana
 * LOG: Add break when handling parser extension.
 * LOG:
 * LOG: Revision 4.27  2001/08/10 17:00:39  mmiers
 * LOG: Macro abuse.
 * LOG:
 * LOG: Revision 4.26  2001/08/07 14:59:28  mmiers
 * LOG: Fix numThreads leakage.
 * LOG:
 * LOG: Revision 4.25  2001/07/26 16:49:41  mmiers
 * LOG: UAL needed engine parse help.  Added this as an example.
 * LOG:
 * LOG: Revision 4.24  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.23  2001/07/23 22:17:13  mmiers
 * LOG: Finish the equality checks.  Finish up diff tomorrow.
 * LOG:
 * LOG: Revision 4.22  2001/07/19 22:02:40  mmiers
 * LOG: Continue adding equality checks.
 * LOG:
 * LOG: Revision 4.21  2001/07/19 16:58:33  mmiers
 * LOG: Make RM not bomb if ss7RM not present.  Continue diff.
 * LOG:
 * LOG: Revision 4.20  2001/07/18 23:10:35  mmiers
 * LOG: Fix a few cut/paste bugs Sandeep found.  Add info on the extensions
 * LOG: (will move to document end of PR5 devel).
 * LOG:
 * LOG: Revision 4.19  2001/07/18 21:43:41  mmiers
 * LOG: Start committing the buildable diff parts.
 * LOG:
 * LOG: Revision 4.18  2001/07/05 22:48:00  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 4.17  2001/06/22 21:01:06  mmiers
 * LOG: Finish integrating DSM and RM.  Need to add PeerDead notification
 * LOG: to complete.
 * LOG:
 * LOG: Revision 4.16  2001/06/22 18:33:27  mmiers
 * LOG: Move DSM to ENGINE.
 * LOG:
 * LOG: Revision 4.15  2001/06/21 15:18:19  mmiers
 * LOG: Add HMI and Alarm.
 * LOG:
 * LOG: Revision 4.14  2001/06/18 20:24:46  mmiers
 * LOG: Add diff framework.  Need to implement.
 * LOG:
 * LOG: Revision 4.13  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.12  2001/06/16 00:35:47  mmiers
 * LOG: Don't keep the handle around.
 * LOG:
 * LOG: Revision 4.11  2001/06/16 00:05:32  mmiers
 * LOG: Add redundancy info
 * LOG:
 * LOG: Revision 4.10  2001/06/14 23:17:25  mmiers
 * LOG: Add redundancy info
 * LOG:
 * LOG: Revision 4.9  2001/06/12 21:01:56  mmiers
 * LOG: Forgot to set the routes.
 * LOG:
 * LOG: Revision 4.8  2001/05/10 22:50:34  mmiers
 * LOG: Add AppOptions
 * LOG:
 * LOG: Revision 4.7  2001/05/10 22:37:14  mmiers
 * LOG: Better naming for work items.
 * LOG:
 * LOG: Revision 4.6  2001/05/10 21:05:51  mmiers
 * LOG: Add pre/post func to obj create.
 * LOG:
 * LOG: Revision 4.5  2001/05/10 17:00:31  mmiers
 * LOG: Forgot to parse UI cbs.
 * LOG:
 * LOG: Revision 4.4  2001/05/10 16:51:44  mmiers
 * LOG: User requested stuff (user intervention).
 * LOG:
 * LOG: Revision 4.3  2001/05/10 00:28:12  mmiers
 * LOG: Add custom dispatch.
 * LOG:
 * LOG: Revision 4.2  2001/05/09 23:19:48  mmiers
 * LOG: PR4 requests.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.2  2001/04/29 00:05:39  mmiers
 * LOG: A few changes required by the validating parser.
 * LOG:
 * LOG: Revision 1.1  2001/04/28 23:38:20  mmiers
 * LOG: Rearrange this to standard form.
 * LOG:
 * LOG: Revision 1.7  2001/04/27 21:42:53  yranade
 * LOG: Missing check for NULL after resolve.
 * LOG:
 * LOG: Revision 1.6  2001/04/26 16:01:22  mmiers
 * LOG: Spew error messages.
 * LOG:
 * LOG: Revision 1.5  2001/04/26 00:35:27  mmiers
 * LOG: Make the library name optional (resolve within the executable if
 * LOG: possible).
 * LOG:
 * LOG: Revision 1.4  2001/04/25 00:21:04  mmiers
 * LOG: Missing callback.
 * LOG:
 * LOG: Revision 1.3  2001/04/19 19:21:51  labuser
 * LOG: Debug.  Need to supply resources even for ITER
 * LOG:
 * LOG: Revision 1.2  2001/04/18 20:17:34  mmiers
 * LOG: Update the driver project files and add preAccept.
 * LOG:
 * LOG: Revision 1.1  2001/04/12 20:10:26  salaoui
 * LOG: Move to a more logical location.
 * LOG:
 * LOG: Revision 1.44  2001/04/12 19:13:41  labuser
 * LOG: Debugging with Yogesh.
 * LOG:
 * LOG: Revision 1.43  2001/04/06 17:48:58  mmiers
 * LOG: Updates.
 * LOG:
 * LOG: Revision 1.42  2001/04/05 23:07:00  mmiers
 * LOG: Debugging C++ API.
 * LOG:
 * LOG: Revision 1.41  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.40  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.39  2001/04/03 22:13:17  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.38  2001/04/03 20:38:06  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.37  2001/04/02 23:36:31  mmiers
 * LOG: Remove printf.
 * LOG:
 * LOG: Revision 1.36  2001/04/02 23:36:11  mmiers
 * LOG: PIC
 * LOG:
 * LOG: Revision 1.35  2001/04/02 21:21:51  mmiers
 * LOG: Align strings with parser.
 * LOG:
 * LOG: Revision 1.34  2001/04/02 19:50:41  mmiers
 * LOG: Solaris cleanup.
 * LOG:
 * LOG: Revision 1.33  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 1.32  2001/03/30 21:03:34  mmiers
 * LOG: Testing.
 * LOG:
 * LOG: Revision 1.31  2001/03/29 18:21:15  mmiers
 * LOG: Debugging the engine.  Runs now.
 * LOG:
 * LOG: Revision 1.30  2001/03/29 17:36:10  mmiers
 * LOG: Make shared libs.
 * LOG:
 * LOG: Revision 1.29  2001/03/29 03:07:33  mmiers
 * LOG: Start debugging.
 * LOG:
 * LOG: Revision 1.28  2001/03/28 23:37:42  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.27  2001/03/28 22:38:29  mmiers
 * LOG: It is coded.
 * LOG:
 * LOG: Revision 1.26  2001/03/28 00:44:26  mmiers
 * LOG: Finish management.
 * LOG:
 * LOG: Revision 1.25  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 1.24  2001/03/27 01:58:40  mmiers
 * LOG: Add options, sanitize the XML.  Need to do features and windows.
 * LOG:
 * LOG: Revision 1.23  2001/03/26 23:02:15  mmiers
 * LOG: Today's installment.  Now that I'm caught up on email, I should
 * LOG: be able to finish the parser tomorrow.
 * LOG:
 * LOG: Revision 1.22  2001/03/17 01:12:15  mmiers
 * LOG: Small cleanups for portability.
 * LOG:
 * LOG: Revision 1.21  2001/03/16 20:56:07  mmiers
 * LOG:
 * LOG: Ok, only resdb and parsing left.
 * LOG:
 * LOG: Revision 1.20  2001/03/15 23:17:04  mmiers
 * LOG: Implement the pools.  TODO is Worker and WorkItem (and CPP bindings).
 * LOG: Finish tomorrow.
 * LOG:
 * LOG: Revision 1.19  2001/03/15 01:27:10  mmiers
 * LOG: Updates for portability (fsm).  I think these were required anyway,
 * LOG: but VC doesn't complain if they aren't there.  The rest is thinking
 * LOG: about the thread pools.  I think I have a handle on this if I can
 * LOG: remember it tomorrow.  The comments should help.
 * LOG:
 * LOG: Revision 1.18  2001/03/14 23:44:01  mmiers
 * LOG: Build the pools and parsing is all that's left.
 * LOG:
 * LOG: Revision 1.17  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 1.16  2001/03/14 01:58:37  mmiers
 * LOG: Work on the implementation.  If I could get 3-4 uninterrupted
 * LOG: hours, this would be done.  TODO: the trace levels and the
 * LOG: thread pools.  The only other thing to do is the syntax tree
 * LOG: creator.
 * LOG:
 * LOG: Revision 1.15  2001/03/13 23:30:17  mmiers
 * LOG: A touchup.
 * LOG:
 * LOG: Revision 1.14  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.13  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 1.12  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 1.11  2001/03/09 21:26:23  mmiers
 * LOG: Get DLL linkage working.
 * LOG:
 * LOG: Revision 1.10  2001/03/02 22:44:14  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 1.9  2001/03/02 21:53:29  mmiers
 * LOG: Add management and stack objects.
 * LOG:
 * LOG: Revision 1.8  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 1.7  2001/03/01 22:52:10  mmiers
 * LOG: Add application class.
 * LOG:
 * LOG: Revision 1.6  2001/03/01 22:10:46  mmiers
 * LOG: Added thread pool.  Need application and serious thought on how
 * LOG: to glue it together.
 * LOG:
 * LOG: Revision 1.5  2001/03/01 02:38:35  mmiers
 * LOG: Add transport classes.  Think about doing this when
 * LOG: global start has *not* been called.
 * LOG:
 * LOG: Revision 1.4  2001/03/01 01:22:51  mmiers
 * LOG: Add trace config obj.
 * LOG:
 * LOG: Revision 1.3  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 1.2  2001/02/28 18:14:06  mmiers
 * LOG: OK, I think I know how this is going to go.  Time to start
 * LOG: implementing.
 * LOG:
 * LOG: Revision 1.1  2001/02/28 17:28:03  mmiers
 * LOG: Start the engine core.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ident "$Id: engine_procs.c,v 1.1.1.1 2007-10-08 11:11:17 bsccs2 Exp $"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <engine.h>
#include <expat.h>
#include "engine_intern.h"

ITSDLLAPI ENGINE_Application    application = NULL;

ITS_BOOLEAN ENGINE_inParser = ITS_FALSE;

static ENGINE_Application       tmpApp = NULL;
static ENGINE_LibCache          driver = NULL;

static XML_Parser   parser;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the necessary engine classes.
 *
 ****************************************************************************/
static void
InitClasses()
{
    int ret;

    ret = ITS_InitializeClass(itsCORE_Class);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_LibCacheClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_FeatureClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TraceClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_RouteClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_DestClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_LinkSetClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_LinkClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TransportSpecificsClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TransportCallbacksClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TransportClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_WorkItemClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ThreadPoolClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_SS7StackMgmtClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ISS7StackClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_FaultToleranceClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ParserExtensionClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ApplicationClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the necessary engine classes.
 *
 ****************************************************************************/
static void
TermClasses()
{
    ITS_DestroyClass(itsENGINE_ApplicationClass);
    ITS_DestroyClass(itsENGINE_ParserExtensionClass);
    ITS_DestroyClass(itsENGINE_FaultToleranceClass);
    ITS_DestroyClass(itsENGINE_ISS7StackClass);
    ITS_DestroyClass(itsENGINE_SS7StackMgmtClass);
    ITS_DestroyClass(itsENGINE_ThreadPoolClass);
    ITS_DestroyClass(itsENGINE_WorkItemClass);
    ITS_DestroyClass(itsENGINE_TransportCallbacksClass);
    ITS_DestroyClass(itsENGINE_TransportSpecificsClass);
    ITS_DestroyClass(itsENGINE_TransportClass);
    ITS_DestroyClass(itsENGINE_LinkClass);
    ITS_DestroyClass(itsENGINE_LinkSetClass);
    ITS_DestroyClass(itsENGINE_DestClass);
    ITS_DestroyClass(itsENGINE_RouteClass);
    ITS_DestroyClass(itsENGINE_TraceClass);
    ITS_DestroyClass(itsENGINE_FeatureClass);
    ITS_DestroyClass(itsENGINE_LibCacheClass);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print the current parser cursor location
 *
 ****************************************************************************/
void
ENGINE_LinePrint()
{
    fprintf(stderr, "At around line %d column %d in parsed text.\n",
            XML_GetCurrentLineNumber(parser),
            XML_GetCurrentColumnNumber(parser));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find (or create) a library within this application
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
ITSDLLAPI ENGINE_LibCache
ENGINE_LibGet(ENGINE_Application app, const char *libName)
{
    ITS_Object list;
    ENGINE_LibCache tmp;

    list = ENGINE_APP_LIB_CACHE(app);

    while (list != NULL)
    {
        if (libName == NULL && ENGINE_LC_LIB_NAME(list) == NULL)
        {
            return ((ENGINE_LibCache)list);
        }

        if (libName && ENGINE_LC_LIB_NAME(list) &&
            strcmp(ENGINE_LC_LIB_NAME(list), libName) == 0)
        {
            return ((ENGINE_LibCache)list);
        }

        list = ENGINE_LC_NEXT(list);
    }

    tmp = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                               app, libName);

    if (tmp == NULL &&
        (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
         SERVICE_GetType() == ST_NOT_SET))
    {
        printf("Error loading library: %s\n", DLSYM_Error());
        fflush(stdout);
    }

    return (tmp);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process the command line and parse the XML configuration.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *      xmlData - buffer containing the XML config
 *      xmlSize - size of xmlData
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ENGINE_Initialize(int argc, const char **argv, char *xmlData, int xmlSize)
{
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;

    buf = NULL;
    size = 0;

    /* init the syntax tree classes */
    InitClasses();

    /* set some defaults */
    SERVICE_InternalName = ITS_StripPath(argv[0]);
    SERVICE_DisplayedName = ITS_StripPath(argv[0]);

    /* set the config file extension */
    APPL_SetConfigFileExtension(XML_EXT_STRING);

    /* get some info from the command line */
    SERVICE_ProcessCommandLine(argc, argv);

    /* parse the XML config. */
    parser = XML_ParserCreate(NULL);
    ITS_C_ASSERT(parser != NULL);

    /* set the token functions */
    XML_SetElementHandler(parser, ENGINE_ElementStart, ENGINE_ElementEnd);

    /* open the ini */
#if !defined(NO_FILESYSTEM)
    xml = fopen(APPL_GetConfigFileName(), "r");
    ITS_C_ASSERT(xml != NULL);

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    ITS_C_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    ITS_C_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = malloc(size);
    ITS_C_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    ITS_C_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NUL */
    buf[size - 1] = 0;

    ENGINE_inParser = ITS_TRUE;
    if (xmlSize != 0)
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_FALSE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    else
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
#endif /* NO_FILESYSTEM */

    ENGINE_inParser = ITS_TRUE;
    if (xmlSize)
    {
        parseSuccessful = XML_Parse(parser, xmlData, xmlSize, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    ENGINE_inParser = ITS_FALSE;

    XML_ParserFree(parser);

#if !defined(NO_FILESYSTEM)
    /* clean up */
    if (buf)
    {
        free(buf);
    }
#endif

    /* reset for the resdb. */
    free(APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class));
    APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) = NULL;
    APPL_SetConfigFileExtension(INI_EXT_STRING);

    /* make sure we have an application */
    ITS_C_ASSERT(application != NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Run the engine.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *
 *  Return Value:
 *      Returns the service exit code.
 *
 ****************************************************************************/
ITSDLLAPI int
ENGINE_Run(int argc, const char **argv)
{
    DRIVER_MainFunc libMain;
    int ret;

    /* make sure we have a config */
    ITS_C_REQUIRE(application != NULL);

    /* Hook up the DBC. */
    DBC_Commit = ENGINE_Commit;

    /* load the driver and go */
    if (ENGINE_APP_CPP_BINDING(application))
    {
        /* CPP binding? */
#if defined(DEBUG) || defined(_DEBUG)
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_CPP_DEBUG_STRING);
#else /* NDEBUG */
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_CPP_STRING);
#endif /* NDEBUG */
    }
    else
    {
        /* Nope.  C binding. */
#if defined(DEBUG) || defined(_DEBUG)
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_C_DEBUG_STRING);
#else /* NDEBUG */
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_C_STRING);
#endif /* NDEBUG */
    }

    ITS_C_ASSERT(driver != NULL);

    /* lookup main */
    libMain = (DRIVER_MainFunc)DLSYM_Resolve(ENGINE_LC_LIBRARY(driver),
                                             DRIVER_MAIN_STRING);
    if (libMain == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   DRIVER_MAIN_STRING, DLSYM_Error());
            fflush(stdout);
        }
    }

    ITS_C_ASSERT(libMain != NULL);

    ret = (libMain)(argc, argv);

    /* clean up after the engine. */
    ITS_DestructObject((ITS_Object)application);
    application = NULL;
    driver = NULL;

    TermClasses();

    /* unhook the DBC */
    DBC_Commit = NULL;

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process the command line and parse the XML configuration, compare
 *      it with the current configuration and add/remove components as
 *      necessary.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *      xmlData - buffer containing the XML config
 *      xmlSize - size of xmlData
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ENGINE_Diff(int argc, const char **argv,
            char *xmlData, int xmlSize)
{
    DRIVER_DiffFunc diffMain;
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;

    buf = NULL;
    size = 0;

    /* make sure we're running and have a driver */
    ITS_C_ASSERT(application != NULL);
    ITS_C_ASSERT(driver != NULL);

    /* save current config */
    tmpApp = application;
    application = NULL;

    /* set the config file extension */
    APPL_SetConfigFileExtension(XML_EXT_STRING);

    /* get some info from the command line */
    SERVICE_ProcessCommandLine(argc, argv);

    /* parse the XML config. */
    parser = XML_ParserCreate(NULL);
    ITS_C_ASSERT(parser != NULL);

    /* set the token functions */
    XML_SetElementHandler(parser, ENGINE_ElementStart, ENGINE_ElementEnd);

    /* open the ini */
#if !defined(NO_FILESYSTEM)
    xml = fopen(APPL_GetConfigFileName(), "r");
    ITS_C_ASSERT(xml != NULL);

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    ITS_C_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    ITS_C_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = malloc(size);
    ITS_C_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    ITS_C_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NUL */
    buf[size - 1] = 0;

    ENGINE_inParser = ITS_TRUE;
    if (xmlSize != 0)
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_FALSE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    else
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
#endif /* NO_FILESYSTEM */

    ENGINE_inParser = ITS_TRUE;
    if (xmlSize)
    {
        parseSuccessful = XML_Parse(parser, xmlData, xmlSize, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    ENGINE_inParser = ITS_FALSE;

    XML_ParserFree(parser);

#if !defined(NO_FILESYSTEM)
    /* clean up */
    if (buf)
    {
        free(buf);
    }
#endif

    /* reset for the resdb. */
    free(APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class));
    APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) = NULL;
    APPL_SetConfigFileExtension(INI_EXT_STRING);

    /* diff the trees */
    diffMain = (DRIVER_DiffFunc)DLSYM_Resolve(ENGINE_LC_LIBRARY(driver),
                                              DRIVER_DIFF_STRING);
    if (diffMain == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   DRIVER_DIFF_STRING, DLSYM_Error());
            fflush(stdout);
        }
    }

    ITS_C_ASSERT(diffMain != NULL);

    ret = (diffMain)(tmpApp, application);

    /* restore environment */
    ITS_DestructObject((ITS_Object)tmpApp);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Stop the main loop.
 *
 *  Input Parameters:
 *      None.
 *
 *  Notes:
 *      This function does not synchronously stop the ENGINE.  Instead,
 *      it marks the main loop with a termination flag.  The engine will
 *      then wait for the thread pools to complete termination before
 *      returning (from ENGINE_Run).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ENGINE_Terminate()
{
    SERVICE_SetStopped();
}
