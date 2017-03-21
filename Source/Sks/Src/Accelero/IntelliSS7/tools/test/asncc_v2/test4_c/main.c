/*------------------------------------------------------------------------------
 *
 * Test4 (equivalent to Test2 but uses Local Reference Format).
 *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <conio.h>

#if defined(WIN32)
#include <crtdbg.h>
#endif /* defined(WIN32) */

#include <its.h>
#include <its_ss7_stubs.h>

#include <asn_common.h>

#include <test4_its_feature_class_c.h>
#include <test4_feature_request_rrl_c.h>


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


static int TestLRF();
static int TestSpeedAndMemory();

static ITS_BOOLEAN testPrint = ITS_TRUE;


int 
main(int argc, char** argv)
{
    int res = ITS_SUCCESS;

#if defined(WIN32)

    /*
     *  Note: MUST NOT be enabled if TestSpeedAndMemory. Responsible for using
     *  all the available heap memory (like an invisible leak).
     *
     */
    
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
     *  Set the debug-heap flag so that freed blocks are kept on the linked
     *  list, to catch any inadvertent use of freed memory
     *
     */ 

    /* SET_CRT_DEBUG_FIELD(_CRTDBG_DELAY_FREE_MEM_DF); */


    /*
     *  Set the debug-heap flag so that memory leaks are reported when the
     *  process terminates. Then, exit.
     *
     */

    /* SET_CRT_DEBUG_FIELD(_CRTDBG_LEAK_CHECK_DF); */

#endif /* defined(WIN32) */

    printf("Begin test...\n");

    res = ITS_AddFeature(itsASN_C_RUNTIME_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = ITS_AddFeature(itsTEST4_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = ITS_GlobalStart(0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = TestLRF();

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = TestSpeedAndMemory();

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }
    
    ITS_GlobalStop();

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsTEST4_Class);

    printf("End of test...\n");

    /* To stop here in console application. */

    printf("Type any key to quit...\n");

    {
        char c = getch();
    }

    return EXIT_SUCCESS;
}


int 
TestLRF()
{
    /* Local variables used before encoding. */

    TEST4_FeatureRequestRRL featureRequestRRL               = NULL;
    TEST4_FeatureResult featureResult                       = NULL;
    TEST4_GroupInformation groupInformation                 = NULL;
    TEST4_TerminationList terminationList                   = NULL;
    TEST4_TerminationList_CHOICE choice1                    = NULL;
    TEST4_TerminationList_CHOICE choice2                    = NULL;
    TEST4_LocalTermination localTermination                 = NULL;
    TEST4_ElectronicSerialNumber electronicSerialNumber     = NULL;
    TEST4_AlertCode alertCode                               = NULL;
    TEST4_PSTNTermination pSTNTermination                   = NULL;
    TEST4_DestinationDigits destinationDigits               = NULL;
    TEST4_CarrierDigits carrierDigits                       = NULL;

    ITS_OCTET array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };
    size_t array1Size = 4;

    ITS_OCTET array2[] = { 0x01U, 0x02U, 0x03U, 0x04U };
    size_t array2Size = 4;

    ITS_OCTET array3[] = { 0xF1U, 0xF2U };
    size_t array3Size = 2;

    ITS_OCTET array4[] = { 0x10U, 0x20U, 0x30U, 0x40U, 0x50U };
    size_t array4Size = 5;

    ITS_OCTET array5[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U };
    size_t array5Size = 7;


    /* Local variables used after decoding. */

    TEST4_FeatureRequestRRL featureRequestRRLAfter              = NULL;
    TEST4_FeatureResult featureResultAfter                      = NULL;
    TEST4_GroupInformation groupInformationAfter                = NULL;
    TEST4_TerminationList terminationListAfter                  = NULL;
    TEST4_TerminationList_CHOICE choice1After                   = NULL;
    TEST4_TerminationList_CHOICE choice2After                   = NULL;
    TEST4_LocalTermination localTerminationAfter                = NULL;
    TEST4_ElectronicSerialNumber electronicSerialNumberAfter    = NULL;
    TEST4_AlertCode alertCodeAfter                              = NULL;
    TEST4_PSTNTermination pSTNTerminationAfter                  = NULL;
    TEST4_DestinationDigits destinationDigitsAfter              = NULL;
    TEST4_CarrierDigits carrierDigitsAfter                      = NULL;


    /* Local variables used for encoding and decoding. */

    ASN_Octets octets                   = NULL;
    ASN_EncodeError encodeError         = NULL;
    ASN_DecodeError decodeError         = NULL;

    int res                             = ITS_SUCCESS;

    int encodeErrorCode                 = ITS_SUCCESS;
    const char* encodeErrorText         = NULL;
    const char* encodeExtendedErrorText = NULL;

    int decodeErrorCode                 = ITS_SUCCESS;
    const char* decodeErrorText         = NULL;
    const char* decodeExtendedErrorText = NULL;


    /*------------------------------------------------------------------------*/
    /* Populate ASN.1 object to encode.                                       */
    /*------------------------------------------------------------------------*/

    featureRequestRRL = TEST4_FeatureRequestRRL_ConstructDefault();

    if (featureRequestRRL == NULL)
    {
        return ITS_ENOMEM;
    }

    featureResult = TEST4_FeatureResult_ConstructDefault();

    if (featureResult == NULL)
    {
        return ITS_ENOMEM;
    }

    TEST4_FeatureResult_SetSuccessful(featureResult);

    TEST4_FeatureRequestRRL_SetFeatureResult(featureRequestRRL, featureResult);

    groupInformation = 
        TEST4_GroupInformation_ConstructWithArraySize(
                                                    array1, 
                                                    array1Size);

    if (groupInformation == NULL)
    {
        return ITS_ENOMEM;
    }

    TEST4_FeatureRequestRRL_SetGroupInformation(
                                        featureRequestRRL, 
                                        groupInformation);

    terminationList = TEST4_TerminationList_ConstructDefault();

    if (terminationList == NULL)
    {
        return ITS_ENOMEM;
    }

    choice1 = TEST4_TerminationList_CHOICE_ConstructDefault();

    if (choice1 == NULL)
    { 
        return ITS_ENOMEM;
    }

    localTermination = TEST4_LocalTermination_ConstructDefault();

    if (localTermination == NULL)
    {
        return ITS_ENOMEM;
    }

    electronicSerialNumber = 
        TEST4_ElectronicSerialNumber_ConstructWithArraySize(
                                                        array2, 
                                                        array2Size);

    if (electronicSerialNumber == NULL)
    {
        return ITS_ENOMEM;
    }

    TEST4_LocalTermination_SetElectronicSerialNumber(
                                            localTermination, 
                                            electronicSerialNumber);

    alertCode = TEST4_AlertCode_ConstructWithArraySize(
                                                    array3, 
                                                    array3Size);

    if (alertCode == NULL)
    {
        return ITS_ENOMEM;
    }

    TEST4_LocalTermination_SetAlertCode(localTermination, alertCode);

    TEST4_TerminationList_CHOICE_SetChoiceLocalTermination(
                                                        choice1, 
                                                        localTermination);

    res = TEST4_TerminationList_AddElement(terminationList, choice1);

    if (res != ITS_SUCCESS)
    {
        return res; 
    }

    choice2 = TEST4_TerminationList_CHOICE_ConstructDefault();

    if (choice2 == NULL)
    {
        return ITS_ENOMEM;
    }

    pSTNTermination = TEST4_PSTNTermination_ConstructDefault();

    if (pSTNTermination == NULL)
    {
        return ITS_ENOMEM;
    }

    destinationDigits = TEST4_DestinationDigits_ConstructWithArraySize(
                                                                    array4, 
                                                                    array4Size);

    if (destinationDigits == NULL)
    {
        return ITS_ENOMEM;
    }

    TEST4_PSTNTermination_SetDestinationDigits(
                                        pSTNTermination, 
                                        destinationDigits);

    carrierDigits = TEST4_CarrierDigits_ConstructWithArraySize(
                                                            array5, 
                                                            array5Size);

    if (carrierDigits == NULL)
    {
        return ITS_ENOMEM;
    }

    TEST4_PSTNTermination_SetCarrierDigits(pSTNTermination, carrierDigits);

    TEST4_TerminationList_CHOICE_SetChoicePSTNTermination(
                                                        choice2, 
                                                        pSTNTermination);

    res = TEST4_TerminationList_AddElement(terminationList, choice2);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    TEST4_FeatureRequestRRL_SetTerminationList(
                                        featureRequestRRL, 
                                        terminationList);

    /*------------------------------------------------------------------------*/
    /* Encode ASN.1 object.                                                   */
    /*------------------------------------------------------------------------*/

    res = TEST4_FeatureRequestRRL_Encode(
                                featureRequestRRL, 
                                &octets, 
                                &encodeError);

    if (res == ITS_E_ASN_ENCODE_ERROR)
    {
        /*  
         *  Status:                                              
         *                                                       
         *  octets == NULL.                                      
         *  encodeError != NULL. Must be destructed by end-user. 
         */


        /* Retrieve and print encode error code. */

        encodeErrorCode = 
            ASN_EncodeError_GetError(encodeError);

        if (testPrint)
        {
            printf(
                "\nEncode error code is <%d>.\n\n", 
                encodeErrorCode);
        }


        /* 
         *  Retrieve and print encode error text (freed automatically when the
         *  encodeError object is destructed).                               
         */

        encodeErrorText = 
            ASN_EncodeError_GetErrorText(encodeError);

        if (encodeErrorText == NULL)
        {
            /* Error: out of memory. */
        }

        if (testPrint)
        {
            printf(
                "\nEncode error text is <%s>.\n\n", 
                encodeErrorText);
        }


        /* 
         *  Retrieve and print extended encode error text (freed automatically
         *  when the encodeError object is destructed).
         */

        encodeExtendedErrorText = 
            ASN_EncodeError_GetExtentedErrorText(encodeError);

        if (testPrint)
        {
            printf(
                "\nEncode error extended text is <%s>.\n\n", 
                encodeExtendedErrorText);
        }


        /* Object encodeError must be destructed by end-user. */

        ASN_EncodeError_Destruct(encodeError);


        TEST4_FeatureRequestRRL_Destruct(featureRequestRRL);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        TEST4_FeatureRequestRRL_Destruct(featureRequestRRL);

        return res;
    }
    else
    {
        /* res == ITS_SUCCESS. Nothing to do. Continue processing. */
    }


    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 encoded value.                                 */
    /*------------------------------------------------------------------------*/

    if (testPrint)
    {
        printf("\nPrinting ASN.1 encoded value...\n\n");

        ASN_Octets_Print(octets);

        printf("\n");
    }


    /*------------------------------------------------------------------------*/
    /* Decode ASN.1 object.                                                   */
    /*------------------------------------------------------------------------*/

    featureRequestRRLAfter = TEST4_FeatureRequestRRL_ConstructDefault();

    if (featureRequestRRLAfter == NULL)
    {
        return ITS_ENOMEM;
    }

    res = TEST4_FeatureRequestRRL_Decode(
                                featureRequestRRLAfter, 
                                octets, 
                                &decodeError);

    if (res == ITS_E_ASN_DECODE_ERROR)
    {
        /* 
         *  Status:                                                   
         *                                                            
         *  encodeError != NULL. Must be destructed by end-user.       
         */


        /* Retrieve and print decode error code. */

        decodeErrorCode = 
            ASN_DecodeError_GetError(decodeError);

        fprintf(
            stderr, 
            "\nDecode error code is <%d>.\n\n", 
            decodeErrorCode);


        /* 
         *  Retrieve and print decode error text (freed automatically when the
         *  decodeError object is destructed).                             
         */

        decodeErrorText = 
            ASN_DecodeError_GetErrorText(decodeError);

        if (decodeErrorText == NULL)
        {
            /* Error: out of memory. */
        }

        fprintf(
            stderr, 
            "\nDecode error text is <%s>.\n\n", 
            decodeErrorText);


        /* 
         *  Retrieve and print extended decode error text (freed automatically
         *  when the decodeError object is destructed).                       
         */

        decodeExtendedErrorText = 
            ASN_DecodeError_GetExtentedErrorText(decodeError);

        fprintf(
            stderr, 
            "\nDecode error extended text is <%s>.\n\n", 
            decodeExtendedErrorText);


        /* Object decodeError must be destructed by end-user. */

        ASN_DecodeError_Destruct(decodeError);


        TEST4_FeatureRequestRRL_Destruct(featureRequestRRL);

        TEST4_FeatureRequestRRL_Destruct(featureRequestRRLAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        TEST4_FeatureRequestRRL_Destruct(featureRequestRRL);

        TEST4_FeatureRequestRRL_Destruct(featureRequestRRLAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else
    {
        /* res == ITS_SUCCESS. Nothing to do. Continue processing. */
    }


    /*------------------------------------------------------------------------*/
    /* Show how to retrieve data from ASN.1 decoded object.                   */
    /*------------------------------------------------------------------------*/

    featureResultAfter = 
        TEST4_FeatureRequestRRL_GetFeatureResult(featureRequestRRLAfter);

    /* Should check that optional GroupInformation is present. */

    groupInformationAfter = 
        TEST4_FeatureRequestRRL_GetGroupInformation(featureRequestRRLAfter);

    /* Should check that optional TerminationList is present. */

    terminationListAfter = 
        TEST4_FeatureRequestRRL_GetTerminationList(featureRequestRRLAfter);

    choice1After = TEST4_TerminationList_GetElementAt(terminationListAfter, 0);

    choice2After = TEST4_TerminationList_GetElementAt(terminationListAfter, 1);

    if (TEST4_TerminationList_CHOICE_ChoiceLocalTermination(choice1After))
    {
        localTerminationAfter = 
            TEST4_TerminationList_CHOICE_GetChoiceLocalTermination(
                                                            choice1After);

        electronicSerialNumberAfter = 
            TEST4_LocalTermination_GetElectronicSerialNumber(
                                                        localTerminationAfter);

        alertCodeAfter = 
            TEST4_LocalTermination_GetAlertCode(localTerminationAfter);
    }

    if (TEST4_TerminationList_CHOICE_ChoicePSTNTermination(choice2After))
    {
        pSTNTerminationAfter = 
            TEST4_TerminationList_CHOICE_GetChoicePSTNTermination(
                                                            choice2After);

        destinationDigitsAfter = 
            TEST4_PSTNTermination_GetDestinationDigits(pSTNTerminationAfter);

        carrierDigitsAfter = 
            TEST4_PSTNTermination_GetCarrierDigits(pSTNTerminationAfter);
    }


    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 decoded object.                                */
    /*------------------------------------------------------------------------*/

    if (testPrint)
    {
        printf("\nPrinting decoded FeatureRequestRRL...\n\n");

        TEST4_FeatureRequestRRL_Print(featureRequestRRLAfter);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/
    /* Release all the memory.                                                */
    /*------------------------------------------------------------------------*/

    TEST4_FeatureRequestRRL_Destruct(featureRequestRRL);

    TEST4_FeatureRequestRRL_Destruct(featureRequestRRLAfter);

    ASN_Octets_Destruct(octets);

    return ITS_SUCCESS;
}


int
TestSpeedAndMemory()
{
    long i = 0;

    printf("\nBegin performance test (code/decode)...\n");

    testPrint = ITS_FALSE;

    for (i = 0; i < 10000l; i++)
    {
       int res = TestLRF();
    }

    testPrint = ITS_FALSE;

    printf("\nEnd performance test (code/decode)...\n");

    return ITS_SUCCESS;
}