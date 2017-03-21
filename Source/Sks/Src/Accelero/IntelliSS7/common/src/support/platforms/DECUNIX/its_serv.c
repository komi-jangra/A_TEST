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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:05  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/01 15:46:23  mmiers
 * LOG: Add priority setting
 * LOG:
 * LOG: Revision 6.3  2002/04/30 19:22:02  mmiers
 * LOG: Don't call UnexpectedExit if the service is already stopped.
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
 * LOG: Revision 3.11  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.10  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 3.9  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 3.8  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.7  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 18:46:28  mmiers
 * LOG: CPP service based on C service.
 * LOG:
 * LOG: Revision 3.2  2000/09/07 17:13:38  labuser
 * LOG:
 * LOG: Fix check for return value from fork() call.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:50  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:12  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:59  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.10  1999/10/12 19:00:31  mmiers
 * LOG:
 * LOG:
 * LOG: Instrument exit condition for services.
 * LOG:
 * LOG: Revision 1.9  1999/10/12 18:34:44  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with non-zero code.
 * LOG:
 * LOG: Revision 1.8  1999/10/12 15:46:10  mmiers
 * LOG:
 * LOG:
 * LOG: Work on increasing the debug support here.
 * LOG:
 * LOG: Revision 1.7  1999/08/23 19:39:18  labuser
 * LOG:
 * LOG:
 * LOG: Don't define BUFSIZ if we don't use it.
 * LOG:
 * LOG: Revision 1.6  1999/08/23 01:25:47  mmiers
 * LOG:
 * LOG:
 * LOG: Correct function linkage.
 * LOG:
 * LOG: Revision 1.5  1999/08/22 01:20:08  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a bunch of service logic code, add interrogate handlers for UNIX,
 * LOG: add a way for the user to call handlers (C).
 * LOG:
 * LOG: Revision 1.4  1999/08/18 16:19:46  mmiers
 * LOG:
 * LOG:
 * LOG: Add in comments.
 * LOG:
 * LOG: Revision 1.3  1999/08/18 14:07:43  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build on NT.
 * LOG:
 * LOG: Revision 1.2  1999/08/18 02:34:27  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks to UNIX services and NT services.  Tomorrow will tell.
 * LOG:
 * LOG: Revision 1.1  1999/08/18 01:02:21  mmiers
 * LOG:
 * LOG:
 * LOG: Default implementations until I can compile on the target.
 * LOG:
 * LOG: Revision 1.1  1999/08/17 23:48:42  mmiers
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_service.h>
#include <its_trace.h>
#include <its_license.h>

#ident "$Id: its_serv.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

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

static ITS_BOOLEAN SERVICE_DefaultControlHandler(int);
static void SERVICE_DefaultSignalHandler(int);

static ITS_BOOLEAN (*SERVICE_ControlHandler)(int curSig) = SERVICE_DefaultControlHandler;
static void (*SERVICE_SignalHandler)(int sig) = SERVICE_DefaultSignalHandler;

static void           _Handler(int sig);
static void           _ControlHandler(int sig);
static void           _CoreHandler(int sig);
static void           _OnExitHandler();

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

    SERVICE_SetExitCode(EXIT_SUCCESS);

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
    int pid;
    struct sigaction action;

    SERVICE_SetType(ST_SERVICE);

    if ((pid = fork()) > 0)
    {
        /* we are the parent */
        SERVICE_SetExitCode(EXIT_SUCCESS);

        return;
    }
    else if (pid == 0)
    {
        /*
         * we are the child
         * become a session leader.  We will lead a new process group,
         * and have no controlling TTY.
         */
        setsid();

        /*
         * ditch stdxx
         */
        close(0);
        close(1);
        close(2);

        /*
         * set signal handlers
         */
        action.sa_handler = _Handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGKILL, &action, NULL);
        sigaction(SIGTERM, &action, NULL);
        sigaction(SIGSTOP, &action, NULL);
        sigaction(SIGCONT, &action, NULL);
        sigaction(SIGHUP, &action, NULL);
        action.sa_handler = _ControlHandler;
        sigaction(SIGINT, &action, NULL);

        action.sa_handler = _CoreHandler;
        sigaction(SIGSEGV, &action, NULL);
        sigaction(SIGILL, &action, NULL);
        sigaction(SIGQUIT, &action, NULL);
        sigaction(SIGFPE, &action, NULL);
        sigaction(SIGBUS, &action, NULL);
        sigaction(SIGXCPU, &action, NULL);
        sigaction(SIGXFSZ, &action, NULL);

        /*
         * call the good stuff
         */
        SERVICE_Run(0, NULL);
    }
    else
    {
        /* fork failure. */
        SERVICE_SetExitCode(EXIT_FAILURE);

        return;
    }
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
    struct sigaction action;

    SERVICE_SetType(ST_CONSOLE_APPLICATION);

    /*
     * set signal handlers
     */
    action.sa_handler = _Handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);
    sigaction(SIGKILL, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGCONT, &action, NULL);
    sigaction(SIGHUP, &action, NULL);
    action.sa_handler = _ControlHandler;
    sigaction(SIGINT, &action, NULL);

    action.sa_handler = _CoreHandler;
    sigaction(SIGSEGV, &action, NULL);
    sigaction(SIGILL, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGFPE, &action, NULL);
    sigaction(SIGBUS, &action, NULL);
    sigaction(SIGXCPU, &action, NULL);
    sigaction(SIGXFSZ, _CoreHandler);
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
    printf("%s: service installed.\n", SERVICE_DisplayedName);

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
    printf("%s: service removed.", SERVICE_DisplayedName);

    return (ITS_SUCCESS);
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
    if (SERVICE_InitFunc)
    {
        (*SERVICE_InitFunc)(argc, (char **)argv);
    }

    while (!SERVICE_IsStopped())
    {
        if (SERVICE_MainFunc)
        {
            (*SERVICE_MainFunc)();
        }
    }

    if (SERVICE_TermFunc)
    {
        (*SERVICE_TermFunc)();
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
SERVICE_SetControlHandler(ITS_BOOLEAN (*ControlHandler)(int curSig))
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
 *      On NT, the ControlHandler handles command requests from the SCM.
 *      On UNIX, the ControlHandler handles signals normally not expected
 *      from the console (e.g., SIGINT).
 *      On UNIX, the SignalHandler handles SIGINT (i.e., Ctrl-C from the
 *      console.
 *      On NT, the SignalHandler handles Ctrl-C and Ctrl-Break from the
 *      console.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SERVICE_SetSignalHandler(void (*Handler)(int sig))
{
    SERVICE_SignalHandler = Handler;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The default signal handler for UNIX.  This function will call
 *      the user registered (or default) handler for each signal covered.
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
 *          SIGTERM (StopHandler)
 *          SIGSTOP (PauseHandler)
 *          SIGCONT (ContinueHandler)
 *          SIGKILL (ShutdownHandler)
 *          UNIX has no equivalent for the InterrogateHandler.
 *
 *  See Also:
 ****************************************************************************/
static void
SERVICE_DefaultSignalHandler(int sig)
{
    switch (sig)
    {
    case SIGTERM:
        if (handlers[SERV_HANDLER_STOP])
        {
            ITS_TRACE_CRITICAL(("SIGTERM, Signal caught\n"));
            (*handlers[SERV_HANDLER_STOP])();
        }
        break;

    case SIGSTOP:
        if (handlers[SERV_HANDLER_PAUSE])
        {
            ITS_TRACE_CRITICAL(("SIGSTOP, Signal caught\n"));
            (*handlers[SERV_HANDLER_PAUSE])();
        }
        break;

    case SIGCONT:
        if (handlers[SERV_HANDLER_CONTINUE])
        {
            ITS_TRACE_CRITICAL(("SIGCONT, Signal caught\n"));
            (*handlers[SERV_HANDLER_CONTINUE])();
        }
        break;

    case SIGKILL:
        if (handlers[SERV_HANDLER_SHUTDOWN])
        {
            ITS_TRACE_CRITICAL(("SIGKILL, Signal caught\n"));   
            (*handlers[SERV_HANDLER_SHUTDOWN])();
        }
        break;

    case SIGHUP:
        if (handlers[SERV_HANDLER_INTERROGATE])
        {
            ITS_TRACE_CRITICAL(("SIGHUP, Signal caught\n"));
            (*handlers[SERV_HANDLER_INTERROGATE])();
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
    SERVICE_SetStopped();
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
 *      On UNIX, this is a NOOP.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultPauseHandler()
{
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
 *      On UNIX, this is a NOOP.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SERVICE_DefaultContinueHandler()
{
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
 *      On UNIX, this is a NOOP.
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
    SERVICE_SetStopped();
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
 *      sig - the signal delivered (SIGINT)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_FALSE to continue
 *      ITS_TRUE to terminate
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
SERVICE_DefaultControlHandler(int sig)
{
    if (handlers[SERV_HANDLER_INTERRUPT])
    {
        (*handlers[SERV_HANDLER_INTERRUPT])();
    }

    return (SERVICE_IsStopped());
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
_Handler(int sig)
{
    ITS_TRACE_CRITICAL(("SigHandler caught: %d\n", sig));

    if (SERVICE_SignalHandler)
    {
        (*SERVICE_SignalHandler)(sig);
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
static void
_ControlHandler(int sig)
{
    ITS_TRACE_CRITICAL(("ControlHandler caught: %d\n", sig));

    if (SERVICE_ControlHandler)
    {
        if ((*SERVICE_ControlHandler)(sig))
        {
            SERVICE_SetStopped();
        }
    }
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
_CoreHandler(int sig)
{
    ITS_TRACE_CRITICAL(("CoreHandler caught: %d\n", sig));
    abort();
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


