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
 *  ID: $Id: asn_desc_bit_string.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescBitString interface.
 */

#if !defined(_C_ASN_DESC_BIT_STRING_H_)
#define _C_ASN_DESC_BIT_STRING_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_BitString_ObjectRec*      ASN_BitString;
typedef struct _ASN_DescBitString_ObjectRec*  ASN_DescBitString;
typedef struct _ASN_DescBitString_ClassRec*   ASN_DescBitStringClass;



/*
 *  Procedure signatures.
 */

typedef ITS_BOOLEAN     (*ASN_DescBitString_IsClauseSizeProc)(const ASN_DescBitString object);
typedef void            (*ASN_DescBitString_SetClauseSizeProc)(ASN_DescBitString object);
typedef void            (*ASN_DescBitString_SetMaxSizeProc)(ASN_DescBitString object, size_t maxSize);
typedef size_t          (*ASN_DescBitString_GetMaxSizeProc)(const ASN_DescBitString object);
typedef void            (*ASN_DescBitString_SetMinSizeProc)(ASN_DescBitString object, size_t minSize);
typedef size_t          (*ASN_DescBitString_GetMinSizeProc)(const ASN_DescBitString object);

/* ASN_DescBitString class. */

typedef struct
{
    ASN_DescBitString_IsClauseSizeProc        isClauseSize;
    ASN_DescBitString_SetClauseSizeProc       setClauseSize;
    ASN_DescBitString_SetMaxSizeProc          setMaxSize;
    ASN_DescBitString_GetMaxSizeProc          getMaxSize;
    ASN_DescBitString_SetMinSizeProc          setMinSize;
    ASN_DescBitString_GetMinSizeProc          getMinSize;
} ASN_DescBitString_ClassPart;


typedef struct _ASN_DescBitString_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescBitString_ClassPart asnDescBitStringClass;
} ASN_DescBitString_ClassRec;

#define ASN_DESC_BIT_STRING_CLASS_IS_CLAUSE_SIZE(x) \
    (((ASN_DescBitStringClass)(x))->asnDescBitStringClass.isClauseSize)

#define ASN_DESC_BIT_STRING_CLASS_SET_CLAUSE_SIZE(x) \
    (((ASN_DescBitStringClass)(x))->asnDescBitStringClass.setClauseSize)

#define ASN_DESC_BIT_STRING_CLASS_SET_MAX_SIZE(x) \
    (((ASN_DescBitStringClass)(x))->asnDescBitStringClass.setMaxSize)

#define ASN_DESC_BIT_STRING_CLASS_GET_MAX_SIZE(x) \
    (((ASN_DescBitStringClass)(x))->asnDescBitStringClass.getMaxSize)

#define ASN_DESC_BIT_STRING_CLASS_SET_MIN_SIZE(x) \
    (((ASN_DescBitStringClass)(x))->asnDescBitStringClass.setMinSize)

#define ASN_DESC_BIT_STRING_CLASS_GET_MIN_SIZE(x) \
    (((ASN_DescBitStringClass)(x))->asnDescBitStringClass.getMinSize)


/*
 *  For inheritance.
 */ 

extern ASN_DescBitString_ClassRec itsASN_DescBitString_ClassRec;


/* ASN_DescBitString object. */

typedef struct _ASN_DescBitString_ObjectPart
{
    ITS_BOOLEAN clauseSize;
    size_t      maxSize;
    size_t      minSize;
} ASN_DescBitString_ObjectPart;


typedef struct _ASN_DescBitString_ObjectRec
{
    ITS_CoreObjectPart              core;
    ASN_DescObject_ObjectPart       asnDescObject;
    ASN_DescBitString_ObjectPart    asnDescBitString;
} ASN_DescBitString_ObjectRec;

#define ASN_DESC_BIT_STRING_CLAUSE_SIZE(x) \
    (((ASN_DescBitString)(x))->asnDescBitString.clauseSize)

#define ASN_DESC_BIT_STRING_MAX_SIZE(x) \
    (((ASN_DescBitString)(x))->asnDescBitString.maxSize)

#define ASN_DESC_BIT_STRING_MIN_SIZE(x) \
    (((ASN_DescBitString)(x))->asnDescBitString.minSize)


#define ASN_DESC_BIT_STRING_CLASS_NAME "ASN_DescBitString"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescBitString ASN_DescBitString_ConstructDefault();
void ASN_DescBitString_Destruct(ASN_DescBitString object);
ASN_Object ASN_DescBitString_Factory(const ASN_DescBitString object);
void ASN_DescBitString_SetCloneForFactory(ASN_DescBitString object, ASN_BitString clone);
ASN_Object ASN_DescBitString_DefaultFactory(const ASN_DescBitString object);
void ASN_DescBitString_SetCloneForDefaultFactory(ASN_DescBitString object, ASN_BitString clone);
ITS_BOOLEAN ASN_DescBitString_IsClauseOptional(const ASN_DescBitString object);
ITS_BOOLEAN ASN_DescBitString_IsClauseDefault(const ASN_DescBitString object);
ITS_BOOLEAN ASN_DescBitString_IsClauseAnyTag(const ASN_DescBitString object);
void ASN_DescBitString_SetClauseOptional(ASN_DescBitString object);
void ASN_DescBitString_SetClauseDefault(ASN_DescBitString object);
void ASN_DescBitString_SetClauseAnyTag(ASN_DescBitString object);
ITS_BOOLEAN ASN_DescBitString_TagIdentify(const ASN_DescBitString object, const ASN_Tag tag);
const ASN_Tag ASN_DescBitString_TagIdentity(const ASN_DescBitString object);
void ASN_DescBitString_TagAddLevel(ASN_DescBitString object, ASN_Tag tag);
size_t ASN_DescBitString_TagLevelNumber(const ASN_DescBitString object);
ASN_LinkedList ASN_DescBitString_TagStack(ASN_DescBitString object);
const char* ASN_DescBitString_GetName(const ASN_DescBitString object);
const char* ASN_DescBitString_GetBaseName(const ASN_DescBitString object);
ITS_BOOLEAN ASN_DescBitString_IsClauseSize(const ASN_DescBitString object);
void ASN_DescBitString_SetClauseSize(ASN_DescBitString object);
void ASN_DescBitString_SetMaxSize(ASN_DescBitString object, size_t maxSize);
size_t ASN_DescBitString_GetMaxSize(const ASN_DescBitString object);
void ASN_DescBitString_SetMinSize(ASN_DescBitString object, size_t minSize);
size_t ASN_DescBitString_GetMinSize(const ASN_DescBitString object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_BIT_STRING_H_) */


