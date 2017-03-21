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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:01  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.10  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:00:01  mmiers
 * LOG: Typo fix, thread bug.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:27:24  mmiers
 * LOG: Add user data to list remove procs
 * LOG: Add memory pool for quick reclamation
 * LOG: Add object creation into user supplied buffer
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/08/14 22:50:50  fhasle
 * LOG:
 * LOG: fixed return value for Remove function.
 * LOG:
 * LOG: Revision 2.4  2000/02/15 20:34:48  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:43  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  2000/01/07 23:49:57  fhasle
 * LOG:
 * LOG:
 * LOG: Fix at least two major brain farts.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 18:23:17  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:50  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.16  1999/06/23 16:36:45  mmiers
 * LOG:
 * LOG:
 * LOG: Oops, make sure that allocation/deallocation to the free pool is
 * LOG: mutex protected.
 * LOG:
 * LOG: Revision 1.15  1999/02/25 22:57:11  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.14  1998/11/19 00:36:27  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.13  1998/09/22 18:51:19  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.12  1998/09/22 17:28:30  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.11  1998/06/16 00:00:27  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.10  1998/06/01 16:35:33  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.9  1998/05/26 20:15:32  mmiers
 * LOG: More work on the documentation.  The custom build step on NT generates
 * LOG: the HTML doc files.
 * LOG:
 * LOG: Revision 1.8  1998/04/24 16:20:22  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.7  1998/04/06 15:43:52  mmiers
 * LOG: Fix list remove bug indicated by the vendor code.
 * LOG:
 * LOG: Revision 1.6  1998/04/06 15:26:51  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.5  1998/04/03 22:17:55  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.4  1998/03/13 04:11:47  mmiers
 * LOG: Update files with latest code.  emlist represents portable message queues.
 * LOG:
 * LOG: Revision 1.3  1998/03/12 03:50:56  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 00:26:01  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:56  mmiers
 * LOG: Add new files for lists, mutex protected lists, and semaphore gated mutex
 * LOG: protected lists (aka "Event Queues").
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <its.h>
#include <its_mlist.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_mlist.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates an MLIST_Manager data structure, and
 *      performs all initialization necessary for that structure; this
 *      includes creating the mutex associated with this structure.
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
    MLIST_Manager *lm = (MLIST_Manager *)obj;

    ITS_TRACE_DEBUG(("Create:\n"));

    if (MUTEX_CreateMutex(&MLIST_MUTEX(lm), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Create: couldn't create mutex\n"));

        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function destroys an instance of the MLIST_Manager data
 *      structure.  In addition, it destroys the buffer pool associated
 *      with this MLIST, as well as all pending nodes.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST_Manager to destroy.
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
    MLIST_Manager *lm = (MLIST_Manager *)obj;

    ITS_TRACE_DEBUG(("Delete:\n"));

    if (lm)
    {
        MUTEX_DeleteMutex(&MLIST_MUTEX(lm));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the head of this
 *      mutex list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this MLIST
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
 *      AddTail()
 ****************************************************************************/
static int
AddHead(LIST_Manager *lm, void *data, int len)
{
    int ret;

    ITS_TRACE_DEBUG(("AddHead:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("AddHead: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = LIST_CLASS_ADD_HEAD(itsLIST_Class)(lm, data, len);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the tail of this
 *      mutex list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this MLIST
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
 *      AddHead()
 ****************************************************************************/
static int
AddTail(LIST_Manager *lm, void *data, int len)
{
    int ret;

    ITS_TRACE_DEBUG(("AddTail:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("AddTail: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = LIST_CLASS_ADD_TAIL(itsLIST_Class)(lm, data, len);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to an arbitrary
 *      position on this mutex list.  In practice, the objects on any given
 *      list should be the same size, as this will result in better efficiency
 *      for the buffer pool.  The position at which this object will be
 *      added is user defined; that is, the MLIST_InsertFunc passed in
 *      as an argument to this function should return ITS_TRUE at the position
 *      this object should be added.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be added to
 *      func - a pointer to the decision function
 *      data - a pointer to a data object to add the this MLIST
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
static int
Insert(LIST_Manager *lm, LIST_InsertFunc func, void *data, int len)
{
    int ret;

    ITS_TRACE_DEBUG(("Insert:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Insert: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = LIST_CLASS_INSERT(itsLIST_Class)(lm, func, data, len);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the head of
 *      this mutex list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be removed from
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
 *      RemTail()
 ****************************************************************************/
static int
RemHead(LIST_Manager *lm, void **data, int *len)
{
    int ret;

    ITS_TRACE_DEBUG(("RemHead:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemHead: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = LIST_CLASS_REM_HEAD(itsLIST_Class)(lm, data, len);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the tail of
 *      this mutex list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be removed from
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
 *      RemHead()
 ****************************************************************************/
static int
RemTail(LIST_Manager *lm, void **data, int *len)
{
    int ret;

    ITS_TRACE_DEBUG(("RemTail:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RemTail: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = LIST_CLASS_REM_TAIL(itsLIST_Class)(lm, data, len);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from an arbitrary
 *      position in this mutex list, as determined by the user.  In practice,
 *      the objects on any given list should be the same size, as this will
 *      result in better efficiency for the buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be removed from
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
 *      The decision function will be invoked on all objects in the mutex
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
static int
Remove(LIST_Manager *lm, LIST_RemoveFunc func,
       void *userData, int userDataLen,
       void **data, int *len)
{
    int ret;

    ITS_TRACE_DEBUG(("Remove:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Remove: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    ret = LIST_CLASS_REMOVE(itsLIST_Class)(lm, func,
                                           userData, userDataLen,
                                           data, len);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function implements the "empty" predicate for MLIST(s).  If the
 *      function returns true, there are no entries (currently) on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the function executed successfully, and the MLIST is not empty,
 *          then ITS_TRUE will be returned
 *      On error, or if the list is not empty, then ITS_FALSE will be returned
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
EmptyP(LIST_Manager *lm)
{
    ITS_BOOLEAN ret;

    ITS_TRACE_DEBUG(("EmptyP:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("EmptyP: couldn't acquire mutex\n"));

        return (ITS_FALSE);
    }

    ret = LIST_CLASS_EMPTYP(itsLIST_Class)(lm);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns the number of nodes in the list
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The number of nodes in the list.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_UINT
GetCount(LIST_Manager *lm)
{
    ITS_UINT ret;

    ITS_TRACE_DEBUG(("GetCount:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (MUTEX_AcquireMutex(&MLIST_MUTEX(lm)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetCount: couldn't acquire mutex\n"));

        return (0);
    }

    ret = LIST_CLASS_GET_COUNT(itsLIST_Class)(lm);

    MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function allows a user to unconditionally lock access to an
 *      MLIST.  Note that the use of this function is discouraged, as
 *      most other functions in this interface will try to acquire the lock;
 *      if a caller invokes this function, followed by any of the standard
 *      functions, the caller will deadlock itself.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST to lock
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
 *      This function is designed for use with MLIST_RemoveNoLock().  This
 *      allows a user to lock the list, walk it, remove entries with
 *      MLIST_RemoveNoLock(), and unlock the list with MLIST_Unlock()
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      Unlock(), RemoveNoLock()
 ****************************************************************************/
static int
Lock(MLIST_Manager *lm)
{
    ITS_C_REQUIRE(lm != NULL);

    return MUTEX_AcquireMutex(&MLIST_MUTEX(lm));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function allows a user to unconditionally unlock access to an
 *      MLIST.  Note that the use of this function is discouraged, as
 *      most other functions in this interface will try to acquire the lock.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST to lock
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
 *      This function is designed for use with MLIST_RemoveNoLock().  This
 *      allows a user to lock the list with MLIST_Lock(), walk it,
 *      remove entries with MLIST_RemoveNoLock(), and unlock the list,
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      RemoveNoLock(), Lock()
 ****************************************************************************/
static int
Unlock(MLIST_Manager *lm)
{
    ITS_C_REQUIRE(lm != NULL);

    return MUTEX_ReleaseMutex(&MLIST_MUTEX(lm));
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
ClassPartInitialize(ITS_Class classRec)
{
    if (MLIST_CLASS_LOCK(classRec) == MLIST_LOCK_UNLOCK_INHERIT)
    {
        MLIST_CLASS_LOCK(classRec) =
            MLIST_CLASS_LOCK(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (MLIST_CLASS_UNLOCK(classRec) == MLIST_LOCK_UNLOCK_INHERIT)
    {
        MLIST_CLASS_UNLOCK(classRec) =
            MLIST_CLASS_UNLOCK(ITS_CLASS_SUPERCLASS(classRec));
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record.
 *
 *  Input Parameters:
 *      classRec - the class to destroy
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
ClassPartDestroy(ITS_Class classRec)
{
}

/*
 * the class record
 */
ITSDLLAPI MLIST_ClassRec itsMLIST_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsLIST_ClassRec,   /* superclass is LIST */
        sizeof(MLIST_Manager),          /* sizeof instance */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        MLIST_CLASS_NAME,               /* class name */
        ITS_AddFeature,                 /* class initialize */
        ITS_RemFeature,                 /* class destroy */
        ClassPartInitialize,            /* class initialize part */
        ClassPartDestroy,               /* class destroy part */
        Create,                         /* instantiate */
        Delete,                         /* destroy */
        NULL                            /* no extension of interest */
    },
    /* list part */
    {
        AddHead,                    /* list add head */
        AddTail,                    /* list add tail */
        Insert,                     /* list insert */
        RemHead,                    /* list rem head */
        RemTail,                    /* list rem tail */
        Remove,                     /* list remove */
        LIST_UNLINK_INHERIT,        /* list unlink */
        EmptyP,                     /* list empty */
        GetCount                    /* list count */
    },
    /* mlist part */
    {
        Lock,                       /* mlist lock */
        Unlock                      /* mlist unlock */
    }
};

ITSDLLAPI ITS_Class itsMLIST_Class = (ITS_Class)&itsMLIST_ClassRec;

#undef MLIST_Create
#undef MLIST_Delete
#undef MLIST_AddHead
#undef MLIST_AddTail
#undef MLIST_Insert
#undef MLIST_RemHead
#undef MLIST_RemTail
#undef MLIST_Remove
#undef MLIST_Lock
#undef MLIST_Unlock
#undef MLIST_RemoveNoLock
#undef MLIST_EmptyP

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates an MLIST_Manager data structure, and
 *      performs all initialization necessary for that structure; this
 *      includes creating the mutex associated with this structure.
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
 *      MLIST_Delete()
 ****************************************************************************/
ITSDLLAPI MLIST_Manager *
MLIST_Create()
{
    ITS_TRACE_DEBUG(("MLIST_Create:\n"));

    return (MLIST_Manager *)ITS_ConstructObject(itsMLIST_Class, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys an instance of the MLIST_Manager data
 *      structure.  In addition, it destroys the buffer pool associated
 *      with this MLIST, as well as all pending nodes.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST_Manager to destroy.
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
 *      MLIST_Create()
 ****************************************************************************/
ITSDLLAPI void
MLIST_Delete(MLIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("MLIST_Delete:\n"));

    ITS_DestructObject((ITS_Object)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the head of this
 *      mutex list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this MLIST
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
 *      MLIST_AddTail()
 ****************************************************************************/
ITSDLLAPI int
MLIST_AddHead(MLIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("MLIST_AddHead:\n"));

    return LIST_CLASS_ADD_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the tail of this
 *      mutex list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this MLIST
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
 *      MLIST_AddHead()
 ****************************************************************************/
ITSDLLAPI int
MLIST_AddTail(MLIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("MLIST_AddTail:\n"));

    return LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to an arbitrary
 *      position on this mutex list.  In practice, the objects on any given
 *      list should be the same size, as this will result in better efficiency
 *      for the buffer pool.  The position at which this object will be
 *      added is user defined; that is, the MLIST_InsertFunc passed in
 *      as an argument to this function should return ITS_TRUE at the position
 *      this object should be added.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be added to
 *      func - a pointer to the decision function
 *      data - a pointer to a data object to add the this MLIST
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
MLIST_Insert(MLIST_Manager *lm, LIST_InsertFunc func, void *data, int len)
{
    ITS_TRACE_DEBUG(("MLIST_Insert:\n"));

    return LIST_CLASS_INSERT(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                func, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the head of
 *      this mutex list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be removed from
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
 *      MLIST_RemTail()
 ****************************************************************************/
ITSDLLAPI int
MLIST_RemHead(MLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("MLIST_RemHead:\n"));

    return LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the tail of
 *      this mutex list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be removed from
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
 *      MLIST_RemHead()
 ****************************************************************************/
ITSDLLAPI int
MLIST_RemTail(MLIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("MLIST_RemTail:\n"));

    return LIST_CLASS_REM_TAIL(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                  data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from an arbitrary
 *      position in this mutex list, as determined by the user.  In practice,
 *      the objects on any given list should be the same size, as this will
 *      result in better efficiency for the buffer pool.
 *
 *  Input Parameters:
 *      lm - the MLIST_Manager this data should be removed from
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
 *      The decision function will be invoked on all objects in the mutex
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
MLIST_Remove(MLIST_Manager *lm, LIST_RemoveFunc func,
             void *userData, int userDataLen,
             void **data, int *len)
{
    ITS_TRACE_DEBUG(("MLIST_Remove:\n"));

    return LIST_CLASS_REMOVE(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm, func,
                                                userData, userDataLen,
                                                data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function implements the "empty" predicate for MLIST(s).  If the
 *      function returns true, there are no entries (currently) on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the function executed successfully, and the MLIST is not empty,
 *          then ITS_TRUE will be returned
 *      On error, or if the list is not empty, then ITS_FALSE will be returned
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
MLIST_EmptyP(MLIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("MLIST_EmptyP:\n"));

    return LIST_CLASS_EMPTYP(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the number of nodes in the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *       The number of nodes in the list.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
MLIST_GetCount(MLIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("MLIST_EmptyP:\n"));

    return LIST_CLASS_GET_COUNT(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows a user to unconditionally lock access to an
 *      MLIST.  Note that the use of this function is discouraged, as
 *      most other functions in this interface will try to acquire the lock;
 *      if a caller invokes this function, followed by any of the standard
 *      functions, the caller will deadlock itself.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST to lock
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
 *      This function is designed for use with MLIST_RemoveNoLock().  This
 *      allows a user to lock the list, walk it, remove entries with
 *      MLIST_RemoveNoLock(), and unlock the list with MLIST_Unlock()
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      MLIST_Unlock(), MLIST_RemoveNoLock()
 ****************************************************************************/
ITSDLLAPI int
MLIST_Lock(MLIST_Manager *lm)
{
    return MLIST_CLASS_LOCK(ITS_OBJ_CLASS(lm))(lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows a user to unconditionally unlock access to an
 *      MLIST.  Note that the use of this function is discouraged, as
 *      most other functions in this interface will try to acquire the lock.
 *
 *  Input Parameters:
 *      lm - a pointer to the MLIST to lock
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
 *      This function is designed for use with MLIST_RemoveNoLock().  This
 *      allows a user to lock the list with MLIST_Lock(), walk it,
 *      remove entries with MLIST_RemoveNoLock(), and unlock the list,
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      MLIST_RemoveNoLock(), MLIST_Lock()
 ****************************************************************************/
ITSDLLAPI int
MLIST_Unlock(MLIST_Manager *lm)
{
    return MLIST_CLASS_UNLOCK(ITS_OBJ_CLASS(lm))(lm);
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
 *      lm - a pointer to the MLIST to lock
 *      msg - a pointer to the MLIST_Entry to remove
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
 *      This function allows a user to lock the list with MLIST_Lock(),
 *      walk it, remove entries, and unlock the list with MLIST_Unlock(),
 *      without worrying about other entities disturbing the list during
 *      the walk.
 *
 *  See Also:
 *      MLIST_Lock(), MLIST_Unlock()
 ****************************************************************************/
ITSDLLAPI int
MLIST_RemoveNoLock(MLIST_Manager *lm, LIST_Entry *msg)
{
    ITS_TRACE_DEBUG(("MLIST_RemoveNoLock:\n"));

    return LIST_CLASS_UNLINK(ITS_OBJ_CLASS(lm))((LIST_Manager *)lm,
                                                msg);
}
