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
 *  ID: $Id: asn_real.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_real.h>
#include <asn_desc_real.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_REAL_CLASS_GET_VALUE(subClass) == ASN_REAL_GET_VALUE_INHERIT)
    {
        ASN_REAL_CLASS_GET_VALUE(subClass) =
            ASN_REAL_CLASS_GET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_REAL_CLASS_SET_VALUE(subClass) == ASN_REAL_SET_VALUE_INHERIT)
    {
        ASN_REAL_CLASS_SET_VALUE(subClass) =
            ASN_REAL_CLASS_SET_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_REAL_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_REAL_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_REAL_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_REAL_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescReal GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    double value                = 0;
    ASN_DescReal description    = NULL;

    value = va_arg(args, double);

    description = va_arg(args, ASN_DescReal);

    ASN_REAL_VALUE(object) = value;

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

    if (ASN_REAL_VALUE(object) != ASN_REAL_VALUE(other))
    {
        return ITS_FALSE;
    }

    return ITS_TRUE;
}

static ASN_DescReal staticDescription = NULL;

static ASN_DescReal
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescReal result      = NULL;
    ASN_Real cloneForFactory        = NULL;
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

        staticDescription = ASN_DescReal_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Real_ConstructWithValueDescription(0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescReal_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescReal_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_Real_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescReal_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescReal_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescReal_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

static double
GetValue(const ASN_Real object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_REAL_VALUE(object);
}

static void 
SetValue(ASN_Real object, double value)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_REAL_VALUE(object) = value;
}

static ASN_Tag
GetUniversalTag(const ASN_Real object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_REAL);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescReal description = NULL;

    double value            = 0;
    ASN_Octets valOctets    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescReal)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    value = ASN_REAL_VALUE(object);

    /* Encode check begin. */

    if (ASN_DescReal_IsClauseRange(description))
    {
        if (value > ASN_DescReal_GetMaxValue(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_REAL_VALUE_OUT_OF_RANGE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
        
        if (value < ASN_DescReal_GetMinValue(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_REAL_VALUE_OUT_OF_RANGE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
    }

    /* Encode check end. */

    {
        ITS_BOOLEAN not_implemented = ITS_FALSE;
        ASN_C_ASSERT(not_implemented);
    }

    return ITS_SUCCESS;
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                     = ITS_SUCCESS;
    ASN_DescReal description    = NULL;
    ASN_Tag tag                 = NULL;
    ASN_Length length           = NULL;
    double value                = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescReal)ASN_OBJECT_DESCRIPTION(object);

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

    ASN_Length_Destruct(length);
    length = NULL;

    {
        ITS_BOOLEAN not_implemented = ITS_FALSE;
        ASN_C_ASSERT(not_implemented);
    }

    /* Decode check begin. */

    if (ASN_DescReal_IsClauseRange(description))
    {
        if (value > ASN_DescReal_GetMaxValue(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_REAL_VALUE_OUT_OF_RANGE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
        
        if (value < ASN_DescReal_GetMinValue(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_REAL_VALUE_OUT_OF_RANGE, 
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
    return "REAL";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "REAL";
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
        "%s (%s)\n[ %f ]\n",
        nameStr,
        baseNameStr,
        ASN_REAL_VALUE(object));

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_Real class record.
 */ 

ASN_Real_ClassRec itsASN_Real_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec, /* ASN_Object is superclass.    */
        sizeof(ASN_Real_ObjectRec),      /* Size of instance.            */
        ITS_FALSE,                          /* Not initted.                 */
        0,                                  /* Initial reference count.     */
        ASN_REAL_CLASS_NAME,             /* Class name.                  */
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

    /* ASN_Real class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetValue,
        SetValue,
        GetUniversalTag
    }
};


ASN_Real 
ASN_Real_ConstructDefault()
{
    ASN_Real result = NULL;

    result = (ASN_Real)ITS_ConstructObject((ITS_Class)&itsASN_Real_ClassRec, 0, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Real 
ASN_Real_ConstructWithValue(double value)
{
    ASN_Real result = NULL;

    result = (ASN_Real)ITS_ConstructObject((ITS_Class)&itsASN_Real_ClassRec, value, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Real
ASN_Real_ConstructWithValueDescription(double value, ASN_DescReal description)
{
    ASN_Real result = NULL;

    ASN_C_REQUIRE(description != NULL);

    result = (ASN_Real)ITS_ConstructObject((ITS_Class)&itsASN_Real_ClassRec, value, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Real_Destruct(ASN_Real object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Real 
ASN_Real_Clone(const ASN_Real object)
{
    return (ASN_Real)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Real_Equals(const ASN_Real object, const ASN_Real other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescReal 
ASN_Real_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Real_DestructStaticDescription()
{
    DestructStaticDescription();
}

double
ASN_Real_GetValue(const ASN_Real object)
{
    return ASN_REAL_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))(object);
}

void
ASN_Real_SetValue(ASN_Real object, double value)
{
    ASN_REAL_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))(object, value);
}

ASN_Tag 
ASN_Real_GetUniversalTag(const ASN_Real object)
{
    return ASN_REAL_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Real_Encode(ASN_Real object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Real_Decode(ASN_Real object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Real_GetName(const ASN_Real object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Real_GetBaseName(const ASN_Real object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Real_Print(const ASN_Real object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Real_ToString(const ASN_Real object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



      

 

 

