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
 *  ID: $Id: asn_desc_object_identifier.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_object_identifier.h>

static int
Construct(ITS_Object object, va_list args)
{
    ASN_C_REQUIRE(object != NULL);

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    /* Nothing to do. */
}

/*
 *  ASN_DescObjectIdentifier class record.
 */ 

ASN_DescObjectIdentifier_ClassRec itsASN_DescObjectIdentifier_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescObjectIdentifier_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_OBJECT_IDENTIFIER_CLASS_NAME,             
        ITS_CLASS_NO_INIT,                 
        ITS_CLASS_NO_DEST,                 
        ITS_CLASS_PART_NO_INIT,      
        ITS_CLASS_PART_NO_DEST,       
        Construct,               
        Destruct,                
        ITS_INST_CLONE_INHERIT,                   
        ITS_INST_PRINT_INHERIT,                   
        ITS_INST_SERIAL_INHERIT, 
        ITS_INST_EQUALS_INHERIT,                  
        ITS_INST_HASH_INHERIT,   
        NULL                     
    },

    /* ASN_DescObject class part. */

    {
        ASN_DESC_OBJECT_FACTORY_INHERIT,                      
        ASN_DESC_OBJECT_SET_CLONE_FOR_FACTORY_INHERIT,        
        ASN_DESC_OBJECT_DEFAULT_FACTORY_INHERIT,              
        ASN_DESC_OBJECT_SET_CLONE_FOR_DEFAULT_FACTORY_INHERIT,
        ASN_DESC_OBJECT_IS_CLAUSE_OPTIONAL_INHERIT,           
        ASN_DESC_OBJECT_IS_CLAUSE_DEFAULT_INHERIT,            
        ASN_DESC_OBJECT_IS_CLAUSE_ANY_TAG_INHERIT,            
        ASN_DESC_OBJECT_SET_CLAUSE_OPTIONAL_INHERIT,          
        ASN_DESC_OBJECT_SET_CLAUSE_DEFAULT_INHERIT,           
        ASN_DESC_OBJECT_SET_CLAUSE_ANY_TAG_INHERIT,           
        ASN_DESC_OBJECT_TAG_IDENTIFY_INHERIT,                 
        ASN_DESC_OBJECT_TAG_IDENTITY_INHERIT,                 
        ASN_DESC_OBJECT_TAG_ADD_LEVEL_INHERIT,                
        ASN_DESC_OBJECT_TAG_LEVEL_NUMBER_INHERIT,             
        ASN_DESC_OBJECT_TAG_STACK_INHERIT,                                       
        ASN_DESC_OBJECT_GET_NAME_INHERIT,                     
        ASN_DESC_OBJECT_GET_BASE_NAME_INHERIT
    }

    /* No ASN_DescObjectIdentifier class part. */

};


ASN_DescObjectIdentifier
ASN_DescObjectIdentifier_ConstructDefault()
{
    ASN_DescObjectIdentifier result = NULL;

    result = (ASN_DescObjectIdentifier)ITS_ConstructObject((ITS_Class)&itsASN_DescObjectIdentifier_ClassRec);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescObjectIdentifier_Destruct(ASN_DescObjectIdentifier object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescObjectIdentifier_Factory(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescObjectIdentifier_SetCloneForFactory(ASN_DescObjectIdentifier object, ASN_ObjectIdentifier clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescObjectIdentifier_DefaultFactory(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescObjectIdentifier_SetCloneForDefaultFactory(ASN_DescObjectIdentifier object, ASN_ObjectIdentifier clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescObjectIdentifier_IsClauseOptional(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescObjectIdentifier_IsClauseDefault(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescObjectIdentifier_IsClauseAnyTag(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescObjectIdentifier_SetClauseOptional(ASN_DescObjectIdentifier object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescObjectIdentifier_SetClauseDefault(ASN_DescObjectIdentifier object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescObjectIdentifier_SetClauseAnyTag(ASN_DescObjectIdentifier object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescObjectIdentifier_TagIdentify(const ASN_DescObjectIdentifier object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescObjectIdentifier_TagIdentity(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescObjectIdentifier_TagAddLevel(ASN_DescObjectIdentifier object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescObjectIdentifier_TagLevelNumber(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescObjectIdentifier_TagStack(ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescObjectIdentifier_GetName(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescObjectIdentifier_GetBaseName(const ASN_DescObjectIdentifier object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

