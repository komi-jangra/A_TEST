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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1  2003/07/22 19:50:07  lbana
 * LOG: added windows.h file.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/01 15:46:23  mmiers
 * LOG: Add priority setting
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/10/11 22:56:15  hdivoux
 * LOG: Correction.
 * LOG:
 * LOG: Revision 5.2  2001/10/11 22:50:44  hdivoux
 * LOG: Update for not using singleton service object after destructor called.
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
 * LOG: Revision 3.17  2001/04/11 21:30:11  mmiers
 * LOG: Apparently declspecs don't apply to static member variables.
 * LOG:
 * LOG: Revision 3.16  2001/04/02 19:50:14  mmiers
 * LOG: Solaris build.
 * LOG:
 * LOG: Revision 3.15  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 3.14  2001/03/26 19:59:39  mmiers
 * LOG: Set the current service.
 * LOG:
 * LOG: Revision 3.13  2001/03/16 17:13:59  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 3.12  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.11  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 3.10  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.9  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.8  2001/03/06 22:01:23  mmiers
 * LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
 * LOG:
 * LOG: Revision 3.7  2001/03/06 02:17:17  mmiers
 * LOG: Work on circular dependencies, down to one cpp file.  Need to
 * LOG: modify exception compiler to get rid of this last dependency.
 * LOG: Then we get to eliminate two more lib copies.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 18:53:36  mmiers
 * LOG: Move method
 * LOG:
 * LOG: Revision 3.2  2001/01/18 18:46:28  mmiers
 * LOG: CPP service based on C service.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:22  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/06/13 19:15:54  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:58  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:43  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.21  1999/11/02 21:46:08  labuser
 * LOG:
 * LOG:
 * LOG: New method (unexpected exit handler).
 * LOG:
 * LOG: Revision 1.20  1999/10/13 17:42:53  labuser
 * LOG:
 * LOG:
 * LOG: More corrections to service logic.
 * LOG:
 * LOG: Revision 1.19  1999/10/07 22:27:59  labuser
 * LOG:
 * LOG:
 * LOG: Find the termination problem with Brite applications.  Due to
 * LOG: not so great signal handling and resource leak.
 * LOG:
 * LOG: Revision 1.18  1999/09/08 16:31:31  mmiers
 * LOG:
 * LOG:
 * LOG: Alter Rajesh's changes so that they are cross-platform sane.
 * LOG:
 * LOG: Revision 1.17  1999/09/03 23:48:01  rsonak
 * LOG:
 * LOG: Added more methods (check its_service-win.cpp) 1.12 comments for details
 * LOG:
 * LOG: Revision 1.16  1999/08/25 16:46:42  mmiers
 * LOG:
 * LOG:
 * LOG: Move the handlers to public scope so users can see them.
 * LOG:
 * LOG: Revision 1.15  1999/08/22 01:20:08  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a bunch of service logic code, add interrogate handlers for UNIX,
 * LOG: add a way for the user to call handlers (C).
 * LOG:
 * LOG: Revision 1.14  1999/08/18 02:54:08  mmiers
 * LOG:
 * LOG:
 * LOG: Watch C++ comments in C code.
 * LOG:
 * LOG: Revision 1.13  1999/08/18 02:34:26  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks to UNIX services and NT services.  Tomorrow will tell.
 * LOG:
 * LOG: Revision 1.12  1999/08/17 23:48:42  mmiers
 * LOG:
 * LOG:
 * LOG: Fooling around with C based services.
 * LOG:
 * LOG: Revision 1.11  1999/08/09 18:55:33  labuser
 * LOG:
 * LOG:
 * LOG: Add a method to set the application type.
 * LOG:
 * LOG: Revision 1.10  1999/06/29 17:14:36  skarmakar
 * LOG:
 * LOG:
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.9  1998/11/18 15:57:45  mmiers
 * LOG: Portable service now complete.
 * LOG:
 * LOG: Revision 1.8  1998/11/18 15:10:46  mmiers
 * LOG: Build service on ALPHA.
 * LOG:
 * LOG: Revision 1.7  1998/11/18 03:37:57  mmiers
 * LOG: Build some service classes.  Need to debug tomorrow.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 20:10:19  hdivoux
 * LOG: Added documentation.
 * LOG:
 * LOG: Revision 1.4  1998/06/01 16:35:18  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.3  1998/05/28 17:28:11  hdivoux
 * LOG: Improved the way event log and exception log work.
 * LOG: Improved the way event log and exception log are used by Service.
 * LOG:
 * LOG: Revision 1.2  1998/05/28 02:24:30  hdivoux
 * LOG: Erased irrelevant static member function.
 * LOG:
 * LOG: Revision 1.1  1998/05/27 23:39:45  hdivoux
 * LOG: Creation.
 * LOG:
 *
 ******************************************************************************/

#if !defined(_ITS_SERVICE_H_)
#define _ITS_SERVICE_H_

#include <its.h>
#include <its_event_log.h>

#if defined (WIN32)
#include <windows.h>
#endif


#ident "$Id: its_service.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*.interface:Service
 *******************************************************************************
 *  Interface:
 *      Service
 *
 *  Purpose:
 *     Base class to help to write services/daemons.
 *
 *  Usage:
 *	    Inherit from Service and redefine the member functions 
 *      BeforeApplicationLoop, ApplicationLoop and AfterApplicationLoop. If a
 *      more advanced behavior than the one provided by default is required
 *      then it is also possible to redefine other virtual functions. Advice:
 *      study well the original code before you try this.
 *
 *******************************************************************************/
typedef enum
{
    ST_NOT_SET,
    ST_SERVICE,
    ST_CONSOLE_APPLICATION
}
SERVICE_Type;

typedef enum
{
    SERV_HANDLER_STOP,
    SERV_HANDLER_PAUSE,
    SERV_HANDLER_CONTINUE,
    SERV_HANDLER_SHUTDOWN,
    SERV_HANDLER_INTERROGATE,
    SERV_HANDLER_INTERRUPT,
    SERV_HANDLER_UNEXPECTED_EXIT,

    SERV_HANDLER_MAX_HANDLERS
}
SERVICE_HandlerType;

#define SERVICE_MIN_PRIORITY    0
#define SERVICE_MAX_PRIORITY    99

#if defined(__cplusplus)
extern "C"
{
#endif

typedef void (*SERVICE_Handler)(void);

/*
 * this is necessary to solve a chicken/egg problem.
 */
ITSDLLAPI extern const char        *SERVICE_InternalName;
ITSDLLAPI extern const char        *SERVICE_DisplayedName;
ITSDLLAPI extern EVENTLOG_Manager  *SERVICE_EventLog;

/*
 * start/stop
 */
ITSDLLAPI int SERVICE_Initialize(const char *DisplayedName,
                                 const char *InternalName,
                                 EVENTLOG_Manager *eventLog);
ITSDLLAPI void SERVICE_Terminate();

/*
 * foreground/background
 */
ITSDLLAPI void            SERVICE_SetType(SERVICE_Type type);
ITSDLLAPI SERVICE_Type    SERVICE_GetType();

/*
 * runtime priority
 */
ITSDLLAPI int             SERVICE_SetPriority(ITS_UINT priority);

/*
 * run styles
 */
ITSDLLAPI void            SERVICE_RunAsService();
ITSDLLAPI void            SERVICE_RunAsConsoleApplication(int argc,
                                                          const char** argv);
ITSDLLAPI int             SERVICE_Run(int argc, const char **argv);

/*
 * common functions
 */
ITSDLLAPI void        SERVICE_ProcessCommandLine(int argc, const char** argv);
ITSDLLAPI void        SERVICE_Usage();
ITSDLLAPI void        SERVICE_SetExitCode(int exitCodeParam);
ITSDLLAPI int         SERVICE_GetExitCode();

ITSDLLAPI int         SERVICE_Install();  /* noop on UNIX */
ITSDLLAPI int         SERVICE_Remove();   /* noop on UNIX */

ITSDLLAPI EVENTLOG_Manager *SERVICE_GetEventLog();

/*
 * application loop functions
 */
ITSDLLAPI void        SERVICE_SetInitFunction(void (*InitFunc)(int argc,
                                                     const char** argv));
ITSDLLAPI void        SERVICE_SetMainFunction(void (*MainFunc)(void));
ITSDLLAPI void        SERVICE_SetTermFunction(void (*TermFunc)(void));

ITSDLLAPI ITS_BOOLEAN SERVICE_IsStopped();
ITSDLLAPI void        SERVICE_SetStopped();

ITSDLLAPI SERVICE_Handler        SERVICE_SetHandler(SERVICE_HandlerType type,
                                                    SERVICE_Handler handler);
ITSDLLAPI int                    SERVICE_CallHandler(SERVICE_HandlerType type);

/*
 * default actions
 */
ITSDLLAPI void        SERVICE_DefaultStopHandler(void);
ITSDLLAPI void        SERVICE_DefaultPauseHandler(void);
ITSDLLAPI void        SERVICE_DefaultContinueHandler(void);
ITSDLLAPI void        SERVICE_DefaultShutdownHandler(void);
ITSDLLAPI void        SERVICE_DefaultInterrogateHandler(void);
ITSDLLAPI void        SERVICE_DefaultInterruptHandler(void);
ITSDLLAPI void        SERVICE_DefaultUnexpectedExitHandler(void);

/*
 * platform specific functions
 */
#if defined(WIN32)

ITSDLLAPI void        SERVICE_SetControlHandler(BOOL (*ControlHandler)(DWORD ctrlType));
ITSDLLAPI void        SERVICE_SetSignalHandler(void (*Handler)(DWORD controlCode));

ITSDLLAPI void        SERVICE_SetControlsAccepted(DWORD controlsAcceptedParam);
ITSDLLAPI void        SERVICE_SetDependencies(const char *deps);
ITSDLLAPI const char* SERVICE_GetDependencies();
ITSDLLAPI void        SERVICE_SetStatus(DWORD currentState, DWORD waitHint);

ITSDLLAPI SERVICE_STATUS  SERVICE_GetStatus();
ITSDLLAPI HANDLE          SERVICE_GetStopEventHandle();

#elif defined(unix)

ITSDLLAPI void        SERVICE_SetControlHandler(ITS_BOOLEAN (*ControlHandler)(int curSig));
ITSDLLAPI void        SERVICE_SetSignalHandler(void (*Handler)(int sig));

#endif

/*
 * these are for C++ usage.  Note the constructor below.
 */
#if defined(__cplusplus)
inline void        SERVICE_InitCPP(int argc, const char **argv);
inline void        SERVICE_MainCPP(void);
inline void        SERVICE_TermCPP(void);

inline void        SERVICE_StopCPP(void);
inline void        SERVICE_PauseCPP(void);
inline void        SERVICE_ContinueCPP(void);
inline void        SERVICE_ShutdownCPP(void);
inline void        SERVICE_InterrogateCPP(void);
inline void        SERVICE_InterruptCPP(void);
inline void        SERVICE_UnexpectedExitCPP(void);
#endif

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <string>

#include <its++.h>
#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_exception.h>
#include <its_timers.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    /* defined(ITS_NAMESPACE) */

// forward (NT is silly)
extern ITSDLLAPI Service*   its_intern_currentService;

//.interface:Service
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      Service
//
//  Purpose:
//	    Base class to help to write services/daemons.
//
//  Usage:
//	    Inherit from Service and redefine the member functions 
//      BeforeApplicationLoop, ApplicationLoop and AfterApplicationLoop. If a
//      more advanced behavior than the one provided by default is required
//      then it is also possible to redefine other virtual functions. Advice:
//      study well the original code before you try this.
//
//      On NT, this class would be used as follows:
//
//  ----------------------------------------------------------------------
//  // 
//  // The exception log and event log objects
//  // MUST always be created as static objects.
//  //
//
//  #if defined(WIN32)
//
//  static ITS_NtExceptionLog exceptionLog("WOS MSC");
//  static ITS_NtEventLog eventLog("WOS MSC");
//
//  // Ideally, the following should be done by
//  // the installation procedure.
//
//  ITS_NtEventLog::RegistryCreateSource("WOS MSC", "ItsMsgFile.dll");
//
//  #else
//
//  static ITS_UnixExceptionLog exceptionLog("TCAP Server");
//  static ITS_UnixEventLog eventLog("TCAP Server");
//
//  #endif
//  
//  try
//  {
//      // Create the unique service object.
//
//      Service service("Test Service",
//                      "Test_Service",
//                      exceptionLog,
//                      eventLog);
//
//      // The following line would be required to allow the
//      // service to accept pause and continue requests.
//
//      // service.SetControlsAccepted(SERVICE_ACCEPT_PAUSE_CONTINUE);
//
//      // Process the command line.
//
//      service.ProcessCommandLine(argc, argv);
//
//      // If not exited then probably under the control of the SCM
//      // (unless if already run as a console application).
//
//      if (service.GetApplicationType() == Service::AT_SERVICE)
//      {
//          service.RunAsService();
//      }
//      else if (service.GetApplicationType() == Service::AT_CONSOLE_APPLICATION)
//      {
//          service.RunAsConsoleApplication(argc, argv);
//      }
//
//      return service.GetExitCode();
//  ----------------------------------------------------------------------
//
//  On UNIX, the same code is more or less used, but not all methods
//  perform an action; the intent on UNIX is to modify this process in
//  such a way as to a) become a session leader, b) become a child
//  of init, and c) close stdxx.
//
////////////////////////////////////////////////////////////////////////////////
class Service
{
public:

    // Constructor.
    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      displayedNameParam - displayed name of the service.
    //      internalNameParam  - internal name of the service.
    //      exceptionLogParam  - specify the exception log (static object).
    //      eventLogParam      - specify the event log (static object).
    //
    ////////////////////////////////////////////////////////////////////////////
    Service(const std::string& displayedNameParam,
            const std::string& internalNameParam,
            ExceptionLog& exceptionLogParam,
            EventLog& eventLogParam)
        : exceptionLog(exceptionLogParam),
          eventLog(eventLogParam),
          displayedName(displayedNameParam),
          internalName(internalNameParam)
    {
        SetCurrentService();

        int ret = SERVICE_Initialize(displayedNameParam.c_str(),
                                     internalNameParam.c_str(),
                                     eventLogParam.log);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        SERVICE_SetExitCode(EXIT_SUCCESS);

        SERVICE_SetInitFunction(SERVICE_InitCPP);
        SERVICE_SetMainFunction(SERVICE_MainCPP);
        SERVICE_SetTermFunction(SERVICE_TermCPP);

        SERVICE_SetHandler(SERV_HANDLER_STOP, SERVICE_StopCPP);
        SERVICE_SetHandler(SERV_HANDLER_PAUSE, SERVICE_StopCPP);
        SERVICE_SetHandler(SERV_HANDLER_CONTINUE, SERVICE_StopCPP);
        SERVICE_SetHandler(SERV_HANDLER_SHUTDOWN, SERVICE_StopCPP);
        SERVICE_SetHandler(SERV_HANDLER_INTERROGATE, SERVICE_StopCPP);
        SERVICE_SetHandler(SERV_HANDLER_INTERRUPT, SERVICE_StopCPP);
        SERVICE_SetHandler(SERV_HANDLER_UNEXPECTED_EXIT, SERVICE_UnexpectedExitCPP);
    }

    // Destructor.
    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~Service()
    {
        SERVICE_Terminate();

        its_intern_currentService = NULL; // Invalid to use object.
    }


    enum ApplicationType
    {
        AT_NOT_SET,
        AT_SERVICE,
        AT_CONSOLE_APPLICATION
    };

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Must be called to run as a service under the control of the SCM (usually
    //      directly or indirectly by the entry point).
    //
    //  Notes:
    //      The SCM passes the startup arguments to the Run(argc, argv) virtual
    //      member function. The startup arguments can be specified in the "Startup 
    //      Parameters" input field in Control Panel - Services.
    //      
    ////////////////////////////////////////////////////////////////////////////
    void
    RunAsService()
    {
        SERVICE_RunAsService();
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Must be called to run as a standard console application (usually
    //      directly or indirectly by the entry point).
    //
    //  Input Parameters:
    //      argc - count of startup arguments.
    //      argv - array of startup arguments.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    RunAsConsoleApplication(int argc, const char** argv)
    {
        SERVICE_RunAsConsoleApplication(argc, argv);
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Set the service singleton for a process
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetCurrentService()
    {
        ITS_THROW_ASSERT(its_intern_currentService == NULL);

        its_intern_currentService = this;
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the service singleton for a process
    //
    ////////////////////////////////////////////////////////////////////////////
    static Service&
    GetCurrentService()
    {
        ITS_THROW_ASSERT(its_intern_currentService != NULL);

        return *its_intern_currentService;
    }
    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Predicate to see if  the service singleton for a process is set
    //
    ////////////////////////////////////////////////////////////////////////////
    static bool
    HasCurrentService()
    {
        return (its_intern_currentService != NULL);
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the exception log associated with a service
    //
    ////////////////////////////////////////////////////////////////////////////
    ExceptionLog&
    GetExceptionLog()
    {
        return exceptionLog;
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the event log associated with a service
    //
    ////////////////////////////////////////////////////////////////////////////
    EventLog&
    GetEventLog()
    {
        return eventLog;
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the application type
    //
    ////////////////////////////////////////////////////////////////////////////
    ApplicationType
    GetApplicationType()
    {
        if (SERVICE_GetType() == ST_SERVICE)
        {
            return (AT_SERVICE);
        }
        else if (SERVICE_GetType() == ST_CONSOLE_APPLICATION)
        {
            return (AT_CONSOLE_APPLICATION);
        }
        else if (SERVICE_GetType() == ST_NOT_SET)
        {
            return (AT_NOT_SET);
        }
        else
        {
            return (AT_SERVICE);
        }
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Set the application type
    //
    //  Input Parameters:
    //      type - service or foreground process
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetApplicationType(ApplicationType type)
    {
        if (type == AT_SERVICE)
        {
            SERVICE_SetType(ST_SERVICE);
        }
        else if (type == AT_CONSOLE_APPLICATION)
        {
            SERVICE_SetType(ST_CONSOLE_APPLICATION);
        }
        else
        {
            SERVICE_SetType(ST_SERVICE);
        }
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Process command line arguments
    //
    //  Input Parameters:
    //      argc - arg count
    //      argv - arg vector
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    ProcessCommandLine(int argc, const char** argv)
    {
        SERVICE_ProcessCommandLine(argc, argv);
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Print the usage for a process
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Usage()
    {
        SERVICE_Usage();
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Set the process exit code.
    //
    //  Input Parameters:
    //      exitCodeParam - value to supply to exit();
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetExitCode(int exitCodeParam)
    {
        SERVICE_SetExitCode(exitCodeParam);
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the exit code (as set by the user)
    //
    ////////////////////////////////////////////////////////////////////////////
    int
    GetExitCode()
    {
        return SERVICE_GetExitCode();
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Install the service in the Service Control Manager database.
    //      NOOP on UNIX
    //
    //  Notes:
    //      Usually indirectly called by the installation procedure or from the 
    //      command line.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    Install()
    {
        int ret = SERVICE_Install();

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }

    //.implementation:public
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Remove the service in the Service Control Manager database. Stop the 
    //      service before if required.
    //
    //  Notes:
    //      Usually indirectly called by the de-installation procedure or from the 
    //      command line.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    Remove()
    {
        int ret = SERVICE_Remove();

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }

    //
    // the following methods are NT-specific.
    //
#if defined(WIN32)
    void
    SetControlsAccepted(DWORD controlsAcceptedParam)
    {
        SERVICE_SetControlsAccepted(controlsAcceptedParam);
    }

#endif

    //
    // On NT, these catch SCM events or Ctrl-C.  On UNIX, these catch signals
    // (SIGTERM, SIGSTOP, SIGCONT, SIGKILL, SIGINT)
    //
    virtual void
    StopHandler()
    {
        SERVICE_DefaultStopHandler();
    }
    virtual void
    PauseHandler()
    {
        SERVICE_DefaultPauseHandler();

        // Log that service is paused.

        std::string infoPaused;

        infoPaused.append(GetDisplayedName());
        infoPaused.append(" service paused");

        GetEventLog().Log(infoPaused, EventLog::LOG_INFORMATION_TYPE);
    }
    virtual void
    ContinueHandler()
    {
        SERVICE_DefaultContinueHandler();

        // Log that service is continued.

        std::string infoContinued;

        infoContinued.append(GetDisplayedName());
        infoContinued.append(" service continued");

        GetEventLog().Log(infoContinued, EventLog::LOG_INFORMATION_TYPE);
    }
    virtual void
    ShutdownHandler()
    {
        SERVICE_DefaultShutdownHandler();
    }
    virtual void
    InterrogateHandler()
    {
        SERVICE_DefaultInterrogateHandler();
    }
    virtual void
    InterruptHandler()
    {
        SERVICE_DefaultInterruptHandler();
    }

    //
    // This handler is a little wierd.  There are some conditions where
    // an application can catch a signal, but our infrastructure doesn't
    // know it (due to the rules of POSIX threads - the running thread
    // catches the signal if it doesn't block the signal).  The fix is
    // for services to register an exit() handler (via onexit() or
    // atexit()), and to call this virtual function if and only if the
    // infrastructure does not think the service has been stopped.
    //
    virtual void
    UnexpectedExitHandler()
    {
        SERVICE_DefaultUnexpectedExitHandler();
    }


    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Only to set the boolean stopEventSignalled.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    SetServiceStopped()
    {
        SERVICE_SetStopped();
    }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Only to check if service is stopped. Dont use this to see if
    //      the service is running.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual bool
    IsServiceStopped()
    {
        if (SERVICE_IsStopped())
        {
            return (true);
        }
        
        return (false);
    }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Do nothing by default. Should be redefined in an heir if required.
    //
    //  Input Parameters:
    //      argc - count of startup arguments.
    //      argv - array of startup arguments.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    BeforeApplicationLoop(int argc, const char** argv)
    {
        // Do nothing by default.
    }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Do nothing by default. Must imperatively be redefined in an heir.
    //
    //  Notes:
    //      Called repetitively by the service or the console application. This
    //      is the main loop of the application and must not be a blocking member
    //      function. A typical call should take less than 5s (to allow the SCM stop
    //      service procedure to work fine).
    //
    ////////////////////////////////////////////////////////////////////////////////
    virtual void
    ApplicationLoop()
    {
        // Do nothing by default, just sleep to save CPU cycles.

        TIMERS_Sleep(5);
    }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Do nothing by default. Should be redefined in an heir if required.
    //
    //  Notes:
    //      Called once by the service or the console application, before exiting.
    //
    ////////////////////////////////////////////////////////////////////////////////
    virtual void
    AfterApplicationLoop()
    {
    }

protected:

    //
    // the following methods are platform independent.
    //
    virtual std::string   GetDisplayedName()
    { return displayedName; }

    virtual std::string   GetInternalName()
    { return internalName; }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Run function for the service or the console application. Can be
    //      redefined in an heir if required. If redefinition, don't forget to call
    //      SetStatus with the appropriate status.
    //      Basically this member function calls once BeforeApplicationLoop, then
    //      calls repetitively ApplicationLoop. When the service or the application
    //      is stopped then calls AfterApplicationLoop, just before returning.
    //
    //  Input Parameters:
    //      argc - count of startup arguments.
    //      argv - array of startup arguments.
    //
    //  Notes:
    //      This member function never returns until the service or the console 
    //      application is stopped.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Run(int argc, const char** argv)
    {
        int ret = SERVICE_Run(argc, argv);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }

    //
    // the rest of these methods are relevant only to NT
    //
#if defined(WIN32)
    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Inform the SCM about a service status change and remember the status
    //      internally.
    //
    //  Input Parameters:
    //      currentState  - current state of the service (e.g. SERVICE_STOPPED).
    //      waitHint      - worst case estimate to next checkpoint (ms).
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetStatus(DWORD currentState, DWORD waitHint)
    {
        SERVICE_SetStatus(currentState, waitHint);
    }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the status of this service.
    //
    ////////////////////////////////////////////////////////////////////////////
    SERVICE_STATUS
    GetStatus()
    {
        return SERVICE_GetStatus();
    }

    //.implementation:protected
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Get the stop-event Handle for this service
    //
    ////////////////////////////////////////////////////////////////////////////
    HANDLE
    GetStopEventHandle()
    {
        return SERVICE_GetStopEventHandle();
    }

    virtual std::string   GetDependencies()
    {
        return SERVICE_GetDependencies();
    }

#endif

private:
    //
    // these are relevant to both platform types, but some are meaningless
    // on UNIX
    //
    ExceptionLog&               exceptionLog;
    EventLog&                   eventLog;
    std::string                 displayedName;
    std::string                 internalName;
};


#if defined(ITS_NAMESPACE)
}
#endif    /* defined(ITS_NAMESPACE) */

/*
 * Provide linkage to C interface
 */
extern "C"
{

inline void
SERVICE_InitCPP(int argc, const char **argv)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().BeforeApplicationLoop(argc, argv);
    }
}

inline void
SERVICE_MainCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().ApplicationLoop();
    }
}

inline void
SERVICE_TermCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().AfterApplicationLoop();
    }
}

inline void
SERVICE_StopCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().StopHandler();
    }
}

inline void
SERVICE_PauseCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().PauseHandler();
    }
}

inline void
SERVICE_ContinueCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().ContinueHandler();
    }
}

inline void
SERVICE_ShutdownCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().ShutdownHandler();
    }
}

inline void
SERVICE_InterrogateCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().InterrogateHandler();
    }
}

inline void
SERVICE_InterruptCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().InterruptHandler();
    }
}

inline void
SERVICE_UnexpectedExitCPP(void)
{
    if (its::Service::HasCurrentService())
    {
        its::Service::GetCurrentService().UnexpectedExitHandler();
    }
}

}

#endif /* USE_CPLUSPLUS */

#endif    /* !defined(_ITS_SERVICE_H_) */
