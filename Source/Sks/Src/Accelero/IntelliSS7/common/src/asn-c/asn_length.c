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
 *  ID: $Id: asn_length.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_length.h>

#include <string.h>


/*
 *  Protected preprocessor constant definitions.
 */

#define LENGTH_INDEFINITE                       (-1)

#define LENGTH_INDEFINITE_FORM_VALUE            0x80U
#define LENGTH_SHORT_FORM_MAX_VALUE             0x7FU
#define LENGTH_LENGTH_MASK                      0x7FU
#define LENGTH_LONG_FORM_INDICATOR              0x80U

#define LENGTH_LONG_FORM_MAX_LENGTH             ASN_BYTES_PER_LONG

#define LENGTH_INDEFINITE_END_MARK_LENGTH       2
#define LENGTH_INDEFINITE_END_MARK_BYTE_ONE     0x00U
#define LENGTH_INDEFINITE_END_MARK_BYTE_TWO     0x00U


/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN Invariant(const ASN_Length object);


static int
Construct(ITS_Object object, va_list args)
{
    ITS_LONG length = 0;

    ASN_C_REQUIRE(object != NULL);

    length = va_arg(args, ITS_LONG);

    ASN_C_REQUIRE(length >= 0 || length == LENGTH_INDEFINITE);

    ASN_LENGTH_LENGTH(object) = length;

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

    if (ASN_LENGTH_LENGTH(object) != ASN_LENGTH_LENGTH(other))
    {
        return ITS_FALSE;
    }

    return ITS_TRUE;
}

static int 
Encode(ASN_Length object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    typedef ITS_OCTET byte;

    ITS_OCTET array[LENGTH_LONG_FORM_MAX_LENGTH + 1];

    int inc         = 0;
    ITS_LONG length = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    memset(array, 0x00U, LENGTH_LONG_FORM_MAX_LENGTH + 1);

    length = ASN_LENGTH_LENGTH(object);

    if (length == LENGTH_INDEFINITE)
    {
        array[0] = LENGTH_INDEFINITE_FORM_VALUE;
        inc = 1;
    }
    else if (length <= LENGTH_SHORT_FORM_MAX_VALUE)
    {
        array[0] = (byte)length;
        inc = 1;
    }
    else
    {
        ITS_BOOLEAN maxShrink   = ITS_FALSE;
        int i                   = 0;

        inc = 1;

        for(i = 1; i <= LENGTH_LONG_FORM_MAX_LENGTH; i++)
        {
            if (!maxShrink)
            {
                byte b = (byte)(((unsigned)length) >>
                                ((LENGTH_LONG_FORM_MAX_LENGTH - i) *
                                ASN_BITS_PER_BYTE));

                if (b == 0)
                {
                    continue;
                }
                else
                {
                    array[0] = LENGTH_LONG_FORM_INDICATOR;
                    array[0] |= LENGTH_LONG_FORM_MAX_LENGTH - (byte)(i - 1);
                    maxShrink = ITS_TRUE;
                }
            }

            array[inc] = (byte)(((unsigned)length) >>
                                ((LENGTH_LONG_FORM_MAX_LENGTH - i) *
                                ASN_BITS_PER_BYTE));

            inc++;
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
Decode(ASN_Length object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    ITS_OCTET b         = 0;
    ITS_LONG  length    = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    if (!ASN_Octets_IsIndexWithOffsetValid(octets, 0))
    {
        *decodeError = 
            ASN_CONSTRUCT_LENGTH_DECODE_ERROR(
                ASN_E_INVALID_LENGTH_LENGTH, 
                object, 
                octets);

        return ITS_E_ASN_DECODE_ERROR;
    }

    b = ASN_Octets_GetOctetAtWithOffset(octets, 0);

    if (b == LENGTH_INDEFINITE_FORM_VALUE)
    {
        length = LENGTH_INDEFINITE;
        ASN_Octets_IncrementOffset(octets);

        ASN_LENGTH_LENGTH(object) = length;
    }
    else if (!(b & LENGTH_LONG_FORM_INDICATOR))
    {
        length = b;
        ASN_Octets_IncrementOffset(octets);

        ASN_LENGTH_LENGTH(object) = length;
    }
    else
    {
        byte ll = (byte)(b & LENGTH_LENGTH_MASK);
        int i   = 0;

        length = 0;

        for (i = 1; i <= ll; i++)
        {
            if (!ASN_Octets_IsIndexWithOffsetValid(octets, i))
            {
                *decodeError = 
                    ASN_CONSTRUCT_LENGTH_DECODE_ERROR(
                        ASN_E_INVALID_LENGTH_LENGTH, 
                        object, 
                        octets);

                return ITS_E_ASN_DECODE_ERROR;
            }

            length |= ((ITS_LONG)ASN_Octets_GetOctetAtWithOffset(octets, i) &
                       ASN_BYTE_MASK_IN_LONG) << (ASN_BITS_PER_BYTE * (ll - i));
        }

        ASN_Octets_IncrementOffsetWithIncrement(octets, 1 + ll);

        ASN_LENGTH_LENGTH(object) = length;
    }

    return ITS_SUCCESS;
}

static int 
DecodePreserveOffset(
                ASN_Length object, 
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
SetLength(ASN_Length object, ITS_LONG length)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_LENGTH_LENGTH(object) = length;
}

static ITS_LONG 
GetLength(const ASN_Length object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LENGTH_LENGTH(object);
}

static ITS_BOOLEAN 
IsIndefinite(const ASN_Length object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LENGTH_LENGTH(object) == LENGTH_INDEFINITE;
}

static ITS_BOOLEAN 
IsIndefiniteEndMark(const ASN_Length object, const ASN_Octets octets)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);

    ASN_C_ASSERT(not_implemented);

    return ITS_FALSE;
}

static void 
IndefiniteEndMarkIncOffset(const ASN_Length object, ASN_Octets octets)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);

    ASN_Octets_IncrementOffsetWithIncrement(
                                    octets, 
                                    LENGTH_INDEFINITE_END_MARK_LENGTH);
}

static char* 
ToString(const ASN_Length object)
{
    char* result                = NULL;
    char* buffer                = NULL;
    size_t maxStringSize        = 0;

    ASN_C_REQUIRE(object != NULL);

    /* Absolute maximum. */

    maxStringSize = 32;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "[ %ld ]",
        ASN_LENGTH_LENGTH(object));

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void
Print(ITS_Object object)
{
    char* toString = NULL;

    ASN_C_REQUIRE(object != NULL);

    toString = ToString((ASN_Length)object);

    if (toString != NULL)
    {
        printf("%s", toString);

        free(toString);
    }
}

static char* 
GetEncodeExtendedErrorText(const ASN_Length object, ASN_Error error)
{
    ASN_C_REQUIRE(object != NULL);

    return strdup("No extended encode error text available for Length.");
}

static char* 
GetDecodeExtendedErrorText(
                        const ASN_Length object, 
                        ASN_Error error, 
                        const ASN_Octets octets)
{
    ASN_C_REQUIRE(object != NULL);

    return strdup("No extended decode error text available for Length.");
}


/*
 *  ASN_Length class record.
 */ 

ASN_Length_ClassRec itsASN_Length_ClassRec =
{
    /* Core part. */

    {
        &itsCORE_ClassRec,         
        sizeof(ASN_Length_ObjectRec), 
        ITS_FALSE,                 
        0,                         
        ASN_LENGTH_CLASS_NAME,        
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

    /* ASN_Length class part. */

    {
        Encode,
        Decode,
        DecodePreserveOffset,
        SetLength,
        GetLength,
        IsIndefinite,
        IsIndefiniteEndMark,
        IndefiniteEndMarkIncOffset,
        ToString,
        GetEncodeExtendedErrorText,
        GetDecodeExtendedErrorText
    }
};


ASN_Length 
ASN_Length_ConstructDefault()
{
    ASN_Length result = NULL;

    result = 
        (ASN_Length)ITS_ConstructObject(
                            (ITS_Class)&itsASN_Length_ClassRec, 
                            0);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Length 
ASN_Length_ConstructWithLength(ITS_LONG length)
{
    ASN_Length result = NULL;

    result = 
        (ASN_Length)ITS_ConstructObject(
                            (ITS_Class)&itsASN_Length_ClassRec, 
                            length);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_Length_Destruct(ASN_Length object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Length 
ASN_Length_Clone(const ASN_Length object)
{
    return (ASN_Length)ITS_CLASS_CLONE(
        ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Length_Equals(const ASN_Length object, const ASN_Length other)
{
    return ITS_CLASS_EQUALS(
        ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

int 
ASN_Length_Encode(
                ASN_Length object, 
                ASN_Octets* octets, 
                ASN_EncodeError* encodeError)
{
    return ASN_LENGTH_CLASS_ENCODE(
        ITS_OBJ_CLASS(object))(object, octets, encodeError);
}

int 
ASN_Length_Decode(
                ASN_Length object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError)
{
    return ASN_LENGTH_CLASS_DECODE(
        ITS_OBJ_CLASS(object))(object, octets, decodeError);
}

int 
ASN_Length_DecodePreserveOffset(
                        ASN_Length object, 
                        ASN_Octets octets, 
                        ASN_DecodeError* decodeError)
{
    return ASN_LENGTH_CLASS_DECODE_PRESERVE_OFFSET(
        ITS_OBJ_CLASS(object))(object, octets, decodeError);
}

void 
ASN_Length_SetLength(ASN_Length object, ITS_LONG length)
{
    ASN_LENGTH_CLASS_SET_LENGTH(
        ITS_OBJ_CLASS(object))(object, length);
}

ITS_LONG 
ASN_Length_GetLength(const ASN_Length object)
{
    return ASN_LENGTH_CLASS_GET_LENGTH(
        ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN
ASN_Length_IsIndefinite(const ASN_Length object)
{
    return ASN_LENGTH_CLASS_IS_INDEFINITE(
        ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN 
ASN_Length_IsIndefiniteEndMark(
                            const ASN_Length object,
                            const ASN_Octets octets)
{
    return ASN_LENGTH_CLASS_IS_INDEFINITE_END_MARK(
        ITS_OBJ_CLASS(object))(object, octets);
}

void 
ASN_Length_IndefiniteEndMarkIncOffset(
                                const ASN_Length object,
                                ASN_Octets octets)
{
    ASN_LENGTH_CLASS_INDEFINITE_END_MARK_INC_OFFSET(
        ITS_OBJ_CLASS(object))(object, octets);
}

char* 
ASN_Length_ToString(const ASN_Length object)
{
    return ASN_LENGTH_CLASS_TO_STRING(
        ITS_OBJ_CLASS(object))(object);
}

void
ASN_Length_Print(const ASN_Length object)
{
    ITS_CLASS_PRINT(
        ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Length_GetEncodeExtendedErrorText(const ASN_Length object, ASN_Error error)
{
    return ASN_LENGTH_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(
        ITS_OBJ_CLASS(object))(object, error);
}

char* 
ASN_Length_GetDecodeExtendedErrorText(
                                const ASN_Length object, 
                                ASN_Error error, 
                                const ASN_Octets octets)
{
    return ASN_LENGTH_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(
        ITS_OBJ_CLASS(object))(object, error, octets);
}

