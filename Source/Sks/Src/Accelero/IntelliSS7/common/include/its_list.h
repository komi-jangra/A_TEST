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
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
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
 * LOG: Revision 3.14  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.13  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.12  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.11  2001/02/05 22:43:58  hxing
 * LOG: Order of namespace termination outside HAVE_STL
 * LOG:
 * LOG: Revision 3.10  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.9  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.8  2001/01/20 00:02:50  mmiers
 * LOG: Ditch the non STL lists.  STL deque is faster.
 * LOG:
 * LOG: Revision 3.7  2001/01/19 19:33:08  mmiers
 * LOG: Mysteries
 * LOG:
 * LOG: Revision 3.6  2001/01/19 16:28:18  mmiers
 * LOG: Finish removing the list alloc and free funcs
 * LOG:
 * LOG: Revision 3.5  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.4  2000/10/02 22:15:49  mmiers
 * LOG: More work.
 * LOG:
 * LOG: Revision 3.3  2000/08/18 23:36:06  mmiers
 * LOG: Start using the mempool.
 * LOG:
 * LOG: Revision 3.2  2000/08/17 23:25:07  mmiers
 * LOG: Add user data to list remove procs.
 * LOG: Add memory pools for quick reclamation.
 * LOG: Add object creation into user supplied buffers.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/04/24 16:50:07  mmiers
 * LOG:
 * LOG:
 * LOG: Fix for growth-without-end thread pool list.
 * LOG:
 * LOG: Revision 2.3  2000/01/26 03:04:09  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.2  1999/12/15 18:22:12  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.1  1999/12/15 02:44:20  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.24  1999/08/23 01:45:21  mmiers
 * LOG:
 * LOG:
 * LOG: Add inline comments.
 * LOG:
 * LOG: Revision 1.23  1999/08/22 20:42:26  labuser
 * LOG:
 * LOG:
 * LOG: Some thread pool implementation helpers.
 * LOG:
 * LOG: Revision 1.22  1998/11/19 00:36:19  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.21  1998/10/07 15:55:29  whu
 * LOG: Found a major one here.  The ITS_ListEntry class was not initializing
 * LOG: the prev/next pointers, which means that Unlink() failed for the
 * LOG: thread pool class.  This implies that the free list would quickly
 * LOG: reach empty.
 * LOG:
 * LOG: Revision 1.20  1998/06/01 16:35:16  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.19  1998/05/29 03:31:30  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.18  1998/05/26 20:15:29  mmiers
 * LOG: More work on the documentation.  The custom build step on NT generates
 * LOG: the HTML doc files.
 * LOG:
 * LOG: Revision 1.17  1998/05/19 17:11:46  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.16  1998/04/27 20:00:25  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.15  1998/04/24 16:20:20  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.14  1998/04/23 17:04:05  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.13  1998/04/19 02:42:47  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.12  1998/04/17 17:43:20  mmiers
 * LOG: Working thread pool.  Still have to do something about termination.
 * LOG:
 * LOG: Revision 1.11  1998/04/17 15:31:53  mmiers
 * LOG: A better implementation of the thread pool.
 * LOG:
 * LOG: Revision 1.10  1998/04/17 03:36:26  mmiers
 * LOG: Start with a FIRST CUT at an implementation for thread pools.
 * LOG:
 * LOG: Revision 1.9  1998/04/09 14:33:19  mmiers
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
 * LOG: Revision 1.6  1998/04/03 23:45:05  mmiers
 * LOG: More changes to support C++.
 * LOG:
 * LOG: Revision 1.5  1998/04/03 22:17:53  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.4  1998/03/13 04:12:31  mmiers
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
 * LOG:
 * LOG: Revision 1.4  1998/02/03 02:11:25  ite
 * LOG: Debug of NMS baseline.
 * LOG:
 * LOG: Revision 1.3  1998/01/28 02:01:50  rsonak
 * LOG: Forgot to complete ANSI build (Mitch).  Cleanup to reflect this.
 * LOG:
 * LOG: Revision 1.2  1998/01/27 23:34:05  mmiers
 * LOG: Finish up the port.
 * LOG:
 * LOG: Revision 1.1  1998/01/27 15:41:42  mmiers
 * LOG: NMS baseline for ITS
 * LOG:
 * LOG: Revision 1.2  1998/01/26 04:42:28  mmiers
 * LOG: Basic cleanup for NMS usage.  Need to add queue handling for correctness.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_LIST_H
#define ITS_LIST_H

#include <its_types.h>
#include <its_object.h>

#ident "$Id: its_list.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _list_entry
{
    struct _list_entry  *prev;
    struct _list_entry  *next;
    void                *data;
    int                 length;
}
LIST_Entry;

typedef struct
{
    LIST_Entry *head;
    LIST_Entry *tail;
    ITS_UINT   count;
}
LIST_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    LIST_ObjectPart     list;
}
LIST_Manager;

#define LIST_HEAD(x) \
    (((LIST_Manager *)(x))->list.head)
#define LIST_TAIL(x) \
    (((LIST_Manager *)(x))->list.tail)
#define LIST_COUNT(x) \
    (((LIST_Manager *)(x))->list.count)

/*
 * locator signature.  "prev" will be NULL for the first node in the
 * list, "next" will be NULL after the last node.  The function has a
 * boolean result.
 * NOTE: THE USER MUST NOT!!! MODIFY THE PREV AND NEXT ENTRIES!!!
 */
typedef int         (*LIST_InsertFunc)(LIST_Entry *prev, LIST_Entry *next,
                                       LIST_Entry *item);
typedef int         (*LIST_RemoveFunc)(LIST_Entry *item,
                                       void *match, int mlen);

/*
 * These signatures define the class implementation.
 */
typedef int         (*LIST_AddProc)(LIST_Manager *, void *, int);
typedef int         (*LIST_InsertProc)(LIST_Manager *, LIST_InsertFunc,
                                       void *, int);
typedef int         (*LIST_RemProc)(LIST_Manager *, void **, int *);
typedef int         (*LIST_RemoveProc)(LIST_Manager *, LIST_RemoveFunc,
                                       void *, int, void **, int *);
typedef int         (*LIST_UnlinkProc)(LIST_Manager *, LIST_Entry *);
typedef ITS_BOOLEAN (*LIST_EmptyPProc)(LIST_Manager *);
typedef ITS_UINT    (*LIST_CountProc)(LIST_Manager *);

#define LIST_ADD_INHERIT        ((LIST_AddProc)NULL)
#define LIST_INSERT_INHERIT     ((LIST_InsertProc)NULL)
#define LIST_REM_INHERIT        ((LIST_RemProc)NULL)
#define LIST_REMOVE_INHERIT     ((LIST_RemoveProc)NULL)
#define LIST_UNLINK_INHERIT     ((LIST_UnlinkProc)NULL)
#define LIST_EMPTYP_INHERIT     ((LIST_EmptyPProc)NULL)
#define LIST_COUNT_INHERIT      ((LIST_CountProc)NULL)

/*
 * the class record
 */
typedef struct
{
    LIST_AddProc          addHead;
    LIST_AddProc          addTail;
    LIST_InsertProc       insert;
    LIST_RemProc          remHead;
    LIST_RemProc          remTail;
    LIST_RemoveProc       remove;
    LIST_UnlinkProc       unlink;
    LIST_EmptyPProc       emptyP;
    LIST_CountProc        getCount;
}
LIST_ClassPart;

typedef struct
{
    ITS_CoreClassPart     coreClass;
    LIST_ClassPart        listClass;
}
LIST_ClassRec, *LIST_Class;

#define LIST_CLASS_ALLOCATOR(x) \
    (((LIST_Class)(x))->listClass.allocator)

#define LIST_CLASS_DEALLOCATOR(x) \
    (((LIST_Class)(x))->listClass.deallocator)

#define LIST_CLASS_ADD_HEAD(x) \
    (((LIST_Class)(x))->listClass.addHead)

#define LIST_CLASS_ADD_TAIL(x) \
    (((LIST_Class)(x))->listClass.addTail)

#define LIST_CLASS_INSERT(x) \
    (((LIST_Class)(x))->listClass.insert)

#define LIST_CLASS_REM_HEAD(x) \
    (((LIST_Class)(x))->listClass.remHead)

#define LIST_CLASS_REM_TAIL(x) \
    (((LIST_Class)(x))->listClass.remTail)

#define LIST_CLASS_REMOVE(x) \
    (((LIST_Class)(x))->listClass.remove)

#define LIST_CLASS_UNLINK(x) \
    (((LIST_Class)(x))->listClass.unlink)

#define LIST_CLASS_EMPTYP(x) \
    (((LIST_Class)(x))->listClass.emptyP)

#define LIST_CLASS_GET_COUNT(x) \
    (((LIST_Class)(x))->listClass.getCount)

#define LIST_CLASS_NAME "LIST"

ITSDLLAPI extern LIST_ClassRec    itsLIST_ClassRec;
ITSDLLAPI extern ITS_Class        itsLIST_Class;

/*.interface:LIST
 *****************************************************************************
 *  Interface:
 *      LIST_*
 *
 *  Purpose:
 *      This interface implements lists, queues, and stacks for "C".
 *
 *  Usage:
 *      This interface is intended for use by those programmers implementing
 *      in "C".
 *
 *      -------------------------------------------------------------------
 *      ...
 *
 *      LIST_Manager* l;
 *
 *      l = LIST_Create();
 *      assert(l != NULL);
 *
 *      ...
 *
 *      void *data;
 *      int len;
 *
 *      if (LIST_RemHead(l, &data, &len) != ITS_SUCCESS)
 *      {
 *          * handle general IntelliSS7 error *
 *      }
 *
 *      * failure to perform this step will completely deplete the buffer
 *      * pool associated with this EMLIST_Manager
 *      ITS_Free(data);
 *      --------------------------------------------------------------------
 *
 *      All LIST_Manager functions are reentrant, but not threadsafe.
 *
 *****************************************************************************/

#if !defined(ITS_FASTCALL)

/*
 * prototypes.  These signatures are provided to give the
 * correct prototypes.  The fastcall mechanism directly invokes
 * the class methods.
 */
ITSDLLAPI LIST_Manager *LIST_Create();
ITSDLLAPI void LIST_Delete(LIST_Manager *lm);

/*
 * NOTE: The API will CREATE A COPY of the data
 */
ITSDLLAPI int LIST_AddHead(LIST_Manager *lm, void *data, int len);
ITSDLLAPI int LIST_AddTail(LIST_Manager *lm, void *data, int len);
ITSDLLAPI int LIST_Insert(LIST_Manager *lm, LIST_InsertFunc func,
                          void *data, int len);

/*
 * NOTE: The user MUST FREE the return data
 */
ITSDLLAPI int LIST_RemHead(LIST_Manager *lm, void **data, int *len);
ITSDLLAPI int LIST_RemTail(LIST_Manager *lm, void **data, int *len);
/* Note: the user can safely walk the next and prev pointers of the node
 * passed to him, BUT HE MUST NOT CHANGE THEM. */
ITSDLLAPI int LIST_Remove(LIST_Manager *lm, LIST_RemoveFunc func,
                          void *userData, int userDataLen,
                          void **data, int *len);
ITSDLLAPI int LIST_Unlink(LIST_Manager *lm, LIST_Entry *item);

/*
 * empty predicate
 */
ITSDLLAPI ITS_BOOLEAN LIST_EmptyP(LIST_Manager *lm);

/*
 * stats
 */
ITSDLLAPI ITS_UINT LIST_GetCount(LIST_Manager *lm);

#else /****************** ITS_FASTCALL ******************/

#define LIST_Create() \
    (LIST_Manager *)ITS_ConstructObject(itsLIST_Class, NULL)

#define LIST_Delete(x) \
    ITS_DestructObject((ITS_Object)(x))

#define LIST_AddHead(l, d, s) \
    LIST_CLASS_ADD_HEAD(ITS_OBJ_CLASS(l))((l), (d), (s))

#define LIST_AddTail(l, d, s) \
    LIST_CLASS_ADD_TAIL(ITS_OBJ_CLASS(l))((l), (d), (s))

#define LIST_Insert(l, f, d, s) \
    LIST_CLASS_INSERT(ITS_OBJ_CLASS(l))((l), (f), (d), (s))

#define LIST_RemHead(l, d, s) \
    LIST_CLASS_REM_HEAD(ITS_OBJ_CLASS(l))((l), (d), (s))

#define LIST_RemTail(l, d, s) \
    LIST_CLASS_REM_TAIL(ITS_OBJ_CLASS(l))((l), (d), (s))

#define LIST_Remove(l, f, ud, ul, d, s) \
    LIST_CLASS_REMOVE(ITS_OBJ_CLASS(l))((l), (f), (ud), (ul), (d), (s))

#define LIST_Unlink(l, m) \
    LIST_CLASS_UNLINK(ITS_OBJ_CLASS(l))((l), (m))

#define LIST_EmptyP(l) \
    LIST_CLASS_EMPTYP(ITS_OBJ_CLASS(l))((l))

#endif /* !defined(ITS_FASTCALL) */

/*
 * some useful shorthand for queues
 */
#define QUEUE_MsgQueue           LIST_Manager
#define QUEUE_Msg                LIST_Entry

#define QUEUE_Create             LIST_Create
#define QUEUE_Delete(m)          LIST_Delete(m)
#define QUEUE_Enqueue(m,d,l)     LIST_AddTail(m, d, l)
#define QUEUE_Dequeue(m,d,l)     LIST_RemHead(m, d, l)
#define QUEUE_Unlink(m,l)        LIST_Unlink(m, l)

/*
 * and more useful shorthand for stacks
 */
#define STACK_MsgQueue           LIST_Manager
#define STACK_Msg                LIST_Entry

#define STACK_Create             LIST_Create
#define STACK_Delete(m)          LIST_Delete(m)
#define STACK_Push(m,d,l)        LIST_AddHead(m, d, l)
#define STACK_Pop(m,d,l)         LIST_RemHead(m, d, l)
#define STACK_Unlink(m,l)        LIST_Unlink(m, l)

#ifdef __cplusplus
}
#endif

#endif /* ITS_LIST_H */
