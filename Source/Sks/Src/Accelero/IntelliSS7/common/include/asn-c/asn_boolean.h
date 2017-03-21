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
 *  ID: $Id: asn_boolean.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Boolean interface.
 */

#if !defined(_C_ASN_BOOLEAN_H_)
#define _C_ASN_BOOLEAN_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_boolean.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Boolean already defined in description. */
typedef struct _ASN_Boolean_ClassRec*       ASN_BooleanClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescBoolean (*ASN_Boolean_GetStaticDescriptionProc)();
typedef void            (*ASN_Boolean_DestructStaticDescriptionProc)();
typedef ITS_BOOLEAN     (*ASN_Boolean_GetValueProc)(const ASN_Boolean object);
typedef void            (*ASN_Boolean_SetValueProc)(ASN_Boolean object, ITS_BOOLEAN value);
typedef ASN_Tag         (*ASN_Boolean_GetUniversalTagProc)(const ASN_Boolean object);


/*
 *  Procedure overrides.
 */

#define ASN_BOOLEAN_GET_VALUE_INHERIT           (ASN_Boolean_GetValueProc)NULL
#define ASN_BOOLEAN_SET_VALUE_INHERIT           (ASN_Boolean_SetValueProc)NULL
#define ASN_BOOLEAN_GET_UNIVERSAL_TAG_INHERIT   (ASN_Boolean_GetUniversalTagProc)NULL

/* ASN_Boolean class. */

typedef struct
{
    ASN_Boolean_GetStaticDescriptionProc        getStaticDescription;
    ASN_Boolean_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_Boolean_GetValueProc                    getValue;
    ASN_Boolean_SetValueProc                    setValue;
    ASN_Boolean_GetUniversalTagProc             getUniversalTag; 
} ASN_Boolean_ClassPart;


typedef struct _ASN_Boolean_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Boolean_ClassPart   asnBooleanClass;
} ASN_Boolean_ClassRec;

#define ASN_BOOLEAN_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_BooleanClass)(x))->asnBooleanClass.getStaticDescription)

#define ASN_BOOLEAN_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_BooleanClass)(x))->asnBooleanClass.destructStaticDescription)

#define ASN_BOOLEAN_CLASS_GET_VALUE(x) \
    (((ASN_BooleanClass)(x))->asnBooleanClass.getValue)

#define ASN_BOOLEAN_CLASS_SET_VALUE(x) \
    (((ASN_BooleanClass)(x))->asnBooleanClass.setValue)

#define ASN_BOOLEAN_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_BooleanClass)(x))->asnBooleanClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_Boolean_ClassRec itsASN_Boolean_ClassRec;


/* ASN_Boolean object. */

typedef struct _ASN_Boolean_ObjectPart
{
    ITS_BOOLEAN value;
} ASN_Boolean_ObjectPart;


typedef struct _ASN_Boolean_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Boolean_ObjectPart  asnBoolean;
} ASN_Boolean_ObjectRec;

#define ASN_BOOLEAN_VALUE(x) \
    (((ASN_Boolean)(x))->asnBoolean.value)

#define ASN_BOOLEAN_CLASS_NAME "ASN_Boolean"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Boolean ASN_Boolean_ConstructDefault();
ASN_Boolean ASN_Boolean_ConstructWithValue(ITS_BOOLEAN value);
ASN_Boolean ASN_Boolean_ConstructWithValueDescription(ITS_BOOLEAN value, ASN_DescBoolean description);
void ASN_Boolean_Destruct(ASN_Boolean object);
ASN_Boolean ASN_Boolean_Clone(const ASN_Boolean object);
ITS_BOOLEAN ASN_Boolean_Equals(const ASN_Boolean object, const ASN_Boolean other);
ASN_DescBoolean ASN_Boolean_GetStaticDescription();
void ASN_Boolean_DestructStaticDescription();
ITS_BOOLEAN ASN_Boolean_GetValue(const ASN_Boolean object);
void ASN_Boolean_SetValue(ASN_Boolean object, ITS_BOOLEAN value);
ASN_Tag ASN_Boolean_GetUniversalTag(const ASN_Boolean object);
int ASN_Boolean_Encode(ASN_Boolean object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Boolean_Decode(ASN_Boolean object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Boolean_GetName(const ASN_Boolean object);
const char* ASN_Boolean_GetBaseName(const ASN_Boolean object);
void ASN_Boolean_Print(const ASN_Boolean object);
char* ASN_Boolean_ToString(const ASN_Boolean object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_BOOLEAN_H_) */
