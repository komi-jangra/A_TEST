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
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:48  cvsadmin
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
 * LOG: Revision 3.16  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.15  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.14  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.13  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.12  2001/02/05 22:43:58  hxing
 * LOG: Order of namespace termination outside HAVE_STL
 * LOG:
 * LOG: Revision 3.11  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.10  2001/01/31 23:40:53  mmiers
 * LOG: Work around thread data duplication.
 * LOG:
 * LOG: Revision 3.9  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.8  2001/01/20 00:05:39  mmiers
 * LOG: Tweaks.
 * LOG:
 * LOG: Revision 3.7  2001/01/20 00:02:50  mmiers
 * LOG: Ditch the non STL lists.  STL deque is faster.
 * LOG:
 * LOG: Revision 3.6  2001/01/19 23:25:18  mmiers
 * LOG: STL emlist fix.
 * LOG:
 * LOG: Revision 3.5  2001/01/19 16:28:18  mmiers
 * LOG: Finish removing the list alloc and free funcs
 * LOG:
 * LOG: Revision 3.4  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.3  2000/08/23 00:02:09  mmiers
 * LOG:
 * LOG: Get the fastcall macros working.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:25:08  mmiers
 * LOG: Add user data to list remove procs.
 * LOG: Add memory pools for quick reclamation.
 * LOG: Add object creation into user supplied buffers.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/08/14 22:51:18  fhasle
 * LOG:
 * LOG: fixed MLIST_Delete macro.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 18:23:15  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 02:47:30  mmiers
 * LOG: Prepare for C inheritance/OO C.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:41  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.22  1999/10/27 14:55:40  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.21  1999/10/26 15:47:42  mmiers
 * LOG:
 * LOG:
 * LOG: Comment the pigs.
 * LOG:
 * LOG: Revision 1.20  1999/10/26 14:27:06  mmiers
 * LOG:
 * LOG:
 * LOG: The truth about STL.
 * LOG:
 * LOG: Revision 1.19  1998/11/19 00:36:19  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.18  1998/06/26 14:30:39  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.17  1998/06/01 16:35:17  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.16  1998/05/29 03:31:31  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.15  1998/05/29 00:32:54  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.14  1998/05/26 20:15:29  mmiers
 * LOG: More work on the documentation.  The custom build step on NT generates
 * LOG: the HTML doc files.
 * LOG:
 * LOG: Revision 1.13  1998/05/19 17:11:46  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.12  1998/04/24 16:20:20  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.11  1998/04/19 02:42:47  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.10  1998/04/17 15:31:53  mmiers
 * LOG: A better implementation of the thread pool.
 * LOG:
 * LOG: Revision 1.9  1998/04/09 14:33:19  mmiers
 * LOG: Visual complains about operator= not having a return value even when hidden
 * LOG: in the private section of the class record and given a stub implementation.
 * LOG:
 * LOG: Revision 1.8  1998/04/09 01:47:18  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.7  1998/04/07 15:42:20  mmiers
 * LOG: Update function signatures in sccp.h.
 * LOG:
 * LOG: Revision 1.6  1998/04/06 15:26:05  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.5  1998/04/03 23:45:05  mmiers
 * LOG: More changes to support C++.
 * LOG:
 * LOG: Revision 1.4  1998/03/13 04:12:31  mmiers
 * LOG: Update files with latest data for TCAP implementation.  emlist represents
 * LOG: portable message queues.
 * LOG:
 * LOG: Revision 1.3  1998/03/12 03:50:54  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 00:25:59  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:10  mmiers
 * LOG: Add some new files for lists, mutex protected lists, and semaphore gated
 * LOG: mutex protected lists.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_MLIST_H
#define ITS_MLIST_H

#include <its.h>
#include <its_mutex.h>
#include <its_list.h>

#ident "$Id: its_mlist.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    ITS_MUTEX   mutex;
}
MLIST_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    LIST_ObjectPart     list;
    MLIST_ObjectPart    mlist;
}
MLIST_Manager;

#define MLIST_MUTEX(x) \
    (((MLIST_Manager *)(x))->mlist.mutex)

/*
 * class methods
 */
typedef int (*MLIST_LockUnlockProc)(MLIST_Manager *);

#define MLIST_LOCK_UNLOCK_INHERIT   ((MLIST_LockUnlockProc)NULL)

/*
 * class record.  Note we inherit from the LIST class
 */
typedef struct
{
    MLIST_LockUnlockProc    lock;
    MLIST_LockUnlockProc    unlock;
}
MLIST_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    LIST_ClassPart      listClass;
    MLIST_ClassPart     mlistClass;
}
MLIST_ClassRec, *MLIST_Class;

#define MLIST_CLASS_LOCK(x) \
    (((MLIST_Class)(x))->mlistClass.lock)

#define MLIST_CLASS_UNLOCK(x) \
    (((MLIST_Class)(x))->mlistClass.unlock)

#define MLIST_CLASS_NAME    "MLIST"

ITSDLLAPI extern MLIST_ClassRec       itsMLIST_ClassRec;
ITSDLLAPI extern ITS_Class            itsMLIST_Class;

/*.interface:MLIST
 *****************************************************************************
 *  Interface:
 *      MLIST_*
 *
 *  Purpose:
 *      This interface implements mutex protected lists, queues, and stacks
 *      for "C".
 *
 *  Usage:
 *      This interface is intended for use by those programmers implementing
 *      in "C".
 *
 *      -------------------------------------------------------------------
 *      ...
 *
 *      MLIST_Manager* rcvQueue;
 *
 *      rcvQueue = MQUEUE_Create();
 *      assert(rcvQueue != NULL);
 *
 *      ...
 *
 *      void *data;
 *      int len;
 *
 *      if (MQUEUE_RemHead(rcvQueue, &data, &len) != ITS_SUCCESS)
 *      {
 *          * handle general IntelliSS7 error *
 *      }
 *
 *      * Manipulate the list entry *
 *
 *      * failure to perform this step will completely deplete the buffer
 *      * pool associated with this MLIST_Manager
 *      ITS_Free(data);
 *      --------------------------------------------------------------------
 *
 *      All MLIST_Manager functions are threadsafe.
 *
 *****************************************************************************/

#if !defined(ITS_FASTCALL)

/*
 * prototypes.  These are included to give the correct signature.  The
 * fastcall mechanism invokes the class methods directly.
 */
ITSDLLAPI MLIST_Manager *MLIST_Create();
ITSDLLAPI void MLIST_Delete(MLIST_Manager *lm);

/*
 * locator signature are inherited from list.
 * Locators are *guaranteed* to be called while the list mutex is
 * locked, so make SURE they don't take a long time.
 */

/*
 * NOTE: The API will CREATE A COPY of the data
 */
ITSDLLAPI int MLIST_AddHead(MLIST_Manager *lm, void *data, int len);
ITSDLLAPI int MLIST_AddTail(MLIST_Manager *lm, void *data, int len);
ITSDLLAPI int MLIST_Insert(MLIST_Manager *lm, LIST_InsertFunc func,
                           void *data, int len);

/*
 * NOTE: The user MUST FREE the return data
 */
ITSDLLAPI int MLIST_RemHead(MLIST_Manager *lm, void **data, int *len);
ITSDLLAPI int MLIST_RemTail(MLIST_Manager *lm, void **data, int *len);
/* Note: the user can safely walk the next and prev pointers of the node
 * passed to him, BUT HE MUST NOT CHANGE THEM. */
ITSDLLAPI int MLIST_Remove(MLIST_Manager *lm, LIST_RemoveFunc func,
                           void *userData, int userDataLen,
                           void **data, int *len);

/*
 * empty predicate
 */
ITSDLLAPI ITS_BOOLEAN MLIST_EmptyP(MLIST_Manager *lm);

/*
 * count proc
 */
ITSDLLAPI ITS_UINT MLIST_GetCount(MLIST_Manager *lm);

/*
 * nobody should use these that hasn't read and UNDERSTOOD the code.
 */
ITSDLLAPI int MLIST_Lock(MLIST_Manager *lm);
ITSDLLAPI int MLIST_Unlock(MLIST_Manager *lm);

/*
 * RemoveNoLock is equivalent to LIST_Unlink.  The name has been
 * changed to cue the user that the list must be manually locked
 * before calling this.
 */
ITSDLLAPI int MLIST_RemoveNoLock(MLIST_Manager *lm, LIST_Entry *msg);

#else /****************** ITS_FASTCALL *******************/

#define MLIST_Create() \
    (MLIST_Manager *)ITS_ConstructObject(itsMLIST_Class, NULL)

#define MLIST_Delete(x) \
    ITS_DestructObject((ITS_Object)(x))

#define MLIST_AddHead(l, d, s) \
    LIST_CLASS_ADD_HEAD(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define MLIST_AddTail(l, d, s) \
    LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define MLIST_Insert(l, f, d, s) \
    LIST_CLASS_INSERT(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (f), (d), (s))

#define MLIST_RemHead(l, d, s) \
    LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define MLIST_RemTail(l, d, s) \
    LIST_CLASS_REM_TAIL(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define MLIST_Remove(l, f, ud, ul, d, s) \
    LIST_CLASS_REMOVE(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (f), \
                                        (ud), (ul), (d), (s))

#define MLIST_Lock(l) \
    MLIST_CLASS_LOCK(ITS_OBJ_CLASS(l))((l))

#define MLIST_Unlock(l) \
    MLIST_CLASS_UNLOCK(ITS_OBJ_CLASS(l))((l))

#define MLIST_RemoveNoLock(l, m) \
    LIST_CLASS_UNLINK(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (m))

#define MLIST_EmptyP(l) \
    LIST_CLASS_EMPTYP(ITS_OBJ_CLASS(l))((LIST_Manager *)(l))

#endif /* !defined(ITS_FASTCALL) */

/*
 * some useful shorthand for queues
 */
#define MQUEUE_MsgQueue           MLIST_Manager
#define MQUEUE_Msg                LIST_Entry

#define MQUEUE_Create             MLIST_Create
#define MQUEUE_Delete(m)          MLIST_Delete(m)
#define MQUEUE_Enqueue(m,d,l)     MLIST_AddTail(m, d, l)
#define MQUEUE_Dequeue(m,d,l)     MLIST_RemHead(m, d, l)
#define MQUEUE_Lock(m)            MLIST_Lock(m)
#define MQUEUE_Unlock(m)          MLIST_Unlock(m)
#define MQUEUE_RemoveNoLock(m,e)  MLIST_RemoveNoLock(m, e)
#define MQUEUE_EmptyP(m)          MLIST_EmptyP(m)

/*
 * and more useful shorthand for stacks
 */
#define MSTACK_MsgQueue           MLIST_Manager
#define MSTACK_Msg                LIST_Entry

#define MSTACK_Create             MLIST_Create
#define MSTACK_Delete(m)          MLIST_Delete(m)
#define MSTACK_Push(m,d,l)        MLIST_AddHead(m, d, l)
#define MSTACK_Pop(m,d,l)         MLIST_RemHead(m, d, l)
#define MSTACK_Lock(m)            MLIST_Lock(m)
#define MSTACK_Unlock(m)          MLIST_Unlock(m)
#define MSTACK_RemoveNoLock(m,e)  MLIST_RemoveNoLock(m, e)
#define MSTACK_EmptyP(m)          MLIST_EmptyP(m)

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_STL_PRESENT)

#include <deque>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:ITS_STL_MList
 *****************************************************************************
 *  Interface:
 *      ITS_MList
 *
 *  Purpose:
 *      The ITS_STL_MList template represents an implementation of reentrant
 *      lists for IntelliSS7.  The name essentially translates to "mutex
 *      protected list".
 *
 *  Usage:
 *      various
 *****************************************************************************/
template <class _NodeType_>
class MList
{
public:
    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method constructs an mutex protected list.
     *
     **************************************************************************/
    MList()
    {
        mutex = new ITS_Mutex(0);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method destroys an mutex protected list.
     *
     **************************************************************************/
    virtual
    ~MList()
    {
        delete mutex;
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method adds a node at the head of the list.
     *
     *  Input Parameters:
     *      node - the node to add
     *
     *  Return Value:
     *      ITS_SUCCESS - node added
     *
     **************************************************************************/
    int
    AddHead(_NodeType_& node)
    {
        if (mutex->Acquire() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        list.push_front(node);

        if (mutex->Release() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        return (ITS_SUCCESS);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method adds a node at the tail of the list.
     *
     *  Input Parameters:
     *      node - the node to add
     *
     *  Return Value:
     *      ITS_SUCCESS - node added
     *
     **************************************************************************/
    int
    AddTail(_NodeType_& node)
    {
        if (mutex->Acquire() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        list.push_back(node);

        if (mutex->Release() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        return (ITS_SUCCESS);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method removes a node from the head of the list.
     *
     *  Output Parameters:
     *      node - the node to remove
     *
     *  Return Value:
     *      ITS_SUCCESS - node removed
     *
     **************************************************************************/
    int
    RemHead(_NodeType_& node)
    {
        if (mutex->Acquire() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        if (list.empty())
        {
            mutex->Release();

            return (ITS_ENOMSG);
        }

        memcpy(&node, &list.front(), sizeof(_NodeType_));

        list.pop_front();

        if (mutex->Release() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        return (ITS_SUCCESS);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method removes a node from the head of the list.
     *
     *  Output Parameters:
     *      node - the node to remove
     *
     *  Return Value:
     *      ITS_SUCCESS - node removed
     *
     **************************************************************************/
    int
    RemTail(_NodeType_& node)
    {
        if (mutex->Acquire() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        if (list.empty())
        {
            mutex->Release();

            return (ITS_ENOMSG);
        }

        memcpy(&node, &list.back(), sizeof(_NodeType_));

        list.pop_back();

        if (mutex->Release() != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        return (ITS_SUCCESS);
    }

private:
    std::deque<_NodeType_>  list;
    Mutex                   *mutex;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* ITS_STL_PRESENT */

#endif /* USE_CPLUSPLUS */

#endif /* ITS_MLIST_H */
