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
 *  ID: $Id: asn_desc_integer.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescInteger interface.
 */

#if !defined(_C_ASN_DESC_INTEGER_H_)
#define _C_ASN_DESC_INTEGER_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Integer_ObjectRec*      ASN_Integer;
typedef struct _ASN_DescInteger_ObjectRec*  ASN_DescInteger;
typedef struct _ASN_DescInteger_ClassRec*   ASN_DescIntegerClass;



/*
 *  Procedure signatures.
 */

typedef ITS_BOOLEAN     (*ASN_DescInteger_IsClauseRangeProc)(const ASN_DescInteger object);
typedef void            (*ASN_DescInteger_SetClauseRangeProc)(ASN_DescInteger object);
typedef void            (*ASN_DescInteger_SetMaxValueProc)(ASN_DescInteger object, ITS_LONG maxValue);
typedef ITS_LONG        (*ASN_DescInteger_GetMaxValueProc)(const ASN_DescInteger object);
typedef void            (*ASN_DescInteger_SetMinValueProc)(ASN_DescInteger object, ITS_LONG minValue);
typedef ITS_LONG        (*ASN_DescInteger_GetMinValueProc)(const ASN_DescInteger object);
typedef void            (*ASN_DescInteger_SetDefaultValueProc)(ASN_DescInteger object, ITS_LONG defaultValue);
typedef ITS_LONG        (*ASN_DescInteger_GetDefaultValueProc)(const ASN_DescInteger object);

/* ASN_DescInteger class. */

typedef struct
{
    ASN_DescInteger_IsClauseRangeProc       isClauseRange;
    ASN_DescInteger_SetClauseRangeProc      setClauseRange;
    ASN_DescInteger_SetMaxValueProc         setMaxValue;
    ASN_DescInteger_GetMaxValueProc         getMaxValue;
    ASN_DescInteger_SetMinValueProc         setMinValue;
    ASN_DescInteger_GetMinValueProc         getMinValue;
    ASN_DescInteger_SetDefaultValueProc     setDefaultValue;
    ASN_DescInteger_GetDefaultValueProc     getDefaultValue;
} ASN_DescInteger_ClassPart;


typedef struct _ASN_DescInteger_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescInteger_ClassPart   asnDescIntegerClass;
} ASN_DescInteger_ClassRec;

#define ASN_DESC_INTEGER_CLASS_IS_CLAUSE_RANGE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.isClauseRange)

#define ASN_DESC_INTEGER_CLASS_SET_CLAUSE_RANGE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.setClauseRange)

#define ASN_DESC_INTEGER_CLASS_SET_MAX_VALUE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.setMaxValue)

#define ASN_DESC_INTEGER_CLASS_GET_MAX_VALUE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.getMaxValue)

#define ASN_DESC_INTEGER_CLASS_SET_MIN_VALUE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.setMinValue)

#define ASN_DESC_INTEGER_CLASS_GET_MIN_VALUE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.getMinValue)

#define ASN_DESC_INTEGER_CLASS_SET_DEFAULT_VALUE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.setDefaultValue)

#define ASN_DESC_INTEGER_CLASS_GET_DEFAULT_VALUE(x) \
    (((ASN_DescIntegerClass)(x))->asnDescIntegerClass.getDefaultValue)


/*
 *  For inheritance.
 */ 

extern ASN_DescInteger_ClassRec itsASN_DescInteger_ClassRec;


/* ASN_DescInteger object. */

typedef struct _ASN_DescInteger_ObjectPart
{
    ITS_BOOLEAN clauseRange;
    ITS_LONG    maxValue;
    ITS_LONG    minValue;
    ITS_LONG    defaultValue;
} ASN_DescInteger_ObjectPart;


typedef struct _ASN_DescInteger_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescInteger_ObjectPart  asnDescInteger;
} ASN_DescInteger_ObjectRec;

#define ASN_DESC_INTEGER_CLAUSE_RANGE(x) \
    (((ASN_DescInteger)(x))->asnDescInteger.clauseRange)

#define ASN_DESC_INTEGER_MAX_VALUE(x) \
    (((ASN_DescInteger)(x))->asnDescInteger.maxValue)

#define ASN_DESC_INTEGER_MIN_VALUE(x) \
    (((ASN_DescInteger)(x))->asnDescInteger.minValue)

#define ASN_DESC_INTEGER_DEFAULT_VALUE(x) \
    (((ASN_DescInteger)(x))->asnDescInteger.defaultValue)


#define ASN_DESC_INTEGER_CLASS_NAME "ASN_DescInteger"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescInteger ASN_DescInteger_ConstructDefault();
void ASN_DescInteger_Destruct(ASN_DescInteger object);
ASN_Object ASN_DescInteger_Factory(const ASN_DescInteger object);
void ASN_DescInteger_SetCloneForFactory(ASN_DescInteger object, ASN_Integer clone);
ASN_Object ASN_DescInteger_DefaultFactory(const ASN_DescInteger object);
void ASN_DescInteger_SetCloneForDefaultFactory(ASN_DescInteger object, ASN_Integer clone);
ITS_BOOLEAN ASN_DescInteger_IsClauseOptional(const ASN_DescInteger object);
ITS_BOOLEAN ASN_DescInteger_IsClauseDefault(const ASN_DescInteger object);
ITS_BOOLEAN ASN_DescInteger_IsClauseAnyTag(const ASN_DescInteger object);
void ASN_DescInteger_SetClauseOptional(ASN_DescInteger object);
void ASN_DescInteger_SetClauseDefault(ASN_DescInteger object);
void ASN_DescInteger_SetClauseAnyTag(ASN_DescInteger object);
ITS_BOOLEAN ASN_DescInteger_TagIdentify(const ASN_DescInteger object, const ASN_Tag tag);
const ASN_Tag ASN_DescInteger_TagIdentity(const ASN_DescInteger object);
void ASN_DescInteger_TagAddLevel(ASN_DescInteger object, ASN_Tag tag);
size_t ASN_DescInteger_TagLevelNumber(const ASN_DescInteger object);
ASN_LinkedList ASN_DescInteger_TagStack(ASN_DescInteger object);
const char* ASN_DescInteger_GetName(const ASN_DescInteger object);
const char* ASN_DescInteger_GetBaseName(const ASN_DescInteger object);
ITS_BOOLEAN ASN_DescInteger_IsClauseRange(const ASN_DescInteger object);
void ASN_DescInteger_SetClauseRange(ASN_DescInteger object);
void ASN_DescInteger_SetMaxValue(ASN_DescInteger object, ITS_LONG maxValue);
ITS_LONG ASN_DescInteger_GetMaxValue(const ASN_DescInteger object);
void ASN_DescInteger_SetMinValue(ASN_DescInteger object, ITS_LONG minValue);
ITS_LONG ASN_DescInteger_GetMinValue(const ASN_DescInteger object);
void ASN_DescInteger_SetDefaultValue(ASN_DescInteger object, ITS_LONG defaultValue);
ITS_LONG ASN_DescInteger_GetDefaultValue(const ASN_DescInteger object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_INTEGER_H_) */


