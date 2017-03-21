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
 *  ID: $Id: asn_set_of.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_SetOf interface.
 */

#if !defined(_C_ASN_SET_OF_H_)
#define _C_ASN_SET_OF_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_set_of.h>
#include <asn_linked_list.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_SetOf already defined in description. */
typedef struct _ASN_SetOf_ClassRec*         ASN_SetOfClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescSetOf           (*ASN_SetOf_GetStaticDescriptionProc)();
typedef void                    (*ASN_SetOf_DestructStaticDescriptionProc)();
typedef const ASN_LinkedList    (*ASN_SetOf_GetElementsProc)(const ASN_SetOf object);
typedef int                     (*ASN_SetOf_AddElementProc)(ASN_SetOf object, ASN_Object element);
typedef const ASN_Object        (*ASN_SetOf_GetElementAtProc)(const ASN_SetOf object, size_t index);
typedef void                    (*ASN_SetOf_RemoveElementProc)(ASN_SetOf object, size_t index);
typedef void                    (*ASN_SetOf_RemoveAllElementsProc)(ASN_SetOf object);
typedef size_t                  (*ASN_SetOf_GetSizeProc)(const ASN_SetOf object);
typedef ITS_BOOLEAN             (*ASN_SetOf_IsEmptyProc)(const ASN_SetOf object);
typedef ASN_Tag                 (*ASN_SetOf_GetUniversalTagProc)(const ASN_SetOf object);


/*
 *  Procedure overrides.
 */

#define ASN_SET_OF_GET_ELEMENTS_INHERIT        (ASN_SetOf_GetElementsProc)NULL              
#define ASN_SET_OF_ADD_ELEMENT_INHERIT         (ASN_SetOf_AddElementProc)NULL           
#define ASN_SET_OF_GET_ELEMENT_AT_INHERIT      (ASN_SetOf_GetElementAtProc)NULL             
#define ASN_SET_OF_REMOVE_ELEMENT_INHERIT      (ASN_SetOf_RemoveElementProc)NULL                  
#define ASN_SET_OF_REMOVE_ALL_ELEMENTS_INHERIT (ASN_SetOf_RemoveAllElementsProc)NULL        
#define ASN_SET_OF_GET_SIZE_INHERIT            (ASN_SetOf_GetSizeProc)NULL
#define ASN_SET_OF_IS_EMPTY_INHERIT            (ASN_SetOf_IsEmptyProc)NULL          
#define ASN_SET_OF_GET_UNIVERSAL_TAG_INHERIT   (ASN_SetOf_GetUniversalTagProc)NULL

/* ASN_SetOf class. */

typedef struct
{
    ASN_SetOf_GetStaticDescriptionProc         getStaticDescription;
    ASN_SetOf_DestructStaticDescriptionProc    destructStaticDescription;
    ASN_SetOf_GetElementsProc                  getElements;
    ASN_SetOf_AddElementProc                   addElement;
    ASN_SetOf_GetElementAtProc                 getElementAt;
    ASN_SetOf_RemoveElementProc                removeElement;
    ASN_SetOf_RemoveAllElementsProc            removeAllElements;
    ASN_SetOf_GetSizeProc                      getSize;
    ASN_SetOf_IsEmptyProc                      isEmpty;
    ASN_SetOf_GetUniversalTagProc              getUniversalTag;
} ASN_SetOf_ClassPart;


typedef struct _ASN_SetOf_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_SetOf_ClassPart     asnSetOfClass;
} ASN_SetOf_ClassRec;

#define ASN_SET_OF_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.getStaticDescription)

#define ASN_SET_OF_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.destructStaticDescription)

#define ASN_SET_OF_CLASS_GET_ELEMENTS(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.getElements)

#define ASN_SET_OF_CLASS_ADD_ELEMENT(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.addElement)

#define ASN_SET_OF_CLASS_GET_ELEMENT_AT(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.getElementAt)

#define ASN_SET_OF_CLASS_REMOVE_ELEMENT(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.removeElement)

#define ASN_SET_OF_CLASS_REMOVE_ALL_ELEMENTS(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.removeAllElements)

#define ASN_SET_OF_CLASS_GET_SIZE(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.getSize)

#define ASN_SET_OF_CLASS_IS_EMPTY(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.isEmpty)

#define ASN_SET_OF_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_SetOfClass)(x))->asnSetOfClass.getUniversalTag)



/*
 *  For inheritance.
 */ 

extern ASN_SetOf_ClassRec itsASN_SetOf_ClassRec;


/* ASN_SetOf object. */

typedef struct _ASN_SetOf_ObjectPart
{
    ASN_LinkedList elements;
} ASN_SetOf_ObjectPart;


typedef struct _ASN_SetOf_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_SetOf_ObjectPart    asnSetOf;
} ASN_SetOf_ObjectRec;

#define ASN_SET_OF_ELEMENTS(x) \
    (((ASN_SetOf)(x))->asnSetOf.elements)


#define ASN_SET_OF_CLASS_NAME "ASN_SetOf"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_SetOf ASN_SetOf_ConstructDefault();
ASN_SetOf ASN_SetOf_ConstructWithDescription(ASN_DescSetOf description);
void ASN_SetOf_Destruct(ASN_SetOf object);
ASN_SetOf ASN_SetOf_Clone(const ASN_SetOf object);
ITS_BOOLEAN ASN_SetOf_Equals(const ASN_SetOf object, const ASN_SetOf other);
ASN_DescSetOf ASN_SetOf_GetStaticDescription();
void ASN_SetOf_DestructStaticDescription();
const ASN_LinkedList ASN_SetOf_GetElements(const ASN_SetOf object);
int ASN_SetOf_AddElement(ASN_SetOf object, ASN_Object element);
const ASN_Object ASN_SetOf_GetElementAt(const ASN_SetOf object, size_t index);
void ASN_SetOf_RemoveElement(ASN_SetOf object, size_t index);
void ASN_SetOf_RemoveAllElements(ASN_SetOf object);
size_t ASN_SetOf_GetSize(const ASN_SetOf object);
ITS_BOOLEAN ASN_SetOf_IsEmpty(const ASN_SetOf object);
ASN_Tag ASN_SetOf_GetUniversalTag(const ASN_SetOf object);
int ASN_SetOf_Encode(ASN_SetOf object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_SetOf_Decode(ASN_SetOf object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_SetOf_GetName(const ASN_SetOf object);
const char* ASN_SetOf_GetBaseName(const ASN_SetOf object);
void ASN_SetOf_Print(const ASN_SetOf object);
char* ASN_SetOf_ToString(const ASN_SetOf object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_SET_OF_H_) */
