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
 *  ID: $Id: asn_desc_enumerated.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_enumerated.h>

static int
Construct(ITS_Object object, va_list args)
{
    size_t size = 0;

    ASN_C_REQUIRE(object != NULL);

    size = va_arg(args, size_t);

    ASN_C_REQUIRE(size >= 0);

    ASN_DESC_ENUMERATED_VALUES(object) = (ITS_LONG*)calloc(size, sizeof(ITS_LONG));

    if (ASN_DESC_ENUMERATED_VALUES(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    ASN_DESC_ENUMERATED_SIZE(object) = size;

    ASN_DESC_ENUMERATED_DEFAULT_VALUE(object)  = 0;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    if (ASN_DESC_ENUMERATED_VALUES(object) != NULL)
    {
        free(ASN_DESC_ENUMERATED_VALUES(object));
        ASN_DESC_ENUMERATED_VALUES(object) = NULL;
    }
}

/*
 *  Forward declarations.
 */

static size_t GetSize(const ASN_DescEnumerated object);

static void 
AddValue(ASN_DescEnumerated object, size_t index, ITS_LONG value)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    ASN_DESC_ENUMERATED_VALUES(object)[index] = value;
}

static ITS_LONG 
GetValueAt(const ASN_DescEnumerated object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    return ASN_DESC_ENUMERATED_VALUES(object)[index];
}

static ITS_BOOLEAN 
Contains(const ASN_DescEnumerated object, ITS_LONG value)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);

    for (i = 0; i < (int)ASN_DESC_ENUMERATED_SIZE(object); i++)
    {
        if (ASN_DESC_ENUMERATED_VALUES(object)[i] == value)
        {
            return ITS_TRUE;
        }
    }

    return ITS_FALSE;
}

static size_t 
GetSize(const ASN_DescEnumerated object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_ENUMERATED_SIZE(object);
}

static void 
SetDefaultValue(ASN_DescEnumerated object, ITS_LONG defaultValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_ENUMERATED_DEFAULT_VALUE(object) = defaultValue;
}

static ITS_LONG
GetDefaultValue(const ASN_DescEnumerated object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_ENUMERATED_DEFAULT_VALUE(object);
}

/*
 *  ASN_DescEnumerated class record.
 */ 

ASN_DescEnumerated_ClassRec itsASN_DescEnumerated_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescEnumerated_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_ENUMERATED_CLASS_NAME,             
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

    /* ASN_DescEnumerated class part. */

    {
        AddValue,
        GetValueAt,
        Contains,
        GetSize,
        SetDefaultValue,
        GetDefaultValue
    }
};


ASN_DescEnumerated
ASN_DescEnumerated_ConstructWithSize(size_t size)
{
    ASN_DescEnumerated result = NULL;

    result = 
        (ASN_DescEnumerated)ITS_ConstructObject(
                                (ITS_Class)&itsASN_DescEnumerated_ClassRec, size); 

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescEnumerated_Destruct(ASN_DescEnumerated object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescEnumerated_Factory(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_SetCloneForFactory(ASN_DescEnumerated object, ASN_Enumerated clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescEnumerated_DefaultFactory(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_SetCloneForDefaultFactory(ASN_DescEnumerated object, ASN_Enumerated clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescEnumerated_IsClauseOptional(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescEnumerated_IsClauseDefault(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescEnumerated_IsClauseAnyTag(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_SetClauseOptional(ASN_DescEnumerated object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_SetClauseDefault(ASN_DescEnumerated object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_SetClauseAnyTag(ASN_DescEnumerated object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescEnumerated_TagIdentify(const ASN_DescEnumerated object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescEnumerated_TagIdentity(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_TagAddLevel(ASN_DescEnumerated object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescEnumerated_TagLevelNumber(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescEnumerated_TagStack(ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescEnumerated_GetName(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescEnumerated_GetBaseName(const ASN_DescEnumerated object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescEnumerated_AddValue(ASN_DescEnumerated object, size_t index, ITS_LONG value)
{
    ASN_DESC_ENUMERATED_CLASS_ADD_VALUE(
        ITS_OBJ_CLASS(object))(object, index, value);
}

ITS_LONG 
ASN_DescEnumerated_GetValueAt(const ASN_DescEnumerated object, size_t index)
{
    return ASN_DESC_ENUMERATED_CLASS_GET_VALUE_AT(
        ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_DescEnumerated_Contains(const ASN_DescEnumerated object, ITS_LONG value)
{
    return ASN_DESC_ENUMERATED_CLASS_CONTAINS(
        ITS_OBJ_CLASS(object))(object, value);
}

size_t 
ASN_DescEnumerated_GetSize(const ASN_DescEnumerated object)
{
    return ASN_DESC_ENUMERATED_CLASS_GET_SIZE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescEnumerated_SetDefaultValue(ASN_DescEnumerated object, ITS_LONG defaultValue)
{
    ASN_DESC_ENUMERATED_CLASS_SET_DEFAULT_VALUE(
        ITS_OBJ_CLASS(object))(object, defaultValue);
}

ITS_LONG 
ASN_DescEnumerated_GetDefaultValue(const ASN_DescEnumerated object)
{
    return ASN_DESC_ENUMERATED_CLASS_GET_DEFAULT_VALUE(
        ITS_OBJ_CLASS(object))(object);
}
