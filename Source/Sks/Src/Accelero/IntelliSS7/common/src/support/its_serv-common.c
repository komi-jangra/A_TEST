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
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:11  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 3.8  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.2  2001/01/18 18:46:28  mmiers
 * LOG: CPP service based on C service.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:40  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:34:08  mmiers
 * LOG: Rename this to avoid collisions.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:02  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/10/11 16:17:01  mmiers
 * LOG:
 * LOG:
 * LOG: Update casts for Solaris.
 * LOG:
 * LOG: Revision 1.10  1999/08/25 01:50:09  mmiers
 * LOG:
 * LOG:
 * LOG: Usage contains note about how to escape comment character.
 * LOG:
 * LOG: Revision 1.9  1999/08/25 01:48:06  mmiers
 * LOG:
 * LOG:
 * LOG: Control for comment char only in column 1, and how to escape comment
 * LOG: characters.
 * LOG:
 * LOG: Revision 1.8  1999/08/22 01:20:10  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a bunch of service logic code, add interrogate handlers for UNIX,
 * LOG: add a way for the user to call handlers (C).
 * LOG:
 * LOG: Revision 1.7  1999/08/20 22:13:10  labuser
 * LOG:
 * LOG:
 * LOG: Fix missing include problem.
 * LOG:
 * LOG: Revision 1.6  1999/08/19 01:37:28  mmiers
 * LOG:
 * LOG:
 * LOG: Whooptydoo debugger startup on assertions.
 * LOG:
 * LOG: Revision 1.5  1999/08/18 16:19:47  mmiers
 * LOG:
 * LOG:
 * LOG: Add in comments.
 * LOG:
 * LOG: Revision 1.4  1999/08/18 15:16:00  mmiers
 * LOG:
 * LOG:
 * LOG: Build the C test.   Finish the C service API.
 * LOG:
 * LOG: Revision 1.3  1999/08/18 14:07:44  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build on NT.
 * LOG:
 * LOG: Revision 1.2  1999/08/18 01:00:03  mmiers
 * LOG:
 * LOG:
 * LOG: More work on C services.
 * LOG:
 * LOG: Revision 1.1  1999/08/17 23:48:43  mmiers
 * LOG:
 * LOG:
 * LOG: Fooling around with C based services.
 * LOG:
 *
 ******************************************************************************/

#include <string.h>
#include <stdlib.h>

#include <its.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <its_service.h>
#include <its_timers.h>

#ident "$Id: its_serv-common.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

static SERVICE_Type servType = ST_NOT_SET;
static int          exitCode = 0;

extern const char *SERVICE_DisplayedName;
extern EVENTLOG_Manager *SERVICE_EventLog;

char *SERVICE_ARGV0 = NULL;

/*
 * forward
 */
static void SERVICE_DefaultMainFunc(void);

/*
 * common handlers
 */
void (*SERVICE_InitFunc)(int argc, const char **argv) = NULL;
void (*SERVICE_MainFunc)(void) = SERVICE_DefaultMainFunc;
void (*SERVICE_TermFunc)(void) = NULL;

extern SERVICE_Handler handlers[];

static ITS_BOOLEAN     stopEventSignalled = ITS_FALSE;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Default main function
 *
 *  Input Parameters:
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
 *
 ****************************************************************************/
static void
SERVICE_DefaultMainFunc(void)
{
    TIMERS_Sleep(5);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Set the service type.
 *
 *  Input Parameters:
 *      type - one of ST_CONSOLE_APPLICATION or ST_SERVICE
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
SERVICE_SetType(SERVICE_Type type)
{
    servType = type;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Retrieve the service type.
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
 *      type - one of ST_CONSOLE_APPLICATION or ST_SERVICE
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI SERVICE_Type
SERVICE_GetType()
{
    return servType;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Print the command line arguments possible.
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
SERVICE_Usage()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <args>\n", SERVICE_DisplayedName);
    fprintf(stderr, "\n");
    fprintf(stderr, "Where args are one or more of:\n");
#if defined(WIN32)
    fprintf(stderr, "                     to run as a service (started by the SCM).\n");
    fprintf(stderr, "  -install           to install the service.\n");
    fprintf(stderr, "  -remove            to remove the service.\n");
#endif
    fprintf(stderr, "  -console           to run as a console application.\n");
    fprintf(stderr, "  -service           to run as a background application.\n");
    fprintf(stderr, "  -commentChar <c>   to set an alternative comment char in\n");
    fprintf(stderr, "                     configuration files. [#;] are the default\n");
    fprintf(stderr, "                     comment characters. '\\' escapes these.\n");
    fprintf(stderr, "  -traceDir <dir>    to set the trace file directory.\n");
    fprintf(stderr, "  -libDir <dir>      to set the shared lib directory.\n");
    fprintf(stderr, "  -configDir <dir>   to set the configuration file directory.\n");
    fprintf(stderr, "  -configExt <dir>   to set the configuration file extension.\n");
    fprintf(stderr, "  -appName <name>    to set the application name.\n");
    fprintf(stderr, "  -configFile <name> to set the configuration file name.\n");
    fprintf(stderr, "                     This overrides configDir and configExt\n");
    fprintf(stderr, "                     when computing the configuration file name.\n");
    fprintf(stderr, "  -putenv <env-var>  to set an environment variable.\n");
    fprintf(stderr, "  -help              to display this message.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Most applications will default to -service if no\n");
    fprintf(stderr, "flags are specified.  Consult your user's guide if\n");
    fprintf(stderr, "unsure about your particular application.\n");
    fprintf(stderr, "\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Process the command line arguments
 *
 *  Input Parameters:
 *      argc - the argument count
 *      argv - the arguments as strings, size of array is argc
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
SERVICE_ProcessCommandLine(int argc, const char** argv)
{
    int i;

#if defined(WIN32)
#define COMPARE     _stricmp
#else
#define COMPARE     strcmp
#endif

    SERVICE_ARGV0 = strdup(argv[0]);

    SERVICE_SetExitCode(EXIT_FAILURE);

    for (i = 1; i < argc; i++)
    {
        if (*argv[i] == '-'
#if defined(WIN32)
            || *argv[i] == '/'
#endif
           )
        {
#if defined(WIN32)
            if (COMPARE("install", argv[i] + 1) == 0)
            {
                if (i == 1)
                {
                    SERVICE_Install();
                    SERVICE_SetExitCode(EXIT_SUCCESS);
                    exit(exitCode);
                }
                else
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }
            }
            else if (COMPARE("remove", argv[i] + 1) == 0)
            {
                if (i == 1)
                {
                    SERVICE_Remove();
                    SERVICE_SetExitCode(EXIT_SUCCESS);
                    exit(exitCode);
                }
                else
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }
            }
            else
#endif
            if (COMPARE("console", argv[i] + 1) == 0)
            {
                if (i == 1)
                {
                    SERVICE_SetType(ST_CONSOLE_APPLICATION);
                    continue;
                }
                else
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }
            }
            else if (COMPARE("service", argv[i] + 1) == 0)
            {
                if (i == 1)
                {
                    SERVICE_SetType(ST_SERVICE);
                    continue;
                }
                else
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }
            }
            else if (COMPARE("help", argv[i] + 1) == 0)
            {
                SERVICE_Usage();
                exit(exitCode);
            }
            else if (COMPARE("configDir", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                APPL_SetConfigDir(argv[i]);
            }
            else if (COMPARE("appName", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                APPL_SetName(argv[i]);
            }
            else if (COMPARE("commentChar", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                RESFILE_SetAltCommentChar(argv[i][0]);
            }
            else if (COMPARE("configFile", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                APPL_SetConfigFileName(argv[i]);
            }
            else if (COMPARE("configExt", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                APPL_SetConfigFileExtension(argv[i]);
            }
            else if (COMPARE("traceDir", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                APPL_SetTraceDir(argv[i]);
            }
            else if (COMPARE("libDir", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                APPL_SetLibDir(argv[i]);
            }
            else if (COMPARE("putenv", argv[i] + 1) == 0)
            {
                i++;
                if (i >= argc)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

                if (argv[i] == NULL)
                {
                    SERVICE_Usage();
                    exit(exitCode);
                }

#if defined(WIN32)
                _putenv(argv[i]);
#else
                putenv((char *)argv[i]);
#endif
            }
        }
    }

    SERVICE_SetExitCode(EXIT_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Set the process exit code.
 *
 *  Input Parameters:
 *      exitCodeparam - the exit code value.
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
SERVICE_SetExitCode(int exitCodeParam)
{
    exitCode = exitCodeParam;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Get the current exit code value
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
 *      exitCodeparam - the exit code value.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SERVICE_GetExitCode()
{
    return exitCode;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Set the initialization function for this process
 *
 *  Input Parameters:
 *      BeforeApplicationLoop - the initialization function
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
SERVICE_SetInitFunction(void (*BeforeApplicationLoop)(int argc,
                                                      const char** argv))
{
    SERVICE_InitFunc = BeforeApplicationLoop;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Set the main processing function for this process
 *
 *  Input Parameters:
 *      ApplicationLoop - the main processing function for this process
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
SERVICE_SetMainFunction(void (*ApplicationLoop)(void))
{
    SERVICE_MainFunc = ApplicationLoop;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Set the termination function for this process.
 *
 *  Input Parameters:
 *      AfterApplicationLoop - the termination function for this process
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
SERVICE_SetTermFunction(void (*AfterApplicationLoop)(void))
{
    SERVICE_TermFunc = AfterApplicationLoop;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Set a handler function for this process (override default behavior).
 *
 *  Input Parameters:
 *      type - which handler to override
 *      handler - the replacement handler
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      handler - a pointer to the last handler registered.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI SERVICE_Handler
SERVICE_SetHandler(SERVICE_HandlerType type,
                   SERVICE_Handler handler)
{
    SERVICE_Handler ret = handlers[type];

    handlers[type] = handler;

    return (ret);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Call a handler function for this process
 *
 *  Input Parameters:
 *      type - which handler to call
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      handler - a pointer to the last handler registered.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SERVICE_CallHandler(SERVICE_HandlerType type)
{
    if (type < 0 || type > SERV_HANDLER_MAX_HANDLERS)
    {
        return (ITS_ENOTFOUND);
    }

    if (handlers[type] == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    (*handlers[type])();

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Detect if the service has been stopped.
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
 *      current state of the stopped flag.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SERVICE_IsStopped()
{
    return (stopEventSignalled);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Stop the main application loop.
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
SERVICE_SetStopped()
{
    stopEventSignalled = ITS_TRUE;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Fetch the event logger
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
ITSDLLAPI EVENTLOG_Manager *
SERVICE_GetEventLog()
{
    return (SERVICE_EventLog);
}
