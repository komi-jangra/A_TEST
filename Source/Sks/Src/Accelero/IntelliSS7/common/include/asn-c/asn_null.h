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
 *  ID: $Id: asn_null.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Null interface.
 */

#if !defined(_C_ASN_NULL_H_)
#define _C_ASN_NULL_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_null.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Null already defined in description. */
typedef struct _ASN_Null_ClassRec*       ASN_NullClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescNull    (*ASN_Null_GetStaticDescriptionProc)();
typedef void            (*ASN_Null_DestructStaticDescriptionProc)();
typedef ASN_Tag         (*ASN_Null_GetUniversalTagProc)(const ASN_Null object);


/*
 *  Procedure overrides.
 */

#define ASN_NULL_GET_UNIVERSAL_TAG_INHERIT   (ASN_Null_GetUniversalTagProc)NULL

/* ASN_Null class. */

typedef struct
{
    ASN_Null_GetStaticDescriptionProc        getStaticDescription;
    ASN_Null_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_Null_GetUniversalTagProc             getUniversalTag; 
} ASN_Null_ClassPart;


typedef struct _ASN_Null_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Null_ClassPart      asnNullClass;
} ASN_Null_ClassRec;

#define ASN_NULL_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_NullClass)(x))->asnNullClass.getStaticDescription)

#define ASN_NULL_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_NullClass)(x))->asnNullClass.destructStaticDescription)

#define ASN_NULL_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_NullClass)(x))->asnNullClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_Null_ClassRec itsASN_Null_ClassRec;


/* ASN_Null object. */

/*
 *  Dummy ASN_Null_ObjectPart.
 */

typedef struct _ASN_Null_ObjectPart
{
    int dummy;
} ASN_Null_ObjectPart;


typedef struct _ASN_Null_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Null_ObjectPart     asnNull;
} ASN_Null_ObjectRec;

#define ASN_NULL_VALUE(x) \
    (((ASN_Null)(x))->asnNull.value)

#define ASN_NULL_CLASS_NAME "ASN_Null"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Null ASN_Null_ConstructDefault();
ASN_Null ASN_Null_ConstructWithDescription(ASN_DescNull description);
void ASN_Null_Destruct(ASN_Null object);
ASN_Null ASN_Null_Clone(const ASN_Null object);
ITS_BOOLEAN ASN_Null_Equals(const ASN_Null object, const ASN_Null other);
ASN_DescNull ASN_Null_GetStaticDescription();
void ASN_Null_DestructStaticDescription();
ASN_Tag ASN_Null_GetUniversalTag(const ASN_Null object);
int ASN_Null_Encode(ASN_Null object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Null_Decode(ASN_Null object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Null_GetName(const ASN_Null object);
const char* ASN_Null_GetBaseName(const ASN_Null object);
void ASN_Null_Print(const ASN_Null object);
char* ASN_Null_ToString(const ASN_Null object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_NULL_H_) */
