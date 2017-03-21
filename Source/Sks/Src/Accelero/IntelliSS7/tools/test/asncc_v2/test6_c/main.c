/*------------------------------------------------------------------------------
 *
 * Test6 (GSMMAP V4).
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

#include <map_v4_its_feature_class_c.h>
#include <map_v4_insert_subscriber_data_arg_c.h>


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

    res = ITS_AddFeature(itsMAP_V4_Class);

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

    /*

    res = TestSpeedAndMemory();

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    */
    
    ITS_GlobalStop();

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsMAP_V4_Class);

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
    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArg  = NULL;
    MAP_V4_IMSI imsi                                        = NULL;
    MAP_V4_ISDN_AddressString iSDN_AddressString            = NULL;
    MAP_V4_Category category                                = NULL;
    MAP_V4_SubscriberStatus subscriberStatus                = NULL;
    MAP_V4_BearerServiceList bearerServiceList              = NULL;
    MAP_V4_BearerServiceCode bearerServiceCode1             = NULL;
    MAP_V4_BearerServiceCode bearerServiceCode2             = NULL;
    MAP_V4_TeleserviceList teleserviceList                  = NULL;
    MAP_V4_TeleserviceCode teleserviceCode1                 = NULL;
    MAP_V4_TeleserviceCode teleserviceCode2                 = NULL;
    MAP_V4_TeleserviceCode teleserviceCode3                 = NULL;
    MAP_V4_SS_InfoList sS_InfoList                          = NULL;
    MAP_V4_SS_Info sS_Info1                                 = NULL;
    MAP_V4_SS_Info sS_Info2                                 = NULL;
    MAP_V4_SS_Info sS_Info3                                 = NULL;
    MAP_V4_ForwardingInfo forwardingInfo                    = NULL;
    MAP_V4_SS_Code sS_Code                                  = NULL;
    MAP_V4_ForwardingFeatureList forwardingFeatureList      = NULL;
    MAP_V4_ForwardingFeature forwardingFeature              = NULL;
    MAP_V4_BasicServiceCode basicServiceCode                = NULL;
    MAP_V4_BearerServiceCode bearerServiceCode              = NULL;
    MAP_V4_ISDN_SubaddressString iSDN_SubaddressString      = NULL;
    MAP_V4_CUG_Info cUG_Info                                = NULL;
    MAP_V4_CUG_SubscriptionList cUG_SubscriptionList        = NULL;
    MAP_V4_CUG_Subscription cUG_Subscription1               = NULL;
    MAP_V4_CUG_Subscription cUG_Subscription2               = NULL;
    MAP_V4_CUG_Index cUG_Index1                             = NULL;
    MAP_V4_CUG_Index cUG_Index2                             = NULL;
    MAP_V4_CUG_Interlock cUG_Interlock1                     = NULL;
    MAP_V4_CUG_Interlock cUG_Interlock2                     = NULL;
    MAP_V4_IntraCUG_Options intraCUG_Options1               = NULL;
    MAP_V4_IntraCUG_Options intraCUG_Options2               = NULL;
    MAP_V4_SS_Data sS_Data                                  = NULL;
    MAP_V4_SS_SubscriptionOption sS_SubscriptionOption      = NULL;
    MAP_V4_CliRestrictionOption cliRestrictionOption        = NULL;
    MAP_V4_ODB_Data oDB_Data                                = NULL;
    MAP_V4_ODB_GeneralData oDB_GeneralData                  = NULL;
    MAP_V4_ODB_HPLMN_Data oDB_HPLMN_Data                    = NULL;


    ITS_OCTET array1[] = { 0x01U, 0x02U, 0x03U, 0x04U };
    size_t array1Size = 4;

    ITS_OCTET array2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };
    size_t array2Size = 5;

    ITS_OCTET array3[] = { 0x66U };
    size_t array3Size = 1;

    ITS_OCTET array4[] = { 0xAAU };
    size_t array4Size = 1;

    ITS_OCTET array5[] = { 0xBBU };
    size_t array5Size = 1;

    ITS_OCTET array6[] = { 0xCCU };
    size_t array6Size = 1;

    ITS_OCTET array7[] = { 0xDDU };
    size_t array7Size = 1;

    ITS_OCTET array8[] = { 0xEEU };
    size_t array8Size = 1;

    ITS_OCTET array9[] = { 0x33U };
    size_t array9Size = 1;

    ITS_OCTET array10[] = { 0x44U };
    size_t array10Size = 1;

    ITS_OCTET array11[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
    size_t array11Size = 8;

    ITS_OCTET array12[] = { 0x11U, 0x22U, 0x33U, 0x44U };
    size_t array12Size = 4;

    ITS_OCTET array13[] = { 0x44U, 0x33U, 0x22U, 0x11U };
    size_t array13Size = 4;

    ITS_BOOLEAN array14[] = { ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE };
    size_t array14Size = 6;

    ITS_BOOLEAN array15[] = { ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE };
    size_t array15Size = 4;


    /* Local variables used after decoding. */

    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArgAfter = NULL;


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

    insertSubscriberDataArg = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArg == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Set imsi. */

    imsi = MAP_V4_IMSI_ConstructWithArraySize(array1, array1Size);

    if (imsi == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_InsertSubscriberDataArg_SetImsi(insertSubscriberDataArg, imsi);

    /* Set msisdn. */

    iSDN_AddressString = 
        MAP_V4_ISDN_AddressString_ConstructWithArraySize(
                                                        array2,
                                                        array2Size);

    if (iSDN_AddressString == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_InsertSubscriberDataArg_SetMsisdn(
                                        insertSubscriberDataArg,
                                        iSDN_AddressString);
    
    /* Set category. */

    category = MAP_V4_Category_ConstructWithArraySize(
                                                    array3,
                                                    array3Size);

    if (category == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_InsertSubscriberDataArg_SetCategory(
                                            insertSubscriberDataArg,
                                            category);

    /* Set subscriberStatus. */

    subscriberStatus = MAP_V4_SubscriberStatus_ConstructDefault();

    if (subscriberStatus == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_SubscriberStatus_SetServiceGranted(subscriberStatus);

    MAP_V4_InsertSubscriberDataArg_SetSubscriberStatus(
                                            insertSubscriberDataArg,
                                            subscriberStatus);

    /* Set bearerServiceList. */

    bearerServiceList = MAP_V4_BearerServiceList_ConstructDefault();

    if (bearerServiceList == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Insert 2 elements (type BearerServiceCode). */

    bearerServiceCode1 = MAP_V4_BearerServiceCode_ConstructWithArraySize(
                                                                    array4,
                                                                    array4Size);

    if (bearerServiceCode1 == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_BearerServiceList_AddElement(
                                        bearerServiceList, 
                                        bearerServiceCode1);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    bearerServiceCode2 = MAP_V4_BearerServiceCode_ConstructWithArraySize(
                                                                    array5,
                                                                    array5Size);

    if (bearerServiceCode2 == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_BearerServiceList_AddElement(
                                        bearerServiceList,
                                        bearerServiceCode2);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    MAP_V4_InsertSubscriberDataArg_SetBearerServiceList(
                                                    insertSubscriberDataArg,
                                                    bearerServiceList);

    /* Set teleserviceList. */

    teleserviceList = MAP_V4_TeleserviceList_ConstructDefault();

    if (teleserviceList == NULL)
    {
        return ITS_ENOMEM;
    }

    teleserviceCode1 = MAP_V4_TeleserviceCode_ConstructWithArraySize(
                                                                array6,
                                                                array6Size);

    if (teleserviceCode1 == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode1);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    teleserviceCode2 = MAP_V4_TeleserviceCode_ConstructWithArraySize(
                                                                array7,
                                                                array7Size);

    if (teleserviceCode2 == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode2);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    teleserviceCode3 = MAP_V4_TeleserviceCode_ConstructWithArraySize(
                                                                array8,
                                                                array8Size);

    if (teleserviceCode3 == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode3);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    MAP_V4_InsertSubscriberDataArg_SetTeleserviceList(
                                                insertSubscriberDataArg,
                                                teleserviceList);

    /* Set provisionedSS (type SS_InfoList). */

    sS_InfoList = MAP_V4_SS_InfoList_ConstructDefault();

    if (sS_InfoList == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Insert 3 elements (type SS_Info). */

    /* First element. */

    sS_Info1 = MAP_V4_SS_Info_ConstructDefault();

    if (sS_Info1 == NULL)
    {
        return ITS_ENOMEM;
    }

    /* First element choice is forwardingInfo. */

    forwardingInfo = MAP_V4_ForwardingInfo_ConstructDefault();

    if (forwardingInfo == NULL)
    {
        return ITS_ENOMEM;
    }

    sS_Code = MAP_V4_SS_Code_ConstructWithArraySize(
                                                array9,
                                                array9Size);

    if (sS_Code == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_ForwardingInfo_SetSs_Code(forwardingInfo, sS_Code);

    forwardingFeatureList = MAP_V4_ForwardingFeatureList_ConstructDefault();

    if (forwardingFeatureList == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Insert 1 element (type ForwardingFeature). */

    forwardingFeature = MAP_V4_ForwardingFeature_ConstructDefault();

    basicServiceCode = MAP_V4_BasicServiceCode_ConstructDefault();

    bearerServiceCode = MAP_V4_BearerServiceCode_ConstructWithArraySize(
                                                                array10,
                                                                array10Size);

    if (bearerServiceCode == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_BasicServiceCode_SetChoiceBearerService(
                                            basicServiceCode, 
                                            bearerServiceCode);

    MAP_V4_ForwardingFeature_SetBasicService(
                                        forwardingFeature,
                                        basicServiceCode);

    iSDN_SubaddressString = 
        MAP_V4_ISDN_SubaddressString_ConstructWithArraySize(
                                                        array11,
                                                        array11Size);

    if (iSDN_SubaddressString == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_ForwardingFeature_SetForwardedToSubaddress(
                                            forwardingFeature, 
                                            iSDN_SubaddressString);

    res = MAP_V4_ForwardingFeatureList_AddElement(
                                            forwardingFeatureList,
                                            forwardingFeature);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    MAP_V4_ForwardingInfo_SetForwardingFeatureList(
                                            forwardingInfo,
                                            forwardingFeatureList);

    MAP_V4_SS_Info_SetChoiceForwardingInfo(
                                        sS_Info1,
                                        forwardingInfo);

    res = MAP_V4_SS_InfoList_AddElement(
                                    sS_InfoList,
                                    sS_Info1);

    /* Second element. */

    sS_Info2 = MAP_V4_SS_Info_ConstructDefault();

    if (sS_Info2 == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Second element choice is cug-Info. */
    
    cUG_Info = MAP_V4_CUG_Info_ConstructDefault();

    if (cUG_Info == NULL)
    {
        return ITS_ENOMEM;
    }

    cUG_SubscriptionList = MAP_V4_CUG_SubscriptionList_ConstructDefault();

    if (cUG_SubscriptionList == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Insert 2 elements (type CUG_Subscription). */

    cUG_Subscription1 = MAP_V4_CUG_Subscription_ConstructDefault();

    if (cUG_Subscription1 == NULL)
    {
        return ITS_ENOMEM;
    }

    cUG_Index1 = MAP_V4_CUG_Index_ConstructWithValue(1999l);

    if (cUG_Index1 == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_CUG_Subscription_SetCug_Index(cUG_Subscription1, cUG_Index1);

    cUG_Interlock1 = MAP_V4_CUG_Interlock_ConstructWithArraySize(array12, array12Size);

    if (cUG_Interlock1 == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_CUG_Subscription_SetCug_Interlock(cUG_Subscription1, cUG_Interlock1);

    intraCUG_Options1 = MAP_V4_IntraCUG_Options_ConstructDefault();

    if (intraCUG_Options1 == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_IntraCUG_Options_SetNoCUG_Restrictions(intraCUG_Options1);

    MAP_V4_CUG_Subscription_SetIntraCUG_Options(cUG_Subscription1, intraCUG_Options1);

    res = MAP_V4_CUG_SubscriptionList_AddElement(cUG_SubscriptionList, cUG_Subscription1);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    cUG_Subscription2 = MAP_V4_CUG_Subscription_ConstructDefault();

    if (cUG_Subscription2 == NULL)
    {
        return ITS_ENOMEM;
    }

    cUG_Index2 = MAP_V4_CUG_Index_ConstructWithValue(2001l);

    if (cUG_Index2 == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_CUG_Subscription_SetCug_Index(cUG_Subscription2, cUG_Index2);

    cUG_Interlock2 = MAP_V4_CUG_Interlock_ConstructWithArraySize(array13, array13Size);

    if (cUG_Interlock2 == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_CUG_Subscription_SetCug_Interlock(cUG_Subscription2, cUG_Interlock2);

    intraCUG_Options2 = MAP_V4_IntraCUG_Options_ConstructDefault();

    if (intraCUG_Options2 == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_IntraCUG_Options_SetNoCUG_Restrictions(intraCUG_Options2);

    MAP_V4_CUG_Subscription_SetIntraCUG_Options(cUG_Subscription2, intraCUG_Options2);

    res = MAP_V4_CUG_SubscriptionList_AddElement(cUG_SubscriptionList, cUG_Subscription2);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    MAP_V4_CUG_Info_SetCug_SubscriptionList(cUG_Info, cUG_SubscriptionList);

    MAP_V4_SS_Info_SetChoiceCug_Info(sS_Info2, cUG_Info);

    res = MAP_V4_SS_InfoList_AddElement(sS_InfoList, sS_Info2);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    /* Third element. */

    sS_Info3 = MAP_V4_SS_Info_ConstructDefault();

    /* Third element choice is ss-Data. */

    sS_Data = MAP_V4_SS_Data_ConstructDefault();

    sS_SubscriptionOption = MAP_V4_SS_SubscriptionOption_ConstructDefault();

    if (sS_SubscriptionOption == NULL)
    {
        return ITS_ENOMEM;
    }

    cliRestrictionOption = MAP_V4_CliRestrictionOption_ConstructDefault();

    if (cliRestrictionOption == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_CliRestrictionOption_SetTemporaryDefaultRestricted(
                                                    cliRestrictionOption);

    MAP_V4_SS_SubscriptionOption_SetChoiceCliRestrictionOption(
                                                    sS_SubscriptionOption,
                                                    cliRestrictionOption);

    MAP_V4_SS_Data_SetSs_SubscriptionOption(
                                        sS_Data, 
                                        sS_SubscriptionOption);

    MAP_V4_SS_Info_SetChoiceSs_Data(sS_Info3, sS_Data);

    res = MAP_V4_SS_InfoList_AddElement(sS_InfoList, sS_Info3);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    MAP_V4_InsertSubscriberDataArg_SetProvisionedSS(insertSubscriberDataArg, sS_InfoList);

    /* Set odb-Data. */

    oDB_Data = MAP_V4_ODB_Data_ConstructDefault();

    if (oDB_Data == NULL)
    {
        return ITS_ENOMEM;
    }

    oDB_GeneralData = MAP_V4_ODB_GeneralData_ConstructWithArraySize(
                                                                array14, 
                                                                array14Size);

    if (oDB_GeneralData == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_ODB_Data_SetOdb_GeneralData(oDB_Data, oDB_GeneralData);

    oDB_HPLMN_Data = MAP_V4_ODB_HPLMN_Data_ConstructWithArraySize(
                                                                array15,
                                                                array15Size);

    if (oDB_HPLMN_Data == NULL)
    {
        return ITS_ENOMEM;
    }

    MAP_V4_ODB_Data_SetOdb_HPLMN_Data(oDB_Data, oDB_HPLMN_Data);

    MAP_V4_InsertSubscriberDataArg_SetOdb_Data(
                                            insertSubscriberDataArg, 
                                            oDB_Data);


    /*------------------------------------------------------------------------*/
    /* Encode ASN.1 object.                                                   */
    /*------------------------------------------------------------------------*/

    res = MAP_V4_InsertSubscriberDataArg_Encode(
                                insertSubscriberDataArg, 
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


        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

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

    insertSubscriberDataArgAfter = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArgAfter == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_InsertSubscriberDataArg_Decode(
                                insertSubscriberDataArgAfter, 
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


        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

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

    /* To be done. */


    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 decoded object.                                */
    /*------------------------------------------------------------------------*/

    if (testPrint)
    {
        printf("\nPrinting decoded FeatureRequestRRL...\n\n");

        MAP_V4_InsertSubscriberDataArg_Print(insertSubscriberDataArgAfter);

        printf("\n");
    }


    /*------------------------------------------------------------------------*/
    /* Release all the memory.                                                */
    /*------------------------------------------------------------------------*/

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

    ASN_Octets_Destruct(octets);

    return ITS_SUCCESS;
}


int
TestSpeedAndMemory()
{
    long i = 0;

    printf("\nBegin performance test (code/decode)...\n");

    testPrint = ITS_FALSE;

    for (i = 0; i < 2000l; i++)
    {
       int res = TestLRF();
    }

    testPrint = ITS_FALSE;

    printf("\nEnd performance test (code/decode)...\n");

    return ITS_SUCCESS;
}