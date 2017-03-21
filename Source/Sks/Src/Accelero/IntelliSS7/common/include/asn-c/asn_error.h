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
 *  ID: $Id: asn_error.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#if !defined(_C_ASN_ERROR_H_)
#define _C_ASN_ERROR_H_

#include <its.h>
#include <its_object.h>
#include <asn_assertion.h>
#include <asn_octets.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/* More user-friendly constants. */

#define ITS_E_ASN_ENCODE_ERROR  ITS_EASNENCODE
#define ITS_E_ASN_DECODE_ERROR  ITS_EASNDECODE


/* Precise ASN.1 errors. */

typedef enum {

    /* General errors. */

    ASN_E_INDEFINITE_LENGTH,

    /* Type releated errors. */

    ASN_E_INVALID_BOOLEAN_LENGTH,
    ASN_E_INVALID_CHOICE,
    ASN_E_UNKNOWN_CHOICE,
    ASN_E_INVALID_ENUMERATED_VALUE,
    ASN_E_INDEFINITE_ENUMERATED_LENGTH,
    ASN_E_NULL_ENUMERATED_LENGTH,
    ASN_E_ENUMERATED_LENGTH_TOO_LARGE,
    ASN_E_INVALID_ENUMERATED_LENGTH,
    ASN_E_INTEGER_VALUE_OUT_OF_RANGE,
    ASN_E_INDEFINITE_INTEGER_LENGTH,
    ASN_E_NULL_INTEGER_LENGTH,
    ASN_E_INTEGER_LENGTH_TOO_LARGE,
    ASN_E_INVALID_INTEGER_LENGTH,
    ASN_E_INVALID_NULL_LENGTH,
    ASN_E_INVALID_OCTET_STRING_SIZE,
    ASN_E_CONSTRUCTED_OCTET_STRING,
    ASN_E_INDEFINITE_OCTET_STRING_LENGTH,
    ASN_E_INVALID_OCTET_STRING_LENGTH,
    ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE,
    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE,
    ASN_E_INVALID_SEQUENCE_OF_SIZE,
    ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE_OF,
    ASN_E_UNKNOWN_ELEMENT_IN_SET,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SET,
    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SET,
    ASN_E_INVALID_SET_OF_SIZE,
    ASN_E_UNKNOWN_ELEMENT_IN_SET_OF,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SET_OF,
    ASN_E_NO_CHOICE_PRESENT,
    ASN_E_INVALID_BIT_STRING_SIZE,
    ASN_E_CONSTRUCTED_BIT_STRING,
    ASN_E_INDEFINITE_BIT_STRING_LENGTH,
    ASN_E_NULL_BIT_STRING_LENGTH,
    ASN_E_INVALID_BIT_STRING_LENGTH,
    ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
    ASN_E_NO_ANY_PRESENT,
    ASN_E_INDEFINITE_ANY_LENGTH,
    ASN_E_INVALID_ANY_LENGTH,
    ASN_E_CONSTRUCTED_OID,
    ASN_E_INDEFINITE_OID_LENGTH,
    ASN_E_NULL_OID_LENGTH,
    ASN_E_INVALID_OID_LENGTH,
    ASN_E_OID_CPT_VALUE_OUT_OF_RANGE,
    ASN_E_OID_CPT_VALUE_INVALID,
    ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID,
    ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID,
    ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID,
    ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID,
    ASN_E_INDEFINITE_REAL_LENGTH,
    ASN_E_NULL_REAL_LENGTH,
    ASN_E_REAL_VALUE_OUT_OF_RANGE,
    ASN_E_REAL_LENGTH_TOO_LARGE,
    ASN_E_INVALID_REAL_LENGTH,

    /* Tag related errors. */

    ASN_E_INVALID_TAG_LENGTH,
    ASN_E_INVALID_UNIVERSAL_NUMBER,

    /* Length related errors. */

    ASN_E_INVALID_LENGTH_LENGTH,
    ASN_E_INVALID_INDEFINITE_LENGTH_LENGTH

} ASN_Error;


/* ASN Encode Error object. */

typedef struct _ASN_EncodeError_ObjectRec
{
    ASN_Error   error;
    char*       extendedError;
    const char* file;
    ITS_ULONG   line;
} ASN_EncodeError_ObjectRec;

typedef struct _ASN_EncodeError_ObjectRec* ASN_EncodeError;



/* ASN Decode Error object. */

typedef struct _ASN_DecodeError_ObjectRec
{
    ASN_Error   error;
    char*       extendedError;
    ASN_Octets  octets;
    const char* file;
    ITS_ULONG   line;
} ASN_DecodeError_ObjectRec;

typedef struct _ASN_DecodeError_ObjectRec* ASN_DecodeError;



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Public interface.                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/


const char* ASN_Error_GetText(ASN_Error error);


ASN_EncodeError ASN_EncodeError_Construct(
                                    ASN_Error error, 
                                    char* extendedError, 
                                    const char* file, 
                                    ITS_ULONG line);

void ASN_EncodeError_Destruct(ASN_EncodeError object);

ASN_Error ASN_EncodeError_GetError(const ASN_EncodeError object);

const char* ASN_EncodeError_GetErrorText(const ASN_EncodeError object);

const char* ASN_EncodeError_GetExtendedErrorText(const ASN_EncodeError object);

char* ASN_EncodeError_ToString(const ASN_EncodeError object);

void ASN_EncodeError_Print(const ASN_EncodeError object);



ASN_DecodeError ASN_DecodeError_Construct(
                                    ASN_Error error, 
                                    char* extendedError, 
                                    const ASN_Octets octets, 
                                    const char* file, 
                                    ITS_ULONG line);

void ASN_DecodeError_Destruct(ASN_DecodeError object);

ASN_Error ASN_DecodeError_GetError(const ASN_DecodeError object);

const char* ASN_DecodeError_GetErrorText(const ASN_DecodeError object);

const char* ASN_DecodeError_GetExtendedErrorText(const ASN_DecodeError object);

const ASN_Octets ASN_DecodeError_GetOctets(const ASN_DecodeError object);

char* ASN_DecodeError_ToString(const ASN_DecodeError object);

void ASN_DecodeError_Print(const ASN_DecodeError object);


/*
 *  Helper macros.
 */

#define ASN_CONSTRUCT_ENCODE_ERROR(error, object)                       \
    ASN_EncodeError_Construct(                                          \
        (error),                                                        \
        ASN_Object_GetEncodeExtendedErrorText((object), (error)),       \
        __FILE__,                                                       \
        __LINE__);                                                      

#define ASN_CONSTRUCT_DECODE_ERROR(error, object, octets)                   \
    ASN_DecodeError_Construct(                                              \
        (error),                                                            \
        ASN_Object_GetDecodeExtendedErrorText((object), (error), (octets)), \
        (octets),                                                           \
        __FILE__,                                                           \
        __LINE__);

#define ASN_CONSTRUCT_TAG_ENCODE_ERROR(error, object)                   \
    ASN_EncodeError_Construct(                                          \
        (error),                                                        \
        ASN_Tag_GetEncodeExtendedErrorText((object), (error)),          \
        __FILE__,                                                       \
        __LINE__);                                                      

#define ASN_CONSTRUCT_TAG_DECODE_ERROR(error, object, octets)               \
    ASN_DecodeError_Construct(                                              \
        (error),                                                            \
        ASN_Tag_GetDecodeExtendedErrorText((object), (error), (octets)),    \
        (octets),                                                           \
        __FILE__,                                                           \
        __LINE__);

#define ASN_CONSTRUCT_LENGTH_ENCODE_ERROR(error, object)                \
    ASN_EncodeError_Construct(                                          \
        (error),                                                        \
        ASN_Length_GetEncodeExtendedErrorText((object), (error)),       \
        __FILE__,                                                       \
        __LINE__);                                                      

#define ASN_CONSTRUCT_LENGTH_DECODE_ERROR(error, object, octets)            \
    ASN_DecodeError_Construct(                                              \
        (error),                                                            \
        ASN_Length_GetDecodeExtendedErrorText((object), (error), (octets)), \
        (octets),                                                           \
        __FILE__,                                                           \
        __LINE__);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_ERROR_H_) */
