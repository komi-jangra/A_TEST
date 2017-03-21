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
 *  ID: $Id: asn_any.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_any.h>
#include <asn_desc_any.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_ANY_CLASS_GET_ANY(subClass) == ASN_ANY_GET_ANY_INHERIT)
    {
        ASN_ANY_CLASS_GET_ANY(subClass) =
            ASN_ANY_CLASS_GET_ANY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_SET_ANY(subClass) == ASN_ANY_SET_ANY_INHERIT)
    {
        ASN_ANY_CLASS_SET_ANY(subClass) =
            ASN_ANY_CLASS_SET_ANY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_CONTAINS(subClass) == ASN_ANY_CONTAINS_INHERIT)
    {
        ASN_ANY_CLASS_CONTAINS(subClass) =
            ASN_ANY_CLASS_CONTAINS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_CONTAINS_ANY(subClass) == ASN_ANY_CONTAINS_ANY_INHERIT)
    {
        ASN_ANY_CLASS_CONTAINS_ANY(subClass) =
            ASN_ANY_CLASS_CONTAINS_ANY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_IS_DECODED(subClass) == ASN_ANY_IS_DECODED_INHERIT)
    {
        ASN_ANY_CLASS_IS_DECODED(subClass) =
            ASN_ANY_CLASS_IS_DECODED(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_GET_DECODED_TAG(subClass) == ASN_ANY_GET_DECODED_TAG_INHERIT)
    {
        ASN_ANY_CLASS_GET_DECODED_TAG(subClass) =
            ASN_ANY_CLASS_GET_DECODED_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_GET_DECODED_LENGTH(subClass) == ASN_ANY_GET_DECODED_LENGTH_INHERIT)
    {
        ASN_ANY_CLASS_GET_DECODED_LENGTH(subClass) =
            ASN_ANY_CLASS_GET_DECODED_LENGTH(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ANY_CLASS_GET_DECODED_OCTETS(subClass) == ASN_ANY_GET_DECODED_OCTETS_INHERIT)
    {
        ASN_ANY_CLASS_GET_DECODED_OCTETS(subClass) =
            ASN_ANY_CLASS_GET_DECODED_OCTETS(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescAny GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ASN_DescAny description = NULL;

    ASN_C_REQUIRE(object != NULL);

    description = va_arg(args, ASN_DescAny);

    ASN_ANY_ANY(object)             = NULL;
    ASN_ANY_DECODED(object)         = ITS_FALSE;
    ASN_ANY_DECODED_TAG(object)     = NULL;
    ASN_ANY_DECODED_LENGTH(object)  = NULL;
    ASN_ANY_DECODED_OCTETS(object)  = NULL;

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
    ASN_C_REQUIRE(object != NULL);

    if (ASN_ANY_ANY(object) != NULL)
    {
        ASN_Object_Destruct(ASN_ANY_ANY(object));
        ASN_ANY_ANY(object) = NULL;
    }

    if (ASN_ANY_DECODED_TAG(object) != NULL)
    {
        ASN_Tag_Destruct(ASN_ANY_DECODED_TAG(object));
        ASN_ANY_DECODED_TAG(object) = NULL;
    }

    if (ASN_ANY_DECODED_LENGTH(object) != NULL)
    {
        ASN_Length_Destruct(ASN_ANY_DECODED_LENGTH(object));
        ASN_ANY_DECODED_LENGTH(object) = NULL;
    }

    if (ASN_ANY_DECODED_OCTETS(object) != NULL)
    {
        ASN_Octets_Destruct(ASN_ANY_DECODED_OCTETS(object));
        ASN_ANY_DECODED_OCTETS(object) = NULL;
    }
}

static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result           = NULL;
    ASN_Object any              = NULL;
    ASN_Tag decodedTag          = NULL;
    ASN_Length decodedLength    = NULL;
    ASN_Octets decodedOctets    = NULL;
    int res                     = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);

    result = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (result == NULL)
    {
        return result;
    }

    memcpy(result, object, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    any = ASN_ANY_ANY(object);

    if (any != NULL)
    {
        ASN_Object clonedAny = NULL;

        clonedAny = ASN_Object_Clone(any);

        ASN_C_ENSURE(clonedAny != NULL);

        if (clonedAny == NULL)
        {
            free(result);

            return NULL;
        }

        ASN_ANY_ANY(result) = clonedAny;
    }
    else
    {
        ASN_ANY_ANY(result) = NULL;
    }

    decodedTag = ASN_ANY_DECODED_TAG(object);

    if (decodedTag != NULL)
    {
        ASN_Tag clonedDecodedTag = NULL;

        clonedDecodedTag = ASN_Tag_Clone(decodedTag);

        ASN_C_ENSURE(clonedDecodedTag != NULL);

        if (clonedDecodedTag == NULL)
        {
            if (ASN_ANY_ANY(result) != NULL)
            {
                ASN_Object_Destruct(ASN_ANY_ANY(result));
                ASN_ANY_ANY(result) = NULL;
            }

            free(result);

            return NULL;
        }

        ASN_ANY_DECODED_TAG(result) = clonedDecodedTag;
    }
    else
    {
        ASN_ANY_DECODED_TAG(result) = NULL;
    }

    decodedLength = ASN_ANY_DECODED_LENGTH(object);

    if (decodedLength != NULL)
    {
        ASN_Length clonedDecodedLength = NULL;

        clonedDecodedLength = ASN_Length_Clone(decodedLength);

        ASN_C_ENSURE(clonedDecodedLength != NULL);

        if (clonedDecodedLength == NULL)
        {
            if (ASN_ANY_ANY(result) != NULL)
            {
                ASN_Object_Destruct(ASN_ANY_ANY(result));
                ASN_ANY_ANY(result) = NULL;
            }

            if (ASN_ANY_DECODED_TAG(result) != NULL)
            {
                ASN_Tag_Destruct(ASN_ANY_DECODED_TAG(result));
                ASN_ANY_DECODED_TAG(result) = NULL;
            }

            free(result);

            return NULL;
        }

        ASN_ANY_DECODED_LENGTH(result) = clonedDecodedLength;
    }
    else
    {
        ASN_ANY_DECODED_LENGTH(result) = NULL;
    }

    decodedOctets = ASN_ANY_DECODED_OCTETS(object);

    if (decodedOctets != NULL)
    {
        ASN_Octets clonedDecodedOctets = NULL;

        clonedDecodedOctets = ASN_Octets_Clone(decodedOctets);

        ASN_C_ENSURE(clonedDecodedOctets != NULL);

        if (clonedDecodedOctets == NULL)
        {
            if (ASN_ANY_ANY(result) != NULL)
            {
                ASN_Object_Destruct(ASN_ANY_ANY(result));
                ASN_ANY_ANY(result) = NULL;
            }

            if (ASN_ANY_DECODED_TAG(result) != NULL)
            {
                ASN_Tag_Destruct(ASN_ANY_DECODED_TAG(result));
                ASN_ANY_DECODED_TAG(result) = NULL;
            }

            if (ASN_ANY_DECODED_LENGTH(result) != NULL)
            {
                ASN_Length_Destruct(ASN_ANY_DECODED_LENGTH(result));
                ASN_ANY_DECODED_LENGTH(result) = NULL;
            }

            free(result);

            return NULL;
        }

        ASN_ANY_DECODED_OCTETS(result) = clonedDecodedOctets;
    }
    else
    {
        ASN_ANY_DECODED_OCTETS(result) = NULL;
    }

    return result;
}

static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    ASN_Tag decodedTag              = NULL;
    ASN_Tag otherDecodedTag         = NULL;
    ASN_Length decodedLength        = NULL;
    ASN_Length otherDecodedLength   = NULL;
    ASN_Octets decodedOctets        = NULL;
    ASN_Octets otherDecodedOctets   = NULL;
    ASN_Object any                  = NULL;
    ASN_Object otherAny             = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(other != NULL);

    if (ITS_OBJ_CLASS(object) != ITS_OBJ_CLASS(other))
    {
        return ITS_FALSE;
    }

    if (ASN_ANY_DECODED(object) != ASN_ANY_DECODED(other))
    {
        return ITS_FALSE;
    }

    decodedTag      = ASN_ANY_DECODED_TAG(object);
    otherDecodedTag = ASN_ANY_DECODED_TAG(other);

    if (decodedTag == NULL && otherDecodedTag != NULL)
    {
        return ITS_FALSE;
    }
    else if (decodedTag != NULL && otherDecodedTag == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        if (!ASN_Tag_Equals(decodedTag, otherDecodedTag))
        {
            return ITS_FALSE;
        }
    }

    decodedLength       = ASN_ANY_DECODED_LENGTH(object);
    otherDecodedLength  = ASN_ANY_DECODED_LENGTH(other);

    if (decodedLength == NULL && otherDecodedLength != NULL)
    {
        return ITS_FALSE;
    }
    else if (decodedLength != NULL && otherDecodedLength == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        if (!ASN_Length_Equals(decodedLength, otherDecodedLength))
        {
            return ITS_FALSE;
        }
    }

    decodedOctets       = ASN_ANY_DECODED_OCTETS(object);
    otherDecodedOctets  = ASN_ANY_DECODED_OCTETS(other);

    if (decodedOctets == NULL && otherDecodedOctets != NULL)
    {
        return ITS_FALSE;
    }
    else if (decodedOctets != NULL && otherDecodedOctets == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        if (!ASN_Octets_Equals(decodedOctets, otherDecodedOctets))
        {
            return ITS_FALSE;
        }
    }

    any      = ASN_ANY_ANY(object);
    otherAny = ASN_ANY_ANY(other);

    if (any == NULL && otherAny == NULL)
    {
        return ITS_TRUE;
    }
    else if (any == NULL && otherAny != NULL)
    {
        return ITS_FALSE;
    }
    else if (any != NULL && otherAny == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        return ASN_Object_Equals(any, otherAny);
    }
}

static ASN_DescAny staticDescription = NULL;

static ASN_DescAny
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescAny result       = NULL;
    ASN_Any cloneForFactory         = NULL;

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

        staticDescription = ASN_DescAny_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Any_ConstructWithDescription(staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescAny_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescAny_SetCloneForFactory(staticDescription, cloneForFactory);

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
        ASN_DescAny_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN ContainsAny(const ASN_Any object);

static const ASN_Object
GetAny(const ASN_Any object)
{
    ASN_Object result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ContainsAny(object));

    result = ASN_ANY_ANY(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void
SetAny(ASN_Any object, ASN_Object any)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(any != NULL);

    if (ASN_ANY_ANY(object) != NULL)
    {
        ASN_Object_Destruct(ASN_ANY_ANY(object));
        ASN_ANY_ANY(object) = NULL;
    }

    ASN_ANY_ANY(object) = any;

    ASN_ANY_DECODED(object) = ITS_FALSE;
}

static ITS_BOOLEAN 
Contains(const ASN_Any object, const ASN_Tag tag)
{
    ASN_Object any                   = NULL;
    ASN_DescObject anyDescription    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    any = ASN_ANY_ANY(object);

    if (any == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        anyDescription = ASN_OBJECT_DESCRIPTION(any);

        ASN_C_ASSERT(anyDescription != NULL);

        if (ASN_DescObject_TagIdentify(anyDescription, tag))
        {
            return ITS_TRUE;
        }
        else
        {
            return ITS_FALSE;
        }
    }
}

static ITS_BOOLEAN
ContainsAny(const ASN_Any object)
{
    ASN_Object any = NULL;

    ASN_C_REQUIRE(object != NULL);

    any = ASN_ANY_ANY(object);

    return any != NULL;
}

static ITS_BOOLEAN 
IsDecoded(const ASN_Any object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_ANY_DECODED(object);
}

static const ASN_Tag 
GetDecodedTag(const ASN_Any object)
{
    ASN_Tag result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsDecoded(object));

    result = ASN_ANY_DECODED_TAG(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static const ASN_Length 
GetDecodedLength(const ASN_Any object)
{
    ASN_Length result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsDecoded(object));

    result = ASN_ANY_DECODED_LENGTH(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static const ASN_Octets 
GetDecodedOctets(const ASN_Any object)
{
    ASN_Octets result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsDecoded(object));

    result = ASN_ANY_DECODED_OCTETS(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescAny description = NULL;

    ASN_Object any          = NULL;
    ASN_Octets anyOctets    = NULL;
    int res                 = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescAny)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    if (ASN_ANY_DECODED(object) == ITS_TRUE)
    {
        /* Special case if ANY already decoded: just re-encode. */

        anyOctets = ASN_Octets_ConstructDefault();

        if (anyOctets == NULL)
        {
            return ITS_ENOMEM;
        }

        res = ASN_Octets_Append(anyOctets, ASN_ANY_DECODED_OCTETS(object));

        if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(anyOctets);

            return res;
        }
    }
    else
    {
        /* Standard case. */

        any = ASN_ANY_ANY(object);

        /* Encode check begin. */

        if (any == NULL)
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_NO_ANY_PRESENT,
                    object);

            return ITS_E_ASN_ENCODE_ERROR;
        }

        ASN_C_ASSERT(any != NULL);

        /* Encode check end. */

        res = ASN_Object_Encode(any, &anyOctets, encodeError);

        if (res != ITS_SUCCESS)
        {
            return res;
        }
    }

    ASN_C_ASSERT(anyOctets != NULL);

    ASN_C_ASSERT(ASN_DescAny_TagLevelNumber(description) >= 1);

    if (ASN_DescAny_TagLevelNumber(description) == 1)
    {
        *octets = anyOctets;

        return ITS_SUCCESS;
    }
    else
    {
        /*
         *  Next call is valid since ASN.1 Object description 
         *  tag stack is used (contains one or more tags as 
         *  ASN_DescAny_TagLevelNumber(description) >= 2).
         */

        *octets = ASN_Object_EncodeTagLengthValue(object, anyOctets);

        if (*octets == NULL)
        {
            ASN_Octets_Destruct(anyOctets);

            return ITS_ENOMEM;
        }

        ASN_Octets_Destruct(anyOctets);

        return ITS_SUCCESS;
    }
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                     = ITS_SUCCESS;
    ASN_DescAny description     = NULL;
    size_t offsetBeforeTag      = 0;
    size_t offsetAfterTag       = 0;
    size_t offsetBeforeLength   = 0;
    size_t offsetAfterLength    = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescAny)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    ASN_C_ASSERT(ASN_DescAny_TagLevelNumber(description) >= 1);

    res = ASN_Object_DecodeRemoveExtraTagLength(
                                            object,
                                            octets,
                                            decodeError);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    if (ASN_ANY_DECODED_TAG(object) != NULL)
    {
        ASN_Tag_Destruct(ASN_ANY_DECODED_TAG(object));
        ASN_ANY_DECODED_TAG(object) = NULL;
    }

    if (ASN_ANY_DECODED_LENGTH(object) != NULL)
    {
        ASN_Length_Destruct(ASN_ANY_DECODED_LENGTH(object));
        ASN_ANY_DECODED_LENGTH(object) = NULL;
    }

    if (ASN_ANY_DECODED_OCTETS(object) != NULL)
    {
        ASN_Octets_Destruct(ASN_ANY_DECODED_OCTETS(object));
        ASN_ANY_DECODED_OCTETS(object) = NULL;
    }

    ASN_ANY_DECODED_TAG(object) = ASN_Tag_ConstructDefault();

    if (ASN_ANY_DECODED_TAG(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    offsetBeforeTag = ASN_Octets_GetOffset(octets);

    res = ASN_Tag_Decode(ASN_ANY_DECODED_TAG(object), octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    offsetAfterTag = offsetBeforeLength = ASN_Octets_GetOffset(octets);

    ASN_ANY_DECODED_LENGTH(object) = ASN_Length_ConstructDefault();

    if (ASN_ANY_DECODED_LENGTH(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    res = ASN_Length_Decode(ASN_ANY_DECODED_LENGTH(object), octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        return res;
    }
    
    offsetAfterLength = ASN_Octets_GetOffset(octets);

    if (ASN_Length_IsIndefinite(ASN_ANY_DECODED_LENGTH(object)))
    {
        *decodeError =
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INDEFINITE_ANY_LENGTH,
                object,
                octets);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else
    {
        ITS_LONG length = ASN_Length_GetLength(ASN_ANY_DECODED_LENGTH(object));

        ITS_OCTET* array            = NULL;
        size_t arraySize            = 0;
        int i                       = 0;
        ITS_OCTET* tagLengthArray   = NULL;
        ASN_Octets valOctets        = NULL;

        ASN_C_ASSERT(length >= 0);

        arraySize = (size_t)length;

        array = (ITS_OCTET*)calloc(arraySize, sizeof(ITS_OCTET));

        if (array == NULL)
        {
            return ITS_ENOMEM;
        }

        for (i = 0; i < length; i++)
        {
            byte b = 0;

            if (!ASN_Octets_IsIndexWithOffsetValid(octets, i))
            {
                *decodeError = 
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_INVALID_ANY_LENGTH,
                        object,
                        octets);

                free(array);
                
                return ITS_E_ASN_DECODE_ERROR;
            }

            b = ASN_Octets_GetOctetAtWithOffset(octets, i);

            array[i] = b;
        }

        ASN_C_ASSERT((int)offsetAfterTag - (int)offsetBeforeTag >= 1);
        ASN_C_ASSERT((int)offsetAfterLength - (int)offsetBeforeLength >= 1);

        tagLengthArray = (ITS_OCTET*)calloc(offsetAfterLength - offsetBeforeTag, sizeof(ITS_OCTET));

        if (tagLengthArray == NULL)
        {
            free(array);

            return ITS_ENOMEM;
        }

        for (i = 0; i < (int)(offsetAfterLength - offsetBeforeTag); i++)
        {
            tagLengthArray[i] = ASN_Octets_GetOctetAt(octets, (size_t)i + offsetBeforeTag);
        }

        ASN_ANY_DECODED_OCTETS(object) = 
            ASN_Octets_ConstructWithArray(
                                tagLengthArray, 
                                offsetAfterLength - offsetBeforeTag);

        if (ASN_ANY_DECODED_OCTETS(object) == NULL)
        {
            free(array);
            free(tagLengthArray);

            return ITS_ENOMEM;
        }

        if (arraySize == 0)
        {
            valOctets = ASN_Octets_ConstructDefault();
        }
        else
        {
            valOctets = ASN_Octets_ConstructWithArray(array, arraySize);
        }

        if (valOctets == NULL)
        {
            free(array);
            free(tagLengthArray);

            return ITS_ENOMEM;
        }

        res = ASN_Octets_Append(ASN_ANY_DECODED_OCTETS(object), valOctets);

        if (res != ITS_SUCCESS)
        {
            free(array);
            free(tagLengthArray);

            return res;
        }

        free(array);
        free(tagLengthArray);

        ASN_Octets_IncrementOffsetWithIncrement(octets, length);
    }

    ASN_ANY_DECODED(object) = ITS_TRUE;

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    return "ANY";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "ANY";
}

static char*
ToString(const ASN_Object object)
{
    char* result                = NULL;
    char* buffer                = NULL;
    const char* nameStr         = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr     = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);
    char* toString              = NULL;
    char* toStringLineShifted   = NULL;
    size_t maxStringSize        = 0;
    ASN_Object any              = NULL;
    ITS_BOOLEAN decoded         = ITS_FALSE;
    ASN_Octets decodedOctets    = NULL;

    ASN_C_REQUIRE(object != NULL);

    maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 32;

    any             = ASN_ANY_ANY(object);
    decoded         = ASN_ANY_DECODED(object);
    decodedOctets   = ASN_ANY_DECODED_OCTETS(object);

    if (any != NULL)
    {
        toString = ASN_Object_ToString(any);

        if (toString == NULL)
        {
            return NULL;
        }

        toStringLineShifted = ASN_AddLineShift(toString);

        if (toStringLineShifted == NULL)
        {
            free(toString);
            return NULL;
        }

        free(toString);
        toString = NULL;

        maxStringSize += strlen(toStringLineShifted);
    }
    else
    {
        if (decoded && decodedOctets != NULL)
        {
            toString = ASN_Octets_ToString(decodedOctets);

            if (toString == NULL)
            {
                return NULL;
            }

            toStringLineShifted = ASN_AddLineShift(toString);

            if (toStringLineShifted == NULL)
            {
                free(toString);
                return NULL;
            }

            free(toString);
            toString = NULL;

            maxStringSize += strlen(toStringLineShifted);
        }
        else
        {
            maxStringSize += 0;
        }
    }

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        if (toStringLineShifted != NULL)
        {
            free(toStringLineShifted);
            toStringLineShifted = NULL;
        }

        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "%s (%s)\n{\n",
        nameStr,
        baseNameStr);

    if (toStringLineShifted != NULL)
    {
        strcat(buffer, toStringLineShifted);
    }
    else
    {
        strcat(buffer, "\n");
    }

    strcat(buffer, "}\n");

    if (toStringLineShifted != NULL)
    {
        free(toStringLineShifted);
        toStringLineShifted = NULL;
    }

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ASSERT(result != NULL);

    return result;
}

/*
 *  ASN_Any class record.
 */ 

ASN_Any_ClassRec itsASN_Any_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,
        sizeof(ASN_Any_ObjectRec),    
        ITS_FALSE,                         
        0,                                 
        ASN_ANY_CLASS_NAME,           
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

    /* ASN_Any class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetAny,
        SetAny,
        Contains,
        ContainsAny,
        IsDecoded,
        GetDecodedTag,
        GetDecodedLength,
        GetDecodedOctets
    }
};

ASN_Any 
ASN_Any_ConstructDefault()
{
    ASN_Any result = NULL;

    result = (ASN_Any)ITS_ConstructObject((ITS_Class)&itsASN_Any_ClassRec, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Any 
ASN_Any_ConstructWithDescription(ASN_DescAny description)
{
    ASN_Any result = NULL;

    result = (ASN_Any)ITS_ConstructObject((ITS_Class)&itsASN_Any_ClassRec, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Any_Destruct(ASN_Any object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Any 
ASN_Any_Clone(const ASN_Any object)
{
    return (ASN_Any)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Any_Equals(const ASN_Any object, const ASN_Any other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescAny 
ASN_Any_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Any_DestructStaticDescription()
{
    DestructStaticDescription();
}

const ASN_Object
ASN_Any_GetAny(const ASN_Any object)
{
    return ASN_ANY_CLASS_GET_ANY(ITS_OBJ_CLASS(object))(object);
}

void
ASN_Any_SetAny(ASN_Any object, ASN_Object any)
{
    ASN_ANY_CLASS_SET_ANY(ITS_OBJ_CLASS(object))(object, any);
}

ITS_BOOLEAN
ASN_Any_Contains(const ASN_Any object, const ASN_Tag tag)
{
    return ASN_ANY_CLASS_CONTAINS(ITS_OBJ_CLASS(object))(object, tag);
}

ITS_BOOLEAN
ASN_Any_ContainsAny(const ASN_Any object)
{
    return ASN_ANY_CLASS_CONTAINS_ANY(ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_Any_IsDecoded(const ASN_Any object)
{
    return ASN_ANY_CLASS_IS_DECODED(ITS_OBJ_CLASS(object))(object);
}

const ASN_Tag 
ASN_Any_GetDecodedTag(const ASN_Any object)
{
    return ASN_ANY_CLASS_GET_DECODED_TAG(ITS_OBJ_CLASS(object))(object);
}

const ASN_Length 
ASN_Any_GetDecodedLength(const ASN_Any object)
{
    return ASN_ANY_CLASS_GET_DECODED_LENGTH(ITS_OBJ_CLASS(object))(object);
}

const ASN_Octets 
ASN_Any_GetDecodedOctets(const ASN_Any object)
{
    return ASN_ANY_CLASS_GET_DECODED_OCTETS(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Any_Encode(ASN_Any object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Any_Decode(ASN_Any object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Any_GetName(const ASN_Any object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Any_GetBaseName(const ASN_Any object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Any_Print(const ASN_Any object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Any_ToString(const ASN_Any object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



