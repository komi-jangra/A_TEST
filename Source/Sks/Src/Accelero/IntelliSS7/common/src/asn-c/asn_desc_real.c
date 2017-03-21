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
 *  ID: $Id: asn_desc_real.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_real.h>

static int
Construct(ITS_Object object, va_list args)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_REAL_CLAUSE_RANGE(object)   = ITS_FALSE;
    ASN_DESC_REAL_MAX_VALUE(object)      = 0;
    ASN_DESC_REAL_MIN_VALUE(object)      = 0;
    ASN_DESC_REAL_DEFAULT_VALUE(object)  = 0;

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    /* Nothing to do. */
}

static ITS_BOOLEAN 
IsClauseRange(const ASN_DescReal object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_REAL_CLAUSE_RANGE(object);
}

static void
SetClauseRange(ASN_DescReal object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_REAL_CLAUSE_RANGE(object) = ITS_TRUE;
}

static void 
SetMaxValue(ASN_DescReal object, double maxValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_REAL_MAX_VALUE(object) = maxValue;
}

static double
GetMaxValue(const ASN_DescReal object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsClauseRange(object));

    return ASN_DESC_REAL_MAX_VALUE(object);
}

static void 
SetMinValue(ASN_DescReal object, double minValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_REAL_MIN_VALUE(object) = minValue;
}

static double
GetMinValue(const ASN_DescReal object)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsClauseRange(object));

    return ASN_DESC_REAL_MIN_VALUE(object);
}

static void 
SetDefaultValue(ASN_DescReal object, double defaultValue)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_DESC_REAL_DEFAULT_VALUE(object) = defaultValue;
}

static double
GetDefaultValue(const ASN_DescReal object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_DESC_REAL_DEFAULT_VALUE(object);
}

/*
 *  ASN_DescReal class record.
 */ 

ASN_DescReal_ClassRec itsASN_DescReal_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescReal_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_REAL_CLASS_NAME,             
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

    /* ASN_DescReal class part. */

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


ASN_DescReal
ASN_DescReal_ConstructDefault()
{
    ASN_DescReal result = NULL;

    result = 
        (ASN_DescReal)ITS_ConstructObject(
                                (ITS_Class)&itsASN_DescReal_ClassRec); 

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescReal_Destruct(ASN_DescReal object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescReal_Factory(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescReal_SetCloneForFactory(ASN_DescReal object, ASN_Real clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescReal_DefaultFactory(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescReal_SetCloneForDefaultFactory(ASN_DescReal object, ASN_Real clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescReal_IsClauseOptional(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescReal_IsClauseDefault(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescReal_IsClauseAnyTag(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescReal_SetClauseOptional(ASN_DescReal object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescReal_SetClauseDefault(ASN_DescReal object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescReal_SetClauseAnyTag(ASN_DescReal object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescReal_TagIdentify(const ASN_DescReal object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescReal_TagIdentity(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescReal_TagAddLevel(ASN_DescReal object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescReal_TagLevelNumber(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescReal_TagStack(ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescReal_GetName(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescReal_GetBaseName(const ASN_DescReal object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescReal_IsClauseRange(const ASN_DescReal object)
{
    return ASN_DESC_REAL_CLASS_IS_CLAUSE_RANGE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescReal_SetClauseRange(ASN_DescReal object)
{
    ASN_DESC_REAL_CLASS_SET_CLAUSE_RANGE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescReal_SetMaxValue(ASN_DescReal object, double maxValue)
{
    ASN_DESC_REAL_CLASS_SET_MAX_VALUE(
        ITS_OBJ_CLASS(object))(object, maxValue);
}

double 
ASN_DescReal_GetMaxValue(const ASN_DescReal object)
{
    return ASN_DESC_REAL_CLASS_GET_MAX_VALUE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescReal_SetMinValue(ASN_DescReal object, double minValue)
{
    ASN_DESC_REAL_CLASS_SET_MIN_VALUE(
        ITS_OBJ_CLASS(object))(object, minValue);
}

double 
ASN_DescReal_GetMinValue(const ASN_DescReal object)
{
    return ASN_DESC_REAL_CLASS_GET_MIN_VALUE(
        ITS_OBJ_CLASS(object))(object);
}

void 
ASN_DescReal_SetDefaultValue(ASN_DescReal object, double defaultValue)
{
    ASN_DESC_REAL_CLASS_SET_DEFAULT_VALUE(
        ITS_OBJ_CLASS(object))(object, defaultValue);
}

double 
ASN_DescReal_GetDefaultValue(const ASN_DescReal object)
{
    return ASN_DESC_REAL_CLASS_GET_DEFAULT_VALUE(
        ITS_OBJ_CLASS(object))(object);
}
