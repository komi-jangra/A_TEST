/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * LOG: Revision 9.1.8.2  2006/02/23 06:31:26  sjaddu
 * LOG: Making trace compatable to mvlppc.
 * LOG:
 * LOG: Revision 9.1.8.1  2005/11/24 06:10:06  yranade
 * LOG: Increase Max Trace Levels to 48.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.24.2  2005/02/21 04:21:17  dsatish
 * LOG: Added SetSubSystemName .
 * LOG:
 * LOG: Revision 7.2.24.1  2005/01/05 07:21:23  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/03/28 01:51:55  mmiers
 * LOG: Enable/disable tracing with C++ as well.
 * LOG:
 * LOG: Revision 6.2  2002/03/28 00:04:34  mmiers
 * LOG: Performance optimizations and DSM table renaming.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/09/19 23:31:40  whu
 * LOG: Added namespace prefix to type names in body of ITS_TRACE.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/16 00:03:42  mmiers
 * LOG: Various fixes from PR4.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.18  2001/04/02 21:21:41  mmiers
 * LOG: Align strings with parser.
 * LOG:
 * LOG: Revision 3.17  2001/03/28 22:38:29  mmiers
 * LOG: It is coded.
 * LOG:
 * LOG: Revision 3.16  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.15  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.14  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.13  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.12  2001/03/06 22:19:30  mmiers
 * LOG: Cross-platform cleanup.
 * LOG:
 * LOG: Revision 3.11  2001/03/06 22:01:23  mmiers
 * LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
 * LOG:
 * LOG: Revision 3.10  2001/03/01 01:22:51  mmiers
 * LOG: Add trace config obj.
 * LOG:
 * LOG: Revision 3.9  2001/02/28 23:07:32  mmiers
 * LOG: No more need for CORE and CORE++, only CORE now.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.5  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.4  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.3  2000/12/04 21:11:54  hdivoux
 * LOG: Added function to expose turn on/off flush after write at the API level.
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/10/18 01:11:36  mmiers
 * LOG: More debugging.  Slow start is still broken.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.11  2000/07/13 22:50:40  mmiers
 * LOG: Smarten the trace macros a bit.
 * LOG:
 * LOG: Revision 2.10  2000/07/12 15:25:47  mmiers
 * LOG:
 * LOG: Some cleanups and performance enhancements.
 * LOG:
 * LOG: Revision 2.9  2000/06/13 19:15:55  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.8  2000/06/12 20:53:58  rsonak
 * LOG:
 * LOG: 2 fixes made
 * LOG: 1) Trace Level now being enabled
 * LOG: 2) Trace-output not throwing exception anymore
 * LOG:
 * LOG: Revision 2.7  2000/03/18 21:03:33  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.6  2000/02/14 19:17:37  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.5  2000/02/14 17:52:50  mmiers
 * LOG:
 * LOG: Integrate TRACE and RESFILE into CORE.  Change RESFILE so that it
 * LOG: sets levels on/off from control strings in the globals segment of the
 * LOG: trace file.  Always include the TRACE and RESFILE classes.
 * LOG:
 * LOG: Revision 2.4  2000/02/12 00:24:00  mmiers
 * LOG:
 * LOG: Make sure the C++ still builds.
 * LOG:
 * LOG: Revision 2.3  2000/02/12 00:07:14  mmiers
 * LOG:
 * LOG: Move RESFILE to core library.  Convert to complete OO footing.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 16:14:23  mmiers
 * LOG:
 * LOG:
 * LOG: Update test with new stack mechanism.
 * LOG:
 * LOG: Revision 2.1  2000/02/01 23:41:49  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:48  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.57  1999/11/06 00:20:15  rsonak
 * LOG:
 * LOG:
 * LOG: Add accessor method for the output struct.  Nastiness in scoping
 * LOG: rules for friends and protected members.
 * LOG:
 * LOG: Revision 1.56  1999/11/03 16:35:23  labuser
 * LOG:
 * LOG:
 * LOG: Convert from char * to const char *
 * LOG:
 * LOG: Revision 1.55  1999/11/02 17:11:15  mmiers
 * LOG:
 * LOG:
 * LOG: Change scoping in C++, add new mask bit for SNMP tracing.
 * LOG:
 * LOG: Revision 1.54  1999/10/12 18:36:10  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with non-zero code.
 * LOG:
 * LOG: Revision 1.53  1999/08/16 15:42:58  mmiers
 * LOG:
 * LOG:
 * LOG: Check trace state before tracing.
 * LOG:
 * LOG: Revision 1.52  1999/08/12 18:30:57  rsonak
 * LOG:
 * LOG: Get rid of the warnings
 * LOG:
 * LOG: Revision 1.51  1999/08/11 23:06:01  mmiers
 * LOG:
 * LOG:
 * LOG: Generate trace header using C method.
 * LOG:
 * LOG: Revision 1.50  1999/08/11 22:23:55  mmiers
 * LOG:
 * LOG:
 * LOG: Make C++ trace automatically put newlines out.
 * LOG:
 * LOG: Revision 1.49  1999/08/11 17:30:57  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.48  1999/07/13 16:12:41  fhasle
 * LOG:
 * LOG: updated ITS_TRACE_PER_FILE_MAX to 10 000 (was 100 000).
 * LOG:
 * LOG: Revision 1.47  1999/07/02 17:27:23  labuser
 * LOG:
 * LOG:
 * LOG: Allow trace to be completely turned off for command line setting.
 * LOG:
 * LOG: Revision 1.46  1999/07/01 23:59:25  labuser
 * LOG:
 * LOG: fhasle: added function to check if a trace is enabled.
 * LOG:
 * LOG: Revision 1.45  1999/06/30 22:59:10  mmiers
 * LOG:
 * LOG:
 * LOG: Make signatures const for warning avoidance.
 * LOG:
 * LOG: Revision 1.44  1999/06/30 22:52:59  mmiers
 * LOG:
 * LOG:
 * LOG: Make some more routines const for warning avoidance.
 * LOG:
 * LOG: Revision 1.43  1999/06/30 19:22:02  mmiers
 * LOG:
 * LOG:
 * LOG: Modified for portability.
 * LOG:
 * LOG: Revision 1.42  1999/06/29 23:39:24  mmiers
 * LOG:
 * LOG:
 * LOG: More portability fixes.
 * LOG:
 * LOG: Revision 1.41  1999/06/28 23:45:23  skarmakar
 * LOG:
 * LOG:
 * LOG: More work on portability.
 * LOG:
 * LOG: Revision 1.40  1999/06/28 23:19:02  skarmakar
 * LOG:
 * LOG:
 * LOG: Many many portability fixes.
 * LOG:
 * LOG: Revision 1.39  1999/05/13 22:27:34  labuser
 * LOG:
 * LOG:
 * LOG: Change tracing defines so that they can be compile-time disabled.
 * LOG:
 * LOG: Revision 1.38  1999/03/12 00:06:10  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.37  1999/01/18 20:37:59  mmiers
 * LOG: Add rollover to both C and C++ bindings; add seconds to C++ binding.
 * LOG:
 * LOG: Revision 1.36  1998/12/16 16:35:06  rsonak
 * LOG: Bug fixes for trace, crash detection in sccp, remove extra console
 * LOG: print in DBC.
 * LOG:
 * LOG: Revision 1.35  1998/11/19 00:36:21  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.34  1998/11/10 15:43:07  mmiers
 * LOG: Merge the C and C++ mutexes so that trace has one global mutex.
 * LOG:
 * LOG: Revision 1.33  1998/10/29 17:31:08  whu
 * LOG: Fix compilation bugs.
 * LOG:
 * LOG: Revision 1.32  1998/10/29 17:24:21  whu
 * LOG: Catch exceptions while tracing.
 * LOG:
 * LOG: Revision 1.31  1998/10/21 16:47:42  mmiers
 * LOG: Fix missing line numbers.
 * LOG:
 * LOG: Revision 1.30  1998/10/14 22:36:55  mmiers
 * LOG: Fix C++ trace.
 * LOG:
 * LOG: Revision 1.29  1998/10/14 22:17:47  rsonak
 * LOG: ITS_TRACE macro now takes 2 arguments
 * LOG:
 * LOG: Revision 1.28  1998/10/01 02:33:05  mmiers
 * LOG: Add idiocy for OSF1 varargs.
 * LOG:
 * LOG: Revision 1.27  1998/10/01 00:01:42  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.26  1998/09/25 23:20:32  mmiers
 * LOG: Add init flag so that output methods can be shared.
 * LOG:
 * LOG: Revision 1.25  1998/09/24 16:10:07  jrao
 * LOG: Can't use trace if trace hasn't been started yet.  Add some code
 * LOG: to the trace macros to check for a valid trace subsystem before
 * LOG: executing.
 * LOG:
 * LOG: Revision 1.24  1998/09/23 23:41:13  mmiers
 * LOG: Tracing is almost complete.  Just need to add event trace.
 * LOG:
 * LOG: Revision 1.23  1998/09/22 16:01:26  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.22  1998/09/21 22:52:30  mmiers
 * LOG: Start adding C-trace to infrastructure.
 * LOG:
 * LOG: Revision 1.21  1998/09/21 18:31:17  mmiers
 * LOG: Get C-trace hooked up and working.
 * LOG:
 * LOG: Revision 1.20  1998/09/18 23:42:32  mmiers
 * LOG: Forgot about the output method.
 * LOG:
 * LOG: Revision 1.19  1998/09/18 23:10:10  mmiers
 * LOG: Add remaining methods.
 * LOG:
 * LOG: Revision 1.18  1998/09/18 22:31:15  mmiers
 * LOG: Remove dead tempory.  Make trace enable/disable per output as well.
 * LOG:
 * LOG: Revision 1.17  1998/09/18 22:15:56  mmiers
 * LOG: Use pointers, not structs.  Convert routing class to static methods.
 * LOG:
 * LOG: Revision 1.16  1998/09/18 22:04:05  mmiers
 * LOG: Rework C trace for vendor code.
 * LOG:
 * LOG: Revision 1.15  1998/06/24 17:45:06  mmiers
 * LOG: Convert over to using the generated exceptions.
 * LOG:
 * LOG: Revision 1.14  1998/06/23 02:31:08  mmiers
 * LOG: Update Solaris build environment.  Part of getting SCCP working.
 * LOG:
 * LOG: Revision 1.13  1998/06/05 17:01:54  hdivoux
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.12  1998/06/01 16:35:21  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.11  1998/06/01 13:44:36  mmiers
 * LOG: Fix compilation bugs.
 * LOG:
 * LOG: Revision 1.10  1998/06/01 00:43:33  mmiers
 * LOG: Add interface descriptions.
 * LOG:
 * LOG: Revision 1.9  1998/05/26 20:07:23  hdivoux
 * LOG: Corrections.
 * LOG:
 * LOG: Revision 1.8  1998/05/19 17:11:49  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.7  1998/05/01 00:24:35  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.6  1998/04/28 22:52:41  mmiers
 * LOG: Rework trace slightly to have a more general semantic.  You are no
 * LOG: longer limited to one trace facility per program.
 * LOG:
 * LOG: Revision 1.5  1998/04/28 01:05:20  mmiers
 * LOG: Minor tweaks to trace.
 * LOG:
 * LOG: Revision 1.4  1998/04/27 20:03:32  mmiers
 * LOG: Slight modification for operator<< (removed).  Need to think more about
 * LOG: that one.
 * LOG:
 * LOG: Revision 1.3  1998/04/27 20:00:27  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.2  1998/04/09 01:47:20  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.1  1998/04/08 03:22:53  mmiers
 * LOG: New ITS APIs for trace, sockets.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_TRACE_H
#define ITS_TRACE_H

#include <stdio.h>
#include <stdarg.h>

#include <its.h>
#include <its_mutex.h>
#include <its_object.h>
/***********************Changes for directing its critical alarm to LOGGER***********/
#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif
#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

#ident "$Id: its_trace.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * Constants. 
 */
#if !defined(ITS_TRACE_ONESHOT)
#define ITS_TRACE_ONESHOT

#define TRACE_MAX_MSG_SIZE  1024     /* Max size of a trace message */

#define TRACE_TO_NONE           (1 << 0)
#define TRACE_TO_DISPLAY        (1 << 1)
#define TRACE_TO_FILE           (1 << 2)
#define TRACE_TO_SYSLOG         (1 << 3)
#define TRACE_TO_NT_EVENT_LOG   (1 << 4)
#define TRACE_TO_SNMP_MASK      (1 << 5)

/*
 * shared global data (C and C++)
 */
#if defined(__cplusplus)
extern "C"
{
#endif

#define ITS_SECS_PER_DAY        86400       /* number of seconds in a day */
#define ITS_NUM_TRACE_FILES     10          /* number of trace files to keep */
#define ITS_TRACE_PER_FILE_MAX  100000      /* number of trace outputs per file */

ITSDLLAPI extern ITS_MUTEX    TRACE_Mutex;

typedef struct _TRACE_OutputMethod* TRACE_OutputMethodPtr;

typedef void (*TRACE_OutputData)(TRACE_OutputMethodPtr method,
                                 const char *fmt, va_list args);

#define TRACE_OUTPUT_INHERIT_OUTPUT ((TRACE_OutputData)NULL)

/*
 * trace output method
 */
typedef struct
{
    char*               name;
    ITS_BOOLEAN         isEnabled;
    ITS_BOOLEAN         initDone;
    void*               data;
    char*               outName;
    ITS_TIME            start;
    ITS_TIME            curday;
    unsigned            reccount;
    void                *back;
}
TRACE_OutputPart;

typedef struct _TRACE_OutputMethod
{
    ITS_CoreObjectPart  core;
    TRACE_OutputPart    trace;
}
TRACE_OutputMethod;

typedef struct
{
    char*           name;
    ITS_BOOLEAN     isEnabled;
    void*           data;
    unsigned        flags;
}
TRACE_OutputInitializer;

#define TRACE_OUTPUT_NAME(x) \
    (((TRACE_OutputMethod *)(x))->trace.name)

#define TRACE_OUTPUT_IS_ENABLED(x) \
    (((TRACE_OutputMethod *)(x))->trace.isEnabled)

#define TRACE_OUTPUT_INIT_DONE(x) \
    (((TRACE_OutputMethod *)(x))->trace.initDone)

#define TRACE_OUTPUT_DATA(x) \
    (((TRACE_OutputMethod *)(x))->trace.data)

#define TRACE_OUTPUT_OUT_NAME(x) \
    (((TRACE_OutputMethod *)(x))->trace.outName)

#define TRACE_OUTPUT_START(x) \
    (((TRACE_OutputMethod *)(x))->trace.start)

#define TRACE_OUTPUT_CUR_DAY(x) \
    (((TRACE_OutputMethod *)(x))->trace.curday)

#define TRACE_OUTPUT_REC_COUNT(x) \
    (((TRACE_OutputMethod *)(x))->trace.reccount)

#define TRACE_OUTPUT_BACK(x) \
    (((TRACE_OutputMethod *)(x))->trace.back)

typedef struct
{
    TRACE_OutputData    output;
}
TRACE_OutputClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    TRACE_OutputClassPart   outputClass;
}
TRACE_OutputClassRec, *TRACE_OutputClass;

#define TRACE_OUTPUT_CLASS_OUTPUT(x) \
    (((TRACE_OutputClass)(x))->outputClass.output)

/*
 * class records.
 */
#define TRACE_OUTPUT_CLASS_NAME             "TRACE Output BaseClass"
#define TRACE_OUTPUT_FILE_CLASS_NAME        "TRACE Output FileClass"
#define TRACE_OUTPUT_STDOUT_CLASS_NAME      "TRACE Output StdoutClass"
#define TRACE_OUTPUT_SYSLOG_CLASS_NAME      "TRACE Output SyslogClass"
#define TRACE_OUTPUT_EVENTLOG_CLASS_NAME    "TRACE Output EventLogClass"

/* base class */
ITSDLLAPI extern TRACE_OutputClassRec itsTRACE_OutputClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_OutputClass;

/* file classes */
ITSDLLAPI extern TRACE_OutputClassRec itsTRACE_OutputFileClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_OutputFileClass;
ITSDLLAPI extern TRACE_OutputClassRec itsTRACE_OutputStdoutClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_OutputStdoutClass;

/* system log classes */
#if defined(unix)
ITSDLLAPI extern TRACE_OutputClassRec itsTRACE_OutputSyslogClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_OutputSyslogClass;
#endif

#if defined(WIN32)
ITSDLLAPI extern TRACE_OutputClassRec itsTRACE_OutputEventLogClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_OutputEventLogClass;
#endif

/*
 * trace map entry
 */
#define MAX_TRACE_LEVEL_OUTPUTS 48 

typedef struct
{
    char*                   levelName;
    ITS_BOOLEAN             isEnabled;      /* note: THIS IS UNGUARDED */
    int                     numOutputs;
    int                     levelNum;       /* Only used by C++ tracing */
    TRACE_OutputMethod*     outputs[MAX_TRACE_LEVEL_OUTPUTS];
    void*                   back;           /* C++ object */
} 
TRACE_LevelPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRACE_LevelPart         level;
}
TRACE_Level;

typedef struct
{
    char*                       levelName;
    ITS_BOOLEAN                 isEnabled;
    int                         numOutputs;
    TRACE_OutputInitializer*    outputs[MAX_TRACE_LEVEL_OUTPUTS];
}
TRACE_LevelInitializer;

#define TRACE_LEVEL_NAME(x) \
    (((TRACE_Level *)(x))->level.levelName)

#define TRACE_LEVEL_IS_ENABLED(x) \
    (((TRACE_Level *)(x))->level.isEnabled)

#define TRACE_LEVEL_NUM_OUTPUTS(x) \
    (((TRACE_Level *)(x))->level.numOutputs)

#define TRACE_LEVEL_LEVEL_NUM(x) \
    (((TRACE_Level *)(x))->level.levelNum)

#define TRACE_LEVEL_OUTPUTS(x) \
    (((TRACE_Level *)(x))->level.outputs)

#define TRACE_LEVEL_BACK(x) \
    (((TRACE_Level *)(x))->level.back)

#define TRACE_LEVEL_CLASS_NAME  "TRACE LevelClass"

typedef ITS_ClassRec    TRACE_LevelClassRec, *TRACE_LevelClass;

ITSDLLAPI extern TRACE_LevelClassRec  itsTRACE_LevelClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_LevelClass;

/*
 * Trace instance data
 *
 * unitName             subsystem identification
 * currentLevel         the trace level in a single trace
 * numLevels            the number of trace levels here
 * levelMap             pointers to each trace level
 */
#define MAX_TRACE_LEVELS        48 

typedef struct
{
    char            unitName[ITS_PATH_MAX]; 
    int             currentLevel;
    int             numLevels;
    TRACE_Level*    levelMap[MAX_TRACE_LEVELS];
}
TRACE_DataPart;

typedef struct
{
    ITS_CoreClassPart   core;
    TRACE_DataPart      trace;
}
TRACE_Data;

#define TRACE_DATA_UNIT_NAME(x) \
    (((TRACE_Data *)(x))->trace.unitName)

#define TRACE_DATA_CURRENT_LEVEL(x) \
    (((TRACE_Data *)(x))->trace.currentLevel)

#define TRACE_DATA_NUM_LEVELS(x) \
    (((TRACE_Data *)(x))->trace.numLevels)

#define TRACE_DATA_LEVEL_MAP(x) \
    (((TRACE_Data *)(x))->trace.levelMap)


typedef ITS_ClassRec    TRACE_DataClassRec, *TRACE_DataClass;

typedef ITS_ClassRec        TRACE_ClassRec;

#define TRACE_CLASS_NAME    "TRACE_CLASS"

ITSDLLAPI extern TRACE_ClassRec       itsTRACE_ClassRec;
ITSDLLAPI extern ITS_Class            itsTRACE_Class;

#define TRACE_IsInitialized() \
    ITS_CLASS_INITTED(itsTRACE_Class)

/*.interface:TRACE
 *****************************************************************************
 *  Interface:
 *      TRACE_*
 *
 *  Purpose:
 *      all tracing levels
 *
 *  Usage:
 *
 *****************************************************************************/

ITSDLLAPI int TRACE_AcquireMutex();
ITSDLLAPI int TRACE_ReleaseMutex();

/*
 * output functions
 */
ITSDLLAPI extern void TRACE_SetOutputOnOff(TRACE_Data* td,
                                           int level, int output,
                                           ITS_BOOLEAN onOff);
ITSDLLAPI extern void TRACE_SetOutputOnOffByName(TRACE_Data* td,
                                                 const char* levName,
                                                 const char* name,
                                                 ITS_BOOLEAN onOff);
ITSDLLAPI extern ITS_BOOLEAN TRACE_IsOutputOn(TRACE_Data* td,
                                              int level,
                                              int output);
/*
 * level functions
 */
ITSDLLAPI extern void TRACE_SetLevelOnOff(TRACE_Data* td,
                                          int level, 
                                          ITS_BOOLEAN onOff);
ITSDLLAPI extern void TRACE_SetLevelOnOffByName(TRACE_Data* td,
                                                const char* name, 
                                                ITS_BOOLEAN onOff);
ITSDLLAPI extern ITS_BOOLEAN TRACE_IsLevelOn(TRACE_Data* td, int level);

ITSDLLAPI extern int  TRACE_AddOutput(TRACE_Level* level,
                                      TRACE_OutputMethod* output);
ITSDLLAPI extern int  TRACE_RemOutput(TRACE_Level* level,
                                      char *name);

/*
 * global functions
 */
ITSDLLAPI extern void TRACE_Output(const char* fmt, ...);

ITSDLLAPI extern void         TRACE_UpdateSettings();

ITSDLLAPI extern char* TRACE_Header(TRACE_Data* td,
                                    const char *fileName, int lineNum);

ITSDLLAPI extern TRACE_Data*  TRACE_Constructor(const char *subsystem,
                                                TRACE_LevelInitializer *levelMap,
                                                int levelMapCount);

ITSDLLAPI extern void TRACE_Destructor(TRACE_Data* data); 

ITSDLLAPI extern int  TRACE_AddLevel(TRACE_Data* data, TRACE_Level* level);
ITSDLLAPI extern int  TRACE_RemLevel(TRACE_Data* data, char *levelName);
ITSDLLAPI extern TRACE_Level* TRACE_FindLevel(TRACE_Data *data, char *levelName);

ITSDLLAPI extern void TRACE_TurnFlushAfterWriteOnOff(ITS_BOOLEAN onOff);

/*
 * to check if tracing is enabled,
 */
ITSDLLAPI extern void TRACE_TurnCriticalTraceOnOff(ITS_BOOLEAN onOff);
ITSDLLAPI extern void TRACE_TurnErrorTraceOnOff(ITS_BOOLEAN onOff);
ITSDLLAPI extern void TRACE_TurnWarningTraceOnOff(ITS_BOOLEAN onOff);
ITSDLLAPI extern void TRACE_TurnDebugTraceOnOff(ITS_BOOLEAN onOff);
ITSDLLAPI extern void TRACE_TurnEventTraceOnOff(ITS_BOOLEAN onOff);

ITSDLLAPI extern ITS_BOOLEAN TRACE_CriticalTraceOn();
ITSDLLAPI extern ITS_BOOLEAN TRACE_ErrorTraceOn();
ITSDLLAPI extern ITS_BOOLEAN TRACE_WarningTraceOn();
ITSDLLAPI extern ITS_BOOLEAN TRACE_DebugTraceOn();
ITSDLLAPI extern ITS_BOOLEAN TRACE_EventTraceOn();

ITSDLLAPI extern void TRACE_EnableTrace();
ITSDLLAPI extern void TRACE_DisableTrace();

/*
 * the ITS internal trace is used by the infrastructure.  Users may or may
 * not want to use these.
 *
 * NOTE: These macros are not useful before ITS_GlobalStart() is called.
 *
static TRACE_OutputMethod fileTrace =
{
    ITS_FILE_STRING,
    ITS_TRUE,
    TRACE_OpenFile,
    TRACE_CloseFile,
    TRACE_OutputFile,
    ".its-trace"
};

static TRACE_OutputMethod stdoutTrace =
{
    ITS_STDOUT_STRING,
    ITS_TRUE,
    TRACE_OpenStdout,
    TRACE_CloseStdout,
    TRACE_OutputFile,
    NULL
};
static TRACE_LevelMap ITS_TraceMap[] =
{
    {ITS_CRITICAL_STRING, ITS_TRUE,  1, { &stdoutTrace, &fileTrace } },
    {ITS_ERROR_STRING,    ITS_TRUE,  1, { &stdoutTrace, &fileTrace } },
    {ITS_WARNING_STRING,  ITS_TRUE,  1, { &stdoutTrace, &fileTrace } },
    {ITS_DEBUG_STRING,    ITS_TRUE,  1, { &stdoutTrace, &fileTrace } },
    {ITS_EVENT_STRING,    ITS_FALSE, 1, { &stdoutTrace, &fileTrace } },
};
 */
ITSDLLAPI extern TRACE_Data* ITS_InternalTrace;

#define ITS_TRACE_LEVEL_CRITICAL      0
#define ITS_TRACE_LEVEL_ERROR         1
#define ITS_TRACE_LEVEL_WARNING       2
#define ITS_TRACE_LEVEL_DEBUG         3
#define ITS_TRACE_LEVEL_EVENT         4

/*
 * trace string names.  These are the names as they appear
 * in the config file.
 */
#define ITS_TRACE_CRITICAL_STRING "TRACE_CRITICAL"
#define ITS_TRACE_ERROR_STRING    "TRACE_ERROR"
#define ITS_TRACE_WARNING_STRING  "TRACE_WARNING"
#define ITS_TRACE_DEBUG_STRING    "TRACE_DEBUG"
#define ITS_TRACE_EVENT_STRING    "TRACE_EVENT"

/*
 * these are the level names for ITS_TRACE_XXX
 */
#define ITS_CRITICAL_STRING "Critical"
#define ITS_ERROR_STRING    "Error"
#define ITS_WARNING_STRING  "Warning"
#define ITS_DEBUG_STRING    "Debug"
#define ITS_EVENT_STRING    "Event"

/*
 * these are the output names for ITS_TRACE_XXX
 */
#define ITS_STDOUT_STRING   "stdout"
#define ITS_FILE_STRING     "file"
#define ITS_SYSLOG_STRING   "syslog"

/*
 * global data
 */
ITSDLLAPI extern TRACE_Data*  TRACE_Current;
ITSDLLAPI extern ITS_BOOLEAN  TRACE_GlobalEnable;

/*
 * Public macros. 
 */
#define TRACE(traceData, level, args)                                          \
    do                                                                         \
    {                                                                          \
        if (TRACE_GlobalEnable && TRACE_IsInitialized() && traceData &&        \
            level >= 0 && level < TRACE_DATA_NUM_LEVELS(traceData) &&          \
            TRACE_LEVEL_IS_ENABLED(TRACE_DATA_LEVEL_MAP(traceData)[(level)]))  \
        {                                                                      \
            MUTEX_AcquireMutex(&TRACE_Mutex);                                  \
            TRACE_DATA_CURRENT_LEVEL(traceData) = level;                       \
            TRACE_Current = traceData;                                         \
            TRACE_Output(TRACE_Header(traceData,                               \
                                      __FILE__, __LINE__));                    \
            TRACE_Output args;                                                 \
            TRACE_Current = NULL;                                              \
            MUTEX_ReleaseMutex(&TRACE_Mutex);                                  \
        }                                                                      \
    }                                                                          \
    while (0)

#define TRACE_RAW(traceData, level, args)                                      \
    do                                                                         \
    {                                                                          \
        if (TRACE_GlobalEnable && TRACE_IsInitialized() && traceData &&        \
            level >= 0 && level < TRACE_DATA_NUM_LEVELS(traceData) &&          \
            TRACE_LEVEL_IS_ENABLED(TRACE_DATA_LEVEL_MAP(traceData)[(level)]))  \
        {                                                                      \
            MUTEX_AcquireMutex(&TRACE_Mutex);                                  \
            TRACE_DATA_CURRENT_LEVEL(traceData) = level;                       \
            TRACE_Current = traceData;                                         \
            TRACE_Output args;                                                 \
            TRACE_Current = NULL;                                              \
            MUTEX_ReleaseMutex(&TRACE_Mutex);                                  \
        }                                                                      \
    }                                                                          \
    while (0)

/*
 * performance affecting.  By default, fflush() is not called
 * after every trace.  Set this to "on" for better trace
 * latency, but it will hurt performance.
 */
#define TRACE_FLUSH_AFTER_WRITE_STRING  "traceFlushAfterWrite"
/***********************************Sandeep jeevan***************/
#ifdef LOGGER_IMR
#define ITS_TRACE_CRITICAL(args) \
	LOG_PRINT_CRITICAL args;
#else


#define ITS_TRACE_CRITICAL(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_CRITICAL, args)
#endif

#ifdef LOGGER_IMR
#define ITS_TRACE_ERROR(args) \
	LOG_PRINT_CRITICAL args;
#else
#define ITS_TRACE_ERROR(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_ERROR, args)
#endif

#if !defined(DISABLE_TRACE)
/*#define ITS_TRACE_CRITICAL(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_CRITICAL, args)
#define ITS_TRACE_ERROR(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_ERROR, args)*/
#define ITS_TRACE_WARNING(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_WARNING, args)
#define ITS_TRACE_DEBUG(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG, args)
#define ITS_TRACE_EVENT(args) \
    TRACE(ITS_InternalTrace, ITS_TRACE_LEVEL_EVENT, args)

#else

#define ITS_TRACE_CRITICAL(args)
#define ITS_TRACE_ERROR(args)
#define ITS_TRACE_WARNING(args)
#define ITS_TRACE_DEBUG(args)
#define ITS_TRACE_EVENT(args)

#endif

#if defined(__cplusplus)
}
#endif

#endif

#if defined(USE_CPLUSPLUS)

#include <its++.h>
#include <its_exception.h>
#include <its_mutex.h>
#include <its_timers.h>

#include <stdarg.h>
#include <string>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:TraceOutputMethod
 *****************************************************************************
 *  Interface:
 *      TraceOutputMethod
 *
 *  Purpose:
 *      Abstract base class for all the trace output methods. A trace output 
 *      method is an abstraction of where a trace can actually be written. It
 *      can be an ASCII file, the standard output, Unix Syslog...
 *
 *  Usage:
 *      Usually not used directly because a group of predefined trace output 
 *      methods already exists. Nevertheless, can be used by inheritance to 
 *      implement a specific trace output method.
 *
 *****************************************************************************/
class TraceOutputMethod
{
public:
    friend class TraceLevel;

    TraceOutputMethod(const char* nameParam)
        : output(NULL)
    {
        name = strdup(nameParam);
    }

    virtual ~TraceOutputMethod()
    {
        if (output)
        {
            ITS_DestructObject((ITS_Object)output);
        }

        free(name);
    }

    virtual void
    Output(const char *format, va_list args)
    {
        TRACE_OUTPUT_CLASS_OUTPUT(output)(output, format, args);
    }

    const char * const
    Name() const
    {
        return name;
    }

   /*.implementation:public,inline,TraceOutputMethod
    ************************************************************************
    *  Purpose:
    *       Is the current trace output enabled?
    *
    *  Return Value:
    *       ITS_BOOLEAN - true if trace output enabled.
    *
    ************************************************************************/
    inline ITS_BOOLEAN
    IsEnabled()
    {
        ITS_THROW_ASSERT(output != NULL);

        return TRACE_OUTPUT_IS_ENABLED(output);
    }

    /*.implementation:public,inline,TraceOutputMethod
    ************************************************************************
    *  Purpose:
    *       Enable the current trace output.
    *
    ************************************************************************/
    inline void
    Enable()
    {
        ITS_THROW_ASSERT(output != NULL);

        TRACE_OUTPUT_IS_ENABLED(output) = ITS_YES;
    }

    /*.implementation:public,inline,ITS_TraceOutput
    ************************************************************************
    *  Purpose:
    *       Disable the current trace output. 
    *
    ************************************************************************/
    inline void
    Disable()
    {
        ITS_THROW_ASSERT(output != NULL);

        TRACE_OUTPUT_IS_ENABLED(output) = ITS_NO;
    }

    /*.implementation:public,inline,ITS_TraceOutput
    ************************************************************************
    *  Purpose:
    *       Get the underlying C object as a const pointer. 
    *
    *  Return Value:
    *       The underlying C struct pointer.
    *
    ************************************************************************/
    inline const TRACE_OutputMethod *
    GetOutput() const
    {
        ITS_THROW_ASSERT(output != NULL);

        return output;
    }
    
protected:
    char *name;
    TRACE_OutputMethod* output;

private:
    /* sorry folks, no copying these */
    TraceOutputMethod(TraceOutputMethod&) {}
    TraceOutputMethod& operator=(TraceOutputMethod&) { return *this; }
};

/*.interface:TraceFile
 *****************************************************************************
 *  Interface:
 *      TraceFile
 *
 *  Purpose:
 *      To trace to a file.
 *
 *  Usage:
 *      See classes TraceSubSystem and TraceLevel. Usually not used
 *      directly.
 *
 *****************************************************************************/
class TraceFile : public TraceOutputMethod
{
public:
    TraceFile(const char *nameParam, char *fname)
        : TraceOutputMethod(nameParam)
    {
        output = (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputFileClass,
										nameParam, ITS_TRUE, fname);

        ITS_THROW_ASSERT(output != NULL);
    }

protected:
    // This is specifically used by the class below.
    TraceFile()
        : TraceOutputMethod("stdout")
    {
        output = (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputStdoutClass,
                                        name, ITS_TRUE, "STDOUT");

        ITS_THROW_ASSERT(output != NULL);
    }
};

/*.interface:TraceStdout
 *****************************************************************************
 *  Interface:
 *      TraceStdout
 *
 *  Purpose:
 *      To trace to the standard output.
 *
 *  Usage:
 *      See classes TraceSubSystem and TraceLevel. Usually not used
 *      directly.
 *
 *****************************************************************************/
class TraceStdout : public TraceFile
{
public:
    TraceStdout()
        : TraceFile()
    {
    }
};

/*
 * trace to syslog
 */
#if defined(unix)

/*.interface:TraceUnixSyslog
 *****************************************************************************
 *  Interface:
 *      TraceUnixSyslog
 *
 *  Purpose:
 *      To trace to Unix Syslog. 
 *
 *  Usage:
 *      See classes TraceSubSystem and TraceLevel. Usually not used
 *      directly.
 *
 *****************************************************************************/
class TraceUnixSyslog : public TraceOutputMethod
{
public:
    TraceUnixSyslog(const char *nameParam)
        : TraceOutputMethod(nameParam)
    {
        output = (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputSyslogClass,
                                        nameParam, ITS_TRUE, "SYSLOG");

        ITS_THROW_ASSERT(output != NULL);
    }
};

#endif

/*
 * trace to the NT event log
 */
#if defined(WIN32)

/*.interface:TraceNtEventLog
 *****************************************************************************
 *  Interface:
 *      TraceNtEventLog
 *
 *  Purpose:
 *      To trace to the NT Event Log.
 *
 *  Usage:
 *      See classes TraceSubSystem and TraceLevel. Usually not used
 *      directly.
 *
 *****************************************************************************/
class TraceNtEventLog : public TraceOutputMethod
{
public:
    TraceNtEventLog(const char *nameParam)
        : TraceOutputMethod(nameParam)
    {
        output = (TRACE_OutputMethod *)
                    ITS_ConstructObject(itsTRACE_OutputEventLogClass,
                                        nameParam, ITS_TRUE, "EventLog");

        ITS_THROW_ASSERT(output != NULL);
    }
};

#endif

/*.interface:TraceLevel
 *****************************************************************************
 *  Interface:
 *      TraceLevel
 *
 *  Purpose:
 *      A level of trace within a subsystem. Uniquely identified within the
 *      subsystem by its name. Can be enabled or disabled.
 *
 *  Usage:
 *      Create one or more trace level objects for a subsystem. Add these
 *      trace level objects to the subsystem trace object. Enable or disable
 *      a trace level. Beware that a trace level name must be unique within
 *      a subsystem. For a concrete how to use example, see the class
 *      TraceSubSystem.
 *
 *****************************************************************************/
class TraceLevel
{
public:
    friend class TraceSubSystem;

    /*.implementation:public,inline,TraceLevel
     ************************************************************************
     *  Purpose:
     *      This method constructs a trace level.
     *
     *  Input Parameters:
     *      name - the name of the trace level.
     *      mask - a mask of trace level modifiers.
     *
     *  See Also:
     *      ~TraceLevel
     *
     ************************************************************************/
    /*TraceLevel::TraceLevel(const char *name, int mask) Kernel 2.6  */
    TraceLevel(const char *name, int mask) 
    {
        char outName[ITS_PATH_MAX];
        TRACE_LevelInitializer init;
        TraceOutputMethod *tmp;

        init.levelName = (char *)name;
        init.isEnabled = ITS_TRUE;
        init.numOutputs = 0;

        level = (TRACE_Level *)ITS_ConstructObject(itsTRACE_LevelClass,
                                                   &init);

        ITS_THROW_ASSERT(level != NULL);

        TRACE_LEVEL_BACK(level) = this;

        if (mask & TRACE_TO_DISPLAY)
        {
            tmp = new TraceStdout();

            ITS_THROW_ASSERT(tmp != NULL);

            TRACE_LEVEL_OUTPUTS(level)[TRACE_LEVEL_NUM_OUTPUTS(level)] = 
                const_cast<TRACE_OutputMethod *>(tmp->GetOutput());

            TRACE_OUTPUT_BACK(TRACE_LEVEL_OUTPUTS(level)
                                [TRACE_LEVEL_NUM_OUTPUTS(level)]) =
                tmp;

            TRACE_LEVEL_NUM_OUTPUTS(level)++;
        }

        if (mask & TRACE_TO_FILE)
        {
            strcpy(outName, name);
            strcat(outName, ".trace");

            tmp = new TraceFile(name, outName);

            TRACE_LEVEL_OUTPUTS(level)[TRACE_LEVEL_NUM_OUTPUTS(level)] = 
                const_cast<TRACE_OutputMethod *>(tmp->GetOutput());

            TRACE_OUTPUT_BACK(TRACE_LEVEL_OUTPUTS(level)
                                [TRACE_LEVEL_NUM_OUTPUTS(level)]) =
                tmp;

            TRACE_LEVEL_NUM_OUTPUTS(level)++;
        }

    #if defined(unix)
        if (mask & TRACE_TO_SYSLOG)
        {
            tmp = new TraceUnixSyslog(name);

            ITS_THROW_ASSERT(tmp != NULL);

            TRACE_LEVEL_OUTPUTS(level)[TRACE_LEVEL_NUM_OUTPUTS(level)] = 
                const_cast<TRACE_OutputMethod *>(tmp->GetOutput());

            TRACE_OUTPUT_BACK(TRACE_LEVEL_OUTPUTS(level)
                                [TRACE_LEVEL_NUM_OUTPUTS(level)]) =
                tmp;

            TRACE_LEVEL_NUM_OUTPUTS(level)++;
        }
    #endif

    #if defined(WIN32)
        if (mask & TRACE_TO_NT_EVENT_LOG)
        {
            tmp = new TraceNtEventLog(name);

            ITS_THROW_ASSERT(tmp != NULL);

            TRACE_LEVEL_OUTPUTS(level)[TRACE_LEVEL_NUM_OUTPUTS(level)] = 
                const_cast<TRACE_OutputMethod *>(tmp->GetOutput());
        
            TRACE_OUTPUT_BACK(TRACE_LEVEL_OUTPUTS(level)
                                [TRACE_LEVEL_NUM_OUTPUTS(level)]) =
                tmp;

            TRACE_LEVEL_NUM_OUTPUTS(level)++;
        }
    #endif
    }

    /*.implementation:public,inline,TraceLevel
     ************************************************************************
     *  Purpose:
     *      This method destroys a trace level.
     *
     *  See Also:
     *      TraceLevel()
     *
     ************************************************************************/
    ~TraceLevel()
    {
        int i;

        for (i = 0; i != TRACE_LEVEL_NUM_OUTPUTS(level); i++)
        {
            delete (TraceOutputMethod *)
                        TRACE_OUTPUT_BACK(TRACE_LEVEL_OUTPUTS(level)[i]);
        }

        TRACE_LEVEL_NUM_OUTPUTS(level) = 0;

        ITS_DestructObject((ITS_Object)level);
    }

   /*.implementation:public,inline,TraceLevel
    ************************************************************************
    *  Purpose:
    *       Is the current trace level enabled?
    *
    *  Return Value:
    *       ITS_BOOLEAN - true is trace level enabled.
    *
    ************************************************************************/
    inline ITS_BOOLEAN
    IsEnabled()
    {
        ITS_THROW_ASSERT(level != NULL);

        return TRACE_LEVEL_IS_ENABLED(level);
    }

    /*.implementation:public,inline,TraceLevel
    ************************************************************************
    *  Purpose:
    *       Enable the current trace level.
    *
    ************************************************************************/
    inline void
    Enable()
    {
        ITS_THROW_ASSERT(level != NULL);

        TRACE_LEVEL_IS_ENABLED(level) = ITS_YES;
    }

    /*.implementation:public,inline,TraceLevel
    ************************************************************************
    *  Purpose:
    *       Disable the current trace level. 
    *
    ************************************************************************/
    inline void
    Disable()
    {
        ITS_THROW_ASSERT(level != NULL);

        TRACE_LEVEL_IS_ENABLED(level) = ITS_NO;
    }

    /*.implementation:public,inline,TraceLevel
    ************************************************************************
    *  Purpose:
    *       To output trace data to the trace level (if enabled).
    *
    *  Input Parameters:
    *       format - a printf() style format string.
    *       list   - a varargs list.
    *
    ************************************************************************/
    inline void
    Output(const char *format, va_list list)
    {
        int i;

        for (i = 0; i < TRACE_LEVEL_NUM_OUTPUTS(level); i++)
        {
            TRACE_OUTPUT_CLASS_OUTPUT(ITS_OBJ_CLASS(TRACE_LEVEL_OUTPUTS(level)[i]))
                                      (TRACE_LEVEL_OUTPUTS(level)[i],
                                       format, list);
        }
    }

protected:
    TRACE_Level*        level;

private:
    /* sorry folks, no copying these */
    TraceLevel() {}
    TraceLevel(TraceLevel&) {}
    TraceLevel& operator=(TraceLevel&) { return *this; }
};


// forward (NT is silly)
extern ITSDLLAPI TraceSubSystem   *its_intern_trace;

/*.interface:TraceSubSystem
 *****************************************************************************
 *  Interface:
 *      TraceSubSystem
 *
 *  Purpose:
 *      Abstraction of the subsystem to be traced. A trace subsystem has one
 *      or more trace levels.
 *
 *  Usage:
 *      Typical use is a two steps process:
 *          
 *      o Initialize the trace mechanism and add the relevant trace levels
 *        needed by the subsystem to be traced.
 *
 *      o Use the trace macro ITS_TRACE to actually perform tracing.
 *
 *
 *      Example:
 *      --------
 *       
 *      // Initialization of the trace mechanism (must be done only once per
 *      // process, logical place is just at the beginning of the execution).
 *
 *      TraceSubSystem::InitializeTrace();     
 *
 *
 *      // Creation of a trace level object. This object must never be
 *      // destructed unless explicitly removed from the subsystem previously
 *      // (advice: consider creating trace level objects as static objects).
 *
 *      TraceLevel traceLevel("TraceLevelName", TRACE_TO_FILE_MASK);
 *
 *
 *      // Enable the trace level.
 *
 *      traceLevel.Enable();
 *
 *
 *      // Add the trace level to the subsystem.
 *
 *      TraceSubSystem::
 *          GetTrace().AddLevel("TraceLevelName", &traceLevel);
 *
 *      // Note: the logical place to create, add and enable trace levels is
 *      // also at the beginning of the execution of the process.
 *
 *      .......
 *
 *
 *      // The trace macro can be used in the subsystem code everywhere a
 *      // trace is required.
 *
 *      ITS_TRACE(("TraceLevelName",
 *                 "Trace a string <%s> and an integer <%d>",
 *                 "This is a string",
 *                 1999));
 *
 *      // Note that the trace macro ITS_TRACE takes a variable number of
 *      // arguments. The first two arguments are mandatory. The first 
 *      // argument must be the name of a trace level. The second argument is
 *      // a printf format like string. The other arguments are optional, but 
 *      // the number and the type of these arguments must correspond to what
 *      // is defined by the printf format like string.
 *
 *****************************************************************************/
class TraceSubSystem
{
public:
    /*.implementation:public,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method creates an TraceSubSystem object
     *
     *  Notes:
     *      This method can throw exceptions if the mutex cannot be initialized.
     *
     *  See Also:
     *      ~TraceSubSystem()
     *
     ************************************************************************/
    TraceSubSystem(const char *name = NULL)
    {
        data = TRACE_Constructor(name, NULL, 0);

        ITS_THROW_ASSERT(data != NULL);
    }

    /*.implementation:public,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method destroys a trace subsytem.
     *
     ************************************************************************/
    ~TraceSubSystem()
    {
        TRACE_Destructor(data);
    }

    /*.implementation:public,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method sets the name to the trace subsystem.
     *
     *  Input Parameters:
     *      name - the name for the subsystem.
     *
     ************************************************************************/
    void SetSubSystemName(const char *name)
    {
        if (name)
        {
            strncpy(TRACE_DATA_UNIT_NAME(data), name, ITS_PATH_MAX);
        }
    }

    /*.implementation:public,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method add a trace level to a trace subsystem.
     *
     *  Input Parameters:
     *      levelName - the name of the level to add.
     *      level     - the level to add.
     *
     ************************************************************************/
    void
    AddLevel(const char *levelName, TraceLevel *level)
    {
        if (TRACE_AcquireMutex() != ITS_SUCCESS)
        {
            return;
        }

        TRACE_AddLevel(data, level->level);

        TRACE_ReleaseMutex();
    }

    /*.implementation:public,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method removes a level from the trace subsystem.
     *
     *  Input Parameters:
     *      levelName - the name of the level to remove.
     *
     ************************************************************************/
    void
    RemLevel(const char *levelName)
    {
        if (TRACE_AcquireMutex() != ITS_SUCCESS)
        {
            return;
        }

        TRACE_RemLevel(data, const_cast<char *>(levelName));

        TRACE_ReleaseMutex();
    }

    /*.implementation:public,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method looks up a level in the trace subsystem by its name.
     *
     *  Input Parameters:
     *      levelName - the name of the level to search for
     *
     *  Return Value:
     *      If the level is found, a pointer to the level is returned.
     *      If an error occurs, or the level cannot be found, NULL is returned.
     *
     ************************************************************************/
    TraceLevel*
    GetLevel(const char *levelName)
    {
        TRACE_Level* level;

        if (TRACE_AcquireMutex() != ITS_SUCCESS)
        {
            return NULL;
        }

        level = TRACE_FindLevel(data, const_cast<char *>(levelName));

        TRACE_ReleaseMutex();

        return (TraceLevel *)TRACE_LEVEL_BACK(level);
    }

    /*.implementation:static,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      Set the current file and line info, grab the mutex
     *
     *  Return Value:
     *      If the trace level is entered, ITS_SUCCESS
     *      is returned.
     *
     *  Notes:
     *      Errors are reported by throwing an exception.
     *
     ************************************************************************/
    int
    TraceEnter(const char *_file, int _line)
    {
        int ret = TRACE_AcquireMutex();

        if (ret == ITS_SUCCESS)
        {
            file = _file;
            line = _line;
        }

        return (ret);
    }

    /*.implementation:static,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      Generate trace output
     *
     ************************************************************************/
    void
    Trace(const char *format, ...)
    {
        if (currentLevel && currentLevel->IsEnabled())
        {
            va_list alist;

            va_start(alist, format);

#if defined(DECUNIX)
/* whose bloody stupid idea was this??? */
            va_list idiocy;
            memset(&idiocy, 0, sizeof(idiocy));
            currentLevel->Output(TRACE_Header(data, file,line), idiocy);

#elif defined(mvlppc)
            va_list idiocy;
            memset(&idiocy, 0, sizeof(idiocy));
            currentLevel->Output(TRACE_Header(data, file,line), idiocy);

#else
            currentLevel->Output(TRACE_Header(data, file, line), NULL);

#endif

            currentLevel->Output(format, alist);

#if defined(DECUNIX)
/* whose bloody stupid idea was this??? */
            currentLevel->Output("\n", idiocy);

#elif defined(mvlppc)
            currentLevel->Output("\n", idiocy);

#else
            currentLevel->Output("\n", NULL);

#endif

            va_end(alist);
        }
    }

    /*.implementation:static,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      Set the current trace level
     *
     ************************************************************************/
    void
    SetLevel(const char *levelName)
    {
        TRACE_Level *level;

        level = TRACE_FindLevel(data, const_cast<char *>(levelName));

        if (level)
        {
            currentLevel = (TraceLevel *)TRACE_LEVEL_BACK(level);
            TRACE_DATA_CURRENT_LEVEL(data) =
                TRACE_LEVEL_LEVEL_NUM(currentLevel->level);
        }
        else
        {
            currentLevel = NULL;
            TRACE_DATA_CURRENT_LEVEL(data) = 0;
        }
    }

    int
    TraceExit(const char *fileName, int lineNo)
    {
        return TRACE_ReleaseMutex();
    }

    /*
     * NOTE: must be called while single threaded
     */
    /*.implementation:static,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      Initialize the trace subystem.
     *
     *  Return Value:
     *      If the trace subsystem is successfully initialized, ITS_SUCCESS
     *      is returned.
     *
     *  Notes:
     *      Errors are reported by throwing an exception.
     *
     ************************************************************************/
    static int
    InitializeTrace()
    {
        its_intern_trace = new TraceSubSystem;

        return ITS_SUCCESS;
    }

    /*.implementation:static,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      This method returns a pointsr to the global trace subsystem.
     *
     ************************************************************************/
    static TraceSubSystem&
    GetTrace()
    {
        if (its_intern_trace == NULL)
        {
            int ret = InitializeTrace();

            ITS_THROW_ASSERT(ret == ITS_SUCCESS);
        }

        return *its_intern_trace;
    }

    /*.implementation:static,inline,TraceSubSystem
     ************************************************************************
     *  Purpose:
     *      Globally enable or disable trace.
     *
     ************************************************************************/
    static void
    EnableTrace(bool onOff)
    {
        if (onOff)
        {
            TRACE_EnableTrace();
        }
        else
        {
            TRACE_DisableTrace();
        }
    }

private:
    /* sorry folks, no copying these */
    TraceSubSystem(TraceSubSystem&) {}
    TraceSubSystem& operator=(TraceSubSystem&) { return *this; }

    TraceLevel*             currentLevel;
    const char*             file;
    int                     line;
    TRACE_Data*             data;
};

#if defined(ITS_NAMESPACE)
}
#endif

/*
 * Usage is:
 * ITS_TRACE("level", ("bite my %s", "left little toe"))
 */
#define ITS_TRACE(level, args)                                              \
    if (TRACE_GlobalEnable && TRACE_IsInitialized() &&                      \
        its::TraceSubSystem::GetTrace().TraceEnter(__FILE__, __LINE__)      \
        == ITS_SUCCESS)                                                     \
    {                                                                       \
        its::TraceSubSystem::GetTrace().SetLevel(level);                    \
        try                                                                 \
        {                                                                   \
            its::TraceSubSystem::GetTrace().Trace args;                     \
            its::TraceSubSystem::GetTrace().TraceExit(NULL, 0);             \
        }                                                                   \
        catch (its::ITS_GenericException& exc)                              \
        {                                                                   \
            exc.Log();                                                      \
            its::TraceSubSystem::                                           \
                GetTrace().Trace("ERROR: Exception while tracing.");        \
            its::TraceSubSystem::GetTrace().TraceExit(NULL, 0);             \
        }                                                                   \
        catch (std::exception& ex)                                          \
        {                                                                   \
            its::ITS_StandardException stx(ex.what(), __FILE__, __LINE__);  \
            stx.Log();                                                      \
            its::TraceSubSystem::                                           \
                GetTrace().Trace("ERROR: Exception while tracing.");        \
            its::TraceSubSystem::GetTrace().TraceExit(NULL, 0);             \
        }                                                                   \
        catch (...)                                                         \
        {                                                                   \
            its::TraceSubSystem::                                           \
                GetTrace().Trace("PANIC: Exception while tracing.");        \
            its::TraceSubSystem::GetTrace().TraceExit(NULL, 0);             \
            exit(EXIT_FAILURE);                                             \
        }                                                                   \
    }

#else   /* HAVE_CPLUSPLUS */

#undef ITS_MUTEX_H

#include <its_mutex.h>

#endif /* USE_CPLUSPLUS */

#endif /* ITS_TRACE_H */
