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
 *  ID: $Id: asn_desc_real.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_DescReal interface.
 */

#if !defined(_C_ASN_DESC_REAL_H_)
#define _C_ASN_DESC_REAL_H_

#include <asn_desc_object.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Real_ObjectRec*      ASN_Real;
typedef struct _ASN_DescReal_ObjectRec*  ASN_DescReal;
typedef struct _ASN_DescReal_ClassRec*   ASN_DescRealClass;



/*
 *  Procedure signatures.
 */

typedef ITS_BOOLEAN     (*ASN_DescReal_IsClauseRangeProc)(const ASN_DescReal object);
typedef void            (*ASN_DescReal_SetClauseRangeProc)(ASN_DescReal object);
typedef void            (*ASN_DescReal_SetMaxValueProc)(ASN_DescReal object, double maxValue);
typedef double          (*ASN_DescReal_GetMaxValueProc)(const ASN_DescReal object);
typedef void            (*ASN_DescReal_SetMinValueProc)(ASN_DescReal object, double minValue);
typedef double          (*ASN_DescReal_GetMinValueProc)(const ASN_DescReal object);
typedef void            (*ASN_DescReal_SetDefaultValueProc)(ASN_DescReal object, double defaultValue);
typedef double          (*ASN_DescReal_GetDefaultValueProc)(const ASN_DescReal object);

/* ASN_DescReal class. */

typedef struct
{
    ASN_DescReal_IsClauseRangeProc       isClauseRange;
    ASN_DescReal_SetClauseRangeProc      setClauseRange;
    ASN_DescReal_SetMaxValueProc         setMaxValue;
    ASN_DescReal_GetMaxValueProc         getMaxValue;
    ASN_DescReal_SetMinValueProc         setMinValue;
    ASN_DescReal_GetMinValueProc         getMinValue;
    ASN_DescReal_SetDefaultValueProc     setDefaultValue;
    ASN_DescReal_GetDefaultValueProc     getDefaultValue;
} ASN_DescReal_ClassPart;


typedef struct _ASN_DescReal_ClassRec
{
    ITS_CoreClassPart           coreClass;
    ASN_DescObject_ClassPart    asnDescObjectClass;
    ASN_DescReal_ClassPart      asnDescRealClass;
} ASN_DescReal_ClassRec;

#define ASN_DESC_REAL_CLASS_IS_CLAUSE_RANGE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.isClauseRange)

#define ASN_DESC_REAL_CLASS_SET_CLAUSE_RANGE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.setClauseRange)

#define ASN_DESC_REAL_CLASS_SET_MAX_VALUE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.setMaxValue)

#define ASN_DESC_REAL_CLASS_GET_MAX_VALUE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.getMaxValue)

#define ASN_DESC_REAL_CLASS_SET_MIN_VALUE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.setMinValue)

#define ASN_DESC_REAL_CLASS_GET_MIN_VALUE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.getMinValue)

#define ASN_DESC_REAL_CLASS_SET_DEFAULT_VALUE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.setDefaultValue)

#define ASN_DESC_REAL_CLASS_GET_DEFAULT_VALUE(x) \
    (((ASN_DescRealClass)(x))->asnDescRealClass.getDefaultValue)


/*
 *  For inheritance.
 */ 

extern ASN_DescReal_ClassRec itsASN_DescReal_ClassRec;


/* ASN_DescReal object. */

typedef struct _ASN_DescReal_ObjectPart
{
    ITS_BOOLEAN clauseRange;
    double      maxValue;
    double      minValue;
    double      defaultValue;
} ASN_DescReal_ObjectPart;


typedef struct _ASN_DescReal_ObjectRec
{
    ITS_CoreObjectPart          core;
    ASN_DescObject_ObjectPart   asnDescObject;
    ASN_DescReal_ObjectPart     asnDescReal;
} ASN_DescReal_ObjectRec;

#define ASN_DESC_REAL_CLAUSE_RANGE(x) \
    (((ASN_DescReal)(x))->asnDescReal.clauseRange)

#define ASN_DESC_REAL_MAX_VALUE(x) \
    (((ASN_DescReal)(x))->asnDescReal.maxValue)

#define ASN_DESC_REAL_MIN_VALUE(x) \
    (((ASN_DescReal)(x))->asnDescReal.minValue)

#define ASN_DESC_REAL_DEFAULT_VALUE(x) \
    (((ASN_DescReal)(x))->asnDescReal.defaultValue)


#define ASN_DESC_REAL_CLASS_NAME "ASN_DescReal"



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_DescReal ASN_DescReal_ConstructDefault();
void ASN_DescReal_Destruct(ASN_DescReal object);
ASN_Object ASN_DescReal_Factory(const ASN_DescReal object);
void ASN_DescReal_SetCloneForFactory(ASN_DescReal object, ASN_Real clone);
ASN_Object ASN_DescReal_DefaultFactory(const ASN_DescReal object);
void ASN_DescReal_SetCloneForDefaultFactory(ASN_DescReal object, ASN_Real clone);
ITS_BOOLEAN ASN_DescReal_IsClauseOptional(const ASN_DescReal object);
ITS_BOOLEAN ASN_DescReal_IsClauseDefault(const ASN_DescReal object);
ITS_BOOLEAN ASN_DescReal_IsClauseAnyTag(const ASN_DescReal object);
void ASN_DescReal_SetClauseOptional(ASN_DescReal object);
void ASN_DescReal_SetClauseDefault(ASN_DescReal object);
void ASN_DescReal_SetClauseAnyTag(ASN_DescReal object);
ITS_BOOLEAN ASN_DescReal_TagIdentify(const ASN_DescReal object, const ASN_Tag tag);
const ASN_Tag ASN_DescReal_TagIdentity(const ASN_DescReal object);
void ASN_DescReal_TagAddLevel(ASN_DescReal object, ASN_Tag tag);
size_t ASN_DescReal_TagLevelNumber(const ASN_DescReal object);
ASN_LinkedList ASN_DescReal_TagStack(ASN_DescReal object);
const char* ASN_DescReal_GetName(const ASN_DescReal object);
const char* ASN_DescReal_GetBaseName(const ASN_DescReal object);
ITS_BOOLEAN ASN_DescReal_IsClauseRange(const ASN_DescReal object);
void ASN_DescReal_SetClauseRange(ASN_DescReal object);
void ASN_DescReal_SetMaxValue(ASN_DescReal object, double maxValue);
double ASN_DescReal_GetMaxValue(const ASN_DescReal object);
void ASN_DescReal_SetMinValue(ASN_DescReal object, double minValue);
double ASN_DescReal_GetMinValue(const ASN_DescReal object);
void ASN_DescReal_SetDefaultValue(ASN_DescReal object, double defaultValue);
double ASN_DescReal_GetDefaultValue(const ASN_DescReal object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_DESC_REAL_H_) */


