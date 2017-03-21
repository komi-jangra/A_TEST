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
 * LOG: Revision 1.2  2007/03/30 04:58:54  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/03/28 01:57:04  mmiers
 * LOG: Potential warning material.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.10  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:55:49  mmiers
 * LOG: A few typos.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.2  2001/01/17 20:34:40  mmiers
 * LOG: Get the flags right.
 * LOG:
 * LOG: Revision 3.1  2001/01/17 01:01:34  mmiers
 * LOG: Convert event log to C.  Add dispatch project.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.9  1999/03/22 17:06:54  hdivoux
 * LOG: Update for better viewing experience with NT Event Viewer.
 * LOG:
 * LOG: Revision 1.8  1998/11/18 15:14:47  mmiers
 * LOG: Correct for HPUX build.
 * LOG:
 * LOG: Revision 1.7  1998/11/18 01:03:55  mmiers
 * LOG: Build event log/exception log on UNIX
 * LOG:
 * LOG: Revision 1.6  1998/11/18 00:50:42  mmiers
 * LOG: Implement UNIX versions of these.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 20:10:42  hdivoux
 * LOG: Added documentation.
 * LOG:
 * LOG: Revision 1.4  1998/06/01 18:57:10  hdivoux
 * LOG: Added documentation.
 * LOG:
 * LOG: Revision 1.3  1998/05/19 16:37:18  hdivoux
 * LOG: Fixed namespace related issues.
 * LOG:
 * LOG: Revision 1.2  1998/05/19 15:49:29  mmiers
 * LOG: Fix the namespace problems.
 * LOG:
 * LOG: Revision 1.1  1998/05/14 20:40:28  hdivoux
 * LOG: Added event log related files.
 * LOG:
 *
 ****************************************************************************/

#include <string.h>

#if defined(WIN32)
#include <windows.h>
#endif
#if defined(unix)
#include <syslog.h>
#endif

#include <its.h>
#include <its_trace.h>
#include <its_event_log.h>
#include <its_assertion.h>

#ident "$Id: its_event_log.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*
 * NT specific code.
 */
#if defined(WIN32)

/*.implementation:extern
 ***************************************************************************
 *
 *  Purpose:
 *      Create an event source in the NT Registry.
 *
 *  Input Parameters:
 *      srcName     - name of the source to create.
 *      msgFileName - name of the associated message file name DLL (typically
 *                    this should be "ItsMsgFile.dll".
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      long - ERROR_SUCCESS if call is successful or an NT error code.
 *
 *  Notes:
 *      Should be called by the installation procedure.
 *
 *  See Also:
 *
 ***************************************************************************/
ITSDLLAPI long
NT_RegistryCreateSource(const char *srcName,
                        const char *msgFileName)
{
    long result = ERROR_SUCCESS;
    char buf[256];
    HKEY hKey;
    DWORD supportedTypes;

    ITS_C_REQUIRE(srcName != NULL);
    ITS_C_REQUIRE(msgFileName != NULL);

    strcpy(buf, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\");
    strcat(buf, srcName);

    result = RegCreateKey(HKEY_LOCAL_MACHINE, buf, &hKey);

    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    /* Add the supported types to the subkey. */
    supportedTypes = EVENTLOG_ERROR_TYPE       |
                     EVENTLOG_WARNING_TYPE     |
                     EVENTLOG_INFORMATION_TYPE |
                     EVENTLOG_AUDIT_SUCCESS    |
                     EVENTLOG_AUDIT_FAILURE;

    result = RegSetValueEx(hKey,
                           "TypesSupported",
                           0,
                           REG_DWORD,
                           (LPBYTE)&supportedTypes,
                           sizeof(DWORD));
    
    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    /* Add the Event ID message file name to the subkey. */

    strcpy(buf, "%SystemRoot%\\System32\\");
    strcat(buf, msgFileName);

    result = RegSetValueEx(hKey,
                           "EventMessageFile",
                           0,
                           REG_EXPAND_SZ,
                           (LPBYTE)buf,
                           strlen(buf));

    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    result = RegCloseKey(hKey);

    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    return result;
}

/*.implementation:extern
 ***************************************************************************
 *
 *  Purpose:
 *      Remove an event source from the NT Registry.
 *
 *  Input Parameters:
 *      srcName - name of the source to remove.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      long - ERROR_SUCCESS if call is successful or an NT error code.
 *
 *  Notes:
 *      Should be called by the installation procedure.
 *
 *  See Also:
 *
 ***************************************************************************/
ITSDLLAPI long 
NT_RegistryRemoveSource(const char *srcName)
{
    long result = ERROR_SUCCESS;
    char buf[256];
    HKEY hParentKey;

    ITS_C_REQUIRE(srcName != NULL);

    strcpy(buf, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application");

    result = RegOpenKey(HKEY_LOCAL_MACHINE, buf, &hParentKey);

    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    result = RegDeleteKey(hParentKey, srcName);

    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    result = RegCloseKey(hParentKey);

    if (result != ERROR_SUCCESS)
    {
        return result;
    }

    return result;
}

/*.implementation:static
 ***************************************************************************
 *
 *  Purpose:
 *      Log an event to the NT Event Log Application log file.
 *
 *  Input Parameters:
 *      text - text of the event to be logged.
 *      type - type of the event to be logged (see notes below).
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
 *      The mapping from generic (portable) event types to NT event types is
 *      the following:
 *
 *          LOG_EMERGENCY_TYPE      --> EVENTLOG_ERROR_TYPE
 *          LOG_ALERT_TYPE          --> EVENTLOG_ERROR_TYPE
 *          LOG_CRITICAL_TYPE       --> EVENTLOG_ERROR_TYPE
 *          LOG_ERROR_TYPE          --> EVENTLOG_ERROR_TYPE
 *          LOG_WARNING_TYPE        --> EVENTLOG_WARNING_TYPE
 *          LOG_NOTICE_TYPE         --> EVENTLOG_INFORMATION_TYPE
 *          LOG_INFORMATION_TYPE    --> EVENTLOG_INFORMATION_TYPE
 *          LOG_SUCCESS_AUDIT_TYPE  --> EVENTLOG_AUDIT_SUCCESS
 *          LOG_FAILURE_AUDIT_TYPE  --> EVENTLOG_AUDIT_FAILURE
 *
 *      Success assumed by default.
 *          
 *  See Also:
 *
 ***************************************************************************/
static void
NT_Log(EVENTLOG_Manager* log, ITS_EventType type, const char *string)
{
    /* Mapping from generic (portable) event types to NT event types. */
    WORD ntType;
    unsigned i, j;
    char buf[512], current, previous;
    char *strings[1] = { buf };
    HANDLE eventSource;

    ITS_C_REQUIRE(log != NULL);
    ITS_C_REQUIRE(string != NULL);

    switch(type)
    {
    case LOG_EMERGENCY_TYPE:
    case LOG_ALERT_TYPE:
    case LOG_CRITICAL_TYPE:
    case LOG_ERROR_TYPE:
        ntType = EVENTLOG_ERROR_TYPE;
        break;
    case LOG_WARNING_TYPE:
        ntType = EVENTLOG_WARNING_TYPE;
        break;
    case LOG_NOTICE_TYPE:
    case LOG_INFORMATION_TYPE:
        ntType = EVENTLOG_INFORMATION_TYPE;
        break;
    case LOG_SUCCESS_AUDIT_TYPE:
        ntType = EVENTLOG_AUDIT_SUCCESS;
        break;
    case LOG_FAILURE_AUDIT_TYPE:
        ntType = EVENTLOG_AUDIT_FAILURE;
        break;
    default:
        ntType = EVENTLOG_ERROR_TYPE;
        break;
    }


    /* NT Event Log Viewer requires '\r' and '\n' to display a new line. */
    previous   = '\0';
    current    = '\0';

    for (i = 0, j= 0; i < strlen(string); i++, j++)
    {
        current = string[i];

        if (current == '\n' && previous != '\r')
        {
            buf[j] = '\r';
            j++;
        }

        buf[j] = current;

        previous = current;
    }

    buf[j] = 0;

    /* Get an event source handle and write to the NT Event Log. */

    eventSource = RegisterEventSource(NULL, EVENTLOG_SRC_NAME(log));

    if (eventSource != NULL)
    {
        ReportEvent(eventSource,
                    ntType,
                    0,
                    type,
                    NULL,
                    1,
                    0,
                    strings,
                    NULL);

        DeregisterEventSource(eventSource);
    }
}

/*.implementation:static
 ***************************************************************************
 *
 *  Purpose:
 *      Create an NT event log
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
 *
 ***************************************************************************/
static int
NT_Create(ITS_Object obj, va_list args)
{
    const char *name;

    ITS_TRACE_DEBUG(("Create:\n"));

    name = va_arg(args, char *);

    EVENTLOG_SRC_NAME(obj) = strdup(name);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ***************************************************************************
 *
 *  Purpose:
 *      Delete an NT event log
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
 *
 ***************************************************************************/
static void
NT_Delete(ITS_Object obj)
{
    if (EVENTLOG_SRC_NAME(obj))
    {
        free(EVENTLOG_SRC_NAME(obj));
    }
}

/*
 * the class record
 */
ITSDLLAPI EVENTLOG_ClassRec itsNT_EVENTLOG_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,          /* CORE is superclass */
        sizeof(EVENTLOG_Manager),   /* sizeof instance */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial refCount */
        EVENTLOG_NT_CLASSNAME,      /* class name */
        ITS_CLASS_NO_INIT,          /* class initialize */
        ITS_CLASS_NO_DEST,          /* class destroy */
        ITS_CLASS_PART_NO_INIT,     /* class initialize part */
        ITS_CLASS_PART_NO_DEST,     /* class destroy part */
        NT_Create,                  /* instantiate */
        NT_Delete,                  /* destroy */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no extension of interest */
    },
    /* eventlog part */
    {
        NT_Log
    }
};

ITSDLLAPI ITS_Class itsNT_EVENTLOG_Class = (ITS_Class)&itsNT_EVENTLOG_ClassRec;

#undef EVENTLOG_CreateLog

/*.implementation:extern
 ***************************************************************************
 *
 *  Purpose:
 *      Create a NT event log
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
 *
 ***************************************************************************/
ITSDLLAPI EVENTLOG_Manager *
EVENTLOG_CreateLog(const char *name)
{
    return (EVENTLOG_Manager *)
                ITS_ConstructObject(itsNT_EVENTLOG_Class,
                                    name);
}

#endif /* defined(WIN32) */


/*
 * Unix specific code.
 */

#if defined(unix)

/*.implementation:static
 ***************************************************************************
 *
 *  Purpose:
 *      Log an event to the NT Event Log Application log file.
 *
 *  Input Parameters:
 *      text - text of the event to be logged.
 *      type - type of the event to be logged (see notes below).
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
 *      The mapping from generic (portable) event types to NT event types is
 *      the following:
 *
 *          LOG_EMERGENCY_TYPE      --> EVENTLOG_ERROR_TYPE
 *          LOG_ALERT_TYPE          --> EVENTLOG_ERROR_TYPE
 *          LOG_CRITICAL_TYPE       --> EVENTLOG_ERROR_TYPE
 *          LOG_ERROR_TYPE          --> EVENTLOG_ERROR_TYPE
 *          LOG_WARNING_TYPE        --> EVENTLOG_WARNING_TYPE
 *          LOG_NOTICE_TYPE         --> EVENTLOG_INFORMATION_TYPE
 *          LOG_INFORMATION_TYPE    --> EVENTLOG_INFORMATION_TYPE
 *          LOG_SUCCESS_AUDIT_TYPE  --> EVENTLOG_AUDIT_SUCCESS
 *          LOG_FAILURE_AUDIT_TYPE  --> EVENTLOG_AUDIT_FAILURE
 *
 *      Success assumed by default.
 *          
 *  See Also:
 *
 ***************************************************************************/
static void 
UNIX_Log(EVENTLOG_Manager *log, ITS_EventType type, const char *text)
{
    /* Mapping from generic (portable) event types to syslog event types. */
    int lType;

    ITS_C_REQUIRE(log != NULL);
    ITS_C_REQUIRE(text != NULL);

    switch(type)
    {
    case LOG_EMERGENCY_TYPE:
        lType = LOG_EMERG;
        break;

    case LOG_ALERT_TYPE:
        lType = LOG_ALERT;
        break;

    case LOG_CRITICAL_TYPE:
        lType = LOG_CRIT;
        break;

    case LOG_ERROR_TYPE:
        lType = LOG_ERR;
        break;
    case LOG_WARNING_TYPE:
        lType = LOG_WARNING;
        break;

    case LOG_NOTICE_TYPE:
        lType = LOG_NOTICE;
        break;

    case LOG_INFORMATION_TYPE:
        lType = LOG_INFO;
        break;

    case LOG_SUCCESS_AUDIT_TYPE:
    case LOG_FAILURE_AUDIT_TYPE:
    default:
        lType = LOG_DEBUG;
        break;
    }

    /* log it. */
    syslog(lType, text);
}

/*
 * only open and close the log once.
 */
static int created = 0;

/*.implementation:static
 ***************************************************************************
 *
 *  Purpose:
 *      Create a UNIX event log
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
 *
 ***************************************************************************/
static int
UNIX_Create(ITS_Object obj, va_list args)
{
    const char *name;

    ITS_TRACE_DEBUG(("Create:\n"));

    name = va_arg(args, char *);

    EVENTLOG_SRC_NAME(obj) = strdup(name);

    if (!created)
    {
        openlog(name, LOG_PID, LOG_DAEMON);
    }

    created++;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ***************************************************************************
 *
 *  Purpose:
 *      Delete a UNIX event log
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
 *
 ***************************************************************************/
static void
UNIX_Delete(ITS_Object obj)
{
    created--;

    if (!created)
    {
        closelog();
    }
}

/*
 * the class record
 */
ITSDLLAPI EVENTLOG_ClassRec itsUNIX_EVENTLOG_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,          /* CORE is superclass */
        sizeof(EVENTLOG_Manager),   /* sizeof instance */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial refCount */
        EVENTLOG_UNIX_CLASSNAME,    /* class name */
        ITS_CLASS_NO_INIT,          /* class initialize */
        ITS_CLASS_NO_DEST,          /* class destroy */
        ITS_CLASS_PART_NO_INIT,     /* class initialize part */
        ITS_CLASS_PART_NO_DEST,     /* class destroy part */
        UNIX_Create,                /* instantiate */
        UNIX_Delete,                /* destroy */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no extension of interest */
    },
    /* eventlog part */
    {
        UNIX_Log
    }
};

ITSDLLAPI ITS_Class itsUNIX_EVENTLOG_Class = (ITS_Class)&itsUNIX_EVENTLOG_ClassRec;

#undef EVENTLOG_CreateLog

/*.implementation:extern
 ***************************************************************************
 *
 *  Purpose:
 *      Create a UNIX event log
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
 *
 ***************************************************************************/
ITSDLLAPI EVENTLOG_Manager *
EVENTLOG_CreateLog(const char *name)
{
    return (EVENTLOG_Manager *)
                ITS_ConstructObject(itsUNIX_EVENTLOG_Class,
                                    name);
}

#endif /* defined(unix) */

#undef EVENTLOG_DestroyLog
#undef EVENTLOG_Log

/*.implementation:extern
 ***************************************************************************
 *
 *  Purpose:
 *      Delete an event log
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
 *
 ***************************************************************************/
ITSDLLAPI void
EVENTLOG_DestroyLog(EVENTLOG_Manager *log)
{
    ITS_DestructObject((ITS_Object)(log));
}

/*.implementation:extern
 ***************************************************************************
 *
 *  Purpose:
 *      Log an event to the NT Event Log Application log file.
 *
 *  Input Parameters:
 *      text - text of the event to be logged.
 *      type - type of the event to be logged (see notes below).
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
 *      The mapping from generic (portable) event types to NT event types is
 *      the following:
 *
 *          LOG_EMERGENCY_TYPE      --> EVENTLOG_ERROR_TYPE
 *          LOG_ALERT_TYPE          --> EVENTLOG_ERROR_TYPE
 *          LOG_CRITICAL_TYPE       --> EVENTLOG_ERROR_TYPE
 *          LOG_ERROR_TYPE          --> EVENTLOG_ERROR_TYPE
 *          LOG_WARNING_TYPE        --> EVENTLOG_WARNING_TYPE
 *          LOG_NOTICE_TYPE         --> EVENTLOG_INFORMATION_TYPE
 *          LOG_INFORMATION_TYPE    --> EVENTLOG_INFORMATION_TYPE
 *          LOG_SUCCESS_AUDIT_TYPE  --> EVENTLOG_AUDIT_SUCCESS
 *          LOG_FAILURE_AUDIT_TYPE  --> EVENTLOG_AUDIT_FAILURE
 *
 *      Success assumed by default.
 *          
 *  See Also:
 *
 ***************************************************************************/
ITSDLLAPI void
EVENTLOG_Log(EVENTLOG_Manager *log,
             ITS_EventType type, const char *string)
{
    EVENTLOG_CLASS_LOG(ITS_OBJ_CLASS(log))(log, type, string);
}


