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
 *  ID: $Id: asn_bit_string.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_BitString interface.
 */

#if !defined(_C_ASN_BIT_STRING_H_)
#define _C_ASN_BIT_STRING_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_bit_string.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_BitString already defined in description. */
typedef struct _ASN_BitString_ClassRec*       ASN_BitStringClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescBitString   (*ASN_BitString_GetStaticDescriptionProc)();
typedef void                (*ASN_BitString_DestructStaticDescriptionProc)();
typedef const ITS_BOOLEAN*  (*ASN_BitString_GetArrayProc)(const ASN_BitString object);
typedef int                 (*ASN_BitString_SetArrayProc)(ASN_BitString object, const ITS_BOOLEAN* array, size_t size);
typedef size_t              (*ASN_BitString_GetSizeProc)(const ASN_BitString object);
typedef void                (*ASN_BitString_SetProc)(ASN_BitString object, size_t index, ITS_BOOLEAN value);
typedef void                (*ASN_BitString_ResetProc)(ASN_BitString object, size_t index);
typedef ITS_BOOLEAN         (*ASN_BitString_IsSetProc)(const ASN_BitString object, size_t index);
typedef ITS_BOOLEAN         (*ASN_BitString_IsDefinedProc)(const ASN_BitString object, size_t index);
typedef void                (*ASN_BitString_SetAllProc)(ASN_BitString object);
typedef void                (*ASN_BitString_ResetAllProc)(ASN_BitString object);
typedef ASN_Tag             (*ASN_BitString_GetUniversalTagProc)(const ASN_BitString object);


/*
 *  Procedure overrides.
 */

#define ASN_BIT_STRING_GET_ARRAY_INHERIT          (ASN_BitString_GetArrayProc)NULL
#define ASN_BIT_STRING_SET_ARRAY_INHERIT          (ASN_BitString_SetArrayProc)NULL
#define ASN_BIT_STRING_GET_SIZE_INHERIT           (ASN_BitString_GetSizeProc)NULL
#define ASN_BIT_STRING_SET_INHERIT                (ASN_BitString_SetProc)NULL
#define ASN_BIT_STRING_RESET_INHERIT              (ASN_BitString_ResetProc)NULL
#define ASN_BIT_STRING_IS_SET_INHERIT             (ASN_BitString_IsSetProc)NULL
#define ASN_BIT_STRING_IS_DEFINED_INHERIT         (ASN_BitString_IsDefinedProc)NULL
#define ASN_BIT_STRING_SET_ALL_INHERIT            (ASN_BitString_SetAllProc)NULL
#define ASN_BIT_STRING_RESET_ALL_INHERIT          (ASN_BitString_ResetAllProc)NULL
#define ASN_BIT_STRING_GET_UNIVERSAL_TAG_INHERIT  (ASN_BitString_GetUniversalTagProc)NULL

/* ASN_BitString class. */

typedef struct
{
    ASN_BitString_GetStaticDescriptionProc      getStaticDescription;
    ASN_BitString_DestructStaticDescriptionProc destructStaticDescription;
    ASN_BitString_GetArrayProc                  getArray;
    ASN_BitString_SetArrayProc                  setArray;
    ASN_BitString_GetSizeProc                   getSize;
    ASN_BitString_SetProc                       set;
    ASN_BitString_ResetProc                     reset;
    ASN_BitString_IsSetProc                     isSet;
    ASN_BitString_IsDefinedProc                 isDefined;
    ASN_BitString_SetAllProc                    setAll;
    ASN_BitString_ResetAllProc                  resetAll;
    ASN_BitString_GetUniversalTagProc           getUniversalTag; 
} ASN_BitString_ClassPart;


typedef struct _ASN_BitString_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_BitString_ClassPart asnBitStringClass;
} ASN_BitString_ClassRec;

#define ASN_BIT_STRING_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.getStaticDescription)

#define ASN_BIT_STRING_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.destructStaticDescription)

#define ASN_BIT_STRING_CLASS_GET_ARRAY(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.getArray)

#define ASN_BIT_STRING_CLASS_SET_ARRAY(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.setArray)

#define ASN_BIT_STRING_CLASS_GET_SIZE(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.getSize)

#define ASN_BIT_STRING_CLASS_SET(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.set)

#define ASN_BIT_STRING_CLASS_RESET(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.reset)

#define ASN_BIT_STRING_CLASS_IS_SET(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.isSet)

#define ASN_BIT_STRING_CLASS_IS_DEFINED(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.isDefined)

#define ASN_BIT_STRING_CLASS_SET_ALL(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.setAll)

#define ASN_BIT_STRING_CLASS_RESET_ALL(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.resetAll)

#define ASN_BIT_STRING_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_BitStringClass)(x))->asnBitStringClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_BitString_ClassRec itsASN_BitString_ClassRec;


/* ASN_BitString object. */

typedef struct _ASN_BitString_ObjectPart
{
    ITS_BOOLEAN*    data;
    size_t          size;
} ASN_BitString_ObjectPart;


typedef struct _ASN_BitString_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_Object_ObjectPart       asnObject;
    ASN_BitString_ObjectPart    asnBitString;
} ASN_BitString_ObjectRec;

#define ASN_BIT_STRING_DATA(x)                  \
    (((ASN_BitString)(x))->asnBitString.data)

#define ASN_BIT_STRING_SIZE(x)                  \
    (((ASN_BitString)(x))->asnBitString.size)


#define ASN_BIT_STRING_CLASS_NAME "ASN_BitString"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_BitString ASN_BitString_ConstructDefault();
ASN_BitString ASN_BitString_ConstructWithArraySize(const ITS_BOOLEAN* array, size_t size);
ASN_BitString ASN_BitString_ConstructWithArraySizeDescription(const ITS_BOOLEAN* array, size_t size, ASN_DescBitString description);
void ASN_BitString_Destruct(ASN_BitString object);
ASN_BitString ASN_BitString_Clone(const ASN_BitString object);
ITS_BOOLEAN ASN_BitString_Equals(const ASN_BitString object, const ASN_BitString other);
ASN_DescBitString ASN_BitString_GetStaticDescription();
void ASN_BitString_DestructStaticDescription();
const ITS_BOOLEAN* ASN_BitString_GetArray(const ASN_BitString object);
size_t ASN_BitString_GetSize(const ASN_BitString object);
int ASN_BitString_SetArray(ASN_BitString object, const ITS_BOOLEAN* array, size_t size);
void ASN_BitString_Set(ASN_BitString object, size_t index, ITS_BOOLEAN value);
void ASN_BitString_Reset(ASN_BitString object, size_t index);
ITS_BOOLEAN ASN_BitString_IsSet(const ASN_BitString object, size_t index);
ITS_BOOLEAN ASN_BitString_IsDefined(const ASN_BitString object, size_t index);
void ASN_BitString_SetAll(ASN_BitString object);
void ASN_BitString_ResetAll(ASN_BitString object);
ASN_Tag ASN_BitString_GetUniversalTag(const ASN_BitString object);
int ASN_BitString_Encode(ASN_BitString object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_BitString_Decode(ASN_BitString object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_BitString_GetName(const ASN_BitString object);
const char* ASN_BitString_GetBaseName(const ASN_BitString object);
void ASN_BitString_Print(const ASN_BitString object);
char* ASN_BitString_ToString(const ASN_BitString object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_BIT_STRING_H_) */
