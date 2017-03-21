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
 *  ID: $Id: asn_desc_sequence.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_sequence.h>

static int
Construct(ITS_Object object, va_list args)
{
    size_t size = 0;

    ASN_C_REQUIRE(object != NULL);

    size = va_arg(args, size_t);

    ASN_C_REQUIRE(size >= 0);

    ASN_DESC_SEQUENCE_ELEMENTS(object) = (ASN_DescObject*)calloc(size, sizeof(ASN_DescObject));

    ASN_C_ENSURE(ASN_DESC_SEQUENCE_ELEMENTS(object) != NULL);

    if (ASN_DESC_SEQUENCE_ELEMENTS(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    ASN_DESC_SEQUENCE_SIZE(object) = size;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);

#if defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY)

    for (i = 0; i < (int)ASN_DESC_SEQUENCE_SIZE(object); i++)
    {
        ASN_DescObject element = ASN_DESC_SEQUENCE_ELEMENTS(object)[i];

        if (element != NULL)
        {
            ASN_DescObject_Destruct(element);

            ASN_DESC_SEQUENCE_ELEMENTS(object)[i] = NULL;
        }
    }

#else /* !defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY) */

    i++; /* Avoid warning. */

#endif /* defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY) */

    if (ASN_DESC_SEQUENCE_ELEMENTS(object) != NULL)
    {
        free(ASN_DESC_SEQUENCE_ELEMENTS(object));
        ASN_DESC_SEQUENCE_ELEMENTS(object) = NULL;
    }
}

/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN Contains(const ASN_DescSequence object, size_t index);
static ITS_BOOLEAN ContainsTag(const ASN_DescSequence object, const ASN_Tag tag);
static size_t GetSize(const ASN_DescSequence object);

static const ASN_DescObject* 
GetElements(const ASN_DescSequence object)
{
    ASN_DescObject* result = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = ASN_DESC_SEQUENCE_ELEMENTS(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void 
AddElement(ASN_DescSequence object, size_t index, ASN_DescObject element)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    ASN_DESC_SEQUENCE_ELEMENTS(object)[index] = element;
}

static const ASN_DescObject 
GetElementAt(const ASN_DescSequence object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));
    ASN_C_REQUIRE(Contains(object, index));

    return ASN_DESC_SEQUENCE_ELEMENTS(object)[index];
}

static const ASN_DescObject 
GetElementAtTag(const ASN_DescSequence object, const ASN_Tag tag)
{
    int i                   = 0;
    ASN_DescObject result   = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);
    ASN_C_REQUIRE(ContainsTag(object, tag));

    for (i = 0; i < (int)ASN_DESC_SEQUENCE_SIZE(object); i++)
    {
        ASN_DescObject element = ASN_DESC_SEQUENCE_ELEMENTS(object)[i];

        if (element != NULL && ASN_DescObject_TagIdentify(element, tag))
        {
            result = element;
            break;
        }
    }
            
    ASN_C_ENSURE(result != NULL);

    return result;
}

static ITS_BOOLEAN 
Contains(const ASN_DescSequence object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    return ASN_DESC_SEQUENCE_ELEMENTS(object)[index] != NULL;
}

static ITS_BOOLEAN 
ContainsTag(const ASN_DescSequence object, const ASN_Tag tag)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    for (i = 0; i < (int)ASN_DESC_SEQUENCE_SIZE(object); i++)
    {
        ASN_DescObject element = ASN_DESC_SEQUENCE_ELEMENTS(object)[i];

        if (element != NULL && ASN_DescObject_TagIdentify(element, tag))
        {
            return ITS_TRUE;
        }
    }
            
    return ITS_FALSE;
}

static size_t 
GetSize(const ASN_DescSequence object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_SEQUENCE_SIZE(object);
}


/*
 *  ASN_DescSequence class record.
 */ 

ASN_DescSequence_ClassRec itsASN_DescSequence_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescSequence_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_SEQUENCE_CLASS_NAME,             
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
        ASN_DESC_OBJECT_TAG_IDENTIFY_INHERIT,                 
        ASN_DESC_OBJECT_TAG_IDENTITY_INHERIT,                 
        ASN_DESC_OBJECT_TAG_ADD_LEVEL_INHERIT,                
        ASN_DESC_OBJECT_TAG_LEVEL_NUMBER_INHERIT,             
        ASN_DESC_OBJECT_TAG_STACK_INHERIT,                    
        ASN_DESC_OBJECT_GET_NAME_INHERIT,                     
        ASN_DESC_OBJECT_GET_BASE_NAME_INHERIT
    },

    /* ASN_DescSequence class part. */

    {
        GetElements,
        AddElement,
        GetElementAt,
        GetElementAtTag,
        Contains,
        ContainsTag,
        GetSize
    }
};


ASN_DescSequence
ASN_DescSequence_ConstructWithSize(size_t size)
{
    ASN_DescSequence result = NULL;

    result = 
        (ASN_DescSequence)ITS_ConstructObject(
                                (ITS_Class)&itsASN_DescSequence_ClassRec, size); 

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescSequence_Destruct(ASN_DescSequence object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescSequence_Factory(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSequence_SetCloneForFactory(ASN_DescSequence object, ASN_Sequence clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescSequence_DefaultFactory(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSequence_SetCloneForDefaultFactory(ASN_DescSequence object, ASN_Sequence clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescSequence_IsClauseOptional(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSequence_IsClauseDefault(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSequence_IsClauseAnyTag(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSequence_SetClauseOptional(ASN_DescSequence object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSequence_SetClauseDefault(ASN_DescSequence object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSequence_SetClauseAnyTag(ASN_DescSequence object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSequence_TagIdentify(const ASN_DescSequence object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescSequence_TagIdentity(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSequence_TagAddLevel(ASN_DescSequence object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescSequence_TagLevelNumber(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescSequence_TagStack(ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescSequence_GetName(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescSequence_GetBaseName(const ASN_DescSequence object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}


const ASN_DescObject* 
ASN_DescSequence_GetElements(const ASN_DescSequence object)
{
    return ASN_DESC_SEQUENCE_CLASS_GET_ELEMENTS(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescSequence_AddElement(ASN_DescSequence object, size_t index, ASN_DescObject element)
{
    ASN_DESC_SEQUENCE_CLASS_ADD_ELEMENT(
        ITS_OBJ_CLASS(object))(object, index, element);
}

const ASN_DescObject 
ASN_DescSequence_GetElementAt(const ASN_DescSequence object, size_t index)
{
    return ASN_DESC_SEQUENCE_CLASS_GET_ELEMENT_AT(
        ITS_OBJ_CLASS(object))(object, index);
}

const ASN_DescObject 
ASN_DescSequence_GetElementAtTag(const ASN_DescSequence object, const ASN_Tag tag)
{
    return ASN_DESC_SEQUENCE_CLASS_GET_ELEMENT_AT_TAG(
        ITS_OBJ_CLASS(object))(object, tag);
}

ITS_BOOLEAN 
ASN_DescSequence_Contains(const ASN_DescSequence object, size_t index)
{
    return ASN_DESC_SEQUENCE_CLASS_CONTAINS(
        ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_DescSequence_ContainsTag(const ASN_DescSequence object, const ASN_Tag tag)
{
    return ASN_DESC_SEQUENCE_CLASS_CONTAINS_TAG(
        ITS_OBJ_CLASS(object))(object, tag);
}

size_t 
ASN_DescSequence_GetSize(const ASN_DescSequence object)
{
    return ASN_DESC_SEQUENCE_CLASS_GET_SIZE(
        ITS_OBJ_CLASS(object))(object);
}


