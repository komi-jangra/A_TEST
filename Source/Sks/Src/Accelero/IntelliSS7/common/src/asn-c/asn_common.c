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
 *  ID: $Id: asn_common.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_common.h>
#include <its_mutex.h>

#include <asn_its_feature_class_c.h>


/*
 *  External static variables.
 */

static ITS_BOOLEAN globalDecodeSkipInvalidEnumeratedValue      = ITS_FALSE;
static ITS_BOOLEAN globalEncodeSkipInvalidEnumeratedValue      = ITS_FALSE;
static ITS_BOOLEAN globalDecodeSkipUnknownElementInSet         = ITS_FALSE;
static ITS_BOOLEAN globalDecodeIgnoreOctetStringSizeConstraint = ITS_FALSE;
static ITS_BOOLEAN globalEncodeIgnoreOctetStringSizeConstraint = ITS_FALSE;
static ITS_BOOLEAN globalDecodeIgnoreIntegerSizeConstraint     = ITS_FALSE;
static ITS_BOOLEAN globalEncodeIgnoreIntegerSizeConstraint     = ITS_FALSE;
static ITS_BOOLEAN globalDecodeIgnoreSequenceOfSizeConstraint  = ITS_FALSE;
static ITS_BOOLEAN globalEncodeIgnoreSequenceOfSizeConstraint  = ITS_FALSE;
static ITS_BOOLEAN globalDecodeIgnoreSetOfSizeConstraint       = ITS_FALSE;
static ITS_BOOLEAN globalEncodeIgnoreSetOfSizeConstraint       = ITS_FALSE;
static ITS_BOOLEAN globalDecodeIgnoreBitStringSizeConstraint   = ITS_FALSE;
static ITS_BOOLEAN globalEncodeIgnoreBitStringSizeConstraint   = ITS_FALSE;



/*-----------------------------------------------------------------*/

/* Decode Skip Invalid Enumerated Value. */

void 
ASN_Options_GlobalSetDecodeSkipInvalidEnumeratedValue()
{ 
    globalDecodeSkipInvalidEnumeratedValue = ITS_TRUE;
}

void 
ASN_Options_GlobalUnsetDecodeSkipInvalidEnumeratedValue()
{ 
    globalDecodeSkipInvalidEnumeratedValue = ITS_FALSE;
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeSkipInvalidEnumeratedValue()
{ 
    return globalDecodeSkipInvalidEnumeratedValue; 
}

/* Encode Skip Invalid Enumerated Value. */

void 
ASN_Options_GlobalSetEncodeSkipInvalidEnumeratedValue()
{ 
    globalEncodeSkipInvalidEnumeratedValue = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetEncodeSkipInvalidEnumeratedValue()
{ 
    globalEncodeSkipInvalidEnumeratedValue = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsEncodeSkipInvalidEnumeratedValue()
{ 
    return globalEncodeSkipInvalidEnumeratedValue; 
}

/*-----------------------------------------------------------------*/

/* Decode Skip Unknown Element In Set. */

void 
ASN_Options_GlobalSetDecodeSkipUnknownElementInSet()
{ 
    globalDecodeSkipUnknownElementInSet = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetDecodeSkipUnknownElementInSet()
{ 
    globalDecodeSkipUnknownElementInSet = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeSkipUnknownElementInSet()
{ 
    return globalDecodeSkipUnknownElementInSet; 
}

/*-----------------------------------------------------------------*/

/* Decode Ignore Octet String Size Constraint. */

void 
ASN_Options_GlobalSetDecodeIgnoreOctetStringSizeConstraint()
{ 
    globalDecodeIgnoreOctetStringSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetDecodeIgnoreOctetStringSizeConstraint()
{ 
    globalDecodeIgnoreOctetStringSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeIgnoreOctetStringSizeConstraint()
{ 
    return globalDecodeIgnoreOctetStringSizeConstraint; 
}

/* Encode Ignore Octet String Size Constraint. */

void 
ASN_Options_GlobalSetEncodeIgnoreOctetStringSizeConstraint()
{ 
    globalEncodeIgnoreOctetStringSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetEncodeIgnoreOctetStringSizeConstraint()
{ 
    globalEncodeIgnoreOctetStringSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsEncodeIgnoreOctetStringSizeConstraint()
{ 
    return globalEncodeIgnoreOctetStringSizeConstraint; 
}

/*-----------------------------------------------------------------*/

/* Decode Ignore Integer Size Constraint. */

void 
ASN_Options_GlobalSetDecodeIgnoreIntegerSizeConstraint()
{ 
    globalDecodeIgnoreIntegerSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetDecodeIgnoreIntegerSizeConstraint()
{ 
    globalDecodeIgnoreIntegerSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeIgnoreIntegerSizeConstraint()
{ 
    return globalDecodeIgnoreIntegerSizeConstraint; 
}

/* Encode Ignore Integer Size Constraint. */

void 
ASN_Options_GlobalSetEncodeIgnoreIntegerSizeConstraint()
{ 
    globalEncodeIgnoreIntegerSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetEncodeIgnoreIntegerSizeConstraint()
{ 
    globalEncodeIgnoreIntegerSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsEncodeIgnoreIntegerSizeConstraint()
{ 
    return globalEncodeIgnoreIntegerSizeConstraint; 
}

/*-----------------------------------------------------------------*/

/* Decode Ignore Sequence of Size Constraint. */

void 
ASN_Options_GlobalSetDecodeIgnoreSequenceOfSizeConstraint()
{ 
    globalDecodeIgnoreSequenceOfSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetDecodeIgnoreSequenceOfSizeConstraint()
{ 
    globalDecodeIgnoreSequenceOfSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeIgnoreSequenceOfSizeConstraint()
{ 
    return globalDecodeIgnoreSequenceOfSizeConstraint; 
}

/* Encode Ignore Sequence of Size Constraint. */

void 
ASN_Options_GlobalSetEncodeIgnoreSequenceOfSizeConstraint()
{ 
    globalEncodeIgnoreSequenceOfSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetEncodeIgnoreSequenceOfSizeConstraint()
{ 
    globalEncodeIgnoreSequenceOfSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsEncodeIgnoreSequenceOfSizeConstraint()
{ 
    return globalEncodeIgnoreSequenceOfSizeConstraint; 
}

/*-----------------------------------------------------------------*/

/* Decode Ignore Set of Size Constraint. */

void 
ASN_Options_GlobalSetDecodeIgnoreSetOfSizeConstraint()
{ 
    globalDecodeIgnoreSetOfSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetDecodeIgnoreSetOfSizeConstraint()
{ 
    globalDecodeIgnoreSetOfSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeIgnoreSetOfSizeConstraint()
{ 
    return globalDecodeIgnoreSetOfSizeConstraint; 
}

/* Encode Ignore Set of Size Constraint. */

void 
ASN_Options_GlobalSetEncodeIgnoreSetOfSizeConstraint()
{ 
    globalEncodeIgnoreSetOfSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetEncodeIgnoreSetOfSizeConstraint()
{ 
    globalEncodeIgnoreSetOfSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsEncodeIgnoreSetOfSizeConstraint()
{ 
    return globalEncodeIgnoreSetOfSizeConstraint; 
}

/*-----------------------------------------------------------------*/

/* Decode Ignore Bit String Size Constraint. */

void 
ASN_Options_GlobalSetDecodeIgnoreBitStringSizeConstraint()
{ 
    globalDecodeIgnoreBitStringSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetDecodeIgnoreBitStringSizeConstraint()
{ 
    globalDecodeIgnoreBitStringSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsDecodeIgnoreBitStringSizeConstraint()
{ 
    return globalDecodeIgnoreBitStringSizeConstraint; 
}

/* Encode Ignore Bit String Size Constraint. */

void 
ASN_Options_GlobalSetEncodeIgnoreBitStringSizeConstraint()
{ 
    globalEncodeIgnoreBitStringSizeConstraint = ITS_TRUE; 
}

void 
ASN_Options_GlobalUnsetEncodeIgnoreBitStringSizeConstraint()
{ 
    globalEncodeIgnoreBitStringSizeConstraint = ITS_FALSE; 
}

ITS_BOOLEAN 
ASN_Options_GlobalIsEncodeIgnoreBitStringSizeConstraint()
{ 
    return globalEncodeIgnoreBitStringSizeConstraint; 
}

/*-----------------------------------------------------------------*/

static ITS_MUTEX lock;

static int
ClassConstruct(ITS_Class objectClass)
{
    int result = ITS_SUCCESS;

    result = MUTEX_CreateMutex(&lock, 0);

    if (result != ITS_SUCCESS)
    {
        return result;
    }


    /* Construct all ASN Useful static descriptions. */

    result = ITS_CLASS_CONSTRUCTOR(itsASN_Class)(itsASN_Class);

    if (result != ITS_SUCCESS)
    {
        return result;
    }

    return ITS_SUCCESS;
}

static void
ClassDestruct(ITS_Class objectClass)
{
    MUTEX_ReleaseMutex(&lock);


    /* Destruct all ASN Useful static descriptions. */

    ITS_CLASS_DESTRUCTOR(itsASN_Class)(itsASN_Class);
}


/*
 *  ASN.1 C Runtime class record.
 */

ASN_C_RUNTIME_ClassRec itsASN_C_RUNTIME_ClassRec =
{
    /* core part */

    {
        &itsCORE_ClassRec,        
        0,                        
        ITS_FALSE,                
        0,                        
        ASN_C_RUNTIME_CLASS_NAME, 
        ClassConstruct,           
        ClassDestruct,            
        ITS_CLASS_PART_NO_INIT,   
        ITS_CLASS_PART_NO_DEST,   
        ITS_INST_NO_CONST,        
        ITS_INST_NO_DEST,         
        ITS_INST_CLONE_INHERIT,   
        ITS_INST_PRINT_INHERIT,   
        ITS_INST_SERIAL_INHERIT,  
        ITS_INST_EQUALS_INHERIT,  
        NULL                      
    }
};

ITS_Class itsASN_C_RUNTIME_Class = (ITS_Class)&itsASN_C_RUNTIME_ClassRec;

void 
ASN_Lock()
{
    int result = ITS_SUCCESS;

    result = MUTEX_AcquireMutex(&lock);

    ASN_C_ENSURE(result == ITS_SUCCESS);
}

void 
ASN_Unlock()
{
    int result = ITS_SUCCESS;

    result = MUTEX_AcquireMutex(&lock);

    ASN_C_ENSURE(result == ITS_SUCCESS);
}

/*
 *  Helper function to add a four space shift before each new line.
 */

char* 
ASN_AddLineShift(const char* str)
{
    char* result            = NULL;
    char* buffer            = NULL;
    int i                   = 0;
    int length              = 0;
    int newLines            = 0;
    size_t maxStringSize    = 0;

    ASN_C_REQUIRE(str != NULL);

    length = strlen(str);

    for (i = 0; i < length; i++)
    {
        char c = str[i];

        if (c == '\n')
        {
            newLines++;
        }
    }

    maxStringSize = length + newLines * 4 + 32;

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        return NULL;
    }

    buffer = result;

    strcat(buffer, "    ");
    buffer +=4;

    for (i = 0; i < length; i++)
    {
        char c = str[i];

        if (c == '\n' && (i < length - 1))
        {
            strcat(buffer, "\n    ");
            buffer += 5;
        }
        else
        {
            *buffer = c;
            buffer += 1;
        }
    }

    *buffer = '\0';

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  Should be used only for testing purpose or if ASN.1 C Runtime is used
 *  without IntelliSS7 (unlikely).
 */

int 
ASN_Initialize()
{
    return ClassConstruct(NULL);
}

void 
ASN_Terminate()
{
    ClassDestruct(NULL);
}





