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
 *  ID: $Id: asn_choice.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_choice.h>
#include <asn_desc_choice.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_CHOICE_CLASS_GET_CHOICE(subClass) == ASN_CHOICE_GET_CHOICE_INHERIT)
    {
        ASN_CHOICE_CLASS_GET_CHOICE(subClass) =
            ASN_CHOICE_CLASS_GET_CHOICE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_CHOICE_CLASS_SET_CHOICE(subClass) == ASN_CHOICE_SET_CHOICE_INHERIT)
    {
        ASN_CHOICE_CLASS_SET_CHOICE(subClass) =
            ASN_CHOICE_CLASS_SET_CHOICE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_CHOICE_CLASS_CONTAINS(subClass) == ASN_CHOICE_CONTAINS_INHERIT)
    {
        ASN_CHOICE_CLASS_CONTAINS(subClass) =
            ASN_CHOICE_CLASS_CONTAINS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_CHOICE_CLASS_CONTAINS_CHOICE(subClass) == ASN_CHOICE_CONTAINS_CHOICE_INHERIT)
    {
        ASN_CHOICE_CLASS_CONTAINS_CHOICE(subClass) =
            ASN_CHOICE_CLASS_CONTAINS_CHOICE(ITS_CLASS_SUPERCLASS(subClass));
    }

    return ITS_SUCCESS;
}

static void
ClassPartDestruct(ITS_Class subClass)
{
    /* Nothing to do. */
}

/*
 *  Forward declarations.
 */ 

static ASN_DescChoice GetStaticDescription();

static int
Construct(ITS_Object object, va_list args)
{
    ASN_DescChoice description = NULL;

    ASN_C_REQUIRE(object != NULL);

    description = va_arg(args, ASN_DescChoice);

    ASN_CHOICE_CHOICE(object) = NULL;

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            return ITS_ENOMEM;
        }

        ASN_C_ASSERT(ASN_OBJECT_DESCRIPTION(object) != NULL);
    }
    else
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)description;
    }

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    if (ASN_CHOICE_CHOICE(object) != NULL)
    {
        ASN_Object_Destruct(ASN_CHOICE_CHOICE(object));
        ASN_CHOICE_CHOICE(object) = NULL;
    }
}

static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result   = NULL;
    ASN_Object choice   = NULL;
    int res             = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);

    result = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (result == NULL)
    {
        return result;
    }

    memcpy(result, object, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    choice = ASN_CHOICE_CHOICE(object);

    if (choice != NULL)
    {
        ASN_Object clonedChoice = NULL;

        clonedChoice = ASN_Object_Clone(choice);

        ASN_C_ENSURE(clonedChoice != NULL);

        if (clonedChoice == NULL)
        {
            free(result);

            return NULL;
        }

        ASN_CHOICE_CHOICE(result) = clonedChoice;
    }
    else
    {
        ASN_CHOICE_CHOICE(result) = NULL;
    }

    return result;
}

static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    ASN_Object choice       = NULL;
    ASN_Object otherChoice  = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(other != NULL);

    if (ITS_OBJ_CLASS(object) != ITS_OBJ_CLASS(other))
    {
        return ITS_FALSE;
    }

    choice      = ASN_CHOICE_CHOICE(object);
    otherChoice = ASN_CHOICE_CHOICE(other);

    if (choice == NULL && otherChoice == NULL)
    {
        return ITS_TRUE;
    }
    else if (choice == NULL && otherChoice != NULL)
    {
        return ITS_FALSE;
    }
    else if (choice != NULL && otherChoice == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        return ASN_Object_Equals(choice, otherChoice);
    }
}

static ASN_DescChoice staticDescription = NULL;

static ASN_DescChoice
GetStaticDescription()
{
    static ITS_BOOLEAN initialized  = ITS_FALSE;
    static ASN_DescChoice result    = NULL;
    ASN_Choice cloneForFactory      = NULL;

    if (initialized)
    {
        ASN_C_ENSURE(result != NULL);

        return result;
    }

    ASN_Lock();

    if (initialized)
    {
        ASN_Unlock();

        ASN_C_ENSURE(result != NULL);

        return result;
    }
    else
    {
        ASN_C_ASSERT(result == NULL);

        staticDescription = ASN_DescChoice_ConstructWithSize(0);

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_Choice_ConstructWithDescription(staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescChoice_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescChoice_SetCloneForFactory(staticDescription, cloneForFactory);

        result = staticDescription;

        initialized = ITS_TRUE;

        ASN_Unlock();

        ASN_C_ENSURE(result != NULL);

        return result;
    }
}

static void
DestructStaticDescription()
{
    if (staticDescription != NULL)
    {
        ASN_DescChoice_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

/*
 *  Forward declarations.
 */ 

static ITS_BOOLEAN ContainsChoice(const ASN_Choice object);

static const ASN_Object
GetChoice(const ASN_Choice object)
{
    ASN_Object result = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(ContainsChoice(object));

    result = ASN_CHOICE_CHOICE(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void
SetChoice(ASN_Choice object, ASN_Object choice)
{
    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(choice != NULL);

    if (ASN_CHOICE_CHOICE(object) != NULL)
    {
        ASN_Object_Destruct(ASN_CHOICE_CHOICE(object));
        ASN_CHOICE_CHOICE(object) = NULL;
    }

    ASN_CHOICE_CHOICE(object) = choice;
}

static ITS_BOOLEAN 
Contains(const ASN_Choice object, const ASN_Tag tag)
{
    ASN_Object choice                   = NULL;
    ASN_DescObject choiceDescription    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(tag != NULL);

    choice = ASN_CHOICE_CHOICE(object);

    if (choice == NULL)
    {
        return ITS_FALSE;
    }
    else
    {
        choiceDescription = ASN_OBJECT_DESCRIPTION(choice);

        ASN_C_ASSERT(choiceDescription != NULL);

        if (ASN_DescObject_TagIdentify(choiceDescription, tag))
        {
            return ITS_TRUE;
        }
        else
        {
            return ITS_FALSE;
        }
    }
}

static ITS_BOOLEAN
ContainsChoice(const ASN_Choice object)
{
    ASN_Object choice = NULL;

    ASN_C_REQUIRE(object != NULL);

    choice = ASN_CHOICE_CHOICE(object);

    return choice != NULL;
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescChoice description = NULL;

    ASN_Object choice                   = NULL;
    ASN_DescObject choiceDescription    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescChoice)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    choice = ASN_CHOICE_CHOICE(object);

    /* Encode check begin. */

    if (choice == NULL)
    {
        *encodeError = 
            ASN_CONSTRUCT_ENCODE_ERROR(
                ASN_E_NO_CHOICE_PRESENT,
                object);

        return ITS_E_ASN_ENCODE_ERROR;
    }

    ASN_C_ASSERT(choice != NULL);

    choiceDescription = ASN_OBJECT_DESCRIPTION(choice);

    if (!ASN_DescChoice_ContainsTag(
                                description, 
                                ASN_DescObject_TagIdentity(choiceDescription)))
    {
        *encodeError = 
            ASN_CONSTRUCT_ENCODE_ERROR(
                ASN_E_INVALID_CHOICE,
                object);

        return ITS_E_ASN_ENCODE_ERROR;
    }

    /* Encode check end. */

    ASN_C_ASSERT(ASN_DescChoice_TagLevelNumber(description) >= 1);

    if (ASN_DescChoice_TagLevelNumber(description) >= 2)
    {
        int res                 = ITS_SUCCESS;
        ASN_Octets choiceOctets = NULL;

        /* 
         *  Must follow ASN.1 TLTLTL..TLV format. 
         */

        res = ASN_Object_Encode(choice, &choiceOctets, encodeError);

        if (res != ITS_SUCCESS)
        {
            return res;
        }

        /*
         *  Next call is valid since ASN.1 Object description
         *  tag stack is used (contains one or more tags as 
         *  ASN_DescChoice_TagLevelNumber(description) >= 2).
         */
         
        *octets = ASN_Object_EncodeTagLengthValue(object, choiceOctets);

        if (*octets == NULL)
        {
            ASN_Octets_Destruct(choiceOctets);

            return ITS_ENOMEM;
        }

        ASN_Octets_Destruct(choiceOctets);

        return ITS_SUCCESS;
    }
    else
    {
        int res = ASN_Object_Encode(choice, octets, encodeError);

        if (res != ITS_SUCCESS)
        {
            return res;
        }
        else
        {
            return ITS_SUCCESS;
        }
    }
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                             = ITS_SUCCESS;
    ASN_DescChoice description          = NULL;
    ASN_Tag choiceTag                   = NULL;
    ASN_Object choice                   = NULL;
    ASN_DescObject choiceDescription    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescChoice)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    ASN_C_ASSERT(ASN_DescChoice_TagLevelNumber(description) >= 1);

    res = ASN_Object_DecodeRemoveExtraTagLength(
                                            object,
                                            octets,
                                            decodeError);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    choiceTag = ASN_Tag_ConstructDefault();

    if (choiceTag == NULL)
    {
        return ITS_ENOMEM;
    }

    res = ASN_Tag_DecodePreserveOffset(choiceTag, octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        ASN_Tag_Destruct(choiceTag);

        return res;
    }

    if (ASN_DescChoice_ContainsTag(description, choiceTag))
    {
        ASN_DescObject choiceDescription = 
            ASN_DescChoice_GetChoiceAtTag(description, choiceTag);

        ASN_Object choiceRetrieved = ASN_DescObject_Factory(choiceDescription);
        
        if (choiceRetrieved == NULL)
        {
            ASN_Tag_Destruct(choiceTag);

            return ITS_ENOMEM;
        }
        
        res = ASN_Object_Decode(choiceRetrieved, octets, decodeError);

        if (res != ITS_SUCCESS)
        {
            ASN_Tag_Destruct(choiceTag);
            ASN_Object_Destruct(choiceRetrieved);

            return res;
        }

        if (ASN_CHOICE_CHOICE(object) != NULL)
        {
            ASN_Object_Destruct(ASN_CHOICE_CHOICE(object));
        }

        ASN_CHOICE_CHOICE(object) = choiceRetrieved;
    }
    else
    {
        *decodeError =
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_UNKNOWN_CHOICE,
                object,
                octets);

        ASN_Tag_Destruct(choiceTag);

        return ITS_E_ASN_DECODE_ERROR;
    }

    ASN_Tag_Destruct(choiceTag);

    /* Decode check begin. */

    choice = ASN_CHOICE_CHOICE(object);

    ASN_C_ASSERT(choice != NULL);

    choiceDescription = ASN_OBJECT_DESCRIPTION(choice);

    ASN_C_ASSERT(choiceDescription != NULL);

    if (!ASN_DescChoice_ContainsTag(
                                description, 
                                ASN_DescObject_TagIdentity(choiceDescription)))
    {
        *decodeError = 
            ASN_CONSTRUCT_DECODE_ERROR(
                ASN_E_INVALID_CHOICE,
                object,
                octets);

        return ITS_E_ASN_DECODE_ERROR;
    }

    /* Decode check end. */

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    return "CHOICE";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "CHOICE";
}

static char*
ToString(const ASN_Object object)
{
    char* result                = NULL;
    char* buffer                = NULL;
    const char* nameStr         = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr     = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);
    char* toString              = NULL;
    char* toStringLineShifted   = NULL;
    size_t maxStringSize        = 0;
    ASN_Object choice           = NULL;

    ASN_C_REQUIRE(object != NULL);

    maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 32;

    choice = ASN_CHOICE_CHOICE(object);

    if (choice != NULL)
    {
        toString = ASN_Object_ToString(choice);

        if (toString == NULL)
        {
            return NULL;
        }

        toStringLineShifted = ASN_AddLineShift(toString);

        if (toStringLineShifted == NULL)
        {
            free(toString);
            return NULL;
        }

        free(toString);
        toString = NULL;

        maxStringSize += strlen(toStringLineShifted);
    }
    else
    {
        maxStringSize += 0;
    }

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        if (toStringLineShifted != NULL)
        {
            free(toStringLineShifted);
            toStringLineShifted = NULL;
        }

        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "%s (%s)\n{\n",
        nameStr,
        baseNameStr);

    if (toStringLineShifted != NULL)
    {
        strcat(buffer, toStringLineShifted);
    }
    else
    {
        strcat(buffer, "\n");
    }

    strcat(buffer, "}\n");

    if (toStringLineShifted != NULL)
    {
        free(toStringLineShifted);
        toStringLineShifted = NULL;
    }

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ASSERT(result != NULL);

    return result;
}

/*
 *  ASN_Choice class record.
 */ 

ASN_Choice_ClassRec itsASN_Choice_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,
        sizeof(ASN_Choice_ObjectRec),    
        ITS_FALSE,                         
        0,                                 
        ASN_CHOICE_CLASS_NAME,           
        ITS_CLASS_NO_INIT,                 
        ITS_CLASS_NO_DEST,  
        ClassPartConstruct,                
        ClassPartDestruct,                 
        Construct,                         
        Destruct,                          
        Clone,                             
        ITS_INST_PRINT_INHERIT,            
        ITS_INST_SERIAL_INHERIT,           
        Equals,                            
        ITS_INST_HASH_INHERIT,             
        NULL                               
    },

    /* ASN_Object class part. */

    {
        Encode,       
        Decode,       
        GetName,      
        GetBaseName,  
        ToString,     
        ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT,
        ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT
    },

    /* ASN_Choice class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetChoice,
        SetChoice,
        Contains,
        ContainsChoice
    }
};

ASN_Choice 
ASN_Choice_ConstructDefault()
{
    ASN_Choice result = NULL;

    result = (ASN_Choice)ITS_ConstructObject((ITS_Class)&itsASN_Choice_ClassRec, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_Choice 
ASN_Choice_ConstructWithDescription(ASN_DescChoice description)
{
    ASN_Choice result = NULL;

    result = (ASN_Choice)ITS_ConstructObject((ITS_Class)&itsASN_Choice_ClassRec, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_Choice_Destruct(ASN_Choice object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_Choice 
ASN_Choice_Clone(const ASN_Choice object)
{
    return (ASN_Choice)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_Choice_Equals(const ASN_Choice object, const ASN_Choice other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescChoice 
ASN_Choice_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_Choice_DestructStaticDescription()
{
    DestructStaticDescription();
}

const ASN_Object
ASN_Choice_GetChoice(const ASN_Choice object)
{
    return ASN_CHOICE_CLASS_GET_CHOICE(ITS_OBJ_CLASS(object))(object);
}

void
ASN_Choice_SetChoice(ASN_Choice object, ASN_Object choice)
{
    ASN_CHOICE_CLASS_SET_CHOICE(ITS_OBJ_CLASS(object))(object, choice);
}

ITS_BOOLEAN
ASN_Choice_Contains(const ASN_Choice object, const ASN_Tag tag)
{
    return ASN_CHOICE_CLASS_CONTAINS(ITS_OBJ_CLASS(object))(object, tag);
}

ITS_BOOLEAN
ASN_Choice_ContainsChoice(const ASN_Choice object)
{
    return ASN_CHOICE_CLASS_CONTAINS_CHOICE(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_Choice_Encode(ASN_Choice object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_Choice_Decode(ASN_Choice object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_Choice_GetName(const ASN_Choice object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_Choice_GetBaseName(const ASN_Choice object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_Choice_Print(const ASN_Choice object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_Choice_ToString(const ASN_Choice object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



