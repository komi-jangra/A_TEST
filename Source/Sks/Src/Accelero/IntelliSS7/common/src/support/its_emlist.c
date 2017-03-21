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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:58:53  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:06:02  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.12  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.11  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.10  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.9  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.8  2001/01/31 00:55:49  mmiers
 * LOG: A few typos.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.5  2001/01/19 19:33:08  mmiers
 * LOG: Mysteries
 * LOG:
 * LOG: Revision 3.4  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.3  2000/11/29 20:05:39  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:27:22  mmiers
 * LOG: Add user data to list remove procs
 * LOG: Add memory pool for quick reclamation
 * LOG: Add object creation into user supplied buffer
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/06/13 23:07:56  rsonak
 * LOG:
 * LOG:
 * LOG: Typo in Unlock method.
 * LOG:
 * LOG: Revision 2.5  2000/05/17 17:08:19  mmiers
 * LOG:
 * LOG:
 * LOG: Help debugging a bit.
 * LOG:
 * LOG: Revision 2.4  2000/02/15 20:34:46  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:41  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  1999/12/22 02:09:00  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 18:23:15  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1999/06/23 16:36:44  mmiers
 * LOG:
 * LOG:
 * LOG: Oops, make sure that allocation/deallocation to the free pool is
 * LOG: mutex protected.
 * LOG:
 * LOG: Revision 1.18  1998/11/19 00:36:24  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.17  1998/09/28 16:21:09  mmiers
 * LOG: Misleading message.
 * LOG:
 * LOG: Revision 1.16  1998/09/22 18:51:18  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.15  1998/09/21 22:52:32  mmiers
 * LOG: Start adding C-trace to infrastructure.
 * LOG:
 * LOG: Revision 1.14  1998/06/16 00:00:24  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.13  1998/06/01 16:35:30  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.12  1998/05/26 20:15:30  mmiers
 * LOG: More work on the documentation.  The custom build step on NT generates
 * LOG: the HTML doc files.
 * LOG:
 * LOG: Revision 1.11  1998/05/26 16:29:27  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.10  1998/04/24 16:20:21  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.9  1998/04/16 15:59:00  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.8  1998/04/16 04:46:31  mmiers
 * LOG: Fixes for WIP.
 * LOG:
 * LOG: Revision 1.7  1998/04/06 15:43:51  mmiers
 * LOG: Fix list remove bug indicated by the vendor code.
 * LOG:
 * LOG: Revision 1.6  1998/04/06 15:26:49  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.5  1998/04/03 22:17:54  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.4  1998/03/13 04:11:46  mmiers
 * LOG: Update files with latest code.  emlist represents portable message queues.
 * LOG:
 * LOG: Revision 1.3  1998/03/12 03:50:55  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 00:26:00  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:55  mmiers
 * LOG: Add new files for lists, mutex protected lists, and semaphore gated mutex
 * LOG: protected lists (aka "Event Queues").
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include <its.h>
#include <its_mutex.h>
#include <its_semaphore.h>
#include <its_mlist.h>
#include <its_emlist.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_emlist.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates an EMLIST_Manager data structure, and
 *      performs all initialization necessary for that structure; this
 *      includes creating the mutex and semaphore associated with this
 *      structure.
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
 *      On success, this function returns a pointer to the initialized
 *          data structure.
 *      On failure, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      Delete()
 ****************************************************************************/
static int
Create(ITS_Object obj, va_list args)
{
    EMLIST_Manager *lm = (EMLIST_Manager *)obj;

    ITS_TRACE_DEBUG(("EMLIST_Create:\n"));

    if (SEMA_CreateSemaphore(&EMLIST_SEMAPHORE(lm), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Create: can't create semaphore\n"));

        return (ITS_EBADSEMAPHORE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function destroys an instance of the EMLIST_Manager data
 *      structure.  In addition, it destroys the buffer pool associated
 *      with this EMLIST, as well as all pending events.
 *
 *  Input Parameters:
 *      lm - a pointer to the EMLIST_Manager to destroy.
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
 *      Create()
 ****************************************************************************/
static void
Delete(ITS_Object obj)
{
    EMLIST_Manager *lm = (EMLIST_Manager *)obj;

    ITS_TRACE_DEBUG(("Delete:\n"));

    if (lm)
    {
        SEMA_DeleteSemaphore(&EMLIST_SEMAPHORE(lm));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function implements the "event queue" functionality of EMLIST(s).
 *      Callers of this function will block until an entry has been added
 *      to the list; at that point, the caller will be awakened, and attempt
 *      to retrieve the first entry on the list.
 *
 *      Entries to the list can be of arbitrary size, but in practice the
 *      entries on any given list should be of the same size in order to
 *      maximize the efficiency of the buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
static int
GetNextEvent(EMLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("GetNextEvent:\n"));

    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(len != NULL);

    if (SEMA_WaitSemaphore(&EMLIST_SEMAPHORE(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetNextEvent: semaphore error\n"));

        return (ITS_EBADSEMAPHORE);
    }

    return LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method allows the user to "peek" at the event list to see
 *      if an event is pending.  If an event is present, the event will
 *      be dequeued.  If no event is present, the function returns
 *      immediately.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
static int
PeekNextEvent(EMLIST_Manager *lm, void **data, int *len)
{
    int ret;

    ITS_TRACE_DEBUG(("PeekNextEvent:\n"));

    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(len != NULL);

    *data = NULL;
    *len = 0;

    if ((ret = SEMA_TryWaitSemaphore(&EMLIST_SEMAPHORE(lm))) != ITS_SUCCESS)
    {
        ITS_TRACE_DEBUG(("PeekNextEvent: semaphore not posted\n"));

        if (ret == ITS_EWOULDBLOCK)
        {
            return (ITS_ENOMSG);
        }

        return (ret);
    }

    return LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function implements the "event queue" functionality of EMLIST(s).
 *      Callers of this function will block until an entry has been added
 *      to the list; at that point, the caller will be awakened, and attempt
 *      to retrieve the first entry on the list.
 *
 *      Entries to the list can be of arbitrary size, but in practice the
 *      entries on any given list should be of the same size in order to
 *      maximize the efficiency of the buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *      msecs - how long to wait.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
static int
GetNextEventWithTimeOut(EMLIST_Manager *lm, void **data, int *len,
                        ITS_UINT msecs)
{
    int ret;

    ITS_TRACE_DEBUG(("GetNextEvent:\n"));

    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(len != NULL);

    if ((ret = SEMA_WaitSemaphoreWithTimeOut(&EMLIST_SEMAPHORE(lm),
                                             msecs)) != ITS_SUCCESS)
    {
        if (ret == ITS_ETIMEOUT)
        {
            return (ret);
        }

        ITS_TRACE_ERROR(("GetNextEvent: semaphore error\n"));

        return (ITS_EBADSEMAPHORE);
    }

    return LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method is used by any entity to place an event on this event
 *      queue.  In doing so, it also signals the semaphore, indicating
 *      that an event is present.  An entity blocked by GetNextEvent() on
 *      this event list will be awakened, and will have an event ready
 *      for processing after this method is called.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this EMLIST
 *      size - the size of the data object to be added
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object to be added is *copied*; that implies that there is
 *      no particular persistence necessary for the object to be added.
 *
 *  See Also:
 ****************************************************************************/
static int
PutEvent(EMLIST_Manager *lm, void *data, int len)
{
    int ret;

    ITS_C_REQUIRE(data != NULL);
    ITS_C_REQUIRE(len != 0);

    ITS_TRACE_DEBUG(("PutEvent:\n"));

    ret = LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                 data, len);

    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("PutEvent: list put error %d\n", ret));

        return (ret);
    }

    return SEMA_PostSemaphore(&EMLIST_SEMAPHORE(lm));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class record.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassPartInitialize(ITS_Class objClass)
{
    if (EMLIST_CLASS_GET_NEXT_EVENT(objClass) == EMLIST_GET_EVENT_INHERIT)
    {
        EMLIST_CLASS_GET_NEXT_EVENT(objClass) =
            EMLIST_CLASS_GET_NEXT_EVENT(ITS_CLASS_SUPERCLASS(objClass));
    }

    if (EMLIST_CLASS_PEEK_NEXT_EVENT(objClass) == EMLIST_GET_EVENT_INHERIT)
    {
        EMLIST_CLASS_PEEK_NEXT_EVENT(objClass) =
            EMLIST_CLASS_PEEK_NEXT_EVENT(ITS_CLASS_SUPERCLASS(objClass));
    }

    if (EMLIST_CLASS_GET_NEXT_EVENT_WITH_TIMEOUT(objClass) ==
        EMLIST_GET_EVENT_TIMEOUT_INHERIT)
    {
        EMLIST_CLASS_GET_NEXT_EVENT_WITH_TIMEOUT(objClass) =
            EMLIST_CLASS_GET_NEXT_EVENT_WITH_TIMEOUT(ITS_CLASS_SUPERCLASS(objClass));
    }

    if (EMLIST_CLASS_PUT_EVENT(objClass) == EMLIST_PUT_EVENT_INHERIT)
    {
        EMLIST_CLASS_PUT_EVENT(objClass) =
            EMLIST_CLASS_PUT_EVENT(ITS_CLASS_SUPERCLASS(objClass));
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record.
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
ClassPartDestroy(ITS_Class objClass)
{
}

/*
 * the class record
 */
ITSDLLAPI EMLIST_ClassRec itsEMLIST_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsMLIST_ClassRec,  /* superclass is MLIST */
        sizeof(EMLIST_Manager),         /* sizeof instance */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        EMLIST_CLASS_NAME,              /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ClassPartInitialize,            /* class initialize part */
        ClassPartDestroy,               /* class destroy part */
        Create,                         /* instantiate */
        Delete,                         /* destroy */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        ITS_INST_HASH_INHERIT,          /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* list part */
    {
        LIST_ADD_INHERIT,           /* list add head */
        LIST_ADD_INHERIT,           /* list add tail */
        LIST_INSERT_INHERIT,        /* list insert */
        LIST_REM_INHERIT,           /* list rem head */
        LIST_REM_INHERIT,           /* list rem tail */
        LIST_REMOVE_INHERIT,        /* list remove */
        LIST_UNLINK_INHERIT,        /* list unlink */
        LIST_EMPTYP_INHERIT,        /* list empty */
        LIST_COUNT_INHERIT          /* list count */
    },
    /* mlist part */
    {
        MLIST_LOCK_UNLOCK_INHERIT,  /* mlist lock */
        MLIST_LOCK_UNLOCK_INHERIT   /* mlist unlock */
    },
    /* emlist part */
    {
        GetNextEvent,               /* emlist getNextEvent */
        PeekNextEvent,              /* emlist peekNextEvent */
        GetNextEventWithTimeOut,    /* emlist getNextEventWithTimeOut */
        PutEvent                    /* emlist putEvent */
    }
};

ITSDLLAPI ITS_Class itsEMLIST_Class = (ITS_Class)&itsEMLIST_ClassRec;

#undef EMLIST_Create
#undef EMLIST_Delete
#undef EMLIST_AddHead
#undef EMLIST_AddTail
#undef EMLIST_Insert
#undef EMLIST_RemHead
#undef EMLIST_RemTail
#undef EMLIST_Remove
#undef EMLIST_Lock
#undef EMLIST_Unlock
#undef EMLIST_RemoveNoLock
#undef EMLIST_EmptyP
#undef EMLIST_GetNextEvent
#undef EMLIST_PeekNextEvent
#undef EMLIST_GetNextEventWithTimeOut
#undef EMLIST_PutEvent

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates an EMLIST_Manager data structure, and
 *      performs all initialization necessary for that structure; this
 *      includes creating the mutex and semaphore associated with this
 *      structure.
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
 *      On success, this function returns a pointer to the initialized
 *          data structure.
 *      On failure, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      EMLIST_Delete()
 ****************************************************************************/
ITSDLLAPI EMLIST_Manager *
EMLIST_Create()
{
    ITS_TRACE_DEBUG(("EMLIST_Create:\n"));

    return (EMLIST_Manager *)ITS_ConstructObject(itsEMLIST_Class, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys an instance of the EMLIST_Manager data
 *      structure.  In addition, it destroys the buffer pool associated
 *      with this EMLIST, as well as all pending events.
 *
 *  Input Parameters:
 *      lm - a pointer to the EMLIST_Manager to destroy.
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
 *      EMLIST_Create()
 ****************************************************************************/
ITSDLLAPI void
EMLIST_Delete(EMLIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("EMLIST_Delete:\n"));

    ITS_DestructObject((ITS_Object)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the head of this
 *      event list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this EMLIST
 *      size - the size of the data object to be added
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object to be added is *copied*; that implies that there is
 *      no particular persistence necessary for the object to be added.
 *
 *  See Also:
 *      EMLIST_AddTail()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_AddHead(EMLIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("EMLIST_AddHead: data %08x len %d\n", data, len));

    return LIST_CLASS_ADD_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the tail of this
 *      event list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this EMLIST
 *      size - the size of the data object to be added
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object to be added is *copied*; that implies that there is
 *      no particular persistence necessary for the object to be added.
 *
 *  See Also:
 *      EMLIST_AddHead()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_AddTail(EMLIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("EMLIST_AddTail: data %08x len %d\n", data, len));

    return LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to an arbitrary
 *      position on this event list.  In practice, the objects on any given
 *      list should be the same size, as this will result in better efficiency
 *      for the buffer pool.  The position at which this object will be
 *      added is user defined; that is, the EMLIST_InsertFunc passed in
 *      as an argument to this function should return ITS_TRUE at the position
 *      this object should be added.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be added to
 *      func - a pointer to the decision function
 *      data - a pointer to a data object to add the this EMLIST
 *      size - the size of the data object to be added
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The decision function will be invoked for every possible position
 *      on the list (including before the head and after the tail).
 *      Invocation of this function will cease as soon as the function
 *      returns a non-zero value.  Insert decision functions take a
 *      pointer the the previous entry, a pointer to the next entry,
 *      and a pointer to the entry to be added.  If the list is empty,
 *      the prev and next pointers will both be NULL, and the function will
 *      only be invoked once.  Before the head of the list, the prev entry
 *      will be NULL.  After the tail of the list, the next pointer will
 *      be NULL.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
EMLIST_Insert(EMLIST_Manager *lm, LIST_InsertFunc func, void *data, int len)
{
    ITS_TRACE_DEBUG(("EMLIST_Insert: data %08x len %d\n", data, len));

    return LIST_CLASS_INSERT(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                func, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the head of
 *      this event list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 *      EMLIST_RemTail()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_RemHead(EMLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("EMLIST_RemHead:\n"));

    return LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the tail of
 *      this event list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 *      EMLIST_RemHead()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_RemTail(EMLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("EMLIST_RemTail:\n"));

    return LIST_CLASS_REM_TAIL(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from an arbitrary
 *      position in this event list, as determined by the user.  In practice,
 *      the objects on any given list should be the same size, as this will
 *      result in better efficiency for the buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *      func - a pointer to the decision function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The decision function will be invoked on all objects in the event
 *      list until a non-zero value is returned.  The non-zero value
 *      indicates that the current node is the node that should be removed.
 *
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
EMLIST_Remove(EMLIST_Manager *lm, LIST_RemoveFunc func,
              void *userData, int userDataLen,
              void **data, int *len)
{
    ITS_TRACE_DEBUG(("EMLIST_Remove:\n"));

    return LIST_CLASS_REMOVE(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm, func,
                                                userData, userDataLen,
                                                data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function implements the "empty" predicate for EMLIST(s).  If the
 *      function returns true, there are no entries (currently) on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the EMLIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the function executed successfully, and the EMLIST is not empty,
 *          then ITS_TRUE will be returned
 *      On error, or if the list is not empty, then ITS_FALSE will be returned
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
EMLIST_EmptyP(EMLIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("EMLIST_EmptyP:\n"));

    return LIST_CLASS_EMPTYP(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows a user to unconditionally lock access to an
 *      EMLIST.  Note that the use of this function is discouraged, as
 *      most other functions in this interface will try to acquire the lock;
 *      if a caller invokes this function, followed by any of the standard
 *      functions, the caller will deadlock itself.
 *
 *  Input Parameters:
 *      lm - a pointer to the EMLIST to lock
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function is designed for use with EMLIST_RemoveNoLock().  This
 *      allows a user to lock the list, walk it, remove entries with
 *      EMLIST_RemoveNoLock(), and unlock the list with EMLIST_Unlock()
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      EMLIST_Unlock(), EMLIST_RemoveNoLock()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_Lock(EMLIST_Manager *lm)
{
    return MLIST_CLASS_LOCK(ITS_OBJ_CLASS(lm))((MLIST_Manager *)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows a user to unconditionally unlock access to an
 *      EMLIST.  Note that the use of this function is discouraged, as
 *      most other functions in this interface will try to acquire the lock.
 *
 *  Input Parameters:
 *      lm - a pointer to the EMLIST to lock
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function is designed for use with EMLIST_RemoveNoLock().  This
 *      allows a user to lock the list with EMLIST_Lock(), walk it,
 *      remove entries with EMLIST_RemoveNoLock(), and unlock the list,
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      EMLIST_RemoveNoLock(), EMLIST_Lock()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_Unlock(EMLIST_Manager *lm)
{
    return MLIST_CLASS_UNLOCK(ITS_OBJ_CLASS(lm))((MLIST_Manager *)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows the caller to remove an entry from the list
 *      without locking it first.  The use of this function is *highly*
 *      discouraged, as it intentionally circumvents the mutex guard on
 *      the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the EMLIST to lock
 *      msg - a pointer to the EMLIST_Entry to remove
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function allows a user to lock the list with EMLIST_Lock(),
 *      walk it, remove entries, and unlock the list with EMLIST_Unlock(),
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      EMLIST_Lock(), EMLIST_Unlock()
 ****************************************************************************/
ITSDLLAPI int
EMLIST_RemoveNoLock(EMLIST_Manager *lm, LIST_Entry *msg)
{
    ITS_TRACE_DEBUG(("EMLIST_RemoveNoLock:\n"));

    return LIST_CLASS_UNLINK(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                msg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function implements the "event queue" functionality of EMLIST(s).
 *      Callers of this function will block until an entry has been added
 *      to the list; at that point, the caller will be awakened, and attempt
 *      to retrieve the first entry on the list.
 *
 *      Entries to the list can be of arbitrary size, but in practice the
 *      entries on any given list should be of the same size in order to
 *      maximize the efficiency of the buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
EMLIST_GetNextEvent(EMLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("EMLIST_GetNextEvent:\n"));

    return EMLIST_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(lm))(lm, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method allows the user to "peek" at the event list to see
 *      if an event is pending.  If an event is present, the event will
 *      be dequeued.  If no event is present, the function returns
 *      immediately.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
EMLIST_PeekNextEvent(EMLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("EMLIST_PeekNextEvent:\n"));

    return EMLIST_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(lm))(lm, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function implements the "event queue" functionality of EMLIST(s).
 *      Callers of this function will block until an entry has been added
 *      to the list; at that point, the caller will be awakened, and attempt
 *      to retrieve the first entry on the list.
 *
 *      Entries to the list can be of arbitrary size, but in practice the
 *      entries on any given list should be of the same size in order to
 *      maximize the efficiency of the buffer pool.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be removed from
 *      msecs - how long to wait.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - the address of a pointer in which the data object's address
 *          will be returned
 *      size - a pointer the an integer in which the size of the object will
 *          be returned
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object returned *should* be returned to the buffer pool by
 *      calling ITS_Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
EMLIST_GetNextEventWithTimeOut(EMLIST_Manager *lm, void **data, int *len,
                               ITS_UINT msecs)
{
    ITS_TRACE_DEBUG(("EMLIST_GetNextEvent:\n"));

    return EMLIST_CLASS_GET_NEXT_EVENT_WITH_TIMEOUT(ITS_OBJ_CLASS(lm))(lm,
                                                                       data,
                                                                       len,
                                                                       msecs);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method is used by any entity to place an event on this event
 *      queue.  In doing so, it also signals the semaphore, indicating
 *      that an event is present.  An entity blocked by GetNextEvent() on
 *      this event list will be awakened, and will have an event ready
 *      for processing after this method is called.
 *
 *  Input Parameters:
 *      lm - the EMLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this EMLIST
 *      size - the size of the data object to be added
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      on success, this function returns ITS_SUCCESS.
 *      any other return code indicates IntelliSS7 processing errors.
 *
 *  Notes:
 *      The object to be added is *copied*; that implies that there is
 *      no particular persistence necessary for the object to be added.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
EMLIST_PutEvent(EMLIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("EMLIST_PutEvent:\n"));

    return EMLIST_CLASS_PUT_EVENT(ITS_OBJ_CLASS(lm))(lm, data, len);
}
