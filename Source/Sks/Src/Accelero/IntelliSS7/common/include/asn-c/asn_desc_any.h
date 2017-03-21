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
 *  ID: $Id: asn_desc_any.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescAny interface.
 */

#if !defined(_C_ASN_DESC_ANY_H_)
#define _C_ASN_DESC_ANY_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Any_ObjectRec*      ASN_Any;
typedef struct _ASN_DescAny_ObjectRec*  ASN_DescAny;
typedef struct _ASN_DescAny_ClassRec*   ASN_DescAnyClass;



/*
 *  Procedure signatures.
 */

/*
 *  No procedures.
 */


/* ASN_DescAny class. */

/*
 *  No ASN_DescAny_ClassPart.
 */ 

typedef struct _ASN_DescAny_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
} ASN_DescAny_ClassRec;


/*
 *  For inheritance.
 */ 

extern ASN_DescAny_ClassRec itsASN_DescAny_ClassRec;


/* ASN_DescAny object. */

/*
 *  No ASN_DescAny_ObjectPart.
 */

typedef struct _ASN_DescAny_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
} ASN_DescAny_ObjectRec;

#define ASN_DESC_ANY_CLASS_NAME "ASN_DescAny"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescAny ASN_DescAny_ConstructDefault();
void ASN_DescAny_Destruct(ASN_DescAny object);
ASN_Object ASN_DescAny_Factory(const ASN_DescAny object);
void ASN_DescAny_SetCloneForFactory(ASN_DescAny object, ASN_Any clone);
ASN_Object ASN_DescAny_DefaultFactory(const ASN_DescAny object);
void ASN_DescAny_SetCloneForDefaultFactory(ASN_DescAny object, ASN_Any clone);
ITS_BOOLEAN ASN_DescAny_IsClauseOptional(const ASN_DescAny object);
ITS_BOOLEAN ASN_DescAny_IsClauseDefault(const ASN_DescAny object);
ITS_BOOLEAN ASN_DescAny_IsClauseAnyTag(const ASN_DescAny object);
void ASN_DescAny_SetClauseOptional(ASN_DescAny object);
void ASN_DescAny_SetClauseDefault(ASN_DescAny object);
void ASN_DescAny_SetClauseAnyTag(ASN_DescAny object);
ITS_BOOLEAN ASN_DescAny_TagIdentify(const ASN_DescAny object, const ASN_Tag tag);
const ASN_Tag ASN_DescAny_TagIdentity(const ASN_DescAny object);
void ASN_DescAny_TagAddLevel(ASN_DescAny object, ASN_Tag tag);
size_t ASN_DescAny_TagLevelNumber(const ASN_DescAny object);
ASN_LinkedList ASN_DescAny_TagStack(ASN_DescAny object);
const char* ASN_DescAny_GetName(const ASN_DescAny object);
const char* ASN_DescAny_GetBaseName(const ASN_DescAny object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_ANY_H_) */


