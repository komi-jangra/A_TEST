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
 *  ID: $Id: asn_object_identifier.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_ObjectIdentifier interface.
 */

#if !defined(_C_ASN_OBJECT_IDENTIFIER_H_)
#define _C_ASN_OBJECT_IDENTIFIER_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_object_identifier.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_ObjectIdentifier already defined in description. */
typedef struct _ASN_ObjectIdentifier_ClassRec*       ASN_ObjectIdentifierClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescObjectIdentifier    (*ASN_ObjectIdentifier_GetStaticDescriptionProc)();
typedef void                        (*ASN_ObjectIdentifier_DestructStaticDescriptionProc)();
typedef const ITS_LONG*             (*ASN_ObjectIdentifier_GetArrayProc)(const ASN_ObjectIdentifier object);
typedef int                         (*ASN_ObjectIdentifier_SetArrayProc)(ASN_ObjectIdentifier object, const ITS_LONG* array, size_t size);
typedef size_t                      (*ASN_ObjectIdentifier_GetSizeProc)(const ASN_ObjectIdentifier object);
typedef ASN_Tag                     (*ASN_ObjectIdentifier_GetUniversalTagProc)(const ASN_ObjectIdentifier object);


/*
 *  Procedure overrides.
 */

#define ASN_OBJECT_IDENTIFIER_GET_ARRAY_INHERIT          (ASN_ObjectIdentifier_GetArrayProc)NULL
#define ASN_OBJECT_IDENTIFIER_SET_ARRAY_INHERIT          (ASN_ObjectIdentifier_SetArrayProc)NULL
#define ASN_OBJECT_IDENTIFIER_GET_SIZE_INHERIT           (ASN_ObjectIdentifier_GetSizeProc)NULL
#define ASN_OBJECT_IDENTIFIER_GET_UNIVERSAL_TAG_INHERIT  (ASN_ObjectIdentifier_GetUniversalTagProc)NULL

/* ASN_ObjectIdentifier class. */

typedef struct
{
    ASN_ObjectIdentifier_GetStaticDescriptionProc        getStaticDescription;
    ASN_ObjectIdentifier_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_ObjectIdentifier_GetArrayProc                    getArray;
    ASN_ObjectIdentifier_SetArrayProc                    setArray;
    ASN_ObjectIdentifier_GetSizeProc                     getSize;
    ASN_ObjectIdentifier_GetUniversalTagProc             getUniversalTag; 
} ASN_ObjectIdentifier_ClassPart;


typedef struct _ASN_ObjectIdentifier_ClassRec
{
    ITS_CoreClassPart               coreClass;
    ASN_Object_ClassPart            asnObjectClass;
    ASN_ObjectIdentifier_ClassPart  asnObjectIdentifierClass;
} ASN_ObjectIdentifier_ClassRec;

#define ASN_OBJECT_IDENTIFIER_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_ObjectIdentifierClass)(x))->asnObjectIdentifierClass.getStaticDescription)

#define ASN_OBJECT_IDENTIFIER_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_ObjectIdentifierClass)(x))->asnObjectIdentifierClass.destructStaticDescription)

#define ASN_OBJECT_IDENTIFIER_CLASS_GET_ARRAY(x) \
    (((ASN_ObjectIdentifierClass)(x))->asnObjectIdentifierClass.getArray)

#define ASN_OBJECT_IDENTIFIER_CLASS_SET_ARRAY(x) \
    (((ASN_ObjectIdentifierClass)(x))->asnObjectIdentifierClass.setArray)

#define ASN_OBJECT_IDENTIFIER_CLASS_GET_SIZE(x) \
    (((ASN_ObjectIdentifierClass)(x))->asnObjectIdentifierClass.getSize)

#define ASN_OBJECT_IDENTIFIER_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_ObjectIdentifierClass)(x))->asnObjectIdentifierClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_ObjectIdentifier_ClassRec itsASN_ObjectIdentifier_ClassRec;


/* ASN_ObjectIdentifier object. */

typedef struct _ASN_ObjectIdentifier_ObjectPart
{
    ITS_LONG*   data;
    size_t      size;
} ASN_ObjectIdentifier_ObjectPart;


typedef struct _ASN_ObjectIdentifier_ObjectRec
{
    ITS_CoreObjectPart              core;
    ASN_Object_ObjectPart           asnObject;
    ASN_ObjectIdentifier_ObjectPart asnObjectIdentifier;
} ASN_ObjectIdentifier_ObjectRec;

#define ASN_OBJECT_IDENTIFIER_DATA(x)                  \
    (((ASN_ObjectIdentifier)(x))->asnObjectIdentifier.data)

#define ASN_OBJECT_IDENTIFIER_SIZE(x)                  \
    (((ASN_ObjectIdentifier)(x))->asnObjectIdentifier.size)


#define ASN_OBJECT_IDENTIFIER_CLASS_NAME "ASN_ObjectIdentifier"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_ObjectIdentifier ASN_ObjectIdentifier_ConstructDefault();
ASN_ObjectIdentifier ASN_ObjectIdentifier_ConstructWithArraySize(const ITS_LONG* array, size_t size);
ASN_ObjectIdentifier ASN_ObjectIdentifier_ConstructWithArraySizeDescription(const ITS_LONG* array, size_t size, ASN_DescObjectIdentifier description);
void ASN_ObjectIdentifier_Destruct(ASN_ObjectIdentifier object);
ASN_ObjectIdentifier ASN_ObjectIdentifier_Clone(const ASN_ObjectIdentifier object);
ITS_BOOLEAN ASN_ObjectIdentifier_Equals(const ASN_ObjectIdentifier object, const ASN_ObjectIdentifier other);
ASN_DescObjectIdentifier ASN_ObjectIdentifier_GetStaticDescription();
void ASN_ObjectIdentifier_DestructStaticDescription();
const ITS_LONG* ASN_ObjectIdentifier_GetArray(const ASN_ObjectIdentifier object);
size_t ASN_ObjectIdentifier_GetSize(const ASN_ObjectIdentifier object);
int ASN_ObjectIdentifier_SetArray(ASN_ObjectIdentifier object, const ITS_LONG* array, size_t size);
ASN_Tag ASN_ObjectIdentifier_GetUniversalTag(const ASN_ObjectIdentifier object);
int ASN_ObjectIdentifier_Encode(ASN_ObjectIdentifier object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_ObjectIdentifier_Decode(ASN_ObjectIdentifier object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_ObjectIdentifier_GetName(const ASN_ObjectIdentifier object);
const char* ASN_ObjectIdentifier_GetBaseName(const ASN_ObjectIdentifier object);
void ASN_ObjectIdentifier_Print(const ASN_ObjectIdentifier object);
char* ASN_ObjectIdentifier_ToString(const ASN_ObjectIdentifier object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_OBJECT_IDENTIFIER_H_) */
