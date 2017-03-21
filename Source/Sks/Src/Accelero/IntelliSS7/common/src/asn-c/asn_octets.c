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
 *  ID: $Id: asn_octets.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_octets.h>


static int
Construct(ITS_Object object, va_list args)
{
    ITS_OCTET* array = NULL;
    size_t size = 0;

    ASN_C_REQUIRE(object != NULL);

    array = va_arg(args, ITS_OCTET*);
    size = va_arg(args, size_t);

    ASN_C_REQUIRE((array == NULL && size == 0) || (array != NULL && size != 0))

    if (array != NULL && size != 0)
    {
        ASN_OCTETS_DATA(object) = (ITS_OCTET*)calloc(size, sizeof(ITS_OCTET));

        ASN_C_ENSURE(ASN_OCTETS_DATA(object) != NULL);

        if (ASN_OCTETS_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memcpy(ASN_OCTETS_DATA(object), array, size * sizeof (ITS_OCTET));
        ASN_OCTETS_SIZE(object) = size;
        ASN_OCTETS_RESERVED_SIZE(object) = size;
    }
    else /* array == NULL && size == 0 */
    {
        ASN_OCTETS_DATA(object) = NULL;
        ASN_OCTETS_SIZE(object) = 0;
        ASN_OCTETS_RESERVED_SIZE(object) = size;
    }

    ASN_OCTETS_OFFSET(object) = 0;

    return ITS_SUCCESS;
}


static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    if (ASN_OCTETS_DATA(object) != NULL)
    {
        free(ASN_OCTETS_DATA(object));
        ASN_OCTETS_DATA(object) = NULL;
    }
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

    if (ASN_OCTETS_SIZE(object) > 0)
    {
        ASN_OCTETS_DATA(result) = (ITS_OCTET*)calloc(ASN_OCTETS_SIZE(object), sizeof(ITS_OCTET));

        if (ASN_OCTETS_DATA(result) == NULL)
        {
            free(result);

            return NULL;
        }

        memcpy(ASN_OCTETS_DATA(result), ASN_OCTETS_DATA(object), ASN_OCTETS_SIZE(object));
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

    if (ASN_OCTETS_SIZE(object) != ASN_OCTETS_SIZE(other))
    {
        return ITS_FALSE;
    }

    if (ASN_OCTETS_OFFSET(object) != ASN_OCTETS_OFFSET(other))
    {
        return ITS_FALSE;
    }

    if (memcmp(
            ASN_OCTETS_DATA(object),
            ASN_OCTETS_DATA(other),
            ASN_OCTETS_SIZE(object)) == 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}


static int 
Reserve(ASN_Octets object, size_t size)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(size > 0);
    ASN_C_REQUIRE(size > ASN_OCTETS_RESERVED_SIZE(object));

    if (ASN_OCTETS_DATA(object) == NULL)
    {
        ASN_C_ASSERT(ASN_OCTETS_SIZE(object) == 0);
        ASN_C_ASSERT(ASN_OCTETS_RESERVED_SIZE(object) == 0);

        ASN_OCTETS_DATA(object) = (ITS_OCTET*)calloc(size, sizeof(ITS_OCTET));
        ASN_OCTETS_RESERVED_SIZE(object) = size;

        ASN_C_ENSURE(ASN_OCTETS_DATA(object) != NULL);

        if (ASN_OCTETS_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }
    }
    else
    {
        ASN_C_ASSERT(ASN_OCTETS_RESERVED_SIZE(object) != 0);

        ASN_OCTETS_DATA(object) = 
            (ITS_OCTET*)realloc(
                ASN_OCTETS_DATA(object), 
                size * sizeof(ITS_OCTET));

        ASN_C_ENSURE(ASN_OCTETS_DATA(object) != NULL);

        if (ASN_OCTETS_DATA(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        memset(
            ASN_OCTETS_DATA(object) + ASN_OCTETS_RESERVED_SIZE(object), 
            0, 
            size - ASN_OCTETS_RESERVED_SIZE(object));

        ASN_OCTETS_RESERVED_SIZE(object) = size;
    }

    return ITS_SUCCESS;
}

static const ITS_OCTET* 
GetArray(const ASN_Octets object)
{
    const ITS_OCTET* result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_OCTETS_SIZE(object) > 0);

    result = ASN_OCTETS_DATA(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static size_t 
GetSize(const ASN_Octets object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_OCTETS_SIZE(object);
}

static int 
SetArray(ASN_Octets object, const ITS_OCTET* array, size_t size)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(array != NULL);
    ASN_C_REQUIRE(size > 0);

    if (size <= ASN_OCTETS_RESERVED_SIZE(object))
    {
        memcpy(ASN_OCTETS_DATA(object), array, size * sizeof (ITS_OCTET));
        ASN_OCTETS_SIZE(object) = size;
    }
    else
    {
        result = Reserve(object, size);

        if (result != ITS_SUCCESS)
        {
            return result;
        }

        memcpy(ASN_OCTETS_DATA(object), array, size);
        ASN_OCTETS_SIZE(object) = size;
    }

    return ITS_SUCCESS;
}

static char* 
ToString(const ASN_Octets object)
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

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ASN_OCTETS_SIZE(object) >= 0);

    divisor = ROW_LENGTH;

    ASN_C_ASSERT(divisor > 1);

    quotient    = ASN_OCTETS_SIZE(object) / divisor;
    remainder   = ASN_OCTETS_SIZE(object) % divisor;

    /* Absolute maximum. */

    maxStringSize = (ASN_OCTETS_SIZE(object) + divisor) * 4 + 16;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(buffer, "[ ");
    buffer += 2;

    for (i = 0; i < quotient; i++)
    {
        for (j = 0; j < divisor; j++)
        {
            sprintf(buffer, "%02X", ASN_OCTETS_DATA(object)[i * divisor + j]);
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
        sprintf(buffer, "%02X", ASN_OCTETS_DATA(object)[i * divisor + j]);
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

    sprintf(buffer, "]");
    buffer += 1;

    sprintf(buffer, "\0");
    buffer += 1;

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static char* 
ToStringWithOffset(const ASN_Octets object)
{
    char* result            = NULL;
    char* toString          = NULL;
    char* buffer            = NULL;
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(object != NULL);

    toString = ToString(object);

    if (toString == NULL)
    { 
        return NULL;
    }

    maxStringSize = strlen(toString) + 32;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        free(toString);

        return NULL;
    }

    buffer = result;

    sprintf(buffer, "[ offset = %u ]\n", ASN_OCTETS_OFFSET(object));

    strcat(buffer, toString);

    free(toString);

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void
Print(ITS_Object object)
{
    char* toString = NULL;

    ASN_C_REQUIRE(object != NULL);

    toString = ToString((ASN_Octets)object);

    if (toString != NULL)
    {
        printf("%s", toString);

        free(toString);
    }
}

static void 
PrintWithOffset(const ASN_Octets object)
{
    char* toStringWithOffset = NULL;

    ASN_C_REQUIRE(object != NULL);

    toStringWithOffset = ToStringWithOffset(object);

    if (toStringWithOffset != NULL)
    {
        printf("%s", toStringWithOffset);

        free(toStringWithOffset);
    }
}

static size_t 
GetOffset(const ASN_Octets object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_OCTETS_OFFSET(object);
}

static void 
SetOffset(ASN_Octets object, size_t offset)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_OCTETS_OFFSET(object) = offset;
}

static void 
IncrementOffset(ASN_Octets object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_OCTETS_OFFSET(object)++;
}

static void 
IncrementOffsetWithIncrement(ASN_Octets object, size_t increment)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_OCTETS_OFFSET(object) += increment;
}

static void 
DecrementOffset(ASN_Octets object)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_OCTETS_OFFSET(object)--;
}

static void 
DecrementOffsetWithDecrement(ASN_Octets object, size_t decrement)
{
    ASN_C_REQUIRE(object != NULL);

    ASN_OCTETS_OFFSET(object) -= decrement;
}

static ITS_BOOLEAN 
IsIndexValid(const ASN_Octets object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);

    return index < ASN_OCTETS_SIZE(object);
}

static ITS_BOOLEAN 
IsIndexWithOffsetValid(const ASN_Octets object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);

    return index + ASN_OCTETS_OFFSET(object) < ASN_OCTETS_SIZE(object);
}

static ITS_BOOLEAN 
IsOffsetValid(const ASN_Octets object, size_t offset)
{
    ASN_C_REQUIRE(object != NULL);

    return offset < ASN_OCTETS_SIZE(object);
}

static ITS_OCTET 
GetOctetAt(const ASN_Octets object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsIndexValid(object, index));

    return ASN_OCTETS_DATA(object)[index];
}

static void 
SetOctetAt(ASN_Octets object, size_t index, ITS_OCTET octet)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsIndexValid(object, index));

    ASN_OCTETS_DATA(object)[index] = octet;
}

static ITS_OCTET 
GetOctetAtWithOffset(const ASN_Octets object, size_t index)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsIndexWithOffsetValid(object, index));

    return ASN_OCTETS_DATA(object)[index + ASN_OCTETS_OFFSET(object)];
}

static void 
SetOctetAtWithOffset(ASN_Octets object, size_t index, ITS_OCTET octet)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(IsIndexWithOffsetValid(object, index));

    ASN_OCTETS_DATA(object)[index + ASN_OCTETS_OFFSET(object)] = octet;
}

static int
Append(ASN_Octets object, const ASN_Octets other)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(other != NULL);

    if (ASN_OCTETS_SIZE(object) + ASN_OCTETS_SIZE(other) <= 
        ASN_OCTETS_RESERVED_SIZE(object))
    {
        memcpy(
            ASN_OCTETS_DATA(object) + ASN_OCTETS_SIZE(object),
            ASN_OCTETS_DATA(other), 
            ASN_OCTETS_SIZE(other));

        ASN_OCTETS_SIZE(object) += ASN_OCTETS_SIZE(other);
    }
    else
    {
        result = Reserve(
                    object, 
                    ASN_OCTETS_SIZE(object) + ASN_OCTETS_SIZE(other));

        if (result != ITS_SUCCESS)
        {
            return result;
        }

        memcpy(
            ASN_OCTETS_DATA(object) + ASN_OCTETS_SIZE(object),
            ASN_OCTETS_DATA(other),
            ASN_OCTETS_SIZE(other));

        ASN_OCTETS_SIZE(object) += ASN_OCTETS_SIZE(other);
    }

    return ITS_SUCCESS;
}



/*
 *  ASN_Octets class record.
 */ 

ASN_Octets_ClassRec itsASN_Octets_ClassRec =
{
    /* Core part. */

    {
        &itsCORE_ClassRec,              /* Core is superclass.      */
        sizeof(ASN_Octets_ObjectRec),   /* Size of instance.        */
        ITS_FALSE,                      /* Not initted.             */
        0,                              /* Initial reference count. */
        ASN_OCTETS_CLASS_NAME,          /* Class name.              */
        ITS_CLASS_NO_INIT,              /* Class initialize.        */
        ITS_CLASS_NO_DEST,              /* Class destroy.           */
        ITS_CLASS_PART_NO_INIT,         /* Class part initialize.   */
        ITS_CLASS_PART_NO_DEST,         /* Class part destroy.      */
        Construct,                      /* Instantiate.             */
        Destruct,                       /* Destroy.                 */
        Clone,                          /* Inherit clone.           */
        Print,                          /* Print.                   */
        ITS_INST_SERIAL_INHERIT,        /* Inherit serial.          */
        Equals,                         /* Inherit equals.          */
        ITS_INST_HASH_INHERIT,          /* Inherit equals.          */
        NULL                            /* No extension.            */
    },

    /* ASN_Octets class part. */

    {
        Reserve,
        GetArray,
        SetArray,
        GetSize,
        PrintWithOffset,
        ToString,
        ToStringWithOffset,
        GetOffset,
        SetOffset,
        IncrementOffset,
        DecrementOffset,
        IncrementOffsetWithIncrement,
        DecrementOffsetWithDecrement,
        IsIndexValid,
        IsIndexWithOffsetValid,
        IsOffsetValid,
        GetOctetAt,
        SetOctetAt,
        GetOctetAtWithOffset,
        SetOctetAtWithOffset,
        Append
    }
};


ASN_Octets 
ASN_Octets_ConstructDefault()
{
    ASN_Octets result = NULL;

    result = 
        (ASN_Octets)ITS_ConstructObject(
                            (ITS_Class)&itsASN_Octets_ClassRec, 
                            NULL, 
                            0);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Octets 
ASN_Octets_ConstructWithArray(const ITS_OCTET* array, size_t size)
{
    ASN_Octets result = NULL;

    result = 
        (ASN_Octets)ITS_ConstructObject(
                            (ITS_Class)&itsASN_Octets_ClassRec, 
                            array, 
                            size);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_Octets_Destruct(ASN_Octets object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Octets 
ASN_Octets_Clone(const ASN_Octets object)
{
    return (ASN_Octets)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Octets_Equals(const ASN_Octets object, const ASN_Octets other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

int 
ASN_Octets_Reserve(ASN_Octets object, size_t size)
{
    return ASN_OCTETS_CLASS_RESERVE(ITS_OBJ_CLASS(object))(object, size);
}

const ITS_OCTET* 
ASN_Octets_GetArray(const ASN_Octets object)
{
    return ASN_OCTETS_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_Octets_GetSize(const ASN_Octets object)
{
    return ASN_OCTETS_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Octets_SetArray(ASN_Octets object, const ITS_OCTET* array, size_t size)
{
    return ASN_OCTETS_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))(object, array, size);
}

void 
ASN_Octets_Print(const ASN_Octets object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

void 
ASN_Octets_PrintWithOffset(const ASN_Octets object)
{
    ASN_OCTETS_CLASS_PRINT_WITH_OFFSET(ITS_OBJ_CLASS(object))(object);
}

char* 
ASN_Octets_ToString(const ASN_Octets object)
{
    return ASN_OCTETS_CLASS_TO_STRING(ITS_OBJ_CLASS(object))(object);
}

char* 
ASN_Octets_ToStringWithOffset(const ASN_Octets object)
{
    return ASN_OCTETS_CLASS_TO_STRING_WITH_OFFSET(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_Octets_GetOffset(const ASN_Octets object)
{
    return ASN_OCTETS_CLASS_GET_OFFSET(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_Octets_SetOffset(ASN_Octets object, size_t offset)
{
    ASN_OCTETS_CLASS_SET_OFFSET(ITS_OBJ_CLASS(object))(object, offset);
}

void 
ASN_Octets_IncrementOffset(ASN_Octets object)
{
    ASN_OCTETS_CLASS_INCREMENT_OFFSET(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_Octets_IncrementOffsetWithIncrement(ASN_Octets object, size_t increment)
{
    ASN_OCTETS_CLASS_INCREMENT_OFFSET_WITH_INCREMENT(ITS_OBJ_CLASS(object))(object, increment);
}

void 
ASN_Octets_DecrementOffset(ASN_Octets object)
{
    ASN_OCTETS_CLASS_DECREMENT_OFFSET(ITS_OBJ_CLASS(object))(object);
}

void 
ASN_Octets_DecrementOffsetWithDecrement(ASN_Octets object, size_t decrement)
{
    ASN_OCTETS_CLASS_DECREMENT_OFFSET_WITH_DECREMENT(ITS_OBJ_CLASS(object))(object, decrement);
}

ITS_BOOLEAN 
ASN_Octets_IsIndexValid(const ASN_Octets object, size_t index)
{
    return ASN_OCTETS_CLASS_IS_INDEX_VALID(ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_Octets_IsIndexWithOffsetValid(const ASN_Octets object, size_t index)
{
    return ASN_OCTETS_CLASS_IS_INDEX_WITH_OFFSET_VALID(ITS_OBJ_CLASS(object))(object, index);
}

ITS_BOOLEAN 
ASN_Octets_IsOffsetValid(const ASN_Octets object, size_t offset)
{
    return ASN_OCTETS_CLASS_IS_OFFSET_VALID(ITS_OBJ_CLASS(object))(object, offset);
}

ITS_OCTET 
ASN_Octets_GetOctetAt(const ASN_Octets object, size_t index)
{
    return ASN_OCTETS_CLASS_GET_OCTET_AT(ITS_OBJ_CLASS(object))(object, index);
}

void 
ASN_Octets_SetOctetAt(ASN_Octets object, size_t index, ITS_OCTET octet)
{
    ASN_OCTETS_CLASS_SET_OCTET_AT(ITS_OBJ_CLASS(object))(object, index, octet);
}


ITS_OCTET 
ASN_Octets_GetOctetAtWithOffset(const ASN_Octets object, size_t index)
{
    return ASN_OCTETS_CLASS_GET_OCTET_AT_WITH_OFFSET(ITS_OBJ_CLASS(object))(object, index);
}

void 
ASN_Octets_SetOctetAtWithOffset(ASN_Octets object, size_t index, ITS_OCTET octet)
{
    ASN_OCTETS_CLASS_SET_OCTET_AT_WITH_OFFSET(ITS_OBJ_CLASS(object))(object, index, octet);
}

int
ASN_Octets_Append(ASN_Octets object, const ASN_Octets other)
{
    return ASN_OCTETS_CLASS_APPEND(ITS_OBJ_CLASS(object))(object, other);
}


