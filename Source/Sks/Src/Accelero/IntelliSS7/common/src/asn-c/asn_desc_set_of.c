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
 *  ID: $Id: asn_desc_set_of.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_set_of.h>

static int
Construct(ITS_Object object, va_list args)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_SET_OF_CLAUSE_SIZE(object)    = ITS_FALSE;
    ASN_DESC_SET_OF_MAX_SIZE(object)       = 0;
    ASN_DESC_SET_OF_MIN_SIZE(object)       = 0;
    ASN_DESC_SET_OF_ELEMENT(object)        = NULL;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

#if defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY)

    if (ASN_DESC_SET_OF_ELEMENT(object) != NULL)
    {
        ASN_DescObject_Destruct(ASN_DESC_SET_OF_ELEMENT(object));
        ASN_DESC_SET_OF_ELEMENT(object) = NULL;
    }

#endif /* defined(ASN_C_DESTRUCT_DESCRIPTION_RECURSIVELY) */

}

static ITS_BOOLEAN 
IsClauseSize(const ASN_DescSetOf object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_SET_OF_CLAUSE_SIZE(object);
}

static void
SetClauseSize(ASN_DescSetOf object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_SET_OF_CLAUSE_SIZE(object) = ITS_TRUE;
}

static void 
SetMaxSize(ASN_DescSetOf object, size_t maxSize)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_SET_OF_MAX_SIZE(object) = maxSize;
}

static size_t
GetMaxSize(const ASN_DescSetOf object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsClauseSize(object));

    return ASN_DESC_SET_OF_MAX_SIZE(object);
}

static void 
SetMinSize(ASN_DescSetOf object, size_t minSize)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_SET_OF_MIN_SIZE(object) = minSize;
}

static size_t
GetMinSize(const ASN_DescSetOf object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsClauseSize(object));

    return ASN_DESC_SET_OF_MIN_SIZE(object);
}

static ASN_DescObject 
GetElement(const ASN_DescSetOf object)
{
    ASN_DescObject result = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = ASN_DESC_SET_OF_ELEMENT(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void 
SetElement(ASN_DescSetOf object, ASN_DescObject element)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(element != NULL);

    ASN_DESC_SET_OF_ELEMENT(object) = element;
}

static ITS_BOOLEAN 
Contains(const ASN_DescSetOf object, const ASN_Tag tag)
{
    ASN_DescObject element = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    element = ASN_DESC_SET_OF_ELEMENT(object);

    ASN_C_ASSERT(element != NULL);

    return ASN_DescObject_TagIdentify(element, tag);
}


/*
 *  ASN_DescSetOf class record.
 */ 

ASN_DescSetOf_ClassRec itsASN_DescSetOf_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescSetOf_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_SET_OF_CLASS_NAME,             
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

    /* ASN_DescSetOf class part. */

    {
        IsClauseSize,
        SetClauseSize,
        SetMaxSize,
        GetMaxSize,
        SetMinSize,
        GetMinSize,
        GetElement,
        SetElement,
        Contains
    }
};


ASN_DescSetOf
ASN_DescSetOf_ConstructDefault()
{
    ASN_DescSetOf result = NULL;

    result = 
        (ASN_DescSetOf)ITS_ConstructObject(
                                (ITS_Class)&itsASN_DescSetOf_ClassRec); 

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescSetOf_Destruct(ASN_DescSetOf object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescSetOf_Factory(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSetOf_SetCloneForFactory(ASN_DescSetOf object, ASN_SetOf clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescSetOf_DefaultFactory(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSetOf_SetCloneForDefaultFactory(ASN_DescSetOf object, ASN_SetOf clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescSetOf_IsClauseOptional(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSetOf_IsClauseDefault(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSetOf_IsClauseAnyTag(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSetOf_SetClauseOptional(ASN_DescSetOf object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSetOf_SetClauseDefault(ASN_DescSetOf object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSetOf_SetClauseAnyTag(ASN_DescSetOf object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSetOf_TagIdentify(const ASN_DescSetOf object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescSetOf_TagIdentity(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescSetOf_TagAddLevel(ASN_DescSetOf object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescSetOf_TagLevelNumber(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescSetOf_TagStack(ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescSetOf_GetName(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescSetOf_GetBaseName(const ASN_DescSetOf object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescSetOf_IsClauseSize(const ASN_DescSetOf object)
{
    return ASN_DESC_SET_OF_CLASS_IS_CLAUSE_SIZE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescSetOf_SetClauseSize(ASN_DescSetOf object)
{
    ASN_DESC_SET_OF_CLASS_SET_CLAUSE_SIZE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescSetOf_SetMaxSize(ASN_DescSetOf object, size_t maxSize)
{                   
    ASN_DESC_SET_OF_CLASS_SET_MAX_SIZE(
        ITS_OBJ_CLASS(object))(object, maxSize);
}

size_t 
ASN_DescSetOf_GetMaxSize(const ASN_DescSetOf object)
{
    return ASN_DESC_SET_OF_CLASS_GET_MAX_SIZE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescSetOf_SetMinSize(ASN_DescSetOf object, size_t minSize)
{
    ASN_DESC_SET_OF_CLASS_SET_MIN_SIZE(
        ITS_OBJ_CLASS(object))(object, minSize);
}

size_t 
ASN_DescSetOf_GetMinSize(const ASN_DescSetOf object)
{
    return ASN_DESC_SET_OF_CLASS_GET_MIN_SIZE(
        ITS_OBJ_CLASS(object))(object);
}

ASN_DescObject 
ASN_DescSetOf_GetElement(const ASN_DescSetOf object)
{
    return ASN_DESC_SET_OF_CLASS_GET_ELEMENT(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescSetOf_SetElement(ASN_DescSetOf object, ASN_DescObject element)
{
    ASN_DESC_SET_OF_CLASS_SET_ELEMENT(
        ITS_OBJ_CLASS(object))(object, element);
}

ITS_BOOLEAN 
ASN_DescSetOf_Contains(const ASN_DescSetOf object, const ASN_Tag tag)
{
    return ASN_DESC_SET_OF_CLASS_CONTAINS(
        ITS_OBJ_CLASS(object))(object, tag);
}

