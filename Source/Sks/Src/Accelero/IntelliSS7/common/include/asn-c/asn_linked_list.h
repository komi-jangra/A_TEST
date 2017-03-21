/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: asn_linked_list.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  Linked-list of objects interface (with small overhead).
 */


#if !defined(_C_ASN_LINKED_LIST_H_)
#define _C_ASN_LINKED_LIST_H_

#include <its.h>
#include <its_object.h>

#include <asn_assertion.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

typedef struct _ASN_LinkedList_ObjectRec*    ASN_LinkedList;
typedef struct _ASN_LinkedList_ClassRec*     ASN_LinkedListClass;

/*
 *  Procedure signatures.
 */

typedef ITS_Object          (*ASN_LinkedList_GetBackProc)(const ASN_LinkedList object);
typedef ITS_Object          (*ASN_LinkedList_GetFrontProc)(const ASN_LinkedList object);
typedef size_t              (*ASN_LinkedList_GetSizeProc)(const ASN_LinkedList object);
typedef void                (*ASN_LinkedList_PopBackProc)(ASN_LinkedList object);
typedef void                (*ASN_LinkedList_PopFrontProc)(ASN_LinkedList object);
typedef int                 (*ASN_LinkedList_PushBackProc)(ASN_LinkedList object, ITS_Object element);
typedef int                 (*ASN_LinkedList_PushFrontProc)(ASN_LinkedList object, ITS_Object element);
typedef void                (*ASN_LinkedList_CursorSetBeginProc)(ASN_LinkedList object);
typedef void                (*ASN_LinkedList_CursorSetEndProc)(ASN_LinkedList object);
typedef void                (*ASN_LinkedList_CursorForthProc)(ASN_LinkedList object);
typedef void                (*ASN_LinkedList_CursorBackProc)(ASN_LinkedList object);
typedef ITS_BOOLEAN         (*ASN_LinkedList_CursorIsBeginProc)(const ASN_LinkedList object);
typedef ITS_BOOLEAN         (*ASN_LinkedList_CursorIsEndProc)(const ASN_LinkedList object);
typedef ITS_Object          (*ASN_LinkedList_CursorGetElementProc)(const ASN_LinkedList object);
typedef void                (*ASN_LinkedList_CursorRemoveElementProc)(ASN_LinkedList object);


/* ASN_LinkedList class. */

typedef struct _ASN_LinkedList_ClassPart
{
    ASN_LinkedList_GetBackProc              getBack;
    ASN_LinkedList_GetFrontProc             getFront;
    ASN_LinkedList_GetSizeProc              getSize;
    ASN_LinkedList_PopBackProc              popBack;
    ASN_LinkedList_PopFrontProc             popFront;
    ASN_LinkedList_PushBackProc             pushBack;
    ASN_LinkedList_PushFrontProc            pushFront;
    ASN_LinkedList_CursorSetBeginProc       cursorSetBegin;
    ASN_LinkedList_CursorSetEndProc         cursorSetEnd;
    ASN_LinkedList_CursorForthProc          cursorForth;
    ASN_LinkedList_CursorBackProc           cursorBack;
    ASN_LinkedList_CursorIsBeginProc        cursorIsBegin;
    ASN_LinkedList_CursorIsEndProc          cursorIsEnd;
    ASN_LinkedList_CursorGetElementProc     cursorGetElement;
    ASN_LinkedList_CursorRemoveElementProc  cursorRemoveElement;
} ASN_LinkedList_ClassPart;


typedef struct _ASN_LinkedList_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_LinkedList_ClassPart    asnLinkedListClass;
} ASN_LinkedList_ClassRec;

#define ASN_LINKED_LIST_CLASS_GET_BACK(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.getBack)

#define ASN_LINKED_LIST_CLASS_GET_FRONT(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.getFront)

#define ASN_LINKED_LIST_CLASS_GET_SIZE(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.getSize)

#define ASN_LINKED_LIST_CLASS_POP_BACK(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.popBack)

#define ASN_LINKED_LIST_CLASS_POP_FRONT(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.popFront)

#define ASN_LINKED_LIST_CLASS_PUSH_BACK(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.pushBack)

#define ASN_LINKED_LIST_CLASS_PUSH_FRONT(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.pushFront)

#define ASN_LINKED_LIST_CLASS_CURSOR_SET_BEGIN(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorSetBegin)

#define ASN_LINKED_LIST_CLASS_CURSOR_SET_END(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorSetEnd)

#define ASN_LINKED_LIST_CLASS_CURSOR_FORTH(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorForth)

#define ASN_LINKED_LIST_CLASS_CURSOR_BACK(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorBack)

#define ASN_LINKED_LIST_CLASS_CURSOR_IS_BEGIN(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorIsBegin)

#define ASN_LINKED_LIST_CLASS_CURSOR_IS_END(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorIsEnd)

#define ASN_LINKED_LIST_CLASS_CURSOR_GET_ELEMENT(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorGetElement)

#define ASN_LINKED_LIST_CLASS_CURSOR_REMOVE_ELEMENT(x) \
    (((ASN_LinkedListClass)(x))->asnLinkedListClass.cursorRemoveElement)


/* ASN_LinkedList cell. */

typedef struct _ASN_LinkedListCell
{
    struct _ASN_LinkedListCell* prev;
    struct _ASN_LinkedListCell* next;
    ITS_Object                  element;
} ASN_LinkedListCell;


/* ASN_LinkedList object. */

typedef struct _ASN_LinkedList_ObjectPart
{
    ASN_LinkedListCell*     cursor;
    ASN_LinkedListCell*     begin;
    ASN_LinkedListCell*     end;
    size_t                  size;
} ASN_LinkedList_ObjectPart;


typedef struct _ASN_LinkedList_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_LinkedList_ObjectPart   asnLinkedList;
} ASN_LinkedList_ObjectRec;


#define ASN_LINKED_LIST_CURSOR(x)       \
    (((ASN_LinkedList)(x))->asnLinkedList.cursor)

#define ASN_LINKED_LIST_BEGIN(x)       \
    (((ASN_LinkedList)(x))->asnLinkedList.begin)

#define ASN_LINKED_LIST_END(x)       \
    (((ASN_LinkedList)(x))->asnLinkedList.end)

#define ASN_LINKED_LIST_SIZE(x)       \
    (((ASN_LinkedList)(x))->asnLinkedList.size)


#define ASN_LINKED_LIST_CLASS_NAME "ASN_LinkedList"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Public interface.                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_LinkedList ASN_LinkedList_ConstructDefault();
void ASN_LinkedList_Destruct(ASN_LinkedList object);
ITS_Object ASN_LinkedList_GetBack(const ASN_LinkedList object);
ITS_Object ASN_LinkedList_GetFront(const ASN_LinkedList object);
size_t ASN_LinkedList_GetSize(const ASN_LinkedList object);
void ASN_LinkedList_PopBack(ASN_LinkedList object);
void ASN_LinkedList_PopFront(ASN_LinkedList object);
int ASN_LinkedList_PushBack(ASN_LinkedList object, ITS_Object element);
int ASN_LinkedList_PushFront(ASN_LinkedList object, ITS_Object element);
void ASN_LinkedList_CursorSetBegin(ASN_LinkedList object);
void ASN_LinkedList_CursorSetEnd(ASN_LinkedList object);
void ASN_LinkedList_CursorForth(ASN_LinkedList object);
void ASN_LinkedList_CursorBack(ASN_LinkedList object);
ITS_BOOLEAN ASN_LinkedList_CursorIsBegin(const ASN_LinkedList object);
ITS_BOOLEAN ASN_LinkedList_CursorIsEnd(const ASN_LinkedList object);
ITS_Object ASN_LinkedList_CursorGetElement(const ASN_LinkedList object);
void ASN_LinkedList_CursorRemoveElement(ASN_LinkedList object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_LINKED_LIST_H_) */
