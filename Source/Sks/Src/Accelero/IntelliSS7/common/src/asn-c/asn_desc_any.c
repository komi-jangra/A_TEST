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
 *  ID: $Id: asn_desc_any.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_desc_any.h>

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
 *  Forward declaration.
 */ 

static size_t TagLevelNumber(const ASN_DescObject object);

static ITS_BOOLEAN 
TagIdentify(const ASN_DescObject object, const ASN_Tag tag)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(TagLevelNumber(object) >= 1);

    if (TagLevelNumber(object) == 1 && ASN_DescObject_IsClauseAnyTag(object))
    {
        return ITS_TRUE;
    }
    else
    {
        ASN_Tag tagStackFront = 
            (ASN_Tag)ASN_LinkedList_GetFront(
                ASN_DESC_OBJECT_TAG_STACK(object));

        ASN_C_ASSERT(tagStackFront != NULL);

        return ASN_Tag_Equals(tag, tagStackFront);
    }
}

static const ASN_Tag 
TagIdentity(const ASN_DescObject object)
{
    ASN_Tag tagStackFront = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(TagLevelNumber(object) >= 1);

    if (TagLevelNumber(object) == 1 && ASN_DescObject_IsClauseAnyTag(object))
    {
        /*  
         *  Should never be reached by design of the encode/decode algorithms.
         *  ANY type is always explicitly tagged by ASN.1 compiler.
         */

        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ASN_C_ASSERT(must_not_be_reached);

        return NULL;
    }
    else
    {
        ASN_Tag tagStackFront = 
            (ASN_Tag)ASN_LinkedList_GetFront(
                ASN_DESC_OBJECT_TAG_STACK(object));

        ASN_C_ENSURE(tagStackFront != NULL);

        return tagStackFront;
    }
}

static void 
TagAddLevel(ASN_DescObject object, ASN_Tag tag)
{
    int result = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    result = ASN_LinkedList_PushFront(
                ASN_DESC_OBJECT_TAG_STACK(object),
                (ITS_Object)tag);

    ASN_C_ENSURE(result == ITS_SUCCESS);
}

static size_t 
TagLevelNumber(const ASN_DescObject object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_LinkedList_GetSize(ASN_DESC_OBJECT_TAG_STACK(object)) + 1;
}

/*
 *  ASN_DescAny class record.
 */ 

ASN_DescAny_ClassRec itsASN_DescAny_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_DescObject_ClassRec,                 
        sizeof(ASN_DescAny_ObjectRec),  
        ITS_FALSE,                         
        0,                                 
        ASN_DESC_ANY_CLASS_NAME,             
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
        TagIdentify,
        TagIdentity,
        TagAddLevel,
        TagLevelNumber,
        ASN_DESC_OBJECT_TAG_STACK_INHERIT,                    
        ASN_DESC_OBJECT_GET_NAME_INHERIT,                     
        ASN_DESC_OBJECT_GET_BASE_NAME_INHERIT
    }

    /* No ASN_DescAny class part. */

};


ASN_DescAny
ASN_DescAny_ConstructDefault()
{
    ASN_DescAny result = NULL;

    result = (ASN_DescAny)ITS_ConstructObject((ITS_Class)&itsASN_DescAny_ClassRec);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void 
ASN_DescAny_Destruct(ASN_DescAny object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Object 
ASN_DescAny_Factory(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescAny_SetCloneForFactory(ASN_DescAny object, ASN_Any clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ASN_Object 
ASN_DescAny_DefaultFactory(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescAny_SetCloneForDefaultFactory(ASN_DescAny object, ASN_Any clone)
{
    ASN_DESC_OBJECT_CLASS_SET_CLONE_FOR_DEFAULT_FACTORY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, (ASN_Object)clone);
}

ITS_BOOLEAN 
ASN_DescAny_IsClauseOptional(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescAny_IsClauseDefault(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescAny_IsClauseAnyTag(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_IS_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescAny_SetClauseOptional(ASN_DescAny object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_OPTIONAL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescAny_SetClauseDefault(ASN_DescAny object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_DEFAULT(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescAny_SetClauseAnyTag(ASN_DescAny object)
{
    ASN_DESC_OBJECT_CLASS_SET_CLAUSE_ANY_TAG(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ITS_BOOLEAN 
ASN_DescAny_TagIdentify(const ASN_DescAny object, const ASN_Tag tag)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTIFY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

const ASN_Tag 
ASN_DescAny_TagIdentity(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_IDENTITY(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

void 
ASN_DescAny_TagAddLevel(ASN_DescAny object, ASN_Tag tag)
{
    ASN_DESC_OBJECT_CLASS_TAG_ADD_LEVEL(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object, tag);
}

size_t
ASN_DescAny_TagLevelNumber(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_LEVEL_NUMBER(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

ASN_LinkedList 
ASN_DescAny_TagStack(ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_TAG_STACK(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescAny_GetName(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_GET_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

const char* 
ASN_DescAny_GetBaseName(const ASN_DescAny object)
{
    return ASN_DESC_OBJECT_CLASS_GET_BASE_NAME(
        ITS_OBJ_CLASS(object))((ASN_DescObject)object);
}

