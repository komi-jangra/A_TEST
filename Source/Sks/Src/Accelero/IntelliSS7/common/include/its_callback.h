/****************************************************************************
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
 * LOG: Revision 4.2  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
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
 * LOG: Revision 3.5  2001/02/06 17:29:12  mmiers
 * LOG: Allow no lock callbacks.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2000/08/23 00:02:09  mmiers
 * LOG:
 * LOG: Get the fastcall macros working.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:10  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/06/13 19:15:53  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.4  2000/05/11 22:17:24  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for link sets.
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:31  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 18:21:09  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 23:44:45  mmiers
 * LOG:
 * LOG:
 * LOG: Convert to the new object format.  Only callback is done so far.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.6  1999/11/12 16:30:09  mmiers
 * LOG:
 * LOG:
 * LOG: Skip C++ if C.
 * LOG:
 * LOG: Revision 1.5  1999/11/12 16:17:06  mmiers
 * LOG:
 * LOG:
 * LOG: Solaris fixes.
 * LOG:
 * LOG: Revision 1.4  1999/02/04 22:26:37  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.3  1998/11/03 15:18:17  mmiers
 * LOG: Fix build bugs due to missing prototypes, typos.
 * LOG:
 * LOG: Revision 1.2  1998/11/03 02:23:40  mmiers
 * LOG: Add callback implementation.
 * LOG:
 * LOG: Revision 1.1  1998/11/03 01:49:11  mmiers
 * LOG: Start implementing a callback object.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_CALLBACK_H
#define ITS_CALLBACK_H

#include <its.h>
#include <its_mutex.h>
#include <its_object.h>

#ident "ID: $Id: its_callback.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(ITS_CALLBACK_ONESHOT)
#define ITS_CALLBACK_ONESHOT

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * callback structures
 */
typedef void (*ITS_CALLBACK)(ITS_POINTER object,
                             ITS_POINTER userData,
                             ITS_POINTER callData);

typedef struct
{
    ITS_CALLBACK    func;
    ITS_POINTER     userData;
}
CALLBACK_Entry;

/*
 * callback instance data
 */
typedef struct
{
    ITS_MUTEX       guard;
    int             numCallbacks;
    int             numAllocated;
    CALLBACK_Entry* callbackList;
}
CALLBACK_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    CALLBACK_ObjectPart callback;
}
CALLBACK_Manager;

#define CALLBACK_GUARD(x) \
    ((x)->callback.guard)

#define CALLBACK_NUM_CALLBACKS(x) \
    ((x)->callback.numCallbacks)

#define CALLBACK_NUM_ALLOCATED(x) \
    ((x)->callback.numAllocated)

#define CALLBACK_CALLBACK_LIST(x) \
    ((x)->callback.callbackList)

/*
 * class record
 */
typedef struct
{
    ITS_CoreClassPart   coreClass;
}
CALLBACK_ClassRec, *CALLBACK_Class;

#define CALLBACK_CLASS_NAME "CALLBACK"

ITSDLLAPI extern CALLBACK_ClassRec    itsCALLBACK_ClassRec;
ITSDLLAPI extern ITS_Class            itsCALLBACK_Class;

#define CALLBACK_NUM_START    8

/*.interface:CALLBACK
 *****************************************************************************
 *  Interface:
 *      CALLBACK_*.
 *
 *  Purpose:
 *      This interface is used to manage lists of callback functions.
 *      Callbacks are used in situations where asynchronous handling of
 *      indications is preferred over message delivery via transports.
 *
 *  Usage:
 *      The user must first initialize a callback manager structure.  They
 *      can then add callback functions to the structure
 *
 *****************************************************************************/

#if !defined(ITS_FASTCALL)

CALLBACK_Manager* CALLBACK_InitManager();
void CALLBACK_DestroyManager(CALLBACK_Manager* callbackList);

#else /* ITS_FASTCALL */

#define CALLBACK_InitManager() \
    (CALLBACK_Manager *)ITS_ConstructObject(itsCALLBACK_Class, NULL)

#define CALLBACK_DestroyManager(m) \
    ITS_DestructObject((ITS_Object)(m))

#endif /* !defined(ITS_FASTCALL) */

ITSDLLAPI int CALLBACK_AddCallback(CALLBACK_Manager* callbackList,
                                   ITS_CALLBACK callFunc,
                                   ITS_POINTER userData);

ITSDLLAPI int CALLBACK_RemCallback(CALLBACK_Manager* callbackList,
                                   ITS_CALLBACK callFunc,
                                   ITS_POINTER userData);

ITSDLLAPI int CALLBACK_CallCallback(CALLBACK_Entry* callbackObj,
                                    ITS_POINTER object,
                                    ITS_POINTER callData);

ITSDLLAPI int CALLBACK_CallCallbackList(CALLBACK_Manager* callbackList,
                                        ITS_POINTER object,
                                        ITS_POINTER callData);

ITSDLLAPI int CALLBACK_CallCallbackListNoLock(CALLBACK_Manager* callbackList,
                                              ITS_POINTER object,
                                              ITS_POINTER callData);

ITSDLLAPI ITS_BOOLEAN CALLBACK_IsListEmpty(CALLBACK_Manager *callbackList);

#if defined(__cplusplus)
}
#endif

#endif /* ONE_SHOT */

#if defined(USE_CPLUSPLUS)

#include <its_exception.h>

/*.interface:CallbackManager
 *****************************************************************************
 *  Interface:
 *      CallbackManager
 *
 *  Purpose:
 *      This interface is used to manage lists of callback functions.
 *      Callbacks are used in situations where asynchronous handling of
 *      indications is preferred over message delivery via transports.
 *
 *  Usage:
 *
 *****************************************************************************/
class CallbackManager
{
public:
    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method constructs the callback manager object.
    *
    *  Input Parameters:
    *       assocObject - the object (if any) this callback manager will be
    *           associated with.
    *
    *  Notes:
    *       Throws exception if manager cannot be initialized.
    *
    ************************************************************************/
    CallbackManager(ITS_POINTER assocObject)
        : object(assocObject)
    {
        manager = CALLBACK_InitManager();

        ITS_THROW_ASSERT(manager != NULL);
    }

    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method destroys the callback manager object.
    *
    ************************************************************************/
    virtual
    ~CallbackManager()
    {
        CALLBACK_DestroyManager(manager);
    }

    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method adds a callback function to the callback list.
    *
    *  Input Parameters:
    *       callback - the callback function pointer
    *       userData - data to be passed to the callback at every
    *           invocation.
    *
    *  Return Value:
    *       ITS_SUCCESS - if successful.  Any other return value indicates
    *           an IntelliSS7 error.
    *
    *  See Also:
    *       RemCallback()
    ************************************************************************/
    int
    AddCallback(ITS_CALLBACK callback, ITS_POINTER userData)
    {
        return CALLBACK_AddCallback(manager, callback, userData);
    }
    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method removes a callback from the callback list.
    *
    *  Input Parameters:
    *       callback - the callback function pointer
    *       userData - data to be passed to the callback at every
    *           invocation.
    *
    *  Return Value:
    *       ITS_SUCCESS - if successful.  Any other return value indicates
    *           an IntelliSS7 error.
    *
    *  Notes:
    *       The user must supply exactly the same "callback" and "userData"
    *       arguments that were passed to AddCallback().  The "callback"
    *       function alone is insufficient, as the user could not add
    *       the same callback function twice with different userData values.
    *
    *  See Also:
    *       AddCallback()
    ************************************************************************/
    int
    RemCallback(ITS_CALLBACK callback, ITS_POINTER userData)
    {
        return CALLBACK_RemCallback(manager, callback, userData);
    }
    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method calls all callbacks in the callback list.
    *
    *  Input Parameters:
    *       callData - per invocation callback function argument
    *
    *  Return Value:
    *       ITS_SUCCESS - if successful.  Any other return value indicates
    *           an IntelliSS7 error.
    *
    *  Notes:
    *       This method calls all callbacks in the callback list, passing
    *       the associated object as the first argument, the userData as
    *       the second argument, and the callData as the third argument.
    *       The callback list is locked before the first callback is invoked,
    *       and unlocked after all callbacks have been called.
    *
    ************************************************************************/
    int
    CallCallbacks(ITS_POINTER callData)
    {
        return CALLBACK_CallCallbackList(manager, object, callData);
    }

    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method sets the object that this callback manager is
    *       associated with.  NULL is a legal value.
    *
    *  Input Parameters:
    *       assocObject - the associated object.
    *
    *  See Also:
    *       GetAssociatedObject()
    ************************************************************************/
    void
    SetAssociatedObject(ITS_POINTER assocObject)
    {
        object = assocObject;
    }
    /*.implementation:public,inline,CallbackManager
    ************************************************************************
    *  Purpose:
    *       This method returns the value of the associated object pointer.
    *
    *  Return Value:
    *       ITS_POINTER - the associated object pointer.
    *
    ************************************************************************/
    ITS_POINTER
    GetAssociatedObject()
    {
        return object;
    }

private:
    /* no copies */
    CallbackManager() {}
    CallbackManager(CallbackManager&) {}
    CallbackManager& operator=(CallbackManager&) { return *this; }

    CALLBACK_Manager*   manager;
    ITS_POINTER         object;
};

#endif /* USE_CPLUS_PLUS */

#endif /* ITS_CALLBACK_H */
