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
 *  ID: $Id: asn_error.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_error.h>


const char* 
ASN_Error_GetText(ASN_Error error)
{
    switch (error)
    {
    case ASN_E_INDEFINITE_LENGTH:
        return "indefinite length";

    case ASN_E_INVALID_BOOLEAN_LENGTH:
        return "invalid boolean length";

    case ASN_E_INVALID_CHOICE:
        return "invalid choice";

    case ASN_E_UNKNOWN_CHOICE:
        return "unknown choice";

    case ASN_E_INVALID_ENUMERATED_VALUE:
        return "invalid enumerated value";

    case ASN_E_INDEFINITE_ENUMERATED_LENGTH:
        return "indefinite enumerated length";

    case ASN_E_NULL_ENUMERATED_LENGTH:
        return "null enumerated length";

    case ASN_E_ENUMERATED_LENGTH_TOO_LARGE:
        return "enumerated length too large";

    case ASN_E_INVALID_ENUMERATED_LENGTH:
        return "invalid enumerated length";

    case ASN_E_INTEGER_VALUE_OUT_OF_RANGE:
        return "integer value out of range";

    case ASN_E_INDEFINITE_INTEGER_LENGTH:
        return "indefinite integer length";

    case ASN_E_NULL_INTEGER_LENGTH:
        return "null integer length";

    case ASN_E_INTEGER_LENGTH_TOO_LARGE:
        return "integer length too large";

    case ASN_E_INVALID_INTEGER_LENGTH:
        return "invalid integer length";

    case ASN_E_INVALID_NULL_LENGTH:
        return "invalid null length";

    case ASN_E_INVALID_OCTET_STRING_SIZE:
        return "invalid octet string size";

    case ASN_E_CONSTRUCTED_OCTET_STRING:
        return "constructed octet string";

    case ASN_E_INDEFINITE_OCTET_STRING_LENGTH:
        return "indefinite octet string length";

    case ASN_E_INVALID_OCTET_STRING_LENGTH:
        return "invalid octet string length";

    case ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE:
        return "unknown element in sequence";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE:
        return "invalid element length in sequence";

    case ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE:
        return "missing mandatory element in sequence";

    case ASN_E_INVALID_SEQUENCE_OF_SIZE:
        return "invalid sequence of size";

    case ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF:
        return "unknown element in sequence of";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE_OF:
        return "invalid element length in sequence of";

    case ASN_E_UNKNOWN_ELEMENT_IN_SET:
        return "unknown element in set";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SET:
        return "invalid element length in set";

    case ASN_E_MISSING_MANDATORY_ELEMENT_IN_SET:
        return "missing mandatory element in set";

    case ASN_E_INVALID_SET_OF_SIZE:
        return "invalid set of size";

    case ASN_E_UNKNOWN_ELEMENT_IN_SET_OF:
        return "unknown element in set of";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SET_OF:
        return "invalid element length in set of";

    case ASN_E_NO_CHOICE_PRESENT:
        return "no choice present";

    case ASN_E_INVALID_BIT_STRING_SIZE:
        return "invalid bit string size";

    case ASN_E_CONSTRUCTED_BIT_STRING:
        return "constructed bit string";

    case ASN_E_INDEFINITE_BIT_STRING_LENGTH:
        return "indefinite bit string length";

    case ASN_E_NULL_BIT_STRING_LENGTH:
        return "null bit string length";

    case ASN_E_INVALID_BIT_STRING_LENGTH:
        return "invalid bit string length";

    case ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER:
        return "invalid bit string unused bits number";

    case ASN_E_NO_ANY_PRESENT:
        return "no any present";

    case ASN_E_INDEFINITE_ANY_LENGTH:
        return "indefinite any length";

    case ASN_E_INVALID_ANY_LENGTH:
        return "invalid any length";

    case ASN_E_CONSTRUCTED_OID:
        return "constructed object identifier";

    case ASN_E_INDEFINITE_OID_LENGTH:
        return "indefinite object identifier length";

    case ASN_E_NULL_OID_LENGTH:
        return "null object identifier length";

    case ASN_E_INVALID_OID_LENGTH:
        return "invalid object identifier length";

    case ASN_E_OID_CPT_VALUE_OUT_OF_RANGE:
        return "object identifier component value out of range";

    case ASN_E_OID_CPT_VALUE_INVALID:
        return "object identifier component value invalid";

    case ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID:
        return "invalid number of components in object identifier";

    case ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID:
        return "invalid first component value in object identifier";

    case ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID:
        return "invalid second component value in object identifier";

    case ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID:
        return "invalid negative component value in object identifier";

    case ASN_E_INDEFINITE_REAL_LENGTH:
        return "indefinite real length";

    case ASN_E_NULL_REAL_LENGTH:
        return "null real length";

    case ASN_E_REAL_VALUE_OUT_OF_RANGE:
        return "real value out of range";

    case ASN_E_REAL_LENGTH_TOO_LARGE:
        return "real length too large";

    case ASN_E_INVALID_REAL_LENGTH:
        return "invalid real length";

    case ASN_E_INVALID_TAG_LENGTH:
        return "invalid tag length";

    case ASN_E_INVALID_UNIVERSAL_NUMBER:
        return "invalid universal number";

    case ASN_E_INVALID_LENGTH_LENGTH:
        return "invalid length length";

    case ASN_E_INVALID_INDEFINITE_LENGTH_LENGTH:
        return "invalid indefinite length length";

    default:
        return "undefined error";
    }
}


ASN_EncodeError 
ASN_EncodeError_Construct(
                        ASN_Error error, 
                        char* extendedError,
                        const char* file,
                        ITS_ULONG line)
{
    ASN_EncodeError result = NULL;

    ASN_C_REQUIRE(extendedError != NULL);

    result = (ASN_EncodeError)calloc(1, sizeof(ASN_EncodeError_ObjectRec));

    ASN_C_ENSURE(result != NULL);

    if (result == NULL)
    {
        free(extendedError);

        return NULL;
    }

    result->error = error;
    result->extendedError = extendedError;
    result->file = file;
    result->line = line;

    return result;
}

void 
ASN_EncodeError_Destruct(ASN_EncodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    free(object->extendedError);
    free(object);
}

ASN_Error 
ASN_EncodeError_GetError(const ASN_EncodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return object->error;
}

const char* 
ASN_EncodeError_GetErrorText(const ASN_EncodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Error_GetText(object->error);
}

const char* 
ASN_EncodeError_GetExtendedErrorText(const ASN_EncodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return object->extendedError;
}

char* 
ASN_EncodeError_ToString(const ASN_EncodeError object)
{
    char* result            = NULL;
    char* buffer            = NULL;
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(object != NULL);

    maxStringSize = 256 + 
                    strlen(ASN_Error_GetText(object->error)) +
                    strlen(object->extendedError);

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "[ASN.1 encode error | Error text <%s> | "
        "Extended error text <%s> | File <%s> | Line <%lu>]",
        ASN_Error_GetText(object->error),
        object->extendedError,
        object->file,
        object->line);

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_EncodeError_Print(const ASN_EncodeError object)
{
    char* toString = NULL;

    ASN_C_REQUIRE(object != NULL);

    toString = ASN_EncodeError_ToString(object);

    if (toString != NULL)
    {
        printf("%s", toString);

        free(toString);
    }
}

ASN_DecodeError 
ASN_DecodeError_Construct(
                    ASN_Error error, 
                    char* extendedError, 
                    const ASN_Octets octets,
                    const char* file,
                    ITS_ULONG line)
{
    ASN_DecodeError result = NULL;

    ASN_C_REQUIRE(extendedError != NULL);
    ASN_C_REQUIRE(octets != NULL);

    result = (ASN_DecodeError)calloc(1, sizeof(ASN_DecodeError_ObjectRec));

    ASN_C_ENSURE(result != NULL);

    if (result == NULL)
    {
        free(extendedError);

        return NULL;
    }

    result->error = error;
    result->extendedError = extendedError;
    result->octets = ASN_Octets_Clone(octets);
    result->file = file;
    result->line = line;

    if (result->octets == NULL)
    {
        free(extendedError);
        free(result);

        result = NULL;

        ASN_C_ENSURE(result != NULL);

        return result;
    }

    return result;
}

void ASN_DecodeError_Destruct(ASN_DecodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    free(object->extendedError);
    ASN_Octets_Destruct(object->octets);
    free(object);
}

ASN_Error 
ASN_DecodeError_GetError(const ASN_DecodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return object->error;
}

const char* 
ASN_DecodeError_GetErrorText(const ASN_DecodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Error_GetText(object->error);
}

const char* 
ASN_DecodeError_GetExtendedErrorText(const ASN_DecodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return object->extendedError;
}

const ASN_Octets
ASN_DecodeError_GetOctets(const ASN_DecodeError object)
{
    ASN_C_REQUIRE(object != NULL);

    return object->octets;
}

char* 
ASN_DecodeError_ToString(const ASN_DecodeError object)
{
    char* result            = NULL;
    char* buffer            = NULL;
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(object != NULL);

    maxStringSize = 256 + 
                    strlen(ASN_Error_GetText(object->error)) +
                    strlen(object->extendedError);

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "[ASN.1 decode error | Error text <%s> | "
        "Extended error text <%s> | File <%s> | Line <%lu>]",
        ASN_Error_GetText(object->error),
        object->extendedError,
        object->file,
        object->line);

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DecodeError_Print(const ASN_DecodeError object)
{
    char* toString = NULL;

    ASN_C_REQUIRE(object != NULL);

    toString = ASN_DecodeError_ToString(object);

    if (toString != NULL)
    {
        printf("%s", toString);

        free(toString);
    }
}

