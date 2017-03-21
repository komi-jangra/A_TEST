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
 *  ID: $Id: asn_desc_object_identifier.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescObjectIdentifier interface.
 */

#if !defined(_C_ASN_DESC_OBJECT_IDENTIFIER_H_)
#define _C_ASN_DESC_OBJECT_IDENTIFIER_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_ObjectIdentifier_ObjectRec*      ASN_ObjectIdentifier;
typedef struct _ASN_DescObjectIdentifier_ObjectRec*  ASN_DescObjectIdentifier;
typedef struct _ASN_DescObjectIdentifier_ClassRec*   ASN_DescObjectIdentifierClass;



/*
 *  Procedure signatures.
 */

/*
 *  No procedures.
 */


/* ASN_DescObjectIdentifier class. */

/*
 *  No ASN_DescObjectIdentifier_ClassPart.
 */ 

typedef struct _ASN_DescObjectIdentifier_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
} ASN_DescObjectIdentifier_ClassRec;


/*
 *  For inheritance.
 */ 

extern ASN_DescObjectIdentifier_ClassRec itsASN_DescObjectIdentifier_ClassRec;


/* ASN_DescObjectIdentifier object. */

/*
 *  No ASN_DescObjectIdentifier_ObjectPart.
 */

typedef struct _ASN_DescObjectIdentifier_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
} ASN_DescObjectIdentifier_ObjectRec;

#define ASN_DESC_OBJECT_IDENTIFIER_CLASS_NAME "ASN_DescObjectIdentifier"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescObjectIdentifier ASN_DescObjectIdentifier_ConstructDefault();
void ASN_DescObjectIdentifier_Destruct(ASN_DescObjectIdentifier object);
ASN_Object ASN_DescObjectIdentifier_Factory(const ASN_DescObjectIdentifier object);
void ASN_DescObjectIdentifier_SetCloneForFactory(ASN_DescObjectIdentifier object, ASN_ObjectIdentifier clone);
ASN_Object ASN_DescObjectIdentifier_DefaultFactory(const ASN_DescObjectIdentifier object);
void ASN_DescObjectIdentifier_SetCloneForDefaultFactory(ASN_DescObjectIdentifier object, ASN_ObjectIdentifier clone);
ITS_BOOLEAN ASN_DescObjectIdentifier_IsClauseOptional(const ASN_DescObjectIdentifier object);
ITS_BOOLEAN ASN_DescObjectIdentifier_IsClauseDefault(const ASN_DescObjectIdentifier object);
ITS_BOOLEAN ASN_DescObjectIdentifier_IsClauseAnyTag(const ASN_DescObjectIdentifier object);
void ASN_DescObjectIdentifier_SetClauseOptional(ASN_DescObjectIdentifier object);
void ASN_DescObjectIdentifier_SetClauseDefault(ASN_DescObjectIdentifier object);
void ASN_DescObjectIdentifier_SetClauseAnyTag(ASN_DescObjectIdentifier object);
ITS_BOOLEAN ASN_DescObjectIdentifier_TagIdentify(const ASN_DescObjectIdentifier object, const ASN_Tag tag);
const ASN_Tag ASN_DescObjectIdentifier_TagIdentity(const ASN_DescObjectIdentifier object);
void ASN_DescObjectIdentifier_TagAddLevel(ASN_DescObjectIdentifier object, ASN_Tag tag);
size_t ASN_DescObjectIdentifier_TagLevelNumber(const ASN_DescObjectIdentifier object);
ASN_LinkedList ASN_DescObjectIdentifier_TagStack(ASN_DescObjectIdentifier object);
const char* ASN_DescObjectIdentifier_GetName(const ASN_DescObjectIdentifier object);
const char* ASN_DescObjectIdentifier_GetBaseName(const ASN_DescObjectIdentifier object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_OBJECT_IDENTIFIER_H_) */


