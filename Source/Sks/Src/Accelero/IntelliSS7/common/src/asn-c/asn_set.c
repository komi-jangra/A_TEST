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
 *  ID: $Id: asn_set.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_set.h>
#include <asn_desc_set.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_SET_CLASS_GET_ELEMENTS(subClass) == ASN_SET_GET_ELEMENTS_INHERIT)
    {
        ASN_SET_CLASS_GET_ELEMENTS(subClass) =
            ASN_SET_CLASS_GET_ELEMENTS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_ADD_ELEMENT(subClass) == ASN_SET_ADD_ELEMENT_INHERIT)
    {
        ASN_SET_CLASS_ADD_ELEMENT(subClass) =
            ASN_SET_CLASS_ADD_ELEMENT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_GET_ELEMENT_AT(subClass) == ASN_SET_GET_ELEMENT_AT_INHERIT)
    {
        ASN_SET_CLASS_GET_ELEMENT_AT(subClass) =
            ASN_SET_CLASS_GET_ELEMENT_AT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_GET_ELEMENT_AT_TAG(subClass) == ASN_SET_GET_ELEMENT_AT_TAG_INHERIT)
    {
        ASN_SET_CLASS_GET_ELEMENT_AT_TAG(subClass) =
            ASN_SET_CLASS_GET_ELEMENT_AT_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_CONTAINS(subClass) == ASN_SET_CONTAINS_INHERIT)
    {
        ASN_SET_CLASS_CONTAINS(subClass) =
            ASN_SET_CLASS_CONTAINS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_CONTAINS_TAG(subClass) == ASN_SET_CONTAINS_TAG_INHERIT)
    {
        ASN_SET_CLASS_CONTAINS_TAG(subClass) =
            ASN_SET_CLASS_CONTAINS_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_REMOVE_ELEMENT(subClass) == ASN_SET_REMOVE_ELEMENT_INHERIT)
    {
        ASN_SET_CLASS_REMOVE_ELEMENT(subClass) =
            ASN_SET_CLASS_REMOVE_ELEMENT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_REMOVE_ELEMENT_TAG(subClass) == ASN_SET_REMOVE_ELEMENT_TAG_INHERIT)
    {
        ASN_SET_CLASS_REMOVE_ELEMENT_TAG(subClass) =
            ASN_SET_CLASS_REMOVE_ELEMENT_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_REMOVE_ALL_ELEMENTS(subClass) == ASN_SET_REMOVE_ALL_ELEMENTS_INHERIT)
    {
        ASN_SET_CLASS_REMOVE_ALL_ELEMENTS(subClass) =
            ASN_SET_CLASS_REMOVE_ALL_ELEMENTS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_GET_SIZE(subClass) == ASN_SET_GET_SIZE_INHERIT)
    {
        ASN_SET_CLASS_GET_SIZE(subClass) =
            ASN_SET_CLASS_GET_SIZE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SET_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_SET_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_SET_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_SET_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
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

static ASN_DescSet GetStaticDescription();
static void RemoveAllElements(ASN_Set object);

static int
Construct(ITS_Object object, va_list args)
{
    size_t size                  = 0;
    ASN_DescSet description = NULL;

    ASN_C_REQUIRE(object != NULL);

    size = va_arg(args, size_t);

    ASN_C_REQUIRE(size >= 0);

    description = va_arg(args, ASN_DescSet);

    ASN_SET_ELEMENTS(object) = (ASN_Object*)calloc(size, sizeof(ASN_Object));

    ASN_C_ENSURE(ASN_SET_ELEMENTS(object) != NULL);

    if (ASN_SET_ELEMENTS(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    ASN_SET_SIZE(object) = size;

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            if (ASN_SET_ELEMENTS(object) != NULL)
            {
                free(ASN_SET_ELEMENTS(object));
                ASN_SET_ELEMENTS(object) = NULL;
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

    RemoveAllElements((ASN_Set)object);

    if (ASN_SET_ELEMENTS(object) != NULL)
    {
        free(ASN_SET_ELEMENTS(object));
        ASN_SET_ELEMENTS(object) = NULL;
    }
}

static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result   = NULL;
    int i               = 0;
    size_t size         = 0;

    ASN_C_REQUIRE(object != NULL);

    result = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (result == NULL)
    {
        return result;
    }

    memcpy(result, object, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    size = ASN_SET_SIZE(object);

    ASN_SET_ELEMENTS(result) = (ASN_Object*)calloc(size, sizeof(ASN_Object));

    ASN_C_ENSURE(ASN_SET_ELEMENTS(result) != NULL);

    if (ASN_SET_ELEMENTS(result) == NULL)
    {
        free(result);

        return NULL;
    }

    for (i = 0; i < (int)ASN_SET_SIZE(result); i++)
    {
        if (ASN_SET_ELEMENTS(result)[i] != NULL)
        {
            ASN_Object clonedElement    = NULL;
            ASN_Object element          = ASN_SET_ELEMENTS(object)[i];

            ASN_C_ASSERT(element != NULL);

            clonedElement = ASN_Object_Clone(element);

            ASN_C_ENSURE(clonedElement != NULL);

            if (clonedElement == NULL)
            {
                RemoveAllElements((ASN_Set)result);
                free(ASN_SET_ELEMENTS(result));
                ASN_SET_ELEMENTS(result) = NULL;
                free(result);

                return NULL;
            }

            ASN_SET_ELEMENTS(result)[i] = clonedElement;
        }
        else
        {
            ASN_SET_ELEMENTS(result)[i] = NULL;
        }
    }

    return result;
}


static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;

    ASN_C_ASSERT(not_implemented);

    return ITS_FALSE;
}

static ASN_DescSet staticDescription = NULL;

static ASN_DescSet
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescSet result  = NULL;
    ASN_Set cloneForFactory    = NULL;
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

        staticDescription = ASN_DescSet_ConstructWithSize(0);

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Set_ConstructWithSizeDescription(0, staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescSet_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescSet_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_Set_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescSet_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescSet_TagAddLevel(staticDescription, universalTag);

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
        ASN_DescSet_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN Contains(const ASN_Set object, size_t index);
static ITS_BOOLEAN ContainsTag(const ASN_Set object, const ASN_Tag tag);
static size_t GetSize(const ASN_Set object);

static const ASN_Object* 
GetElements(const ASN_Set object)
{
    ASN_Object* result = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = ASN_SET_ELEMENTS(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void 
AddElement(ASN_Set object, size_t index, ASN_Object element)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));
    ASN_C_REQUIRE(element != NULL);

    if (ASN_SET_ELEMENTS(object)[index] != NULL)
    {
        ASN_Object_Destruct(ASN_SET_ELEMENTS(object)[index]);
    }

    ASN_SET_ELEMENTS(object)[index] = element;
}

static const ASN_Object 
GetElementAt(const ASN_Set object, size_t index)
{
    ASN_Object result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));
    ASN_C_REQUIRE(Contains(object, index));

    result = ASN_SET_ELEMENTS(object)[index];

    ASN_C_ENSURE(result != NULL);

    return result;
}

static const ASN_Object 
GetElementAtTag(const ASN_Set object, const ASN_Tag tag)
{
    int i               = 0;
    ASN_Object result   = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);
    ASN_C_REQUIRE(ContainsTag(object, tag));

    for (i = 0; i < (int)ASN_SET_SIZE(object); i++)
    {
        ASN_Object element = ASN_SET_ELEMENTS(object)[i];

        if (element != NULL)
        {
            ASN_DescObject elementDescription = ASN_OBJECT_DESCRIPTION(element);

            if (ASN_DescObject_TagIdentify(elementDescription, tag))
            {
                result = element;
                break;
            }
        }
    }
            
    ASN_C_ENSURE(result != NULL);

    return result;
}

static ITS_BOOLEAN 
Contains(const ASN_Set object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    return ASN_SET_ELEMENTS(object)[index] != NULL;
}

static ITS_BOOLEAN 
ContainsTag(const ASN_Set object, const ASN_Tag tag)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    for (i = 0; i < (int)ASN_SET_SIZE(object); i++)
    {
        ASN_Object element = ASN_SET_ELEMENTS(object)[i];

        if (element != NULL)
        {
            ASN_DescObject elementDescription = ASN_OBJECT_DESCRIPTION(element);

            if (ASN_DescObject_TagIdentify(elementDescription, tag))
            {
                return ITS_TRUE;
            }
        }
    }
            
    return ITS_FALSE;
}

static void 
RemoveElement(ASN_Set object, size_t index)
{
    ASN_Object element = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));
    ASN_C_REQUIRE(Contains(object, index));

    element = ASN_SET_ELEMENTS(object)[index];

    ASN_C_ASSERT(element != NULL);

    ASN_Object_Destruct(element);

    ASN_SET_ELEMENTS(object)[index] = NULL;
}

static void 
RemoveElementTag(ASN_Set object, const ASN_Tag tag)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);
    ASN_C_REQUIRE(ContainsTag(object, tag));

    for (i = 0; i < (int)ASN_SET_SIZE(object); i++)
    {
        ASN_Object element = ASN_SET_ELEMENTS(object)[i];

        if (element != NULL)
        {
            ASN_DescObject elementDescription = ASN_OBJECT_DESCRIPTION(element);

            if (ASN_DescObject_TagIdentify(elementDescription, tag))
            {
                ASN_Object_Destruct(element);
                ASN_SET_ELEMENTS(object)[i] = NULL;
                break;
            }
        }
    }
}

static void 
RemoveAllElements(ASN_Set object)
{
    int i = 0;

    ASN_C_REQUIRE(object != NULL);

    for (i = 0; i < (int)ASN_SET_SIZE(object); i++)
    {
        ASN_Object element = ASN_SET_ELEMENTS(object)[i];

        if (element != NULL)
        {
            ASN_Object_Destruct(element);

            ASN_SET_ELEMENTS(object)[i] = NULL;
        }
    }
}

static size_t 
GetSize(const ASN_Set object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_SET_SIZE(object);
}

static ASN_Tag
GetUniversalTag(const ASN_Set object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_SET);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescSet description = NULL;

    int i                   = 0;
    ASN_Octets valOctets    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescSet)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    /* Encode check begin. */

    for (i = 0; i < (int)ASN_DESC_SET_SIZE(description); i++)
    {
        ASN_DescObject elementDescription = NULL;

        ASN_C_ASSERT(ASN_DescSet_Contains(description, i));

        elementDescription = ASN_DescSet_GetElementAt(description, i);

        if (!ASN_DescObject_IsClauseOptional(elementDescription))
        {
            if (!Contains((ASN_Set)object, i))
            {
                *encodeError = 
                    ASN_CONSTRUCT_ENCODE_ERROR(
                        ASN_E_MISSING_MANDATORY_ELEMENT_IN_SET,
                        object);

                return ITS_E_ASN_ENCODE_ERROR;
            }
        }
    }
                        
    /* Encode check end. */

    valOctets = ASN_Octets_ConstructDefault();

    if (valOctets == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < (int)ASN_SET_SIZE(object); i++)
    {
        if (Contains((ASN_Set)object, i))
        {
            int res                     = ITS_SUCCESS;
            ASN_Octets elementOctets    = NULL;
            ASN_Object element          = ASN_SET_ELEMENTS(object)[i];

            ASN_C_ASSERT(element != NULL);

            res = ASN_Object_Encode(element, &elementOctets, encodeError);

            if (res != ITS_SUCCESS)
            {
                ASN_Octets_Destruct(valOctets);

                return res;
            }

            res = ASN_Octets_Append(valOctets, elementOctets);

            if (res != ITS_SUCCESS)
            {
                ASN_Octets_Destruct(valOctets);
                ASN_Octets_Destruct(elementOctets);

                return res;
            }

            ASN_Octets_Destruct(elementOctets);
        }
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

    int res                 = ITS_SUCCESS;
    ASN_DescSet description = NULL;
    ASN_Tag tag             = NULL;
    ASN_Length length       = NULL;
    size_t startOffset      = 0;
    ITS_BOOLEAN stop        = ITS_FALSE;
    int i                   = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescSet)ASN_OBJECT_DESCRIPTION(object);

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

    startOffset = ASN_Octets_GetOffset(octets);

    stop = ITS_FALSE;

    if (ASN_Length_GetLength(length) == 0)
    {
        stop = ITS_TRUE;
    }

    RemoveAllElements((ASN_Set)object);

    while (!stop)
    {
        ITS_BOOLEAN foundWithIndex          = ITS_FALSE;
        size_t descriptionIndex             = 0;
        size_t currentOffset                = 0;
        ASN_Tag elementTag                  = NULL;
        ASN_Object element                  = NULL;

        elementTag = ASN_Tag_ConstructDefault();

        if (elementTag == NULL)
        {
            ASN_Length_Destruct(length);

            return ITS_ENOMEM;
        }

        res = ASN_Tag_DecodePreserveOffset(elementTag, octets, decodeError);

        if (res != ITS_SUCCESS)
        {
            ASN_Length_Destruct(length);
            ASN_Tag_Destruct(elementTag);

            return res;
        }

        if (ASN_DescSet_ContainsTag(description, elementTag))
        {
            ASN_DescObject elementDescription   = NULL;
            ASN_Object element                  = NULL;

            elementDescription = 
                ASN_DescSet_GetElementAtTag(description, elementTag);

            element = ASN_DescObject_Factory(elementDescription);

            if (element == NULL)
            {
                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);

                return ITS_ENOMEM;
            }

            res = ASN_Object_Decode(element, octets, decodeError);

            if (res != ITS_SUCCESS)
            {
                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);
                ASN_Object_Destruct(element);

                return res;
            }

            descriptionIndex    = 0;
            foundWithIndex      = ITS_FALSE;

            while (descriptionIndex < ASN_DESC_SET_SIZE(description))
            {
                ASN_DescObject elementDescription =
                    ASN_DescSet_GetElementAt(description, descriptionIndex);

                if (ASN_DescObject_TagIdentify(elementDescription, elementTag))
                {
                    AddElement((ASN_Set)object, descriptionIndex, element);

                    foundWithIndex = ITS_TRUE;

                    break;
                }

                descriptionIndex++;
            }

            if (!foundWithIndex)
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ASN_C_ASSERT(must_not_be_reached);
            }
        }
        else
        {
            if (!ASN_Options_GlobalIsDecodeSkipUnknownElementInSet())
            {
                *decodeError =
                    ASN_CONSTRUCT_DECODE_ERROR(
                                        ASN_E_UNKNOWN_ELEMENT_IN_SET,
                                        object,
                                        octets);
                        
                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);

                return ITS_E_ASN_DECODE_ERROR;
            }
            else
            {
                /* Skip unknown element. */

                ASN_Tag unknownElementTag       = NULL;
                ASN_Length unknownElementLength = NULL;

                unknownElementTag = ASN_Tag_ConstructDefault();

                if (unknownElementTag == NULL)
                {
                    ASN_Length_Destruct(length);
                    ASN_Tag_Destruct(elementTag);

                    return ITS_ENOMEM;
                }

                res = ASN_Tag_Decode(unknownElementTag, octets, decodeError);

                if (res != ITS_SUCCESS)
                {
                    ASN_Length_Destruct(length);
                    ASN_Tag_Destruct(elementTag);
                    ASN_Tag_Destruct(unknownElementTag);

                    return res;
                }

                ASN_Tag_Destruct(unknownElementTag);
                unknownElementTag = NULL;

                unknownElementLength = ASN_Length_ConstructDefault();

                if (unknownElementLength == NULL)
                {
                    ASN_Length_Destruct(length);
                    ASN_Tag_Destruct(elementTag);

                    return ITS_ENOMEM;
                }

                res = ASN_Length_Decode(unknownElementLength, octets, decodeError);

                if (res != ITS_SUCCESS)
                {
                    ASN_Length_Destruct(length);
                    ASN_Tag_Destruct(elementTag);
                    ASN_Length_Destruct(unknownElementLength);

                    return res;
                }

                ASN_Octets_IncrementOffsetWithIncrement(
                            octets, 
                            ASN_Length_GetLength(unknownElementLength));
            }
        }
                
        currentOffset = ASN_Octets_GetOffset(octets);

        if (!ASN_Length_IsIndefinite(length))
        {
            if (ASN_Length_GetLength(length) == (ITS_LONG)(currentOffset - startOffset))
            {
                stop = ITS_TRUE;
            }
            else if (ASN_Length_GetLength(length) > (ITS_LONG)(currentOffset - startOffset))
            {
                stop = ITS_FALSE;
            }
            else
            {
                *decodeError = 
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_INVALID_ELEMENT_LENGTH_IN_SET,
                        object,
                        octets);

                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);

                return ITS_E_ASN_DECODE_ERROR;
            }
        }
        else
        {
            if (ASN_Length_IsIndefiniteEndMark(length, octets))
            {
                ASN_Length_IndefiniteEndMarkIncOffset(length, octets);
                stop = ITS_TRUE;
            }
            else
            {
                stop = ITS_FALSE;
            }
        }

        ASN_Tag_Destruct(elementTag);
        elementTag = NULL;
    }

    ASN_Length_Destruct(length);

    /* Decode check begin. */

    for (i = 0; i < (int)ASN_DESC_SET_SIZE(description); i++)
    {
        ASN_DescObject elementDescription = NULL;

        ASN_C_ASSERT(ASN_DescSet_Contains(description, i));

        elementDescription = ASN_DescSet_GetElementAt(description, i);

        if (!ASN_DescObject_IsClauseOptional(elementDescription))
        {
            if (!Contains((ASN_Set)object, i))
            {
                *decodeError = 
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_MISSING_MANDATORY_ELEMENT_IN_SET,
                        object,
                        octets);

                return ITS_E_ASN_DECODE_ERROR;
            }
        }
    }

    /* Decode check end. */

    return ITS_SUCCESS;
}


static const char*
GetName(const ASN_Object object)
{
    return "SET";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "SET";
}

/*
 *  Helper function to destruct a linked list of strings.
 */

static void
StringListDestruct(ASN_LinkedList stringList)
{
    ASN_C_REQUIRE(stringList != NULL);

    ASN_LinkedList_CursorSetBegin(stringList);

    while (!ASN_LinkedList_CursorIsEnd(stringList))
    {
        char* str = (char*)ASN_LinkedList_CursorGetElement(stringList);

        ASN_C_ASSERT(str != NULL);

        free(str);

        ASN_LinkedList_CursorForth(stringList);
    }

    ASN_LinkedList_Destruct(stringList);
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
    int i                       = 0;
    size_t maxStringSize        = 0;
    ASN_LinkedList stringList   = NULL;
    ITS_BOOLEAN first           = ITS_FALSE;

    ASN_C_REQUIRE(object != NULL);

    stringList = ASN_LinkedList_ConstructDefault();

    if (stringList == NULL)
    {
        return NULL;
    }

    for (i = 0; i < (int)ASN_SET_SIZE(object); i++)
    {
        ASN_Object element = ASN_SET_ELEMENTS(object)[i];

        if (element != NULL)
        {
            toString = ASN_Object_ToString(element);

            if (toString == NULL)
            {
                StringListDestruct(stringList);

                return NULL;
            }

            toStringLineShifted = ASN_AddLineShift(toString);

            if (toStringLineShifted == NULL)
            {
                StringListDestruct(stringList);
                free(toString);
                
                return NULL;
            }

            free(toString);

            ASN_LinkedList_PushBack(stringList, (ITS_Object)toStringLineShifted);
        }
    }

    maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 32;

    ASN_LinkedList_CursorSetBegin(stringList);

    while (!ASN_LinkedList_CursorIsEnd(stringList))
    {
        char* str = (char*)ASN_LinkedList_CursorGetElement(stringList);

        maxStringSize += strlen(str) + 1;

        ASN_LinkedList_CursorForth(stringList);
    }

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        StringListDestruct(stringList);
    
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "%s (%s)\n{\n",
        nameStr,
        baseNameStr);

    first = ITS_TRUE;

    ASN_LinkedList_CursorSetBegin(stringList);

    while (!ASN_LinkedList_CursorIsEnd(stringList))
    {
        char* str = (char*)ASN_LinkedList_CursorGetElement(stringList);

        ASN_C_ASSERT(str != NULL);

        if (!first)
        {
            strcat(buffer, "\n");
        }
        else
        {
            first = ITS_FALSE;
        }

        strcat(buffer, str);

        ASN_LinkedList_CursorForth(stringList);
    }

    strcat(buffer, "}\n");

    StringListDestruct(stringList);

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_Set class record.
 */ 

ASN_Set_ClassRec itsASN_Set_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,
        sizeof(ASN_Set_ObjectRec),    
        ITS_FALSE,                         
        0,                                 
        ASN_SET_CLASS_NAME,           
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

    /* ASN_Set class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetElements,
        AddElement,
        GetElementAt,
        GetElementAtTag,
        Contains,
        ContainsTag,
        RemoveElement,
        RemoveElementTag,
        RemoveAllElements,
        GetSize,
        GetUniversalTag
    }
};

ASN_Set 
ASN_Set_ConstructWithSize(size_t size)
{
    ASN_Set result = NULL;

    result = (ASN_Set)ITS_ConstructObject((ITS_Class)&itsASN_Set_ClassRec, size, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Set 
ASN_Set_ConstructWithSizeDescription(size_t size, ASN_DescSet description)
{
    ASN_Set result = NULL;

    result = (ASN_Set)ITS_ConstructObject((ITS_Class)&itsASN_Set_ClassRec, size, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Set_Destruct(ASN_Set object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Set 
ASN_Set_Clone(const ASN_Set object)
{
    return (ASN_Set)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Set_Equals(const ASN_Set object, const ASN_Set other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescSet 
ASN_Set_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Set_DestructStaticDescription()
{
    DestructStaticDescription();
}


const ASN_Object* 
ASN_Set_GetElements(const ASN_Set object)
{
    return ASN_SET_CLASS_GET_ELEMENTS(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_Set_AddElement(ASN_Set object, size_t index, ASN_Object element)
{
    ASN_SET_CLASS_ADD_ELEMENT(ITS_OBJ_CLASS(object))(object, index, element);
}

const ASN_Object 
ASN_Set_GetElementAt(const ASN_Set object, size_t index)
{
    return ASN_SET_CLASS_GET_ELEMENT_AT(ITS_OBJ_CLASS(object))(object, index);
}

const ASN_Object 
ASN_Set_GetElementAtTag(const ASN_Set object, const ASN_Tag tag)
{
    return ASN_SET_CLASS_GET_ELEMENT_AT_TAG(ITS_OBJ_CLASS(object))(object, tag);
}

ITS_BOOLEAN 
ASN_Set_Contains(const ASN_Set object, size_t index)
{
    return ASN_SET_CLASS_CONTAINS(ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_Set_ContainsTag(const ASN_Set object, const ASN_Tag tag)
{
    return ASN_SET_CLASS_CONTAINS_TAG(ITS_OBJ_CLASS(object))(object, tag);
}

void 
ASN_Set_RemoveElement(ASN_Set object, size_t index)
{
    ASN_SET_CLASS_REMOVE_ELEMENT(ITS_OBJ_CLASS(object))(object, index);
}

void 
ASN_Set_RemoveElementTag(ASN_Set object, const ASN_Tag tag)
{
    ASN_SET_CLASS_REMOVE_ELEMENT_TAG(ITS_OBJ_CLASS(object))(object, tag);
}

void 
ASN_Set_RemoveAllElements(ASN_Set object)
{
    ASN_SET_CLASS_REMOVE_ALL_ELEMENTS(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_Set_GetSize(const ASN_Set object)
{
    return ASN_SET_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

ASN_Tag 
ASN_Set_GetUniversalTag(const ASN_Set object)
{
    return ASN_SET_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Set_Encode(ASN_Set object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Set_Decode(ASN_Set object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Set_GetName(const ASN_Set object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Set_GetBaseName(const ASN_Set object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Set_Print(const ASN_Set object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Set_ToString(const ASN_Set object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



