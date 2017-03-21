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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.3  2002/12/17 20:45:44  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 7.2  2002/09/26 22:18:49  yranade
 * LOG: Change signature
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/02/06 23:44:58  mmiers
 * LOG: Continued ISUP integration
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/04/03 23:56:35  mmiers
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
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:36  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:17  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/03/18 21:03:31  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.4  2000/03/02 18:10:33  fhasle
 * LOG:
 * LOG: fix RESFILE_GetNextSectionName macro.
 * LOG:
 * LOG: Revision 2.3  2000/02/12 00:07:13  mmiers
 * LOG:
 * LOG: Move RESFILE to core library.  Convert to complete OO footing.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 02:20:47  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.1  2000/01/24 22:19:20  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:38  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.26  1999/10/25 18:28:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.25  1999/08/30 17:53:41  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.24  1999/08/25 01:48:05  mmiers
 * LOG:
 * LOG:
 * LOG: Control for comment char only in column 1, and how to escape comment
 * LOG: characters.
 * LOG:
 * LOG: Revision 1.23  1999/08/23 19:42:05  labuser
 * LOG:
 * LOG:
 * LOG: Decrease max line length, still reasonable at 2K.
 * LOG:
 * LOG: Revision 1.22  1999/08/23 02:03:23  mmiers
 * LOG:
 * LOG:
 * LOG: Add const modifiers.
 * LOG:
 * LOG: Revision 1.21  1999/08/20 22:21:36  labuser
 * LOG:
 * LOG:
 * LOG: Syntax for UNIX
 * LOG:
 * LOG: Revision 1.20  1999/08/20 20:09:58  mmiers
 * LOG:
 * LOG:
 * LOG: Resfile test.
 * LOG:
 * LOG: Revision 1.19  1999/08/20 20:01:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add a findnext function.
 * LOG:
 * LOG: Revision 1.18  1999/08/11 17:30:57  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.17  1999/08/10 21:10:01  mmiers
 * LOG:
 * LOG:
 * LOG: Commonize the command line handling for services.  Make spaces
 * LOG: between the variable and the value (in resource files) the same
 * LOG: as an equal sign.  Let the user specify an alternate comment
 * LOG: character in a resource file.  Let the user add to his own environment
 * LOG: via the command line.
 * LOG:
 * LOG: Revision 1.16  1999/08/02 22:22:17  mmiers
 * LOG:
 * LOG:
 * LOG: Change away from using constructor.
 * LOG:
 * LOG: Revision 1.15  1999/08/02 17:02:31  mmiers
 * LOG:
 * LOG:
 * LOG: Document the format string for INI file names.
 * LOG:
 * LOG: Revision 1.14  1999/08/02 16:51:37  mmiers
 * LOG:
 * LOG:
 * LOG: Add constructor to copy RESFILE_Manager object.
 * LOG:
 * LOG: Revision 1.13  1999/07/29 00:08:38  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.12  1999/06/22 22:53:11  mmiers
 * LOG:
 * LOG:
 * LOG: Add key insertion/deletion to this interface.
 * LOG:
 * LOG: Revision 1.11  1999/03/12 00:06:10  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.10  1998/07/03 19:41:41  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.9  1998/06/26 14:30:38  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.8  1998/06/18 00:24:57  mmiers
 * LOG: Documentation update, C versions of some transports, C version of
 * LOG: resource file manager.
 * LOG:
 * LOG: Revision 1.7  1998/06/02 17:24:47  mmiers
 * LOG: Cleanup for the doc tool.
 * LOG:
 * LOG: Revision 1.6  1998/06/01 16:35:16  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.5  1998/05/27 22:53:17  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 17:11:45  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.3  1998/05/01 00:24:31  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.2  1998/04/22 22:20:04  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 * LOG: Revision 1.1  1998/04/20 22:05:37  mmiers
 * LOG: INI file parser.
 * LOG:
 * LOG: Revision 1.1  1998/04/19 02:42:48  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_INIPARSE_H
#define ITS_INIPARSE_H

#include <stdio.h>

#include <its_mutex.h>
#include <its_object.h>

#ident "$Id: its_iniparse.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(INIPARSE_ONESHOT)
#define INIPARSE_ONESHOT

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * a resource var/value pair
 */
typedef struct _VarValue
{
    struct _VarValue*   next;
    char*               variable;
    char*               value;
}
RESFILE_VAR_VALUE;

/*
 * a resource file section
 */
typedef struct _ResPart
{
    struct _ResPart*    next;
    char*               name;
    RESFILE_VAR_VALUE*  entries;
    RESFILE_VAR_VALUE*  current;
}
RESFILE_SECTION;

/*
 * A structure to manage a resource file
 */
typedef struct
{
    char*               name;
    FILE*               fpSettings;
    ITS_BOOLEAN         fileValid;
    ITS_MUTEX           guard;
    RESFILE_SECTION*    sections;
}
RESFILE_ManagerPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    RESFILE_ManagerPart *manager;
}
RESFILE_Manager;

#define RESFILE_NAME(x) \
    (((RESFILE_Manager *)(x))->manager->name)

#define RESFILE_FILE(x) \
    (((RESFILE_Manager *)(x))->manager->fpSettings)

#define RESFILE_VALID(x) \
    (((RESFILE_Manager *)(x))->manager->fileValid)

#define RESFILE_LOCK(x) \
    (((RESFILE_Manager *)(x))->manager->guard)

#define RESFILE_SECTIONS(x) \
    (((RESFILE_Manager *)(x))->manager->sections)

typedef int (*RESFILE_LockUnlockProc)(RESFILE_Manager *res);
typedef int (*RESFILE_GetKeyPartProc)(RESFILE_Manager *res,
                                      const char *section,
                                      char *part,
                                      int maxPartLen);
typedef int (*RESFILE_GetValueOfKeyProc)(RESFILE_Manager *res,
                                         const char *section,
                                         const char *key,
                                         char *keyValue,
                                         int maxKeyValueSize);
typedef int (*RESFILE_AddRemSectionProc)(RESFILE_Manager *res,
                                         const char *section);
typedef int (*RESFILE_AddKeyValueProc)(RESFILE_Manager *res,
                                       const char *section,
                                       const char *key,
                                       const char *value);
typedef int (*RESFILE_RemKeyValueProc)(RESFILE_Manager *res,
                                       const char *section,
                                       const char *key);
typedef int (*RESFILE_RewindSectionProc)(RESFILE_Manager *res,
                                         const char *section);
typedef int (*RESFILE_LoadReloadProc)(RESFILE_Manager *res);
typedef void (*RESFILE_UnloadProc)(RESFILE_Manager *res);
typedef const char* (*RESFILE_GetNextSectionProc)(RESFILE_Manager *res,
                                                  const char *lastSection);

/*
 * class record
 */
typedef struct
{
    RESFILE_LockUnlockProc      lock;
    RESFILE_LockUnlockProc      unlock;
    RESFILE_GetKeyPartProc      getName;
    RESFILE_GetKeyPartProc      getValue;
    RESFILE_GetValueOfKeyProc   getValueOfKey;
    RESFILE_AddRemSectionProc   addSection;
    RESFILE_AddRemSectionProc   remSection;
    RESFILE_RewindSectionProc   rewindSection;
    RESFILE_GetNextSectionProc  getNextSection;
    RESFILE_AddKeyValueProc     addKey;
    RESFILE_RemKeyValueProc     remKey;
    RESFILE_LoadReloadProc      load;
    RESFILE_LoadReloadProc      reload;
    RESFILE_UnloadProc          unload;
}
RESFILE_ManagerClassPart;

typedef struct
{
    ITS_CoreClassPart           coreClass;
    RESFILE_ManagerClassPart    managerClass;
}
RESFILE_ClassRec, *RESFILE_Class;

#define RESFILE_MAN_CLASS_LOCK(x) \
    (((RESFILE_Class)(x))->managerClass.lock)

#define RESFILE_MAN_CLASS_UNLOCK(x) \
    (((RESFILE_Class)(x))->managerClass.unlock)

#define RESFILE_MAN_CLASS_GET_KEY_NAME(x) \
    (((RESFILE_Class)(x))->managerClass.getName)

#define RESFILE_MAN_CLASS_GET_KEY_VALUE(x) \
    (((RESFILE_Class)(x))->managerClass.getValue)

#define RESFILE_MAN_CLASS_GET_VALUE_OF_KEY(x) \
    (((RESFILE_Class)(x))->managerClass.getValueOfKey)

#define RESFILE_MAN_CLASS_ADD_SECTION(x) \
    (((RESFILE_Class)(x))->managerClass.addSection)

#define RESFILE_MAN_CLASS_REM_SECTION(x) \
    (((RESFILE_Class)(x))->managerClass.remSection)

#define RESFILE_MAN_CLASS_REWIND_SECTION(x) \
    (((RESFILE_Class)(x))->managerClass.rewindSection)

#define RESFILE_MAN_CLASS_GET_NEXT_SECTION(x) \
    (((RESFILE_Class)(x))->managerClass.getNextSection)

#define RESFILE_MAN_CLASS_ADD_KEY(x) \
    (((RESFILE_Class)(x))->managerClass.addKey)

#define RESFILE_MAN_CLASS_REM_KEY(x) \
    (((RESFILE_Class)(x))->managerClass.remKey)

#define RESFILE_MAN_CLASS_LOAD(x) \
    (((RESFILE_Class)(x))->managerClass.load)

#define RESFILE_MAN_CLASS_UNLOAD(x) \
    (((RESFILE_Class)(x))->managerClass.unload)

#define RESFILE_MAN_CLASS_RELOAD(x) \
    (((RESFILE_Class)(x))->managerClass.reload)

#define RESFILE_CLASS_NAME  "RESFILE_CLASS"

ITSDLLAPI extern RESFILE_ClassRec     itsRESFILE_ClassRec;
ITSDLLAPI extern ITS_Class            itsRESFILE_Class;

/*
 *  Private definitions for parsing
 */
#define MAX_LINE_LENGTH   2048
#define MAX_STRING_LEN    1024

#if defined(__cplusplus)
}
#endif

#endif /* INIPARSE_ONESHOT */

#include <stdio.h>

#include <its.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#if !defined(ITS_FASTCALL)

ITSDLLAPI RESFILE_Manager* RESFILE_CreateResourceManager(const char* file);
ITSDLLAPI RESFILE_Manager* RESFILE_CreateEmptyResourceManager(const char* dbName);
ITSDLLAPI void RESFILE_DeleteResourceManager(RESFILE_Manager* res);

ITSDLLAPI int RESFILE_Lock(RESFILE_Manager *res);
ITSDLLAPI int RESFILE_Unlock(RESFILE_Manager *res);

ITSDLLAPI int RESFILE_GetKeyValue(RESFILE_Manager *res, const char *section,
                                  char *wkey, int len);
ITSDLLAPI int RESFILE_GetKeyName(RESFILE_Manager *res, const char *section,
                                 char *key, int len);

ITSDLLAPI int RESFILE_GetKeyValueOf(RESFILE_Manager *res, const char *section,
                                    const char *search, char *keyvalue, int klen);
ITSDLLAPI int RESFILE_AddKeyValue(RESFILE_Manager *res, const char *section,
                                  const char *key, const char *value);
ITSDLLAPI int RESFILE_RemKeyValue(RESFILE_Manager *res, const char *section,
                                  const char *key);

ITSDLLAPI int RESFILE_AddSection(RESFILE_Manager *res, const char *section);
ITSDLLAPI int RESFILE_RemSection(RESFILE_Manager *res, const char *section);
ITSDLLAPI int RESFILE_Rewind(RESFILE_Manager *res, const char *section);
ITSDLLAPI const char * RESFILE_GetNextSectionName(RESFILE_Manager *res,
                                                  const char *section);

ITSDLLAPI int RESFILE_Load(RESFILE_Manager* res);
ITSDLLAPI int RESFILE_Reload(RESFILE_Manager* res);
ITSDLLAPI void RESFILE_Unload(RESFILE_Manager* res);

#else

#define RESFILE_CreateResourceManager(fileName) \
    (RESFILE_Manager *)ITS_ConstructObject(itsRESFILE_Class, \
                                           fileName, ITS_TRUE)

#define RESFILE_CreateEmptyResourceManager(dbName) \
    (RESFILE_Manager *)ITS_ConstructObject(itsRESFILE_Class, \
                                           dbName, ITS_FALSE)

#define RESFILE_DeleteResourceManager(res) \
    ITS_DestructObject((ITS_Object)res)

#define RESFILE_Lock(res) \
    RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res)

#define RESFILE_Unlock(res) \
    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res)

#define RESFILE_GetKeyValue(res,s,k,l) \
    RESFILE_MAN_CLASS_GET_KEY_VALUE(ITS_OBJ_CLASS(res))(res,s,k,l)

#define RESFILE_GetKeyName(res,s,k,l) \
    RESFILE_MAN_CLASS_GET_KEY_NAME(ITS_OBJ_CLASS(res))(res,s,k,l)

#define RESFILE_GetKeyValueOf(res,s,k,v,l) \
    RESFILE_MAN_CLASS_GET_VALUE_OF_KEY(ITS_OBJ_CLASS(res))(res,s,k,v,l)

#define RESFILE_AddSection(res,s) \
    RESFILE_MAN_CLASS_ADD_SECTION(ITS_OBJ_CLASS(res))(res,s)

#define RESFILE_RemSection(res,s) \
    RESFILE_MAN_CLASS_REM_SECTION(ITS_OBJ_CLASS(res))(res,s)

#define RESFILE_Rewind(res,s) \
    RESFILE_MAN_CLASS_REWIND_SECTION(ITS_OBJ_CLASS(res))(res,s)

#define RESFILE_GetNextSectionName(res,s) \
    RESFILE_MAN_CLASS_GET_NEXT_SECTION(ITS_OBJ_CLASS(res))(res,s)

#define RESFILE_AddKeyValue(res,s,k,v) \
    RESFILE_MAN_CLASS_ADD_KEY(ITS_OBJ_CLASS(res))(res,s,k,v)

#define RESFILE_RemKeyValue(res,s,k) \
    RESFILE_MAN_CLASS_REM_KEY(ITS_OBJ_CLASS(res))(res,s,k)

#define RESFILE_Load(res) \
    RESFILE_MAN_CLASS_LOAD(ITS_OBJ_CLASS(res))(res)

#define RESFILE_Unload(res) \
    RESFILE_MAN_CLASS_LOAD(ITS_OBJ_CLASS(res))(res)

#define RESFILE_Reload(res) \
    RESFILE_MAN_CLASS_LOAD(ITS_OBJ_CLASS(res))(res)

#endif

/*
 * special value for the point code functions
 */
#define RESFILE_BAD_POINT_CODE      (~0U)

/*
 * These functions are either helpers, or control parser behavior.
 * They are only relevant to the default implementation.
 */
ITSDLLAPI char          RESFILE_SetAltCommentChar(char nc);
ITSDLLAPI ITS_BOOLEAN   RESFILE_SetCommentCharOnlyInColumnOne(ITS_BOOLEAN onlyInColumnOne);
ITSDLLAPI char          RESFILE_SetAltPointCodeSeparator(char nc);
ITSDLLAPI ITS_LONG      RESFILE_ParseNum(const char *num);
ITSDLLAPI ITS_UINT      RESFILE_StrToPointCode_ANSI(const char *pcStr);
ITSDLLAPI ITS_UINT      RESFILE_StrToPointCode_CCITT(const char *pcStr);
ITSDLLAPI void          RESFILE_Dump(RESFILE_Manager *);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <stdio.h>
#include <string.h>

#include <its.h>

#include <string>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:ResourceManager
 *************************************************************************
 *  Interface:
 *      ResourceManager
 *
 *  Purpose:
 *      This class is to be used in a multiplatform role as a processing
 *      aid for resource files (aka "INI" files).   The format of the file
 *      is as follows:
 *        o '#' or ';' in column 1, indicates a comment line
 *        o empty lines are ignored
 *        o [text] (open bracket in column 1) indicates a section name.
 *          A section name indicates the resources between this section
 *          name and the next are all relevant to this section.  A
 *          section represents either a subsystem or a transport.
 *        o all other lines are to take the format KEY=VALUE
 *          where KEY and VALUE are text strings.  The parsing of the
 *          VALUE portion to any application specific format is left
 *          to the application.
 *
 *      The resource key/value pairs can be accessed either sequentially
 *      or randomly, as the user desires.  Note that random access is
 *      considerably more costly that sequential access.
 *
 *  Usage:
 *      The usage for this class is fairly straightforward:
 *      ----------------------------------------------------------------
 *      // create the object
 *      ResourceManager *rf = new ITS_ResouceFile("MyFile.ini");
 *
 *      ...
 *      
 *      // sequential parsing
 *      char key[ITS_PATH_MAX], char value[ITS_PATH_MAX];
 *
 *      rf->Lock();
 *      rf->Rewind(NULL);
 *      while (rf->GetKeyName(rbuf, key, ITS_PATH_MAX) == ITS_SUCCESS &&
 *             rf->GetKeyValue(rbuf, value, ITS_PATH_MAX) == ITS_SUCCESS)
 *      {
 *          if (strcmp(key, "foo") == 0)
 *          {
 *              // act on value of variable "foo"
 *          }
 *          ...
 *      }
 *      rf->Unlock();
 *
 *      ...
 *
 *      // as an alternative, you can look for specific strings
 *      // this method implicitly locks the database
 *      if (rf->GetKeyValueOf("foo", value, ITS_PATH_MAX)
 *          == ITS_SUCCESS)
 *      {
 *          // act on value of variable "foo"
 *      }
 *
 *      ...
 *
 *      // when processing is complete, destroy the object
 *      delete rf;
 *      ----------------------------------------------------------------
 *
 *      The object code is reentrant, but an instance is not thread-safe.
 *
 **************************************************************************/
class ResourceManager
{
public:
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method opens the specified resource file for processing.
     *
     *  Input Parameters:
     *      file - the name of the resource file
     *
     *  Notes:
     *      It the file is not found, or permissions are not valid, an exception
     *          may be thrown.
     *
     *  See Also:
     *      ~ResourceManager()
     ************************************************************************/
    ResourceManager(const char *file,
                    const char *section = NULL,
                    bool wantsFile = true)
    {
        if (wantsFile)
        {
            if ((res = RESFILE_CreateResourceManager(file)) == NULL)
            {
                throw Error(ITS_EMISSINGRES);
            }
        }
        else
        {
            if ((res = RESFILE_CreateEmptyResourceManager(file)) == NULL)
            {
                throw Error(ITS_EMISSINGRES);
            }
        }
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method constructs a resource manager object.
     *
     *  Input Parameters:
     *      file - the name of the file to load from if the file
     *          is not in the cache
     *      section - the name of the section relevant for this handle
     *
     ************************************************************************/
    ResourceManager(const std::string file,
                    const std::string section = "",
                    bool wantsFile = true)
    {
        if (wantsFile)
        {
            if ((res = RESFILE_CreateResourceManager(file.c_str())) == NULL)
            {
                throw Error(ITS_EMISSINGRES);
            }
        }
        else
        {
            if ((res = RESFILE_CreateEmptyResourceManager(file.c_str())) == NULL)
            {
                throw Error(ITS_EMISSINGRES);
            }
        }
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method constructs a resource manager object.
     *
     *  Input Parameters:
     *      file - the name of the file to load from if the file
     *          is not in the cache
     *      section - the name of the section relevant for this handle
     *
     ************************************************************************/
    ResourceManager(RESFILE_Manager *copy)
    {
        if ((res = RESFILE_CreateResourceManager(RESFILE_NAME(copy))) == NULL)
        {
            throw Error(ITS_EMISSINGRES);
        }
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method constructs a resource manager object.
     *
     *  Input Parameters:
     *      file - the name of the file to load from if the file
     *          is not in the cache
     *      section - the name of the section relevant for this handle
     *
     ************************************************************************/
    ResourceManager(const ResourceManager& copy)
    {
        ITS_THROW_ASSERT(copy.res != NULL &&
                         RESFILE_NAME(copy.res) != NULL);

        if ((res = RESFILE_CreateResourceManager(RESFILE_NAME(copy.res))) ==
            NULL)
        {
            throw Error(ITS_EMISSINGRES);
        }
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method will close the resource file, terminating further
     *      processing.
     *
     ************************************************************************/
    virtual ~ResourceManager()
    {
        RESFILE_DeleteResourceManager(res);
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method constructs a resource manager object.
     *
     *  Input Parameters:
     *      file - the name of the file to load from if the file
     *          is not in the cache
     *      section - the name of the section relevant for this handle
     *
     ************************************************************************/
    ResourceManager&
    operator=(const ResourceManager& copy)
    {
        if (res)
        {
            RESFILE_DeleteResourceManager(res);
        }

        ITS_THROW_ASSERT(copy.res != NULL &&
                         RESFILE_NAME(copy.res) != NULL);

        if ((res = RESFILE_CreateResourceManager(RESFILE_NAME(copy.res))) ==
            NULL)
        {
            throw Error(ITS_EMISSINGRES);
        }

        return (*this);
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method locks the resource file.
     *
     ************************************************************************/
    int
    Lock()
    {
        return RESFILE_Lock(res);
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method unlocks the resource file.
     *
     ************************************************************************/
    int
    Unlock()
    {
        return RESFILE_Unlock(res);
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method rewinds the resource file.
     *
     *  Input Parameters:
     *      section - the name of the section to rewind.
     *
     ************************************************************************/
    void
    Rewind(const char *section)
    {
        RESFILE_Rewind(res, section);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method rewinds a section of the resource database to
     *      the beginning of that section.
     *
     *  Input Parameters:
     *      section - the name of the section to rewind
     *
     *  Return Value:
     *      ITS_SUCCESS - successful operation.  Any other return code
     *      indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *      This method should only be called after acquiring the database
     *      lock.  Failure to do so results in undefined behavior.
     *
     ************************************************************************/
    void
    Rewind(const std::string& section)
    {
        Rewind(section.c_str());
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method will parse the value portion of a resource line and
     *      return it to the user.
     *
     *  Input Parameters:
     *      string - the resource line to parse for the resource value
     *      len - the maximum value length the user will tolerate.
     *
     *  Output Parameters:
     *      value - a pointer to a buffer to copy the value into.
     *
     *  Return Value:
     *      If the value is successfully parsed, SETTINGS_NO_ERROR is returned.
     *      Any other return value indicates a parse error.
     *
     *  See Also:
     *      GetSettingString(), GetKeyName()
     ************************************************************************/
    int
    GetKeyValue(const char *section,
                char *wkey, int len)
    {
        return RESFILE_GetKeyValue(res, section, wkey, len);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method returns the value of the key/value pair at
     *      the current location in the section
     *
     *  Input Parameters:
     *      section - the name of the section to fetch from
     *
     *  Output Parameters:
     *      value - where to put the current value
     *
     *  Return Value:
     *      ITS_SUCCESS - successful operation.  Any other return code
     *      indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *      This method is intended to operate with Rewind() and
     *      GetKeyName().  The user can call Lock(), Rewind() and then
     *      repeat calls to GetKeyName()/GetKeyValue() until the
     *      return code is not ITS_SUCCESS, indicating that the end
     *      of the section has been reached.  The user should finish
     *      with Unlock().
     *
     ************************************************************************/
    int
    GetKeyValue(const std::string& section, std::string& value)
    {
        int ret;
        char buf[MAX_STRING_LEN];

        buf[0] = 0;
        value.erase(value.begin(), value.end());

        ret = GetKeyValue(section.c_str(), buf, MAX_STRING_LEN);

        if (ret == ITS_SUCCESS)
        {
            value.assign(&buf[0], &buf[strlen(buf)]);
        }

        return ret;
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method will parse the key portion of a resource line, and
     *      return the key name to the user.
     *
     *  Input Parameters:
     *      string - the resource string to parse.
     *      len - the maximum key name length the user will tolerate.
     *
     *  Output Parameters:
     *      key - a pointer to a buffer to copy the key name into.
     *
     *  Return Value:
     *      If the key name is parsed successfully, SETTINGS_NO_ERROR is returned.
     *      Any other return code indicates an error parsing the resource line.
     *
     *  See Also:
     *      GetSettingString(), GetKeyValue()
     ************************************************************************/
    int
    GetKeyName(const char *section,
               char *key, int len)
    {
        return RESFILE_GetKeyName(res, section, key, len);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method returns the key of the key/value pair at
     *      the current location in the section
     *
     *  Input Parameters:
     *      section - the name of the section to fetch from
     *
     *  Output Parameters:
     *      key - where to put the current key
     *
     *  Return Value:
     *      ITS_SUCCESS - successful operation.  Any other return code
     *      indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *      This method is intended to operate with Rewind() and
     *      GetKeyValue().  The user can call Lock(), Rewind() and then
     *      repeat calls to GetKeyName()/GetKeyValue() until the
     *      return code is not ITS_SUCCESS, indicating that the end
     *      of the section has been reached.  The user should finish
     *      with Unlock().
     *
     ************************************************************************/
    int
    GetKeyName(const std::string& section, std::string& key)
    {
        int ret;
        char buf[MAX_STRING_LEN];

        buf[0] = 0;
        key.erase(key.begin(), key.end());

        ret = GetKeyName(section.c_str(), buf, MAX_STRING_LEN);

        if (ret == ITS_SUCCESS)
        {
            key.assign(&buf[0], &buf[strlen(buf)]);
        }

        return ret;
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method allows the user to randomly access a resource file to
     *      find the value associated with a specific key.
     *
     *  Input Parameters:
     *      search - a pointer to the key value to search for
     *      klen - the maximum value size the user will tolerate
     *
     *  Output Parameters:
     *      keyvalue - a pointer to a buffer to copy the value into if found.
     *
     *  Return Value:
     *      If the value is found, and successfully parsed, SETTINGS_NO_ERROR
     *          is returned.
     *      Any other return value indicates that the key was not found or
     *          that a processing error has occurred.
     *
     *  Notes:
     *      This method can be called even when parsing the file sequentially.
     *      It saves the current file position before searching for the key,
     *      and restores the file position before returning to the user.
     *
     ************************************************************************/
    int
    GetKeyValueOf(const char *section, const char *search,
                  char *keyvalue, int klen)
    {
        return RESFILE_GetKeyValueOf(res, section, search, keyvalue, klen);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method returns the value of the key/value pair of the
     *      given key.
     *
     *  Input Parameters:
     *      section - the name of the section to fetch from
     *      key - the name of the key to fetch the value for
     *
     *  Output Parameters:
     *      value - where to put the value of the key
     *
     *  Return Value:
     *      ITS_SUCCESS - successful operation.  Any other return code
     *      indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    GetKeyValueOf(const std::string& section, const std::string& key,
                  std::string& value)
    {
        int ret;
        char buf[MAX_STRING_LEN];

        buf[0] = 0;
        value.erase(value.begin(), value.end());

        ret = GetKeyValueOf(section.c_str(), key.c_str(),
                            buf, MAX_STRING_LEN);

        if (ret == ITS_SUCCESS)
        {
            value.assign(&buf[0], &buf[strlen(buf)]);
        }

        return ret;
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method adds a section to the resource file.
     *
     *  Input Parameters:
     *      section - the name of the section to add.
     *
     *  Notes:
     *      If a section with the same name already exists, the new section
     *      will not be added.
     *
     ************************************************************************/
    int
    AddSection(const char *section)
    {
        return RESFILE_AddSection(res, section);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Add a section with the given name to the database.
     *
     *  Input Parameters:
     *      section - the name of the section to add
     *
     *  Return Value:
     *     ITS_SUCCESS - successful operation.  Any other return code
     *     indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    AddSection(const std::string& section)
    {
        return AddSection(section.c_str());
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method removes a section from the resource file.
     *
     *  Input Parameters:
     *      section - the name of the section to remove.
     *
     *  Notes:
     *      The NULL (or global) section cannot be removed.
     *
     ************************************************************************/
    int
    RemSection(const char *section)
    {
        return RESFILE_RemSection(res, section);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Remove a section with the given name from the database.
     *
     *  Input Parameters:
     *      section - the name of the section to remove
     *
     *  Return Value:
     *     ITS_SUCCESS - successful operation.  Any other return code
     *     indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    RemSection(const std::string& section)
    {
        return RemSection(section.c_str());
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method adds a key/value pair to the resource file section.
     *
     *  Input Parameters:
     *      section - the name of the section to add to.
     *      key - the key to add
     *      value - the value for the key
     *
     *  Notes:
     *      If a key by the given name already exists, the new key will not
     *      be added.
     *
     ************************************************************************/
    int
    AddKeyValue(const char *section, const char *key, const char *value)
    {
        return RESFILE_AddKeyValue(res, section, key, value);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Add a key/value pair to the section with the given name in
     *      the database.
     *
     *  Input Parameters:
     *      section - the name of the section to add to
     *      key - the key to add
     *      value - the value for that key
     *
     *  Return Value:
     *     ITS_SUCCESS - successful operation.  Any other return code
     *     indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    AddKeyValue(const std::string& section,
                const std::string& key, const std::string& value)
    {
        return AddKeyValue(section.c_str(), key.c_str(), value.c_str());
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method removes a key/value pair to the resource file section.
     *
     *  Input Parameters:
     *      section - the name of the section to add to.
     *      key - the key to add
     *      value - the value for the key
     *
     *  Notes:
     *      If a key by the given name already exists, the new key will not
     *      be added.
     *
     ************************************************************************/
    int
    RemKeyValue(const char *section, const char *key)
    {
        return RESFILE_RemKeyValue(res, section, key);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Remove a key/value pair from the section with the given name in
     *      the database.
     *
     *  Input Parameters:
     *      section - the name of the section to remove from
     *      key - the key to remove
     *
     *  Return Value:
     *     ITS_SUCCESS - successful operation.  Any other return code
     *     indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    RemKeyValue(const std::string& section, const std::string& key)
    {
        return RemKeyValue(section.c_str(), key.c_str());
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Find the name of the database section after the one with
     *      this name
     *
     *  Input Parameters:
     *      section - the name of the current section
     *
     *  Return Value:
     *      The name of the next section, or NULL on error (section
     *      may not exist).
     *
     *  Notes:
     *      The return pointer is guaranteed only while the database
     *      is locked.
     *
     ************************************************************************/
    const char *
    GetNextSectionName(const char *section)
    {
        return (RESFILE_GetNextSectionName(res, section));
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Find the name of the database section after the one with
     *      this name
     *
     *  Input Parameters:
     *      section - the name of the current section
     *
     *  Return Value:
     *      The name of the next section, or NULL on error (section
     *      may not exist).
     *
     ************************************************************************/
    std::string
    GetNextSectionName(const std::string& section)
    {
        const char *ret;

        ret = RESFILE_GetNextSectionName(res, section.c_str());

        return (ret == NULL ? "" : ret);
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      This method reloads the resource database.
     *
     ************************************************************************/
    int
    Reload()
    {
        return RESFILE_Reload(res);
    }

    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Set the global alternate comment character
     *
     *  Input Parameters:
     *      nc - the new alternate comment character
     *
     *  Return Value:
     *      The value of the old alternate comment character
     *
     *  Notes:
     *      This function is not MT-safe.
     *
     ************************************************************************/
    static char
    SetAltCommentChar(char nc)
    {
        return RESFILE_SetAltCommentChar(nc);
    }
    /*.implementation:public,inline,ResourceManager
     ************************************************************************
     *  Purpose:
     *      Set whether comments are valid in other than column 1.
     *
     *  Input Parameters:
     *      onlyInColumnOne - if true, comment chars are valid only in
     *      column 1.
     *
     *  Return Value:
     *      The value of the old setting
     *
     *  Notes:
     *      The default behavior is for comment characters to be valid
     *      anywhere on the line.  Comment characters can be escaped
     *      with a backslash.
     *      This function is not MT-safe.
     *
     ************************************************************************/
    static bool
    SetCommentCharOnlyInColumnOne(bool onlyInColumnOne)
    {
        return RESFILE_SetCommentCharOnlyInColumnOne(onlyInColumnOne
                                                         ? ITS_TRUE
                                                         : ITS_FALSE) == ITS_TRUE;
    }

private:
    RESFILE_Manager* res;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_INIPARSE_H */
