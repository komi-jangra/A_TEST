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
 * LOG: Revision 8.3  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2005/01/31 11:32:38  mmanikandan
 * LOG: WIN32 is added along with FASTCALL.
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
 * LOG: Revision 1.7  2001/04/26 15:06:01  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 1.6  2001/04/26 15:01:18  mmiers
 * LOG: Forgot the fastcall
 * LOG:
 * LOG: Revision 1.5  2001/04/26 15:00:04  mmiers
 * LOG: Add error function
 * LOG:
 * LOG: Revision 1.4  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 1.3  2001/03/02 22:44:14  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 1.2  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 1.1  2001/02/08 22:43:05  mmiers
 * LOG: Add dynamic symbol resolution.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_ITS_DLSYM_H_)
#define _ITS_DLSYM_H_

#include <its.h>

#ident "$Id: its_dlsym.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

/*
 * "dumb" implementations (those that can't do dynamic loading)
 * need this.
 */
typedef struct
{
    char    *symName;
    void    *value;
}
DLSYM_Link;

/*
 * object part.
 */
typedef struct
{
    DLSYM_Link          *map;   /* only for "dumb" impls */
    ITS_DLSYM_HANDLE    handle;
}
DLSYM_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    DLSYM_ObjectPart    dlsym;
}
DLSYM_Manager;

#define DLSYM_MAP(x) \
    (((DLSYM_Manager *)(x))->dlsym.map)

#define DLSYM_HANDLE(x) \
    (((DLSYM_Manager *)(x))->dlsym.handle)

/*
 * class part
 */
typedef ITS_DLSYM (*DLSYM_ResolvProc)(DLSYM_Manager *,
                                      const char *);

typedef struct
{
    DLSYM_ResolvProc    resolve;
}
DLSYM_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    DLSYM_ClassPart     dlsymClass;
}
DLSYM_ClassRec, *DLSYM_Class;

#define DLSYM_CLASS_RESOLVE(x) \
    (((DLSYM_Class)(x))->dlsymClass.resolve)

#define DLSYM_CLASS_NAME    "Dynamic Loader Class"

ITSDLLAPI extern DLSYM_ClassRec   itsDLSYM_ClassRec;
ITSDLLAPI extern ITS_Class        itsDLSYM_Class;

/*
 * type for cache
 */
typedef struct _DLSYM_CacheEntry
{
    struct _DLSYM_CacheEntry    *next;
    int                         refCount;
    ITS_DLSYM_HANDLE            handle;
    char                        *name;
}
DLSYM_CacheEntry;

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:DLSYM_
 *****************************************************************************
 *  Interface:
 *      DLSYM_*
 *
 *  Purpose:
 *      This interface provides an API for architecture independent dynamic
 *      symbol resolution.
 *
 *  Usage:
 *      Typical LoadLibrary()/dlopen(), GetProcAddress()/dlsym() usage.
 *      
 *****************************************************************************/

#if !defined(ITS_FASTCALL) || defined (WIN32)

ITSDLLAPI DLSYM_Manager  *DLSYM_Create(const char *dllName);
ITSDLLAPI void            DLSYM_Destroy(DLSYM_Manager *manager);
ITSDLLAPI ITS_DLSYM       DLSYM_Resolve(DLSYM_Manager *manager,
                                        const char *symName);

#else

#define DLSYM_Create(dn) \
    (DLSYM_Manager *)ITS_ConstructObject(itsDLSYM_Class, (dn))

#define DLSYM_Destroy(dm) \
    ITS_DestructObject((ITS_Object)dm)

#define DLSYM_Resolve(dm, sn) \
    DLSYM_CLASS_RESOLVE(ITS_OBJ_CLASS(dm))(dm, sn);

#endif

/*
 * no fastcall for this
 */
ITSDLLAPI const char *    DLSYM_Error();

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_DLSYM_H_ */
