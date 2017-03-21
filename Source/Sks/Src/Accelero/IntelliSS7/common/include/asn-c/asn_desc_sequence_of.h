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
 *  ID: $Id: asn_desc_sequence_of.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescSequenceOf interface.
 */

#if !defined(_C_ASN_DESC_SEQUENCE_OF_H_)
#define _C_ASN_DESC_SEQUENCE_OF_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_SequenceOf_ObjectRec*      ASN_SequenceOf;
typedef struct _ASN_DescSequenceOf_ObjectRec*  ASN_DescSequenceOf;
typedef struct _ASN_DescSequenceOf_ClassRec*   ASN_DescSequenceOfClass;



/*
 *  Procedure signatures.
 */

typedef ITS_BOOLEAN     (*ASN_DescSequenceOf_IsClauseSizeProc)(const ASN_DescSequenceOf object);
typedef void            (*ASN_DescSequenceOf_SetClauseSizeProc)(ASN_DescSequenceOf object);
typedef void            (*ASN_DescSequenceOf_SetMaxSizeProc)(ASN_DescSequenceOf object, size_t maxSize);
typedef size_t          (*ASN_DescSequenceOf_GetMaxSizeProc)(const ASN_DescSequenceOf object);
typedef void            (*ASN_DescSequenceOf_SetMinSizeProc)(ASN_DescSequenceOf object, size_t minSize);
typedef size_t          (*ASN_DescSequenceOf_GetMinSizeProc)(const ASN_DescSequenceOf object);
typedef ASN_DescObject  (*ASN_DescSequenceOf_GetElementProc)(const ASN_DescSequenceOf object);
typedef void            (*ASN_DescSequenceOf_SetElementProc)(ASN_DescSequenceOf object, ASN_DescObject element);
typedef ITS_BOOLEAN     (*ASN_DescSequenceOf_ContainsProc)(const ASN_DescSequenceOf object, const ASN_Tag tag);

/* ASN_DescSequenceOf class. */

typedef struct
{
    ASN_DescSequenceOf_IsClauseSizeProc     isClauseSize;
    ASN_DescSequenceOf_SetClauseSizeProc    setClauseSize;
    ASN_DescSequenceOf_SetMaxSizeProc       setMaxSize;
    ASN_DescSequenceOf_GetMaxSizeProc       getMaxSize;
    ASN_DescSequenceOf_SetMinSizeProc       setMinSize;
    ASN_DescSequenceOf_GetMinSizeProc       getMinSize;
    ASN_DescSequenceOf_GetElementProc       getElement;
    ASN_DescSequenceOf_SetElementProc       setElement;
    ASN_DescSequenceOf_ContainsProc         contains;
} ASN_DescSequenceOf_ClassPart;


typedef struct _ASN_DescSequenceOf_ClassRec
{
    ITS_CoreClassPart               coreClass;
    ASN_DescObject_ClassPart        asnDescObjectClass;
    ASN_DescSequenceOf_ClassPart    asnDescSequenceOfClass;
} ASN_DescSequenceOf_ClassRec;

#define ASN_DESC_SEQUENCE_OF_CLASS_IS_CLAUSE_SIZE(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.isClauseSize)

#define ASN_DESC_SEQUENCE_OF_CLASS_SET_CLAUSE_SIZE(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.setClauseSize)

#define ASN_DESC_SEQUENCE_OF_CLASS_SET_MAX_SIZE(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.setMaxSize)

#define ASN_DESC_SEQUENCE_OF_CLASS_GET_MAX_SIZE(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.getMaxSize)

#define ASN_DESC_SEQUENCE_OF_CLASS_SET_MIN_SIZE(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.setMinSize)

#define ASN_DESC_SEQUENCE_OF_CLASS_GET_MIN_SIZE(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.getMinSize)

#define ASN_DESC_SEQUENCE_OF_CLASS_GET_ELEMENT(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.getElement)

#define ASN_DESC_SEQUENCE_OF_CLASS_SET_ELEMENT(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.setElement)

#define ASN_DESC_SEQUENCE_OF_CLASS_CONTAINS(x) \
    (((ASN_DescSequenceOfClass)(x))->asnDescSequenceOfClass.contains)


/*
 *  For inheritance.
 */ 

extern ASN_DescSequenceOf_ClassRec itsASN_DescSequenceOf_ClassRec;


/* ASN_DescSequenceOf object. */

typedef struct _ASN_DescSequenceOf_ObjectPart
{
    ITS_BOOLEAN     clauseSize;
    size_t          maxSize;
    size_t          minSize;
    ASN_DescObject  element;
} ASN_DescSequenceOf_ObjectPart;


typedef struct _ASN_DescSequenceOf_ObjectRec
{
    ITS_CoreObjectPart              core;
    ASN_DescObject_ObjectPart       asnDescObject;
    ASN_DescSequenceOf_ObjectPart   asnDescSequenceOf;
} ASN_DescSequenceOf_ObjectRec;

#define ASN_DESC_SEQUENCE_OF_CLAUSE_SIZE(x) \
    (((ASN_DescSequenceOf)(x))->asnDescSequenceOf.clauseSize)

#define ASN_DESC_SEQUENCE_OF_MAX_SIZE(x) \
    (((ASN_DescSequenceOf)(x))->asnDescSequenceOf.maxSize)

#define ASN_DESC_SEQUENCE_OF_MIN_SIZE(x) \
    (((ASN_DescSequenceOf)(x))->asnDescSequenceOf.minSize)

#define ASN_DESC_SEQUENCE_OF_ELEMENT(x) \
    (((ASN_DescSequenceOf)(x))->asnDescSequenceOf.element)


#define ASN_DESC_SEQUENCE_OF_CLASS_NAME "ASN_DescSequenceOf"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescSequenceOf ASN_DescSequenceOf_ConstructDefault();
void ASN_DescSequenceOf_Destruct(ASN_DescSequenceOf object);
ASN_Object ASN_DescSequenceOf_Factory(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetCloneForFactory(ASN_DescSequenceOf object, ASN_SequenceOf clone);
ASN_Object ASN_DescSequenceOf_DefaultFactory(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetCloneForDefaultFactory(ASN_DescSequenceOf object, ASN_SequenceOf clone);
ITS_BOOLEAN ASN_DescSequenceOf_IsClauseOptional(const ASN_DescSequenceOf object);
ITS_BOOLEAN ASN_DescSequenceOf_IsClauseDefault(const ASN_DescSequenceOf object);
ITS_BOOLEAN ASN_DescSequenceOf_IsClauseAnyTag(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetClauseOptional(ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetClauseDefault(ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetClauseAnyTag(ASN_DescSequenceOf object);
ITS_BOOLEAN ASN_DescSequenceOf_TagIdentify(const ASN_DescSequenceOf object, const ASN_Tag tag);
const ASN_Tag ASN_DescSequenceOf_TagIdentity(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_TagAddLevel(ASN_DescSequenceOf object, ASN_Tag tag);
size_t ASN_DescSequenceOf_TagLevelNumber(const ASN_DescSequenceOf object);
ASN_LinkedList ASN_DescSequenceOf_TagStack(ASN_DescSequenceOf object);
const char* ASN_DescSequenceOf_GetName(const ASN_DescSequenceOf object);
const char* ASN_DescSequenceOf_GetBaseName(const ASN_DescSequenceOf object);
ITS_BOOLEAN ASN_DescSequenceOf_IsClauseSize(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetClauseSize(ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetMaxSize(ASN_DescSequenceOf object, size_t maxSize);
size_t ASN_DescSequenceOf_GetMaxSize(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetMinSize(ASN_DescSequenceOf object, size_t minSize);
size_t ASN_DescSequenceOf_GetMinSize(const ASN_DescSequenceOf object);
ASN_DescObject ASN_DescSequenceOf_GetElement(const ASN_DescSequenceOf object);
void ASN_DescSequenceOf_SetElement(ASN_DescSequenceOf object, ASN_DescObject element);
ITS_BOOLEAN ASN_DescSequenceOf_Contains(const ASN_DescSequenceOf object, const ASN_Tag tag);


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_SEQUENCE_OF_H_) */


