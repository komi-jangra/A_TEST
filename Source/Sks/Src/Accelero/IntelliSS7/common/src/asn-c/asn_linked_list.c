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
 *  ID: $Id: asn_linked_list.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  Linked-list of objects interface (with small overhead).
 */

#include <asn_linked_list.h>

static int
Construct(ITS_Object object, va_list args)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_LINKED_LIST_END(object) = (ASN_LinkedListCell*)calloc(1, sizeof(ASN_LinkedListCell));

    ASN_C_ENSURE(ASN_LINKED_LIST_END(object) != NULL);

    if (ASN_LINKED_LIST_END(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    ASN_LINKED_LIST_END(object)->prev       = NULL;
    ASN_LINKED_LIST_END(object)->next       = NULL;
    ASN_LINKED_LIST_END(object)->element    = NULL;

    ASN_LINKED_LIST_BEGIN(object)       = ASN_LINKED_LIST_END(object);
    ASN_LINKED_LIST_CURSOR(object)      = ASN_LINKED_LIST_END(object);

    ASN_LINKED_LIST_SIZE(object)        = 0;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_LinkedListCell* currCell = NULL;
    ASN_LinkedListCell* prevCell = NULL;

    ASN_C_REQUIRE(object != NULL);

    if (ASN_LINKED_LIST_BEGIN(object) != ASN_LINKED_LIST_END(object))
    {
        ASN_C_ASSERT(ASN_LINKED_LIST_SIZE(object) != 0);
        ASN_C_ASSERT(ASN_LINKED_LIST_BEGIN(object) != NULL);

        prevCell = currCell = ASN_LINKED_LIST_BEGIN(object);

        while (currCell != ASN_LINKED_LIST_END(object))
        {
            currCell = prevCell->next;

            ASN_C_ASSERT(currCell != NULL);

            free(prevCell);

            prevCell = currCell;
        }
    }
    else
    {
        ASN_C_ASSERT(ASN_LINKED_LIST_SIZE(object) == 0);
    }

    ASN_C_ASSERT(ASN_LINKED_LIST_END(object) != NULL);

    free(ASN_LINKED_LIST_END(object));

    ASN_LINKED_LIST_END(object)     = NULL;
    ASN_LINKED_LIST_BEGIN(object)   = NULL;
    ASN_LINKED_LIST_CURSOR(object)  = NULL;
}

static ITS_Object
Clone(ITS_Object object)
{
    /* Not implemented. */

    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ASN_C_ASSERT(not_implemented);

    return NULL;
}

static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    /* Not implemented. */

    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ASN_C_ASSERT(not_implemented);

    return ITS_FALSE;
}

/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN CursorIsBegin(const ASN_LinkedList object);
static ITS_BOOLEAN CursorIsEnd(const ASN_LinkedList object);
static size_t GetSize(const ASN_LinkedList object);

static ITS_Object 
GetBack(const ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(GetSize(object) > 0);

    if (ASN_LINKED_LIST_BEGIN(object) != ASN_LINKED_LIST_END(object))
    {
        ASN_LinkedListCell* currCell = ASN_LINKED_LIST_END(object)->prev;

        ASN_C_ASSERT(currCell != NULL);
        ASN_C_ASSERT(currCell->element != NULL);

        return currCell->element;
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ASN_C_ASSERT(must_not_be_reached);

        return NULL;
    }
}

static ITS_Object 
GetFront(const ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(GetSize(object) > 0);

    if (ASN_LINKED_LIST_BEGIN(object) != ASN_LINKED_LIST_END(object))
    {
        ASN_LinkedListCell* currCell = ASN_LINKED_LIST_BEGIN(object);

        ASN_C_ASSERT(currCell != NULL);
        ASN_C_ASSERT(currCell->element != NULL);

        return currCell->element;
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ASN_C_ASSERT(must_not_be_reached);

        return NULL;
    }
}

static size_t 
GetSize(const ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LINKED_LIST_SIZE(object);
}

static void 
PopBack(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(GetSize(object) > 0);

    if (ASN_LINKED_LIST_END(object) != ASN_LINKED_LIST_BEGIN(object))
    {
        ASN_LinkedListCell* currCell = ASN_LINKED_LIST_END(object);
        ASN_LinkedListCell* prevCell = ASN_LINKED_LIST_END(object)->prev;

        if (prevCell == ASN_LINKED_LIST_BEGIN(object))
        {
            currCell->prev = NULL;

            ASN_LINKED_LIST_BEGIN(object) = ASN_LINKED_LIST_END(object);

            free(prevCell);

            ASN_LINKED_LIST_SIZE(object)--;

            ASN_C_ASSERT(ASN_LINKED_LIST_SIZE(object) == 0);
        }
        else
        {
            ASN_LinkedListCell* prevPrevCell = prevCell->prev;

            ASN_C_ASSERT(prevPrevCell != NULL);

            currCell->prev = prevPrevCell;
            prevPrevCell->next = currCell;

            free(prevCell);

            ASN_LINKED_LIST_SIZE(object)--;

            ASN_C_ASSERT(ASN_LINKED_LIST_SIZE(object) > 0);
        }
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ASN_C_ASSERT(must_not_be_reached);
    }
}

static void 
PopFront(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(GetSize(object) > 0);

    if (ASN_LINKED_LIST_BEGIN(object) != ASN_LINKED_LIST_END(object))
    {
        ASN_LinkedListCell* currCell = ASN_LINKED_LIST_BEGIN(object);
        ASN_LinkedListCell* nextCell = ASN_LINKED_LIST_BEGIN(object)->next;

        if (nextCell == ASN_LINKED_LIST_END(object))
        {
            nextCell->prev = NULL;

            ASN_LINKED_LIST_BEGIN(object) = ASN_LINKED_LIST_END(object);

            free(currCell);

            ASN_LINKED_LIST_SIZE(object)--;

            ASN_C_ASSERT(ASN_LINKED_LIST_SIZE(object) == 0);
        }
        else
        {
            nextCell->prev = NULL;

            free(currCell);

            ASN_LINKED_LIST_BEGIN(object) = nextCell;

            ASN_LINKED_LIST_SIZE(object)--;

            ASN_C_ASSERT(ASN_LINKED_LIST_SIZE(object) > 0);
        }
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ASN_C_ASSERT(must_not_be_reached);
    }
}

static int 
PushBack(ASN_LinkedList object, ITS_Object element)
{
    ASN_LinkedListCell* currCell = NULL;
    ASN_LinkedListCell* nextCell = NULL;
    ASN_LinkedListCell* prevCell = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(element != NULL);

    currCell = (ASN_LinkedListCell*)calloc(1, sizeof(ASN_LinkedListCell));

    ASN_C_ENSURE(currCell != NULL);

    if (currCell == NULL)
    {
        return ITS_ENOMEM;
    }

    nextCell = ASN_LINKED_LIST_END(object);

    if (ASN_LINKED_LIST_END(object) != ASN_LINKED_LIST_BEGIN(object))
    {
        prevCell = nextCell->prev;

        prevCell->next = currCell;
        nextCell->prev = currCell;

        currCell->next = nextCell;
        currCell->prev = prevCell;
        currCell->element = element;

        ASN_LINKED_LIST_SIZE(object)++;
    }
    else
    {
        ASN_LINKED_LIST_BEGIN(object) = currCell;

        nextCell->prev = currCell;

        currCell->prev = NULL;
        currCell->next = nextCell;
        currCell->element = element;

        ASN_LINKED_LIST_SIZE(object)++;
    }
    
    return ITS_SUCCESS;
}

static int 
PushFront(ASN_LinkedList object, ITS_Object element)
{
    ASN_LinkedListCell* currCell = NULL;
    ASN_LinkedListCell* nextCell = NULL;
    ASN_LinkedListCell* prevCell = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(element != NULL);

    currCell = (ASN_LinkedListCell*)calloc(1, sizeof(ASN_LinkedListCell));

    ASN_C_ENSURE(currCell != NULL);

    if (currCell == NULL)
    {
        return ITS_ENOMEM;
    }

    if (ASN_LINKED_LIST_END(object) != ASN_LINKED_LIST_BEGIN(object))
    {
        nextCell = ASN_LINKED_LIST_BEGIN(object);

        nextCell->prev = currCell;

        currCell->prev = NULL;
        currCell->next = nextCell;
        currCell->element = element;

        ASN_LINKED_LIST_BEGIN(object) = currCell;

        ASN_LINKED_LIST_SIZE(object)++;
    }
    else
    {
        nextCell = ASN_LINKED_LIST_END(object);

        nextCell->prev = currCell;

        currCell->prev = NULL;
        currCell->next = nextCell;
        currCell->element = element;

        ASN_LINKED_LIST_BEGIN(object) = currCell;

        ASN_LINKED_LIST_SIZE(object)++;
    }

    return ITS_SUCCESS;
}

static void 
CursorSetBegin(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_LINKED_LIST_CURSOR(object) = ASN_LINKED_LIST_BEGIN(object);
}

static void 
CursorSetEnd(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_LINKED_LIST_CURSOR(object) = ASN_LINKED_LIST_END(object);
}

static void 
CursorForth(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(!CursorIsEnd(object));

    ASN_LINKED_LIST_CURSOR(object) = ASN_LINKED_LIST_CURSOR(object)->next;
}

static void 
CursorBack(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(!CursorIsBegin(object));

    ASN_LINKED_LIST_CURSOR(object) = ASN_LINKED_LIST_CURSOR(object)->prev;

}

static ITS_BOOLEAN 
CursorIsBegin(const ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LINKED_LIST_CURSOR(object) == ASN_LINKED_LIST_BEGIN(object);
}

static ITS_BOOLEAN 
CursorIsEnd(const ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LINKED_LIST_CURSOR(object) == ASN_LINKED_LIST_END(object);

}

static ITS_Object 
CursorGetElement(const ASN_LinkedList object)
{
    ITS_Object result = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = ASN_LINKED_LIST_CURSOR(object)->element;

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void
CursorRemoveElement(ASN_LinkedList object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(!CursorIsEnd(object));

    if (CursorIsBegin(object))
    {
        PopFront(object);
    }
    else
    {
        ASN_LinkedListCell* currCell = ASN_LINKED_LIST_CURSOR(object);
        ASN_LinkedListCell* prevCell = ASN_LINKED_LIST_CURSOR(object)->prev;
        ASN_LinkedListCell* nextCell = ASN_LINKED_LIST_CURSOR(object)->next;

        ASN_C_ASSERT(!CursorIsBegin(object));
        ASN_C_ASSERT(!CursorIsEnd(object));

        prevCell->next = nextCell;
        nextCell->prev = prevCell;

        ASN_LINKED_LIST_CURSOR(object) = prevCell;

        free(currCell);

        ASN_LINKED_LIST_SIZE(object)--;
    }
}




/*
 *  ASN_LinkedList class record.
 */ 

ASN_LinkedList_ClassRec itsASN_LinkedList_ClassRec =
{
    /* Core part. */

    {
        &itsCORE_ClassRec,                  /* Core is superclass.      */
        sizeof(ASN_LinkedList_ObjectRec),   /* Size of instance.        */
        ITS_FALSE,                          /* Not initted.             */
        0,                                  /* Initial reference count. */
        ASN_LINKED_LIST_CLASS_NAME,         /* Class name.              */
        ITS_CLASS_NO_INIT,                  /* Class initialize.        */
        ITS_CLASS_NO_DEST,                  /* Class destroy.           */
        ITS_CLASS_PART_NO_INIT,             /* Class part initialize.   */
        ITS_CLASS_PART_NO_DEST,             /* Class part destroy.      */
        Construct,                          /* Instantiate.             */
        Destruct,                           /* Destroy.                 */
        Clone,                              /* Inherit clone.           */
        ITS_INST_PRINT_INHERIT,             /* Inherit Print.           */
        ITS_INST_SERIAL_INHERIT,            /* Inherit serial.          */
        Equals,                             /* Inherit equals.          */
        ITS_INST_HASH_INHERIT,              /* Inherit equals.          */
        NULL                                /* No extension.            */
    },

    /* ASN_LinkedList class part. */

    {
        GetBack,
        GetFront,
        GetSize,
        PopBack,
        PopFront,
        PushBack,
        PushFront,
        CursorSetBegin,
        CursorSetEnd,
        CursorForth,
        CursorBack,
        CursorIsBegin,
        CursorIsEnd,
        CursorGetElement,
        CursorRemoveElement
    }
};



ASN_LinkedList 
ASN_LinkedList_ConstructDefault()
{
    ASN_LinkedList result = NULL;

    result = 
        (ASN_LinkedList)ITS_ConstructObject((ITS_Class)&itsASN_LinkedList_ClassRec);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_LinkedList_Destruct(ASN_LinkedList object)
{
    ITS_DestructObject((ITS_Object)object);
}

ITS_Object 
ASN_LinkedList_GetBack(const ASN_LinkedList object)
{
    return ASN_LINKED_LIST_CLASS_GET_BACK(ITS_OBJ_CLASS(object))(object);
}

ITS_Object 
ASN_LinkedList_GetFront(const ASN_LinkedList object)
{
    return ASN_LINKED_LIST_CLASS_GET_FRONT(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_LinkedList_GetSize(const ASN_LinkedList object)
{
    return ASN_LINKED_LIST_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_LinkedList_PopBack(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_POP_BACK(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_LinkedList_PopFront(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_POP_FRONT(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_LinkedList_PushBack(ASN_LinkedList object, ITS_Object element)
{
    return ASN_LINKED_LIST_CLASS_PUSH_BACK(ITS_OBJ_CLASS(object))(object, element);
}

int 
ASN_LinkedList_PushFront(ASN_LinkedList object, ITS_Object element)
{
    return ASN_LINKED_LIST_CLASS_PUSH_FRONT(ITS_OBJ_CLASS(object))(object, element);
}

void 
ASN_LinkedList_CursorSetBegin(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_CURSOR_SET_BEGIN(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_LinkedList_CursorSetEnd(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_CURSOR_SET_END(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_LinkedList_CursorForth(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_CURSOR_FORTH(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_LinkedList_CursorBack(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_CURSOR_BACK(ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_LinkedList_CursorIsBegin(const ASN_LinkedList object)
{
    return ASN_LINKED_LIST_CLASS_CURSOR_IS_BEGIN(ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_LinkedList_CursorIsEnd(const ASN_LinkedList object)
{
    return ASN_LINKED_LIST_CLASS_CURSOR_IS_END(ITS_OBJ_CLASS(object))(object);
}

ITS_Object 
ASN_LinkedList_CursorGetElement(const ASN_LinkedList object)
{
    return ASN_LINKED_LIST_CLASS_CURSOR_GET_ELEMENT(ITS_OBJ_CLASS(object))(object);
}

void
ASN_LinkedList_CursorRemoveElement(ASN_LinkedList object)
{
    ASN_LINKED_LIST_CLASS_CURSOR_REMOVE_ELEMENT(ITS_OBJ_CLASS(object))(object);
}




