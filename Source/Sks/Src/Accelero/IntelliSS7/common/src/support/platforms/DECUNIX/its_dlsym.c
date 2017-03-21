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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:03  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/19 20:59:22  mmiers
 * LOG: Avoid putting extra symbols into the namespace
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 18:30:28  mmiers
 * LOG: Move these back.  Support can't be dynamically loaded due to
 * LOG: WIN32.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.7  2001/04/27 21:44:03  yranade
 * LOG: Don't take the chance of returning NULL.
 * LOG:
 * LOG: Revision 1.6  2001/04/26 15:14:57  mmiers
 * LOG: Add error function.
 * LOG:
 * LOG: Revision 1.5  2001/03/29 18:21:15  mmiers
 * LOG: Debugging the engine.  Runs now.
 * LOG:
 * LOG: Revision 1.4  2001/03/29 18:00:41  mmiers
 * LOG: error message on dlopen fail.
 * LOG:
 * LOG: Revision 1.3  2001/03/29 03:07:34  mmiers
 * LOG: Start debugging.
 * LOG:
 * LOG: Revision 1.2  2001/03/09 16:08:26  mmiers
 * LOG: Add DLL modifier.
 * LOG:
 * LOG: Revision 1.1  2001/03/02 22:44:15  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 1.1  2001/02/08 22:48:56  mmiers
 * LOG: Get it to work on Linux.
 * LOG:
 * LOG: Revision 1.1  2001/02/08 22:43:05  mmiers
 * LOG: Add dynamic symbol resolution.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dlfcn.h>

#include <its_dlsym.h>
#include <its_mutex.h>
#include <its_object.h>

#ident "$Id: its_dlsym.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*
 * cache list
 */
static DLSYM_CacheEntry *cache = NULL;

static ITS_MUTEX        cacheGate;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a handle to a shared library.
 *
 *  Input Parameters:
 *      obj - the object being created
 *      args - vararg list for creation
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - object created successfully.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Create(ITS_Object obj, va_list args)
{
    DLSYM_CacheEntry *node;
    DLSYM_Manager *manager = (DLSYM_Manager *)obj;
    const char *dllName;

    dllName = va_arg(args, const char *);

    if (MUTEX_AcquireMutex(&cacheGate) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* look for it in the cache first */
    for (node = cache; node != NULL; node = node->next)
    {
        /* handle NULL ok.  That indicates self. */
        if (node->name == NULL && dllName == NULL)
        {
            DLSYM_HANDLE(manager) = node->handle;

            node->refCount++;

            MUTEX_ReleaseMutex(&cacheGate);

            return (ITS_SUCCESS);
        }

        if (dllName && node->name && strcmp(node->name, dllName) == 0)
        {
            DLSYM_HANDLE(manager) = node->handle;

            node->refCount++;

            MUTEX_ReleaseMutex(&cacheGate);

            return (ITS_SUCCESS);
        }
    }

    /* not there, have to load it. */
    DLSYM_HANDLE(manager) = dlopen(dllName, RTLD_LAZY|RTLD_GLOBAL);

    if (DLSYM_HANDLE(manager) == NULL)
    {
        MUTEX_ReleaseMutex(&cacheGate);

        return (ITS_ENOTFOUND);
    }

    /* new cache entry for it */
    node = (DLSYM_CacheEntry *)calloc(1, sizeof(DLSYM_CacheEntry));
    if (node == NULL)
    {
        dlclose(DLSYM_HANDLE(manager));

        MUTEX_ReleaseMutex(&cacheGate);

        return (ITS_ENOMEM);
    }

    /* fill in the node info */
    if (dllName)
    {
        node->name = strdup(dllName);
        if (node->name == NULL)
        {
            dlclose(DLSYM_HANDLE(manager));

            free(node);

            MUTEX_ReleaseMutex(&cacheGate);

            return (ITS_ENOMEM);
        }
    }
    else
    {
        node->name = NULL;
    }

    node->refCount = 1;
    node->handle = DLSYM_HANDLE(manager);

    /* add to cache */
    node->next = cache;
    cache = node;

    MUTEX_ReleaseMutex(&cacheGate);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the handle to the shared object
 *
 *  Input Parameters:
 *      obj = the handle to be destroyed
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
Destroy(ITS_Object obj)
{
    DLSYM_Manager *manager = (DLSYM_Manager *)obj;
    DLSYM_CacheEntry **node;

    if (MUTEX_AcquireMutex(&cacheGate) != ITS_SUCCESS)
    {
        return;
    }

    /* decrement cache reference */
    for (node = &cache; *node != NULL; node = &(*node)->next)
    {
        if ((*node)->handle == DLSYM_HANDLE(manager))
        {
            (*node)->refCount--;

            /* yank it from the cache */
            if ((*node)->refCount <= 0)
            {
                DLSYM_CacheEntry *tmp;

                tmp = *node;

                *node = (*node)->next;

                dlclose(tmp->handle);

                if (tmp->name)
                {
                    free(tmp->name);
                }
                free(tmp);

                MUTEX_ReleaseMutex(&cacheGate);

                return;
            }
        }
    }

    /* not in cache.  Broken, but try to handle it. */
    dlclose(DLSYM_HANDLE(manager));

    MUTEX_ReleaseMutex(&cacheGate);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Resolve a symbol in the shared object
 *
 *  Input Parameters:
 *      manager - handle to the shared object
 *      symName - the symbol to resolve
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      a pointer to the resolved object.  NULL is returned if the object
 *      is not found.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_DLSYM
Resolve(DLSYM_Manager *manager, const char *symName)
{
    return dlsym(DLSYM_HANDLE(manager), symName);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class part
 *
 *  Input Parameters:
 *      objClass - class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful initialization
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    if (MUTEX_CreateMutex(&cacheGate, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record
 *
 *  Input Parameters:
 *      objClass - the class to destroy
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
ClassDestroy(ITS_Class objClass)
{
    MUTEX_DeleteMutex(&cacheGate);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class part (inheritance hook).
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
static int
ClassPartInitialize(ITS_Class objClass)
{
    if (DLSYM_CLASS_RESOLVE(objClass) == NULL)
    {
        DLSYM_CLASS_RESOLVE(objClass) =
            DLSYM_CLASS_RESOLVE(ITS_CLASS_SUPERCLASS(objClass));
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class part.
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
ClassPartDestroy(ITS_Class objClass)
{
}

/*
 * the class record
 */
ITSDLLAPI DLSYM_ClassRec itsDLSYM_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsCORE_ClassRec,   /* superclass is CORE */
        sizeof(DLSYM_Manager),          /* sizeof instance */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        DLSYM_CLASS_NAME,               /* class name */
        ClassInit,                      /* class initialize */
        ClassDestroy,                   /* class destroy */
        ClassPartInitialize,            /* class initialize part */
        ClassPartDestroy,               /* class destroy part */
        Create,                         /* instantiate */
        Destroy,                        /* destroy */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        ITS_INST_HASH_INHERIT,          /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* resolve part */
    {
        Resolve
    }
};

ITSDLLAPI ITS_Class itsDLSYM_Class = (ITS_Class)&itsDLSYM_ClassRec;

#undef DLSYM_Create
#undef DLSYM_Destroy
#undef DLSYM_Resolve

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create a handle to a shared library.
 *
 *  Input Parameters:
 *      dllName - the name of the shared lib
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the created handle, or NULL
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI DLSYM_Manager *
DLSYM_Create(const char *dllName)
{
    return (DLSYM_Manager *)ITS_ConstructObject(itsDLSYM_Class, dllName);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy the handle to the shared object
 *
 *  Input Parameters:
 *      obj = the handle to be destroyed
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
DLSYM_Destroy(DLSYM_Manager *obj)
{
    ITS_DestructObject((ITS_Object)obj);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Resolve a symbol in the shared object
 *
 *  Input Parameters:
 *      manager - handle to the shared object
 *      symName - the symbol to resolve
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      a pointer to the resolved object.  NULL is returned if the object
 *      is not found.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_DLSYM
DLSYM_Resolve(DLSYM_Manager *manager, const char *symName)
{
    return DLSYM_CLASS_RESOLVE(ITS_OBJ_CLASS(manager))(manager, symName);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return an error text string if a load or resolve fails
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
 *      a string with the error reason specified
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char *
DLSYM_Error()
{
    const char *ret;

    ret = dlerror();

    if (ret == NULL)
    {
        return "(error not set)";
    }

    return (ret);
}

