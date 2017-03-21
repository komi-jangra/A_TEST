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
 *  ID: $Id: asn_enumerated.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_enumerated.h>
#include <asn_desc_enumerated.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_ENUMERATED_CLASS_GET_VALUE(subClass) == ASN_ENUMERATED_GET_VALUE_INHERIT)
    {
        ASN_ENUMERATED_CLASS_GET_VALUE(subClass) =
            ASN_ENUMERATED_CLASS_GET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ENUMERATED_CLASS_SET_VALUE(subClass) == ASN_ENUMERATED_SET_VALUE_INHERIT)
    {
        ASN_ENUMERATED_CLASS_SET_VALUE(subClass) =
            ASN_ENUMERATED_CLASS_SET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_ENUMERATED_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_ENUMERATED_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_ENUMERATED_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_ENUMERATED_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescEnumerated GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ITS_LONG value                  = 0;
    ASN_DescEnumerated description  = NULL;

    value = va_arg(args, ITS_LONG);

    description = va_arg(args, ASN_DescEnumerated);

    ASN_ENUMERATED_VALUE(object) = value;

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

    if (ASN_ENUMERATED_VALUE(object) != ASN_ENUMERATED_VALUE(other))
    {
        return ITS_FALSE;
    }

    return ITS_TRUE;
}

static ASN_DescEnumerated staticDescription = NULL;

static ASN_DescEnumerated
GetStaticDescription()
{
    static ITS_BOOLEAN initialized      = ITS_FALSE;
    static ASN_DescEnumerated result    = NULL;
    ASN_Enumerated cloneForFactory      = NULL;
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

        staticDescription = ASN_DescEnumerated_ConstructWithSize(0);

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Enumerated_ConstructWithValueDescription(0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescEnumerated_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescEnumerated_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_Enumerated_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescEnumerated_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescEnumerated_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescEnumerated_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static ITS_LONG
GetValue(const ASN_Enumerated object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_ENUMERATED_VALUE(object);
}

static void 
SetValue(ASN_Enumerated object, ITS_LONG value)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_ENUMERATED_VALUE(object) = value;
}

static ITS_LONG 
GetValueFromValueName(const ASN_Enumerated object, const char* valueName)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return 0;
}

static const char* 
GetValueNameFromValue(const ASN_Enumerated object, ITS_LONG value)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return NULL;
}

static ASN_Tag
GetUniversalTag(const ASN_Enumerated object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_ENUMERATED);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescEnumerated description = NULL;

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

    description = (ASN_DescEnumerated)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    memset(array, 0x00U, ASN_BYTES_PER_LONG);

    value = ASN_ENUMERATED_VALUE(object);

    /* Encode check begin. */

    if (!ASN_Options_GlobalIsEncodeSkipInvalidEnumeratedValue())
    {
        if (!ASN_DescEnumerated_Contains(description, value))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_ENUMERATED_VALUE, 
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

    int res                         = ITS_SUCCESS;
    ASN_DescEnumerated description  = NULL;
    ASN_Tag tag                     = NULL;
    ASN_Length length               = NULL;
    ITS_LONG value                  = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescEnumerated)ASN_OBJECT_DESCRIPTION(object);

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
                ASN_E_NULL_ENUMERATED_LENGTH,
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
                    ASN_E_INVALID_ENUMERATED_LENGTH,
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
                        ASN_E_INVALID_ENUMERATED_LENGTH,
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

    ASN_ENUMERATED_VALUE(object) = value;

    /* Decode check begin. */

    if (!ASN_Options_GlobalIsDecodeSkipInvalidEnumeratedValue())
    {
        if (!ASN_DescEnumerated_Contains(description, value))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_ENUMERATED_VALUE, 
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
    return "ENUMERATED";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "ENUMERATED";
}

static char*
ToString(const ASN_Object object)
{
    char* result                    = NULL;
    char* buffer                    = NULL;
    const char* nameStr             = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr         = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);
    size_t maxStringSize            = 0;
    ASN_DescEnumerated description  = NULL;
    const char* valueNameStr        = NULL;

    ASN_C_REQUIRE(object != NULL);

    description = (ASN_DescEnumerated)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    if (ASN_DescEnumerated_Contains(description, ASN_ENUMERATED_VALUE(object)))
    {
        valueNameStr = ASN_Enumerated_GetValueNameFromValue(
                                        (ASN_Enumerated)object, 
                                        ASN_ENUMERATED_VALUE(object));

        maxStringSize = strlen(nameStr) + strlen(baseNameStr) + strlen(valueNameStr) + 32;
    }
    else
    {
        maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 32;
    }

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    if (ASN_DescEnumerated_Contains(description, ASN_ENUMERATED_VALUE(object)))
    {
        sprintf(
            buffer,
            "%s (%s)\n[ %s(%ld) ]\n",
            nameStr,
            baseNameStr,
            valueNameStr,
            ASN_ENUMERATED_VALUE(object));
    }
    else
    {
        sprintf(
            buffer,
            "%s (%s)\n[ (%ld) ]\n",
            nameStr,
            baseNameStr,
            ASN_ENUMERATED_VALUE(object));
    }

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_Enumerated class record.
 */ 

ASN_Enumerated_ClassRec itsASN_Enumerated_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,
        sizeof(ASN_Enumerated_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_ENUMERATED_CLASS_NAME,         
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

    /* ASN_Enumerated class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetValue,
        SetValue,
        GetValueFromValueName,
        GetValueNameFromValue,
        GetUniversalTag
    }
};


ASN_Enumerated 
ASN_Enumerated_ConstructDefault()
{
    ASN_Enumerated result = NULL;

    result = (ASN_Enumerated)ITS_ConstructObject((ITS_Class)&itsASN_Enumerated_ClassRec, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Enumerated 
ASN_Enumerated_ConstructWithValue(ITS_LONG value)
{
    ASN_Enumerated result = NULL;

    result = (ASN_Enumerated)ITS_ConstructObject((ITS_Class)&itsASN_Enumerated_ClassRec, value, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Enumerated
ASN_Enumerated_ConstructWithValueDescription(ITS_LONG value, ASN_DescEnumerated description)
{
    ASN_Enumerated result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_Enumerated)ITS_ConstructObject((ITS_Class)&itsASN_Enumerated_ClassRec, value, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Enumerated_Destruct(ASN_Enumerated object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Enumerated 
ASN_Enumerated_Clone(const ASN_Enumerated object)
{
    return (ASN_Enumerated)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Enumerated_Equals(const ASN_Enumerated object, const ASN_Enumerated other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescEnumerated 
ASN_Enumerated_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Enumerated_DestructStaticDescription()
{
    DestructStaticDescription();
}

ITS_LONG
ASN_Enumerated_GetValue(const ASN_Enumerated object)
{
    return ASN_ENUMERATED_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))(object);
}

void
ASN_Enumerated_SetValue(ASN_Enumerated object, ITS_LONG value)
{
    ASN_ENUMERATED_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))(object, value);
}

ITS_LONG 
ASN_Enumerated_GetValueFromValueName(const ASN_Enumerated object, const char* valueName)
{
    return ASN_ENUMERATED_CLASS_GET_VALUE_FROM_VALUE_NAME(ITS_OBJ_CLASS(object))(object, valueName);
}

const char* 
ASN_Enumerated_GetValueNameFromValue(const ASN_Enumerated object, ITS_LONG value)
{
    return ASN_ENUMERATED_CLASS_GET_VALUE_NAME_FROM_VALUE(ITS_OBJ_CLASS(object))(object, value);
}

ASN_Tag 
ASN_Enumerated_GetUniversalTag(const ASN_Enumerated object)
{
    return ASN_ENUMERATED_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Enumerated_Encode(ASN_Enumerated object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Enumerated_Decode(ASN_Enumerated object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Enumerated_GetName(const ASN_Enumerated object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Enumerated_GetBaseName(const ASN_Enumerated object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Enumerated_Print(const ASN_Enumerated object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Enumerated_ToString(const ASN_Enumerated object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

