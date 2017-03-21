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
 * LOG: Revision 9.1  2005/03/23 12:51:18  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:49:21  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.2  2003/04/07 08:11:38  randresol
 * LOG: Add MML Commands for LINK/LINKSET subsystem
 * LOG:
 * LOG: Revision 7.4.2.1  2003/03/28 15:50:10  randresol
 * LOG: Add Debug Console command for the ROUTE System
 * LOG:
 * LOG: Revision 7.4  2002/12/26 22:31:21  mmiers
 * LOG: Let the user specify the instance if they really know what they're
 * LOG: doing.  Don't document this feature, it's mostly for us.
 * LOG:
 * LOG: Revision 7.3  2002/08/29 16:02:11  mmiers
 * LOG: Add default HMI callback
 * LOG:
 * LOG: Revision 7.2  2002/08/29 15:46:33  mmiers
 * LOG: Add the deselector to the DTD
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:41  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.32  2002/08/26 21:13:28  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.31  2002/08/01 19:21:56  mmiers
 * LOG: Allow virtuals to be added.
 * LOG:
 * LOG: Revision 6.30  2002/08/01 19:16:08  mmiers
 * LOG: Get the pool in there
 * LOG:
 * LOG: Revision 6.29  2002/07/30 18:56:39  mmiers
 * LOG: Fixup
 * LOG:
 * LOG: Revision 6.28  2002/07/30 18:29:47  mmiers
 * LOG: Set instance number, add resources
 * LOG:
 * LOG: Revision 6.27  2002/07/30 17:59:18  mmiers
 * LOG: get the right return, dispatch the transport.
 * LOG:
 * LOG: Revision 6.26  2002/07/23 16:56:33  mmiers
 * LOG: Complete addborder framework
 * LOG:
 * LOG: Revision 6.25  2002/07/10 20:20:17  mmiers
 * LOG: type, not flags
 * LOG:
 * LOG: Revision 6.24  2002/07/10 20:11:14  mmiers
 * LOG: Don't delay create for task queues as borders
 * LOG:
 * LOG: Revision 6.23  2002/07/05 22:24:12  yranade
 * LOG: Fix flag bug.
 * LOG:
 * LOG: Revision 6.22  2002/07/02 21:26:36  mmiers
 * LOG: Work on getting debug console interface added to engine.
 * LOG:
 * LOG: Revision 6.21  2002/05/22 19:05:23  mmiers
 * LOG: Warning removal (predicate always true due to limited range
 * LOG: of data type).
 * LOG:
 * LOG: Revision 6.20  2002/05/15 19:12:19  hdivoux
 * LOG: Reorder adding FtGroup specific callbacks (using pre-add functions).
 * LOG:
 * LOG: Revision 6.19  2002/05/15 16:45:12  hdivoux
 * LOG: Added missing calls to string duplicate.
 * LOG:
 * LOG: Revision 6.18  2002/05/08 20:24:49  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.17  2002/05/07 20:31:44  hdivoux
 * LOG: Report symbol resolving errors for user's preFunc and postFunc.
 * LOG:
 * LOG: Revision 6.16  2002/05/07 16:21:12  mmiers
 * LOG: Teardown pointer reset.
 * LOG:
 * LOG: Revision 6.15  2002/05/07 14:51:14  wweng
 * LOG: Add output for missing features.
 * LOG:
 * LOG: Revision 6.14  2002/05/06 21:15:52  hdivoux
 * LOG: Cleanup after FT/HA integration.
 * LOG:
 * LOG: Revision 6.13  2002/05/01 20:09:44  hdivoux
 * LOG: Allow to specify no master FT group members (for stub).
 * LOG:
 * LOG: Revision 6.12  2002/04/25 15:45:18  mmiers
 * LOG: Add the application context.
 * LOG:
 * LOG: Revision 6.11  2002/04/24 21:42:14  hdivoux
 * LOG: Forte C++ doesn't like reinterpret_cast<::engine... use <engine::
 * LOG:
 * LOG: Revision 6.10  2002/04/23 20:59:34  mmiers
 * LOG: provide an app selector if the user didn't specify one and has asked
 * LOG: for a worker pool.
 * LOG:
 * LOG: Revision 6.9  2002/04/23 20:48:20  mmiers
 * LOG: Add auto dispatch function for simplification.
 * LOG:
 * LOG: Revision 6.8  2002/04/16 21:29:38  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.7  2002/04/16 21:21:09  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.6  2002/04/15 21:06:58  hdivoux
 * LOG: Added configurable FtGroups.
 * LOG:
 * LOG: Revision 6.5  2002/04/10 22:52:55  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.4  2002/04/09 22:45:44  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.3  2002/03/20 22:48:44  mmiers
 * LOG: Somebody put hard tabs in.
 * LOG:
 * LOG: Revision 6.2  2002/03/15 17:14:16  rsonak
 * LOG: Dispatch the borders after User's PreFunc
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10  2001/12/19 18:02:32  mmiers
 * LOG: ADAX testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 5.9  2001/12/18 22:50:07  mmiers
 * LOG: Add levels to global trace object
 * LOG:
 * LOG: Revision 5.8  2001/12/18 20:14:18  mmiers
 * LOG: If trace outputs are off disable trace
 * LOG:
 * LOG: Revision 5.7  2001/11/13 17:37:29  mmiers
 * LOG: Make it work with windows too.
 * LOG:
 * LOG: Revision 5.6  2001/11/13 17:28:23  mmiers
 * LOG: NDEBUG isn't defined by Forte.
 * LOG:
 * LOG: Revision 5.5  2001/11/09 16:54:35  mmiers
 * LOG: Mark mempool init as potentially removable.
 * LOG:
 * LOG: Revision 5.4  2001/09/20 19:16:15  hdivoux
 * LOG: Update for XML GCS configuration attributes.
 * LOG:
 * LOG: Revision 5.3  2001/09/18 16:34:56  mmiers
 * LOG: Some bugs Hubert caught.
 * LOG:
 * LOG: Revision 5.2  2001/08/20 19:08:56  mmiers
 * LOG: Initialize mempool
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.23  2001/08/13 21:04:41  mmiers
 * LOG: Fix type bug.
 * LOG:
 * LOG: Revision 4.22  2001/08/10 19:47:12  lbana
 * LOG: Namespace usage doesn't match NT/g++
 * LOG:
 * LOG: Revision 4.21  2001/07/27 16:59:23  mmiers
 * LOG: Remove scope modifiers.
 * LOG:
 * LOG: Revision 4.20  2001/07/27 16:43:32  mmiers
 * LOG: Remove bogus nulls
 * LOG:
 * LOG: Revision 4.19  2001/07/26 19:24:24  mmiers
 * LOG: Split out dispatch.
 * LOG:
 * LOG: Revision 4.18  2001/07/26 19:04:14  mmiers
 * LOG: Add engine thread pool type for pattern matcher.
 * LOG:
 * LOG: Revision 4.17  2001/07/26 18:10:32  mmiers
 * LOG: Diff, version 1.
 * LOG:
 * LOG: Revision 4.16  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.15  2001/07/19 16:05:17  mmiers
 * LOG: nodeId uninitiailized.
 * LOG:
 * LOG: Revision 4.14  2001/07/18 21:43:41  mmiers
 * LOG: Start committing the buildable diff parts.
 * LOG:
 * LOG: Revision 4.13  2001/07/13 15:12:30  mmiers
 * LOG: some bugs Hubert noticed, snapshot before digging into diff.
 * LOG:
 * LOG: Revision 4.12  2001/07/05 22:48:00  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 4.11  2001/06/22 21:01:06  mmiers
 * LOG: Finish integrating DSM and RM.  Need to add PeerDead notification
 * LOG: to complete.
 * LOG:
 * LOG: Revision 4.10  2001/06/22 19:18:40  mmiers
 * LOG: Integrate RM and DSM.
 * LOG:
 * LOG: Revision 4.9  2001/06/21 15:18:19  mmiers
 * LOG: Add HMI and Alarm.
 * LOG:
 * LOG: Revision 4.8  2001/06/20 22:01:25  mmiers
 * LOG: Get DSM building as a DLL.  Correct some namespace bugs.
 * LOG:
 * LOG: Revision 4.7  2001/06/18 20:24:46  mmiers
 * LOG: Add diff framework.  Need to implement.
 * LOG:
 * LOG: Revision 4.6  2001/05/10 16:51:44  mmiers
 * LOG: User requested stuff (user intervention).
 * LOG:
 * LOG: Revision 4.5  2001/05/10 00:35:50  mmiers
 * LOG: Move pre and post to be first and last respectively.  They
 * LOG: probably want to grab threads for custom duties.
 * LOG:
 * LOG: Revision 4.4  2001/05/10 00:28:12  mmiers
 * LOG: Add custom dispatch.
 * LOG:
 * LOG: Revision 4.3  2001/05/09 23:57:47  mmiers
 * LOG: Add calls to pre and post func.
 * LOG:
 * LOG: Revision 4.2  2001/05/04 14:30:52  mmiers
 * LOG: A few bug fixes from PR4.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.1  2001/04/28 23:38:20  mmiers
 * LOG: Rearrange this to standard form.
 * LOG:
 * LOG: Revision 1.6  2001/04/26 16:01:22  mmiers
 * LOG: Spew error messages.
 * LOG:
 * LOG: Revision 1.5  2001/04/26 00:35:27  mmiers
 * LOG: Make the library name optional (resolve within the executable if
 * LOG: possible).
 * LOG:
 * LOG: Revision 1.4  2001/04/20 17:29:58  mmiers
 * LOG: Fix type bugs introduced yesterday.
 * LOG:
 * LOG: Revision 1.3  2001/04/19 19:21:50  labuser
 * LOG: Debug.  Need to supply resources even for ITER
 * LOG:
 * LOG: Revision 1.2  2001/04/18 20:17:34  mmiers
 * LOG: Update the driver project files and add preAccept.
 * LOG:
 * LOG: Revision 1.1  2001/04/12 20:10:26  salaoui
 * LOG: Move to a more logical location.
 * LOG:
 * LOG: Revision 1.27  2001/04/12 19:13:41  labuser
 * LOG: Debugging with Yogesh.
 * LOG:
 * LOG: Revision 1.26  2001/04/11 21:52:01  mmiers
 * LOG: Don't create workers delayed.
 * LOG:
 * LOG: Revision 1.25  2001/04/11 01:04:22  mmiers
 * LOG: Rename it for consistency.
 * LOG:
 * LOG: Revision 1.24  2001/04/11 00:45:11  mmiers
 * LOG: Move the EngineWorker class so that users can see it.
 * LOG:
 * LOG: Revision 1.23  2001/04/10 19:29:16  mmiers
 * LOG: Debugging still.
 * LOG:
 * LOG: Revision 1.22  2001/04/06 15:04:29  mmiers
 * LOG: Forgot to commit these.
 * LOG:
 * LOG: Revision 1.21  2001/04/04 22:06:12  mmiers
 * LOG: Formatting.
 * LOG:
 * LOG: Revision 1.20  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 1.19  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.18  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.17  2001/04/03 22:14:14  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.16  2001/04/03 22:13:17  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.15  2001/04/03 20:44:20  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.14  2001/04/03 20:38:06  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.13  2001/04/03 17:45:42  mmiers
 * LOG: Fix some major engine bugs.
 * LOG:
 * LOG: Revision 1.12  2001/04/02 19:50:41  mmiers
 * LOG: Solaris cleanup.
 * LOG:
 * LOG: Revision 1.11  2001/03/28 23:37:42  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.10  2001/03/28 22:38:29  mmiers
 * LOG: It is coded.
 * LOG:
 * LOG: Revision 1.9  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 1.8  2001/03/26 23:02:15  mmiers
 * LOG: Today's installment.  Now that I'm caught up on email, I should
 * LOG: be able to finish the parser tomorrow.
 * LOG:
 * LOG: Revision 1.7  2001/03/17 01:12:15  mmiers
 * LOG: Small cleanups for portability.
 * LOG:
 * LOG: Revision 1.6  2001/03/16 23:18:46  mmiers
 * LOG: Ok, everything done but the parser.
 * LOG:
 * LOG: Revision 1.5  2001/03/16 20:56:07  mmiers
 * LOG:
 * LOG: Ok, only resdb and parsing left.
 * LOG:
 * LOG: Revision 1.4  2001/03/14 23:44:01  mmiers
 * LOG: Build the pools and parsing is all that's left.
 * LOG:
 * LOG: Revision 1.3  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 1.2  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.1  2001/03/09 22:56:44  mmiers
 * LOG: Add the driver libs.
 * LOG:
 *
 ****************************************************************************/

/*
 * pick up the right exports
 */
#define DRIVER_IMPLEMENTATION

#include <its++.h>
#include <engine++.h>

#define SIMULTANEOUS_PROTOCOL_FAMILIES
/* ANSI Support changes
#if !defined(ANSI)
#define ANSI
#endif
#if !defined(CCITT)
#define CCITT
#endif
ANSI Support changes Ends*/
#if defined(CCITT)
#include <itu/mtp3.h>
#include <itu/sccp.h>
#include <itu/isup.h>
/* ANSI Support changes*/
#define ISUP_ManagementCallbacks ISUP_CCITT_ManagementCallbacks
#define SCCP_ManagementCallbacks SCCP_CCITT_ManagementCallbacks
#define  SCCP_GlobalTitleTranslator SCCP_CCITT_GlobalTitleTranslator
#define  SCCP_SSNRoutingCallbacks SCCP_CCITT_SSNRoutingCallbacks
/* ANSI Support changes Ends*/
#elif defined(ANSI)
#include <ansi/mtp3.h>
#include <ansi/sccp.h>
#include <ansi/isup.h>
/* ANSI Support changes*/
#define ISUP_ManagementCallbacks ISUP_ANSI_ManagementCallbacks
#define SCCP_ManagementCallbacks SCCP_ANSI_ManagementCallbacks
#define  SCCP_GlobalTitleTranslator SCCP_ANSI_GlobalTitleTranslator
#define  SCCP_SSNRoutingCallbacks SCCP_ANSI_SSNRoutingCallbacks
#endif
/* ANSI Support changes Ends*/
#ident "$Id: driver++.cpp,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $"

#undef ITSDLLAPI
#define ITS_IMPLEMENTATION
#if defined(WIN32)
#if defined(ITS_IMPLEMENTATION)
#define ITSDLLAPI __declspec(dllexport)
#else
#define ITSDLLAPI __declspec(dllimport)
#endif
#else  /* WIN32 */
#define ITSDLLAPI
#endif /* WIN32 */

#include "engine_intern.h"
#include <its_statics.cpp>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

namespace engine
{
DRVDLLAPI its::TraceLevel   *AppDebugTrace = NULL;
DRVDLLAPI its::TraceLevel   *AppWarningTrace = NULL;
DRVDLLAPI its::TraceLevel   *AppErrorTrace = NULL;
DRVDLLAPI its::TraceLevel   *AppCriticalTrace = NULL;
DRVDLLAPI EnginePool        *borderPool = NULL;
DRVDLLAPI EnginePool        *workerPool = NULL;
}

DRVDLLAPI its::WorkItemPool     *workItemPool = NULL;

#if defined(WIN32)
static NtEventLog           *eventLog = NULL;
static NtExceptionLog       *exceptionLog = NULL;
#elif defined(unix)
static UnixEventLog         *eventLog = NULL;
static UnixExceptionLog     *exceptionLog = NULL;
#endif

static Service              *service = NULL;

/*
 * implementation variables
 */
static ITS_Object       transports = NULL;
static RESFILE_Manager  *appRes = NULL;

/*
 * local strings
 */
#if defined(WIN32)

#define DISPATCH_DEBUG_STRING     "DISPATCH++D.DLL"
#define DISPATCH_STRING           "DISPATCH++.DLL"

#else

#if defined(CCITT)
#define DISPATCH_DEBUG_STRING     "libCCITT-DISPATCH++D.so"
#define DISPATCH_STRING           "libCCITT-DISPATCH++.so"

#else
#define DISPATCH_DEBUG_STRING     "libANSI-DISPATCH++D.so"
#define DISPATCH_STRING           "libANSI-DISPATCH++.so"

#endif

#endif


/*
 * for workers
 */
class EngineWorkerPool : public engine::EnginePool
{
public:
    virtual ThreadPoolThread *CreatePoolThread(int stackSize);
};

/*
 * for dynamics
 */
class EngineDynamicPool : public engine::EnginePool
{
public:
    EngineDynamicPool(engine::Worker *p)
        : parent(p)
    {
    }

    virtual ThreadPoolThread *CreatePoolThread(int stackSize);

    engine::Worker    *parent;
};

/*
 * for general borders
 */
class EngineBorderPool : public engine::EnginePool
{
public:
    virtual ThreadPoolThread *CreatePoolThread(int stackSize);
};

/*
 * engine thread pools
 */
bool
engine::EnginePool::MatchThread(ThreadPoolThread *thr,
                                  void *userData)
{
    engine::Worker *worker = reinterpret_cast<engine::Worker *>(thr);

    return (worker->GetConfigRec() == userData);
}

/*
 * get the resource builder
 */
#include "resources.c"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Resolve callbacks.
 *
 ****************************************************************************/
static void
ResolveCallbacks(ENGINE_TransportCallbacks cbRec, DISP_FuncsCPP *cbs)
{
    ENGINE_LibCache cbLib;
    int (*initFunc)(ThreadPoolThread *);
    int (*postInitFunc)(ThreadPoolThread *, ITS_HANDLE);
    bool (*failFunc)(ThreadPoolThread *, int);
    int (*eventFunc)(ThreadPoolThread *, Event &);
    int (*acceptFunc)(ThreadPoolThread *, ThreadPoolThread *);
    void (*termFunc)(ThreadPoolThread *);

    /* get the lib */
    cbLib = ENGINE_LibGet(application,
                          ENGINE_TC_LIB_NAME(cbRec));
    ITS_C_ASSERT(cbLib != NULL);

    /* resolve each function specified */
    if (ENGINE_TC_PRE_INIT(cbRec))
    {
        initFunc = (int (*)(ThreadPoolThread *))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_PRE_INIT(cbRec));

        if (initFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_PRE_INIT(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(initFunc != NULL);
        cbs->PreInitialize = initFunc;
    }
    if (ENGINE_TC_POST_INIT(cbRec))
    {
        postInitFunc = (int (*)(ThreadPoolThread *, ITS_HANDLE))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_POST_INIT(cbRec));

        if (postInitFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_POST_INIT(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(postInitFunc != NULL);
        cbs->PostInitialize = postInitFunc;
    }
    if (ENGINE_TC_PRE_NEXT_EVENT(cbRec))
    {
        initFunc = (int (*)(ThreadPoolThread *))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_PRE_NEXT_EVENT(cbRec));

        if (initFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_PRE_NEXT_EVENT(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(initFunc != NULL);
        cbs->PreNextEvent = initFunc;
    }
    if (ENGINE_TC_NEXT_EVENT_FAIL(cbRec))
    {
        failFunc = (bool (*)(ThreadPoolThread *, int))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_NEXT_EVENT_FAIL(cbRec));

        if (failFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_NEXT_EVENT_FAIL(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(failFunc != NULL);
        cbs->NextEventFailed = failFunc;
    }
    if (ENGINE_TC_POST_NEXT_EVENT(cbRec))
    {
        eventFunc = (int (*)(ThreadPoolThread *, Event &))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_POST_NEXT_EVENT(cbRec));

        if (eventFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_POST_NEXT_EVENT(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(eventFunc != NULL);
        cbs->PostNextEvent = eventFunc;
    }
    if (ENGINE_TC_DISP_USER(cbRec))
    {
        eventFunc = (int (*)(ThreadPoolThread *, Event &))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_DISP_USER(cbRec));

        if (eventFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_DISP_USER(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(eventFunc != NULL);
        cbs->DispatchUserEvent = eventFunc;
    }
    if (ENGINE_TC_DISP_ISUP(cbRec))
    {
        eventFunc = (int (*)(ThreadPoolThread *, Event &))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_DISP_ISUP(cbRec));

        if (eventFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_DISP_ISUP(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(eventFunc != NULL);
        cbs->DispatchISUPEvent = eventFunc;
    }
    if (ENGINE_TC_DISP_SCCP(cbRec))
    {
        eventFunc = (int (*)(ThreadPoolThread *, Event &))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_DISP_SCCP(cbRec));

        if (eventFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_DISP_SCCP(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(eventFunc != NULL);
        cbs->DispatchSCCPEvent = eventFunc;
    }
    if (ENGINE_TC_PRE_ACCEPT(cbRec))
    {
        acceptFunc = (int (*)(ThreadPoolThread *, ThreadPoolThread *))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_PRE_ACCEPT(cbRec));

        if (acceptFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_PRE_ACCEPT(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(acceptFunc != NULL);
        cbs->PreAccept = acceptFunc;
    }
    if (ENGINE_TC_ON_ACCEPT(cbRec))
    {
        acceptFunc = (int (*)(ThreadPoolThread *, ThreadPoolThread *))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_ON_ACCEPT(cbRec));

        if (acceptFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_ON_ACCEPT(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(acceptFunc != NULL);
        cbs->OnAccept = acceptFunc;
    }
    if (ENGINE_TC_PRE_TERM(cbRec))
    {
        termFunc = (void (*)(ThreadPoolThread *))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_PRE_TERM(cbRec));

        if (termFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_PRE_TERM(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(termFunc != NULL);
        cbs->PreTerminate = termFunc;
    }
    if (ENGINE_TC_POST_TERM(cbRec))
    {
        termFunc = (void (*)(ThreadPoolThread *))
            DLSYM_Resolve(ENGINE_LC_LIBRARY(cbLib),
                          ENGINE_TC_POST_TERM(cbRec));

        if (termFunc == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_TC_POST_TERM(cbRec), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(termFunc != NULL);
        cbs->PostTerminate = termFunc;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Construct a worker transport.
 *
 *  Notes:
 *      This is actually where we advance the transport pointer.  Be
 *      careful of its usage.
 *
 ****************************************************************************/
ThreadPoolThread *
EngineWorkerPool::CreatePoolThread(int stackSize)
{
    engine::Worker *worker;
    DISP_FuncsCPP *cbs;
    ENGINE_TransportCallbacks cbRec;
    static int numAssociates = 0;
    static ITS_BOOLEAN buildingAssociates = ITS_FALSE;
    static char buf[ITS_PATH_MAX];

    /* catch numThreads > item count in list */
    ITS_C_REQUIRE(transports != NULL);

    try
    {
        /* give it a name if it lacks one */
        if (ENGINE_TR_NAME(transports) == NULL)
        {
            sprintf(buf, ITS_UNNAMED_TRANSPORT_FORMAT_STRING,
                    ENGINE_TR_INST(transports));
        }
        else
        {
            strcpy(buf, ENGINE_TR_NAME(transports));
        }

        /* create the worker transport */
        worker = new engine::Worker(stackSize, buf,
                                    ENGINE_TR_INST(transports),
                                    ENGINE_TR_MASK(transports));
        ITS_C_ASSERT(worker != NULL);

        /* set the config rec */
        worker->GetConfigRec() = transports;

        /* create the callback struct. */
        worker->GetCallbackStruct() = (DISP_FuncsCPP *)
                                          calloc(1, sizeof(DISP_FuncsCPP));
        ITS_C_ASSERT(worker->GetCallbackStruct() != NULL);
        cbs = worker->GetCallbackStruct();

        /* populate the callbacks */
        cbRec = (ENGINE_TransportCallbacks)ENGINE_TR_CALLBACKS(transports);
        cbs->type = ENGINE_TC_TYPE(cbRec);

        /* resolve callbacks */
        ResolveCallbacks(cbRec, cbs);

        /* advance the pointer */
        if (buildingAssociates)
        {
            numAssociates--;

            ENGINE_TR_INST(transports)++;

            if (numAssociates == 0)
            {
                buildingAssociates = ITS_FALSE;
            }
        }
        else
        {
            if (ENGINE_TR_NUM_ASSOCIATES(transports))
            {
                numAssociates = ENGINE_TR_NUM_ASSOCIATES(transports) - 1;

                if (numAssociates)
                {
                    buildingAssociates = ITS_TRUE;

                    ENGINE_TR_INST(transports)++;
                }
            }
        }

        if (!buildingAssociates)
        {
            transports = ENGINE_TR_NEXT(transports);
        }

        return (ThreadPoolThread *)worker;
    }
    catch (GenericException& ge)
    {
        ge.Log();

        return (NULL);
    }
    catch (exception& ex)
    {
        StandardException se(ex.what());

        se.Log();

        return (NULL);
    }

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Construct a dynamic transport.
 *
 ****************************************************************************/
ThreadPoolThread *
EngineDynamicPool::CreatePoolThread(int stackSize)
{
    ITS_UINT mask = parent->GetMask();
    engine::Worker *sub;
    char buf[ITS_PATH_MAX];

    try
    {
        /* zero out the appropriate bits */
        mask &= ~ITS_TRANSPORT_SSOCKET_ITER;
        mask |= ITS_TRANSPORT_SSOCKET_DYN;

        /* make a name */
        sprintf(buf, "%s-%d", parent->GetName(),
                ENGINE_TR_INST(transports));

        /* build the worker */
        sub = new engine::Worker(stackSize, buf,
                                 ENGINE_TR_INST(transports), mask);
        ITS_C_REQUIRE(sub != NULL);

        /* update the instance */
        ENGINE_TR_INST(transports)++;

        /* set the config rec */
        sub->GetConfigRec() = transports;

        /* copy the parent's resources */
        sub->GetCallbackStruct() = (DISP_FuncsCPP *)
                                       calloc(1, sizeof(DISP_FuncsCPP));
        ITS_C_ASSERT(sub->GetCallbackStruct() != NULL);
        memcpy(sub->GetCallbackStruct(), parent->GetCallbackStruct(),
               sizeof(DISP_FuncsCPP));

        return (ThreadPoolThread *)sub;
    }
    catch (GenericException& ge)
    {
        ge.Log();

        return (NULL);
    }
    catch (exception& ex)
    {
        StandardException se(ex.what());

        se.Log();

        return (NULL);
    }

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Construct a border transport.
 *
 *  Notes:
 *      This is actually where we advance the transport pointer.  Be
 *      careful of its usage.
 *
 ****************************************************************************/
ThreadPoolThread *
EngineBorderPool::CreatePoolThread(int stackSize)
{
    engine::Worker *border;
    DISP_FuncsCPP *cbs;
    ENGINE_TransportCallbacks cbRec;

    /* catch numThreads > item count in list */
    ITS_C_REQUIRE(transports != NULL);

    try
    {
        /* create the border transport */
        if (ITS_GET_TRANSPORT_TYPE(ENGINE_TR_MASK(transports)) ==
            ITS_TRANSPORT_TQUEUE)
        {
            border = new engine::Worker(stackSize, ENGINE_TR_NAME(transports),
                                        ENGINE_TR_INST(transports),
                                        ENGINE_TR_MASK(transports));
        }
        else
        {
            border = new engine::Worker(stackSize, ENGINE_TR_NAME(transports),
                                        ENGINE_TR_INST(transports),
                                        ENGINE_TR_MASK(transports)|
                                         ITS_TRANSPORT_DELAY_CREATE);
        }
        ITS_C_ASSERT(border != NULL);

        /* update the instance number in case of subs */
        ENGINE_TR_INST(transports)++;
    
        /* set the config rec */
        border->GetConfigRec() = transports;

        /* create the callback struct. */
        border->GetCallbackStruct() = (DISP_FuncsCPP *)
                                          calloc(1, sizeof(DISP_FuncsCPP));
        ITS_C_ASSERT(border->GetCallbackStruct() != NULL);
        cbs = border->GetCallbackStruct();

        /* populate the callbacks */
        cbRec = (ENGINE_TransportCallbacks)ENGINE_TR_CALLBACKS(transports);
        cbs->type = ENGINE_TC_TYPE(cbRec);

        /* resolve callbacks */
        ResolveCallbacks(cbRec, cbs);

        /* if it's iterative, it needs a sub-pool */
        if (ENGINE_TR_MASK(transports) & ITS_TRANSPORT_SSOCKET_ITER)
        {
            ENGINE_LibCache mainLib;
            const char *mainFunc;

            /* which function? */
            if ((ENGINE_TR_MASK(transports) & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                mainFunc = DISP_ANSI_CPP_STRING;
            }
            else if ((ENGINE_TR_MASK(transports) & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                mainFunc = DISP_CCITT_CPP_STRING;
            }
            else
            {
                mainFunc = DISP_USER_CPP_STRING;
            }

#if defined(DEBUG) || defined(_DEBUG)
            mainLib = ENGINE_LibGet(application,
                                    DISPATCH_DEBUG_STRING);
#else
            mainLib = ENGINE_LibGet(application,
                                    DISPATCH_STRING);
#endif
            ITS_C_ASSERT(mainLib != NULL);

            /* bind it. */
            cbs->dispAccept = (DISP_CPPDispatcher)
                                DLSYM_Resolve(ENGINE_LC_LIBRARY(mainLib),
                                mainFunc);

            if (cbs->dispAccept == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       mainFunc, DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cbs->dispAccept != NULL);

            /* create the pool */
            cbs->pool = new EngineDynamicPool(border);
            ITS_C_ASSERT(cbs->pool != NULL);

            cbs->pool->CreatePool(ENGINE_TR_NUM_ASSOCIATES(transports),
                                  stackSize);
        }

        /* advance the pointer */
        transports = ENGINE_TR_NEXT(transports);

        /* skip virtual transports */
        while (transports &&
               (ENGINE_TR_MASK(transports) & (ITS_TRANSPORT_DATAGRAM |
                                              ITS_TRANSPORT_DGRAM_VIRT)) ==
               (ITS_TRANSPORT_DATAGRAM | ITS_TRANSPORT_DGRAM_VIRT))
        {
            transports = ENGINE_TR_NEXT(transports);
        }

        return (ThreadPoolThread *)border;
    }
    catch (GenericException& ge)
    {
        ge.Log();

        return (NULL);
    }
    catch (exception& ex)
    {
        StandardException se(ex.what());

        se.Log();

        return (NULL);
    }

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dispatch a border transport.
 *
 ****************************************************************************/
static void
DispatchBorder(ITS_Object trans)
{
    ENGINE_TransportCallbacks cb;
    ENGINE_LibCache mainLib;
    DISP_CPPDispatcher mainFunc;
    ThreadPoolEntry thr;
    int ret;

    /* skip virtual transports */
    if ((ENGINE_TR_MASK(trans) & (ITS_TRANSPORT_DATAGRAM |
                                  ITS_TRANSPORT_DGRAM_VIRT)) ==
           (ITS_TRANSPORT_DATAGRAM | ITS_TRANSPORT_DGRAM_VIRT))
    {
        return;
    }

    /* get the callback control record */
    cb = (ENGINE_TransportCallbacks)ENGINE_TR_CALLBACKS(trans);

    /* resolve mainFunc */
    if (ENGINE_TC_HANDLER_TYPE(cb) == DISP_PROT_CUSTOM)
    {
        mainLib = ENGINE_LibGet(application,
                                ENGINE_TC_LIB_NAME(cb));
    }
    else
    {
#if defined(DEBUG) || defined(_DEBUG)
        mainLib = ENGINE_LibGet(application,
                                DISPATCH_DEBUG_STRING);
#else
        mainLib = ENGINE_LibGet(application,
                                DISPATCH_STRING);
#endif
    }

    ITS_C_ASSERT(mainLib != NULL);

    mainFunc = (DISP_CPPDispatcher)
        DLSYM_Resolve(ENGINE_LC_LIBRARY(mainLib),
                      ENGINE_TC_MAIN(cb));

    if (mainFunc == NULL &&
        (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
         SERVICE_GetType() == ST_NOT_SET))
    {
        printf("Error resolving symbol %s : %s\n",
               ENGINE_TC_MAIN(cb), DLSYM_Error());
        fflush(stdout);
    }

    ITS_C_ASSERT(mainFunc != NULL);

    /* get the thread and dispatch it */
    ret = engine::borderPool->GetFirstAvailThread(thr);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = engine::borderPool->DispatchOnThread(thr, mainFunc,
                                               ((engine::Worker *)
                                                thr.GetThread())->
                                                   GetCallbackStruct());
    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Construct the thread pools.  This is too difficult to do inline.
 *
 ****************************************************************************/
static void
BuildThreadPools()
{
    ITS_Object list, trans;
    int numTransports;

    try
    {
        /* create worker pool first */
        for (list = ENGINE_APP_POOLS(application);
             list != NULL;
             list = ENGINE_TP_NEXT(list))
        {
            if (ENGINE_TP_TYPE(list) == TP_WORKERS)
            {
                /*
                 * here we create workers, whether they be specific (e.g.,
                 * protocol engines) or generic (e.g., simple workers).
                 */
                ITS_C_ASSERT(engine::workerPool == NULL);

                /* count 'em */
                numTransports = 0;
                for (trans = ENGINE_TP_TRANSPORTS(list);
                     trans != NULL;
                     trans = ENGINE_TR_NEXT(trans))
                {
                    numTransports++;

                    if (ENGINE_TR_NUM_ASSOCIATES(trans))
                    {
                        numTransports += ENGINE_TR_NUM_ASSOCIATES(trans) - 1;
                    }
                }

                /* cache a pointer to the list we're working */
                transports = ENGINE_TP_TRANSPORTS(list);

                /* create the pool */
                engine::workerPool = new EngineWorkerPool();
                ITS_C_ASSERT(engine::workerPool != NULL);

                engine::workerPool->CreatePool(numTransports,
                                       ENGINE_TP_STACK_SIZE(list));

            }
        }

        /* create workItem pool next */
        for (list = ENGINE_APP_POOLS(application);
             list != NULL;
             list = ENGINE_TP_NEXT(list))
        {
            if (ENGINE_TP_TYPE(list) == TP_WORK_ITEMS)
            {
                ITS_Object items;

                /*
                 * here we create a single work item pool.  Note that this
                 * pool will be reused by ALL work items.
                 */
                ITS_C_ASSERT(workItemPool == NULL);

                /* create the pool */
                transports = ENGINE_TP_TRANSPORTS(list);
                ITS_C_ASSERT(transports != NULL);

                workItemPool = new WorkItemPool(ENGINE_TR_INST(transports),
                                                ENGINE_TR_NUM_ASSOCIATES(transports),
                                                ENGINE_TP_STACK_SIZE(list));
                ITS_C_ASSERT(workItemPool != NULL);

                /* add the work items */
                for (items = ENGINE_TR_WORK_ITEMS(transports);
                     items != NULL;
                     items = ENGINE_WI_NEXT(items))
                {
                    ENGINE_LibCache wiLib;
                    WORKITEM_ItemFunc wiFunc;
                    int i, ret;

                    /* resolve the delegate */
                    wiLib = ENGINE_LibGet(application,
                                          ENGINE_WI_LIB_NAME(items));
                    ITS_C_ASSERT(wiLib != NULL);

                    wiFunc = (WORKITEM_ItemFunc)
                                DLSYM_Resolve(ENGINE_LC_LIBRARY(wiLib),
                                              ENGINE_WI_DELEGATE(items));

                    if (wiFunc == NULL &&
                        (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                         SERVICE_GetType() == ST_NOT_SET))
                    {
                        printf("Error resolving symbol %s : %s\n",
                               ENGINE_WI_DELEGATE(items), DLSYM_Error());
                        fflush(stdout);
                    }

                    ITS_C_ASSERT(wiFunc != NULL);

                    /* add the items */
                    for (i = 0; i < ENGINE_WI_REPEAT(items); i++)
                    {
                        WORKITEM_Instance *item;

                        item = WORKITEM_Create(sizeof(WORKITEM_Instance),
                                               ENGINE_WI_PERSIST(items),
                                               wiFunc);
                        ITS_C_ASSERT(item != NULL);

                        ret = WORKITEM_PutWorkItem(ENGINE_TR_INST(transports),
                                                   item);
                        ITS_C_ASSERT(ret == ITS_SUCCESS);
                    }
                }
            }
        }

        /* finally, create the border pools */
        for (list = ENGINE_APP_POOLS(application);
             list != NULL;
             list = ENGINE_TP_NEXT(list))
        {
            if (ENGINE_TP_TYPE(list) == TP_BORDERS)
            {
                /*
                 * we are expecting a list of unique border threads.  One thing
                 * to note is that all distinct threads will be created first.
                 * If ITERATIVE transports are created, a separate sub-pool
                 * will be created for each.  In this way we can assure homogeneous
                 * pools for each ITERATIVE transport.  The sub-pool will be
                 * stored in the callback structure for each iterative.
                 */
                ITS_C_ASSERT(engine::borderPool == NULL);

                /* count 'em */
                numTransports = 0;
                for (trans = ENGINE_TP_TRANSPORTS(list);
                     trans != NULL;
                     trans = ENGINE_TR_NEXT(trans))
                {
                    /* skip virtual transports */
                    if ((ENGINE_TR_MASK(trans) & (ITS_TRANSPORT_DATAGRAM |
                                                  ITS_TRANSPORT_DGRAM_VIRT)) ==
                           (ITS_TRANSPORT_DATAGRAM | ITS_TRANSPORT_DGRAM_VIRT))
                    {
                        continue;
                    }

                    numTransports++;
                }

                /* cache a pointer to the list we're working */
                transports = ENGINE_TP_TRANSPORTS(list);

                /* skip virtual transports */
                while (transports &&
                       (ENGINE_TR_MASK(transports) & (ITS_TRANSPORT_DATAGRAM |
                                                      ITS_TRANSPORT_DGRAM_VIRT)) ==
                       (ITS_TRANSPORT_DATAGRAM | ITS_TRANSPORT_DGRAM_VIRT))
                {
                    transports = ENGINE_TR_NEXT(transports);
                }

                /* create the pool */
                engine::borderPool = new EngineBorderPool();
                ITS_C_ASSERT(engine::borderPool != NULL);

                engine::borderPool->CreatePool(numTransports,
                                               ENGINE_TP_STACK_SIZE(list));

            }
        }
    }
    catch (GenericException& ge)
    {
        ge.Log();

        ITS_C_ASSERT(ITS_FALSE);
    }
    catch (exception& ex)
    {
        StandardException se(ex.what());

        se.Log();

        ITS_C_ASSERT(ITS_FALSE);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Perform initialization duties
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *
 ****************************************************************************/
extern "C" void
PreFunc(int argc, const char **argv)
{
    ITS_Object list;
    const char *name = APPL_GetConfigFileName();
    ENGINE_LibCache appLib;
    int i;
    ITS_Class dbClass;

    /* set up the resource file */
    i = ITS_InitializeClass(itsRESFILE_Class);

    ITS_C_ASSERT(i == ITS_SUCCESS);

    appRes = RESFILE_CreateEmptyResourceManager(name);

    /* add any global options */
    for (i = 0; i < ENGINE_APP_NUM_OPTIONS(application); i++)
    {
        char buf[ITS_PATH_MAX], *tmp;

        strcpy(buf, ENGINE_APP_OPTIONS(application)[i]);
        tmp = strchr(buf, '=');

        ITS_C_ASSERT(tmp != NULL);

        *tmp = 0;
        tmp++;

        RESFILE_AddKeyValue(appRes, NULL, buf, tmp);
    }

    /* add any feature records */
    for (list = ENGINE_APP_FEATURES(application);
         list != NULL;
         list = ENGINE_FEAT_NEXT(list))
    {
        ITS_C_ASSERT(ENGINE_FEAT_CLASS_REC(list) != NULL);

        if (ITS_AddFeature(ENGINE_FEAT_CLASS_REC(list)) != ITS_SUCCESS)
        {
            printf("Failed to add feature: '%s'\n",
                   ITS_CLASS_CLASSNAME(ENGINE_FEAT_CLASS_REC(list)));

            abort();
        }

        for (i = 0; i < ENGINE_FEAT_NUM_OPTIONS(list); i++)
        {
            char buf[ITS_PATH_MAX], *tmp;

            strcpy(buf, ENGINE_FEAT_OPTIONS(list)[i]);
            tmp = strchr(buf, '=');

            ITS_C_ASSERT(tmp != NULL);

            *tmp = 0;
            tmp++;

            RESFILE_AddKeyValue(appRes, NULL, buf, tmp);
        }
    }

    /* set trace */
    SetSupportTrace(application);

    /* Set up FaultTolerance (before setting up the resources). */
    if (ENGINE_APP_FAULT_TOLERANCE(application))
    {
        ITS_Object ftGroupMbList;
        ITS_Object ftGroupList;
        char buffer[32];
        int ret;
        ENGINE_FaultTolerance ft =
            (ENGINE_FaultTolerance)ENGINE_APP_FAULT_TOLERANCE(application);

        ret = RESFILE_AddSection(
                appRes, 
                DSM_FAULT_TOLERANCE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = RESFILE_AddSection(
                appRes,
                DSM_NODE_NAME_RESOURCES_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = RESFILE_AddSection(
                appRes,
                DSM_PROCESS_NAME_RESOURCES_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = RESFILE_AddSection(
                appRes,
                DSM_FT_GROUP_NAME_RESOURCES_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_MAX_NUM_FT_GROUPS(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_MAX_NUM_FT_GROUPS_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_MAX_NUM_PROCESSES(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_MAX_NUM_PROCESSES_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_MAX_NUM_NODES(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_MAX_NUM_NODES_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_NODE_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_NODE_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_PROCESS_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_PROCESS_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_TCAP_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_TCAP_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_SCCP_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_SCCP_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_MTP3_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_MTP3_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_ISUP_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_ISUP_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_ROUTING_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_ROUTING_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_TIMERS_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_TIMERS_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buffer, "%u", ENGINE_FT_MGMT_DATA_FT_GROUP_ID(ft));
        ret = RESFILE_AddKeyValue(
                appRes,
                DSM_FAULT_TOLERANCE_STRING,
                DSM_MGMT_DATA_FT_GROUP_ID_STRING,
                buffer);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        for (
            ftGroupList = ENGINE_FT_FT_GROUPS(ft); 
            ftGroupList != NULL; 
            ftGroupList = ENGINE_FT_GROUP_NEXT(ftGroupList))
        {
            ITS_USHORT ftGroupId;
            char ftGroupName[64];
            ITS_USHORT numFtGroupMbs;
            ENGINE_FtGroup ftGroup = (ENGINE_FtGroup)ftGroupList;

            ftGroupId = ENGINE_FT_GROUP_FT_GROUP_ID(ftGroup);

            sprintf(ftGroupName, "%s%u", DSM_FT_GROUP_STRING, ftGroupId);

            ret = RESFILE_AddSection(
                    appRes,
                    ftGroupName);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            sprintf(buffer, "%u", ENGINE_FT_GROUP_FT_GROUP_ID(ftGroup));
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_FT_GROUP_ID_STRING,
                    buffer);

            if (ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup))
            {
                sprintf(buffer, "%u", ENGINE_FT_GROUP_FT_GROUP_ID(ftGroup));
                ret = RESFILE_AddKeyValue(
                        appRes,
                        DSM_FT_GROUP_NAME_RESOURCES_STRING,
                        DSM_FT_GROUP_NAME_RES_FT_GROUP_ID,
                        buffer);
                ITS_C_ASSERT(ret == ITS_SUCCESS);

                ret = RESFILE_AddKeyValue(
                        appRes,
                        DSM_FT_GROUP_NAME_RESOURCES_STRING,
                        DSM_FT_GROUP_NAME_RES_FT_GROUP_NAME,
                        ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup));
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            sprintf(buffer, "%u", ENGINE_FT_GROUP_DSM_SIZE(ftGroup));
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SIZE_STRING,
                    buffer);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_BASE_ADDRESS_STRING,
                    ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup));
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            sprintf(buffer, "%u", ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(ftGroup));
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_MAX_NUM_TABLES_STRING,
                    buffer);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_TYPE_STRING,
                    ENGINE_FT_GROUP_DSM_TYPE(ftGroup));
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            numFtGroupMbs = 0;

            for (
                ftGroupMbList = ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftGroup);
                ftGroupMbList != NULL;
                ftGroupMbList = ENGINE_FT_GROUP_MEMBER_NEXT(ftGroupMbList))
            {
                numFtGroupMbs++;
            }

            sprintf(buffer, "%u", numFtGroupMbs);

            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_NUM_FT_GROUP_MEMBERS_STRING,
                    buffer);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            for (
                ftGroupMbList = ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftGroup);
                ftGroupMbList != NULL;
                ftGroupMbList = ENGINE_FT_GROUP_MEMBER_NEXT(ftGroupMbList))
            {
                ENGINE_FtGroupMember ftGroupMb = 
                    (ENGINE_FtGroupMember)ftGroupMbList;

                sprintf(
                    buffer, 
                    "%u", 
                    ENGINE_FT_GROUP_MEMBER_NODE_ID(ftGroupMb));
                ret = RESFILE_AddKeyValue(
                        appRes,
                        ftGroupName,
                        DSM_FT_GROUP_MEMBER_NODE_ID_STRING,
                        buffer);
                ITS_C_ASSERT(ret == ITS_SUCCESS);

                sprintf(
                    buffer, 
                    "%u", 
                    ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftGroupMb));
                ret = RESFILE_AddKeyValue(
                        appRes,
                        ftGroupName,
                        DSM_FT_GROUP_MEMBER_PROCESS_ID_STRING,
                        buffer);
                ITS_C_ASSERT(ret == ITS_SUCCESS);

                if (ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMb))
                {
                    sprintf(
                        buffer, 
                        "%u", 
                        ENGINE_FT_GROUP_MEMBER_NODE_ID(ftGroupMb));
                    ret = RESFILE_AddKeyValue(
                            appRes,
                            DSM_NODE_NAME_RESOURCES_STRING,
                            DSM_NODE_NAME_RES_NODE_ID,
                            buffer);
                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                    
                    ret = RESFILE_AddKeyValue(
                            appRes,
                            DSM_NODE_NAME_RESOURCES_STRING,
                            DSM_NODE_NAME_RES_NODE_NAME,
                            ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMb));
                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                }

                if (ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMb))
                {
                    sprintf(
                        buffer, 
                        "%u", 
                        ENGINE_FT_GROUP_MEMBER_NODE_ID(ftGroupMb));
                    ret = RESFILE_AddKeyValue(
                            appRes,
                            DSM_PROCESS_NAME_RESOURCES_STRING,
                            DSM_PROCESS_NAME_RES_NODE_ID,
                            buffer);
                    ITS_C_ASSERT(ret == ITS_SUCCESS);

                    sprintf(
                        buffer, 
                        "%u", 
                        ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftGroupMb));
                    ret = RESFILE_AddKeyValue(
                            appRes,
                            DSM_PROCESS_NAME_RESOURCES_STRING,
                            DSM_PROCESS_NAME_RES_PROCESS_ID,
                            buffer);
                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                    
                    ret = RESFILE_AddKeyValue(
                            appRes,
                            DSM_PROCESS_NAME_RESOURCES_STRING,
                            DSM_PROCESS_NAME_RES_PROCESS_NAME,
                            ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMb));
                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                }
            }

            numFtGroupMbs = 0;

            for (
                ftGroupMbList = 
                    ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(ftGroup);
                ftGroupMbList != NULL;
                ftGroupMbList = ENGINE_FT_GROUP_MEMBER_NEXT(ftGroupMbList))
            {
                numFtGroupMbs++;
            }

            sprintf(buffer, "%u", numFtGroupMbs);
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_NUM_MASTER_FT_GROUP_MEMBERS_STRING,
                    buffer);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            for (
                ftGroupMbList = 
                    ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(ftGroup);
                ftGroupMbList != NULL;
                ftGroupMbList = ENGINE_FT_GROUP_MEMBER_NEXT(ftGroupMbList))
            {
                ENGINE_FtGroupMember ftGroupMb = 
                    (ENGINE_FtGroupMember)ftGroupMbList;

                sprintf(
                    buffer,
                    "%u",
                    ENGINE_FT_GROUP_MEMBER_NODE_ID(ftGroupMb));
                ret = RESFILE_AddKeyValue(
                        appRes,
                        ftGroupName,
                        DSM_MASTER_FT_GROUP_MEMBER_NODE_ID_STRING,
                        buffer);
                ITS_C_ASSERT(ret == ITS_SUCCESS);

                sprintf(
                    buffer,
                    "%u",
                    ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftGroupMb));
                ret = RESFILE_AddKeyValue(
                        appRes,
                        ftGroupName,
                        DSM_MASTER_FT_GROUP_MEMBER_PROCESS_ID_STRING,
                        buffer);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }
        }
    }

    /* set the resources */
    PopulateResources();

    /* set up toolkit trace */
    i = ITS_InitializeClass(itsTRACE_Class);
    ITS_C_ASSERT(i == ITS_SUCCESS);
    TRACE_UpdateSettings();

    /* dump sanity check */
    RESFILE_Dump(appRes);

    /* 
     * Resolve and set up Fault Tolerance FtGroup specific callbacks (if any). 
     * Use "pre-add callback" DSM API functions. Need to be done before DSM
     * initialization (part of ITS_GlobalStart) to generate "self-alive" and 
     * "self-join" related callbacks.
     */
    if (ENGINE_APP_FAULT_TOLERANCE(application))
    {
        ENGINE_FaultTolerance ft;
        ITS_Object ftGroupList;

        ft = (ENGINE_FaultTolerance)ENGINE_APP_FAULT_TOLERANCE(application);

        for (
            ftGroupList = ENGINE_FT_FT_GROUPS(ft); 
            ftGroupList != NULL; 
            ftGroupList = ENGINE_FT_GROUP_NEXT(ftGroupList))
        {
            ENGINE_FtGroup ftGroup;
            ITS_USHORT ftGroupId;
            ITS_Object callbacks;
            ENGINE_LibCache lib;
            int ret;

            ftGroup = (ENGINE_FtGroup)ftGroupList;

            ftGroupId = ENGINE_FT_GROUP_FT_GROUP_ID(ftGroup);

            for (
                callbacks = ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup);
                callbacks != NULL;
                callbacks = ENGINE_FT_CALLBACK_NEXT(callbacks))
            {
                switch (ENGINE_FT_CALLBACK_TYPE(callbacks))
                {
                case FT_CALLBACK_MEMBERSHIP_CHANGE:
                    {
                        DSM_MembershipChangeCb cbFunc;

                        if (ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) == NULL)
                        {
                            ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) = 
                                strdup("");

                            ITS_C_ASSERT(
                                ENGINE_FT_CALLBACK_LIBRARY_NAME(
                                    callbacks) != NULL);
                        }

                        lib = ENGINE_LibGet(
                                application,
                                ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks));

                        ITS_C_ASSERT(lib != NULL);

                        cbFunc = 
                        (DSM_MembershipChangeCb)
                            DLSYM_Resolve(
                                ENGINE_LC_LIBRARY(lib),
                                ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks));
                        if (cbFunc == NULL)
                        {
                            printf(
                                "Error resolving symbol %s : %s\n",
                                ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks),
                                DLSYM_Error());
                            fflush(stdout);
                        }

                        ret = DSM_PreAddMembershipChangeCallback(
                                ftGroupId,
                                cbFunc,
                                NULL);
                        if (ret != ITS_SUCCESS)
                        {
                            /* TODO: add trace. */
                        }

                        break;
                    }

                case FT_CALLBACK_EVENT_FROM_FT_GROUP_MEMBER:
                    {
                        DSM_EventFromFtGroupMemberCb cbFunc;

                        if (ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) == NULL)
                        {
                            ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) = 
                                strdup("");

                            ITS_C_ASSERT(
                                ENGINE_FT_CALLBACK_LIBRARY_NAME(
                                    callbacks) != NULL);
                        }

                        lib = ENGINE_LibGet(
                                application,
                                ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks));

                        ITS_C_ASSERT(lib != NULL);

                        cbFunc = 
                        (DSM_EventFromFtGroupMemberCb)
                            DLSYM_Resolve(
                                ENGINE_LC_LIBRARY(lib),
                                ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks));
                        if (cbFunc == NULL)
                        {
                            printf(
                                "Error resolving symbol %s : %s\n",
                                ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks),
                                DLSYM_Error());
                            fflush(stdout);
                        }

                        ret = DSM_PreAddEventFromFtGroupMemberCallback(
                                ftGroupId,
                                cbFunc,
                                NULL);
                        if (ret != ITS_SUCCESS)
                        {
                            /* TODO: add trace. */
                        }

                        break;
                    }

                default:
                    {
                        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                        ITS_C_ASSERT(must_not_be_reached);
                        break;
                    }
                }
            }
        }
    }

    /* start IntelliSS7 */
    ITS_GlobalStart(ENGINE_APP_GS_MASK(application));

    /* 
     * Resolve and set up Fault Tolerance procedures and all FtGroups callbacks
     * (if any). 
     */
    if (ENGINE_APP_FAULT_TOLERANCE(application))
    {
        ENGINE_FaultTolerance ft;
        ITS_Object callbacks;
        ENGINE_LibCache lib;
        int ret;

        ft = (ENGINE_FaultTolerance)ENGINE_APP_FAULT_TOLERANCE(application);

        if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL)
        {
            FTM_PreExecuteLogicProc proc;

            if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) == NULL)
            {
                ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) = strdup("");

                ITS_C_ASSERT(
                    ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
            }

            lib = ENGINE_LibGet(
                    application, 
                    ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft));

            ITS_C_ASSERT(lib != NULL);

            proc = (FTM_PreExecuteLogicProc)
                        DLSYM_Resolve(
                            ENGINE_LC_LIBRARY(lib),
                            ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft));
            if (proc == NULL)
            {
                printf(
                    "Error resolving symbol %s : %s\n",
                    ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft), 
                    DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(proc != NULL);

            FTM_SetPreExecuteLogic(proc);                   
        }

        if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL)
        {
            FTM_LoopExecuteLogicProc proc;

            if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) == NULL)
            {
                ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) = strdup("");

                ITS_C_ASSERT(
                    ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
            }

            lib = ENGINE_LibGet(
                    application, 
                    ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft));

            ITS_C_ASSERT(lib != NULL);

            proc = (FTM_LoopExecuteLogicProc)
                        DLSYM_Resolve(
                            ENGINE_LC_LIBRARY(lib),
                            ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft));
            if (proc == NULL)
            {
                printf(
                    "Error resolving symbol %s : %s\n",
                    ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft), 
                    DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(proc != NULL);

            FTM_SetLoopExecuteLogic(proc);                   
        }

        if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL)
        {
            FTM_PostExecuteLogicProc proc;

            if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) == NULL)
            {
                ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) = strdup("");

                ITS_C_ASSERT(
                    ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
            }

            lib = ENGINE_LibGet(
                    application, 
                    ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft));

            ITS_C_ASSERT(lib != NULL);

            proc = (FTM_PostExecuteLogicProc)
                        DLSYM_Resolve(
                            ENGINE_LC_LIBRARY(lib),
                            ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft));
            if (proc == NULL)
            {
                printf(
                    "Error resolving symbol %s : %s\n",
                    ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft), 
                    DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(proc != NULL);

            FTM_SetPostExecuteLogic(proc);                   
        }

        for (
            callbacks = ENGINE_FT_CALLBACKS(ft);
            callbacks != NULL;
            callbacks = ENGINE_FT_CALLBACK_NEXT(callbacks))
        {
            switch (ENGINE_FT_CALLBACK_TYPE(callbacks))
            {
            case FT_CALLBACK_MEMBERSHIP_CHANGE_ALL_FT_GROUPS:
                {
                    FTM_MembershipChangeAllFtGroupsCb cbFunc;
                    CALLBACK_Manager* cbManager;
                    FTM_CoreObject* coreObj;

                    if (ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) == NULL)
                    {
                        ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) = 
                            strdup("");

                        ITS_C_ASSERT(
                            ENGINE_FT_CALLBACK_LIBRARY_NAME(
                                callbacks) != NULL);
                    }

                    lib = ENGINE_LibGet(
                            application,
                            ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks));

                    ITS_C_ASSERT(lib != NULL);

                    cbFunc = 
                        (FTM_MembershipChangeAllFtGroupsCb)
                            DLSYM_Resolve(
                                ENGINE_LC_LIBRARY(lib),
                                ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks));
                    if (cbFunc == NULL)
                    {
                        printf(
                            "Error resolving symbol %s : %s\n",
                            ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks), 
                            DLSYM_Error());
                        fflush(stdout);
                    }

                    cbManager = FTM_GetMembershipChangeAllFtGroupsCallbacks();
                    ITS_C_ASSERT(cbManager != NULL);

                    coreObj = (FTM_CoreObject*)
                                LOCKABLE_GetShared(itsFTM_CoreClass);
                    ITS_C_ASSERT(coreObj != NULL);

                    ret = CALLBACK_AddCallback(
                            cbManager,
                            cbFunc,
                            (ITS_POINTER)coreObj);
                    if (ret != ITS_SUCCESS)
                    {
                        /* TODO: add trace. */
                    }

                    break;
                }

            case FT_CALLBACK_EVENT_FROM_ALL_FT_GROUP_MEMBERS:
                {
                    FTM_EventFromAllFtGroupMembersCb cbFunc;
                    CALLBACK_Manager* cbManager;
                    FTM_CoreObject* coreObj;

                    if (ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) == NULL)
                    {
                        ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks) = 
                            strdup("");

                        ITS_C_ASSERT(
                            ENGINE_FT_CALLBACK_LIBRARY_NAME(
                                callbacks) != NULL);
                    }

                    lib = ENGINE_LibGet(
                            application,
                            ENGINE_FT_CALLBACK_LIBRARY_NAME(callbacks));

                    ITS_C_ASSERT(lib != NULL);

                    cbFunc = 
                        (FTM_EventFromAllFtGroupMembersCb)
                            DLSYM_Resolve(
                                ENGINE_LC_LIBRARY(lib),
                                ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks));
                    if (cbFunc == NULL)
                    {
                        printf(
                            "Error resolving symbol %s : %s\n",
                            ENGINE_FT_CALLBACK_FUNCTION_NAME(callbacks), 
                            DLSYM_Error());
                        fflush(stdout);
                    }

                    cbManager = FTM_GetEventFromAllFtGroupMembersCallbacks();
                    ITS_C_ASSERT(cbManager != NULL);

                    coreObj = (FTM_CoreObject*)
                                LOCKABLE_GetShared(itsFTM_CoreClass);
                    ITS_C_ASSERT(coreObj != NULL);

                    ret = CALLBACK_AddCallback(
                            cbManager,
                            cbFunc,
                            (ITS_POINTER)coreObj);
                    if (ret != ITS_SUCCESS)
                    {
                        /* TODO: add trace. */
                    }

                    break;
                }

            default:
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                    ITS_C_ASSERT(must_not_be_reached);
                    break;
                }
            }
        }
    }

    /* do the selectors, if present */
    appLib = ENGINE_LibGet(application, ENGINE_APP_LIB_NAME(application));

    ITS_C_ASSERT(appLib != NULL);

    if (ENGINE_APP_SS7_SELECTOR(application))
    {
        ROUTE_SS7Selector ss7Select;

        ss7Select = (ROUTE_SS7Selector)
                        DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                      ENGINE_APP_SS7_SELECTOR(application));

        if (ss7Select == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_SS7_SELECTOR(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(ss7Select != NULL);

        ROUTE_SetSS7Selector(ss7Select);
    }

    if (ENGINE_APP_APP_SELECTOR(application))
    {
        ROUTE_AppSelector appSelect;

        appSelect = (ROUTE_AppSelector)
                        DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                      ENGINE_APP_APP_SELECTOR(application));

        if (appSelect == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_APP_SELECTOR(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(appSelect != NULL);

        ROUTE_SetApplicationSelector(appSelect);
    }

    if (ENGINE_APP_APP_DESELECTOR(application))
    {
        ROUTE_AppDeselector appDeselect;

        appDeselect = (ROUTE_AppDeselector)
                        DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                      ENGINE_APP_APP_DESELECTOR(application));

        if (appDeselect == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_APP_DESELECTOR(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(appDeselect != NULL);

        ROUTE_SetApplicationDeselector(appDeselect);
    }

    /* set up HMI, if present */
    if (ENGINE_APP_HMI_CB(application))
    {
        ITS_CALLBACK cb;

        cb = (ITS_CALLBACK)
                DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                              ENGINE_APP_HMI_CB(application));

        if (cb == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_HMI_CB(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(cb != NULL);

        CALLBACK_AddCallback(HMI_Callbacks, cb, NULL);
    }
    else
    {
        CALLBACK_AddCallback(HMI_Callbacks, DRIVER_HandleHMI, NULL);
    }

    /* set up alarm, if present */
    if (ENGINE_APP_ALARM_CB(application))
    {
        ITS_CALLBACK cb;

        cb = (ITS_CALLBACK)
                DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                              ENGINE_APP_ALARM_CB(application));

        if (cb == NULL &&
            (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
             SERVICE_GetType() == ST_NOT_SET))
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_ALARM_CB(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(cb != NULL);

        CALLBACK_AddCallback(ALARM_Callbacks, cb, NULL);
    }

    /* set the stack callbacks */
    if (ENGINE_APP_SS7_STACK_MGMT(application))
    {
        ENGINE_SS7StackMgmt stackMgmt;
        ENGINE_LibCache mgmtLib;
        ITS_CALLBACK cb;

        stackMgmt = (ENGINE_SS7StackMgmt)ENGINE_APP_SS7_STACK_MGMT(application);
        mgmtLib = ENGINE_LibGet(application, ENGINE_S7_LIB_NAME(stackMgmt));

        ITS_C_ASSERT(stackMgmt != NULL);

        if (ENGINE_S7_MTP3_MGMT_ANSI(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_MTP3_MGMT_ANSI(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_MTP3_MGMT_ANSI(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(MTP3_ANSI_ManagementCallbacks, cb, NULL);
        }
        if (ENGINE_S7_MTP3_MGMT_CCITT(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_MTP3_MGMT_CCITT(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_MTP3_MGMT_CCITT(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(MTP3_CCITT_ManagementCallbacks, cb, NULL);
        }

        if (ENGINE_S7_ISUP_MGMT_ANSI(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_ISUP_MGMT_ANSI(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_ISUP_MGMT_ANSI(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(ISUP_ManagementCallbacks, cb, NULL);
        }
        if (ENGINE_S7_ISUP_MGMT_CCITT(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_ISUP_MGMT_CCITT(stackMgmt));

            ITS_C_ASSERT(cb != NULL);

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_ISUP_MGMT_CCITT(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }
            /* ANSI Support changes */

            CALLBACK_AddCallback(ISUP_ManagementCallbacks, cb, NULL);
        }

        if (ENGINE_S7_SCCP_MGMT_ANSI(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_SCCP_MGMT_ANSI(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_SCCP_MGMT_ANSI(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(SCCP_ManagementCallbacks, cb, NULL);
        }
        if (ENGINE_S7_SCCP_MGMT_CCITT(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_SCCP_MGMT_CCITT(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_SCCP_MGMT_CCITT(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);
            /* ANSI Support changes */

            CALLBACK_AddCallback(SCCP_ManagementCallbacks, cb, NULL);
        }

        if (ENGINE_S7_SCCP_GTT_ANSI(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_SCCP_GTT_ANSI(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_SCCP_GTT_ANSI(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(SCCP_GlobalTitleTranslator, cb, NULL);
        }
        if (ENGINE_S7_SCCP_GTT_CCITT(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_SCCP_GTT_CCITT(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_SCCP_GTT_CCITT(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);
            /* ANSI Support changes */

            CALLBACK_AddCallback(SCCP_GlobalTitleTranslator, cb, NULL);
        }

        if (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(SCCP_SSNRoutingCallbacks, cb, NULL);
        }
        if (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stackMgmt))
        {
            cb = (ITS_CALLBACK)DLSYM_Resolve(ENGINE_LC_LIBRARY(mgmtLib),
                                             ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stackMgmt));

            if (cb == NULL &&
                (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                 SERVICE_GetType() == ST_NOT_SET))
            {
                printf("Error resolving symbol %s : %s\n",
                       ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stackMgmt), DLSYM_Error());
                fflush(stdout);
            }
            /* ANSI Support changes */

            ITS_C_ASSERT(cb != NULL);

            CALLBACK_AddCallback(SCCP_SSNRoutingCallbacks, cb, NULL);
        }
    }

    /* now we have trace.  Let the user know */
    ITS_TRACE_DEBUG(("Starting initialization\n"));

    /* build the application trace */
    for (list = ENGINE_APP_TRACE_LEVELS(application);
         list != NULL;
         list = ENGINE_TL_NEXT(list))
    {
        if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_CRITICAL_STRING) == 0)
        {
            engine::AppCriticalTrace =
                new TraceLevel(ENGINE_TL_LEVEL_NAME(list),
                               ENGINE_TL_LEVEL_MASK(list));

            TraceSubSystem::GetTrace().AddLevel(APP_LEVEL_CRITICAL,
                                                engine::AppCriticalTrace);

            if (ENGINE_TL_LEVEL_MASK(list) & TRACE_TO_NONE)
            {
                engine::AppCriticalTrace->Disable();
            }
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_ERROR_STRING) == 0)
        {
            engine::AppErrorTrace =
                new TraceLevel(ENGINE_TL_LEVEL_NAME(list),
                               ENGINE_TL_LEVEL_MASK(list));

            TraceSubSystem::GetTrace().AddLevel(APP_LEVEL_ERROR,
                                                engine::AppErrorTrace);

            if (ENGINE_TL_LEVEL_MASK(list) & TRACE_TO_NONE)
            {
                engine::AppErrorTrace->Disable();
            }
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_WARNING_STRING) == 0)
        {
            engine::AppWarningTrace =
                new TraceLevel(ENGINE_TL_LEVEL_NAME(list),
                               ENGINE_TL_LEVEL_MASK(list));

            TraceSubSystem::GetTrace().AddLevel(APP_LEVEL_WARNING,
                                                engine::AppWarningTrace);

            if (ENGINE_TL_LEVEL_MASK(list) & TRACE_TO_NONE)
            {
                engine::AppWarningTrace->Disable();
            }
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_DEBUG_STRING) == 0)
        {
            engine::AppDebugTrace =
                new TraceLevel(ENGINE_TL_LEVEL_NAME(list),
                               ENGINE_TL_LEVEL_MASK(list));

            TraceSubSystem::GetTrace().AddLevel(APP_LEVEL_DEBUG,
                                                engine::AppDebugTrace);

            if (ENGINE_TL_LEVEL_MASK(list) & TRACE_TO_NONE)
            {
                engine::AppDebugTrace->Disable();
            }
        }
    }

    /* build the thread pools */
    BuildThreadPools();

    /* if the user has a worker pool but didn't supply an AppSelector,
     * give them one */
    if (ENGINE_APP_APP_SELECTOR(application) == NULL &&
        ::engine::workerPool != NULL)
    {
        ROUTE_SetApplicationSelector(DRIVER_AppSelector);
    }

    /* Call FTM pre-execute logic procedure if any. */
    if (FTM_GetPreExecuteLogic())
    {
        FTM_PreExecuteLogicProc proc = FTM_GetPreExecuteLogic();

        (*proc)();
    }

    /* Set FTM loop-execute logic to be SERVICE main function. */
    if (FTM_GetLoopExecuteLogic())
    {
        SERVICE_SetMainFunction(FTM_GetLoopExecuteLogic());
    }

    /* call the user's preFunc, if any */
    if (ENGINE_APP_PRE_FUNC(application))
    {
        ENGINE_PrePostFunc preFunc;

        preFunc = (ENGINE_PrePostFunc)
                        DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                      ENGINE_APP_PRE_FUNC(application));

        if (preFunc == NULL)
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_PRE_FUNC(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(preFunc != NULL);

        (*preFunc)();
    }

    /* finally, dispatch the border pools */
    for (list = ENGINE_APP_POOLS(application);
    	 list != NULL;
    	 list = ENGINE_TP_NEXT(list))
    {
    	if (ENGINE_TP_TYPE(list) == TP_BORDERS)
    	{
            ITS_Object trans;

            ITS_C_ASSERT(engine::borderPool != NULL);

            /* dispatch 'em */
            for (trans = ENGINE_TP_TRANSPORTS(list);
                 trans != NULL;
                 trans = ENGINE_TR_NEXT(trans))
            {
                DispatchBorder(trans);
            }
        }
    }

    /* add the engine console */
    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(ENGINE_Console);
        DBC_AddDoCommand(ROUTE_Console);
        DBC_AddDoCommand(LINK_Console);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Cleanup function.
 *
 ****************************************************************************/
extern "C" void
PostFunc(void)
{
    ITS_Object list;
    ITS_Class dbClass;

    /* let the user know we're stopping */
    ITS_TRACE_DEBUG(("Terminating application\n"));

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(ENGINE_Console);
        DBC_RemDoCommand(ROUTE_Console);
        DBC_RemDoCommand(LINK_Console);
    }

    /* call the user's postFunc, if any */
    if (ENGINE_APP_POST_FUNC(application))
    {
        ENGINE_LibCache appLib;
        ENGINE_PrePostFunc postFunc;

        /* do the selectors, if present */
        appLib = ENGINE_LibGet(application, ENGINE_APP_LIB_NAME(application));

        ITS_C_ASSERT(appLib != NULL);

        postFunc = (ENGINE_PrePostFunc)
                        DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                      ENGINE_APP_POST_FUNC(application));

        if (postFunc == NULL)
        {
            printf("Error resolving symbol %s : %s\n",
                   ENGINE_APP_POST_FUNC(application), DLSYM_Error());
            fflush(stdout);
        }

        ITS_C_ASSERT(postFunc != NULL);

        (*postFunc)();
    }

    /* Call FTM post-execute logic procedure if any. */
    if (FTM_GetPostExecuteLogic())
    {
        FTM_PostExecuteLogicProc proc = FTM_GetPostExecuteLogic();

        (*proc)();
    }

    /* kill the thread pools */
    if (engine::borderPool)
    {
        delete engine::borderPool;

        engine::borderPool = NULL;

        ThreadPool::WaitForDeletionComplete();
    }

    if (workItemPool)
    {
        delete workItemPool;

        workItemPool = NULL;

        ThreadPool::WaitForDeletionComplete();
    }

    if (engine::workerPool)
    {
        delete engine::workerPool;

        engine::workerPool = NULL;

        ThreadPool::WaitForDeletionComplete();
    }

    /* lose the app trace */
    if (engine::AppCriticalTrace)
    {
        delete engine::AppCriticalTrace;

        engine::AppCriticalTrace = NULL;
    }

    if (engine::AppErrorTrace)
    {
        delete engine::AppErrorTrace;

        engine::AppErrorTrace = NULL;
    }

    if (engine::AppWarningTrace)
    {
        delete engine::AppWarningTrace;

        engine::AppWarningTrace = NULL;
    }

    if (engine::AppDebugTrace)
    {
        delete engine::AppDebugTrace;

        engine::AppDebugTrace = NULL;
    }

    /* stop IntelliSS7 */
    ITS_GlobalStop();

    /* remove any feature records */
    for (list = ENGINE_APP_FEATURES(application);
         list != NULL;
         list = ENGINE_FEAT_NEXT(list))
    {
    }
    while (list != NULL)
    {
        ITS_RemFeature(ENGINE_FEAT_CLASS_REC(list));

        list = ENGINE_FEAT_PREV(list);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Driver app selector.
 *
 *  Input Parameters:
 *
 *  Return Value:
 *
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
DRIVER_AppSelector(ITS_HDR* hdr, ITS_EVENT* ev)
{
    ThreadPoolEntry thr;
    ITS_USHORT ret = ITS_NO_SRC;
    ENGINE_LibCache mainLib;
    const char *mainFunc;
    DISP_FuncsCPP *cbs;
    ::engine::Worker *worker;

    /* get a thread */
    if (engine::workerPool->GetFirstAvailThread(thr) != ITS_SUCCESS)
    {
        return (ret);
    }

    worker = reinterpret_cast<engine::Worker *>(thr.GetThread());

    /* get the callbacks for this thread */
    cbs = worker->GetCallbackStruct();

    /* see if we've cached the dispatch function yet. */
    if (cbs->dispAccept == NULL)
    {
        mainFunc = DISP_USER_CPP_STRING;

#if defined(DEBUG) || defined(_DEBUG)
        mainLib = ENGINE_LibGet(application,
                                DISPATCH_DEBUG_STRING);
#else
        mainLib = ENGINE_LibGet(application,
                                DISPATCH_STRING);
#endif
        ITS_C_ASSERT(mainLib != NULL);

        /* bind it. */
        cbs->dispAccept = (DISP_CPPDispatcher)
                            DLSYM_Resolve(ENGINE_LC_LIBRARY(mainLib),
                                          mainFunc);
    }

    /* make sure we can actually dispatch */
    if (cbs->dispAccept == NULL)
    {
        engine::workerPool->ReturnToAvailThreads(thr);

        return (ret);
    }

    /* add the context */
    if (ROUTE_AddApplication(worker->GetInstance(), hdr) != ITS_SUCCESS)
    {
        engine::workerPool->ReturnToAvailThreads(thr);

        return (ret);
    }

    /* send him off */
    if (engine::workerPool->DispatchOnThread(thr, cbs->dispAccept,
                                             cbs) != ITS_SUCCESS)
    {
        engine::workerPool->ReturnToAvailThreads(thr);

        return (ret);
    }

    ret = worker->GetInstance();

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Driver app selector.
 *
 *  Input Parameters:
 *
 *  Return Value:
 *
 ****************************************************************************/
ITSDLLAPI void
DRIVER_HandleHMI(ITS_POINTER object,
                 ITS_POINTER userData, ITS_POINTER callData)
{
    /* This is more for informational purposes than anything else */

    FTM_SignalTermination();
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Driver main.  This gets the ball rolling.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *
 *  Return Value:
 *      returns the value of SERVICE_GetExitCode().
 *
 ****************************************************************************/
extern "C" ITSDLLAPI int
DRIVER_Main(int argc, const char **argv)
{
    int ret;
    ENGINE_LibCache mainLib;

    ITS_C_REQUIRE(application != NULL);

    /* create the eventLog.  The specialization will be created later */
#if defined(WIN32)
    eventLog = new NtEventLog(ITS_StripPath(argv[0]));
    exceptionLog = new NtExceptionLog(ITS_StripPath(argv[0]));
#elif defined(unix)
    eventLog = new UnixEventLog(ITS_StripPath(argv[0]));
    exceptionLog = new UnixExceptionLog(ITS_StripPath(argv[0]));
#endif

    /* initialize the service info.  This is essentially temporary */
    service = new Service(APPL_GetName(), APPL_GetName(),
                          *exceptionLog,  *eventLog);

    /* set the vectors */
    SERVICE_SetInitFunction(PreFunc);

    /* Note: SERVICE_SetMainFunction is called by PreFunc. */

    SERVICE_SetTermFunction(PostFunc);

    /* go ahead and get the dispatchers to complete the namespace */
#if defined(DEBUG) || defined(_DEBUG)
    mainLib = ENGINE_LibGet(application,
                            DISPATCH_DEBUG_STRING);
#else
    mainLib = ENGINE_LibGet(application,
                            DISPATCH_STRING);
#endif
    ITS_C_ASSERT(mainLib != NULL);

    /* See how we're running */
    if (ENGINE_APP_IS_SERVICE(application))
    {
        /* let command line override */
        if (service->GetApplicationType() == Service::AT_CONSOLE_APPLICATION)
        {
            service->RunAsConsoleApplication(argc, argv);
        }
        else
        {
            service->RunAsService();
        }
    }
    else
    {
        /* let command line override */
        if (service->GetApplicationType() == Service::AT_SERVICE)
        {
            service->RunAsService();
        }
        else
        {
            service->RunAsConsoleApplication(argc, argv);
        }
    }

    ret = (service->GetExitCode());

    delete service;
    delete exceptionLog;
    delete eventLog;

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      diff the thread pools.  Compare trees and add/prune accordingly.
 *
 *  Input Parameters:
 *      oldApp - the old tree
 *      newApp - the new look
 *
 *  Return Value:
 *      Result of the diff
 *
 ****************************************************************************/
static void
UpdatePools(ENGINE_Application oldTree, ENGINE_Application newTree)
{
    ITS_Object list, list2, trans, trans2, items, items2;
    int i, ret, numTransports;

    /* compare worker pool first */
    for (list = ENGINE_APP_POOLS(newTree);
         list != NULL;
         list = ENGINE_TP_NEXT(list))
    {
        if (ENGINE_TP_TYPE(list) == TP_WORKERS)
        {
            break;
        }
    }

    for (list2 = ENGINE_APP_POOLS(oldTree);
         list2 != NULL;
         list2 = ENGINE_TP_NEXT(list2))
    {
        if (ENGINE_TP_TYPE(list2) == TP_WORKERS)
        {
            break;
        }
    }

    /* should have both pointers.  Compare them */
    if (list && list2)
    {
        /* find which are new, which are old.  Delete old, add new */
        /*
         * here we create workers, whether they be specific (e.g.,
         * protocol engines) or generic (e.g., simple workers).
         */
        ITS_C_ASSERT(engine::workerPool != NULL);

        /* new transports */
        for (trans = ENGINE_TP_TRANSPORTS(list);
             trans != NULL;
             trans = ENGINE_TR_NEXT(trans))
        {
            for (trans2 = ENGINE_TP_TRANSPORTS(list2);
                 trans2 != NULL;
                 trans2 = ENGINE_TR_NEXT(trans))
            {
                if (ITS_Equals(trans, trans2))
                {
                    break;
                }
            }

            /* not found?  New transport */
            if (trans2 == NULL)
            {
                /* cache a pointer to the list we're working */
                transports = trans;

                /* set resources */
                 numTransports = 1;

                if (ENGINE_TR_NUM_ASSOCIATES(trans))
                {
                    numTransports += ENGINE_TR_NUM_ASSOCIATES(trans) - 1;
                }

                for (i = 0; i < numTransports; i++)
                {
                    /* this relies on ITS_NO_SRC being an alias for zero */
                    if (ENGINE_TR_INST(trans) == ITS_NO_SRC)
                    {
                        currentInstance = lastWorker;
                        lastWorker++;
                        ENGINE_TR_INST(trans) = currentInstance;
                    }

                    ProcessOneTransport(transports, list);

                    ret = engine::workerPool->AddThread(ENGINE_TP_STACK_SIZE(list));

                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                }
            }
        }

        /* dead transports */
        for (trans2 = ENGINE_TP_TRANSPORTS(list2);
             trans2 != NULL;
             trans2 = ENGINE_TR_NEXT(trans2))
        {
            for (trans = ENGINE_TP_TRANSPORTS(list);
                 trans != NULL;
                 trans = ENGINE_TR_NEXT(trans))
            {
                if (ITS_Equals(trans, trans2))
                {
                    break;
                }
            }

            /* deader? */
            if (trans == NULL)
            {
                ThreadPoolThread *ew;

                ret = engine::workerPool->FindThread(&ew, trans);

                if (ret == ITS_SUCCESS && ew)
                {
                    engine::Worker *worker = (engine::Worker *)ew;

                    worker->SetExit(true);
                }
            }
        }
    }
    else if (list2)
    {
        /* no workers in new config.  Delete them all */
        delete engine::workerPool;
        engine::workerPool = NULL;
    }

    /* compare workitem pool next */
    for (list = ENGINE_APP_POOLS(newTree);
         list != NULL;
         list = ENGINE_TP_NEXT(list))
    {
        if (ENGINE_TP_TYPE(list) == TP_WORK_ITEMS)
        {
            break;
        }
    }

    for (list2 = ENGINE_APP_POOLS(oldTree);
         list2 != NULL;
         list2 = ENGINE_TP_NEXT(list2))
    {
        if (ENGINE_TP_TYPE(list2) == TP_WORK_ITEMS)
        {
            break;
        }
    }

    /* should have both pointers.  Compare the work items */
    if (list && list2)
    {
        /* create the pool */
        transports = ENGINE_TP_TRANSPORTS(list);
        trans2 = ENGINE_TP_TRANSPORTS(list2);
        ITS_C_ASSERT(transports != NULL);

        if (workItemPool == NULL)
        {
            workItemPool = new WorkItemPool(ENGINE_TR_INST(transports),
                                            ENGINE_TR_NUM_ASSOCIATES(transports),
                                            ENGINE_TP_STACK_SIZE(list));
            ITS_C_ASSERT(workItemPool != NULL);
        }

        /* add the work items */
        for (items = ENGINE_TR_WORK_ITEMS(transports);
             items != NULL;
             items = ENGINE_WI_NEXT(items))
        {
            for (items2 = ENGINE_TR_WORK_ITEMS(trans2);
                 items2 != NULL;
                 items2 = ENGINE_WI_NEXT(items2))
            {
                if (ITS_Equals(items, items2))
                {
                    break;
                }

                /* new item? */
                if (items2 == NULL)
                {
                    ENGINE_LibCache wiLib;
                    WORKITEM_ItemFunc wiFunc;
                    int i, ret;

                    /* resolve the delegate */
                    wiLib = ENGINE_LibGet(application,
                                          ENGINE_WI_LIB_NAME(items));
                    ITS_C_ASSERT(wiLib != NULL);

                    wiFunc = (WORKITEM_ItemFunc)
                                DLSYM_Resolve(ENGINE_LC_LIBRARY(wiLib),
                                              ENGINE_WI_DELEGATE(items));

                    if (wiFunc == NULL &&
                        (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                         SERVICE_GetType() == ST_NOT_SET))
                    {
                        printf("Error resolving symbol %s : %s\n",
                               ENGINE_WI_DELEGATE(items), DLSYM_Error());
                        fflush(stdout);
                    }

                    ITS_C_ASSERT(wiFunc != NULL);

                    /* add the items */
                    for (i = 0; i < ENGINE_WI_REPEAT(items); i++)
                    {
                        WORKITEM_Instance *item;

                        item = WORKITEM_Create(sizeof(WORKITEM_Instance),
                                               ENGINE_WI_PERSIST(items),
                                               wiFunc);
                        ITS_C_ASSERT(item != NULL);

                        ret = WORKITEM_PutWorkItem(ENGINE_TR_INST(transports), item);
                        ITS_C_ASSERT(ret == ITS_SUCCESS);
                    }
                }
            }
        }
    }
    else if (list2)
    {
        /* no workers in new config.  Delete them all */
        if (workItemPool)
        {
            delete workItemPool;
            workItemPool = NULL;
        }
    }
    
    /* finally compare border pool next */
    for (list = ENGINE_APP_POOLS(newTree);
         list != NULL;
         list = ENGINE_TP_NEXT(list))
    {
        if (ENGINE_TP_TYPE(list) == TP_BORDERS)
        {
            break;
        }
    }

    for (list2 = ENGINE_APP_POOLS(oldTree);
         list2 != NULL;
         list2 = ENGINE_TP_NEXT(list2))
    {
        if (ENGINE_TP_TYPE(list2) == TP_BORDERS)
        {
            break;
        }
    }

    /* should have both pointers.  Compare them */
    if (list && list2)
    {
        /* find which are new, which are old.  Delete old, add new */
        /*
         * here we create workers, whether they be specific (e.g.,
         * protocol engines) or generic (e.g., simple workers).
         */
        ITS_C_ASSERT(engine::workerPool != NULL);

        /* new transports */
        for (trans = ENGINE_TP_TRANSPORTS(list);
             trans != NULL;
             trans = ENGINE_TR_NEXT(trans))
        {
            for (trans2 = ENGINE_TP_TRANSPORTS(list2);
                 trans2 != NULL;
                 trans2 = ENGINE_TR_NEXT(trans))
            {
                if (ITS_Equals(trans, trans2))
                {
                    break;
                }
            }

            /* not found?  New transport */
            if (trans2 == NULL)
            {
                /* cache a pointer to the list we're working */
                transports = trans;

                /* set resources */
                 numTransports = 1;

                if (ENGINE_TR_NUM_ASSOCIATES(trans))
                {
                    numTransports += ENGINE_TR_NUM_ASSOCIATES(trans) - 1;
                }

                for (i = 0; i < numTransports; i++)
                {
                    /* this relies on ITS_NO_SRC being an alias for zero */
                    if (ENGINE_TR_INST(trans) == ITS_NO_SRC)
                    {
                        currentInstance = lastWorker;
                        lastWorker++;
                        ENGINE_TR_INST(trans) = currentInstance;
                    }

                    ProcessOneTransport(transports, list);

                    ret = engine::borderPool->AddThread(ENGINE_TP_STACK_SIZE(list));

                    DispatchBorder(trans);

                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                }
            }
        }

        /* dead transports */
        for (trans2 = ENGINE_TP_TRANSPORTS(list2);
             trans2 != NULL;
             trans2 = ENGINE_TR_NEXT(trans2))
        {
            for (trans = ENGINE_TP_TRANSPORTS(list);
                 trans != NULL;
                 trans = ENGINE_TR_NEXT(trans))
            {
                if (ITS_Equals(trans, trans2))
                {
                    break;
                }
            }

            /* deader? */
            if (trans == NULL)
            {
                ThreadPoolThread *ew;

                ret = engine::borderPool->FindThread(&ew, trans);

                if (ret == ITS_SUCCESS && ew)
                {
                    engine::Worker *worker = (engine::Worker *)ew;

                    worker->SetExit(true);
                }
            }
        }
    }
    else if (list2)
    {
        /* no workers in new config.  Delete them all */
        delete engine::borderPool;
        engine::borderPool = NULL;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Driver diff.  Compare trees and add/prune accordingly.
 *
 *  Input Parameters:
 *      oldApp - the old tree
 *      newApp - the new look
 *
 *  Return Value:
 *      Result of the diff
 *
 ****************************************************************************/
extern "C" ITSDLLAPI int
DRIVER_Diff(ENGINE_Application oldTree,
            ENGINE_Application newTree)
{
    /*
     * walk the two trees, modifying the application to suit.
     *
     * What do we want to accomplish:
     * Add borders (no remove?)
     * Change callbacks (what if they're being called?)
     * Add workitems (no remove?)
     * Add workers (grow pools?)
     * Change features? (yes - this is hot upgrade).
     * Change libraries? (same)
     * Force failover.
     * what else?
     *
     * for now, only
     *  remove non-matching workers
     *  add new workers
     *  add new work items
     *  remove non-matching borders
     *  add new borders
     *  add features
     *  update trace
     */

    try
    {
        /* add any new feature records */
        AddNewFeatures(newTree);

        /* set SUPPORT trace */
        SetSupportTrace(newTree);

        /* update the pools */
        UpdatePools(oldTree, newTree);
    }
    catch (GenericException& ge)
    {
        ge.Log();
    }
    catch (exception& ex)
    {
        StandardException se(ex.what());

        se.Log();
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a transport to the border pool.
 *
 *  Input Parameters:
 *      dbc - the debug console
 *      tr - the ENGINE_Transport to be added
 *
 *  Return Value:
 *      success or failure
 *
 ****************************************************************************/
static int
AddBorder(DBC_Server *dbc, ITS_Object tr, ITS_Object pool)
{
    int ret;

    if (application == NULL)
    {
        DBC_AppendText(dbc, "Application is not configured\n");

        return (ITS_EINVALIDARGS);
    }

    if (engine::borderPool == NULL)
    {
        DBC_AppendText(dbc, "Border pool is not configured\n");

        return (ITS_EINVALIDARGS);
    }

    transports = tr;
    ENGINE_TR_NEXT(tr) = NULL;

    /* no threads for virtuals */
    if (ENGINE_TR_SPECIFICS(tr) &&
        !(ENGINE_TS_MASK(ENGINE_TR_SPECIFICS(tr)) & ITS_TRANSPORT_DGRAM_VIRT))
    {
        ret = engine::borderPool->AddThread(ENGINE_TP_STACK_SIZE(pool));

        if (ret != ITS_SUCCESS)
        {
            transports = NULL;

            DBC_AppendText(dbc, "Unable to create transport\n");

            return (ret);
        }

        DispatchBorder(tr);
    }

    /* add the transport to the application list */
    ENGINE_TR_NEXT(tr) = ENGINE_TP_TRANSPORTS(pool);
    ENGINE_TP_TRANSPORTS(pool) = tr;

    transports = NULL;

    DBC_AppendText(dbc, "Border transport added\n");

    return (ITS_SUCCESS);
}
