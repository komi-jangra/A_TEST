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
 *  ID: $Id: asn_desc_enumerated.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescEnumerated interface.
 */

#if !defined(_C_ASN_DESC_ENUMERATED_H_)
#define _C_ASN_DESC_ENUMERATED_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Enumerated_ObjectRec*      ASN_Enumerated;
typedef struct _ASN_DescEnumerated_ObjectRec*  ASN_DescEnumerated;
typedef struct _ASN_DescEnumerated_ClassRec*   ASN_DescEnumeratedClass;



/*
 *  Procedure signatures.
 */

typedef void        (*ASN_DescEnumerated_AddValueProc)(ASN_DescEnumerated object, size_t index, ITS_LONG value);
typedef ITS_LONG    (*ASN_DescEnumerated_GetValueAtProc)(const ASN_DescEnumerated object, size_t index);
typedef ITS_BOOLEAN (*ASN_DescEnumerated_ContainsProc)(const ASN_DescEnumerated object, ITS_LONG value);
typedef size_t      (*ASN_DescEnumerated_GetSizeProc)(const ASN_DescEnumerated object);
typedef void        (*ASN_DescEnumerated_SetDefaultValueProc)(ASN_DescEnumerated object, ITS_LONG defaultValue);
typedef ITS_LONG    (*ASN_DescEnumerated_GetDefaultValueProc)(const ASN_DescEnumerated object);

/* ASN_DescEnumerated class. */

typedef struct
{
    ASN_DescEnumerated_AddValueProc             addValue;
    ASN_DescEnumerated_GetValueAtProc           getValueAt;
    ASN_DescEnumerated_ContainsProc             contains;
    ASN_DescEnumerated_GetSizeProc              getSize;
    ASN_DescEnumerated_SetDefaultValueProc      setDefaultValue;
    ASN_DescEnumerated_GetDefaultValueProc      getDefaultValue;
} ASN_DescEnumerated_ClassPart;


typedef struct _ASN_DescEnumerated_ClassRec
{
    ITS_CoreClassPart               coreClass;
    ASN_DescObject_ClassPart        asnDescObjectClass;
    ASN_DescEnumerated_ClassPart    asnDescEnumeratedClass;
} ASN_DescEnumerated_ClassRec;

#define ASN_DESC_ENUMERATED_CLASS_ADD_VALUE(x) \
    (((ASN_DescEnumeratedClass)(x))->asnDescEnumeratedClass.addValue)

#define ASN_DESC_ENUMERATED_CLASS_GET_VALUE_AT(x) \
    (((ASN_DescEnumeratedClass)(x))->asnDescEnumeratedClass.getValueAt)

#define ASN_DESC_ENUMERATED_CLASS_CONTAINS(x) \
    (((ASN_DescEnumeratedClass)(x))->asnDescEnumeratedClass.contains)

#define ASN_DESC_ENUMERATED_CLASS_GET_SIZE(x) \
    (((ASN_DescEnumeratedClass)(x))->asnDescEnumeratedClass.getSize)

#define ASN_DESC_ENUMERATED_CLASS_SET_DEFAULT_VALUE(x) \
    (((ASN_DescEnumeratedClass)(x))->asnDescEnumeratedClass.setDefaultValue)

#define ASN_DESC_ENUMERATED_CLASS_GET_DEFAULT_VALUE(x) \
    (((ASN_DescEnumeratedClass)(x))->asnDescEnumeratedClass.getDefaultValue)


/*
 *  For inheritance.
 */ 

extern ASN_DescEnumerated_ClassRec itsASN_DescEnumerated_ClassRec;


/* ASN_DescEnumerated object. */

typedef struct _ASN_DescEnumerated_ObjectPart
{
    ITS_LONG*   values;
    size_t      size;
    ITS_LONG    defaultValue;
} ASN_DescEnumerated_ObjectPart;


typedef struct _ASN_DescEnumerated_ObjectRec
{
    ITS_CoreObjectPart              core;
    ASN_DescObject_ObjectPart       asnDescObject;
    ASN_DescEnumerated_ObjectPart   asnDescEnumerated;
} ASN_DescEnumerated_ObjectRec;

#define ASN_DESC_ENUMERATED_VALUES(x) \
    (((ASN_DescEnumerated)(x))->asnDescEnumerated.values)

#define ASN_DESC_ENUMERATED_SIZE(x) \
    (((ASN_DescEnumerated)(x))->asnDescEnumerated.size)

#define ASN_DESC_ENUMERATED_DEFAULT_VALUE(x) \
    (((ASN_DescEnumerated)(x))->asnDescEnumerated.defaultValue)


#define ASN_DESC_ENUMERATED_CLASS_NAME "ASN_DescEnumerated"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescEnumerated ASN_DescEnumerated_ConstructWithSize(size_t size);
void ASN_DescEnumerated_Destruct(ASN_DescEnumerated object);
ASN_Object ASN_DescEnumerated_Factory(const ASN_DescEnumerated object);
void ASN_DescEnumerated_SetCloneForFactory(ASN_DescEnumerated object, ASN_Enumerated clone);
ASN_Object ASN_DescEnumerated_DefaultFactory(const ASN_DescEnumerated object);
void ASN_DescEnumerated_SetCloneForDefaultFactory(ASN_DescEnumerated object, ASN_Enumerated clone);
ITS_BOOLEAN ASN_DescEnumerated_IsClauseOptional(const ASN_DescEnumerated object);
ITS_BOOLEAN ASN_DescEnumerated_IsClauseDefault(const ASN_DescEnumerated object);
ITS_BOOLEAN ASN_DescEnumerated_IsClauseAnyTag(const ASN_DescEnumerated object);
void ASN_DescEnumerated_SetClauseOptional(ASN_DescEnumerated object);
void ASN_DescEnumerated_SetClauseDefault(ASN_DescEnumerated object);
void ASN_DescEnumerated_SetClauseAnyTag(ASN_DescEnumerated object);
ITS_BOOLEAN ASN_DescEnumerated_TagIdentify(const ASN_DescEnumerated object, const ASN_Tag tag);
const ASN_Tag ASN_DescEnumerated_TagIdentity(const ASN_DescEnumerated object);
void ASN_DescEnumerated_TagAddLevel(ASN_DescEnumerated object, ASN_Tag tag);
size_t ASN_DescEnumerated_TagLevelNumber(const ASN_DescEnumerated object);
ASN_LinkedList ASN_DescEnumerated_TagStack(ASN_DescEnumerated object);
const char* ASN_DescEnumerated_GetName(const ASN_DescEnumerated object);
const char* ASN_DescEnumerated_GetBaseName(const ASN_DescEnumerated object);
void ASN_DescEnumerated_AddValue(ASN_DescEnumerated object, size_t index, ITS_LONG value);
ITS_LONG ASN_DescEnumerated_GetValueAt(const ASN_DescEnumerated object, size_t index);
ITS_BOOLEAN ASN_DescEnumerated_Contains(const ASN_DescEnumerated object, ITS_LONG value);
size_t ASN_DescEnumerated_GetSize(const ASN_DescEnumerated object);
void ASN_DescEnumerated_SetDefaultValue(ASN_DescEnumerated object, ITS_LONG defaultValue);
ITS_LONG ASN_DescEnumerated_GetDefaultValue(const ASN_DescEnumerated object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_ENUMERATED_H_) */


