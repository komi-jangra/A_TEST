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
 *  ID: $Id: asn_null.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_null.h>
#include <asn_desc_null.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
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

static ASN_DescNull GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ASN_DescNull description = NULL;

    description = va_arg(args, ASN_DescNull);

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

    return ITS_TRUE;
}

static ASN_DescNull staticDescription = NULL;

static ASN_DescNull
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescNull result      = NULL;
    ASN_Null cloneForFactory        = NULL;
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

        staticDescription = ASN_DescNull_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Null_ConstructWithDescription(staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescNull_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescNull_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_Null_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescNull_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescNull_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescNull_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static ASN_Tag
GetUniversalTag(const ASN_Null object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_NULL);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescNull description    = NULL;
    ASN_Octets valOctets        = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescNull)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    /* Encode check begin. */

    /* Nothing to do. */

    /* Encode check end. */

    valOctets = ASN_Octets_ConstructDefault();

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
    ASN_DescNull description    = NULL;
    ASN_Tag tag                 = NULL;
    ASN_Length length           = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescNull)ASN_OBJECT_DESCRIPTION(object);

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

    if (ASN_Length_GetLength(length) != 0)
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INVALID_NULL_LENGTH, 
                object, 
                octets);

        ASN_Length_Destruct(length);

        return ITS_E_ASN_DECODE_ERROR;
    }

    ASN_Length_Destruct(length);

    /* Decode check begin. */

    /* Nothing to do. */

    /* Decode check end. */

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    return "NULL";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "NULL";
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

    maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 16;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "%s (%s)\n[ ]\n",
        nameStr,
        baseNameStr);

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_Null class record.
 */ 

ASN_Null_ClassRec itsASN_Null_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec, 
        sizeof(ASN_Null_ObjectRec),      
        ITS_FALSE,                          
        0,                                  
        ASN_NULL_CLASS_NAME,             
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

    /* ASN_Null class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetUniversalTag
    }
};


ASN_Null 
ASN_Null_ConstructDefault()
{
    ASN_Null result = NULL;

    result = (ASN_Null)ITS_ConstructObject((ITS_Class)&itsASN_Null_ClassRec, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Null
ASN_Null_ConstructWithDescription(ASN_DescNull description)
{
    ASN_Null result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_Null)ITS_ConstructObject((ITS_Class)&itsASN_Null_ClassRec, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Null_Destruct(ASN_Null object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Null 
ASN_Null_Clone(const ASN_Null object)
{
    return (ASN_Null)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Null_Equals(const ASN_Null object, const ASN_Null other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescNull 
ASN_Null_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Null_DestructStaticDescription()
{
    DestructStaticDescription();
}

ASN_Tag 
ASN_Null_GetUniversalTag(const ASN_Null object)
{
    return ASN_NULL_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Null_Encode(ASN_Null object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Null_Decode(ASN_Null object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Null_GetName(const ASN_Null object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Null_GetBaseName(const ASN_Null object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Null_Print(const ASN_Null object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Null_ToString(const ASN_Null object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

