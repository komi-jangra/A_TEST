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
 *  ID: $Id: asn_desc_integer.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_integer.h>

static int
Construct(ITS_Object object, va_list args)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_INTEGER_CLAUSE_RANGE(object)   = ITS_FALSE;
    ASN_DESC_INTEGER_MAX_VALUE(object)      = 0;
    ASN_DESC_INTEGER_MIN_VALUE(object)      = 0;
    ASN_DESC_INTEGER_DEFAULT_VALUE(object)  = 0;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    /* Nothing to do. */
}

static ITS_BOOLEAN 
IsClauseRange(const ASN_DescInteger object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_INTEGER_CLAUSE_RANGE(object);
}

static void
SetClauseRange(ASN_DescInteger object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_INTEGER_CLAUSE_RANGE(object) = ITS_TRUE;
}

static void 
SetMaxValue(ASN_DescInteger object, ITS_LONG maxValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_INTEGER_MAX_VALUE(object) = maxValue;
}

static ITS_LONG
GetMaxValue(const ASN_DescInteger object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsClauseRange(object));

    return ASN_DESC_INTEGER_MAX_VALUE(object);
}

static void 
SetMinValue(ASN_DescInteger object, ITS_LONG minValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_INTEGER_MIN_VALUE(object) = minValue;
}

static ITS_LONG
GetMinValue(const ASN_DescInteger object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsClauseRange(object));

    return ASN_DESC_INTEGER_MIN_VALUE(object);
}

static void 
SetDefaultValue(ASN_DescInteger object, ITS_LONG defaultValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_INTEGER_DEFAULT_VALUE(object) = defaultValue;
}

static ITS_LONG
GetDefaultValue(const ASN_DescInteger object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_INTEGER_DEFAULT_VALUE(object);
}

/*
 *  ASN_DescInteger class record.
 */ 

ASN_DescInteger_ClassRec itsASN_DescInteger_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescInteger_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_INTEGER_CLASS_NAME,             
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

    /* ASN_DescInteger class part. */

    {
        IsClauseRange,
        SetClauseRange,
        SetMaxValue,
        GetMaxValue,
        SetMinValue,
        GetMinValue,
        SetDefaultValue,
        GetDefaultValue
    }
};


ASN_DescInteger
ASN_DescInteger_ConstructDefault()
{
    ASN_DescInteger result = NULL;

    result = 
        (ASN_DescInteger)ITS_ConstructObject(
                                (ITS_Class)&itsASN_DescInteger_ClassRec); 

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescInteger_Destruct(ASN_DescInteger object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescInteger_Factory(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescInteger_SetCloneForFactory(ASN_DescInteger object, ASN_Integer clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescInteger_DefaultFactory(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescInteger_SetCloneForDefaultFactory(ASN_DescInteger object, ASN_Integer clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescInteger_IsClauseOptional(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescInteger_IsClauseDefault(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescInteger_IsClauseAnyTag(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescInteger_SetClauseOptional(ASN_DescInteger object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescInteger_SetClauseDefault(ASN_DescInteger object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescInteger_SetClauseAnyTag(ASN_DescInteger object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescInteger_TagIdentify(const ASN_DescInteger object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescInteger_TagIdentity(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescInteger_TagAddLevel(ASN_DescInteger object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescInteger_TagLevelNumber(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescInteger_TagStack(ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescInteger_GetName(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescInteger_GetBaseName(const ASN_DescInteger object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescInteger_IsClauseRange(const ASN_DescInteger object)
{
    return ASN_DESC_INTEGER_CLASS_IS_CLAUSE_RANGE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescInteger_SetClauseRange(ASN_DescInteger object)
{
    ASN_DESC_INTEGER_CLASS_SET_CLAUSE_RANGE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescInteger_SetMaxValue(ASN_DescInteger object, ITS_LONG maxValue)
{
    ASN_DESC_INTEGER_CLASS_SET_MAX_VALUE(
        ITS_OBJ_CLASS(object))(object, maxValue);
}

ITS_LONG 
ASN_DescInteger_GetMaxValue(const ASN_DescInteger object)
{
    return ASN_DESC_INTEGER_CLASS_GET_MAX_VALUE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescInteger_SetMinValue(ASN_DescInteger object, ITS_LONG minValue)
{
    ASN_DESC_INTEGER_CLASS_SET_MIN_VALUE(
        ITS_OBJ_CLASS(object))(object, minValue);
}

ITS_LONG 
ASN_DescInteger_GetMinValue(const ASN_DescInteger object)
{
    return ASN_DESC_INTEGER_CLASS_GET_MIN_VALUE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescInteger_SetDefaultValue(ASN_DescInteger object, ITS_LONG defaultValue)
{
    ASN_DESC_INTEGER_CLASS_SET_DEFAULT_VALUE(
        ITS_OBJ_CLASS(object))(object, defaultValue);
}

ITS_LONG 
ASN_DescInteger_GetDefaultValue(const ASN_DescInteger object)
{
    return ASN_DESC_INTEGER_CLASS_GET_DEFAULT_VALUE(
        ITS_OBJ_CLASS(object))(object);
}
