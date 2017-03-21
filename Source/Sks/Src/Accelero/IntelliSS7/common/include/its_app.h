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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.8  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.7  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.6  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:23:56  hxing
 * LOG: Bugs in BC.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:09  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:31  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 18:01:22  mmiers
 * LOG:
 * LOG:
 * LOG: Start the feature processing function.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:30  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.13  1999/08/11 20:12:34  mmiers
 * LOG:
 * LOG:
 * LOG: Try for cleanness.
 * LOG:
 * LOG: Revision 1.12  1999/08/11 02:35:30  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.11  1999/07/29 19:52:22  rsonak
 * LOG:
 * LOG:
 * LOG: Move extern "C" decls.
 * LOG:
 * LOG: Revision 1.10  1999/07/29 19:48:31  hdivoux
 * LOG: Moved extern "C" final } to avoid including C++ class in extern "C".
 * LOG:
 * LOG: Revision 1.9  1999/07/29 02:15:12  mmiers
 * LOG:
 * LOG:
 * LOG: Correct compilation errors after addressing Hubert's comments.
 * LOG:
 * LOG: Revision 1.8  1999/07/29 01:58:17  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.7  1999/07/29 00:08:38  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.6  1999/07/16 20:23:01  mmiers
 * LOG: Make argument const to avoid Sun warning.
 * LOG:
 * LOG: Revision 1.5  1999/07/13 14:48:19  mmiers
 * LOG:
 * LOG:
 * LOG: Group the environment variables in its.h.  Add environment variable for
 * LOG: trace files (default to cwd).  Remove dbc_command from dbc workspace.
 * LOG:
 * LOG: Revision 1.4  1999/03/24 23:50:03  mmiers
 * LOG:
 * LOG:
 * LOG: Update build configurations.
 * LOG:
 * LOG: Revision 1.3  1999/03/24 23:12:41  mmiers
 * LOG:
 * LOG:
 * LOG: Add C++ interface for application class.  Fix clean routine
 * LOG: to remove mem leak.
 * LOG:
 * LOG: Revision 1.2  1999/03/23 21:25:10  mmiers
 * LOG:
 * LOG:
 * LOG: Update for new core libraries.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 00:06:09  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_APP_H
#define ITS_APP_H

#include <its.h>
#include <its_object.h>

#ident "$Id: its_app.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(ITS_APP_ONESHOT)
#define ITS_APP_ONESHOT

/*.interface:APPL_
 *****************************************************************************
 *  Interface:
 *      APPL_*
 *
 *  Purpose:
 *      This interface gives an application writer control over the location
 *      of application configuration files and the name of the application
 *      itself.
 *
 *  Usage:
 *
 *****************************************************************************/
/*
 * The user can set the absolute path of the directory containing the
 * configuration files for this application via APPL_SetConfigDir().
 * NOTE NOTE NOTE: The string pointed to by this variable MUST
 * include your operating systems path separator as the last component!
 * Example: (NT) "C:\CONFIG\", or (UNIX) "/etc/IntelliSS7/config/".
 * NOTE THE TRAILING '\' or '/'!
 */
#if defined(__cplusplus)
extern "C"
{
#endif

ITSDLLAPI void APPL_SetConfigDir(const char *dirName);
ITSDLLAPI void APPL_SetTraceDir(const char *dirName);
ITSDLLAPI void APPL_SetLibDir(const char *dirName);
ITSDLLAPI void APPL_SetName(const char *appName);
ITSDLLAPI void APPL_SetConfigFileName(const char *fileName);
ITSDLLAPI void APPL_SetConfigFileExtension(const char *extension);

ITSDLLAPI const char *APPL_GetConfigDir();
ITSDLLAPI const char *APPL_GetTraceDir();
ITSDLLAPI const char *APPL_GetLibDir();
ITSDLLAPI const char *APPL_GetName();
ITSDLLAPI const char *APPL_GetConfigFileName();
ITSDLLAPI const char *APPL_GetConfigFileExtension();

typedef struct
{
    char* configDir;
    char* name;
    char* configFileName;
    char* traceDir;
    char* libDir;
    char* configFileExtension;
}
APPLICATION_ClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    APPLICATION_ClassPart   applicationClass;
}
APPLICATION_ClassRec, *APPLICATION_Class;

#define APPLICATION_CLASS_NAME  "APPLICATION_CLASS"

ITSDLLAPI extern APPLICATION_ClassRec itsAPPLICATION_ClassRec;
ITSDLLAPI extern ITS_Class            itsAPPLICATION_Class;

#define APPLICATION_CLASS_CONFIG_DIR(x) \
    (((APPLICATION_Class)(x))->applicationClass.configDir)

#define APPLICATION_CLASS_APP_NAME(x) \
    (((APPLICATION_Class)(x))->applicationClass.name)

#define APPLICATION_CLASS_CONFIG_FILE_NAME(x) \
    (((APPLICATION_Class)(x))->applicationClass.configFileName)

#define APPLICATION_CLASS_TRACE_DIR(x) \
    (((APPLICATION_Class)(x))->applicationClass.traceDir)

#define APPLICATION_CLASS_LIB_DIR(x) \
    (((APPLICATION_Class)(x))->applicationClass.libDir)

#define APPLICATION_CLASS_CONFIG_FILE_EXTENSION(x) \
    (((APPLICATION_Class)(x))->applicationClass.configFileExtension)

#if defined(__cplusplus)
}
#endif

#endif /* ITS_APP_ONESHOT */

#if defined(USE_CPLUSPLUS)

#include <string>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Application
 *****************************************************************************
 *  Interface:
 *      Application
 *
 *  Purpose:
 *      This interface gives an application writer control over the location
 *      of application configuration files and the name of the application
 *      itself.
 *
 *  Usage:
 *
 *****************************************************************************/
class Application
{
public:
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the application name as a C string.
     *
     *  Input Parameters:
     *      name - the application name
     *
     ************************************************************************/
    static void
    SetName(const char *name)
    {
        APPL_SetName(const_cast<char *>(name));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the application name as a C++ string.
     *
     *  Input Parameters:
     *      name - the application name
     *
     ************************************************************************/
    static void
    SetName(const std::string& name)
    {
        APPL_SetName(name.c_str());
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the configuration file name as a C string.
     *
     *  Input Parameters:
     *      name - the configuration file name
     *
     ************************************************************************/
    static void
    SetConfigFileName(const char *name)
    {
        APPL_SetConfigFileName(const_cast<char *>(name));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the config file name as a C++ string.
     *
     *  Input Parameters:
     *      name - the application name
     *
     ************************************************************************/
    static void
    SetConfigFileName(const std::string& name)
    {
        APPL_SetConfigFileName(name.c_str());
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the configuration file extension as a C string.
     *
     *  Input Parameters:
     *      name - the configuration file extension
     *
     ************************************************************************/
    static void
    SetConfigFileExtension(const char *name)
    {
        APPL_SetConfigFileExtension(const_cast<char *>(name));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the config file extension as a C++ string.
     *
     *  Input Parameters:
     *      name - the application extension
     *
     ************************************************************************/
    static void
    SetConfigFileExtension(const std::string& name)
    {
        APPL_SetConfigFileExtension(name.c_str());
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the application configuration file directory as a C string.
     *
     *  Input Parameters:
     *      dir - the application configuration file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    SetConfigDir(const char *dir)
    {
        APPL_SetConfigDir(const_cast<char *>(dir));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the application configuration file directory as a C++ string.
     *
     *  Input Parameters:
     *      dir - the application configuration file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    SetConfigDir(const std::string& dir)
    {
        APPL_SetConfigDir(dir.c_str());
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the application trace file directory as a C string.
     *
     *  Input Parameters:
     *      dir - the application trace file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    SetTraceDir(const char *dir)
    {
        APPL_SetTraceDir(const_cast<char *>(dir));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the application trace file directory as a C++ string.
     *
     *  Input Parameters:
     *      dir - the application trace file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    SetTraceDir(const std::string& dir)
    {
        APPL_SetTraceDir(dir.c_str());
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the ADP lib directory as a C string.
     *
     *  Input Parameters:
     *      dir - the ADP lib directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    SetLibDir(const char *dir)
    {
        APPL_SetLibDir(const_cast<char *>(dir));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Set the ADP lib directory as a C++ string.
     *
     *  Input Parameters:
     *      dir - the ADP lib directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    SetLibDir(const std::string& dir)
    {
        APPL_SetLibDir(dir.c_str());
    }

    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the application name as a C string.
     *
     *  Return Value:
     *      name - the application name
     *
     ************************************************************************/
    static const char * const
    GetName()
    {
        return APPL_GetName();
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the application name as a C++ string.
     *
     *  Output Parameters:
     *      name - the application name
     *
     ************************************************************************/
    static void
    GetName(std::string& name)
    {
        name.erase(name.begin(), name.end());

        name.assign(APPL_GetName(), strlen(APPL_GetName()));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the configuration file name as a C string.
     *
     *  Return Value:
     *      name - the configuration file name
     *
     ************************************************************************/
    static const char * const
    GetConfigFileName()
    {
        return APPL_GetConfigFileName();
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the configuration file name as a C++ string.
     *
     *  Output Parameters:
     *      name - the configuration file name
     *
     ************************************************************************/
    static void
    GetConfigFileName(std::string& name)
    {
        name.erase(name.begin(), name.end());

        name.assign(APPL_GetConfigFileName(), strlen(APPL_GetConfigFileName()));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the configuration file extension as a C string.
     *
     *  Return Value:
     *      name - the configuration file extension
     *
     ************************************************************************/
    static const char * const
    GetConfigFileExtension()
    {
        return APPL_GetConfigFileExtension();
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the configuration file extension as a C++ string.
     *
     *  Output Parameters:
     *      name - the configuration file extension
     *
     ************************************************************************/
    static void
    GetConfigFileExtension(std::string& name)
    {
        name.erase(name.begin(), name.end());

        name.assign(APPL_GetConfigFileExtension(),
                    strlen(APPL_GetConfigFileExtension()));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the application configuration file directory as a C string.
     *
     *  Return Value:
     *      dir - the application configuration file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static const char * const
    GetConfigDir()
    {
        return APPL_GetConfigDir();
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the application configuration file directory as a C++ string.
     *
     *  Output Parameters:
     *      dir - the application configuration file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    GetConfigDir(std::string& dir)
    {
        dir.erase(dir.begin(), dir.end());

        dir.assign(APPL_GetConfigDir(), strlen(APPL_GetConfigDir()));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the trace file directory as a C string.
     *
     *  Return Value:
     *      dir - the trace file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static const char * const
    GetTraceDir()
    {
        return APPL_GetTraceDir();
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the trace file directory as a C++ string.
     *
     *  Output Parameters:
     *      dir - the trace file directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    GetTraceDir(std::string& dir)
    {
        dir.erase(dir.begin(), dir.end());

        dir.assign(APPL_GetTraceDir(), strlen(APPL_GetTraceDir()));
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the ADP lib directory as a C string.
     *
     *  Return Value:
     *      dir - the ADP lib directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static const char * const
    GetLibDir()
    {
        return APPL_GetLibDir();
    }
    /*.implementation:public,inline,Application
     ************************************************************************
     *  Purpose:
     *      Get the ADP lib directory as a C++ string.
     *
     *  Output Parameters:
     *      dir - the ADP lib directory
     *
     *  Notes:
     *      The pathname must end in the path separator valid for your
     *      operating system.
     *
     ************************************************************************/
    static void
    GetLibDir(std::string& dir)
    {
        dir.erase(dir.begin(), dir.end());

        dir.assign(APPL_GetLibDir(), strlen(APPL_GetLibDir()));
    }

private:
    // no creating these
    Application();
    Application(const Application&);
    Application& operator=(Application&) { return (*this); }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_APP_H */
