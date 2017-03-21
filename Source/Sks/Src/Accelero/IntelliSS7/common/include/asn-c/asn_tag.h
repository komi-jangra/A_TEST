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
 *  ID: $Id: asn_tag.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Tag interface.
 */

#if !defined(_C_ASN_TAG_H_)
#define _C_ASN_TAG_H_

#include <its.h>
#include <its_object.h>

#include <asn_common.h>
#include <asn_assertion.h>
#include <asn_error.h>
#include <asn_octets.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Preprocessor constant definitions.
 */


/*
 *  Tag classes.
 */

#define TAG_CLASS_UNIVERSAL          0x00U
#define TAG_CLASS_APPLICATION        0x01U
#define TAG_CLASS_CONTEXT_SPECIFIC   0x02U
#define TAG_CLASS_PRIVATE            0x03U


/*
 *  Tag types.
 */

#define TAG_PRIMITIVE    0x00U
#define TAG_CONSTRUCTED  0x01U 


/*
 *  Universal tag numbers.
 */

#define TAG_BOOLEAN            1
#define TAG_INTEGER            2
#define TAG_BIT_STRING         3
#define TAG_OCTET_STRING       4
#define TAG_NULL               5
#define TAG_OBJECT_IDENTIFIER  6
#define TAG_OBJECT_DESCRIPTOR  7
#define TAG_EXTERNAL           8
#define TAG_REAL               9
#define TAG_ENUMERATED         10
#define TAG_ENCRYPTED          11

/* 12 - 15 reserved for future versions. */

#define TAG_SEQUENCE           16
#define TAG_SET                17
#define TAG_NUMERICAL_STRING   18
#define TAG_PRINTABLE_STRING   19
#define TAG_TELETEX_STRING     20
#define TAG_VIDEOTEX_STRING    21
#define TAG_IA5_STRING         22
#define TAG_UTC_TIME           23
#define TAG_GENERALIZED_TIME   24
#define TAG_GRAPHICS_STRING    25
#define TAG_VISIBLE_STRING     26
#define TAG_GENERAL_STRING     27

/* 28 - 30 reserved for future versions. */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Tag_ObjectRec*    ASN_Tag;
typedef struct _ASN_Tag_ClassRec*     ASN_TagClass;


/*
 *  Procedure signatures.
 */

typedef int         (*ASN_Tag_EncodeProc)(
                                    ASN_Tag object, 
                                    ASN_Octets* octets, 
                                    ASN_EncodeError* encodeError);

typedef int         (*ASN_Tag_DecodeProc)(
                                    ASN_Tag object, 
                                    ASN_Octets octets, 
                                    ASN_DecodeError* decodeError);

typedef int         (*ASN_Tag_DecodePreserveOffsetProc)(
                                    ASN_Tag object, 
                                    ASN_Octets octets, 
                                    ASN_DecodeError* decodeError);

typedef void        (*ASN_Tag_SetTagClassProc)(
                                    ASN_Tag object, 
                                    ITS_OCTET tagClass);

typedef void        (*ASN_Tag_SetTypeProc)(
                                    ASN_Tag object, 
                                    ITS_OCTET type);

typedef void        (*ASN_Tag_SetNumberProc)(
                                    ASN_Tag object, 
                                    ITS_ULONG number);

typedef ITS_OCTET   (*ASN_Tag_GetTagClassProc)(
                                    const ASN_Tag object);

typedef ITS_OCTET   (*ASN_Tag_GetTypeProc)(
                                    const ASN_Tag object);

typedef ITS_ULONG   (*ASN_Tag_GetNumberProc)(
                                    const ASN_Tag object);

typedef char*       (*ASN_Tag_ToStringProc)(
                                    const ASN_Tag object);

typedef char*       (*ASN_Tag_GetEncodeExtendedErrorTextProc)(
                                    const ASN_Tag object, 
                                    ASN_Error error);

typedef char*       (*ASN_Tag_GetDecodeExtendedErrorTextProc)(
                                    const ASN_Tag object, 
                                    ASN_Error error, 
                                    const ASN_Octets octets);

typedef ITS_BOOLEAN (*ASN_Tag_IsUniversalProc)(
                                    const ASN_Tag object, 
                                    ITS_ULONG number);

typedef ITS_BOOLEAN (*ASN_Tag_InvariantProc)(
                                    const ASN_Tag object);


/* ASN_Tag class. */

typedef struct _ASN_Tag_ClassPart
{
    ASN_Tag_EncodeProc                      encode;
    ASN_Tag_DecodeProc                      decode;
    ASN_Tag_DecodePreserveOffsetProc        decodePreserveOffset;
    ASN_Tag_SetTagClassProc                 setTagClass;
    ASN_Tag_SetTypeProc                     setType;
    ASN_Tag_SetNumberProc                   setNumber;
    ASN_Tag_GetTagClassProc                 getTagClass;
    ASN_Tag_GetTypeProc                     getType;
    ASN_Tag_GetNumberProc                   getNumber;
    ASN_Tag_ToStringProc                    toString;
    ASN_Tag_GetEncodeExtendedErrorTextProc  getEncodeExtendedErrorText;
    ASN_Tag_GetDecodeExtendedErrorTextProc  getDecodeExtendedErrorText;
    ASN_Tag_IsUniversalProc                 isUniversal;
    ASN_Tag_InvariantProc                   invariant;
} ASN_Tag_ClassPart;

typedef struct _ASN_Tag_ClassRec
{
    ITS_CoreClassPart   coreClass;
    ASN_Tag_ClassPart   asnTagClass;
} ASN_Tag_ClassRec;

#define ASN_TAG_CLASS_ENCODE(x) \
    (((ASN_TagClass)(x))->asnTagClass.encode)

#define ASN_TAG_CLASS_DECODE(x) \
    (((ASN_TagClass)(x))->asnTagClass.decode)

#define ASN_TAG_CLASS_DECODE_PRESERVE_OFFSET(x) \
    (((ASN_TagClass)(x))->asnTagClass.decodePreserveOffset)

#define ASN_TAG_CLASS_SET_TAG_CLASS(x) \
    (((ASN_TagClass)(x))->asnTagClass.setTagClass)

#define ASN_TAG_CLASS_SET_TYPE(x) \
    (((ASN_TagClass)(x))->asnTagClass.setType)

#define ASN_TAG_CLASS_SET_NUMBER(x) \
    (((ASN_TagClass)(x))->asnTagClass.setNumber)

#define ASN_TAG_CLASS_GET_TAG_CLASS(x) \
    (((ASN_TagClass)(x))->asnTagClass.getTagClass)

#define ASN_TAG_CLASS_GET_TYPE(x) \
    (((ASN_TagClass)(x))->asnTagClass.getType)

#define ASN_TAG_CLASS_GET_NUMBER(x) \
    (((ASN_TagClass)(x))->asnTagClass.getNumber)

#define ASN_TAG_CLASS_TO_STRING(x) \
    (((ASN_TagClass)(x))->asnTagClass.toString)

#define ASN_TAG_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(x) \
    (((ASN_TagClass)(x))->asnTagClass.getEncodeExtendedErrorText)

#define ASN_TAG_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(x) \
    (((ASN_TagClass)(x))->asnTagClass.getDecodeExtendedErrorText)

#define ASN_TAG_CLASS_IS_UNIVERSAL(x) \
    (((ASN_TagClass)(x))->asnTagClass.isUniversal)

#define ASN_TAG_CLASS_INVARIANT(x) \
    (((ASN_TagClass)(x))->asnTagClass.invariant)

/* ASN_Tag object. */

typedef struct _ASN_Tag_ObjectPart
{
    ITS_OCTET   tagClass;
    ITS_OCTET   type;
    ITS_ULONG   number;
} ASN_Tag_ObjectPart;


typedef struct _ASN_Tag_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Tag_ObjectPart      asnTag;
} ASN_Tag_ObjectRec;

#define ASN_TAG_TAG_CLASS(x)                \
    (((ASN_Tag)(x))->asnTag.tagClass)

#define ASN_TAG_TYPE(x)                     \
    (((ASN_Tag)(x))->asnTag.type)

#define ASN_TAG_NUMBER(x)                   \
    (((ASN_Tag)(x))->asnTag.number)

#define ASN_TAG_CLASS_NAME "ASN_Tag"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/


ASN_Tag ASN_Tag_ConstructDefault();

ASN_Tag ASN_Tag_ConstructWithClassTypeNumber(
                                        ITS_OCTET tagClass, 
                                        ITS_OCTET type, 
                                        ITS_ULONG number);

void ASN_Tag_Destruct(ASN_Tag object);

ASN_Tag ASN_Tag_Clone(const ASN_Tag object);

ITS_BOOLEAN ASN_Tag_Equals(const ASN_Tag object, const ASN_Tag other);

int ASN_Tag_Encode(
                ASN_Tag object, 
                ASN_Octets* octets, 
                ASN_EncodeError* encodeError);

int ASN_Tag_Decode(
                ASN_Tag object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError);

int ASN_Tag_DecodePreserveOffset(
                ASN_Tag object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError);

void ASN_Tag_SetTagClass(ASN_Tag object, ITS_OCTET tagClass);

void ASN_Tag_SetType(ASN_Tag object, ITS_OCTET type);

void ASN_Tag_SetNumber(ASN_Tag object, ITS_ULONG number);

ITS_OCTET ASN_Tag_GetTagClass(const ASN_Tag object);

ITS_OCTET ASN_Tag_GetType(const ASN_Tag object);

ITS_ULONG ASN_Tag_GetNumber(const ASN_Tag object);

char* ASN_Tag_ToString(const ASN_Tag object);

void ASN_Tag_Print(const ASN_Tag object);

char* ASN_Tag_GetEncodeExtendedErrorText(
                                const ASN_Tag object, 
                                ASN_Error error);

char* ASN_Tag_GetDecodeExtendedErrorText(
                                const ASN_Tag object, 
                                ASN_Error error, 
                                const ASN_Octets octets);

ITS_BOOLEAN ASN_Tag_IsUniversal(const ASN_Tag object, ITS_ULONG number);

ITS_BOOLEAN ASN_Tag_Invariant(const ASN_Tag object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_TAG_H_) */
