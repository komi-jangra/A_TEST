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
 *  ID: $Id: asn_bit_string.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_bit_string.h>
#include <asn_desc_bit_string.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_BIT_STRING_CLASS_GET_ARRAY(subClass) == ASN_BIT_STRING_GET_ARRAY_INHERIT)
    {
        ASN_BIT_STRING_CLASS_GET_ARRAY(subClass) =
            ASN_BIT_STRING_CLASS_GET_ARRAY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_SET_ARRAY(subClass) == ASN_BIT_STRING_SET_ARRAY_INHERIT)
    {
        ASN_BIT_STRING_CLASS_SET_ARRAY(subClass) =
            ASN_BIT_STRING_CLASS_SET_ARRAY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_GET_SIZE(subClass) == ASN_BIT_STRING_GET_SIZE_INHERIT)
    {
        ASN_BIT_STRING_CLASS_GET_SIZE(subClass) =
            ASN_BIT_STRING_CLASS_GET_SIZE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_SET(subClass) == ASN_BIT_STRING_SET_INHERIT)
    {
        ASN_BIT_STRING_CLASS_SET(subClass) =
            ASN_BIT_STRING_CLASS_SET(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_RESET(subClass) == ASN_BIT_STRING_RESET_INHERIT)
    {
        ASN_BIT_STRING_CLASS_RESET(subClass) =
            ASN_BIT_STRING_CLASS_RESET(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_IS_SET(subClass) == ASN_BIT_STRING_IS_SET_INHERIT)
    {
        ASN_BIT_STRING_CLASS_IS_SET(subClass) =
            ASN_BIT_STRING_CLASS_IS_SET(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_IS_DEFINED(subClass) == ASN_BIT_STRING_IS_DEFINED_INHERIT)
    {
        ASN_BIT_STRING_CLASS_IS_DEFINED(subClass) =
            ASN_BIT_STRING_CLASS_IS_DEFINED(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_SET_ALL(subClass) == ASN_BIT_STRING_SET_ALL_INHERIT)
    {
        ASN_BIT_STRING_CLASS_SET_ALL(subClass) =
            ASN_BIT_STRING_CLASS_SET_ALL(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_RESET_ALL(subClass) == ASN_BIT_STRING_RESET_ALL_INHERIT)
    {
        ASN_BIT_STRING_CLASS_RESET_ALL(subClass) =
            ASN_BIT_STRING_CLASS_RESET_ALL(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_BIT_STRING_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_BIT_STRING_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_BIT_STRING_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_BIT_STRING_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescBitString GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ITS_BOOLEAN* array              = NULL;
    size_t size                     = 0;
    ASN_DescBitString description   = NULL;

    array = va_arg(args, ITS_BOOLEAN*);
    size = va_arg(args, size_t);

    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    description = va_arg(args, ASN_DescBitString);

    if (array != NULL && size != 0)
    {
        ASN_BIT_STRING_DATA(object) = (ITS_BOOLEAN*)calloc(size, sizeof(ITS_BOOLEAN));

        ASN_C_ENSURE(ASN_BIT_STRING_DATA(object) != NULL);

        if (ASN_BIT_STRING_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_BIT_STRING_DATA(object), array, size * sizeof (ITS_BOOLEAN));
        ASN_BIT_STRING_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_BIT_STRING_DATA(object) = NULL;
        ASN_BIT_STRING_SIZE(object) = 0;
    }

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            if (ASN_BIT_STRING_DATA(object) != NULL)
            {
                free(ASN_BIT_STRING_DATA(object));
                ASN_BIT_STRING_DATA(object) = NULL;
            }

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

    if (ASN_BIT_STRING_DATA(object) != NULL)
    {
        free(ASN_BIT_STRING_DATA(object));
        ASN_BIT_STRING_DATA(object) = NULL;
    }
}


static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result   = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (result == NULL)
    {
        return result;
    }

    memcpy(result, object, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (ASN_BIT_STRING_SIZE(object) > 0)
    {
        ASN_BIT_STRING_DATA(result) = (ITS_BOOLEAN*)calloc(ASN_BIT_STRING_SIZE(object), sizeof(ITS_BOOLEAN));

        ASN_C_ENSURE(ASN_BIT_STRING_DATA(result) != NULL);

        if (ASN_BIT_STRING_DATA(result) == NULL)
        {
            free(result);

            return NULL;
        }

        memcpy(ASN_BIT_STRING_DATA(result), ASN_BIT_STRING_DATA(object), ASN_BIT_STRING_SIZE(object));
    }
    else
    {
        /* Nothing to do. */
    }

    return result;
}


static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    if (ITS_OBJ_CLASS(object) != ITS_OBJ_CLASS(other))
    {
        return ITS_FALSE;
    }

    if (ASN_BIT_STRING_SIZE(object) != ASN_BIT_STRING_SIZE(other))
    {
        return ITS_FALSE;
    }

    if (memcmp(
            ASN_BIT_STRING_DATA(object),
            ASN_BIT_STRING_DATA(other),
            ASN_BIT_STRING_SIZE(object)) == 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ASN_DescBitString staticDescription = NULL;

static ASN_DescBitString
GetStaticDescription()
{
    static ITS_BOOLEAN initialized    = ITS_FALSE;
    static ASN_DescBitString result   = NULL;
    ASN_BitString cloneForFactory     = NULL;
    ASN_Tag universalTag              = NULL;

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

        staticDescription = ASN_DescBitString_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_BitString_ConstructWithArraySizeDescription(NULL, 0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescBitString_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescBitString_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_BitString_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescBitString_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescBitString_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescBitString_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static const ITS_BOOLEAN* 
GetArray(const ASN_BitString object)
{
    const ITS_BOOLEAN* result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_BIT_STRING_SIZE(object) > 0);

    result = ASN_BIT_STRING_DATA(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static size_t 
GetSize(const ASN_BitString object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_BIT_STRING_SIZE(object);
}

static int 
SetArray(ASN_BitString object, const ITS_BOOLEAN* array, size_t size)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    if (ASN_BIT_STRING_DATA(object) != NULL)
    {
        free(ASN_BIT_STRING_DATA(object));
        ASN_BIT_STRING_DATA(object) = NULL;
    }

    if (array != NULL && size != 0)
    {
        ASN_BIT_STRING_DATA(object) = (ITS_BOOLEAN*)calloc(size, sizeof(ITS_BOOLEAN));

        ASN_C_ENSURE(ASN_BIT_STRING_DATA(object) != NULL);

        if (ASN_BIT_STRING_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_BIT_STRING_DATA(object), array, size * sizeof (ITS_BOOLEAN));
        ASN_BIT_STRING_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_BIT_STRING_DATA(object) = NULL;
        ASN_BIT_STRING_SIZE(object) = 0;
    }

    return ITS_SUCCESS;
}

static void 
Set(ASN_BitString object, size_t index, ITS_BOOLEAN value)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    ASN_BIT_STRING_DATA(object)[index] = value;
}

static void 
Reset(ASN_BitString object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    ASN_BIT_STRING_DATA(object)[index] = ITS_FALSE;
}

static ITS_BOOLEAN 
IsSet(const ASN_BitString object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    return ASN_BIT_STRING_DATA(object)[index] == ITS_TRUE;
}

static ITS_BOOLEAN 
IsDefined(const ASN_BitString object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);

    return index < GetSize(object);
}

static void 
SetAll(ASN_BitString object)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);

    for (i = 0; i < (int)ASN_BIT_STRING_SIZE(object); i++)
    {
        ASN_BIT_STRING_DATA(object)[i] = ITS_TRUE;
    }
}

static void 
ResetAll(ASN_BitString object)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);

    for (i = 0; i < (int)ASN_BIT_STRING_SIZE(object); i++)
    {
        ASN_BIT_STRING_DATA(object)[i] = ITS_FALSE;
    }
}

static ASN_Tag
GetUniversalTag(const ASN_BitString object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_BIT_STRING);
}

/*
 *  Helper functions (conversion) for encode and decode.
 */

static void
BooleanArrayToBits(const ITS_BOOLEAN* booleanArray, /* in       */
                   size_t booleanArraySize,         /* in       */
                   size_t* numberOfBits,            /* out      */
                   ITS_OCTET* octetArray,           /* in-out   */
                   size_t* octetArraySize)          /* in-out   */
{
    typedef ITS_OCTET byte;

    size_t numberOfBytes    = 0;
    size_t n                = 0;
    int i                   = 0;
    int j                   = 0;

    ASN_C_REQUIRE(booleanArray != NULL);
    ASN_C_REQUIRE(numberOfBits != NULL);
    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(octetArraySize != NULL);
    ASN_C_REQUIRE((*octetArraySize) >= booleanArraySize / ASN_BITS_PER_BYTE + 1);

    memset(octetArray, 0, (*octetArraySize) * sizeof(ITS_OCTET));

    *numberOfBits = booleanArraySize;

    numberOfBytes = (*numberOfBits) / ASN_BITS_PER_BYTE;

    if ((*numberOfBits) % ASN_BITS_PER_BYTE > 0)
    {
        numberOfBytes += 1;
    }

    ASN_C_ASSERT((*octetArraySize) >= numberOfBytes);

    (*octetArraySize) = numberOfBytes;

    n = 0; /* Bit number starting from zero. */

    for (i = 0; i < (int)numberOfBytes; i++)
    {
        byte b = 0x00U;

        for (j = ASN_BITS_PER_BYTE - 1; j >= 0; j--)
        {
            if (booleanArray[n])
            {
                b |= 0x01U << j;
            }

            n++;

            if (n >= *numberOfBits)
            { 
                break;
            }
        }

        octetArray[i] = b;
    }
}

static void
BitsToBooleanArray(size_t numberOfBits,         /* in       */
                   const ITS_OCTET* octetArray, /* in       */
                   size_t octetArraySize,       /* in       */
                   ITS_BOOLEAN* booleanArray,   /* in-out   */
                   size_t* booleanArraySize)    /* in-out   */
{
    typedef ITS_OCTET byte;

    size_t requiredNumberOfBytes    = 0;
    size_t n                        = 0;
    int i                           = 0;
    int j                           = 0;
    int k                           = 0;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(booleanArray != NULL);
    ASN_C_REQUIRE(booleanArraySize != NULL);
    ASN_C_REQUIRE((*booleanArraySize) >= octetArraySize * ASN_BITS_PER_BYTE + 1);

    requiredNumberOfBytes = numberOfBits / ASN_BITS_PER_BYTE;

    if (numberOfBits % ASN_BITS_PER_BYTE > 0)
    {
        requiredNumberOfBytes += 1;
    }

    ASN_C_REQUIRE(octetArraySize == requiredNumberOfBytes);

    memset(booleanArray, 0, (*booleanArraySize) * sizeof(ITS_BOOLEAN));

    n = 0; /* Bit number starting from zero. */

    k = 0;

    for (i = 0; i < (int)octetArraySize; i++)
    {
        byte b = octetArray[i];

        for (j = ASN_BITS_PER_BYTE - 1; j >= 0; j--)
        {
            if ((b & (0x01U << j)) != 0x00U)
            {
                booleanArray[k++] = ITS_TRUE;
            }
            else
            {
                booleanArray[k++] = ITS_FALSE;
            }

            n++;

            if (n >= numberOfBits)
            {
                break;
            }
        }
    }

    ASN_C_ENSURE((k - 1) < (int)(*booleanArraySize));

    *booleanArraySize = numberOfBits;
}
    
static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescBitString description = NULL;

    ITS_BOOLEAN* data               = NULL;
    size_t size                     = 0;
    size_t numberOfBits             = 0;
    long finalOctetUnusedBits       = 0;
    ITS_OCTET* octetArray           = NULL;
    size_t octetArraySize           = 0;
    size_t octetArraySizeMinusOne   = 0;
    ASN_Octets valOctets            = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescBitString)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    data = ASN_BIT_STRING_DATA(object);
    size = ASN_BIT_STRING_SIZE(object);

    ASN_C_ASSERT((data == NULL && size == 0) || (data != NULL && size != 0))

    /* Encode check begin. */

    if (ASN_DescBitString_IsClauseSize(description) &&
        !ASN_Options_GlobalIsEncodeIgnoreBitStringSizeConstraint())
    {
        if (size > ASN_DescBitString_GetMaxSize(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_SIZE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
        
        if (size < ASN_DescBitString_GetMinSize(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_SIZE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
    }

    /* Encode check end. */

    numberOfBits = 0;

    octetArraySize = size / ASN_BITS_PER_BYTE + 2;

    ASN_C_ASSERT(octetArraySize >= 1);

    octetArraySizeMinusOne = octetArraySize - 1;

    octetArray = (ITS_OCTET*)calloc(octetArraySize, sizeof(ITS_OCTET));

    if (octetArray == NULL)
    {
        return ITS_ENOMEM;
    }

    BooleanArrayToBits(
                    data,
                    size,
                    &numberOfBits,
                    &octetArray[1],
                    &octetArraySizeMinusOne);

    ASN_C_ASSERT(octetArraySizeMinusOne <= size / ASN_BITS_PER_BYTE + 1);

    finalOctetUnusedBits = 0;

    if (numberOfBits % ASN_BITS_PER_BYTE != 0)
    {
        finalOctetUnusedBits = 
            ASN_BITS_PER_BYTE -
                (numberOfBits %
                    ASN_BITS_PER_BYTE);
    }

    octetArray[0] = (byte)finalOctetUnusedBits;

    valOctets = ASN_Octets_ConstructWithArray(octetArray, octetArraySize);

    if (valOctets == NULL)
    {
        free(octetArray);
        return ITS_ENOMEM;
    }

    *octets = ASN_Object_EncodeTagLengthValue((ASN_Object)object, valOctets);

    if (*octets == NULL)
    {
        free(octetArray);
        ASN_Octets_Destruct(valOctets);

        return ITS_ENOMEM;
    }

    free(octetArray);
    ASN_Octets_Destruct(valOctets);

    return ITS_SUCCESS;
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                         = ITS_SUCCESS;
    ASN_DescBitString description   = NULL;
    ASN_Tag tag                     = NULL;
    ASN_Length length               = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescBitString)ASN_OBJECT_DESCRIPTION(object);

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

    if (ASN_Tag_GetType(tag) == TAG_CONSTRUCTED)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_CONSTRUCTED_BIT_STRING, 
                object, 
                octets);

        ASN_Tag_Destruct(tag);

        return ITS_E_ASN_DECODE_ERROR;
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
                ASN_E_INDEFINITE_BIT_STRING_LENGTH, 
                object, 
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else if (ASN_Length_GetLength(length) == 0)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_NULL_BIT_STRING_LENGTH,
                object,
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else
    {
        byte b                              = 0;
        unsigned long finalOctetUnusedBits  = 0;
        ITS_OCTET* octetArray               = NULL;
        size_t octetArraySize               = 0;
        int i                               = 0;
        size_t numberOfBits                 = 0;
        size_t booleanArraySize             = 0;

        if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
        {
            *decodeError =
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_LENGTH,
                    object,
                    octets);

            ASN_Length_Destruct(length);

            return ITS_E_ASN_DECODE_ERROR;
        }

        b = ASN_Octets_GetOctetAtWithOffset(octets, 0);

        finalOctetUnusedBits = (unsigned long)b;

        if (finalOctetUnusedBits >= ASN_BITS_PER_BYTE)
        {
            *decodeError =
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
                    object,
                    octets);

            ASN_Length_Destruct(length);

            return ITS_E_ASN_DECODE_ERROR;
        }

        ASN_C_ASSERT(ASN_Length_GetLength(length) > 0);

        octetArraySize = (size_t)ASN_Length_GetLength(length) - 1;

        octetArray = (ITS_OCTET*)calloc(octetArraySize, sizeof(ITS_OCTET));

        ASN_C_ENSURE(octetArray != NULL);

        if (octetArray == NULL)
        {
            ASN_Length_Destruct(length);
            
            return ITS_ENOMEM;
        }

        for (i = 1; i < (int)octetArraySize + 1; i++)
        {
            if (!ASN_Octets_IsIndexWithOffsetValid(octets, i))
            {
                *decodeError =
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_INVALID_BIT_STRING_LENGTH,
                        object,
                        octets);

                ASN_Length_Destruct(length);

                return ITS_E_ASN_DECODE_ERROR;
            }

            b = ASN_Octets_GetOctetAtWithOffset(octets, i);

            octetArray[i - 1] = b;
        }

        numberOfBits = 
            octetArraySize * 
                ASN_BITS_PER_BYTE -
                    finalOctetUnusedBits;

        /* Absolute maximum. */

        booleanArraySize = octetArraySize * ASN_BITS_PER_BYTE + 1;

        if (ASN_BIT_STRING_DATA(object) != NULL)
        {
            free(ASN_BIT_STRING_DATA(object));
        }

        ASN_BIT_STRING_DATA(object) =
            (ITS_BOOLEAN*)calloc(booleanArraySize, sizeof(ITS_BOOLEAN));

        ASN_C_ENSURE(ASN_BIT_STRING_DATA(object) != NULL);

        if (ASN_BIT_STRING_DATA(object) == NULL)
        {
            free(octetArray);
            ASN_Length_Destruct(length);

            return ITS_ENOMEM;
        }

        BitsToBooleanArray(
                    numberOfBits,
                    octetArray,
                    octetArraySize,
                    ASN_BIT_STRING_DATA(object),
                    &booleanArraySize);

        ASN_C_ASSERT(numberOfBits == booleanArraySize);

        ASN_BIT_STRING_SIZE(object) = booleanArraySize;

        ASN_Octets_IncrementOffsetWithIncrement(
                                            octets, 
                                            ASN_Length_GetLength(length));

        free(octetArray);
    }

    ASN_Length_Destruct(length);

    /* Decode check begin. */

    if (ASN_DescBitString_IsClauseSize(description) && 
        !ASN_Options_GlobalIsDecodeIgnoreBitStringSizeConstraint())
    {
        if (ASN_BIT_STRING_SIZE(object) > 
            ASN_DescBitString_GetMaxSize(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_SIZE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
        
        if (ASN_BIT_STRING_SIZE(object) < 
            ASN_DescBitString_GetMinSize(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_SIZE, 
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
    return "BIT STRING";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "BIT STRING";
}

static char*
ToString(const ASN_Object object)
{
    char* result                = NULL;
    static const int ROW_LENGTH = 30;
    int divisor                 = 0;
    int quotient                = 0;
    int remainder               = 0;
    int i                       = 0;
    int j                       = 0;
    char* buffer                = NULL;
    size_t maxStringSize        = 0;
    const char* nameStr         = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr     = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);
    size_t size                 = 0;
    ITS_BOOLEAN* data           = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_BIT_STRING_SIZE(object) >= 0);

    size = ASN_BIT_STRING_SIZE(object);
    data = ASN_BIT_STRING_DATA(object);

    divisor = ROW_LENGTH;

    ASN_C_ASSERT(divisor > 1);

    quotient    = ASN_BIT_STRING_SIZE(object) / divisor;
    remainder   = ASN_BIT_STRING_SIZE(object) % divisor;

    /* Absolute maximum. */

    maxStringSize = strlen(nameStr) + 
                    strlen(baseNameStr) + 
                    (ASN_BIT_STRING_SIZE(object) + divisor) * 3 + 
                    48;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(buffer, "%s", nameStr);
    buffer += strlen(nameStr);

    sprintf(buffer, " (");
    buffer += 2;

    sprintf(buffer, "%s", baseNameStr);
    buffer += strlen(baseNameStr);

    sprintf(buffer, ")\n");
    buffer += 2;

    sprintf(buffer, "[ ");
    buffer += 2;

    for (i = 0; i < quotient; i++)
    {
        for (j = 0; j < divisor; j++)
        {
            if (ASN_BIT_STRING_DATA(object)[i * divisor + j])
            {
                sprintf(buffer, "1");
                buffer += 1;
            }
            else
            {
                sprintf(buffer, "0");
                buffer += 1;
            }
        }

        if (!(remainder == 0) || i != quotient - 1)
        {
            sprintf(buffer, "\n");
            buffer += 1;
        }

        if (i < quotient - 1)
        {
            sprintf(buffer, "  ");
            buffer += 2;
        }
    }

    if (quotient != 0 && !(remainder == 0))
    {
        sprintf(buffer, "  ");
        buffer += 2;
    }

    for (j = 0; j < remainder; j++)
    {
        if (ASN_BIT_STRING_DATA(object)[i * divisor + j])
        {
            sprintf(buffer, "1");
            buffer += 1;
        }
        else
        {
            sprintf(buffer, "0");
            buffer += 1;
        }
    }

    if (remainder != 0 && quotient != 0)
    {
        for (j = 0; j < divisor - remainder; j++)
        {
            sprintf(buffer, " ");
            buffer += 1;
        }
    }

    sprintf(buffer, " ]\n");
    buffer += 3;

    sprintf(buffer, "\0");
    buffer += 1;

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_BitString class record.
 */ 

ASN_BitString_ClassRec itsASN_BitString_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,
        sizeof(ASN_BitString_ObjectRec),   
        ITS_FALSE,                         
        0,                                 
        ASN_BIT_STRING_CLASS_NAME,         
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

    /* ASN_BitString class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetArray,
        SetArray,
        GetSize,
        Set,
        Reset,
        IsSet,
        IsDefined,
        SetAll,
        ResetAll,
        GetUniversalTag
    }
};

ASN_BitString 
ASN_BitString_ConstructDefault()
{
    ASN_BitString result = NULL;

    result = (ASN_BitString)ITS_ConstructObject((ITS_Class)&itsASN_BitString_ClassRec, NULL, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_BitString 
ASN_BitString_ConstructWithArraySize(const ITS_BOOLEAN* array, size_t size)
{
    ASN_BitString result = NULL;

    result = (ASN_BitString)ITS_ConstructObject((ITS_Class)&itsASN_BitString_ClassRec, array, size, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_BitString
ASN_BitString_ConstructWithArraySizeDescription(const ITS_BOOLEAN* array, size_t size, ASN_DescBitString description)
{
    ASN_BitString result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_BitString)ITS_ConstructObject((ITS_Class)&itsASN_BitString_ClassRec, array, size, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_BitString_Destruct(ASN_BitString object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_BitString 
ASN_BitString_Clone(const ASN_BitString object)
{
    return (ASN_BitString)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_BitString_Equals(const ASN_BitString object, const ASN_BitString other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescBitString 
ASN_BitString_GetStaticDescription()
{
    return GetStaticDescription();
}

void 
ASN_BitString_DestructStaticDescription()
{
    DestructStaticDescription();
}

const ITS_BOOLEAN* 
ASN_BitString_GetArray(const ASN_BitString object)
{
    return ASN_BIT_STRING_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_BitString_GetSize(const ASN_BitString object)
{
    return ASN_BIT_STRING_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_BitString_SetArray(ASN_BitString object, const ITS_BOOLEAN* array, size_t size)
{
    return ASN_BIT_STRING_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))(object, array, size);
}

void 
ASN_BitString_Set(ASN_BitString object, size_t index, ITS_BOOLEAN value)
{
    ASN_BIT_STRING_CLASS_SET(ITS_OBJ_CLASS(object))(object, index, value);
}

void 
ASN_BitString_Reset(ASN_BitString object, size_t index)
{
    ASN_BIT_STRING_CLASS_RESET(ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_BitString_IsSet(const ASN_BitString object, size_t index)
{
    return ASN_BIT_STRING_CLASS_IS_SET(ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_BitString_IsDefined(const ASN_BitString object, size_t index)
{
    return ASN_BIT_STRING_CLASS_IS_DEFINED(ITS_OBJ_CLASS(object))(object, index);
}

void 
ASN_BitString_SetAll(ASN_BitString object)
{
    ASN_BIT_STRING_CLASS_SET_ALL(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_BitString_ResetAll(ASN_BitString object)
{
    ASN_BIT_STRING_CLASS_RESET_ALL(ITS_OBJ_CLASS(object))(object);
}

ASN_Tag 
ASN_BitString_GetUniversalTag(const ASN_BitString object)
{
    return ASN_BIT_STRING_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_BitString_Encode(ASN_BitString object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_BitString_Decode(ASN_BitString object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_BitString_GetName(const ASN_BitString object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_BitString_GetBaseName(const ASN_BitString object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_BitString_Print(const ASN_BitString object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_BitString_ToString(const ASN_BitString object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

