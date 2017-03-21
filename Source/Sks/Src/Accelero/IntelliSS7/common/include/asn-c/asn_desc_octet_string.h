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
 *  ID: $Id: asn_desc_octet_string.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescOctetString interface.
 */

#if !defined(_C_ASN_DESC_OCTET_STRING_H_)
#define _C_ASN_DESC_OCTET_STRING_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_OctetString_ObjectRec*      ASN_OctetString;
typedef struct _ASN_DescOctetString_ObjectRec*  ASN_DescOctetString;
typedef struct _ASN_DescOctetString_ClassRec*   ASN_DescOctetStringClass;



/*
 *  Procedure signatures.
 */

typedef ITS_BOOLEAN     (*ASN_DescOctetString_IsClauseSizeProc)(const ASN_DescOctetString object);
typedef void            (*ASN_DescOctetString_SetClauseSizeProc)(ASN_DescOctetString object);
typedef void            (*ASN_DescOctetString_SetMaxSizeProc)(ASN_DescOctetString object, size_t maxSize);
typedef size_t          (*ASN_DescOctetString_GetMaxSizeProc)(const ASN_DescOctetString object);
typedef void            (*ASN_DescOctetString_SetMinSizeProc)(ASN_DescOctetString object, size_t minSize);
typedef size_t          (*ASN_DescOctetString_GetMinSizeProc)(const ASN_DescOctetString object);

/* ASN_DescOctetString class. */

typedef struct
{
    ASN_DescOctetString_IsClauseSizeProc        isClauseSize;
    ASN_DescOctetString_SetClauseSizeProc       setClauseSize;
    ASN_DescOctetString_SetMaxSizeProc          setMaxSize;
    ASN_DescOctetString_GetMaxSizeProc          getMaxSize;
    ASN_DescOctetString_SetMinSizeProc          setMinSize;
    ASN_DescOctetString_GetMinSizeProc          getMinSize;
} ASN_DescOctetString_ClassPart;


typedef struct _ASN_DescOctetString_ClassRec
{
    ITS_CoreClassPart               coreClass;
    ASN_DescObject_ClassPart        asnDescObjectClass;
    ASN_DescOctetString_ClassPart   asnDescOctetStringClass;
} ASN_DescOctetString_ClassRec;

#define ASN_DESC_OCTET_STRING_CLASS_IS_CLAUSE_SIZE(x) \
    (((ASN_DescOctetStringClass)(x))->asnDescOctetStringClass.isClauseSize)

#define ASN_DESC_OCTET_STRING_CLASS_SET_CLAUSE_SIZE(x) \
    (((ASN_DescOctetStringClass)(x))->asnDescOctetStringClass.setClauseSize)

#define ASN_DESC_OCTET_STRING_CLASS_SET_MAX_SIZE(x) \
    (((ASN_DescOctetStringClass)(x))->asnDescOctetStringClass.setMaxSize)

#define ASN_DESC_OCTET_STRING_CLASS_GET_MAX_SIZE(x) \
    (((ASN_DescOctetStringClass)(x))->asnDescOctetStringClass.getMaxSize)

#define ASN_DESC_OCTET_STRING_CLASS_SET_MIN_SIZE(x) \
    (((ASN_DescOctetStringClass)(x))->asnDescOctetStringClass.setMinSize)

#define ASN_DESC_OCTET_STRING_CLASS_GET_MIN_SIZE(x) \
    (((ASN_DescOctetStringClass)(x))->asnDescOctetStringClass.getMinSize)


/*
 *  For inheritance.
 */ 

extern ASN_DescOctetString_ClassRec itsASN_DescOctetString_ClassRec;


/* ASN_DescOctetString object. */

typedef struct _ASN_DescOctetString_ObjectPart
{
    ITS_BOOLEAN clauseSize;
    size_t      maxSize;
    size_t      minSize;
} ASN_DescOctetString_ObjectPart;


typedef struct _ASN_DescOctetString_ObjectRec
{
    ITS_CoreObjectPart              core;
    ASN_DescObject_ObjectPart       asnDescObject;
    ASN_DescOctetString_ObjectPart  asnDescOctetString;
} ASN_DescOctetString_ObjectRec;

#define ASN_DESC_OCTET_STRING_CLAUSE_SIZE(x) \
    (((ASN_DescOctetString)(x))->asnDescOctetString.clauseSize)

#define ASN_DESC_OCTET_STRING_MAX_SIZE(x) \
    (((ASN_DescOctetString)(x))->asnDescOctetString.maxSize)

#define ASN_DESC_OCTET_STRING_MIN_SIZE(x) \
    (((ASN_DescOctetString)(x))->asnDescOctetString.minSize)


#define ASN_DESC_OCTET_STRING_CLASS_NAME "ASN_DescOctetString"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescOctetString ASN_DescOctetString_ConstructDefault();
void ASN_DescOctetString_Destruct(ASN_DescOctetString object);
ASN_Object ASN_DescOctetString_Factory(const ASN_DescOctetString object);
void ASN_DescOctetString_SetCloneForFactory(ASN_DescOctetString object, ASN_OctetString clone);
ASN_Object ASN_DescOctetString_DefaultFactory(const ASN_DescOctetString object);
void ASN_DescOctetString_SetCloneForDefaultFactory(ASN_DescOctetString object, ASN_OctetString clone);
ITS_BOOLEAN ASN_DescOctetString_IsClauseOptional(const ASN_DescOctetString object);
ITS_BOOLEAN ASN_DescOctetString_IsClauseDefault(const ASN_DescOctetString object);
ITS_BOOLEAN ASN_DescOctetString_IsClauseAnyTag(const ASN_DescOctetString object);
void ASN_DescOctetString_SetClauseOptional(ASN_DescOctetString object);
void ASN_DescOctetString_SetClauseDefault(ASN_DescOctetString object);
void ASN_DescOctetString_SetClauseAnyTag(ASN_DescOctetString object);
ITS_BOOLEAN ASN_DescOctetString_TagIdentify(const ASN_DescOctetString object, const ASN_Tag tag);
const ASN_Tag ASN_DescOctetString_TagIdentity(const ASN_DescOctetString object);
void ASN_DescOctetString_TagAddLevel(ASN_DescOctetString object, ASN_Tag tag);
size_t ASN_DescOctetString_TagLevelNumber(const ASN_DescOctetString object);
ASN_LinkedList ASN_DescOctetString_TagStack(ASN_DescOctetString object);
const char* ASN_DescOctetString_GetName(const ASN_DescOctetString object);
const char* ASN_DescOctetString_GetBaseName(const ASN_DescOctetString object);
ITS_BOOLEAN ASN_DescOctetString_IsClauseSize(const ASN_DescOctetString object);
void ASN_DescOctetString_SetClauseSize(ASN_DescOctetString object);
void ASN_DescOctetString_SetMaxSize(ASN_DescOctetString object, size_t maxSize);
size_t ASN_DescOctetString_GetMaxSize(const ASN_DescOctetString object);
void ASN_DescOctetString_SetMinSize(ASN_DescOctetString object, size_t minSize);
size_t ASN_DescOctetString_GetMinSize(const ASN_DescOctetString object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_OCTET_STRING_H_) */


