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
 *  ID: $Id: asn_object.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Object interface.
 */

#if !defined(_C_ASN_OBJECT_H_)
#define _C_ASN_OBJECT_H_

#include <its.h>
#include <its_object.h>

#include <asn_common.h>
#include <asn_assertion.h>
#include <asn_error.h>
#include <asn_octets.h>
#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

/* ASN_Object already defined in description. */
typedef struct _ASN_Object_ClassRec*    ASN_ObjectClass;



/*
 *  Procedure signatures.
 */

typedef int (*ASN_Object_EncodeProc)(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError);
typedef int (*ASN_Object_DecodeProc)(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError);
typedef const char* (*ASN_Object_GetNameProc)(const ASN_Object object);
typedef const char* (*ASN_Object_GetBaseNameProc)(const ASN_Object object);
typedef char* (*ASN_Object_ToStringProc)(const ASN_Object object);
typedef char* (*ASN_Object_GetEncodeExtendedErrorTextProc)(const ASN_Object object, ASN_Error error);
typedef char* (*ASN_Object_GetDecodeExtendedErrorTextProc)(const ASN_Object object, ASN_Error error, const ASN_Octets octets);
typedef ASN_Octets (*ASN_Object_EncodeTagLengthValueProc)(ASN_Object object, const ASN_Octets value);
typedef int (*ASN_Object_DecodeRemoveExtraTagLengthProc)(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError);


/*
 *  Procedure overrides.
 */

#define ASN_OBJECT_ENCODE_INHERIT                           (ASN_Object_EncodeProc)NULL
#define ASN_OBJECT_DECODE_INHERIT                           (ASN_Object_DecodeProc)NULL
#define ASN_OBJECT_GET_NAME_INHERIT                         (ASN_Object_GetNameProc)NULL
#define ASN_OBJECT_GET_BASE_NAME_INHERIT                    (ASN_Object_GetBaseNameProc)NULL
#define ASN_OBJECT_TO_STRING_INHERIT                        (ASN_Object_ToStringProc)NULL
#define ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT   (ASN_Object_GetEncodeExtendedErrorTextProc)NULL
#define ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT   (ASN_Object_GetDecodeExtendedErrorTextProc)NULL
#define ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT          (ASN_Object_EncodeTagLengthValueProc)NULL
#define ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT   (ASN_Object_DecodeRemoveExtraTagLengthProc)NULL


/* ASN_Object class. */

typedef struct
{
    ASN_Object_EncodeProc                       encode;
    ASN_Object_DecodeProc                       decode;
    ASN_Object_GetNameProc                      getName;
    ASN_Object_GetBaseNameProc                  getBaseName;
    ASN_Object_ToStringProc                     toString;
    ASN_Object_GetEncodeExtendedErrorTextProc   getEncodeExtendedErrorText;
    ASN_Object_GetDecodeExtendedErrorTextProc   getDecodeExtendedErrorText;
    ASN_Object_EncodeTagLengthValueProc         encodeTagLengthValue;
    ASN_Object_DecodeRemoveExtraTagLengthProc   decodeRemoveExtraTagLength;
} ASN_Object_ClassPart;


typedef struct _ASN_Object_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
} ASN_Object_ClassRec;

#define ASN_OBJECT_CLASS_ENCODE(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.encode)

#define ASN_OBJECT_CLASS_DECODE(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.decode)

#define ASN_OBJECT_CLASS_GET_NAME(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.getName)

#define ASN_OBJECT_CLASS_GET_BASE_NAME(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.getBaseName)

#define ASN_OBJECT_CLASS_TO_STRING(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.toString)

#define ASN_OBJECT_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.getEncodeExtendedErrorText)

#define ASN_OBJECT_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.getDecodeExtendedErrorText)

#define ASN_OBJECT_CLASS_ENCODE_TAG_LENGTH_VALUE(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.encodeTagLengthValue)

#define ASN_OBJECT_CLASS_DECODE_REMOVE_EXTRA_TAG_LENGTH(x) \
    (((ASN_ObjectClass)(x))->asnObjectClass.decodeRemoveExtraTagLength)

/*
 *  For inheritance.
 */ 

extern ASN_Object_ClassRec        itsASN_Object_ClassRec;


/* ASN_Object object. */

typedef struct _ASN_Object_ObjectPart
{
    ASN_DescObject description;
} ASN_Object_ObjectPart;


typedef struct _ASN_Object_ObjectRec
{
    ITS_CoreObjectPart core;
    ASN_Object_ObjectPart asnObject;
} ASN_Object_ObjectRec;

#define ASN_OBJECT_DESCRIPTION(x) \
    (((ASN_Object)(x))->asnObject.description)

#define ASN_OBJECT_CLASS_NAME "ASN_Object"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

void ASN_Object_Destruct(ASN_Object object);

ASN_Object ASN_Object_Clone(const ASN_Object object);

ITS_BOOLEAN ASN_Object_Equals(const ASN_Object object, const ASN_Object other);

char* ASN_Object_GetEncodeExtendedErrorText(
                                        const ASN_Object object, 
                                        ASN_Error error);

char* ASN_Object_GetDecodeExtendedErrorText(
                                        const ASN_Object object, 
                                        ASN_Error error, 
                                        const ASN_Octets octets);

ASN_Octets ASN_Object_EncodeTagLengthValue(
                                        ASN_Object object, 
                                        const ASN_Octets value);

int ASN_Object_DecodeRemoveExtraTagLength(
                                        ASN_Object object, 
                                        ASN_Octets octets,
                                        ASN_DecodeError* decodeError);

int ASN_Object_Encode(
                    ASN_Object object, 
                    ASN_Octets* octets, 
                    ASN_EncodeError* encodeError);

int ASN_Object_Decode(
                    ASN_Object object, 
                    ASN_Octets octets, 
                    ASN_DecodeError* decodeError);

const char* ASN_Object_GetName(const ASN_Object object);

const char* ASN_Object_GetBaseName(const ASN_Object object);

char* ASN_Object_ToString(const ASN_Object object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_OBJECT_H_) */
