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
 *  ID: $Id: asn_desc_set_of.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescSetOf interface.
 */

#if !defined(_C_ASN_DESC_SET_OF_H_)
#define _C_ASN_DESC_SET_OF_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_SetOf_ObjectRec*      ASN_SetOf;
typedef struct _ASN_DescSetOf_ObjectRec*  ASN_DescSetOf;
typedef struct _ASN_DescSetOf_ClassRec*   ASN_DescSetOfClass;



/*
 *  Procedure signatures.
 */

typedef ITS_BOOLEAN     (*ASN_DescSetOf_IsClauseSizeProc)(const ASN_DescSetOf object);
typedef void            (*ASN_DescSetOf_SetClauseSizeProc)(ASN_DescSetOf object);
typedef void            (*ASN_DescSetOf_SetMaxSizeProc)(ASN_DescSetOf object, size_t maxSize);
typedef size_t          (*ASN_DescSetOf_GetMaxSizeProc)(const ASN_DescSetOf object);
typedef void            (*ASN_DescSetOf_SetMinSizeProc)(ASN_DescSetOf object, size_t minSize);
typedef size_t          (*ASN_DescSetOf_GetMinSizeProc)(const ASN_DescSetOf object);
typedef ASN_DescObject  (*ASN_DescSetOf_GetElementProc)(const ASN_DescSetOf object);
typedef void            (*ASN_DescSetOf_SetElementProc)(ASN_DescSetOf object, ASN_DescObject element);
typedef ITS_BOOLEAN     (*ASN_DescSetOf_ContainsProc)(const ASN_DescSetOf object, const ASN_Tag tag);

/* ASN_DescSetOf class. */

typedef struct
{
    ASN_DescSetOf_IsClauseSizeProc     isClauseSize;
    ASN_DescSetOf_SetClauseSizeProc    setClauseSize;
    ASN_DescSetOf_SetMaxSizeProc       setMaxSize;
    ASN_DescSetOf_GetMaxSizeProc       getMaxSize;
    ASN_DescSetOf_SetMinSizeProc       setMinSize;
    ASN_DescSetOf_GetMinSizeProc       getMinSize;
    ASN_DescSetOf_GetElementProc       getElement;
    ASN_DescSetOf_SetElementProc       setElement;
    ASN_DescSetOf_ContainsProc         contains;
} ASN_DescSetOf_ClassPart;


typedef struct _ASN_DescSetOf_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescSetOf_ClassPart     asnDescSetOfClass;
} ASN_DescSetOf_ClassRec;

#define ASN_DESC_SET_OF_CLASS_IS_CLAUSE_SIZE(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.isClauseSize)

#define ASN_DESC_SET_OF_CLASS_SET_CLAUSE_SIZE(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.setClauseSize)

#define ASN_DESC_SET_OF_CLASS_SET_MAX_SIZE(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.setMaxSize)

#define ASN_DESC_SET_OF_CLASS_GET_MAX_SIZE(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.getMaxSize)

#define ASN_DESC_SET_OF_CLASS_SET_MIN_SIZE(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.setMinSize)

#define ASN_DESC_SET_OF_CLASS_GET_MIN_SIZE(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.getMinSize)

#define ASN_DESC_SET_OF_CLASS_GET_ELEMENT(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.getElement)

#define ASN_DESC_SET_OF_CLASS_SET_ELEMENT(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.setElement)

#define ASN_DESC_SET_OF_CLASS_CONTAINS(x) \
    (((ASN_DescSetOfClass)(x))->asnDescSetOfClass.contains)


/*
 *  For inheritance.
 */ 

extern ASN_DescSetOf_ClassRec itsASN_DescSetOf_ClassRec;


/* ASN_DescSetOf object. */

typedef struct _ASN_DescSetOf_ObjectPart
{
    ITS_BOOLEAN     clauseSize;
    size_t          maxSize;
    size_t          minSize;
    ASN_DescObject  element;
} ASN_DescSetOf_ObjectPart;


typedef struct _ASN_DescSetOf_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescSetOf_ObjectPart    asnDescSetOf;
} ASN_DescSetOf_ObjectRec;

#define ASN_DESC_SET_OF_CLAUSE_SIZE(x) \
    (((ASN_DescSetOf)(x))->asnDescSetOf.clauseSize)

#define ASN_DESC_SET_OF_MAX_SIZE(x) \
    (((ASN_DescSetOf)(x))->asnDescSetOf.maxSize)

#define ASN_DESC_SET_OF_MIN_SIZE(x) \
    (((ASN_DescSetOf)(x))->asnDescSetOf.minSize)

#define ASN_DESC_SET_OF_ELEMENT(x) \
    (((ASN_DescSetOf)(x))->asnDescSetOf.element)


#define ASN_DESC_SET_OF_CLASS_NAME "ASN_DescSetOf"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescSetOf ASN_DescSetOf_ConstructDefault();
void ASN_DescSetOf_Destruct(ASN_DescSetOf object);
ASN_Object ASN_DescSetOf_Factory(const ASN_DescSetOf object);
void ASN_DescSetOf_SetCloneForFactory(ASN_DescSetOf object, ASN_SetOf clone);
ASN_Object ASN_DescSetOf_DefaultFactory(const ASN_DescSetOf object);
void ASN_DescSetOf_SetCloneForDefaultFactory(ASN_DescSetOf object, ASN_SetOf clone);
ITS_BOOLEAN ASN_DescSetOf_IsClauseOptional(const ASN_DescSetOf object);
ITS_BOOLEAN ASN_DescSetOf_IsClauseDefault(const ASN_DescSetOf object);
ITS_BOOLEAN ASN_DescSetOf_IsClauseAnyTag(const ASN_DescSetOf object);
void ASN_DescSetOf_SetClauseOptional(ASN_DescSetOf object);
void ASN_DescSetOf_SetClauseDefault(ASN_DescSetOf object);
void ASN_DescSetOf_SetClauseAnyTag(ASN_DescSetOf object);
ITS_BOOLEAN ASN_DescSetOf_TagIdentify(const ASN_DescSetOf object, const ASN_Tag tag);
const ASN_Tag ASN_DescSetOf_TagIdentity(const ASN_DescSetOf object);
void ASN_DescSetOf_TagAddLevel(ASN_DescSetOf object, ASN_Tag tag);
size_t ASN_DescSetOf_TagLevelNumber(const ASN_DescSetOf object);
ASN_LinkedList ASN_DescSetOf_TagStack(ASN_DescSetOf object);
const char* ASN_DescSetOf_GetName(const ASN_DescSetOf object);
const char* ASN_DescSetOf_GetBaseName(const ASN_DescSetOf object);
ITS_BOOLEAN ASN_DescSetOf_IsClauseSize(const ASN_DescSetOf object);
void ASN_DescSetOf_SetClauseSize(ASN_DescSetOf object);
void ASN_DescSetOf_SetMaxSize(ASN_DescSetOf object, size_t maxSize);
size_t ASN_DescSetOf_GetMaxSize(const ASN_DescSetOf object);
void ASN_DescSetOf_SetMinSize(ASN_DescSetOf object, size_t minSize);
size_t ASN_DescSetOf_GetMinSize(const ASN_DescSetOf object);
ASN_DescObject ASN_DescSetOf_GetElement(const ASN_DescSetOf object);
void ASN_DescSetOf_SetElement(ASN_DescSetOf object, ASN_DescObject element);
ITS_BOOLEAN ASN_DescSetOf_Contains(const ASN_DescSetOf object, const ASN_Tag tag);


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_SET_OF_H_) */


