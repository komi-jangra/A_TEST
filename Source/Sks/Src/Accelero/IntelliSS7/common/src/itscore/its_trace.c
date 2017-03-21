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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.15  2005/03/21 13:51:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1.10.2  2005/01/05 13:35:02  craghavendra
 * LOG: Updates for Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.2.10.1.10.1  2005/01/05 07:21:25  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2.10.1  2004/07/12 10:42:23  mmanikandan
 * LOG: traceFlushAfterWrite logic is modified.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/03/28 00:05:06  mmiers
 * LOG: Performance optimizations.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 16:31:41  lbana
 * LOG: do string comparison fro stdout instead of pointer(stdout pointer is
 * LOG: is not constant for each task in vxworks)
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.12  2001/04/02 21:21:51  mmiers
 * LOG: Align strings with parser.
 * LOG:
 * LOG: Revision 3.11  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.10  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.9  2001/02/28 23:07:32  mmiers
 * LOG: No more need for CORE and CORE++, only CORE now.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.4  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.3  2001/01/16 15:20:21  mmiers
 * LOG: Defines for an OS without a filesystem
 * LOG:
 * LOG: Revision 3.2  2000/12/04 21:11:39  hdivoux
 * LOG: Added function to expose turn on/off flush after write at the API level.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:06  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.14  2000/08/10 00:04:56  mmiers
 * LOG: SCTP update.  Almost there.
 * LOG:
 * LOG: Revision 2.13  2000/07/12 15:25:48  mmiers
 * LOG:
 * LOG: Some cleanups and performance enhancements.
 * LOG:
 * LOG: Revision 2.12  2000/07/07 17:05:08  mmiers
 * LOG:
 * LOG:
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 2.11  2000/06/26 15:28:17  mmiers
 * LOG:
 * LOG:
 * LOG: Use reentrant version of localtime.
 * LOG:
 * LOG: Revision 2.10  2000/03/28 22:23:18  mmiers
 * LOG:
 * LOG:
 * LOG: Fix Nick's bug report.
 * LOG:
 * LOG: Revision 2.9  2000/03/28 15:59:24  npopov
 * LOG: Introduced conditional compilation macro NO_TIME_STAMP for regression testing
 * LOG:
 * LOG: Revision 2.8  2000/03/23 20:21:31  mmiers
 * LOG:
 * LOG:
 * LOG: Final IntelliSS7 changes from Plano.
 * LOG:
 * LOG: Revision 2.7  2000/03/18 21:03:50  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.6  2000/02/15 20:34:44  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.5  2000/02/14 19:17:39  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.4  2000/02/14 17:52:51  mmiers
 * LOG:
 * LOG: Integrate TRACE and RESFILE into CORE.  Change RESFILE so that it
 * LOG: sets levels on/off from control strings in the globals segment of the
 * LOG: trace file.  Always include the TRACE and RESFILE classes.
 * LOG:
 * LOG: Revision 2.3  2000/02/12 00:08:42  mmiers
 * LOG:
 * LOG: Move RESFILE to core library.  Convert RESFILE and TRACE to OO footing.
 * LOG:
 * LOG: Revision 2.2  2000/02/01 23:41:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 2.1  2000/01/27 00:02:16  mmiers
 * LOG:
 * LOG:
 * LOG: Make core lib smarter
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:19  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.48  1999/10/12 18:34:46  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with non-zero code.
 * LOG:
 * LOG: Revision 1.47  1999/08/23 01:56:13  mmiers
 * LOG:
 * LOG:
 * LOG: Fix for Solaris build.
 * LOG:
 * LOG: Revision 1.46  1999/08/16 15:42:59  mmiers
 * LOG:
 * LOG:
 * LOG: Check trace state before tracing.
 * LOG:
 * LOG: Revision 1.45  1999/08/11 23:06:01  mmiers
 * LOG:
 * LOG:
 * LOG: Generate trace header using C method.
 * LOG:
 * LOG: Revision 1.44  1999/08/11 17:31:02  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.43  1999/08/11 14:09:31  mmiers
 * LOG:
 * LOG:
 * LOG: Fix compilation warnings.
 * LOG:
 * LOG: Revision 1.42  1999/08/11 02:35:32  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.41  1999/07/13 19:41:23  fhasle
 * LOG:
 * LOG: When not able to create a trace file: when printing the file name, replace (NULL)
 * LOG: by buf string.
 * LOG:
 * LOG: Revision 1.40  1999/07/13 16:09:38  mmiers
 * LOG:
 * LOG:
 * LOG: Use the correct variable for file name.
 * LOG:
 * LOG: Revision 1.39  1999/07/13 15:30:33  mmiers
 * LOG:
 * LOG:
 * LOG: Open the right file name.
 * LOG:
 * LOG: Revision 1.38  1999/07/13 14:48:19  mmiers
 * LOG:
 * LOG:
 * LOG: Group the environment variables in its.h.  Add environment variable for
 * LOG: trace files (default to cwd).  Remove dbc_command from dbc workspace.
 * LOG:
 * LOG: Revision 1.37  1999/07/02 00:02:26  labuser
 * LOG:
 * LOG: fhasle: added functions to check if a trace is enabled.
 * LOG:
 * LOG: Revision 1.36  1999/06/30 22:58:42  mmiers
 * LOG:
 * LOG:
 * LOG: Make more signatures const for warning avoidance
 * LOG:
 * LOG: Revision 1.35  1999/06/24 00:59:14  mmiers
 * LOG:
 * LOG:
 * LOG: Add an IPC type semaphore
 * LOG:
 * LOG: Revision 1.34  1999/03/24 22:45:28  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.33  1999/03/12 00:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.32  1999/02/25 22:57:13  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.31  1999/01/18 20:38:00  mmiers
 * LOG: Add rollover to both C and C++ bindings; add seconds to C++ binding.
 * LOG:
 * LOG: Revision 1.30  1998/11/19 00:36:31  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.29  1998/11/12 00:09:16  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.28  1998/11/10 15:43:08  mmiers
 * LOG: Merge the C and C++ mutexes so that trace has one global mutex.
 * LOG:
 * LOG: Revision 1.27  1998/09/30 20:33:30  jrao
 * LOG: Fix a number of release bugs with pthread_cond_t(s).
 * LOG:
 * LOG: Revision 1.26  1998/09/30 19:09:13  jrao
 * LOG: Mutex implementations MUST NOT include trace, or recursion problems
 * LOG: will result.
 * LOG:
 * LOG: Revision 1.25  1998/09/28 19:59:06  mmiers
 * LOG: Watch the termination conditions.
 * LOG:
 * LOG: Revision 1.24  1998/09/25 23:20:33  mmiers
 * LOG: Add init flag so that output methods can be shared.
 * LOG:
 * LOG: Revision 1.23  1998/09/25 21:37:21  mmiers
 * LOG: Flush output.
 * LOG:
 * LOG: Revision 1.22  1998/09/25 21:34:59  mmiers
 * LOG: Fix file tracing.
 * LOG:
 * LOG: Revision 1.21  1998/09/25 21:03:12  mmiers
 * LOG: More fixes for MTP3.
 * LOG:
 * LOG: Revision 1.20  1998/09/23 23:41:14  mmiers
 * LOG: Tracing is almost complete.  Just need to add event trace.
 * LOG:
 * LOG: Revision 1.19  1998/09/22 18:52:47  mmiers
 * LOG: Turn debugging trace off by default.
 * LOG:
 * LOG: Revision 1.18  1998/09/21 22:52:34  mmiers
 * LOG: Start adding C-trace to infrastructure.
 * LOG:
 * LOG: Revision 1.17  1998/09/21 18:31:18  mmiers
 * LOG: Get C-trace hooked up and working.
 * LOG:
 * LOG: Revision 1.16  1998/09/18 23:42:32  mmiers
 * LOG: Forgot about the output method.
 * LOG:
 * LOG: Revision 1.15  1998/09/18 23:10:11  mmiers
 * LOG: Add remaining methods.
 * LOG:
 * LOG: Revision 1.14  1998/09/18 22:31:15  mmiers
 * LOG: Remove dead tempory.  Make trace enable/disable per output as well.
 * LOG:
 * LOG: Revision 1.13  1998/09/18 22:15:57  mmiers
 * LOG: Use pointers, not structs.  Convert routing class to static methods.
 * LOG:
 * LOG: Revision 1.12  1998/09/18 22:04:05  mmiers
 * LOG: Rework C trace for vendor code.
 * LOG:
 * LOG: Revision 1.11  1998/06/20 03:50:42  mmiers
 * LOG: Add Linux as a target.
 * LOG:
 * LOG: Revision 1.10  1998/06/16 00:00:28  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.9  1998/06/02 17:24:48  mmiers
 * LOG: Cleanup for the doc tool.
 * LOG:
 * LOG: Revision 1.8  1998/06/01 16:35:38  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.7  1998/05/31 22:20:16  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.6  1998/05/20 04:44:09  mmiers
 * LOG: Cleanup.
 * LOG: Hubert, some iterators need to be constant while others don't.  Please
 * LOG: see me about this.
 * LOG:
 * LOG: Revision 1.5  1998/04/28 22:52:41  mmiers
 * LOG: Rework trace slightly to have a more general semantic.  You are no
 * LOG: longer limited to one trace facility per program.
 * LOG:
 * LOG: Revision 1.4  1998/04/27 20:00:28  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 01:47:20  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.2  1998/04/08 20:26:55  mmiers
 * LOG: Work on tracing...
 * LOG:
 * LOG: Revision 1.1  1998/04/08 03:23:47  mmiers
 * LOG: Trace and sockets APIs.
 * LOG:
 * LOG: Revision 1.2  1998/01/30 23:07:29  ssharma
 * LOG: *** empty log message ***
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>             /* For variable arg stuff */ 
#include <stdlib.h> 

#if defined(unix)
#include <unistd.h>
#include <syslog.h>
#if !defined(linux)
#include <libgen.h>
#endif
#endif

#if defined(WIN32)
#include <direct.h>
#include <windows.h>
#endif

#include <its.h>
#include <its_trace.h>
#include <its_timers.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <its_assertion.h>

#ident "$Id: its_trace.c,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

/*
 * application global variables.
 */
ITSDLLAPI ITS_MUTEX    TRACE_Mutex;
ITSDLLAPI TRACE_Data*  TRACE_Current = NULL;
ITSDLLAPI ITS_BOOLEAN  TRACE_GlobalEnable = ITS_TRUE;

#if defined(vxworks)
#undef  stdout
#define stdout  stdioFp(1)
#endif

/*
 * consts
 */
#define TIME_STRING_SIZE       80

#if defined (unix)
#define ITS_SYSLOG_FACILITY    LOG_LOCAL6
#endif


static TRACE_OutputInitializer fileCritTrace =
{
    ITS_FILE_STRING,
    ITS_TRUE,
#if !defined(TANDEM)
    ".its-traceCritical",
#else
    "GCRIT",
#endif
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    ITS_FILE_STRING,
    ITS_TRUE,
#if !defined(TANDEM)
    ".its-traceError",
#else
    "GCRIT",
#endif
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    ITS_FILE_STRING,
    ITS_TRUE,
#if !defined(TANDEM)
    ".its-traceWarn",
#else
    "GWARN",
#endif
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    ITS_FILE_STRING,
    ITS_TRUE,
#if !defined(TANDEM)
    ".its-traceDebug",
#else
    "GDEBUG",
#endif
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    ITS_FILE_STRING,
    ITS_TRUE,
#if !defined(TANDEM)
    ".its-traceEvent",
#else
    "GEVENT",
#endif
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    ITS_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    ITS_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer ITS_TraceMap[] =
{
    {ITS_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {ITS_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {ITS_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {ITS_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {ITS_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

ITSDLLAPI TRACE_Data* ITS_InternalTrace = NULL;

static RESFILE_Manager *globalRes = NULL;
static int              traceFlushAfterWrite=0;

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_EnableTrace
 *
 *  Purpose:
 *      This function will enable C based tracing for the entire
 *      application.
 *
 *  Input Parameters:
 *      None.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_EnableTrace()
{
    TRACE_GlobalEnable = ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_DisableTrace
 *
 *  Purpose:
 *      This function will disable C based tracing for the entire
 *      application.
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
 *  Notes:
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_DisableTrace()
{
    TRACE_GlobalEnable = ITS_FALSE;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_TurnFlushAfterWriteOnOff
 *
 *  Purpose:
 *      Enable/disable flush after write for tracing in the support library.
 *
 *  Input Parameters:
 *      onOff   - enable/disable flush after write.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_TurnFlushAfterWriteOnOff(ITS_BOOLEAN onOff)
{
    if (onOff)
    {
        traceFlushAfterWrite = 1;
    }
    else
    {
        traceFlushAfterWrite = 0;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_TurnCriticalTraceOnOff
 *
 *  Purpose:
 *      This function will enable/disable critical trace in the support library.
 *
 *  Input Parameters:
 *      onOff   - set the enabled/disabled state of critical trace.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      This must be called BEFORE calling ITS_GlobalStart/ITS_Initialize()
 *      to effectively trace the infrastructure.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_TurnCriticalTraceOnOff(ITS_BOOLEAN onOff)
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                  ITS_CRITICAL_STRING,
                                  onOff);
    }
    else
    {
        ITS_TraceMap[ITS_TRACE_LEVEL_CRITICAL].isEnabled = onOff;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_TurnErrorTraceOnOff
 *
 *  Purpose:
 *      This function will enable/disable error trace in the support library.
 *
 *  Input Parameters:
 *      onOff   - set the enabled/disabled state of error trace.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      This must be called BEFORE calling ITS_GlobalStart/ITS_Initialize()
 *      to effectively trace the infrastructure.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_TurnErrorTraceOnOff(ITS_BOOLEAN onOff)
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                  ITS_ERROR_STRING,
                                  onOff);
    }
    else
    {
        ITS_TraceMap[ITS_TRACE_LEVEL_ERROR].isEnabled = onOff;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_TurnWarningTraceOnOff
 *
 *  Purpose:
 *      This function will enable/disable warning trace in the support library.
 *
 *  Input Parameters:
 *      onOff   - set the enabled/disabled state of warning trace.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      This must be called BEFORE calling ITS_GlobalStart/ITS_Initialize()
 *      to effectively trace the infrastructure.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_TurnWarningTraceOnOff(ITS_BOOLEAN onOff)
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                  ITS_WARNING_STRING,
                                  onOff);
    }
    else
    {
        ITS_TraceMap[ITS_TRACE_LEVEL_WARNING].isEnabled = onOff;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_TurnDebugTraceOnOff
 *
 *  Purpose:
 *      This function will enable/disable debug trace in the support library.
 *
 *  Input Parameters:
 *      onOff   - set the enabled/disabled state of debug trace.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      This must be called BEFORE calling ITS_GlobalStart/ITS_Initialize()
 *      to effectively trace the infrastructure.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_TurnDebugTraceOnOff(ITS_BOOLEAN onOff)
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                  ITS_DEBUG_STRING,
                                  onOff);
    }
    else
    {
        ITS_TraceMap[ITS_TRACE_LEVEL_DEBUG].isEnabled = onOff;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_TurnEventTraceOnOff
 *
 *  Purpose:
 *      This function will enable/disable event trace in the support library.
 *
 *  Input Parameters:
 *      onOff   - set the enabled/disabled state of debug trace.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      This must be called BEFORE calling ITS_GlobalStart/ITS_Initialize()
 *      to effectively trace the infrastructure.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_TurnEventTraceOnOff(ITS_BOOLEAN onOff)
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                  ITS_EVENT_STRING,
                                  onOff);
    }
    else
    {
        ITS_TraceMap[ITS_TRACE_LEVEL_EVENT].isEnabled = onOff;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_CriticalTraceOn
 *
 *  Purpose:
 *      This function will tell if the trace is enabled.
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
 *  Notes:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if the trace is enabled. ITS_FALSE otherwise.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_CriticalTraceOn()
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        return TRACE_IsLevelOn(ITS_InternalTrace, ITS_TRACE_LEVEL_CRITICAL);
    }
    else
    {
        return TRACE_LEVEL_IS_ENABLED(
                    &ITS_TraceMap[ITS_TRACE_LEVEL_CRITICAL]);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_ErrorTraceOn
 *
 *  Purpose:
 *      This function will tell if the trace is enabled.
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
 *  Notes:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if the trace is enabled. ITS_FALSE otherwise.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_ErrorTraceOn()
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        return TRACE_IsLevelOn(ITS_InternalTrace, ITS_TRACE_LEVEL_ERROR);
    }
    else
    {
        return TRACE_LEVEL_IS_ENABLED(&ITS_TraceMap[ITS_TRACE_LEVEL_ERROR]);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_WarningTraceOn
 *
 *  Purpose:
 *      This function will tell if the trace is enabled.
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
 *  Notes:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if the trace is enabled. ITS_FALSE otherwise.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_WarningTraceOn()
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        return TRACE_IsLevelOn(ITS_InternalTrace, ITS_TRACE_LEVEL_WARNING);
    }
    else
    {
        return TRACE_LEVEL_IS_ENABLED(
                    &ITS_TraceMap[ITS_TRACE_LEVEL_WARNING]);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_DebugTraceOn
 *
 *  Purpose:
 *      This function will tell if the trace is enabled.
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
 *  Notes:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if the trace is enabled. ITS_FALSE otherwise.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_DebugTraceOn()
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        return TRACE_IsLevelOn(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG);
    }
    else
    {
        return TRACE_LEVEL_IS_ENABLED(&ITS_TraceMap[ITS_TRACE_LEVEL_DEBUG]);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_EventTraceOn
 *
 *  Purpose:
 *      This function will tell if the trace is enabled.
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
 *  Notes:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if the trace is enabled. ITS_FALSE otherwise..
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_EventTraceOn()
{
    if (ITS_CLASS_INITTED(itsTRACE_Class))
    {
        return TRACE_IsLevelOn(ITS_InternalTrace, ITS_TRACE_LEVEL_EVENT);
    }
    else
    {
        return TRACE_LEVEL_IS_ENABLED(&ITS_TraceMap[ITS_TRACE_LEVEL_EVENT]);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_IsInitialized
 *
 *  Purpose:
 *      This function will indicate the state of infrastructure trace
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
 *  Notes:
 *
 *  Return Value:
 *      ITS_TRUE - trace running
 *      ITS_FALSE - trace not running
 ****************************************************************************/
#undef TRACE_IsInitialized
ITSDLLAPI ITS_BOOLEAN
TRACE_IsInitialized()
{
    return ITS_CLASS_INITTED(itsTRACE_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_UpdateSettings
 *
 *  Purpose:
 *      This function will update the trace settings with information
 *      taken from the resource database.
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
 ****************************************************************************/
ITSDLLAPI void
TRACE_UpdateSettings()
{
    char value[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    globalRes = RESFILE_CreateResourceManager(name);

    if (globalRes == NULL)
    {
        return;
    }

    name = NULL;

    /* critical */
    if (RESFILE_GetKeyValueOf(globalRes, name, ITS_TRACE_CRITICAL_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(value, ITS_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_CRITICAL_STRING,
                                       ITS_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_CRITICAL_STRING,
                                       ITS_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_CRITICAL_STRING,
                                       ITS_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_CRITICAL_STRING,
                                       ITS_SYSLOG_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_CRITICAL_STRING,
                                       ITS_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_CRITICAL_STRING,
                                       ITS_FILE_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_CRITICAL_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_CRITICAL_STRING, ITS_FALSE);
        }
    }

    /* error */
    if (RESFILE_GetKeyValueOf(globalRes, name, ITS_TRACE_ERROR_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(value, ITS_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_ERROR_STRING,
                                       ITS_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_ERROR_STRING,
                                       ITS_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_ERROR_STRING,
                                       ITS_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_ERROR_STRING,
                                       ITS_SYSLOG_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_ERROR_STRING,
                                       ITS_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_ERROR_STRING,
                                       ITS_FILE_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_ERROR_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_ERROR_STRING, ITS_FALSE);
        }
    }

    /* warning */
    if (RESFILE_GetKeyValueOf(globalRes, name, ITS_TRACE_WARNING_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(value, ITS_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_WARNING_STRING,
                                       ITS_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_WARNING_STRING,
                                       ITS_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_WARNING_STRING,
                                       ITS_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_WARNING_STRING,
                                       ITS_SYSLOG_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_WARNING_STRING,
                                       ITS_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_WARNING_STRING,
                                       ITS_FILE_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_WARNING_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_WARNING_STRING, ITS_FALSE);
        }
    }

    /* debug */
    if (RESFILE_GetKeyValueOf(globalRes, name, ITS_TRACE_DEBUG_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(value, ITS_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_SYSLOG_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_FILE_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_DEBUG_STRING, ITS_FALSE);
        }
    }

    /* event */
    if (RESFILE_GetKeyValueOf(globalRes, name, ITS_TRACE_EVENT_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(value, ITS_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_EVENT_STRING,
                                       ITS_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_EVENT_STRING,
                                       ITS_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_DEBUG_STRING,
                                       ITS_SYSLOG_STRING, ITS_FALSE);
        }
        if (strstr(value, ITS_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_EVENT_STRING,
                                       ITS_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ITS_InternalTrace,
                                       ITS_EVENT_STRING,
                                       ITS_FILE_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ITS_InternalTrace,
                                      ITS_EVENT_STRING, ITS_FALSE);
        }
    }

    /* flushAfterWrite */
    if (RESFILE_GetKeyValueOf(globalRes, name, TRACE_FLUSH_AFTER_WRITE_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        traceFlushAfterWrite = strstr(value, "on") != NULL ||
                               strstr(value, "ON") != NULL ||
                               strstr(value, "yes") != NULL ||
                               strstr(value, "YES") != NULL;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      TRACE_Init
 *
 *  Purpose:
 *      This function will initialize the infrastructure tracing.
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
 *  Notes:
 *
 *  Return Value:
 *      ITS_SUCCES  - successful start.
 *      anything else - error starting
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    /*
     * create the serialization mutexes
     */
    if (MUTEX_CreateMutex(&TRACE_Mutex, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if ((ITS_InternalTrace =
            TRACE_Constructor("ITS-Support", ITS_TraceMap,
                              sizeof(ITS_TraceMap) /
                              sizeof(TRACE_LevelInitializer))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      TRACE_Delete
 *
 *  Purpose:
 *      This function will terminate infrastructure tracing.
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
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    TRACE_Destructor(ITS_InternalTrace);
    ITS_InternalTrace = NULL;

    MUTEX_DeleteMutex(&TRACE_Mutex);

    if (globalRes)
    {
        /* this is ordinarily illegal.  However, I know how it works. */
        free(globalRes);
    }
}

/*.implementation:static
 *****************************************************************************
 *  Name:
 *      TRACE_Constructor
 *
 *  Purpose:
 *      This function initializes the tracing facility.
 *
 *  Input Parameters:
 *      subsystem -     Set this to whatever you want the subsystem id to be. 
 *      levelMap -      The user defined trace level map.
 *      levelMapCount - The number of entries in the level map.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the initialized trace subsystem.
 ****************************************************************************/
static int
Constructor(ITS_Object obj, va_list args)
{ 
    TRACE_Data *td = (TRACE_Data *)obj;
    char *subsystem;
    TRACE_LevelInitializer *levelMap;
    int levelMapCount;
    int i;

    subsystem = va_arg(args, char *);
    levelMap = va_arg(args, TRACE_LevelInitializer *);
    levelMapCount = va_arg(args, int);

    if (subsystem == NULL)
    {
        subsystem = "Default";
    }

    strncpy(TRACE_DATA_UNIT_NAME(td), subsystem, ITS_PATH_MAX); 

    for (i = 0; i < levelMapCount; i++)
    {
        TRACE_DATA_LEVEL_MAP(td)[i] =
            (TRACE_Level *)ITS_ConstructObject(itsTRACE_LevelClass,
                                               &levelMap[i]);
    }

    TRACE_DATA_NUM_LEVELS(td) = levelMapCount;

    return (ITS_SUCCESS);
}         

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      Destructor
 *
 *  Purpose:
 *      This function should be called in the shutdown portion of the 
 *      application program. 
 *
 *      NOTE: Right now this is not required, as a normally exiting 
 *            function will close all open files, however things may be 
 *            added here in the future.
 *
 *  Input Parameters:
 *      td - the trace subsystem to terminate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void 
Destructor(ITS_Object obj)
{
    TRACE_Data* td = (TRACE_Data *)obj;
    int i;

    if (!td)
    {
        return;
    }

    /* delete all levels */
    for (i = 0; i < TRACE_DATA_NUM_LEVELS(td); i++)
    {
        ITS_DestructObject((ITS_Object)TRACE_DATA_LEVEL_MAP(td)[i]);
    }
}  

ITSDLLAPI TRACE_ClassRec itsTRACE_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(TRACE_Data),             /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_CLASS_NAME,               /* class name */
        ClassInitialize,                /* class init */
        ClassDestroy,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        Constructor,                    /* instance create */
        Destructor,                     /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsTRACE_Class = (ITS_Class)&itsTRACE_ClassRec;

/*.implementation:extern
 *****************************************************************************
 *  Name:
 *      LevelConstructor
 *
 *  Purpose:
 *      This function initializes a trace level
 *
 *  Input Parameters:
 *      levelMap -      The user defined trace level map.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the initialized trace subsystem.
 ****************************************************************************/
static int
LevelConstructor(ITS_Object obj, va_list args)
{ 
    TRACE_Level *tl = (TRACE_Level *)obj;
    TRACE_LevelInitializer *levelMap;
    int i;

    ITS_C_REQUIRE(tl != NULL);

    levelMap = va_arg(args, TRACE_LevelInitializer *);

    if (levelMap == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    TRACE_LEVEL_NAME(tl) = strdup(levelMap->levelName);
    TRACE_LEVEL_IS_ENABLED(tl) = levelMap->isEnabled;
    TRACE_LEVEL_NUM_OUTPUTS(tl) = levelMap->numOutputs;

    /* duplicate the outputs */
    for (i = 0; i < levelMap->numOutputs; i++)
    {
        switch (levelMap->outputs[i]->flags)
        {
        case TRACE_TO_DISPLAY:
            TRACE_LEVEL_OUTPUTS(tl)[i] =
                (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputStdoutClass,
                                        levelMap->outputs[i]->name,
                                        levelMap->outputs[i]->isEnabled,
                                        levelMap->outputs[i]->data);
            break;

        case TRACE_TO_FILE:
            TRACE_LEVEL_OUTPUTS(tl)[i] =
                (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputFileClass,
                                        levelMap->outputs[i]->name,
                                        levelMap->outputs[i]->isEnabled,
                                        levelMap->outputs[i]->data);
            break;

#if defined(unix)
        case TRACE_TO_SYSLOG:
            TRACE_LEVEL_OUTPUTS(tl)[i] =
                (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputSyslogClass,
                                        levelMap->outputs[i]->name,
                                        levelMap->outputs[i]->isEnabled,
                                        levelMap->outputs[i]->data);
            break;
#endif

#if defined(WIN32)
        case TRACE_TO_NT_EVENT_LOG:
            TRACE_LEVEL_OUTPUTS(tl)[i] =
                (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputEventLogClass,
                                        levelMap->outputs[i]->name,
                                        levelMap->outputs[i]->isEnabled,
                                        levelMap->outputs[i]->data);
            break;
#endif

        case TRACE_TO_SNMP_MASK:
            /* FIXME */
            break;

        case TRACE_TO_NONE:
        default:
            break;
        }
    }

    return (ITS_SUCCESS);
}         

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_Destructor
 *
 *  Purpose:
 *      This function should be called in the shutdown portion of the 
 *      application program. 
 *
 *      NOTE: Right now this is not required, as a normally exiting 
 *            function will close all open files, however things may be 
 *            added here in the future.
 *
 *  Input Parameters:
 *      td - the trace subsystem to terminate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void 
LevelDestructor(ITS_Object obj)
{
    TRACE_Level* td = (TRACE_Level *)obj;
    int i;

    /* delete all outputs */
    for (i = 0; i < TRACE_LEVEL_NUM_OUTPUTS(td); i++)
    {
        ITS_DestructObject((ITS_Object)TRACE_LEVEL_OUTPUTS(td)[i]);
    }

    free(TRACE_LEVEL_NAME(td));
}  

ITSDLLAPI TRACE_ClassRec itsTRACE_LevelClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(TRACE_Level),            /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_LEVEL_CLASS_NAME,         /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        LevelConstructor,               /* instance create */
        LevelDestructor,                /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsTRACE_LevelClass =
    (ITS_Class)&itsTRACE_LevelClassRec;

/*.implementation:static
 *****************************************************************************
 *  Name:
 *      TRACE_Constructor
 *
 *  Purpose:
 *      This function initializes the tracing facility.
 *
 *  Input Parameters:
 *      subsystem -     Set this to whatever you want the subsystem id to be. 
 *      levelMap -      The user defined trace level map.
 *      levelMapCount - The number of entries in the level map.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the initialized trace subsystem.
 ****************************************************************************/
ITSDLLAPI TRACE_Data*
TRACE_Constructor(const char *subsystem,
                  TRACE_LevelInitializer* levelMap,
                  int numLevels)
{ 
    return (TRACE_Data *)ITS_ConstructObject(itsTRACE_Class,
                                             subsystem,
                                             levelMap,
                                             numLevels);
}         

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      Destructor
 *
 *  Purpose:
 *      This function should be called in the shutdown portion of the 
 *      application program. 
 *
 *      NOTE: Right now this is not required, as a normally exiting 
 *            function will close all open files, however things may be 
 *            added here in the future.
 *
 *  Input Parameters:
 *      td - the trace subsystem to terminate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_Destructor(TRACE_Data *td)
{
    ITS_C_REQUIRE(td != NULL);

    ITS_DestructObject((ITS_Object)td);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_SetLevelOnOff
 *
 *  Purpose:
 *      This function enables/disables trace for a given level.
 *
 *  Input Parameters:
 *      td - trace data to modify
 *      level - level to enable/disable
 *      onOff - ITS_TRUE = enable, ITS_FALSE = disable
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_SetLevelOnOff(TRACE_Data* td,
                    int level, 
                    ITS_BOOLEAN onOff)
{
    ITS_C_REQUIRE(td != NULL);

    if (level < 0 || level >= TRACE_DATA_NUM_LEVELS(td))
    {
        return;
    }

    TRACE_LEVEL_IS_ENABLED(TRACE_DATA_LEVEL_MAP(td)[level]) = onOff;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_SetLevelOnOffByName
 *
 *  Purpose:
 *      This function enables/disables trace for a given level.
 *
 *  Input Parameters:
 *      td - trace data to modify
 *      namel - the name of the level to enable/disable
 *      onOff - ITS_TRUE = enable, ITS_FALSE = disable
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_SetLevelOnOffByName(TRACE_Data* td,
                          const char* name, 
                          ITS_BOOLEAN onOff)
{
    int i;

    ITS_C_REQUIRE(td != NULL);
    ITS_C_REQUIRE(name != NULL);

    for (i = 0; i < TRACE_DATA_NUM_LEVELS(td); i++)
    {
        if (strcmp(name, TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(td)[i])) == 0)
        {
            TRACE_LEVEL_IS_ENABLED(TRACE_DATA_LEVEL_MAP(td)[i]) = onOff;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_IsLevelOn
 *
 *  Purpose:
 *      This function returns enabled status for a given level.
 *
 *  Input Parameters:
 *      td - trace data to modify
 *      level - the level to report on
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_IsLevelOn(TRACE_Data* td, int level)
{
    ITS_C_REQUIRE(td != NULL);

    if (level < 0 || level >= TRACE_DATA_NUM_LEVELS(td))
    {
        return (ITS_FALSE);
    }

    return (TRACE_LEVEL_IS_ENABLED(TRACE_DATA_LEVEL_MAP(td)[level]));
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_SetOutputOnOff
 *
 *  Purpose:
 *      This function enables/disables trace for a given output.
 *
 *  Input Parameters:
 *      td - trace data to modify
 *      level - level to enable/disable
 *      output - the output at this level to turn on/off
 *      onOff - ITS_TRUE = enable, ITS_FALSE = disable
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      Outputs can be shared between levels; beware of side-effects.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_SetOutputOnOff(TRACE_Data* td,
                     int level, int output,
                     ITS_BOOLEAN onOff)
{
    ITS_C_REQUIRE(td != NULL);

    if (level < 0 || level >= TRACE_DATA_NUM_LEVELS(td))
    {
        return;
    }

    if (output < 0 ||
        output >= TRACE_LEVEL_NUM_OUTPUTS(TRACE_DATA_LEVEL_MAP(td)[level]))
    {
        return;
    }

    TRACE_OUTPUT_IS_ENABLED(
        TRACE_LEVEL_OUTPUTS(TRACE_DATA_LEVEL_MAP(td)[level])[output]) = onOff;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_SetOutputOnOffByName
 *
 *  Purpose:
 *      This function enables/disables trace for a given output.
 *
 *  Input Parameters:
 *      td - trace data to modify
 *      levName - the name of the level where outputs are altered
 *      name - the name of the output at this level to turn on/off
 *      onOff - ITS_TRUE = enable, ITS_FALSE = disable
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      Outputs can be shared between levels; beware of side-effects.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
TRACE_SetOutputOnOffByName(TRACE_Data* td,
                           const char* levName, const char* name,
                           ITS_BOOLEAN onOff)
{
    int i, j;

    ITS_C_REQUIRE(td != NULL);
    ITS_C_REQUIRE(levName != NULL);
    ITS_C_REQUIRE(name != NULL);

    for (i = 0; i < TRACE_DATA_NUM_LEVELS(td); i++)
    {
        if (strcmp(levName,
                   TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(td)[i])) == 0)
        {
            for (j = 0;
                 j < TRACE_LEVEL_NUM_OUTPUTS(TRACE_DATA_LEVEL_MAP(td)[i]);
                 j++)
            {
                if (strcmp(TRACE_OUTPUT_NAME(
                            TRACE_LEVEL_OUTPUTS(TRACE_DATA_LEVEL_MAP(td)[i])[j]),
                           name) == 0)
                {
                    TRACE_OUTPUT_IS_ENABLED(
                        TRACE_LEVEL_OUTPUTS(
                        TRACE_DATA_LEVEL_MAP(td)[i])[j]) = onOff;
                }
            }
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_IsOutputOn
 *
 *  Purpose:
 *      This function enables/disables trace for a given output.
 *
 *  Input Parameters:
 *      td - trace data to modify
 *      level - level to enable/disable
 *      output - the output at this level to turn on/off
 *      onOff - ITS_TRUE = enable, ITS_FALSE = disable
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      Outputs can be shared between levels; beware of side-effects.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
TRACE_IsOutputOn(TRACE_Data* td,
                 int level, int output)
{
    ITS_C_REQUIRE(td != NULL);

    if (level < 0 || level >= TRACE_DATA_NUM_LEVELS(td))
    {
        return (ITS_FALSE);
    }

    if (output < 0 ||
        output >= TRACE_LEVEL_NUM_OUTPUTS(TRACE_DATA_LEVEL_MAP(td)[level]))
    {
        return (ITS_FALSE);
    }

    return (TRACE_OUTPUT_IS_ENABLED(
              TRACE_LEVEL_OUTPUTS(TRACE_DATA_LEVEL_MAP(td)[level])[output]));
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_AddOutput
 *
 *  Purpose:
 *      This function will add the trace output to the trace level.
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
 ****************************************************************************/
ITSDLLAPI int
TRACE_AddOutput(TRACE_Level* data, TRACE_OutputMethod* output)
{
    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(output != NULL);

    if (TRACE_LEVEL_NUM_OUTPUTS(data) >= MAX_TRACE_LEVEL_OUTPUTS)
    {
        return (ITS_EOVERFLOW);
    }

    TRACE_LEVEL_OUTPUTS(data)[TRACE_LEVEL_NUM_OUTPUTS(data)] = output;

    TRACE_LEVEL_NUM_OUTPUTS(data)++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_RemOutput
 *
 *  Purpose:
 *      This function will remove the trace output from the trace level.
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
 ****************************************************************************/
ITSDLLAPI int
TRACE_RemOutput(TRACE_Level* data, char* output)
{
    int i;

    ITS_C_REQUIRE(data != NULL);

    if (output == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    for (i = 0; i < TRACE_LEVEL_NUM_OUTPUTS(data); i++)
    {
        if (TRACE_LEVEL_OUTPUTS(data)[i] &&
            TRACE_OUTPUT_NAME(TRACE_LEVEL_OUTPUTS(data)[i]) &&
            output &&
            strcmp(TRACE_OUTPUT_NAME(TRACE_LEVEL_OUTPUTS(data)[i]),
                   output) == 0)
        {
            if (i == TRACE_LEVEL_NUM_OUTPUTS(data) - 1)
            {
                TRACE_LEVEL_NUM_OUTPUTS(data)--;

                return (ITS_SUCCESS);
            }
            else
            {
                memcpy(&TRACE_LEVEL_OUTPUTS(data)[i],
                       &TRACE_LEVEL_OUTPUTS(data)[i+1],
                       (TRACE_LEVEL_NUM_OUTPUTS(data) - i - 1) *
                            sizeof(TRACE_OutputMethod *));

                TRACE_LEVEL_NUM_OUTPUTS(data)--;

                return (ITS_SUCCESS);
            }
        }
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_AddLevel
 *
 *  Purpose:
 *      This function will add the trace level to the trace subsystem.
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
 ****************************************************************************/
ITSDLLAPI int
TRACE_AddLevel(TRACE_Data* data, TRACE_Level* level)
{
    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(level != NULL);

    if (TRACE_DATA_NUM_LEVELS(data) >= MAX_TRACE_LEVELS)
    {
        return (ITS_EOVERFLOW);
    }

    TRACE_DATA_LEVEL_MAP(data)[TRACE_DATA_NUM_LEVELS(data)] = level;
    TRACE_LEVEL_LEVEL_NUM(level) = TRACE_DATA_NUM_LEVELS(data);

    TRACE_DATA_NUM_LEVELS(data)++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_AddLevel
 *
 *  Purpose:
 *      This function will add the trace level to the trace subsystem.
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
 ****************************************************************************/
ITSDLLAPI int
TRACE_RemLevel(TRACE_Data* data, char* level)
{
    int i, j;

    ITS_C_REQUIRE(data != NULL);

    if (level == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    for (i = 0; i < TRACE_DATA_NUM_LEVELS(data); i++)
    {
        if (TRACE_DATA_LEVEL_MAP(data)[i] &&
            TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(data)[i]) &&
            level &&
            strcmp(TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(data)[i]),
                   level) == 0)
        {
            if (i == TRACE_DATA_NUM_LEVELS(data) - 1)
            {
                TRACE_DATA_NUM_LEVELS(data)--;

                return (ITS_SUCCESS);
            }
            else
            {
                memcpy(&TRACE_DATA_LEVEL_MAP(data)[i],
                       &TRACE_DATA_LEVEL_MAP(data)[i+1],
                       (TRACE_DATA_NUM_LEVELS(data) - i - 1) *
                            sizeof(TRACE_Level *));

                TRACE_DATA_NUM_LEVELS(data)--;

                for (j = i; j < TRACE_DATA_NUM_LEVELS(data); j++)
                {
                    TRACE_LEVEL_LEVEL_NUM(TRACE_DATA_LEVEL_MAP(data)[i])--;
                }

                return (ITS_SUCCESS);
            }
        }
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_FindLevel
 *
 *  Purpose:
 *      This function will find the trace level in the trace subsystem.
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
 ****************************************************************************/
ITSDLLAPI TRACE_Level *
TRACE_FindLevel(TRACE_Data* data, char *name)
{
    int i;

    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(name != NULL);

    for (i = 0; i < TRACE_DATA_NUM_LEVELS(data); i++)
    {
        if (TRACE_DATA_LEVEL_MAP(data)[i] &&
            TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(data)[i]) &&
            name &&
            strcmp(TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(data)[i]),
                   name) == 0)
        {
            return TRACE_DATA_LEVEL_MAP(data)[i];
        }
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_Output
 *
 *  Purpose:
 *      This function formats a message and writes it via the output method
 *      on the current level.
 *      The message is built using the variable arguments and the format 
 *      string passed in. 
 *      Additional information put in the message include the current 
 *      timestamp, the name of the source file and line number from which 
 *      the function is being called. 
 *
 *  Input:
 *      fmtString           formats(1) style text formatting string 
 *      ...                 Variable arguments follow  
 *
 *  Input/Output:
 *      None.
 *
 *  Output:
 *      None.
 *
 *  Returns:
 *      None.
 ****************************************************************************/
ITSDLLAPI void 
TRACE_Output(const char *fmtString, ...)
{
    va_list argp;                 /* Used for variable argument stuff */ 
    TRACE_OutputMethod* tmp;
    TRACE_Level*     curLevel;
    int i;

    ITS_C_REQUIRE(fmtString != NULL);

    /*
     * Note that the application is responsible for calling the constructor,
     * before invoking a trace function.
     */
    if (!TRACE_Current)
    {
        return;
    }
   
    /*
     * Start the variable-argument magic 
     */
    va_start(argp, fmtString); 

    /*
     * output it.
     */
    curLevel =
        TRACE_DATA_LEVEL_MAP(TRACE_Current)
            [TRACE_DATA_CURRENT_LEVEL(TRACE_Current)];

    for (i = 0; i < TRACE_LEVEL_NUM_OUTPUTS(curLevel); i++)
    {
        tmp = TRACE_LEVEL_OUTPUTS(curLevel)[i];
        if (TRACE_OUTPUT_IS_ENABLED(tmp))
        {
            TRACE_OUTPUT_CLASS_OUTPUT(ITS_OBJ_CLASS(tmp))(tmp,
                                                          fmtString,
                                                          argp);
        }
    }

    /*
     * Done with the magic stuff 
     */
    va_end(argp); 
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_Header
 *
 *  Purpose:
 *      This function will return the header to be added for each trace 
 *      message.
 *
 *  Input Parameters:
 *      levelPtr  -  pointer to the severity level mapping.
 *      fileName  - name of the source file calling the trace macro.
 *      lineNum  -  line number of the call.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Notes:
 *      This function is mutex guarded.
 *
 *  Return Value:
 *      the trace header.
 ****************************************************************************/
ITSDLLAPI char *
TRACE_Header(TRACE_Data* td,
             const char *fileName, int lineNum)
{
    /* dangerous, but the mutex should be held before entering this */
    static char outString[TRACE_MAX_MSG_SIZE];
    char tempOutString[TRACE_MAX_MSG_SIZE];
    char * levelName, *tmp;
#ifndef NO_TIME_STAMP
    time_t now;                   /* Current time */
    struct tm *now_time
#if !defined(WIN32) && !defined(TANDEM)
        , tbuf
#endif
        ;
    char temptime[TIME_STRING_SIZE]; 

    ITS_C_REQUIRE(td != NULL);
    ITS_C_REQUIRE(fileName != NULL);

    /*
     * Set up the timestamp string  
     */
    time(&now);

#if defined(WIN32) || defined(TANDEM)
    now_time = localtime(&now);

    strftime(temptime, TIME_STRING_SIZE, "[%b%d %Y %H:%M:%S]: ", now_time);     
                                  /* [MMMDD YY, HH:MM:SS\0]  */
#else
    now_time = localtime_r(&now, &tbuf);

    strftime(temptime, TIME_STRING_SIZE, "[%b%d %Y %H:%M:%S]: ", &tbuf);     
                                  /* [MMMDD YY, HH:MM:SS\0]  */
#endif
    
    /*
     * Timestamp 
     */
    sprintf(outString, "%s", temptime);
#else
    outString[0] = 0;
#endif /* !NO_TIME_STAMP */

    /*
     * Include the program name, fileName, linenumber info 
     */
    sprintf(tempOutString, "%-10.11s: ", TRACE_DATA_UNIT_NAME(td)); 
    strcat(outString, tempOutString);


    levelName =
        TRACE_LEVEL_NAME(TRACE_DATA_LEVEL_MAP(td)
                            [TRACE_DATA_CURRENT_LEVEL(td)]);
    if (levelName == NULL)
    {
        sprintf(tempOutString, "%-10.10s: ", "UNKNOWN");
    }
    else
    {
        sprintf(tempOutString, "%-10.10s: ", levelName);
    }
    strcat(outString, tempOutString);
      
    
    if ((tmp = strrchr(fileName, '/')) == NULL)
    {
        tmp = strrchr(fileName, '\\');
        if (tmp)
        {
            tmp++;
        }
    }
    else
    {
        tmp++;
    }

    if (!tmp)
    {
        tmp = (char *)fileName;
    }

    sprintf(tempOutString, "%-20.20s: ", tmp); 
    strcat(outString, tempOutString);

    sprintf(tempOutString, "line %-d\n", lineNum); 
    strcat(outString, tempOutString);

    return outString;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_AcquireMutex
 *
 *  Purpose:
 *      This function acquires the trace global mutex.  If trace has not
 *      been started, it will be started here.
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
 ****************************************************************************/
ITSDLLAPI int
TRACE_AcquireMutex()
{
    int ret;

    if (!ITS_CLASS_INITTED(itsTRACE_Class))
    {
        if ((ret = ITS_InitializeClass(itsTRACE_Class)) != ITS_SUCCESS)
        {
            return (ret);
        }
    }

    return MUTEX_AcquireMutex(&TRACE_Mutex);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      TRACE_ReleaseMutex
 *
 *  Purpose:
 *      This function releases the trace global mutex.
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
 ****************************************************************************/
ITSDLLAPI int
TRACE_ReleaseMutex()
{
    return MUTEX_ReleaseMutex(&TRACE_Mutex);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the trace subsystem.
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
 *      ITS_SUCCESS
 *
 *  Notes:
 *
 ****************************************************************************/
static int
OutputClassPartInitialize(ITS_Class objClass)
{
    if (TRACE_OUTPUT_CLASS_OUTPUT(objClass) == TRACE_OUTPUT_INHERIT_OUTPUT)
    {
        TRACE_OUTPUT_CLASS_OUTPUT(objClass) =
            TRACE_OUTPUT_CLASS_OUTPUT(ITS_CLASS_SUPERCLASS(objClass));
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      a constant pointer to the application name
 *
 *  Notes:
 *
 ****************************************************************************/
static void
OutputClassPartDestroy(ITS_Class objClass)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      a constant pointer to the application name
 *
 *  Notes:
 *
 ****************************************************************************/
static void
OutputError(TRACE_OutputMethodPtr method,
            const char *format,
            va_list args)
{
    fprintf(stderr, "Use of abstract base class or child class invalid\n");
}

ITSDLLAPI TRACE_OutputClassRec itsTRACE_OutputClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(TRACE_OutputMethod),     /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_OUTPUT_CLASS_NAME,        /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        OutputClassPartInitialize,      /* class part init */
        OutputClassPartDestroy,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* output part */
    {
        OutputError
    }
};

ITSDLLAPI ITS_Class itsTRACE_OutputClass = (ITS_Class)&itsTRACE_OutputClassRec;

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      OpenFile
 *
 *  Purpose:
 *      This function will open the appropriate trace file.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
CollideOpenFile(ITS_Object obj, va_list args)
{
    TRACE_OutputMethod *tom = (TRACE_OutputMethod *)obj;
    char buf[ITS_PATH_MAX];

    TRACE_OUTPUT_NAME(tom) = va_arg(args, char *);
    TRACE_OUTPUT_IS_ENABLED(tom) = va_arg(args, ITS_BOOLEAN);
    TRACE_OUTPUT_OUT_NAME(tom) = va_arg(args, void *);

    TRACE_OUTPUT_INIT_DONE(tom) = ITS_FALSE;
    TRACE_OUTPUT_DATA(tom) = NULL;

    TRACE_OUTPUT_START(tom) = time(NULL);
    TRACE_OUTPUT_CUR_DAY(tom) = TRACE_OUTPUT_START(tom) / ITS_SECS_PER_DAY;

    if (APPL_GetTraceDir() != NULL)
    {
        sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
                APPL_GetTraceDir(), TRACE_OUTPUT_OUT_NAME(tom),
                TRACE_OUTPUT_CUR_DAY(tom) % ITS_NUM_TRACE_FILES);
    }
    else
    {
        sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
                "", TRACE_OUTPUT_OUT_NAME(tom),
                TRACE_OUTPUT_CUR_DAY(tom) % ITS_NUM_TRACE_FILES);
    }

    TRACE_OUTPUT_OUT_NAME(tom) = strdup(TRACE_OUTPUT_OUT_NAME(tom));

    return (ITS_SUCCESS);
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      CloseFile
 *
 *  Purpose:
 *      This function will close the appropriate trace file.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
CollideCloseFile(ITS_Object obj)
{
    TRACE_OutputMethod *tom = (TRACE_OutputMethod *)obj;

    if (TRACE_OUTPUT_INIT_DONE(tom) &&
        TRACE_OUTPUT_IS_ENABLED(tom))
    {
        if (TRACE_OUTPUT_DATA(tom))
        {
#if !defined(NO_FILESYSTEM)
            fclose((FILE *)TRACE_OUTPUT_DATA(tom));
#endif
        }
    }

    free(TRACE_OUTPUT_OUT_NAME(tom));
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      OpenStdout
 *
 *  Purpose:
 *      This function will set the trace data to stdout.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
OpenStdout(ITS_Object obj, va_list args)
{ 
    TRACE_OutputMethod *tom = (TRACE_OutputMethod *)obj;

    TRACE_OUTPUT_NAME(tom) = va_arg(args, char *);
    TRACE_OUTPUT_IS_ENABLED(tom) = va_arg(args, ITS_BOOLEAN);
    TRACE_OUTPUT_DATA(tom) = va_arg(args, void *);

    TRACE_OUTPUT_INIT_DONE(tom) = ITS_TRUE;

    TRACE_OUTPUT_OUT_NAME(tom) = NULL;

    TRACE_OUTPUT_DATA(tom) = stdout;

    return (ITS_SUCCESS);
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      CloseStdout
 *
 *  Purpose:
 *      This function will terminate trace to stdout.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
CloseStdout(ITS_Object obj)
{ 
    TRACE_OutputMethod *tom = (TRACE_OutputMethod *)obj;

    TRACE_OUTPUT_DATA(tom) = NULL;
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      OutputFile
 *
 *  Purpose:
 *      This function will output to the appropriate trace file.
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
 ****************************************************************************/
static void
OutputFile(TRACE_OutputMethod *tom, const char *format, va_list args) 
{ 
    char buf[ITS_PATH_MAX];
    ITS_TIME day;

    if (TRACE_OUTPUT_IS_ENABLED(tom))
    {
        TRACE_OUTPUT_REC_COUNT(tom)++;

#if !defined(NO_FILESYSTEM)
        /* check to see if we need open */
        if (!TRACE_OUTPUT_INIT_DONE(tom) ||
            TRACE_OUTPUT_DATA(tom) == NULL)
        {
            TRACE_OUTPUT_INIT_DONE(tom) = ITS_TRUE;

            day = (time(NULL) - TRACE_OUTPUT_START(tom)) / ITS_SECS_PER_DAY;

            TRACE_OUTPUT_REC_COUNT(tom) = 0;
            TRACE_OUTPUT_CUR_DAY(tom) = day;

            if (APPL_GetTraceDir() != NULL)
            {
                sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
                        APPL_GetTraceDir(), TRACE_OUTPUT_OUT_NAME(tom),
                        day % ITS_NUM_TRACE_FILES);
            }
            else
            {
                sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
                        "", TRACE_OUTPUT_OUT_NAME(tom),
                        day % ITS_NUM_TRACE_FILES);
            }

            TRACE_OUTPUT_DATA(tom) = fopen(buf, "w");
        }
        /* check to see if we roll over */
        else if (strcmp(TRACE_OUTPUT_NAME(tom), "stdout") != 0)
        {
            day = (time(NULL) - TRACE_OUTPUT_START(tom)) / ITS_SECS_PER_DAY;

            /* note that this code means it is possible to roll over
             * the same day. */
            if (day > TRACE_OUTPUT_CUR_DAY(tom) ||
                TRACE_OUTPUT_REC_COUNT(tom) > ITS_TRACE_PER_FILE_MAX)
            {
                if (TRACE_OUTPUT_DATA(tom) != NULL)
                {
                    fclose(TRACE_OUTPUT_DATA(tom));
                }

                TRACE_OUTPUT_REC_COUNT(tom) = 0;
                TRACE_OUTPUT_CUR_DAY(tom) = day;

                if (APPL_GetTraceDir() != NULL)
                {
                    sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
                            APPL_GetTraceDir(), TRACE_OUTPUT_OUT_NAME(tom),
                            day % ITS_NUM_TRACE_FILES);
                }
                else
                {
                    sprintf(buf, ITS_TRACE_FILE_NAME_FORMAT_STRING,
                            "", (char *)TRACE_OUTPUT_OUT_NAME(tom),
                            day % ITS_NUM_TRACE_FILES);
                }

                TRACE_OUTPUT_DATA(tom) = fopen(buf, "w");
            }
        }
#endif

        /* don't barf if the file open failed */
        if (TRACE_OUTPUT_DATA(tom))
        {
            vfprintf((FILE *)TRACE_OUTPUT_DATA(tom), format, args);
            if (traceFlushAfterWrite)
            {
                fflush((FILE *)TRACE_OUTPUT_DATA(tom));
            }
        }
    }
    else if ((strcmp(TRACE_OUTPUT_NAME(tom), "stdout") != 0) &&
             TRACE_OUTPUT_DATA(tom) != NULL)
    {
#if !defined(NO_FILESYSTEM)
        fclose((FILE *)TRACE_OUTPUT_DATA(tom));
#endif

        TRACE_OUTPUT_DATA(tom) = NULL;
    }
}  

/*
 * file class records
 */
ITSDLLAPI TRACE_OutputClassRec itsTRACE_OutputFileClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsTRACE_OutputClassRec,
                                        /* Trace output is superclass */
        sizeof(TRACE_OutputMethod),     /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_OUTPUT_FILE_CLASS_NAME,   /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CollideOpenFile,                /* instance create */
        CollideCloseFile,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* output part */
    {
        OutputFile
    }
};

ITSDLLAPI ITS_Class itsTRACE_OutputFileClass =
    (ITS_Class)&itsTRACE_OutputFileClassRec;

ITSDLLAPI TRACE_OutputClassRec itsTRACE_OutputStdoutClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsTRACE_OutputClassRec,
                                        /* Trace output file is superclass */
        sizeof(TRACE_OutputMethod),     /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_OUTPUT_STDOUT_CLASS_NAME, /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        OpenStdout,                     /* instance create */
        CloseStdout,                    /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* output part */
    {
        OutputFile
    }
};

ITSDLLAPI ITS_Class itsTRACE_OutputStdoutClass =
    (ITS_Class)&itsTRACE_OutputStdoutClassRec;

#if defined(unix)
/*.implementation:static
 ****************************************************************************
 *  Name:
 *      OpenSyslog
 *
 *  Purpose:
 *      This function will open a channel to the system logger.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
OpenSyslog(ITS_Object obj, va_list args) 
{ 
    TRACE_OutputMethod *tom = (TRACE_OutputMethod *)obj;
 
    const char *name = APPL_GetName();

    TRACE_OUTPUT_NAME(tom) = va_arg(args, char *);
    TRACE_OUTPUT_IS_ENABLED(tom) = va_arg(args, ITS_BOOLEAN);
    TRACE_OUTPUT_DATA(tom) = va_arg(args, void *);

    if (name)
    {
        openlog(name, LOG_NDELAY | LOG_PID, ITS_SYSLOG_FACILITY);
    }
    else
    {
        openlog(TRACE_OUTPUT_NAME(tom), LOG_NDELAY | LOG_PID, ITS_SYSLOG_FACILITY);
    }

    TRACE_OUTPUT_INIT_DONE(tom) = ITS_TRUE;
    TRACE_OUTPUT_OUT_NAME(tom) = NULL;

    return (ITS_SUCCESS);
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      CloseSyslog
 *
 *  Purpose:
 *      This function will terminate trace to the system log.
 *
 *  Input Parameters:
 *      tom - the output method to modify on close
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
CloseSyslog(ITS_Object obj) 
{
    closelog();
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      OutputSyslog
 *
 *  Purpose:
 *      This function will output to the system logger.
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
 ****************************************************************************/
static void
OutputSyslog(TRACE_OutputMethod *tom, const char *format, va_list args) 
{
    char buf[TRACE_MAX_MSG_SIZE];

    TRACE_Level* curLevel = NULL;
    char levelName[ITS_PATH_MAX];

    vsprintf(buf, format, args);

    if (TRACE_Current != NULL)
    {
        curLevel =
            TRACE_DATA_LEVEL_MAP(TRACE_Current)
                [TRACE_DATA_CURRENT_LEVEL(TRACE_Current)];
        strcpy(levelName, TRACE_LEVEL_NAME(curLevel));
    }
    else
    {
        syslog(LOG_DEBUG, buf);
        return;
    }

    if (strcmp(levelName, ITS_CRITICAL_STRING) == 0)
    {
        syslog(LOG_CRIT, buf);
    }
    else if (strcmp(levelName, ITS_ERROR_STRING) == 0)
    {
        syslog(LOG_ERR, buf);
    }
    else if (strcmp(levelName, ITS_WARNING_STRING) == 0)
    {
        syslog(LOG_WARNING, buf);
    }
    else if (strcmp(levelName, ITS_DEBUG_STRING) == 0)
    {
        syslog(LOG_DEBUG, buf);
    }
}  

/*
 * syslog class records
 */
ITSDLLAPI TRACE_OutputClassRec itsTRACE_OutputSyslogClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsTRACE_OutputClassRec,
                                        /* Trace output is superclass */
        sizeof(TRACE_OutputMethod),     /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_OUTPUT_SYSLOG_CLASS_NAME, /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        OpenSyslog,                     /* instance create */
        CloseSyslog,                    /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* output part */
    {
        OutputSyslog
    }
};

ITSDLLAPI ITS_Class itsTRACE_OutputSyslogClass =
    (ITS_Class)&itsTRACE_OutputSyslogClassRec;

#endif

#if defined(WIN32)
/*.implementation:static
 ****************************************************************************
 *  Name:
 *      OpenEventLog
 *
 *  Purpose:
 *      This function will open a channel to the NT event log.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
CollideOpenEventLog(ITS_Object obj, va_list args) 
{ 
    TRACE_OutputMethod *tom = (TRACE_OutputMethod *)obj;

    TRACE_OUTPUT_NAME(tom) = va_arg(args, char *);
    TRACE_OUTPUT_IS_ENABLED(tom) = va_arg(args, ITS_BOOLEAN);
    TRACE_OUTPUT_DATA(tom) = va_arg(args, void *);

    TRACE_OUTPUT_INIT_DONE(tom) = ITS_TRUE;

    return (ITS_SUCCESS);
}  

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      CloseEventLog
 *
 *  Purpose:
 *      This function will terminate the channel to the NT event log.
 *
 *  Input Parameters:
 *      tom - the output method to modify on open
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
CollideCloseEventLog(ITS_Object obj) 
{
}  

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      OutputFile
 *
 *  Purpose:
 *      This function will output to the NT event log.
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
 ****************************************************************************/
static void
CollideOutputEventLog(TRACE_OutputMethod *tom,
               const char *format, va_list args) 
{
    char buf[ITS_PATH_MAX];

    vsprintf(buf, format, args);
}  

/*
 * EventLog class records
 */
ITSDLLAPI TRACE_OutputClassRec itsTRACE_OutputEventLogClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsTRACE_OutputClassRec,
                                        /* Trace output is superclass */
        sizeof(TRACE_OutputMethod),     /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TRACE_OUTPUT_EVENTLOG_CLASS_NAME,/* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CollideOpenEventLog,            /* instance create */
        CollideCloseEventLog,           /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* output part */
    {
        CollideOutputEventLog
    }
};

ITSDLLAPI ITS_Class itsTRACE_OutputEventLogClass =
    (ITS_Class)&itsTRACE_OutputEventLogClassRec;

#endif
