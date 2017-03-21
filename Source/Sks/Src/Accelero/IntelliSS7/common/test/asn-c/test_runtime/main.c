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
 *  ID: $Id: main.c,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  ASN.1 runtime (V2) quick test. Memory leak detection under WIN32.
 */

/*----------------------------------------------------------------------------*/

#include <stdio.h>

#if defined(WIN32)

#include <crtdbg.h>

#endif /* defined(WIN32) */

#include <its.h>

#include <asn_integer.h>
#include <asn_octet_string.h>
#include <asn_sequence.h>
#include <asn_set.h>
#include <asn_sequence_of.h>
#include <asn_choice.h>
#include <asn_boolean.h>
#include <asn_bit_string.h>
#include <asn_object_identifier.h>
#include <asn_desc_integer.h>
#include <asn_desc_octet_string.h>
#include <asn_desc_sequence.h>
#include <asn_desc_set.h>
#include <asn_desc_sequence_of.h>
#include <asn_desc_choice.h>
#include <asn_desc_boolean.h>
#include <asn_desc_bit_string.h>
#include <asn_desc_object_identifier.h>
#include <asn_octets.h>
#include <asn_linked_list.h>
#include <asn_tag.h>
#include <asn_length.h>


#if defined(WIN32)

/*
 *  The following macros set and clear, respectively, given bits of the C
 *  runtime library debug flag, as specified by a bitmask.
 */

#if defined(_DEBUG)

#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#else /* !defined(_DEBUG) */

#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)

#endif /* defined(_DEBUG) */

#endif /* defined(WIN32) */


void main(int argc, char** argv)
{

#if defined(WIN32)
    
   /*
    * Send all reports to STDOUT.
    */

    /*

   _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
   _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
   _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
   _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

   */

   /*
    * Set the debug-heap flag so that freed blocks are kept on the linked list,
    * to catch any inadvertent use of freed memory
    */ 

   SET_CRT_DEBUG_FIELD(_CRTDBG_DELAY_FREE_MEM_DF);

   /*
    * Set the debug-heap flag so that memory leaks are reported when the process
    * terminates. Then, exit.
    */

   SET_CRT_DEBUG_FIELD(_CRTDBG_LEAK_CHECK_DF);

#endif /* defined(WIN32) */

    /* Should be done through ITS_AddFeature(). */

    ASN_Initialize();


    /***************************************************************************
     *
     *  Test partially ASN_Integer and ASN_Octets.
     *
     */

    {
        const char* name                = NULL;
        ASN_Octets octets               = NULL;
        ASN_Octets octetsOther          = NULL;
        size_t size                     = 0;
        ITS_OCTET array[]               = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                            0x07, 0x08, 0x09, 0x10, 0x11, 0x12 };
        ASN_Integer integer             = NULL;
        ASN_DescInteger descInteger     = NULL;
        ITS_BOOLEAN b                   = ITS_FALSE;
        char* str                       = NULL;

        integer = ASN_Integer_ConstructWithValue(1999);

        descInteger = (ASN_DescInteger)ASN_OBJECT_DESCRIPTION(integer);

        name = ASN_Integer_GetName(integer);

        str = ASN_Integer_ToString(integer);

        free(str);

        str = NULL;

        ASN_Integer_Print(integer);


        ASN_Integer_Destruct(integer);


        octets = ASN_Octets_ConstructDefault();

        size = ASN_Octets_GetSize(octets);

        ASN_Octets_SetArray(octets, array, 12);

        ASN_Octets_Print(octets);

        

        ASN_Octets_PrintWithOffset(octets);

        octetsOther = ASN_Octets_Clone(octets);

        ASN_Octets_Print(octetsOther);

        ASN_Octets_PrintWithOffset(octetsOther);

        ASN_Octets_Destruct(octets);

        ASN_Octets_Destruct(octetsOther);

    }


    /***************************************************************************
     *
     *  Test partially ASN_LinkedList.
     *
     */

    {
        ASN_Integer integer         = NULL;
        ASN_Integer integer1        = NULL;
        ASN_Integer integer2        = NULL;
        ASN_Integer integer3        = NULL;
        ASN_Integer integer4        = NULL;
        ASN_LinkedList linkedList   = NULL;

        integer1 = ASN_Integer_ConstructWithValue(2001);
        integer2 = ASN_Integer_ConstructWithValue(2002);
        integer3 = ASN_Integer_ConstructWithValue(2003);
        integer4 = ASN_Integer_ConstructWithValue(2004);


        linkedList = ASN_LinkedList_ConstructDefault();

        ASN_LinkedList_PushBack(linkedList, (ITS_Object)integer3);
        ASN_LinkedList_PushBack(linkedList, (ITS_Object)integer4);
        ASN_LinkedList_PushFront(linkedList, (ITS_Object)integer2);
        ASN_LinkedList_PushFront(linkedList, (ITS_Object)integer1);


        ASN_LinkedList_CursorSetBegin(linkedList);

        while (!ASN_LinkedList_CursorIsEnd(linkedList))
        {
            ASN_Integer integer = NULL;

            integer = (ASN_Integer)ASN_LinkedList_CursorGetElement(linkedList);

            printf("\n\n");

            ASN_Integer_Print(integer);

            ASN_LinkedList_CursorForth(linkedList);
        }

        printf("\n\n");

        integer = (ASN_Integer)ASN_LinkedList_GetFront(linkedList);

        ASN_Integer_Print(integer);

        printf("\n\n");

        ASN_LinkedList_PopFront(linkedList);

        integer = (ASN_Integer)ASN_LinkedList_GetBack(linkedList);

        ASN_Integer_Print(integer);

        printf("\n\n");

        ASN_LinkedList_PopBack(linkedList);

        ASN_LinkedList_CursorSetBegin(linkedList);

        while (!ASN_LinkedList_CursorIsEnd(linkedList))
        {
            ASN_Integer integer = NULL;

            integer = (ASN_Integer)ASN_LinkedList_CursorGetElement(linkedList);

            printf("\n\n");

            ASN_Integer_Print(integer);

            ASN_LinkedList_CursorForth(linkedList);
        }

        ASN_LinkedList_Destruct(linkedList);

        ASN_Integer_Destruct(integer1);
        ASN_Integer_Destruct(integer2);
        ASN_Integer_Destruct(integer3);
        ASN_Integer_Destruct(integer4);

    }


    /***************************************************************************
     *
     *  Test partially ASN_Tag.
     *
     */

    {
        ASN_Octets octetsTag        = NULL;
        ASN_Tag tag1                = NULL;
        ASN_Tag tag2                = NULL;
        ASN_EncodeError encodeError = NULL;
        ASN_DecodeError decodeError = NULL;
        int res = 0;

        tag1 = ASN_Tag_ConstructWithClassTypeNumber(3, 1, 1999);

        printf("\n\n");

        ASN_Tag_Print(tag1);

        printf("\n\n");

        res = ASN_Tag_Encode(tag1, &octetsTag, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        tag2 = ASN_Tag_ConstructDefault();

        res = ASN_Tag_Decode(tag2, octetsTag, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Tag_Print(tag2);

        printf("\n\n");

        if (octetsTag != NULL)
        {
            ASN_Octets_Destruct(octetsTag);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Tag_Destruct(tag1);

        ASN_Tag_Destruct(tag2);
    }

    /***************************************************************************
     *
     *  Test partially ASN_Length.
     *
     */

    {
        ASN_Octets octetsLength     = NULL;
        ASN_Length length1          = NULL;
        ASN_Length length2          = NULL;
        ASN_EncodeError encodeError = NULL;
        ASN_DecodeError decodeError = NULL;
        int res = 0;

        length1 = ASN_Length_ConstructWithLength(12222);

        printf("\n\n");

        ASN_Length_Print(length1);

        printf("\n\n");

        res = ASN_Length_Encode(length1, &octetsLength, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        length2 = ASN_Length_ConstructDefault();

        res = ASN_Length_Decode(length2, octetsLength, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Length_Print(length2);

        printf("\n\n");

        if (octetsLength != NULL)
        {
            ASN_Octets_Destruct(octetsLength);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Length_Destruct(length1);

        ASN_Length_Destruct(length2);
    }    


    /***************************************************************************
     *
     *  Test partially ASN_Integer.
     *
     */

    {
        ASN_Integer integer         = NULL;
        ASN_Integer integerAfter    = NULL;
        ASN_EncodeError encodeError = NULL;
        ASN_DecodeError decodeError = NULL;
        ASN_Octets octets           = NULL;
        int res                     = 0;
        char* str                   = NULL;

        integer = ASN_Integer_ConstructWithValue(1999);

        printf("\n\n");

        ASN_Integer_Print(integer);

        printf("\n\n");

        res = ASN_Integer_Encode(integer, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        integerAfter = ASN_Integer_ConstructDefault();

        res = ASN_Integer_Decode(integerAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Integer_Print(integerAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Integer_Destruct(integer);

        ASN_Integer_Destruct(integerAfter);
    }


    /***************************************************************************
     *
     *  Test partially ASN_OctetString.
     *
     */

    {
        ASN_OctetString octetString         = NULL;
        ASN_OctetString octetStringAfter    = NULL;
        ASN_EncodeError encodeError         = NULL;
        ASN_DecodeError decodeError         = NULL;
        ASN_Octets octets                   = NULL;
        int res                             = 0;
        char* str                           = NULL;
        ITS_OCTET array[]                   = { 0x1AU, 0x2BU, 0x3CU, 0x4DU, 0x5EU, 0x6FU };
        size_t size                         = 6;

        octetString = ASN_OctetString_ConstructWithArraySize(array, size);

        printf("\n\n");

        ASN_OctetString_Print(octetString);

        printf("\n\n");

        res = ASN_OctetString_Encode(octetString, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        octetStringAfter = ASN_OctetString_ConstructDefault();

        res = ASN_OctetString_Decode(octetStringAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_OctetString_Print(octetStringAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_OctetString_Destruct(octetString);

        ASN_OctetString_Destruct(octetStringAfter);
    }


    /***************************************************************************
     *
     *  Test partially ASN_Sequence.
     *
     */

    {
        ASN_Sequence sequence                   = NULL;
        ASN_DescSequence descSequence           = NULL;

        ASN_Integer integer1                    = NULL;
        ASN_DescInteger descInteger1            = NULL;

        ASN_Integer integer2                    = NULL;
        ASN_DescInteger descInteger2            = NULL;

        ASN_OctetString octetString             = NULL;
        ASN_DescOctetString descOctetString     = NULL;

        ASN_Tag tag                             = NULL;

        ASN_Sequence sequenceAfter              = NULL;
        ASN_Integer integer1After               = NULL;
        ASN_Integer integer2After               = NULL;
        ASN_OctetString octetStringAfter        = NULL;


        ASN_EncodeError encodeError             = NULL;
        ASN_DecodeError decodeError             = NULL;
        ASN_Octets octets                       = NULL;
        int res                                 = 0;

        ITS_OCTET arrayForOctetString[]         = { 0x1AU, 0x2BU, 0x3CU, 0x4DU, 0x5EU, 0x6FU };
        size_t sizeForOctetString               = 6;




        descInteger1 = ASN_DescInteger_ConstructDefault();

        integer1 = ASN_Integer_ConstructWithValueDescription(0, descInteger1);
        ASN_DescInteger_SetCloneForFactory(descInteger1, integer1);
        integer1 = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 1);
        ASN_DescInteger_TagAddLevel(descInteger1, tag);
        tag = NULL;


        descInteger2 = ASN_DescInteger_ConstructDefault();

        integer2 = ASN_Integer_ConstructWithValueDescription(0, descInteger2);
        ASN_DescInteger_SetCloneForFactory(descInteger2, integer2);
        integer2 = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 2);
        ASN_DescInteger_TagAddLevel(descInteger2, tag);
        tag = NULL;


        descOctetString = ASN_DescOctetString_ConstructDefault();

        octetString = ASN_OctetString_ConstructWithArraySizeDescription(NULL, 0, descOctetString);
        ASN_DescOctetString_SetCloneForFactory(descOctetString, octetString);
        octetString = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 3);
        ASN_DescOctetString_TagAddLevel(descOctetString, tag);
        tag = NULL;


        descSequence = ASN_DescSequence_ConstructWithSize(3);

        sequence = ASN_Sequence_ConstructWithSizeDescription(3, descSequence);
        ASN_DescSequence_SetCloneForFactory(descSequence, sequence);
        sequence = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_UNIVERSAL, TAG_CONSTRUCTED, TAG_SEQUENCE);
        ASN_DescSequence_TagAddLevel(descSequence, tag);
        tag = NULL;
        ASN_DescSequence_AddElement(descSequence, 0, (ASN_DescObject)descInteger1);
        ASN_DescSequence_AddElement(descSequence, 1, (ASN_DescObject)descInteger2);
        ASN_DescSequence_AddElement(descSequence, 2, (ASN_DescObject)descOctetString);


        
        integer1 = ASN_Integer_ConstructWithValue(1999);
        ASN_OBJECT_DESCRIPTION(integer1) = (ASN_DescObject)descInteger1;


        integer2 = ASN_Integer_ConstructWithValue(2001);
        ASN_OBJECT_DESCRIPTION(integer2) = (ASN_DescObject)descInteger2;


        octetString = ASN_OctetString_ConstructWithArraySize(arrayForOctetString, sizeForOctetString);
        ASN_OBJECT_DESCRIPTION(octetString) = (ASN_DescObject)descOctetString;


        sequence = ASN_Sequence_ConstructWithSize(3);
        ASN_OBJECT_DESCRIPTION(sequence) = (ASN_DescObject)descSequence;


        ASN_Sequence_AddElement(sequence, 0, (ASN_Object)integer1);
        ASN_Sequence_AddElement(sequence, 1, (ASN_Object)integer2);
        ASN_Sequence_AddElement(sequence, 2, (ASN_Object)octetString);

        printf("\n\n");

        ASN_Sequence_Print(sequence);

        printf("\n\n");

        res = ASN_Sequence_Encode(sequence, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        sequenceAfter = ASN_Sequence_ConstructWithSize(3);
        ASN_OBJECT_DESCRIPTION(sequenceAfter) = (ASN_DescObject)descSequence;

        res = ASN_Sequence_Decode(sequenceAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Sequence_Print(sequenceAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Sequence_Destruct(sequence);

        ASN_Sequence_Destruct(sequenceAfter);


        ASN_DescInteger_Destruct(descInteger1);
        ASN_DescInteger_Destruct(descInteger2);
        ASN_DescOctetString_Destruct(descOctetString);
        ASN_DescSequence_Destruct(descSequence);
    }


    /***************************************************************************
     *
     *  Test partially ASN_Set.
     *
     */

    {
        ASN_Set set                         = NULL;
        ASN_DescSet descSet                 = NULL;

        ASN_Integer integer1                = NULL;
        ASN_DescInteger descInteger1        = NULL;

        ASN_Integer integer2                = NULL;
        ASN_DescInteger descInteger2        = NULL;

        ASN_OctetString octetString         = NULL;
        ASN_DescOctetString descOctetString = NULL;

        ASN_Tag tag                         = NULL;

        ASN_Set setAfter                    = NULL;
        ASN_Integer integer1After           = NULL;
        ASN_Integer integer2After           = NULL;
        ASN_OctetString octetStringAfter    = NULL;


        ASN_EncodeError encodeError         = NULL;
        ASN_DecodeError decodeError         = NULL;
        ASN_Octets octets                   = NULL;
        int res                             = 0;

        ITS_OCTET arrayForOctetString[]     = { 0x1AU, 0x2BU, 0x3CU, 0x4DU, 0x5EU, 0x6FU };
        size_t sizeForOctetString           = 6;




        descInteger1 = ASN_DescInteger_ConstructDefault();

        integer1 = ASN_Integer_ConstructWithValueDescription(0, descInteger1);
        ASN_DescInteger_SetCloneForFactory(descInteger1, integer1);
        integer1 = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 1);
        ASN_DescInteger_TagAddLevel(descInteger1, tag);
        tag = NULL;


        descInteger2 = ASN_DescInteger_ConstructDefault();

        integer2 = ASN_Integer_ConstructWithValueDescription(0, descInteger2);
        ASN_DescInteger_SetCloneForFactory(descInteger2, integer2);
        integer2 = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 2);
        ASN_DescInteger_TagAddLevel(descInteger2, tag);
        tag = NULL;


        descOctetString = ASN_DescOctetString_ConstructDefault();

        octetString = ASN_OctetString_ConstructWithArraySizeDescription(NULL, 0, descOctetString);
        ASN_DescOctetString_SetCloneForFactory(descOctetString, octetString);
        octetString = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 3);
        ASN_DescOctetString_TagAddLevel(descOctetString, tag);
        tag = NULL;


        descSet = ASN_DescSet_ConstructWithSize(3);

        set = ASN_Set_ConstructWithSizeDescription(3, descSet);
        ASN_DescSet_SetCloneForFactory(descSet, set);
        set = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_UNIVERSAL, TAG_CONSTRUCTED, TAG_SEQUENCE);
        ASN_DescSet_TagAddLevel(descSet, tag);
        tag = NULL;
        ASN_DescSet_AddElement(descSet, 0, (ASN_DescObject)descInteger1);
        ASN_DescSet_AddElement(descSet, 1, (ASN_DescObject)descInteger2);
        ASN_DescSet_AddElement(descSet, 2, (ASN_DescObject)descOctetString);


        
        integer1 = ASN_Integer_ConstructWithValue(1999);
        ASN_OBJECT_DESCRIPTION(integer1) = (ASN_DescObject)descInteger1;


        integer2 = ASN_Integer_ConstructWithValue(2001);
        ASN_OBJECT_DESCRIPTION(integer2) = (ASN_DescObject)descInteger2;


        octetString = ASN_OctetString_ConstructWithArraySize(arrayForOctetString, sizeForOctetString);
        ASN_OBJECT_DESCRIPTION(octetString) = (ASN_DescObject)descOctetString;


        set = ASN_Set_ConstructWithSize(3);
        ASN_OBJECT_DESCRIPTION(set) = (ASN_DescObject)descSet;


        ASN_Set_AddElement(set, 0, (ASN_Object)integer1);
        ASN_Set_AddElement(set, 1, (ASN_Object)integer2);
        ASN_Set_AddElement(set, 2, (ASN_Object)octetString);

        printf("\n\n");

        ASN_Set_Print(set);

        printf("\n\n");

        res = ASN_Set_Encode(set, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        setAfter = ASN_Set_ConstructWithSize(3);
        ASN_OBJECT_DESCRIPTION(setAfter) = (ASN_DescObject)descSet;

        res = ASN_Set_Decode(setAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Set_Print(setAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Set_Destruct(set);

        ASN_Set_Destruct(setAfter);


        ASN_DescInteger_Destruct(descInteger1);
        ASN_DescInteger_Destruct(descInteger2);
        ASN_DescOctetString_Destruct(descOctetString);
        ASN_DescSet_Destruct(descSet);
    }


    /***************************************************************************
     *
     *  Test partially ASN_SequenceOf.
     *
     */

    {
        ASN_SequenceOf sequenceOf           = NULL;
        ASN_DescSequenceOf descSequenceOf   = NULL;

        ASN_Integer integer                 = NULL;
        ASN_DescInteger descInteger         = NULL;

        ASN_Tag tag                         = NULL;

        ASN_SequenceOf sequenceOfAfter      = NULL;
        ASN_Integer integerAfter            = NULL;

        ASN_EncodeError encodeError         = NULL;
        ASN_DecodeError decodeError         = NULL;
        ASN_Octets octets                   = NULL;
        int res                             = 0;

        descInteger = ASN_DescInteger_ConstructDefault();

        integer = ASN_Integer_ConstructWithValueDescription(0, descInteger);
        ASN_DescInteger_SetCloneForFactory(descInteger, integer);
        integer = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 1);
        ASN_DescInteger_TagAddLevel(descInteger, tag);
        tag = NULL;

        descSequenceOf = ASN_DescSequenceOf_ConstructDefault();

        sequenceOf = ASN_SequenceOf_ConstructWithDescription(descSequenceOf);
        ASN_DescSequenceOf_SetCloneForFactory(descSequenceOf, sequenceOf);
        sequenceOf = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_UNIVERSAL, TAG_CONSTRUCTED, TAG_SEQUENCE);
        ASN_DescSequenceOf_TagAddLevel(descSequenceOf, tag);
        tag = NULL;
        ASN_DescSequenceOf_SetElement(descSequenceOf, (ASN_DescObject)descInteger);
        
        sequenceOf = ASN_SequenceOf_ConstructDefault();
        ASN_OBJECT_DESCRIPTION(sequenceOf) = (ASN_DescObject)descSequenceOf;

        integer = ASN_Integer_ConstructWithValue(1999);
        ASN_OBJECT_DESCRIPTION(integer) = (ASN_DescObject)descInteger;
        ASN_SequenceOf_AddElement(sequenceOf, (ASN_Object)integer);
        integer = NULL;

        integer = ASN_Integer_ConstructWithValue(2000);
        ASN_OBJECT_DESCRIPTION(integer) = (ASN_DescObject)descInteger;
        ASN_SequenceOf_AddElement(sequenceOf, (ASN_Object)integer);
        integer = NULL;

        integer = ASN_Integer_ConstructWithValue(2001);
        ASN_OBJECT_DESCRIPTION(integer) = (ASN_DescObject)descInteger;
        ASN_SequenceOf_AddElement(sequenceOf, (ASN_Object)integer);
        integer = NULL;

        printf("\n\n");

        ASN_SequenceOf_Print(sequenceOf);

        printf("\n\n");

        res = ASN_SequenceOf_Encode(sequenceOf, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        sequenceOfAfter = ASN_SequenceOf_ConstructDefault();
        ASN_OBJECT_DESCRIPTION(sequenceOfAfter) = (ASN_DescObject)descSequenceOf;

        res = ASN_SequenceOf_Decode(sequenceOfAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_SequenceOf_Print(sequenceOfAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_SequenceOf_Destruct(sequenceOf);

        ASN_SequenceOf_Destruct(sequenceOfAfter);


        ASN_DescInteger_Destruct(descInteger);
        ASN_DescSequenceOf_Destruct(descSequenceOf);
    }


    /***************************************************************************
     *
     *  Test partially ASN_Choice.
     *
     */

    {
        ASN_Choice choice                   = NULL;
        ASN_DescChoice descChoice           = NULL;

        ASN_Integer integer                 = NULL;
        ASN_DescInteger descInteger         = NULL;

        ASN_OctetString octetString         = NULL;
        ASN_DescOctetString descOctetString = NULL;

        ASN_Tag tag                         = NULL;

        ASN_Choice choiceAfter              = NULL;
        ASN_Integer integerAfter            = NULL;
        ASN_OctetString octetStringAfter    = NULL;

        ASN_EncodeError encodeError         = NULL;
        ASN_DecodeError decodeError         = NULL;
        ASN_Octets octets                   = NULL;
        int res                             = 0;

        ITS_OCTET arrayForOctetString[]     = { 0x1AU, 0x2BU, 0x3CU, 0x4DU, 0x5EU, 0x6FU };
        size_t sizeForOctetString           = 6;


        descInteger = ASN_DescInteger_ConstructDefault();

        integer = ASN_Integer_ConstructWithValueDescription(0, descInteger);
        ASN_DescInteger_SetCloneForFactory(descInteger, integer);
        integer = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 1);
        ASN_DescInteger_TagAddLevel(descInteger, tag);
        tag = NULL;

        descOctetString = ASN_DescOctetString_ConstructDefault();

        octetString = ASN_OctetString_ConstructWithArraySizeDescription(NULL, 0, descOctetString);
        ASN_DescOctetString_SetCloneForFactory(descOctetString, octetString);
        octetString = NULL;
        tag = ASN_Tag_ConstructWithClassTypeNumber(TAG_CLASS_CONTEXT_SPECIFIC, TAG_PRIMITIVE, 2);
        ASN_DescOctetString_TagAddLevel(descOctetString, tag);
        tag = NULL;

        descChoice = ASN_DescChoice_ConstructWithSize(2);

        choice = ASN_Choice_ConstructWithDescription(descChoice);
        ASN_DescChoice_SetCloneForFactory(descChoice, choice);
        choice = NULL;
        ASN_DescChoice_AddChoice(descChoice, 0, (ASN_DescObject)descInteger);
        ASN_DescChoice_AddChoice(descChoice, 1, (ASN_DescObject)descOctetString);

        integer = ASN_Integer_ConstructWithValue(1999);
        ASN_OBJECT_DESCRIPTION(integer) = (ASN_DescObject)descInteger;

        octetString = ASN_OctetString_ConstructWithArraySize(arrayForOctetString, sizeForOctetString);
        ASN_OBJECT_DESCRIPTION(octetString) = (ASN_DescObject)descOctetString;

        choice = ASN_Choice_ConstructDefault();
        ASN_OBJECT_DESCRIPTION(choice) = (ASN_DescObject)descChoice;

        ASN_Choice_SetChoice(choice, (ASN_Object)octetString);

        printf("\n\n");

        ASN_Choice_Print(choice);

        printf("\n\n");

        res = ASN_Choice_Encode(choice, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        choiceAfter = ASN_Choice_ConstructDefault();
        ASN_OBJECT_DESCRIPTION(choiceAfter) = (ASN_DescObject)descChoice;

        res = ASN_Choice_Decode(choiceAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Choice_Print(choiceAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Choice_Destruct(choice);

        ASN_Choice_Destruct(choiceAfter);

        ASN_Integer_Destruct(integer);

        ASN_DescInteger_Destruct(descInteger);
        ASN_DescOctetString_Destruct(descOctetString);
        ASN_DescChoice_Destruct(descChoice);
    }


    /***************************************************************************
     *
     *  Test partially ASN_Boolean.
     *
     */

    {
        ASN_Boolean boolean         = NULL;
        ASN_Boolean booleanAfter    = NULL;
        ASN_EncodeError encodeError = NULL;
        ASN_DecodeError decodeError = NULL;
        ASN_Octets octets           = NULL;
        int res                     = 0;
        char* str                   = NULL;

        boolean = ASN_Boolean_ConstructWithValue(ITS_TRUE);

        printf("\n\n");

        ASN_Boolean_Print(boolean);

        printf("\n\n");

        res = ASN_Boolean_Encode(boolean, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        booleanAfter = ASN_Boolean_ConstructDefault();

        res = ASN_Boolean_Decode(booleanAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_Boolean_Print(booleanAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_Boolean_Destruct(boolean);

        ASN_Boolean_Destruct(booleanAfter);
    }


    /***************************************************************************
     *
     *  Test partially ASN_BitString.
     *
     */

    {
        ASN_BitString bitString         = NULL;
        ASN_BitString bitStringAfter    = NULL;
        ASN_EncodeError encodeError     = NULL;
        ASN_DecodeError decodeError     = NULL;
        ASN_Octets octets               = NULL;
        int res                         = 0;
        char* str                       = NULL;
        ITS_BOOLEAN array[]             = { ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE,
                                            ITS_TRUE, ITS_TRUE, ITS_TRUE };

        size_t size                         = 67;

        bitString = ASN_BitString_ConstructWithArraySize(array, size);

        printf("\n\n");

        ASN_BitString_Print(bitString);

        printf("\n\n");

        res = ASN_BitString_Encode(bitString, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        bitStringAfter = ASN_BitString_ConstructDefault();

        res = ASN_BitString_Decode(bitStringAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_BitString_Print(bitStringAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_BitString_Destruct(bitString);

        ASN_BitString_Destruct(bitStringAfter);
    }


    /***************************************************************************
     *
     *  Test partially ASN_ObjectIdentifier.
     *
     */

    {
        ASN_ObjectIdentifier objectIdentifier       = NULL;
        ASN_ObjectIdentifier objectIdentifierAfter  = NULL;
        ASN_EncodeError encodeError                 = NULL;
        ASN_DecodeError decodeError                 = NULL;
        ASN_Octets octets                           = NULL;
        int res                                     = 0;
        char* str                                   = NULL;
        ITS_LONG array[]                            = { 0, 2, 22, 1999, 2000, 2001 };
        size_t size                                 = 6;

        objectIdentifier = ASN_ObjectIdentifier_ConstructWithArraySize(array, size);

        printf("\n\n");

        ASN_ObjectIdentifier_Print(objectIdentifier);

        printf("\n\n");

        res = ASN_ObjectIdentifier_Encode(objectIdentifier, &octets, &encodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nEncode success...\n");
        }
        else
        {
            printf("\nEncode failure...\n");
        }

        objectIdentifierAfter = ASN_ObjectIdentifier_ConstructDefault();

        res = ASN_ObjectIdentifier_Decode(objectIdentifierAfter, octets, &decodeError);

        if (res == ITS_SUCCESS)
        {
            printf("\nDecode success...\n");
        }
        else
        {
            printf("\nDecode failure...\n");
        }

        printf("\n\n");

        ASN_ObjectIdentifier_Print(objectIdentifierAfter);

        printf("\n\n");

        if (octets != NULL)
        {
            ASN_Octets_Destruct(octets);
        }

        if (encodeError != NULL)
        {
            ASN_EncodeError_Destruct(encodeError);
        }

        if (decodeError != NULL)
        {
            ASN_DecodeError_Destruct(decodeError);
        }

        ASN_ObjectIdentifier_Destruct(objectIdentifier);

        ASN_ObjectIdentifier_Destruct(objectIdentifierAfter);
    }

    /**************************************************************************/


    /* Should be done through ITS_RemFeature in the future. */

    ASN_Integer_DestructStaticDescription();
    ASN_OctetString_DestructStaticDescription();
    ASN_Sequence_DestructStaticDescription();
    ASN_Set_DestructStaticDescription();
    ASN_SequenceOf_DestructStaticDescription();
    ASN_Choice_DestructStaticDescription();
    ASN_Boolean_DestructStaticDescription();
    ASN_BitString_DestructStaticDescription();
    ASN_ObjectIdentifier_DestructStaticDescription();

    /* Should be done through ITS_RemFeature(). */

    ASN_Terminate();


}

