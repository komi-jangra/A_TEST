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
 *  ID: $Id: asn_desc_choice.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_choice.h>

static int
Construct(ITS_Object object, va_list args)
{
    size_t size = 0;

    ASN_C_REQUIRE(object != NULL);

    size = va_arg(args, size_t);

    ASN_C_REQUIRE(size >= 0);

    ASN_DESC_CHOICE_CHOICES(object) = (ASN_DescObject*)calloc(size, sizeof(ASN_DescObject));

    ASN_C_ENSURE(ASN_DESC_CHOICE_CHOICES(object) != NULL);

    if (ASN_DESC_CHOICE_CHOICES(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    ASN_DESC_CHOICE_SIZE(object) = size;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);

#if defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY)

    for (i = 0; i < (int)ASN_DESC_CHOICE_SIZE(object); i++)
    {
        ASN_DescObject choice = ASN_DESC_CHOICE_CHOICES(object)[i];

        if (choice != NULL)
        {   
            ASN_DescObject_Destruct(choice);

            ASN_DESC_CHOICE_CHOICES(object)[i] = NULL;
        }
    }

#else /* !defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY) */

    i++; /* Avoid warning. */

#endif /* defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY) */

    if (ASN_DESC_CHOICE_CHOICES(object) != NULL)
    {
        free(ASN_DESC_CHOICE_CHOICES(object));
        ASN_DESC_CHOICE_CHOICES(object) = NULL;
    }
}


/*
 *  Forward declaration.
 */ 

static size_t TagLevelNumber(const ASN_DescObject object);

static ITS_BOOLEAN 
TagIdentify(const ASN_DescObject object, const ASN_Tag tag)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(TagLevelNumber(object) >= 1);

    if (TagLevelNumber(object) == 1)
    {
        int i = 0;

        for (i = 0; i < (int)ASN_DESC_CHOICE_SIZE(object); i++)
        {
            ASN_DescObject choiceDescription = ASN_DESC_CHOICE_CHOICES(object)[i];

            ASN_C_ASSERT(choiceDescription != NULL);

            if (ASN_DescObject_TagIdentify(choiceDescription, tag))
            {
                return ITS_TRUE;
            }
        }

        return ITS_FALSE;
    }
    else
    {
        ASN_Tag tagStackFront = 
            (ASN_Tag)ASN_LinkedList_GetFront(
                ASN_DESC_OBJECT_TAG_STACK(object));

        ASN_C_ASSERT(tagStackFront != NULL);

        return ASN_Tag_Equals(tag, tagStackFront);
    }
}

static const ASN_Tag 
TagIdentity(const ASN_DescObject object)
{
    ASN_Tag tagStackFront = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(TagLevelNumber(object) >= 1);

    if (TagLevelNumber(object) == 1)
    {
        /*
         *  Should never be reached by design of the encode/decode algorithms.
         *  CHOICE type is always explicitly tagged by ASN.1 compiler.
         */

        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ASN_C_ASSERT(must_not_be_reached);

        return NULL;
    }
    else
    {
        ASN_Tag tagStackFront = 
            (ASN_Tag)ASN_LinkedList_GetFront(
                ASN_DESC_OBJECT_TAG_STACK(object));

        ASN_C_ENSURE(tagStackFront != NULL);

        return tagStackFront;
    }
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

    return ASN_LinkedList_GetSize(ASN_DESC_OBJECT_TAG_STACK(object)) + 1;
}

/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN Contains(const ASN_DescChoice object, size_t index);
static ITS_BOOLEAN ContainsTag(const ASN_DescChoice object, const ASN_Tag tag);
static size_t GetSize(const ASN_DescChoice object);

static const ASN_DescObject* 
GetChoices(const ASN_DescChoice object)
{
    ASN_DescObject* result = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = ASN_DESC_CHOICE_CHOICES(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void 
AddChoice(ASN_DescChoice object, size_t index, ASN_DescObject choice)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));
    ASN_C_REQUIRE(choice != NULL);

    ASN_DESC_CHOICE_CHOICES(object)[index] = choice;
}

static const ASN_DescObject 
GetChoiceAt(const ASN_DescChoice object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));
    ASN_C_REQUIRE(Contains(object, index));

    return ASN_DESC_CHOICE_CHOICES(object)[index];
}

static const ASN_DescObject 
GetChoiceAtTag(const ASN_DescChoice object, const ASN_Tag tag)
{
    int i                   = 0;
    ASN_DescObject result   = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);
    ASN_C_REQUIRE(ContainsTag(object, tag));

    for (i = 0; i < (int)ASN_DESC_CHOICE_SIZE(object); i++)
    {
        ASN_DescObject choiceDescription = ASN_DESC_CHOICE_CHOICES(object)[i];

        ASN_C_ASSERT(choiceDescription != NULL);

        if (ASN_DescObject_TagIdentify(choiceDescription, tag))
        {
            result = choiceDescription;
            break;
        }
    }
            
    ASN_C_ENSURE(result != NULL);

    return result;
}

static ITS_BOOLEAN 
Contains(const ASN_DescChoice object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    return ASN_DESC_CHOICE_CHOICES(object)[index] != NULL;
}

static ITS_BOOLEAN 
ContainsTag(const ASN_DescChoice object, const ASN_Tag tag)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    for (i = 0; i < (int)ASN_DESC_CHOICE_SIZE(object); i++)
    {
        ASN_DescObject choiceDescription = ASN_DESC_CHOICE_CHOICES(object)[i];

        ASN_C_ASSERT(choiceDescription != NULL);

        if (ASN_DescObject_TagIdentify(choiceDescription, tag))
        {
            return ITS_TRUE;
        }
    }
            
    return ITS_FALSE;
}

static size_t 
GetSize(const ASN_DescChoice object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_CHOICE_SIZE(object);
}


/*
 *  ASN_DescChoice class record.
 */ 

ASN_DescChoice_ClassRec itsASN_DescChoice_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescChoice_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_CHOICE_CLASS_NAME,             
        ITS_CLASS_NO_INIT,                 
        ITS_CLASS_NO_DEST,                 
        ITS_CLASS_PART_NO_INIT,      
        ITS_CLASS_PART_NO_DEST,       
        Construct,               
        Destruct,                
        ITS_INST_CLONE_INHERIT,                   
        ITS_INST_PRINT_INHERIT,                   
        ITS_INST_SERIAL_INHERIT, 
        ITS_INST_EQUALS_INHERIT,                  
        ITS_INST_HASH_INHERIT,   
        NULL                     
    },

    /* ASN_DescObject class part. */

    {
        ASN_DESC_OBJECT_FACTORY_INHERIT,                      
        ASN_DESC_OBJECT_SET_CLONE_FOR_FACTORY_INHERIT,        
        ASN_DESC_OBJECT_DEFAULT_FACTORY_INHERIT,              
        ASN_DESC_OBJECT_SET_CLONE_FOR_DEFAULT_FACTORY_INHERIT,
        ASN_DESC_OBJECT_IS_CLAUSE_OPTIONAL_INHERIT,           
        ASN_DESC_OBJECT_IS_CLAUSE_DEFAULT_INHERIT,            
        ASN_DESC_OBJECT_IS_CLAUSE_ANY_TAG_INHERIT,            
        ASN_DESC_OBJECT_SET_CLAUSE_OPTIONAL_INHERIT,          
        ASN_DESC_OBJECT_SET_CLAUSE_DEFAULT_INHERIT,           
        ASN_DESC_OBJECT_SET_CLAUSE_ANY_TAG_INHERIT,           
        TagIdentify,
        TagIdentity,
        TagAddLevel,
        TagLevelNumber,
        ASN_DESC_OBJECT_TAG_STACK_INHERIT,                    
        ASN_DESC_OBJECT_GET_NAME_INHERIT,                     
        ASN_DESC_OBJECT_GET_BASE_NAME_INHERIT
    },

    /* ASN_DescChoice class part. */

    {
        GetChoices,
        AddChoice,
        GetChoiceAt,
        GetChoiceAtTag,
        Contains,
        ContainsTag,
        GetSize
    }
};


ASN_DescChoice
ASN_DescChoice_ConstructWithSize(size_t size)
{
    ASN_DescChoice result = NULL;

    result = 
        (ASN_DescChoice)ITS_ConstructObject(
                                (ITS_Class)&itsASN_DescChoice_ClassRec, size); 

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescChoice_Destruct(ASN_DescChoice object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescChoice_Factory(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescChoice_SetCloneForFactory(ASN_DescChoice object, ASN_Choice clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescChoice_DefaultFactory(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescChoice_SetCloneForDefaultFactory(ASN_DescChoice object, ASN_Choice clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescChoice_IsClauseOptional(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescChoice_IsClauseDefault(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescChoice_IsClauseAnyTag(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescChoice_SetClauseOptional(ASN_DescChoice object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescChoice_SetClauseDefault(ASN_DescChoice object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescChoice_SetClauseAnyTag(ASN_DescChoice object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescChoice_TagIdentify(const ASN_DescChoice object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescChoice_TagIdentity(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescChoice_TagAddLevel(ASN_DescChoice object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescChoice_TagLevelNumber(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescChoice_TagStack(ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescChoice_GetName(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescChoice_GetBaseName(const ASN_DescChoice object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}


const ASN_DescObject* 
ASN_DescChoice_GetChoices(const ASN_DescChoice object)
{
    return ASN_DESC_CHOICE_CLASS_GET_CHOICES(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescChoice_AddChoice(ASN_DescChoice object, size_t index, ASN_DescObject choice)
{
    ASN_DESC_CHOICE_CLASS_ADD_CHOICE(
        ITS_OBJ_CLASS(object))(object, index, choice);
}

const ASN_DescObject 
ASN_DescChoice_GetChoiceAt(const ASN_DescChoice object, size_t index)
{
    return ASN_DESC_CHOICE_CLASS_GET_CHOICE_AT(
        ITS_OBJ_CLASS(object))(object, index);
}

const ASN_DescObject 
ASN_DescChoice_GetChoiceAtTag(const ASN_DescChoice object, const ASN_Tag tag)
{
    return ASN_DESC_CHOICE_CLASS_GET_CHOICE_AT_TAG(
        ITS_OBJ_CLASS(object))(object, tag);
}

ITS_BOOLEAN 
ASN_DescChoice_Contains(const ASN_DescChoice object, size_t index)
{
    return ASN_DESC_CHOICE_CLASS_CONTAINS(
        ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_DescChoice_ContainsTag(const ASN_DescChoice object, const ASN_Tag tag)
{
    return ASN_DESC_CHOICE_CLASS_CONTAINS_TAG(
        ITS_OBJ_CLASS(object))(object, tag);
}

size_t 
ASN_DescChoice_GetSize(const ASN_DescChoice object)
{
    return ASN_DESC_CHOICE_CLASS_GET_SIZE(
        ITS_OBJ_CLASS(object))(object);
}


