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
 *  ID: $Id: asn_desc_sequence.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescSequence interface.
 */

#if !defined(_C_ASN_DESC_SEQUENCE_H_)
#define _C_ASN_DESC_SEQUENCE_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Sequence_ObjectRec*      ASN_Sequence;
typedef struct _ASN_DescSequence_ObjectRec*  ASN_DescSequence;
typedef struct _ASN_DescSequence_ClassRec*   ASN_DescSequenceClass;



/*
 *  Procedure signatures.
 */

typedef const ASN_DescObject*   (*ASN_DescSequence_GetElementsProc)(const ASN_DescSequence object);
typedef void                    (*ASN_DescSequence_AddElementProc)(ASN_DescSequence object, size_t index, ASN_DescObject element);
typedef const ASN_DescObject    (*ASN_DescSequence_GetElementAtProc)(const ASN_DescSequence object, size_t index);
typedef const ASN_DescObject    (*ASN_DescSequence_GetElementAtTagProc)(const ASN_DescSequence object, const ASN_Tag tag);
typedef ITS_BOOLEAN             (*ASN_DescSequence_ContainsProc)(const ASN_DescSequence object, size_t index);
typedef ITS_BOOLEAN             (*ASN_DescSequence_ContainsTagProc)(const ASN_DescSequence object, const ASN_Tag tag);
typedef size_t                  (*ASN_DescSequence_GetSizeProc)(const ASN_DescSequence object);



/* ASN_DescSequence class. */

typedef struct
{
    ASN_DescSequence_GetElementsProc        getElements;
    ASN_DescSequence_AddElementProc         addElement;
    ASN_DescSequence_GetElementAtProc       getElementAt;
    ASN_DescSequence_GetElementAtTagProc    getElementAtTag;
    ASN_DescSequence_ContainsProc           contains;
    ASN_DescSequence_ContainsTagProc        containsTag;
    ASN_DescSequence_GetSizeProc            getSize;
} ASN_DescSequence_ClassPart;


typedef struct _ASN_DescSequence_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescSequence_ClassPart  asnDescSequenceClass;
} ASN_DescSequence_ClassRec;

#define ASN_DESC_SEQUENCE_CLASS_GET_ELEMENTS(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.getElements)

#define ASN_DESC_SEQUENCE_CLASS_ADD_ELEMENT(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.addElement)

#define ASN_DESC_SEQUENCE_CLASS_GET_ELEMENT_AT(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.getElementAt)

#define ASN_DESC_SEQUENCE_CLASS_GET_ELEMENT_AT_TAG(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.getElementAtTag)

#define ASN_DESC_SEQUENCE_CLASS_CONTAINS(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.contains)

#define ASN_DESC_SEQUENCE_CLASS_CONTAINS_TAG(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.containsTag)

#define ASN_DESC_SEQUENCE_CLASS_GET_SIZE(x) \
    (((ASN_DescSequenceClass)(x))->asnDescSequenceClass.getSize)


/*
 *  For inheritance.
 */ 

extern ASN_DescSequence_ClassRec itsASN_DescSequence_ClassRec;


/* ASN_DescSequence object. */

typedef struct _ASN_DescSequence_ObjectPart
{
    ASN_DescObject* elements;
    size_t          size;
} ASN_DescSequence_ObjectPart;


typedef struct _ASN_DescSequence_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescSequence_ObjectPart asnDescSequence;
} ASN_DescSequence_ObjectRec;

#define ASN_DESC_SEQUENCE_ELEMENTS(x) \
    (((ASN_DescSequence)(x))->asnDescSequence.elements)

#define ASN_DESC_SEQUENCE_SIZE(x) \
    (((ASN_DescSequence)(x))->asnDescSequence.size)

#define ASN_DESC_SEQUENCE_CLASS_NAME "ASN_DescSequence"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescSequence ASN_DescSequence_ConstructWithSize(size_t size);
void ASN_DescSequence_Destruct(ASN_DescSequence object);
ASN_Object ASN_DescSequence_Factory(const ASN_DescSequence object);
void ASN_DescSequence_SetCloneForFactory(ASN_DescSequence object, ASN_Sequence clone);
ASN_Object ASN_DescSequence_DefaultFactory(const ASN_DescSequence object);
void ASN_DescSequence_SetCloneForDefaultFactory(ASN_DescSequence object, ASN_Sequence clone);
ITS_BOOLEAN ASN_DescSequence_IsClauseOptional(const ASN_DescSequence object);
ITS_BOOLEAN ASN_DescSequence_IsClauseDefault(const ASN_DescSequence object);
ITS_BOOLEAN ASN_DescSequence_IsClauseAnyTag(const ASN_DescSequence object);
void ASN_DescSequence_SetClauseOptional(ASN_DescSequence object);
void ASN_DescSequence_SetClauseDefault(ASN_DescSequence object);
void ASN_DescSequence_SetClauseAnyTag(ASN_DescSequence object);
ITS_BOOLEAN ASN_DescSequence_TagIdentify(const ASN_DescSequence object, const ASN_Tag tag);
const ASN_Tag ASN_DescSequence_TagIdentity(const ASN_DescSequence object);
void ASN_DescSequence_TagAddLevel(ASN_DescSequence object, ASN_Tag tag);
size_t ASN_DescSequence_TagLevelNumber(const ASN_DescSequence object);
ASN_LinkedList ASN_DescSequence_TagStack(ASN_DescSequence object);
const char* ASN_DescSequence_GetName(const ASN_DescSequence object);
const char* ASN_DescSequence_GetBaseName(const ASN_DescSequence object);
const ASN_DescObject* ASN_DescSequence_GetElements(const ASN_DescSequence object);
void ASN_DescSequence_AddElement(ASN_DescSequence object, size_t index, ASN_DescObject element);
const ASN_DescObject ASN_DescSequence_GetElementAt(const ASN_DescSequence object, size_t index);
const ASN_DescObject ASN_DescSequence_GetElementAtTag(const ASN_DescSequence object, const ASN_Tag tag);
ITS_BOOLEAN ASN_DescSequence_Contains(const ASN_DescSequence object, size_t index);
ITS_BOOLEAN ASN_DescSequence_ContainsTag(const ASN_DescSequence object, const ASN_Tag tag);
size_t ASN_DescSequence_GetSize(const ASN_DescSequence object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_SEQUENCE_H_) */


