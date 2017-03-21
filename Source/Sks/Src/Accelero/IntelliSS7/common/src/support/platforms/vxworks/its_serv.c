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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:31  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/01 15:46:24  mmiers
 * LOG: Add priority setting
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.4  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.3  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 1.2  2001/02/12 21:42:33  lbana
 * LOG: ident macro is defined
 * LOG:
 * LOG: Revision 1.1  2001/02/12 21:09:01  lbana
 * LOG: stubs for vxWorks porting
 * LOG:
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_service.h>
#include <its_trace.h>

#ident "$Id: its_serv.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $"

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
    SERVICE_DefaultInterruptHandler
};

ITSDLLAPI const char * SERVICE_InternalName = NULL;
ITSDLLAPI const char * SERVICE_DisplayedName = NULL;
ITSDLLAPI EVENTLOG_Manager *SERVICE_EventLog = NULL;

static ITS_BOOLEAN SERVICE_DefaultControlHandler(int);
static void SERVICE_DefaultSignalHandler(int);

static ITS_BOOLEAN (*SERVICE_ControlHandler)(int curSig) = SERVICE_DefaultControlHandler;
static void (*SERVICE_SignalHandler)(int sig) = SERVICE_DefaultSignalHandler;

static ITS_BOOLEAN    stopEventSignalled = ITS_FALSE;

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
    printf("SUPPORT_ERROR: No service available in vxworks\n");

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
    printf("SUPPORT_ERROR: No service available in vxworks\n");  
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");

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
    printf("SUPPORT_ERROR: No service available in vxworks\n");

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
    printf("SUPPORT_ERROR: No service available in vxworks\n");

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
SERVICE_SetControlHandler(ITS_BOOLEAN (*ControlHandler)(int curSig))
{
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
SERVICE_SetSignalHandler(void (*Handler)(int sig))
{
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
ITSDLLAPI void
SERVICE_DefaultSignalHandler(int sig)
{
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
ITSDLLAPI ITS_BOOLEAN
SERVICE_DefaultControlHandler(int sig)
{
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
    printf("SUPPORT_ERROR: No service available in vxworks\n");
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
   printf("SUPPORT_ERROR: No service available in vxworks\n");
   return !(ITS_SUCCESS);
}

#endif /* SERVICE_TEST */
