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
 *  ID: $Id: asn_octets.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Octets interface.
 */

#if !defined(_C_ASN_OCTETS_H_)
#define _C_ASN_OCTETS_H_

#include <its.h>
#include <its_object.h>

#include <asn_assertion.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Forward declarations.
 */ 

typedef struct _ASN_Octets_ObjectRec*    ASN_Octets;
typedef struct _ASN_Octets_ClassRec*     ASN_OctetsClass;


/*
 *  Procedure signatures.
 */

typedef int                 (*ASN_Octets_ReserveProc)(ASN_Octets object, size_t size);
typedef const ITS_OCTET*    (*ASN_Octets_GetArrayProc)(const ASN_Octets object);
typedef int                 (*ASN_Octets_SetArrayProc)(ASN_Octets object, const ITS_OCTET* array, size_t size);
typedef size_t              (*ASN_Octets_GetSizeProc)(const ASN_Octets object);
typedef void                (*ASN_Octets_PrintWithOffsetProc)(const ASN_Octets object);
typedef char*               (*ASN_Octets_ToStringProc)(const ASN_Octets object);
typedef char*               (*ASN_Octets_ToStringWithOffsetProc)(const ASN_Octets object);
typedef size_t              (*ASN_Octets_GetOffsetProc)(const ASN_Octets object);
typedef void                (*ASN_Octets_SetOffsetProc)(ASN_Octets object, size_t offset);
typedef void                (*ASN_Octets_IncrementOffsetProc)(ASN_Octets object);
typedef void                (*ASN_Octets_DecrementOffsetProc)(ASN_Octets object);            
typedef void                (*ASN_Octets_IncrementOffsetWithIncrementProc)(ASN_Octets object, size_t increment);
typedef void                (*ASN_Octets_DecrementOffsetWithDecrementProc)(ASN_Octets object, size_t decrement);
typedef ITS_BOOLEAN         (*ASN_Octets_IsIndexValidProc)(const ASN_Octets object, size_t index);
typedef ITS_BOOLEAN         (*ASN_Octets_IsIndexWithOffsetValidProc)(const ASN_Octets object, size_t index);
typedef ITS_BOOLEAN         (*ASN_Octets_IsOffsetValidProc)(const ASN_Octets object, size_t offset); 
typedef ITS_OCTET           (*ASN_Octets_GetOctetAtProc)(const ASN_Octets object, size_t index);
typedef void                (*ASN_Octets_SetOctetAtProc)(ASN_Octets object, size_t index, ITS_OCTET octet);
typedef ITS_OCTET           (*ASN_Octets_GetOctetAtWithOffsetProc)(const ASN_Octets object, size_t index);
typedef void                (*ASN_Octets_SetOctetAtWithOffsetProc)(ASN_Octets, size_t index, ITS_OCTET octet);
typedef int                 (*ASN_Octets_AppendProc)(ASN_Octets object, const ASN_Octets other);

/* ASN_Octets class. */

typedef struct _ASN_Octets_ClassPart
{
    ASN_Octets_ReserveProc                      reserve;
    ASN_Octets_GetArrayProc                     getArray;
    ASN_Octets_SetArrayProc                     setArray;
    ASN_Octets_GetSizeProc                      getSize;
    ASN_Octets_PrintWithOffsetProc              printWithOffset;
    ASN_Octets_ToStringProc                     toString;
    ASN_Octets_ToStringWithOffsetProc           toStringWithOffset;
    ASN_Octets_GetOffsetProc                    getOffset;
    ASN_Octets_SetOffsetProc                    setOffset;
    ASN_Octets_IncrementOffsetProc              incrementOffset;
    ASN_Octets_DecrementOffsetProc              decrementOffset;
    ASN_Octets_IncrementOffsetWithIncrementProc incrementOffsetWithIncrement;
    ASN_Octets_DecrementOffsetWithDecrementProc decrementOffsetWithDecrement;
    ASN_Octets_IsIndexValidProc                 isIndexValid;
    ASN_Octets_IsIndexWithOffsetValidProc       isIndexWithOffsetValid;
    ASN_Octets_IsOffsetValidProc                isOffsetValid;
    ASN_Octets_GetOctetAtProc                   getOctetAt;
    ASN_Octets_SetOctetAtProc                   setOctetAt;
    ASN_Octets_GetOctetAtWithOffsetProc         getOctetAtWithOffset;
    ASN_Octets_SetOctetAtWithOffsetProc         setOctetAtWithOffset;
    ASN_Octets_AppendProc                       append;
} ASN_Octets_ClassPart;

typedef struct _ASN_Octets_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Octets_ClassPart    asnOctetsClass;
} ASN_Octets_ClassRec;

#define ASN_OCTETS_CLASS_RESERVE(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.reserve)

#define ASN_OCTETS_CLASS_GET_ARRAY(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.getArray)

#define ASN_OCTETS_CLASS_SET_ARRAY(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.setArray)

#define ASN_OCTETS_CLASS_GET_SIZE(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.getSize)

#define ASN_OCTETS_CLASS_PRINT_WITH_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.printWithOffset)

#define ASN_OCTETS_CLASS_TO_STRING(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.toString)

#define ASN_OCTETS_CLASS_TO_STRING_WITH_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.toStringWithOffset)

#define ASN_OCTETS_CLASS_GET_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.getOffset)

#define ASN_OCTETS_CLASS_SET_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.setOffset)

#define ASN_OCTETS_CLASS_INCREMENT_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.incrementOffset)

#define ASN_OCTETS_CLASS_DECREMENT_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.decrementOffset)

#define ASN_OCTETS_CLASS_INCREMENT_OFFSET_WITH_INCREMENT(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.incrementOffsetWithIncrement)

#define ASN_OCTETS_CLASS_DECREMENT_OFFSET_WITH_DECREMENT(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.decrementOffsetWithDecrement)

#define ASN_OCTETS_CLASS_IS_INDEX_VALID(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.isIndexValid)

#define ASN_OCTETS_CLASS_IS_INDEX_WITH_OFFSET_VALID(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.isIndexWithOffsetValid)

#define ASN_OCTETS_CLASS_IS_OFFSET_VALID(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.isOffsetValid)

#define ASN_OCTETS_CLASS_GET_OCTET_AT(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.getOctetAt)

#define ASN_OCTETS_CLASS_SET_OCTET_AT(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.setOctetAt)

#define ASN_OCTETS_CLASS_GET_OCTET_AT_WITH_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.getOctetAtWithOffset)

#define ASN_OCTETS_CLASS_SET_OCTET_AT_WITH_OFFSET(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.setOctetAtWithOffset)

#define ASN_OCTETS_CLASS_APPEND(x) \
    (((ASN_OctetsClass)(x))->asnOctetsClass.append)

/* ASN_Octets object. */

typedef struct _ASN_Octets_ObjectPart
{
    ITS_OCTET*  data;
    size_t      reservedSize;
    size_t      size;
    size_t      offset;
} ASN_Octets_ObjectPart;


typedef struct _ASN_Octets_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Octets_ObjectPart   asnOctets;
} ASN_Octets_ObjectRec;

#define ASN_OCTETS_DATA(x)                  \
    (((ASN_Octets)(x))->asnOctets.data)

#define ASN_OCTETS_RESERVED_SIZE(x)         \
    (((ASN_Octets)(x))->asnOctets.reservedSize)

#define ASN_OCTETS_SIZE(x)                  \
    (((ASN_Octets)(x))->asnOctets.size)

#define ASN_OCTETS_OFFSET(x)                \
    (((ASN_Octets)(x))->asnOctets.offset)


#define ASN_OCTETS_CLASS_NAME "ASN_Octets"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Public interface.                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/


ASN_Octets ASN_Octets_ConstructDefault();
ASN_Octets ASN_Octets_ConstructWithArray(const ITS_OCTET* array, size_t size);
void ASN_Octets_Destruct(ASN_Octets object);
ASN_Octets ASN_Octets_Clone(const ASN_Octets object);
ITS_BOOLEAN ASN_Octets_Equals(const ASN_Octets object, const ASN_Octets other);
int ASN_Octets_Reserve(ASN_Octets object, size_t size);
const ITS_OCTET* ASN_Octets_GetArray(const ASN_Octets object);
size_t ASN_Octets_GetSize(const ASN_Octets object);
int ASN_Octets_SetArray(ASN_Octets object, const ITS_OCTET* array, size_t size);
void ASN_Octets_Print(const ASN_Octets object);
void ASN_Octets_PrintWithOffset(const ASN_Octets object);
char* ASN_Octets_ToString(const ASN_Octets object);
char* ASN_Octets_ToStringWithOffset(const ASN_Octets object);


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface (used by ASN.1 C runtime internally).                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

size_t ASN_Octets_GetOffset(const ASN_Octets object);
void ASN_Octets_SetOffset(ASN_Octets object, size_t offset);
void ASN_Octets_IncrementOffset(ASN_Octets object);
void ASN_Octets_IncrementOffsetWithIncrement(ASN_Octets object, size_t increment);
void ASN_Octets_DecrementOffset(ASN_Octets object);
void ASN_Octets_DecrementOffsetWithDecrement(ASN_Octets object, size_t decrement);
ITS_BOOLEAN ASN_Octets_IsIndexValid(const ASN_Octets object, size_t index);
ITS_BOOLEAN ASN_Octets_IsIndexWithOffsetValid(const ASN_Octets object, size_t index);
ITS_BOOLEAN ASN_Octets_IsOffsetValid(const ASN_Octets object, size_t offset);
ITS_OCTET ASN_Octets_GetOctetAt(const ASN_Octets object, size_t index);
void ASN_Octets_SetOctetAt(ASN_Octets object, size_t index, ITS_OCTET octet);
ITS_OCTET ASN_Octets_GetOctetAtWithOffset(const ASN_Octets object, size_t index);
void ASN_Octets_SetOctetAtWithOffset(ASN_Octets object, size_t index, ITS_OCTET octet);
int ASN_Octets_Append(ASN_Octets object, const ASN_Octets other);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_OCTETS_H_) */
