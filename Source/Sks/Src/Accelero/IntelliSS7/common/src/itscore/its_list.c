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
 * LOG: Revision 7.1  2002/08/26 22:10:00  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/10/29 17:28:44  ssharma
 * LOG: Bug in Insert function.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.17  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.16  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.15  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.14  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.13  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.12  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.11  2001/01/24 17:27:44  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 3.10  2001/01/24 17:09:18  mmiers
 * LOG: Fourth try
 * LOG:
 * LOG: Revision 3.9  2001/01/24 17:08:34  mmiers
 * LOG: Third try.
 * LOG:
 * LOG: Revision 3.8  2001/01/24 17:08:14  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 3.7  2001/01/24 17:07:21  mmiers
 * LOG: Try rcsid
 * LOG:
 * LOG: Revision 3.6  2001/01/19 19:33:08  mmiers
 * LOG: Mysteries
 * LOG:
 * LOG: Revision 3.5  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.4  2000/10/03 21:17:09  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.3  2000/08/18 23:36:06  mmiers
 * LOG: Start using the mempool.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:27:23  mmiers
 * LOG: Add user data to list remove procs
 * LOG: Add memory pool for quick reclamation
 * LOG: Add object creation into user supplied buffer
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/02/15 20:34:47  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.5  2000/02/14 19:17:43  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.4  2000/02/09 18:51:40  mmiers
 * LOG:
 * LOG:
 * LOG: Debug of EndPoint sockets done.  On to RUDP debug.
 * LOG:
 * LOG: Revision 2.3  1999/12/22 02:09:02  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 18:23:16  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 02:44:22  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:49  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.12  1998/11/19 00:36:26  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.11  1998/09/22 17:28:30  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.10  1998/06/16 00:00:27  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.9  1998/05/26 20:15:31  mmiers
 * LOG: More work on the documentation.  The custom build step on NT generates
 * LOG: the HTML doc files.
 * LOG:
 * LOG: Revision 1.8  1998/04/24 16:20:21  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.7  1998/04/23 17:04:06  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.6  1998/04/06 15:26:50  mmiers
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
 * LOG: Revision 1.2  1998/03/12 00:26:00  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:55  mmiers
 * LOG: Add new files for lists, mutex protected lists, and semaphore gated mutex
 * LOG: protected lists (aka "Event Queues").
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <its.h>
#include <its_list.h>
#include <its_trace.h>
#include <its_mem_pool.h>
#include <its_assertion.h>

#ident "$Id: its_list.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates a LIST_Manager data structure, and
 *      performs all initialization necessary for that structure.
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
    ITS_TRACE_DEBUG(("Create:\n"));

    /* nothing to do */

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function destroys an instance of the LIST_Manager data
 *      structure.  In addition, it destroys the buffer pool associated
 *      with this LIST, as well as all nodes on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST_Manager to destroy.
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
    LIST_Manager *lm = (LIST_Manager *)obj;
    LIST_Entry *entry, *tmp;

    ITS_TRACE_DEBUG(("Delete:\n"));

    if (lm)
    {
        entry = LIST_HEAD(lm);
        for (;;)
        {
            if (entry == NULL)
            {
                break;
            }

            tmp = entry->next;

            if (entry->data)
            {
                ITS_Free(entry->data);
            }

            ITS_Free(entry);

            if (entry == LIST_TAIL(lm))
            {
                break;
            }

            entry = tmp;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the head of this
 *      list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this LIST
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
    LIST_Entry *ni;

    ITS_TRACE_DEBUG(("AddHead:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(data != NULL || len == 0);

    if ((ni = (LIST_Entry *)ITS_Malloc(sizeof(LIST_Entry))) == NULL)
    {
        ITS_TRACE_ERROR(("AddHead: entry alloc failed\n"));

        return (ITS_ENOMEM);
    }

    if ((ni->data = ITS_Malloc(len)) == NULL)
    {
        ITS_TRACE_ERROR(("AddHead: data alloc failed\n"));

        ITS_Free(ni);

        return (ITS_ENOMEM);
    }

    memcpy(ni->data, data, len);
    ni->length = len;

    if (LIST_HEAD(lm) == NULL)
    {
        LIST_HEAD(lm) = LIST_TAIL(lm) = ni;
        ni->prev = NULL;
        ni->next = NULL;
    }
    else if (LIST_HEAD(lm) != NULL)
    {
        LIST_HEAD(lm)->prev = ni;
        ni->next = LIST_HEAD(lm);
        ni->prev = NULL;
        LIST_HEAD(lm) = ni;
    }
    else
    {
        ITS_TRACE_CRITICAL(("AddHead: list is inconsistent\n"));

        ITS_C_REQUIRE(0);
    }

    LIST_COUNT(lm)++;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the tail of this
 *      list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this LIST
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
AddTail(LIST_Manager *lm, void *data, int len)
{
    LIST_Entry *ni;

    ITS_TRACE_DEBUG(("AddTail:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(data != NULL || len == 0);

    if ((ni = (LIST_Entry *)ITS_Malloc(sizeof(LIST_Entry))) == NULL)
    {
        ITS_TRACE_ERROR(("AddTail: entry alloc failed\n"));

        return (ITS_ENOMEM);
    }

    if ((ni->data = ITS_Malloc(len)) == NULL)
    {
        ITS_TRACE_ERROR(("AddTail: data alloc failed\n"));

        ITS_Free(ni);

        return (ITS_ENOMEM);
    }

    memcpy(ni->data, data, len);
    ni->length = len;

    if (LIST_HEAD(lm) == NULL)
    {
        LIST_HEAD(lm) = LIST_TAIL(lm) = ni;
        ni->prev = NULL;
        ni->next = NULL;
    }
    else if (LIST_TAIL(lm) != NULL)
    {
        LIST_TAIL(lm)->next = ni;
        ni->prev = LIST_TAIL(lm);
        ni->next = NULL;
        LIST_TAIL(lm) = ni;
    }
    else
    {
        ITS_TRACE_CRITICAL(("AddTail: list is inconsistent\n"));

        ITS_C_REQUIRE(0);
    }

    LIST_COUNT(lm)++;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to an arbitrary
 *      position on this list.  In practice, the objects on any given
 *      list should be the same size, as this will result in better efficiency
 *      for the buffer pool.  The position at which this object will be
 *      added is user defined; that is, the LIST_InsertFunc passed in
 *      as an argument to this function should return ITS_TRUE at the position
 *      this object should be added.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be added to
 *      func - a pointer to the decision function
 *      data - a pointer to a data object to add the this LIST
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
    LIST_Entry *bef, *aft;
    LIST_Entry *ni;

    ITS_TRACE_DEBUG(("Insert:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(data != NULL || len == 0);

    if ((ni = (LIST_Entry *)ITS_Malloc(sizeof(LIST_Entry))) == NULL)
    {
        ITS_TRACE_ERROR(("Insert: entry alloc failed\n"));

        return (ITS_ENOMEM);
    }

    if ((ni->data = ITS_Malloc(len)) == NULL)
    {
        ITS_TRACE_ERROR(("Insert: data alloc failed\n"));

        ITS_Free(ni);

        return (ITS_ENOMEM);
    }

    memcpy(ni->data, data, len);
    ni->length = len;

    bef = NULL;
    aft = LIST_HEAD(lm);

    /* if the list is empty, give the user one shot to insert it */
    if (bef == NULL && aft == NULL)
    {
        ITS_TRACE_DEBUG(("Insert: insert into empty list\n"));

        if ((*func)(bef, aft, ni))
        {
            ni->prev = NULL;
            ni->next = NULL;
            LIST_HEAD(lm) = LIST_TAIL(lm) = ni;
        }

        return (ITS_SUCCESS);
    }

    /* otherwise, let them play */
    for (;;)
    {
        /* past the end of the list? */
        if (bef == NULL && aft == NULL)
        {
            ITS_TRACE_DEBUG(("Insert: at end of list\n"));

            ITS_Free(ni->data);
            ITS_Free(ni);

            return (ITS_EENDOFLIST);
        }

        if ((*func)(bef, aft, ni))
        {
            /* at head of list? */
            if (aft == LIST_HEAD(lm))
            {
                /* make sure we aren't corrupt */
                ITS_C_ASSERT(bef == NULL);

                /* empty list was handled above */
                if (LIST_HEAD(lm) != NULL)
                {
                    LIST_HEAD(lm)->prev = ni;
                    ni->next = LIST_HEAD(lm);
                    ni->prev = NULL;
                    LIST_HEAD(lm) = ni;
                }
                else
                {
                    ITS_TRACE_CRITICAL(("Insert: list is inconsistent\n"));

                    ITS_C_REQUIRE(0);
                }
            }
            /* at tail of list? */
            else if (bef == LIST_TAIL(lm))
            {
                /* make sure we aren't corrupt */
                ITS_C_ASSERT(aft == NULL);

                /* empty list was handled above */
                if (LIST_TAIL(lm) != NULL)
                {
                    LIST_TAIL(lm)->next = ni;
                    ni->prev = LIST_TAIL(lm);
                    ni->next = NULL;
                    LIST_TAIL(lm) = ni;
                }
                else
                {
                    ITS_TRACE_CRITICAL(("Insert: list is inconsistent\n"));

                    ITS_C_ASSERT(0);
                }
            }
            /* safely in the middle */
            else
            {
                /* make sure we aren't corrupt */
                ITS_C_ASSERT(bef != NULL && aft != NULL);
                ITS_C_ASSERT(bef->next == aft && aft->prev == bef);

                bef->next = ni;
                aft->prev = ni;
                ni->prev = bef;
                ni->next = aft;
            }

            /* we either died or inserted, so return to the user. */
            break;
        }

        /* update the place pointers */
        bef = aft;
        if (aft)
        {
            aft = aft->next;
        }
    }

    LIST_COUNT(lm)++;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the head of
 *      this list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be removed from
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
 *      calling Free() with the object once processing for this
 *      object has been completed.  Failure to do so will cause the
 *      buffer pool to grow without bound.
 *
 *  See Also:
 *      RemTail()
 ****************************************************************************/
static int
RemHead(LIST_Manager *lm, void **data, int *len)
{
    LIST_Entry *di;

    ITS_TRACE_DEBUG(("RemHead:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(data != NULL && len != NULL);

    *data = NULL;
    *len = 0;

    if (LIST_HEAD(lm) == NULL)
    {
        ITS_TRACE_DEBUG(("RemHead: list is empty\n"));

        return (ITS_ENOMSG);
    }
    else
    {
        di = LIST_HEAD(lm);
        if (LIST_HEAD(lm) == LIST_TAIL(lm))
        {
            LIST_HEAD(lm) = LIST_TAIL(lm) = NULL;
        }
        else
        {
            LIST_HEAD(lm) = di->next;
            if (di->next != NULL)
            {
                di->next->prev = NULL;
            }
            else
            {
                LIST_TAIL(lm) = NULL;
            }
        }
    }

    *data = di->data;
    *len = di->length;

    ITS_Free(di);

    LIST_COUNT(lm)--;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the tail of
 *      this list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be removed from
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
RemTail(LIST_Manager *lm, void **data, int *len)
{
    LIST_Entry *di;

    ITS_TRACE_DEBUG(("RemTail:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(data != NULL && len != NULL);

    *data = NULL;
    *len = 0;

    if (LIST_TAIL(lm) == NULL)
    {
        ITS_TRACE_DEBUG(("RemTail: list is empty\n"));

        return (ITS_ENOMSG);
    }
    else
    {
        di = LIST_TAIL(lm);
        if (LIST_HEAD(lm) == LIST_TAIL(lm))
        {
            LIST_HEAD(lm) = LIST_TAIL(lm) = NULL;
        }
        else
        {
            LIST_TAIL(lm) = di->prev;
            if (di->prev != NULL)
            {
                di->prev->next = NULL;
            }
            else
            {
                LIST_HEAD(lm) = NULL;
            }
        }
    }

    *data = di->data;
    *len = di->length;

    ITS_Free(di);

    LIST_COUNT(lm)--;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from an arbitrary
 *      position in this list, as determined by the user.  In practice,
 *      the objects on any given list should be the same size, as this will
 *      result in better efficiency for the buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be removed from
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
 *      calling Free() with the object once processing for this
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
    LIST_Entry *di;

    ITS_TRACE_DEBUG(("Remove:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(data != NULL && len != NULL);

    *data = NULL;
    *len = 0;

    if (LIST_HEAD(lm) == NULL)
    {
        ITS_TRACE_DEBUG(("Remove: list is empty\n"));

        return (ITS_EENDOFLIST);
    }

    di = LIST_HEAD(lm);

    /* if the list is empty, what the heck does the user want? */
    if (LIST_HEAD(lm) == NULL && LIST_TAIL(lm) == NULL)
    {
        ITS_TRACE_DEBUG(("Remove: list is empty\n"));

        return (ITS_EENDOFLIST);
    }

    for (;;)
    {
        /* end of the line? */
        if (di == NULL)
        {
            ITS_TRACE_DEBUG(("Remove: end of list\n"));

            return (ITS_EENDOFLIST);
        }

        if ((*func)(di, userData, userDataLen))
        {
            /* one entry list? */
            if (di == LIST_HEAD(lm) && di == LIST_TAIL(lm))
            {
                LIST_HEAD(lm) = LIST_TAIL(lm) = NULL;
            }
            /* list head? */
            else if (di == LIST_HEAD(lm))
            {
                LIST_HEAD(lm) = di->next;
                if (di->next != NULL)
                {
                    di->next->prev = NULL;
                }
            }
            /* list tail? */
            else if (di == LIST_TAIL(lm))
            {
                LIST_TAIL(lm) = di->prev;
                if (di->prev != NULL)
                {
                    di->prev->next = NULL;
                }
            }
            /* safely buried in list */
            else
            {
                ITS_C_ASSERT(di->prev != NULL && di->next != NULL);

                di->prev->next = di->next;
                di->next->prev = di->prev;
                di->prev = di->next = NULL;
            }

            /* we either died or removed, so exit the loop */
            break;
        }

        di = di->next;
    }

    if (!di)
    {
        ITS_TRACE_DEBUG(("Remove: no entry returned\n"));

        return (ITS_ENOMSG);
    }

    *data = di->data;
    *len = di->length;

    ITS_Free(di);

    LIST_COUNT(lm)--;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function implements the "empty" predicate for LIST(s).  If the
 *      function returns true, there are no entries (currently) on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the function executed successfully, and the LIST is not empty,
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
    ITS_TRACE_DEBUG(("EmptyP:\n"));

    ITS_C_REQUIRE(lm != NULL);

    if (LIST_HEAD(lm) == NULL && LIST_TAIL(lm) == NULL)
    {
        ITS_TRACE_DEBUG(("EmptyP: is empty\n"));

        return (ITS_TRUE);
    }
    else
    {
        ITS_TRACE_DEBUG(("EmptyP: is not empty\n"));

        return (ITS_FALSE);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function allows the caller to remove an arbitrary entry from
 *      the list, knowing only the list entry.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST to lock
 *      msg - a pointer to the LIST_Entry to remove
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
Unlink(LIST_Manager *lm, LIST_Entry *msg)
{
    ITS_TRACE_DEBUG(("Unlink:\n"));

    ITS_C_REQUIRE(lm != NULL);
    ITS_C_REQUIRE(msg != NULL);

    if (LIST_HEAD(lm) == msg)
    {
        LIST_HEAD(lm) = msg->next;
        if (msg->next)
        {
            msg->next->prev = NULL;
        }

        if (LIST_HEAD(lm) == NULL)
        {
            LIST_TAIL(lm) = NULL;
        }
    }
    else if (LIST_TAIL(lm) == msg)
    {
        LIST_TAIL(lm) = msg->prev;
        if (msg->prev)
        {
            msg->prev->next = NULL;
        }

        if (LIST_TAIL(lm) == NULL)
        {
            LIST_HEAD(lm) = NULL;
        }
    }
    else
    {
        ITS_C_ASSERT(msg->prev != NULL && msg->next != NULL);

        msg->prev->next = msg->next;
        msg->next->prev = msg->prev;
    }

    LIST_COUNT(lm)--;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the number of nodes in the list
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST to lock
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      An unsigned number containing the node count
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_UINT
GetCount(LIST_Manager *lm)
{
    return LIST_COUNT(lm);
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
    if (LIST_CLASS_ADD_HEAD(classRec) == LIST_ADD_INHERIT)
    {
        LIST_CLASS_ADD_HEAD(classRec) =
            LIST_CLASS_ADD_HEAD(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_ADD_TAIL(classRec) == LIST_ADD_INHERIT)
    {
        LIST_CLASS_ADD_TAIL(classRec) =
            LIST_CLASS_ADD_TAIL(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_INSERT(classRec) == LIST_INSERT_INHERIT)
    {
        LIST_CLASS_INSERT(classRec) =
            LIST_CLASS_INSERT(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_REM_HEAD(classRec) == LIST_REM_INHERIT)
    {
        LIST_CLASS_REM_HEAD(classRec) =
            LIST_CLASS_REM_HEAD(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_REM_TAIL(classRec) == LIST_REM_INHERIT)
    {
        LIST_CLASS_REM_TAIL(classRec) =
            LIST_CLASS_REM_TAIL(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_REMOVE(classRec) == LIST_REMOVE_INHERIT)
    {
        LIST_CLASS_REMOVE(classRec) =
            LIST_CLASS_REMOVE(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_UNLINK(classRec) == LIST_UNLINK_INHERIT)
    {
        LIST_CLASS_UNLINK(classRec) =
            LIST_CLASS_UNLINK(ITS_CLASS_SUPERCLASS(classRec));
    }

    if (LIST_CLASS_EMPTYP(classRec) == LIST_EMPTYP_INHERIT)
    {
        LIST_CLASS_EMPTYP(classRec) =
            LIST_CLASS_EMPTYP(ITS_CLASS_SUPERCLASS(classRec));
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
ITSDLLAPI LIST_ClassRec itsLIST_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,          /* CORE is superclass */
        sizeof(LIST_Manager),       /* sizeof instance */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial refCount */
        LIST_CLASS_NAME,            /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ClassPartInitialize,        /* class initialize part */
        ClassPartDestroy,           /* class destroy part */
        Create,                     /* instantiate */
        Delete,                     /* destroy */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no extension of interest */
    },
    /* list part */
    {
        AddHead,                    /* list add head */
        AddTail,                    /* list add tail */
        Insert,                     /* list insert */
        RemHead,                    /* list rem head */
        RemTail,                    /* list rem tail */
        Remove,                     /* list remove */
        Unlink,                     /* list unlink */
        EmptyP,                     /* list empty */
        GetCount                    /* list count */
    }
};

ITSDLLAPI ITS_Class itsLIST_Class = (ITS_Class)&itsLIST_ClassRec;

#undef LIST_Create
#undef LIST_Delete
#undef LIST_AddHead
#undef LIST_AddTail
#undef LIST_Insert
#undef LIST_RemHead
#undef LIST_RemTail
#undef LIST_Remove
#undef LIST_Unlink
#undef LIST_EmptyP

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates a LIST_Manager data structure, and
 *      performs all initialization necessary for that structure.
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
 *      This is the one list function that cannot be used on all list
 *      and derived types (MLIST, EMLIST).
 *
 *  See Also:
 *      LIST_Delete()
 ****************************************************************************/
ITSDLLAPI LIST_Manager *
LIST_Create()
{
    ITS_TRACE_DEBUG(("LIST_Create\n"));

    return (LIST_Manager *)(ITS_ConstructObject)(itsLIST_Class, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys an instance of the LIST_Manager data
 *      structure.  In addition, it destroys the buffer pool associated
 *      with this LIST, as well as all nodes on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST_Manager to destroy.
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
 *      This function can be used for MLIST and EMLIST as well.
 *
 *  See Also:
 *      LIST_Create()
 ****************************************************************************/
ITSDLLAPI void
LIST_Delete(LIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("LIST_Delete\n"));

    ITS_DestructObject((ITS_Object)lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the head of this
 *      list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this LIST
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
 *      LIST_AddTail()
 ****************************************************************************/
ITSDLLAPI int
LIST_AddHead(LIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("LIST_AddHead:\n"));

    return LIST_CLASS_ADD_HEAD(ITS_OBJ_CLASS(lm))(lm, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to the tail of this
 *      list.  In practice, the objects on any given list should be
 *      the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be added to
 *      data - a pointer to a data object to add the this LIST
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
 *      LIST_AddTail()
 ****************************************************************************/
ITSDLLAPI int
LIST_AddTail(LIST_Manager *lm, void *data, int len)
{
    ITS_TRACE_DEBUG(("LIST_AddTail:\n"));

    return LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(lm))(lm, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds an arbitrarily sized object to an arbitrary
 *      position on this list.  In practice, the objects on any given
 *      list should be the same size, as this will result in better efficiency
 *      for the buffer pool.  The position at which this object will be
 *      added is user defined; that is, the LIST_InsertFunc passed in
 *      as an argument to this function should return ITS_TRUE at the position
 *      this object should be added.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be added to
 *      func - a pointer to the decision function
 *      data - a pointer to a data object to add the this LIST
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
LIST_Insert(LIST_Manager *lm, LIST_InsertFunc func, void *data, int len)
{
    ITS_TRACE_DEBUG(("LIST_Insert:\n"));

    return LIST_CLASS_INSERT(ITS_OBJ_CLASS(lm))(lm, func, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the head of
 *      this list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be removed from
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
 *      LIST_RemTail()
 ****************************************************************************/
ITSDLLAPI int
LIST_RemHead(LIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("LIST_RemHead:\n"));

    return LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(lm))(lm, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from the tail of
 *      this list.  In practice, the objects on any given list should
 *      be the same size, as this will result in better efficiency for the
 *      buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be removed from
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
 *      LIST_RemTail()
 ****************************************************************************/
ITSDLLAPI int
LIST_RemTail(LIST_Manager *lm, void **data, int *len)
{
    ITS_TRACE_DEBUG(("LIST_RemTail:\n"));

    return LIST_CLASS_REM_TAIL(ITS_OBJ_CLASS(lm))(lm, data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function removes an arbitrarily sized object from an arbitrary
 *      position in this list, as determined by the user.  In practice,
 *      the objects on any given list should be the same size, as this will
 *      result in better efficiency for the buffer pool.
 *
 *  Input Parameters:
 *      lm - the LIST_Manager this data should be removed from
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
LIST_Remove(LIST_Manager *lm, LIST_RemoveFunc func,
            void *userData, int userDataLen,
            void **data, int *len)
{
    ITS_TRACE_DEBUG(("LIST_Remove:\n"));

    return LIST_CLASS_REMOVE(ITS_OBJ_CLASS(lm))(lm, func,
                                                userData, userDataLen,
                                                data, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function implements the "empty" predicate for LIST(s).  If the
 *      function returns true, there are no entries (currently) on the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST_Manager to test
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the function executed successfully, and the LIST is not empty,
 *          then ITS_TRUE will be returned
 *      On error, or if the list is not empty, then ITS_FALSE will be returned
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
LIST_EmptyP(LIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("LIST_EmptyP:\n"));

    return LIST_CLASS_EMPTYP(ITS_OBJ_CLASS(lm))(lm);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allows the caller to remove an arbitrary entry from
 *      the list, knowing only the list entry.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST to lock
 *      msg - a pointer to the LIST_Entry to remove
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
ITSDLLAPI int
LIST_Unlink(LIST_Manager *lm, LIST_Entry *msg)
{
    ITS_TRACE_DEBUG(("LIST_Unlink:\n"));

    return LIST_CLASS_UNLINK(ITS_OBJ_CLASS(lm))(lm, msg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the number of nodes in the list.
 *
 *  Input Parameters:
 *      lm - a pointer to the LIST to lock
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      An unsigned count of the number of nodes
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
LIST_GetCount(LIST_Manager *lm)
{
    ITS_TRACE_DEBUG(("LIST_GetCount:\n"));

    return LIST_CLASS_GET_COUNT(ITS_OBJ_CLASS(lm))(lm);
}
