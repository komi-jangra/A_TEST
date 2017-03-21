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
 *  ID: $Id: asn_set.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Set interface.
 */

#if !defined(_C_ASN_SET_H_)
#define _C_ASN_SET_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_set.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Set already defined in description. */
typedef struct _ASN_Set_ClassRec*       ASN_SetClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescSet         (*ASN_Set_GetStaticDescriptionProc)();
typedef void                (*ASN_Set_DestructStaticDescriptionProc)();
typedef const ASN_Object*   (*ASN_Set_GetElementsProc)(const ASN_Set object);
typedef void                (*ASN_Set_AddElementProc)(ASN_Set object, size_t index, ASN_Object element);
typedef const ASN_Object    (*ASN_Set_GetElementAtProc)(const ASN_Set object, size_t index);
typedef const ASN_Object    (*ASN_Set_GetElementAtTagProc)(const ASN_Set object, const ASN_Tag tag);
typedef ITS_BOOLEAN         (*ASN_Set_ContainsProc)(const ASN_Set object, size_t index);
typedef ITS_BOOLEAN         (*ASN_Set_ContainsTagProc)(const ASN_Set object, const ASN_Tag tag);
typedef void                (*ASN_Set_RemoveElementProc)(ASN_Set object, size_t index);
typedef void                (*ASN_Set_RemoveElementTagProc)(ASN_Set object, const ASN_Tag tag);
typedef void                (*ASN_Set_RemoveAllElementsProc)(ASN_Set object);
typedef size_t              (*ASN_Set_GetSizeProc)(const ASN_Set object);
typedef ASN_Tag             (*ASN_Set_GetUniversalTagProc)(const ASN_Set object);


/*
 *  Procedure overrides.
 */

#define ASN_SET_GET_ELEMENTS_INHERIT           (ASN_Set_GetElementsProc)NULL              
#define ASN_SET_ADD_ELEMENT_INHERIT            (ASN_Set_AddElementProc)NULL           
#define ASN_SET_GET_ELEMENT_AT_INHERIT         (ASN_Set_GetElementAtProc)NULL             
#define ASN_SET_GET_ELEMENT_AT_TAG_INHERIT     (ASN_Set_GetElementAtTagProc)NULL          
#define ASN_SET_CONTAINS_INHERIT               (ASN_Set_ContainsProc)NULL                 
#define ASN_SET_CONTAINS_TAG_INHERIT           (ASN_Set_ContainsTagProc)NULL              
#define ASN_SET_REMOVE_ELEMENT_INHERIT         (ASN_Set_RemoveElementProc)NULL            
#define ASN_SET_REMOVE_ELEMENT_TAG_INHERIT     (ASN_Set_RemoveElementTagProc)NULL         
#define ASN_SET_REMOVE_ALL_ELEMENTS_INHERIT    (ASN_Set_RemoveAllElementsProc)NULL        
#define ASN_SET_GET_SIZE_INHERIT               (ASN_Set_GetSizeProc)NULL                  
#define ASN_SET_GET_UNIVERSAL_TAG_INHERIT      (ASN_Set_GetUniversalTagProc)NULL

/* ASN_Set class. */

typedef struct
{
    ASN_Set_GetStaticDescriptionProc       getStaticDescription;
    ASN_Set_DestructStaticDescriptionProc  destructStaticDescription;
    ASN_Set_GetElementsProc                getElements;
    ASN_Set_AddElementProc                 addElement;
    ASN_Set_GetElementAtProc               getElementAt;
    ASN_Set_GetElementAtTagProc            getElementAtTag;
    ASN_Set_ContainsProc                   contains;
    ASN_Set_ContainsTagProc                containsTag;
    ASN_Set_RemoveElementProc              removeElement;
    ASN_Set_RemoveElementTagProc           removeElementTag;
    ASN_Set_RemoveAllElementsProc          removeAllElements;
    ASN_Set_GetSizeProc                    getSize;
    ASN_Set_GetUniversalTagProc            getUniversalTag;
} ASN_Set_ClassPart;


typedef struct _ASN_Set_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Set_ClassPart  asnSetClass;
} ASN_Set_ClassRec;

#define ASN_SET_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_SetClass)(x))->asnSetClass.getStaticDescription)

#define ASN_SET_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_SetClass)(x))->asnSetClass.destructStaticDescription)

#define ASN_SET_CLASS_GET_ELEMENTS(x) \
    (((ASN_SetClass)(x))->asnSetClass.getElements)

#define ASN_SET_CLASS_ADD_ELEMENT(x) \
    (((ASN_SetClass)(x))->asnSetClass.addElement)

#define ASN_SET_CLASS_GET_ELEMENT_AT(x) \
    (((ASN_SetClass)(x))->asnSetClass.getElementAt)

#define ASN_SET_CLASS_GET_ELEMENT_AT_TAG(x) \
    (((ASN_SetClass)(x))->asnSetClass.getElementAtTag)

#define ASN_SET_CLASS_CONTAINS(x) \
    (((ASN_SetClass)(x))->asnSetClass.contains)

#define ASN_SET_CLASS_CONTAINS_TAG(x) \
    (((ASN_SetClass)(x))->asnSetClass.containsTag)

#define ASN_SET_CLASS_REMOVE_ELEMENT(x) \
    (((ASN_SetClass)(x))->asnSetClass.removeElement)

#define ASN_SET_CLASS_REMOVE_ELEMENT_TAG(x) \
    (((ASN_SetClass)(x))->asnSetClass.removeElementTag)

#define ASN_SET_CLASS_REMOVE_ALL_ELEMENTS(x) \
    (((ASN_SetClass)(x))->asnSetClass.removeAllElements)

#define ASN_SET_CLASS_GET_SIZE(x) \
    (((ASN_SetClass)(x))->asnSetClass.getSize)

#define ASN_SET_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_SetClass)(x))->asnSetClass.getUniversalTag)



/*
 *  For inheritance.
 */ 

extern ASN_Set_ClassRec itsASN_Set_ClassRec;


/* ASN_Set object. */

typedef struct _ASN_Set_ObjectPart
{
    ASN_Object* elements;
    size_t      size;
} ASN_Set_ObjectPart;


typedef struct _ASN_Set_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Set_ObjectPart      asnSet;
} ASN_Set_ObjectRec;

#define ASN_SET_ELEMENTS(x) \
    (((ASN_Set)(x))->asnSet.elements)

#define ASN_SET_SIZE(x) \
    (((ASN_Set)(x))->asnSet.size)


#define ASN_SET_CLASS_NAME "ASN_Set"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Set ASN_Set_ConstructWithSize(size_t size);
ASN_Set ASN_Set_ConstructWithSizeDescription(size_t size, ASN_DescSet description);
void ASN_Set_Destruct(ASN_Set object);
ASN_Set ASN_Set_Clone(const ASN_Set object);
ITS_BOOLEAN ASN_Set_Equals(const ASN_Set object, const ASN_Set other);
ASN_DescSet ASN_Set_GetStaticDescription();
void ASN_Set_DestructStaticDescription();
const ASN_Object* ASN_Set_GetElements(const ASN_Set object);
void ASN_Set_AddElement(ASN_Set object, size_t index, ASN_Object element);
const ASN_Object ASN_Set_GetElementAt(const ASN_Set object, size_t index);
const ASN_Object ASN_Set_GetElementAtTag(const ASN_Set object, const ASN_Tag tag);
ITS_BOOLEAN ASN_Set_Contains(const ASN_Set object, size_t index);
ITS_BOOLEAN ASN_Set_ContainsTag(const ASN_Set object, const ASN_Tag tag);
void ASN_Set_RemoveElement(ASN_Set object, size_t index);
void ASN_Set_RemoveElementTag(ASN_Set object, const ASN_Tag tag);
void ASN_Set_RemoveAllElements(ASN_Set object);
size_t ASN_Set_GetSize(const ASN_Set object);
ASN_Tag ASN_Set_GetUniversalTag(const ASN_Set object);
int ASN_Set_Encode(ASN_Set object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Set_Decode(ASN_Set object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Set_GetName(const ASN_Set object);
const char* ASN_Set_GetBaseName(const ASN_Set object);
void ASN_Set_Print(const ASN_Set object);
char* ASN_Set_ToString(const ASN_Set object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_SET_H_) */
