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
 *  ID: $Id: asn_desc_set.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescSet interface.
 */

#if !defined(_C_ASN_DESC_SET_H_)
#define _C_ASN_DESC_SET_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Set_ObjectRec*      ASN_Set;
typedef struct _ASN_DescSet_ObjectRec*  ASN_DescSet;
typedef struct _ASN_DescSet_ClassRec*   ASN_DescSetClass;



/*
 *  Procedure signatures.
 */

typedef const ASN_DescObject*   (*ASN_DescSet_GetElementsProc)(const ASN_DescSet object);
typedef void                    (*ASN_DescSet_AddElementProc)(ASN_DescSet object, size_t index, ASN_DescObject element);
typedef const ASN_DescObject    (*ASN_DescSet_GetElementAtProc)(const ASN_DescSet object, size_t index);
typedef const ASN_DescObject    (*ASN_DescSet_GetElementAtTagProc)(const ASN_DescSet object, const ASN_Tag tag);
typedef ITS_BOOLEAN             (*ASN_DescSet_ContainsProc)(const ASN_DescSet object, size_t index);
typedef ITS_BOOLEAN             (*ASN_DescSet_ContainsTagProc)(const ASN_DescSet object, const ASN_Tag tag);
typedef size_t                  (*ASN_DescSet_GetSizeProc)(const ASN_DescSet object);



/* ASN_DescSet class. */

typedef struct
{
    ASN_DescSet_GetElementsProc        getElements;
    ASN_DescSet_AddElementProc         addElement;
    ASN_DescSet_GetElementAtProc       getElementAt;
    ASN_DescSet_GetElementAtTagProc    getElementAtTag;
    ASN_DescSet_ContainsProc           contains;
    ASN_DescSet_ContainsTagProc        containsTag;
    ASN_DescSet_GetSizeProc            getSize;
} ASN_DescSet_ClassPart;


typedef struct _ASN_DescSet_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescSet_ClassPart       asnDescSetClass;
} ASN_DescSet_ClassRec;

#define ASN_DESC_SET_CLASS_GET_ELEMENTS(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.getElements)

#define ASN_DESC_SET_CLASS_ADD_ELEMENT(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.addElement)

#define ASN_DESC_SET_CLASS_GET_ELEMENT_AT(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.getElementAt)

#define ASN_DESC_SET_CLASS_GET_ELEMENT_AT_TAG(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.getElementAtTag)

#define ASN_DESC_SET_CLASS_CONTAINS(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.contains)

#define ASN_DESC_SET_CLASS_CONTAINS_TAG(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.containsTag)

#define ASN_DESC_SET_CLASS_GET_SIZE(x) \
    (((ASN_DescSetClass)(x))->asnDescSetClass.getSize)


/*
 *  For inheritance.
 */ 

extern ASN_DescSet_ClassRec itsASN_DescSet_ClassRec;


/* ASN_DescSet object. */

typedef struct _ASN_DescSet_ObjectPart
{
    ASN_DescObject* elements;
    size_t          size;
} ASN_DescSet_ObjectPart;


typedef struct _ASN_DescSet_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescSet_ObjectPart      asnDescSet;
} ASN_DescSet_ObjectRec;

#define ASN_DESC_SET_ELEMENTS(x) \
    (((ASN_DescSet)(x))->asnDescSet.elements)

#define ASN_DESC_SET_SIZE(x) \
    (((ASN_DescSet)(x))->asnDescSet.size)

#define ASN_DESC_SET_CLASS_NAME "ASN_DescSet"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescSet ASN_DescSet_ConstructWithSize(size_t size);
void ASN_DescSet_Destruct(ASN_DescSet object);
ASN_Object ASN_DescSet_Factory(const ASN_DescSet object);
void ASN_DescSet_SetCloneForFactory(ASN_DescSet object, ASN_Set clone);
ASN_Object ASN_DescSet_DefaultFactory(const ASN_DescSet object);
void ASN_DescSet_SetCloneForDefaultFactory(ASN_DescSet object, ASN_Set clone);
ITS_BOOLEAN ASN_DescSet_IsClauseOptional(const ASN_DescSet object);
ITS_BOOLEAN ASN_DescSet_IsClauseDefault(const ASN_DescSet object);
ITS_BOOLEAN ASN_DescSet_IsClauseAnyTag(const ASN_DescSet object);
void ASN_DescSet_SetClauseOptional(ASN_DescSet object);
void ASN_DescSet_SetClauseDefault(ASN_DescSet object);
void ASN_DescSet_SetClauseAnyTag(ASN_DescSet object);
ITS_BOOLEAN ASN_DescSet_TagIdentify(const ASN_DescSet object, const ASN_Tag tag);
const ASN_Tag ASN_DescSet_TagIdentity(const ASN_DescSet object);
void ASN_DescSet_TagAddLevel(ASN_DescSet object, ASN_Tag tag);
size_t ASN_DescSet_TagLevelNumber(const ASN_DescSet object);
ASN_LinkedList ASN_DescSet_TagStack(ASN_DescSet object);
const char* ASN_DescSet_GetName(const ASN_DescSet object);
const char* ASN_DescSet_GetBaseName(const ASN_DescSet object);
const ASN_DescObject* ASN_DescSet_GetElements(const ASN_DescSet object);
void ASN_DescSet_AddElement(ASN_DescSet object, size_t index, ASN_DescObject element);
const ASN_DescObject ASN_DescSet_GetElementAt(const ASN_DescSet object, size_t index);
const ASN_DescObject ASN_DescSet_GetElementAtTag(const ASN_DescSet object, const ASN_Tag tag);
ITS_BOOLEAN ASN_DescSet_Contains(const ASN_DescSet object, size_t index);
ITS_BOOLEAN ASN_DescSet_ContainsTag(const ASN_DescSet object, const ASN_Tag tag);
size_t ASN_DescSet_GetSize(const ASN_DescSet object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_SET_H_) */


