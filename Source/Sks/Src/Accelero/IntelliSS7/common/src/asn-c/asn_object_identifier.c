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
 *  ID: $Id: asn_object_identifier.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_object_identifier.h>
#include <asn_desc_object_identifier.h>
#include <asn_length.h>

/*
 *  Protected preprocessor constant definitions.
 */

/* Constants for encode/decode checks. */

#define OID_FIRST_CPT_CCITT_VALUE               0
#define OID_FIRST_CPT_ISO_VALUE                 1
#define OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE     2
#define OID_SECOND_CPT_MINIMUM_VALUE            0
#define OID_SECOND_CPT_MAXIMUM_VALUE            39
#define OID_MINIMUM_NUMBER_OF_CPTS              2

/* Constants for encode/decode. */

#define OID_FIRST_SUBID_DISC        40U
#define OID_SUBID_INVALID_VALUE     0x80U
#define OID_OCTET_BITS              0x7FU
#define OID_OCTETS_FOLLOW           0x80U
#define OID_LONG_SHIFT              7




static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_OBJECT_IDENTIFIER_CLASS_GET_ARRAY(subClass) == ASN_OBJECT_IDENTIFIER_GET_ARRAY_INHERIT)
    {
        ASN_OBJECT_IDENTIFIER_CLASS_GET_ARRAY(subClass) =
            ASN_OBJECT_IDENTIFIER_CLASS_GET_ARRAY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_IDENTIFIER_CLASS_SET_ARRAY(subClass) == ASN_OBJECT_IDENTIFIER_SET_ARRAY_INHERIT)
    {
        ASN_OBJECT_IDENTIFIER_CLASS_SET_ARRAY(subClass) =
            ASN_OBJECT_IDENTIFIER_CLASS_SET_ARRAY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_IDENTIFIER_CLASS_GET_SIZE(subClass) == ASN_OBJECT_IDENTIFIER_GET_SIZE_INHERIT)
    {
        ASN_OBJECT_IDENTIFIER_CLASS_GET_SIZE(subClass) =
            ASN_OBJECT_IDENTIFIER_CLASS_GET_SIZE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_IDENTIFIER_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_OBJECT_IDENTIFIER_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_OBJECT_IDENTIFIER_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_OBJECT_IDENTIFIER_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescObjectIdentifier GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ITS_LONG* array                         = NULL;
    size_t size                             = 0;
    ASN_DescObjectIdentifier description    = NULL;

    array = va_arg(args, ITS_LONG*);
    size = va_arg(args, size_t);

    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    description = va_arg(args, ASN_DescObjectIdentifier);

    if (array != NULL && size != 0)
    {
        ASN_OBJECT_IDENTIFIER_DATA(object) = (ITS_LONG*)calloc(size, sizeof(ITS_LONG));

        ASN_C_ENSURE(ASN_OBJECT_IDENTIFIER_DATA(object) != NULL);

        if (ASN_OBJECT_IDENTIFIER_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_OBJECT_IDENTIFIER_DATA(object), array, size * sizeof (ITS_LONG));
        ASN_OBJECT_IDENTIFIER_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_OBJECT_IDENTIFIER_DATA(object) = NULL;
        ASN_OBJECT_IDENTIFIER_SIZE(object) = 0;
    }

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            if (ASN_OBJECT_IDENTIFIER_DATA(object) != NULL)
            {
                free(ASN_OBJECT_IDENTIFIER_DATA(object));
                ASN_OBJECT_IDENTIFIER_DATA(object) = NULL;
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

    if (ASN_OBJECT_IDENTIFIER_DATA(object) != NULL)
    {
        free(ASN_OBJECT_IDENTIFIER_DATA(object));
        ASN_OBJECT_IDENTIFIER_DATA(object) = NULL;
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

    if (ASN_OBJECT_IDENTIFIER_SIZE(object) > 0)
    {
        ASN_OBJECT_IDENTIFIER_DATA(result) = (ITS_LONG*)calloc(ASN_OBJECT_IDENTIFIER_SIZE(object), sizeof(ITS_LONG));

        ASN_C_ENSURE(ASN_OBJECT_IDENTIFIER_DATA(result) != NULL);

        if (ASN_OBJECT_IDENTIFIER_DATA(result) == NULL)
        {
            free(result);

            return NULL;
        }

        memcpy(ASN_OBJECT_IDENTIFIER_DATA(result), ASN_OBJECT_IDENTIFIER_DATA(object), ASN_OBJECT_IDENTIFIER_SIZE(object));
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

    if (ASN_OBJECT_IDENTIFIER_SIZE(object) != ASN_OBJECT_IDENTIFIER_SIZE(other))
    {
        return ITS_FALSE;
    }

    if (memcmp(
            ASN_OBJECT_IDENTIFIER_DATA(object),
            ASN_OBJECT_IDENTIFIER_DATA(other),
            ASN_OBJECT_IDENTIFIER_SIZE(object)) == 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ASN_DescObjectIdentifier staticDescription = NULL;

static ASN_DescObjectIdentifier
GetStaticDescription()
{
    static ITS_BOOLEAN initialized          = ITS_FALSE;
    static ASN_DescObjectIdentifier result  = NULL;
    ASN_ObjectIdentifier cloneForFactory    = NULL;
    ASN_Tag universalTag                    = NULL;

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

        staticDescription = ASN_DescObjectIdentifier_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_ObjectIdentifier_ConstructWithArraySizeDescription(NULL, 0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescObjectIdentifier_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescObjectIdentifier_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_ObjectIdentifier_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescObjectIdentifier_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescObjectIdentifier_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescObjectIdentifier_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static const ITS_LONG* 
GetArray(const ASN_ObjectIdentifier object)
{
    const ITS_LONG* result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_OBJECT_IDENTIFIER_SIZE(object) > 0);

    result = ASN_OBJECT_IDENTIFIER_DATA(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static size_t 
GetSize(const ASN_ObjectIdentifier object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_OBJECT_IDENTIFIER_SIZE(object);
}

static int 
SetArray(ASN_ObjectIdentifier object, const ITS_LONG* array, size_t size)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    if (ASN_OBJECT_IDENTIFIER_DATA(object) != NULL)
    {
        free(ASN_OBJECT_IDENTIFIER_DATA(object));
        ASN_OBJECT_IDENTIFIER_DATA(object) = NULL;
    }

    if (array != NULL && size != 0)
    {
        ASN_OBJECT_IDENTIFIER_DATA(object) = (ITS_LONG*)calloc(size, sizeof(ITS_LONG));

        ASN_C_ENSURE(ASN_OBJECT_IDENTIFIER_DATA(object) != NULL);

        if (ASN_OBJECT_IDENTIFIER_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_OBJECT_IDENTIFIER_DATA(object), array, size * sizeof (ITS_LONG));
        ASN_OBJECT_IDENTIFIER_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_OBJECT_IDENTIFIER_DATA(object) = NULL;
        ASN_OBJECT_IDENTIFIER_SIZE(object) = 0;
    }

    return ITS_SUCCESS;
}

static ASN_Tag
GetUniversalTag(const ASN_ObjectIdentifier object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_OBJECT_IDENTIFIER);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescObjectIdentifier description = NULL;

    ITS_LONG* data                  = NULL;
    size_t size                     = 0;
    ASN_Octets valOctets            = NULL;
    ITS_LONG firstComponentValue    = 0;
    ITS_LONG secondComponentValue   = 0;
    int i                           = 0;
    int n                           = 0;
    ITS_OCTET* array                = 0;
    size_t arraySize                = 0;
    byte firstSubid                 = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescObjectIdentifier)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    data = ASN_OBJECT_IDENTIFIER_DATA(object);
    size = ASN_OBJECT_IDENTIFIER_SIZE(object);

    ASN_C_ASSERT((data == NULL && size == 0) || (data != NULL && size != 0))

    /* Encode check begin. */

    if (size < OID_MINIMUM_NUMBER_OF_CPTS)
    {
        *encodeError = 
            ASN_CONSTRUCT_ENCODE_ERROR(
                ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID, 
                object); 

        return ITS_E_ASN_ENCODE_ERROR;
    }

    firstComponentValue = data[0];

    if (firstComponentValue != OID_FIRST_CPT_CCITT_VALUE              &&
        firstComponentValue != OID_FIRST_CPT_ISO_VALUE                &&
        firstComponentValue != OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE)
    {
        *encodeError = 
            ASN_CONSTRUCT_ENCODE_ERROR(
                ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID, 
                object); 

        return ITS_E_ASN_ENCODE_ERROR;
    }

    secondComponentValue = data[1];

    if (secondComponentValue < OID_SECOND_CPT_MINIMUM_VALUE ||
        secondComponentValue > OID_SECOND_CPT_MAXIMUM_VALUE)
    {
        *encodeError = 
            ASN_CONSTRUCT_ENCODE_ERROR(
                ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID, 
                object); 

        return ITS_E_ASN_ENCODE_ERROR;
    }

    for (i = 2; i < (int)size; i++)
    {
        ITS_LONG componentValue = data[i];

        if (componentValue < 0)
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
    }

    /* Encode check end. */

    arraySize = size * (ASN_BYTES_PER_LONG + 2) + 16;

    array = (ITS_OCTET*)calloc(arraySize, sizeof(ITS_OCTET));

    if (array == NULL)
    {
        return ITS_ENOMEM;
    }

    ASN_C_ASSERT(size >= 2);

    n = 0;

    firstSubid = (byte)(data[0] * OID_FIRST_SUBID_DISC + data[1]);

    array[n++] = firstSubid;

    for (i = 2; i < (int)size; i++)
    {
        ITS_LONG value  = data[i];
        byte subid      = 0x00U;

        if (value <= OID_OCTET_BITS)
        {
            subid = (byte)value;
            subid &= ~OID_OCTETS_FOLLOW;
            array[n++] = subid;
        }
        else if ((value >> OID_LONG_SHIFT) <= OID_OCTET_BITS)
        {
            subid = (byte)(((value >> OID_LONG_SHIFT) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array[n++] = subid;
            subid = (byte)(value & OID_OCTET_BITS);
            subid &= ~OID_OCTETS_FOLLOW;
            array[n++] = subid;
        }
        else if ((value >> OID_LONG_SHIFT * 2) <= OID_OCTET_BITS)
        {
            subid = (byte)(((value >> OID_LONG_SHIFT * 2) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array[n++] = subid;
            subid = (byte)(((value >> OID_LONG_SHIFT) & 
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array[n++] = subid;
            subid = (byte)(value & OID_OCTET_BITS);
            subid &= ~OID_OCTETS_FOLLOW;
            array[n++] = subid;
        }
        else
        {
            subid = (byte)(((value >> OID_LONG_SHIFT * 3) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array[n++] = subid;
            subid = (byte)(((value >> OID_LONG_SHIFT * 2) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array[n++] = subid;
            subid = (byte)(((value >> OID_LONG_SHIFT) & 
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array[n++] = subid;
            subid = (byte)(value & OID_OCTET_BITS);
            subid &= ~OID_OCTETS_FOLLOW;
            array[n++] = subid;
        }
    }

    ASN_C_ASSERT(n < (int)arraySize);


    valOctets = ASN_Octets_ConstructWithArray(array, n);

    if (valOctets == NULL)
    {
        free(array);

        return ITS_ENOMEM;
    }

    *octets = ASN_Object_EncodeTagLengthValue((ASN_Object)object, valOctets);

    if (*octets == NULL)
    {
        free(array);
        ASN_Octets_Destruct(valOctets);

        return ITS_ENOMEM;
    }

    free(array);
    ASN_Octets_Destruct(valOctets);

    return ITS_SUCCESS;
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                                 = ITS_SUCCESS;
    ASN_DescObjectIdentifier description    = NULL;
    ASN_Tag tag                             = NULL;
    ASN_Length length                       = NULL;
    ITS_LONG* data                          = NULL;
    size_t size                             = 0;
    int i                                   = 0;
    ITS_LONG firstComponentValue            = 0;
    ITS_LONG secondComponentValue           = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescObjectIdentifier)ASN_OBJECT_DESCRIPTION(object);

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
                ASN_E_CONSTRUCTED_OID, 
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
                ASN_E_INDEFINITE_OID_LENGTH, 
                object, 
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else if (ASN_Length_GetLength(length) == 0)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_NULL_OID_LENGTH,
                object,
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else
    {
        byte b              = 0;
        byte firstCptVal    = 0;
        byte secondCptVal   = 0;
        int i               = 0;
        int j               = 0;
        int n               = 0;

        if (ASN_OBJECT_IDENTIFIER_DATA(object) != NULL)
        {
            free(ASN_OBJECT_IDENTIFIER_DATA(object));
        }

        /*
         *  Reserve for greatest possible case.
         */

        ASN_OBJECT_IDENTIFIER_DATA(object) = 
            (ITS_LONG*)calloc(ASN_Length_GetLength(length) + 1, sizeof(ITS_LONG));

        ASN_C_ENSURE(ASN_OBJECT_IDENTIFIER_DATA(object) != NULL);

        if (ASN_OBJECT_IDENTIFIER_DATA(object) == NULL)
        {
            ASN_Length_Destruct(length);

            return ITS_ENOMEM;
        }

        n = 0; /* Start index. */

        data = ASN_OBJECT_IDENTIFIER_DATA(object);

        /* First octet. */

        if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
        {
            *decodeError =
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_OID_LENGTH,
                    object,
                    octets);

            ASN_Length_Destruct(length);

            return ITS_E_ASN_DECODE_ERROR;
        }

        b = ASN_Octets_GetOctetAtWithOffset(octets, 0);

        firstCptVal     = 0;
        secondCptVal    = 0;

        ASN_C_ASSERT(OID_FIRST_CPT_ISO_VALUE *
                        OID_FIRST_SUBID_DISC +
                            OID_SECOND_CPT_MAXIMUM_VALUE +
                                1 == 
                                    OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE *
                                        OID_FIRST_SUBID_DISC);

        if (b > (byte)(
                    OID_FIRST_CPT_ISO_VALUE *
                        OID_FIRST_SUBID_DISC + 
                            OID_SECOND_CPT_MAXIMUM_VALUE))
        {
            firstCptVal = (byte)OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE;

            if (b >= (byte)(
                        OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE *
                            OID_FIRST_SUBID_DISC))
            {
                secondCptVal = 
                    (byte)(
                        b - 
                            OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE *
                                OID_FIRST_SUBID_DISC);
            }
            else
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ASN_C_ASSERT(must_not_be_reached);
            }
        }
        else
        {
            firstCptVal = (byte)(b / OID_FIRST_SUBID_DISC);
            secondCptVal = (byte)(b % OID_FIRST_SUBID_DISC);
        }

        data[n++] = firstCptVal;
        data[n++] = secondCptVal;

        /* Remaining octets. */

        if (ASN_Length_GetLength(length) > 1)
        {
            size = (size_t)ASN_Length_GetLength(length) - 1;

            for (j = 0; j < (int)size; j++)
            {
                ITS_LONG value                  = 0;
                size_t numberOfShifts           = 0;
                ITS_BOOLEAN firstSubidentifier  = ITS_TRUE;
                ITS_BOOLEAN stop                = ITS_FALSE;

                while (!stop)
                {
                    if (!ASN_Octets_IsIndexWithOffsetValid(octets, j + 1))
                    {
                        *decodeError =
                            ASN_CONSTRUCT_DECODE_ERROR(
                            ASN_E_INVALID_OID_LENGTH,
                            object,
                            octets);

                        ASN_Length_Destruct(length);

                        return ITS_E_ASN_DECODE_ERROR;
                    }

                    b = ASN_Octets_GetOctetAtWithOffset(octets, j + 1);

                    if (firstSubidentifier)
                    {
                        if (b == OID_SUBID_INVALID_VALUE)
                        {
                            *decodeError =
                                ASN_CONSTRUCT_DECODE_ERROR(
                                ASN_E_OID_CPT_VALUE_INVALID,
                                object,
                                octets);

                            ASN_Length_Destruct(length);

                            return ITS_E_ASN_DECODE_ERROR;
                        }

                        firstSubidentifier = ITS_FALSE;
                    }

                    value |= (b & OID_OCTET_BITS) & ASN_BYTE_MASK_IN_LONG;

                    if (b & OID_OCTETS_FOLLOW)
                    {
                        value <<= OID_LONG_SHIFT;

                        numberOfShifts++;

                        if (numberOfShifts >= ASN_BYTES_PER_LONG)
                        {
                            *decodeError =
                                ASN_CONSTRUCT_DECODE_ERROR(
                                ASN_E_OID_CPT_VALUE_OUT_OF_RANGE,
                                object,
                                octets);

                            ASN_Length_Destruct(length);

                            return ITS_E_ASN_DECODE_ERROR;
                        }

                        j++;

                        if (j >= (int)size)
                        {
                           *decodeError =
                                ASN_CONSTRUCT_DECODE_ERROR(
                                ASN_E_INVALID_OID_LENGTH,
                                object,
                                octets);

                            ASN_Length_Destruct(length);

                            return ITS_E_ASN_DECODE_ERROR;
                        }
                    }
                    else
                    {
                        stop = ITS_TRUE;
                    }                
                }

                data[n++] = value;
            }
        }

        ASN_C_ASSERT(n <= ASN_Length_GetLength(length) + 1);

        ASN_OBJECT_IDENTIFIER_SIZE(object) = n;

        ASN_Octets_IncrementOffsetWithIncrement(
                                            octets, 
                                            ASN_Length_GetLength(length));
    }

    ASN_Length_Destruct(length);

    /* Decode check begin. */

    data = ASN_OBJECT_IDENTIFIER_DATA(object);
    size = ASN_OBJECT_IDENTIFIER_SIZE(object);

    if (size < OID_MINIMUM_NUMBER_OF_CPTS)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID, 
                object,
                octets); 

        return ITS_E_ASN_DECODE_ERROR;
    }

    firstComponentValue = data[0];

    if (firstComponentValue != OID_FIRST_CPT_CCITT_VALUE              &&
        firstComponentValue != OID_FIRST_CPT_ISO_VALUE                &&
        firstComponentValue != OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID, 
                object,
                octets); 

        return ITS_E_ASN_DECODE_ERROR;
    }

    secondComponentValue = data[1];

    if (secondComponentValue < OID_SECOND_CPT_MINIMUM_VALUE ||
        secondComponentValue > OID_SECOND_CPT_MAXIMUM_VALUE)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID, 
                object,
                octets); 

        return ITS_E_ASN_DECODE_ERROR;
    }

    for (i = 2; i < (int)size; i++)
    {
        ITS_LONG componentValue = data[i];

        if (componentValue < 0)
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID, 
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
    return "OBJECT IDENTIFIER";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "OBJECT IDENTIFIER";
}

static char*
ToString(const ASN_Object object)
{
    char* result            = NULL;
    char* buffer            = NULL;
    size_t maxStringSize    = 0;
    int i                   = 0;
    const char* nameStr     = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_OBJECT_IDENTIFIER_SIZE(object) >= 0);

    /* Absolute maximum. */

    maxStringSize = strlen(nameStr) + 
                    strlen(baseNameStr) + 
                    ASN_OBJECT_IDENTIFIER_SIZE(object) * 16 + 
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

    for (i = 0; i < (int)ASN_OBJECT_IDENTIFIER_SIZE(object); i++)
    {
        char cptNumberBuffer[32];

        memset(cptNumberBuffer, 0, 32);

        sprintf(cptNumberBuffer, "%ld", ASN_OBJECT_IDENTIFIER_DATA(object)[i]);

        ASN_C_ASSERT(strlen(cptNumberBuffer) < 16);

        strcat(buffer, cptNumberBuffer);
        buffer += strlen(cptNumberBuffer);

        if (i != (int)ASN_OBJECT_IDENTIFIER_SIZE(object) - 1)
        {
            sprintf(buffer, ", ");
            buffer += 2;
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
 *  ASN_ObjectIdentifier class record.
 */ 

ASN_ObjectIdentifier_ClassRec itsASN_ObjectIdentifier_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,    
        sizeof(ASN_ObjectIdentifier_ObjectRec),
        ITS_FALSE,                             
        0,                                     
        ASN_OBJECT_IDENTIFIER_CLASS_NAME,      
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

    /* ASN_ObjectIdentifier class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetArray,
        SetArray,
        GetSize,
        GetUniversalTag
    }
};

ASN_ObjectIdentifier 
ASN_ObjectIdentifier_ConstructDefault()
{
    ASN_ObjectIdentifier result = NULL;

    result = (ASN_ObjectIdentifier)ITS_ConstructObject((ITS_Class)&itsASN_ObjectIdentifier_ClassRec, NULL, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_ObjectIdentifier 
ASN_ObjectIdentifier_ConstructWithArraySize(const ITS_LONG* array, size_t size)
{
    ASN_ObjectIdentifier result = NULL;

    result = (ASN_ObjectIdentifier)ITS_ConstructObject((ITS_Class)&itsASN_ObjectIdentifier_ClassRec, array, size, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_ObjectIdentifier
ASN_ObjectIdentifier_ConstructWithArraySizeDescription(const ITS_LONG* array, size_t size, ASN_DescObjectIdentifier description)
{
    ASN_ObjectIdentifier result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_ObjectIdentifier)ITS_ConstructObject((ITS_Class)&itsASN_ObjectIdentifier_ClassRec, array, size, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_ObjectIdentifier_Destruct(ASN_ObjectIdentifier object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_ObjectIdentifier 
ASN_ObjectIdentifier_Clone(const ASN_ObjectIdentifier object)
{
    return (ASN_ObjectIdentifier)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_ObjectIdentifier_Equals(const ASN_ObjectIdentifier object, const ASN_ObjectIdentifier other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescObjectIdentifier 
ASN_ObjectIdentifier_GetStaticDescription()
{
    return GetStaticDescription();
}

void 
ASN_ObjectIdentifier_DestructStaticDescription()
{
    DestructStaticDescription();
}

const ITS_LONG* 
ASN_ObjectIdentifier_GetArray(const ASN_ObjectIdentifier object)
{
    return ASN_OBJECT_IDENTIFIER_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_ObjectIdentifier_GetSize(const ASN_ObjectIdentifier object)
{
    return ASN_OBJECT_IDENTIFIER_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_ObjectIdentifier_SetArray(ASN_ObjectIdentifier object, const ITS_LONG* array, size_t size)
{
    return ASN_OBJECT_IDENTIFIER_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))(object, array, size);
}

ASN_Tag 
ASN_ObjectIdentifier_GetUniversalTag(const ASN_ObjectIdentifier object)
{
    return ASN_OBJECT_IDENTIFIER_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_ObjectIdentifier_Encode(ASN_ObjectIdentifier object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_ObjectIdentifier_Decode(ASN_ObjectIdentifier object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_ObjectIdentifier_GetName(const ASN_ObjectIdentifier object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_ObjectIdentifier_GetBaseName(const ASN_ObjectIdentifier object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_ObjectIdentifier_Print(const ASN_ObjectIdentifier object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_ObjectIdentifier_ToString(const ASN_ObjectIdentifier object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

