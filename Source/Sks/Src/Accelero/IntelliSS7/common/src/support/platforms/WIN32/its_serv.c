/******************************************************************************
 *                                                                            *
 *      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:30  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/01 15:46:23  mmiers
 * LOG: Add priority setting
 * LOG:
 * LOG: Revision 6.3  2002/04/30 19:15:26  hdivoux
 * LOG: Don't invoke the unexpected exit handler if the service is stopped.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/05/04 18:30:28  mmiers
 * LOG: Move these back.  Support can't be dynamically loaded due to
 * LOG: WIN32.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.11  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 3.10  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.4  2001/01/25 16:17:26  mmiers
 * LOG: Missed handler
 * LOG:
 * LOG: Revision 3.3  2001/01/19 22:47:46  mmiers
 * LOG: cleanup
 * LOG:
 * LOG: Revision 3.2  2001/01/18 18:46:28  mmiers
 * LOG: CPP service based on C service.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:52  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/06/13 19:27:10  mmiers
 * LOG:
 * LOG: Return path without return code.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:20  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:01  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.9  1999/10/12 18:34:46  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with non-zero code.
 * LOG:
 * LOG: Revision 1.8  1999/08/23 19:39:19  labuser
 * LOG:
 * LOG:
 * LOG: Don't define BUFSIZ if we don't use it.
 * LOG:
 * LOG: Revision 1.7  1999/08/23 01:25:48  mmiers
 * LOG:
 * LOG:
 * LOG: Correct function linkage.
 * LOG:
 * LOG: Revision 1.6  1999/08/22 01:20:09  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a bunch of service logic code, add interrogate handlers for UNIX,
 * LOG: add a way for the user to call handlers (C).
 * LOG:
 * LOG: Revision 1.5  1999/08/18 16:19:47  mmiers
 * LOG:
 * LOG:
 * LOG: Add in comments.
 * LOG:
 * LOG: Revision 1.4  1999/08/18 14:07:44  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build on NT.
 * LOG:
 * LOG: Revision 1.3  1999/08/18 02:34:28  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks to UNIX services and NT services.  Tomorrow will tell.
 * LOG:
 * LOG: Revision 1.2  1999/08/18 01:00:03  mmiers
 * LOG:
 * LOG:
 * LOG: More work on C services.
 * LOG:
 * LOG: Revision 1.1  1999/08/17 23:48:42  mmiers
 * LOG:
 * LOG:
 * LOG: Fooling around with C based services.
 * LOG:
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_trace.h>
#include <its_service.h>
#include <its_license.h>

#ident "$Id: its_serv.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

/*
 * local data
 */
static char *dependencies = NULL;

/*
 * handlers
 */
extern void (*SERVICE_InitFunc)(int argc, char **argv);
extern void (*SERVICE_MainFunc)(void);
extern void (*SERVICE_TermFunc)(void);

SERVICE_Handler handlers[SERV_HANDLER_MAX_HANDLERS] =
{
    SERVICE_DefaultStopHandler,
    SERVICE_DefaultPauseHandler,
    SERVICE_DefaultContinueHandler,
    SERVICE_DefaultShutdownHandler,
    SERVICE_DefaultInterrogateHandler,
    SERVICE_DefaultInterruptHandler,
    SERVICE_DefaultUnexpectedExitHandler
};

ITSDLLAPI const char * SERVICE_InternalName = NULL;
ITSDLLAPI const char * SERVICE_DisplayedName = NULL;
ITSDLLAPI EVENTLOG_Manager *SERVICE_EventLog = NULL;

static BOOL SERVICE_DefaultControlHandler(DWORD);
static void SERVICE_DefaultSignalHandler(DWORD controlCode);

static BOOL (*SERVICE_ControlHandler)(DWORD ctrlType) = SERVICE_DefaultControlHandler;
static void (*SERVICE_SignalHandler)(DWORD controlCode) = SERVICE_DefaultSignalHandler;
static DWORD SERVICE_CurrentState = 0;
static DWORD SERVICE_WaitHint = 0;

static DWORD                 checkPoint;
static SERVICE_STATUS        status;
static SERVICE_STATUS_HANDLE statusHandle;
static HANDLE                stopEventHandle;
static DWORD                 ctrlType;
static void                  ServiceMain(int argc, const char** argv);
static void  WINAPI          _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
static void  WINAPI          _Handler(DWORD fdwControl);
static BOOL  WINAPI          _ControlHandler(DWORD dwControlType);
static void                  _OnExitHandler(void);
static DWORD                 controlsAccepted = SERVICE_ACCEPT_STOP;

ITSDLLAPI HANDLE
SERVICE_GetStopEventHandle()
{
    return stopEventHandle;
}

ITSDLLAPI SERVICE_STATUS
SERVICE_GetStatus()
{
    return (status);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the service subsystem.
 *
 *  Input Parameters:
 *      displayedName - the user friendly name of this application
 *      internalName - the name this application is known as by the OS.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCES - success.  Any other value indicates an IntelliSS7
 *      processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SERVICE_Initialize(const char *displayedName,
                   const char *internalName,
                   EVENTLOG_Manager *eventLog)
{
    SERVICE_InternalName = internalName;
    SERVICE_DisplayedName = displayedName;
    SERVICE_EventLog = eventLog;

    checkPoint = 1;
    statusHandle = 0;
    stopEventHandle = NULL;
    controlsAccepted = SERVICE_ACCEPT_STOP;

    SERVICE_SetExitCode(NO_ERROR);

    /*
     * Setup the initial service status.
     */
    status.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
    status.dwCurrentState            = SERVICE_STOPPED;
    status.dwControlsAccepted        = controlsAccepted;
    status.dwWin32ExitCode           = 0;
    status.dwServiceSpecificExitCode = 0;
    status.dwCheckPoint              = 0;
    status.dwWaitHint                = 0;

    /*
     * Create the stop event.
     *   NULL,    - No security attributes.
     *   TRUE,    - Manual reset event.
     *   FALSE,   - Not signaled.
     *   NULL);   - Unnamed.
     */
    stopEventHandle = CreateEvent(NULL, TRUE,
                                  FALSE, NULL);

    if (stopEventHandle == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    atexit(_OnExitHandler);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the service.  If the user wishes a graceful shutdown,
 *      they may call this after RunAsService() or RunAsConsoleApplication()
 *      returns.
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
ITSDLLAPI void
SERVICE_Terminate()
{
    if (stopEventHandle)
    {
        BOOL bRes = CloseHandle(stopEventHandle);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Run this process as a service.  The behavior of this function is
 *      OS dependent.  On NT, this attempts to cue the SCM to start the
 *      already registered service.  On UNIX systems, this forks the
 *      service off as a daemon process.
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
ITSDLLAPI void
SERVICE_RunAsService()
{
    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { (char *)SERVICE_InternalName, _ServiceMain },
        { NULL, NULL }
    };

    SERVICE_SetType(ST_SERVICE);

    /*
     * Blocks until service is stopped.
     */
    StartServiceCtrlDispatcher(dispatchTable);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Run the process as a foreground application.
 *
 *  Input Parameters:
 *      argc - the command line argument count
 *      argv - the command line arguments.  Size of array is argc.
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
ITSDLLAPI void
SERVICE_RunAsConsoleApplication(int argc, const char** argv)
{
    SERVICE_SetType(ST_CONSOLE_APPLICATION);

    SetConsoleCtrlHandler(_ControlHandler, TRUE);

    printf("%s: running as a console application.\n", SERVICE_DisplayedName);

    SERVICE_Run(argc, argv);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the OS priority of the process
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
ITSDLLAPI int
SERVICE_SetPriority(ITS_UINT priority)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Install the service.  On UNIX, this is a NOOP.
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
ITSDLLAPI int
SERVICE_Install()
{
    SC_HANDLE hService = NULL;
    SC_HANDLE hSCM     = NULL;
    char path[ITS_PATH_MAX];

    DWORD resLength = GetModuleFileName(NULL, path, ITS_PATH_MAX);

    if (resLength == 0)
    {
        return (ITS_EINVALIDARGS);
    }


    hSCM = OpenSCManager(NULL, /* Machine (NULL == local). */
                         NULL, /* Database (NULL == default). */
                         SC_MANAGER_ALL_ACCESS); /* Access required. */

    if (hSCM == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    hService = CreateService(hSCM,                      /* SCM. */
                             SERVICE_InternalName,      /* Service name. */
                             SERVICE_DisplayedName,     /* Service displayed name. */
                             SERVICE_ALL_ACCESS,        /* Desired access. */
                             SERVICE_WIN32_OWN_PROCESS, /* Service type. */
                             SERVICE_DEMAND_START,      /* Start type. */
                             SERVICE_ERROR_NORMAL,      /* Error control type. */
                             path,                      /* Service's binary. */
                             NULL,                      /* No load ordering group. */
                             NULL,                      /* No tag identifier. */
                             SERVICE_GetDependencies(), /* Dependencies. */
                             NULL,                      /* LocalSystem account. */
                             NULL);                     /* No password. */


    if (hService == NULL)
    {
        CloseServiceHandle(hSCM);

        return (ITS_EINVALIDARGS);
    }

    // Service has been successfully installed.

    printf("%s: service installed.\n", SERVICE_DisplayedName);

    CloseServiceHandle(hService);

    CloseServiceHandle(hSCM);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove the service.  On UNIX, this is a NOOP.
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
ITSDLLAPI int
SERVICE_Remove()
{
    SC_HANDLE hService = NULL;
    SC_HANDLE hSCM     = NULL;
    BOOL bRes;

    hSCM = OpenSCManager(NULL,                   /* Machine (NULL == local). */
                         NULL,                   /* Database (NULL == default). */
                         SC_MANAGER_ALL_ACCESS); /* Access required. */

    if (hSCM == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    hService = OpenService(hSCM,                 /* SCM. */
                           SERVICE_InternalName, /* Service name. */
                           SERVICE_ALL_ACCESS);  /* Desired access. */

    if (hService == NULL)
    {
        CloseServiceHandle(hSCM);

        return (ITS_EINVALIDARGS);
    }

    /*
     * Try to stop the service (if it is currently running).
     */
    bRes = ControlService(hService, SERVICE_CONTROL_STOP, &status);

    if (bRes)
    {
        Sleep(500);    // 0.5s.

        while(QueryServiceStatus(hService, &status))
        {
            if (status.dwCurrentState == SERVICE_STOP_PENDING)
            {
                printf(".");

                Sleep(500);    // 0.5s.
            }
            else
            {
                printf("\n");

                break;
            }
        }

        if (status.dwCurrentState == SERVICE_STOPPED)
        {
            printf("%s: service stopped.", SERVICE_DisplayedName);
        }
        else
        {
            CloseServiceHandle(hService);

            CloseServiceHandle(hSCM);

            return (ITS_EINVALIDARGS);
        }
    }

    bRes = DeleteService(hService);

    if (!bRes)
    {
        CloseServiceHandle(hService);

        CloseServiceHandle(hSCM);

        return (ITS_EINVALIDARGS);
    }


    /*
     * Service has been successfully removed.
     */
    printf("%s: service removed.", SERVICE_DisplayedName);

    CloseServiceHandle(hService);

    CloseServiceHandle(hSCM);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the SCM commands accepted by this application.  This function
 *      is NT specific.
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
 *      By default, only the controls accepted are SERVICE_ACCEPT_STOP.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SERVICE_SetControlsAccepted(DWORD controlsAcceptedParam)
{
    controlsAccepted |= controlsAcceptedParam;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the names of the services this service is dependent on.
 *      This function is NT specific.
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
ITSDLLAPI void
SERVICE_SetDependencies(const char *deps)
{
    if (dependencies)
    {
        free(dependencies);
    }

    dependencies = strdup(deps);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the service names this service is dependent on.  This function
 *      is NT specific.
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
ITSDLLAPI const char*
SERVICE_GetDependencies()
{
    return (dependencies);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function really provides the "main" for a process.  The
 *      main thread (whether started by the SCM on NT, or the daemon
 *      main on UNIX) executes this function via RunAsService() or
 *      RunAsConsoleApplication().  The InitFunction (if registered)
 *      is called, then the MainFunction (if registered) is called until
 *      the application receives a termination signal or control; finally
 *      the TermFunction (if registered) is called.
 *
 *  Input Parameters:
 *      argc - the command line argument count
 *      argv - the command line arguments.  Size of array is argc.
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
 *      The main function should do some delay or sleep to keep from
 *      thrashing the CPU.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SERVICE_Run(int argc, const char** argv)
{
    if (SERVICE_GetType() == ST_SERVICE)
    {
        /*
         * To tell the SCM that the service is now started.
         */
        SERVICE_SetStatus(SERVICE_RUNNING, 0);
    }

    if (SERVICE_InitFunc)
    {
        (*SERVICE_InitFunc)(argc, (char **)argv);
    }

    if (!SERVICE_IsStopped())
    {
        while (1)
        {
            DWORD res;

            if (SERVICE_MainFunc)
            {
                (*SERVICE_MainFunc)();
            }

            res = WaitForSingleObject(stopEventHandle,  /* Handle. */
                                      0);               /* Just test if signaled. */

            if (res == WAIT_OBJECT_0)
            {
                BOOL bRes = ResetEvent(stopEventHandle);

                if (!bRes)
                {
                    return (ITS_EINVALIDARGS);
                }

                break;
            }
            else if (res == WAIT_TIMEOUT)
            { 
                continue;
            }
            else if (res == WAIT_FAILED)
            {
                return (ITS_EINVALIDARGS);
            }
            else
            {
                continue;
            }
        }
    }

    if (SERVICE_TermFunc)
    {
        (*SERVICE_TermFunc)();
    }

    if (SERVICE_GetType() == ST_SERVICE)
    {
        /*
         * To tell the SCM that the service is now stopped.
         */
        SERVICE_SetStatus(SERVICE_STOPPED, 0);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Let the user override the default control handler.
 *
 *  Input Parameters:
 *      ControlHandler - the replacement control handler
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
 *      See the DefaultControlHandler for a list of controls handled.
 *      This (and the SignalHandler) have somewhat misleading names.
 *      On NT, the SignalHandler handles command requests from the SCM.
 *      On UNIX, the SignalHandler handles signals normally not expected
 *      from the console (e.g., SIGTERM, SIGPAUSE, etc).
 *      On UNIX, the ControlHandler handles SIGINT (i.e., Ctrl-C from the
 *      console.
 *      On NT, the ControlHandler handles Ctrl-C and Ctrl-Break from the
 *      console.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SERVICE_SetControlHandler(BOOL (*ControlHandler)(DWORD ctrlType))
{
    SERVICE_ControlHandler = ControlHandler;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Let the user override the default signal handler.
 *
 *  Input Parameters:
 *      Handler - the replacement handler.
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
 *      This (and the ControlHandler) have somewhat misleading names.
 *      On NT, the SignalHandler handles command requests from the SCM.
 *      On UNIX, the SignalHandler handles signals normally not expected
 *      from the console (e.g., SIGTERM, SIGPAUSE, etc).
 *      On UNIX, the ControlHandler handles SIGINT (i.e., Ctrl-C from the
 *      console.
 *      On NT, the ControlHandler handles Ctrl-C and Ctrl-Break from the
 *      console.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SERVICE_SetSignalHandler(void (*Handler)(DWORD controlCode))
{
    SERVICE_SignalHandler = Handler;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows the user to set the current service status
 *      with the SCM.  This function is NT specific.
 *
 *  Input Parameters:
 *      currentState - the new state of the service
 *      waitHint - an indication of the wait for SCM
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
ITSDLLAPI void
SERVICE_SetStatus(DWORD currentState, DWORD waitHint)
{
    char *traceCurrentState = NULL;

    switch (currentState)
    {
    case SERVICE_STOPPED:
        traceCurrentState = "SERVICE_STOPPED";
        break;

    case SERVICE_START_PENDING:
        traceCurrentState = "SERVICE_START_PENDING";            
        break;

    case SERVICE_STOP_PENDING:
        traceCurrentState = "SERVICE_STOP_PENDING";
        break;

    case SERVICE_RUNNING:
        traceCurrentState = "SERVICE_RUNNING";
        break;

    case SERVICE_CONTINUE_PENDING:
        traceCurrentState = "SERVICE_CONTINUE_PENDING";
        break;

    case SERVICE_PAUSE_PENDING:
        traceCurrentState = "SERVICE_PAUSE_PENDING";
        break;

    case SERVICE_PAUSED:
        traceCurrentState = "SERVICE_PAUSED";
        break;

    default:
        break;
    }

    /*
     * Nothing should be reported to the SCM if console application.
     */
    if (SERVICE_GetType() == ST_SERVICE)
    {
        if (currentState == SERVICE_START_PENDING)
        {
            status.dwControlsAccepted = 0;
        }
        else
        {
            status.dwControlsAccepted = controlsAccepted;
        }

        status.dwCurrentState = currentState;
        status.dwWin32ExitCode = SERVICE_GetExitCode();
        status.dwWaitHint = waitHint;

        if (currentState == SERVICE_RUNNING || 
            currentState == SERVICE_STOPPED)
        {
            status.dwCheckPoint = 0;
        }
        else
        {
            status.dwCheckPoint = checkPoint++;
        }

        /*
         * Report the status of the service to the SCM.
         */
    	SetServiceStatus(statusHandle, &status);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default signal handler for NT.  This function will call
 *      the user registered (or default) handler for each control code.
 *
 *  Input Parameters:
 *      controlCode - the control code issued by the SCM.
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
 *      The default handler handles:
 *          SERVICE_CONTROL_STOP (StopHandler)
 *          SERVICE_CONTORL_PAUSE (PauseHandler)
 *          SERVICE_CONTROL_CONTINUE (ContinueHandler)
 *          SERVICE_CONTROL_INTERROGATE (InterrogateHandler)
 *          SERVICE_CONTROL_SHUTDOWN (ShutdownHandler)
 *
 *  See Also:
 ****************************************************************************/
static void
SERVICE_DefaultSignalHandler(DWORD controlCode)
{
    switch (controlCode)
    {
    case SERVICE_CONTROL_STOP:
        // Must be reported before to avoid a race condition.
        SERVICE_SetStatus(SERVICE_STOP_PENDING, 5000);
        if (handlers[SERV_HANDLER_STOP])
        {
            ITS_TRACE_CRITICAL(("SERVICE_CONTROL_STOP, Signal caught\n"));
            (*handlers[SERV_HANDLER_STOP])();
        }
	break;

    case SERVICE_CONTROL_PAUSE:
        SERVICE_SetStatus(SERVICE_PAUSE_PENDING, 5000);
        if (handlers[SERV_HANDLER_PAUSE])
        {
            ITS_TRACE_CRITICAL(("SERVICE_CONTROL_PAUSE, Signal caught\n"));
            (*handlers[SERV_HANDLER_PAUSE])();
        }
	break;

    case SERVICE_CONTROL_CONTINUE:
        SERVICE_SetStatus(SERVICE_CONTINUE_PENDING, 5000);
        if (handlers[SERV_HANDLER_CONTINUE])
        {
            ITS_TRACE_CRITICAL(("SERVICE_CONTROL_CONTINUE, Signal caught\n"));
            (*handlers[SERV_HANDLER_CONTINUE])();
        }
	break;

    case SERVICE_CONTROL_INTERROGATE:
        if (handlers[SERV_HANDLER_INTERROGATE])
        {
            ITS_TRACE_CRITICAL(("SERVICE_CONTROL_INTERROGATE, Signal caught\n"));
            (*handlers[SERV_HANDLER_INTERROGATE])();
        }
	break;

    case SERVICE_CONTROL_SHUTDOWN:
        if (handlers[SERV_HANDLER_SHUTDOWN])
        {
            ITS_TRACE_CRITICAL(("SERVICE_CONTROL_SHUTDOWN, Signal caught\n"));
            (*handlers[SERV_HANDLER_SHUTDOWN])();
        }
	break;

    default:
        break;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default stop handler.
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
 *      This function is responsible for terminating the loop around
 *      the MainFunction() in SERVICE_Run().
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SERVICE_DefaultStopHandler()
{
    BOOL bRes = SetEvent(stopEventHandle);   
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default pause handler
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
 *      On NT, this function updates the service status
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultPauseHandler()
{
    SERVICE_SetStatus(SERVICE_PAUSED, 0);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default continue handler
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
 *      On NT, this function updates the service status.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultContinueHandler()
{
    SERVICE_SetStatus(SERVICE_RUNNING, 0);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The defualt interrogate handler.
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
 *      On NT, this is a NOOP.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultInterrogateHandler()
{
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default shutdown handler.
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
 *      This function is a NOOP.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultShutdownHandler()
{
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default interrupt handler
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
 *      This function can also signal SERVICE_Run() to terminate the
 *      loop around the MainFunction.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultInterruptHandler()
{
    BOOL bRes;

    bRes = SetEvent(stopEventHandle);   
    if (bRes)
    {
        SERVICE_SetStopped();
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default interrupt handler
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
 *      This function can also signal SERVICE_Run() to terminate the
 *      loop around the MainFunction.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SERVICE_DefaultUnexpectedExitHandler()
{
    if (!SERVICE_IsStopped())
    {
        if (!LICENSE_Exiting())
        {
            ITS_TRACE_CRITICAL(("License Failure\n"));
            abort();
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default control handler.  This function accepts a control
 *      key indication from the console.
 *
 *  Input Parameters:
 *      ctrlType = the control key hit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      FALSE to continue
 *      TRUE to terminate
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static BOOL 
SERVICE_DefaultControlHandler(DWORD ctrlType)
{
    switch(ctrlType)
    {
    case CTRL_BREAK_EVENT:  
    case CTRL_C_EVENT:      
        if (handlers[SERV_HANDLER_INTERRUPT])
        {
            (*handlers[SERV_HANDLER_INTERRUPT])();
        }
        break;
    }

    if (SERVICE_IsStopped())
    {
        return (TRUE);    
    }

    return (FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      ServiceMain.  This function (NT specific) registers the static
 *      handler for SCM controls, and runs the service.
 *
 *  Input Parameters:
 *      argc - the command line argument count
 *      argv - the command line arguments.  Size of array is argc.
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
void
ServiceMain(int argc, const char** argv)
{
    /*
     * To register _Handler to handle the service control requests.
     */
    statusHandle = RegisterServiceCtrlHandler(SERVICE_InternalName,
                                              _Handler);

    if (statusHandle == 0)
    {
        return;
    }

    SERVICE_SetStatus(SERVICE_START_PENDING, 5000);

    status.dwWin32ExitCode = 0;
    status.dwCheckPoint    = 0;
    status.dwWaitHint      = 0;

    /*
     * The service has stopped when the Run function return.
     */

    SERVICE_Run(argc, argv);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      _ServiceMain.  This function (NT specific) is the service entry
 *      point registered with the SCM.
 *
 *  Input Parameters:
 *      argc - the command line argument count
 *      argv - the command line arguments.  Size of array is argc.
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
void WINAPI 
_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    ServiceMain(dwArgc, lpszArgv);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function provides an always-present signal handler.  It calls
 *      the user defined (or default) signal handler, if present.
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
static void WINAPI 
_Handler(DWORD fdwControl)
{
    ITS_TRACE_CRITICAL(("SignalHandler caught\n"));

    if (SERVICE_SignalHandler)
    {
        (*SERVICE_SignalHandler)(fdwControl);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function provides an always-present control handler.  It calls
 *      the user defined (or default) control handler, if present.
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
static BOOL WINAPI
_ControlHandler(DWORD dwCtrlType)
{
    ITS_TRACE_CRITICAL(("ControlHandler caught\n"));

    if (SERVICE_ControlHandler)
    {
        return (*SERVICE_ControlHandler)(dwCtrlType);
    }

    return (FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function provides an always-present signal handler.  It calls
 *      the user registered (or default) signal handler, if present.
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
static void
_OnExitHandler()
{
    ITS_TRACE_CRITICAL(("OnExitHandler called: stopEvent %d\n",
                     SERVICE_IsStopped()));

    if (!SERVICE_IsStopped())
    {
        SERVICE_CallHandler(SERV_HANDLER_UNEXPECTED_EXIT);
    }
}

#if defined(SERVICE_TEST)

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Testing vehicle.
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
int 
main(int argc, const char** argv)
{
    if (SERVICE_Initialize("Test Service", "Test_Service") != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to initialize the service\n");

        exit(EXIT_FAILURE);
    }

    /*
     * The following line would be required to allow the
     * service to accept pause and continue requests.
     *
     * service.SetControlsAccepted(SERVICE_ACCEPT_PAUSE_CONTINUE);
     */

    /*
     * Process the command line.
     */
    SERVICE_ProcessCommandLine(argc, argv);

    /*
     * run in whichever mode is correct
     */
    if (SERVICE_GetType() == ST_SERVICE)
    {
        SERVICE_RunAsService();
    }
    else if (SERVICE_GetType() == ST_CONSOLE_APPLICATION)
    {
        SERVICE_RunAsConsoleApplication(argc, argv);
    }
    else if (SERVICE_GetType() == ST_NOT_SET)
    {
        SERVICE_SetType(ST_SERVICE);

        SERVICE_RunAsService();
    }

    SERVICE_Terminate();

    return SERVICE_GetExitCode();
}

#endif /* SERVICE_TEST */


