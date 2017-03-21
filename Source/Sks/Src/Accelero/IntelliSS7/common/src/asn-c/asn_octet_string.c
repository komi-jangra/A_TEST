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
 *  ID: $Id: asn_octet_string.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_octet_string.h>
#include <asn_desc_octet_string.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_OCTET_STRING_CLASS_GET_ARRAY(subClass) == ASN_OCTET_STRING_GET_ARRAY_INHERIT)
    {
        ASN_OCTET_STRING_CLASS_GET_ARRAY(subClass) =
            ASN_OCTET_STRING_CLASS_GET_ARRAY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OCTET_STRING_CLASS_SET_ARRAY(subClass) == ASN_OCTET_STRING_SET_ARRAY_INHERIT)
    {
        ASN_OCTET_STRING_CLASS_SET_ARRAY(subClass) =
            ASN_OCTET_STRING_CLASS_SET_ARRAY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OCTET_STRING_CLASS_GET_SIZE(subClass) == ASN_OCTET_STRING_GET_SIZE_INHERIT)
    {
        ASN_OCTET_STRING_CLASS_GET_SIZE(subClass) =
            ASN_OCTET_STRING_CLASS_GET_SIZE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OCTET_STRING_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_OCTET_STRING_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_OCTET_STRING_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_OCTET_STRING_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescOctetString GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ITS_OCTET* array                = NULL;
    size_t size                     = 0;
    ASN_DescOctetString description = NULL;

    array = va_arg(args, ITS_OCTET*);
    size = va_arg(args, size_t);

    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    description = va_arg(args, ASN_DescOctetString);

    if (array != NULL && size != 0)
    {
        ASN_OCTET_STRING_DATA(object) = (ITS_OCTET*)calloc(size, sizeof(ITS_OCTET));

        ASN_C_ENSURE(ASN_OCTET_STRING_DATA(object) != NULL);

        if (ASN_OCTET_STRING_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_OCTET_STRING_DATA(object), array, size * sizeof (ITS_OCTET));
        ASN_OCTET_STRING_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_OCTET_STRING_DATA(object) = NULL;
        ASN_OCTET_STRING_SIZE(object) = 0;
    }

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            if (ASN_OCTET_STRING_DATA(object) != NULL)
            {
                free(ASN_OCTET_STRING_DATA(object));
                ASN_OCTET_STRING_DATA(object) = NULL;
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

    if (ASN_OCTET_STRING_DATA(object) != NULL)
    {
        free(ASN_OCTET_STRING_DATA(object));
        ASN_OCTET_STRING_DATA(object) = NULL;
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

    if (ASN_OCTET_STRING_SIZE(object) > 0)
    {
        ASN_OCTET_STRING_DATA(result) = (ITS_OCTET*)calloc(ASN_OCTET_STRING_SIZE(object), sizeof(ITS_OCTET));

        ASN_C_ENSURE(ASN_OCTET_STRING_DATA(result) != NULL);

        if (ASN_OCTET_STRING_DATA(result) == NULL)
        {
            free(result);

            return NULL;
        }

        memcpy(ASN_OCTET_STRING_DATA(result), ASN_OCTET_STRING_DATA(object), ASN_OCTET_STRING_SIZE(object));
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

    if (ASN_OCTET_STRING_SIZE(object) != ASN_OCTET_STRING_SIZE(other))
    {
        return ITS_FALSE;
    }

    if (memcmp(
            ASN_OCTET_STRING_DATA(object),
            ASN_OCTET_STRING_DATA(other),
            ASN_OCTET_STRING_SIZE(object)) == 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ASN_DescOctetString staticDescription = NULL;

static ASN_DescOctetString
GetStaticDescription()
{
    static ITS_BOOLEAN initialized      = ITS_FALSE;
    static ASN_DescOctetString result   = NULL;
    ASN_OctetString cloneForFactory     = NULL;
    ASN_Tag universalTag                = NULL;

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

        staticDescription = ASN_DescOctetString_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_OctetString_ConstructWithArraySizeDescription(NULL, 0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescOctetString_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescOctetString_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_OctetString_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescOctetString_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescOctetString_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescOctetString_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static const ITS_OCTET* 
GetArray(const ASN_OctetString object)
{
    const ITS_OCTET* result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_OCTET_STRING_SIZE(object) > 0);

    result = ASN_OCTET_STRING_DATA(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static size_t 
GetSize(const ASN_OctetString object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_OCTET_STRING_SIZE(object);
}

static int 
SetArray(ASN_OctetString object, const ITS_OCTET* array, size_t size)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    if (ASN_OCTET_STRING_DATA(object) != NULL)
    {
        free(ASN_OCTET_STRING_DATA(object));
        ASN_OCTET_STRING_DATA(object) = NULL;
    }

    if (array != NULL && size != 0)
    {
        ASN_OCTET_STRING_DATA(object) = (ITS_OCTET*)calloc(size, sizeof(ITS_OCTET));

        ASN_C_ENSURE(ASN_OCTET_STRING_DATA(object) != NULL);

        if (ASN_OCTET_STRING_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_OCTET_STRING_DATA(object), array, size * sizeof (ITS_OCTET));
        ASN_OCTET_STRING_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_OCTET_STRING_DATA(object) = NULL;
        ASN_OCTET_STRING_SIZE(object) = 0;
    }

    return ITS_SUCCESS;
}

static ASN_Tag
GetUniversalTag(const ASN_OctetString object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_OCTET_STRING);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescOctetString description = NULL;

    ITS_OCTET* data         = NULL;
    size_t size             = 0;
    ASN_Octets valOctets    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescOctetString)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    data = ASN_OCTET_STRING_DATA(object);
    size = ASN_OCTET_STRING_SIZE(object);

    ASN_C_ASSERT((data == NULL && size == 0) || (data != NULL && size != 0))

    /* Encode check begin. */

    if (ASN_DescOctetString_IsClauseSize(description))
    {
        if (size > ASN_DescOctetString_GetMaxSize(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_OCTET_STRING_SIZE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
        
        if (size < ASN_DescOctetString_GetMinSize(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_OCTET_STRING_SIZE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
    }

    /* Encode check end. */

    valOctets = ASN_Octets_ConstructWithArray(data, size);

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

    int res                         = ITS_SUCCESS;
    ASN_DescOctetString description = NULL;
    ASN_Tag tag                     = NULL;
    ASN_Length length               = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescOctetString)ASN_OBJECT_DESCRIPTION(object);

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
                ASN_E_CONSTRUCTED_OCTET_STRING, 
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
                ASN_E_INDEFINITE_OCTET_STRING_LENGTH, 
                object, 
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }
    else if (ASN_Length_GetLength(length) == 0)
    {
        if (ASN_OCTET_STRING_DATA(object) != NULL)
        {
            free(ASN_OCTET_STRING_DATA(object));
        }

        ASN_OCTET_STRING_DATA(object) = NULL;
        ASN_OCTET_STRING_SIZE(object) = 0;
    }
    else
    {
        int i   = 0;
        byte b  = 0;

        if (ASN_OCTET_STRING_DATA(object) != NULL)
        {
            free(ASN_OCTET_STRING_DATA(object));
        }

        ASN_OCTET_STRING_DATA(object) = 
            (ITS_OCTET*)calloc(ASN_Length_GetLength(length), sizeof(ITS_OCTET));

        ASN_C_ENSURE(ASN_OCTET_STRING_DATA(object) != NULL);

        if (ASN_OCTET_STRING_DATA(object) == NULL)
        {
            ASN_Length_Destruct(length);

            return ITS_ENOMEM;
        }

        for (i = 0; i < ASN_Length_GetLength(length); i++)
        {
            if (!ASN_Octets_IsIndexWithOffsetValid(octets, i))
            {
                *decodeError =
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_INVALID_OCTET_STRING_LENGTH,
                        object,
                        octets);

                ASN_Length_Destruct(length);

                return ITS_E_ASN_DECODE_ERROR;
            }

            b = ASN_Octets_GetOctetAtWithOffset(octets, i);

            ASN_OCTET_STRING_DATA(object)[i] = b;
        }

        ASN_OCTET_STRING_SIZE(object) = ASN_Length_GetLength(length);
                
        ASN_Octets_IncrementOffsetWithIncrement(
                                            octets, 
                                            ASN_Length_GetLength(length));
    }

    ASN_Length_Destruct(length);

    /* Decode check begin. */

    if (ASN_DescOctetString_IsClauseSize(description) && 
        !ASN_Options_GlobalIsDecodeIgnoreOctetStringSizeConstraint())
    {
        if (ASN_OCTET_STRING_SIZE(object) > 
            ASN_DescOctetString_GetMaxSize(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_OCTET_STRING_SIZE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
        
        if (ASN_OCTET_STRING_SIZE(object) < 
            ASN_DescOctetString_GetMinSize(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_OCTET_STRING_SIZE, 
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
    return "OCTET STRING";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "OCTET STRING";
}

static char*
ToString(const ASN_Object object)
{
    char* result                = NULL;
    static const int ROW_LENGTH = 10;
    int divisor                 = 0;
    int quotient                = 0;
    int remainder               = 0;
    int i                       = 0;
    int j                       = 0;
    char* buffer                = NULL;
    size_t maxStringSize        = 0;
    const char* nameStr         = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr     = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_OCTET_STRING_SIZE(object) >= 0);

    divisor = ROW_LENGTH;

    ASN_C_ASSERT(divisor > 1);

    quotient    = ASN_OCTET_STRING_SIZE(object) / divisor;
    remainder   = ASN_OCTET_STRING_SIZE(object) % divisor;

    /* Absolute maximum. */

    maxStringSize = strlen(nameStr) + 
                    strlen(baseNameStr) + 
                    (ASN_OCTET_STRING_SIZE(object) + divisor) * 4 + 
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
            sprintf(buffer, "%02X", ASN_OCTET_STRING_DATA(object)[i * divisor + j]);
            buffer += 2;
            sprintf(buffer, " ");
            buffer += 1;
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
        sprintf(buffer, "%02X", ASN_OCTET_STRING_DATA(object)[i * divisor + j]);
        buffer += 2;
        sprintf(buffer, " ");
        buffer += 1;
    }

    if (remainder != 0 && quotient != 0)
    {
        for (j = 0; j < divisor - remainder; j++)
        {
            sprintf(buffer, "   ");
            buffer += 3;
        }
    }

    sprintf(buffer, "]\n");
    buffer += 2;

    sprintf(buffer, "\0");
    buffer += 1;

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_OctetString class record.
 */ 

ASN_OctetString_ClassRec itsASN_OctetString_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec, /* ASN_Object is superclass.    */
        sizeof(ASN_OctetString_ObjectRec),  /* Size of instance.            */
        ITS_FALSE,                          /* Not initted.                 */
        0,                                  /* Initial reference count.     */
        ASN_OCTET_STRING_CLASS_NAME,        /* Class name.                  */
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

    /* ASN_OctetString class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetArray,
        SetArray,
        GetSize,
        GetUniversalTag
    }
};

ASN_OctetString 
ASN_OctetString_ConstructDefault()
{
    ASN_OctetString result = NULL;

    result = (ASN_OctetString)ITS_ConstructObject((ITS_Class)&itsASN_OctetString_ClassRec, NULL, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_OctetString 
ASN_OctetString_ConstructWithArraySize(const ITS_OCTET* array, size_t size)
{
    ASN_OctetString result = NULL;

    result = (ASN_OctetString)ITS_ConstructObject((ITS_Class)&itsASN_OctetString_ClassRec, array, size, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_OctetString
ASN_OctetString_ConstructWithArraySizeDescription(const ITS_OCTET* array, size_t size, ASN_DescOctetString description)
{
    ASN_OctetString result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_OctetString)ITS_ConstructObject((ITS_Class)&itsASN_OctetString_ClassRec, array, size, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_OctetString_Destruct(ASN_OctetString object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_OctetString 
ASN_OctetString_Clone(const ASN_OctetString object)
{
    return (ASN_OctetString)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_OctetString_Equals(const ASN_OctetString object, const ASN_OctetString other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescOctetString 
ASN_OctetString_GetStaticDescription()
{
    return GetStaticDescription();
}

void 
ASN_OctetString_DestructStaticDescription()
{
    DestructStaticDescription();
}

const ITS_OCTET* 
ASN_OctetString_GetArray(const ASN_OctetString object)
{
    return ASN_OCTET_STRING_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_OctetString_GetSize(const ASN_OctetString object)
{
    return ASN_OCTET_STRING_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_OctetString_SetArray(ASN_OctetString object, const ITS_OCTET* array, size_t size)
{
    return ASN_OCTET_STRING_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))(object, array, size);
}

ASN_Tag 
ASN_OctetString_GetUniversalTag(const ASN_OctetString object)
{
    return ASN_OCTET_STRING_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_OctetString_Encode(ASN_OctetString object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_OctetString_Decode(ASN_OctetString object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_OctetString_GetName(const ASN_OctetString object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_OctetString_GetBaseName(const ASN_OctetString object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_OctetString_Print(const ASN_OctetString object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_OctetString_ToString(const ASN_OctetString object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

