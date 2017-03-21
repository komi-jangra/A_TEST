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
 *  ID: $Id: asn_octet_string.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_OctetString interface.
 */

#if !defined(_C_ASN_OCTET_STRING_H_)
#define _C_ASN_OCTET_STRING_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_octet_string.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_OctetString already defined in description. */
typedef struct _ASN_OctetString_ClassRec*       ASN_OctetStringClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescOctetString (*ASN_OctetString_GetStaticDescriptionProc)();
typedef void                (*ASN_OctetString_DestructStaticDescriptionProc)();
typedef const ITS_OCTET*    (*ASN_OctetString_GetArrayProc)(const ASN_OctetString object);
typedef int                 (*ASN_OctetString_SetArrayProc)(ASN_OctetString object, const ITS_OCTET* array, size_t size);
typedef size_t              (*ASN_OctetString_GetSizeProc)(const ASN_OctetString object);
typedef ASN_Tag             (*ASN_OctetString_GetUniversalTagProc)(const ASN_OctetString object);


/*
 *  Procedure overrides.
 */

#define ASN_OCTET_STRING_GET_ARRAY_INHERIT          (ASN_OctetString_GetArrayProc)NULL
#define ASN_OCTET_STRING_SET_ARRAY_INHERIT          (ASN_OctetString_SetArrayProc)NULL
#define ASN_OCTET_STRING_GET_SIZE_INHERIT           (ASN_OctetString_GetSizeProc)NULL
#define ASN_OCTET_STRING_GET_UNIVERSAL_TAG_INHERIT  (ASN_OctetString_GetUniversalTagProc)NULL

/* ASN_OctetString class. */

typedef struct
{
    ASN_OctetString_GetStaticDescriptionProc        getStaticDescription;
    ASN_OctetString_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_OctetString_GetArrayProc                    getArray;
    ASN_OctetString_SetArrayProc                    setArray;
    ASN_OctetString_GetSizeProc                     getSize;
    ASN_OctetString_GetUniversalTagProc             getUniversalTag; 
} ASN_OctetString_ClassPart;


typedef struct _ASN_OctetString_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_Object_ClassPart        asnObjectClass;
    ASN_OctetString_ClassPart   asnOctetStringClass;
} ASN_OctetString_ClassRec;

#define ASN_OCTET_STRING_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_OctetStringClass)(x))->asnOctetStringClass.getStaticDescription)

#define ASN_OCTET_STRING_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_OctetStringClass)(x))->asnOctetStringClass.destructStaticDescription)

#define ASN_OCTET_STRING_CLASS_GET_ARRAY(x) \
    (((ASN_OctetStringClass)(x))->asnOctetStringClass.getArray)

#define ASN_OCTET_STRING_CLASS_SET_ARRAY(x) \
    (((ASN_OctetStringClass)(x))->asnOctetStringClass.setArray)

#define ASN_OCTET_STRING_CLASS_GET_SIZE(x) \
    (((ASN_OctetStringClass)(x))->asnOctetStringClass.getSize)

#define ASN_OCTET_STRING_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_OctetStringClass)(x))->asnOctetStringClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_OctetString_ClassRec itsASN_OctetString_ClassRec;


/* ASN_OctetString object. */

typedef struct _ASN_OctetString_ObjectPart
{
    ITS_OCTET*  data;
    size_t      size;
} ASN_OctetString_ObjectPart;


typedef struct _ASN_OctetString_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_Object_ObjectPart       asnObject;
    ASN_OctetString_ObjectPart  asnOctetString;
} ASN_OctetString_ObjectRec;

#define ASN_OCTET_STRING_DATA(x)                  \
    (((ASN_OctetString)(x))->asnOctetString.data)

#define ASN_OCTET_STRING_SIZE(x)                  \
    (((ASN_OctetString)(x))->asnOctetString.size)


#define ASN_OCTET_STRING_CLASS_NAME "ASN_OctetString"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_OctetString ASN_OctetString_ConstructDefault();
ASN_OctetString ASN_OctetString_ConstructWithArraySize(const ITS_OCTET* array, size_t size);
ASN_OctetString ASN_OctetString_ConstructWithArraySizeDescription(const ITS_OCTET* array, size_t size, ASN_DescOctetString description);
void ASN_OctetString_Destruct(ASN_OctetString object);
ASN_OctetString ASN_OctetString_Clone(const ASN_OctetString object);
ITS_BOOLEAN ASN_OctetString_Equals(const ASN_OctetString object, const ASN_OctetString other);
ASN_DescOctetString ASN_OctetString_GetStaticDescription();
void ASN_OctetString_DestructStaticDescription();
const ITS_OCTET* ASN_OctetString_GetArray(const ASN_OctetString object);
size_t ASN_OctetString_GetSize(const ASN_OctetString object);
int ASN_OctetString_SetArray(ASN_OctetString object, const ITS_OCTET* array, size_t size);
ASN_Tag ASN_OctetString_GetUniversalTag(const ASN_OctetString object);
int ASN_OctetString_Encode(ASN_OctetString object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_OctetString_Decode(ASN_OctetString object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_OctetString_GetName(const ASN_OctetString object);
const char* ASN_OctetString_GetBaseName(const ASN_OctetString object);
void ASN_OctetString_Print(const ASN_OctetString object);
char* ASN_OctetString_ToString(const ASN_OctetString object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_OCTET_STRING_H_) */
