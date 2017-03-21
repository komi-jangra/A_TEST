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
 * LOG: Revision 6.2  2002/04/25 20:01:40  hdivoux
 * LOG: Correction: empty predicate was reversed.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:22  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/06 17:29:12  mmiers
 * LOG: Allow no lock callbacks.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/03/18 21:03:48  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.3  2000/02/15 20:34:43  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.2  2000/02/14 19:17:38  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.1  2000/02/01 19:17:43  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten things out a little better (more appropriate stuff in core).
 * LOG:
 * LOG: Revision 2.4  1999/12/22 02:09:00  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.3  1999/12/15 18:23:15  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 02:44:21  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 23:44:46  mmiers
 * LOG:
 * LOG:
 * LOG: Convert to the new object format.  Only callback is done so far.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:27  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1998/11/19 00:36:23  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.4  1998/11/04 15:21:58  mmiers
 * LOG: Add doc headers to its_callback.
 * LOG:
 * LOG: Revision 1.3  1998/11/03 15:18:18  mmiers
 * LOG: Fix build bugs due to missing prototypes, typos.
 * LOG:
 * LOG: Revision 1.2  1998/11/03 02:56:17  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.1  1998/11/03 02:23:41  mmiers
 * LOG: Add callback implementation.
 * LOG:
 * LOG: Revision 1.1  1998/11/03 01:49:11  mmiers
 * LOG: Start implementing a callback object.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its_assertion.h>
#include <its_callback.h>
#include <its_trace.h>

#ident "$Id: its_callback.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#undef CALLBACK_InitManager
#undef CALLBACK_DestroyManager

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a callback manager
 *
 *  Input Parameters:
 *      obj - memory to construct into
 *      args - unused
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful create.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Construct(ITS_Object obj, va_list args)
{
    CALLBACK_Manager *callbackList = (CALLBACK_Manager *)obj;
    int ret;

    ITS_TRACE_DEBUG(("CALLBACK_InitManager:\n"));

    CALLBACK_NUM_CALLBACKS(callbackList) = 0;
    CALLBACK_NUM_ALLOCATED(callbackList) = CALLBACK_NUM_START;
    CALLBACK_CALLBACK_LIST(callbackList) = NULL;

    if ((ret = MUTEX_CreateMutex(&CALLBACK_GUARD(callbackList), 0)) !=
        ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("CALLBACK_InitManager: Couldn't build mutex\n"));

        return (ret);
    }

    if ((CALLBACK_CALLBACK_LIST(callbackList) =
            (CALLBACK_Entry *)calloc(CALLBACK_NUM_START,
                                     sizeof(CALLBACK_Entry))) == NULL)
    {
        ITS_TRACE_ERROR(("CALLBACK_InitManager: Out of memory\n"));

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy a callback manager
 *
 *  Input Parameters:
 *      obj - the object to destroy
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
Destruct(ITS_Object obj)
{
    CALLBACK_Manager* callbackList = (CALLBACK_Manager *)obj;

    ITS_TRACE_DEBUG(("CALLBACK_DestroyManager:\n"));

    if (CALLBACK_CALLBACK_LIST(callbackList))
    {
        free(CALLBACK_CALLBACK_LIST(callbackList));
    }

    MUTEX_DeleteMutex(&CALLBACK_GUARD(callbackList));
}

/*
 * the callback class record
 */
ITSDLLAPI CALLBACK_ClassRec itsCALLBACK_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,          /* core is superclass */
        sizeof(CALLBACK_Manager),   /* sizeof instance */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial refCount */
        CALLBACK_CLASS_NAME,        /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        Construct,                  /* instantiate */
        Destruct,                   /* destroy */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no extension of interest */
    }
    /* no derivative class methods */
};

ITSDLLAPI ITS_Class itsCALLBACK_Class = (ITS_Class)&itsCALLBACK_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create a callback manager.
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
 *      a pointer to the allocated object.  NULL is returned on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI CALLBACK_Manager*
CALLBACK_InitManager()
{
    return (CALLBACK_Manager *)ITS_ConstructObject(itsCALLBACK_Class, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy a callback manager.
 *
 *  Input Parameters:
 *      callbackList - the object to destroy
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
CALLBACK_DestroyManager(CALLBACK_Manager* callbackList)
{
    ITS_DestructObject((ITS_Object)&callbackList->core);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a callback to a list of callbacks.
 *
 *  Input Parameters:
 *      callbackList - the manager to add a callback to
 *      callFunc - the callback to add
 *      userData - the second parameter of the callback function
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the callback was added.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
CALLBACK_AddCallback(CALLBACK_Manager* callbackList,
                     ITS_CALLBACK callFunc,
                     ITS_POINTER userData)
{
    ITS_TRACE_DEBUG(("CALLBACK_AddCallback:\n"));

    ITS_C_REQUIRE(callbackList != NULL);
    ITS_C_REQUIRE(callFunc != NULL);

    if (MUTEX_AcquireMutex(&CALLBACK_GUARD(callbackList)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("CALLBACK_AddCallback: Couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if ((CALLBACK_NUM_CALLBACKS(callbackList) + 1) >=
        CALLBACK_NUM_ALLOCATED(callbackList))
    {
        if ((CALLBACK_CALLBACK_LIST(callbackList) =
                (CALLBACK_Entry *)realloc((void *)CALLBACK_CALLBACK_LIST(callbackList),
                                          (CALLBACK_NUM_ALLOCATED(callbackList) * 2) *
                                              sizeof(CALLBACK_Entry))) == NULL)
        {
            ITS_TRACE_ERROR(("CALLBACK_AddCallback: Out of memory\n"));

            MUTEX_ReleaseMutex(&CALLBACK_GUARD(callbackList));

            return (ITS_ENOMEM);
        }

        CALLBACK_NUM_ALLOCATED(callbackList) *= 2;
    }

    CALLBACK_CALLBACK_LIST(callbackList)[CALLBACK_NUM_CALLBACKS(callbackList)].func = callFunc;
    CALLBACK_CALLBACK_LIST(callbackList)[CALLBACK_NUM_CALLBACKS(callbackList)].userData = userData;

    CALLBACK_NUM_CALLBACKS(callbackList)++;

    MUTEX_ReleaseMutex(&CALLBACK_GUARD(callbackList));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove a callback
 *
 *  Input Parameters:
 *      callbackList - the manager to remove from
 *      callFunc - the function to remove
 *      userData - userData to match
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
 *      Both callFunc and userData must match what was added (to allow
 *      the same function to be registered more than once).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
CALLBACK_RemCallback(CALLBACK_Manager* callbackList,
                     ITS_CALLBACK callFunc,
                     ITS_POINTER userData)
{
    int i;

    ITS_TRACE_DEBUG(("CALLBACK_RemCallback:\n"));

    ITS_C_REQUIRE(callbackList != NULL);
    ITS_C_REQUIRE(callFunc != NULL);

    if (MUTEX_AcquireMutex(&CALLBACK_GUARD(callbackList)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("CALLBACK_AddCallback: Couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    for (i = 0; i < CALLBACK_NUM_CALLBACKS(callbackList); i++)
    {
        if (CALLBACK_CALLBACK_LIST(callbackList)[CALLBACK_NUM_CALLBACKS(callbackList)].func
            == callFunc &&
            CALLBACK_CALLBACK_LIST(callbackList)[CALLBACK_NUM_CALLBACKS(callbackList)].userData
            == userData)
        {
            if (i == (CALLBACK_NUM_CALLBACKS(callbackList) - 1))
            {
                CALLBACK_NUM_CALLBACKS(callbackList)--;

                MUTEX_ReleaseMutex(&CALLBACK_GUARD(callbackList));

                return (ITS_SUCCESS);
            }
            else
            {
                memmove(&CALLBACK_CALLBACK_LIST(callbackList)[i],
                        &CALLBACK_CALLBACK_LIST(callbackList)[i + 1],
                        (CALLBACK_NUM_CALLBACKS(callbackList) - i - 1) *
                            sizeof(CALLBACK_Entry));

                MUTEX_ReleaseMutex(&CALLBACK_GUARD(callbackList));

                return (ITS_SUCCESS);
            }
        }
    }

    MUTEX_ReleaseMutex(&CALLBACK_GUARD(callbackList));

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Call a single callback.
 *
 *  Input Parameters:
 *      callbackObj - a callback entry
 *      object - parameter one of the callback function
 *      callData - parameter three of the callback function
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the callback was successfully invoked.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
CALLBACK_CallCallback(CALLBACK_Entry* callbackObj,
                      ITS_POINTER object,
                      ITS_POINTER callData)
{
    ITS_TRACE_DEBUG(("CALLBACK_CallCallback:\n"));

    ITS_C_REQUIRE(callbackObj != NULL);

    if (callbackObj->func == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    (callbackObj->func)(object, callbackObj->userData, callData);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Call all registered callbacks on this manager
 *
 *  Input Parameters:
 *      callbackList - the manager to invoke
 *      object - parameter one of the callbacks
 *      callData - parameter three of the callbacks
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
 *      The callback mutex ensures the integrity of the callback manager
 *      while this function is invoked.
 *      The callback manager should really be protected with a RWLock,
 *      but that can't be used here.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
CALLBACK_CallCallbackList(CALLBACK_Manager* callbackList,
                          ITS_POINTER object,
                          ITS_POINTER callData)
{
    int i;

    ITS_TRACE_DEBUG(("CALLBACK_CallCallbackList:\n"));

    ITS_C_REQUIRE(callbackList != NULL);

    if (MUTEX_AcquireMutex(&CALLBACK_GUARD(callbackList)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("CALLBACK_CallCallbackList: Couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    for (i = 0; i < CALLBACK_NUM_CALLBACKS(callbackList); i++)
    {
        CALLBACK_CallCallback(&CALLBACK_CALLBACK_LIST(callbackList)[i],
                              object,
                              callData);
    }

    MUTEX_ReleaseMutex(&CALLBACK_GUARD(callbackList));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Call the callback list without locking first.
 *
 *  Input Parameters:
 *      callbackList - the manager to invoke
 *      object - parameter one of the callbacks
 *      callData - parameter three of the callbacks
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
 *      This function is inherently dangerous (no locking).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
CALLBACK_CallCallbackListNoLock(CALLBACK_Manager* callbackList,
                                ITS_POINTER object,
                                ITS_POINTER callData)
{
    int i;

    ITS_TRACE_DEBUG(("CALLBACK_CallCallbackListNoLock:\n"));

    ITS_C_REQUIRE(callbackList != NULL);

    for (i = 0; i < CALLBACK_NUM_CALLBACKS(callbackList); i++)
    {
        CALLBACK_CallCallback(&CALLBACK_CALLBACK_LIST(callbackList)[i],
                              object,
                              callData);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Predicate to see if the callback list is empty
 *
 *  Input Parameters:
 *      callbackList - the manager to invoke
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
ITSDLLAPI ITS_BOOLEAN
CALLBACK_IsListEmpty(CALLBACK_Manager *callbackList)
{
    if (CALLBACK_NUM_CALLBACKS(callbackList))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

