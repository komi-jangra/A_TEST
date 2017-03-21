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
 *  ID: $Id: asn_object.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_length.h>


static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_OBJECT_CLASS_ENCODE(subClass) == ASN_OBJECT_ENCODE_INHERIT)
    {
        ASN_OBJECT_CLASS_ENCODE(subClass) = 
            ASN_OBJECT_CLASS_ENCODE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_DECODE(subClass) == ASN_OBJECT_DECODE_INHERIT)
    {
        ASN_OBJECT_CLASS_DECODE(subClass) = 
            ASN_OBJECT_CLASS_DECODE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_GET_NAME(subClass) == ASN_OBJECT_GET_NAME_INHERIT)
    {
        ASN_OBJECT_CLASS_GET_NAME(subClass) = 
            ASN_OBJECT_CLASS_GET_NAME(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_GET_BASE_NAME(subClass) == ASN_OBJECT_GET_BASE_NAME_INHERIT)
    {
        ASN_OBJECT_CLASS_GET_BASE_NAME(subClass) = 
            ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_TO_STRING(subClass) == ASN_OBJECT_TO_STRING_INHERIT)
    {
        ASN_OBJECT_CLASS_TO_STRING(subClass) = 
            ASN_OBJECT_CLASS_TO_STRING(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(subClass) == ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT)
    {
        ASN_OBJECT_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(subClass) = 
            ASN_OBJECT_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(subClass) == ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT)
    {
        ASN_OBJECT_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(subClass) = 
            ASN_OBJECT_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_ENCODE_TAG_LENGTH_VALUE(subClass) == ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT)
    {
        ASN_OBJECT_CLASS_ENCODE_TAG_LENGTH_VALUE(subClass) = 
            ASN_OBJECT_CLASS_ENCODE_TAG_LENGTH_VALUE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_OBJECT_CLASS_DECODE_REMOVE_EXTRA_TAG_LENGTH(subClass) == ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT)
    {
        ASN_OBJECT_CLASS_DECODE_REMOVE_EXTRA_TAG_LENGTH(subClass) = 
            ASN_OBJECT_CLASS_DECODE_REMOVE_EXTRA_TAG_LENGTH(ITS_CLASS_SUPERCLASS(subClass));
    }

    return ITS_SUCCESS;
}


static void
ClassPartDestruct(ITS_Class subClass)
{
    /* Nothing to do. */
}


static ITS_Object
Clone(ITS_Object object)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return NULL;
}


static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return ITS_FALSE;
}


static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return ITS_SUCCESS;
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return "";
}

static const char*
GetBaseName(const ASN_Object object)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return "";
}

static char*
ToString(const ASN_Object object)
{
    /* Abstract function => must be redefined in heirs. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ASN_C_ASSERT(must_not_be_reached);

    return "";
}

static void
Print(ITS_Object object)
{
    char* toString = NULL;

    ASN_C_REQUIRE(object != NULL);

    toString = ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);

    if (toString != NULL)
    {
        printf("%s", toString);

        free(toString);
    }
}

static char*
GetEncodeExtendedErrorText(const ASN_Object object, ASN_Error error)
{
    char* result            = NULL;
    char* toString          = NULL;
    char* buffer            = NULL;
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(object != NULL);

    toString = ASN_Object_ToString(object);

    if (toString != NULL)
    {
        /* Absolute maximum. */

        maxStringSize = strlen(toString) + 64;

        result = (char*)calloc(maxStringSize, sizeof(char));

        if (result == NULL)
        {
            free(toString);

            return NULL;
        }

        buffer = result;

        sprintf(
            buffer,
            "\nASN.1 Type and Value:\n%s\n",
            toString);

        free(toString);

        ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

        ASN_C_ENSURE(result != NULL);

        return result;
    }
    else
    {
        return NULL;
    }
}

static char*
GetDecodeExtendedErrorText(const ASN_Object object, ASN_Error error, const ASN_Octets octets)
{
    char* result            = NULL;
    char* toString          = NULL;
    const char* name        = NULL;
    const char* baseName    = NULL;
    char* buffer            = NULL;
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);

    name        = ASN_Object_GetName(object);
    baseName    = ASN_Object_GetBaseName(object);

    toString = ASN_Octets_ToStringWithOffset(octets);

    if (toString != NULL)
    {
        /* Absolute maximum. */

        maxStringSize = strlen(toString)    +
                        strlen(name)        +
                        strlen(baseName)    +
                        64;

        result = (char*)calloc(maxStringSize, sizeof(char));

        if (result == NULL)
        {
            free(toString);

            return NULL;
        }

        buffer = result;

        sprintf(
            buffer,
            "\nASN.1 Type:\n%s (%s)\n\nRaw TLV Dump:\n%s\n",
            name,
            baseName,
            toString);

        free(toString);

        ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

        ASN_C_ENSURE(result != NULL);

        return result;
    }
    else
    {
        /* Absolute maximum. */

        maxStringSize = strlen(name)        +
                        strlen(baseName)    +
                        64;

        result = (char*)calloc(maxStringSize, sizeof(char));

        if (result == NULL)
        {
            return NULL;
        }

        buffer = result;

        sprintf(
            buffer,
            "\nASN.1 Type:\n%s (%s)\n",
            name,
            baseName);

        ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

        ASN_C_ENSURE(result != NULL);

        return result;
    }
}

static ASN_Octets
EncodeTagLengthValue(ASN_Object object, const ASN_Octets value)
{
    ASN_DescObject description  = NULL;
    ASN_LinkedList tagStack     = NULL;
    ASN_Tag tagStackFront       = NULL;
    ASN_Tag tagStackBack        = NULL;
    ASN_Tag tag                 = NULL;
    ASN_Tag tagCursor           = NULL;
    ASN_Length length           = NULL;
    ASN_EncodeError encodeError = NULL;
    ASN_Octets result           = NULL;
    ASN_Octets tagOctets        = NULL;
    ASN_Octets lengthOctets     = NULL;
    int res                     = ITS_SUCCESS;
    ITS_BOOLEAN bStop           = ITS_FALSE;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(value != NULL);

    description = ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);
    ASN_C_ASSERT(ASN_DescObject_TagLevelNumber(description) >= 1);

    tagStack = ASN_DescObject_TagStack(description);

    ASN_C_ASSERT(ASN_LinkedList_GetSize(tagStack) >= 1);

    tagStackFront = (ASN_Tag)ASN_LinkedList_GetFront(tagStack);
    tagStackBack = (ASN_Tag)ASN_LinkedList_GetBack(tagStack);

    ASN_C_ASSERT(tagStackFront != NULL);
    ASN_C_ASSERT(tagStackBack != NULL);

    tag = ASN_Tag_Clone(tagStackBack);

    if (tag == NULL)
    {
        return NULL;
    }

    res = ASN_Tag_Encode(tag, &tagOctets, &encodeError);

    /* ASN_Tag_Encode: no encode error possible. */

    if (res == ITS_ENOMEM)
    {
        ASN_Tag_Destruct(tag);

        ASN_C_ASSERT(tagOctets == NULL);
        ASN_C_ASSERT(encodeError == NULL);

        return NULL;
    }

    ASN_C_ASSERT(res == ITS_SUCCESS);
    ASN_C_ASSERT(tagOctets != NULL);
    ASN_C_ASSERT(encodeError == NULL);

    length = ASN_Length_ConstructWithLength((ITS_LONG)ASN_Octets_GetSize(value));

    if (length == NULL)
    {
        ASN_Tag_Destruct(tag);
        ASN_Octets_Destruct(tagOctets);

        return NULL;
    }

    res = ASN_Length_Encode(length, &lengthOctets, &encodeError);

    /* ASN_Length_Encode: no encode error possible. */

    if (res == ITS_ENOMEM)
    {
        ASN_Tag_Destruct(tag);
        ASN_Octets_Destruct(tagOctets);
        ASN_Length_Destruct(length);

        ASN_C_ASSERT(lengthOctets == NULL);
        ASN_C_ASSERT(encodeError == NULL);

        return NULL;
    }

    ASN_C_ASSERT(res == ITS_SUCCESS);
    ASN_C_ASSERT(lengthOctets != NULL);
    ASN_C_ASSERT(encodeError == NULL);

    result = ASN_Octets_ConstructDefault();

    if (result == NULL)
    {
        ASN_Tag_Destruct(tag);
        ASN_Octets_Destruct(tagOctets);
        ASN_Length_Destruct(length);
        ASN_Octets_Destruct(lengthOctets);

        return NULL;
    }

    res = ASN_Octets_Append(result, tagOctets);

    if (res != ITS_SUCCESS)
    {
        ASN_Tag_Destruct(tag);
        ASN_Octets_Destruct(tagOctets);
        ASN_Length_Destruct(length);
        ASN_Octets_Destruct(lengthOctets);
        ASN_Octets_Destruct(result);

        return NULL;
    }

    res = ASN_Octets_Append(result, lengthOctets);

    if (res != ITS_SUCCESS)
    {
        ASN_Tag_Destruct(tag);
        ASN_Octets_Destruct(tagOctets);
        ASN_Length_Destruct(length);
        ASN_Octets_Destruct(lengthOctets);
        ASN_Octets_Destruct(result);

        return NULL;
    }

    res = ASN_Octets_Append(result, value);

    if (res != ITS_SUCCESS)
    {
        ASN_Tag_Destruct(tag);
        ASN_Octets_Destruct(tagOctets);
        ASN_Length_Destruct(length);
        ASN_Octets_Destruct(lengthOctets);
        ASN_Octets_Destruct(result);

        return NULL;
    }

    ASN_Tag_Destruct(tag);
    tag = NULL;

    ASN_Octets_Destruct(tagOctets);
    tagOctets = NULL;

    ASN_Length_Destruct(length);
    length = NULL;

    ASN_Octets_Destruct(lengthOctets);
    lengthOctets = NULL;

    /*
     *  If tagStackFront == tagStackBack then standard TLV format is used, else
     *  TLTLTL..TLV format is used (case of non implicit tagging).
     */

    /* Check stop condition. */

    if (tagStackFront == tagStackBack)
    {
        ASN_C_ASSERT(ASN_LinkedList_GetSize(tagStack) == 1);

        bStop = ITS_TRUE;
    }
    else
    {
        ASN_C_ASSERT(ASN_LinkedList_GetSize(tagStack) > 1);

        bStop = ITS_FALSE;
    }

    if (bStop == ITS_TRUE)
    {
        ASN_C_ENSURE(result != NULL);

        return result;
    }

    ASN_LinkedList_CursorSetEnd(tagStack); 
    
    /* Cursor is now after back element. */

    ASN_LinkedList_CursorBack(tagStack); 
    
    /* Cursor is now on back element. */

    ASN_LinkedList_CursorBack(tagStack); 
    
    /* Cursor is now on element before back element. */

    tagCursor = (ASN_Tag)ASN_LinkedList_CursorGetElement(tagStack);

    ASN_C_ASSERT(tagCursor != NULL);

    while (!bStop)
    {
        ASN_Octets valOctets = result;

        result = NULL;

        if (tagCursor == tagStackFront)
        {
            bStop = ITS_TRUE; /* Stop after executing while block. */
        }

        ASN_C_ASSERT(tag == NULL);

        tag = ASN_Tag_Clone(tagCursor);

        if (tag == NULL)
        {
            ASN_Octets_Destruct(valOctets);

            return NULL;
        }

        res = ASN_Tag_Encode(tag, &tagOctets, &encodeError);

        /* ASN_Tag_Encode: no encode error possible. */

        if (res == ITS_ENOMEM)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);

            ASN_C_ASSERT(tagOctets == NULL);
            ASN_C_ASSERT(encodeError == NULL);

            return NULL;
        }

        ASN_C_ASSERT(res == ITS_SUCCESS);
        ASN_C_ASSERT(tagOctets != NULL);
        ASN_C_ASSERT(encodeError == NULL);

        length = ASN_Length_ConstructWithLength((ITS_LONG)ASN_Octets_GetSize(valOctets));

        if (length == NULL)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);
            ASN_Octets_Destruct(tagOctets);

            return NULL;
        }

        res = ASN_Length_Encode(length, &lengthOctets, &encodeError);

        /* ASN_Length_Encode: no encode error possible. */

        if (res == ITS_ENOMEM)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);
            ASN_Octets_Destruct(tagOctets);
            ASN_Length_Destruct(length);

            ASN_C_ASSERT(lengthOctets == NULL);
            ASN_C_ASSERT(encodeError == NULL);

            return NULL;
        }

        ASN_C_ASSERT(res == ITS_SUCCESS);
        ASN_C_ASSERT(lengthOctets != NULL);
        ASN_C_ASSERT(encodeError == NULL);

        result = ASN_Octets_ConstructDefault();

        if (result == NULL)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);
            ASN_Octets_Destruct(tagOctets);
            ASN_Length_Destruct(length);
            ASN_Octets_Destruct(lengthOctets);

            return NULL;
        }

        res = ASN_Octets_Append(result, tagOctets);

        if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);
            ASN_Octets_Destruct(tagOctets);
            ASN_Length_Destruct(length);
            ASN_Octets_Destruct(lengthOctets);
            ASN_Octets_Destruct(result);

            return NULL;
        }

        res = ASN_Octets_Append(result, lengthOctets);

        if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);
            ASN_Octets_Destruct(tagOctets);
            ASN_Length_Destruct(length);
            ASN_Octets_Destruct(lengthOctets);
            ASN_Octets_Destruct(result);

            return NULL;
        }

        res = ASN_Octets_Append(result, valOctets);

        if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Tag_Destruct(tag);
            ASN_Octets_Destruct(tagOctets);
            ASN_Length_Destruct(length);
            ASN_Octets_Destruct(lengthOctets);
            ASN_Octets_Destruct(result);

            return NULL;
        }

        ASN_Octets_Destruct(valOctets);
        valOctets = NULL;

        ASN_Octets_Destruct(tagOctets);
        tagOctets = NULL;

        ASN_Length_Destruct(length);
        length = NULL;

        ASN_Octets_Destruct(lengthOctets);
        lengthOctets = NULL;

        if (!bStop)
        {
            /* Move back cursor and update tagCursor. */

            ASN_LinkedList_CursorBack(tagStack);

            tagCursor = (ASN_Tag)ASN_LinkedList_CursorGetElement(tagStack);
        }
    }

    ASN_C_ENSURE(result != NULL);

    return result;
}

static int
DecodeRemoveExtraTagLength(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    ASN_DescObject description  = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);
    ASN_C_ASSERT(ASN_DescObject_TagLevelNumber(description) >= 1);

    if (ASN_DescObject_TagLevelNumber(description) == 1)
    {
        /* Standard TLV format used. */

        return ITS_SUCCESS;
    }
    else
    {
        size_t i                = 0;
        int res                 = ITS_SUCCESS;
        size_t tagLevelNumber   = ASN_DescObject_TagLevelNumber(description);
        ASN_Tag tag             = NULL;
        ASN_Length length       = NULL;


        /* TLTLTLT..TLV format used. Remove TLTLTL.. and keep TLV. */

        ASN_C_ASSERT(tagLevelNumber >= 2);

        for (i = 1; i < tagLevelNumber; i++)
        {
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

            ASN_Length_Destruct(length);
            length = NULL;
        }

        return ITS_SUCCESS;
    }
}


/*
 *  ASN_Object class record.
 */ 

ASN_Object_ClassRec itsASN_Object_ClassRec =
{
    /* Core part. */

    {
        &itsCORE_ClassRec,             
        sizeof(ASN_Object_ObjectRec),  
        ITS_FALSE,                     
        0,                             
        ASN_OBJECT_CLASS_NAME,         
        ITS_CLASS_NO_INIT,             
        ITS_CLASS_NO_DEST,             
        ClassPartConstruct,            
        ClassPartDestruct,             
        ITS_INST_NO_CONST,             
        ITS_INST_NO_DEST,              
        Clone,                         
        Print,                         
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
        GetEncodeExtendedErrorText,
        GetDecodeExtendedErrorText,
        EncodeTagLengthValue,
        DecodeRemoveExtraTagLength
    }
};

void 
ASN_Object_Destruct(ASN_Object object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_Object_Clone(const ASN_Object object)
{
    return (ASN_Object)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Object_Equals(const ASN_Object object, const ASN_Object other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

char* 
ASN_Object_GetEncodeExtendedErrorText(
                                    const ASN_Object object, 
                                    ASN_Error error)
{
    return ASN_OBJECT_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(
        ITS_OBJ_CLASS(object))(object, error);
}

char* 
ASN_Object_GetDecodeExtendedErrorText(
                                    const ASN_Object object, 
                                    ASN_Error error, 
                                    const ASN_Octets octets)
{
    return ASN_OBJECT_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(
        ITS_OBJ_CLASS(object))(object, error, octets);
}

ASN_Octets 
ASN_Object_EncodeTagLengthValue(
                            ASN_Object object, 
                            const ASN_Octets value)
{
    return ASN_OBJECT_CLASS_ENCODE_TAG_LENGTH_VALUE(
        ITS_OBJ_CLASS(object))(object, value);
}

int 
ASN_Object_DecodeRemoveExtraTagLength(
                            ASN_Object object, 
                            ASN_Octets octets,
                            ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE_REMOVE_EXTRA_TAG_LENGTH(
        ITS_OBJ_CLASS(object))(object, octets, decodeError);
}

const char* 
ASN_Object_GetName(const ASN_Object object)
{
    return ASN_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Object_Encode(
                ASN_Object object, 
                ASN_Octets* octets, 
                ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(
        ITS_OBJ_CLASS(object))(object, octets, encodeError);
}

int 
ASN_Object_Decode(
                ASN_Object object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(
        ITS_OBJ_CLASS(object))(object, octets, decodeError);
}

const char* 
ASN_Object_GetBaseName(const ASN_Object object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))(object);
}

char* 
ASN_Object_ToString(const ASN_Object object)
{
    return ASN_OBJECT_CLASS_TO_STRING(
        ITS_OBJ_CLASS(object))(object);
}


