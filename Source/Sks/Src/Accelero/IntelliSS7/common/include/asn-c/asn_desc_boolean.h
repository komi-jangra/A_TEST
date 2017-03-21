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
 *  ID: $Id: asn_desc_boolean.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescBoolean interface.
 */

#if !defined(_C_ASN_DESC_BOOLEAN_H_)
#define _C_ASN_DESC_BOOLEAN_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Boolean_ObjectRec*      ASN_Boolean;
typedef struct _ASN_DescBoolean_ObjectRec*  ASN_DescBoolean;
typedef struct _ASN_DescBoolean_ClassRec*   ASN_DescBooleanClass;



/*
 *  Procedure signatures.
 */

typedef void        (*ASN_DescBoolean_SetDefaultValueProc)(ASN_DescBoolean object, ITS_BOOLEAN defaultValue);
typedef ITS_BOOLEAN (*ASN_DescBoolean_GetDefaultValueProc)(const ASN_DescBoolean object);

/* ASN_DescBoolean class. */

typedef struct
{
    ASN_DescBoolean_SetDefaultValueProc setDefaultValue;
    ASN_DescBoolean_GetDefaultValueProc getDefaultValue;
} ASN_DescBoolean_ClassPart;


typedef struct _ASN_DescBoolean_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescBoolean_ClassPart   asnDescBooleanClass;
} ASN_DescBoolean_ClassRec;


#define ASN_DESC_BOOLEAN_CLASS_SET_DEFAULT_VALUE(x) \
    (((ASN_DescBooleanClass)(x))->asnDescBooleanClass.setDefaultValue)

#define ASN_DESC_BOOLEAN_CLASS_GET_DEFAULT_VALUE(x) \
    (((ASN_DescBooleanClass)(x))->asnDescBooleanClass.getDefaultValue)


/*
 *  For inheritance.
 */ 

extern ASN_DescBoolean_ClassRec itsASN_DescBoolean_ClassRec;


/* ASN_DescBoolean object. */

typedef struct _ASN_DescBoolean_ObjectPart
{
    ITS_BOOLEAN defaultValue;
} ASN_DescBoolean_ObjectPart;


typedef struct _ASN_DescBoolean_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescBoolean_ObjectPart  asnDescBoolean;
} ASN_DescBoolean_ObjectRec;


#define ASN_DESC_BOOLEAN_DEFAULT_VALUE(x) \
    (((ASN_DescBoolean)(x))->asnDescBoolean.defaultValue)


#define ASN_DESC_BOOLEAN_CLASS_NAME "ASN_DescBoolean"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescBoolean ASN_DescBoolean_ConstructDefault();
void ASN_DescBoolean_Destruct(ASN_DescBoolean object);
ASN_Object ASN_DescBoolean_Factory(const ASN_DescBoolean object);
void ASN_DescBoolean_SetCloneForFactory(ASN_DescBoolean object, ASN_Boolean clone);
ASN_Object ASN_DescBoolean_DefaultFactory(const ASN_DescBoolean object);
void ASN_DescBoolean_SetCloneForDefaultFactory(ASN_DescBoolean object, ASN_Boolean clone);
ITS_BOOLEAN ASN_DescBoolean_IsClauseOptional(const ASN_DescBoolean object);
ITS_BOOLEAN ASN_DescBoolean_IsClauseDefault(const ASN_DescBoolean object);
ITS_BOOLEAN ASN_DescBoolean_IsClauseAnyTag(const ASN_DescBoolean object);
void ASN_DescBoolean_SetClauseOptional(ASN_DescBoolean object);
void ASN_DescBoolean_SetClauseDefault(ASN_DescBoolean object);
void ASN_DescBoolean_SetClauseAnyTag(ASN_DescBoolean object);
ITS_BOOLEAN ASN_DescBoolean_TagIdentify(const ASN_DescBoolean object, const ASN_Tag tag);
const ASN_Tag ASN_DescBoolean_TagIdentity(const ASN_DescBoolean object);
void ASN_DescBoolean_TagAddLevel(ASN_DescBoolean object, ASN_Tag tag);
size_t ASN_DescBoolean_TagLevelNumber(const ASN_DescBoolean object);
ASN_LinkedList ASN_DescBoolean_TagStack(ASN_DescBoolean object);
const char* ASN_DescBoolean_GetName(const ASN_DescBoolean object);
const char* ASN_DescBoolean_GetBaseName(const ASN_DescBoolean object);
void ASN_DescBoolean_SetDefaultValue(ASN_DescBoolean object, ITS_BOOLEAN defaultValue);
ITS_BOOLEAN ASN_DescBoolean_GetDefaultValue(const ASN_DescBoolean object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_BOOLEAN_H_) */


