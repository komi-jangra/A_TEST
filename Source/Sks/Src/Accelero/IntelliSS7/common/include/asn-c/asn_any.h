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
 *  ID: $Id: asn_any.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Any interface.
 */

#if !defined(_C_ASN_ANY_H_)
#define _C_ASN_ANY_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_length.h>
#include <asn_desc_any.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Any already defined in description. */
typedef struct _ASN_Any_ClassRec*        ASN_AnyClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescAny         (*ASN_Any_GetStaticDescriptionProc)();
typedef void                (*ASN_Any_DestructStaticDescriptionProc)();
typedef const ASN_Object    (*ASN_Any_GetAnyProc)(const ASN_Any object);
typedef void                (*ASN_Any_SetAnyProc)(ASN_Any object, ASN_Object any);
typedef ITS_BOOLEAN         (*ASN_Any_ContainsProc)(const ASN_Any object, const ASN_Tag tag);
typedef ITS_BOOLEAN         (*ASN_Any_ContainsAnyProc)(const ASN_Any object);
typedef ITS_BOOLEAN         (*ASN_Any_IsDecodedProc)(const ASN_Any object);
typedef const ASN_Tag       (*ASN_Any_GetDecodedTagProc)(const ASN_Any object);
typedef const ASN_Length    (*ASN_Any_GetDecodedLengthProc)(const ASN_Any object);
typedef const ASN_Octets    (*ASN_Any_GetDecodedOctetsProc)(const ASN_Any object);

/*
 *  Procedure overrides.
 */

#define ASN_ANY_GET_ANY_INHERIT             (ASN_Any_GetAnyProc)NULL              
#define ASN_ANY_SET_ANY_INHERIT             (ASN_Any_SetAnyProc)NULL
#define ASN_ANY_CONTAINS_INHERIT            (ASN_Any_ContainsProc)NULL             
#define ASN_ANY_CONTAINS_ANY_INHERIT        (ASN_Any_ContainsAnyProc)NULL
#define ASN_ANY_IS_DECODED_INHERIT          (ASN_Any_IsDecodedProc)NULL
#define ASN_ANY_GET_DECODED_TAG_INHERIT     (ASN_Any_GetDecodedTagProc)NULL
#define ASN_ANY_GET_DECODED_LENGTH_INHERIT  (ASN_Any_GetDecodedLengthProc)NULL
#define ASN_ANY_GET_DECODED_OCTETS_INHERIT  (ASN_Any_GetDecodedOctetsProc)NULL    


/* ASN_Any class. */

typedef struct
{
    ASN_Any_GetStaticDescriptionProc        getStaticDescription;
    ASN_Any_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_Any_GetAnyProc                      getAny;
    ASN_Any_SetAnyProc                      setAny;
    ASN_Any_ContainsProc                    contains;
    ASN_Any_ContainsAnyProc                 containsAny;
    ASN_Any_IsDecodedProc                   isDecoded;
    ASN_Any_GetDecodedTagProc               getDecodedTag;
    ASN_Any_GetDecodedLengthProc            getDecodedLength;
    ASN_Any_GetDecodedOctetsProc            getDecodedOctets;
} ASN_Any_ClassPart;


typedef struct _ASN_Any_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Any_ClassPart       asnAnyClass;
} ASN_Any_ClassRec;

#define ASN_ANY_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.getStaticDescription)

#define ASN_ANY_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.destructStaticDescription)

#define ASN_ANY_CLASS_GET_ANY(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.getAny)

#define ASN_ANY_CLASS_SET_ANY(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.setAny)

#define ASN_ANY_CLASS_CONTAINS(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.contains)

#define ASN_ANY_CLASS_CONTAINS_ANY(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.containsAny)

#define ASN_ANY_CLASS_IS_DECODED(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.isDecoded)

#define ASN_ANY_CLASS_GET_DECODED_TAG(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.getDecodedTag)

#define ASN_ANY_CLASS_GET_DECODED_LENGTH(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.getDecodedLength)

#define ASN_ANY_CLASS_GET_DECODED_OCTETS(x) \
    (((ASN_AnyClass)(x))->asnAnyClass.getDecodedOctets)


/*
 *  For inheritance.
 */ 

extern ASN_Any_ClassRec itsASN_Any_ClassRec;


/* ASN_Any object. */

typedef struct _ASN_Any_ObjectPart
{
    ASN_Object  any;
    ITS_BOOLEAN decoded;
    ASN_Tag     decodedTag;
    ASN_Length  decodedLength;
    ASN_Octets  decodedOctets;
} ASN_Any_ObjectPart;


typedef struct _ASN_Any_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Any_ObjectPart      asnAny;
} ASN_Any_ObjectRec;

#define ASN_ANY_ANY(x) \
    (((ASN_Any)(x))->asnAny.any)

#define ASN_ANY_DECODED(x) \
    (((ASN_Any)(x))->asnAny.decoded)

#define ASN_ANY_DECODED_TAG(x) \
    (((ASN_Any)(x))->asnAny.decodedTag)

#define ASN_ANY_DECODED_LENGTH(x) \
    (((ASN_Any)(x))->asnAny.decodedLength)

#define ASN_ANY_DECODED_OCTETS(x) \
    (((ASN_Any)(x))->asnAny.decodedOctets)

#define ASN_ANY_CLASS_NAME "ASN_Any"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Any ASN_Any_ConstructDefault();
ASN_Any ASN_Any_ConstructWithDescription(ASN_DescAny description);
void ASN_Any_Destruct(ASN_Any object);
ASN_Any ASN_Any_Clone(const ASN_Any object);
ITS_BOOLEAN ASN_Any_Equals(const ASN_Any object, const ASN_Any other);
ASN_DescAny ASN_Any_GetStaticDescription();
void ASN_Any_DestructStaticDescription();
const ASN_Object ASN_Any_GetAny(const ASN_Any object);
void ASN_Any_SetAny(ASN_Any object, ASN_Object any);
ITS_BOOLEAN ASN_Any_Contains(const ASN_Any object, const ASN_Tag tag);
ITS_BOOLEAN ASN_Any_ContainsAny(const ASN_Any object);
ITS_BOOLEAN ASN_Any_IsDecoded(const ASN_Any object);
const ASN_Tag ASN_Any_GetDecodedTag(const ASN_Any object);
const ASN_Length ASN_Any_GetDecodedLength(const ASN_Any object);
const ASN_Octets ASN_Any_GetDecodedOctets(const ASN_Any object);
int ASN_Any_Encode(ASN_Any object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Any_Decode(ASN_Any object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Any_GetName(const ASN_Any object);
const char* ASN_Any_GetBaseName(const ASN_Any object);
void ASN_Any_Print(const ASN_Any object);
char* ASN_Any_ToString(const ASN_Any object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_ANY_H_) */
