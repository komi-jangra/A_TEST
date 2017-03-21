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
 *  ID: $Id: asn_sequence.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Sequence interface.
 */

#if !defined(_C_ASN_SEQUENCE_H_)
#define _C_ASN_SEQUENCE_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_sequence.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Sequence already defined in description. */
typedef struct _ASN_Sequence_ClassRec*       ASN_SequenceClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescSequence    (*ASN_Sequence_GetStaticDescriptionProc)();
typedef void                (*ASN_Sequence_DestructStaticDescriptionProc)();
typedef const ASN_Object*   (*ASN_Sequence_GetElementsProc)(const ASN_Sequence object);
typedef void                (*ASN_Sequence_AddElementProc)(ASN_Sequence object, size_t index, ASN_Object element);
typedef const ASN_Object    (*ASN_Sequence_GetElementAtProc)(const ASN_Sequence object, size_t index);
typedef const ASN_Object    (*ASN_Sequence_GetElementAtTagProc)(const ASN_Sequence object, const ASN_Tag tag);
typedef ITS_BOOLEAN         (*ASN_Sequence_ContainsProc)(const ASN_Sequence object, size_t index);
typedef ITS_BOOLEAN         (*ASN_Sequence_ContainsTagProc)(const ASN_Sequence object, const ASN_Tag tag);
typedef void                (*ASN_Sequence_RemoveElementProc)(ASN_Sequence object, size_t index);
typedef void                (*ASN_Sequence_RemoveElementTagProc)(ASN_Sequence object, const ASN_Tag tag);
typedef void                (*ASN_Sequence_RemoveAllElementsProc)(ASN_Sequence object);
typedef size_t              (*ASN_Sequence_GetSizeProc)(const ASN_Sequence object);
typedef ASN_Tag             (*ASN_Sequence_GetUniversalTagProc)(const ASN_Sequence object);


/*
 *  Procedure overrides.
 */

#define ASN_SEQUENCE_GET_ELEMENTS_INHERIT           (ASN_Sequence_GetElementsProc)NULL              
#define ASN_SEQUENCE_ADD_ELEMENT_INHERIT            (ASN_Sequence_AddElementProc)NULL           
#define ASN_SEQUENCE_GET_ELEMENT_AT_INHERIT         (ASN_Sequence_GetElementAtProc)NULL             
#define ASN_SEQUENCE_GET_ELEMENT_AT_TAG_INHERIT     (ASN_Sequence_GetElementAtTagProc)NULL          
#define ASN_SEQUENCE_CONTAINS_INHERIT               (ASN_Sequence_ContainsProc)NULL                 
#define ASN_SEQUENCE_CONTAINS_TAG_INHERIT           (ASN_Sequence_ContainsTagProc)NULL              
#define ASN_SEQUENCE_REMOVE_ELEMENT_INHERIT         (ASN_Sequence_RemoveElementProc)NULL            
#define ASN_SEQUENCE_REMOVE_ELEMENT_TAG_INHERIT     (ASN_Sequence_RemoveElementTagProc)NULL         
#define ASN_SEQUENCE_REMOVE_ALL_ELEMENTS_INHERIT    (ASN_Sequence_RemoveAllElementsProc)NULL        
#define ASN_SEQUENCE_GET_SIZE_INHERIT               (ASN_Sequence_GetSizeProc)NULL                  
#define ASN_SEQUENCE_GET_UNIVERSAL_TAG_INHERIT      (ASN_Sequence_GetUniversalTagProc)NULL

/* ASN_Sequence class. */

typedef struct
{
    ASN_Sequence_GetStaticDescriptionProc       getStaticDescription;
    ASN_Sequence_DestructStaticDescriptionProc  destructStaticDescription;
    ASN_Sequence_GetElementsProc                getElements;
    ASN_Sequence_AddElementProc                 addElement;
    ASN_Sequence_GetElementAtProc               getElementAt;
    ASN_Sequence_GetElementAtTagProc            getElementAtTag;
    ASN_Sequence_ContainsProc                   contains;
    ASN_Sequence_ContainsTagProc                containsTag;
    ASN_Sequence_RemoveElementProc              removeElement;
    ASN_Sequence_RemoveElementTagProc           removeElementTag;
    ASN_Sequence_RemoveAllElementsProc          removeAllElements;
    ASN_Sequence_GetSizeProc                    getSize;
    ASN_Sequence_GetUniversalTagProc            getUniversalTag;
} ASN_Sequence_ClassPart;


typedef struct _ASN_Sequence_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Sequence_ClassPart  asnSequenceClass;
} ASN_Sequence_ClassRec;

#define ASN_SEQUENCE_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.getStaticDescription)

#define ASN_SEQUENCE_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.destructStaticDescription)

#define ASN_SEQUENCE_CLASS_GET_ELEMENTS(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.getElements)

#define ASN_SEQUENCE_CLASS_ADD_ELEMENT(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.addElement)

#define ASN_SEQUENCE_CLASS_GET_ELEMENT_AT(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.getElementAt)

#define ASN_SEQUENCE_CLASS_GET_ELEMENT_AT_TAG(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.getElementAtTag)

#define ASN_SEQUENCE_CLASS_CONTAINS(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.contains)

#define ASN_SEQUENCE_CLASS_CONTAINS_TAG(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.containsTag)

#define ASN_SEQUENCE_CLASS_REMOVE_ELEMENT(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.removeElement)

#define ASN_SEQUENCE_CLASS_REMOVE_ELEMENT_TAG(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.removeElementTag)

#define ASN_SEQUENCE_CLASS_REMOVE_ALL_ELEMENTS(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.removeAllElements)

#define ASN_SEQUENCE_CLASS_GET_SIZE(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.getSize)

#define ASN_SEQUENCE_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_SequenceClass)(x))->asnSequenceClass.getUniversalTag)



/*
 *  For inheritance.
 */ 

extern ASN_Sequence_ClassRec itsASN_Sequence_ClassRec;


/* ASN_Sequence object. */

typedef struct _ASN_Sequence_ObjectPart
{
    ASN_Object* elements;
    size_t      size;
} ASN_Sequence_ObjectPart;


typedef struct _ASN_Sequence_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Sequence_ObjectPart asnSequence;
} ASN_Sequence_ObjectRec;

#define ASN_SEQUENCE_ELEMENTS(x) \
    (((ASN_Sequence)(x))->asnSequence.elements)

#define ASN_SEQUENCE_SIZE(x) \
    (((ASN_Sequence)(x))->asnSequence.size)


#define ASN_SEQUENCE_CLASS_NAME "ASN_Sequence"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Sequence ASN_Sequence_ConstructWithSize(size_t size);
ASN_Sequence ASN_Sequence_ConstructWithSizeDescription(size_t size, ASN_DescSequence description);
void ASN_Sequence_Destruct(ASN_Sequence object);
ASN_Sequence ASN_Sequence_Clone(const ASN_Sequence object);
ITS_BOOLEAN ASN_Sequence_Equals(const ASN_Sequence object, const ASN_Sequence other);
ASN_DescSequence ASN_Sequence_GetStaticDescription();
void ASN_Sequence_DestructStaticDescription();
const ASN_Object* ASN_Sequence_GetElements(const ASN_Sequence object);
void ASN_Sequence_AddElement(ASN_Sequence object, size_t index, ASN_Object element);
const ASN_Object ASN_Sequence_GetElementAt(const ASN_Sequence object, size_t index);
const ASN_Object ASN_Sequence_GetElementAtTag(const ASN_Sequence object, const ASN_Tag tag);
ITS_BOOLEAN ASN_Sequence_Contains(const ASN_Sequence object, size_t index);
ITS_BOOLEAN ASN_Sequence_ContainsTag(const ASN_Sequence object, const ASN_Tag tag);
void ASN_Sequence_RemoveElement(ASN_Sequence object, size_t index);
void ASN_Sequence_RemoveElementTag(ASN_Sequence object, const ASN_Tag tag);
void ASN_Sequence_RemoveAllElements(ASN_Sequence object);
size_t ASN_Sequence_GetSize(const ASN_Sequence object);
ASN_Tag ASN_Sequence_GetUniversalTag(const ASN_Sequence object);
int ASN_Sequence_Encode(ASN_Sequence object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Sequence_Decode(ASN_Sequence object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Sequence_GetName(const ASN_Sequence object);
const char* ASN_Sequence_GetBaseName(const ASN_Sequence object);
void ASN_Sequence_Print(const ASN_Sequence object);
char* ASN_Sequence_ToString(const ASN_Sequence object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_SEQUENCE_H_) */
