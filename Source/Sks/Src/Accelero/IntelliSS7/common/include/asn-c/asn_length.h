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
 *  ID: $Id: asn_length.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Length interface.
 */

#if !defined(_C_ASN_LENGTH_H_)
#define _C_ASN_LENGTH_H_

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
 *  Forward declarations.
 */ 

typedef struct _ASN_Length_ObjectRec*    ASN_Length;
typedef struct _ASN_Length_ClassRec*     ASN_LengthClass;


/*
 *  Procedure signatures.
 */

typedef int         (*ASN_Length_EncodeProc)(
                                    ASN_Length object, 
                                    ASN_Octets* octets, 
                                    ASN_EncodeError* encodeError);

typedef int         (*ASN_Length_DecodeProc)(
                                    ASN_Length object, 
                                    ASN_Octets octets, 
                                    ASN_DecodeError* decodeError);

typedef int         (*ASN_Length_DecodePreserveOffsetProc)(
                                    ASN_Length object, 
                                    ASN_Octets octets, 
                                    ASN_DecodeError* decodeError);

typedef void        (*ASN_Length_SetLengthProc)(
                                    ASN_Length object, 
                                    ITS_LONG length);

typedef ITS_LONG    (*ASN_Length_GetLengthProc)(
                                    const ASN_Length object);

typedef ITS_BOOLEAN (*ASN_Length_IsIndefiniteProc)(
                                    const ASN_Length object);

typedef ITS_BOOLEAN (*ASN_Length_IsIndefiniteEndMarkProc)(
                                    const ASN_Length object,
                                    const ASN_Octets octets);

typedef void        (*ASN_Length_IndefiniteEndMarkIncOffsetProc)(
                                    const ASN_Length object,
                                    ASN_Octets octets);

typedef char*       (*ASN_Length_ToStringProc)(
                                    const ASN_Length object);

typedef char*       (*ASN_Length_GetEncodeExtendedErrorTextProc)(
                                    const ASN_Length object, 
                                    ASN_Error error);

typedef char*       (*ASN_Length_GetDecodeExtendedErrorTextProc)(
                                    const ASN_Length object, 
                                    ASN_Error error, 
                                    const ASN_Octets octets);

/* ASN_Length class. */

typedef struct _ASN_Length_ClassPart
{
    ASN_Length_EncodeProc                       encode;
    ASN_Length_DecodeProc                       decode;
    ASN_Length_DecodePreserveOffsetProc         decodePreserveOffset;
    ASN_Length_SetLengthProc                    setLength;
    ASN_Length_GetLengthProc                    getLength;
    ASN_Length_IsIndefiniteProc                 isIndefinite;
    ASN_Length_IsIndefiniteEndMarkProc          isIndefiniteEndMark;
    ASN_Length_IndefiniteEndMarkIncOffsetProc   indefiniteEndMarkIncOffset;
    ASN_Length_ToStringProc                     toString;
    ASN_Length_GetEncodeExtendedErrorTextProc   getEncodeExtendedErrorText;
    ASN_Length_GetDecodeExtendedErrorTextProc   getDecodeExtendedErrorText;
} ASN_Length_ClassPart;

typedef struct _ASN_Length_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Length_ClassPart    asnLengthClass;
} ASN_Length_ClassRec;

#define ASN_LENGTH_CLASS_ENCODE(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.encode)

#define ASN_LENGTH_CLASS_DECODE(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.decode)

#define ASN_LENGTH_CLASS_DECODE_PRESERVE_OFFSET(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.decodePreserveOffset)

#define ASN_LENGTH_CLASS_SET_LENGTH(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.setLength)

#define ASN_LENGTH_CLASS_GET_LENGTH(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.getLength)

#define ASN_LENGTH_CLASS_IS_INDEFINITE(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.isIndefinite)

#define ASN_LENGTH_CLASS_IS_INDEFINITE_END_MARK(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.isIndefiniteEndMark)

#define ASN_LENGTH_CLASS_INDEFINITE_END_MARK_INC_OFFSET(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.indefiniteEndMarkIncOffset)

#define ASN_LENGTH_CLASS_TO_STRING(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.toString)

#define ASN_LENGTH_CLASS_GET_ENCODE_EXTENDED_ERROR_TEXT(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.getEncodeExtendedErrorText)

#define ASN_LENGTH_CLASS_GET_DECODE_EXTENDED_ERROR_TEXT(x) \
    (((ASN_LengthClass)(x))->asnLengthClass.getDecodeExtendedErrorText)

/* ASN_Length object. */

typedef struct _ASN_Length_ObjectPart
{
    ITS_LONG    length;
} ASN_Length_ObjectPart;


typedef struct _ASN_Length_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Length_ObjectPart   asnLength;
} ASN_Length_ObjectRec;

#define ASN_LENGTH_LENGTH(x)                \
    (((ASN_Length)(x))->asnLength.length)

#define ASN_LENGTH_CLASS_NAME "ASN_Length"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/


ASN_Length ASN_Length_ConstructDefault();

ASN_Length ASN_Length_ConstructWithLength(ITS_LONG length); 

void ASN_Length_Destruct(ASN_Length object);

ASN_Length ASN_Length_Clone(const ASN_Length object);

ITS_BOOLEAN ASN_Length_Equals(const ASN_Length object, const ASN_Length other);

int ASN_Length_Encode(
                ASN_Length object, 
                ASN_Octets* octets, 
                ASN_EncodeError* encodeError);

int ASN_Length_Decode(
                ASN_Length object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError);

int ASN_Length_DecodePreserveOffset(
                ASN_Length object, 
                ASN_Octets octets, 
                ASN_DecodeError* decodeError);

void ASN_Length_SetLength(ASN_Length object, ITS_LONG length);

ITS_LONG ASN_Length_GetLength(const ASN_Length object);

ITS_BOOLEAN ASN_Length_IsIndefinite(const ASN_Length object);

ITS_BOOLEAN ASN_Length_IsIndefiniteEndMark(
                                const ASN_Length object,
                                const ASN_Octets octets);

void ASN_Length_IndefiniteEndMarkIncOffset(
                                const ASN_Length object,
                                ASN_Octets octets);

char* ASN_Length_ToString(const ASN_Length object);

void ASN_Length_Print(const ASN_Length object);

char* ASN_Length_GetEncodeExtendedErrorText(
                                const ASN_Length object, 
                                ASN_Error error);

char* ASN_Length_GetDecodeExtendedErrorText(
                                const ASN_Length object, 
                                ASN_Error error, 
                                const ASN_Octets octets);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_LENGTH_H_) */
