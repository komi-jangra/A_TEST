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
 * LOG: Revision 8.2  2005/03/21 13:50:45  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
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
 * LOG: Revision 4.2  2001/05/02 19:06:01  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.14  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.13  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.12  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.11  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.10  2001/02/05 22:43:58  hxing
 * LOG: Order of namespace termination outside HAVE_STL
 * LOG:
 * LOG: Revision 3.9  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.8  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.7  2001/01/20 00:02:50  mmiers
 * LOG: Ditch the non STL lists.  STL deque is faster.
 * LOG:
 * LOG: Revision 3.6  2001/01/19 16:28:18  mmiers
 * LOG: Finish removing the list alloc and free funcs
 * LOG:
 * LOG: Revision 3.5  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.4  2000/11/29 18:24:42  mmiers
 * LOG: Write ok.  Think about SLS->stream.
 * LOG:
 * LOG: Revision 3.3  2000/08/23 00:02:09  mmiers
 * LOG:
 * LOG: Get the fastcall macros working.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:25:07  mmiers
 * LOG: Add user data to list remove procs.
 * LOG: Add memory pools for quick reclamation.
 * LOG: Add object creation into user supplied buffers.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:11  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 18:21:09  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 02:47:30  mmiers
 * LOG: Prepare for C inheritance/OO C.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.24  1999/10/27 14:55:40  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.23  1999/10/26 15:47:42  mmiers
 * LOG:
 * LOG:
 * LOG: Comment the pigs.
 * LOG:
 * LOG: Revision 1.22  1999/10/26 14:27:06  mmiers
 * LOG:
 * LOG:
 * LOG: The truth about STL.
 * LOG:
 * LOG: Revision 1.21  1998/11/19 00:36:16  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.20  1998/06/26 14:30:37  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.19  1998/06/01 16:35:13  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.18  1998/05/29 03:31:28  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.17  1998/05/26 20:15:29  mmiers
 * LOG: More work on the documentation.  The custom build step on NT generates
 * LOG: the HTML doc files.
 * LOG:
 * LOG: Revision 1.16  1998/05/26 16:29:27  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.15  1998/05/19 17:11:43  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.14  1998/04/24 16:20:20  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.13  1998/04/19 02:42:46  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.12  1998/04/16 16:59:52  mmiers
 * LOG: Final commit before baseline.
 * LOG:
 * LOG: Revision 1.11  1998/04/16 15:58:59  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.9  1998/04/09 14:33:18  mmiers
 * LOG: Visual complains about operator= not having a return value even when hidden
 * LOG: in the private section of the class record and given a stub implementation.
 * LOG:
 * LOG: Revision 1.8  1998/04/09 01:47:17  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.7  1998/04/06 15:26:04  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.6  1998/04/03 23:45:04  mmiers
 * LOG: More changes to support C++.
 * LOG:
 * LOG: Revision 1.5  1998/03/13 04:46:46  mmiers
 * LOG: For the most part, TCAP modifications.  Quite a few of these files are false
 * LOG: positive due to timestamps.
 * LOG:
 * LOG: Revision 1.4  1998/03/13 04:12:30  mmiers
 * LOG: Update files with latest data for TCAP implementation.  emlist represents
 * LOG: portable message queues.
 * LOG:
 * LOG: Revision 1.3  1998/03/12 03:50:54  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 00:25:58  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:10  mmiers
 * LOG: Add some new files for lists, mutex protected lists, and semaphore gated
 * LOG: mutex protected lists.
 *
 ****************************************************************************/

#ifndef ITS_EMLIST_H
#define ITS_EMLIST_H

#include <its.h>
#include <its_mutex.h>
#include <its_semaphore.h>
#include <its_mlist.h>

#ident "$Id: its_emlist.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    ITS_SEMAPHORE eventAvailable;
}
EMLIST_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    LIST_ObjectPart     list;
    MLIST_ObjectPart    mlist;
    EMLIST_ObjectPart   emlist;
}
EMLIST_Manager;

#define EMLIST_SEMAPHORE(x) \
    (((EMLIST_Manager *)(x))->emlist.eventAvailable)

/*
 * class method signatures.  Starting to resemble transports...
 */
typedef int (*EMLIST_GetEventProc)(EMLIST_Manager *lm,
                                   void **data, int *len);
typedef int (*EMLIST_GetEventTimeOutProc)(EMLIST_Manager *lm,
                                          void **data, int *len,
                                          ITS_UINT msecs);
typedef int (*EMLIST_PutEventProc)(EMLIST_Manager *lm,
                                   void *data, int len);

#define EMLIST_GET_EVENT_INHERIT            ((EMLIST_GetEventProc)NULL)
#define EMLIST_GET_EVENT_TIMEOUT_INHERIT    ((EMLIST_GetEventTimeOutProc)NULL)
#define EMLIST_PUT_EVENT_INHERIT            ((EMLIST_PutEventProc)NULL)

/*
 * the class record.
 */
typedef struct
{
    EMLIST_GetEventProc         getNextEvent;
    EMLIST_GetEventProc         peekNextEvent;
    EMLIST_GetEventTimeOutProc  getNextEventWithTimeOut;
    EMLIST_PutEventProc         putEvent;
}
EMLIST_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    LIST_ClassPart      listClass;
    MLIST_ClassPart     mlistClass;
    EMLIST_ClassPart    emlistClass;
}
EMLIST_ClassRec, *EMLIST_Class;

#define EMLIST_CLASS_GET_NEXT_EVENT(x) \
    (((EMLIST_Class)(x))->emlistClass.getNextEvent)

#define EMLIST_CLASS_GET_NEXT_EVENT_WITH_TIMEOUT(x) \
    (((EMLIST_Class)(x))->emlistClass.getNextEventWithTimeOut)

#define EMLIST_CLASS_PEEK_NEXT_EVENT(x) \
    (((EMLIST_Class)(x))->emlistClass.peekNextEvent)

#define EMLIST_CLASS_PUT_EVENT(x) \
    (((EMLIST_Class)(x))->emlistClass.putEvent)

#define EMLIST_CLASS_NAME   "EMLIST"

ITSDLLAPI extern EMLIST_ClassRec      itsEMLIST_ClassRec;
ITSDLLAPI extern ITS_Class            itsEMLIST_Class;

/*
 * locator signature are the same as those for list.  Note that the
 * list mutex is locked, so make SURE they don't take a long time.
 * NOTE: THE USER MUST NOT!!! MODIFY THE PREV AND NEXT ENTRIES!!!
 */
/*.interface:EMLIST
 *****************************************************************************
 *  Interface:
 *      EMLIST_*
 *
 *  Purpose:
 *      This interface implements mutex protected lists, queues, and stacks
 *      for "C".  EMLISTs have an additional "someone poked me" indicator
 *      (beyond the implementation of MLISTs, from which they semantically
 *      inherit behavior) which makes them suitable for use as event
 *      queues.
 *
 *  Usage:
 *      This interface is intended for use by those programmers implementing
 *      in "C".  To use the EMLIST_Manager in conjunction with the
 *      TRANSPORT mechanism, the following code is required:
 *
 *      -------------------------------------------------------------------
 *      static int
 *      putEvent(void *trans, ITS_EVENT *ev)
 *      {
 *          EMQUEUE_MsgQueue *mq = (EMQUEUE_MsgQueue *)trans;
 *
 *          return EMQUEUE_PutEvent(mq, ev, sizeof(ITS_EVENT));
 *      }
 *
 *      ...
 *
 *      EMLIST_Manager* rcvQueue;
 *
 *      rcvQueue = EMQUEUE_Create();
 *      assert(rcvQueue != NULL);
 *
 *      assert(TRANSPORT_RegisterTransport("foo", ITS_DEFAULT_USER_SRC,
 *             rcvQueue, putEvent) == ITS_SUCCESS);
 *
 *      ...
 *
 *      ITS_EVENT ev;
 *      void *data;
 *      int len;
 *
 *      for (;;)
 *      {
 *          if (EMQUEUE_GetNextEvent(rcvQueue, &data, &len) != ITS_SUCCESS)
 *          {
 *              * handle general IntelliSS7 error *
 *          }
 *
 *          * manipulate the data, usually like this *
 *          assert(len == sizeof(ITS_EVENT));
 *          memcpy(&ev, data, len);
 *
 *          * failure to perform this step will completely deplete the buffer
 *          * pool associated with this EMLIST_Manager
 *          ITS_Free(data);
 *      }
 *      --------------------------------------------------------------------
 *
 *      All EMLIST_Manager functions are threadsafe.
 *
 *****************************************************************************/

#if !defined(ITS_FASTCALL)

/*
 * prototypes
 */
ITSDLLAPI EMLIST_Manager *EMLIST_Create();
ITSDLLAPI void EMLIST_Delete(EMLIST_Manager *lm);

/*
 * NOTE: The API will CREATE A COPY of the data
 */
ITSDLLAPI int EMLIST_AddHead(EMLIST_Manager *lm, void *data, int len);
ITSDLLAPI int EMLIST_AddTail(EMLIST_Manager *lm, void *data, int len);
ITSDLLAPI int EMLIST_Insert(EMLIST_Manager *lm, LIST_InsertFunc func,
                            void *data, int len);

/*
 * NOTE: The user MUST FREE the return data
 */
ITSDLLAPI int EMLIST_RemHead(EMLIST_Manager *lm, void **data, int *len);
ITSDLLAPI int EMLIST_RemTail(EMLIST_Manager *lm, void **data, int *len);
/* Note: the user can safely walk the next and prev pointers of the node
 * passed to him, BUT HE MUST NOT CHANGE THEM. */
ITSDLLAPI int EMLIST_Remove(EMLIST_Manager *lm, LIST_RemoveFunc func,
                            void *userData, int userDataLen,
                            void **data, int *len);

/*
 * empty predicate
 */
ITSDLLAPI ITS_BOOLEAN EMLIST_EmptyP(EMLIST_Manager *lm);

/*
 * count proc
 */
ITSDLLAPI ITS_UINT    EMLIST_GetCount(EMLIST_Manager *lm);

/*
 * nobody should use these that hasn't read and UNDERSTOOD the code.
 */
ITSDLLAPI int EMLIST_Lock(EMLIST_Manager *lm);
ITSDLLAPI int EMLIST_Unlock(EMLIST_Manager *lm);
ITSDLLAPI int EMLIST_RemoveNoLock(EMLIST_Manager *lm, LIST_Entry *entry);

/*
 * wait primitive(s)
 */
ITSDLLAPI int EMLIST_GetNextEvent(EMLIST_Manager *lm, void **data, int *len);
ITSDLLAPI int EMLIST_PeekNextEvent(EMLIST_Manager *lm, void **data, int *len);
ITSDLLAPI int EMLIST_GetNextEventWithTimeOut(EMLIST_Manager *lm,
                                             void **data, int *len
                                             ITS_UINT msecs);
ITSDLLAPI int EMLIST_PutEvent(EMLIST_Manager *lm, void *data, int len);

#else /* ITS_FASTCALL */

#define EMLIST_Create() \
    (EMLIST_Manager *)ITS_ConstructObject(itsEMLIST_Class, NULL)

#define EMLIST_Delete(x) \
    ITS_DestructObject((ITS_Object)(x))

#define EMLIST_AddHead(l, d, s) \
    LIST_CLASS_ADD_HEAD(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define EMLIST_AddTail(l, d, s) \
    LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define EMLIST_Insert(l, f, d, s) \
    LIST_CLASS_INSERT(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (f), (d), (s))

#define EMLIST_RemHead(l, d, s) \
    LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define EMLIST_RemTail(l, d, s) \
    LIST_CLASS_REM_TAIL(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (d), (s))

#define EMLIST_Remove(l, f, ud, ul, d, s) \
    LIST_CLASS_REMOVE(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (f), \
                                        (ud), (ul), (d), (s))

#define EMLIST_Lock(l) \
    MLIST_CLASS_LOCK(ITS_OBJ_CLASS(l))((MLIST_Manager *)(l))

#define EMLIST_Unlock(l) \
    MLIST_CLASS_UNLOCK(ITS_OBJ_CLASS(l))((MLIST_Manager *)(l))

#define EMLIST_RemoveNoLock(l, m) \
    LIST_CLASS_UNLINK(ITS_OBJ_CLASS(l))((LIST_Manager *)(l), (m))

#define EMLIST_EmptyP(l) \
    LIST_CLASS_EMPTYP(ITS_OBJ_CLASS(l))((LIST_Manager *)(l))

#define EMLIST_GetNextEvent(l, d, s) \
    EMLIST_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(l))((l), (d), (s))

#define EMLIST_PeekNextEvent(l, d, s) \
    EMLIST_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(l))((l), (d), (s))

#define EMLIST_GetNextEventWithTimeOut(l, d, s, t) \
    EMLIST_CLASS_GET_NEXT_EVENT_WITH_TIMEOUT(ITS_OBJ_CLASS(l))((l), (d), (s), (t))

#define EMLIST_PutEvent(l, d, s) \
    EMLIST_CLASS_PUT_EVENT(ITS_OBJ_CLASS(l))((l), (d), (s))

#endif /* !defined(ITS_FASTCALL) */

/*
 * some useful shorthand for queues
 */
#define EMQUEUE_MsgQueue            EMLIST_Manager
#define EMQUEUE_Msg                 LIST_Entry

#define EMQUEUE_Create              EMLIST_Create
#define EMQUEUE_Delete(m)           EMLIST_Delete(m)
#define EMQUEUE_Enqueue(m,d,l)      EMLIST_AddTail(m, d, l)
#define EMQUEUE_Dequeue(m,d,l)      EMLIST_RemHead(m, d, l)
#define EMQUEUE_Lock(m)             EMLIST_Lock(m)
#define EMQUEUE_Unlock(m)           EMLIST_Unlock(m)
#define EMQUEUE_RemoveNoLock(m,e)   EMLIST_RemoveNoLock(m, e)
#define EMQUEUE_GetNextEvent(m,e,l) EMLIST_GetNextEvent(m, e, l)
#define EMQUEUE_PutEvent(m,d,l)     EMLIST_PutEvent(m, d, l)

/*
 * and more useful shorthand for stacks
 */
#define EMSTACK_MsgQueue            EMLIST_Manager
#define EMSTACK_Msg                 LIST_Entry

#define EMSTACK_Create              EMLIST_Create
#define EMSTACK_Delete(m)           EMLIST_Delete(m)
#define EMSTACK_Push(m,d,l)         EMLIST_AddHead(m, d, l)
#define EMSTACK_Pop(m,d,l)          EMLIST_RemHead(m, d, l)
#define EMSTACK_Lock(m)             EMLIST_Lock(m)
#define EMSTACK_Unlock(m)           EMLIST_Unlock(m)
#define EMSTACK_RemoveNoLock(m,e)   EMLIST_RemoveNoLock(m, e)
#define EMSTACK_GetNextEvent(m,e,l) EMLIST_GetNextEvent(m, e, l)
#define EMSTACK_PutEvent(m,d,l)     EMLIST_PutEvent(m, d, l)

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_STL_PRESENT)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:EMList
 *****************************************************************************
 *  Interface:
 *      EMList
 *
 *  Purpose:
 *      The EMList class represents an implementation of task queues for
 *      IntelliSS7.
 *
 *  Usage:
 *      various
 *****************************************************************************/
template <class _NodeType_>
class EMList
    : public MList<_NodeType_>
{
public:
    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method constructs an mutex protected, semaphore signalled
     *      list.
     *
     **************************************************************************/
    EMList()
    {
        semaphore = new ITS_Semaphore(0);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method destroys an mutex protected, semaphore signalled
     *      list.
     *
     **************************************************************************/
    virtual
    ~EMList()
    {
        delete semaphore;
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method blocks until an entry is pending on the list.
     *
     *  Output Parameters:
     *      node - the first available node from the list.
     *
     *  Return Value:
     *      ITS_SUCCESS - event fetched
     *
     **************************************************************************/
    int
    GetNextEvent(_NodeType_& node)
    {
        if (semaphore->Wait() != ITS_SUCCESS)
        {
            return (ITS_EBADSEMAPHORE);
        }

        return RemHead(node);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method checks if an entry is pending on the list.
     *
     *  Output Parameters:
     *      node - the first available node from the list.
     *
     *  Return Value:
     *      ITS_ENOMSG - no message is pending.
     *
     **************************************************************************/
    int
    PeekNextEvent(_NodeType_& node)
    {
        if (semaphore->TryWait() == ITS_SUCCESS)
        {
            return RemHead(node);
        }

        return (ITS_ENOMSG);
    }

    /*.implementation:public,inline,ITS_MList
     **************************************************************************
     *  Purpose:
     *      This method puts an entry on the list.
     *
     *  Input Parameters:
     *      node - the node to put on the list.
     *
     *  Return Value:
     *      ITS_SUCCESS - node added
     *
     **************************************************************************/
    int
    PutEvent(_NodeType_& node)
    {
        if (AddTail(node) != ITS_SUCCESS)
        {
            return (ITS_ENOLIST);
        }

        return semaphore->Post();
    }

private:
    Semaphore   *semaphore;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* ITS_STL_PRESENT */

#endif /* USE_CPLUSPLUS */

#endif /* ITS_EMLIST_H */
