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
 *  ID: $Id: asn_integer.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Integer interface.
 */

#if !defined(_C_ASN_INTEGER_H_)
#define _C_ASN_INTEGER_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_integer.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Integer already defined in description. */
typedef struct _ASN_Integer_ClassRec*       ASN_IntegerClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescInteger (*ASN_Integer_GetStaticDescriptionProc)();
typedef void            (*ASN_Integer_DestructStaticDescriptionProc)();
typedef ITS_LONG        (*ASN_Integer_GetValueProc)(const ASN_Integer object);
typedef void            (*ASN_Integer_SetValueProc)(ASN_Integer object, ITS_LONG value);
typedef ASN_Tag         (*ASN_Integer_GetUniversalTagProc)(const ASN_Integer object);


/*
 *  Procedure overrides.
 */

#define ASN_INTEGER_GET_VALUE_INHERIT           (ASN_Integer_GetValueProc)NULL
#define ASN_INTEGER_SET_VALUE_INHERIT           (ASN_Integer_SetValueProc)NULL
#define ASN_INTEGER_GET_UNIVERSAL_TAG_INHERIT   (ASN_Integer_GetUniversalTagProc)NULL

/* ASN_Integer class. */

typedef struct
{
    ASN_Integer_GetStaticDescriptionProc        getStaticDescription;
    ASN_Integer_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_Integer_GetValueProc                    getValue;
    ASN_Integer_SetValueProc                    setValue;
    ASN_Integer_GetUniversalTagProc             getUniversalTag; 
} ASN_Integer_ClassPart;


typedef struct _ASN_Integer_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Integer_ClassPart   asnIntegerClass;
} ASN_Integer_ClassRec;

#define ASN_INTEGER_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_IntegerClass)(x))->asnIntegerClass.getStaticDescription)

#define ASN_INTEGER_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_IntegerClass)(x))->asnIntegerClass.destructStaticDescription)

#define ASN_INTEGER_CLASS_GET_VALUE(x) \
    (((ASN_IntegerClass)(x))->asnIntegerClass.getValue)

#define ASN_INTEGER_CLASS_SET_VALUE(x) \
    (((ASN_IntegerClass)(x))->asnIntegerClass.setValue)

#define ASN_INTEGER_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_IntegerClass)(x))->asnIntegerClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_Integer_ClassRec itsASN_Integer_ClassRec;


/* ASN_Integer object. */

typedef struct _ASN_Integer_ObjectPart
{
    ITS_LONG value;
} ASN_Integer_ObjectPart;


typedef struct _ASN_Integer_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Integer_ObjectPart  asnInteger;
} ASN_Integer_ObjectRec;

#define ASN_INTEGER_VALUE(x) \
    (((ASN_Integer)(x))->asnInteger.value)

#define ASN_INTEGER_CLASS_NAME "ASN_Integer"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Integer ASN_Integer_ConstructDefault();
ASN_Integer ASN_Integer_ConstructWithValue(ITS_LONG value);
ASN_Integer ASN_Integer_ConstructWithValueDescription(ITS_LONG value, ASN_DescInteger description);
void ASN_Integer_Destruct(ASN_Integer object);
ASN_Integer ASN_Integer_Clone(const ASN_Integer object);
ITS_BOOLEAN ASN_Integer_Equals(const ASN_Integer object, const ASN_Integer other);
ASN_DescInteger ASN_Integer_GetStaticDescription();
void ASN_Integer_DestructStaticDescription();
ITS_LONG ASN_Integer_GetValue(const ASN_Integer object);
void ASN_Integer_SetValue(ASN_Integer object, ITS_LONG value);
ASN_Tag ASN_Integer_GetUniversalTag(const ASN_Integer object);
int ASN_Integer_Encode(ASN_Integer object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Integer_Decode(ASN_Integer object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Integer_GetName(const ASN_Integer object);
const char* ASN_Integer_GetBaseName(const ASN_Integer object);
void ASN_Integer_Print(const ASN_Integer object);
char* ASN_Integer_ToString(const ASN_Integer object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_INTEGER_H_) */
