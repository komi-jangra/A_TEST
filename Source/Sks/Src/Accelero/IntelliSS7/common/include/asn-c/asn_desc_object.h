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
 *  ID: $Id: asn_desc_object.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescObject interface.
 */

#if !defined(_C_ASN_DESC_OBJECT_H_)
#define _C_ASN_DESC_OBJECT_H_

#include <its.h>
#include <its_object.h>

#include <asn_common.h>
#include <asn_tag.h>
#include <asn_assertion.h>
#include <asn_linked_list.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Object_ObjectRec*       ASN_Object;
typedef struct _ASN_DescObject_ObjectRec*   ASN_DescObject;
typedef struct _ASN_DescObject_ClassRec*    ASN_DescObjectClass;



/*
 *  Procedure signatures.
 */

typedef ASN_Object      (*ASN_DescObject_FactoryProc)(const ASN_DescObject object);
typedef void            (*ASN_DescObject_SetCloneForFactoryProc)(ASN_DescObject object, ASN_Object clone);
typedef ASN_Object      (*ASN_DescObject_DefaultFactoryProc)(const ASN_DescObject object);
typedef void            (*ASN_DescObject_SetCloneForDefaultFactoryProc)(ASN_DescObject object, ASN_Object clone);
typedef ITS_BOOLEAN     (*ASN_DescObject_IsClauseOptionalProc)(const ASN_DescObject object);
typedef ITS_BOOLEAN     (*ASN_DescObject_IsClauseDefaultProc)(const ASN_DescObject object);
typedef ITS_BOOLEAN     (*ASN_DescObject_IsClauseAnyTagProc)(const ASN_DescObject object);
typedef void            (*ASN_DescObject_SetClauseOptionalProc)(ASN_DescObject object);
typedef void            (*ASN_DescObject_SetClauseDefaultProc)(ASN_DescObject object);
typedef void            (*ASN_DescObject_SetClauseAnyTagProc)(ASN_DescObject object);
typedef ITS_BOOLEAN     (*ASN_DescObject_TagIdentifyProc)(const ASN_DescObject object, const ASN_Tag tag);
typedef const ASN_Tag   (*ASN_DescObject_TagIdentityProc)(const ASN_DescObject object);
typedef void            (*ASN_DescObject_TagAddLevelProc)(ASN_DescObject object, ASN_Tag tag);
typedef size_t          (*ASN_DescObject_TagLevelNumberProc)(const ASN_DescObject object);
typedef ASN_LinkedList  (*ASN_DescObject_TagStackProc)(ASN_DescObject object);
typedef const char*     (*ASN_DescObject_GetNameProc)(const ASN_DescObject object);
typedef const char*     (*ASN_DescObject_GetBaseNameProc)(const ASN_DescObject object);


/*
 *  Procedure overrides.
 */

#define ASN_DESC_OBJECT_FACTORY_INHERIT                         (ASN_DescObject_FactoryProc)NULL
#define ASN_DESC_OBJECT_SET_CLONE_FOR_FACTORY_INHERIT           (ASN_DescObject_SetCloneForFactoryProc)NULL
#define ASN_DESC_OBJECT_DEFAULT_FACTORY_INHERIT                 (ASN_DescObject_DefaultFactoryProc)NULL
#define ASN_DESC_OBJECT_SET_CLONE_FOR_DEFAULT_FACTORY_INHERIT   (ASN_DescObject_SetCloneForDefaultFactoryProc)NULL
#define ASN_DESC_OBJECT_IS_CLAUSE_OPTIONAL_INHERIT              (ASN_DescObject_IsClauseOptionalProc)NULL
#define ASN_DESC_OBJECT_IS_CLAUSE_DEFAULT_INHERIT               (ASN_DescObject_IsClauseDefaultProc)NULL
#define ASN_DESC_OBJECT_IS_CLAUSE_ANY_TAG_INHERIT               (ASN_DescObject_IsClauseAnyTagProc)NULL
#define ASN_DESC_OBJECT_SET_CLAUSE_OPTIONAL_INHERIT             (ASN_DescObject_SetClauseOptionalProc)NULL
#define ASN_DESC_OBJECT_SET_CLAUSE_DEFAULT_INHERIT              (ASN_DescObject_SetClauseDefaultProc)NULL
#define ASN_DESC_OBJECT_SET_CLAUSE_ANY_TAG_INHERIT              (ASN_DescObject_SetClauseAnyTagProc)NULL
#define ASN_DESC_OBJECT_TAG_IDENTIFY_INHERIT                    (ASN_DescObject_TagIdentifyProc)NULL
#define ASN_DESC_OBJECT_TAG_IDENTITY_INHERIT                    (ASN_DescObject_TagIdentityProc)NULL
#define ASN_DESC_OBJECT_TAG_ADD_LEVEL_INHERIT                   (ASN_DescObject_TagAddLevelProc)NULL
#define ASN_DESC_OBJECT_TAG_LEVEL_NUMBER_INHERIT                (ASN_DescObject_TagLevelNumberProc)NULL
#define ASN_DESC_OBJECT_TAG_STACK_INHERIT                       (ASN_DescObject_TagStackProc)NULL
#define ASN_DESC_OBJECT_GET_NAME_INHERIT                        (ASN_DescObject_GetNameProc)NULL
#define ASN_DESC_OBJECT_GET_BASE_NAME_INHERIT                   (ASN_DescObject_GetBaseNameProc)NULL


/* ASN_DescObject class. */

typedef struct
{
    ASN_DescObject_FactoryProc                      factory;
    ASN_DescObject_SetCloneForFactoryProc           setCloneForFactory;
    ASN_DescObject_DefaultFactoryProc               defaultFactory;
    ASN_DescObject_SetCloneForDefaultFactoryProc    setCloneForDefaultFactory;
    ASN_DescObject_IsClauseOptionalProc             isClauseOptional;
    ASN_DescObject_IsClauseDefaultProc              isClauseDefault;
    ASN_DescObject_IsClauseAnyTagProc               isClauseAnyTag;
    ASN_DescObject_SetClauseOptionalProc            setClauseOptional;
    ASN_DescObject_SetClauseDefaultProc             setClauseDefault;
    ASN_DescObject_SetClauseAnyTagProc              setClauseAnyTag;
    ASN_DescObject_TagIdentifyProc                  tagIdentify;
    ASN_DescObject_TagIdentityProc                  tagIdentity;
    ASN_DescObject_TagAddLevelProc                  tagAddLevel;
    ASN_DescObject_TagLevelNumberProc               tagLevelNumber;
    ASN_DescObject_TagStackProc                     tagStack;
    ASN_DescObject_GetNameProc                      getName;
    ASN_DescObject_GetBaseNameProc                  getBaseName;
} ASN_DescObject_ClassPart;


typedef struct _ASN_DescObject_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
} ASN_DescObject_ClassRec;

#define ASN_DESC_OBJECT_CLASS_FACTORY(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.factory)

#define ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.setCloneForFactory)

#define ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.defaultFactory)

#define ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.setCloneForDefaultFactory)

#define ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.isClauseOptional)

#define ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.isClauseDefault)

#define ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.isClauseAnyTag)

#define ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.setClauseOptional)

#define ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.setClauseDefault)

#define ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.setClauseAnyTag)

#define ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.tagIdentify)

#define ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.tagIdentity)

#define ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.tagAddLevel)

#define ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.tagLevelNumber)

#define ASN_DESC_OBJECT_CLASS_TAG_STACK(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.tagStack)

#define ASN_DESC_OBJECT_CLASS_GET_NAME(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.getName)

#define ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(x) \
    (((ASN_DescObjectClass)(x))->asnDescObjectClass.getBaseName)


/*
 *  For inheritance.
 */ 

extern ASN_DescObject_ClassRec itsASN_DescObject_ClassRec;


/* ASN_DescObject object. */

typedef struct _ASN_DescObject_ObjectPart
{
    ITS_BOOLEAN     clauseOptional;
    ITS_BOOLEAN     clauseDefault;
    ITS_BOOLEAN     clauseAnyTag;
    ASN_LinkedList  tagStack;
    ASN_Object      cloneForFactory;
    ASN_Object      cloneForDefaultFactory;
} ASN_DescObject_ObjectPart;


typedef struct _ASN_DescObject_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
} ASN_DescObject_ObjectRec;

#define ASN_DESC_OBJECT_CLAUSE_OPTIONAL(x) \
    (((ASN_DescObject)(x))->asnDescObject.clauseOptional)

#define ASN_DESC_OBJECT_CLAUSE_DEFAULT(x) \
    (((ASN_DescObject)(x))->asnDescObject.clauseDefault)

#define ASN_DESC_OBJECT_CLAUSE_ANY_TAG(x) \
    (((ASN_DescObject)(x))->asnDescObject.clauseAnyTag)

#define ASN_DESC_OBJECT_TAG_STACK(x) \
    (((ASN_DescObject)(x))->asnDescObject.tagStack)

#define ASN_DESC_OBJECT_CLONE_FOR_FACTORY(x) \
    (((ASN_DescObject)(x))->asnDescObject.cloneForFactory)

#define ASN_DESC_OBJECT_CLONE_FOR_DEFAULT_FACTORY(x) \
    (((ASN_DescObject)(x))->asnDescObject.cloneForDefaultFactory)


#define ASN_DESC_OBJECT_CLASS_NAME "ASN_DescObject"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

void ASN_DescObject_Destruct(ASN_DescObject object);
ASN_Object ASN_DescObject_Factory(const ASN_DescObject object);
void ASN_DescObject_SetCloneForFactory(ASN_DescObject object, ASN_Object clone);
ASN_Object ASN_DescObject_DefaultFactory(const ASN_DescObject object);
void ASN_DescObject_SetCloneForDefaultFactory(ASN_DescObject object, ASN_Object clone);
ITS_BOOLEAN ASN_DescObject_IsClauseOptional(const ASN_DescObject object);
ITS_BOOLEAN ASN_DescObject_IsClauseDefault(const ASN_DescObject object);
ITS_BOOLEAN ASN_DescObject_IsClauseAnyTag(const ASN_DescObject object);
void ASN_DescObject_SetClauseOptional(ASN_DescObject object);
void ASN_DescObject_SetClauseDefault(ASN_DescObject object);
void ASN_DescObject_SetClauseAnyTag(ASN_DescObject object);
ITS_BOOLEAN ASN_DescObject_TagIdentify(const ASN_DescObject object, const ASN_Tag tag);
const ASN_Tag ASN_DescObject_TagIdentity(const ASN_DescObject object);
void ASN_DescObject_TagAddLevel(ASN_DescObject object, ASN_Tag tag);
size_t ASN_DescObject_TagLevelNumber(const ASN_DescObject object);
ASN_LinkedList ASN_DescObject_TagStack(ASN_DescObject object);
const char* ASN_DescObject_GetName(const ASN_DescObject object);
const char* ASN_DescObject_GetBaseName(const ASN_DescObject object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_OBJECT_H_) */

