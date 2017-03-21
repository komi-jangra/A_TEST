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
 * LOG: Revision 8.2  2005/03/21 13:50:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
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
 * LOG: Revision 3.4  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:12  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:33  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/10/25 18:43:09  mmiers
 * LOG:
 * LOG:
 * LOG: Add the factory classes.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_FACTORY_H
#define ITS_FACTORY_H

#include <stdarg.h>

#include <its_lockable.h>

#ident "$Id: its_factory.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct _FACTORY_ClassRec *FACTORY_Class;

typedef ITS_Object  (*FACTORY_CreateProc)(FACTORY_Class, va_list);
typedef void        (*FACTORY_DeleteProc)(FACTORY_Class, ITS_Object);

typedef struct
{
    FACTORY_CreateProc  createInstance;
    FACTORY_DeleteProc  deleteInstance;
    /* probably should add register interface, deregister interface */
}
FACTORY_ClassPart;

typedef struct _FACTORY_ClassRec
{
    ITS_CoreClassPart   coreClass;
    FACTORY_ClassPart   factoryClass;
}
FACTORY_ClassRec;

#define FACTORY_CLASS_CREATE_PROC(x) \
    (((FACTORY_Class)(x))->factoryClass.createInstance)

#define FACTORY_CLASS_DELETE_PROC(x) \
    (((FACTORY_Class)(x))->factoryClass.deleteInstance)

ITSDLLAPI ITS_Object  FACTORY_CreateInstance(FACTORY_Class, ...);
ITSDLLAPI void        FACTORY_DeleteInstance(FACTORY_Class, ITS_Object);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_singleton.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Factory
 *****************************************************************************
 *  Interface:
 *      Factory
 *
 *  Purpose:
 *
 *  Usage:
 *****************************************************************************/
template <class _FactoryType_, class _ObjectType_>
class Factory
    : public Singleton<_FactoryType_>
{
public:
    Factory<_FactoryType_, _ObjectType_>()
        : Singleton<_FactoryType_>()
    {
    }

    ~Factory<_FactoryType_, _ObjectType_>()
    {
    }

    static int Initialize();
    static void Terminate();

    static _FactoryType_& GetFactory();

    virtual _ObjectType_* CreateInstance() = 0;
    virtual void          ReleaseInstance(_ObjectType_*) = 0;
};

template <class _FactoryType_, class _ObjectType_>
int
Factory<_FactoryType_, _ObjectType_>::Initialize()
{
    return Singleton<_FactoryType_>::Initialize();
}

template <class _FactoryType_, class _ObjectType_>
void
Factory<_FactoryType_, _ObjectType_>::Terminate()
{
    Singleton<_FactoryType_>::Terminate();
}

template <class _FactoryType_, class _ObjectType_>
_FactoryType_&
Factory<_FactoryType_, _ObjectType_>::GetFactory()
{
    return Singleton<_FactoryType_>::GetShared();
}

/*.interface:Factory
 *****************************************************************************
 *  Interface:
 *      Factory
 *
 *  Purpose:
 *
 *  Usage:
 *****************************************************************************/
template <class _FactoryType_, class _ObjectType_>
class ThreadSafeFactory
    : public SingletonMultithreaded<_FactoryType_>
{
public:
    ThreadSafeFactory<_FactoryType_, _ObjectType_>()
        : SingletonMultithreaded<_FactoryType_>()
    {
    }

    ~ThreadSafeFactory<_FactoryType_, _ObjectType_>()
    {
    }

    static int Initialize();
    static void Terminate();

    static _FactoryType_& GetFactory();

    virtual _ObjectType_* CreateInstance() = 0;
    virtual void          ReleaseInstance(_ObjectType_*) = 0;
};

template <class _FactoryType_, class _ObjectType_>
int
ThreadSafeFactory<_FactoryType_, _ObjectType_>::Initialize()
{
    return SingletonMultithreaded<_FactoryType_>::Initialize();
}

template <class _FactoryType_, class _ObjectType_>
void
ThreadSafeFactory<_FactoryType_, _ObjectType_>::Terminate()
{
    SingletonMultithreaded<_FactoryType_>::Terminate();
}

template <class _FactoryType_, class _ObjectType_>
_FactoryType_&
ThreadSafeFactory<_FactoryType_, _ObjectType_>::GetFactory()
{
    return SingletonMultithreaded<_FactoryType_>::GetShared();
}

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_FACTORY_H */
