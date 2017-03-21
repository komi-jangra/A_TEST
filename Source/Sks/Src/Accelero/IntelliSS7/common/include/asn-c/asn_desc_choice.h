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
 *  ID: $Id: asn_desc_choice.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescChoice interface.
 */

#if !defined(_C_ASN_DESC_CHOICE_H_)
#define _C_ASN_DESC_CHOICE_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Choice_ObjectRec*      ASN_Choice;
typedef struct _ASN_DescChoice_ObjectRec*  ASN_DescChoice;
typedef struct _ASN_DescChoice_ClassRec*   ASN_DescChoiceClass;



/*
 *  Procedure signatures.
 */

typedef const ASN_DescObject*   (*ASN_DescChoice_GetChoicesProc)(const ASN_DescChoice object);
typedef void                    (*ASN_DescChoice_AddChoiceProc)(ASN_DescChoice object, size_t index, ASN_DescObject element);
typedef const ASN_DescObject    (*ASN_DescChoice_GetChoiceAtProc)(const ASN_DescChoice object, size_t index);
typedef const ASN_DescObject    (*ASN_DescChoice_GetChoiceAtTagProc)(const ASN_DescChoice object, const ASN_Tag tag);
typedef ITS_BOOLEAN             (*ASN_DescChoice_ContainsProc)(const ASN_DescChoice object, size_t index);
typedef ITS_BOOLEAN             (*ASN_DescChoice_ContainsTagProc)(const ASN_DescChoice object, const ASN_Tag tag);
typedef size_t                  (*ASN_DescChoice_GetSizeProc)(const ASN_DescChoice object);



/* ASN_DescChoice class. */

typedef struct
{
    ASN_DescChoice_GetChoicesProc       getChoices;
    ASN_DescChoice_AddChoiceProc        addChoice;
    ASN_DescChoice_GetChoiceAtProc      getChoiceAt;
    ASN_DescChoice_GetChoiceAtTagProc   getChoiceAtTag;
    ASN_DescChoice_ContainsProc         contains;
    ASN_DescChoice_ContainsTagProc      containsTag;
    ASN_DescChoice_GetSizeProc          getSize;
} ASN_DescChoice_ClassPart;


typedef struct _ASN_DescChoice_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescChoice_ClassPart    asnDescChoiceClass;
} ASN_DescChoice_ClassRec;

#define ASN_DESC_CHOICE_CLASS_GET_CHOICES(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.getChoices)

#define ASN_DESC_CHOICE_CLASS_ADD_CHOICE(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.addChoice)

#define ASN_DESC_CHOICE_CLASS_GET_CHOICE_AT(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.getChoiceAt)

#define ASN_DESC_CHOICE_CLASS_GET_CHOICE_AT_TAG(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.getChoiceAtTag)

#define ASN_DESC_CHOICE_CLASS_CONTAINS(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.contains)

#define ASN_DESC_CHOICE_CLASS_CONTAINS_TAG(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.containsTag)

#define ASN_DESC_CHOICE_CLASS_GET_SIZE(x) \
    (((ASN_DescChoiceClass)(x))->asnDescChoiceClass.getSize)


/*
 *  For inheritance.
 */ 

extern ASN_DescChoice_ClassRec itsASN_DescChoice_ClassRec;


/* ASN_DescChoice object. */

typedef struct _ASN_DescChoice_ObjectPart
{
    ASN_DescObject* choices;
    size_t          size;
} ASN_DescChoice_ObjectPart;


typedef struct _ASN_DescChoice_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescChoice_ObjectPart   asnDescChoice;
} ASN_DescChoice_ObjectRec;

#define ASN_DESC_CHOICE_CHOICES(x) \
    (((ASN_DescChoice)(x))->asnDescChoice.choices)

#define ASN_DESC_CHOICE_SIZE(x) \
    (((ASN_DescChoice)(x))->asnDescChoice.size)

#define ASN_DESC_CHOICE_CLASS_NAME "ASN_DescChoice"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescChoice ASN_DescChoice_ConstructWithSize(size_t size);
void ASN_DescChoice_Destruct(ASN_DescChoice object);
ASN_Object ASN_DescChoice_Factory(const ASN_DescChoice object);
void ASN_DescChoice_SetCloneForFactory(ASN_DescChoice object, ASN_Choice clone);
ASN_Object ASN_DescChoice_DefaultFactory(const ASN_DescChoice object);
void ASN_DescChoice_SetCloneForDefaultFactory(ASN_DescChoice object, ASN_Choice clone);
ITS_BOOLEAN ASN_DescChoice_IsClauseOptional(const ASN_DescChoice object);
ITS_BOOLEAN ASN_DescChoice_IsClauseDefault(const ASN_DescChoice object);
ITS_BOOLEAN ASN_DescChoice_IsClauseAnyTag(const ASN_DescChoice object);
void ASN_DescChoice_SetClauseOptional(ASN_DescChoice object);
void ASN_DescChoice_SetClauseDefault(ASN_DescChoice object);
void ASN_DescChoice_SetClauseAnyTag(ASN_DescChoice object);
ITS_BOOLEAN ASN_DescChoice_TagIdentify(const ASN_DescChoice object, const ASN_Tag tag);
const ASN_Tag ASN_DescChoice_TagIdentity(const ASN_DescChoice object);
void ASN_DescChoice_TagAddLevel(ASN_DescChoice object, ASN_Tag tag);
size_t ASN_DescChoice_TagLevelNumber(const ASN_DescChoice object);
ASN_LinkedList ASN_DescChoice_TagStack(ASN_DescChoice object);
const char* ASN_DescChoice_GetName(const ASN_DescChoice object);
const char* ASN_DescChoice_GetBaseName(const ASN_DescChoice object);
const ASN_DescObject* ASN_DescChoice_GetChoices(const ASN_DescChoice object);
void ASN_DescChoice_AddChoice(ASN_DescChoice object, size_t index, ASN_DescObject choice);
const ASN_DescObject ASN_DescChoice_GetChoiceAt(const ASN_DescChoice object, size_t index);
const ASN_DescObject ASN_DescChoice_GetChoiceAtTag(const ASN_DescChoice object, const ASN_Tag tag);
ITS_BOOLEAN ASN_DescChoice_Contains(const ASN_DescChoice object, size_t index);
ITS_BOOLEAN ASN_DescChoice_ContainsTag(const ASN_DescChoice object, const ASN_Tag tag);
size_t ASN_DescChoice_GetSize(const ASN_DescChoice object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_CHOICE_H_) */


