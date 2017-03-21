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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/07 15:27:42  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/29 21:36:37  randresol
 * LOG: define INTERNODE_STRING
 * LOG:
 * LOG: Revision 6.1.2.1  2002/04/18 19:24:39  randresol
 * LOG: Add changes for redundant MTP3
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.13  2002/01/24 21:50:53  mmiers
 * LOG: Add finding a transport by name.
 * LOG:
 * LOG: Revision 5.12  2002/01/10 21:05:05  mmiers
 * LOG: Dummy methods
 * LOG:
 * LOG: Revision 5.11  2002/01/10 18:07:32  mmiers
 * LOG: Add TransportRef class.
 * LOG:
 * LOG: Revision 5.10  2002/01/10 17:37:38  mmiers
 * LOG: Finish off the refcounting code.
 * LOG:
 * LOG: Revision 5.9  2002/01/09 23:31:15  mmiers
 * LOG: Add the C++ interface.
 * LOG:
 * LOG: Revision 5.8  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.7  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.6  2001/11/20 17:42:01  mmiers
 * LOG: Finish DBC conversion.
 * LOG:
 * LOG: Revision 5.5  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.4  2001/09/19 00:53:36  mmiers
 * LOG: Bugs found in cross platform build.
 * LOG:
 * LOG: Revision 5.3  2001/09/18 22:18:27  mmiers
 * LOG: Add internal transports API to kill races.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/06/27 22:57:42  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.5  2001/05/03 15:30:48  mmiers
 * LOG: C++ fixes.
 * LOG:
 * LOG: Revision 4.4  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.3  2001/05/02 19:06:01  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.2  2001/05/02 00:01:50  mmiers
 * LOG: Finish alarm implementation.  HMI just needs the monitor
 * LOG: algorithm.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.19  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.18  2001/04/25 01:17:01  mmiers
 * LOG: Better encapsulation.  We need the lock anyway.
 * LOG:
 * LOG: Revision 3.17  2001/04/25 01:04:24  mmiers
 * LOG: Before PR4 is cut, add in the HMI requirements for transport.
 * LOG:
 * LOG: Revision 3.16  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 3.15  2001/03/16 23:18:46  mmiers
 * LOG: Ok, everything done but the parser.
 * LOG:
 * LOG: Revision 3.14  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.13  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.12  2001/03/02 23:04:04  mmiers
 * LOG: Cross platform cleanup.
 * LOG:
 * LOG: Revision 3.11  2001/03/02 18:27:17  mmiers
 * LOG: Add work item.  Need to add WorkItemPool.
 * LOG:
 * LOG: Revision 3.10  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.9  2001/02/06 17:29:12  mmiers
 * LOG: Allow no lock callbacks.
 * LOG:
 * LOG: Revision 3.8  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.7  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.6  2001/01/15 17:36:33  mmiers
 * LOG: Bug fixes from Olivier
 * LOG:
 * LOG: Revision 3.5  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.4  2000/11/22 18:03:45  mmiers
 * LOG: More SCTP integration.
 * LOG:
 * LOG: Revision 3.3  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.3  2000/11/09 23:04:25  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.2  2000/10/04 17:07:15  omayor
 * LOG: Added Duplicate PC and SSN Strings for initialization in
 * LOG: TRANSPORT_RegisterSS7Data().
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.11  2000/06/02 02:05:16  mmiers
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
 * LOG: Revision 2.9  2000/05/15 22:34:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.8  2000/05/11 22:17:25  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for link sets.
 * LOG:
 * LOG: Revision 2.7  2000/05/11 20:44:30  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the IMAL heartbeat.
 * LOG:
 * LOG: Revision 2.6  2000/03/18 21:03:34  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.5  2000/02/14 19:17:37  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.4  2000/01/12 00:19:09  mmiers
 * LOG:
 * LOG:
 * LOG: Keep NMS happy.
 * LOG:
 * LOG: Revision 2.3  2000/01/11 21:48:03  lbana
 * LOG:
 * LOG: Added padding to Transport_Control to keep NMS hapy
 * LOG:
 * LOG: Revision 2.2  1999/12/22 17:38:12  mmiers
 * LOG:
 * LOG:
 * LOG: Correct the conversion macro.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:52:36  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:49  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.62  1999/11/10 18:27:18  mmiers
 * LOG:
 * LOG:
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.61  1999/11/10 00:09:26  mmiers
 * LOG:
 * LOG:
 * LOG: In goes the mods.
 * LOG:
 * LOG: Revision 1.60  1999/11/05 20:30:07  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up first cut of GDI, remove volatile qualifier from
 * LOG: FindTransport.
 * LOG:
 * LOG: Revision 1.59  1999/10/25 23:38:49  mmiers
 * LOG:
 * LOG:
 * LOG: Documentation code for the programming impaired.
 * LOG:
 * LOG: Revision 1.58  1999/10/25 18:28:10  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.57  1999/10/07 22:44:27  labuser
 * LOG:
 * LOG:
 * LOG: Make the linkage of these extern "C".
 * LOG:
 * LOG: Revision 1.56  1999/09/01 00:53:30  mmiers
 * LOG:
 * LOG:
 * LOG: This work makes the transport system a little more sane.  What I
 * LOG: did was make the Transport class implement the default behavior
 * LOG: for transports, which should make things like:
 * LOG:     Transport tc = transport->GetTC();
 * LOG: work when you say
 * LOG:     tc.GetNextEvent(ev);
 * LOG:
 * LOG: Revision 1.55  1999/07/23 20:07:58  mmiers
 * LOG:
 * LOG:
 * LOG: Separate out registration/deregistration of the SS7 routing info.
 * LOG: This makes this callable for dynamic style transports.
 * LOG:
 * LOG: Revision 1.54  1999/06/28 22:10:18  mmiers
 * LOG:
 * LOG:
 * LOG: I give up on friend functions.
 * LOG:
 * LOG: Revision 1.53  1999/06/28 21:47:30  skarmakar
 * LOG:
 * LOG:
 * LOG: A fix for the namespace craziness.
 * LOG:
 * LOG: Revision 1.52  1999/06/28 21:08:57  skarmakar
 * LOG:
 * LOG:
 * LOG: Try this one out for friend "C" functions.
 * LOG:
 * LOG: Revision 1.51  1999/06/23 21:21:18  rsonak
 * LOG:
 * LOG:
 * LOG: Rework the iterative/dynamic socket server (more tightly coupled
 * LOG: with infrastructure).
 * LOG:
 * LOG: Revision 1.50  1999/03/25 22:28:03  mmiers
 * LOG:
 * LOG: Add a memory leak test, and an inline to retrieve the C transport from
 * LOG: a C++ transport.
 * LOG:
 * LOG: Revision 1.49  1999/02/04 22:26:37  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.48  1998/11/18 21:07:39  mmiers
 * LOG: Minor build tweaks.
 * LOG:
 * LOG: Revision 1.47  1998/11/11 00:44:47  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.46  1998/11/10 02:48:41  mmiers
 * LOG: Add concerned strings.
 * LOG:
 * LOG: Revision 1.45  1998/11/05 03:26:51  mmiers
 * LOG: Add serialization counters to transports.
 * LOG:
 * LOG: Revision 1.44  1998/11/04 20:00:30  mmiers
 * LOG: Change this around a bit.
 * LOG:
 * LOG: Revision 1.43  1998/11/04 19:48:38  mmiers
 * LOG: Add callback invocation to TRANSPORT_SetState() and
 * LOG: TRANSPORT_SetCongestion()
 * LOG:
 * LOG: Revision 1.42  1998/11/04 02:47:22  mmiers
 * LOG: Remove ITS_SS7_LOCAL_ROUTE, it is irrelevant, we don't do that.
 * LOG: Add congestion callback list, it will be used for SS7.
 * LOG: Update TODO to reflect what needs to be added.
 * LOG:
 * LOG: Revision 1.41  1998/11/03 02:56:10  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.40  1998/10/15 03:09:31  mmiers
 * LOG: Fix SEE ALSO.
 * LOG:
 * LOG: Revision 1.39  1998/10/15 02:17:14  mmiers
 * LOG: Fix comment regarding SEE ALSO for resource file.
 * LOG:
 * LOG: Revision 1.38  1998/09/30 14:46:19  mmiers
 * LOG: friend functions are not handled consistently.  Need to think about this.
 * LOG:
 * LOG: Revision 1.37  1998/09/30 14:36:26  mmiers
 * LOG: Try a modified version of "friend".
 * LOG:
 * LOG: Revision 1.36  1998/09/30 02:40:08  mmiers
 * LOG: Updates for SCCP.  I think I've got the compromises for SCCP routing
 * LOG: down.  Need to add the routing label everywhere.
 * LOG:
 * LOG: Revision 1.35  1998/09/28 22:42:43  mmiers
 * LOG: More work enhancing MTP3-ish support.
 * LOG:
 * LOG: Revision 1.34  1998/09/22 16:01:27  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.33  1998/07/08 20:01:54  mmiers
 * LOG: Fix some buggy comments Hongling identified.
 * LOG:
 * LOG: Revision 1.32  1998/06/26 15:27:33  mmiers
 * LOG: Finish up conversion to C-style transports.
 * LOG:
 * LOG: Revision 1.31  1998/06/26 14:54:37  mmiers
 * LOG: Finish conversion.
 * LOG:
 * LOG: Revision 1.30  1998/06/26 14:30:40  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.29  1998/06/22 16:24:20  mmiers
 * LOG: More work with resource files.
 * LOG:
 * LOG: Revision 1.28  1998/06/22 16:11:42  mmiers
 * LOG: Add transport PC/SSN settings.
 * LOG:
 * LOG: Revision 1.27  1998/06/18 01:02:41  mmiers
 * LOG: More "C" style transports.
 * LOG:
 * LOG: Revision 1.26  1998/06/18 00:24:57  mmiers
 * LOG: Documentation update, C versions of some transports, C version of
 * LOG: resource file manager.
 * LOG:
 * LOG: Revision 1.25  1998/06/17 19:57:04  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.24  1998/06/16 00:00:22  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.23  1998/06/12 16:42:53  mmiers
 * LOG: Add dual mutexes for sockets and fifos.
 * LOG:
 * LOG: Revision 1.22  1998/06/01 23:41:53  mmiers
 * LOG: Fix a typo in Transport, snarf leading blanks for funcLines.
 * LOG:
 * LOG: Revision 1.21  1998/06/01 16:35:22  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.20  1998/05/31 20:14:57  mmiers
 * LOG: Finishing up the general documenation.
 * LOG:
 * LOG: Revision 1.19  1998/05/31 02:59:41  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.18  1998/05/29 23:53:14  mmiers
 * LOG: More documentation.  I'm nearing the finish on the support subsystem.
 * LOG:
 * LOG: Revision 1.17  1998/05/29 22:35:37  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.16  1998/05/29 03:31:34  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.15  1998/05/22 22:46:52  whu
 * LOG: Add static initialization methods.
 * LOG:
 * LOG: Revision 1.14  1998/05/20 17:06:05  mmiers
 * LOG: Get the namespace thing right.  You must include its++.h if
 * LOG: you want to use the its namespace.
 * LOG:
 * LOG: Revision 1.13  1998/05/19 17:11:50  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.12  1998/05/01 00:24:36  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.11  1998/04/23 00:11:32  mmiers
 * LOG: Working on TCAP now.
 * LOG:
 * LOG: Revision 1.10  1998/04/22 22:20:05  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 * LOG: Revision 1.9  1998/04/22 19:00:11  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.8  1998/04/20 22:04:45  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.7  1998/04/17 02:11:44  mmiers
 * LOG: Fix transports on Solaris.  Add dependency computation to Makefile.
 * LOG:
 * LOG: Revision 1.6  1998/04/16 23:39:04  mmiers
 * LOG: More work on transports.
 * LOG:
 * LOG: Revision 1.5  1998/04/16 19:44:20  mmiers
 * LOG: Start adding transport implementation.
 * LOG:
 * LOG: Revision 1.4  1998/04/16 17:23:33  mmiers
 * LOG: Ok, not the final baseline.  More work on the transports, first.
 * LOG:
 * LOG: Revision 1.3  1998/04/16 16:59:52  mmiers
 * LOG: Final commit before baseline.
 * LOG:
 * LOG: Revision 1.2  1998/04/16 15:58:59  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  1998/04/16 14:40:47  mmiers
 * LOG: New file for transport independence.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_TRANSPORTS_H
#define ITS_TRANSPORTS_H

#include <its.h>
#include <its_iniparse.h>
#include <its_callback.h>
#include <its_rwlock.h>
#include <its_route.h>
#include <its_thread.h>

#ident "$Id: its_transports.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if !defined(ITS_TRANSPORT_ONE_SHOT)
#define ITS_TRANSPORT_ONE_SHOT

#define ITS_MAX_EVENT_QUEUES     65536

/*
 * shorthand here.  The stack uses it.
 */
#define NUM_THREADS_STRING                          "numThreads"
#define INTERNODE_STRING                            "isInterNode"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * ss7 management and routing information
 */
typedef struct
{
    CALLBACK_Manager*   resumeCallbacks; /* call when connection opened */
    CALLBACK_Manager*   pauseCallbacks;  /* call when connection closed */
    CALLBACK_Manager*   statusCallbacks; /* call when connection congested */

    SS7_LinkPtr         linkInfo;        /* route information for this transport */
}
TRANSPORT_SS7Info;

/*
 * THIS MUST BE THE FIRST MEMBER OF A TRANSPORT TYPE INSTANCE RECORD
 */
typedef struct
{
    char*               name;
    ITS_UINT            mask;
    ITS_USHORT          instance;
    ITS_USHORT          pad;  /* keep NMS happy */
    RESFILE_Manager*    res;
    void*               back; /* back pointer to private data (C++) */
    ITS_SERIAL          curInitInvoke;  /* avoid timer mishaps */
    ITS_SERIAL          curTermInvoke;  /* avoid timer mishaps */
    ITS_BOOLEAN         exitNow;
    ITS_BOOLEAN         isActive;
    ITS_TIME            lastUpdate;
    struct _itransport  *next;
    struct _itransport  *prev;
    ITS_THREAD          *owner;
    ITS_UINT            numSent;
    ITS_UINT            numRecv;
    ITS_UINT            refcnt;
    TRANSPORT_SS7Info   ss7Info;
}
TRANSPORT_ObjectPart;

typedef struct _itransport
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
}
TRANSPORT_Control;

/*
 * this gets used too many places not to define
 */
#define TRANSPORT(x) \
    ((TRANSPORT_Control *)(x))

#define TRANSPORT_NAME(x) \
    (((TRANSPORT_Control *)(x))->transport.name)

#define TRANSPORT_MASK(x) \
    (((TRANSPORT_Control *)(x))->transport.mask)

#define TRANSPORT_INSTANCE(x) \
    (((TRANSPORT_Control *)(x))->transport.instance)

#define TRANSPORT_RES(x) \
    (((TRANSPORT_Control *)(x))->transport.res)

#define TRANSPORT_BACK(x) \
    (((TRANSPORT_Control *)(x))->transport.back)

#define TRANSPORT_CUR_INIT_INVOKE(x) \
    (((TRANSPORT_Control *)(x))->transport.curInitInvoke)

#define TRANSPORT_CUR_TERM_INVOKE(x) \
    (((TRANSPORT_Control *)(x))->transport.curTermInvoke)

#define TRANSPORT_EXIT_NOW(x) \
    (((TRANSPORT_Control *)(x))->transport.exitNow)

#define TRANSPORT_IS_ACTIVE(x) \
    (((TRANSPORT_Control *)(x))->transport.isActive)

#define TRANSPORT_LAST_UPDATE(x) \
    (((TRANSPORT_Control *)(x))->transport.lastUpdate)

#define TRANSPORT_HMI_NEXT(x) \
    (((TRANSPORT_Control *)(x))->transport.next)

#define TRANSPORT_HMI_PREV(x) \
    (((TRANSPORT_Control *)(x))->transport.prev)

#define TRANSPORT_OWNER(x) \
    (((TRANSPORT_Control *)(x))->transport.owner)

#define TRANSPORT_NUM_SENT(x) \
    (((TRANSPORT_Control *)(x))->transport.numSent)

#define TRANSPORT_NUM_RECV(x) \
    (((TRANSPORT_Control *)(x))->transport.numRecv)

#define TRANSPORT_REFCNT(x) \
    (((TRANSPORT_Control *)(x))->transport.refcnt)

#define TRANSPORT_SS7_INFO(x) \
    (((TRANSPORT_Control *)(x))->transport.ss7Info)

/*
 * a generic "C" style transport.
 */
typedef int (*TRANSPORT_EventProc)(ITS_HANDLE, ITS_EVENT *);
typedef void (*TRANSPORT_HandleProc)(ITS_HANDLE);
typedef void (*TRANSPORT_ExitProc)(ITS_HANDLE, ITS_BOOLEAN);

#define TRANSPORT_INHERIT_EVENT_PROC    ((TRANSPORT_EventProc)NULL)
#define TRANSPORT_INHERIT_HANDLE_PROC   ((TRANSPORT_HandleProc)NULL)
#define TRANSPORT_INHERIT_EXIT_PROC     ((TRANSPORT_ExitProc)NULL)

typedef struct
{
    TRANSPORT_EventProc     getNextEvent;
    TRANSPORT_EventProc     peekNextEvent;
    TRANSPORT_EventProc     putEvent;
    TRANSPORT_HandleProc    onConnect;
    TRANSPORT_HandleProc    onDisconnect;
    TRANSPORT_ExitProc      setExit;
}
TRANSPORT_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    TRANSPORT_ClassPart transportClass;
}
TRANSPORT_ClassRec, *TRANSPORT_Class;

#define TRANSPORT_CLASS_GET_NEXT_EVENT(x) \
    (((TRANSPORT_Class)(x))->transportClass.getNextEvent)

#define TRANSPORT_CLASS_PEEK_NEXT_EVENT(x) \
    (((TRANSPORT_Class)(x))->transportClass.peekNextEvent)

#define TRANSPORT_CLASS_PUT_EVENT(x) \
    (((TRANSPORT_Class)(x))->transportClass.putEvent)

#define TRANSPORT_CLASS_ON_CONNECT(x) \
    (((TRANSPORT_Class)(x))->transportClass.onConnect)

#define TRANSPORT_CLASS_ON_DISCONNECT(x) \
    (((TRANSPORT_Class)(x))->transportClass.onDisconnect)

#define TRANSPORT_CLASS_SET_EXIT(x) \
    (((TRANSPORT_Class)(x))->transportClass.setExit)

/*
 * A note about the transportGate.  We need to ensure that we serialize access
 * to this data structure.
 */
typedef struct
{
    TRANSPORT_Control*  arrayOfTransports[ITS_MAX_EVENT_QUEUES];
    ITS_RWLOCK          transportGate;
    TRANSPORT_Control*  listHead;
    TRANSPORT_Control*  listTail;
}
TRANSPORT_Manager;

/*.interface:TRANSPORT
 *****************************************************************************
 *  Interface:
 *      TRANSPORT_*
 *
 *  Purpose:
 *      This interface provides the C API to the transport mechanism.
 *
 *  Usage:
 *      Warning: TRANSPORT_FindTransport() returns the transport pointer,
 *      but the lifetime of the pointer is indeterminate (the transport
 *      may be destroyed while you are examining it).  Use at your own
 *      risk.
 *      This is obsolete.  Now when you FindTransport() you increment a
 *      reference count.  The transport pointer will be valid until the
 *      reference count reaches 0.  The reference count is decremented
 *      by UnfindTransport() and Delete().
 *
 *****************************************************************************/
/*
 * for subclassing
 */
ITSDLLAPI extern TRANSPORT_ClassRec       itsTRANSPORT_BaseClassRec;
ITSDLLAPI extern ITS_Class                itsTRANSPORT_BaseClass;

#define TRANSPORT_CLASS_NAME    "TRANSPORT"

ITSDLLAPI ITS_HANDLE TRANSPORT_Create(TRANSPORT_Class tClass, const char *name,
                                      ITS_USHORT instance, ITS_UINT mask);

ITSDLLAPI void TRANSPORT_Delete(ITS_HANDLE);

ITSDLLAPI int TRANSPORT_GetNextEvent(TRANSPORT_Control *base, ITS_EVENT *ev);
ITSDLLAPI int TRANSPORT_PeekNextEvent(TRANSPORT_Control *base, ITS_EVENT *ev);

ITSDLLAPI int TRANSPORT_PutEvent(ITS_USHORT id, ITS_EVENT* entry);

ITSDLLAPI int TRANSPORT_SetState(TRANSPORT_Control* base, ITS_BOOLEAN isAllowed);
ITSDLLAPI int TRANSPORT_SetCongestion(TRANSPORT_Control* base, ITS_OCTET level);

ITSDLLAPI TRANSPORT_Control* TRANSPORT_FindTransport(ITS_USHORT instance);
ITSDLLAPI TRANSPORT_Control* TRANSPORT_FindTransportByName(const char *name);
ITSDLLAPI void               TRANSPORT_UnfindTransport(TRANSPORT_Control *);

ITSDLLAPI ITS_UINT TRANSPORT_GetNumSent(TRANSPORT_Control* base);
ITSDLLAPI ITS_UINT TRANSPORT_GetNumRecv(TRANSPORT_Control* base);

ITSDLLAPI void TRANSPORT_ClearNumSent(TRANSPORT_Control* base);
ITSDLLAPI void TRANSPORT_ClearNumRecv(TRANSPORT_Control* base);

ITSDLLAPI ITS_BOOLEAN TRANSPORT_GetExit(TRANSPORT_Control* base);
ITSDLLAPI void        TRANSPORT_SetExit(TRANSPORT_Control* base,
                                        ITS_BOOLEAN doExit);

/*
 * protos
 */
ITSDLLAPI int TRANSPORT_RegisterTransport(TRANSPORT_Control* trans);
ITSDLLAPI int TRANSPORT_DeregisterTransport(ITS_USHORT id);

ITSDLLAPI int TRANSPORT_RegisterSS7Data(TRANSPORT_Control* base);
ITSDLLAPI void TRANSPORT_DeregisterSS7Data(TRANSPORT_Control* base);

ITSDLLAPI extern CALLBACK_Manager *TRANSPORT_registrations;
ITSDLLAPI extern CALLBACK_Manager *TRANSPORT_deregistrations;

/*
 * for internal use only
 */
ITSDLLAPI TRANSPORT_Manager *TRANSPORT_GetManager();
ITSDLLAPI TRANSPORT_Control *TRANSPORT_FindTransportNoLock(ITS_USHORT instance);
ITSDLLAPI int                TRANSPORT_ReserveSlot(ITS_USHORT instance);
ITSDLLAPI int                TRANSPORT_LockManager();
ITSDLLAPI int                TRANSPORT_UnlockManager();

#if defined(__cplusplus)
}
#endif

#endif /* ITS_TRANSPORT_ONESHOT */

#if defined(USE_CPLUSPLUS)

#include <its++.h>
#include <its_iniparse.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Transport
 *****************************************************************************
 *  Interface:
 *      Transport
 *
 *  Purpose:
 *      Transports are the most crucial part of the IntelliSS7 infrastructure.
 *      They represent the method by which events move between tasks and
 *      processes in an IntellISS7 application.
 *
 *      All transports are identified by a unique number called the "instance'.
 *      The usage of this number can be somewhat confusing as workers in a
 *      multithreaded environement are also identified by instance.  The
 *      reason for that is because all ITS_Worker objects have a transport
 *      associated with them, which means that identifying a transport also
 *      identifies the thread associated with that transport.  See
 *      <A HREF=its_worker.html>ITS_Worker</A>
 *      for information about the ITS_Worker class.
 *
 *      Transports are event sources to their owners.  In a multithreaded
 *      environment, there can be many transports; in a singlethreaded
 *      environment, there is never more than one transport.  The owner
 *      of a transport is therefore either a thread, or a process, depending
 *      on the users choice of a programming model.
 *
 *      There are two basic kinds of transports - those that deliver events
 *      within a process, and those that deliver events between process.
 *      An intraprocess transport (e.g. ITS_TaskQueueTransport) will only
 *      have one "end", or delivery point.  Sending an event to this kind
 *      of transport simply means that an event is enqueued on the transport
 *      medium; normally, other threads within a process will use the tranports
 *      PutEvent() method to "send" an event to a particular thread.  Because
 *      any entity can send an event, this kind of transport MUST be thread
 *      safe, even though that capability might not be needed for a single
 *      threaded application.
 *
 *      The other kind of transport is an interprocess transport (e.g.,
 *      ITS_FifoTransport and ITS_SS7Transport).  These transports have two
 *      "end"s; the local end, where events appear from an external process,
 *      and the remote end, where events generated by a process are sent.
 *      When an event is sent to this kind of transport, there is an implicit
 *      understanding that ANY thread in a process can send; for this reason
 *      this kind of transport MUST be thread safe as well, for the same reason
 *      as intraprocess transports.
 *
 *      Interprocess transports are sometimes referred to as "border" transports
 *      in that they act as event dispatchers from external entities to
 *      internal entities.  Typically, interprocess transports are
 *      point-to-point, but there are exceptions (true SS7 transports,
 *      UDP transports) where a single transport endpoint in an application
 *      can exchange messages with multiple destination endpoints.
 *
 *      In multithreaded environments, transports have a close association with
 *      the routing subystem.  The routing subsystem helps entities determine
 *      where a particular event should be sent.  Some routing can be performed
 *      automatically (such as SS7 routing), whereas other routing needs some
 *      help from the application.  See
 *      <A HREF=its_route.html>ITS_RoutingMap</A>
 *      for more information on routing.
 *
 *      Finally, the transport subsystem allows the user to send messages
 *      to any transport, without having a reference to that transport
 *      other than the transport's instance number.  This is a crucial
 *      requirement for entities wishing to send information to a destination
 *      without forcing the user to reference a translation table.
 *
 *  Usage:
 *      All transports MUST be thread safe!  Also, transports must be unique
 *      (not copyable).  How transports are created depends on the threading
 *      model and the language of implementation.  In general, the user will
 *      never need to create a transport directly; instead, they will have
 *      transports created for them via the ITS_Worker objects (when
 *      multithreaded), or via ITS_Initialize() (when single user).
 *
 *      Transports form the basis of the event loop:
 *      ---------------------------------------------------------------------
 *      ITS_SS7Transports *tr;
 *
 *      // create the transport
 *      try
 *      {
 *          tr = new ITS_SS7Transport("SS7", 5, mask);
 *      }
 *
 *      // process events
 *      for (;;)
 *      {
 *          Event ev;
 *          if (tr->GetNextEvent(ev) != ITS_SUCCESS)
 *          {
 *              // an error occurred
 *              continue;
 *          }
 *
 *          // process the event
 *          userCode(tr, ev);
 *      }
 *      ----------------------------------------------------------------------
 *
 *      The function "userCode()" represents code for handling specific
 *      messages.  Note that the event loop code included above can be
 *      considered generic; only the objects and methods used will change
 *      (for example, ITS_Worker objects will use the GetNextEvent() method
 *      on the worker object -- which merely calls the GetNextEvent() on
 *      the transport it is associated with).
 *
 *      Note that if a user wants to check for events without blocking if
 *      no event is present, they can use the PeekNextEvent() function
 *      instead.  However, this is considered bad form, as the programming
 *      model changes to a "polled" architecture, which has inherently more
 *      processing requirements than an event driven model.
 *
 *****************************************************************************/
class Transport
{
public:
    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *      This method creates an instance of the Transport base class.
     *      As part of this procedure, the transport is registered in the
     *      instance/transport translation table.
     *
     *  Input Parameters:
     *      tc - the C level transport to wrapper
     *
     *  See Also:
     *      ~Transport()
     ************************************************************************/
    Transport(TRANSPORT_Control* _tc)
        : tc(_tc)
    {
    }
    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *      This method destroys a transport.  This effectively removes this
     *      transport from the instance/transport mapping table.
     *
     *  See Also:
     *      Transport()
     ************************************************************************/
    virtual ~Transport()
    {
    }

    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *       This method provides access to the instance member variable.
     *       The instance is read-only
     *
     *  Return Value:
     *       The instance id of this transport.
     *
     *  See Also:
     *       GetMask()
     ************************************************************************/
    ITS_USHORT
    GetInstance() const
    {
        return (ITS_USHORT)(tc ? TRANSPORT_INSTANCE(tc) : ITS_INVALID_SRC);
    }
    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *       This method provides access to the mask member variable.
     *       The mask is read-only
     *
     *  Return Value:
     *       The instance id of this transport.
     *
     *  See Also:
     *       GetInstance()
     ************************************************************************/
    ITS_UINT
    GetMask() const
    {
        return (tc ? TRANSPORT_MASK(tc) : 0);
    }
    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *      Find a transport based on the instance.
     *
     *  Return Value:
     *      A new Transport object.
     *
     ************************************************************************/
    static Transport
    Find(ITS_USHORT inst)
    {
        TRANSPORT_Control *tc = TRANSPORT_FindTransport(inst);

        ITS_THROW_ASSERT(tc != NULL);

        return Transport(tc);
    }
    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *      Unfind a transport based on the instance (decrement the ref
     *      count).
     *
     *  Return Value:
     *      None.
     *
     ************************************************************************/
    static void
    Unfind(Transport& who)
    {
        TRANSPORT_UnfindTransport(who.tc);
    }

    /*.implementation:public,abstract,Transport
     ************************************************************************
     *  Purpose:
     *       This method provides the means to fetch an Event
     *       data structure from this transport.
     *
     *  Output Parameters:
     *       ev - a pointer to the area to copy the event into
     *
     *  Return Value:
     *       If an event is successfully retrieved, ITS_SUCCESS is returned.
     *       Any other return value indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    GetNextEvent(Event& event)
    {
        ITS_Class cl = ITS_OBJ_CLASS(tc);

        ITS_THROW_ASSERT(tc != NULL && cl != NULL);

        if (TRANSPORT_CLASS_GET_NEXT_EVENT(cl))
        {
            return TRANSPORT_CLASS_GET_NEXT_EVENT(cl)(tc, &event.GetEvent());
        }
        else
        {
            return (ITS_EINVALIDARGS);
        }
    }

    /*.implementation:public,abstract,Transport
     ************************************************************************
     *  Purpose:
     *       This method provides the mechanism for peeking at the
     *       transport and fetching an Event.
     *
     *  Output Parameters:
     *       ev - a pointer to the area to copy the event into
     *
     *  Return Value:
     *       If an event is successfully retrieved, ITS_SUCCESS is returned.
     *       If no event is available, ITS_ENOMSG is returned.
     *       Any other return value indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    PeekNextEvent(Event& event)
    {
        ITS_Class cl = ITS_OBJ_CLASS(tc);

        ITS_THROW_ASSERT(tc != NULL && cl != NULL);

        if (TRANSPORT_CLASS_PEEK_NEXT_EVENT(cl))
        {
            return TRANSPORT_CLASS_PEEK_NEXT_EVENT(cl)(tc, &event.GetEvent());
        }
        else
        {
            return (ITS_EINVALIDARGS);
        }
    }
    /*.implementation:public,abstract,Transport
     ************************************************************************
     *  Purpose:
     *       This method provides the mechanism for sending an Event to
     *       this transport.
     *
     *  Input Parameters:
     *       ev - a pointer to the ITS_EVENT to send
     *
     ************************************************************************/
    virtual int
    PutEvent(Event& event)
    {
        ITS_Class cl = ITS_OBJ_CLASS(tc);

        ITS_THROW_ASSERT(tc != NULL && cl != NULL);

        if (TRANSPORT_CLASS_PUT_EVENT(cl))
        {
            return TRANSPORT_CLASS_PUT_EVENT(cl)(tc, &event.GetEvent());
        }
        else
        {
            return (ITS_EINVALIDARGS);
        }
    }

    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method provides access to the resource file associated
    *       with this transport.
    *
    *  Return Value:
    *       A pointer to the resource file object.
    *
    ************************************************************************/
    RESFILE_Manager*
    GetResourceFile()
    {
        return (tc ? TRANSPORT_RES(tc) : NULL);
    }
    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method allows the user to close the resource file
    *       associated with this transport.
    *
    *  Return Value:
    *       A pointer to the resource file object.
    *
    ************************************************************************/
    void
    CloseResourceFile()
    {
    }

    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method returns the number of events sent on this transport.
    *
    *  Return Value:
    *       The number of events sent.
    *
    ************************************************************************/
    ITS_UINT
    GetNumSent()
    {
        return TRANSPORT_GetNumSent(tc);
    }
    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method returns the number of events recv on this transport.
    *
    *  Return Value:
    *       The number of events recv.
    *
    ************************************************************************/
    ITS_UINT
    GetNumRecv()
    {
        return TRANSPORT_GetNumRecv(tc);
    }
    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method clears the number of events sent on this transport.
    *
    ************************************************************************/
    void
    ClearSendCount()
    {
        TRANSPORT_ClearNumSent(tc);
    }
    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method clears the number of events recv on this transport.
    *
    ************************************************************************/
    void
    ClearRecvCount()
    {
        TRANSPORT_ClearNumRecv(tc);
    }

    /*.implementation:public,inline,Transport
    ************************************************************************
    *  Purpose:
    *       This method allows the user to get a pointer to the underlying
    *       C style transport.
    *
    *  Return Value:
    *       A pointer to the transport object.
    *
    ************************************************************************/
    const TRANSPORT_Control*
    GetTC() const
    {
        return (tc);
    }

    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *       This method sets the allowed/prohibited status for routes through
     *       this transport.
     *
     *  Input Parameters:
     *       isUp - if the destination is Up
     *
     ************************************************************************/
    int
    SetState(ITS_BOOLEAN isAllowed)
    {
        return TRANSPORT_SetState(tc, isAllowed);
    }
    /*.implementation:public,inline,Transport
     ************************************************************************
     *  Purpose:
     *       This method provides sets the congestion level for routes through
     *       this transport.
     *
     *  Input Parameters:
     *       level - the congestion level
     *
     ************************************************************************/
    int
    SetCongestion(ITS_OCTET level)
    {
        return TRANSPORT_SetCongestion(tc, level);
    }

    /*.implementation:static,inline,Transport
     ************************************************************************
     *  Purpose:
     *      This method is an interface to TRANSPORT_PutEvent().  It takes
     *      a transport instance and an event, looks up the transport to
     *      send to, and calls that transport's PutEvent function.
     *
     *  Input Parameters:
     *      instance - the transport instance to send this event to
     *      entry - the event to send
     *
     ************************************************************************/
    static int
    PutEvent(ITS_USHORT id, ITS_EVENT* entry)
    {
        return TRANSPORT_PutEvent(id, entry);
    }
    /*.implementation:static,inline,Transport
     ************************************************************************
     *  Purpose:
     *      This method is an interface to TRANSPORT_PutEvent().  It takes
     *      a transport instance and an event, looks up the transport to
     *      send to, and calls that transport's PutEvent function.
     *
     *  Input Parameters:
     *      instance - the transport instance to send this event to
     *      entry - the event to send
     *
     *  Notes:
     *      This method causes Transport::PutEvent(void *tr, ITS_EVENT *ev)
     *      to be called.
     *
     ************************************************************************/
    static int
    PutEvent(ITS_USHORT id, Event& entry)
    {
        return TRANSPORT_PutEvent(id, &entry.GetEvent());
    }

protected:
    TRANSPORT_Control *tc;

private:
    /* sorry, no default constructor */
    Transport() {};
};

#define ITS_HANDLE_TO_ITS_TRANSPORT(x) \
    ((x) ? (Transport *)TRANSPORT_BACK(x) : NULL)

/*.interface:TransportRef
 *****************************************************************************
 *  Interface:
 *      TransportRef
 *
 *  Purpose:
 *      Reference count C++ transports.
 *
 *  Usage:
 *      Transport tc(h);
 *      TransportRef tref(tc);
 *
 *    Or
 *
 *      Transport tc = Transport::Find(instance);
 *      TransportRef tref(tc);
 *      Transport::Unfind(tc);
 *
 *    Note that in the second case, Transport::Find() adds a reference,
 *    requiring Transport::Unfind() to be called to release it.
 *    TransportRef adds a second reference, which is released when the
 *    object goes out of scope.
 *
 *****************************************************************************/
class TransportRef
{
public:
    TransportRef(Transport& _ref)
        : ref(_ref)
    {
        tc = TRANSPORT_FindTransport(ref.GetInstance());
    }

    ~TransportRef()
    {
        TRANSPORT_UnfindTransport(tc);
    }

    Transport&
    GetTransport()
    {
        return ref;
    }

protected:
    TRANSPORT_Control *tc;
    Transport& ref;

private:
    /* sorry, no copying */
    TransportRef();
    TransportRef(TransportRef&);
    TransportRef& operator=(const TransportRef&);
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_TRANSPORTS_H */
