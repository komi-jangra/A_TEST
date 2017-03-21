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
 *  ID: $Id: asn_desc_null.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescNull interface.
 */

#if !defined(_C_ASN_DESC_NULL_H_)
#define _C_ASN_DESC_NULL_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Null_ObjectRec*      ASN_Null;
typedef struct _ASN_DescNull_ObjectRec*  ASN_DescNull;
typedef struct _ASN_DescNull_ClassRec*   ASN_DescNullClass;



/*
 *  Procedure signatures.
 */

/*
 *  No procedures.
 */


/* ASN_DescNull class. */

/*
 *  No ASN_DescNull_ClassPart.
 */ 

typedef struct _ASN_DescNull_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
} ASN_DescNull_ClassRec;


/*
 *  For inheritance.
 */ 

extern ASN_DescNull_ClassRec itsASN_DescNull_ClassRec;


/* ASN_DescNull object. */

/*
 *  No ASN_DescNull_ObjectPart.
 */

typedef struct _ASN_DescNull_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
} ASN_DescNull_ObjectRec;

#define ASN_DESC_NULL_CLASS_NAME "ASN_DescNull"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescNull ASN_DescNull_ConstructDefault();
void ASN_DescNull_Destruct(ASN_DescNull object);
ASN_Object ASN_DescNull_Factory(const ASN_DescNull object);
void ASN_DescNull_SetCloneForFactory(ASN_DescNull object, ASN_Null clone);
ASN_Object ASN_DescNull_DefaultFactory(const ASN_DescNull object);
void ASN_DescNull_SetCloneForDefaultFactory(ASN_DescNull object, ASN_Null clone);
ITS_BOOLEAN ASN_DescNull_IsClauseOptional(const ASN_DescNull object);
ITS_BOOLEAN ASN_DescNull_IsClauseDefault(const ASN_DescNull object);
ITS_BOOLEAN ASN_DescNull_IsClauseAnyTag(const ASN_DescNull object);
void ASN_DescNull_SetClauseOptional(ASN_DescNull object);
void ASN_DescNull_SetClauseDefault(ASN_DescNull object);
void ASN_DescNull_SetClauseAnyTag(ASN_DescNull object);
ITS_BOOLEAN ASN_DescNull_TagIdentify(const ASN_DescNull object, const ASN_Tag tag);
const ASN_Tag ASN_DescNull_TagIdentity(const ASN_DescNull object);
void ASN_DescNull_TagAddLevel(ASN_DescNull object, ASN_Tag tag);
size_t ASN_DescNull_TagLevelNumber(const ASN_DescNull object);
ASN_LinkedList ASN_DescNull_TagStack(ASN_DescNull object);
const char* ASN_DescNull_GetName(const ASN_DescNull object);
const char* ASN_DescNull_GetBaseName(const ASN_DescNull object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_NULL_H_) */


