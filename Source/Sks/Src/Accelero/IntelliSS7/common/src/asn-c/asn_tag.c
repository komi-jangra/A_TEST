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
 *  ID: $Id: asn_tag.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_tag.h>

#include <string.h>


/*
 *  Protected preprocessor constant definitions.
 */


/* Helper constant for encoding/decoding extended tag numbers. */

#define TAG_EXTENDED           31


/* Binary format helper constants. */

#define TAG_CLASS_SHIFT        6
#define TAG_CLASS_BITS         0x03U

#define TAG_TYPE_SHIFT         5
#define TAG_TYPE_BITS          0x01U

#define TAG_NUMBER_BITS        0x1FU

#define TAG_OCTET_BITS         0x7FU
#define TAG_OCTETS_FOLLOW      0x80U

#define TAG_MAX_LENGTH         5
#define TAG_LONG_SHIFT         7


/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN Invariant(const ASN_Tag object);


static int
Construct(ITS_Object object, va_list args)
{
    ITS_OCTET tagClass  = 0;
    ITS_OCTET type      = 0;
    ITS_ULONG number    = 0;

    ASN_C_REQUIRE(object != NULL);

    tagClass    = va_arg(args, ITS_OCTET);
    type        = va_arg(args, ITS_OCTET);
    number      = va_arg(args, ITS_ULONG);


    ASN_C_REQUIRE(
        tagClass == TAG_CLASS_UNIVERSAL        ||
        tagClass == TAG_CLASS_APPLICATION      ||
        tagClass == TAG_CLASS_CONTEXT_SPECIFIC ||
        tagClass == TAG_CLASS_PRIVATE);

    ASN_C_REQUIRE(type == TAG_PRIMITIVE || type == TAG_CONSTRUCTED);

    ASN_TAG_TAG_CLASS(object)   = tagClass;
    ASN_TAG_TYPE(object)        = type;
    ASN_TAG_NUMBER(object)      = number;

    ASN_C_ASSERT(Invariant((ASN_Tag)object));

    return ITS_SUCCESS;
}


static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    /* Nothing to do. */
}


static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result   = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = (ITS_Object)calloc(
                            1, 
                            ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

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
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(other != NULL);

    if (ITS_OBJ_CLASS(object) != ITS_OBJ_CLASS(other))
    {
        return ITS_FALSE;
    }

    if (ASN_TAG_TAG_CLASS(object) != ASN_TAG_TAG_CLASS(other))
    {
        return ITS_FALSE;
    }

    if (ASN_TAG_TYPE(object) != ASN_TAG_TYPE(other))
    {
        return ITS_FALSE;
    }

    if (ASN_TAG_NUMBER(object) != ASN_TAG_NUMBER(other))
    {
        return ITS_FALSE;
    }

    return ITS_TRUE;
}

static int 
Encode(ASN_Tag object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    typedef ITS_OCTET byte;

    ITS_OCTET array[TAG_MAX_LENGTH];

    int inc             = 0;
    ITS_OCTET tagClass  = 0;
    ITS_OCTET type      = 0;
    ITS_ULONG number    = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    memset(array, 0x00U, TAG_MAX_LENGTH);

    tagClass    = ASN_TAG_TAG_CLASS(object);
    type        = ASN_TAG_TYPE(object);
    number      = ASN_TAG_NUMBER(object);

    if (tagClass == TAG_CLASS_UNIVERSAL)
    {
        array[0] = tagClass << TAG_CLASS_SHIFT;
        array[0] |= type << TAG_TYPE_SHIFT;
        array[0] |= (byte)number;
        inc = 1;
    }
    else
    {
        array[0] = tagClass << TAG_CLASS_SHIFT;
        array[0] |= type << TAG_TYPE_SHIFT;
        if (number < TAG_EXTENDED)
        {
            array[0] |= (byte)number;
            inc = 1;
        }
        else
        {
            array[0] |= (byte)TAG_EXTENDED;
            if (number <= TAG_OCTET_BITS)
            {
                array[1] = (byte)number;
                array[1] &= ~TAG_OCTETS_FOLLOW;
                inc = 2;
            }
            else if ((number >> TAG_LONG_SHIFT) <= TAG_OCTET_BITS)
            {
                array[1] = (byte)(((number >> TAG_LONG_SHIFT) &
                                   TAG_OCTET_BITS) | TAG_OCTETS_FOLLOW);
                array[2] = (byte)(number & TAG_OCTET_BITS);
                array[2] &= ~TAG_OCTETS_FOLLOW;
                inc = 3;
            }
            else if ((number >> TAG_LONG_SHIFT * 2) <= TAG_OCTET_BITS)
            {
                array[1] = (byte)(((number >> TAG_LONG_SHIFT * 2) &
                                   TAG_OCTET_BITS) | TAG_OCTETS_FOLLOW);
                array[2] = (byte)(((number >> TAG_LONG_SHIFT) & 
                                   TAG_OCTET_BITS) | TAG_OCTETS_FOLLOW);
                array[3] = (byte)(number & TAG_OCTET_BITS);
                array[3] &= ~TAG_OCTETS_FOLLOW;
                inc = 4;
            }
            else
            {
                array[1] = (byte)(((number >> TAG_LONG_SHIFT * 3) &
                                   TAG_OCTET_BITS) | TAG_OCTETS_FOLLOW);
                array[2] = (byte)(((number >> TAG_LONG_SHIFT * 2) &
                                   TAG_OCTET_BITS) | TAG_OCTETS_FOLLOW);
                array[3] = (byte)(((number >> TAG_LONG_SHIFT) & 
                                   TAG_OCTET_BITS) | TAG_OCTETS_FOLLOW);
                array[4] = (byte)(number & TAG_OCTET_BITS);
                array[4] &= ~TAG_OCTETS_FOLLOW;
                inc = 5;
            }
        }
    }

    *octets         = ASN_Octets_ConstructWithArray(array, inc);
    *encodeError    = NULL;

    if (*octets == NULL)
    {
        return ITS_ENOMEM;
    }
    else
    {
        return ITS_SUCCESS;
    }
}

static int 
Decode(ASN_Tag object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    ITS_OCTET b         = 0;
    ITS_OCTET tagClass  = 0;
    ITS_OCTET type      = 0;
    ITS_ULONG number    = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
    {
        *decodeError = 
            ASN_CONSTRUCT_TAG_DECODE_ERROR(
                ASN_E_INVALID_TAG_LENGTH, 
                object, 
                octets);

        return ITS_E_ASN_DECODE_ERROR;
    }

    b = ASN_Octets_GetOctetAtWithOffset(octets, 0);

    tagClass = (byte)((b >> TAG_CLASS_SHIFT) & TAG_CLASS_BITS);
    type = (byte)((b >> TAG_TYPE_SHIFT) & TAG_TYPE_BITS);
    number = (unsigned long)(b & TAG_NUMBER_BITS);

    if (tagClass == TAG_CLASS_UNIVERSAL)
    {
        if (!ASN_Tag_IsUniversal(object, number))
        {
            *decodeError = 
                ASN_CONSTRUCT_TAG_DECODE_ERROR(
                    ASN_E_INVALID_UNIVERSAL_NUMBER, 
                    object, 
                    octets);

            return ITS_E_ASN_DECODE_ERROR;
        }
                
        ASN_Octets_IncrementOffset(octets);
    }
    else
    {
        if (number != TAG_EXTENDED)
        {
            ASN_Octets_IncrementOffset(octets);
        }
        else
        {
            int i = 0;

            number = 0;

            while (i < TAG_MAX_LENGTH)
            {
                i++;

                if (!ASN_Octets_IsIndexWithOffsetValid(octets, i))
                {
                    *decodeError = 
                        ASN_CONSTRUCT_TAG_DECODE_ERROR(
                            ASN_E_INVALID_TAG_LENGTH, 
                            object, 
                            octets);

                    return ITS_E_ASN_DECODE_ERROR;
                }

                number |= (ASN_Octets_GetOctetAtWithOffset(octets, i) & 
                           TAG_OCTET_BITS) &
                          ASN_BYTE_MASK_IN_LONG;

                if ((ASN_Octets_GetOctetAtWithOffset(octets, i) & 
                     TAG_OCTETS_FOLLOW) != 0)
                {
                    number <<= TAG_LONG_SHIFT;
                }
                else
                {
                    break;
                }
            }

            ASN_Octets_IncrementOffsetWithIncrement(octets, i + 1);
        }
    }

    ASN_TAG_TAG_CLASS(object)   = tagClass;
    ASN_TAG_TYPE(object)        = type;
    ASN_TAG_NUMBER(object)      = number;

    return ITS_SUCCESS;
}

static int 
DecodePreserveOffset(
                ASN_Tag object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError)
{
    size_t offset   = 0;
    int result      = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);

    offset = ASN_Octets_GetOffset(octets);

    result = Decode(object, octets, decodeError);

    ASN_Octets_SetOffset(octets, offset);

    return result;
}

static void 
SetTagClass(ASN_Tag object, ITS_OCTET tagClass)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_TAG_TAG_CLASS(object) = tagClass;
}

static void 
SetType(ASN_Tag object, ITS_OCTET type)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_TAG_TYPE(object) = type;
}

static void 
SetNumber(ASN_Tag object, ITS_ULONG number)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_TAG_NUMBER(object) = number;
}

static ITS_OCTET 
GetTagClass(const ASN_Tag object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_TAG_TAG_CLASS(object);
}

static ITS_OCTET 
GetType(const ASN_Tag object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_TAG_TYPE(object);
}

static ITS_ULONG 
GetNumber(const ASN_Tag object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_TAG_NUMBER(object);
}

static char* 
ToString(const ASN_Tag object)
{
    char* result                = NULL;
    char* buffer                = NULL;
    size_t maxStringSize        = 0;

    ASN_C_REQUIRE(object != NULL);

    /* Absolute maximum. */

    maxStringSize = 64;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "[ %d %d %ld ]",
        ASN_TAG_TAG_CLASS(object),
        ASN_TAG_TYPE(object),
        ASN_TAG_NUMBER(object));

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void
Print(ITS_Object object)
{
    char* toString = NULL;

    ASN_C_REQUIRE(object != NULL);

    toString = ToString((ASN_Tag)object);

    if (toString != NULL)
    {
        printf("%s", toString);

        free(toString);
    }
}

static char* 
GetEncodeExtendedErrorText(const ASN_Tag object, ASN_Error error)
{
    ASN_C_REQUIRE(object != NULL);

    return strdup("No extended encode error text available for Tag.");
}

static char* 
GetDecodeExtendedErrorText(
                        const ASN_Tag object, 
                        ASN_Error error, 
                        const ASN_Octets octets)
{
    ASN_C_REQUIRE(object != NULL);

    return strdup("No extended decode error text available for Tag.");
}

static ITS_BOOLEAN 
IsUniversal(const ASN_Tag object, ITS_ULONG number)
{
    ASN_C_REQUIRE(object != NULL);

    if (number == TAG_BOOLEAN           ||
        number == TAG_INTEGER           ||
        number == TAG_BIT_STRING        ||
        number == TAG_OCTET_STRING      ||
        number == TAG_NULL              ||
        number == TAG_OBJECT_IDENTIFIER ||
        number == TAG_OBJECT_DESCRIPTOR ||
        number == TAG_EXTERNAL          ||
        number == TAG_REAL              ||
        number == TAG_ENUMERATED        ||
        number == TAG_ENCRYPTED         ||
        number == TAG_SEQUENCE          ||
        number == TAG_SET               ||
        number == TAG_NUMERICAL_STRING  ||
        number == TAG_PRINTABLE_STRING  ||
        number == TAG_TELETEX_STRING    ||
        number == TAG_VIDEOTEX_STRING   ||
        number == TAG_IA5_STRING        ||
        number == TAG_UTC_TIME          ||
        number == TAG_GENERALIZED_TIME  ||
        number == TAG_GRAPHICS_STRING   ||
        number == TAG_VISIBLE_STRING    ||
        number == TAG_GENERAL_STRING)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN 
Invariant(const ASN_Tag object)
{
    ITS_OCTET tagClass  = 0;
    ITS_ULONG number    = 0;

    ASN_C_REQUIRE(object != NULL);

    tagClass    = ASN_TAG_TAG_CLASS(object);
    number      = ASN_TAG_NUMBER(object);

    if (tagClass == TAG_CLASS_UNIVERSAL && !IsUniversal(object, number))
    {
        return ITS_FALSE;
    }
    else
    {
        return ITS_TRUE;
    }
}


/*
 *  ASN_Tag class record.
 */ 

ASN_Tag_ClassRec itsASN_Tag_ClassRec =
{
    /* Core part. */

    {
        &itsCORE_ClassRec,         
        sizeof(ASN_Tag_ObjectRec), 
        ITS_FALSE,                 
        0,                         
        ASN_TAG_CLASS_NAME,        
        ITS_CLASS_NO_INIT,         
        ITS_CLASS_NO_DEST,         
        ITS_CLASS_PART_NO_INIT,    
        ITS_CLASS_PART_NO_DEST,    
        Construct,                 
        Destruct,                  
        Clone,                     
        Print,                     
        ITS_INST_SERIAL_INHERIT,   
        Equals,                    
        ITS_INST_HASH_INHERIT,     
        NULL                
    },

    /* ASN_Tag class part. */

    {
        Encode,
        Decode,
        DecodePreserveOffset,
        SetTagClass,
        SetType,
        SetNumber,
        GetTagClass,
        GetType,
        GetNumber,
        ToString,
        GetEncodeExtendedErrorText,
        GetDecodeExtendedErrorText,
        IsUniversal,
        Invariant
    }
};


ASN_Tag 
ASN_Tag_ConstructDefault()
{
    ASN_Tag result = NULL;

    result = 
        (ASN_Tag)ITS_ConstructObject(
                            (ITS_Class)&itsASN_Tag_ClassRec, 
                            TAG_CLASS_UNIVERSAL, 
                            TAG_PRIMITIVE,
                            TAG_BOOLEAN);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Tag 
ASN_Tag_ConstructWithClassTypeNumber(
                                ITS_OCTET tagClass, 
                                ITS_OCTET type, 
                                ITS_ULONG number)
{
    ASN_Tag result = NULL;

    result = 
        (ASN_Tag)ITS_ConstructObject(
                            (ITS_Class)&itsASN_Tag_ClassRec, 
                            tagClass, 
                            type,
                            number);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_Tag_Destruct(ASN_Tag object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Tag 
ASN_Tag_Clone(const ASN_Tag object)
{
    return (ASN_Tag)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Tag_Equals(const ASN_Tag object, const ASN_Tag other)
{
    return ITS_CLASS_EQUALS(
        ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

int 
ASN_Tag_Encode(ASN_Tag object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_TAG_CLASS_ENCODE(
        ITS_OBJ_CLASS(object))(object, octets, encodeError);
}

int 
ASN_Tag_Decode(ASN_Tag object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_TAG_CLASS_DECODE(
        ITS_OBJ_CLASS(object))(object, octets, decodeError);
}

int 
ASN_Tag_DecodePreserveOffset(
                        ASN_Tag object, 
                        ASN_Octets octets, 
                        ASN_DecodeError* decodeError)
{
    return ASN_TAG_CLASS_DECODE_PRESERVE_OFFSET(
        ITS_OBJ_CLASS(object))(object, octets, decodeError);
}

void 
ASN_Tag_SetTagClass(ASN_Tag object, ITS_OCTET tagClass)
{
    ASN_TAG_CLASS_SET_TAG_CLASS(
        ITS_OBJ_CLASS(object))(object, tagClass);
}

void 
ASN_Tag_SetType(ASN_Tag object, ITS_OCTET type)
{
    ASN_TAG_CLASS_SET_TYPE(
        ITS_OBJ_CLASS(object))(object, type);
}

void 
ASN_Tag_SetNumber(ASN_Tag object, ITS_ULONG number)
{
    ASN_TAG_CLASS_SET_NUMBER(
        ITS_OBJ_CLASS(object))(object, number);
}

ITS_OCTET 
ASN_Tag_GetTagClass(const ASN_Tag object)
{
    return ASN_TAG_CLASS_GET_TAG_CLASS(
        ITS_OBJ_CLASS(object))(object);
}

ITS_OCTET 
ASN_Tag_GetType(const ASN_Tag object)
{
    return ASN_TAG_CLASS_GET_TYPE(
        ITS_OBJ_CLASS(object))(object);
}

ITS_ULONG 
ASN_Tag_GetNumber(const ASN_Tag object)
{
    return ASN_TAG_CLASS_GET_NUMBER(
        ITS_OBJ_CLASS(object))(object);
}

char* 
ASN_Tag_ToString(const ASN_Tag object)
{
    return ASN_TAG_CLASS_TO_STRING(
        ITS_OBJ_CLASS(object))(object);
}

void
ASN_Tag_Print(const ASN_Tag object)
{
    ITS_CLASS_PRINT(
        ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Tag_GetEncodeExtendedErrorText(const ASN_Tag object, ASN_Error error)
{
    return ASN_TAG_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(
        ITS_OBJ_CLASS(object))(object, error);
}

char* 
ASN_Tag_GetDecodeExtendedErrorText(
                                const ASN_Tag object, 
                                ASN_Error error, 
                                const ASN_Octets octets)
{
    return ASN_TAG_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(
        ITS_OBJ_CLASS(object))(object, error, octets);
}

ITS_BOOLEAN 
ASN_Tag_IsUniversal(const ASN_Tag object, ITS_ULONG number)
{
    return ASN_TAG_CLASS_IS_UNIVERSAL(
        ITS_OBJ_CLASS(object))(object, number);
}

ITS_BOOLEAN 
ASN_Tag_Invariant(const ASN_Tag object)
{
    return ASN_TAG_CLASS_INVARIANT(
        ITS_OBJ_CLASS(object))(object);
}

