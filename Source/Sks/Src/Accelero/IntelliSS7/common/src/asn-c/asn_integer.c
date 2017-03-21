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
 *  ID: $Id: asn_integer.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_integer.h>
#include <asn_desc_integer.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_INTEGER_CLASS_GET_VALUE(subClass) == ASN_INTEGER_GET_VALUE_INHERIT)
    {
        ASN_INTEGER_CLASS_GET_VALUE(subClass) =
            ASN_INTEGER_CLASS_GET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_INTEGER_CLASS_SET_VALUE(subClass) == ASN_INTEGER_SET_VALUE_INHERIT)
    {
        ASN_INTEGER_CLASS_SET_VALUE(subClass) =
            ASN_INTEGER_CLASS_SET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_INTEGER_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_INTEGER_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_INTEGER_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_INTEGER_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescInteger GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ITS_LONG value              = 0;
    ASN_DescInteger description = NULL;

    value = va_arg(args, ITS_LONG);

    description = va_arg(args, ASN_DescInteger);

    ASN_INTEGER_VALUE(object) = value;

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

    if (ASN_INTEGER_VALUE(object) != ASN_INTEGER_VALUE(other))
    {
        return ITS_FALSE;
    }

    return ITS_TRUE;
}

static ASN_DescInteger staticDescription = NULL;

static ASN_DescInteger
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescInteger result   = NULL;
    ASN_Integer cloneForFactory     = NULL;
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

        staticDescription = ASN_DescInteger_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Integer_ConstructWithValueDescription(0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescInteger_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescInteger_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_Integer_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescInteger_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescInteger_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescInteger_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static ITS_LONG
GetValue(const ASN_Integer object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_INTEGER_VALUE(object);
}

static void 
SetValue(ASN_Integer object, ITS_LONG value)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_INTEGER_VALUE(object) = value;
}

static ASN_Tag
GetUniversalTag(const ASN_Integer object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_INTEGER);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescInteger description = NULL;

    ITS_OCTET array[ASN_BYTES_PER_LONG];

    ITS_LONG value          = 0;
    int inc                 = 0;
    ITS_BOOLEAN maxShrink   = ITS_FALSE;
    int j                   = 0;
    ASN_Octets valOctets    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescInteger)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    memset(array, 0x00U, ASN_BYTES_PER_LONG);

    value = ASN_INTEGER_VALUE(object);

    /* Encode check begin. */

    if (ASN_DescInteger_IsClauseRange(description))
    {
        if (value > ASN_DescInteger_GetMaxValue(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INTEGER_VALUE_OUT_OF_RANGE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
        
        if (value < ASN_DescInteger_GetMinValue(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INTEGER_VALUE_OUT_OF_RANGE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
    }

    /* Encode check end. */

    for (j = 0; j < ASN_BYTES_PER_LONG; j++)
    {
        if (!maxShrink && j < ASN_BYTES_PER_LONG - 1)
        {
            byte curr    = (byte)((value >> ((ASN_BYTES_PER_LONG - j - 1) *
                                   ASN_BITS_PER_BYTE)) & ASN_ALL_BITS_SET);

            byte next    = (byte)((value >> ((ASN_BYTES_PER_LONG - j - 2) *
                                   ASN_BITS_PER_BYTE)) & ASN_ALL_BITS_SET);

            if ((curr == 0 && (next & ASN_SIGN_BIT) == 0) ||
                (curr == ASN_ALL_BITS_SET && (next & ASN_SIGN_BIT) != 0 ))
            {
                continue;
            }
            else
            {
                maxShrink = ITS_TRUE;
            }
        }

        array[inc] = (byte)((value >> ((ASN_BYTES_PER_LONG - j - 1) *
                             ASN_BITS_PER_BYTE)) & ASN_ALL_BITS_SET);

        inc++;
    }

    valOctets = ASN_Octets_ConstructWithArray(array, inc);

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
    ASN_DescInteger description = NULL;
    ASN_Tag tag                 = NULL;
    ASN_Length length           = NULL;
    ITS_LONG value              = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescInteger)ASN_OBJECT_DESCRIPTION(object);

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

    if (ASN_Length_IsIndefinite(length))
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INDEFINITE_LENGTH, 
                object, 
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else if (ASN_Length_GetLength(length) == 0)
    {
        *decodeError =
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_NULL_INTEGER_LENGTH,
                object,
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else
    {
        int i = 0;
        byte b = 0;

        if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
        {
            *decodeError =
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_INTEGER_LENGTH,
                    object,
                    octets);

            ASN_Length_Destruct(length);

            return ITS_E_ASN_DECODE_ERROR;
        }

        b = ASN_Octets_GetOctetAtWithOffset(octets, 0);

        if ((b & ASN_SIGN_BIT) != 0)
        {
            value = -1;
        }
        else
        {
            value = 0;
        }

        for (i = 0; i < ASN_Length_GetLength(length); i++)
        {
            if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
            {
                *decodeError =
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_INVALID_INTEGER_LENGTH,
                        object,
                        octets);

                ASN_Length_Destruct(length);

                return ITS_E_ASN_DECODE_ERROR;
            }

            value <<= ASN_BITS_PER_BYTE;
            value &= ~ASN_ALL_BITS_SET | ~ASN_BYTE_MASK_IN_LONG;
            value |= ASN_Octets_GetOctetAtWithOffset(octets, i) & 
                                                    ASN_BYTE_MASK_IN_LONG;
        }

        ASN_Octets_IncrementOffsetWithIncrement(
                                            octets, 
                                            ASN_Length_GetLength(length));
    }

    ASN_Length_Destruct(length);

    ASN_INTEGER_VALUE(object) = value;

    /* Decode check begin. */

    if (ASN_DescInteger_IsClauseRange(description))
    {
        if (value > ASN_DescInteger_GetMaxValue(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INTEGER_VALUE_OUT_OF_RANGE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
        
        if (value < ASN_DescInteger_GetMinValue(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INTEGER_VALUE_OUT_OF_RANGE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
    }

    /* Decode check end. */

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    return "INTEGER";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "INTEGER";
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

    sprintf(
        buffer,
        "%s (%s)\n[ %ld ]\n",
        nameStr,
        baseNameStr,
        ASN_INTEGER_VALUE(object));

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_Integer class record.
 */ 

ASN_Integer_ClassRec itsASN_Integer_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec, /* ASN_Object is superclass.    */
        sizeof(ASN_Integer_ObjectRec),      /* Size of instance.            */
        ITS_FALSE,                          /* Not initted.                 */
        0,                                  /* Initial reference count.     */
        ASN_INTEGER_CLASS_NAME,             /* Class name.                  */
        ITS_CLASS_NO_INIT,                 
        ITS_CLASS_NO_DEST,  
        ClassPartConstruct,                 /* Class part initialize.       */
        ClassPartDestruct,                  /* Class part destroy.          */
        Construct,                          /* Initialize.                  */
        Destruct,                           /* Destroy.                     */
        Clone,                              /* Clone.                       */
        ITS_INST_PRINT_INHERIT,             /* Inherit print.               */
        ITS_INST_SERIAL_INHERIT,            /* Inherit serial.              */
        Equals,                             /* Equals.                      */
        ITS_INST_HASH_INHERIT,              /* Inherit equals.              */
        NULL                                /* No extension.                */
    },

    /* ASN_Object class part. */

    {
        Encode,                                     /* Encode.      */
        Decode,                                     /* Decode.      */
        GetName,                                    /* GetName.     */
        GetBaseName,                                /* GetBaseName. */
        ToString,                                   /* ToString.    */
        ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT,
        ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT
    },

    /* ASN_Integer class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetValue,
        SetValue,
        GetUniversalTag
    }
};


ASN_Integer 
ASN_Integer_ConstructDefault()
{
    ASN_Integer result = NULL;

    result = (ASN_Integer)ITS_ConstructObject((ITS_Class)&itsASN_Integer_ClassRec, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Integer 
ASN_Integer_ConstructWithValue(ITS_LONG value)
{
    ASN_Integer result = NULL;

    result = (ASN_Integer)ITS_ConstructObject((ITS_Class)&itsASN_Integer_ClassRec, value, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Integer
ASN_Integer_ConstructWithValueDescription(ITS_LONG value, ASN_DescInteger description)
{
    ASN_Integer result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_Integer)ITS_ConstructObject((ITS_Class)&itsASN_Integer_ClassRec, value, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Integer_Destruct(ASN_Integer object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Integer 
ASN_Integer_Clone(const ASN_Integer object)
{
    return (ASN_Integer)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Integer_Equals(const ASN_Integer object, const ASN_Integer other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescInteger 
ASN_Integer_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Integer_DestructStaticDescription()
{
    DestructStaticDescription();
}

ITS_LONG
ASN_Integer_GetValue(const ASN_Integer object)
{
    return ASN_INTEGER_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))(object);
}

void
ASN_Integer_SetValue(ASN_Integer object, ITS_LONG value)
{
    ASN_INTEGER_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))(object, value);
}

ASN_Tag 
ASN_Integer_GetUniversalTag(const ASN_Integer object)
{
    return ASN_INTEGER_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Integer_Encode(ASN_Integer object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Integer_Decode(ASN_Integer object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Integer_GetName(const ASN_Integer object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Integer_GetBaseName(const ASN_Integer object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Integer_Print(const ASN_Integer object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Integer_ToString(const ASN_Integer object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

