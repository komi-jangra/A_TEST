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
 *  ID: $Id: asn_desc_object.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_object.h>
#include <asn_object.h>


static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_DESC_OBJECT_CLASS_FACTORY(subClass) == ASN_DESC_OBJECT_FACTORY_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_FACTORY(subClass) =
            ASN_DESC_OBJECT_CLASS_FACTORY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(subClass) == ASN_DESC_OBJECT_SET_CLONE_FOR_FACTORY_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(subClass) =
            ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(subClass) == ASN_DESC_OBJECT_DEFAULT_FACTORY_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(subClass) =
            ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(subClass) == ASN_DESC_OBJECT_SET_CLONE_FOR_DEFAULT_FACTORY_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(subClass) =
            ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(subClass) == ASN_DESC_OBJECT_IS_CLAUSE_OPTIONAL_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(subClass) =
            ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(subClass) == ASN_DESC_OBJECT_IS_CLAUSE_DEFAULT_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(subClass) =
            ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(subClass) == ASN_DESC_OBJECT_IS_CLAUSE_ANY_TAG_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(subClass) =
            ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(subClass) == ASN_DESC_OBJECT_SET_CLAUSE_OPTIONAL_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(subClass) =
            ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(subClass) == ASN_DESC_OBJECT_SET_CLAUSE_DEFAULT_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(subClass) =
            ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(subClass) == ASN_DESC_OBJECT_SET_CLAUSE_ANY_TAG_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(subClass) =
            ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(subClass) == ASN_DESC_OBJECT_TAG_IDENTIFY_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(subClass) =
            ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(subClass) == ASN_DESC_OBJECT_TAG_IDENTITY_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(subClass) =
            ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(subClass) == ASN_DESC_OBJECT_TAG_ADD_LEVEL_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(subClass) =
            ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(subClass) == ASN_DESC_OBJECT_TAG_LEVEL_NUMBER_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(subClass) =
            ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_TAG_STACK(subClass) == ASN_DESC_OBJECT_TAG_STACK_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_TAG_STACK(subClass) =
            ASN_DESC_OBJECT_CLASS_TAG_STACK(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_GET_NAME(subClass) == ASN_DESC_OBJECT_GET_NAME_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_GET_NAME(subClass) =
            ASN_DESC_OBJECT_CLASS_GET_NAME(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(subClass) == ASN_DESC_OBJECT_GET_BASE_NAME_INHERIT)
    {
        ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(subClass) =
            ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(ITS_CLASS_SUPERCLASS(subClass));
    }

    return ITS_SUCCESS;
}

static void
ClassPartDestruct(ITS_Class subClass)
{
    /* Nothing to do. */
}

static int
Construct(ITS_Object object, va_list args)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_OBJECT_CLAUSE_OPTIONAL(object) = ITS_FALSE;
    ASN_DESC_OBJECT_CLAUSE_DEFAULT(object)  = ITS_FALSE;
    ASN_DESC_OBJECT_CLAUSE_ANY_TAG(object)  = ITS_FALSE;

    ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object)           = NULL;
    ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object)   = NULL;

    ASN_DESC_OBJECT_TAG_STACK(object) = ASN_LinkedList_ConstructDefault();

    if (ASN_DESC_OBJECT_TAG_STACK(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    if (ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object) != NULL)
    {
        ASN_Object_Destruct(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object));
        ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object) = NULL;
    }

    if (ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object) != NULL)
    {
        ASN_Object_Destruct(ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object));
        ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object) = NULL;
    }

    if (ASN_DESC_OBJECT_TAG_STACK(object) != NULL)
    {
        ASN_LinkedList tagStack = ASN_DESC_OBJECT_TAG_STACK(object);

        ASN_LinkedList_CursorSetBegin(tagStack);

        while (!ASN_LinkedList_CursorIsEnd(tagStack))
        {
            ASN_Tag tag = (ASN_Tag)ASN_LinkedList_CursorGetElement(tagStack);

            ASN_Tag_Destruct(tag);

            ASN_LinkedList_CursorForth(tagStack);
        }

        ASN_LinkedList_Destruct(tagStack);

        ASN_DESC_OBJECT_TAG_STACK(object) = NULL;
    }
}

static ITS_Object
Clone(ITS_Object object)
{
    /* Not defined => must not be reached. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return NULL;
}

static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    /* Not defined => must not be reached. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return ITS_FALSE;
}

static ASN_Object 
Factory(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_C_ASSERT(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object) != NULL);

    return ASN_Object_Clone(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object));
}

static void 
SetCloneForFactory(ASN_DescObject object, ASN_Object clone)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(clone != NULL);

    ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object) = clone;
    ASN_OBJECT_DESCRIPTION(clone) = object;
}

static ASN_Object 
DefaultFactory(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_C_ASSERT(ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object) != NULL);

    return ASN_Object_Clone(ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object));
}

static void 
SetCloneForDefaultFactory(ASN_DescObject object, ASN_Object clone)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(clone != NULL);

    ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(object) = clone;
    ASN_OBJECT_DESCRIPTION(clone) = object;
}

static ITS_BOOLEAN 
IsClauseOptional(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_OBJECT_CLAUSE_OPTIONAL(object);
}

static ITS_BOOLEAN 
IsClauseDefault(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_OBJECT_CLAUSE_DEFAULT(object);
}

static ITS_BOOLEAN 
IsClauseAnyTag(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_OBJECT_CLAUSE_ANY_TAG(object);
}

static void 
SetClauseOptional(ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_OBJECT_CLAUSE_OPTIONAL(object) = ITS_TRUE;
}

static void 
SetClauseDefault(ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_OBJECT_CLAUSE_DEFAULT(object) = ITS_TRUE;
}

static void 
SetClauseAnyTag(ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_OBJECT_CLAUSE_ANY_TAG(object) = ITS_TRUE;
}

/*
 *  Forward declaration.
 */ 

static size_t TagLevelNumber(const ASN_DescObject object);

static ITS_BOOLEAN 
TagIdentify(const ASN_DescObject object, const ASN_Tag tag)
{
    ASN_Tag tagStackFront = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(TagLevelNumber(object) >= 1);

    tagStackFront = 
        (ASN_Tag)ASN_LinkedList_GetFront(
            ASN_DESC_OBJECT_TAG_STACK(object));

    ASN_C_ASSERT(tagStackFront != NULL);

    return ASN_Tag_Equals(tag, tagStackFront);
}

static const ASN_Tag 
TagIdentity(const ASN_DescObject object)
{
    ASN_Tag tagStackFront = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(TagLevelNumber(object) >= 1);

    tagStackFront = 
        (ASN_Tag)ASN_LinkedList_GetFront(
            ASN_DESC_OBJECT_TAG_STACK(object));

    ASN_C_ENSURE(tagStackFront != NULL);

    return tagStackFront;
}

static void 
TagAddLevel(ASN_DescObject object, ASN_Tag tag)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    result = ASN_LinkedList_PushFront(
                ASN_DESC_OBJECT_TAG_STACK(object),
                (ITS_Object)tag);

    ASN_C_ENSURE(result == ITS_SUCCESS);
}

static size_t 
TagLevelNumber(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LinkedList_GetSize(
                ASN_DESC_OBJECT_TAG_STACK(object));
}

static ASN_LinkedList 
TagStack(ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_OBJECT_TAG_STACK(object);
}

static const char* 
GetName(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_ASSERT(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object) != NULL);

    return ASN_Object_GetName(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object));
}

static const char* 
GetBaseName(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_ASSERT(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object) != NULL);

    return ASN_Object_GetBaseName(ASN_DESC_OBJECT_CLONE_FOR_FACTORY(object));
}


/*
 *  ASN_DescObject class record.
 */ 

ASN_DescObject_ClassRec itsASN_DescObject_ClassRec =
{
    /* Core part. */

    {
        &itsCORE_ClassRec,                 
        sizeof(ASN_DescObject_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_OBJECT_CLASS_NAME,             
        ITS_CLASS_NO_INIT,                 
        ITS_CLASS_NO_DEST,                 
        ClassPartConstruct,      
        ClassPartDestruct,       
        Construct,               
        Destruct,                
        Clone,                   
        ITS_INST_PRINT_INHERIT,                   
        ITS_INST_SERIAL_INHERIT, 
        Equals,                  
        ITS_INST_HASH_INHERIT,   
        NULL                     
    },

    /* ASN_DescObject class part. */

    {
        Factory,
        SetCloneForFactory,
        DefaultFactory,
        SetCloneForDefaultFactory,
        IsClauseOptional,
        IsClauseDefault,
        IsClauseAnyTag,
        SetClauseOptional,
        SetClauseDefault,
        SetClauseAnyTag,
        TagIdentify,
        TagIdentity,
        TagAddLevel,
        TagLevelNumber,
        TagStack,
        GetName,
        GetBaseName
    }
};


void 
ASN_DescObject_Destruct(ASN_DescObject object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescObject_Factory(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescObject_SetCloneForFactory(ASN_DescObject object, ASN_Object clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))(object, clone);
}

ASN_Object 
ASN_DescObject_DefaultFactory(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescObject_SetCloneForDefaultFactory(ASN_DescObject object, ASN_Object clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))(object, clone);
}

ITS_BOOLEAN 
ASN_DescObject_IsClauseOptional(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_DescObject_IsClauseDefault(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_DescObject_IsClauseAnyTag(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescObject_SetClauseOptional(ASN_DescObject object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescObject_SetClauseDefault(ASN_DescObject object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescObject_SetClauseAnyTag(ASN_DescObject object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_DescObject_TagIdentify(const ASN_DescObject object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))(object, tag);
}

const ASN_Tag 
ASN_DescObject_TagIdentity(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescObject_TagAddLevel(ASN_DescObject object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))(object, tag);
}

size_t
ASN_DescObject_TagLevelNumber(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))(object);
}

ASN_LinkedList 
ASN_DescObject_TagStack(ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))(object);
}

const char* 
ASN_DescObject_GetName(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))(object);
}

const char* 
ASN_DescObject_GetBaseName(const ASN_DescObject object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))(object);
}
