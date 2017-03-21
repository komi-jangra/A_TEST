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
 *  ID: $Id: asn_real.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Real interface.
 */

#if !defined(_C_ASN_REAL_H_)
#define _C_ASN_REAL_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_real.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Real already defined in description. */
typedef struct _ASN_Real_ClassRec*       ASN_RealClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescReal    (*ASN_Real_GetStaticDescriptionProc)();
typedef void            (*ASN_Real_DestructStaticDescriptionProc)();
typedef double          (*ASN_Real_GetValueProc)(const ASN_Real object);
typedef void            (*ASN_Real_SetValueProc)(ASN_Real object, double value);
typedef ASN_Tag         (*ASN_Real_GetUniversalTagProc)(const ASN_Real object);


/*
 *  Procedure overrides.
 */

#define ASN_REAL_GET_VALUE_INHERIT           (ASN_Real_GetValueProc)NULL
#define ASN_REAL_SET_VALUE_INHERIT           (ASN_Real_SetValueProc)NULL
#define ASN_REAL_GET_UNIVERSAL_TAG_INHERIT   (ASN_Real_GetUniversalTagProc)NULL

/* ASN_Real class. */

typedef struct
{
    ASN_Real_GetStaticDescriptionProc        getStaticDescription;
    ASN_Real_DestructStaticDescriptionProc   destructStaticDescription;
    ASN_Real_GetValueProc                    getValue;
    ASN_Real_SetValueProc                    setValue;
    ASN_Real_GetUniversalTagProc             getUniversalTag; 
} ASN_Real_ClassPart;


typedef struct _ASN_Real_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Real_ClassPart      asnRealClass;
} ASN_Real_ClassRec;

#define ASN_REAL_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_RealClass)(x))->asnRealClass.getStaticDescription)

#define ASN_REAL_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_RealClass)(x))->asnRealClass.destructStaticDescription)

#define ASN_REAL_CLASS_GET_VALUE(x) \
    (((ASN_RealClass)(x))->asnRealClass.getValue)

#define ASN_REAL_CLASS_SET_VALUE(x) \
    (((ASN_RealClass)(x))->asnRealClass.setValue)

#define ASN_REAL_CLASS_GET_UNIVERSAL_TAG(x) \
    (((ASN_RealClass)(x))->asnRealClass.getUniversalTag)


/*
 *  For inheritance.
 */ 

extern ASN_Real_ClassRec itsASN_Real_ClassRec;


/* ASN_Real object. */

typedef struct _ASN_Real_ObjectPart
{
    double value;
} ASN_Real_ObjectPart;


typedef struct _ASN_Real_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Real_ObjectPart     asnReal;
} ASN_Real_ObjectRec;

#define ASN_REAL_VALUE(x) \
    (((ASN_Real)(x))->asnReal.value)

#define ASN_REAL_CLASS_NAME "ASN_Real"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Real ASN_Real_ConstructDefault();
ASN_Real ASN_Real_ConstructWithValue(double value);
ASN_Real ASN_Real_ConstructWithValueDescription(double value, ASN_DescReal description);
void ASN_Real_Destruct(ASN_Real object);
ASN_Real ASN_Real_Clone(const ASN_Real object);
ITS_BOOLEAN ASN_Real_Equals(const ASN_Real object, const ASN_Real other);
ASN_DescReal ASN_Real_GetStaticDescription();
void ASN_Real_DestructStaticDescription();
double ASN_Real_GetValue(const ASN_Real object);
void ASN_Real_SetValue(ASN_Real object, double value);
ASN_Tag ASN_Real_GetUniversalTag(const ASN_Real object);
int ASN_Real_Encode(ASN_Real object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Real_Decode(ASN_Real object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Real_GetName(const ASN_Real object);
const char* ASN_Real_GetBaseName(const ASN_Real object);
void ASN_Real_Print(const ASN_Real object);
char* ASN_Real_ToString(const ASN_Real object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_REAL_H_) */
