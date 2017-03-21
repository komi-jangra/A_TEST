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
 *  ID: $Id: asn_common.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#if !defined(_C_ASN_COMMON_H_)
#define _C_ASN_COMMON_H_

#include <its.h>
#include <its_object.h>
#include <asn_assertion.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Preprocessor constant definitions.
 */

#define ASN_BITS_PER_BYTE       8
#define ASN_BITS_PER_LONG       32
#define ASN_BYTES_PER_INT       4
#define ASN_BYTES_PER_LONG      4
#define ASN_BYTES_PER_DOUBLE    8

#define ASN_BYTE_MASK_IN_LONG   0x000000FF
#define ASN_SHORT_MASK_IN_LONG  0x0000FFFF
#define ASN_INT_MASK_IN_LONG    0xFFFFFFFF

#define ASN_BYTE_MASK_IN_INT    0x000000FF
#define ASN_SHORT_MASK_IN_INT   0x0000FFFF
    
#define ASN_BYTE_MASK_IN_SHORT  0x00FF

#define ASN_ALL_BITS_SET        0xFFU
#define ASN_SIGN_BIT            0x80U


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Public interface.                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------*/

/* Decode Skip Invalid Enumerated Value. */

void ASN_Options_GlobalSetDecodeSkipInvalidEnumeratedValue();
void ASN_Options_GlobalUnsetDecodeSkipInvalidEnumeratedValue();
ITS_BOOLEAN ASN_Options_GlobalIsDecodeSkipInvalidEnumeratedValue();

/* Encode Skip Invalid Enumerated Value. */

void ASN_Options_GlobalSetEncodeSkipInvalidEnumeratedValue();
void ASN_Options_GlobalUnsetEncodeSkipInvalidEnumeratedValue();
ITS_BOOLEAN ASN_Options_GlobalIsEncodeSkipInvalidEnumeratedValue();

/*-----------------------------------------------------------------*/

/* Decode Skip Unknown Element In Set. */

void ASN_Options_GlobalSetDecodeSkipUnknownElementInSet();
void ASN_Options_GlobalUnsetDecodeSkipUnknownElementInSet();
ITS_BOOLEAN ASN_Options_GlobalIsDecodeSkipUnknownElementInSet();

/*-----------------------------------------------------------------*/

/* Decode Ignore Octet String Size Constraint. */

void ASN_Options_GlobalSetDecodeIgnoreOctetStringSizeConstraint();
void ASN_Options_GlobalUnsetDecodeIgnoreOctetStringSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsDecodeIgnoreOctetStringSizeConstraint();

/* Encode Ignore Octet String Size Constraint. */

void ASN_Options_GlobalSetEncodeIgnoreOctetStringSizeConstraint();
void ASN_Options_GlobalUnsetEncodeIgnoreOctetStringSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsEncodeIgnoreOctetStringSizeConstraint();

/*-----------------------------------------------------------------*/

/* Decode Ignore Sequence of Size Constraint. */

void ASN_Options_GlobalSetDecodeIgnoreSequenceOfSizeConstraint();
void ASN_Options_GlobalUnsetDecodeIgnoreSequenceOfSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsDecodeIgnoreSequenceOfSizeConstraint();

/* Encode Ignore Sequence of Size Constraint. */

void ASN_Options_GlobalSetEncodeIgnoreSequenceOfSizeConstraint();
void ASN_Options_GlobalUnsetEncodeIgnoreSequenceOfSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsEncodeIgnoreSequenceOfSizeConstraint();

/*-----------------------------------------------------------------*/

/* Decode Ignore Set of Size Constraint. */

void ASN_Options_GlobalSetDecodeIgnoreSetOfSizeConstraint();
void ASN_Options_GlobalUnsetDecodeIgnoreSetOfSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsDecodeIgnoreSetOfSizeConstraint();

/* Encode Ignore Set of Size Constraint. */

void ASN_Options_GlobalSetEncodeIgnoreSetOfSizeConstraint();
void ASN_Options_GlobalUnsetEncodeIgnoreSetOfSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsEncodeIgnoreSetOfSizeConstraint();

/*-----------------------------------------------------------------*/

/* Decode Ignore Bit String Size Constraint. */

void ASN_Options_GlobalSetDecodeIgnoreBitStringSizeConstraint();
void ASN_Options_GlobalUnsetDecodeIgnoreBitStringSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsDecodeIgnoreBitStringSizeConstraint();

/* Encode Ignore Bit String Size Constraint. */

void ASN_Options_GlobalSetEncodeIgnoreBitStringSizeConstraint();
void ASN_Options_GlobalUnsetEncodeIgnoreBitStringSizeConstraint();
ITS_BOOLEAN ASN_Options_GlobalIsEncodeIgnoreBitStringSizeConstraint();

/*-----------------------------------------------------------------*/


/*
 *  Initialization/termination of ASN.1 C Runtime.
 */

typedef ITS_ClassRec                ASN_C_RUNTIME_ClassRec;

#define ASN_C_RUNTIME_CLASS_NAME    "ASN_C_RUNTIME"

extern ASN_C_RUNTIME_ClassRec       itsASN_C_RUNTIME_ClassRec;
extern ITS_Class                    itsASN_C_RUNTIME_Class;


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

void ASN_Lock();
void ASN_Unlock();
char* ASN_AddLineShift(const char* str);


/*
 *  Should be used only for testing purpose or if ASN.1 C Runtime is used
 *  without IntelliSS7 (unlikely).
 */

int ASN_Initialize();
void ASN_Terminate();

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_COMMON_H_) */
