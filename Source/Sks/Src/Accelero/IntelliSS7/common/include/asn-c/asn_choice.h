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
 *  ID: $Id: asn_choice.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN_Choice interface.
 */

#if !defined(_C_ASN_CHOICE_H_)
#define _C_ASN_CHOICE_H_

#include <asn_object.h>
#include <asn_tag.h>
#include <asn_desc_choice.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/*
 *  Forward declarations.
 */ 

/* ASN_Choice already defined in description. */
typedef struct _ASN_Choice_ClassRec*        ASN_ChoiceClass;


/*
 *  Procedure signatures.
 */

typedef ASN_DescChoice      (*ASN_Choice_GetStaticDescriptionProc)();
typedef void                (*ASN_Choice_DestructStaticDescriptionProc)();
typedef const ASN_Object    (*ASN_Choice_GetChoiceProc)(const ASN_Choice object);
typedef void                (*ASN_Choice_SetChoiceProc)(ASN_Choice object, ASN_Object choice);
typedef ITS_BOOLEAN         (*ASN_Choice_ContainsProc)(const ASN_Choice object, const ASN_Tag tag);
typedef ITS_BOOLEAN         (*ASN_Choice_ContainsChoiceProc)(const ASN_Choice object);

/*
 *  Procedure overrides.
 */

#define ASN_CHOICE_GET_CHOICE_INHERIT           (ASN_Choice_GetChoiceProc)NULL              
#define ASN_CHOICE_SET_CHOICE_INHERIT           (ASN_Choice_SetChoiceProc)NULL
#define ASN_CHOICE_CONTAINS_INHERIT             (ASN_Choice_ContainsProc)NULL             
#define ASN_CHOICE_CONTAINS_CHOICE_INHERIT      (ASN_Choice_ContainsChoiceProc)NULL


/* ASN_Choice class. */

typedef struct
{
    ASN_Choice_GetStaticDescriptionProc         getStaticDescription;
    ASN_Choice_DestructStaticDescriptionProc    destructStaticDescription;
    ASN_Choice_GetChoiceProc                    getChoice;
    ASN_Choice_SetChoiceProc                    setChoice;
    ASN_Choice_ContainsProc                     contains;
    ASN_Choice_ContainsChoiceProc               containsChoice;
} ASN_Choice_ClassPart;


typedef struct _ASN_Choice_ClassRec
{
    ITS_CoreClassPart       coreClass;
    ASN_Object_ClassPart    asnObjectClass;
    ASN_Choice_ClassPart    asnChoiceClass;
} ASN_Choice_ClassRec;

#define ASN_CHOICE_CLASS_GET_STATIC_DESCRIPTION(x) \
    (((ASN_ChoiceClass)(x))->asnChoiceClass.getStaticDescription)

#define ASN_CHOICE_CLASS_DESTRUCT_STATIC_DESCRIPTION(x) \
    (((ASN_ChoiceClass)(x))->asnChoiceClass.destructStaticDescription)

#define ASN_CHOICE_CLASS_GET_CHOICE(x) \
    (((ASN_ChoiceClass)(x))->asnChoiceClass.getChoice)

#define ASN_CHOICE_CLASS_SET_CHOICE(x) \
    (((ASN_ChoiceClass)(x))->asnChoiceClass.setChoice)

#define ASN_CHOICE_CLASS_CONTAINS(x) \
    (((ASN_ChoiceClass)(x))->asnChoiceClass.contains)

#define ASN_CHOICE_CLASS_CONTAINS_CHOICE(x) \
    (((ASN_ChoiceClass)(x))->asnChoiceClass.containsChoice)


/*
 *  For inheritance.
 */ 

extern ASN_Choice_ClassRec itsASN_Choice_ClassRec;


/* ASN_Choice object. */

typedef struct _ASN_Choice_ObjectPart
{
    ASN_Object choice;
} ASN_Choice_ObjectPart;


typedef struct _ASN_Choice_ObjectRec
{
    ITS_CoreObjectPart      core;
    ASN_Object_ObjectPart   asnObject;
    ASN_Choice_ObjectPart   asnChoice;
} ASN_Choice_ObjectRec;

#define ASN_CHOICE_CHOICE(x) \
    (((ASN_Choice)(x))->asnChoice.choice)


#define ASN_CHOICE_CLASS_NAME "ASN_Choice"


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  Protected interface.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

ASN_Choice ASN_Choice_ConstructDefault();
ASN_Choice ASN_Choice_ConstructWithDescription(ASN_DescChoice description);
void ASN_Choice_Destruct(ASN_Choice object);
ASN_Choice ASN_Choice_Clone(const ASN_Choice object);
ITS_BOOLEAN ASN_Choice_Equals(const ASN_Choice object, const ASN_Choice other);
ASN_DescChoice ASN_Choice_GetStaticDescription();
void ASN_Choice_DestructStaticDescription();
const ASN_Object ASN_Choice_GetChoice(const ASN_Choice object);
void ASN_Choice_SetChoice(ASN_Choice object, ASN_Object choice);
ITS_BOOLEAN ASN_Choice_Contains(const ASN_Choice object, const ASN_Tag tag);
ITS_BOOLEAN ASN_Choice_ContainsChoice(const ASN_Choice object);
int ASN_Choice_Encode(ASN_Choice object, ASN_Octets* octets, ASN_EncodeError* encodeError);
int ASN_Choice_Decode(ASN_Choice object, ASN_Octets octets, ASN_DecodeError* decodeError);
const char* ASN_Choice_GetName(const ASN_Choice object);
const char* ASN_Choice_GetBaseName(const ASN_Choice object);
void ASN_Choice_Print(const ASN_Choice object);
char* ASN_Choice_ToString(const ASN_Choice object);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_CHOICE_H_) */
