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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:44  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:41  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:00  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:19  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2004/04/16 05:07:54  akumar
 * LOG: Modified to allow SIP configurable thru XML.
 * LOG:
 * LOG: Revision 8.2  2003/06/16 13:26:48  mmanikandan
 * LOG: Xml Persistency is added.
 * LOG:
 * LOG: Revision 8.1  2003/02/27 15:46:56  mmiers
 * LOG: Implementation was getting too large.  Split into
 * LOG: manageable chunks.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ident "$Id: engine_objs.c,v 1.1.1.1 2007-10-08 11:11:17 bsccs2 Exp $"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <engine.h>
#include <expat.h>
#include "engine_intern.h"

extern ITS_BOOLEAN  ENGINE_inParser;

#undef ITS_C_ASSERT
#define ITS_C_ASSERT(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_ASSERT_PRINT(assertion);                                        \
        if (ENGINE_inParser)                                                  \
        {                                                                     \
            ENGINE_LinePrint();                                               \
        }                                                                     \
        abort();                                                              \
    }


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a lib cache object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_LibCacheClass, app, libName);
 *
 *  See Also:
 ****************************************************************************/
static int
CacheCreate(ITS_Object obj, va_list args)
{
    char *libName, buf[ITS_PATH_MAX];
    ENGINE_LibCache crec = (ENGINE_LibCache)obj;
    ENGINE_Application app;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    libName = va_arg(args, char *);

    ITS_C_REQUIRE(app != NULL);

    /* init the rec */
    ENGINE_LC_NEXT(crec) = NULL;
    ENGINE_LC_APP(crec) = app;
    if (libName && strlen(libName) != 0)
    {
        ENGINE_LC_LIB_NAME(crec) = strdup(libName);

        ITS_C_ASSERT(ENGINE_LC_LIB_NAME(crec) != NULL);
    }

    /* lookup local */
    ENGINE_LC_LIBRARY(crec) = DLSYM_Create(ENGINE_LC_LIB_NAME(crec));

    /* if not found, try global */
    if (ENGINE_LC_LIBRARY(crec) == NULL)
    {
        strcpy(buf, APPL_GetLibDir());
        strcat(buf, ENGINE_LC_LIB_NAME(crec));

        ENGINE_LC_LIBRARY(crec) = DLSYM_Create(buf);

        if (ENGINE_LC_LIBRARY(crec) == NULL)
        {
            free(ENGINE_LC_LIB_NAME(crec));

            return (ITS_ENOTFOUND);
        }
    }

    /* tail add */
    for (list = &ENGINE_APP_LIB_CACHE(app);
         *list;
         list = &ENGINE_LC_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a lib cache object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
CacheDestroy(ITS_Object obj)
{
    ENGINE_LibCache crec = (ENGINE_LibCache)obj;

    DLSYM_Destroy(ENGINE_LC_LIBRARY(crec));

    if (ENGINE_LC_LIB_NAME(crec))
    {
        free(ENGINE_LC_LIB_NAME(crec));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare cache records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
CacheCompare(ITS_Object o1, ITS_Object o2)
{
    /* init the rec */
    if ((!ENGINE_LC_LIB_NAME(o1) && !ENGINE_LC_LIB_NAME(o2)) ||
        (ENGINE_LC_LIB_NAME(o1) && ENGINE_LC_LIB_NAME(o2) &&
         !strlen(ENGINE_LC_LIB_NAME(o1)) && !strlen(ENGINE_LC_LIB_NAME(o2))) ||
        (ENGINE_LC_LIB_NAME(o1) && ENGINE_LC_LIB_NAME(o2) &&
         strlen(ENGINE_LC_LIB_NAME(o1)) && strlen(ENGINE_LC_LIB_NAME(o2)) &&
         strcmp(ENGINE_LC_LIB_NAME(o1), ENGINE_LC_LIB_NAME(o2)) == 0))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_LibCacheClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_LibCacheRec),     /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Lib Cache Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CacheCreate,                    /* instantiate */
        CacheDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        CacheCompare,                   /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_LibCacheClass = &itsENGINE_LibCacheClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a parser extension object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ParserExtensionClass, app,
 *                          "libNMS.so", "NMS-Data"
 *                          "NMS_ParseStart", "NMS_ParseEnd",
 *                          "NMS_ConvertParserData");
 *
 *  See Also:
 ****************************************************************************/
static int
ExtensionCreate(ITS_Object obj, va_list args)
{
    char *libName, *elemName;
    char *start = NULL, *stop = NULL, *xlate = NULL, *diff = NULL;
    ENGINE_ParserExtension pext = (ENGINE_ParserExtension)obj;
    ENGINE_Application app;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    libName = va_arg(args, char *);
    elemName = va_arg(args, char *);
    start = va_arg(args, char *);
    stop = va_arg(args, char *);
    xlate = va_arg(args, char *);
    diff = va_arg(args, char *);

    ITS_C_REQUIRE(app != NULL);
    ITS_C_REQUIRE(elemName != NULL && strlen(elemName) != 0);

    ENGINE_PE_NEXT(pext) = NULL;
    ENGINE_PE_ELEMENT_NAME(pext) = strdup(elemName);
    ENGINE_PE_LIB_CACHE_ENTRY(pext) = ENGINE_LibGet(app, libName);
    ENGINE_PE_USER_DATA(pext) = NULL;

    ITS_C_ASSERT(ENGINE_PE_ELEMENT_NAME(pext) != NULL);
    ITS_C_ASSERT(ENGINE_PE_LIB_CACHE_ENTRY(pext) != NULL);

    if (start == NULL && stop == NULL && xlate == NULL)
    {
        printf("Are you kidding me?\n");

        return (ITS_EINVALIDARGS);
    }

    if (start && strlen(start) != 0)
    {
        ENGINE_PE_START_FUNC(pext) = (ENGINE_ParseStartFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          start);

        if (ENGINE_PE_START_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       start, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_START_FUNC_NAME(pext) = strdup(start);
        }
    }
    if (stop && strlen(stop) != 0)
    {
        ENGINE_PE_STOP_FUNC(pext) = (ENGINE_ParseStopFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          stop);

        if (ENGINE_PE_STOP_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       stop, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_STOP_FUNC_NAME(pext) = strdup(stop);
        }
    }
    if (xlate && strlen(xlate) != 0)
    {
        ENGINE_PE_XLATE_FUNC(pext) = (ENGINE_ResourceXlateFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          xlate);

        if (ENGINE_PE_XLATE_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       xlate, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_XLATE_FUNC_NAME(pext) = strdup(xlate);
        }
    }
    if (diff && strlen(diff) != 0)
    {
        ENGINE_PE_DIFF_FUNC(pext) = (ENGINE_ExtensionDiffFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          diff);

        if (ENGINE_PE_DIFF_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       diff, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_DIFF_FUNC_NAME(pext) = strdup(diff);
        }
    }

    /* tail add */
    for (list = &ENGINE_APP_PARSER_EXTENSIONS(app);
         *list;
         list = &ENGINE_PE_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
ExtensionDestroy(ITS_Object obj)
{
    ENGINE_ParserExtension pext = (ENGINE_ParserExtension)obj;

    free(ENGINE_PE_ELEMENT_NAME(pext));

    if (ENGINE_PE_START_FUNC_NAME(pext))
    {
        free(ENGINE_PE_START_FUNC_NAME(pext));
    }

    if (ENGINE_PE_STOP_FUNC_NAME(pext))
    {
        free(ENGINE_PE_STOP_FUNC_NAME(pext));
    }

    if (ENGINE_PE_XLATE_FUNC_NAME(pext))
    {
        free(ENGINE_PE_XLATE_FUNC_NAME(pext));
    }

    if (ENGINE_PE_DIFF_FUNC_NAME(pext))
    {
        free(ENGINE_PE_DIFF_FUNC_NAME(pext));
    }

    if (ENGINE_PE_USER_DATA(pext))
    {
        free(ENGINE_PE_USER_DATA(pext));
    }

    if (ENGINE_PE_ELEMENT_DATA(pext))
    {
        int idx;
        for (idx = 0; 
             idx < ENGINE_PE_ELEMENT_DATA_COUNT(pext); 
             idx++)
        {
            free(ENGINE_PE_ELEMENT_DATA(pext)[idx]);
        }
        free(ENGINE_PE_ELEMENT_DATA(pext));
    }

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare extension records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ExtensionCompare(ITS_Object o1, ITS_Object o2)
{
    if (((ENGINE_PE_ELEMENT_NAME(o1) == NULL) ^ 
         (ENGINE_PE_ELEMENT_NAME(o2) == NULL)) ||
        (ENGINE_PE_ELEMENT_NAME(o1) &&
         strcmp(ENGINE_PE_ELEMENT_NAME(o1),
                ENGINE_PE_ELEMENT_NAME(o2)) != 0) ||
        ENGINE_PE_LIB_CACHE_ENTRY(o1) != ENGINE_PE_LIB_CACHE_ENTRY(o2) ||
        ENGINE_PE_START_FUNC(o1) != ENGINE_PE_START_FUNC(o2) ||
        ENGINE_PE_STOP_FUNC(o1) != ENGINE_PE_STOP_FUNC(o2) ||
        ENGINE_PE_XLATE_FUNC(o1) != ENGINE_PE_XLATE_FUNC(o2) ||
        ENGINE_PE_DIFF_FUNC(o1) != ENGINE_PE_DIFF_FUNC(o2))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ParserExtensionClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ParserExtensionRec),/* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Extension Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ExtensionCreate,                /* instantiate */
        ExtensionDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ExtensionCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ParserExtensionClass =
    &itsENGINE_ParserExtensionClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_FeatureClass, app, "SCTP",
 *                          "libSCTP.so", "itsSCTP_Class",
 *                          options, numOptions);
 *
 *  See Also:
 ****************************************************************************/
static int
FeatureCreate(ITS_Object obj, va_list args)
{
    char *featName, *libName, *className, **options;
    ENGINE_Feature feat = (ENGINE_Feature)obj;
    ENGINE_Application app;
    ITS_Object *list, tail;
    int numOptions;
    ITS_Class *cl;

    app = va_arg(args, ENGINE_Application);
    featName = va_arg(args, char *);
    libName = va_arg(args, char *);
    className = va_arg(args, char *);
    options = va_arg(args, char **);
    numOptions = va_arg(args, int);

    ITS_C_REQUIRE(app != NULL);
    ITS_C_REQUIRE(featName != NULL && strlen(featName) != 0);
    ITS_C_REQUIRE(className != NULL && strlen(className) != 0);
    if (numOptions)
    {
        ITS_C_REQUIRE(options != NULL);
    }

    ENGINE_FEAT_NEXT(feat) = NULL;
    ENGINE_FEAT_PREV(feat) = NULL;
    ENGINE_FEAT_APP(feat) = app;
    ENGINE_FEAT_NAME(feat) = strdup(featName);
    ENGINE_FEAT_CLASS_NAME(feat)=strdup(className);
    ENGINE_FEAT_LIB_CACHE_ENTRY(feat) = ENGINE_LibGet(app, libName);

    ITS_C_ASSERT(ENGINE_FEAT_NAME(feat) != NULL);
    ITS_C_ASSERT(ENGINE_FEAT_LIB_CACHE_ENTRY(feat) != NULL);

    cl = (ITS_Class *)
        DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_FEAT_LIB_CACHE_ENTRY(feat)),
                      className);

    if (cl == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   className, DLSYM_Error());
            fflush(stdout);
        }

        return (ITS_ENOTFOUND);
    }

    ENGINE_FEAT_CLASS_REC(feat) = *cl;

    ENGINE_FEAT_OPTIONS(feat) = options;
    ENGINE_FEAT_NUM_OPTIONS(feat) = numOptions;

    /* tail add */
    for (list = &ENGINE_APP_FEATURES(app), tail = ENGINE_APP_FEATURES(app);
         *list;
         tail = *list, list = &ENGINE_FEAT_NEXT(*list))
    {
    }
    *list = obj;
    ENGINE_FEAT_PREV(feat) = tail;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
FeatureDestroy(ITS_Object obj)
{
    ENGINE_Feature feat = (ENGINE_Feature)obj;
    int i;

    free(ENGINE_FEAT_NAME(feat));

    if (ENGINE_FEAT_CLASS_NAME(feat))
    {
        free(ENGINE_FEAT_CLASS_NAME(feat));
    }

    if (ENGINE_FEAT_NUM_OPTIONS(feat))
    {
        for (i = 0; i < ENGINE_FEAT_NUM_OPTIONS(feat); i++)
        {
            free(ENGINE_FEAT_OPTIONS(feat)[i]);
        }

        free(ENGINE_FEAT_OPTIONS(feat));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare feature records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FeatureCompare(ITS_Object o1, ITS_Object o2)
{
    int i;

    if (strcmp(ENGINE_FEAT_NAME(o1), ENGINE_FEAT_NAME(o2)) != 0 ||
        ENGINE_FEAT_LIB_CACHE_ENTRY(o1) != ENGINE_FEAT_LIB_CACHE_ENTRY(o2) ||
        ENGINE_FEAT_CLASS_REC(o1) != ENGINE_FEAT_CLASS_REC(o2) ||
        ENGINE_FEAT_NUM_OPTIONS(o1) != ENGINE_FEAT_NUM_OPTIONS(o2))
    {
        return (ITS_FALSE);
    }

    for (i = 0; i < ENGINE_FEAT_NUM_OPTIONS(o1); i++)
    {
        if (strcmp(ENGINE_FEAT_OPTIONS(o1)[i],
                   ENGINE_FEAT_OPTIONS(o2)[i]) != 0)
        {
            return (ITS_FALSE);
        }
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_FeatureClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_FeatureRec),      /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Feature Class",         /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        FeatureCreate,                  /* instantiate */
        FeatureDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        FeatureCompare,                 /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FeatureClass = &itsENGINE_FeatureClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a trace config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TraceClass, traceList, "levelName",
 *                          levelMask);
 *
 *  See Also:
 ****************************************************************************/
static int
TraceCreate(ITS_Object obj, va_list args)
{
    char *levelName;
    ENGINE_Trace trace = (ENGINE_Trace)obj;
    ITS_Object* traceList;
    int levelMask;
    ITS_Object *list;

    traceList = va_arg(args, ITS_Object *);
    levelName = va_arg(args, char *);
    levelMask = va_arg(args, int);

    ITS_C_REQUIRE(traceList != NULL);
    ITS_C_REQUIRE(levelName != NULL && strlen(levelName) != 0);
    ITS_C_REQUIRE(levelMask != 0);

    ENGINE_TL_NEXT(trace) = NULL;
    ENGINE_TL_LEVEL_NAME(trace) = strdup(levelName);
    ENGINE_TL_LEVEL_MASK(trace) = levelMask;

    ITS_C_ASSERT(ENGINE_TL_LEVEL_NAME(trace) != NULL);

    /* tail add */
    for (list = traceList;
         *list;
         list = &ENGINE_TL_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a trace config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
TraceDestroy(ITS_Object obj)
{
    ENGINE_Trace trace = (ENGINE_Trace)obj;

    free(ENGINE_TL_LEVEL_NAME(trace));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare trace records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TraceCompare(ITS_Object o1, ITS_Object o2)
{
    /*
     * don't bother with this.  It's simpler just to adjust the trace levels
     */
    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TraceClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_TraceRec),        /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Trace Class",           /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        TraceCreate,                    /* instantiate */
        TraceDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        TraceCompare,                   /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TraceClass = &itsENGINE_TraceClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_RouteClass, application, pointCode,
 *                          type, style, ...);
 *
 *  See Also:
 ****************************************************************************/
static int
RouteCreate(ITS_Object obj, va_list args)
{
    ENGINE_Route route = (ENGINE_Route)obj;
    ITS_UINT pointCode, mask;
    ROUTE_TYPE type;
    ROUTE_CRITERIA style;
    SS7_Family family;
    ENGINE_Application app;
    ITS_Object *list;
    int ret;

    app = va_arg(args, ENGINE_Application);
    mask = va_arg(args, ITS_UINT);
    pointCode = va_arg(args, ITS_UINT);
    type = va_arg(args, ROUTE_TYPE);
    style = va_arg(args, ROUTE_CRITERIA);
    family = va_arg(args, SS7_Family);

    ITS_C_ASSERT(app != NULL);

    ENGINE_RT_NEXT(route) = NULL;

    ret = ROUTE_ParseRouteMatchInfo(&ENGINE_RT_INFO(route), pointCode,
                                    type, style, family, &args);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ENGINE_RT_INFO(route).basic.mask = mask;

    /* tail add */
    for (list = &ENGINE_APP_ROUTES(app);
         *list;
         list = &ENGINE_RT_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
RouteDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare route records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
RouteCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_RT_INFO(o1).basic.type != ENGINE_RT_INFO(o2).basic.type ||
        ENGINE_RT_INFO(o1).basic.style != ENGINE_RT_INFO(o2).basic.style ||
        ENGINE_RT_INFO(o1).basic.dpc != ENGINE_RT_INFO(o2).basic.dpc ||
        ENGINE_RT_INFO(o1).priority != ENGINE_RT_INFO(o2).priority)
    {
        return (ITS_FALSE);
    }

    switch (ENGINE_RT_INFO(o1).basic.style)
    {
    case ROUTE_DPC_NI:
        if ((ENGINE_RT_INFO(o1).basic.criteria.sio & ROUTE_NI_MASK) !=
            (ENGINE_RT_INFO(o2).basic.criteria.sio & ROUTE_NI_MASK))
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_NI:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            (ENGINE_RT_INFO(o1).basic.criteria.sio & ROUTE_NI_MASK) !=
            (ENGINE_RT_INFO(o2).basic.criteria.sio & ROUTE_NI_MASK))
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO_SSN_RANGE:
    case ROUTE_DPC_SIO_CIC_RANGE:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.range.begin !=
            ENGINE_RT_INFO(o2).basic.criteria.range.begin ||
            ENGINE_RT_INFO(o1).basic.criteria.range.end !=
            ENGINE_RT_INFO(o2).basic.criteria.range.end)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO_SSN:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.ssn !=
            ENGINE_RT_INFO(o2).basic.criteria.ssn)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO_CIC:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.cic !=
            ENGINE_RT_INFO(o2).basic.criteria.cic)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.range.begin !=
            ENGINE_RT_INFO(o2).basic.criteria.range.begin ||
            ENGINE_RT_INFO(o1).basic.criteria.range.end !=
            ENGINE_RT_INFO(o2).basic.criteria.range.end)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO_SSN:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.ssn !=
            ENGINE_RT_INFO(o2).basic.criteria.ssn)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO_CIC:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.cic !=
            ENGINE_RT_INFO(o2).basic.criteria.cic)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_UDEF:
        return (ITS_FALSE);

    default:
        return (ITS_FALSE);
    }
    
    /* NOTREACHED */
}

ITSDLLAPI ITS_ClassRec itsENGINE_RouteClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_RouteRec),        /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Route Class",           /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        RouteCreate,                    /* instantiate */
        RouteDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        RouteCompare,                   /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_RouteClass = &itsENGINE_RouteClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_DestinationClass, app,
 *                          pointCode, ni,
 *                          mtp3Var, isupVar, sccpVar, tcapVar,
 *                          tupVar, dupVar);
 *
 *  See Also:
 ****************************************************************************/
static int
DestCreate(ITS_Object obj, va_list args)
{
    ENGINE_Dest dest = (ENGINE_Dest)obj;
    ENGINE_Application app;
    ITS_Object *list;
    char *isupVar;

    app = va_arg(args, ENGINE_Application);
    ENGINE_DE_PC(dest) = va_arg(args, ITS_UINT);
    ENGINE_DE_NI(dest) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_DE_FAMILY(dest) = va_arg(args, SS7_Family);
    ENGINE_DE_MTP3(dest) = va_arg(args, ITS_INT);
    isupVar = va_arg(args, char *);
    ENGINE_DE_SCCP(dest) = va_arg(args, ITS_INT);
    ENGINE_DE_TCAP(dest) = va_arg(args, ITS_INT);
    ENGINE_DE_TUP(dest) = va_arg(args, ITS_INT);
    ENGINE_DE_DUP(dest) = va_arg(args, ITS_INT);

    ITS_C_ASSERT(app != NULL);

    if (isupVar)
    {
        ENGINE_DE_ISUP(dest) = strdup(isupVar);
        if (ENGINE_DE_ISUP(dest) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

    ENGINE_DE_NEXT(dest) = NULL;

    /* tail add */
    for (list = &ENGINE_APP_DESTS(app);
         *list;
         list = &ENGINE_DE_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
DestDestroy(ITS_Object obj)
{
    if (ENGINE_DE_ISUP(obj))
    {
        free(ENGINE_DE_ISUP(obj));
    }

    if (ENGINE_DE_ISUP_ATTR(obj))
    {
        ITS_DestructObject(ENGINE_DE_ISUP_ATTR(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare route records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
DestCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_DE_PC(o1) == ENGINE_DE_PC(o2) &&
        ENGINE_DE_NI(o1) == ENGINE_DE_NI(o2) &&
        ENGINE_DE_FAMILY(o1) == ENGINE_DE_FAMILY(o2) &&
        ENGINE_DE_MTP3(o1) == ENGINE_DE_MTP3(o2) &&
        (ENGINE_DE_ISUP(o1) != NULL && ENGINE_DE_ISUP(o2) != NULL &&
         strcmp(ENGINE_DE_ISUP(o1), ENGINE_DE_ISUP(o2)) == 0) &&
        ENGINE_DE_SCCP(o1) == ENGINE_DE_SCCP(o2) &&
        ENGINE_DE_TCAP(o1) == ENGINE_DE_TCAP(o2) &&
        ENGINE_DE_TUP(o1) == ENGINE_DE_TUP(o2) &&
        ENGINE_DE_DUP(o1) == ENGINE_DE_DUP(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_DestClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_DestRec),         /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Dest Class",            /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        DestCreate,                     /* instantiate */
        DestDestroy,                    /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        DestCompare,                    /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_DestClass = &itsENGINE_DestClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a link set config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_LinkSetClass, application,
 *                          adjacent, lpc, id, ni, numToStart,
 *                          adjacentSTP, isCLinkSet, is5Bit);
 *
 *  See Also:
 ****************************************************************************/
static int
LinkSetCreate(ITS_Object obj, va_list args)
{
    ENGINE_LinkSet linkSet = (ENGINE_LinkSet)obj;
    ENGINE_Application app;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    ENGINE_LS_ADJ(linkSet) = va_arg(args, ITS_UINT);
    ENGINE_LS_LOC(linkSet) = va_arg(args, ITS_UINT);
    ENGINE_LS_ID(linkSet) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LS_NI(linkSet) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LS_NUM_TO_START(linkSet) = va_arg(args, ITS_UINT);
    ENGINE_LS_ADJACENT_STP(linkSet) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LS_IS_C(linkSet) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LS_IS_5BIT(linkSet) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LS_FAMILY(linkSet) = va_arg(args, SS7_Family);
    ENGINE_LS_NEXT(linkSet) = NULL;

    ITS_C_ASSERT(app != NULL);

    /* tail add */
    for (list = &ENGINE_APP_LINK_SETS(app);
         *list;
         list = &ENGINE_LS_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
LinkSetDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare linkSet records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
LinkSetCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_LS_ADJ(o1) == ENGINE_LS_ADJ(o2) &&
        ENGINE_LS_ID(o1) == ENGINE_LS_ID(o2) &&
        ENGINE_LS_FAMILY(o1) == ENGINE_LS_FAMILY(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_LinkSetClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_LinkSetRec),      /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE LinkSet Class",         /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        LinkSetCreate,                  /* instantiate */
        LinkSetDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        LinkSetCompare,                 /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_LinkSetClass = &itsENGINE_LinkSetClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a link config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_LinkClass, &linkList,
 *                          set, code, pri, initActive,
 *                          termFixed, linkFixed, terminal, link);
 *
 *  See Also:
 ****************************************************************************/
static int
LinkCreate(ITS_Object obj, va_list args)
{
    ENGINE_Link link = (ENGINE_Link)obj;
    ITS_Object *rlist, *list;

    rlist = va_arg(args, ITS_Object *);
    ENGINE_LN_SET(link) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LN_CODE(link) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LN_PRI(link) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LN_INIT_ACTIVE(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_TERM_FIXED(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_LINK_FIXED(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_TERMINAL(link) = (ITS_USHORT)va_arg(args, ITS_UINT);
    ENGINE_LN_CIRCUIT(link) = (ITS_USHORT)va_arg(args, ITS_UINT);
    ENGINE_LN_IS_SAAL(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_IS_LOCAL(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_FAMILY(link) = va_arg(args, SS7_Family);
    ENGINE_LN_NEXT(link) = NULL;

    ITS_C_ASSERT(rlist != NULL);

    /* tail add */
    for (list = rlist; *list; list = &ENGINE_LN_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a link config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
LinkDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare link records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
LinkCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_LN_SET(o1) == ENGINE_LN_SET(o2) &&
        ENGINE_LN_CODE(o1) == ENGINE_LN_CODE(o2) &&
        ENGINE_LN_PRI(o1) == ENGINE_LN_PRI(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_LinkClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_LinkRec),         /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Link Class",            /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        LinkCreate,                     /* instantiate */
        LinkDestroy,                    /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        LinkCompare,                    /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_LinkClass = &itsENGINE_LinkClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse transport specific information
 *
 *  Input Parameters:
 *      part = the part to parse into
 *      args = the transport specific args
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
 ****************************************************************************/
static int
ParseTransportSpecifics(ENGINE_TransportSpecifics specs,
                               va_list args)
{
    char *tmp;

    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(specs)))
    {
    case ITS_TRANSPORT_SS7:
        /* vendor lib */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).ss7Specs.vendorName = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).ss7Specs.vendorName != NULL);

        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).ss7Specs.vendorLib = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).ss7Specs.vendorLib != NULL);

        /* vendor class */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).ss7Specs.vendorClass = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).ss7Specs.vendorClass != NULL);
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        /* client path */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).fifoSpecs.clientPath = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).fifoSpecs.clientPath != NULL);

        /* server path */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).fifoSpecs.serverPath = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).fifoSpecs.serverPath != NULL);
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        /* socket domain */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).tcpSpecs.socketDomain = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.socketDomain != NULL);

        /* server path */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).tcpSpecs.serverPath = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.serverPath != NULL);

        /* server port */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).tcpSpecs.serverPort = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.serverPort != NULL);

        /* retry delay (optional) */
        tmp = va_arg(args, char *);
        if (tmp && strlen(tmp) != 0)
        {
            ENGINE_TS_DATA(specs).tcpSpecs.retryDelay = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.retryDelay != NULL);
        }

        /* retry count (optional) */
        tmp = va_arg(args, char *);
        if (tmp && strlen(tmp) != 0)
        {
            ENGINE_TS_DATA(specs).tcpSpecs.retryCount = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.retryCount != NULL);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            /* local PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).gdiSpecs.localPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).gdiSpecs.localPC != NULL);

            /* remote PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).gdiSpecs.remotePC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).gdiSpecs.remotePC != NULL);

            /* remote SSN */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN != NULL);
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            /* local PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.localPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.localPC != NULL);

            /* adjacent PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.adjacentPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.adjacentPC != NULL);

            /* allowed on open */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen != NULL);

            /* user upper layer */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer != NULL);
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* local PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).imalSpecs.localPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).imalSpecs.localPC != NULL);

            /* adjacent PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).imalSpecs.adjacentPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).imalSpecs.adjacentPC != NULL);

            /* timeout */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut != NULL);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        /* local host */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).udpSpecs.localHost = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).udpSpecs.localHost != NULL);

        /* local port */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).udpSpecs.localPort = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).udpSpecs.localPort != NULL);

        /* associates */
        ENGINE_TS_DATA(specs).udpSpecs.associates =
            va_arg(args, char **);
        ENGINE_TS_DATA(specs).udpSpecs.numAssociates = va_arg(args, int);
        if (ENGINE_TS_DATA(specs).udpSpecs.numAssociates)
        {
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).udpSpecs.associates != NULL);
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            ENGINE_TS_DATA(specs).sctpSpecs.extraHomes = va_arg(args, char **);
            ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes = va_arg(args, int);

            if (ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes)
            {
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.extraHomes != NULL);
            }

            /* max in streams */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams != NULL);
            }

            /* num out streams */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams != NULL);
            }

            /* max attempts */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts != NULL);
            }

            /* cookie life */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.cookieLife = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.cookieLife != NULL);
            }

            /* hb on */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.hbOn = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.hbOn != NULL);
            }

            /* init time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut != NULL);
            }

            /* send time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut != NULL);
            }

            /* recv time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut != NULL);
            }

            /* hb time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut != NULL);
            }

            /* shutdown time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut != NULL);
            }

            /* pmtu time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut != NULL);
            }

            /* is client */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.isClient = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.isClient != NULL);
            }

            /* payload type */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.payloadType = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.payloadType != NULL);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free transport specific args
 *
 *  Input Parameters:
 *      part - the part to free
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
FreeTransportSpecifics(ENGINE_TransportSpecifics specs)
{
    int i;

    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(specs)))
    {
    case ITS_TRANSPORT_SS7:
        /* vendor lib */
        free(ENGINE_TS_DATA(specs).ss7Specs.vendorLib);

        /* vendor class */
        free(ENGINE_TS_DATA(specs).ss7Specs.vendorClass);
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        /* client path */
        free(ENGINE_TS_DATA(specs).fifoSpecs.clientPath);

        /* server path */
        free(ENGINE_TS_DATA(specs).fifoSpecs.serverPath);
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        /* socket domain */
        free(ENGINE_TS_DATA(specs).tcpSpecs.socketDomain);

        /* server path */
        free(ENGINE_TS_DATA(specs).tcpSpecs.serverPath);

        /* server port */
        free(ENGINE_TS_DATA(specs).tcpSpecs.serverPort);

        /* retry delay (optional) */
        if (ENGINE_TS_DATA(specs).tcpSpecs.retryDelay)
        {
            free(ENGINE_TS_DATA(specs).tcpSpecs.retryDelay);
        }

        /* retry count (optional) */
        if (ENGINE_TS_DATA(specs).tcpSpecs.retryCount)
        {
            free(ENGINE_TS_DATA(specs).tcpSpecs.retryCount);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            /* local PC */
            free(ENGINE_TS_DATA(specs).gdiSpecs.localPC);

            /* remote PC */
            free(ENGINE_TS_DATA(specs).gdiSpecs.remotePC);

            /* remote SSN */
            free(ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN);
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            /* local PC */
            free(ENGINE_TS_DATA(specs).taliSpecs.localPC);

            /* adjacent PC */
            free(ENGINE_TS_DATA(specs).taliSpecs.adjacentPC);

            /* allowed on open */
            free(ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen);

            /* user upper layer */
            free(ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer);
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* local PC */
            free(ENGINE_TS_DATA(specs).imalSpecs.localPC);

            /* adjacent PC */
            free(ENGINE_TS_DATA(specs).imalSpecs.adjacentPC);

            /* keepalive */
            if (ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut)
            {
                free(ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        /* local host */
        free(ENGINE_TS_DATA(specs).udpSpecs.localHost);

        /* local port */
        free(ENGINE_TS_DATA(specs).udpSpecs.localPort);

        /* associates */
        if (ENGINE_TS_DATA(specs).udpSpecs.associates)
        {
            for (i = 0; i < ENGINE_TS_DATA(specs).udpSpecs.numAssociates; i++)
            {
                free(ENGINE_TS_DATA(specs).udpSpecs.associates[i]);
            }

            free(ENGINE_TS_DATA(specs).udpSpecs.associates);
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (ENGINE_TS_DATA(specs).sctpSpecs.extraHomes)
            {
                for (i = 0; i < ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes; i++)
                {
                    free(ENGINE_TS_DATA(specs).sctpSpecs.extraHomes[i]);
                }

                free(ENGINE_TS_DATA(specs).sctpSpecs.extraHomes);
            }

            /* max in streams */
            if (ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams);
            }

            /* num out streams */
            if (ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams);
            }

            /* max attempts */
            if (ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts);
            }

            /* cookie life */
            if (ENGINE_TS_DATA(specs).sctpSpecs.cookieLife)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.cookieLife);
            }

            /* hb on */
            if (ENGINE_TS_DATA(specs).sctpSpecs.hbOn)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.hbOn);
            }

            /* init time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut);
            }

            /* send time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut);
            }

            /* recv time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut);
            }

            /* hb time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut);
            }

            /* shutdown time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut);
            }

            /* pmtu time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut);
            }

            /* is client */
            if (ENGINE_TS_DATA(specs).sctpSpecs.isClient)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.isClient);
            }

            /* payload type */
            if (ENGINE_TS_DATA(specs).sctpSpecs.payloadType)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.payloadType);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a transport specifics config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
 *                          mask, ...);
 *
 *  See Also:
 ****************************************************************************/
static int
TransportSpecificsCreate(ITS_Object obj, va_list args)
{
    ENGINE_TransportSpecifics ts = (ENGINE_TransportSpecifics)obj;
    ITS_UINT mask;
    int ret;

    mask = va_arg(args, ITS_UINT);

    ENGINE_TS_MASK(ts) = mask;

    ret = ParseTransportSpecifics(ts, args);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a transport specific config object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
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
 ****************************************************************************/
static void
TransportSpecificsDestroy(ITS_Object obj)
{
    FreeTransportSpecifics((ENGINE_TransportSpecifics)obj);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare transport specifics records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TransportSpecificsCompare(ITS_Object o1, ITS_Object o2)
{
    int i;

    if (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(o1)) !=
        ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(o2)))
    {
        return (ITS_FALSE);
    }

    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(o1)))
    {
    case ITS_TRANSPORT_SS7:
        if (strcmp(ENGINE_TS_DATA(o1).ss7Specs.vendorLib,
                   ENGINE_TS_DATA(o2).ss7Specs.vendorLib) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).ss7Specs.vendorClass,
                   ENGINE_TS_DATA(o2).ss7Specs.vendorClass) != 0)
        {
            return (ITS_FALSE);
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        if (strcmp(ENGINE_TS_DATA(o1).fifoSpecs.clientPath,
                   ENGINE_TS_DATA(o2).fifoSpecs.clientPath) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).fifoSpecs.serverPath,
                   ENGINE_TS_DATA(o2).fifoSpecs.serverPath) != 0)
        {
            return (ITS_FALSE);
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        if (strcmp(ENGINE_TS_DATA(o1).tcpSpecs.socketDomain,
                   ENGINE_TS_DATA(o2).tcpSpecs.socketDomain) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.serverPath,
                   ENGINE_TS_DATA(o2).tcpSpecs.serverPath) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.serverPort,
                   ENGINE_TS_DATA(o2).tcpSpecs.serverPort) != 0)
        {
            return (ITS_FALSE);
        }

        if ((ENGINE_TS_DATA(o1).tcpSpecs.retryDelay == NULL) ^
            (ENGINE_TS_DATA(o2).tcpSpecs.retryDelay == NULL))
        {
            return (ITS_FALSE);
        }
        if (ENGINE_TS_DATA(o1).tcpSpecs.retryDelay != NULL &&
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.retryDelay,
                   ENGINE_TS_DATA(o2).tcpSpecs.retryDelay) != 0)
        {
            return (ITS_FALSE);
        }

        if ((ENGINE_TS_DATA(o1).tcpSpecs.retryCount == NULL) ^
            (ENGINE_TS_DATA(o2).tcpSpecs.retryCount == NULL))
        {
            return (ITS_FALSE);
        }
        if (ENGINE_TS_DATA(o1).tcpSpecs.retryCount != NULL &&
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.retryCount,
                   ENGINE_TS_DATA(o2).tcpSpecs.retryCount) != 0)
        {
            return (ITS_FALSE);
        }

        if ((ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
             ITS_TRANSPORT_SOCKP_MASK) != 
            (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o2)) &
             ITS_TRANSPORT_SOCKP_MASK))
        {
            return (ITS_FALSE);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            if (strcmp(ENGINE_TS_DATA(o1).gdiSpecs.localPC,
                       ENGINE_TS_DATA(o2).gdiSpecs.localPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).gdiSpecs.remotePC,
                       ENGINE_TS_DATA(o2).gdiSpecs.remotePC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).gdiSpecs.remoteSSN,
                       ENGINE_TS_DATA(o2).gdiSpecs.remoteSSN) != 0)
            {
                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            if (strcmp(ENGINE_TS_DATA(o1).taliSpecs.localPC,
                       ENGINE_TS_DATA(o2).taliSpecs.localPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).taliSpecs.adjacentPC,
                       ENGINE_TS_DATA(o2).taliSpecs.adjacentPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).taliSpecs.localAllowedOnOpen,
                       ENGINE_TS_DATA(o2).taliSpecs.localAllowedOnOpen) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).taliSpecs.useUpperLayer,
                       ENGINE_TS_DATA(o2).taliSpecs.useUpperLayer) != 0)
            {
                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            if (strcmp(ENGINE_TS_DATA(o1).imalSpecs.localPC,
                       ENGINE_TS_DATA(o2).imalSpecs.localPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).imalSpecs.adjacentPC,
                       ENGINE_TS_DATA(o2).imalSpecs.adjacentPC) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).imalSpecs.keepAliveTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).imalSpecs.keepAliveTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).imalSpecs.keepAliveTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).imalSpecs.keepAliveTimeOut,
                       ENGINE_TS_DATA(o2).imalSpecs.keepAliveTimeOut) != 0)
            {
                return (ITS_FALSE);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        if (strcmp(ENGINE_TS_DATA(o1).udpSpecs.localHost,
                   ENGINE_TS_DATA(o2).udpSpecs.localHost) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).udpSpecs.localPort,
                   ENGINE_TS_DATA(o2).udpSpecs.localPort) != 0)
        {
            return (ITS_FALSE);
        }

        /* associates */
        if (ENGINE_TS_DATA(o1).udpSpecs.numAssociates !=
            ENGINE_TS_DATA(o2).udpSpecs.numAssociates)
        {
            return (ITS_FALSE);
        }

        for (i = 0; i < ENGINE_TS_DATA(o1).udpSpecs.numAssociates; i++)
        {
            if (strcmp(ENGINE_TS_DATA(o1).udpSpecs.associates[i],
                       ENGINE_TS_DATA(o1).udpSpecs.associates[i]) != 0)
            {
                return (ITS_FALSE);
            }
        }

        if ((ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
             ITS_TRANSPORT_SOCKP_MASK) != 
            (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o2)) &
             ITS_TRANSPORT_SOCKP_MASK))
        {
            return (ITS_FALSE);
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (ENGINE_TS_DATA(o1).sctpSpecs.numExtraHomes !=
                ENGINE_TS_DATA(o2).sctpSpecs.numExtraHomes)
            {
                return (ITS_FALSE);
            }

            for (i = 0; i < ENGINE_TS_DATA(o1).sctpSpecs.numExtraHomes; i++)
            {
                if (strcmp(ENGINE_TS_DATA(o1).sctpSpecs.extraHomes[i],
                           ENGINE_TS_DATA(o2).sctpSpecs.extraHomes[i]) != 0)
                {
                    return (ITS_FALSE);
                }
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.maxInStreams == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.maxInStreams == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.maxInStreams &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.maxInStreams,
                       ENGINE_TS_DATA(o2).sctpSpecs.maxInStreams) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.numOutStreams == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.numOutStreams == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.numOutStreams &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.numOutStreams,
                       ENGINE_TS_DATA(o2).sctpSpecs.numOutStreams) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.maxAttempts == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.maxAttempts == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.maxAttempts &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.maxAttempts,
                       ENGINE_TS_DATA(o2).sctpSpecs.maxAttempts) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.cookieLife == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.cookieLife == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.cookieLife &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.cookieLife,
                       ENGINE_TS_DATA(o2).sctpSpecs.cookieLife) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.hbOn == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.hbOn == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.hbOn &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.hbOn,
                       ENGINE_TS_DATA(o2).sctpSpecs.hbOn) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.initTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.initTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.initTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.initTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.initTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.sendTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.sendTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.sendTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.sendTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.sendTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.recvTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.recvTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.recvTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.recvTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.recvTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.hbTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.hbTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.hbTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.hbTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.hbTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.shutdownTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.shutdownTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.shutdownTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.shutdownTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.shutdownTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.pmtuTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.pmtuTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.pmtuTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.pmtuTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.pmtuTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.isClient == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.isClient == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.isClient &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.isClient,
                       ENGINE_TS_DATA(o2).sctpSpecs.isClient) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.payloadType == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.payloadType == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.payloadType &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.payloadType,
                       ENGINE_TS_DATA(o2).sctpSpecs.payloadType) != 0)
            {
                return (ITS_FALSE);
            }

            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TransportSpecificsClassRec =
{
    {
        &itsCORE_ClassRec,                      /* superclass */
        sizeof(ENGINE_TransportSpecificsRec),   /* instance size */
        ITS_FALSE,                              /* class initted */
        0,                                      /* class ref count */
        "ENGINE Transport Specifics Class",     /* class name */
        ITS_CLASS_NO_INIT,                      /* class init */
        ITS_CLASS_NO_DEST,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        TransportSpecificsCreate,               /* instantiate */
        TransportSpecificsDestroy,              /* destroy */
        ITS_INST_CLONE_INHERIT,                 /* clone */
        ITS_INST_PRINT_INHERIT,                 /* print */
        ITS_INST_SERIAL_INHERIT,                /* serialize */
        TransportSpecificsCompare,              /* equals */
        ITS_INST_HASH_INHERIT                   /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TransportSpecificsClass =
    &itsENGINE_TransportSpecificsClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a transport callback config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TransportCallbacksClass, app,
 *                          "libCISCO.so", notTrueSS7,
 *                          DISP_PROT_USER, DISP_BLOCKING,
 *                          "PreInit", "PostInit",
 *                          "PreNext", "NextEventFailed", "PostNext",
 *                          "DispatchUSER", "DispatchISUP", "DispatchSCCP",
 *                          "PreAccept", "OnAccept",
 *                          "PreTerminate", "PostTerminate",
 *                          DISP_PROT_USER);
 *
 *  See Also:
 ****************************************************************************/
static int
TransportCallbacksCreate(ITS_Object obj, va_list args)
{
    ENGINE_TransportCallbacks tc = (ENGINE_TransportCallbacks)obj;
    ENGINE_Application app;
    ITS_BOOLEAN trueSS7;
    char *tmp;

    app = va_arg(args, ENGINE_Application);
    tmp = va_arg(args, char *);
    trueSS7 = va_arg(args, ITS_BOOLEAN);
    ENGINE_TC_HANDLER_TYPE(tc) = va_arg(args, int);
    ENGINE_TC_TYPE(tc) = va_arg(args, int);

    ITS_C_REQUIRE(app != NULL);

    if (tmp && strlen(tmp) != 0)
    {
        ENGINE_TC_LIB_NAME(tc) = strdup(tmp);

        ITS_C_ASSERT(ENGINE_TC_LIB_NAME(tc) != NULL);
    }

    switch (ENGINE_TC_HANDLER_TYPE(tc))
    {
    case DISP_PROT_CCITT:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_CCITT_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_CCITT_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_CCITT_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_CCITT_STRING;
            }
        }
        break;

    case DISP_PROT_ANSI:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_ANSI_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_ANSI_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_ANSI_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_ANSI_STRING;
            }
        }
        break;

    case DISP_PROT_PRC:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_PRC_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_PRC_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_PRC_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_PRC_STRING;
            }
        }
        break;

    case DISP_PROT_USER:
        if (ENGINE_APP_CPP_BINDING(app))
        {
            ENGINE_TC_MAIN(tc) = DISP_USER_CPP_STRING;
        }
        else
        {
            ENGINE_TC_MAIN(tc) = DISP_USER_STRING;
        }
        break;

    case DISP_PROT_ITERATIVE:
        if (ENGINE_APP_CPP_BINDING(app))
        {
            ENGINE_TC_MAIN(tc) = DISP_ITERATIVE_CPP_STRING;
        }
        else
        {
            ENGINE_TC_MAIN(tc) = DISP_ITERATIVE_STRING;
        }
        break;

    case DISP_PROT_WORK_ITEM:
        ENGINE_TC_MAIN(tc) = DISP_WORK_ITEM_STRING;
        break;

    case DISP_PROT_DBC:
        if (ENGINE_APP_CPP_BINDING(app))
        {
            ENGINE_TC_MAIN(tc) = DISP_DBC_CPP_STRING;
        }
        else
        {
            ENGINE_TC_MAIN(tc) = DISP_DBC_STRING;
        }
        break;

    case DISP_PROT_CUSTOM:
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp && strlen(tmp) != 0);
        ENGINE_TC_MAIN(tc) = strdup(tmp);
        return (ITS_SUCCESS);

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    /* get bindings */
    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_INIT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_INIT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_INIT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_POST_INIT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_POST_INIT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_POST_INIT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_NEXT_EVENT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_NEXT_EVENT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_NEXT_EVENT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_NEXT_EVENT_FAIL(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_NEXT_EVENT_FAIL(tc) != NULL);
    }
    else
    {
        ENGINE_TC_NEXT_EVENT_FAIL(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_POST_NEXT_EVENT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_POST_NEXT_EVENT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_POST_NEXT_EVENT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_DISP_USER(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_DISP_USER(tc) != NULL);
    }
    else
    {
        ENGINE_TC_DISP_USER(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_DISP_ISUP(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_DISP_ISUP(tc) != NULL);
    }
    else
    {
        ENGINE_TC_DISP_ISUP(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_DISP_SCCP(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_DISP_SCCP(tc) != NULL);
    }
    else
    {
        ENGINE_TC_DISP_SCCP(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_ACCEPT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_ACCEPT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_ACCEPT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_ON_ACCEPT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_ON_ACCEPT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_ON_ACCEPT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_TERM(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_TERM(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_TERM(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_POST_TERM(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_POST_TERM(tc) != NULL);
    }
    else
    {
        ENGINE_TC_POST_TERM(tc) = NULL;
    }

    ENGINE_TC_ACCEPT_HANDLER_TYPE(tc) = va_arg(args, int);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a transport callback config object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
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
 ****************************************************************************/
static void
TransportCallbacksDestroy(ITS_Object obj)
{
    if (ENGINE_TC_LIB_NAME(obj))
    {
        free(ENGINE_TC_LIB_NAME(obj));
    }

    if (ENGINE_TC_HANDLER_TYPE(obj) == DISP_PROT_CUSTOM)
    {
        free(ENGINE_TC_MAIN(obj));
    }

    if (ENGINE_TC_PRE_INIT(obj))
    {
        free(ENGINE_TC_PRE_INIT(obj));
    }
    if (ENGINE_TC_POST_INIT(obj))
    {
        free(ENGINE_TC_POST_INIT(obj));
    }
    if (ENGINE_TC_PRE_NEXT_EVENT(obj))
    {
        free(ENGINE_TC_PRE_NEXT_EVENT(obj));
    }
    if (ENGINE_TC_NEXT_EVENT_FAIL(obj))
    {
        free(ENGINE_TC_NEXT_EVENT_FAIL(obj));
    }
    if (ENGINE_TC_POST_NEXT_EVENT(obj))
    {
        free(ENGINE_TC_POST_NEXT_EVENT(obj));
    }
    if (ENGINE_TC_DISP_USER(obj))
    {
        free(ENGINE_TC_DISP_USER(obj));
    }
    if (ENGINE_TC_DISP_ISUP(obj))
    {
        free(ENGINE_TC_DISP_ISUP(obj));
    }
    if (ENGINE_TC_DISP_SCCP(obj))
    {
        free(ENGINE_TC_DISP_SCCP(obj));
    }
    if (ENGINE_TC_PRE_TERM(obj))
    {
        free(ENGINE_TC_PRE_TERM(obj));
    }
    if (ENGINE_TC_POST_TERM(obj))
    {
        free(ENGINE_TC_POST_TERM(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare transport callback records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TransportCallbacksCompare(ITS_Object o1, ITS_Object o2)
{
    if (strcmp(ENGINE_TC_MAIN(o1), ENGINE_TC_MAIN(o2)) != 0)
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_INIT(o1) == NULL) ^
         (ENGINE_TC_PRE_INIT(o2) == NULL)) ||
        (ENGINE_TC_PRE_INIT(o1) &&
         strcmp(ENGINE_TC_PRE_INIT(o1), ENGINE_TC_PRE_INIT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_POST_INIT(o1) == NULL) ^
         (ENGINE_TC_POST_INIT(o2) == NULL)) ||
        (ENGINE_TC_POST_INIT(o1) &&
         strcmp(ENGINE_TC_POST_INIT(o1), ENGINE_TC_POST_INIT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_NEXT_EVENT(o1) == NULL) ^
         (ENGINE_TC_PRE_NEXT_EVENT(o2) == NULL)) ||
        (ENGINE_TC_PRE_NEXT_EVENT(o1) &&
         strcmp(ENGINE_TC_PRE_NEXT_EVENT(o1),
                ENGINE_TC_PRE_NEXT_EVENT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_NEXT_EVENT_FAIL(o1) == NULL) ^
         (ENGINE_TC_NEXT_EVENT_FAIL(o2) == NULL)) ||
        (ENGINE_TC_NEXT_EVENT_FAIL(o1) &&
         strcmp(ENGINE_TC_NEXT_EVENT_FAIL(o1),
                ENGINE_TC_NEXT_EVENT_FAIL(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_POST_NEXT_EVENT(o1) == NULL) ^
         (ENGINE_TC_POST_NEXT_EVENT(o2) == NULL)) ||
        (ENGINE_TC_POST_NEXT_EVENT(o1) &&
         strcmp(ENGINE_TC_POST_NEXT_EVENT(o1),
                ENGINE_TC_POST_NEXT_EVENT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_DISP_USER(o1) == NULL) ^
         (ENGINE_TC_DISP_USER(o2) == NULL)) ||
        (ENGINE_TC_DISP_USER(o1) &&
         strcmp(ENGINE_TC_DISP_USER(o1),
                ENGINE_TC_DISP_USER(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_DISP_ISUP(o1) == NULL) ^
         (ENGINE_TC_DISP_ISUP(o2) == NULL)) ||
        (ENGINE_TC_DISP_ISUP(o1) &&
         strcmp(ENGINE_TC_DISP_ISUP(o1),
                ENGINE_TC_DISP_ISUP(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_DISP_SCCP(o1) == NULL) ^
         (ENGINE_TC_DISP_SCCP(o2) == NULL)) ||
        (ENGINE_TC_DISP_SCCP(o1) &&
         strcmp(ENGINE_TC_DISP_SCCP(o1),
                ENGINE_TC_DISP_SCCP(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_ACCEPT(o1) == NULL) ^
         (ENGINE_TC_PRE_ACCEPT(o2) == NULL)) ||
        (ENGINE_TC_PRE_ACCEPT(o1) &&
         strcmp(ENGINE_TC_PRE_ACCEPT(o1), ENGINE_TC_PRE_ACCEPT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_ON_ACCEPT(o1) == NULL) ^
         (ENGINE_TC_ON_ACCEPT(o2) == NULL)) ||
        (ENGINE_TC_ON_ACCEPT(o1) &&
         strcmp(ENGINE_TC_ON_ACCEPT(o1), ENGINE_TC_ON_ACCEPT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_TERM(o1) == NULL) ^
         (ENGINE_TC_PRE_TERM(o2) == NULL)) ||
        (ENGINE_TC_PRE_TERM(o1) &&
         strcmp(ENGINE_TC_PRE_TERM(o1), ENGINE_TC_PRE_TERM(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_POST_TERM(o1) == NULL) ^
         (ENGINE_TC_POST_TERM(o2) == NULL)) ||
        (ENGINE_TC_POST_TERM(o1) &&
         strcmp(ENGINE_TC_POST_TERM(o1), ENGINE_TC_POST_TERM(o2)) != 0))
    {
        return (ITS_FALSE);
    }


    if (ENGINE_TC_ACCEPT_HANDLER_TYPE(o1) != 
        ENGINE_TC_ACCEPT_HANDLER_TYPE(o2))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TransportCallbacksClassRec =
{
    {
        &itsCORE_ClassRec,                      /* superclass */
        sizeof(ENGINE_TransportCallbacksRec),   /* instance size */
        ITS_FALSE,                              /* class initted */
        0,                                      /* class ref count */
        "ENGINE Transport Callbacks Class",     /* class name */
        ITS_CLASS_NO_INIT,                      /* class init */
        ITS_CLASS_NO_DEST,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        TransportCallbacksCreate,               /* instantiate */
        TransportCallbacksDestroy,              /* destroy */
        ITS_INST_CLONE_INHERIT,                 /* clone */
        ITS_INST_PRINT_INHERIT,                 /* print */
        ITS_INST_SERIAL_INHERIT,                /* serialize */
        TransportCallbacksCompare,              /* equals */
        ITS_INST_HASH_INHERIT                   /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TransportCallbacksClass =
    &itsENGINE_TransportCallbacksClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a transport config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TransportClass, threadPool,
 *                          name, mask, instance, isInterNode,
 *                          specifics, callbacks, routes, workItems);
 *
 *  See Also:
 ****************************************************************************/
static int
TransportCreate(ITS_Object obj, va_list args)
{
    ENGINE_Transport trans = (ENGINE_Transport)obj;
    ITS_Object tp;
    char *name;
    ITS_UINT mask;
    ITS_USHORT inst;
    ITS_BOOLEAN isInterNode;
    ITS_Object specifics;
    ITS_Object callbacks;
    ITS_Object links;
    ITS_Object workItems;
    ITS_Object *list;

    tp = va_arg(args, ITS_Object);
    name = va_arg(args, char *);
    mask = va_arg(args, ITS_UINT);
    inst = (ITS_USHORT)va_arg(args, ITS_UINT);
    isInterNode = va_arg(args, ITS_BOOLEAN);
    specifics = va_arg(args, ITS_Object);
    callbacks = va_arg(args, ITS_Object);
    links = va_arg(args, ITS_Object);
    workItems = va_arg(args, ITS_Object);

    ITS_C_ASSERT(callbacks != NULL);

    ENGINE_TR_NEXT(trans) = NULL;
    ENGINE_TR_POOL(trans) = tp;
    if (name && strlen(name) != 0)
    {
        ENGINE_TR_NAME(trans) = strdup(name);
        ITS_C_ASSERT(ENGINE_TR_NAME(trans) != NULL);
    }
    ENGINE_TR_MASK(trans) = mask;
    ENGINE_TR_INST(trans) = inst;
    ENGINE_TR_IS_INTERNODE(trans) = isInterNode;
    ENGINE_TR_SPECIFICS(trans) = specifics;
    ENGINE_TR_CALLBACKS(trans) = callbacks;
    ENGINE_TR_LINKS(trans) = links;
    ENGINE_TR_WORK_ITEMS(trans) = workItems;

    /* tail add */
    if (tp)
    {
        for (list = &ENGINE_TP_TRANSPORTS(tp);
             *list;
             list = &ENGINE_TR_NEXT(*list))
        {
        }
        *list = obj;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a transport config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
TransportDestroy(ITS_Object obj)
{
    ITS_Object list, tmp;

    free(ENGINE_TR_NAME(obj));

    ITS_DestructObject(ENGINE_TR_SPECIFICS(obj));
    ITS_DestructObject(ENGINE_TR_CALLBACKS(obj));

    for (list = ENGINE_TR_LINKS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_LN_NEXT(list);

        ITS_DestructObject(list);
    }

    for (list = ENGINE_TR_WORK_ITEMS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_WI_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare transport records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TransportCompare(ITS_Object o1, ITS_Object o2)
{
    if (((ENGINE_TR_NAME(o1) == NULL) ^
         (ENGINE_TR_NAME(o2) == NULL)) ||
        (ENGINE_TR_NAME(o1) &&
         strcmp(ENGINE_TR_NAME(o1), ENGINE_TR_NAME(o2)) != 0) ||
        ENGINE_TR_MASK(o1) != ENGINE_TR_MASK(o2)    ||
        ENGINE_TR_IS_INTERNODE(o1) != ENGINE_TR_IS_INTERNODE(o2))
    {
        return (ITS_FALSE);
    }

    if (!ITS_Equals(ENGINE_TR_SPECIFICS(o1), ENGINE_TR_SPECIFICS(o2)))
    {
        return (ITS_FALSE);
    }

    if (!ITS_Equals(ENGINE_TR_CALLBACKS(o1), ENGINE_TR_CALLBACKS(o2)))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TransportClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_TransportRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Transport Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        TransportCreate,                /* instantiate */
        TransportDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        TransportCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TransportClass = &itsENGINE_TransportClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a workItem object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_WorkItemClass, transport,
 *                          ITS_TRUE, 20, "libCISCO.so", "WorkItemDelegate");
 *
 *  See Also:
 ****************************************************************************/
static int
WorkItemCreate(ITS_Object obj, va_list args)
{
    char *libName, *delegate;
    ENGINE_WorkItem wi = (ENGINE_WorkItem)obj;
    ENGINE_Transport trans;
    ITS_BOOLEAN persist;
    ITS_UINT repeat;
    ITS_Object *list;

    trans = va_arg(args, ENGINE_Transport);
    persist = va_arg(args, ITS_BOOLEAN);
    repeat = va_arg(args, int);
    libName = va_arg(args, char *);
    delegate = va_arg(args, char *);

    ITS_C_REQUIRE(trans);
    ITS_C_REQUIRE(delegate != NULL && strlen(delegate) != 0);

    ENGINE_WI_NEXT(wi) = NULL;
    ENGINE_WI_TRANSPORT(wi) = trans;
    ENGINE_WI_PERSIST(wi) = persist;
    ENGINE_WI_REPEAT(wi) = repeat;
    if (libName && strlen(libName) != 0)
    {
        ENGINE_WI_LIB_NAME(wi) = strdup(libName);

        ITS_C_ASSERT(ENGINE_WI_LIB_NAME(wi) != NULL);
    }

    ENGINE_WI_DELEGATE(wi) = strdup(delegate);

    ITS_C_ASSERT(ENGINE_WI_DELEGATE(wi) != NULL);

    /* tail add */
    for (list = &ENGINE_TR_WORK_ITEMS(trans);
         *list;
         list = &ENGINE_WI_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a work item object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
WorkItemDestroy(ITS_Object obj)
{
    if (ENGINE_WI_LIB_NAME(obj))
    {
        free(ENGINE_WI_LIB_NAME(obj));
    }

    free(ENGINE_WI_DELEGATE(obj));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare workitem records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
WorkItemCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_WI_PERSIST(o1) != ENGINE_WI_PERSIST(o2) ||
        ENGINE_WI_REPEAT(o1) != ENGINE_WI_REPEAT(o2))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_WI_LIB_NAME(o1) == NULL) ^
         (ENGINE_WI_LIB_NAME(o2) == NULL)) ||
        (ENGINE_WI_LIB_NAME(o1) &&
         strcmp(ENGINE_WI_LIB_NAME(o1), ENGINE_WI_LIB_NAME(o2)) != 0) ||
        strcmp(ENGINE_WI_DELEGATE(o1), ENGINE_WI_DELEGATE(o2)) != 0)
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_WorkItemClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_WorkItemRec),     /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Work Item Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        WorkItemCreate,                 /* instantiate */
        WorkItemDestroy,                /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        WorkItemCompare,                /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_WorkItemClass = &itsENGINE_WorkItemClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a threadPool object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ThreadPoolClass, app,
 *                          stackSize, TPOOL_WORKERS);
 *
 *  See Also:
 ****************************************************************************/
static int
ThreadPoolCreate(ITS_Object obj, va_list args)
{
    ENGINE_ThreadPool tp = (ENGINE_ThreadPool)obj;
    ENGINE_Application app;
    int stackSize;
    ENGINE_ThreadPoolType type;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    stackSize = va_arg(args, int);
    type = va_arg(args, int);

    ITS_C_REQUIRE(app != NULL);

    ENGINE_TP_NEXT(tp) = NULL;
    ENGINE_TP_APP(tp) = app;
    ENGINE_TP_STACK_SIZE(tp) = stackSize;
    ENGINE_TP_TYPE(tp) = type;
    ENGINE_TP_TRANSPORTS(tp) = NULL;

    /* tail add */
    for (list = &ENGINE_APP_POOLS(app);
         *list;
         list = &ENGINE_TP_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a thread pool object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
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
 ****************************************************************************/
static void
ThreadPoolDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;

    for (list = ENGINE_TP_TRANSPORTS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TR_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare thread pool records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ThreadPoolCompare(ITS_Object o1, ITS_Object o2)
{
    /* not particularly useful. */
    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ThreadPoolClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ThreadPoolRec),   /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Thread Pool Class",     /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ThreadPoolCreate,               /* instantiate */
        ThreadPoolDestroy,              /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ThreadPoolCompare,              /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ThreadPoolClass = &itsENGINE_ThreadPoolClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a SS7 stack mgmt object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SS7StackMgmtClass, app,
 *                          "libCISCO.so",
 *                          "MTP3MgmtANSI", NULL,
 *                          "ISUPMgmtANSI", NULL,
 *                          "SCCPMgmtANSI", NULL,
 *                          "GTTMgmtANSI", NULL);
 *
 *  See Also:
 ****************************************************************************/
static int
StackMgmtCreate(ITS_Object obj, va_list args)
{
    ENGINE_SS7StackMgmt stack = (ENGINE_SS7StackMgmt)obj;
    ENGINE_Application app;
    char *libName;
    char *mtp3ANSI, *mtp3CCITT;
    char *isupANSI, *isupCCITT;
    char *sccpANSI, *sccpCCITT;
    char *gttANSI, *gttCCITT;
    char *ssnRouteANSI, *ssnRouteCCITT;

    app = va_arg(args, ENGINE_Application);
    libName = va_arg(args, char *);
    mtp3ANSI = va_arg(args, char *);
    mtp3CCITT = va_arg(args, char *);
    isupANSI = va_arg(args, char *);
    isupCCITT = va_arg(args, char *);
    sccpANSI = va_arg(args, char *);
    sccpCCITT = va_arg(args, char *);
    gttANSI = va_arg(args, char *);
    gttCCITT = va_arg(args, char *);
    ssnRouteANSI = va_arg(args, char *);
    ssnRouteCCITT = va_arg(args, char *);

    ITS_C_REQUIRE(app != NULL);

    ENGINE_S7_APP(stack) = app;
    ENGINE_APP_SS7_STACK_MGMT(app) = obj;

    /* optional user lib */
    if (libName && strlen(libName) != 0)
    {
        ENGINE_S7_LIB_NAME(stack) = strdup(libName);

        ITS_C_ASSERT(ENGINE_S7_LIB_NAME(stack) != NULL);
    }

    /* optional callbacks */
    if (mtp3ANSI && strlen(mtp3ANSI) != 0)
    {
        ENGINE_S7_MTP3_MGMT_ANSI(stack) = strdup(mtp3ANSI);

        ITS_C_ASSERT(ENGINE_S7_MTP3_MGMT_ANSI(stack) != NULL);
    }
    if (mtp3CCITT && strlen(mtp3CCITT) != 0)
    {
        ENGINE_S7_MTP3_MGMT_CCITT(stack) = strdup(mtp3CCITT);

        ITS_C_ASSERT(ENGINE_S7_MTP3_MGMT_CCITT(stack) != NULL);
    }

    if (isupANSI && strlen(isupANSI) != 0)
    {
        ENGINE_S7_ISUP_MGMT_ANSI(stack) = strdup(isupANSI);

        ITS_C_ASSERT(ENGINE_S7_ISUP_MGMT_ANSI(stack) != NULL);
    }
    if (isupCCITT && strlen(isupCCITT) != 0)
    {
        ENGINE_S7_ISUP_MGMT_CCITT(stack) = strdup(isupCCITT);

        ITS_C_ASSERT(ENGINE_S7_ISUP_MGMT_CCITT(stack) != NULL);
    }

    if (sccpANSI && strlen(sccpANSI) != 0)
    {
        ENGINE_S7_SCCP_MGMT_ANSI(stack) = strdup(sccpANSI);

        ITS_C_ASSERT(ENGINE_S7_SCCP_MGMT_ANSI(stack) != NULL);
    }
    if (sccpCCITT && strlen(sccpCCITT) != 0)
    {
        ENGINE_S7_SCCP_MGMT_CCITT(stack) = strdup(sccpCCITT);

        ITS_C_ASSERT(ENGINE_S7_SCCP_MGMT_CCITT(stack) != NULL);
    }

    if (gttANSI && strlen(gttANSI) != 0)
    {
        ENGINE_S7_SCCP_GTT_ANSI(stack) = strdup(gttANSI);

        ITS_C_ASSERT(ENGINE_S7_SCCP_GTT_ANSI(stack) != NULL);
    }
    if (gttCCITT && strlen(gttCCITT) != 0)
    {
        ENGINE_S7_SCCP_GTT_CCITT(stack) = strdup(gttCCITT);

        ITS_C_ASSERT(ENGINE_S7_SCCP_GTT_CCITT(stack) != NULL);
    }

    if (ssnRouteANSI && strlen(ssnRouteANSI) != 0)
    {
        ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stack) = strdup(ssnRouteANSI);

        ITS_C_ASSERT(ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stack) != NULL);
    }
    if (ssnRouteCCITT && strlen(ssnRouteCCITT) != 0)
    {
        ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stack) = strdup(ssnRouteCCITT);

        ITS_C_ASSERT(ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stack) != NULL);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SS7 stack mgmt object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
StackMgmtDestroy(ITS_Object obj)
{
    if (ENGINE_S7_LIB_NAME(obj))
    {
        free(ENGINE_S7_LIB_NAME(obj));
    }

    if (ENGINE_S7_MTP3_MGMT_ANSI(obj))
    {
        free(ENGINE_S7_MTP3_MGMT_ANSI(obj));
    }
    if (ENGINE_S7_MTP3_MGMT_CCITT(obj))
    {
        free(ENGINE_S7_MTP3_MGMT_CCITT(obj));
    }

    if (ENGINE_S7_ISUP_MGMT_ANSI(obj))
    {
        free(ENGINE_S7_ISUP_MGMT_ANSI(obj));
    }
    if (ENGINE_S7_ISUP_MGMT_CCITT(obj))
    {
        free(ENGINE_S7_ISUP_MGMT_CCITT(obj));
    }

    if (ENGINE_S7_SCCP_MGMT_ANSI(obj))
    {
        free(ENGINE_S7_SCCP_MGMT_ANSI(obj));
    }
    if (ENGINE_S7_SCCP_MGMT_CCITT(obj))
    {
        free(ENGINE_S7_SCCP_MGMT_CCITT(obj));
    }

    if (ENGINE_S7_SCCP_GTT_ANSI(obj))
    {
        free(ENGINE_S7_SCCP_GTT_ANSI(obj));
    }
    if (ENGINE_S7_SCCP_GTT_CCITT(obj))
    {
        free(ENGINE_S7_SCCP_GTT_CCITT(obj));
    }

    if (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(obj))
    {
        free(ENGINE_S7_SCCP_SSN_ROUTE_ANSI(obj));
    }
    if (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(obj))
    {
        free(ENGINE_S7_SCCP_SSN_ROUTE_CCITT(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare stack management records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
StackMgmtCompare(ITS_Object o1, ITS_Object o2)
{
    if (((ENGINE_S7_LIB_NAME(o1) == NULL) ^
         (ENGINE_S7_LIB_NAME(o2) == NULL)) ||
        (ENGINE_S7_LIB_NAME(o1) &&
         strcmp(ENGINE_S7_LIB_NAME(o1), ENGINE_S7_LIB_NAME(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_MTP3_MGMT_ANSI(o1) == NULL) ^
         (ENGINE_S7_MTP3_MGMT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_MTP3_MGMT_ANSI(o1) &&
         strcmp(ENGINE_S7_MTP3_MGMT_ANSI(o1),
                ENGINE_S7_MTP3_MGMT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_MTP3_MGMT_CCITT(o1) == NULL) ^
         (ENGINE_S7_MTP3_MGMT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_MTP3_MGMT_CCITT(o1) &&
         strcmp(ENGINE_S7_MTP3_MGMT_CCITT(o1),
                ENGINE_S7_MTP3_MGMT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_ISUP_MGMT_ANSI(o1) == NULL) ^
         (ENGINE_S7_ISUP_MGMT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_ISUP_MGMT_ANSI(o1) &&
         strcmp(ENGINE_S7_ISUP_MGMT_ANSI(o1),
                ENGINE_S7_ISUP_MGMT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_ISUP_MGMT_CCITT(o1) == NULL) ^
         (ENGINE_S7_ISUP_MGMT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_ISUP_MGMT_CCITT(o1) &&
         strcmp(ENGINE_S7_ISUP_MGMT_CCITT(o1),
                ENGINE_S7_ISUP_MGMT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_SCCP_MGMT_ANSI(o1) == NULL) ^
         (ENGINE_S7_SCCP_MGMT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_SCCP_MGMT_ANSI(o1) &&
         strcmp(ENGINE_S7_SCCP_MGMT_ANSI(o1),
                ENGINE_S7_SCCP_MGMT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_SCCP_MGMT_CCITT(o1) == NULL) ^
         (ENGINE_S7_SCCP_MGMT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_SCCP_MGMT_CCITT(o1) &&
         strcmp(ENGINE_S7_SCCP_MGMT_CCITT(o1),
                ENGINE_S7_SCCP_MGMT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_SCCP_GTT_ANSI(o1) == NULL) ^
         (ENGINE_S7_SCCP_GTT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_SCCP_GTT_ANSI(o1) &&
         strcmp(ENGINE_S7_SCCP_GTT_ANSI(o1),
                ENGINE_S7_SCCP_GTT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_SCCP_GTT_CCITT(o1) == NULL) ^
         (ENGINE_S7_SCCP_GTT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_SCCP_GTT_CCITT(o1) &&
         strcmp(ENGINE_S7_SCCP_GTT_CCITT(o1),
                ENGINE_S7_SCCP_GTT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o1) == NULL) ^
         (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o2) == NULL)) ||
        (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o1) &&
         strcmp(ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o1),
                ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o1) == NULL) ^
         (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o2) == NULL)) ||
        (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o1) &&
         strcmp(ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o1),
                ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_SS7StackMgmtClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_SS7StackMgmtRec), /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE SS7 Stack Mgmt Class",  /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        StackMgmtCreate,                /* instantiate */
        StackMgmtDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        StackMgmtCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SS7StackMgmtClass = &itsENGINE_SS7StackMgmtClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create an isup timer object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ISUPTimerClass, isupAttributes,
 *                          id, value, handler);
 *
 *  See Also:
 ****************************************************************************/
static int
ISUPTimerCreate(ITS_Object obj, va_list args)
{
    ENGINE_ISUPTimer timer = (ENGINE_ISUPTimer)obj;
    ITS_Object attr;
    ITS_Object *tlist;
    ITS_Object *list;
    char *id, *value, *handler;

    attr = va_arg(args, ITS_Object);
    id = va_arg(args, char *);
    value = va_arg(args, char *);
    handler = va_arg(args, char *);

    ITS_C_ASSERT(attr != NULL);
    ITS_C_ASSERT(id != NULL);

    ENGINE_IT_NEXT(timer) = NULL;

    ENGINE_IT_ID(timer) = strdup(id);
    if (ENGINE_IT_ID(timer) == NULL)
    {
        return (ITS_ENOMEM);
    }
    if (value)
    {
        ENGINE_IT_VALUE(timer) = strdup(value);
        if (ENGINE_IT_VALUE(timer) == NULL)
        {
            free(ENGINE_IT_ID(timer));

            return (ITS_ENOMEM);
        }
    }
    if (handler)
    {
        ENGINE_IT_HANDLER(timer) = strdup(handler);
        if (ENGINE_IT_HANDLER(timer) == NULL)
        {
            free(ENGINE_IT_ID(timer));
            if (ENGINE_IT_VALUE(timer));
            {
                free(ENGINE_IT_VALUE(timer));
            }

            return (ITS_ENOMEM);
        }
    }

    /* tail add */
    tlist = &ENGINE_IA_TIMERS(attr);
    for (list = tlist;
         *list;
         list = &ENGINE_IT_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
ISUPTimerDestroy(ITS_Object obj)
{
    free(ENGINE_IT_ID(obj));
    if (ENGINE_IT_VALUE(obj))
    {
        free(ENGINE_IT_VALUE(obj));
    }
    if (ENGINE_IT_HANDLER(obj))
    {
        free(ENGINE_IT_HANDLER(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ISUPTimerCompare(ITS_Object o1, ITS_Object o2)
{
    if (strcmp(ENGINE_IT_ID(o1), ENGINE_IT_ID(o2)) == 0 &&
        ((ENGINE_IT_VALUE(o1) == NULL && ENGINE_IT_VALUE(o2) == NULL) ||
         (ENGINE_IT_VALUE(o1) != NULL && ENGINE_IT_VALUE(o2) != NULL &&
          strcmp(ENGINE_IT_VALUE(o1), ENGINE_IT_VALUE(o2)) == 0)) &&
        ((ENGINE_IT_HANDLER(o1) == NULL && ENGINE_IT_HANDLER(o2) == NULL) ||
         (ENGINE_IT_HANDLER(o1) != NULL && ENGINE_IT_HANDLER(o2) != NULL &&
          strcmp(ENGINE_IT_HANDLER(o1), ENGINE_IT_HANDLER(o2)) == 0)))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ISUPTimerClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ISUPTimerRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE ISUP Timer Class",      /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ISUPTimerCreate,                /* instantiate */
        ISUPTimerDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ISUPTimerCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ISUPTimerClass = &itsENGINE_ISUPTimerClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create an isup timer object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_CICsClass, circuitGroup,
 *                          start, count);
 *
 *  See Also:
 ****************************************************************************/
static int
CircuitCodeCreate(ITS_Object obj, va_list args)
{
    ENGINE_CICs cics = (ENGINE_CICs)obj;
    ITS_Object cg;
    ITS_Object *tlist;
    ITS_Object *list;

    cg = va_arg(args, ITS_Object);
    ENGINE_IC_START(cics) = va_arg(args, ITS_UINT);
    ENGINE_IC_COUNT(cics) = va_arg(args, ITS_UINT);

    ITS_C_ASSERT(cg != NULL);
    ENGINE_IC_NEXT(cics) = NULL;

    /* tail add */
    tlist = &ENGINE_CG_CODES(cg);
    for (list = tlist;
         *list;
         list = &ENGINE_IC_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
CircuitCodeDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
CircuitCodeCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_IC_START(o1) == ENGINE_IC_START(o2) &&
        ENGINE_IC_COUNT(o1) == ENGINE_IC_COUNT(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_CICsClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_CICsRec),         /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE CICs Class",            /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CircuitCodeCreate,              /* instantiate */
        CircuitCodeDestroy,             /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        CircuitCodeCompare,             /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_CICsClass = &itsENGINE_CICsClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a circuit group object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_CircuitGroupClass, isupAttr,
 *                          huntRule);
 *
 *  See Also:
 ****************************************************************************/
static int
CircuitGroupCreate(ITS_Object obj, va_list args)
{
    ENGINE_CircuitGroup group = (ENGINE_CircuitGroup)obj;
    ITS_Object attr;
    ITS_Object *tlist;
    ITS_Object *list;
    char *huntRule;

    attr = va_arg(args, ITS_Object);
    huntRule = va_arg(args, char *);

    ITS_C_ASSERT(attr != NULL);

    ENGINE_CG_NEXT(group) = NULL;

    if (huntRule)
    {
        ENGINE_CG_HUNT_RULE(group) = strdup(huntRule);
        if (ENGINE_CG_HUNT_RULE(group) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

    /* tail add */
    tlist = &ENGINE_IA_GROUPS(attr);
    for (list = tlist;
         *list;
         list = &ENGINE_CG_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
CircuitGroupDestroy(ITS_Object obj)
{
    if (ENGINE_CG_HUNT_RULE(obj))
    {
        free(ENGINE_CG_HUNT_RULE(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
CircuitGroupCompare(ITS_Object o1, ITS_Object o2)
{
    if ((ENGINE_CG_HUNT_RULE(o1) == NULL && ENGINE_CG_HUNT_RULE(o2) == NULL) ||
        (ENGINE_CG_HUNT_RULE(o1) != NULL && ENGINE_CG_HUNT_RULE(o2) != NULL &&
         strcmp(ENGINE_CG_HUNT_RULE(o1), ENGINE_CG_HUNT_RULE(o2)) == 0))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_CircuitGroupClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_CircuitGroupRec), /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE CircuitGroup Class",    /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CircuitGroupCreate,             /* instantiate */
        CircuitGroupDestroy,            /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        CircuitGroupCompare,            /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_CircuitGroupClass = &itsENGINE_CircuitGroupClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ISUPAttrClass,
 *                          application, destination,
 *                          localPointCode, classRec, library);
 *
 *  See Also:
 ****************************************************************************/
static int
ISUPAttrCreate(ITS_Object obj, va_list args)
{
    char *libName, *className;
    ENGINE_ISUPAttr isupAttr = (ENGINE_ISUPAttr)obj;
    ENGINE_Application app;
    ENGINE_Dest dest;
    ITS_Class *cl;
    char *xchangeType = NULL;
    char *segmentationSupported = NULL;

    app = va_arg(args, ENGINE_Application);
    dest = va_arg(args, ENGINE_Dest);
    ENGINE_IA_LPC(isupAttr) = va_arg(args, ITS_UINT);
    className = va_arg(args, char *);
    libName = va_arg(args, char *);
    ENGINE_IA_SIO(isupAttr) = va_arg(args, ITS_UINT);

    xchangeType = va_arg(args, char *);
    if (xchangeType == NULL)
    {
        ENGINE_IA_XTYPE(isupAttr) = xchangeType;
    }
    else
    {
        ENGINE_IA_XTYPE(isupAttr) = strdup(xchangeType);
    }

    segmentationSupported = va_arg(args, char *);
    if (segmentationSupported == NULL)
    {
        ENGINE_IA_XTYPE(isupAttr) = xchangeType;
    }
    else
    {
       ENGINE_IA_SEGMENTATIONSUPPORT(isupAttr) = strdup(segmentationSupported);
    }

    ITS_C_REQUIRE(dest != NULL);
    ITS_C_REQUIRE(className != NULL && strlen(className) != 0);

    ENGINE_IA_CLASS_REC(isupAttr) = strdup(className);
    ENGINE_IA_LIB(isupAttr) = ENGINE_LibGet(app, libName);

    ITS_C_ASSERT(ENGINE_IA_CLASS_REC(isupAttr) != NULL);
    ITS_C_ASSERT(ENGINE_IA_LIB(isupAttr) != NULL);

    dest->dest.isupAttr = obj;

    cl = (ITS_Class *)
        DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_IA_LIB(isupAttr)),
                      className);

    if (cl == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   className, DLSYM_Error());
            fflush(stdout);
        }

        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
ISUPAttrDestroy(ITS_Object obj)
{
    ITS_Object list, tmp;

    free(ENGINE_IA_CLASS_REC(obj));

    for (list = ENGINE_IA_TIMERS(obj); list; list = tmp)
    {
        tmp = ENGINE_IT_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_IA_GROUPS(obj); list; list = tmp)
    {
        tmp = ENGINE_CG_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare feature records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ISUPAttrCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_IA_LPC(o1) == ENGINE_IA_LPC(o2) &&
        strcmp(ENGINE_IA_CLASS_REC(o1), ENGINE_IA_CLASS_REC(o2)) == 0 &&
        ENGINE_FEAT_LIB_CACHE_ENTRY(o1) == ENGINE_FEAT_LIB_CACHE_ENTRY(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ISUPAttrClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ISUPAttrRec),     /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE ISUP Attr Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ISUPAttrCreate,                 /* instantiate */
        ISUPAttrDestroy,                /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ISUPAttrCompare,                /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ISUPAttrClass = &itsENGINE_ISUPAttrClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create an sip timer object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SIPTimerClass, sipttributes,
 *                          id, value);
 *
 *  See Also:
 ****************************************************************************/
static int
SIPTimerCreate(ITS_Object obj, va_list args)
{
    ENGINE_SIPTimer timer = (ENGINE_SIPTimer)obj;
    ITS_Object attr;
    ITS_Object *tlist;
    ITS_Object *list;
    char *id, *value;

    attr = va_arg(args, ITS_Object);
    id = va_arg(args, char *);
    value = va_arg(args, char *);

    ITS_C_ASSERT(attr != NULL);
    ITS_C_ASSERT(id != NULL);

    ENGINE_ST_NEXT(timer) = NULL;

    ENGINE_ST_ID(timer) = strdup(id);
    if (ENGINE_ST_ID(timer) == NULL)
    {
        return (ITS_ENOMEM);
    }
    if (value)
    {
        ENGINE_ST_VALUE(timer) = strdup(value);
        if (ENGINE_ST_VALUE(timer) == NULL)
        {
            free(ENGINE_ST_ID(timer));

            return (ITS_ENOMEM);
        }
    }
    /* tail add */
    tlist = &ENGINE_SIP_TIMERS(attr);
    for (list = tlist;
         *list;
         list = &ENGINE_ST_NEXT(*list))
    {
    }
    *list = obj;
    
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SIP Timer object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
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
 ****************************************************************************/
static void
SIPTimerDestroy(ITS_Object obj)
{
    free(ENGINE_ST_ID(obj));
    if (ENGINE_ST_VALUE(obj))
    {
        free(ENGINE_ST_VALUE(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
SIPTimerCompare(ITS_Object o1, ITS_Object o2)
{
    if (strcmp(ENGINE_ST_ID(o1), ENGINE_ST_ID(o2)) == 0 &&
        ((ENGINE_ST_VALUE(o1) == NULL && ENGINE_ST_VALUE(o2) == NULL) ||
         (ENGINE_ST_VALUE(o1) != NULL && ENGINE_ST_VALUE(o2) != NULL &&
          strcmp(ENGINE_ST_VALUE(o1), ENGINE_ST_VALUE(o2)) == 0)))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_SIPTimerClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_SIPTimerRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE SIP Timer Class",      /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        SIPTimerCreate,                 /* instantiate */
        SIPTimerDestroy,                /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        SIPTimerCompare,                /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SIPTimerClass = &itsENGINE_SIPTimerClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a SIP object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SIPAttrClass,
 *                          application,
 *                          UDPPortNo, TCPPortNo, ipAddr); 
 *
 *  See Also:
 ****************************************************************************/
static int
SIPAttrCreate(ITS_Object obj, va_list args)
{   
    ENGINE_SIPAttr sipAttr = (ENGINE_SIPAttr)obj;
    ENGINE_Application app;
    char *ipAddr = NULL;
 
    app = va_arg(args, ENGINE_Application);
    ENGINE_SIP_UDPPORT(sipAttr) = va_arg(args, int);
    ENGINE_SIP_TCPPORT(sipAttr) = va_arg(args, int);
 
    ipAddr = va_arg(args, char *);
    if (ipAddr == NULL)
    {   
        ENGINE_SIP_IPADDR(sipAttr) = ipAddr;
    }
    else
    {
        ENGINE_SIP_IPADDR(sipAttr) = strdup(ipAddr);
    }   

    app->application.sipAttributes = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SIP object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
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
 ****************************************************************************/
static void
SIPAttrDestroy(ITS_Object obj)
{
    ITS_Object list, tmp;

    if (ENGINE_SIP_IPADDR(obj))
    {
        free(ENGINE_SIP_IPADDR(obj));
    }
   
    for (list = ENGINE_SIP_TIMERS(obj); list; list = tmp)
    {
        tmp = ENGINE_ST_NEXT(list);
        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare feature records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
SIPAttrCompare(ITS_Object o1, ITS_Object o2)
{
    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_SIPAttrClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_SIPAttrRec),      /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE SIP Attr Class",        /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        SIPAttrCreate,                  /* instantiate */
        SIPAttrDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        SIPAttrCompare,                 /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SIPAttrClass = &itsENGINE_SIPAttrClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a ISS7Stack object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ISS7StackClass, app, name,
                            variant, numThreads);
 *
 *  See Also:
 ****************************************************************************/
static int
ISS7StackCreate(ITS_Object obj, va_list args)
{
    ENGINE_ISS7Stack stack = (ENGINE_ISS7Stack)obj;
    ENGINE_Application app;
    char *name;
    int variant;
    ITS_Object *list;
    int numThreads;

    app = va_arg(args, ENGINE_Application);
    name = va_arg(args, char *);
    variant = va_arg(args, int);
    numThreads = va_arg(args, int);

    ITS_C_ASSERT(app != NULL);
    ITS_C_ASSERT(name != NULL && strlen(name) != 0);

    ENGINE_ISS7_NAME(stack) = strdup(name);
    ITS_C_ASSERT(ENGINE_ISS7_NAME(stack) != NULL);

    if (numThreads <= 0)
    {
        numThreads = 1;
    }
    ENGINE_ISS7_NUM_THREADS(stack) = numThreads;

    if (variant)
    {
        ENGINE_ISS7_VARIANT(stack) = variant;
    }

    /* tail add */
    for (list = &ENGINE_APP_ISS7_STACK_CTRL(app);
         *list;
         list = &ENGINE_ISS7_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a ISS7 object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
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
 ****************************************************************************/
static void
ISS7StackDestroy(ITS_Object obj)
{
    int i;
    ITS_Object list, tmp;

    free(ENGINE_ISS7_NAME(obj));

    for (list = ENGINE_ISS7_TRACE(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TL_NEXT(list);

        ITS_DestructObject(list);
    }

    for (list = ENGINE_ISS7_LINKS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_LN_NEXT(list);

        ITS_DestructObject(list);
    }

    if (ENGINE_ISS7_NUM_TIMERS(obj))
    {
        for (i = 0; i < ENGINE_ISS7_NUM_TIMERS(obj); i++)
        {
            free(ENGINE_ISS7_TIMERS(obj)[i]);
        }

        free(ENGINE_ISS7_TIMERS(obj));
    }

    if (ENGINE_ISS7_NUM_MODIFIERS(obj))
    {
        for (i = 0; i < ENGINE_ISS7_NUM_MODIFIERS(obj); i++)
        {
            free(ENGINE_ISS7_MODIFIERS(obj)[i]);
        }

        free(ENGINE_ISS7_MODIFIERS(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare ISS7 stack records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ISS7StackCompare(ITS_Object o1, ITS_Object o2)
{
    int i;

    if (strcmp(ENGINE_ISS7_NAME(o1), ENGINE_ISS7_NAME(o2)) != 0 ||
        ENGINE_ISS7_NUM_THREADS(o1) != ENGINE_ISS7_NUM_THREADS(o2))
    {
        return (ITS_FALSE);
    }

    if (ENGINE_ISS7_VARIANT(o1) != ENGINE_ISS7_VARIANT(o2))
    {
        return (ITS_FALSE);
    }

    if (ENGINE_ISS7_NUM_TIMERS(o1) != ENGINE_ISS7_NUM_TIMERS(o2) ||
        ENGINE_ISS7_NUM_MODIFIERS(o1) != ENGINE_ISS7_NUM_MODIFIERS(o2))
    {
        return (ITS_FALSE);
    }

    for (i = 0; i < ENGINE_ISS7_NUM_TIMERS(o1); i++)
    {
        if (strcmp(ENGINE_ISS7_TIMERS(o1)[i],
                   ENGINE_ISS7_TIMERS(o2)[i]) != 0)
        {
            return (ITS_FALSE);
        }
    }

    for (i = 0; i < ENGINE_ISS7_NUM_MODIFIERS(o1); i++)
    {
        if (strcmp(ENGINE_ISS7_MODIFIERS(o1)[i],
                   ENGINE_ISS7_MODIFIERS(o2)[i]) != 0)
        {
            return (ITS_FALSE);
        }
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ISS7StackClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ISS7StackRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE ISS7Stack Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ISS7StackCreate,                /* instantiate */
        ISS7StackDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ISS7StackCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ISS7StackClass = &itsENGINE_ISS7StackClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a FtCallback object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FtCallbackClass,
 *              list,
 *              type, 
 *              functionName,
 *              libraryName);
 *
 *  See Also:
 ****************************************************************************/
static int
FtCallbackCreate(ITS_Object obj, va_list args)
{
    ENGINE_FtCallback ftCallback = (ENGINE_FtCallback)obj;
    ENGINE_FtCallbackType type;
    char* functionName;
    char* libraryName;
    ITS_Object* rlist;
    ITS_Object* list;

    rlist = va_arg(args, ITS_Object*);
    type = (ENGINE_FtCallbackType)va_arg(args, int);
    functionName = va_arg(args, char*);
    libraryName = va_arg(args, char*);

    ITS_C_REQUIRE(rlist != NULL);

    ENGINE_FT_CALLBACK_TYPE(ftCallback) = type;

    if (functionName && strlen(functionName) != 0)
    {
        ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback) = 
            strdup(functionName);

        ITS_C_ASSERT(ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback) != NULL);
    }

    if (libraryName && strlen(libraryName) != 0)
    {
        ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback) = 
            strdup(libraryName);

        ITS_C_ASSERT(ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback) != NULL);
    }

    /* Add to tail. */
    for (list = rlist; *list; list = &ENGINE_FT_CALLBACK_NEXT(*list))
    {
    }
    *list = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a FtCallback object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
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
FtCallbackDestroy(ITS_Object obj)
{
    ENGINE_FtCallback ftCallback = (ENGINE_FtCallback)obj;

    if (ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback) != NULL)
    {
        free(ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback));
    }

    if (ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback) != NULL)
    {
        free(ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare FtCallback records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FtCallbackCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FtCallbackClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FtCallbackRec),       /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE FtCallback Class",          /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FtCallbackCreate,                   /* instance create          */
        FtCallbackDestroy,                  /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FtCallbackCompare,                  /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FtCallbackClass = &itsENGINE_FtCallbackClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a FtGroup Member object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FtGroupMemberClass,
 *              list,
 *              type,
 *              nodeId,
 *              nodeName,
 *              processId,
 *              processName);
 *
 *  See Also:
 ****************************************************************************/
static int
FtGroupMemberCreate(ITS_Object obj, va_list args)
{
    ENGINE_FtGroupMember ftGroupMember = (ENGINE_FtGroupMember)obj;
    ENGINE_FtGroupMemberType type;
    ITS_USHORT nodeId;
    char* nodeName;
    ITS_USHORT processId;
    char* processName;
    ITS_Object* rlist;
    ITS_Object* list;

    rlist = va_arg(args, ITS_Object*);
    type = (ENGINE_FtGroupMemberType)va_arg(args, int);
    nodeId = (ITS_USHORT)va_arg(args, int);
    nodeName = va_arg(args, char*);
    processId = (ITS_USHORT)va_arg(args, int);
    processName = va_arg(args, char*);

    ITS_C_REQUIRE(rlist != NULL);

    ENGINE_FT_GROUP_MEMBER_TYPE(ftGroupMember) = type;
    ENGINE_FT_GROUP_MEMBER_NODE_ID(ftGroupMember) = nodeId;

    if (nodeName && strlen(nodeName) != 0)
    {
        ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember) =
            strdup(nodeName);

        ITS_C_ASSERT(ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember) != NULL);
    }

    ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftGroupMember) = processId;

    if (processName && strlen(processName) != 0)
    {
        ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember) =
            strdup(processName);

        ITS_C_ASSERT(ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember) != NULL);
    }
    
    /* Add to tail. */
    for (list = rlist; *list; list = &ENGINE_FT_GROUP_MEMBER_NEXT(*list))
    {
    }
    *list = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a FtGroup Member object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
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
FtGroupMemberDestroy(ITS_Object obj)
{
    ENGINE_FtGroupMember ftGroupMember = (ENGINE_FtGroupMember)obj;

    if (ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember) != NULL)
    {
        free(ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember));
    }

    if (ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember) != NULL)
    {
        free(ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare FtGroupMember records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FtGroupMemberCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FtGroupMemberClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FtGroupMemberRec),    /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE FtGroup Member Class",      /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FtGroupMemberCreate,                /* instance create          */
        FtGroupMemberDestroy,               /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FtGroupMemberCompare,               /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FtGroupMemberClass = &itsENGINE_FtGroupMemberClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a FtGroup object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FtGroupClass,
 *              list,
 *              ftGroupId,
 *              ftGroupName,
 *              dsmSize,
 *              dsmBaseAddress,
 *              dsmMaxNumTables,
 *              dsmType);
 *
 *  See Also:
 ****************************************************************************/
static int
FtGroupCreate(ITS_Object obj, va_list args)
{
    ENGINE_FtGroup ftGroup = (ENGINE_FtGroup)obj;
    ITS_USHORT ftGroupId;
    char* ftGroupName;
    ITS_UINT dsmSize;
    char* dsmBaseAddress;
    ITS_UINT dsmMaxNumTables;
    char* dsmType;
    ITS_Object* rlist;
    ITS_Object* list;

    rlist = va_arg(args, ITS_Object*);
    ftGroupId = (ITS_USHORT)va_arg(args, int);
    ftGroupName = va_arg(args, char*);
    dsmSize = (ITS_UINT)va_arg(args, int);
    dsmBaseAddress = va_arg(args, char*);
    dsmMaxNumTables = (ITS_UINT)va_arg(args, int);
    dsmType = va_arg(args, char*);

    ITS_C_REQUIRE(rlist != NULL);

    ENGINE_FT_GROUP_FT_GROUP_ID(ftGroup) = ftGroupId;

    if (ftGroupName && strlen(ftGroupName) != 0)
    {
        ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup) =
            strdup(ftGroupName);

        ITS_C_ASSERT(ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup) != NULL);
    }

    ENGINE_FT_GROUP_DSM_SIZE(ftGroup) = dsmSize;

    if (dsmBaseAddress && strlen(dsmBaseAddress) != 0)
    {
        ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) =
            strdup(dsmBaseAddress);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) != NULL);
    }

    ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(ftGroup) = dsmMaxNumTables;

    if (dsmType && strlen(dsmType) != 0)
    {
        ENGINE_FT_GROUP_DSM_TYPE(ftGroup) = 
            strdup(dsmType);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_TYPE(ftGroup) != NULL);
    }

    /* Add to tail. */
    for (list = rlist; *list; list = &ENGINE_FT_GROUP_NEXT(*list))
    {
    }
    *list = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a FtGroup object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
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
FtGroupDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;

    ENGINE_FtGroup ftGroup = (ENGINE_FtGroup)obj;

    if (ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup) != NULL)
    {
        free(ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup));
    }

    if (ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) != NULL)
    {
        free(ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup));
    }

    if (ENGINE_FT_GROUP_DSM_TYPE(ftGroup) != NULL)
    {
        free(ENGINE_FT_GROUP_DSM_TYPE(ftGroup));
    }

    for (
        list = ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftGroup); 
        list != NULL; 
        list = tmp)
    {
        tmp = ENGINE_FT_GROUP_MEMBER_NEXT(list);

        ITS_DestructObject(list);
    }

    for (
        list = ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(ftGroup);
        list != NULL; 
        list = tmp)
    {
        tmp = ENGINE_FT_GROUP_MEMBER_NEXT(list);

        ITS_DestructObject(list);
    }

    for (
        list = ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup); 
        list != NULL; 
        list = tmp)
    {
        tmp = ENGINE_FT_CALLBACK_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare FtGroup records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FtGroupCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FtGroupClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FtGroupRec),          /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE FtGroup Class",             /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FtGroupCreate,                      /* instance create          */
        FtGroupDestroy,                     /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FtGroupCompare,                     /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FtGroupClass = &itsENGINE_FtGroupClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a Fault Tolerance object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FaultToleranceClass,
 *              app,
 *              maxNumFtGroups,
 *              maxNumProcesses,
 *              maxNumNodes,
 *              nodeId,
 *              processId,
 *              tcapFtGroupId,
 *              sccpFtGroupId,
 *              mtp3FtGroupId,
 *              isupFtGroupId,
 *              routingFtGroupId,
 *              timersFtGroupId,
 *              mgmtDataFtGroupId,
 *              ftmPreExecLogicProcName,
 *              ftmPreExecLogicProcLibName,
 *              ftmLoopExecLogicProcName,
 *              ftmLoopExecLogicProcLibName, 
 *              ftmPostExecLogicProcName,
 *              ftmPostExecLogicProcLibName);
 *
 *  See Also:
 ****************************************************************************/
static int
FaultToleranceCreate(ITS_Object obj, va_list args)
{
    ENGINE_FaultTolerance ft = (ENGINE_FaultTolerance)obj;
    ENGINE_Application app;
    ITS_USHORT maxNumFtGroups;
    ITS_USHORT maxNumProcesses;
    ITS_USHORT maxNumNodes;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    ITS_USHORT tcapFtGroupId;
    ITS_USHORT sccpFtGroupId;
    ITS_USHORT mtp3FtGroupId;
    ITS_USHORT isupFtGroupId;
    ITS_USHORT routingFtGroupId;
    ITS_USHORT timersFtGroupId;
    ITS_USHORT mgmtDataFtGroupId;
    char* ftmPreExecLogicProcName;
    char* ftmPreExecLogicProcLibName;
    char* ftmLoopExecLogicProcName;
    char* ftmLoopExecLogicProcLibName;
    char* ftmPostExecLogicProcName;
    char* ftmPostExecLogicProcLibName;

    app = va_arg(args, ENGINE_Application);
    maxNumFtGroups = (ITS_USHORT)va_arg(args, int);
    maxNumProcesses = (ITS_USHORT)va_arg(args, int);
    maxNumNodes = (ITS_USHORT)va_arg(args, int);
    nodeId = (ITS_USHORT)va_arg(args, int);
    processId = (ITS_USHORT)va_arg(args, int);
    tcapFtGroupId = (ITS_USHORT)va_arg(args, int);
    sccpFtGroupId = (ITS_USHORT)va_arg(args, int);
    mtp3FtGroupId = (ITS_USHORT)va_arg(args, int);
    isupFtGroupId = (ITS_USHORT)va_arg(args, int);
    routingFtGroupId = (ITS_USHORT)va_arg(args, int);
    timersFtGroupId = (ITS_USHORT)va_arg(args, int);
    mgmtDataFtGroupId = (ITS_USHORT)va_arg(args, int);
    ftmPreExecLogicProcName = va_arg(args, char*);
    ftmPreExecLogicProcLibName = va_arg(args, char*);
    ftmLoopExecLogicProcName = va_arg(args, char*);
    ftmLoopExecLogicProcLibName = va_arg(args, char*);
    ftmPostExecLogicProcName = va_arg(args, char*);
    ftmPostExecLogicProcLibName = va_arg(args, char*);

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(app != NULL);
    ITS_C_ASSERT(ENGINE_APP_FAULT_TOLERANCE(app) == NULL);

    ENGINE_FT_MAX_NUM_FT_GROUPS(ft) = maxNumFtGroups;
    ENGINE_FT_MAX_NUM_PROCESSES(ft) = maxNumProcesses;
    ENGINE_FT_MAX_NUM_NODES(ft) = maxNumNodes;
    ENGINE_FT_NODE_ID(ft) = nodeId;
    ENGINE_FT_PROCESS_ID(ft) = processId;
    ENGINE_FT_TCAP_FT_GROUP_ID(ft) = tcapFtGroupId;
    ENGINE_FT_SCCP_FT_GROUP_ID(ft) = sccpFtGroupId;
    ENGINE_FT_MTP3_FT_GROUP_ID(ft) = mtp3FtGroupId;
    ENGINE_FT_ISUP_FT_GROUP_ID(ft) = isupFtGroupId;
    ENGINE_FT_ROUTING_FT_GROUP_ID(ft) = routingFtGroupId;
    ENGINE_FT_TIMERS_FT_GROUP_ID(ft) = timersFtGroupId;
    ENGINE_FT_MGMT_DATA_FT_GROUP_ID(ft) = mgmtDataFtGroupId;

    if (ftmPreExecLogicProcName && 
        strlen(ftmPreExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPreExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPreExecLogicProcLibName && 
        strlen(ftmPreExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPreExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }

    if (ftmLoopExecLogicProcName && 
        strlen(ftmLoopExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmLoopExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmLoopExecLogicProcLibName && 
        strlen(ftmLoopExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmLoopExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }

    if (ftmPostExecLogicProcName && 
        strlen(ftmPreExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPostExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPostExecLogicProcLibName && 
        strlen(ftmPostExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPostExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }

    ENGINE_APP_FAULT_TOLERANCE(app) = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a Fault Tolerance object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
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
FaultToleranceDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;

    ENGINE_FaultTolerance ft = (ENGINE_FaultTolerance)obj;

    if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft));
    }

    if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft));
    }

    if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft));
    }

    if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    for (list = ENGINE_FT_CALLBACKS(ft); list != NULL; list = tmp)
    {
        tmp = ENGINE_FT_CALLBACK_NEXT(list);

        ITS_DestructObject(list);
    }

    for (list = ENGINE_FT_FT_GROUPS(ft); list != NULL; list = tmp)
    {
        tmp = ENGINE_FT_GROUP_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare Fault Tolerance records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FaultToleranceCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FaultToleranceClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FaultToleranceRec),   /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE Fault Tolerance Class",     /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FaultToleranceCreate,               /* instance create          */
        FaultToleranceDestroy,              /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FaultToleranceCompare,              /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FaultToleranceClass = &itsENGINE_FaultToleranceClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a application object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ApplicationClass, isService,
 *                          usesCPP, globalStartMask, "libCISCO.so",
 *                          "ss7Selector", "appSelector", "appDeselector");
 *
 *  See Also:
 ****************************************************************************/
static int
ApplicationCreate(ITS_Object obj, va_list args)
{
    ENGINE_Application app = (ENGINE_Application)obj;
    ITS_BOOLEAN isService;
    ITS_BOOLEAN usesCpp;
    ITS_UINT gsMask;
    char *libName, *ss7Selector, *appSelector, *appDeselector, *hmi, *alarm;
    char *preFunc, *postFunc;

    isService = va_arg(args, ITS_BOOLEAN);
    usesCpp = va_arg(args, ITS_BOOLEAN);
    gsMask = va_arg(args, ITS_UINT);
    libName = va_arg(args, char *);
    ss7Selector = va_arg(args, char *);
    appSelector = va_arg(args, char *);
    appDeselector = va_arg(args, char *);
    hmi = va_arg(args, char *);
    alarm = va_arg(args, char *);
    preFunc = va_arg(args, char *);
    postFunc = va_arg(args, char *);

    ENGINE_APP_IS_SERVICE(app) = isService;
    ENGINE_APP_CPP_BINDING(app) = usesCpp;
    ENGINE_APP_GS_MASK(app) = gsMask;
    if (libName && strlen(libName) != 0)
    {
        ENGINE_APP_LIB_NAME(app) = strdup(libName);

        ITS_C_ASSERT(ENGINE_APP_LIB_NAME(app) != NULL);
    }
    if (ss7Selector && strlen(ss7Selector) != 0)
    {
        ENGINE_APP_SS7_SELECTOR(app) = strdup(ss7Selector);

        ITS_C_ASSERT(ENGINE_APP_SS7_SELECTOR(app) != NULL);
    }
    if (appSelector && strlen(appSelector) != 0)
    {
        ENGINE_APP_APP_SELECTOR(app) = strdup(appSelector);

        ITS_C_ASSERT(ENGINE_APP_APP_SELECTOR(app) != NULL);
    }
    if (appDeselector && strlen(appDeselector) != 0)
    {
        ENGINE_APP_APP_DESELECTOR(app) = strdup(appDeselector);

        ITS_C_ASSERT(ENGINE_APP_APP_DESELECTOR(app) != NULL);
    }
    if (hmi && strlen(hmi) != 0)
    {
        ENGINE_APP_HMI_CB(app) = strdup(alarm);

        ITS_C_ASSERT(ENGINE_APP_HMI_CB(app) != NULL);
    }
    if (alarm && strlen(alarm) != 0)
    {
        ENGINE_APP_ALARM_CB(app) = strdup(alarm);

        ITS_C_ASSERT(ENGINE_APP_ALARM_CB(app) != NULL);
    }
    if (preFunc && strlen(preFunc) != 0)
    {
        ENGINE_APP_PRE_FUNC(app) = strdup(preFunc);

        ITS_C_ASSERT(ENGINE_APP_PRE_FUNC(app) != NULL);
    }
    if (postFunc && strlen(postFunc) != 0)
    {
        ENGINE_APP_POST_FUNC(app) = strdup(postFunc);

        ITS_C_ASSERT(ENGINE_APP_POST_FUNC(app) != NULL);
    }

    ENGINE_APP_OPTIONS(app) = NULL;
    ENGINE_APP_NUM_OPTIONS(app) = 0;
    ENGINE_APP_LIB_CACHE(app) = NULL;
    ENGINE_APP_TRACE_LEVELS(app) = NULL;
    ENGINE_APP_FEATURES(app) = NULL;
    ENGINE_APP_POOLS(app) = NULL;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a application object
 *
 *  Input Parameters:
 *      obj - the obj to create
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
 ****************************************************************************/
static void
ApplicationDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;
    int i;

    if (ENGINE_APP_LIB_NAME(obj))
    {
        free(ENGINE_APP_LIB_NAME(obj));
    }

    if (ENGINE_APP_SS7_SELECTOR(obj))
    {
        free(ENGINE_APP_SS7_SELECTOR(obj));
    }

    if (ENGINE_APP_APP_SELECTOR(obj))
    {
        free(ENGINE_APP_APP_SELECTOR(obj));
    }

    if (ENGINE_APP_PRE_FUNC(obj))
    {
        free(ENGINE_APP_PRE_FUNC(obj));
    }

    if (ENGINE_APP_POST_FUNC(obj))
    {
        free(ENGINE_APP_POST_FUNC(obj));
    }

    for (list = ENGINE_APP_LIB_CACHE(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_LC_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_TRACE_LEVELS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TL_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_FEATURES(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_FEAT_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_POOLS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TP_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_PARSER_EXTENSIONS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_PE_NEXT(list);

        ITS_DestructObject(list);
    }

    if (ENGINE_APP_FAULT_TOLERANCE(obj))
    {
        ITS_DestructObject(ENGINE_APP_FAULT_TOLERANCE(obj));
    }

    if (ENGINE_APP_NUM_OPTIONS(obj))
    {
        for (i = 0; i < ENGINE_APP_NUM_OPTIONS(obj); i++)
        {
            free(ENGINE_APP_OPTIONS(obj)[i]);
        }

        free(ENGINE_APP_OPTIONS(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare application records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ApplicationCompare(ITS_Object o1, ITS_Object o2)
{
    /* no point */
    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ApplicationClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ApplicationRec),  /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Application Class",     /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ApplicationCreate,              /* instantiate */
        ApplicationDestroy,             /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ApplicationCompare,             /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ApplicationClass = &itsENGINE_ApplicationClassRec;

