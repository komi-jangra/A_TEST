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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:22  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.5  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:01  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/03/18 21:03:48  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.5  2000/02/14 19:17:38  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.4  2000/02/01 23:41:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 2.3  2000/01/26 19:58:53  mmiers
 * LOG:
 * LOG:
 * LOG: Forgot the class pointer.
 * LOG:
 * LOG: Revision 2.2  2000/01/26 18:12:10  mmiers
 * LOG:
 * LOG:
 * LOG: Add feature processing.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 18:01:22  mmiers
 * LOG:
 * LOG:
 * LOG: Start the feature processing function.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:20  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.10  1999/08/22 21:56:48  labuser
 * LOG:
 * LOG:
 * LOG: Integration fixes.
 * LOG:
 * LOG: Revision 1.9  1999/08/11 20:20:45  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the parens.
 * LOG:
 * LOG: Revision 1.8  1999/08/11 20:20:02  mmiers
 * LOG:
 * LOG:
 * LOG: Bulletproofing.
 * LOG:
 * LOG: Revision 1.7  1999/08/11 20:12:36  mmiers
 * LOG:
 * LOG:
 * LOG: Try for cleanness.
 * LOG:
 * LOG: Revision 1.6  1999/08/11 20:04:06  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a few bugs.
 * LOG:
 * LOG: Revision 1.5  1999/08/11 02:48:12  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build issue.
 * LOG:
 * LOG: Revision 1.4  1999/08/11 02:35:31  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.3  1999/07/29 02:15:12  mmiers
 * LOG:
 * LOG:
 * LOG: Correct compilation errors after addressing Hubert's comments.
 * LOG:
 * LOG: Revision 1.2  1999/07/29 00:08:39  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:11  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 00:06:11  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <its.h>
#include <its_app.h>

#ident "$Id: its_app.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the name of the configuration database directory
 *
 *  Input Parameters:
 *      name - the directory name, including the trailing file separator.
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI void
APPL_SetConfigDir(const char *dirName)
{
    if (APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class));
    }

    if (dirName)
    {
        APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class) =
            strdup(dirName);
    }
    else
    {
        APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class) = NULL;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the name of the lib directory
 *
 *  Input Parameters:
 *      name - the directory name, including the trailing file separator.
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
 *      The file separator is operating system specific.
 *
 ****************************************************************************/
ITSDLLAPI void
APPL_SetLibDir(const char *dirName)
{
    if (APPLICATION_CLASS_LIB_DIR(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_LIB_DIR(itsAPPLICATION_Class));
    }

    if (dirName)
    {
        APPLICATION_CLASS_LIB_DIR(itsAPPLICATION_Class) =
            strdup(dirName);
    }
    else
    {
        APPLICATION_CLASS_LIB_DIR(itsAPPLICATION_Class) = NULL;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the name of the trace directory
 *
 *  Input Parameters:
 *      name - the directory name, including the trailing file separator.
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
 *      The file separator is operating system specific.  The trace
 *      directory is combined with the trace output name using the format
 *      string ITS_TRACE_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the trace file.
 *
 ****************************************************************************/
ITSDLLAPI void
APPL_SetTraceDir(const char *dirName)
{
    if (APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class));
    }

    if (dirName)
    {
        APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class) =
            strdup(dirName);
    }
    else
    {
        APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class) = NULL;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the application name.
 *
 *  Input Parameters:
 *      name - the application name.
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI void
APPL_SetName(const char *appName)
{
    if (APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class));
    }

    if (appName)
    {
        APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class) =
            strdup(appName);
    }
    else
    {
        APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class) = NULL;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the configuration file name, including the complete path.
 *      If the path information is not absolute, the path information
 *      will be assumed to be relative to the current working directory
 *      of the application when it was started.
 *
 *  Input Parameters:
 *      name - the configuration file name.
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI void
APPL_SetConfigFileName(const char *configName)
{
    if (APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class));
    }

    if (configName)
    {
        APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) =
            strdup(configName);
    }
    else
    {
        APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) = NULL;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the configuration file extension.
 *
 *  Input Parameters:
 *      name - the configuration file extension.
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI void
APPL_SetConfigFileExtension(const char *configName)
{
    if (APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class));
    }

    if (configName)
    {
        APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class) =
            strdup(configName);
    }
    else
    {
        APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class) =
            strdup("ini");
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the configuration directory name.
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
 *      a constant pointer to the configuration directory name.
 *
 *  Notes:
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI const char *
APPL_GetConfigDir()
{
    if (APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class) == NULL)
    {
        char *ret = getenv(INTELLISS7_CONFIG_DIR_VAR);

        if (ret)
        {
            APPL_SetConfigDir(ret);
        }
    }

    return APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the trace directory name.
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
 *      a constant pointer to the trace directory name.
 *
 *  Notes:
 *      The file separator is operating system specific.  The trace
 *      directory is combined with the trace output name using the format
 *      string ITS_TRACE_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the trace file.
 *
 ****************************************************************************/
ITSDLLAPI const char *
APPL_GetTraceDir()
{
    if (APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class) == NULL)
    {
        char *env;

        if ((env = getenv(INTELLISS7_TRACE_DIR_VAR)) == NULL)
        {
            env = "";
        }

        APPL_SetTraceDir(env);
    }

    return APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the lib directory name.
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
 *      a constant pointer to the trace directory name.
 *
 *  Notes:
 *      The file separator is operating system specific.
 *
 ****************************************************************************/
ITSDLLAPI const char *
APPL_GetLibDir()
{
    if (APPLICATION_CLASS_LIB_DIR(itsAPPLICATION_Class) == NULL)
    {
        char *env;

        if ((env = getenv(INTELLISS7_LIB_DIR_VAR)) == NULL)
        {
            env = "";
        }

        APPL_SetLibDir(env);
    }

    return APPLICATION_CLASS_LIB_DIR(itsAPPLICATION_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the name of the application
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI const char *
APPL_GetName()
{
    if (!APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class))
    {
        return "DefaultName";
    }

    return APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the name of the application configuration file
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI const char *
APPL_GetConfigFileName()
{
    if (APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) == NULL)
    {
        char buf[ITS_PATH_MAX];

        if (APPL_GetConfigDir())
        {
            if (APPL_GetConfigFileExtension() == NULL ||
                strlen(APPL_GetConfigFileExtension()) == 0)
            {
                sprintf(buf, ITS_ALT_INI_FILE_NAME_FORMAT_STRING,
                        APPL_GetConfigDir(), APPL_GetName());
            }
            else
            {
                sprintf(buf, ITS_INI_FILE_NAME_FORMAT_STRING,
                        APPL_GetConfigDir(), APPL_GetName(),
                        APPL_GetConfigFileExtension());
            }
        }
        else
        {
            if (APPL_GetConfigFileExtension() == NULL ||
                strlen(APPL_GetConfigFileExtension()) == 0)
            {
                sprintf(buf, ITS_ALT_INI_FILE_NAME_FORMAT_STRING,
                        "", APPL_GetName());
            }
            else
            {
                sprintf(buf, ITS_INI_FILE_NAME_FORMAT_STRING,
                        "", APPL_GetName(),
                        APPL_GetConfigFileExtension());
            }
        }

        APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) =
            strdup(buf);
    }

    return APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the name of the application configuration file
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
 *      The file separator is operating system specific.  The configuration
 *      directory is combined with the application name using the format
 *      string ITS_INI_FILE_NAME_FORMAT_STRING (its.h) to form the name
 *      of the default configuration file.  The user can override this
 *      name via APPL_SetConfigFileName().
 *
 ****************************************************************************/
ITSDLLAPI const char *
APPL_GetConfigFileExtension()
{
    if (APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class) == NULL)
    {
        APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class) =
            strdup("ini");
    }

    return APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Prepare application info for running.
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
 *      This currently does no work, and is included only for completeness.
 *
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    APPL_GetConfigDir();

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gracefully destroy the application subsystem.
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
ClassDestroy(ITS_Class objClass)
{
    if (APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_CONFIG_DIR(itsAPPLICATION_Class));
    }

    if (APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_APP_NAME(itsAPPLICATION_Class));
    }

    if (APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class));
    }

    if (APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_TRACE_DIR(itsAPPLICATION_Class));
    }

    if (APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class))
    {
        free(APPLICATION_CLASS_CONFIG_FILE_EXTENSION(itsAPPLICATION_Class));
    }
}

ITSDLLAPI APPLICATION_ClassRec itsAPPLICATION_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        APPLICATION_CLASS_NAME,         /* class name */
        ClassInitialize,                /* class init */
        ClassDestroy,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* application part */
    {
        NULL,   /* configDir */
        NULL,   /* name */
        NULL,   /* configFileName */
        NULL,   /* traceDir */
        NULL    /* configFileExtension */
    }
};

ITSDLLAPI ITS_Class itsAPPLICATION_Class = (ITS_Class)&itsAPPLICATION_ClassRec;
