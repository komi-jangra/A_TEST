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
 *  ID: $Id: asn_boolean.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_boolean.h>
#include <asn_desc_boolean.h>
#include <asn_length.h>

/*
 *  Protected preprocessor constant definitions.
 */

#define ASN_BOOLEAN_LENGTH          1
#define ASN_BOOLEAN_VALUE_TRUE      0xFFU
#define ASN_BOOLEAN_VALUE_FALSE     0x00U

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_BOOLEAN_CLASS_GET_VALUE(subClass) == ASN_BOOLEAN_GET_VALUE_INHERIT)
    {
        ASN_BOOLEAN_CLASS_GET_VALUE(subClass) =
            ASN_BOOLEAN_CLASS_GET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BOOLEAN_CLASS_SET_VALUE(subClass) == ASN_BOOLEAN_SET_VALUE_INHERIT)
    {
        ASN_BOOLEAN_CLASS_SET_VALUE(subClass) =
            ASN_BOOLEAN_CLASS_SET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BOOLEAN_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_BOOLEAN_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_BOOLEAN_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_BOOLEAN_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    return ITS_SUCCESS;
}

static void
ClassPartDestruct(ITS_Class subClass)
{
    /* Nothing to do. */
}

/*
 *  Forward declarations.
 */ 

static ASN_DescBoolean GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ITS_BOOLEAN value           = 0;
    ASN_DescBoolean description = NULL;

    value = va_arg(args, ITS_BOOLEAN);

    description = va_arg(args, ASN_DescBoolean);

    ASN_BOOLEAN_VALUE(object) = value;

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        ASN_C_ASSERT(ASN_OBJECT_DESCRIPTION(object) != NULL);
    }
    else
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)description;
    }

    return ITS_SUCCESS;
}


static void
Destruct(ITS_Object object)
{
    /* Nothing to do. */
}


static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result   = NULL;

    result = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (result == NULL)
    {
        return result;
    }

    memcpy(result, object, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    return result;
}


static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    if (ITS_OBJ_CLASS(object) != ITS_OBJ_CLASS(other))
    {
        return ITS_FALSE;
    }

    if (ASN_BOOLEAN_VALUE(object) != ASN_BOOLEAN_VALUE(other))
    {
        return ITS_FALSE;
    }

    return ITS_TRUE;
}

static ASN_DescBoolean staticDescription = NULL;

static ASN_DescBoolean
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescBoolean result   = NULL;
    ASN_Boolean cloneForFactory     = NULL;
    ASN_Tag universalTag            = NULL;

    if (initialized)
    {
        ASN_C_ENSURE(result != NULL);

        return result;
    }

    ASN_Lock();

    if (initialized)
    {
        ASN_Unlock();

        ASN_C_ENSURE(result != NULL);

        return result;
    }
    else
    {
        ASN_C_ASSERT(result == NULL);

        staticDescription = ASN_DescBoolean_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Boolean_ConstructWithValueDescription(ITS_FALSE, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescBoolean_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescBoolean_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_Boolean_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescBoolean_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescBoolean_TagAddLevel(staticDescription, universalTag);

        result = staticDescription;

        initialized = ITS_TRUE;

        ASN_Unlock();

        ASN_C_ENSURE(result != NULL);

        return result;
    }
}

static void
DestructStaticDescription()
{
    if (staticDescription != NULL)
    {
        ASN_DescBoolean_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static ITS_BOOLEAN
GetValue(const ASN_Boolean object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_BOOLEAN_VALUE(object);
}

static void 
SetValue(ASN_Boolean object, ITS_BOOLEAN value)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_BOOLEAN_VALUE(object) = value;
}

static ASN_Tag
GetUniversalTag(const ASN_Boolean object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_BOOLEAN);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescBoolean description = NULL;

    ITS_OCTET array[ASN_BOOLEAN_LENGTH];

    ITS_BOOLEAN value       = ITS_FALSE;
    ASN_Octets valOctets    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescBoolean)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    memset(array, 0x00U, ASN_BOOLEAN_LENGTH);

    value = ASN_BOOLEAN_VALUE(object);

    /* Encode check begin. */

    /* Nothing to do. */

    /* Encode check end. */

    if (value)
    {
        array[0] = ASN_BOOLEAN_VALUE_TRUE;
    }
    else
    {
        array[0] = ASN_BOOLEAN_VALUE_FALSE;
    }

    valOctets = ASN_Octets_ConstructWithArray(array, ASN_BOOLEAN_LENGTH);

    if (valOctets == NULL)
    {
        return ITS_ENOMEM;
    }

    *octets = ASN_Object_EncodeTagLengthValue((ASN_Object)object, valOctets);

    if (*octets == NULL)
    {
        ASN_Octets_Destruct(valOctets);

        return ITS_ENOMEM;
    }

    ASN_Octets_Destruct(valOctets);

    return ITS_SUCCESS;
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                     = ITS_SUCCESS;
    ASN_DescBoolean description = NULL;
    ASN_Tag tag                 = NULL;
    ASN_Length length           = NULL;
    ITS_BOOLEAN value           = ITS_FALSE;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescBoolean)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    res = ASN_Object_DecodeRemoveExtraTagLength(
                                            object,
                                            octets,
                                            decodeError);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    tag = ASN_Tag_ConstructDefault();

    if (tag == NULL)
    {
        return ITS_ENOMEM;
    }

    res = ASN_Tag_Decode(tag, octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        ASN_Tag_Destruct(tag);

        return res;
    }

    ASN_Tag_Destruct(tag);
    tag = NULL;

    length = ASN_Length_ConstructDefault();

    if (length == NULL)
    {
        return ITS_ENOMEM;
    }

    res = ASN_Length_Decode(length, octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        ASN_Length_Destruct(length);

        return res;
    }

    if (ASN_Length_GetLength(length) != ASN_BOOLEAN_LENGTH)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INVALID_BOOLEAN_LENGTH, 
                object, 
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else
    {
        byte b = 0;

        if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
        {
            *decodeError =
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_BOOLEAN_LENGTH,
                    object,
                    octets);

            ASN_Length_Destruct(length);

            return ITS_E_ASN_DECODE_ERROR;
        }

        b = ASN_Octets_GetOctetAtWithOffset(octets, 0);

        if (b == ASN_BOOLEAN_VALUE_FALSE)
        {
            value = ITS_FALSE;
        }
        else
        {
            value = ITS_TRUE;
        }

        ASN_Octets_IncrementOffsetWithIncrement(
                                            octets, 
                                            ASN_BOOLEAN_LENGTH);
    }

    ASN_Length_Destruct(length);

    ASN_BOOLEAN_VALUE(object) = value;

    /* Decode check begin. */

    /* Nothing to do. */

    /* Decode check end. */

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    return "BOOLEAN";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "BOOLEAN";
}

static char*
ToString(const ASN_Object object)
{
    char* result            = NULL;
    char* buffer            = NULL;
    const char* nameStr     = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(object != NULL);

    maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 32;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    if (ASN_BOOLEAN_VALUE(object))
    {
        sprintf(
            buffer,
            "%s (%s)\n[ TRUE ]\n",
            nameStr,
            baseNameStr);
    }
    else
    {
        sprintf(
            buffer,
            "%s (%s)\n[ FALSE ]\n",
            nameStr,
            baseNameStr);
    }

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_Boolean class record.
 */ 

ASN_Boolean_ClassRec itsASN_Boolean_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec, 
        sizeof(ASN_Boolean_ObjectRec),      
        ITS_FALSE,                          
        0,                                  
        ASN_BOOLEAN_CLASS_NAME,             
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

    /* ASN_Object class part. */

    {
        Encode,                             
        Decode,                             
        GetName,                            
        GetBaseName,                        
        ToString,                           
        ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT,
        ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT
    },

    /* ASN_Boolean class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetValue,
        SetValue,
        GetUniversalTag
    }
};


ASN_Boolean 
ASN_Boolean_ConstructDefault()
{
    ASN_Boolean result = NULL;

    result = (ASN_Boolean)ITS_ConstructObject((ITS_Class)&itsASN_Boolean_ClassRec, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Boolean 
ASN_Boolean_ConstructWithValue(ITS_BOOLEAN value)
{
    ASN_Boolean result = NULL;

    result = (ASN_Boolean)ITS_ConstructObject((ITS_Class)&itsASN_Boolean_ClassRec, value, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Boolean
ASN_Boolean_ConstructWithValueDescription(ITS_BOOLEAN value, ASN_DescBoolean description)
{
    ASN_Boolean result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_Boolean)ITS_ConstructObject((ITS_Class)&itsASN_Boolean_ClassRec, value, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Boolean_Destruct(ASN_Boolean object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Boolean 
ASN_Boolean_Clone(const ASN_Boolean object)
{
    return (ASN_Boolean)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Boolean_Equals(const ASN_Boolean object, const ASN_Boolean other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescBoolean 
ASN_Boolean_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Boolean_DestructStaticDescription()
{
    DestructStaticDescription();
}

ITS_BOOLEAN
ASN_Boolean_GetValue(const ASN_Boolean object)
{
    return ASN_BOOLEAN_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))(object);
}

void
ASN_Boolean_SetValue(ASN_Boolean object, ITS_BOOLEAN value)
{
    ASN_BOOLEAN_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))(object, value);
}

ASN_Tag 
ASN_Boolean_GetUniversalTag(const ASN_Boolean object)
{
    return ASN_BOOLEAN_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Boolean_Encode(ASN_Boolean object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Boolean_Decode(ASN_Boolean object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Boolean_GetName(const ASN_Boolean object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Boolean_GetBaseName(const ASN_Boolean object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Boolean_Print(const ASN_Boolean object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Boolean_ToString(const ASN_Boolean object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

