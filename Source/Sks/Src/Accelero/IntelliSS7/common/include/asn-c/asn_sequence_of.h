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
 *  ID: $Id: asn_sequence_of.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_SequenceOf interface.
 */

#if !defined(_C_ASN_SEQUENCE_OF_H_)
#define _C_ASN_SEQUENCE_OF_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_sequence_of.h>
#include <asn_linked_list.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_SequenceOf already defined in description. */
typedef struct _ASN_SequenceOf_ClassRec*        ASN_SequenceOfClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescSequenceOf      (*ASN_SequenceOf_GetStaticDescriptionProc)();
typedef void                    (*ASN_SequenceOf_DestructStaticDescriptionProc)();
typedef const ASN_LinkedList    (*ASN_SequenceOf_GetElementsProc)(const ASN_SequenceOf object);
typedef int                     (*ASN_SequenceOf_AddElementProc)(ASN_SequenceOf object, ASN_Object element);
typedef const ASN_Object        (*ASN_SequenceOf_GetElementAtProc)(const ASN_SequenceOf object, size_t index);
typedef void                    (*ASN_SequenceOf_RemoveElementProc)(ASN_SequenceOf object, size_t index);
typedef void                    (*ASN_SequenceOf_RemoveAllElementsProc)(ASN_SequenceOf object);
typedef size_t                  (*ASN_SequenceOf_GetSizeProc)(const ASN_SequenceOf object);
typedef ITS_BOOLEAN             (*ASN_SequenceOf_IsEmptyProc)(const ASN_SequenceOf object);
typedef ASN_Tag                 (*ASN_SequenceOf_GetUniversalTagProc)(const ASN_SequenceOf object);


/*
 *  Procedure overrides.
 */

#define ASN_SEQUENCE_OF_GET_ELEMENTS_INHERIT        (ASN_SequenceOf_GetElementsProc)NULL              
#define ASN_SEQUENCE_OF_ADD_ELEMENT_INHERIT         (ASN_SequenceOf_AddElementProc)NULL           
#define ASN_SEQUENCE_OF_GET_ELEMENT_AT_INHERIT      (ASN_SequenceOf_GetElementAtProc)NULL             
#define ASN_SEQUENCE_OF_REMOVE_ELEMENT_INHERIT      (ASN_SequenceOf_RemoveElementProc)NULL                  
#define ASN_SEQUENCE_OF_REMOVE_ALL_ELEMENTS_INHERIT (ASN_SequenceOf_RemoveAllElementsProc)NULL        
#define ASN_SEQUENCE_OF_GET_SIZE_INHERIT            (ASN_SequenceOf_GetSizeProc)NULL
#define ASN_SEQUENCE_OF_IS_EMPTY_INHERIT            (ASN_SequenceOf_IsEmptyProc)NULL          
#define ASN_SEQUENCE_OF_GET_UNIVERSAL_TAG_INHERIT   (ASN_SequenceOf_GetUniversalTagProc)NULL

/* ASN_SequenceOf class. */

typedef struct
{
    ASN_SequenceOf_GetStaticDescriptionProc         getStaticDescription;
    ASN_SequenceOf_DestructStaticDescriptionProc    destructStaticDescription;
    ASN_SequenceOf_GetElementsProc                  getElements;
    ASN_SequenceOf_AddElementProc                   addElement;
    ASN_SequenceOf_GetElementAtProc                 getElementAt;
    ASN_SequenceOf_RemoveElementProc                removeElement;
    ASN_SequenceOf_RemoveAllElementsProc            removeAllElements;
    ASN_SequenceOf_GetSizeProc                      getSize;
    ASN_SequenceOf_IsEmptyProc                      isEmpty;
    ASN_SequenceOf_GetUniversalTagProc              getUniversalTag;
} ASN_SequenceOf_ClassPart;


typedef struct _ASN_SequenceOf_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_Object_ClassPart        asnObjectClass;
    ASN_SequenceOf_ClassPart    asnSequenceOfClass;
} ASN_SequenceOf_ClassRec;

#define ASN_SEQUENCE_OF_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.getStaticDescription)

#define ASN_SEQUENCE_OF_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.destructStaticDescription)

#define ASN_SEQUENCE_OF_CLASS_GET_ELEMENTS(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.getElements)

#define ASN_SEQUENCE_OF_CLASS_ADD_ELEMENT(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.addElement)

#define ASN_SEQUENCE_OF_CLASS_GET_ELEMENT_AT(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.getElementAt)

#define ASN_SEQUENCE_OF_CLASS_REMOVE_ELEMENT(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.removeElement)

#define ASN_SEQUENCE_OF_CLASS_REMOVE_ALL_ELEMENTS(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.removeAllElements)

#define ASN_SEQUENCE_OF_CLASS_GET_SIZE(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.getSize)

#define ASN_SEQUENCE_OF_CLASS_IS_EMPTY(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.isEmpty)

#define ASN_SEQUENCE_OF_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_SequenceOfClass)(x))->asnSequenceOfClass.getUniversalTag)



/*
 *  For inheritance.
 */ 

extern ASN_SequenceOf_ClassRec itsASN_SequenceOf_ClassRec;


/* ASN_SequenceOf object. */

typedef struct _ASN_SequenceOf_ObjectPart
{
    ASN_LinkedList elements;
} ASN_SequenceOf_ObjectPart;


typedef struct _ASN_SequenceOf_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_Object_ObjectPart       asnObject;
    ASN_SequenceOf_ObjectPart   asnSequenceOf;
} ASN_SequenceOf_ObjectRec;

#define ASN_SEQUENCE_OF_ELEMENTS(x) \
    (((ASN_SequenceOf)(x))->asnSequenceOf.elements)


#define ASN_SEQUENCE_OF_CLASS_NAME "ASN_SequenceOf"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_SequenceOf ASN_SequenceOf_ConstructDefault();
ASN_SequenceOf ASN_SequenceOf_ConstructWithDescription(ASN_DescSequenceOf description);
void ASN_SequenceOf_Destruct(ASN_SequenceOf object);
ASN_SequenceOf ASN_SequenceOf_Clone(const ASN_SequenceOf object);
ITS_BOOLEAN ASN_SequenceOf_Equals(const ASN_SequenceOf object, const ASN_SequenceOf other);
ASN_DescSequenceOf ASN_SequenceOf_GetStaticDescription();
void ASN_SequenceOf_DestructStaticDescription();
const ASN_LinkedList ASN_SequenceOf_GetElements(const ASN_SequenceOf object);
int ASN_SequenceOf_AddElement(ASN_SequenceOf object, ASN_Object element);
const ASN_Object ASN_SequenceOf_GetElementAt(const ASN_SequenceOf object, size_t index);
void ASN_SequenceOf_RemoveElement(ASN_SequenceOf object, size_t index);
void ASN_SequenceOf_RemoveAllElements(ASN_SequenceOf object);
size_t ASN_SequenceOf_GetSize(const ASN_SequenceOf object);
ITS_BOOLEAN ASN_SequenceOf_IsEmpty(const ASN_SequenceOf object);
ASN_Tag ASN_SequenceOf_GetUniversalTag(const ASN_SequenceOf object);
int ASN_SequenceOf_Encode(ASN_SequenceOf object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_SequenceOf_Decode(ASN_SequenceOf object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_SequenceOf_GetName(const ASN_SequenceOf object);
const char* ASN_SequenceOf_GetBaseName(const ASN_SequenceOf object);
void ASN_SequenceOf_Print(const ASN_SequenceOf object);
char* ASN_SequenceOf_ToString(const ASN_SequenceOf object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_SEQUENCE_OF_H_) */
