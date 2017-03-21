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
 *  ID: $Id: asn_enumerated.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Enumerated interface.
 */

#if !defined(_C_ASN_ENUMERATED_H_)
#define _C_ASN_ENUMERATED_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_enumerated.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Enumerated already defined in description. */
typedef struct _ASN_Enumerated_ClassRec*       ASN_EnumeratedClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescEnumerated  (*ASN_Enumerated_GetStaticDescriptionProc)();
typedef void                (*ASN_Enumerated_DestructStaticDescriptionProc)();
typedef ITS_LONG            (*ASN_Enumerated_GetValueProc)(const ASN_Enumerated object);
typedef void                (*ASN_Enumerated_SetValueProc)(ASN_Enumerated object, ITS_LONG value);
typedef ITS_LONG            (*ASN_Enumerated_GetValueFromValueNameProc)(const ASN_Enumerated object, const char* valueName);
typedef const char*         (*ASN_Enumerated_GetValueNameFromValueProc)(const ASN_Enumerated object, ITS_LONG value);
typedef ASN_Tag             (*ASN_Enumerated_GetUniversalTagProc)(const ASN_Enumerated object);


/*
 *  Procedure overrides.
 */

#define ASN_ENUMERATED_GET_VALUE_INHERIT           (ASN_Enumerated_GetValueProc)NULL
#define ASN_ENUMERATED_SET_VALUE_INHERIT           (ASN_Enumerated_SetValueProc)NULL
#define ASN_ENUMERATED_GET_UNIVERSAL_TAG_INHERIT   (ASN_Enumerated_GetUniversalTagProc)NULL

/* ASN_Enumerated class. */

typedef struct
{
    ASN_Enumerated_GetStaticDescriptionProc        getStaticDescription;
    ASN_Enumerated_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_Enumerated_GetValueProc                    getValue;
    ASN_Enumerated_SetValueProc                    setValue;
    ASN_Enumerated_GetValueFromValueNameProc       getValueFromValueName;
    ASN_Enumerated_GetValueNameFromValueProc       getValueNameFromValue;
    ASN_Enumerated_GetUniversalTagProc             getUniversalTag; 
} ASN_Enumerated_ClassPart;


typedef struct _ASN_Enumerated_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_Object_ClassPart        asnObjectClass;
    ASN_Enumerated_ClassPart    asnEnumeratedClass;
} ASN_Enumerated_ClassRec;

#define ASN_ENUMERATED_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.getStaticDescription)

#define ASN_ENUMERATED_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.destructStaticDescription)

#define ASN_ENUMERATED_CLASS_GET_VALUE(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.getValue)

#define ASN_ENUMERATED_CLASS_SET_VALUE(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.setValue)

#define ASN_ENUMERATED_CLASS_GET_VALUE_FROM_VALUE_NAME(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.getValueFromValueName)

#define ASN_ENUMERATED_CLASS_GET_VALUE_NAME_FROM_VALUE(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.getValueNameFromValue)

#define ASN_ENUMERATED_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_EnumeratedClass)(x))->asnEnumeratedClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_Enumerated_ClassRec itsASN_Enumerated_ClassRec;


/* ASN_Enumerated object. */

typedef struct _ASN_Enumerated_ObjectPart
{
    ITS_LONG value;
} ASN_Enumerated_ObjectPart;


typedef struct _ASN_Enumerated_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_Object_ObjectPart       asnObject;
    ASN_Enumerated_ObjectPart   asnEnumerated;
} ASN_Enumerated_ObjectRec;

#define ASN_ENUMERATED_VALUE(x) \
    (((ASN_Enumerated)(x))->asnEnumerated.value)

#define ASN_ENUMERATED_CLASS_NAME "ASN_Enumerated"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Enumerated ASN_Enumerated_ConstructDefault();
ASN_Enumerated ASN_Enumerated_ConstructWithValue(ITS_LONG value);
ASN_Enumerated ASN_Enumerated_ConstructWithValueDescription(ITS_LONG value, ASN_DescEnumerated description);
void ASN_Enumerated_Destruct(ASN_Enumerated object);
ASN_Enumerated ASN_Enumerated_Clone(const ASN_Enumerated object);
ITS_BOOLEAN ASN_Enumerated_Equals(const ASN_Enumerated object, const ASN_Enumerated other);
ASN_DescEnumerated ASN_Enumerated_GetStaticDescription();
void ASN_Enumerated_DestructStaticDescription();
ITS_LONG ASN_Enumerated_GetValue(const ASN_Enumerated object);
void ASN_Enumerated_SetValue(ASN_Enumerated object, ITS_LONG value);
ITS_LONG ASN_Enumerated_GetValueFromValueName(const ASN_Enumerated object, const char* valueName);
const char* ASN_Enumerated_GetValueNameFromValue(const ASN_Enumerated object, ITS_LONG value);
ASN_Tag ASN_Enumerated_GetUniversalTag(const ASN_Enumerated object);
int ASN_Enumerated_Encode(ASN_Enumerated object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Enumerated_Decode(ASN_Enumerated object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Enumerated_GetName(const ASN_Enumerated object);
const char* ASN_Enumerated_GetBaseName(const ASN_Enumerated object);
void ASN_Enumerated_Print(const ASN_Enumerated object);
char* ASN_Enumerated_ToString(const ASN_Enumerated object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_ENUMERATED_H_) */
